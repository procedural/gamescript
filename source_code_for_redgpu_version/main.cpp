#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_redgpu.h"
#include <stdio.h>             // printf, fprintf
#include <stdlib.h>            // abort
#define GLFW_INCLUDE_NONE
#include "glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "glfw3native.h"
#ifdef _WIN32
#include <Windows.h> // GetModuleHandle
#endif

static RedContext               g_Instance = NULL;
static RedHandleGpuDevice       g_PhysicalDevice = NULL;
static RedHandleGpu             g_Device = NULL;
static uint32_t                 g_DeviceIndex = 0;
static uint32_t                 g_QueueFamily = 0;
static RedHandleQueue           g_Queue = NULL;
static RedHandleProcedureCache  g_PipelineCache = NULL;
static RedHandleStructsMemory   g_DescriptorPool = NULL;
static RedHandleStructsMemory   g_DescriptorPoolSamplers = NULL;

static ImGui_ImplRedGpuH_Window g_MainWindowData;
static int                      g_MinImageCount = 2;
static bool                     g_SwapChainRebuild = false;

static void SetupRedGpu()
{
    // Create REDGPU Instance
    {
        RedSdkExtension extensions[2] = {RED_SDK_EXTENSION_PROCEDURE_PARAMETERS_HANDLES, RED_SDK_EXTENSION_WSI_WIN32};
        redCreateContext(malloc, free, NULL, NULL, NULL, RED_SDK_VERSION_1_0_135, 2, (const uint32_t *)extensions, "", 0, "", 0, NULL, &g_Instance, NULL, __FILE__, __LINE__, NULL);
    }

    // Select GPU
    {
        g_PhysicalDevice = g_Instance->gpus[g_DeviceIndex].gpuDevice;
    }

    // Select Logical Device
    {
        g_Device = g_Instance->gpus[g_DeviceIndex].gpu;
        g_Queue  = g_Instance->gpus[g_DeviceIndex].queues[0];
    }

    // Create Descriptor Pool
    {
        redStructsMemoryAllocate(g_Instance, g_Device, NULL, 2, 0, 0, 2, 0, &g_DescriptorPool, NULL, __FILE__, __LINE__, NULL);
        redStructsMemoryAllocateSamplers(g_Instance, g_Device, NULL, 2, 2, &g_DescriptorPoolSamplers, NULL, __FILE__, __LINE__, NULL);
    }
}

// All the ImGui_ImplRedGpuH_XXX structures/functions are optional helpers used by the demo.
// Your real engine/app may not use them.
static void SetupRedGpuWindow(ImGui_ImplRedGpuH_Window* wd, RedHandleSurface surface, int width, int height)
{
    IM_ASSERT(surface != NULL);
    wd->Surface = surface;

    // Check for REDGPU WSI support
    RedQueueFamilyIndexGetSupportsPresentOnWin32   supportsWsiOnWin32   = {};
    RedQueueFamilyIndexGetSupportsPresentOnSurface supportsWsiOnSurface = {};
    supportsWsiOnSurface.surface = wd->Surface;
    redQueueFamilyIndexGetSupportsPresent(g_Instance, g_Device, g_QueueFamily, &supportsWsiOnWin32, NULL, NULL, &supportsWsiOnSurface, NULL, __FILE__, __LINE__, NULL);
    if (supportsWsiOnWin32.outQueueFamilyIndexSupportsPresentOnWin32 == 0 || supportsWsiOnSurface.outQueueFamilyIndexSupportsPresentOnSurface == 0)
    {
        fprintf(stderr, "Error: no REDGPU WSI support.\n");
        exit(-1);
    }

    // Select Surface Format
    wd->SurfaceFormat = ImGui_ImplRedGpuH_SelectSurfaceFormat();

    // Select Present Mode
    wd->PresentMode = ImGui_ImplRedGpuH_SelectPresentMode();

    // Create SwapChain, RenderPass, Framebuffer, etc.
    IM_ASSERT(g_MinImageCount == 2);
    ImGui_ImplRedGpuH_CreateOrResizeWindow(g_Instance, g_DeviceIndex, g_PhysicalDevice, g_Device, wd, g_QueueFamily, width, height, g_MinImageCount);
}

static void CleanupRedGpu()
{
    redStructsMemoryFree(g_Instance, g_Device, g_DescriptorPool, __FILE__, __LINE__, NULL);
    redStructsMemoryFree(g_Instance, g_Device, g_DescriptorPoolSamplers, __FILE__, __LINE__, NULL);

    redDestroyContext(g_Instance, __FILE__, __LINE__, NULL);
}

static void CleanupRedGpuWindow()
{
    ImGui_ImplRedGpuH_DestroyWindow(g_Instance, g_DeviceIndex, g_Device, &g_MainWindowData);
}

static void FrameRender(ImGui_ImplRedGpuH_Window* wd, ImDrawData* draw_data)
{
    RedCallProceduresAndAddresses cpa;
    redGetCallProceduresAndAddresses(g_Instance, g_Device, &cpa, NULL, __FILE__, __LINE__, NULL);

    RedHandleGpuSignal image_acquired_semaphore  = wd->FrameSemaphores[wd->SemaphoreIndex].ImageAcquiredSemaphore;
    RedHandleGpuSignal render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
    RedStatuses statuses = {};
    redPresentGetImageIndex(g_Instance, g_Device, wd->Swapchain, NULL, image_acquired_semaphore, &wd->FrameIndex, &statuses, __FILE__, __LINE__, NULL);
    if (statuses.statusError == RED_STATUS_ERROR_PRESENT_IS_OUT_OF_DATE || statuses.status == RED_STATUS_PRESENT_IS_SUBOPTIMAL)
    {
        g_SwapChainRebuild = true;
        return;
    }

    ImGui_ImplRedGpuH_Frame* fd = &wd->Frames[wd->FrameIndex];
    {
        redCpuSignalWait(g_Instance, g_Device, 1, &fd->Fence, 1, NULL, __FILE__, __LINE__, NULL);
        redCpuSignalUnsignal(g_Instance, g_Device, 1, &fd->Fence, NULL, __FILE__, __LINE__, NULL);
    }
    {
        redCallsSet(g_Instance, g_Device, fd->CommandBuffer.handle, fd->CommandBuffer.memory, fd->CommandBuffer.reusable, NULL, __FILE__, __LINE__, NULL);
    }
    {
        RedUsageImage imageUsage = {};
        imageUsage.barrierSplit           = RED_BARRIER_SPLIT_NONE;
        imageUsage.oldAccessStages        = 0;
        imageUsage.newAccessStages        = RED_ACCESS_STAGE_BITFLAG_OUTPUT_COLOR;
        imageUsage.oldAccess              = 0;
        imageUsage.newAccess              = RED_ACCESS_BITFLAG_OUTPUT_COLOR_W;
        imageUsage.oldState               = RED_STATE_UNUSABLE;
        imageUsage.newState               = RED_STATE_USABLE;
        imageUsage.queueFamilyIndexSource = -1;
        imageUsage.queueFamilyIndexTarget = -1;
        imageUsage.image                  = wd->Frames[wd->FrameIndex].Backbuffer;
        imageUsage.imageAllParts          = RED_IMAGE_PART_BITFLAG_COLOR;
        imageUsage.imageLevelsFirst       = 0;
        imageUsage.imageLevelsCount       = -1;
        imageUsage.imageLayersFirst       = 0;
        imageUsage.imageLayersCount       = -1;
        redCallUsageAliasOrderBarrier(cpa.redCallUsageAliasOrderBarrier, fd->CommandBuffer.handle, g_Instance, 0, NULL, 1, &imageUsage, 0, NULL, 0, NULL, 0);

        RedColorsClearValuesFloat clearValues = {};
        clearValues.r[0] = wd->ClearValues[0];
        clearValues.g[0] = wd->ClearValues[1];
        clearValues.b[0] = wd->ClearValues[2];
        clearValues.a[0] = wd->ClearValues[3];
        redCallSetProcedureOutput(cpa.redCallSetProcedureOutput, fd->CommandBuffer.handle, wd->RenderPass, fd->Framebuffer.handle, NULL, wd->Width, wd->Height, fd->Framebuffer.depthStencilEnable, fd->Framebuffer.colorsCount, 0.0f, 0, &clearValues, NULL, NULL);
    }

    // Record dear imgui primitives into command buffer
    ImGui_ImplRedGpu_RenderDrawData(draw_data, fd->CommandBuffer.handle, NULL);

    redCallEndProcedureOutput(cpa.redCallEndProcedureOutput, fd->CommandBuffer.handle);
    {
        RedUsageImage imageUsage = {};
        imageUsage.barrierSplit           = RED_BARRIER_SPLIT_NONE;
        imageUsage.oldAccessStages        = RED_ACCESS_STAGE_BITFLAG_OUTPUT_COLOR;
        imageUsage.newAccessStages        = 0;
        imageUsage.oldAccess              = RED_ACCESS_BITFLAG_OUTPUT_COLOR_W;
        imageUsage.newAccess              = 0;
        imageUsage.oldState               = RED_STATE_USABLE;
        imageUsage.newState               = RED_STATE_PRESENT;
        imageUsage.queueFamilyIndexSource = -1;
        imageUsage.queueFamilyIndexTarget = -1;
        imageUsage.image                  = wd->Frames[wd->FrameIndex].Backbuffer;
        imageUsage.imageAllParts          = RED_IMAGE_PART_BITFLAG_COLOR;
        imageUsage.imageLevelsFirst       = 0;
        imageUsage.imageLevelsCount       = -1;
        imageUsage.imageLayersFirst       = 0;
        imageUsage.imageLayersCount       = -1;
        redCallUsageAliasOrderBarrier(cpa.redCallUsageAliasOrderBarrier, fd->CommandBuffer.handle, g_Instance, 0, NULL, 1, &imageUsage, 0, NULL, 0, NULL, 0);
    }
    // Submit command buffer
    {
        redCallsEnd(g_Instance, g_Device, fd->CommandBuffer.handle, fd->CommandBuffer.memory, NULL, __FILE__, __LINE__, NULL);

        RedHandleCalls callsHandles[1] = {
          fd->CommandBuffer.handle,
        };
        RedGpuTimeline timelines[1] = {};
        uint32_t array65536[1] = {65536};
        timelines[0].setTo4                            = 4;
        timelines[0].setTo0                            = 0;
        timelines[0].waitForAndUnsignalGpuSignalsCount = 1;
        timelines[0].waitForAndUnsignalGpuSignals      = &image_acquired_semaphore;
        timelines[0].setTo65536                        = array65536;
        timelines[0].callsCount                        = 1;
        timelines[0].calls                             = callsHandles;
        timelines[0].signalGpuSignalsCount             = 1;
        timelines[0].signalGpuSignals                  = &render_complete_semaphore;
        redQueueSubmit(g_Instance, g_Device, g_Queue, 1, timelines, fd->Fence, NULL, __FILE__, __LINE__, NULL);
    }
}

static void FramePresent(ImGui_ImplRedGpuH_Window* wd)
{
    if (g_SwapChainRebuild)
        return;
    RedHandleGpuSignal render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
    RedStatuses statuses = {};
    redQueuePresent(g_Instance, g_Device, g_Queue, 1, &render_complete_semaphore, 1, &wd->Swapchain, &wd->FrameIndex, NULL, &statuses, __FILE__, __LINE__, NULL);
    if (statuses.statusError == RED_STATUS_ERROR_PRESENT_IS_OUT_OF_DATE || statuses.status == RED_STATUS_PRESENT_IS_SUBOPTIMAL)
    {
        g_SwapChainRebuild = true;
        return;
    }
    wd->SemaphoreIndex = (wd->SemaphoreIndex + 1) % wd->ImageCount; // Now we can use the next set of semaphores
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(int, char**)
{
    // Setup GLFW window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW + REDGPU example", NULL, NULL);

    SetupRedGpu();

    // Create Window Surface
    RedHandleSurface surface;
    redCreateSurfaceWin32(g_Instance, g_Device, NULL, GetModuleHandle(NULL), glfwGetWin32Window(window), &surface, NULL, __FILE__, __LINE__, NULL);

    // Create Framebuffers
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    ImGui_ImplRedGpuH_Window* wd = &g_MainWindowData;
    SetupRedGpuWindow(wd, surface, w, h);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForVulkan(window, true);
    ImGui_ImplRedGpu_InitInfo init_info = {};
    init_info.Instance = g_Instance;
    init_info.PhysicalDevice = g_PhysicalDevice;
    init_info.Device = g_Device;
    init_info.QueueFamily = g_QueueFamily;
    init_info.Queue = g_Queue;
    init_info.PipelineCache = g_PipelineCache;
    init_info.DescriptorPool = g_DescriptorPool;
    init_info.DescriptorPoolSamplers = g_DescriptorPoolSamplers;
    init_info.Subpass = 0;
    init_info.MinImageCount = g_MinImageCount;
    init_info.ImageCount = wd->ImageCount;
    init_info.MSAASamples = RED_MULTISAMPLE_COUNT_BITFLAG_1;
    ImGui_ImplRedGpu_Init(&init_info, wd->RenderPass);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Upload Fonts
    {
        // Use any command queue
        RedCalls command_buffer = wd->Frames[wd->FrameIndex].CommandBuffer;

        redCallsSet(g_Instance, g_Device, command_buffer.handle, command_buffer.memory, command_buffer.reusable, NULL, __FILE__, __LINE__, NULL);

        ImGui_ImplRedGpu_CreateFontsTexture(command_buffer.handle);

        redCallsEnd(g_Instance, g_Device, command_buffer.handle, command_buffer.memory, NULL, __FILE__, __LINE__, NULL);

        {
          RedGpuTimeline timeline = {};
          timeline.setTo4                            = 4;
          timeline.setTo0                            = 0;
          timeline.waitForAndUnsignalGpuSignalsCount = 0;
          timeline.waitForAndUnsignalGpuSignals      = 0;
          timeline.setTo65536                        = 0;
          timeline.callsCount                        = 1;
          timeline.calls                             = &command_buffer.handle;
          timeline.signalGpuSignalsCount             = 0;
          timeline.signalGpuSignals                  = 0;
          RedHandleCpuSignal cpuSignal = NULL;
          redCreateCpuSignal(g_Instance, g_Device, 0, 0, &cpuSignal, NULL, __FILE__, __LINE__, NULL);
          redQueueSubmit(g_Instance, g_Device, g_Queue, 1, &timeline, cpuSignal, NULL, __FILE__, __LINE__, NULL);
          redCpuSignalWait(g_Instance, g_Device, 1, &cpuSignal, 1, NULL, __FILE__, __LINE__, NULL);
          redDestroyCpuSignal(g_Instance, g_Device, cpuSignal, __FILE__, __LINE__, NULL);
        }

        ImGui_ImplRedGpu_DestroyFontUploadObjects();
    }

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Resize swap chain?
        if (g_SwapChainRebuild)
        {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            if (width > 0 && height > 0)
            {
                ImGui_ImplRedGpu_SetMinImageCount(g_MinImageCount, wd);
                ImGui_ImplRedGpuH_CreateOrResizeWindow(g_Instance, g_DeviceIndex, g_PhysicalDevice, g_Device, &g_MainWindowData, g_QueueFamily, width, height, g_MinImageCount);
                g_MainWindowData.FrameIndex = 0;
                g_SwapChainRebuild = false;
            }
        }

        // Start the Dear ImGui frame
        ImGui_ImplRedGpu_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        ImDrawData* draw_data = ImGui::GetDrawData();
        const bool is_minimized = (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f);
        if (!is_minimized)
        {
            wd->ClearValues[0] = clear_color.x * clear_color.w;
            wd->ClearValues[1] = clear_color.y * clear_color.w;
            wd->ClearValues[2] = clear_color.z * clear_color.w;
            wd->ClearValues[3] = clear_color.w;
            FrameRender(wd, draw_data);
            FramePresent(wd);
        }
    }

    // Cleanup
    for (uint32_t i = 0; i < wd->ImageCount; i++)
    {
        redCpuSignalWait(g_Instance, g_Device, 1, &wd->Frames[i].Fence, 1, NULL, __FILE__, __LINE__, NULL);
    }
    ImGui_ImplRedGpu_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    CleanupRedGpuWindow();
    CleanupRedGpu();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

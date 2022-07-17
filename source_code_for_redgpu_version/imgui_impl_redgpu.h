// dear imgui: Renderer Backend for REDGPU
// This needs to be used along with a Platform Backend (e.g. GLFW, SDL, Win32, custom..)

// Important: on 32-bit systems, user texture binding is only supported if your imconfig file has '#define ImTextureID ImU64'.
// See imgui_impl_redgpu.cpp file for details.

// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#pragma once
#include "imgui.h"      // IMGUI_IMPL_API

// REDGPU includes
#ifdef _WIN32
#include "C:/RedGpuSDK/redgpu.h"
#include "C:/RedGpuSDK/redgpu_wsi.h"
#else
#include "/opt/RedGpuSDK/redgpu.h"
#include "/opt/RedGpuSDK/redgpu_wsi.h"
#endif

// Initialization data, for ImGui_ImplRedGpu_Init()
// [Please zero-clear before use!]
struct ImGui_ImplRedGpu_InitInfo
{
    RedContext                      Instance;
    RedHandleGpuDevice              PhysicalDevice;
    RedHandleGpu                    Device;
    uint32_t                        DeviceIndex;
    uint32_t                        QueueFamily;
    RedHandleQueue                  Queue;
    RedHandleProcedureCache         PipelineCache;
    RedHandleStructsMemory          DescriptorPool;
    RedHandleStructsMemory          DescriptorPoolSamplers;
    uint32_t                        Subpass;
    uint32_t                        MinImageCount;          // >= 2
    uint32_t                        ImageCount;             // >= MinImageCount
    RedMultisampleCountBitflag      MSAASamples;            // >= RED_MULTISAMPLE_COUNT_BITFLAG_1 (0 -> default to RED_MULTISAMPLE_COUNT_BITFLAG_1)
};

// Called by user code
IMGUI_IMPL_API bool         ImGui_ImplRedGpu_Init(ImGui_ImplRedGpu_InitInfo* info, RedHandleOutputDeclaration render_pass);
IMGUI_IMPL_API void         ImGui_ImplRedGpu_Shutdown();
IMGUI_IMPL_API void         ImGui_ImplRedGpu_NewFrame();
IMGUI_IMPL_API void         ImGui_ImplRedGpu_RenderDrawData(ImDrawData* draw_data, RedHandleCalls command_buffer, RedHandleProcedure pipeline = NULL);
IMGUI_IMPL_API bool         ImGui_ImplRedGpu_CreateFontsTexture(RedHandleCalls command_buffer);
IMGUI_IMPL_API void         ImGui_ImplRedGpu_DestroyFontUploadObjects();

// Register a texture (RedHandleStruct == ImTextureID)
// FIXME: This is experimental in the sense that we are unsure how to best design/tackle this problem, please post to https://github.com/ocornut/imgui/pull/914 if you have suggestions.
IMGUI_IMPL_API RedHandleStruct ImGui_ImplRedGpu_AddTexture(RedHandleSampler sampler, RedHandleTexture image_view);

//-------------------------------------------------------------------------
// Internal / Miscellaneous RedGpu Helpers
// (Used by example's main.cpp. Used by multi-viewport features. PROBABLY NOT used by your own engine/app.)
//-------------------------------------------------------------------------
// You probably do NOT need to use or care about those functions.
// Those functions only exist because:
//   1) they facilitate the readability and maintenance of the multiple main.cpp examples files.
//   2) the upcoming multi-viewport feature will need them internally.
// Generally we avoid exposing any kind of superfluous high-level helpers in the backends,
// but it is too much code to duplicate everywhere so we exceptionally expose them.
//
// Your engine/app will likely _already_ have code to setup all that stuff (swap chain, render pass, frame buffers, etc.).
// You may read this code to learn about RedGpu, but it is recommended you use you own custom tailored code to do equivalent work.
// (The ImGui_ImplRedGpuH_XXX functions do not interact with any of the state used by the regular ImGui_ImplRedGpu_XXX functions)
//-------------------------------------------------------------------------

struct ImGui_ImplRedGpuH_Frame;
struct ImGui_ImplRedGpuH_Window;

IMGUI_IMPL_API void                 ImGui_ImplRedGpu_SetMinImageCount(uint32_t min_image_count, ImGui_ImplRedGpuH_Window* wd); // To override MinImageCount after initialization (e.g. if swap chain is recreated)

// Helpers
IMGUI_IMPL_API void                 ImGui_ImplRedGpuH_CreateOrResizeWindow(RedContext instance, uint32_t deviceIndex, RedHandleGpuDevice physical_device, RedHandleGpu device, ImGui_ImplRedGpuH_Window* wnd, uint32_t queue_family, int w, int h, uint32_t min_image_count);
IMGUI_IMPL_API void                 ImGui_ImplRedGpuH_DestroyWindow(RedContext instance, uint32_t deviceIndex, RedHandleGpu device, ImGui_ImplRedGpuH_Window* wnd);
IMGUI_IMPL_API RedFormat            ImGui_ImplRedGpuH_SelectSurfaceFormat();
IMGUI_IMPL_API RedPresentVsyncMode  ImGui_ImplRedGpuH_SelectPresentMode();
IMGUI_IMPL_API int                  ImGui_ImplRedGpuH_GetMinImageCountFromPresentMode(RedPresentVsyncMode present_mode);

// Helper structure to hold the data needed by one rendering frame
// (Used by example's main.cpp. Used by multi-viewport features. Probably NOT used by your own engine/app.)
// [Please zero-clear before use!]
struct ImGui_ImplRedGpuH_Frame
{
    RedCalls            CommandBuffer;
    RedHandleCpuSignal  Fence;
    RedHandleImage      Backbuffer;
    RedHandleTexture    BackbufferView;
    RedOutput           Framebuffer;
};

struct ImGui_ImplRedGpuH_FrameSemaphores
{
    RedHandleGpuSignal  ImageAcquiredSemaphore;
    RedHandleGpuSignal  RenderCompleteSemaphore;
};

// Helper structure to hold the data needed by one rendering context into one OS window
// (Used by example's main.cpp. Used by multi-viewport features. Probably NOT used by your own engine/app.)
struct ImGui_ImplRedGpuH_Window
{
    int                 Width;
    int                 Height;
    RedHandlePresent    Swapchain;
    RedHandleSurface    Surface;
    RedFormat           SurfaceFormat;
    RedPresentVsyncMode PresentMode;
    RedHandleOutputDeclaration RenderPass;
    RedHandleProcedure  Pipeline;               // The window pipeline may uses a different VkRenderPass than the one passed in ImGui_ImplRedGpu_InitInfo
    bool                ClearEnable;
    float               ClearValues[4];
    uint32_t            FrameIndex;             // Current frame being rendered to (0 <= FrameIndex < FrameInFlightCount)
    uint32_t            ImageCount;             // Number of simultaneous in-flight frames (returned by vkGetSwapchainImagesKHR, usually derived from min_image_count)
    uint32_t            SemaphoreIndex;         // Current set of swapchain wait semaphores we're using (needs to be distinct from per frame data)
    ImGui_ImplRedGpuH_Frame*            Frames;
    ImGui_ImplRedGpuH_FrameSemaphores*  FrameSemaphores;

    ImGui_ImplRedGpuH_Window()
    {
        memset((void*)this, 0, sizeof(*this));
        PresentMode = (RedPresentVsyncMode)~0;     // Ensure we get an error if user doesn't set this.
        ClearEnable = true;
    }
};


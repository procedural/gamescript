#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_redgpu.h"
#include <stdio.h>             // printf, fprintf
#include <stdlib.h>            // abort
#define GLFW_INCLUDE_NONE
#include "glfw3.h"
#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#else
#define GLFW_EXPOSE_NATIVE_X11
#endif
#include "glfw3native.h"
#ifdef _WIN32
#include <Windows.h> // GetModuleHandle
#endif

#include <malloc.h>
#include <string>
#include <sstream>   // std::stringstream
#include <fstream>
#include <mutex>

#include "script.h"

extern "C" size_t gsDroidSansMonoFontGetBytesCount();
extern "C" unsigned char gGsDroidSansMonoFont[];

static GLFWwindow *              g_Window = NULL;
static RedContext                g_Instance = NULL;
static RedHandleGpuDevice        g_PhysicalDevice = NULL;
static RedHandleGpu              g_Device = NULL;
static uint32_t                  g_DeviceIndex = 0;
static uint32_t                  g_QueueFamily = 0;
static RedHandleQueue            g_Queue = NULL;
static RedHandleProcedureCache   g_PipelineCache = NULL;
static RedHandleStructsMemory    g_DescriptorPool = NULL;
static RedHandleStructsMemory    g_DescriptorPoolSamplers = NULL;
static ImGui_ImplRedGpu_InitInfo g_RedGpuInitInfo = {};
static ImGui_ImplRedGpuH_Window  g_MainWindowData = {};
static int                       g_MinImageCount = 2;
static bool                      g_SwapChainRebuild = false;

// NOTE(Constantine): Global variables for main.cpp.
bool                       g_windowsHideAll                     = false;
static bool                g_windowsShowAll                     = false;
static bool                g_windowShowGameScript               = true;
static bool                g_windowShowUIScale                  = false;
static bool                g_windowShowCodeCurrentLine          = false;
static bool                g_windowShowCodeSaveLoad             = false;
static bool                g_windowShowCodeRun                  = true;
static bool                g_windowForceShowCodeRun             = false;
bool                       g_windowShowCodeErrors               = false;
bool                       g_windowForceShowCodeErrors          = false;
static bool                g_windowShowConsole                  = false;
static bool                g_windowForceShowConsole             = false;
static bool                g_windowShowAbout                    = false;
static bool                g_windowShowMemoryViewer             = false;
static bool                g_windowForceShowMemoryViewer        = false;
static bool                g_windowShowKeyboardOptions          = false;
static bool                g_windowShowCHeaderForRedGpu         = false;
static bool                g_windowShowLicenses                 = false;
static bool                g_windowShowListOfFunctions          = false;
static bool                g_windowShowFrame0Cache              = false;
static bool                g_windowShowCodeCompileMode          = false;
static bool                g_enableOnScreenKeyboard             = true;
static bool                g_enableDoubleNewlineWorkaround      = true;
static float               g_uiScale                            = 1.0f;
static int                 g_codeRunMode                        = 0; // 0: default, 1: run from gamescript_run.txt or gamescript_compile_and_run.txt
std::string                g_codeString;
std::string                g_codeStringCopied;
static std::string         g_codeSaveLoadFilepath               = "gamescript_autosave.txt\n";
static bool                g_codeStringHasSelection             = false;
static int                 g_codeStringSelectionStart           = 0;
static int                 g_codeStringSelectionEnd             = 0;
static uint64_t            g_codeCurrentLineNumber              = 1;
static int                 g_addKeyEventCountdownDelayCount     = 19;
static int                 g_addKeyEventCountdownLBracketKey    = 0;
static int                 g_addKeyEventCountdownRBracketKey    = 0;
static int                 g_addKeyEventCountdownEqualKey       = 0;
static int                 g_addKeyEventCountdownUnderscoreKey  = 0;
static int                 g_addKeyEventCountdownLogicalOrKey   = 0;
static int                 g_addKeyEventCountdownUpKey          = 0;
static int                 g_addKeyEventCountdownLeftKey        = 0;
static int                 g_addKeyEventCountdownDownKey        = 0;
static int                 g_addKeyEventCountdownRightKey       = 0;
bool                       g_runDefaultViewportClearCommands    = true;
static bool                g_runScriptOnce                      = false;
bool                       g_runScript                          = false;
std::string                g_codeErrorsString;
std::string                g_consoleString;
std::mutex                 __g_b042ff2_gsKeyEventsGuardAndSerializeMutex;
std::mutex                 __g_b042ff2_gsMotionEventsGuardAndSerializeMutex;
volatile uint64_t          g_keyEventsUniqueIdCounter           = 0;
uint64_t                   g_keyEventsCircularBufferMaxCount    = 50;
std::vector<GsKeyEvent>    g_keyEvents;
volatile uint64_t          g_motionEventsUniqueIdCounter        = 0;
uint64_t                   g_motionEventsCircularBufferMaxCount = 50;
std::vector<GsMotionEvent> g_motionEvents;
void *                     gExternalLibraryHandle                                  = 0;
void                     (*gExternalLibraryProcedureCall2)(double, double)         = 0;
void                     (*gExternalLibraryProcedureCall3)(double, double, double) = 0;
bool                       g_frame0CacheEnable                  = false;
bool                       g_frame0CacheStartPositionIsDirty    = true;
uint64_t                   g_frame0CacheStartPosition           = 0;
bool                       g_compileMode                        = true;

// NOTE(Constantine): Global variables and procedures from script.cpp.
extern uint64_t                                  g_currentFrame;
extern std::unordered_map<std::string, uint64_t> gGlobalArrayBytesCount;
extern std::unordered_map<std::string, void *>   gGlobalArrayPointer;
extern std::unordered_map<std::string, uint64_t> gGlobalArrayPersistentBytesCount;
extern std::unordered_map<std::string, void *>   gGlobalArrayPersistentPointer;
extern std::unordered_map<std::string, uint64_t> gGlobalSharedArrayPersistentBytesCount;
extern std::unordered_map<std::string, void *>   gGlobalSharedArrayPersistentPointer;
void scriptDestroyContext();
void scriptCompileProgram();
void scriptTick();

std::string fileRead(const char * filepath) {
  std::ostringstream ss;
  ss << std::ifstream(filepath).rdbuf();
  std::string s = ss.str();
  return s;
}

void fileWrite(const char * filepath, const char * writeString) {
  std::ofstream fs(filepath, std::ofstream::out);
  fs << writeString;
  fs.close();
}

void fileAppend(const char * filepath, const char * appendString) {
  std::ofstream fs(filepath, std::ofstream::app);
  fs << appendString;
  fs.close();
}

// NOTE(Constantine): Procedures implementations for script.cpp.

void * getInitDataPointer() {
  return (void *)&g_RedGpuInitInfo;
}

void * getWindowDataPointer() {
  return (void *)&g_MainWindowData;
}

int gamepadIsPresent(int gamepadId) {
  return glfwJoystickIsGamepad(gamepadId);
}

void gamepadGet15Buttons6AxesNumbers(int gamepadId, double * out15Buttons, double * out6Axes) {
  GLFWgamepadstate state = {};
  int status = glfwGetGamepadState(gamepadId, &state);
  out15Buttons[0]  = (double)state.buttons[0];
  out15Buttons[1]  = (double)state.buttons[1];
  out15Buttons[2]  = (double)state.buttons[2];
  out15Buttons[3]  = (double)state.buttons[3];
  out15Buttons[4]  = (double)state.buttons[4];
  out15Buttons[5]  = (double)state.buttons[5];
  out15Buttons[6]  = (double)state.buttons[6];
  out15Buttons[7]  = (double)state.buttons[7];
  out15Buttons[8]  = (double)state.buttons[8];
  out15Buttons[9]  = (double)state.buttons[9];
  out15Buttons[10] = (double)state.buttons[10];
  out15Buttons[11] = (double)state.buttons[11];
  out15Buttons[12] = (double)state.buttons[12];
  out15Buttons[13] = (double)state.buttons[13];
  out15Buttons[14] = (double)state.buttons[14];
  out6Axes[0]      = (double)state.axes[0];
  out6Axes[1]      = (double)state.axes[1];
  out6Axes[2]      = (double)state.axes[2];
  out6Axes[3]      = (double)state.axes[3];
  out6Axes[4]      = (double)state.axes[4];
  out6Axes[5]      = (double)state.axes[5];
}

int gamepadUpdateGamepadMappings(const char * mappings) {
  return glfwUpdateGamepadMappings(mappings);
}

void setClipboard(const char * text) {
  glfwSetClipboardString(g_Window, text);
}

void windowSetTitle(const char * title) {
  glfwSetWindowTitle(g_Window, title);
}

float windowGetWidth() {
  return ImGui::GetIO().DisplaySize.x;
}

float windowGetHeight() {
  return ImGui::GetIO().DisplaySize.y;
}

void igSetStyleColor(uint64_t colorIndex, float r, float g, float b, float a) {
  ImGui::GetStyle().Colors[colorIndex] = ImVec4(r, g, b, a);
}

bool igBegin(const char * name, bool * p_open, int flags) {
  return ImGui::Begin(name, p_open, flags);
}

void igEnd() {
  ImGui::End();
}

bool igButton(const char * label, float sizeX, float sizeY) {
  return ImGui::Button(label, ImVec2(sizeX, sizeY));
}

void igTextUnformatted(const char * text) {
  ImGui::TextUnformatted(text);
}

bool igInputTextMultiline(const char * label, char * buf, size_t buf_size, float sizeX, float sizeY, int flags, void * callback, void * user_data) {
  return ImGui::InputTextMultiline(label, buf, buf_size, ImVec2(sizeX, sizeY), flags, 0, 0);
}

bool igInputText(const char * label, char * buf, size_t buf_size, int flags, void * callback, void * user_data) {
  return ImGui::InputText(label, buf, buf_size, flags, 0, 0);
}

static void gsAutosaveSave() {
  std::string code = g_codeString;
  if (code.back() == '\n') {
    code.pop_back();
  }
  fileWrite("gamescript_autosave.txt", code.c_str());
}

static void gsAutosaveLoad() {
  g_codeString = fileRead("gamescript_autosave.txt");
  g_codeString += "\n";
}

static void SetupRedGpu()
{
    // Create REDGPU Instance
    {
#ifdef _WIN32
        uint32_t extensions[3] = {RED_SDK_EXTENSION_PROCEDURE_PARAMETERS_HANDLES, RED_SDK_EXTENSION_ARRAY_TIMESTAMP, RED_SDK_EXTENSION_WSI_WIN32};
#else
        uint32_t extensions[3] = {RED_SDK_EXTENSION_PROCEDURE_PARAMETERS_HANDLES, RED_SDK_EXTENSION_ARRAY_TIMESTAMP, RED_SDK_EXTENSION_WSI_XLIB};
#endif
        redCreateContext(malloc, free, NULL, NULL, NULL, RED_SDK_VERSION_1_0_135, 3, (const uint32_t *)extensions, "", 0, "", 0, NULL, &g_Instance, NULL, __FILE__, __LINE__, NULL);
        IM_ASSERT(g_Instance != NULL);
        IM_ASSERT(g_Instance->gpusCount > 0);
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
    if (
#ifdef _WIN32
        supportsWsiOnWin32.outQueueFamilyIndexSupportsPresentOnWin32 == 0 ||
#endif
        supportsWsiOnSurface.outQueueFamilyIndexSupportsPresentOnSurface == 0
    )
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
    ImGui_ImplRedGpuH_CreateOrResizeWindow(g_Instance, g_DeviceIndex, g_PhysicalDevice, g_Device, g_Queue, wd, g_QueueFamily, width, height, g_MinImageCount);
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

// NOTE(Constantine): Game Script procedures.

static int imguiCodeEditorCallback(ImGuiInputTextCallbackData * data) {
  g_frame0CacheStartPositionIsDirty = true;
  if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
    g_codeString.resize(data->BufSize);
    data->Buf = &g_codeString[0];
  }
  g_codeStringHasSelection = data->HasSelection();
  if (g_codeStringHasSelection == true) {
    g_codeStringSelectionStart = data->SelectionStart;
    g_codeStringSelectionEnd   = data->SelectionEnd;
  } else {
    g_codeStringSelectionStart = data->CursorPos;
    g_codeStringSelectionEnd   = data->CursorPos;
  }
  // NOTE(Constantine): Compute current line number.
  {
    g_codeCurrentLineNumber = 1;
    if (g_codeString.size() > 0) {
      uint64_t cursorPos = data->CursorPos;
      if (cursorPos > (g_codeString.size() - 1)) {
        cursorPos = g_codeString.size() - 1;
      }
      for (uint64_t i = 0; i < cursorPos; i += 1) {
        char c = g_codeString[i];
        if (c == '\n') {
          g_codeCurrentLineNumber += 1;
        }
      }
    }
  }
  return 0;
}

static int imguiCodeSaveLoadFilepathCallback(ImGuiInputTextCallbackData * data) {
  if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
    g_codeSaveLoadFilepath.resize(data->BufSize);
    data->Buf = &g_codeSaveLoadFilepath[0];
  }
  return 0;
}

std::string gMemoryViewerGlobalArrayNameChars;
std::string gMemoryViewerInterpretBytesChars;

static int guiMemoryViewerCallback(ImGuiInputTextCallbackData * data) {
  if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
    gMemoryViewerGlobalArrayNameChars.resize(data->BufSize);
    data->Buf = &gMemoryViewerGlobalArrayNameChars[0];
  }
  return 0;
}

static int guiMemoryViewerIntepretBytesCallback(ImGuiInputTextCallbackData * data) {
  if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
    gMemoryViewerInterpretBytesChars.resize(data->BufSize);
    data->Buf = &gMemoryViewerInterpretBytesChars[0];
  }
  return 0;
}

static std::string address_to_hex_string(uint64_t address) {
  std::stringstream ss;
  ss << std::hex << address;
  std::string result = std::string("0x") + ss.str();
  return result;
}

static std::string byte_to_binary_string(unsigned char byte) {
  char b[9];
  b[0] = (byte & REDGPU_B8(1000,0000)) == 0 ? '0' : '1';
  b[1] = (byte & REDGPU_B8(0100,0000)) == 0 ? '0' : '1';
  b[2] = (byte & REDGPU_B8(0010,0000)) == 0 ? '0' : '1';
  b[3] = (byte & REDGPU_B8(0001,0000)) == 0 ? '0' : '1';
  b[4] = (byte & REDGPU_B8(0000,1000)) == 0 ? '0' : '1';
  b[5] = (byte & REDGPU_B8(0000,0100)) == 0 ? '0' : '1';
  b[6] = (byte & REDGPU_B8(0000,0010)) == 0 ? '0' : '1';
  b[7] = (byte & REDGPU_B8(0000,0001)) == 0 ? '0' : '1';
  b[8] = 0;
  std::string result = b;
  return result;
}

void FilterTextForLineMatches(std::string & text, std::string lineMatch);

void tick()
{
    ImGuiIO& io = ImGui::GetIO();

    if (g_codeRunMode == 0) {
      if (ImGui::Begin("Windows")) {
        ImGui::Checkbox("Hide all windows", &g_windowsHideAll);
        ImGui::Checkbox("Show all windows", &g_windowsShowAll);
        ImGui::Checkbox("Show Game Script window", &g_windowShowGameScript);
        ImGui::Checkbox("Show UI Scale window", &g_windowShowUIScale);
        ImGui::Checkbox("Show Code Current Line window", &g_windowShowCodeCurrentLine);
        ImGui::Checkbox("Show Code Save Load window", &g_windowShowCodeSaveLoad);
        ImGui::Checkbox("Show Code Run window", &g_windowShowCodeRun);
        ImGui::Checkbox("Force show Code Run window", &g_windowForceShowCodeRun);
        ImGui::Checkbox("Show Code Errors window", &g_windowShowCodeErrors);
        ImGui::Checkbox("Force show Code Errors window", &g_windowForceShowCodeErrors);
        ImGui::Checkbox("Show Console window", &g_windowShowConsole);
        ImGui::Checkbox("Force show Console window", &g_windowForceShowConsole);
        ImGui::Checkbox("Show Memory Viewer window", &g_windowShowMemoryViewer);
        ImGui::Checkbox("Force show Memory Viewer window", &g_windowForceShowMemoryViewer);
        ImGui::Checkbox("Show Keyboard Options window", &g_windowShowKeyboardOptions);
        ImGui::Checkbox("Show List of Functions window", &g_windowShowListOfFunctions);
        ImGui::Checkbox("Show C Header for REDGPU window", &g_windowShowCHeaderForRedGpu);
        ImGui::Checkbox("Show Frame 0 Cache window", &g_windowShowFrame0Cache);
        ImGui::Checkbox("Show Code Compile Mode window", &g_windowShowCodeCompileMode);
        ImGui::Checkbox("Show Licenses window", &g_windowShowLicenses);
        ImGui::Checkbox("Show About window", &g_windowShowAbout);
      }
      ImGui::End();

      static bool holdShiftKey = false;
      if (g_windowsShowAll == true || (g_windowsHideAll == false && g_windowShowGameScript == true)) {
        if (ImGui::Begin("Game Script", &g_windowShowGameScript)) {
          ImGui::SetWindowSize(ImVec2(975, 700), ImGuiCond_FirstUseEver);

          if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape), false)) {
          } else {
            ImVec2 inputSize = {};
            inputSize.x = -1;
            inputSize.y = -1;
            ImGui::InputTextMultiline(" Script", &g_codeString[0], g_codeString.size(), inputSize, ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CallbackResize | ImGuiInputTextFlags_CallbackAlways, imguiCodeEditorCallback, 0);
          }
        }
        ImGui::End();
      }

      if (g_windowsShowAll == true || (g_windowsHideAll == false && g_windowShowUIScale == true)) {
        if (ImGui::Begin("UI Scale", &g_windowShowUIScale)) {
          ImGui::SetWindowSize(ImVec2(500, 165), ImGuiCond_FirstUseEver);

          if (ImGui::InputFloat("Scale", &g_uiScale)) {
            if (g_uiScale >= 1.0f && g_uiScale <= 100.0f) {
              io.FontGlobalScale = g_uiScale;
            }
          }
        }
        ImGui::End();
      }

      static int  goToLine    = 0;
      static int  goToLineDir = 0; // 0: stop, 1: up, 2: down
      static bool goToLineGo  = false;
      if (g_windowsShowAll == true || (g_windowsHideAll == false && g_windowShowCodeCurrentLine == true)) {
        if (ImGui::Begin("Code Current Line", &g_windowShowCodeCurrentLine)) {
          ImGui::Text("Current line: %llu", g_codeCurrentLineNumber);
          ImGui::InputInt("Go to line", &goToLine);
          if (ImGui::Checkbox("Go", &goToLineGo)) {
            if (goToLineGo == true) {
              if (g_codeCurrentLineNumber > goToLine) {
                goToLineDir = 1;
                io.AddKeyEvent(ImGuiKey_UpArrow, true);
              } else if (g_codeCurrentLineNumber < goToLine) {
                goToLineDir = 2;
                io.AddKeyEvent(ImGuiKey_DownArrow, true);
              }
            } else {
              if (goToLineDir == 1) {
                io.AddKeyEvent(ImGuiKey_UpArrow, false);
              } else if (goToLineDir == 2) {
                io.AddKeyEvent(ImGuiKey_DownArrow, false);
              }
              goToLineDir = 0;
            }
          }
          if (goToLineGo == true) {
            if (goToLineDir == 1 && g_codeCurrentLineNumber <= goToLine) {
              io.AddKeyEvent(ImGuiKey_UpArrow, false);
              goToLineDir = 0;
              goToLineGo  = false;
            } else if (goToLineDir == 2 && g_codeCurrentLineNumber >= goToLine) {
              io.AddKeyEvent(ImGuiKey_DownArrow, false);
              goToLineDir = 0;
              goToLineGo  = false;
            }
          }
        }
        ImGui::End();
      }

      if (g_windowsShowAll == true || (g_windowsHideAll == false && g_windowShowCodeSaveLoad == true)) {
        if (ImGui::Begin("Code Save Load", &g_windowShowCodeSaveLoad)) {
          ImGui::SetWindowSize(ImVec2(650, 235), ImGuiCond_FirstUseEver);

          ImGui::InputText("Filepath", &g_codeSaveLoadFilepath[0], g_codeSaveLoadFilepath.size(), ImGuiInputTextFlags_CallbackResize, imguiCodeSaveLoadFilepathCallback, 0);
          ImGui::Indent(16.0f);
          if (ImGui::Button("Save") && g_codeSaveLoadFilepath.empty() == false && g_codeString.empty() == false) {
            std::string path = g_codeSaveLoadFilepath;
            if (path.back() == '\n') {
              path.pop_back();
            }
            fileWrite(path.c_str(), g_codeString.c_str());
          }
          ImGui::SameLine();
          if (ImGui::Button("Copy code from file") && g_codeSaveLoadFilepath.empty() == false) {
            std::string path = g_codeSaveLoadFilepath;
            if (path.back() == '\n') {
              path.pop_back();
            }
            std::string code = fileRead(path.c_str());
            if (code.empty() == false) {
              g_codeStringCopied = code;
            }
          }
          ImGui::Unindent(16.0f);
        }
        ImGui::End();
      }

      static int  codeRunResetFrameTo = 0;
      if (g_windowForceShowCodeRun == true || g_windowsShowAll == true || (g_windowsHideAll == false && g_windowShowCodeRun == true)) {
        if (ImGui::Begin("Code Run", &g_windowShowCodeRun)) {
          ImGui::Text("Current frame: %llu", g_currentFrame);
          if (ImGui::Checkbox("Run code", &g_runScript)) {
            g_frame0CacheStartPositionIsDirty = true;
            if (g_runScript == true) {
              gsAutosaveSave();
            }
          }
          ImGui::InputInt("Frame", &codeRunResetFrameTo);
          if (ImGui::Button("Run code once") && g_runScript == false) {
            g_frame0CacheStartPositionIsDirty = true;
            gsAutosaveSave();
            g_runScriptOnce = true;
          }
          ImGui::SameLine();
          if (ImGui::Button("Set frame")) {
            g_currentFrame = codeRunResetFrameTo;
          }
          if (g_compileMode == true) {
            ImGui::SameLine();
            if (ImGui::Button("Recompile code")) {
              scriptCompileProgram();
            }
          }
        }
        ImGui::End();
      }

      if (g_windowForceShowConsole == true || g_windowsShowAll == true || (g_windowsHideAll == false && g_windowShowConsole == true)) {
        if (ImGui::Begin("Console", &g_windowShowConsole, ImGuiWindowFlags_HorizontalScrollbar)) {
          ImGui::SetWindowSize(ImVec2(875, 700), ImGuiCond_FirstUseEver);

          if (ImGui::Button("Clear")) {
            g_consoleString.clear();
          }
          ImGui::SameLine();
          if (ImGui::Button("Save")) {
            fileWrite("gamescript_console.txt", g_consoleString.c_str());
          }
          if (g_consoleString.empty() == false) {
            ImGui::TextUnformatted(g_consoleString.c_str());
          }
        }
        ImGui::End();
      }

      if (g_windowsShowAll == true || (g_windowsHideAll == false && g_windowShowAbout == true)) {
        if (ImGui::Begin("About", &g_windowShowAbout, ImGuiWindowFlags_HorizontalScrollbar)) {
          ImGui::Text("Version from %s %s", __DATE__, __TIME__);
          ImGui::Text("Website: https://github.com/procedural/gamescript");
          ImGui::Text("Game Script REDGPU Version, created by Constantine Tarasenkov.");
          ImGui::Text("Special thanks to Irina Salnikova, Alexander Tarasenkov, Vitaliy Tarasenkov and Mario Rodriguez Palomino.");
        }
        ImGui::End();
      }

      if (g_windowsShowAll == true || (g_windowsHideAll == false && g_windowShowFrame0Cache == true)) {
        if (ImGui::Begin("Frame 0 Cache", &g_windowShowFrame0Cache, ImGuiWindowFlags_HorizontalScrollbar)) {
          if (ImGui::Checkbox("Enable frame 0 cache", &g_frame0CacheEnable)) {
            g_frame0CacheStartPositionIsDirty = true;
          }
          ImGui::TextUnformatted(
            "Description: frame 0 cache ignores all the code up to @ character for non-0 frames.\n"
            "\n"
            "Code example:\n"
            "\n"
            "setFrame0Cache(true)\n"
            "printConsole(\"This line will be parsed and executed only on frame 0 because it's written before the cache character.\")\n"
            "//@\n"
            "printConsole(\"This line will always be parsed and executed because it's written after the cache character.\")\n"
          );
        }
        ImGui::End();
      }

      if (g_windowsShowAll == true || (g_windowsHideAll == false && g_windowShowCodeCompileMode == true)) {
        if (ImGui::Begin("Code Compile Mode", &g_windowShowCodeCompileMode, ImGuiWindowFlags_HorizontalScrollbar)) {
          if (ImGui::Checkbox("Enable code compile mode", &g_compileMode)) {
            scriptDestroyContext();
          }
        }
        ImGui::End();
      }

      static int  windowMemoryViewerGlobalArrayIsShared     = 0;
      static int  windowMemoryViewerGlobalArrayIsPersistent = 0;
      static int  windowMemoryViewerBytesRangeLimit         = 1;
      static int  windowMemoryViewerBytesRangeLimitFirst    = 0;
      static int  windowMemoryViewerBytesRangeLimitCount    = 8;
      static int  windowMemoryViewerBytesPerRow             = 8;
      if (g_windowForceShowMemoryViewer == true || g_windowsShowAll == true || (g_windowsHideAll == false && g_windowShowMemoryViewer == true)) {
        if (ImGui::Begin("Memory Viewer", &g_windowShowMemoryViewer)) {
          ImGui::SetWindowSize(ImVec2(1010, 560), ImGuiCond_FirstUseEver);

          ImGui::InputText("Global array name", &gMemoryViewerGlobalArrayNameChars[0], gMemoryViewerGlobalArrayNameChars.size(), ImGuiInputTextFlags_CallbackResize, guiMemoryViewerCallback, 0);
          ImGui::Checkbox("Global array is shared", (bool *)&windowMemoryViewerGlobalArrayIsShared);
          ImGui::Checkbox("Global array is persistent", (bool *)&windowMemoryViewerGlobalArrayIsPersistent);
          ImGui::InputInt("Bytes per row", &windowMemoryViewerBytesPerRow, 1, 1, 0);
          ImGui::InputInt("Bytes range first", &windowMemoryViewerBytesRangeLimitFirst, 1, 1, 0);
          ImGui::InputInt("Bytes range count", &windowMemoryViewerBytesRangeLimitCount, 1, 1, 0);
          if (ImGui::TreeNode("Bits interpretation")) {
            ImGui::InputText("Bytes", &gMemoryViewerInterpretBytesChars[0], gMemoryViewerInterpretBytesChars.size(), ImGuiInputTextFlags_CallbackResize, guiMemoryViewerIntepretBytesCallback, 0);
            char char65FromUser[65]       = {};
            char char65ReintepretedTo[65] = {};
            for (size_t i = 0, j = 0; i < gMemoryViewerInterpretBytesChars.size(); i += 1) {
              if (j == 64) {
                break;
              }
              char c = gMemoryViewerInterpretBytesChars[i];
              if (c == 0) {
                break;
              }
              if (c == '0' || c == '1') {
                char65FromUser[j] = c;
                j += 1;
              }
            }
            char65ReintepretedTo[0]  = char65FromUser[7*8+0] == '1' ? '1' : '0';
            char65ReintepretedTo[1]  = char65FromUser[7*8+1] == '1' ? '1' : '0';
            char65ReintepretedTo[2]  = char65FromUser[7*8+2] == '1' ? '1' : '0';
            char65ReintepretedTo[3]  = char65FromUser[7*8+3] == '1' ? '1' : '0';
            char65ReintepretedTo[4]  = char65FromUser[7*8+4] == '1' ? '1' : '0';
            char65ReintepretedTo[5]  = char65FromUser[7*8+5] == '1' ? '1' : '0';
            char65ReintepretedTo[6]  = char65FromUser[7*8+6] == '1' ? '1' : '0';
            char65ReintepretedTo[7]  = char65FromUser[7*8+7] == '1' ? '1' : '0';
            char65ReintepretedTo[8]  = char65FromUser[6*8+0] == '1' ? '1' : '0';
            char65ReintepretedTo[9]  = char65FromUser[6*8+1] == '1' ? '1' : '0';
            char65ReintepretedTo[10] = char65FromUser[6*8+2] == '1' ? '1' : '0';
            char65ReintepretedTo[11] = char65FromUser[6*8+3] == '1' ? '1' : '0';
            char65ReintepretedTo[12] = char65FromUser[6*8+4] == '1' ? '1' : '0';
            char65ReintepretedTo[13] = char65FromUser[6*8+5] == '1' ? '1' : '0';
            char65ReintepretedTo[14] = char65FromUser[6*8+6] == '1' ? '1' : '0';
            char65ReintepretedTo[15] = char65FromUser[6*8+7] == '1' ? '1' : '0';
            char65ReintepretedTo[16] = char65FromUser[5*8+0] == '1' ? '1' : '0';
            char65ReintepretedTo[17] = char65FromUser[5*8+1] == '1' ? '1' : '0';
            char65ReintepretedTo[18] = char65FromUser[5*8+2] == '1' ? '1' : '0';
            char65ReintepretedTo[19] = char65FromUser[5*8+3] == '1' ? '1' : '0';
            char65ReintepretedTo[20] = char65FromUser[5*8+4] == '1' ? '1' : '0';
            char65ReintepretedTo[21] = char65FromUser[5*8+5] == '1' ? '1' : '0';
            char65ReintepretedTo[22] = char65FromUser[5*8+6] == '1' ? '1' : '0';
            char65ReintepretedTo[23] = char65FromUser[5*8+7] == '1' ? '1' : '0';
            char65ReintepretedTo[24] = char65FromUser[4*8+0] == '1' ? '1' : '0';
            char65ReintepretedTo[25] = char65FromUser[4*8+1] == '1' ? '1' : '0';
            char65ReintepretedTo[26] = char65FromUser[4*8+2] == '1' ? '1' : '0';
            char65ReintepretedTo[27] = char65FromUser[4*8+3] == '1' ? '1' : '0';
            char65ReintepretedTo[28] = char65FromUser[4*8+4] == '1' ? '1' : '0';
            char65ReintepretedTo[29] = char65FromUser[4*8+5] == '1' ? '1' : '0';
            char65ReintepretedTo[30] = char65FromUser[4*8+6] == '1' ? '1' : '0';
            char65ReintepretedTo[31] = char65FromUser[4*8+7] == '1' ? '1' : '0';
            char65ReintepretedTo[32] = char65FromUser[3*8+0] == '1' ? '1' : '0';
            char65ReintepretedTo[33] = char65FromUser[3*8+1] == '1' ? '1' : '0';
            char65ReintepretedTo[34] = char65FromUser[3*8+2] == '1' ? '1' : '0';
            char65ReintepretedTo[35] = char65FromUser[3*8+3] == '1' ? '1' : '0';
            char65ReintepretedTo[36] = char65FromUser[3*8+4] == '1' ? '1' : '0';
            char65ReintepretedTo[37] = char65FromUser[3*8+5] == '1' ? '1' : '0';
            char65ReintepretedTo[38] = char65FromUser[3*8+6] == '1' ? '1' : '0';
            char65ReintepretedTo[39] = char65FromUser[3*8+7] == '1' ? '1' : '0';
            char65ReintepretedTo[40] = char65FromUser[2*8+0] == '1' ? '1' : '0';
            char65ReintepretedTo[41] = char65FromUser[2*8+1] == '1' ? '1' : '0';
            char65ReintepretedTo[42] = char65FromUser[2*8+2] == '1' ? '1' : '0';
            char65ReintepretedTo[43] = char65FromUser[2*8+3] == '1' ? '1' : '0';
            char65ReintepretedTo[44] = char65FromUser[2*8+4] == '1' ? '1' : '0';
            char65ReintepretedTo[45] = char65FromUser[2*8+5] == '1' ? '1' : '0';
            char65ReintepretedTo[46] = char65FromUser[2*8+6] == '1' ? '1' : '0';
            char65ReintepretedTo[47] = char65FromUser[2*8+7] == '1' ? '1' : '0';
            char65ReintepretedTo[48] = char65FromUser[1*8+0] == '1' ? '1' : '0';
            char65ReintepretedTo[49] = char65FromUser[1*8+1] == '1' ? '1' : '0';
            char65ReintepretedTo[50] = char65FromUser[1*8+2] == '1' ? '1' : '0';
            char65ReintepretedTo[51] = char65FromUser[1*8+3] == '1' ? '1' : '0';
            char65ReintepretedTo[52] = char65FromUser[1*8+4] == '1' ? '1' : '0';
            char65ReintepretedTo[53] = char65FromUser[1*8+5] == '1' ? '1' : '0';
            char65ReintepretedTo[54] = char65FromUser[1*8+6] == '1' ? '1' : '0';
            char65ReintepretedTo[55] = char65FromUser[1*8+7] == '1' ? '1' : '0';
            char65ReintepretedTo[56] = char65FromUser[0*8+0] == '1' ? '1' : '0';
            char65ReintepretedTo[57] = char65FromUser[0*8+1] == '1' ? '1' : '0';
            char65ReintepretedTo[58] = char65FromUser[0*8+2] == '1' ? '1' : '0';
            char65ReintepretedTo[59] = char65FromUser[0*8+3] == '1' ? '1' : '0';
            char65ReintepretedTo[60] = char65FromUser[0*8+4] == '1' ? '1' : '0';
            char65ReintepretedTo[61] = char65FromUser[0*8+5] == '1' ? '1' : '0';
            char65ReintepretedTo[62] = char65FromUser[0*8+6] == '1' ? '1' : '0';
            char65ReintepretedTo[63] = char65FromUser[0*8+7] == '1' ? '1' : '0';
            char65ReintepretedTo[64] = 0;
            ImGui::InputText("Bytes as bits", char65ReintepretedTo, 65, ImGuiInputTextFlags_ReadOnly, 0, 0);
            uint64_t b = 0;
            b |= char65ReintepretedTo[0]  == '0' ? 0 : REDGPU_B64(1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[1]  == '0' ? 0 : REDGPU_B64(0100,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[2]  == '0' ? 0 : REDGPU_B64(0010,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[3]  == '0' ? 0 : REDGPU_B64(0001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[4]  == '0' ? 0 : REDGPU_B64(0000,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[5]  == '0' ? 0 : REDGPU_B64(0000,0100,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[6]  == '0' ? 0 : REDGPU_B64(0000,0010,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[7]  == '0' ? 0 : REDGPU_B64(0000,0001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[8]  == '0' ? 0 : REDGPU_B64(0000,0000,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[9]  == '0' ? 0 : REDGPU_B64(0000,0000,0100,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[10] == '0' ? 0 : REDGPU_B64(0000,0000,0010,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[11] == '0' ? 0 : REDGPU_B64(0000,0000,0001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[12] == '0' ? 0 : REDGPU_B64(0000,0000,0000,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[13] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0100,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[14] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0010,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[15] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[16] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[17] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0100,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[18] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0010,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[19] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[20] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[21] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0100,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[22] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0010,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[23] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[24] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[25] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0100,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[26] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0010,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[27] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0001,0000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[28] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,1000,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[29] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0100,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[30] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0010,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[31] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0001,0000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[32] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,1000,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[33] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0100,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[34] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0010,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[35] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0001,0000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[36] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,1000,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[37] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0100,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[38] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0010,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[39] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0001,0000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[40] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,1000,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[41] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0100,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[42] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0010,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[43] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0001,0000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[44] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,1000,0000,0000,0000,0000);
            b |= char65ReintepretedTo[45] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0100,0000,0000,0000,0000);
            b |= char65ReintepretedTo[46] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0010,0000,0000,0000,0000);
            b |= char65ReintepretedTo[47] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0001,0000,0000,0000,0000);
            b |= char65ReintepretedTo[48] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,1000,0000,0000,0000);
            b |= char65ReintepretedTo[49] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0100,0000,0000,0000);
            b |= char65ReintepretedTo[50] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0010,0000,0000,0000);
            b |= char65ReintepretedTo[51] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0001,0000,0000,0000);
            b |= char65ReintepretedTo[52] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,1000,0000,0000);
            b |= char65ReintepretedTo[53] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0100,0000,0000);
            b |= char65ReintepretedTo[54] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0010,0000,0000);
            b |= char65ReintepretedTo[55] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0001,0000,0000);
            b |= char65ReintepretedTo[56] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,1000,0000);
            b |= char65ReintepretedTo[57] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0100,0000);
            b |= char65ReintepretedTo[58] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0010,0000);
            b |= char65ReintepretedTo[59] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0001,0000);
            b |= char65ReintepretedTo[60] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,1000);
            b |= char65ReintepretedTo[61] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0100);
            b |= char65ReintepretedTo[62] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0010);
            b |= char65ReintepretedTo[63] == '0' ? 0 : REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0001);
            std::string as;
            {
              char bb;
              memcpy((void *)&bb, (void *)&b, sizeof(char));
              as += bb;
              ImGui::InputText("Bytes as char", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
              as.clear();
            }
            {
              uint8_t bb;
              memcpy((void *)&bb, (void *)&b, sizeof(uint8_t));
              as += std::to_string(bb);
              ImGui::InputText("Bytes as uint8_t", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
              as.clear();
            }
            {
              uint16_t bb;
              memcpy((void *)&bb, (void *)&b, sizeof(uint16_t));
              as += std::to_string(bb);
              ImGui::InputText("Bytes as uint16_t", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
              as.clear();
            }
            {
              uint32_t bb;
              memcpy((void *)&bb, (void *)&b, sizeof(uint32_t));
              as += std::to_string(bb);
              ImGui::InputText("Bytes as uint32_t", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
              as.clear();
            }
            {
              uint64_t bb;
              memcpy((void *)&bb, (void *)&b, sizeof(uint64_t));
              as += std::to_string(bb);
              ImGui::InputText("Bytes as uint64_t", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
              as.clear();
            }
            {
              int8_t bb;
              memcpy((void *)&bb, (void *)&b, sizeof(int8_t));
              as += std::to_string(bb);
              ImGui::InputText("Bytes as int8_t", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
              as.clear();
            }
            {
              int16_t bb;
              memcpy((void *)&bb, (void *)&b, sizeof(int16_t));
              as += std::to_string(bb);
              ImGui::InputText("Bytes as int16_t", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
              as.clear();
            }
            {
              int32_t bb;
              memcpy((void *)&bb, (void *)&b, sizeof(int32_t));
              as += std::to_string(bb);
              ImGui::InputText("Bytes as int32_t", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
              as.clear();
            }
            {
              int64_t bb;
              memcpy((void *)&bb, (void *)&b, sizeof(int64_t));
              as += std::to_string(bb);
              ImGui::InputText("Bytes as int64_t", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
              as.clear();
            }
            {
              float bb;
              memcpy((void *)&bb, (void *)&b, sizeof(float));
              as += std::to_string(bb);
              ImGui::InputText("Bytes as float", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
              as.clear();
            }
            {
              double bb;
              memcpy((void *)&bb, (void *)&b, sizeof(double));
              as += std::to_string(bb);
              ImGui::InputText("Bytes as double", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
              as.clear();
            }
            ImGui::TreePop();
          }
          if (windowMemoryViewerBytesPerRow <= 0) {
            windowMemoryViewerBytesPerRow = 1;
          }
          if (windowMemoryViewerBytesRangeLimitFirst < 0) {
            windowMemoryViewerBytesRangeLimitFirst = 0;
          }
          if (windowMemoryViewerBytesRangeLimitCount < 0) {
            windowMemoryViewerBytesRangeLimitCount = 0;
          }
          {
            std::string key = gMemoryViewerGlobalArrayNameChars;
            std::string keyQuery;
            if (key.size() > 0) {
              for (size_t i = 0, count = key.size(); i < count; i += 1) {
                char k = key[i];
                if (k == 0) {
                  break;
                }
                keyQuery += k;
              }
            }
            unsigned char * pointer = 0;
            if (windowMemoryViewerGlobalArrayIsPersistent == 0) {
              pointer = (unsigned char *)gGlobalArrayPointer[keyQuery];
            } else {
              if (windowMemoryViewerGlobalArrayIsShared == 0) {
                pointer = (unsigned char *)gGlobalArrayPersistentPointer[keyQuery];
              } else {
                pointer = (unsigned char *)gGlobalSharedArrayPersistentPointer[keyQuery];
              }
            }
            if (pointer != 0) {
              // Found the global array.
              uint64_t bytesCount = 0;
              if (windowMemoryViewerGlobalArrayIsPersistent == 0) {
                bytesCount = gGlobalArrayBytesCount[keyQuery];
              } else {
                if (windowMemoryViewerGlobalArrayIsShared == 0) {
                  bytesCount = gGlobalArrayPersistentBytesCount[keyQuery];
                } else {
                  bytesCount = gGlobalSharedArrayPersistentBytesCount[keyQuery];
                }
              }
              if (bytesCount > 0) {
                // Bytes count is valid.
                uint64_t bytesStart = 0;
                uint64_t bytesEnd   = bytesCount;
                if (windowMemoryViewerBytesRangeLimit == 1) {
                  // 0 1 2 3 4 . . : Count 5
                  //     ^       ^
                  // first 2
                  // count 4
                  // range 5 - 2 = 3
                  bytesStart = windowMemoryViewerBytesRangeLimitFirst;
                  if (bytesStart > (bytesCount-1)) {
                    bytesStart = bytesCount-1;
                  }
                  uint64_t bytesCountRange = bytesCount - bytesStart;
                  bytesEnd = windowMemoryViewerBytesRangeLimitCount;
                  if (bytesEnd > bytesCountRange) {
                    bytesEnd = bytesCountRange;
                  }
                }
                unsigned char * pointerSubrange = &pointer[bytesStart];
                pointer = pointerSubrange;
                std::string rowName = address_to_hex_string((uint64_t)(void *)pointer);
                std::string rowString;
                for (uint64_t i = 0; i < bytesEnd; i += 1) {
                  uint64_t row = i % windowMemoryViewerBytesPerRow;
                  if (row == 0 && i != 0) {
                    // New row then.
                    ImGui::InputText(rowName.c_str(), &rowString[0], rowString.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
                    rowString = std::string();
                    // Next row name:
                    rowName = address_to_hex_string((uint64_t)(void *)(pointer + i));
                  }
                  if (row != 0) {
                    rowString += " ";
                  }
                  rowString += byte_to_binary_string(pointer[i]);
                }
                if (rowString != "") {
                  // New row then.
                  ImGui::InputText(rowName.c_str(), &rowString[0], rowString.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
                  rowString = std::string();
                }
              }
            }
          }
        }
        ImGui::End();
      }

      if (g_windowsShowAll == true || (g_windowsHideAll == false && g_windowShowCHeaderForRedGpu == true)) {
        if (ImGui::Begin("C Header for REDGPU", &g_windowShowCHeaderForRedGpu, ImGuiWindowFlags_HorizontalScrollbar)) {
          ImGui::SetWindowSize(ImVec2(1010, 560), ImGuiCond_FirstUseEver);

          const char * text =
"// https://github.com/redgpu/redgpu/blob/34a317ac7e0ed2ee2551bb9d9144046350c6d04e/RedGpuSDK/redgpu.h"
"\n"
"\n#pragma once"
"\n"
"\n#ifndef REDGPU_NO_INCLUDES"
"\n#if defined(_WIN32) && !defined(_WIN64)"
"\ntypedef unsigned size_t;"
"\ntypedef unsigned __int64 uint64_t;"
"\n#else"
"\n#include <stddef.h> // For size_t"
"\n#include <stdint.h> // For uint64_t"
"\n#endif"
"\n#endif"
"\n"
"\n#ifdef __cplusplus"
"\nextern \"C\" {"
"\n#endif"
"\n"
"\n#ifdef _WIN32"
"\n#define REDGPU_B4_0000 0"
"\n#define REDGPU_B4_0001 1"
"\n#define REDGPU_B4_0010 2"
"\n#define REDGPU_B4_0011 3"
"\n#define REDGPU_B4_0100 4"
"\n#define REDGPU_B4_0101 5"
"\n#define REDGPU_B4_0110 6"
"\n#define REDGPU_B4_0111 7"
"\n#define REDGPU_B4_1000 8"
"\n#define REDGPU_B4_1001 9"
"\n#define REDGPU_B4_1010 a"
"\n#define REDGPU_B4_1011 b"
"\n#define REDGPU_B4_1100 c"
"\n#define REDGPU_B4_1101 d"
"\n#define REDGPU_B4_1110 e"
"\n#define REDGPU_B4_1111 f"
"\n#define REDGPU_B4_TO_HEX(b) REDGPU_B4_##b"
"\n#define REDGPU_HEX_MERGE(a,b,c,d,e,f,g,h) 0x##a##b##c##d##e##f##g##h"
"\n#define REDGPU_HEX(a,b,c,d,e,f,g,h) REDGPU_HEX_MERGE(a,b,c,d,e,f,g,h)"
"\n#define REDGPU_B32(a,b,c,d,e,f,g,h) REDGPU_HEX(REDGPU_B4_TO_HEX(a),REDGPU_B4_TO_HEX(b),REDGPU_B4_TO_HEX(c),REDGPU_B4_TO_HEX(d),REDGPU_B4_TO_HEX(e),REDGPU_B4_TO_HEX(f),REDGPU_B4_TO_HEX(g),REDGPU_B4_TO_HEX(h))"
"\n#else"
"\n#define REDGPU_B32(a,b,c,d,e,f,g,h) 0b##a##b##c##d##e##f##g##h"
"\n#endif"
"\n"
"\n#if defined(_WIN32) && !defined(_WIN64)"
"\n#define REDGPU_CALLING_CONVENTION __stdcall"
"\n#else"
"\n#define REDGPU_CALLING_CONVENTION"
"\n#endif"
"\n"
"\ntypedef unsigned RedBool32;"
"\n"
"\n#if defined(_WIN32) && !defined(_WIN64)"
"\ntypedef struct RedTypeContext                   * RedContext;"
"\ntypedef struct RedTypeHandleContext             * RedHandleContext;"
"\ntypedef struct RedTypeHandleGpu                 * RedHandleGpu;"
"\ntypedef struct RedTypeHandleGpuDevice           * RedHandleGpuDevice;"
"\ntypedef struct RedTypeHandleQueue               * RedHandleQueue;"
"\ntypedef uint64_t                                  RedHandleMemory;"
"\ntypedef uint64_t                                  RedHandleArray;"
"\ntypedef uint64_t                                  RedHandleImage;"
"\ntypedef uint64_t                                  RedHandleSampler;"
"\ntypedef uint64_t                                  RedHandleTexture;"
"\ntypedef uint64_t                                  RedHandleGpuCode;"
"\ntypedef uint64_t                                  RedHandleOutputDeclaration;"
"\ntypedef uint64_t                                  RedHandleStructDeclaration;"
"\ntypedef uint64_t                                  RedHandleProcedureParameters;"
"\ntypedef uint64_t                                  RedHandleProcedureCache;"
"\ntypedef uint64_t                                  RedHandleProcedure;"
"\ntypedef uint64_t                                  RedHandleOutput;"
"\ntypedef uint64_t                                  RedHandleStruct;"
"\ntypedef uint64_t                                  RedHandleStructsMemory;"
"\ntypedef struct RedTypeHandleCalls               * RedHandleCalls;"
"\ntypedef uint64_t                                  RedHandleCallsMemory;"
"\ntypedef uint64_t                                  RedHandleCpuSignal;"
"\ntypedef uint64_t                                  RedHandleGpuSignal;"
"\ntypedef uint64_t                                  RedHandleGpuToCpuSignal;"
"\n#else"
"\ntypedef struct RedTypeContext                   * RedContext;"
"\ntypedef struct RedTypeHandleContext             * RedHandleContext;"
"\ntypedef struct RedTypeHandleGpu                 * RedHandleGpu;"
"\ntypedef struct RedTypeHandleGpuDevice           * RedHandleGpuDevice;"
"\ntypedef struct RedTypeHandleQueue               * RedHandleQueue;"
"\ntypedef struct RedTypeHandleMemory              * RedHandleMemory;"
"\ntypedef struct RedTypeHandleArray               * RedHandleArray;"
"\ntypedef struct RedTypeHandleImage               * RedHandleImage;"
"\ntypedef struct RedTypeHandleSampler             * RedHandleSampler;"
"\ntypedef struct RedTypeHandleTexture             * RedHandleTexture;"
"\ntypedef struct RedTypeHandleGpuCode             * RedHandleGpuCode;"
"\ntypedef struct RedTypeHandleOutputDeclaration   * RedHandleOutputDeclaration;"
"\ntypedef struct RedTypeHandleStructDeclaration   * RedHandleStructDeclaration;"
"\ntypedef struct RedTypeHandleProcedureParameters * RedHandleProcedureParameters;"
"\ntypedef struct RedTypeHandleProcedureCache      * RedHandleProcedureCache;"
"\ntypedef struct RedTypeHandleProcedure           * RedHandleProcedure;"
"\ntypedef struct RedTypeHandleOutput              * RedHandleOutput;"
"\ntypedef struct RedTypeHandleStruct              * RedHandleStruct;"
"\ntypedef struct RedTypeHandleStructsMemory       * RedHandleStructsMemory;"
"\ntypedef struct RedTypeHandleCalls               * RedHandleCalls;"
"\ntypedef struct RedTypeHandleCallsMemory         * RedHandleCallsMemory;"
"\ntypedef struct RedTypeHandleCpuSignal           * RedHandleCpuSignal;"
"\ntypedef struct RedTypeHandleGpuSignal           * RedHandleGpuSignal;"
"\ntypedef struct RedTypeHandleGpuToCpuSignal      * RedHandleGpuToCpuSignal;"
"\n#endif"
"\n"
"\ntypedef struct RedArray {"
"\n  RedHandleArray       handle;"
"\n  uint64_t             memoryBytesAlignment;"
"\n  uint64_t             memoryBytesCount;"
"\n  unsigned             memoryTypesSupported; // Bitflags"
"\n} RedArray;"
"\n"
"\ntypedef struct RedImage {"
"\n  RedHandleImage       handle;"
"\n  uint64_t             memoryBytesAlignment;"
"\n  uint64_t             memoryBytesCount;"
"\n  unsigned             memoryTypesSupported; // Bitflags"
"\n} RedImage;"
"\n"
"\ntypedef struct RedOutput {"
"\n  RedHandleOutput      handle;"
"\n  unsigned             width;"
"\n  unsigned             height;"
"\n  RedBool32            depthStencilEnable;"
"\n  unsigned             colorsCount;          // Max: 8"
"\n} RedOutput;"
"\n"
"\ntypedef struct RedCalls {"
"\n  RedHandleCalls       handle;"
"\n  RedHandleCallsMemory memory;"
"\n  RedBool32            reusable;"
"\n} RedCalls;"
"\n"
"\ntypedef enum RedStatus {"
"\n  RED_STATUS_SUCCESS                       = 0,"
"\n  RED_STATUS_NOT_READY                     = 1,"
"\n  RED_STATUS_TIMEOUT                       = 2,"
"\n  RED_STATUS_GPU_TO_CPU_SIGNAL_SIGNALED    = 3,"
"\n  RED_STATUS_GPU_TO_CPU_SIGNAL_UNSIGNALED  = 4,"
"\n  RED_STATUS_INCOMPLETE                    = 5,"
"\n  RED_STATUS_PRESENT_IS_SUBOPTIMAL         = 1000001003, // WSI specific"
"\n  RED_STATUS_ERROR_OUT_OF_CPU_MEMORY       = -1,"
"\n  RED_STATUS_ERROR_OUT_OF_GPU_MEMORY       = -2,"
"\n  RED_STATUS_ERROR_INITIALIZATION_FAILED   = -3,"
"\n  RED_STATUS_ERROR_GPU_IS_LOST             = -4,"
"\n  RED_STATUS_ERROR_MEMORY_MAPPING_FAILED   = -5, // Memory mapping will fail if the implementation is unable to allocate an appropriately sized contiguous virtual address range, e.g. due to virtual address space fragmentation or platform limits. The program can improve the likelihood of success by reducing the size of the mapped range and/or remove unneeded mappings using redMemoryUnmap"
"\n  RED_STATUS_ERROR_LAYER_IS_NOT_FOUND      = -6,"
"\n  RED_STATUS_ERROR_EXTENSION_IS_NOT_FOUND  = -7,"
"\n  RED_STATUS_ERROR_FEATURE_IS_NOT_FOUND    = -8,"
"\n  RED_STATUS_ERROR_INCOMPATIBLE_DRIVER     = -9,"
"\n  RED_STATUS_ERROR_TOO_MANY_HANDLES        = -10,"
"\n  RED_STATUS_ERROR_FORMAT_IS_NOT_SUPPORTED = -11,"
"\n  RED_STATUS_ERROR_MEMORY_IS_FRAGMENTED    = -12,"
"\n  RED_STATUS_ERROR_MEMORY_OVERFLOW         = -1000069000,"
"\n  RED_STATUS_ERROR_WINDOW_IS_ALREADY_USED  = -1000000001, // WSI specific"
"\n  RED_STATUS_ERROR_SURFACE_IS_LOST         = -1000000000, // WSI specific"
"\n  RED_STATUS_ERROR_PRESENT_IS_OUT_OF_DATE  = -1000001004, // WSI specific"
"\n  RED_STATUS_ERROR_VALIDATION_FAILED       = -1000011001,"
"\n  RED_STATUS_ERROR_INVALID_GPU_CODE        = -1000012000,"
"\n} RedStatus;"
"\n"
"\ntypedef enum RedProcedureId {"
"\n  RED_PROCEDURE_ID_UNDEFINED                                      = 0,"
"\n  RED_PROCEDURE_ID_redMemoryGetBudget                             = 1,"
"\n  RED_PROCEDURE_ID_redMemoryAllocate                              = 2,"
"\n  RED_PROCEDURE_ID_redMemoryAllocateMappable                      = 3,"
"\n  RED_PROCEDURE_ID_redMemoryFree                                  = 4,"
"\n  RED_PROCEDURE_ID_redMemorySet                                   = 5,"
"\n  RED_PROCEDURE_ID_redMemoryMap                                   = 6,"
"\n  RED_PROCEDURE_ID_redMemoryUnmap                                 = 7,"
"\n  RED_PROCEDURE_ID_redMemoryNonCoherentFlush                      = 8,"
"\n  RED_PROCEDURE_ID_redMemoryNonCoherentInvalidate                 = 9,"
"\n  RED_PROCEDURE_ID_redStructsMemoryAllocate                       = 10,"
"\n  RED_PROCEDURE_ID_redStructsMemoryAllocateSamplers               = 11,"
"\n  RED_PROCEDURE_ID_redStructsMemorySuballocateStructs             = 12,"
"\n  RED_PROCEDURE_ID_redStructsMemoryReset                          = 13,"
"\n  RED_PROCEDURE_ID_redStructsMemoryFree                           = 14,"
"\n  RED_PROCEDURE_ID_redStructsSet                                  = 15,"
"\n  RED_PROCEDURE_ID_redCreateContext                               = 16,"
"\n  RED_PROCEDURE_ID_redCreateArray                                 = 17,"
"\n  RED_PROCEDURE_ID_redCreateImage                                 = 18,"
"\n  RED_PROCEDURE_ID_redCreateSampler                               = 19,"
"\n  RED_PROCEDURE_ID_redCreateTexture                               = 20,"
"\n  RED_PROCEDURE_ID_redCreateGpuCode                               = 21,"
"\n  RED_PROCEDURE_ID_redCreateOutputDeclaration                     = 22,"
"\n  RED_PROCEDURE_ID_redCreateStructDeclaration                     = 23,"
"\n  RED_PROCEDURE_ID_redCreateProcedureParameters                   = 24,"
"\n  RED_PROCEDURE_ID_redCreateProcedureCache                        = 25,"
"\n  RED_PROCEDURE_ID_redCreateProcedure                             = 26,"
"\n  RED_PROCEDURE_ID_redCreateProcedureCompute                      = 27,"
"\n  RED_PROCEDURE_ID_redCreateOutput                                = 28,"
"\n  RED_PROCEDURE_ID_redCreateCpuSignal                             = 29,"
"\n  RED_PROCEDURE_ID_redCreateGpuSignal                             = 30,"
"\n  RED_PROCEDURE_ID_redCreateGpuToCpuSignal                        = 31,"
"\n  RED_PROCEDURE_ID_redCreateCalls                                 = 32,"
"\n  RED_PROCEDURE_ID_redCreateCallsReusable                         = 33,"
"\n  RED_PROCEDURE_ID_redDestroyContext                              = 34,"
"\n  RED_PROCEDURE_ID_redDestroyArray                                = 35,"
"\n  RED_PROCEDURE_ID_redDestroyImage                                = 36,"
"\n  RED_PROCEDURE_ID_redDestroySampler                              = 37,"
"\n  RED_PROCEDURE_ID_redDestroyTexture                              = 38,"
"\n  RED_PROCEDURE_ID_redDestroyGpuCode                              = 39,"
"\n  RED_PROCEDURE_ID_redDestroyOutputDeclaration                    = 40,"
"\n  RED_PROCEDURE_ID_redDestroyStructDeclaration                    = 41,"
"\n  RED_PROCEDURE_ID_redDestroyProcedureParameters                  = 42,"
"\n  RED_PROCEDURE_ID_redDestroyProcedureCache                       = 43,"
"\n  RED_PROCEDURE_ID_redDestroyProcedure                            = 44,"
"\n  RED_PROCEDURE_ID_redDestroyOutput                               = 45,"
"\n  RED_PROCEDURE_ID_redDestroyCpuSignal                            = 46,"
"\n  RED_PROCEDURE_ID_redDestroyGpuSignal                            = 47,"
"\n  RED_PROCEDURE_ID_redDestroyGpuToCpuSignal                       = 48,"
"\n  RED_PROCEDURE_ID_redDestroyCalls                                = 49,"
"\n  RED_PROCEDURE_ID_redProcedureCacheGetBlob                       = 50,"
"\n  RED_PROCEDURE_ID_redProcedureCacheMergeCaches                   = 51,"
"\n  RED_PROCEDURE_ID_redCpuSignalGetStatus                          = 52,"
"\n  RED_PROCEDURE_ID_redCpuSignalWait                               = 53,"
"\n  RED_PROCEDURE_ID_redCpuSignalUnsignal                           = 54,"
"\n  RED_PROCEDURE_ID_redGpuToCpuSignalGetStatus                     = 55,"
"\n  RED_PROCEDURE_ID_redGpuToCpuSignalUnsignal                      = 56,"
"\n  RED_PROCEDURE_ID_redCallsSet                                    = 57,"
"\n  RED_PROCEDURE_ID_redCallsEnd                                    = 58,"
"\n  RED_PROCEDURE_ID_redGetCallProceduresAndAddresses               = 59,"
"\n  RED_PROCEDURE_ID_redQueueSubmit                                 = 60,"
"\n  RED_PROCEDURE_ID_redMark                                        = 61,"
"\n  RED_PROCEDURE_ID_redMarkSet                                     = 62,"
"\n  RED_PROCEDURE_ID_redMarkEnd                                     = 63,"
"\n  RED_PROCEDURE_ID_redCreateSurfaceWin32                          = 64, // WSI specific"
"\n  RED_PROCEDURE_ID_redCreateSurfaceXlibOrXcb                      = 65, // WSI specific"
"\n  RED_PROCEDURE_ID_redCreatePresent                               = 66, // WSI specific"
"\n  RED_PROCEDURE_ID_redDestroySurface                              = 67, // WSI specific"
"\n  RED_PROCEDURE_ID_redDestroyPresent                              = 68, // WSI specific"
"\n  RED_PROCEDURE_ID_redQueueFamilyIndexGetSupportsPresent          = 69, // WSI specific"
"\n  RED_PROCEDURE_ID_redSurfaceGetPresentFeatures                   = 70, // WSI specific"
"\n  RED_PROCEDURE_ID_redSurfaceGetCurrentPropertiesAndPresentLimits = 71, // WSI specific"
"\n  RED_PROCEDURE_ID_redPresentGetImageIndex                        = 72, // WSI specific"
"\n  RED_PROCEDURE_ID_redQueuePresent                                = 73, // WSI specific"
"\n  RED_PROCEDURE_ID_redDebugArrayGetHandle                         = 74, // Debug specific"
"\n  RED_PROCEDURE_ID_redDebugArrayCallPrint                         = 75, // Debug specific"
"\n} RedProcedureId;"
"\n"
"\ntypedef unsigned RedMultisampleCountBitflags;"
"\ntypedef enum RedMultisampleCountBitflag {"
"\n  RED_MULTISAMPLE_COUNT_BITFLAG_1  = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0001),"
"\n  RED_MULTISAMPLE_COUNT_BITFLAG_2  = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0010),"
"\n  RED_MULTISAMPLE_COUNT_BITFLAG_4  = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0100),"
"\n  RED_MULTISAMPLE_COUNT_BITFLAG_8  = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,1000),"
"\n  RED_MULTISAMPLE_COUNT_BITFLAG_16 = REDGPU_B32(0000,0000,0000,0000,0000,0000,0001,0000),"
"\n} RedMultisampleCountBitflag;"
"\n"
"\ntypedef enum RedGpuType {"
"\n  RED_GPU_TYPE_OTHER      = 0,"
"\n  RED_GPU_TYPE_INTEGRATED = 1,"
"\n  RED_GPU_TYPE_DISCRETE   = 2,"
"\n  RED_GPU_TYPE_VIRTUAL    = 3,"
"\n  RED_GPU_TYPE_CPU        = 4,"
"\n} RedGpuType;"
"\n"
"\ntypedef struct RedMemoryType {"
"\n  unsigned  memoryHeapIndex;"
"\n  RedBool32 isGpuVram;"
"\n  RedBool32 isCpuMappable;"
"\n  RedBool32 isCpuCoherent;"
"\n  RedBool32 isCpuCached;"
"\n} RedMemoryType;"
"\n"
"\ntypedef struct RedMemoryHeap {"
"\n  uint64_t  memoryBytesCount;"
"\n  RedBool32 isGpuVram;"
"\n} RedMemoryHeap;"
"\n"
"\ntypedef struct RedQueueCopyLimits {    // Draw and compute queues will always report (1, 1, 1)"
"\n  unsigned copyBlockTexelsCountWidth;  // x and width  parameters must be integer multiples of this limit"
"\n  unsigned copyBlockTexelsCountHeight; // y and height parameters must be integer multiples of this limit"
"\n  unsigned copyBlockTexelsCountDepth;  // z and depth  parameters must be integer multiples of this limit"
"\n} RedQueueCopyLimits;                  // Copy queues are only required to report (0, 0, 0) which indicates that only whole mip levels must be copied"
"\n"
"\ntypedef struct RedImageFormatLimitsDimensions {"
"\n  unsigned maxWidth;"
"\n  unsigned maxHeight;"
"\n  unsigned maxDepth;"
"\n} RedImageFormatLimitsDimensions;"
"\n"
"\ntypedef struct RedImageFormatLimits {"
"\n  RedImageFormatLimitsDimensions maxDimensions;"
"\n  unsigned                       maxLevelsCount;"
"\n  unsigned                       maxLayersCount;"
"\n  RedMultisampleCountBitflags    supportedMultisampleCounts;"
"\n  uint64_t                       maxBytesCount;              // Min: 2^31. An upper bound on the total image bytes count, inclusive of all levels and layers. Implementations may have an address space limit on total size of an image, which is advertized by this limit"
"\n  RedStatus                      status;"
"\n} RedImageFormatLimits;"
"\n"
"\ntypedef struct RedImageFormatFeatures {"
"\n  RedBool32 supportsCopyR;"
"\n  RedBool32 supportsCopyW;"
"\n  RedBool32 supportsTextureRO;"
"\n  RedBool32 supportsTextureRW;                // Multisample RW textures depend on RedGpuInfo::supportsGpuCodeTextureRWMultisample"
"\n  RedBool32 supportsOutputDepthStencil;"
"\n  RedBool32 supportsOutputColor;"
"\n  RedBool32 supportsTextureROFilteringLinear; // Format can be used for RO textures with RED_SAMPLER_FILTERING_LINEAR, RED_SAMPLER_FILTERING_MIP_LINEAR sampling"
"\n  RedBool32 supportsTextureRWAtomics;         // Format can be used for RW textures with atomic operations"
"\n  RedBool32 supportsOutputColorBlend;         // Format can be used for output colors with the corresponding RedProcedureState::outputColorsBlendEnable set to 1"
"\n} RedImageFormatFeatures;"
"\n"
"\ntypedef struct RedGpuInfo {"
"\n  RedHandleGpu                   gpu;"
"\n  RedHandleGpuDevice             gpuDevice;"
"\n  char                           gpuName[256];"
"\n  RedGpuType                     gpuType;"
"\n  unsigned                       gpuVendorId;"
"\n  unsigned                       gpuDeviceId;"
"\n  unsigned                       gpuDriverVersion;"
"\n  unsigned char                  gpuProcedureCacheUuid[16];"
"\n  // Memory"
"\n  unsigned                       memoryTypesCount;"
"\n  const RedMemoryType *          memoryTypes;            // Array of memoryTypesCount"
"\n  const char **                  memoryTypesDescription; // Array of memoryTypesCount, can be NULL"
"\n  unsigned                       memoryHeapsCount;"
"\n  const RedMemoryHeap *          memoryHeaps;            // Array of memoryHeapsCount"
"\n  const char **                  memoryHeapsDescription; // Array of memoryHeapsCount, can be NULL"
"\n  // Queues"
"\n  unsigned                       queuesCount;"
"\n  const RedHandleQueue *         queues;"
"\n  const char **                  queuesDescription; // Array of queuesCount, can be NULL"
"\n  const unsigned *               queuesFamilyIndex; // Array of queuesCount"
"\n  const RedBool32 *              queuesCanCopy;     // Array of queuesCount"
"\n  const RedBool32 *              queuesCanDraw;     // Array of queuesCount"
"\n  const RedBool32 *              queuesCanCompute;  // Array of queuesCount"
"\n  // Limits: Queues"
"\n  const RedQueueCopyLimits *     queuesCopyLimits;  // Array of queuesCount"
"\n  // Limits: Memory                                                           // Guaranteed limits:       // Limits descriptions:"
"\n  unsigned                       maxMemoryAllocateCount;                      // Min: 4096                // Max number of allocations redMemoryAllocate* can make"
"\n  uint64_t                       minMemoryAllocateBytesAlignment;             // Min: 64                  // Min alignment bytes for redMemoryAllocate*::bytesCount"
"\n  uint64_t                       maxMemoryAllocateBytesCount;                 // Min: 2^30                // Max number of bytes for redMemoryAllocate*::bytesCount, even if there is more space available in the heap"
"\n  uint64_t                       minMemoryNonCoherentBlockBytesCount;         // Max: 256                 // Min bytes count and alignment bytes for non-coherent memory blocks. Non-coherent memory must operate only on blocks of this size. The end of non-coherent memory must be aligned to this limit (internal issue 611)"
"\n  unsigned                       maxCreateSamplerCount;                       // Min: 4000                // Max number of samplers redCreateSampler can allocate"
"\n  uint64_t                       minMemoryPageSeparationArrayImageBytesCount; // Min: 1, max: 2 * 65536   // Page separation in bytes between an array and an image to not alias each other, and vice versa. That is, the end of one resource and the beginning of the next resource with a different resource type must be on separate \"pages\" of size minMemoryPageSeparationArrayImageBytesCount"
"\n  // Limits: Arrays"
"\n  uint64_t                       minArrayROCStructMemberRangeBytesAlignment;  // Min: 1, max: 256         // Min alignment bytes for RedStructMemberArray::arrayRangeBytesFirst and RedStructMemberArray::arrayRangeBytesCount for RO constant arrays"
"\n  uint64_t                       maxArrayROCStructMemberRangeBytesCount;      // Min: 16384, on PC: 65536 // Max number of bytes for RedStructMemberArray::arrayRangeBytesCount                                                for RO constant arrays"
"\n  uint64_t                       minArrayRORWStructMemberRangeBytesAlignment; // Min: 1, max: 256         // Min alignment bytes for RedStructMemberArray::arrayRangeBytesFirst and RedStructMemberArray::arrayRangeBytesCount for RO or RW    arrays"
"\n  uint64_t                       maxArrayRORWStructMemberRangeBytesCount;     // Min: 2^27 (2048 * 65536) // Max number of bytes for RedStructMemberArray::arrayRangeBytesCount                                                for RO or RW    arrays"
"\n  unsigned                       maxArrayIndexUint32Value;                    // Min: (2^24)-1            // Max index value that can be used for indexed procedure calls. -1 excludes the primitive restart index value of 0xFFFFFFFF"
"\n  // Limits: Images"
"\n  unsigned                       maxImageDimensions1D;                        // Min: 4096                // Max dimension (width)                    supported for RED_IMAGE_DIMENSIONS_1D images"
"\n  unsigned                       maxImageDimensions2D;                        // Min: 4096                // Max dimension (width or height)          supported for RED_IMAGE_DIMENSIONS_2D images"
"\n  unsigned                       maxImageDimensions3D;                        // Min: 256                 // Max dimension (width or height or depth) supported for RED_IMAGE_DIMENSIONS_3D and RED_IMAGE_DIMENSIONS_3D_WITH_TEXTURE_DIMENSIONS_2D_AND_2D_LAYERED images"
"\n  unsigned                       maxImageDimensionsCube;                      // Min: 4096                // Max dimension (width or height)          supported for RED_IMAGE_DIMENSIONS_2D_WITH_TEXTURE_DIMENSIONS_CUBE_AND_CUBE_LAYERED images"
"\n  unsigned                       maxImageLayersCount;                         // Min: 256                 // Max number of layers for a layered image"
"\n  // Limits: Samplers"
"\n  float                          maxSamplerMipLodBias;                        // Min: 2.f                 // Max absolute sampler LOD bias. The sum of the redCreateSampler::mipLodBias and the Bias operand of image sampling operations in GPU code (or 0 if no Bias operand is provided to an image sampling operation) are clamped to the range [-maxSamplerMipLodBias,+maxSamplerMipLodBias]"
"\n  float                          maxSamplerAnisotropy;                        // Min: 16.f                // Max degree of sampler anisotropy. The maximum degree of anisotropic filtering used for an image sampling operation is the minimum of the redCreateSampler::maxAnisotropy and this limit"
"\n  unsigned                       precisionBitsSamplerFilteringMagMin;         // Min: 4                   // The number of bits of precision in the division along an axis of an image used for magnification and minification filters. 2^precisionBitsSamplerFilteringMagMin is the actual number of divisions along each axis of the image represented. Sub-texel values calculated during image sampling will snap to these locations when generating the filtered results"
"\n  unsigned                       precisionBitsSamplerFilteringMip;            // Min: 4                   // The number of bits of precision in the division that the LOD calculation for mip fetching get snapped to when determining the contribution from each mip level to the mip filtered results. 2^precisionBitsSamplerFilteringMip is the actual number of divisions. For example, if this value is 2 bits then when linearly filtering between two levels, each level could contribute 0%, 33%, 66%, or 100% (this is just an example and the amount of contribution should be covered by different equations)"
"\n  // Limits: Output declarations and outputs"
"\n  unsigned                       maxOutputWidth;                              // Min: 4096                // Max width  for an output"
"\n  unsigned                       maxOutputHeight;                             // Min: 4096                // Max height for an output"
"\n  unsigned                       maxOutputColorsCount;                        // Min: 4, max: 8           // Max number of colors an output can have"
"\n  RedMultisampleCountBitflags    supportedMultisampleCountsForOutputDepth;    // Min: 1 | 4               // Supported multisample counts for output depth"
"\n  RedMultisampleCountBitflags    supportedMultisampleCountsForOutputStencil;  // Min: 1 | 4               // Supported multisample counts for output stencil"
"\n  RedMultisampleCountBitflags    supportedMultisampleCountsForOutputColor;    // Min: 1 | 4               // Supported multisample counts for output color with floating-point formats. Does not cover integer formats (internal issue 550, c8c0862dee6ba9ed861e87648c59fcdf8a032f3a)"
"\n  RedMultisampleCountBitflags    supportedMultisampleCountsForEmptyOutput;    // Min: 1 | 4               // Supported multisample counts for empty output"
"\n  // Limits: Struct declarations and structs"
"\n  unsigned                       maxStructSlotsCount;                         // Min: 1024                // Max number of slots a struct can have"
"\n  unsigned                       maxStructPerStageArrayROCsCount;             // Min: 12                  // Max number of RO constant arrays allowed per-stage in a struct"
"\n  unsigned                       maxStructPerStageArrayRORWsCount;            // Min: 4                   // Max number of RO or RW    arrays allowed per-stage in a struct"
"\n  unsigned                       maxStructPerStageSamplersCount;              // Min: 16                  // Max number of samplers           allowed per-stage in a struct"
"\n  unsigned                       maxStructPerStageTextureROsCount;            // Min: 16                  // Max number of RO textures        allowed per-stage in a struct"
"\n  unsigned                       maxStructPerStageTextureRWsCount;            // Min: 4                   // Max number of RW textures        allowed per-stage in a struct"
"\n  unsigned                       maxStructPerStageAllResourcesCount;          // Min: 128                 // Max number of all resources      allowed per-stage in a struct"
"\n  unsigned                       maxStructArrayROCsCount;                     // Min: 12 * stages count   // Max number of RO constant arrays allowed in all stages in a struct"
"\n  unsigned                       maxStructArrayRORWsCount;                    // Min: 4  * stages count   // Max number of RO or RW    arrays allowed in all stages in a struct"
"\n  unsigned                       maxStructSamplersCount;                      // Min: 16 * stages count   // Max number of samplers           allowed in all stages in a struct"
"\n  unsigned                       maxStructTextureROsCount;                    // Min: 16 * stages count   // Max number of RO textures        allowed in all stages in a struct"
"\n  unsigned                       maxStructTextureRWsCount;                    // Min: 4  * stages count   // Max number of RW textures        allowed in all stages in a struct"
"\n  // Limits: Procedure parameters"
"\n  unsigned                       maxProcedureParametersVariablesBytesCount;   // Min: 128                 // Max number of bytes for procedure parameters variables in all stages"
"\n  // Limits: Viewport"
"\n  unsigned                       maxViewportDimensions[2];                    // Min: 4096, 4096          // Max viewport dimensions (width, height)"
"\n  float                          minViewportBoundsRange;                      // Max: -8192.f             // Min viewport bounds range that the corners of a viewport must be contained in"
"\n  float                          maxViewportBoundsRange;                      // Min: 8191.f              // Max Viewport bounds range that the corners of a viewport must be contained in"
"\n  unsigned                       precisionBitsViewportCoordinates;            // Min: 4                   // The number of bits of subpixel precision in  viewport coordinates x and y"
"\n  unsigned                       precisionBitsViewportBounds;                 // Min: 0                   // The number of bits of subpixel precision for viewport bounds. The subpixel precision that floating-point viewport bounds are interpreted at is given by this limit"
"\n  // Limits: Vertex stage and fragment stage"
"\n  unsigned                       maxPerStageClipDistances;                    // Min: 8                   // Max number of clip distances allowed per-stage"
"\n  unsigned                       maxPerStageCullDistances;                    // Min: 8                   // Max number of cull distances allowed per-stage"
"\n  unsigned                       maxPerStageClipAndCullDistances;             // Min: 8                   // Max number of clip and cull distances combined allowed per-stage. The sum of the sizes of any pair of arrays declared with the ClipDistance and CullDistance built-in decoration used by a single stage must be less than or equal to this limit"
"\n  // Limits: Vertex stage"
"\n  unsigned                       maxVertexOutputLocationsCount;               // Min: 64                  // Max number of output locations in the vertex   stage. All location values used in GPU code must be below this limit"
"\n  // Limits: Fragment stage"
"\n  unsigned                       maxFragmentInputLocationsCount;              // Min: 64                  // Max number of input  locations in the fragment stage. All location values used in GPU code must be below this limit"
"\n  unsigned                       maxFragmentOutputColorsCount;                // Min: 4, max: 8           // Max number of output colors in the fragment stage"
"\n  unsigned                       maxFragmentOutputColorsCountBlendDualSource; // Min: 1, max: 8           // Max number of output colors in the fragment stage when using dual-source blend"
"\n  unsigned                       maxFragmentOutputResourcesCount;             // Min: 4                   // Max number of RW arrays, RW textures and output colors combined"
"\n  // Limits: Compute stage"
"\n  unsigned                       maxComputeSharedMemoryBytesCount;            // Min: 16384, on PC: 32768 // Max number of bytes for shared memory"
"\n  unsigned                       maxComputeWorkgroupsCount[3];                // Min: 65535, 65535, 65535 // Max number of compute workgroups (workgroupsCountX, workgroupsCountY, workgroupsCountZ) that may be dispatched by a single redCallProcedureCompute call"
"\n  unsigned                       maxComputeWorkgroupInvocationsCount;         // Min: 128                 // Max number of compute invocations in a single workgroup"
"\n  unsigned                       maxComputeWorkgroupDimensions[3];            // Min: 128, 128, 64        // Max workgroup dimensions (x, y, z)"
"\n  // Limits: OpImageSample*, OpImageFetch*"
"\n  int                            minImageSampleImageFetchOffset;              // Max: -8                  // The minimum offset value for the ConstOffset image operand of any of the OpImageSample* or OpImageFetch* image IR instructions"
"\n  unsigned                       maxImageSampleImageFetchOffset;              // Min: 7                   // The maximum offset value for the ConstOffset image operand of any of the OpImageSample* or OpImageFetch* image IR instructions"
"\n  // Limits: OpImage*Gather"
"\n  int                            minImageGatherOffset;                        // Max: -8                  // The minimum offset value for the Offset or ConstOffsets image operands of any of the OpImage*Gather image IR instructions"
"\n  unsigned                       maxImageGatherOffset;                        // Min: 7                   // The maximum offset value for the Offset or ConstOffsets image operands of any of the OpImage*Gather image IR instructions"
"\n  // Limits: interpolateAtOffset"
"\n  float                          minInterpolateAtOffset;                      // Max: -0.5f                                               // The minimum negative offset value for the offset operand of the InterpolateAtOffset extended IR instruction. The value describes the closed interval of supported interpolation offsets"
"\n  float                          maxInterpolateAtOffset;                      // Min: 0.5f - (1.f / 2.f^precisionBitsInterpolateAtOffset) // The maximum positive offset value for the offset operand of the InterpolateAtOffset extended IR instruction. The value describes the closed interval of supported interpolation offsets"
"\n  unsigned                       precisionBitsInterpolateAtOffset;            // Min: 4                                                   // The number of subpixel fractional bits that the x and y offsets to the InterpolateAtOffset extended IR instruction may be rounded to as fixed-point values. If precisionBitsInterpolateAtOffset is 4, this provides increments of (1.f / 2.f^4) = 0.0625, and thus the range of supported interpolation offsets would be [-0.5, 0.4375]"
"\n  // Limits: Copy calls"
"\n  uint64_t                       optimalCopyArrayImageRangeArrayBytesFirstBytesAlignment;"
"\n  uint64_t                       optimalCopyArrayImageRangeArrayTexelsCountToNextRowBytesAlignment;"
"\n  // Features"
"\n  RedBool32                      supportsWsi;                                                     // WSI specific functionality is supported by the GPU.                                                 If this feature is not available, the GPU handle should not be passed to WSI specific procedures"
"\n  RedBool32                      supportsMemoryGetBudget;                                         // redMemoryGetBudget can return memory budget values.                                                 If this feature is not available, redMemoryGetBudget::outMemoryBudget values won't be set and redMemoryGetBudget::outStatuses will return RED_STATUS_ERROR_FEATURE_IS_NOT_FOUND"
"\n  RedBool32                      supportsFullArrayIndexUint32Value;                               // Full 32-bit range of indices is supported.                                                          If this feature is available,     maxArrayIndexUint32Value must be (2^32)-1. -1 excludes the primitive restart index value of 0xFFFFFFFF"
"\n  RedBool32                      supportsSamplerAnisotropy;                                       // Anisotropic filtering is supported.                                                                 If this feature is not available, the redCreateSampler::enableAnisotropy must be set to 0 and the redCreateSampler::maxAnisotropy is ignored"
"\n  RedBool32                      supportsTextureDimensionsCubeLayered;                            // Specifies whether RED_TEXTURE_DIMENSIONS_CUBE_LAYERED textures can be created.                      If this feature is available,     the SampledCubeArray and ImageCubeArray IR capabilities can be used"
"\n  RedBool32                      supportsProcedureStateRasterizationDepthClamp;                   // Depth clamping is supported.                                                                        If this feature is not available, the RedProcedureState::rasterizationDepthClampEnable             must be set to 0"
"\n  RedBool32                      supportsProcedureStateRasterizationDepthBiasDynamic;             // Dynamic depth bias is supported.                                                                    If this feature is not available, the RedProcedureState::rasterizationDepthBiasDynamic             must be set to 0 and redCallSetDynamicDepthBias          must not be called"
"\n  RedBool32                      supportsProcedureStateRasterizationDepthBiasClamp;               // Depth bias clamping is supported.                                                                   If this feature is not available, the RedProcedureState::rasterizationDepthBiasStaticClamp         must be set to 0 and if RedProcedureState::rasterizationDepthBiasDynamic is available redCallSetDynamicDepthBias::clamp must be set to 0"
"\n  RedBool32                      supportsProcedureStateMultisampleSampleShading;                  // Specifies whether sample shading and multisample interpolation are supported.                       If this feature is not available, the RedProcedureState::multisampleSampleShadingEnable            must be set to 0 and the RedProcedureState::multisampleSampleShadingMin is ignored. This also specifies whether IR can declare the SampleRateShading capability"
"\n  RedBool32                      supportsProcedureStateMultisampleAlphaToOne;                     // The fragment alpha component can be forced to maximum representable alpha value.                    If this feature is not available, the RedProcedureState::multisampleAlphaToOneEnable               must be set to 0"
"\n  RedBool32                      supportsProcedureStateDepthTestBoundsTest;                       // Depth bounds test is supported.                                                                     If this feature is not available, the RedProcedureState::depthTestBoundsTestEnable                 must be set to 0 and the RedProcedureState::depthTestBoundsTestStaticMin, RedProcedureState::depthTestBoundsTestStaticMax, redCallSetDynamicDepthBounds::min and redCallSetDynamicDepthBounds::max are ignored"
"\n  RedBool32                      supportsProcedureStateDepthTestBoundsTestDynamic;                // Dynamic depth bounds test is supported.                                                             If this feature is not available, the RedProcedureState::depthTestBoundsTestDynamic                must be set to 0 and redCallSetDynamicDepthBounds        must not be called"
"\n  RedBool32                      supportsProcedureStateStencilTestFrontAndBackDynamicCompareMask; // Dynamic compare mask is supported.                                                                  If this feature is not available, the RedProcedureState::stencilTestFrontAndBackDynamicCompareMask must be set to 0 and redCallSetDynamicStencilCompareMask must not be called"
"\n  RedBool32                      supportsProcedureStateStencilTestFrontAndBackDynamicWriteMask;   // Dynamic write mask is supported.                                                                    If this feature is not available, the RedProcedureState::stencilTestFrontAndBackDynamicWriteMask   must be set to 0 and redCallSetDynamicStencilWriteMask   must not be called"
"\n  RedBool32                      supportsProcedureStateBlendLogicOp;                              // Logic operations are supported.                                                                     If this feature is not available, the RedProcedureState::blendLogicOpEnable                        must be set to 0 and the RedProcedureState::blendLogicOp is ignored"
"\n  RedBool32                      supportsProcedureStateOutputColorsBlendVaryingPerColor;          // Blend operations are controlled per output color.                                                   If this feature is not available, the RedProcedureState::outputColorsBlend* values for all output colors must be identical. Otherwise, different RedProcedureState::outputColorsBlend* values can be provided for output colors"
"\n  RedBool32                      supportsProcedureStateOutputColorsBlendDualSource;               // Blend operations which take two sources are supported.                                              If this feature is not available, the RED_BLEND_FACTOR_SOURCE1_COLOR, RED_BLEND_FACTOR_ONE_MINUS_SOURCE1_COLOR, RED_BLEND_FACTOR_SOURCE1_ALPHA or RED_BLEND_FACTOR_ONE_MINUS_SOURCE1_ALPHA must not be used as source or target blend factors"
"\n  RedBool32                      supportsMultisampleEmptyOutputVariableMultisampleCount;          // Multisample rate can be different for all procedure calls in an empty output.                       If this feature is not available, the current output is empty, and this is not the first procedure call for the current output, then the multisample count specified by this procedure must match that set in the previous procedure"
"\n  RedBool32                      supportsMultisampleStandardSampleLocations;                      // Specifies whether rasterization uses the standard sample locations.                                 If this feature is available,     the implementation uses the documented sample locations. Otherwise, the implementation may use different sample locations"
"\n  RedBool32                      supportsGpuCodeWritesAndAtomicsInStageVertex;                    // Writes and atomic operations on RW textures are supported in the vertex   stage.                    If this feature is not available, all RW texture variables used by the vertex   stage in GPU code must be decorated with the NonWritable decoration in IR"
"\n  RedBool32                      supportsGpuCodeWritesAndAtomicsInStageFragment;                  // Writes and atomic operations on RW textures are supported in the fragment stage.                    If this feature is not available, all RW texture variables used by the fragment stage in GPU code must be decorated with the NonWritable decoration in IR"
"\n  RedBool32                      supportsGpuCodeImageGatherExtended;                              // The extended set of texture gather IR instructions are available in GPU code.                       If this feature is not available, the OpImage*Gather IR instructions do not support the Offset and ConstOffsets operands. This also specifies whether IR can declare the ImageGatherExtended capability"
"\n  RedBool32                      supportsGpuCodeTextureRWExtendedFormats;                         // All the extended RW texture formats are available in GPU code.                                      See StorageImageExtendedFormats in IR specification (internal issue 1273, 0a7a04f32bd473bc7428efdbbbe132f33afad68c)"
"\n  RedBool32                      supportsGpuCodeTextureRWMultisample;                             // Multisample RW textures are supported.                                                              If this feature is not available, images set as RED_STRUCT_MEMBER_TYPE_TEXTURE_RW must be created with multisample count equal to RED_MULTISAMPLE_COUNT_BITFLAG_1. This also specifies whether IR can declare the StorageImageMultisample capability"
"\n  RedBool32                      supportsGpuCodeTextureRWReadWithoutFormat;                       // RW textures don't require a format qualifier to be specified when reading from  RW textures.        If this feature is not available, the OpImageRead  IR instruction must not have an OpTypeImage of Unknown. This also specifies whether IR can declare the StorageImageReadWithoutFormat  capability"
"\n  RedBool32                      supportsGpuCodeTextureRWWriteWithoutFormat;                      // RW textures don't require a format qualifier to be specified when writing to    RW textures.        If this feature is not available, the OpImageWrite IR instruction must not have an OpTypeImage of Unknown. This also specifies whether IR can declare the StorageImageWriteWithoutFormat capability"
"\n  RedBool32                      supportsGpuCodeDynamicallyIndexableArraysOfArrayROCs;            // Arrays of RO constant arrays can be indexed by dynamically uniform integer expressions in GPU code. If this feature is not available, resources with a struct member type of RED_STRUCT_MEMBER_TYPE_ARRAY_RO_CONSTANT must be indexed only by constant integral expressions when aggregated into arrays in GPU code. This also specifies whether IR can declare the UniformBufferArrayDynamicIndexing capability"
"\n  RedBool32                      supportsGpuCodeDynamicallyIndexableArraysOfArrayRORWs;           // Arrays of RO or RW    arrays can be indexed by dynamically uniform integer expressions in GPU code. If this feature is not available, resources with a struct member type of RED_STRUCT_MEMBER_TYPE_ARRAY_RO_RW       must be indexed only by constant integral expressions when aggregated into arrays in GPU code. This also indicates whether IR can declare the StorageBufferArrayDynamicIndexing capability"
"\n  RedBool32                      supportsGpuCodeDynamicallyIndexableArraysOfSamplers;             // Arrays of samplers           can be indexed by dynamically uniform integer expressions in GPU code. If this feature is not available, resources with a struct member type of RED_STRUCT_MEMBER_TYPE_SAMPLER           must be indexed only by constant integral expressions when aggregated into arrays in GPU code. This also specifies whether IR can declare the SampledImageArrayDynamicIndexing  capability"
"\n  RedBool32                      supportsGpuCodeDynamicallyIndexableArraysOfTextureROs;           // Arrays of RO textures        can be indexed by dynamically uniform integer expressions in GPU code. If this feature is not available, resources with a struct member type of RED_STRUCT_MEMBER_TYPE_TEXTURE_RO        must be indexed only by constant integral expressions when aggregated into arrays in GPU code. This also specifies whether IR can declare the SampledImageArrayDynamicIndexing  capability"
"\n  RedBool32                      supportsGpuCodeDynamicallyIndexableArraysOfTextureRWs;           // Arrays of RW textures        can be indexed by dynamically uniform integer expressions in GPU code. If this feature is not available, resources with a struct member type of RED_STRUCT_MEMBER_TYPE_TEXTURE_RW        must be indexed only by constant integral expressions when aggregated into arrays in GPU code. This also specifies whether IR can declare the StorageImageArrayDynamicIndexing  capability"
"\n  RedBool32                      supportsGpuCodeClipDistance;                                     // Clip distances are supported in GPU code.                                                           If this feature is not available, any members decorated with the ClipDistance built-in decoration must not be read from or written to in GPU code. This also specifies whether IR can declare the ClipDistance capability"
"\n  RedBool32                      supportsGpuCodeCullDistance;                                     // Cull distances are supported in GPU code.                                                           If this feature is not available, any members decorated with the CullDistance built-in decoration must not be read from or written to in GPU code. This also specifies whether IR can declare the CullDistance capability"
"\n  RedBool32                      supportsGpuCodeInt64;                                            // 64-bit integers (signed and unsigned) are supported in GPU code.                                    If this feature is not available, 64-bit integer        types must not be used in GPU code. This also specifies whether IR can declare the Int64   capability"
"\n  RedBool32                      supportsGpuCodeFloat64;                                          // 64-bit floats   (doubles)             are supported in GPU code.                                    If this feature is not available, 64-bit floating-point types must not be used in GPU code. This also specifies whether IR can declare the Float64 capability"
"\n  RedBool32                      supportsGpuCodeMinLod;                                           // Image operations that specify the minimum resource LOD are supported in GPU code.                   If this feature is not available, the    MinLod image operand must not be used in GPU code. This also specifies whether IR can declare the MinLod  capability"
"\n  // Image formats"
"\n  const RedImageFormatLimits *   imageFormatsLimitsImageDimensions1D;                                        // Count: 131, indexable with RedFormat values"
"\n  const RedImageFormatLimits *   imageFormatsLimitsImageDimensions2D;                                        // Count: 131, indexable with RedFormat values"
"\n  const RedImageFormatLimits *   imageFormatsLimitsImageDimensions2DMultisample;                             // Count: 131, indexable with RedFormat values"
"\n  const RedImageFormatLimits *   imageFormatsLimitsImageDimensions2DWithTextureDimensionsCubeAndCubeLayered; // Count: 131, indexable with RedFormat values"
"\n  const RedImageFormatLimits *   imageFormatsLimitsImageDimensions3D;                                        // Count: 131, indexable with RedFormat values"
"\n  const RedImageFormatLimits *   imageFormatsLimitsImageDimensions3DWithTextureDimensions2DAnd2DLayered;     // Count: 131, indexable with RedFormat values"
"\n  const RedImageFormatFeatures * imageFormatsFeatures;                                                       // Count: 131, indexable with RedFormat values"
"\n  const void *                   optionalInfo;                                                               // A NULL or a pointer to a singly linked list of RedGpuInfoOptionalInfo* structs"
"\n} RedGpuInfo;"
"\n"
"\ntypedef struct RedStatuses {"
"\n  RedStatus      status;"
"\n  unsigned       statusCode;"
"\n  int            statusHresult;"
"\n  RedProcedureId statusProcedureId;"
"\n  const char *   statusFile;"
"\n  int            statusLine;"
"\n  RedStatus      statusError;"
"\n  unsigned       statusErrorCode;"
"\n  int            statusErrorHresult;"
"\n  RedProcedureId statusErrorProcedureId;"
"\n  const char *   statusErrorFile;"
"\n  int            statusErrorLine;"
"\n  char           statusErrorDescription[512];"
"\n} RedStatuses;"
"\n"
"\nstruct RedTypeContext {"
"\n  unsigned            gpusCount;"
"\n  const RedGpuInfo *  gpus;"
"\n  const RedStatuses * gpusStatuses; // Array of gpusCount"
"\n  RedHandleContext    handle;"
"\n  void *              userData;"
"\n};"
"\n"
"\ntypedef enum RedSdkExtension {"
"\n  RED_SDK_EXTENSION_NONE                                      = 0,"
"\n  RED_SDK_EXTENSION_ADDITIONAL_INFO_0                         = 1,"
"\n  RED_SDK_EXTENSION_WSI_WIN32                                 = 2,  // WSI specific"
"\n  RED_SDK_EXTENSION_WSI_XLIB                                  = 3,  // WSI specific"
"\n  RED_SDK_EXTENSION_WSI_XCB                                   = 4,  // WSI specific"
"\n  RED_SDK_EXTENSION_TREAT_ALL_MAPPABLE_MEMORY_AS_NON_COHERENT = 5,"
"\n  RED_SDK_EXTENSION_DRIVER_PROPERTIES                         = 6,"
"\n  RED_SDK_EXTENSION_RESOLVE_DEPTH_STENCIL                     = 7,"
"\n  RED_SDK_EXTENSION_DEDICATE_MEMORY                           = 8,"
"\n  RED_SDK_EXTENSION_PROCEDURE_PARAMETERS_HANDLES              = 9,"
"\n  RED_SDK_EXTENSION_BATCH_MEMORY_SET                          = 10,"
"\n  RED_SDK_EXTENSION_RASTERIZATION_MODE                        = 11,"
"\n  RED_SDK_EXTENSION_FORMAL_MEMORY_MODEL                       = 12,"
"\n  RED_SDK_EXTENSION_RAY_TRACING                               = 13,"
"\n} RedSdkExtension;"
"\n"
"\ntypedef enum RedGpuInfoOptionalInfo {"
"\n  RED_GPU_INFO_OPTIONAL_INFO_NONE                                      = 0,"
"\n  RED_GPU_INFO_OPTIONAL_INFO_ADDITIONAL_INFO_0                         = 1,"
"\n  RED_GPU_INFO_OPTIONAL_INFO_WSI_WIN32                                 = 2,  // WSI specific"
"\n  RED_GPU_INFO_OPTIONAL_INFO_WSI_XLIB                                  = 3,  // WSI specific"
"\n  RED_GPU_INFO_OPTIONAL_INFO_WSI_XCB                                   = 4,  // WSI specific"
"\n  RED_GPU_INFO_OPTIONAL_INFO_TREAT_ALL_MAPPABLE_MEMORY_AS_NON_COHERENT = 5,"
"\n  RED_GPU_INFO_OPTIONAL_INFO_DRIVER_PROPERTIES                         = 6,"
"\n  RED_GPU_INFO_OPTIONAL_INFO_RESOLVE_DEPTH_STENCIL                     = 7,"
"\n  RED_GPU_INFO_OPTIONAL_INFO_DEDICATE_MEMORY                           = 8,"
"\n  RED_GPU_INFO_OPTIONAL_INFO_PROCEDURE_PARAMETERS_HANDLES              = 9,"
"\n  RED_GPU_INFO_OPTIONAL_INFO_BATCH_MEMORY_SET                          = 10,"
"\n  RED_GPU_INFO_OPTIONAL_INFO_RASTERIZATION_MODE                        = 11,"
"\n  RED_GPU_INFO_OPTIONAL_INFO_FORMAL_MEMORY_MODEL                       = 12,"
"\n  RED_GPU_INFO_OPTIONAL_INFO_RAY_TRACING                               = 13,"
"\n} RedGpuInfoOptionalInfo;"
"\n"
"\ntypedef enum RedDriverId {"
"\n  RED_DRIVER_ID_UNKNOWN                   = 0,"
"\n  RED_DRIVER_ID_AMD_PROPRIETARY           = 1,"
"\n  RED_DRIVER_ID_AMD_OPEN_SOURCE           = 2,"
"\n  RED_DRIVER_ID_MESA_RADV                 = 3,"
"\n  RED_DRIVER_ID_NVIDIA_PROPRIETARY        = 4,"
"\n  RED_DRIVER_ID_INTEL_PROPRIETARY_WINDOWS = 5,"
"\n  RED_DRIVER_ID_INTEL_OPEN_SOURCE_MESA    = 6,"
"\n  RED_DRIVER_ID_IMAGINATION_PROPRIETARY   = 7,"
"\n  RED_DRIVER_ID_QUALCOMM_PROPRIETARY      = 8,"
"\n  RED_DRIVER_ID_ARM_PROPRIETARY           = 9,"
"\n  RED_DRIVER_ID_GOOGLE_SWIFTSHADER        = 10,"
"\n  RED_DRIVER_ID_GGP_PROPRIETARY           = 11,"
"\n  RED_DRIVER_ID_BROADCOM_PROPRIETARY      = 12,"
"\n} RedDriverId;"
"\n"
"\ntypedef struct RedGpuInfoOptionalInfoIterator {"
"\n  unsigned     optionalInfo;"
"\n  const void * next;"
"\n} RedGpuInfoOptionalInfoIterator;"
"\n"
"\ntypedef struct RedGpuInfoOptionalInfoAdditionalInfo0 {"
"\n  RedGpuInfoOptionalInfo optionalInfo;"
"\n  const void *           next;"
"\n  RedBool32              supportsArraysImagesUsageBeforeMemorySet;"
"\n  RedBool32              supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfArrays;"
"\n  RedBool32              supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfImages;"
"\n  RedBool32              supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfImagesMultisample;"
"\n  RedBool32              supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfImagesDepthStencil;"
"\n} RedGpuInfoOptionalInfoAdditionalInfo0;"
"\n"
"\ntypedef struct RedGpuInfoOptionalInfoDriverProperties {"
"\n  RedGpuInfoOptionalInfo optionalInfo;"
"\n  const void *           next;"
"\n  RedDriverId            id;"
"\n  char                   name[256];"
"\n  char                   info[256];"
"\n  unsigned char          compliantWithConformanceTestSuiteVersionMajor;"
"\n  unsigned char          compliantWithConformanceTestSuiteVersionMinor;"
"\n  unsigned char          compliantWithConformanceTestSuiteVersionSubminor;"
"\n  unsigned char          compliantWithConformanceTestSuiteVersionPatch;"
"\n} RedGpuInfoOptionalInfoDriverProperties;"
"\n"
"\ntypedef struct RedGpuInfoOptionalInfoResolveDepthStencil {"
"\n  RedGpuInfoOptionalInfo optionalInfo;"
"\n  const void *           next;"
"\n  RedBool32              supportsResolveDepthStencil;"
"\n  RedBool32              supportsResolveModeDepthSampleIndexZero;"
"\n  RedBool32              supportsResolveModeDepthAverage;"
"\n  RedBool32              supportsResolveModeDepthMin;"
"\n  RedBool32              supportsResolveModeDepthMax;"
"\n  RedBool32              supportsResolveModeStencilSampleIndexZero;"
"\n  RedBool32              supportsResolveModeStencilAverage;"
"\n  RedBool32              supportsResolveModeStencilMin;"
"\n  RedBool32              supportsResolveModeStencilMax;"
"\n  RedBool32              supportsResolveIndependentNone;"
"\n  RedBool32              supportsResolveIndependent;"
"\n} RedGpuInfoOptionalInfoResolveDepthStencil;"
"\n"
"\ntypedef struct RedGpuInfoOptionalInfoProcedureParametersHandles {"
"\n  RedGpuInfoOptionalInfo optionalInfo;"
"\n  const void *           next;"
"\n  RedBool32              supportsProcedureParametersHandles;"
"\n  unsigned               maxProcedureParametersHandlesCount;"
"\n} RedGpuInfoOptionalInfoProcedureParametersHandles;"
"\n"
"\ntypedef struct RedGpuInfoOptionalInfoRasterizationMode {"
"\n  RedGpuInfoOptionalInfo optionalInfo;"
"\n  const void *           next;"
"\n  RedBool32              supportsRasterizationModeOverestimate;"
"\n  RedBool32              supportsRasterizationModeUnderestimate;"
"\n  RedBool32              supportsGuaranteedZeroAreaBackFacingTriangles;"
"\n  RedBool32              supportsGpuCodeFullyCoveredEXT;"
"\n} RedGpuInfoOptionalInfoRasterizationMode;"
"\n"
"\ntypedef struct RedGpuInfoOptionalInfoFormalMemoryModel {"
"\n  RedGpuInfoOptionalInfo optionalInfo;"
"\n  const void *           next;"
"\n  RedBool32              supportsFormalMemoryModel;"
"\n  RedBool32              supportsFormalMemoryModelGpuScopeSynchronization;"
"\n  RedBool32              supportsFormalMemoryModelAvailabilityAndVisibilityChains;"
"\n} RedGpuInfoOptionalInfoFormalMemoryModel;"
"\n"
"\ntypedef struct RedGpuInfoOptionalInfoRayTracing {"
"\n  RedGpuInfoOptionalInfo optionalInfo;"
"\n  const void *           next;"
"\n  RedBool32              supportsRayTracing;"
"\n} RedGpuInfoOptionalInfoRayTracing;"
"\n"
"\n// redMemoryGetBudget"
"\n"
"\ntypedef struct RedMemoryBudget {"
"\n  unsigned setTo1000237000;"
"\n  size_t   setTo0;"
"\n  uint64_t memoryHeapsBudget[16]; // Array of RedGpuInfo::memoryHeapsCount"
"\n  uint64_t memoryHeapsUsage[16];  // Array of RedGpuInfo::memoryHeapsCount"
"\n} RedMemoryBudget;"
"\n"
"\n// redMemoryAllocate"
"\n// redMemoryAllocateMappable"
"\n"
"\ntypedef unsigned RedMemoryBitflags;"
"\ntypedef enum RedMemoryBitflag {"
"\n  RED_MEMORY_BITFLAG_ALLOW_ATOMICS = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0001),"
"\n} RedMemoryBitflag;"
"\n"
"\n// redMemorySet"
"\n"
"\ntypedef struct RedMemoryArray {"
"\n  unsigned        setTo1000157000;"
"\n  size_t          setTo0;"
"\n  RedHandleArray  array;"
"\n  RedHandleMemory memory;"
"\n  uint64_t        memoryBytesFirst;"
"\n} RedMemoryArray;"
"\n"
"\ntypedef struct RedMemoryImage {"
"\n  unsigned        setTo1000157001;"
"\n  size_t          setTo0;"
"\n  RedHandleImage  image;"
"\n  RedHandleMemory memory;"
"\n  uint64_t        memoryBytesFirst;"
"\n} RedMemoryImage;"
"\n"
"\n// redMemoryNonCoherentFlush"
"\n// redMemoryNonCoherentInvalidate"
"\n"
"\ntypedef struct RedMappableMemoryRange {"
"\n  unsigned        setTo6;"
"\n  size_t          setTo0;"
"\n  RedHandleMemory mappableMemory;"
"\n  uint64_t        mappableMemoryRangeBytesFirst;"
"\n  uint64_t        mappableMemoryRangeBytesCount;"
"\n} RedMappableMemoryRange;"
"\n"
"\n// redStructsSet"
"\n"
"\ntypedef enum RedStructMemberType {"
"\n  RED_STRUCT_MEMBER_TYPE_ARRAY_RO_CONSTANT = 6,"
"\n  RED_STRUCT_MEMBER_TYPE_ARRAY_RO_RW       = 7,"
"\n  RED_STRUCT_MEMBER_TYPE_SAMPLER           = 0,"
"\n  RED_STRUCT_MEMBER_TYPE_TEXTURE_RO        = 2,"
"\n  RED_STRUCT_MEMBER_TYPE_TEXTURE_RW        = 3,"
"\n} RedStructMemberType;"
"\n"
"\ntypedef struct RedStructMemberTexture {"
"\n  RedHandleSampler sampler;"
"\n  RedHandleTexture texture;"
"\n  unsigned         setTo1;"
"\n} RedStructMemberTexture;"
"\n"
"\ntypedef struct RedStructMemberArray {"
"\n  RedHandleArray   array;"
"\n  uint64_t         arrayRangeBytesFirst;"
"\n  uint64_t         arrayRangeBytesCount;"
"\n} RedStructMemberArray;"
"\n"
"\ntypedef struct RedStructMember {"
"\n  unsigned                       setTo35;"
"\n  size_t                         setTo0;"
"\n  RedHandleStruct                structure;"
"\n  unsigned                       slot;"
"\n  unsigned                       first;"
"\n  unsigned                       count;"
"\n  RedStructMemberType            type;"
"\n  const RedStructMemberTexture * textures; // Array of count"
"\n  const RedStructMemberArray *   arrays;   // Array of count"
"\n  size_t                         setTo00;"
"\n} RedStructMember;"
"\n"
"\n// redCreateContext"
"\n"
"\ntypedef enum RedSdkVersion {"
"\n  RED_SDK_VERSION_1_0_135 = 0,"
"\n} RedSdkVersion;"
"\n"
"\ntypedef enum RedContextOptionalSettings {"
"\n  RED_CONTEXT_OPTIONAL_SETTINGS_0           = 0,"
"\n  RED_CONTEXT_OPTIONAL_SETTINGS_DEBUG_ARRAY = 1, // Debug specific"
"\n} RedContextOptionalSettings;"
"\n"
"\ntypedef struct RedContextOptionalSettingsIterator {"
"\n  unsigned     settings;"
"\n  const void * next;"
"\n} RedContextOptionalSettingsIterator;"
"\n"
"\ntypedef struct RedContextOptionalSettings0 {"
"\n  RedContextOptionalSettings settings;"
"\n  const void *               next;"
"\n  RedBool32                  skipCheckingContextLayers;"
"\n  RedBool32                  skipCheckingContextExtensions;"
"\n  RedBool32                  gpusExposeOnlyOneQueue;"
"\n} RedContextOptionalSettings0;"
"\n"
"\ntypedef enum RedDebugCallbackSeverity {"
"\n  RED_DEBUG_CALLBACK_SEVERITY_WARNING = REDGPU_B32(0000,0000,0000,0000,0000,0001,0000,0000),"
"\n  RED_DEBUG_CALLBACK_SEVERITY_ERROR   = REDGPU_B32(0000,0000,0000,0000,0001,0000,0000,0000),"
"\n} RedDebugCallbackSeverity;"
"\n"
"\ntypedef unsigned RedDebugCallbackTypeBitflags;"
"\ntypedef enum RedDebugCallbackTypeBitflag {"
"\n  RED_DEBUG_CALLBACK_TYPE_BITFLAG_GENERAL    = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0001),"
"\n  RED_DEBUG_CALLBACK_TYPE_BITFLAG_VALIDATION = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0010),"
"\n} RedDebugCallbackTypeBitflag;"
"\n"
"\ntypedef enum RedHandleType {"
"\n  RED_HANDLE_TYPE_CONTEXT              = 1,"
"\n  RED_HANDLE_TYPE_GPU                  = 3,"
"\n  RED_HANDLE_TYPE_GPU_DEVICE           = 2,"
"\n  RED_HANDLE_TYPE_QUEUE                = 4,"
"\n  RED_HANDLE_TYPE_MEMORY               = 8,"
"\n  RED_HANDLE_TYPE_ARRAY                = 9,"
"\n  RED_HANDLE_TYPE_IMAGE                = 10,"
"\n  RED_HANDLE_TYPE_SAMPLER              = 21,"
"\n  RED_HANDLE_TYPE_TEXTURE              = 14,"
"\n  RED_HANDLE_TYPE_GPU_CODE             = 15,"
"\n  RED_HANDLE_TYPE_OUTPUT_DECLARATION   = 18,"
"\n  RED_HANDLE_TYPE_STRUCT_DECLARATION   = 20,"
"\n  RED_HANDLE_TYPE_PROCEDURE_PARAMETERS = 17,"
"\n  RED_HANDLE_TYPE_PROCEDURE_CACHE      = 16,"
"\n  RED_HANDLE_TYPE_PROCEDURE            = 19,"
"\n  RED_HANDLE_TYPE_OUTPUT               = 24,"
"\n  RED_HANDLE_TYPE_STRUCT               = 23,"
"\n  RED_HANDLE_TYPE_STRUCTS_MEMORY       = 22,"
"\n  RED_HANDLE_TYPE_CALLS                = 6,"
"\n  RED_HANDLE_TYPE_CALLS_MEMORY         = 25,"
"\n  RED_HANDLE_TYPE_CPU_SIGNAL           = 7,"
"\n  RED_HANDLE_TYPE_GPU_SIGNAL           = 5,"
"\n  RED_HANDLE_TYPE_GPU_TO_CPU_SIGNAL    = 11,"
"\n  RED_HANDLE_TYPE_SURFACE              = 1000000000, // WSI specific"
"\n  RED_HANDLE_TYPE_PRESENT              = 1000001000, // WSI specific"
"\n} RedHandleType;"
"\n"
"\ntypedef struct RedHandleInfo {"
"\n  unsigned      _0;"
"\n  const void *  _1;"
"\n  RedHandleType handleType;"
"\n  const void *  handle;"
"\n  const char *  handleName;"
"\n} RedHandleInfo;"
"\n"
"\ntypedef struct RedDebugCallbackData {"
"\n  unsigned              _0;"
"\n  const void *          _1;"
"\n  unsigned              statusCode;"
"\n  const char *          messageIdName;"
"\n  int                   statusHresult;"
"\n  const char *          message;"
"\n  unsigned              _2;"
"\n  const void *          _3;"
"\n  unsigned              _4;"
"\n  const void *          _5;"
"\n  unsigned              handleInfosCount;"
"\n  const RedHandleInfo * handleInfos;"
"\n} RedDebugCallbackData;"
"\n"
"\ntypedef struct RedMemoryAllocationTag {"
"\n  char tag[512];"
"\n} RedMemoryAllocationTag;"
"\n"
"\ntypedef void * (*RedTypeProcedureMalloc)       (size_t bytesCount);"
"\ntypedef void   (*RedTypeProcedureFree)         (void * pointer);"
"\ntypedef void * (*RedTypeProcedureMallocTagged) (size_t bytesCount, unsigned procedureId, uint64_t memoryAllocationCode, const RedMemoryAllocationTag * optionalMemoryAllocationTag, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\ntypedef void   (*RedTypeProcedureFreeTagged)   (void * pointer, unsigned procedureId, uint64_t memoryAllocationCode, const RedMemoryAllocationTag * optionalMemoryAllocationTag, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\ntypedef RedBool32 (REDGPU_CALLING_CONVENTION *RedTypeProcedureDebugCallback) (RedDebugCallbackSeverity severity, RedDebugCallbackTypeBitflags types, const RedDebugCallbackData * data, RedContext context);"
"\n"
"\n// redCreateArray"
"\n"
"\ntypedef enum RedArrayType {"
"\n  RED_ARRAY_TYPE_ARRAY_RW          = REDGPU_B32(0000,0000,0000,0000,0000,0000,0010,0011), // GPU code: RWByteAddressBuffer (RW), RWStructuredBuffer<T> (RW). RWByteAddressBuffer's Load() method expects a byte offset and returns uint value that can be casted to a float with asfloat() procedure. Structured buffer elements cannot be larger than 2048 bytes"
"\n  RED_ARRAY_TYPE_ARRAY_R0          = REDGPU_B32(1000,0000,0000,0000,0000,0000,0000,0000), // GPU code: ByteAddressBuffer   (RO), StructuredBuffer<T>   (RO). ByteAddressBuffer's   Load() method expects a byte offset and returns uint value that can be casted to a float with asfloat() procedure. Structured buffer elements cannot be larger than 2048 bytes"
"\n  RED_ARRAY_TYPE_ARRAY_RO_CONSTANT = REDGPU_B32(0000,0000,0000,0000,0000,0000,0001,0010), // GPU code: ConstantBuffer<T>   (RO)"
"\n  RED_ARRAY_TYPE_INDEX_RO          = REDGPU_B32(0000,0000,0000,0000,0000,0000,0100,0010),"
"\n} RedArrayType;"
"\n"
"\n// redCreateImage"
"\n"
"\ntypedef enum RedImageDimensions {"
"\n  RED_IMAGE_DIMENSIONS_1D                                               = 0,"
"\n  RED_IMAGE_DIMENSIONS_2D                                               = 1,"
"\n  RED_IMAGE_DIMENSIONS_2D_WITH_TEXTURE_DIMENSIONS_CUBE_AND_CUBE_LAYERED = 3,"
"\n  RED_IMAGE_DIMENSIONS_3D                                               = 2,"
"\n  RED_IMAGE_DIMENSIONS_3D_WITH_TEXTURE_DIMENSIONS_2D_AND_2D_LAYERED     = 4,"
"\n} RedImageDimensions;"
"\n"
"\ntypedef enum RedFormat {"
"\n  RED_FORMAT_UNDEFINED                                      = 0,"
"\n  RED_FORMAT_R_8_UINT_TO_FLOAT_0_1                          = 9,   // UINT_TO_FLOAT_0_1: The components are unsigned integer values that get converted to normalized floating-point values in the range [0.f, 1.f]"
"\n  RED_FORMAT_R_8_UINT                                       = 13,"
"\n  RED_FORMAT_R_8_SINT                                       = 14,"
"\n  RED_FORMAT_RGBA_8_8_8_8_UINT_TO_FLOAT_0_1                 = 37,"
"\n  RED_FORMAT_RGBA_8_8_8_8_UINT_TO_FLOAT_0_1_GAMMA_CORRECTED = 43,"
"\n  RED_FORMAT_RGBA_8_8_8_8_UINT                              = 41,"
"\n  RED_FORMAT_RGBA_8_8_8_8_SINT                              = 42,"
"\n  RED_FORMAT_PRESENT_BGRA_8_8_8_8_UINT_TO_FLOAT_0_1         = 50,  // WSI specific"
"\n  RED_FORMAT_R_16_UINT                                      = 74,"
"\n  RED_FORMAT_R_16_SINT                                      = 75,"
"\n  RED_FORMAT_R_16_FLOAT                                     = 76,"
"\n  RED_FORMAT_RGBA_16_16_16_16_UINT                          = 95,"
"\n  RED_FORMAT_RGBA_16_16_16_16_SINT                          = 96,"
"\n  RED_FORMAT_RGBA_16_16_16_16_FLOAT                         = 97,"
"\n  RED_FORMAT_R_32_UINT                                      = 98,"
"\n  RED_FORMAT_R_32_SINT                                      = 99,"
"\n  RED_FORMAT_R_32_FLOAT                                     = 100,"
"\n  RED_FORMAT_RGBA_32_32_32_32_UINT                          = 107,"
"\n  RED_FORMAT_RGBA_32_32_32_32_SINT                          = 108,"
"\n  RED_FORMAT_RGBA_32_32_32_32_FLOAT                         = 109,"
"\n  RED_FORMAT_DEPTH_16_UINT_TO_FLOAT_0_1                     = 124, // RED_IMAGE_PART_BITFLAG_DEPTH"
"\n  RED_FORMAT_DEPTH_32_FLOAT                                 = 126, // RED_IMAGE_PART_BITFLAG_DEPTH"
"\n  RED_FORMAT_DEPTH_24_UINT_TO_FLOAT_0_1_STENCIL_8_UINT      = 129, // RED_IMAGE_PART_BITFLAG_DEPTH | RED_IMAGE_PART_BITFLAG_STENCIL"
"\n  RED_FORMAT_DEPTH_32_FLOAT_STENCIL_8_UINT                  = 130, // RED_IMAGE_PART_BITFLAG_DEPTH | RED_IMAGE_PART_BITFLAG_STENCIL"
"\n} RedFormat;"
"\n"
"\n// redCreateSampler"
"\n"
"\ntypedef enum RedSamplerFiltering {"
"\n  RED_SAMPLER_FILTERING_NEAREST = 0,"
"\n  RED_SAMPLER_FILTERING_LINEAR  = 1,"
"\n} RedSamplerFiltering;"
"\n"
"\ntypedef enum RedSamplerFilteringMip {"
"\n  RED_SAMPLER_FILTERING_MIP_NEAREST = 0,"
"\n  RED_SAMPLER_FILTERING_MIP_LINEAR  = 1,"
"\n} RedSamplerFilteringMip;"
"\n"
"\ntypedef enum RedSamplerBehaviorOutsideTextureCoordinate {"
"\n  RED_SAMPLER_BEHAVIOR_OUTSIDE_TEXTURE_COORDINATE_REPEAT              = 0,"
"\n  RED_SAMPLER_BEHAVIOR_OUTSIDE_TEXTURE_COORDINATE_REPEAT_MIRRORED     = 1,"
"\n  RED_SAMPLER_BEHAVIOR_OUTSIDE_TEXTURE_COORDINATE_CLAMP_TO_EDGE_VALUE = 2,"
"\n} RedSamplerBehaviorOutsideTextureCoordinate;"
"\n"
"\n// redCreateTexture"
"\n"
"\ntypedef unsigned RedImagePartBitflags;"
"\ntypedef enum RedImagePartBitflag {"
"\n  RED_IMAGE_PART_BITFLAG_COLOR   = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0001),"
"\n  RED_IMAGE_PART_BITFLAG_DEPTH   = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0010), // GPU code: R float channel"
"\n  RED_IMAGE_PART_BITFLAG_STENCIL = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0100), // GPU code: G uint  channel"
"\n} RedImagePartBitflag;"
"\n"
"\ntypedef enum RedTextureDimensions {"
"\n  RED_TEXTURE_DIMENSIONS_1D           = 0, // GPU code: {RW}Texture1D<T>"
"\n  RED_TEXTURE_DIMENSIONS_1D_LAYERED   = 4, // GPU code: {RW}Texture1DArray<T>"
"\n  RED_TEXTURE_DIMENSIONS_2D           = 1, // GPU code: {RW}Texture{2D,2DMS}<T>"
"\n  RED_TEXTURE_DIMENSIONS_2D_LAYERED   = 5, // GPU code: {RW}Texture{2DArray,2DMSArray}<T>"
"\n  RED_TEXTURE_DIMENSIONS_3D           = 2, // GPU code: {RW}Texture3D<T>"
"\n  RED_TEXTURE_DIMENSIONS_CUBE         = 3, // GPU code: TextureCube<T>"
"\n  RED_TEXTURE_DIMENSIONS_CUBE_LAYERED = 6, // GPU code: TextureCubeArray<T> // Depends on RedGpuInfo::supportsTextureDimensionsCubeLayered"
"\n} RedTextureDimensions;"
"\n"
"\n// redCreateOutputDeclaration"
"\n"
"\ntypedef enum RedSetProcedureOutputOp {"
"\n  RED_SET_PROCEDURE_OUTPUT_OP_PRESERVE = 0,"
"\n  RED_SET_PROCEDURE_OUTPUT_OP_CLEAR    = 1,"
"\n  RED_SET_PROCEDURE_OUTPUT_OP_DISCARD  = 2,"
"\n} RedSetProcedureOutputOp;"
"\n"
"\ntypedef enum RedEndProcedureOutputOp {"
"\n  RED_END_PROCEDURE_OUTPUT_OP_PRESERVE = 0,"
"\n  RED_END_PROCEDURE_OUTPUT_OP_DISCARD  = 1,"
"\n} RedEndProcedureOutputOp;"
"\n"
"\ntypedef enum RedResolveMode {"
"\n  RED_RESOLVE_MODE_NONE              = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0000),"
"\n  RED_RESOLVE_MODE_SAMPLE_INDEX_ZERO = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0001),"
"\n  RED_RESOLVE_MODE_AVERAGE           = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0010),"
"\n  RED_RESOLVE_MODE_MIN               = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0100),"
"\n  RED_RESOLVE_MODE_MAX               = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,1000),"
"\n} RedResolveMode;"
"\n"
"\ntypedef struct RedOutputDeclarationMembers {"
"\n  RedBool32                  depthStencilEnable;"
"\n  RedFormat                  depthStencilFormat;"
"\n  RedMultisampleCountBitflag depthStencilMultisampleCount;"
"\n  RedSetProcedureOutputOp    depthStencilDepthSetProcedureOutputOp;"
"\n  RedEndProcedureOutputOp    depthStencilDepthEndProcedureOutputOp;"
"\n  RedSetProcedureOutputOp    depthStencilStencilSetProcedureOutputOp;"
"\n  RedEndProcedureOutputOp    depthStencilStencilEndProcedureOutputOp;"
"\n  RedBool32                  depthStencilSharesMemoryWithAnotherMember;"
"\n  unsigned                   colorsCount;                               // Max: 8"
"\n  RedFormat                  colorsFormat[8];"
"\n  RedMultisampleCountBitflag colorsMultisampleCount[8];"
"\n  RedSetProcedureOutputOp    colorsSetProcedureOutputOp[8];"
"\n  RedEndProcedureOutputOp    colorsEndProcedureOutputOp[8];"
"\n  RedBool32                  colorsSharesMemoryWithAnotherMember[8];"
"\n} RedOutputDeclarationMembers;"
"\n"
"\ntypedef struct RedOutputDeclarationMembersResolveSources {"
"\n  RedResolveMode resolveModeDepth;"
"\n  RedResolveMode resolveModeStencil;"
"\n  RedBool32      resolveDepthStencil;"
"\n  RedBool32      resolveColors;"
"\n} RedOutputDeclarationMembersResolveSources;"
"\n"
"\n// redCreateStructDeclaration"
"\n"
"\ntypedef unsigned RedVisibleToStageBitflags;"
"\ntypedef enum RedVisibleToStageBitflag {"
"\n  RED_VISIBLE_TO_STAGE_BITFLAG_VERTEX   = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0001),"
"\n  RED_VISIBLE_TO_STAGE_BITFLAG_FRAGMENT = REDGPU_B32(0000,0000,0000,0000,0000,0000,0001,0000),"
"\n  RED_VISIBLE_TO_STAGE_BITFLAG_COMPUTE  = REDGPU_B32(0000,0000,0000,0000,0000,0000,0010,0000),"
"\n} RedVisibleToStageBitflag;"
"\n"
"\ntypedef struct RedStructDeclarationMember {"
"\n  unsigned                  slot;"
"\n  RedStructMemberType       type;            // RED_SDK_EXTENSION_PROCEDURE_PARAMETERS_HANDLES supported types: RED_STRUCT_MEMBER_TYPE_ARRAY_RO_CONSTANT, RED_STRUCT_MEMBER_TYPE_ARRAY_RO_RW"
"\n  unsigned                  count;           // RED_SDK_EXTENSION_PROCEDURE_PARAMETERS_HANDLES supported count: 1, RedStructDeclarationMember::inlineSampler supported count: 1"
"\n  RedVisibleToStageBitflags visibleToStages;"
"\n  const RedHandleSampler *  inlineSampler;   // Array of 1"
"\n} RedStructDeclarationMember;"
"\n"
"\ntypedef struct RedStructDeclarationMemberArrayRO {"
"\n  unsigned                  slot;"
"\n} RedStructDeclarationMemberArrayRO;"
"\n"
"\n// redCreateProcedureParameters"
"\n"
"\ntypedef struct RedProcedureParametersDeclaration {"
"\n  unsigned                   variablesSlot;"
"\n  RedVisibleToStageBitflags  variablesVisibleToStages;"
"\n  unsigned                   variablesBytesCount;"
"\n  unsigned                   structsDeclarationsCount; // Max: 7"
"\n  RedHandleStructDeclaration structsDeclarations[7];"
"\n  RedHandleStructDeclaration handlesDeclaration;"
"\n} RedProcedureParametersDeclaration;"
"\n"
"\n// redCreateProcedure"
"\n"
"\ntypedef enum RedPrimitiveTopology {"
"\n  RED_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST  = 3,"
"\n  RED_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP = 4,"
"\n} RedPrimitiveTopology;"
"\n"
"\ntypedef enum RedCullMode {"
"\n  RED_CULL_MODE_NONE  = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0000),"
"\n  RED_CULL_MODE_FRONT = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0001),"
"\n  RED_CULL_MODE_BACK  = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0010),"
"\n} RedCullMode;"
"\n"
"\ntypedef enum RedFrontFace {"
"\n  RED_FRONT_FACE_COUNTER_CLOCKWISE = 0,"
"\n  RED_FRONT_FACE_CLOCKWISE         = 1,"
"\n} RedFrontFace;"
"\n"
"\ntypedef enum RedCompareOp {"
"\n  RED_COMPARE_OP_NEVER            = 0,"
"\n  RED_COMPARE_OP_LESS             = 1,"
"\n  RED_COMPARE_OP_EQUAL            = 2,"
"\n  RED_COMPARE_OP_LESS_OR_EQUAL    = 3,"
"\n  RED_COMPARE_OP_GREATER          = 4,"
"\n  RED_COMPARE_OP_NOT_EQUAL        = 5,"
"\n  RED_COMPARE_OP_GREATER_OR_EQUAL = 6,"
"\n  RED_COMPARE_OP_ALWAYS           = 7,"
"\n} RedCompareOp;"
"\n"
"\ntypedef enum RedStencilOp {"
"\n  RED_STENCIL_OP_KEEP                = 0,"
"\n  RED_STENCIL_OP_ZERO                = 1,"
"\n  RED_STENCIL_OP_REPLACE             = 2,"
"\n  RED_STENCIL_OP_INCREMENT_AND_CLAMP = 3,"
"\n  RED_STENCIL_OP_DECREMENT_AND_CLAMP = 4,"
"\n  RED_STENCIL_OP_INVERT              = 5,"
"\n  RED_STENCIL_OP_INCREMENT_AND_WRAP  = 6,"
"\n  RED_STENCIL_OP_DECREMENT_AND_WRAP  = 7,"
"\n} RedStencilOp;"
"\n"
"\ntypedef enum RedLogicOp {"
"\n  RED_LOGIC_OP_CLEAR         = 0,"
"\n  RED_LOGIC_OP_AND           = 1,"
"\n  RED_LOGIC_OP_AND_REVERSE   = 2,"
"\n  RED_LOGIC_OP_COPY          = 3,"
"\n  RED_LOGIC_OP_AND_INVERTED  = 4,"
"\n  RED_LOGIC_OP_NO_OP         = 5,"
"\n  RED_LOGIC_OP_XOR           = 6,"
"\n  RED_LOGIC_OP_OR            = 7,"
"\n  RED_LOGIC_OP_NOR           = 8,"
"\n  RED_LOGIC_OP_EQUIVALENT    = 9,"
"\n  RED_LOGIC_OP_INVERT        = 10,"
"\n  RED_LOGIC_OP_OR_REVERSE    = 11,"
"\n  RED_LOGIC_OP_COPY_INVERTED = 12,"
"\n  RED_LOGIC_OP_OR_INVERTED   = 13,"
"\n  RED_LOGIC_OP_NAND          = 14,"
"\n  RED_LOGIC_OP_SET           = 15,"
"\n} RedLogicOp;"
"\n"
"\ntypedef unsigned RedColorComponentBitflags;"
"\ntypedef enum RedColorComponentBitflag {"
"\n  RED_COLOR_COMPONENT_BITFLAG_R = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0001),"
"\n  RED_COLOR_COMPONENT_BITFLAG_G = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0010),"
"\n  RED_COLOR_COMPONENT_BITFLAG_B = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0100),"
"\n  RED_COLOR_COMPONENT_BITFLAG_A = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,1000),"
"\n} RedColorComponentBitflag;"
"\n"
"\ntypedef enum RedBlendFactor {"
"\n  RED_BLEND_FACTOR_ZERO                     = 0,"
"\n  RED_BLEND_FACTOR_ONE                      = 1,"
"\n  RED_BLEND_FACTOR_SOURCE_COLOR             = 2,"
"\n  RED_BLEND_FACTOR_ONE_MINUS_SOURCE_COLOR   = 3,"
"\n  RED_BLEND_FACTOR_TARGET_COLOR             = 4,"
"\n  RED_BLEND_FACTOR_ONE_MINUS_TARGET_COLOR   = 5,"
"\n  RED_BLEND_FACTOR_SOURCE_ALPHA             = 6,"
"\n  RED_BLEND_FACTOR_ONE_MINUS_SOURCE_ALPHA   = 7,"
"\n  RED_BLEND_FACTOR_TARGET_ALPHA             = 8,"
"\n  RED_BLEND_FACTOR_ONE_MINUS_TARGET_ALPHA   = 9,"
"\n  RED_BLEND_FACTOR_CONSTANT_COLOR           = 10,"
"\n  RED_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR = 11,"
"\n  RED_BLEND_FACTOR_SOURCE_ALPHA_SATURATE    = 14,"
"\n  RED_BLEND_FACTOR_SOURCE1_COLOR            = 15, // Depends on RedGpuInfo::supportsProcedureStateOutputColorsBlendDualSource"
"\n  RED_BLEND_FACTOR_ONE_MINUS_SOURCE1_COLOR  = 16, // Depends on RedGpuInfo::supportsProcedureStateOutputColorsBlendDualSource"
"\n  RED_BLEND_FACTOR_SOURCE1_ALPHA            = 17, // Depends on RedGpuInfo::supportsProcedureStateOutputColorsBlendDualSource"
"\n  RED_BLEND_FACTOR_ONE_MINUS_SOURCE1_ALPHA  = 18, // Depends on RedGpuInfo::supportsProcedureStateOutputColorsBlendDualSource"
"\n} RedBlendFactor;"
"\n"
"\ntypedef enum RedBlendOp {"
"\n  RED_BLEND_OP_ADD              = 0,"
"\n  RED_BLEND_OP_SUBTRACT         = 1,"
"\n  RED_BLEND_OP_REVERSE_SUBTRACT = 2,"
"\n  RED_BLEND_OP_MIN              = 3,"
"\n  RED_BLEND_OP_MAX              = 4,"
"\n} RedBlendOp;"
"\n"
"\ntypedef struct RedProcedureState {"
"\n  RedPrimitiveTopology       inputAssemblyTopology;"
"\n  RedBool32                  inputAssemblyPrimitiveRestartEnable;"
"\n  RedBool32                  viewportDynamic;"
"\n  float                      viewportStaticX;"
"\n  float                      viewportStaticY;"
"\n  float                      viewportStaticWidth;"
"\n  float                      viewportStaticHeight;"
"\n  float                      viewportStaticDepthMin;"
"\n  float                      viewportStaticDepthMax;"
"\n  RedBool32                  scissorDynamic;"
"\n  int                        scissorStaticX;"
"\n  int                        scissorStaticY;"
"\n  unsigned                   scissorStaticWidth;"
"\n  unsigned                   scissorStaticHeight;"
"\n  RedBool32                  rasterizationDepthClampEnable;                  // Depends on RedGpuInfo::supportsProcedureStateRasterizationDepthClamp"
"\n  RedBool32                  rasterizationDiscardAllPrimitivesEnable;"
"\n  RedCullMode                rasterizationCullMode;"
"\n  RedFrontFace               rasterizationFrontFace;"
"\n  RedBool32                  rasterizationDepthBiasEnable;"
"\n  RedBool32                  rasterizationDepthBiasDynamic;                  // Depends on RedGpuInfo::supportsProcedureStateRasterizationDepthBiasDynamic"
"\n  float                      rasterizationDepthBiasStaticConstantFactor;"
"\n  float                      rasterizationDepthBiasStaticClamp;              // Depends on RedGpuInfo::supportsProcedureStateRasterizationDepthBiasClamp"
"\n  float                      rasterizationDepthBiasStaticSlopeFactor;"
"\n  RedMultisampleCountBitflag multisampleCount;"
"\n  const unsigned *           multisampleSampleMask;                          // Array of 1"
"\n  RedBool32                  multisampleSampleShadingEnable;                 // Depends on RedGpuInfo::supportsProcedureStateMultisampleSampleShading"
"\n  float                      multisampleSampleShadingMin;                    // Depends on RedGpuInfo::supportsProcedureStateMultisampleSampleShading"
"\n  RedBool32                  multisampleAlphaToCoverageEnable;"
"\n  RedBool32                  multisampleAlphaToOneEnable;                    // Depends on RedGpuInfo::supportsProcedureStateMultisampleAlphaToOne"
"\n  RedBool32                  depthTestEnable;"
"\n  RedBool32                  depthTestDepthWriteEnable;"
"\n  RedCompareOp               depthTestDepthCompareOp;"
"\n  RedBool32                  depthTestBoundsTestEnable;                      // Depends on RedGpuInfo::supportsProcedureStateDepthTestBoundsTest"
"\n  RedBool32                  depthTestBoundsTestDynamic;                     // Depends on RedGpuInfo::supportsProcedureStateDepthTestBoundsTest and RedGpuInfo::supportsProcedureStateDepthTestBoundsTestDynamic"
"\n  float                      depthTestBoundsTestStaticMin;                   // Depends on RedGpuInfo::supportsProcedureStateDepthTestBoundsTest"
"\n  float                      depthTestBoundsTestStaticMax;                   // Depends on RedGpuInfo::supportsProcedureStateDepthTestBoundsTest"
"\n  RedBool32                  stencilTestEnable;"
"\n  RedStencilOp               stencilTestFrontStencilTestFailOp;"
"\n  RedStencilOp               stencilTestFrontStencilTestPassDepthTestPassOp;"
"\n  RedStencilOp               stencilTestFrontStencilTestPassDepthTestFailOp;"
"\n  RedCompareOp               stencilTestFrontCompareOp;"
"\n  RedStencilOp               stencilTestBackStencilTestFailOp;"
"\n  RedStencilOp               stencilTestBackStencilTestPassDepthTestPassOp;"
"\n  RedStencilOp               stencilTestBackStencilTestPassDepthTestFailOp;"
"\n  RedCompareOp               stencilTestBackCompareOp;"
"\n  RedBool32                  stencilTestFrontAndBackDynamicCompareMask;      // Depends on RedGpuInfo::supportsProcedureStateStencilTestFrontAndBackDynamicCompareMask"
"\n  RedBool32                  stencilTestFrontAndBackDynamicWriteMask;        // Depends on RedGpuInfo::supportsProcedureStateStencilTestFrontAndBackDynamicWriteMask"
"\n  RedBool32                  stencilTestFrontAndBackDynamicReference;"
"\n  unsigned                   stencilTestFrontAndBackStaticCompareMask;"
"\n  unsigned                   stencilTestFrontAndBackStaticWriteMask;"
"\n  unsigned                   stencilTestFrontAndBackStaticReference;"
"\n  RedBool32                  blendLogicOpEnable;                             // Depends on RedGpuInfo::supportsProcedureStateBlendLogicOp"
"\n  RedLogicOp                 blendLogicOp;                                   // Depends on RedGpuInfo::supportsProcedureStateBlendLogicOp"
"\n  RedBool32                  blendConstantsDynamic;"
"\n  float                      blendConstantsStatic[4];"
"\n  unsigned                   outputColorsCount;                              // Max: 8"
"\n  RedColorComponentBitflags  outputColorsWriteMask[8];                       // Depends on RedGpuInfo::supportsProcedureStateOutputColorsBlendVaryingPerColor"
"\n  RedBool32                  outputColorsBlendEnable[8];                     // Depends on RedGpuInfo::supportsProcedureStateOutputColorsBlendVaryingPerColor"
"\n  RedBlendFactor             outputColorsBlendColorFactorSource[8];          // Depends on RedGpuInfo::supportsProcedureStateOutputColorsBlendVaryingPerColor"
"\n  RedBlendFactor             outputColorsBlendColorFactorTarget[8];          // Depends on RedGpuInfo::supportsProcedureStateOutputColorsBlendVaryingPerColor"
"\n  RedBlendOp                 outputColorsBlendColorOp[8];                    // Depends on RedGpuInfo::supportsProcedureStateOutputColorsBlendVaryingPerColor"
"\n  RedBlendFactor             outputColorsBlendAlphaFactorSource[8];          // Depends on RedGpuInfo::supportsProcedureStateOutputColorsBlendVaryingPerColor"
"\n  RedBlendFactor             outputColorsBlendAlphaFactorTarget[8];          // Depends on RedGpuInfo::supportsProcedureStateOutputColorsBlendVaryingPerColor"
"\n  RedBlendOp                 outputColorsBlendAlphaOp[8];                    // Depends on RedGpuInfo::supportsProcedureStateOutputColorsBlendVaryingPerColor"
"\n} RedProcedureState;"
"\n"
"\ntypedef enum RedProcedureStateExtension {"
"\n  RED_PROCEDURE_STATE_EXTENSION_UNDEFINED          = 0,"
"\n  RED_PROCEDURE_STATE_EXTENSION_RASTERIZATION_MODE = 1,"
"\n} RedProcedureStateExtension;"
"\n"
"\ntypedef enum RedRasterizationMode {"
"\n  RED_RASTERIZATION_MODE_DEFAULT       = 0,"
"\n  RED_RASTERIZATION_MODE_OVERESTIMATE  = 1, // Depends on RedGpuInfoOptionalInfoRasterizationMode::supportsRasterizationModeOverestimate"
"\n  RED_RASTERIZATION_MODE_UNDERESTIMATE = 2, // Depends on RedGpuInfoOptionalInfoRasterizationMode::supportsRasterizationModeUnderestimate"
"\n} RedRasterizationMode;"
"\n"
"\ntypedef struct RedProcedureStateExtensionIterator {"
"\n  unsigned     extension;"
"\n  const void * next;"
"\n} RedProcedureStateExtensionIterator;"
"\n"
"\ntypedef struct RedProcedureStateExtensionRasterizationMode {"
"\n  RedProcedureStateExtension extension;"
"\n  const void *               next;"
"\n  RedRasterizationMode       rasterizationMode;"
"\n} RedProcedureStateExtensionRasterizationMode;"
"\n"
"\n// redCreateOutput"
"\n"
"\ntypedef struct RedOutputMembers {"
"\n  RedHandleTexture depthStencil;"
"\n  unsigned         colorsCount;  // Max: 8"
"\n  RedHandleTexture colors[8];"
"\n} RedOutputMembers;"
"\n"
"\ntypedef struct RedOutputMembersResolveTargets {"
"\n  RedHandleTexture depthStencil;"
"\n  RedHandleTexture colors[8];"
"\n} RedOutputMembersResolveTargets;"
"\n"
"\n// redCallCopyArrayToArray"
"\n"
"\ntypedef struct RedCopyArrayRange {"
"\n  uint64_t arrayRBytesFirst;"
"\n  uint64_t arrayWBytesFirst;"
"\n  uint64_t bytesCount;"
"\n} RedCopyArrayRange;"
"\n"
"\n// redCallCopyImageToImage"
"\n"
"\ntypedef struct RedCopyImageParts {"
"\n  RedImagePartBitflags allParts;"
"\n  unsigned             level;"
"\n  unsigned             layersFirst; // Set to 0 for RED_IMAGE_DIMENSIONS_3D and RED_IMAGE_DIMENSIONS_3D_WITH_TEXTURE_DIMENSIONS_2D_AND_2D_LAYERED images"
"\n  unsigned             layersCount; // Set to 1 for RED_IMAGE_DIMENSIONS_3D and RED_IMAGE_DIMENSIONS_3D_WITH_TEXTURE_DIMENSIONS_2D_AND_2D_LAYERED images"
"\n} RedCopyImageParts;"
"\n"
"\ntypedef struct RedCopyImageOffset {"
"\n  int texelX;"
"\n  int texelY;"
"\n  int texelZ;"
"\n} RedCopyImageOffset;"
"\n"
"\ntypedef struct RedCopyImageExtent {"
"\n  unsigned texelsCountWidth;"
"\n  unsigned texelsCountHeight; // Set to 1 for RED_IMAGE_DIMENSIONS_1D images"
"\n  unsigned texelsCountDepth;  // Set to 1 for RED_IMAGE_DIMENSIONS_1D, RED_IMAGE_DIMENSIONS_2D and RED_IMAGE_DIMENSIONS_2D_WITH_TEXTURE_DIMENSIONS_CUBE_AND_CUBE_LAYERED images"
"\n} RedCopyImageExtent;"
"\n"
"\ntypedef struct RedCopyImageRange {"
"\n  RedCopyImageParts  imageRParts;"
"\n  RedCopyImageOffset imageROffset;"
"\n  RedCopyImageParts  imageWParts;"
"\n  RedCopyImageOffset imageWOffset;"
"\n  RedCopyImageExtent extent;"
"\n} RedCopyImageRange;"
"\n"
"\n// redCallCopyArrayToImage"
"\n// redCallCopyImageToArray"
"\n"
"\ntypedef struct RedCopyArrayImageRange {"
"\n  uint64_t           arrayBytesFirst;"
"\n  unsigned           arrayTexelsCountToNextRow;"
"\n  unsigned           arrayTexelsCountToNextLayerOr3DDepthSliceDividedByTexelsCountToNextRow;"
"\n  RedCopyImageParts  imageParts;"
"\n  RedCopyImageOffset imageOffset;"
"\n  RedCopyImageExtent imageExtent;"
"\n} RedCopyArrayImageRange;"
"\n"
"\n// Example code for copying 2x2 texels from an array to a 2D color image with redCallCopyArrayToImage:"
"\n//"
"\n// ```"
"\n// RedCopyArrayImageRange range;"
"\n//"
"\n// range.arrayBytesFirst               = 0 * sizeof(texel);"
"\n// range.arrayTexelsCountToNextRow     = 5;"
"\n// range.arrayTexelsCountToNextLayerOr3DDepthSliceDividedByTexelsCountToNextRow = 0;"
"\n//"
"\n// range.imageParts.allParts           = RED_IMAGE_PART_BITFLAG_COLOR;"
"\n// range.imageParts.level              = 0;"
"\n// range.imageParts.layersFirst        = 0;"
"\n// range.imageParts.layersCount        = 1;"
"\n//"
"\n// range.imageOffset.texelX            = 1;"
"\n// range.imageOffset.texelY            = 2;"
"\n// range.imageOffset.texelZ            = 0;"
"\n//"
"\n// range.imageExtent.texelsCountWidth  = 2;"
"\n// range.imageExtent.texelsCountHeight = 2;"
"\n// range.imageExtent.texelsCountDepth  = 1;"
"\n// ```"
"\n//"
"\n// Example diagram for the code above (requires monospaced font):"
"\n//"
"\n//             Array            |        Image"
"\n// -----------------------------+----------------------"
"\n//                              |"
"\n//   arrayTexelsCountToNextRow  |"
"\n//         ______|______        |  [.][.][.][.][.][.]"
"\n//        |             |       |  [.][.][.][.][.][.]"
"\n//        [x][x][.][.][.]       |  [.][x][x][.][.][.]"
"\n//        [x][x][.][.][.]       |  [.][x][x][.][.][.]"
"\n//                              |  [.][.][.][.][.][.]"
"\n//                              |  [.][.][.][.][.][.]"
"\n//                              |"
"\n//                              |"
"\n// -----------------------------+----------------------"
"\n//"
"\n// Example code for array addressing:"
"\n//"
"\n// ```"
"\n// texelsCountToNextRow = range.arrayTexelsCountToNextRow != 0 ? range.arrayTexelsCountToNextRow : range.imageExtent.texelsCountWidth;"
"\n// texelsCountToNextLayerOrSliceDividedByTexelsCountToNextRow = range.arrayTexelsCountToNextLayerOr3DDepthSliceDividedByTexelsCountToNextRow != 0 ? range.arrayTexelsCountToNextLayerOr3DDepthSliceDividedByTexelsCountToNextRow : range.imageExtent.texelsCountHeight;"
"\n//"
"\n// for (unsigned l = 0; l < range.imageParts.layersCount; l += 1) {"
"\n//   for (unsigned z = 0; z < range.imageExtent.texelsCountDepth; z += 1) {"
"\n//     for (unsigned y = 0; y < range.imageExtent.texelsCountHeight; y += 1) {"
"\n//       for (unsigned x = 0; x < range.imageExtent.texelsCountWidth; x += 1) {"
"\n//         unsigned zy = (l + z) * texelsCountToNextLayerOrSliceDividedByTexelsCountToNextRow + y;"
"\n//         uint64_t arrayAddress = range.arrayBytesFirst + (zy * texelsCountToNextRow + x) * sizeof(texel);"
"\n//       }"
"\n//     }"
"\n//   }"
"\n// }"
"\n// ```"
"\n"
"\n// redCallSetProcedure"
"\n// redCallSetProcedureParametersStructs"
"\n// redCallSetProcedureParametersHandles"
"\n"
"\ntypedef enum RedProcedureType {"
"\n  RED_PROCEDURE_TYPE_DRAW    = 0,"
"\n  RED_PROCEDURE_TYPE_COMPUTE = 1,"
"\n} RedProcedureType;"
"\n"
"\n// redCallSetProcedureParametersHandles"
"\n"
"\ntypedef enum RedProcedureParametersHandleType {"
"\n  RED_PROCEDURE_PARAMETERS_HANDLE_TYPE_ARRAY_RO_CONSTANT = 6,"
"\n  RED_PROCEDURE_PARAMETERS_HANDLE_TYPE_ARRAY_RO_RW       = 7,"
"\n} RedProcedureParametersHandleType;"
"\n"
"\ntypedef struct RedProcedureParametersHandleArray {"
"\n  RedHandleArray array;"
"\n  uint64_t       setTo0;"
"\n  uint64_t       setToMaxValue;"
"\n} RedProcedureParametersHandleArray;"
"\n"
"\ntypedef struct RedProcedureParametersHandle {"
"\n  unsigned                                  setTo35;"
"\n  size_t                                    setTo0;"
"\n  uint64_t                                  setTo00;"
"\n  unsigned                                  slot;"
"\n  unsigned                                  setTo000;"
"\n  unsigned                                  setTo1;"
"\n  RedProcedureParametersHandleType          type;"
"\n  size_t                                    setTo0000;"
"\n  const RedProcedureParametersHandleArray * array;"
"\n  size_t                                    setTo00000;"
"\n} RedProcedureParametersHandle;"
"\n"
"\n// redCallSetDynamicStencilCompareMask"
"\n// redCallSetDynamicStencilWriteMask"
"\n// redCallSetDynamicStencilReference"
"\n"
"\ntypedef enum RedStencilFace {"
"\n  RED_STENCIL_FACE_FRONT_AND_BACK = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0011),"
"\n} RedStencilFace;"
"\n"
"\ntypedef void (REDGPU_CALLING_CONVENTION *RedTypeProcedureCallGpuToCpuSignalSignal)            (RedHandleCalls calls, RedHandleGpuToCpuSignal signalGpuToCpuSignal, unsigned setTo8192);"
"\ntypedef void (REDGPU_CALLING_CONVENTION *RedTypeProcedureCallCopyArrayToArray)                (RedHandleCalls calls, RedHandleArray arrayR, RedHandleArray arrayW, unsigned rangesCount, const RedCopyArrayRange * ranges);"
"\ntypedef void (REDGPU_CALLING_CONVENTION *RedTypeProcedureCallCopyImageToImage)                (RedHandleCalls calls, RedHandleImage imageR, unsigned setTo1, RedHandleImage imageW, unsigned setTo01, unsigned rangesCount, const RedCopyImageRange * ranges);"
"\ntypedef void (REDGPU_CALLING_CONVENTION *RedTypeProcedureCallCopyArrayToImage)                (RedHandleCalls calls, RedHandleArray arrayR, RedHandleImage imageW, unsigned setTo1, unsigned rangesCount, const RedCopyArrayImageRange * ranges);"
"\ntypedef void (REDGPU_CALLING_CONVENTION *RedTypeProcedureCallCopyImageToArray)                (RedHandleCalls calls, RedHandleImage imageR, unsigned setTo1, RedHandleArray arrayW, unsigned rangesCount, const RedCopyArrayImageRange * ranges);"
"\ntypedef void (REDGPU_CALLING_CONVENTION *RedTypeProcedureCallProcedure)                       (RedHandleCalls calls, unsigned vertexCount, unsigned instanceCount, unsigned vertexFirst, unsigned instanceFirst);"
"\ntypedef void (REDGPU_CALLING_CONVENTION *RedTypeProcedureCallProcedureIndexed)                (RedHandleCalls calls, unsigned indexCount, unsigned instanceCount, unsigned indexFirst, int vertexBase, unsigned instanceFirst);"
"\ntypedef void (REDGPU_CALLING_CONVENTION *RedTypeProcedureCallProcedureCompute)                (RedHandleCalls calls, unsigned workgroupsCountX, unsigned workgroupsCountY, unsigned workgroupsCountZ);"
"\ntypedef void (REDGPU_CALLING_CONVENTION *RedTypeProcedureCallSetProcedure)                    (RedHandleCalls calls, RedProcedureType procedureType, RedHandleProcedure procedure);"
"\ntypedef void (REDGPU_CALLING_CONVENTION *RedTypeProcedureCallSetProcedureIndices)             (RedHandleCalls calls, RedHandleArray array, uint64_t setTo0, unsigned setTo1);"
"\ntypedef void (REDGPU_CALLING_CONVENTION *RedTypeProcedureCallSetProcedureParametersVariables) (RedHandleCalls calls, RedHandleProcedureParameters procedureParameters, RedVisibleToStageBitflags visibleToStages, unsigned variablesBytesFirst, unsigned dataBytesCount, const void * data);"
"\ntypedef void (REDGPU_CALLING_CONVENTION *RedTypeProcedureCallSetProcedureParametersStructs)   (RedHandleCalls calls, RedProcedureType procedureType, RedHandleProcedureParameters procedureParameters, unsigned procedureParametersDeclarationStructsDeclarationsFirst, unsigned structsCount, const RedHandleStruct * structs, unsigned setTo0, size_t setTo00);"
"\ntypedef void (REDGPU_CALLING_CONVENTION *RedTypeProcedureCallSetProcedureParametersHandles)   (RedHandleCalls calls, RedProcedureType procedureType, RedHandleProcedureParameters procedureParameters, unsigned procedureParametersDeclarationStructsDeclarationsCount, unsigned handlesCount, const RedProcedureParametersHandle * handles); // One redCallSetProcedureParametersHandles call should set all the handles"
"\ntypedef void (REDGPU_CALLING_CONVENTION *RedTypeProcedureCallSetDynamicDepthBias)             (RedHandleCalls calls, float constantFactor, float clamp, float slopeFactor); // Depends on RedGpuInfo::supportsProcedureStateRasterizationDepthBiasClamp"
"\ntypedef void (REDGPU_CALLING_CONVENTION *RedTypeProcedureCallSetDynamicDepthBounds)           (RedHandleCalls calls, float min, float max);                                 // Depends on RedGpuInfo::supportsProcedureStateDepthTestBoundsTest"
"\ntypedef void (REDGPU_CALLING_CONVENTION *RedTypeProcedureCallSetDynamicStencilCompareMask)    (RedHandleCalls calls, RedStencilFace face, unsigned compareMask);"
"\ntypedef void (REDGPU_CALLING_CONVENTION *RedTypeProcedureCallSetDynamicStencilWriteMask)      (RedHandleCalls calls, RedStencilFace face, unsigned writeMask);"
"\ntypedef void (REDGPU_CALLING_CONVENTION *RedTypeProcedureCallSetDynamicStencilReference)      (RedHandleCalls calls, RedStencilFace face, unsigned reference);"
"\ntypedef void (REDGPU_CALLING_CONVENTION *RedTypeProcedureCallSetDynamicBlendConstants)        (RedHandleCalls calls, const float * blendConstants);"
"\ntypedef struct RedTypeProcedureCallSetDynamicViewport *                                        RedTypeProcedureAddressCallSetDynamicViewport;"
"\ntypedef struct RedTypeProcedureCallSetDynamicScissor *                                         RedTypeProcedureAddressCallSetDynamicScissor;"
"\ntypedef struct RedTypeProcedureCallSetStructsMemory *                                          RedTypeProcedureAddressCallSetStructsMemory;"
"\ntypedef struct RedTypeProcedureCallSetProcedureParameters *                                    RedTypeProcedureAddressCallSetProcedureParameters;"
"\ntypedef struct RedTypeProcedureCallSetProcedureOutput *                                        RedTypeProcedureAddressCallSetProcedureOutput;"
"\ntypedef struct RedTypeProcedureCallEndProcedureOutput *                                        RedTypeProcedureAddressCallEndProcedureOutput;"
"\ntypedef struct RedTypeProcedureCallUsageAliasOrderBarrier *                                    RedTypeProcedureAddressCallUsageAliasOrderBarrier;"
"\ntypedef struct RedTypeProcedureCallMark *                                                      RedTypeProcedureAddressCallMark;"
"\ntypedef struct RedTypeProcedureCallMarkSet *                                                   RedTypeProcedureAddressCallMarkSet;"
"\ntypedef struct RedTypeProcedureCallMarkEnd *                                                   RedTypeProcedureAddressCallMarkEnd;"
"\n"
"\ntypedef struct RedCallProceduresAndAddresses {"
"\n  RedTypeProcedureCallGpuToCpuSignalSignal            redCallGpuToCpuSignalSignal;"
"\n  RedTypeProcedureCallCopyArrayToArray                redCallCopyArrayToArray;"
"\n  RedTypeProcedureCallCopyImageToImage                redCallCopyImageToImage;"
"\n  RedTypeProcedureCallCopyArrayToImage                redCallCopyArrayToImage;"
"\n  RedTypeProcedureCallCopyImageToArray                redCallCopyImageToArray;"
"\n  RedTypeProcedureCallProcedure                       redCallProcedure;"
"\n  RedTypeProcedureCallProcedureIndexed                redCallProcedureIndexed;"
"\n  RedTypeProcedureCallProcedureCompute                redCallProcedureCompute;"
"\n  RedTypeProcedureCallSetProcedure                    redCallSetProcedure;"
"\n  RedTypeProcedureCallSetProcedureIndices             redCallSetProcedureIndices;"
"\n  RedTypeProcedureCallSetProcedureParametersVariables redCallSetProcedureParametersVariables;"
"\n  RedTypeProcedureCallSetProcedureParametersStructs   redCallSetProcedureParametersStructs;"
"\n  RedTypeProcedureCallSetProcedureParametersHandles   redCallSetProcedureParametersHandles;"
"\n  RedTypeProcedureCallSetDynamicDepthBias             redCallSetDynamicDepthBias;"
"\n  RedTypeProcedureCallSetDynamicDepthBounds           redCallSetDynamicDepthBounds;"
"\n  RedTypeProcedureCallSetDynamicStencilCompareMask    redCallSetDynamicStencilCompareMask;"
"\n  RedTypeProcedureCallSetDynamicStencilWriteMask      redCallSetDynamicStencilWriteMask;"
"\n  RedTypeProcedureCallSetDynamicStencilReference      redCallSetDynamicStencilReference;"
"\n  RedTypeProcedureCallSetDynamicBlendConstants        redCallSetDynamicBlendConstants;"
"\n  RedTypeProcedureAddressCallSetDynamicViewport       redCallSetDynamicViewport;"
"\n  RedTypeProcedureAddressCallSetDynamicScissor        redCallSetDynamicScissor;"
"\n  RedTypeProcedureAddressCallSetStructsMemory         redCallSetStructsMemory;"
"\n  RedTypeProcedureAddressCallSetProcedureParameters   redCallSetProcedureParameters;"
"\n  RedTypeProcedureAddressCallSetProcedureOutput       redCallSetProcedureOutput;"
"\n  RedTypeProcedureAddressCallEndProcedureOutput       redCallEndProcedureOutput;"
"\n  RedTypeProcedureAddressCallUsageAliasOrderBarrier   redCallUsageAliasOrderBarrier;"
"\n  RedTypeProcedureAddressCallMark                     redCallMark;"
"\n  RedTypeProcedureAddressCallMarkSet                  redCallMarkSet;"
"\n  RedTypeProcedureAddressCallMarkEnd                  redCallMarkEnd;"
"\n} RedCallProceduresAndAddresses;"
"\n"
"\n// redCallSetProcedureOutput"
"\n"
"\ntypedef struct RedInlineOutput {"
"\n  const RedOutputMembers *               outputMembers;"
"\n  const RedOutputMembersResolveTargets * outputMembersResolveTargets;"
"\n} RedInlineOutput;"
"\n"
"\ntypedef struct RedColorsClearValuesFloat {"
"\n  float    r[8];"
"\n  float    g[8];"
"\n  float    b[8];"
"\n  float    a[8];"
"\n} RedColorsClearValuesFloat;"
"\n"
"\ntypedef struct RedColorsClearValuesSint {"
"\n  int      r[8];"
"\n  int      g[8];"
"\n  int      b[8];"
"\n  int      a[8];"
"\n} RedColorsClearValuesSint;"
"\n"
"\ntypedef struct RedColorsClearValuesUint {"
"\n  unsigned r[8];"
"\n  unsigned g[8];"
"\n  unsigned b[8];"
"\n  unsigned a[8];"
"\n} RedColorsClearValuesUint;"
"\n"
"\n// redCallUsageAliasOrderBarrier"
"\n"
"\ntypedef enum RedBarrierSplit {"
"\n  RED_BARRIER_SPLIT_NONE = 0,"
"\n  RED_BARRIER_SPLIT_SET  = 1,"
"\n  RED_BARRIER_SPLIT_END  = 2,"
"\n} RedBarrierSplit;"
"\n"
"\ntypedef unsigned RedAccessStageBitflags;"
"\ntypedef enum RedAccessStageBitflag {"
"\n  RED_ACCESS_STAGE_BITFLAG_COPY                 = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0001),"
"\n  RED_ACCESS_STAGE_BITFLAG_COMPUTE              = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0010),"
"\n  RED_ACCESS_STAGE_BITFLAG_INDEX                = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0100),"
"\n  RED_ACCESS_STAGE_BITFLAG_VERTEX               = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,1000),"
"\n  RED_ACCESS_STAGE_BITFLAG_FRAGMENT             = REDGPU_B32(0000,0000,0000,0000,0000,0000,0001,0000),"
"\n  RED_ACCESS_STAGE_BITFLAG_OUTPUT_DEPTH_STENCIL = REDGPU_B32(0000,0000,0000,0000,0000,0000,0010,0000),"
"\n  RED_ACCESS_STAGE_BITFLAG_OUTPUT_COLOR         = REDGPU_B32(0000,0000,0000,0000,0000,0000,0100,0000),"
"\n  RED_ACCESS_STAGE_BITFLAG_RESOLVE              = REDGPU_B32(0000,0000,0000,0000,0000,0000,1000,0000),"
"\n  RED_ACCESS_STAGE_BITFLAG_CPU                  = REDGPU_B32(0000,0000,0000,0000,0000,0001,0000,0000),"
"\n} RedAccessStageBitflag;"
"\n"
"\ntypedef unsigned RedAccessBitflags;"
"\ntypedef enum RedAccessBitflag {"
"\n  RED_ACCESS_BITFLAG_COPY_R                               = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0001),"
"\n  RED_ACCESS_BITFLAG_COPY_W                               = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0010),"
"\n  RED_ACCESS_BITFLAG_INDEX_R                              = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0100),"
"\n  RED_ACCESS_BITFLAG_STRUCT_ARRAY_RO_CONSTANT_R           = REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,1000),"
"\n  RED_ACCESS_BITFLAG_STRUCT_RESOURCE_NON_FRAGMENT_STAGE_R = REDGPU_B32(0000,0000,0000,0000,0000,0000,0001,0000),"
"\n  RED_ACCESS_BITFLAG_STRUCT_RESOURCE_FRAGMENT_STAGE_R     = REDGPU_B32(0000,0000,0000,0000,0000,0000,0010,0000),"
"\n  RED_ACCESS_BITFLAG_STRUCT_RESOURCE_W                    = REDGPU_B32(0000,0000,0000,0000,0000,0000,0100,0000),"
"\n  RED_ACCESS_BITFLAG_OUTPUT_DEPTH_R                       = REDGPU_B32(0000,0000,0000,0000,0000,0000,1000,0000),"
"\n  RED_ACCESS_BITFLAG_OUTPUT_DEPTH_RW                      = REDGPU_B32(0000,0000,0000,0000,0000,0001,0000,0000),"
"\n  RED_ACCESS_BITFLAG_OUTPUT_STENCIL_R                     = REDGPU_B32(0000,0000,0000,0000,0000,0010,0000,0000),"
"\n  RED_ACCESS_BITFLAG_OUTPUT_STENCIL_RW                    = REDGPU_B32(0000,0000,0000,0000,0000,0100,0000,0000),"
"\n  RED_ACCESS_BITFLAG_OUTPUT_COLOR_W                       = REDGPU_B32(0000,0000,0000,0000,0000,1000,0000,0000),"
"\n  RED_ACCESS_BITFLAG_RESOLVE_SOURCE_R                     = REDGPU_B32(0000,0000,0000,0000,0001,0000,0000,0000),"
"\n  RED_ACCESS_BITFLAG_RESOLVE_TARGET_W                     = REDGPU_B32(0000,0000,0000,0000,0010,0000,0000,0000),"
"\n  RED_ACCESS_BITFLAG_CPU_RW                               = REDGPU_B32(0000,0000,0000,0000,0100,0000,0000,0000),"
"\n} RedAccessBitflag;"
"\n"
"\ntypedef enum RedState {"
"\n  RED_STATE_UNUSABLE = 0,"
"\n  RED_STATE_USABLE   = 1,"
"\n  RED_STATE_PRESENT  = 1000001002, // WSI specific"
"\n} RedState;"
"\n"
"\ntypedef struct RedUsageArray {"
"\n  RedBarrierSplit        barrierSplit;"
"\n  RedAccessStageBitflags oldAccessStages;"
"\n  RedAccessStageBitflags newAccessStages;"
"\n  RedAccessBitflags      oldAccess;"
"\n  RedAccessBitflags      newAccess;"
"\n  unsigned               queueFamilyIndexSource; // Set to max value to ignore"
"\n  unsigned               queueFamilyIndexTarget; // Set to max value to ignore"
"\n  RedHandleArray         array;"
"\n  uint64_t               arrayBytesFirst;"
"\n  uint64_t               arrayBytesCount;"
"\n} RedUsageArray;"
"\n"
"\ntypedef struct RedUsageImage {"
"\n  RedBarrierSplit        barrierSplit;"
"\n  RedAccessStageBitflags oldAccessStages;"
"\n  RedAccessStageBitflags newAccessStages;"
"\n  RedAccessBitflags      oldAccess;"
"\n  RedAccessBitflags      newAccess;"
"\n  RedState               oldState;"
"\n  RedState               newState;"
"\n  unsigned               queueFamilyIndexSource; // Set to max value to ignore"
"\n  unsigned               queueFamilyIndexTarget; // Set to max value to ignore"
"\n  RedHandleImage         image;"
"\n  RedImagePartBitflags   imageAllParts;"
"\n  unsigned               imageLevelsFirst;"
"\n  unsigned               imageLevelsCount;"
"\n  unsigned               imageLayersFirst;"
"\n  unsigned               imageLayersCount;"
"\n} RedUsageImage;"
"\n"
"\ntypedef struct RedAlias {"
"\n  RedBarrierSplit        barrierSplit;"
"\n  uint64_t               oldResourceHandle;"
"\n  uint64_t               newResourceHandle;"
"\n} RedAlias;"
"\n"
"\ntypedef struct RedOrder {"
"\n  RedBarrierSplit        barrierSplit;"
"\n  uint64_t               resourceHandle;"
"\n} RedOrder;"
"\n"
"\n// redQueueSubmit"
"\n"
"\ntypedef struct RedGpuTimeline {"
"\n  unsigned                   setTo4;"
"\n  size_t                     setTo0;"
"\n  unsigned                   waitForAndUnsignalGpuSignalsCount;"
"\n  const RedHandleGpuSignal * waitForAndUnsignalGpuSignals;"
"\n  const unsigned *           setTo65536;                        // Array of waitForAndUnsignalGpuSignalsCount"
"\n  unsigned                   callsCount;"
"\n  const RedHandleCalls *     calls;"
"\n  unsigned                   signalGpuSignalsCount;"
"\n  const RedHandleGpuSignal * signalGpuSignals;"
"\n} RedGpuTimeline;"
"\n"
"\n#ifndef REDGPU_DECLSPEC"
"\n#define REDGPU_DECLSPEC"
"\n#endif"
"\n"
"\n#ifndef REDGPU_API"
"\n#define REDGPU_API"
"\n#endif"
"\n"
"\n// Memory"
"\n"
"\nREDGPU_DECLSPEC void REDGPU_API redMemoryGetBudget                 (RedContext context, RedHandleGpu gpu, RedMemoryBudget * outMemoryBudget, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redMemoryAllocate                  (RedContext context, RedHandleGpu gpu, const char * handleName, uint64_t bytesCount, unsigned memoryTypeIndex, RedHandleArray dedicateToArray, RedHandleImage dedicateToImage, unsigned memoryBitflags, RedHandleMemory * outMemory, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redMemoryAllocateMappable          (RedContext context, RedHandleGpu gpu, const char * handleName, RedBool32 dedicate, RedHandleArray array, uint64_t arrayMemoryBytesCount, unsigned memoryTypeIndex, unsigned memoryBitflags, RedHandleMemory * outMemory, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redMemoryFree                      (RedContext context, RedHandleGpu gpu, RedHandleMemory memory, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redMemorySet                       (RedContext context, RedHandleGpu gpu, unsigned memoryArraysCount, const RedMemoryArray * memoryArrays, unsigned memoryImagesCount, const RedMemoryImage * memoryImages, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redMemoryMap                       (RedContext context, RedHandleGpu gpu, RedHandleMemory mappableMemory, uint64_t mappableMemoryBytesFirst, uint64_t mappableMemoryBytesCount, void ** outVolatilePointer, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redMemoryUnmap                     (RedContext context, RedHandleGpu gpu, RedHandleMemory mappableMemory, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redMemoryNonCoherentFlush          (RedContext context, RedHandleGpu gpu, unsigned mappableMemoryRangesCount, const RedMappableMemoryRange * mappableMemoryRanges, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redMemoryNonCoherentInvalidate     (RedContext context, RedHandleGpu gpu, unsigned mappableMemoryRangesCount, const RedMappableMemoryRange * mappableMemoryRanges, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\n"
"\n// Struct"
"\n"
"\nREDGPU_DECLSPEC void REDGPU_API redStructsMemoryAllocate           (RedContext context, RedHandleGpu gpu, const char * handleName, unsigned maxStructsCount, unsigned maxStructsMembersOfTypeArrayROConstantCount, unsigned maxStructsMembersOfTypeArrayROOrArrayRWCount, unsigned maxStructsMembersOfTypeTextureROCount, unsigned maxStructsMembersOfTypeTextureRWCount, RedHandleStructsMemory * outStructsMemory, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redStructsMemoryAllocateSamplers   (RedContext context, RedHandleGpu gpu, const char * handleName, unsigned maxStructsCount, unsigned maxStructsMembersOfTypeSamplerCount, RedHandleStructsMemory * outStructsMemory, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redStructsMemorySuballocateStructs (RedContext context, RedHandleGpu gpu, const char ** handleNames, RedHandleStructsMemory structsMemory, unsigned structsDeclarationsCount, const RedHandleStructDeclaration * structsDeclarations, RedHandleStruct * outStructs, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redStructsMemoryReset              (RedContext context, RedHandleGpu gpu, RedHandleStructsMemory structsMemory, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redStructsMemoryFree               (RedContext context, RedHandleGpu gpu, RedHandleStructsMemory structsMemory, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redStructsSet                      (RedContext context, RedHandleGpu gpu, unsigned structsMembersCount, const RedStructMember * structsMembers, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\n"
"\n// Create"
"\n"
"\nREDGPU_DECLSPEC void REDGPU_API redCreateContext                   (RedTypeProcedureMalloc malloc, RedTypeProcedureFree free, RedTypeProcedureMallocTagged optionalMallocTagged, RedTypeProcedureFreeTagged optionalFreeTagged, RedTypeProcedureDebugCallback debugCallback, RedSdkVersion sdkVersion, unsigned sdkExtensionsCount, const unsigned * sdkExtensions, const char * optionalProgramName, unsigned optionalProgramVersion, const char * optionalEngineName, unsigned optionalEngineVersion, const void * optionalSettings, RedContext * outContext, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCreateArray                     (RedContext context, RedHandleGpu gpu, const char * handleName, RedArrayType type, uint64_t bytesCount, uint64_t structuredBufferElementBytesCount, RedAccessBitflags initialAccess, unsigned initialQueueFamilyIndex, RedBool32 dedicate, RedArray * outArray, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCreateImage                     (RedContext context, RedHandleGpu gpu, const char * handleName, RedImageDimensions dimensions, RedFormat format, unsigned width, unsigned height, unsigned depth, unsigned levelsCount, unsigned layersCount, RedMultisampleCountBitflag multisampleCount, RedAccessBitflags restrictToAccess, RedAccessBitflags initialAccess, unsigned initialQueueFamilyIndex, RedBool32 dedicate, RedImage * outImage, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCreateSampler                   (RedContext context, RedHandleGpu gpu, const char * handleName, RedSamplerFiltering filteringMag, RedSamplerFiltering filteringMin, RedSamplerFilteringMip filteringMip, RedSamplerBehaviorOutsideTextureCoordinate behaviorOutsideTextureCoordinateU, RedSamplerBehaviorOutsideTextureCoordinate behaviorOutsideTextureCoordinateV, RedSamplerBehaviorOutsideTextureCoordinate behaviorOutsideTextureCoordinateW, float mipLodBias, RedBool32 enableAnisotropy, float maxAnisotropy, RedBool32 enableCompare, RedCompareOp compareOp, float minLod, float maxLod, RedHandleSampler * outSampler, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCreateTexture                   (RedContext context, RedHandleGpu gpu, const char * handleName, RedHandleImage image, RedImagePartBitflags parts, RedTextureDimensions dimensions, RedFormat format, unsigned levelsFirst, unsigned levelsCount, unsigned layersFirst, unsigned layersCount, RedAccessBitflags restrictToAccess, RedHandleTexture * outTexture, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCreateGpuCode                   (RedContext context, RedHandleGpu gpu, const char * handleName, uint64_t irBytesCount, const void * ir, RedHandleGpuCode * outGpuCode, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCreateOutputDeclaration         (RedContext context, RedHandleGpu gpu, const char * handleName, const RedOutputDeclarationMembers * outputDeclarationMembers, const RedOutputDeclarationMembersResolveSources * outputDeclarationMembersResolveSources, RedBool32 dependencyByRegion, RedBool32 dependencyByRegionAllowUsageAliasOrderBarriers, RedHandleOutputDeclaration * outOutputDeclaration, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCreateStructDeclaration         (RedContext context, RedHandleGpu gpu, const char * handleName, unsigned structDeclarationMembersCount, const RedStructDeclarationMember * structDeclarationMembers, unsigned structDeclarationMembersArrayROCount, const RedStructDeclarationMemberArrayRO * structDeclarationMembersArrayRO, RedBool32 procedureParametersHandlesDeclaration, RedHandleStructDeclaration * outStructDeclaration, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCreateProcedureParameters       (RedContext context, RedHandleGpu gpu, const char * handleName, const RedProcedureParametersDeclaration * procedureParametersDeclaration, RedHandleProcedureParameters * outProcedureParameters, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCreateProcedureCache            (RedContext context, RedHandleGpu gpu, const char * handleName, uint64_t fromBlobBytesCount, const void * fromBlob, RedHandleProcedureCache * outProcedureCache, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCreateProcedure                 (RedContext context, RedHandleGpu gpu, const char * handleName, RedHandleProcedureCache procedureCache, RedHandleOutputDeclaration outputDeclaration, RedHandleProcedureParameters procedureParameters, const char * gpuCodeVertexMainProcedureName, RedHandleGpuCode gpuCodeVertex, const char * gpuCodeFragmentMainProcedureName, RedHandleGpuCode gpuCodeFragment, const RedProcedureState * state, const void * stateExtension, RedBool32 deriveBase, RedHandleProcedure deriveFrom, RedHandleProcedure * outProcedure, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCreateProcedureCompute          (RedContext context, RedHandleGpu gpu, const char * handleName, RedHandleProcedureCache procedureCache, RedHandleProcedureParameters procedureParameters, const char * gpuCodeMainProcedureName, RedHandleGpuCode gpuCode, RedHandleProcedure * outProcedure, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCreateOutput                    (RedContext context, RedHandleGpu gpu, const char * handleName, RedHandleOutputDeclaration outputDeclaration, const RedOutputMembers * outputMembers, const RedOutputMembersResolveTargets * outputMembersResolveTargets, unsigned width, unsigned height, RedOutput * outOutput, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCreateCpuSignal                 (RedContext context, RedHandleGpu gpu, const char * handleName, RedBool32 createSignaled, RedHandleCpuSignal * outCpuSignal, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCreateGpuSignal                 (RedContext context, RedHandleGpu gpu, const char * handleName, RedHandleGpuSignal * outGpuSignal, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCreateGpuToCpuSignal            (RedContext context, RedHandleGpu gpu, const char * handleName, RedHandleGpuToCpuSignal * outGpuToCpuSignal, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCreateCalls                     (RedContext context, RedHandleGpu gpu, const char * handleName, unsigned queueFamilyIndex, RedCalls * outCalls, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCreateCallsReusable             (RedContext context, RedHandleGpu gpu, const char * handleName, unsigned queueFamilyIndex, RedCalls * outCalls, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\n"
"\n// Destroy"
"\n"
"\nREDGPU_DECLSPEC void REDGPU_API redDestroyContext                  (RedContext context, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redDestroyArray                    (RedContext context, RedHandleGpu gpu, RedHandleArray array, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redDestroyImage                    (RedContext context, RedHandleGpu gpu, RedHandleImage image, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redDestroySampler                  (RedContext context, RedHandleGpu gpu, RedHandleSampler sampler, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redDestroyTexture                  (RedContext context, RedHandleGpu gpu, RedHandleTexture texture, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redDestroyGpuCode                  (RedContext context, RedHandleGpu gpu, RedHandleGpuCode gpuCode, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redDestroyOutputDeclaration        (RedContext context, RedHandleGpu gpu, RedHandleOutputDeclaration outputDeclaration, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redDestroyStructDeclaration        (RedContext context, RedHandleGpu gpu, RedHandleStructDeclaration structDeclaration, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redDestroyProcedureParameters      (RedContext context, RedHandleGpu gpu, RedHandleProcedureParameters procedureParameters, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redDestroyProcedureCache           (RedContext context, RedHandleGpu gpu, RedHandleProcedureCache procedureCache, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redDestroyProcedure                (RedContext context, RedHandleGpu gpu, RedHandleProcedure procedure, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redDestroyOutput                   (RedContext context, RedHandleGpu gpu, RedHandleOutput output, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redDestroyCpuSignal                (RedContext context, RedHandleGpu gpu, RedHandleCpuSignal cpuSignal, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redDestroyGpuSignal                (RedContext context, RedHandleGpu gpu, RedHandleGpuSignal gpuSignal, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redDestroyGpuToCpuSignal           (RedContext context, RedHandleGpu gpu, RedHandleGpuToCpuSignal gpuToCpuSignal, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redDestroyCalls                    (RedContext context, RedHandleGpu gpu, RedHandleCalls calls, RedHandleCallsMemory callsMemory, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\n"
"\n// Procedure cache"
"\n"
"\nREDGPU_DECLSPEC void REDGPU_API redProcedureCacheGetBlob           (RedContext context, RedHandleGpu gpu, RedHandleProcedureCache procedureCache, uint64_t * outBlobBytesCount, void * outBlob, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redProcedureCacheMergeCaches       (RedContext context, RedHandleGpu gpu, unsigned sourceProcedureCachesCount, const RedHandleProcedureCache * sourceProcedureCaches, RedHandleProcedureCache targetProcedureCache, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\n"
"\n// CPU signal"
"\n"
"\nREDGPU_DECLSPEC void REDGPU_API redCpuSignalGetStatus              (RedContext context, RedHandleGpu gpu, RedHandleCpuSignal cpuSignal, RedStatus * outStatus, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCpuSignalWait                   (RedContext context, RedHandleGpu gpu, unsigned cpuSignalsCount, const RedHandleCpuSignal * cpuSignals, RedBool32 waitAll, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCpuSignalUnsignal               (RedContext context, RedHandleGpu gpu, unsigned cpuSignalsCount, const RedHandleCpuSignal * cpuSignals, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\n"
"\n// GPU to CPU signal"
"\n"
"\nREDGPU_DECLSPEC void REDGPU_API redGpuToCpuSignalGetStatus         (RedContext context, RedHandleGpu gpu, RedHandleGpuToCpuSignal gpuToCpuSignal, RedStatus * outStatus, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redGpuToCpuSignalUnsignal          (RedContext context, RedHandleGpu gpu, RedHandleGpuToCpuSignal gpuToCpuSignal, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\n"
"\n// Calls"
"\n"
"\nREDGPU_DECLSPEC void REDGPU_API redCallsSet                        (RedContext context, RedHandleGpu gpu, RedHandleCalls calls, RedHandleCallsMemory callsMemory, RedBool32 callsReusable, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCallsEnd                        (RedContext context, RedHandleGpu gpu, RedHandleCalls calls, RedHandleCallsMemory callsMemory, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\n"
"\n// Calls recording"
"\n"
"\nREDGPU_DECLSPEC void REDGPU_API redGetCallProceduresAndAddresses   (RedContext context, RedHandleGpu gpu, RedCallProceduresAndAddresses * outCallProceduresAndAddresses, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCallSetDynamicViewport          (RedTypeProcedureAddressCallSetDynamicViewport     address, RedHandleCalls calls, float x, float y, float width, float height, float depthMin, float depthMax);"
"\nREDGPU_DECLSPEC void REDGPU_API redCallSetDynamicScissor           (RedTypeProcedureAddressCallSetDynamicScissor      address, RedHandleCalls calls, int x, int y, unsigned width, unsigned height);"
"\nREDGPU_DECLSPEC void REDGPU_API redCallSetStructsMemory            (RedTypeProcedureAddressCallSetStructsMemory       address, RedHandleCalls calls, RedHandleStructsMemory structsMemory, RedHandleStructsMemory structsMemorySamplers);"
"\nREDGPU_DECLSPEC void REDGPU_API redCallSetProcedureParameters      (RedTypeProcedureAddressCallSetProcedureParameters address, RedHandleCalls calls, RedProcedureType procedureType, RedHandleProcedureParameters procedureParameters);"
"\nREDGPU_DECLSPEC void REDGPU_API redCallSetProcedureOutput          (RedTypeProcedureAddressCallSetProcedureOutput     address, RedHandleCalls calls, RedHandleOutputDeclaration outputDeclaration, RedHandleOutput output, RedInlineOutput * inlineOutput, unsigned outputWidth, unsigned outputHeight, RedBool32 outputDepthStencilEnable, unsigned outputColorsCount, float depthClearValue, unsigned stencilClearValue, const RedColorsClearValuesFloat * colorsClearValuesFloat, const RedColorsClearValuesSint * colorsClearValuesSint, const RedColorsClearValuesUint * colorsClearValuesUint);"
"\nREDGPU_DECLSPEC void REDGPU_API redCallEndProcedureOutput          (RedTypeProcedureAddressCallEndProcedureOutput     address, RedHandleCalls calls);"
"\nREDGPU_DECLSPEC void REDGPU_API redCallUsageAliasOrderBarrier      (RedTypeProcedureAddressCallUsageAliasOrderBarrier address, RedHandleCalls calls, RedContext context, unsigned arrayUsagesCount, const RedUsageArray * arrayUsages, unsigned imageUsagesCount, const RedUsageImage * imageUsages, unsigned aliasesCount, const RedAlias * aliases, unsigned ordersCount, const RedOrder * orders, RedBool32 dependencyByRegion);"
"\nREDGPU_DECLSPEC void REDGPU_API redCallMark                        (RedTypeProcedureAddressCallMark                   address, RedHandleCalls calls, const char * mark);"
"\nREDGPU_DECLSPEC void REDGPU_API redCallMarkSet                     (RedTypeProcedureAddressCallMarkSet                address, RedHandleCalls calls, const char * mark);"
"\nREDGPU_DECLSPEC void REDGPU_API redCallMarkEnd                     (RedTypeProcedureAddressCallMarkEnd                address, RedHandleCalls calls);"
"\n"
"\n// Queue"
"\n"
"\nREDGPU_DECLSPEC void REDGPU_API redQueueSubmit                     (RedContext context, RedHandleGpu gpu, RedHandleQueue queue, unsigned timelinesCount, const RedGpuTimeline * timelines, RedHandleCpuSignal signalCpuSignal, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\n"
"\n// Mark"
"\n"
"\nREDGPU_DECLSPEC void REDGPU_API redMark                            (const char * mark, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redMarkSet                         (const char * mark, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redMarkEnd                         (const char * optionalFile, int optionalLine, void * optionalUserData);"
"\n"
"\n#ifdef __cplusplus"
"\n}"
"\n#endif"
"\n"
"\n// Additional notes:"
"\n// * redQueueSubmit: signaling GPU signal will implicitly flush all GPU write caches and waiting on GPU signal will implicitly invalidate all GPU read caches."
"\n// * redQueueSubmit: for non-coherent and coherent read back arrays, waiting on a CPU signal signaled in redQueueSubmit doesn't guarantee that the GPU will make the writes available to the CPU, redCallUsageAliasOrderBarrier with CPU stage and stage access flags must be issued."
"\n// * redQueueSubmit: passing multiple timelines is needed only when the timelines were created on different threads to amortize the cost of calls recording or the timelines were split to synchronize queues with GPU signals."
"\n// * Procedure parameters all fight for the same parameters memory; redCreateProcedureParameters::procedureParametersDeclaration::variablesBytesCount, redCreateProcedureParameters::procedureParametersDeclaration::structsDeclarations and each handle of redCreateProcedureParameters::procedureParametersDeclaration::handlesDeclaration take up space in parameters memory."
"\n// * For a struct, the first slot can start with any value, but the following slot values must be consecutive."
"\n"
"\n#ifdef __cplusplus"
"\nextern \"C\" {"
"\n#endif"
"\n"
"\ntypedef struct RedTypeHandleArrayTimestamp * RedHandleArrayTimestamp;"
"\n"
"\ntypedef enum RedProcedureId2 {"
"\n  RED_PROCEDURE_ID_redCreateArrayTimestamp  = 77,"
"\n  RED_PROCEDURE_ID_redDestroyArrayTimestamp = 78,"
"\n  RED_PROCEDURE_ID_redArrayTimestampRead    = 79,"
"\n} RedProcedureId2;"
"\n"
"\n// redCreateContext"
"\n"
"\ntypedef enum RedSdkExtension2 {"
"\n  RED_SDK_EXTENSION_ARRAY_TIMESTAMP = 15,"
"\n} RedSdkExtension2;"
"\n"
"\ntypedef enum RedGpuInfoOptionalInfo2 {"
"\n  RED_GPU_INFO_OPTIONAL_INFO_ARRAY_TIMESTAMP = 15,"
"\n} RedGpuInfoOptionalInfo2;"
"\n"
"\ntypedef struct RedGpuInfoOptionalInfoArrayTimestamp {"
"\n  RedGpuInfoOptionalInfo2 optionalInfo;"
"\n  const void *            next;"
"\n  RedBool32               supportsArrayTimestamp;"
"\n  const unsigned *        queuesPrecisionBits64BitTicksCount; // Array of RedGpuInfo::queuesCount, can be NULL if supportsArrayTimestamp == 0"
"\n  float                   nanosecondsPerTick;"
"\n} RedGpuInfoOptionalInfoArrayTimestamp;"
"\n"
"\ntypedef enum RedHandleType1 {"
"\n  RED_HANDLE_TYPE_ARRAY_TIMESTAMP = 12,"
"\n} RedHandleType1;"
"\n"
"\nREDGPU_DECLSPEC void REDGPU_API redCreateArrayTimestamp    (RedContext context, RedHandleGpu gpu, const char * handleName, unsigned count, RedHandleArrayTimestamp * outArrayTimestamp, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redDestroyArrayTimestamp   (RedContext context, RedHandleGpu gpu, RedHandleArrayTimestamp arrayTimestamp, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\nREDGPU_DECLSPEC void REDGPU_API redCallArrayTimestampWrite (RedHandleCalls calls, RedContext context, RedHandleArrayTimestamp arrayTimestamp, unsigned index);"
"\nREDGPU_DECLSPEC void REDGPU_API redArrayTimestampRead      (RedContext context, RedHandleGpu gpu, RedHandleArrayTimestamp arrayTimestamp, unsigned rangeFirst, unsigned rangeCount, void * out64BitTicksCounts, RedStatuses * outStatuses, const char * optionalFile, int optionalLine, void * optionalUserData);"
"\n"
"\n#ifdef __cplusplus"
"\n}"
"\n#endif"
"\n"
          ;

          if (ImGui::Button("Save")) {
            fileWrite("gamescript_redgpu_h.txt", text);
          }
          ImGui::TextUnformatted(text);
        }
        ImGui::End();
      }

      if (g_windowsShowAll == true || (g_windowsHideAll == false && g_windowShowLicenses == true)) {
        if (ImGui::Begin("Licenses", &g_windowShowLicenses, ImGuiWindowFlags_HorizontalScrollbar)) {
          ImGui::SetWindowSize(ImVec2(1010, 560), ImGuiCond_FirstUseEver);

          const char * text =
            "The MIT License (MIT)" "\n"
            "\n"
            "The Ape Programming Language, Copyright (c) 2022 Krzysztof Gabis." "\n"
            "\n"
            "Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the \"Software\"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:" "\n"
            "\n"
            "The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software." "\n"
            "\n"
            "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE." "\n"
            "\n"
            "---" "\n"
            "\n"
            "The MIT License (MIT)" "\n"
            "\n"
            "Dear ImGui, Copyright (c) 2014-2022 Omar Cornut." "\n"
            "\n"
            "Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the \"Software\"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:" "\n"
            "\n"
            "The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software." "\n"
            "\n"
            "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE." "\n"
            "\n"
            "---" "\n"
            "\n"
            "The zlib/libpng License (Zlib)" "\n"
            "\n"
            "sokol_gfx.h, Copyright (c) 2022 Andre Weissflog." "\n"
            "\n"
            "This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software." "\n"
            "\n"
            "Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:" "\n"
            "\n"
            "1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required." "\n"
            "\n"
            "2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software." "\n"
            "\n"
            "3. This notice may not be removed or altered from any source distribution." "\n"
            "\n"
            "---" "\n"
            "\n"
            "The zlib/libpng License (Zlib)" "\n"
            "\n"
            "SoLoud audio engine, Copyright (c) 2013-2022 Jari Komppa." "\n"
            "\n"
            "This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software." "\n"
            "\n"
            "Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:" "\n"
            "\n"
            "1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required." "\n"
            "\n"
            "2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software." "\n"
            "\n"
            "3. This notice may not be removed or altered from any source distribution." "\n"
            "\n"
            "---" "\n"
            "\n"
            "The Apache License, Version 2.0" "\n"
            "\n"
            "REDGPU, Copyright (c) 2019-2021 Constantine Tarasenkov (iamvfx@gmail.com). All rights reserved." "\n"
            "\n"
            "Licensed under the Apache License, Version 2.0 (the \"License\"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0" "\n"
            "\n"
            "Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an \"AS IS\" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License." "\n"
            "\n"
            "---" "\n"
            "\n"
            "The Apache License, Version 2.0" "\n"
            "\n"
            "Droid Sans Mono, Digitized data copyright (c) 2007, Google Corporation. Designed by Steve Matteson of Ascender Corporation." "\n"
            "\n"
            "Licensed under the Apache License, Version 2.0 (the \"License\"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0" "\n"
            "\n"
            "Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an \"AS IS\" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License." "\n"
          ;

          // NOTE(Constantine): "Droid Sans license?" https://github.com/google/fonts/issues/26

          if (ImGui::Button("Save")) {
            fileWrite("gamescript_licenses.txt", text);
          }
          ImGui::TextUnformatted(text);
        }
        ImGui::End();
      }

      if (g_windowsShowAll == true || (g_windowsHideAll == false && g_windowShowListOfFunctions == true)) {
        if (ImGui::Begin("List of Functions (F1)", &g_windowShowListOfFunctions, ImGuiWindowFlags_HorizontalScrollbar)) {
          ImGui::SetWindowSize(ImVec2(1010, 560), ImGuiCond_FirstUseEver);

          const char * text =
"// Game Script REDGPU Version"
"\nfn getGameScriptRedGpuVersionInitDataPointer() -> Number pointer"
"\nfn getGameScriptRedGpuVersionWindowDataPointer() -> Number pointer"
"\n// Game Script"
"\nfn printConsole(String string)"
"\nfn windowSetTitle(String title)"
"\nfn windowGetWidth() -> Number width"
"\nfn windowGetHeight() -> Number height"
"\nfn getCurrentFrame() -> Number frame"
"\nfn setCurrentFrame(Number frame)"
"\nfn getRandomNumber() -> Number number"
"\nfn isLinux() -> Bool isLinux"
"\nfn isWindows() -> Bool isWindows"
"\nfn globalArrayNew8Bit(String label, Number count) -> Number pointer"
"\nfn globalArrayPersistentNew8Bit(String label, Number count) -> Number pointer"
"\nfn globalArrayDelete(String label)"
"\nfn globalArrayPersistentDelete(String label)"
"\nfn globalArrayDeleteAll()"
"\nfn globalArrayPersistentDeleteAll()"
"\nfn globalArrayGetBytesCount(String label) -> Number bytesCount"
"\nfn globalArrayGetPointer(String label) -> Number pointer"
"\nfn globalArrayPersistentGetBytesCount(String label) -> Number bytesCount"
"\nfn globalArrayPersistentGetPointer(String label) -> Number pointer"
"\nfn pointerGetBool(Number pointerTo8BitBools, Number index) -> Bool value"
"\nfn pointerGetString(Number pointer) -> String string"
"\nfn pointerGetSubstring(Number pointer, Number pointerCharsFirst, Number charsCount) -> String string"
"\nfn pointerGetNumber(Number pointerTo32BitFloats, Number index) -> Number value"
"\nfn pointerGetInteger(Number pointerTo32BitInts, Number index) -> Number value"
"\nfn pointerGetUnsignedInteger(Number pointerTo32BitUints, Number index) -> Number value"
"\nfn pointerGetInteger8Bit(Number pointerTo8BitInts, Number index) -> Number value"
"\nfn pointerGetUnsignedInteger8Bit(Number pointerTo8BitUints, Number index) -> Number value"
"\nfn pointerGetAtOffsetNumber(Number pointer, Number bytesFirst) -> Number value"
"\nfn pointerGetAtOffsetInteger(Number pointer, Number bytesFirst) -> Number value"
"\nfn pointerGetAtOffsetUnsignedInteger(Number pointer, Number bytesFirst) -> Number value"
"\nfn pointerGetAtOffsetInteger16Bit(Number pointer, Number bytesFirst) -> Number value"
"\nfn pointerGetAtOffsetUnsignedInteger16Bit(Number pointer, Number bytesFirst) -> Number value"
"\nfn pointerGetAtOffsetNumber64Bit(Number pointer, Number bytesFirst) -> Number value"
"\nfn pointerGetAtOffsetInteger64Bit(Number pointer, Number bytesFirst) -> Number value"
"\nfn pointerGetAtOffsetUnsignedInteger64Bit(Number pointer, Number bytesFirst) -> Number value"
"\nfn pointerSetBool(Number pointerTo8BitBools, Number index, Bool value)"
"\nfn pointerSetString(Number pointer, Number pointerCharsFirst, String string)"
"\nfn pointerSetStringExcludingNullChar(Number pointer, Number pointerCharsFirst, String string)"
"\nfn pointerSetSubstring(Number pointer, Number pointerCharsFirst, String string, Number stringCharsFirst, Number stringCharsCount)"
"\nfn pointerSetNumber(Number pointerTo32BitFloats, Number index, Number value)"
"\nfn pointerSetInteger(Number pointerTo32BitInts, Number index, Number value)"
"\nfn pointerSetUnsignedInteger(Number pointerTo32BitUints, Number index, Number value)"
"\nfn pointerSetInteger8Bit(Number pointerTo8BitInts, Number index, Number value)"
"\nfn pointerSetUnsignedInteger8Bit(Number pointerTo8BitUints, Number index, Number value)"
"\nfn pointerSetAtOffsetNumber(Number pointer, Number bytesFirst, Number value)"
"\nfn pointerSetAtOffsetInteger(Number pointer, Number bytesFirst, Number value)"
"\nfn pointerSetAtOffsetUnsignedInteger(Number pointer, Number bytesFirst, Number value)"
"\nfn pointerSetAtOffsetInteger16Bit(Number pointer, Number bytesFirst, Number value)"
"\nfn pointerSetAtOffsetUnsignedInteger16Bit(Number pointer, Number bytesFirst, Number value)"
"\nfn pointerSetAtOffsetNumber64Bit(Number pointer, Number bytesFirst, Number value)"
"\nfn pointerSetAtOffsetInteger64Bit(Number pointer, Number bytesFirst, Number value)"
"\nfn pointerSetAtOffsetUnsignedInteger64Bit(Number pointer, Number bytesFirst, Number value)"
"\nfn pointerGetRaw8Bit(Number pointer, Number bytesFirst) -> Number raw8BitsAsDouble"
"\nfn pointerGetRaw16Bit(Number pointer, Number bytesFirst) -> Number raw16BitsAsDouble"
"\nfn pointerGetRaw32Bit(Number pointer, Number bytesFirst) -> Number raw32BitsAsDouble"
"\nfn pointerGetRaw64Bit(Number pointer, Number bytesFirst) -> Number raw64BitsAsDouble"
"\nfn pointerSetRaw8Bit(Number pointer, Number bytesFirst, Number raw8BitsAsDouble)"
"\nfn pointerSetRaw16Bit(Number pointer, Number bytesFirst, Number raw16BitsAsDouble)"
"\nfn pointerSetRaw32Bit(Number pointer, Number bytesFirst, Number raw32BitsAsDouble)"
"\nfn pointerSetRaw64Bit(Number pointer, Number bytesFirst, Number raw64BitsAsDouble)"
"\nfn pointerIsNull(Number pointer) -> Bool isNull"
"\nfn pointerGetNull() -> Number nullPointer"
"\nfn pointersAreEqual(Number pointerA, Number pointerB) -> Bool areEqual"
"\nfn pointerOffsetByBytes(Number pointer, Number bytesOffset) -> Number offsettedPointer"
"\nfn globalDynamicArrayNew(String label) -> Number handle"
"\nfn globalDynamicArrayPersistentNew(String label) -> Number handle"
"\nfn globalDynamicArrayDelete(String label)"
"\nfn globalDynamicArrayPersistentDelete(String label)"
"\nfn globalDynamicArrayDeleteAll()"
"\nfn globalDynamicArrayPersistentDeleteAll()"
"\nfn globalDynamicArrayGetHandle(String label) -> Number handle"
"\nfn globalDynamicArrayPersistentGetHandle(String label) -> Number handle"
"\nfn dynamicArrayGet(Number handle, Number index) -> Number value"
"\nfn dynamicArraySet(Number handle, Number index, Number value)"
"\nfn dynamicArrayAppend(Number handle, Number value)"
"\nfn dynamicArrayRemoveAt(Number handle, Number index) -> Bool success"
"\nfn dynamicArrayRemoveLast(Number handle)"
"\nfn dynamicArrayGetSize(Number handle) -> Number size"
"\nfn memset(Number pointer, Number pointerBytesFirst, Number value8Bit, Number bytesCount)"
"\nfn memcpy(Number pointerTarget, Number pointerTargetBytesFirst, Number pointerSource, Number pointerSourceBytesFirst, Number bytesCount)"
"\nfn memcmp(Number pointerA, Number pointerABytesFirst, Number pointerB, Number pointerBBytesFirst, Number bytesCount) -> Bool areEqual"
"\nfn strlenWithNullChar(String string) -> Number length"
"\nfn gamepadIsPresent(Number gamepadId0to15) -> Bool gamepadIsPresent"
"\nfn gamepadGet15Buttons6AxesNumbers(Number gamepadId0to15) -> Number buttonsAndAxes [21] {a, b, x, y, leftBumper, rightBumper, back, start, guide, leftThumb, rightThumb, dpadUp, dpadRight, dpadDown, dpadLeft, axisLeftX, axisLeftY, axisRightX, axisRightY, leftTrigger, rightTrigger}"
"\nfn gamepadUpdateGamecontrollerdbTxt(Number gamepadId0to15, String mappings) -> Bool success"
"\nfn boolToNumber(Bool boolean) -> Number number"
"\nfn boolToString(Bool boolean) -> String string"
"\nfn numberFromRaw8BitInteger(Number raw8BitInteger) -> Number number"
"\nfn numberFromRaw8BitUnsignedInteger(Number raw8BitUnsignedInteger) -> Number number"
"\nfn numberFromRaw16BitInteger(Number raw16BitInteger) -> Number number"
"\nfn numberFromRaw16BitUnsignedInteger(Number raw16BitUnsignedInteger) -> Number number"
"\nfn numberFromRaw32BitInteger(Number raw32BitInteger) -> Number number"
"\nfn numberFromRaw32BitUnsignedInteger(Number raw32BitUnsignedInteger) -> Number number"
"\nfn numberFromRaw32BitFloat(Number raw32BitFloat) -> Number number"
"\nfn numberFromRaw64BitInteger(Number raw64BitInteger) -> Number number"
"\nfn numberFromRaw64BitUnsignedInteger(Number raw64BitUnsignedInteger) -> Number number"
"\nfn numberToBool(Number number) -> Bool boolean"
"\nfn numberToString(Number number) -> String string"
"\nfn numberToBinaryString(Number number) -> String string"
"\nfn numberWholePartToString(Number number) -> String string"
"\nfn stringCharToNumber(String string) -> Number charNumber"
"\nfn stringToNumberArray(String string) -> Number array []"
"\nfn interpretStringToInteger(String string) -> Number integer"
"\nfn interpretStringToFloat(String string) -> Number float"
"\nfn interpretStringToDouble(String string) -> Number double"
"\nfn stringReadFromFile(String filepath) -> String string"
"\nfn stringWriteToFile(String string, String filepath)"
"\nfn stringAppendToFile(String string, String filepath)"
"\nfn binaryGetByteSizeOfFile(String filepath) -> Number bytesCount"
"\nfn binaryReadFromFile(String filepath, Number writeToPointer, Number writeToPointerBytesFirst)"
"\nfn binaryWriteToFile(Number pointer, Number pointerBytesFirst, Number pointerBytesCount, String writeToFilepath)"
"\nfn imguiWindowBegin(String windowName, Number outPointerToWindowIsOpenBool, Number outPointerToWindowIsOpenBoolBytesFirst) -> Bool state"
"\nfn imguiWindowEnd()"
"\nfn imguiButton(String buttonName, Number buttonWidth, Number buttonHeight) -> Bool state"
"\nfn imguiTextMultiline(String textFieldName, String text, Number textFieldWidth, Number textFieldHeight) -> Bool state"
"\nfn imguiInputText(String textFieldName, Number outPointerToString, Number outPointerToStringBytesFirst, Number outPointerToStringBytesCountMax) -> Bool state"
"\nfn imguiInputTextMultiline(String textFieldName, Number outPointerToString, Number outPointerToStringBytesFirst, Number outPointerToStringBytesCountMax, Number textFieldWidth, Number textFieldHeight) -> Bool state"
"\nfn getUniqueNumber() -> Number uniqueNumber"
"\nfn getUint64Max() -> Number uint64Max"
"\nfn getGameScriptString() -> String script"
"\nfn libGameScriptExternalProcedureReload(Bool printErrors)"
"\nfn libGameScriptExternalProcedureCall2(Number parameter1, Number parameter2)"
"\nfn libGameScriptExternalProcedureCall3(Number parameter1, Number parameter2, Number parameter3)"
"\nfn globalKeyPropertyGetKeyLabelsCount() -> Number count"
"\nfn globalKeyPropertyIsKeyLabelExists(String key) -> Bool exists"
"\nfn globalKeyPropertyGetKeyLabelByKeyIndex(Number index) -> String label"
"\nfn globalKeyPropertyGetKeyPropertyLabelsCount(String key) -> Number count"
"\nfn globalKeyPropertyIsKeyPropertyLabelExists(String key, String property) -> Bool exists"
"\nfn globalKeyPropertyGetKeyPropertyLabelByPropertyIndex(String key, Number index) -> String label"
"\nfn globalKeyPropertyRemoveKey(String key)"
"\nfn globalKeyPropertyRemoveAllKeys()"
"\nfn globalKeyPropertyRemoveProperty(String key, String property)"
"\nfn globalKeyPropertyRemoveAllProperties(String key)"
"\nfn globalKeyPropertySetString(String key, String property, String value)"
"\nfn globalKeyPropertySetNumber(String key, String property, Number value)"
"\nfn globalKeyPropertySetBool(String key, String property, Bool value)"
"\nfn globalKeyPropertyGetString(String key, String property) -> String value"
"\nfn globalKeyPropertyGetNumber(String key, String property) -> Number value"
"\nfn globalKeyPropertyGetBool(String key, String property) -> Bool value"
"\nfn getRedStructsCount() -> Number count"
"\nfn getRedStructName(Number index) -> String name"
"\nfn getRedStructMembersCount() -> Number count"
"\nfn getRedStructMemberName(Number index) -> String name"
"\nfn redStructSizeof(String structName) -> Number bytesCount"
"\nfn redStructMemberSizeof(String structName, String structMemberName) -> Number bytesCount"
"\nfn redStructMemberOffsetof(String structName, String structMemberName) -> Number bytesFirst"
"\nfn redStructMemberTypeof(String structName, String structMemberName) -> Number structMemberType"
"\nfn redCreateContext(Bool enableDebugMode) -> Number context"
"\nfn redHandleContextGetProcAddr(Number contextHandle, String procedureName) -> Number address"
"\nfn redMemoryGetBudget(Number context, Number gpuHandle, Number outMemoryBudget, Number outStatuses)"
"\nfn redMemoryAllocate(Number context, Number gpuHandle, String handleName, Number bytesCount, Number memoryTypeIndex, Number dedicateToArray, Number dedicateToImage, Number memoryBitflags, Number outStatuses) -> Number memoryHandle"
"\nfn redMemoryAllocateMappable(Number context, Number gpuHandle, String handleName, Bool dedicate, Number array, Number arrayMemoryBytesCount, Number memoryTypeIndex, Number memoryBitflags, Number outStatuses) -> Number memoryHandle"
"\nfn redMemoryFree(Number context, Number gpuHandle, Number memory)"
"\nfn redMemorySet(Number context, Number gpuHandle, Number memoryArraysCount, Number memoryArrays, Number memoryImagesCount, Number memoryImages, Number outStatuses)"
"\nfn redMemoryMap(Number context, Number gpuHandle, Number mappableMemory, Number mappableMemoryBytesFirst, Number mappableMemoryBytesCount, Number outStatuses) -> Number pointer"
"\nfn redMemoryUnmap(Number context, Number gpuHandle, Number mappableMemory)"
"\nfn redMemoryNonCoherentFlush(Number context, Number gpuHandle, Number mappableMemoryRangesCount, Number mappableMemoryRanges, Number outStatuses)"
"\nfn redMemoryNonCoherentInvalidate(Number context, Number gpuHandle, Number mappableMemoryRangesCount, Number mappableMemoryRanges, Number outStatuses)"
"\nfn redStructsMemoryAllocate(Number context, Number gpuHandle, String handleName, Number maxStructsCount, Number maxStructsMembersOfTypeArrayROConstantCount, Number maxStructsMembersOfTypeArrayROOrArrayRWCount, Number maxStructsMembersOfTypeTextureROCount, Number maxStructsMembersOfTypeTextureRWCount, Number outStatuses) -> Number structsMemoryHandle"
"\nfn redStructsMemoryAllocateSamplers(Number context, Number gpuHandle, String handleName, Number maxStructsCount, Number maxStructsMembersOfTypeSamplerCount, Number outStatuses) -> Number structsMemoryHandle"
"\nfn redStructsMemorySuballocateStructs(Number context, Number gpuHandle, Number handleNames, Number structsMemory, Number structsDeclarationsCount, Number structsDeclarations, Number outStructs, Number outStatuses)"
"\nfn redStructsMemoryReset(Number context, Number gpuHandle, Number structsMemory, Number outStatuses)"
"\nfn redStructsMemoryFree(Number context, Number gpuHandle, Number structsMemory)"
"\nfn redStructsSet(Number context, Number gpuHandle, Number structsMembersCount, Number structsMembers)"
"\nfn redCreateArray(Number context, Number gpuHandle, String handleName, Number type, Number bytesCount, Number structuredBufferElementBytesCount, Number initialAccess, Number initialQueueFamilyIndex, Bool dedicate, Number outArray, Number outStatuses) -> Number arrayHandle"
"\nfn redCreateImage(Number context, Number gpuHandle, String handleName, Number dimensions, Number format, Number width, Number height, Number depth, Number levelsCount, Number layersCount, Number multisampleCount, Number restrictToAccess, Number initialAccess, Number initialQueueFamilyIndex, Bool dedicate, Number outImage, Number outStatuses) -> Number imageHandle"
"\nfn redCreateSampler(Number context, Number gpuHandle, String handleName, Number filteringMag, Number filteringMin, Number filteringMip, Number behaviorOutsideTextureCoordinateU, Number behaviorOutsideTextureCoordinateV, Number behaviorOutsideTextureCoordinateW, Number mipLodBias, Bool enableAnisotropy, Number maxAnisotropy, Bool enableCompare, Number compareOp, Number minLod, Number maxLod, Number outStatuses) -> Number samplerHandle"
"\nfn redCreateTexture(Number context, Number gpuHandle, String handleName, Number image, Number parts, Number dimensions, Number format, Number levelsFirst, Number levelsCount, Number layersFirst, Number layersCount, Number restrictToAccess, Number outStatuses) -> Number textureHandle"
"\nfn redCreateGpuCode(Number context, Number gpuHandle, String handleName, Number irBytesCount, Number ir, Number outStatuses) -> Number gpuCodeHandle"
"\nfn redCreateOutputDeclaration(Number context, Number gpuHandle, String handleName, Number outputDeclarationMembers, Number outputDeclarationMembersResolveSources, Bool dependencyByRegion, Bool dependencyByRegionAllowUsageAliasOrderBarriers, Number outStatuses) -> Number outputDeclarationHandle"
"\nfn redCreateStructDeclaration(Number context, Number gpuHandle, String handleName, Number structDeclarationMembersCount, Number structDeclarationMembers, Number structDeclarationMembersArrayROCount, Number structDeclarationMembersArrayRO, Bool procedureParametersHandlesDeclaration, Number outStatuses) -> Number structDeclarationHandle"
"\nfn redCreateProcedureParameters(Number context, Number gpuHandle, String handleName, Number procedureParametersDeclaration, Number outStatuses) -> Number procedureParametersHandle"
"\nfn redCreateProcedureCache(Number context, Number gpuHandle, String handleName, Number fromBlobBytesCount, Number fromBlob, Number outStatuses) -> Number procedureCacheHandle"
"\nfn redCreateProcedure(Number context, Number gpuHandle, String handleName, Number procedureCache, Number outputDeclaration, Number procedureParameters, String gpuCodeVertexMainProcedureName, Number gpuCodeVertex, String gpuCodeFragmentMainProcedureName, Number gpuCodeFragment, Number state, Number stateExtension, Bool deriveBase, Number deriveFrom, Number outStatuses) -> Number procedureHandle"
"\nfn redCreateProcedureCompute(Number context, Number gpuHandle, String handleName, Number procedureCache, Number procedureParameters, String gpuCodeMainProcedureName, Number gpuCode, Number outStatuses) -> Number procedureHandle"
"\nfn redCreateOutput(Number context, Number gpuHandle, String handleName, Number outputDeclaration, Number outputMembers, Number outputMembersResolveTargets, Number width, Number height, Number outOutput, Number outStatuses) -> Number outputHandle"
"\nfn redCreateCpuSignal(Number context, Number gpuHandle, String handleName, Bool createSignaled, Number outStatuses) -> Number cpuSignalHandle"
"\nfn redCreateGpuSignal(Number context, Number gpuHandle, String handleName, Number outStatuses) -> Number gpuSignalHandle"
"\nfn redCreateGpuToCpuSignal(Number context, Number gpuHandle, String handleName, Number outStatuses) -> Number gpuToCpuHandle"
"\nfn redCreateCalls(Number context, Number gpuHandle, String handleName, Number queueFamilyIndex, Number outCalls, Number outStatuses)"
"\nfn redCreateCallsReusable(Number context, Number gpuHandle, String handleName, Number queueFamilyIndex, Number outCalls, Number outStatuses)"
"\nfn redDestroyContext(Number context)"
"\nfn redDestroyArray(Number context, Number gpuHandle, Number array)"
"\nfn redDestroyImage(Number context, Number gpuHandle, Number image)"
"\nfn redDestroySampler(Number context, Number gpuHandle, Number sampler)"
"\nfn redDestroyTexture(Number context, Number gpuHandle, Number texture)"
"\nfn redDestroyGpuCode(Number context, Number gpuHandle, Number gpuCode)"
"\nfn redDestroyOutputDeclaration(Number context, Number gpuHandle, Number outputDeclaration)"
"\nfn redDestroyStructDeclaration(Number context, Number gpuHandle, Number structDeclaration)"
"\nfn redDestroyProcedureParameters(Number context, Number gpuHandle, Number procedureParameters)"
"\nfn redDestroyProcedureCache(Number context, Number gpuHandle, Number procedureCache)"
"\nfn redDestroyProcedure(Number context, Number gpuHandle, Number procedure)"
"\nfn redDestroyOutput(Number context, Number gpuHandle, Number output)"
"\nfn redDestroyCpuSignal(Number context, Number gpuHandle, Number cpuSignal)"
"\nfn redDestroyGpuSignal(Number context, Number gpuHandle, Number gpuSignal)"
"\nfn redDestroyGpuToCpuSignal(Number context, Number gpuHandle, Number gpuToCpuSignal)"
"\nfn redDestroyCalls(Number context, Number gpuHandle, Number calls, Number callsMemory)"
"\nfn redProcedureCacheGetBlob(Number context, Number gpuHandle, Number procedureCache, Number outBlobBytesCount, Number outBlob, Number outStatuses)"
"\nfn redProcedureCacheMergeCaches(Number context, Number gpuHandle, Number sourceProcedureCachesCount, Number sourceProcedureCaches, Number targetProcedureCache, Number outStatuses)"
"\nfn redCpuSignalGetStatus(Number context, Number gpuHandle, Number cpuSignal) -> Number status"
"\nfn redCpuSignalWait(Number context, Number gpuHandle, Number cpuSignalsCount, Number cpuSignals, Bool waitAll, Number outStatuses)"
"\nfn redCpuSignalUnsignal(Number context, Number gpuHandle, Number cpuSignalsCount, Number cpuSignals, Number outStatuses)"
"\nfn redGpuToCpuSignalGetStatus(Number context, Number gpuHandle, Number gpuToCpuSignal) -> Number status"
"\nfn redGpuToCpuSignalUnsignal(Number context, Number gpuHandle, Number gpuToCpuSignal, Number outStatuses)"
"\nfn redCallsSet(Number context, Number gpuHandle, Number calls, Number callsMemory, Bool callsReusable, Number outStatuses)"
"\nfn redCallsEnd(Number context, Number gpuHandle, Number calls, Number callsMemory, Number outStatuses)"
"\nfn redGetCallProceduresAndAddresses(Number context, Number gpuHandle, Number outCallProceduresAndAddresses, Number outStatuses)"
"\nfn redCallGpuToCpuSignalSignal(Number callProceduresAndAddresses, Number calls, Number signalGpuToCpuSignal, Number setTo8192)"
"\nfn redCallCopyArrayToArray(Number callProceduresAndAddresses, Number calls, Number arrayR, Number arrayW, Number rangesCount, Number ranges)"
"\nfn redCallCopyImageToImage(Number callProceduresAndAddresses, Number calls, Number imageR, Number setTo1, Number imageW, Number setTo01, Number rangesCount, Number ranges)"
"\nfn redCallCopyArrayToImage(Number callProceduresAndAddresses, Number calls, Number arrayR, Number imageW, Number setTo1, Number rangesCount, Number ranges)"
"\nfn redCallCopyImageToArray(Number callProceduresAndAddresses, Number calls, Number imageR, Number setTo1, Number arrayW, Number rangesCount, Number ranges)"
"\nfn redCallProcedure(Number callProceduresAndAddresses, Number calls, Number vertexCount, Number instanceCount, Number vertexFirst, Number instanceFirst)"
"\nfn redCallProcedureIndexed(Number callProceduresAndAddresses, Number calls, Number indexCount, Number instanceCount, Number indexFirst, Number vertexBase, Number instanceFirst)"
"\nfn redCallProcedureCompute(Number callProceduresAndAddresses, Number calls, Number workgroupsCountX, Number workgroupsCountY, Number workgroupsCountZ)"
"\nfn redCallSetProcedure(Number callProceduresAndAddresses, Number calls, Number procedureType, Number procedure)"
"\nfn redCallSetProcedureIndices(Number callProceduresAndAddresses, Number calls, Number array, Number setTo0, Number setTo1)"
"\nfn redCallSetProcedureParametersVariables(Number callProceduresAndAddresses, Number calls, Number procedureParameters, Number visibleToStages, Number variablesBytesFirst, Number dataBytesCount, Number data)"
"\nfn redCallSetProcedureParametersStructs(Number callProceduresAndAddresses, Number calls, Number procedureType, Number procedureParameters, Number procedureParametersDeclarationStructsDeclarationsFirst, Number structsCount, Number structs, Number setTo0, Number setTo00)"
"\nfn redCallSetProcedureParametersHandles(Number callProceduresAndAddresses, Number calls, Number procedureType, Number procedureParameters, Number procedureParametersDeclarationStructsDeclarationsCount, Number handlesCount, Number handles)"
"\nfn redCallSetDynamicDepthBias(Number callProceduresAndAddresses, Number calls, Number constantFactor, Number clamp, Number slopeFactor)"
"\nfn redCallSetDynamicDepthBounds(Number callProceduresAndAddresses, Number calls, Number min, Number max)"
"\nfn redCallSetDynamicStencilCompareMask(Number callProceduresAndAddresses, Number calls, Number face, Number compareMask)"
"\nfn redCallSetDynamicStencilWriteMask(Number callProceduresAndAddresses, Number calls, Number face, Number writeMask)"
"\nfn redCallSetDynamicStencilReference(Number callProceduresAndAddresses, Number calls, Number face, Number reference)"
"\nfn redCallSetDynamicBlendConstants(Number callProceduresAndAddresses, Number calls, Number blendConstants)"
"\nfn redCallSetDynamicViewport(Number callProceduresAndAddresses, Number calls, Number x, Number y, Number width, Number height, Number depthMin, Number depthMax)"
"\nfn redCallSetDynamicScissor(Number callProceduresAndAddresses, Number calls, Number x, Number y, Number width, Number height)"
"\nfn redCallSetStructsMemory(Number callProceduresAndAddresses, Number calls, Number structsMemory, Number structsMemorySamplers)"
"\nfn redCallSetProcedureParameters(Number callProceduresAndAddresses, Number calls, Number procedureType, Number procedureParameters)"
"\nfn redCallSetProcedureOutput(Number callProceduresAndAddresses, Number calls, Number outputDeclaration, Number output, Number inlineOutput, Number outputWidth, Number outputHeight, Bool outputDepthStencilEnable, Number outputColorsCount, Number depthClearValue, Number stencilClearValue, Number colorsClearValuesFloat, Number colorsClearValuesSint, Number colorsClearValuesUint)"
"\nfn redCallEndProcedureOutput(Number callProceduresAndAddresses, Number calls)"
"\nfn redCallUsageAliasOrderBarrier(Number callProceduresAndAddresses, Number calls, Number context, Number arrayUsagesCount, Number arrayUsages, Number imageUsagesCount, Number imageUsages, Number aliasesCount, Number aliases, Number ordersCount, Number orders, Bool dependencyByRegion)"
"\nfn redCallMark(Number callProceduresAndAddresses, Number calls, String mark)"
"\nfn redCallMarkSet(Number callProceduresAndAddresses, Number calls, String mark)"
"\nfn redCallMarkEnd(Number callProceduresAndAddresses, Number calls)"
"\nfn redQueueSubmit(Number context, Number gpuHandle, Number queue, Number timelinesCount, Number timelines, Number signalCpuSignal, Number outStatuses)"
"\nfn redMark(String mark)"
"\nfn redMarkSet(String mark)"
"\nfn redMarkEnd()"
"\nfn redCreateArrayTimestamp(Number context, Number gpuHandle, String handleName, Number count, Number outStatuses) -> Number arrayTimestampHandle"
"\nfn redDestroyArrayTimestamp(Number context, Number gpuHandle, Number arrayTimestamp)"
"\nfn redCallArrayTimestampWrite(Number calls, Number context, Number arrayTimestamp, Number index)"
"\nfn redArrayTimestampRead(Number context, Number gpuHandle, Number arrayTimestamp, Number rangeFirst, Number rangeCount, Number out64BitTicksCounts, Number outStatuses)"
"\n// Game Script for Windows Platform"
"\nfn isWindowsPlatform() -> Bool isWindowsPlatform"
"\nfn setAllWindowsHidden(Bool enable)"
"\nfn getGamepadsCount() -> Number gamepadsCount"
"\nfn getWindowsPlatformInstalledLocationPathString() -> String path"
"\nfn getWindowsPlatformLocalFolderPathString() -> String path"
"\nfn getWindowsPlatformLocalCacheFolderPathString() -> String path"
"\nfn getWindowsPlatformTemporaryFolderPathString() -> String path"
"\nfn getTimeClockNowSinceEpoch100NsecCount() -> Number filetime100NsecCount"
"\nfn getRightGamepadStickAsArrowKeys() -> Bool enabled"
"\nfn setRightGamepadStickAsArrowKeys(Bool enable)"
"\nfn getControlUiWithGamepad() -> Bool enabled"
"\nfn setControlUiWithGamepad(Bool enable)"
"\n// Game Script for Android"
"\nfn printConsoleClear()"
"\nfn isAndroid() -> Bool isAndroid"
"\nfn areAllWindowsHidden() -> Bool areHidden"
"\nfn toggleDefaultViewportClearCommands(Bool enable)"
"\nfn getTimeClockRealTimeSecAndNsec() -> Number values [2] {sec, nsec}"
"\nfn getTimeClockMonotonicSecAndNsec() -> Number values [2] {sec, nsec}"
"\nfn stringDownloadFromUrl(String url) -> String content"
"\nfn deviceGetOrientation() -> Number configurationOrientation // 0 for any, 1 for portrait, 2 for landscape, 3 for square"
"\nfn keyEventsGetUniqueIdCounter() -> Number value"
"\nfn motionEventsGetUniqueIdCounter() -> Number value"
"\nfn keyEventsGetCircularBufferMaxCount() -> Number value"
"\nfn motionEventsGetCircularBufferMaxCount() -> Number value"
"\nfn keyEventsSetCircularBufferMaxCount(Number maxCount)"
"\nfn motionEventsSetCircularBufferMaxCount(Number maxCount)"
"\nfn keyEventsGetEvent(Number keyEventsCircularBufferIndex) -> Number values [11] {uniqueKeyId, deviceId, source, action, flags, keyCode, scanCode, metaState, repeatCount, downTime, eventTime}"
"\nfn motionEventsGetEvent(Number motionEventsCircularBufferIndex) -> Number values [15] {uniqueMotionId, deviceId, source, action, flags, metaState, buttonState, edgeFlags, downTime, eventTime, xOffset, yOffset, xPrecision, yPrecision, pointersCount}"
"\nfn motionEventsGetEventPointer(Number motionEventsCircularBufferIndex, Number pointerIndex) -> Number values [13] {pointerId, toolType, rawX, rawY, x, y, pressure, size, touchMajor, touchMinor, toolMajor, toolMinor, orientation}"
"\nfn imguiSetStyleColor(Number styleColorIndex, Number r, Number g, Number b, Number a)"
"\nfn imguiTextUnformatted(String text)"
"\nfn setGameScriptString(String string)"
"\nfn getCopiedCodeString() -> String code"
"\nfn setCopiedCodeString(String code)"
"\nfn getCodeErrorsString() -> String codeErrors"
"\nfn codeErrorsAppendString(String codeError)"
"\nfn codeErrorsForceShowWindow(Bool forceShow)"
"\nfn stopRunningCodeAfterThisFrame()"
"\nfn getFrame0Cache() -> Bool enabled"
"\nfn setFrame0Cache(Bool enable)"
"\nfn slSoloud_destroy(Number aClassPtr)"
"\nfn slSoloud_create() -> Number value"
"\nfn slSoloud_initEx(Number aClassPtr, Number aFlags, Number aBackend, Number aSamplerate, Number aBufferSize, Number aChannels) -> Number value"
"\nfn slSoloud_deinit(Number aClassPtr)"
"\nfn slSoloud_getVersion(Number aClassPtr) -> Number value"
"\nfn slSoloud_getErrorString(Number aClassPtr, Number aErrorCode) -> String value"
"\nfn slSoloud_getBackendId(Number aClassPtr) -> Number value"
"\nfn slSoloud_getBackendString(Number aClassPtr) -> String value"
"\nfn slSoloud_getBackendChannels(Number aClassPtr) -> Number value"
"\nfn slSoloud_getBackendSamplerate(Number aClassPtr) -> Number value"
"\nfn slSoloud_getBackendBufferSize(Number aClassPtr) -> Number value"
"\nfn slSoloud_setSpeakerPosition(Number aClassPtr, Number aChannel, Number aX, Number aY, Number aZ) -> Number value"
"\nfn slSoloud_getSpeakerPosition(Number aClassPtr, Number aChannel) -> Number values [4] {x, y, z, result}"
"\nfn slSoloud_playEx(Number aClassPtr, Number aSoundClassPtr, Number aVolume, Number aPan, Number aPaused, Number aBus) -> Number value"
"\nfn slSoloud_playClockedEx(Number aClassPtr, Number aSoundTime, Number aSoundClassPtr, Number aVolume, Number aPan, Number aBus) -> Number value"
"\nfn slSoloud_play3dEx(Number aClassPtr, Number aSoundClassPtr, Number aPosX, Number aPosY, Number aPosZ, Number aVelX, Number aVelY, Number aVelZ, Number aVolume, Number aPaused, Number aBus) -> Number value"
"\nfn slSoloud_play3dClockedEx(Number aClassPtr, Number aSoundTime, Number aSoundClassPtr, Number aPosX, Number aPosY, Number aPosZ, Number aVelX, Number aVelY, Number aVelZ, Number aVolume, Number aBus) -> Number value"
"\nfn slSoloud_playBackgroundEx(Number aClassPtr, Number aSoundClassPtr, Number aVolume, Number aPaused, Number aBus) -> Number value"
"\nfn slSoloud_seek(Number aClassPtr, Number aVoiceHandle, Number aSeconds) -> Number value"
"\nfn slSoloud_stop(Number aClassPtr, Number aVoiceHandle)"
"\nfn slSoloud_stopAll(Number aClassPtr)"
"\nfn slSoloud_stopAudioSource(Number aClassPtr, Number aSoundClassPtr)"
"\nfn slSoloud_countAudioSource(Number aClassPtr, Number aSoundClassPtr) -> Number value"
"\nfn slSoloud_setFilterParameter(Number aClassPtr, Number aVoiceHandle, Number aFilterId, Number aAttributeId, Number aValue)"
"\nfn slSoloud_getFilterParameter(Number aClassPtr, Number aVoiceHandle, Number aFilterId, Number aAttributeId) -> Number value"
"\nfn slSoloud_fadeFilterParameter(Number aClassPtr, Number aVoiceHandle, Number aFilterId, Number aAttributeId, Number aTo, Number aTime)"
"\nfn slSoloud_oscillateFilterParameter(Number aClassPtr, Number aVoiceHandle, Number aFilterId, Number aAttributeId, Number aFrom, Number aTo, Number aTime)"
"\nfn slSoloud_getStreamTime(Number aClassPtr, Number aVoiceHandle) -> Number value"
"\nfn slSoloud_getStreamPosition(Number aClassPtr, Number aVoiceHandle) -> Number value"
"\nfn slSoloud_getPause(Number aClassPtr, Number aVoiceHandle) -> Number value"
"\nfn slSoloud_getVolume(Number aClassPtr, Number aVoiceHandle) -> Number value"
"\nfn slSoloud_getOverallVolume(Number aClassPtr, Number aVoiceHandle) -> Number value"
"\nfn slSoloud_getPan(Number aClassPtr, Number aVoiceHandle) -> Number value"
"\nfn slSoloud_getSamplerate(Number aClassPtr, Number aVoiceHandle) -> Number value"
"\nfn slSoloud_getProtectVoice(Number aClassPtr, Number aVoiceHandle) -> Number value"
"\nfn slSoloud_getActiveVoiceCount(Number aClassPtr) -> Number value"
"\nfn slSoloud_getVoiceCount(Number aClassPtr) -> Number value"
"\nfn slSoloud_isValidVoiceHandle(Number aClassPtr, Number aVoiceHandle) -> Number value"
"\nfn slSoloud_getRelativePlaySpeed(Number aClassPtr, Number aVoiceHandle) -> Number value"
"\nfn slSoloud_getPostClipScaler(Number aClassPtr) -> Number value"
"\nfn slSoloud_getMainResampler(Number aClassPtr) -> Number value"
"\nfn slSoloud_getGlobalVolume(Number aClassPtr) -> Number value"
"\nfn slSoloud_getMaxActiveVoiceCount(Number aClassPtr) -> Number value"
"\nfn slSoloud_getLooping(Number aClassPtr, Number aVoiceHandle) -> Number value"
"\nfn slSoloud_getAutoStop(Number aClassPtr, Number aVoiceHandle) -> Number value"
"\nfn slSoloud_getLoopPoint(Number aClassPtr, Number aVoiceHandle) -> Number value"
"\nfn slSoloud_setLoopPoint(Number aClassPtr, Number aVoiceHandle, Number aLoopPoint)"
"\nfn slSoloud_setLooping(Number aClassPtr, Number aVoiceHandle, Number aLooping)"
"\nfn slSoloud_setAutoStop(Number aClassPtr, Number aVoiceHandle, Number aAutoStop)"
"\nfn slSoloud_setMaxActiveVoiceCount(Number aClassPtr, Number aVoiceCount) -> Number value"
"\nfn slSoloud_setInaudibleBehavior(Number aClassPtr, Number aVoiceHandle, Number aMustTick, Number aKill)"
"\nfn slSoloud_setGlobalVolume(Number aClassPtr, Number aVolume)"
"\nfn slSoloud_setPostClipScaler(Number aClassPtr, Number aScaler)"
"\nfn slSoloud_setMainResampler(Number aClassPtr, Number aResampler)"
"\nfn slSoloud_setPause(Number aClassPtr, Number aVoiceHandle, Number aPause)"
"\nfn slSoloud_setPauseAll(Number aClassPtr, Number aPause)"
"\nfn slSoloud_setRelativePlaySpeed(Number aClassPtr, Number aVoiceHandle, Number aSpeed) -> Number value"
"\nfn slSoloud_setProtectVoice(Number aClassPtr, Number aVoiceHandle, Number aProtect)"
"\nfn slSoloud_setSamplerate(Number aClassPtr, Number aVoiceHandle, Number aSamplerate)"
"\nfn slSoloud_setPan(Number aClassPtr, Number aVoiceHandle, Number aPan)"
"\nfn slSoloud_setPanAbsolute(Number aClassPtr, Number aVoiceHandle, Number aLVolume, Number aRVolume)"
"\nfn slSoloud_setChannelVolume(Number aClassPtr, Number aVoiceHandle, Number aChannel, Number aVolume)"
"\nfn slSoloud_setVolume(Number aClassPtr, Number aVoiceHandle, Number aVolume)"
"\nfn slSoloud_setDelaySamples(Number aClassPtr, Number aVoiceHandle, Number aSamples)"
"\nfn slSoloud_fadeVolume(Number aClassPtr, Number aVoiceHandle, Number aTo, Number aTime)"
"\nfn slSoloud_fadePan(Number aClassPtr, Number aVoiceHandle, Number aTo, Number aTime)"
"\nfn slSoloud_fadeRelativePlaySpeed(Number aClassPtr, Number aVoiceHandle, Number aTo, Number aTime)"
"\nfn slSoloud_fadeGlobalVolume(Number aClassPtr, Number aTo, Number aTime)"
"\nfn slSoloud_schedulePause(Number aClassPtr, Number aVoiceHandle, Number aTime)"
"\nfn slSoloud_scheduleStop(Number aClassPtr, Number aVoiceHandle, Number aTime)"
"\nfn slSoloud_oscillateVolume(Number aClassPtr, Number aVoiceHandle, Number aFrom, Number aTo, Number aTime)"
"\nfn slSoloud_oscillatePan(Number aClassPtr, Number aVoiceHandle, Number aFrom, Number aTo, Number aTime)"
"\nfn slSoloud_oscillateRelativePlaySpeed(Number aClassPtr, Number aVoiceHandle, Number aFrom, Number aTo, Number aTime)"
"\nfn slSoloud_oscillateGlobalVolume(Number aClassPtr, Number aFrom, Number aTo, Number aTime)"
"\nfn slSoloud_setGlobalFilter(Number aClassPtr, Number aFilterId, Number aFilterClassPtr)"
"\nfn slSoloud_setVisualizationEnable(Number aClassPtr, Number aEnable)"
"\nfn slSoloud_calcFFT(Number aClassPtr) -> Number values [256]"
"\nfn slSoloud_getWave(Number aClassPtr) -> Number values [256]"
"\nfn slSoloud_getApproximateVolume(Number aClassPtr, Number aChannel) -> Number value"
"\nfn slSoloud_getLoopCount(Number aClassPtr, Number aVoiceHandle) -> Number value"
"\nfn slSoloud_getInfo(Number aClassPtr, Number aVoiceHandle, Number aInfoKey) -> Number value"
"\nfn slSoloud_createVoiceGroup(Number aClassPtr) -> Number value"
"\nfn slSoloud_destroyVoiceGroup(Number aClassPtr, Number aVoiceGroupHandle) -> Number value"
"\nfn slSoloud_addVoiceToGroup(Number aClassPtr, Number aVoiceGroupHandle, Number aVoiceHandle) -> Number value"
"\nfn slSoloud_isVoiceGroup(Number aClassPtr, Number aVoiceGroupHandle) -> Number value"
"\nfn slSoloud_isVoiceGroupEmpty(Number aClassPtr, Number aVoiceGroupHandle) -> Number value"
"\nfn slSoloud_update3dAudio(Number aClassPtr)"
"\nfn slSoloud_set3dSoundSpeed(Number aClassPtr, Number aSpeed) -> Number value"
"\nfn slSoloud_get3dSoundSpeed(Number aClassPtr) -> Number value"
"\nfn slSoloud_set3dListenerParametersEx(Number aClassPtr, Number aPosX, Number aPosY, Number aPosZ, Number aAtX, Number aAtY, Number aAtZ, Number aUpX, Number aUpY, Number aUpZ, Number aVelocityX, Number aVelocityY, Number aVelocityZ)"
"\nfn slSoloud_set3dListenerPosition(Number aClassPtr, Number aPosX, Number aPosY, Number aPosZ)"
"\nfn slSoloud_set3dListenerAt(Number aClassPtr, Number aAtX, Number aAtY, Number aAtZ)"
"\nfn slSoloud_set3dListenerUp(Number aClassPtr, Number aUpX, Number aUpY, Number aUpZ)"
"\nfn slSoloud_set3dListenerVelocity(Number aClassPtr, Number aVelocityX, Number aVelocityY, Number aVelocityZ)"
"\nfn slSoloud_set3dSourceParametersEx(Number aClassPtr, Number aVoiceHandle, Number aPosX, Number aPosY, Number aPosZ, Number aVelocityX, Number aVelocityY, Number aVelocityZ)"
"\nfn slSoloud_set3dSourcePosition(Number aClassPtr, Number aVoiceHandle, Number aPosX, Number aPosY, Number aPosZ)"
"\nfn slSoloud_set3dSourceVelocity(Number aClassPtr, Number aVoiceHandle, Number aVelocityX, Number aVelocityY, Number aVelocityZ)"
"\nfn slSoloud_set3dSourceMinMaxDistance(Number aClassPtr, Number aVoiceHandle, Number aMinDistance, Number aMaxDistance)"
"\nfn slSoloud_set3dSourceAttenuation(Number aClassPtr, Number aVoiceHandle, Number aAttenuationModel, Number aAttenuationRolloffFactor)"
"\nfn slSoloud_set3dSourceDopplerFactor(Number aClassPtr, Number aVoiceHandle, Number aDopplerFactor)"
"\nfn slSoloud_mix(Number aClassPtr, Number aBufferPtr, Number aSamples)"
"\nfn slSoloud_mixSigned16(Number aClassPtr, Number aBufferPtr, Number aSamples)"
"\nfn slBassboostFilter_destroy(Number aClassPtr)"
"\nfn slBassboostFilter_getParamCount(Number aClassPtr) -> Number value"
"\nfn slBassboostFilter_getParamName(Number aClassPtr, Number aParamIndex) -> String value"
"\nfn slBassboostFilter_getParamType(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slBassboostFilter_getParamMax(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slBassboostFilter_getParamMin(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slBassboostFilter_setParams(Number aClassPtr, Number aBoost) -> Number value"
"\nfn slBassboostFilter_create() -> Number value"
"\nfn slBiquadResonantFilter_destroy(Number aClassPtr)"
"\nfn slBiquadResonantFilter_getParamCount(Number aClassPtr) -> Number value"
"\nfn slBiquadResonantFilter_getParamName(Number aClassPtr, Number aParamIndex) -> String value"
"\nfn slBiquadResonantFilter_getParamType(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slBiquadResonantFilter_getParamMax(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slBiquadResonantFilter_getParamMin(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slBiquadResonantFilter_create() -> Number value"
"\nfn slBiquadResonantFilter_setParams(Number aClassPtr, Number aType, Number aFrequency, Number aResonance) -> Number value"
"\nfn slBus_destroy(Number aClassPtr)"
"\nfn slBus_create() -> Number value"
"\nfn slBus_setFilter(Number aClassPtr, Number aFilterId, Number aFilterClassPtr)"
"\nfn slBus_playEx(Number aClassPtr, Number aSoundClassPtr, Number aVolume, Number aPan, Number aPaused) -> Number value"
"\nfn slBus_playClockedEx(Number aClassPtr, Number aSoundTime, Number aSoundClassPtr, Number aVolume, Number aPan) -> Number value"
"\nfn slBus_play3dEx(Number aClassPtr, Number aSoundClassPtr, Number aPosX, Number aPosY, Number aPosZ, Number aVelX, Number aVelY, Number aVelZ, Number aVolume, Number aPaused) -> Number value"
"\nfn slBus_play3dClockedEx(Number aClassPtr, Number aSoundTime, Number aSoundClassPtr, Number aPosX, Number aPosY, Number aPosZ, Number aVelX, Number aVelY, Number aVelZ, Number aVolume) -> Number value"
"\nfn slBus_setChannels(Number aClassPtr, Number aChannels) -> Number value"
"\nfn slBus_setVisualizationEnable(Number aClassPtr, Number aEnable)"
"\nfn slBus_annexSound(Number aClassPtr, Number aVoiceHandle)"
"\nfn slBus_calcFFT(Number aClassPtr) -> Number values [256]"
"\nfn slBus_getWave(Number aClassPtr) -> Number values [256]"
"\nfn slBus_getApproximateVolume(Number aClassPtr, Number aChannel) -> Number value"
"\nfn slBus_getActiveVoiceCount(Number aClassPtr) -> Number value"
"\nfn slBus_getResampler(Number aClassPtr) -> Number value"
"\nfn slBus_setResampler(Number aClassPtr, Number aResampler)"
"\nfn slBus_setVolume(Number aClassPtr, Number aVolume)"
"\nfn slBus_setLooping(Number aClassPtr, Number aLoop)"
"\nfn slBus_setAutoStop(Number aClassPtr, Number aAutoStop)"
"\nfn slBus_set3dMinMaxDistance(Number aClassPtr, Number aMinDistance, Number aMaxDistance)"
"\nfn slBus_set3dAttenuation(Number aClassPtr, Number aAttenuationModel, Number aAttenuationRolloffFactor)"
"\nfn slBus_set3dDopplerFactor(Number aClassPtr, Number aDopplerFactor)"
"\nfn slBus_set3dListenerRelative(Number aClassPtr, Number aListenerRelative)"
"\nfn slBus_set3dDistanceDelay(Number aClassPtr, Number aDistanceDelay)"
"\nfn slBus_set3dColliderEx(Number aClassPtr, Number aColliderClassPtr, Number aUserData)"
"\nfn slBus_set3dAttenuator(Number aClassPtr, Number aAttenuatorClassPtr)"
"\nfn slBus_setInaudibleBehavior(Number aClassPtr, Number aMustTick, Number aKill)"
"\nfn slBus_setLoopPoint(Number aClassPtr, Number aLoopPoint)"
"\nfn slBus_getLoopPoint(Number aClassPtr) -> Number value"
"\nfn slBus_stop(Number aClassPtr)"
"\nfn slDCRemovalFilter_destroy(Number aClassPtr)"
"\nfn slDCRemovalFilter_create() -> Number value"
"\nfn slDCRemovalFilter_setParamsEx(Number aClassPtr, Number aLength) -> Number value"
"\nfn slDCRemovalFilter_getParamCount(Number aClassPtr) -> Number value"
"\nfn slDCRemovalFilter_getParamName(Number aClassPtr, Number aParamIndex) -> String value"
"\nfn slDCRemovalFilter_getParamType(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slDCRemovalFilter_getParamMax(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slDCRemovalFilter_getParamMin(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slEchoFilter_destroy(Number aClassPtr)"
"\nfn slEchoFilter_getParamCount(Number aClassPtr) -> Number value"
"\nfn slEchoFilter_getParamName(Number aClassPtr, Number aParamIndex) -> String value"
"\nfn slEchoFilter_getParamType(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slEchoFilter_getParamMax(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slEchoFilter_getParamMin(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slEchoFilter_create() -> Number value"
"\nfn slEchoFilter_setParamsEx(Number aClassPtr, Number aDelay, Number aDecay, Number aFilter) -> Number value"
"\nfn slFFTFilter_destroy(Number aClassPtr)"
"\nfn slFFTFilter_create() -> Number value"
"\nfn slFFTFilter_getParamCount(Number aClassPtr) -> Number value"
"\nfn slFFTFilter_getParamName(Number aClassPtr, Number aParamIndex) -> String value"
"\nfn slFFTFilter_getParamType(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slFFTFilter_getParamMax(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slFFTFilter_getParamMin(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slFlangerFilter_destroy(Number aClassPtr)"
"\nfn slFlangerFilter_getParamCount(Number aClassPtr) -> Number value"
"\nfn slFlangerFilter_getParamName(Number aClassPtr, Number aParamIndex) -> String value"
"\nfn slFlangerFilter_getParamType(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slFlangerFilter_getParamMax(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slFlangerFilter_getParamMin(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slFlangerFilter_create() -> Number value"
"\nfn slFlangerFilter_setParams(Number aClassPtr, Number aDelay, Number aFreq) -> Number value"
"\nfn slFreeverbFilter_destroy(Number aClassPtr)"
"\nfn slFreeverbFilter_getParamCount(Number aClassPtr) -> Number value"
"\nfn slFreeverbFilter_getParamName(Number aClassPtr, Number aParamIndex) -> String value"
"\nfn slFreeverbFilter_getParamType(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slFreeverbFilter_getParamMax(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slFreeverbFilter_getParamMin(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slFreeverbFilter_create() -> Number value"
"\nfn slFreeverbFilter_setParams(Number aClassPtr, Number aMode, Number aRoomSize, Number aDamp, Number aWidth) -> Number value"
"\nfn slLofiFilter_destroy(Number aClassPtr)"
"\nfn slLofiFilter_getParamCount(Number aClassPtr) -> Number value"
"\nfn slLofiFilter_getParamName(Number aClassPtr, Number aParamIndex) -> String value"
"\nfn slLofiFilter_getParamType(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slLofiFilter_getParamMax(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slLofiFilter_getParamMin(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slLofiFilter_create() -> Number value"
"\nfn slLofiFilter_setParams(Number aClassPtr, Number aSampleRate, Number aBitdepth) -> Number value"
"\nfn slMonotone_destroy(Number aClassPtr)"
"\nfn slMonotone_create() -> Number value"
"\nfn slMonotone_setParamsEx(Number aClassPtr, Number aHardwareChannels, Number aWaveform) -> Number value"
"\nfn slMonotone_load(Number aClassPtr, String aFilename) -> Number value"
"\nfn slMonotone_loadMemEx(Number aClassPtr, Number aMemPtr, Number aLength, Number aCopy, Number aTakeOwnership) -> Number value"
"\nfn slMonotone_setVolume(Number aClassPtr, Number aVolume)"
"\nfn slMonotone_setLooping(Number aClassPtr, Number aLoop)"
"\nfn slMonotone_setAutoStop(Number aClassPtr, Number aAutoStop)"
"\nfn slMonotone_set3dMinMaxDistance(Number aClassPtr, Number aMinDistance, Number aMaxDistance)"
"\nfn slMonotone_set3dAttenuation(Number aClassPtr, Number aAttenuationModel, Number aAttenuationRolloffFactor)"
"\nfn slMonotone_set3dDopplerFactor(Number aClassPtr, Number aDopplerFactor)"
"\nfn slMonotone_set3dListenerRelative(Number aClassPtr, Number aListenerRelative)"
"\nfn slMonotone_set3dDistanceDelay(Number aClassPtr, Number aDistanceDelay)"
"\nfn slMonotone_set3dColliderEx(Number aClassPtr, Number aColliderClassPtr, Number aUserData)"
"\nfn slMonotone_set3dAttenuator(Number aClassPtr, Number aAttenuatorClassPtr)"
"\nfn slMonotone_setInaudibleBehavior(Number aClassPtr, Number aMustTick, Number aKill)"
"\nfn slMonotone_setLoopPoint(Number aClassPtr, Number aLoopPoint)"
"\nfn slMonotone_getLoopPoint(Number aClassPtr) -> Number value"
"\nfn slMonotone_setFilter(Number aClassPtr, Number aFilterId, Number aFilterClassPtr)"
"\nfn slMonotone_stop(Number aClassPtr)"
"\nfn slQueue_destroy(Number aClassPtr)"
"\nfn slQueue_create() -> Number value"
"\nfn slQueue_play(Number aClassPtr, Number aSoundClassPtr) -> Number value"
"\nfn slQueue_getQueueCount(Number aClassPtr) -> Number value"
"\nfn slQueue_isCurrentlyPlaying(Number aClassPtr, Number aSoundClassPtr) -> Number value"
"\nfn slQueue_setParamsFromAudioSource(Number aClassPtr, Number aSoundClassPtr) -> Number value"
"\nfn slQueue_setParamsEx(Number aClassPtr, Number aSamplerate, Number aChannels) -> Number value"
"\nfn slQueue_setVolume(Number aClassPtr, Number aVolume)"
"\nfn slQueue_setLooping(Number aClassPtr, Number aLoop)"
"\nfn slQueue_setAutoStop(Number aClassPtr, Number aAutoStop)"
"\nfn slQueue_set3dMinMaxDistance(Number aClassPtr, Number aMinDistance, Number aMaxDistance)"
"\nfn slQueue_set3dAttenuation(Number aClassPtr, Number aAttenuationModel, Number aAttenuationRolloffFactor)"
"\nfn slQueue_set3dDopplerFactor(Number aClassPtr, Number aDopplerFactor)"
"\nfn slQueue_set3dListenerRelative(Number aClassPtr, Number aListenerRelative)"
"\nfn slQueue_set3dDistanceDelay(Number aClassPtr, Number aDistanceDelay)"
"\nfn slQueue_set3dColliderEx(Number aClassPtr, Number aColliderClassPtr, Number aUserData)"
"\nfn slQueue_set3dAttenuator(Number aClassPtr, Number aAttenuatorClassPtr)"
"\nfn slQueue_setInaudibleBehavior(Number aClassPtr, Number aMustTick, Number aKill)"
"\nfn slQueue_setLoopPoint(Number aClassPtr, Number aLoopPoint)"
"\nfn slQueue_getLoopPoint(Number aClassPtr) -> Number value"
"\nfn slQueue_setFilter(Number aClassPtr, Number aFilterId, Number aFilterClassPtr)"
"\nfn slQueue_stop(Number aClassPtr)"
"\nfn slRobotizeFilter_destroy(Number aClassPtr)"
"\nfn slRobotizeFilter_getParamCount(Number aClassPtr) -> Number value"
"\nfn slRobotizeFilter_getParamName(Number aClassPtr, Number aParamIndex) -> String value"
"\nfn slRobotizeFilter_getParamType(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slRobotizeFilter_getParamMax(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slRobotizeFilter_getParamMin(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slRobotizeFilter_setParams(Number aClassPtr, Number aFreq, Number aWaveform)"
"\nfn slRobotizeFilter_create() -> Number value"
"\nfn slSfxr_destroy(Number aClassPtr)"
"\nfn slSfxr_create() -> Number value"
"\nfn slSfxr_resetParams(Number aClassPtr)"
"\nfn slSfxr_loadParams(Number aClassPtr, String aFilename) -> Number value"
"\nfn slSfxr_loadParamsMemEx(Number aClassPtr, Number aMemPtr, Number aLength, Number aCopy, Number aTakeOwnership) -> Number value"
"\nfn slSfxr_loadPreset(Number aClassPtr, Number aPresetNo, Number aRandSeed) -> Number value"
"\nfn slSfxr_setVolume(Number aClassPtr, Number aVolume)"
"\nfn slSfxr_setLooping(Number aClassPtr, Number aLoop)"
"\nfn slSfxr_setAutoStop(Number aClassPtr, Number aAutoStop)"
"\nfn slSfxr_set3dMinMaxDistance(Number aClassPtr, Number aMinDistance, Number aMaxDistance)"
"\nfn slSfxr_set3dAttenuation(Number aClassPtr, Number aAttenuationModel, Number aAttenuationRolloffFactor)"
"\nfn slSfxr_set3dDopplerFactor(Number aClassPtr, Number aDopplerFactor)"
"\nfn slSfxr_set3dListenerRelative(Number aClassPtr, Number aListenerRelative)"
"\nfn slSfxr_set3dDistanceDelay(Number aClassPtr, Number aDistanceDelay)"
"\nfn slSfxr_set3dColliderEx(Number aClassPtr, Number aColliderClassPtr, Number aUserData)"
"\nfn slSfxr_set3dAttenuator(Number aClassPtr, Number aAttenuatorClassPtr)"
"\nfn slSfxr_setInaudibleBehavior(Number aClassPtr, Number aMustTick, Number aKill)"
"\nfn slSfxr_setLoopPoint(Number aClassPtr, Number aLoopPoint)"
"\nfn slSfxr_getLoopPoint(Number aClassPtr) -> Number value"
"\nfn slSfxr_setFilter(Number aClassPtr, Number aFilterId, Number aFilterClassPtr)"
"\nfn slSfxr_stop(Number aClassPtr)"
"\nfn slSpeech_destroy(Number aClassPtr)"
"\nfn slSpeech_create() -> Number value"
"\nfn slSpeech_setText(Number aClassPtr, String aText) -> Number value"
"\nfn slSpeech_setParamsEx(Number aClassPtr, Number aBaseFrequency, Number aBaseSpeed, Number aBaseDeclination, Number aBaseWaveform) -> Number value"
"\nfn slSpeech_setVolume(Number aClassPtr, Number aVolume)"
"\nfn slSpeech_setLooping(Number aClassPtr, Number aLoop)"
"\nfn slSpeech_setAutoStop(Number aClassPtr, Number aAutoStop)"
"\nfn slSpeech_set3dMinMaxDistance(Number aClassPtr, Number aMinDistance, Number aMaxDistance)"
"\nfn slSpeech_set3dAttenuation(Number aClassPtr, Number aAttenuationModel, Number aAttenuationRolloffFactor)"
"\nfn slSpeech_set3dDopplerFactor(Number aClassPtr, Number aDopplerFactor)"
"\nfn slSpeech_set3dListenerRelative(Number aClassPtr, Number aListenerRelative)"
"\nfn slSpeech_set3dDistanceDelay(Number aClassPtr, Number aDistanceDelay)"
"\nfn slSpeech_set3dColliderEx(Number aClassPtr, Number aColliderClassPtr, Number aUserData)"
"\nfn slSpeech_set3dAttenuator(Number aClassPtr, Number aAttenuatorClassPtr)"
"\nfn slSpeech_setInaudibleBehavior(Number aClassPtr, Number aMustTick, Number aKill)"
"\nfn slSpeech_setLoopPoint(Number aClassPtr, Number aLoopPoint)"
"\nfn slSpeech_getLoopPoint(Number aClassPtr) -> Number value"
"\nfn slSpeech_setFilter(Number aClassPtr, Number aFilterId, Number aFilterClassPtr)"
"\nfn slSpeech_stop(Number aClassPtr)"
"\nfn slWav_destroy(Number aClassPtr)"
"\nfn slWav_create() -> Number value"
"\nfn slWav_load(Number aClassPtr, String aFilename) -> Number value"
"\nfn slWav_loadMemEx(Number aClassPtr, Number aMemPtr, Number aLength, Number aCopy, Number aTakeOwnership) -> Number value"
"\nfn slWav_loadRawWave8Ex(Number aClassPtr, Number aMemPtr, Number aLength, Number aSamplerate, Number aChannels) -> Number value"
"\nfn slWav_loadRawWave16Ex(Number aClassPtr, Number aMemPtr, Number aLength, Number aSamplerate, Number aChannels) -> Number value"
"\nfn slWav_loadRawWaveEx(Number aClassPtr, Number aMemPtr, Number aLength, Number aSamplerate, Number aChannels, Number aCopy, Number aTakeOwnership) -> Number value"
"\nfn slWav_getLength(Number aClassPtr) -> Number value"
"\nfn slWav_setVolume(Number aClassPtr, Number aVolume)"
"\nfn slWav_setLooping(Number aClassPtr, Number aLoop)"
"\nfn slWav_setAutoStop(Number aClassPtr, Number aAutoStop)"
"\nfn slWav_set3dMinMaxDistance(Number aClassPtr, Number aMinDistance, Number aMaxDistance)"
"\nfn slWav_set3dAttenuation(Number aClassPtr, Number aAttenuationModel, Number aAttenuationRolloffFactor)"
"\nfn slWav_set3dDopplerFactor(Number aClassPtr, Number aDopplerFactor)"
"\nfn slWav_set3dListenerRelative(Number aClassPtr, Number aListenerRelative)"
"\nfn slWav_set3dDistanceDelay(Number aClassPtr, Number aDistanceDelay)"
"\nfn slWav_set3dColliderEx(Number aClassPtr, Number aColliderClassPtr, Number aUserData)"
"\nfn slWav_set3dAttenuator(Number aClassPtr, Number aAttenuatorClassPtr)"
"\nfn slWav_setInaudibleBehavior(Number aClassPtr, Number aMustTick, Number aKill)"
"\nfn slWav_setLoopPoint(Number aClassPtr, Number aLoopPoint)"
"\nfn slWav_getLoopPoint(Number aClassPtr) -> Number value"
"\nfn slWav_setFilter(Number aClassPtr, Number aFilterId, Number aFilterClassPtr)"
"\nfn slWav_stop(Number aClassPtr)"
"\nfn slWaveShaperFilter_destroy(Number aClassPtr)"
"\nfn slWaveShaperFilter_setParams(Number aClassPtr, Number aAmount) -> Number value"
"\nfn slWaveShaperFilter_create() -> Number value"
"\nfn slWaveShaperFilter_getParamCount(Number aClassPtr) -> Number value"
"\nfn slWaveShaperFilter_getParamName(Number aClassPtr, Number aParamIndex) -> String value"
"\nfn slWaveShaperFilter_getParamType(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slWaveShaperFilter_getParamMax(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slWaveShaperFilter_getParamMin(Number aClassPtr, Number aParamIndex) -> Number value"
"\nfn slWavStream_destroy(Number aClassPtr)"
"\nfn slWavStream_create() -> Number value"
"\nfn slWavStream_load(Number aClassPtr, String aFilename) -> Number value"
"\nfn slWavStream_loadMemEx(Number aClassPtr, Number aDataPtr, Number aDataLen, Number aCopy, Number aTakeOwnership) -> Number value"
"\nfn slWavStream_loadToMem(Number aClassPtr, String aFilename) -> Number value"
"\nfn slWavStream_getLength(Number aClassPtr) -> Number value"
"\nfn slWavStream_setVolume(Number aClassPtr, Number aVolume)"
"\nfn slWavStream_setLooping(Number aClassPtr, Number aLoop)"
"\nfn slWavStream_setAutoStop(Number aClassPtr, Number aAutoStop)"
"\nfn slWavStream_set3dMinMaxDistance(Number aClassPtr, Number aMinDistance, Number aMaxDistance)"
"\nfn slWavStream_set3dAttenuation(Number aClassPtr, Number aAttenuationModel, Number aAttenuationRolloffFactor)"
"\nfn slWavStream_set3dDopplerFactor(Number aClassPtr, Number aDopplerFactor)"
"\nfn slWavStream_set3dListenerRelative(Number aClassPtr, Number aListenerRelative)"
"\nfn slWavStream_set3dDistanceDelay(Number aClassPtr, Number aDistanceDelay)"
"\nfn slWavStream_set3dColliderEx(Number aClassPtr, Number aColliderClassPtr, Number aUserData)"
"\nfn slWavStream_set3dAttenuator(Number aClassPtr, Number aAttenuatorClassPtr)"
"\nfn slWavStream_setInaudibleBehavior(Number aClassPtr, Number aMustTick, Number aKill)"
"\nfn slWavStream_setLoopPoint(Number aClassPtr, Number aLoopPoint)"
"\nfn slWavStream_getLoopPoint(Number aClassPtr) -> Number value"
"\nfn slWavStream_setFilter(Number aClassPtr, Number aFilterId, Number aFilterClassPtr)"
"\nfn slWavStream_stop(Number aClassPtr)"
"\n"
          ;

          if (ImGui::Button("Save")) {
            fileWrite("gamescript_list_of_functions.txt", text);
          }

          ImGui::SameLine();

          static std::string g_ListOfFunctionsTextFiltered = text;

          static char g_ListOfFunctionsSearchFunctionName[256] = {};
          if (ImGui::InputText("Search function name", g_ListOfFunctionsSearchFunctionName, 255, 0, 0, 0)) {
            g_ListOfFunctionsTextFiltered = text;
            if (g_ListOfFunctionsSearchFunctionName[0] != 0) {
              FilterTextForLineMatches(g_ListOfFunctionsTextFiltered, std::string("fn ") + std::string(g_ListOfFunctionsSearchFunctionName));
            }
          }

          ImGui::TextUnformatted(g_ListOfFunctionsTextFiltered.c_str());
        }
        ImGui::End();
      }

      if (g_windowsShowAll == true || (g_windowsHideAll == false && g_windowShowKeyboardOptions == true)) {
        if (ImGui::Begin("Keyboard Options", &g_windowShowKeyboardOptions, ImGuiWindowFlags_HorizontalScrollbar)) {
          ImGui::Checkbox("Enable on-screen keyboard", &g_enableOnScreenKeyboard);
          ImGui::Checkbox("Enable double newline workaround", &g_enableDoubleNewlineWorkaround);
          ImGui::Text("Notes:");
          ImGui::Text("* You may need to disable your keyboard settings -> 'English prediction' option that can prevent any typing.");
          ImGui::Text("* To have Shift key working in scrcpy program, run it with --prefer-text flag.");
        }
        ImGui::End();
      }
    }

    // NOTE(Constantine): If force show code errors is set to true, show it even in game mode, that's why it's here.
    if (g_windowForceShowCodeErrors == true || g_windowsShowAll == true || (g_windowsHideAll == false && g_windowShowCodeErrors == true)) {
      if (ImGui::Begin("Code Errors", &g_windowShowCodeErrors, ImGuiWindowFlags_HorizontalScrollbar)) {
        ImGui::SetWindowSize(ImVec2(875, 700), ImGuiCond_FirstUseEver);

        if (ImGui::Button("Clear")) {
          g_codeErrorsString.clear();
        }
        ImGui::SameLine();
        if (ImGui::Button("Save")) {
          fileWrite("gamescript_code_errors.txt", g_codeErrorsString.c_str());
        }
        if (g_codeErrorsString.empty() == false) {
          ImGui::TextUnformatted(g_codeErrorsString.c_str());
        }
      }
      ImGui::End();
    }

    if (g_runScriptOnce == true) {
      scriptTick();
      g_runScriptOnce = false;
    } else if (g_runScript == true) {
      scriptTick();
    }
    if (g_codeRunMode == 1 && g_codeErrorsString.empty() == false) {
      g_windowForceShowCodeErrors = true;
    }
}

void KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
    g_windowShowListOfFunctions = g_windowShowListOfFunctions == 0 ? 1 : 0;
  }
  if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
    static bool g_KeyCallbackF11 = true;
    static int  g_KeyCallbackF11PreviousWindowX;
    static int  g_KeyCallbackF11PreviousWindowY;
    static int  g_KeyCallbackF11PreviousWindowWidth;
    static int  g_KeyCallbackF11PreviousWindowHeight;
    if (g_KeyCallbackF11 == true) {
      glfwGetWindowPos(window, &g_KeyCallbackF11PreviousWindowX, &g_KeyCallbackF11PreviousWindowY);
      glfwGetWindowSize(window, &g_KeyCallbackF11PreviousWindowWidth, &g_KeyCallbackF11PreviousWindowHeight);
    }
    if (g_KeyCallbackF11 == true) {
      const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
      glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
    } else {
      glfwSetWindowMonitor(window, NULL, g_KeyCallbackF11PreviousWindowX, g_KeyCallbackF11PreviousWindowY, g_KeyCallbackF11PreviousWindowWidth, g_KeyCallbackF11PreviousWindowHeight, GLFW_DONT_CARE);
    }
    g_KeyCallbackF11 = g_KeyCallbackF11 == true ? false : true;
  }
}

int main(int, char**)
{
    // Setup GLFW window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    g_Window = glfwCreateWindow(1280, 720, "Game Script REDGPU Version", NULL, NULL);
    glfwSetKeyCallback(g_Window, KeyCallback);

    SetupRedGpu();

    // Create Window Surface
    RedHandleSurface surface;
#ifdef _WIN32
    redCreateSurfaceWin32(g_Instance, g_Device, NULL, GetModuleHandle(NULL), glfwGetWin32Window(g_Window), &surface, NULL, __FILE__, __LINE__, NULL);
#else
    redCreateSurfaceXlibOrXcb(g_Instance, g_Device, NULL, glfwGetX11Display(), glfwGetX11Window(g_Window), NULL, 0, &surface, NULL, __FILE__, __LINE__, NULL);
#endif

    // Create Framebuffers
    int w, h;
    glfwGetFramebufferSize(g_Window, &w, &h);
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
    ImGui_ImplGlfw_InitForVulkan(g_Window, true);
    g_RedGpuInitInfo.Instance = g_Instance;
    g_RedGpuInitInfo.PhysicalDevice = g_PhysicalDevice;
    g_RedGpuInitInfo.Device = g_Device;
    g_RedGpuInitInfo.QueueFamily = g_QueueFamily;
    g_RedGpuInitInfo.PipelineCache = g_PipelineCache;
    g_RedGpuInitInfo.DescriptorPool = g_DescriptorPool;
    g_RedGpuInitInfo.DescriptorPoolSamplers = g_DescriptorPoolSamplers;
    g_RedGpuInitInfo.Subpass = 0;
    g_RedGpuInitInfo.MinImageCount = g_MinImageCount;
    g_RedGpuInitInfo.ImageCount = wd->ImageCount;
    g_RedGpuInitInfo.MSAASamples = RED_MULTISAMPLE_COUNT_BITFLAG_1;
    ImGui_ImplRedGpu_Init(&g_RedGpuInitInfo, wd->RenderPass);

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

    {
      size_t fontDataBytesCount = gsDroidSansMonoFontGetBytesCount();
      char * fontData = new(std::nothrow) char[fontDataBytesCount];
      if (fontData != 0) {
        memcpy(fontData, gGsDroidSansMonoFont, fontDataBytesCount);
        ImFont * imfont = io.Fonts->AddFontFromMemoryTTF(fontData, fontDataBytesCount, 22.0f);
        // delete[] fontData; // NOTE(Constantine): Commented out intentionally, "ownership of font_data is transfered by Dear ImGui by default".
      }
    }

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

    {
      srand(time(NULL));
      std::string run           = fileRead("gamescript_run.txt");
      std::string compileAndRun = fileRead("gamescript_compile_and_run.txt");
      if (run.empty() == false) {
        g_codeRunMode    = 1;
        g_codeString     = run;
        g_windowsHideAll = true;
        g_runScript      = true;
        g_compileMode    = false;
      } else if (compileAndRun.empty() == false) {
        g_codeRunMode    = 1;
        g_codeString     = compileAndRun;
        g_windowsHideAll = true;
        g_runScript      = true;
        g_compileMode    = true;
        scriptCompileProgram();
      } else {
        gsAutosaveLoad();
      }
    }

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(g_Window))
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
            glfwGetFramebufferSize(g_Window, &width, &height);
            if (width > 0 && height > 0)
            {
                ImGui_ImplRedGpu_SetMinImageCount(g_MinImageCount, wd);
                ImGui_ImplRedGpuH_CreateOrResizeWindow(g_Instance, g_DeviceIndex, g_PhysicalDevice, g_Device, g_Queue, &g_MainWindowData, g_QueueFamily, width, height, g_MinImageCount);
                g_MainWindowData.FrameIndex = 0;
                g_SwapChainRebuild = false;
            }
        }

        // Start the Dear ImGui frame
        ImGui_ImplRedGpu_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        tick();

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

    if (g_codeRunMode != 1) {
      gsAutosaveSave();
    }

    ImGui_ImplRedGpu_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    CleanupRedGpuWindow();
    CleanupRedGpu();

    glfwDestroyWindow(g_Window);
    glfwTerminate();

    return 0;
}

void FilterTextForLineMatches(std::string & text, std::string lineMatch) {
  std::string out;

  std::stringstream ss;
  ss << text;
  for (std::string line; std::getline(ss, line, '\n');) {
    if (line.rfind(lineMatch, 0) == 0) {
      out += line;
      out += "\n";
    }
  }

  text = out;
}

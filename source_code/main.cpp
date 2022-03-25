#if defined(GAME_SCRIPT_MIN)
#define MINSL_IMPLEMENTATION
#endif
#include "gamescript.h"

#if defined(GAME_SCRIPT_NATIVE)
#ifdef _WIN32
#pragma comment(lib, "C:/Users/Constantine/Desktop/game_script_source_code/gamescript_library_procedures.dll.lib")
#endif
#include "gamescript_library_procedures.h"
#endif // #if defined(GAME_SCRIPT_NATIVE)

#if defined(GAME_SCRIPT_C)
#ifdef _WIN32
#pragma comment(lib, "C:/Users/Constantine/Desktop/game_script_source_code/libtcc.lib")
#endif
#endif // #if defined(GAME_SCRIPT_C)

#if defined(_WIN32) && defined(GAME_SCRIPT_NATIVE)
#else
#define LZ4X_C // Include C implementation
#define ULZ_C  // Include C implementation
#endif
#if defined(_WIN32) && !defined(__MINGW32__)
#include "C:/github/r-lyeh/stdpack.c/src/lz4x.c"
#include "C:/github/r-lyeh/stdpack.c/src/ulz.c"
#endif
#if defined(__linux__) || defined(__MINGW32__)
#include "dependencies/r-lyeh/stdpack.c/src/lz4x.c"
#include "dependencies/r-lyeh/stdpack.c/src/ulz.c"
#endif

#ifdef GAME_SCRIPT
// NOTE(Constantine):
// Include gamescript.cpp directly in main.cpp with static keyword added to all Game Script procedures to make the final binary size smaller.
#define GS_API static
#include "gamescript.cpp"
#endif

#if defined(GAME_SCRIPT_NATIVE)
#define GAME_SCRIPT_WINDOW_TITLE "Game Script Native from Feb 27, 2022 (github.com/procedural/gamescript)"
#elif defined(GAME_SCRIPT_MIN)
#define GAME_SCRIPT_WINDOW_TITLE "Game Script Min from Feb 27, 2022 (github.com/procedural/gamescript)"
#elif defined(GAME_SCRIPT_C)
#define GAME_SCRIPT_WINDOW_TITLE "Game Script C from Feb 27, 2022 (github.com/procedural/gamescript)"
#else
#define GAME_SCRIPT_WINDOW_TITLE "Game Script from Feb 27, 2022 (github.com/procedural/gamescript)"
#endif

#if defined(_WIN32) && defined(GAME_SCRIPT_NATIVE)
#define GSN_WIN_EXPORT __declspec(dllexport)
#else
#define GSN_WIN_EXPORT
#endif

GSN_WIN_EXPORT float                                                    gImguiFontGlobalScale                                   = 1.8f;
GSN_WIN_EXPORT int                                                      gReadScriptFromDataGameDotScript                        = 0;
GSN_WIN_EXPORT int                                                      gDisableDefaultFkeys                                    = 0;
GSN_WIN_EXPORT int                                                      gFullscreenExclusive                                    = 0;
GSN_WIN_EXPORT int                                                      gFullscreenF11Override                                  = 0;
GSN_WIN_EXPORT int                                                      gFullscreenF11OverrideOnce                              = 0;
GSN_WIN_EXPORT int                                                      gFullscreen                                             = 0;
GSN_WIN_EXPORT int                                                      gF1WindowIsShownFromNowOn                               = 0;
GSN_WIN_EXPORT volatile uint64_t                                        gStopScript                                             = 0;
GSN_WIN_EXPORT int                                                      gRunScriptOnce                                          = 0;
GSN_WIN_EXPORT int                                                      gRerun                                                  = 0;
GSN_WIN_EXPORT volatile uint64_t                                        gCurrentFrame                                           = 0;
GSN_WIN_EXPORT volatile uint64_t                                        gCurrentFrameThread2                                    = 0;
GSN_WIN_EXPORT RedFHandleImgui *                                        gGuiImgui                                               = 0;
GSN_WIN_EXPORT int                                                      gPreviousGameMode                                       = 0;
GSN_WIN_EXPORT int                                                      gGameMode                                               = 0;
GSN_WIN_EXPORT int                                                      gPreviousDefaultCameraEnabled                           = 0;
GSN_WIN_EXPORT int                                                      gDefaultCameraEnabled                                   = 0;
GSN_WIN_EXPORT int                                                      gDefaultCameraForceEnabled                              = 0;
GSN_WIN_EXPORT RedFHandleFirstPersonCamera *                            gCamera                                                 = 0;
GSN_WIN_EXPORT ape_t *                                                  gApe                                                    = 0;
GSN_WIN_EXPORT ape_t *                                                  gApeThread2                                             = 0;
GSN_WIN_EXPORT char *                                                   gApeCodeCharsCurrentlyRunning                           = 0;
GSN_WIN_EXPORT char *                                                   gApeCodeCharsCurrentlyRunningThread2                    = 0;
GSN_WIN_EXPORT int                                                      gApeErrorCheck                                          = 1;
GSN_WIN_EXPORT int                                                      gApeErrorCheckThread2                                   = 1;
GSN_WIN_EXPORT int                                                      gF2Toggle                                               = 1;
GSN_WIN_EXPORT int                                                      gGameScriptNativeRecompileSignal                        = 0;
GSN_WIN_EXPORT int                                                      gGameScriptNativeRecompileSignalThread2                 = 0;
GSN_WIN_EXPORT std::string                                              gApeCodeCharsNextRunning;
GSN_WIN_EXPORT std::string                                              gApeCodeCharsNextRunningThread2;
GSN_WIN_EXPORT std::string                                              gApeCodeChars;
GSN_WIN_EXPORT std::string                                              gApeMemoryViewerGlobalArrayNameChars;
GSN_WIN_EXPORT std::string                                              gApeMemoryViewerInterpretBytesChars;
GSN_WIN_EXPORT std::string                                              gApeErrors;
GSN_WIN_EXPORT std::vector<ApeDrawLabelDebugText>                       gApeDrawLabelStackDebugTexts;
GSN_WIN_EXPORT std::vector<ApeDrawLabelPoint>                           gApeDrawLabelStackPoints;
GSN_WIN_EXPORT std::vector<ApeDrawLabelLine>                            gApeDrawLabelStackLines;
GSN_WIN_EXPORT std::vector<ApeDrawLabelTriangle>                        gApeDrawLabelStackTriangles;
GSN_WIN_EXPORT std::vector<ApeDrawLabelMesh>                            gApeDrawLabelStackMeshes;
GSN_WIN_EXPORT std::vector<ApeDrawFbo>                                  gApeDrawFbos;
GSN_WIN_EXPORT std::vector<ApeDrawImage>                                gApeDrawImages;
GSN_WIN_EXPORT std::vector<ApeDrawImageSubsection>                      gApeDrawImagesSubsections;
GSN_WIN_EXPORT void *                                                   gExternalLibraryHandle                                  = 0;
GSN_WIN_EXPORT void                                                   (*gExternalLibraryProcedureCall2)(double, double)         = 0;
GSN_WIN_EXPORT void                                                   (*gExternalLibraryProcedureCall3)(double, double, double) = 0;
GSN_WIN_EXPORT std::vector<std::string>                                 gProgramArguments;
GSN_WIN_EXPORT char *                                                   gCurrentExeDir                                          = 0;
GSN_WIN_EXPORT char *                                                   gClipboard                                              = 0;
GSN_WIN_EXPORT std::unordered_map<int/*keycode*/, int/*event*/>         gGlfwKeyEvent;
GSN_WIN_EXPORT std::unordered_map<int/*keycode*/, int/*mdofiers*/>      gGlfwKeyModifiers;
GSN_WIN_EXPORT unsigned                                                 gGlfwCodepointCharacter                                 = 0;
GSN_WIN_EXPORT std::unordered_map<std::string, uint64_t>                gApeGlobalArrayBytesCount;
GSN_WIN_EXPORT std::unordered_map<std::string, void *>                  gApeGlobalArrayPointer;
GSN_WIN_EXPORT std::unordered_map<std::string, uint64_t>                gApeGlobalArrayPersistentBytesCount;
GSN_WIN_EXPORT std::unordered_map<std::string, void *>                  gApeGlobalArrayPersistentPointer;
GSN_WIN_EXPORT std::unordered_map<std::string, uint64_t>                gApeGlobalSharedArrayPersistentBytesCount;
GSN_WIN_EXPORT std::unordered_map<std::string, void *>                  gApeGlobalSharedArrayPersistentPointer;
GSN_WIN_EXPORT std::unordered_map<std::string, std::vector<double> *>   gApeGlobalDynamicArray;
GSN_WIN_EXPORT std::unordered_map<std::string, std::vector<double> *>   gApeGlobalDynamicArrayPersistent;
GSN_WIN_EXPORT unsigned                                                 gMouseEvent                                             = 0;
GSN_WIN_EXPORT int                                                      gMouseButtonIsPressed[8]                                = {};
GSN_WIN_EXPORT int                                                      gMouseButtonIsReleased[8]                               = {};
GSN_WIN_EXPORT float                                                    gMouseWheelScroll                                       = 0;
GSN_WIN_EXPORT std::unordered_map<std::string, RedFHandleManipulator *> gApeGizmos;
GSN_WIN_EXPORT std::unordered_map<std::string, RedFHandleFbo *>         gApeFbos;
GSN_WIN_EXPORT std::map<std::string, RedFHandleMesh *>                  gApeMeshes;
GSN_WIN_EXPORT std::map<std::string, RedFHandleMesh *>                  gApeMeshesPersistent;
GSN_WIN_EXPORT std::unordered_map<std::string, RedFHandleAssimp *>      gApeAssimpPersistent;
GSN_WIN_EXPORT std::unordered_map<std::string, RedFHandleImage *>       gApeImages;
GSN_WIN_EXPORT std::unordered_map<std::string, RedFHandleImage *>       gApeImagesPersistent;
GSN_WIN_EXPORT std::unordered_map<std::string, RedFHandleShader *>      gApeShaders;
GSN_WIN_EXPORT std::unordered_map<std::string, RedFHandleSoundPlayer *> gApeSoundPlayers;
GSN_WIN_EXPORT std::unordered_map<std::string, RedFHandleSoundPlayer *> gApeSoundPlayersPersistent;
GSN_WIN_EXPORT std::unordered_map<std::string, RedFHandleFbx *>         gApeFbxs;
GSN_WIN_EXPORT std::map<std::string, std::map<std::string, GlobalKeyPropery> > gKeyProperties;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallErtDecRef;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallErtDestroyDevice;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedCpuSignalWait;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedMemoryFree;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedStructsMemoryFree;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyContext;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyArray;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyImage;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroySampler;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyTexture;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyGpuCode;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyOutputDeclaration;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyStructDeclaration;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyProcedureParameters;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyProcedureCache;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyProcedure;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyOutput;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyCpuSignal;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyGpuSignal;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyGpuToCpuSignal;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyCalls;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyArrayTimestamp;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRrtDestroyContext;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRrtReleaseCommandStream;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRrtReleaseEvent;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRrtWaitEvent;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRrtReleaseDevicePtr;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRrtReleaseExternalCommandStream;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRrtUnmapDevicePtr;
GSN_WIN_EXPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallXatlasDestroy;
GSN_WIN_EXPORT std::string                                              gF1CommandOptions;
GSN_WIN_EXPORT std::string                                              gThreadF1OutputText;
GSN_WIN_EXPORT RedFHandleThread *                                       gThreadF1                                               = 0;
GSN_WIN_EXPORT RedFHandleThread *                                       gThread2                                                = 0;
GSN_WIN_EXPORT volatile uint64_t                                        gThread2StopSignal                                      = 0;
GSN_WIN_EXPORT volatile uint64_t                                        gUniqueNumber                                           = 0;
GSN_WIN_EXPORT int                                                      gEmbreeIsEnabled                                        = 1;
GSN_WIN_EXPORT int                                                      gRedGpuIsEnabled                                        = 1;
GSN_WIN_EXPORT int                                                      gXatlasIsEnabled                                        = 1;
GSN_WIN_EXPORT int                                                      gFbxIsEnabled                                           = 1;
GSN_WIN_EXPORT std::mutex                                               __GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_thread2PrintGuardAndSerializeMutex;
GSN_WIN_EXPORT std::mutex                                               __GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_thread2GlobalSharedArrayPersistentGuardAndSerializeMutex;
GSN_WIN_EXPORT std::mutex                                               __GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_thread2ThreadSafeMemoryGuardAndSerializeMutex;
GSN_WIN_EXPORT std::mutex                                               __GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex;
GSN_WIN_EXPORT std::mutex                                               __GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_fbxsMutex;
GSN_WIN_EXPORT std::mutex                                               __GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_threadF1OutputTextMutex;
GSN_WIN_EXPORT std::mutex                                               __GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_minScriptLangErrorMutex;
GSN_WIN_EXPORT volatile uint64_t                                        gDragAndDropCounter                                     = 0;
GSN_WIN_EXPORT float                                                    gDragAndDropPositionX                                   = 0;
GSN_WIN_EXPORT float                                                    gDragAndDropPositionY                                   = 0;
GSN_WIN_EXPORT std::vector<std::string>                                 gDragAndDropFilepaths;
#if defined(GAME_SCRIPT_NATIVE)
GSN_WIN_EXPORT void *                                                   libgame                                                 = 0;
GSN_WIN_EXPORT void *                                                   libthread2                                              = 0;
#endif
#if defined(GAME_SCRIPT_C)
GSN_WIN_EXPORT void *                                                   gTCCStateCache[2]                                       = {0, 0};
GSN_WIN_EXPORT int                                                      gTCCStateRerun[2]                                       = {0, 0};
GSN_WIN_EXPORT void                                                   (*gTCCStateCacheFrameFunction)(void)                      = 0;
GSN_WIN_EXPORT void                                                   (*gTCCStateCacheFrameFunctionThread2)(void)               = 0;
#endif

#if defined(GAME_SCRIPT_C)
void tccMessageCallback(void * opaque, const char * msg) {
  if (msg != 0) {
    std::lock_guard<std::mutex> __minScriptLangErrorGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_minScriptLangErrorMutex);
    gApeErrors += msg;
    gApeErrors += "\n";
  }
}
#endif

void * libvulkan                      = 0;
void * libvulkanVkGetInstanceProcAddr = 0;
#if defined(__linux__)
GSN_WIN_EXPORT void * _gsVkGetInstanceProcAddr(void * instance, const char * name) {
  if (libvulkan == 0) {
    libvulkan = dlopen("libvulkan.so", RTLD_LAZY);
  }
  if (libvulkan == 0) {
    return 0;
  }
  if (libvulkanVkGetInstanceProcAddr == 0) {
    libvulkanVkGetInstanceProcAddr = dlsym(libvulkan, "vkGetInstanceProcAddr");
  }
  if (libvulkanVkGetInstanceProcAddr == 0) {
    return 0;
  }
  void * (*getInstanceProcAddr)(void * instance, const char * name) = (void * (*)(void *, const char *))libvulkanVkGetInstanceProcAddr;
  void * out = getInstanceProcAddr(instance, name);
  return out;
}
#elif defined(_WIN32)
GSN_WIN_EXPORT void * _gsVkGetInstanceProcAddr(void * instance, const char * name) {
  if (libvulkan == 0) {
    libvulkan = (void *)LoadLibraryA("vulkan-1.dll");
  }
  if (libvulkan == 0) {
    return 0;
  }
  if (libvulkanVkGetInstanceProcAddr == 0) {
    libvulkanVkGetInstanceProcAddr = (void *)(void (*)(void))GetProcAddress((HMODULE)libvulkan, "vkGetInstanceProcAddr");
  }
  if (libvulkanVkGetInstanceProcAddr == 0) {
    return 0;
  }
  void * (*getInstanceProcAddr)(void * instance, const char * name) = (void * (*)(void *, const char *))libvulkanVkGetInstanceProcAddr;
  void * out = getInstanceProcAddr(instance, name);
  return out;
}
#else
#error Error
#endif

GSN_WIN_EXPORT void _gsPrintThreadSafe(const char * astring) {
  std::lock_guard<std::mutex> __thread2PrintGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_thread2PrintGuardAndSerializeMutex);
  printf("%s", astring);
  fflush(stdout);
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

static inline std::vector<float> crossProduct(float x0, float y0, float z0, float x1, float y1, float z1) {
  float x = y0 * z1 - y1 * z0;
  float y = z0 * x1 - z1 * x0;
  float z = x0 * y1 - x1 * y0;
  std::vector<float> out = {x, y, z};
  return out;
}

static inline float dotProduct(float x0, float y0, float z0, float x1, float y1, float z1) {
  return x0 * x1 + y0 * y1 + z0 * z1;
}

// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
static std::vector<float> rayTriangleIntersection(float rayOriginX, float rayOriginY, float rayOriginZ, float rayVectorX, float rayVectorY, float rayVectorZ, float trianglev0x, float trianglev0y, float trianglev0z, float trianglev1x, float trianglev1y, float trianglev1z, float trianglev2x, float trianglev2y, float trianglev2z) {
  std::vector<float> out = {0, 0, 0, 0};
  float epsilon = 0.0000001;
  float vertex0x = trianglev0x;
  float vertex0y = trianglev0y;
  float vertex0z = trianglev0z;
  float vertex1x = trianglev1x;
  float vertex1y = trianglev1y;
  float vertex1z = trianglev1z;
  float vertex2x = trianglev2x;
  float vertex2y = trianglev2y;
  float vertex2z = trianglev2z;
  float edge1x = vertex1x - vertex0x;
  float edge1y = vertex1y - vertex0y;
  float edge1z = vertex1z - vertex0z;
  float edge2x = vertex2x - vertex0x;
  float edge2y = vertex2y - vertex0y;
  float edge2z = vertex2z - vertex0z;
  std::vector<float> hv = crossProduct(rayVectorX, rayVectorY, rayVectorZ, edge2x, edge2y, edge2z);
  float hx = hv[0];
  float hy = hv[1];
  float hz = hv[2];
  float a = dotProduct(edge1x, edge1y, edge1z, hx, hy, hz);
  if (a > -epsilon && a < epsilon) {
    return out; // This ray is parallel to this triangle.
  }
  float f = 1.0 / a;
  float sx = rayOriginX - vertex0x;
  float sy = rayOriginY - vertex0y;
  float sz = rayOriginZ - vertex0z;
  float u = f * dotProduct(sx, sy, sz, hx, hy, hz);
  if (u < 0.0 || u > 1.0) {
    return out;
  }
  std::vector<float> qv = crossProduct(sx, sy, sz, edge1x, edge1y, edge1z);
  float qx = qv[0];
  float qy = qv[1];
  float qz = qv[2];
  float v = f * dotProduct(rayVectorX, rayVectorY, rayVectorZ, qx, qy, qz);
  if (v < 0.0 || u + v > 1.0) {
    return out;
  }
  // At this stage we can compute t to find out where the intersection point is on the line.
  float t = f * dotProduct(edge2x, edge2y, edge2z, qx, qy, qz);
  if (t > epsilon) {
    // Ray intersection
    float outIntersectionPointX = rayOriginX + rayVectorX * t;
    float outIntersectionPointY = rayOriginY + rayVectorY * t;
    float outIntersectionPointZ = rayOriginZ + rayVectorZ * t;
    out[0] = outIntersectionPointX;
    out[1] = outIntersectionPointY;
    out[2] = outIntersectionPointZ;
    out[3] = 1;
    return out;
  } else {
    // This means that there is a line intersection but not a ray intersection.
    return out;
  }
}

static void f1CommandOptionsSave(std::string filename) {
  std::string filepath = gCurrentExeDir;
  filepath += filename;

  std::ofstream fs(filepath, std::ofstream::out);
  fs << gF1CommandOptions.c_str();
  fs.close();
}

static void scriptSave(std::string filename) {
  std::string filepath = gCurrentExeDir;
  filepath += filename;

  std::ofstream fs(filepath, std::ofstream::out);
  fs << gApeCodeChars.c_str();
  if (gApeCodeChars != "") {
    if (gApeCodeChars.back() != '\n') {
      fs << "\n"; // NOTE(Constantine): This is here for a reason: Dear ImGui deletes last character at the beginning of script editing for some reason.
    }
  }
  fs.close();
}

static void scriptLoad(std::string filename) {
  std::string filepath = gCurrentExeDir;
  filepath += filename;

  std::ostringstream ss;
  ss << std::ifstream(filepath).rdbuf();
  gApeCodeChars = ss.str();
}

static void apeScriptRerun(RedFBool32 startupRerun) {
  if (gThread2 != 0) {
    gThread2StopSignal = 1;
    if (redFThreadIsRunning(gThread2[0]) == 1) {
      redFThreadWaitFor(gThread2[0], 1, -1);
    }
    gCurrentFrameThread2 = 0;
  }
#if defined(GAME_SCRIPT_C)
  if (startupRerun == 0) {
    gTCCStateRerun[0]    = 1;
    gTCCStateRerun[1]    = 1;
  }
#endif
  gRerun                 = 1;
  gCurrentFrame          = 0;
  gApeErrors             = "";
  gF2Toggle              = 1;
  for (auto & kv : gApeGlobalArrayPointer) {
    free(kv.second);
  }
  for (auto & kv : gApeGlobalDynamicArray) {
    delete kv.second;
  }
  for (auto & kv : gApeFbos) {
    redFDestroyFbo(kv.second);
  }
  for (auto & kv : gApeMeshes) {
    redFDestroyMesh(kv.second);
  }
  for (auto & kv : gApeImages) {
    redFDestroyImage(kv.second);
  }
  for (auto & kv : gApeShaders) {
    redFDestroyShader(kv.second);
  }
  for (auto & kv : gApeSoundPlayers) {
    redFDestroySoundPlayer(kv.second);
  }
  gApeGlobalArrayBytesCount.clear();
  gApeGlobalArrayPointer.clear();
  gApeGlobalDynamicArray.clear();
  gApeFbos.clear();
  gApeMeshes.clear();
  gApeImages.clear();
  gApeShaders.clear();
  gApeSoundPlayers.clear();
  {

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRrtWaitEvent) {
      RRContext context = (RRContext)element.storage[0];
      RREvent   handle   = (RREvent)element.storage[1];

      RRError status = rrWaitEvent(context, handle);
      if (status != RR_SUCCESS) {
        std::string msg;
        msg += "[REDGPU] rrtWaitEvent on rerun call returned RRError != RR_SUCCESS for RRContext ";
        msg += std::to_string((uint64_t)context);
        msg += ", handle ";
        msg += std::to_string((uint64_t)handle);
        _gsPrintThreadSafe(msg.c_str());
      }
    }
    gGlobalArrayPersistentOnRerunCallRrtWaitEvent.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedCpuSignalWait) {
      RedContext         context = (RedContext)element.storage[0];
      RedHandleGpu       gpu     = (RedHandleGpu)element.storage[1];
      RedHandleCpuSignal handle  = (RedHandleCpuSignal)element.storage[2];

      redCpuSignalWait(context, gpu, 1, &handle, 1, 0, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedCpuSignalWait.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallXatlasDestroy) {
      XatlasAtlas * xatlas = (XatlasAtlas *)element.storage[0];
      xatlasDestroy(xatlas);
    }
    gGlobalArrayPersistentOnRerunCallXatlasDestroy.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallErtDecRef) {
      embree::Device *         device = (embree::Device *)element.storage[0];
      embree::Device::RTHandle handle = (embree::Device::RTHandle)element.storage[1];
      device->rtDecRef(handle);
    }
    gGlobalArrayPersistentOnRerunCallErtDecRef.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallErtDestroyDevice) {
      embree::Device * device = (embree::Device *)element.storage[0];
      delete device;
    }
    gGlobalArrayPersistentOnRerunCallErtDestroyDevice.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRrtReleaseEvent) {
      RRContext context = (RRContext)element.storage[0];
      RREvent   handle  = (RREvent)element.storage[1];

      RRError status = rrReleaseEvent(context, handle);
      if (status != RR_SUCCESS) {
        std::string msg;
        msg += "[REDGPU] rrReleaseEvent on rerun call returned RRError != RR_SUCCESS for RRContext ";
        msg += std::to_string((uint64_t)context);
        msg += ", handle ";
        msg += std::to_string((uint64_t)handle);
        _gsPrintThreadSafe(msg.c_str());
      }
    }
    gGlobalArrayPersistentOnRerunCallRrtReleaseEvent.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRrtReleaseExternalCommandStream) {
      RRContext       context = (RRContext)element.storage[0];
      RRCommandStream handle  = (RRCommandStream)element.storage[1];

      RRError status = rrReleaseExternalCommandStream(context, handle);
      if (status != RR_SUCCESS) {
        std::string msg;
        msg += "[REDGPU] rrReleaseExternalCommandStream on rerun call returned RRError != RR_SUCCESS for RRContext ";
        msg += std::to_string((uint64_t)context);
        msg += ", handle ";
        msg += std::to_string((uint64_t)handle);
        _gsPrintThreadSafe(msg.c_str());
      }
    }
    gGlobalArrayPersistentOnRerunCallRrtReleaseExternalCommandStream.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRrtReleaseCommandStream) {
      RRContext       context = (RRContext)element.storage[0];
      RRCommandStream handle  = (RRCommandStream)element.storage[1];

      RRError status = rrReleaseCommandStream(context, handle);
      if (status != RR_SUCCESS) {
        std::string msg;
        msg += "[REDGPU] rrReleaseCommandStream on rerun call returned RRError != RR_SUCCESS for RRContext ";
        msg += std::to_string((uint64_t)context);
        msg += ", handle ";
        msg += std::to_string((uint64_t)handle);
        _gsPrintThreadSafe(msg.c_str());
      }
    }
    gGlobalArrayPersistentOnRerunCallRrtReleaseCommandStream.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRrtUnmapDevicePtr) {
      RRContext   context       = (RRContext)element.storage[0];
      RRDevicePtr devicePointer = (RRDevicePtr)element.storage[1];
      void **     handle        = (void **)element.storage[2];

      RRError status = rrUnmapDevicePtr(context, devicePointer, handle);
      if (status != RR_SUCCESS) {
        std::string msg;
        msg += "[REDGPU] rrtUnmapDevicePtr on rerun call returned RRError != RR_SUCCESS for RRContext ";
        msg += std::to_string((uint64_t)context);
        msg += ", RRDevicePtr ";
        msg += std::to_string((uint64_t)devicePointer);
        msg += ", handle ";
        msg += std::to_string((uint64_t)handle);
        _gsPrintThreadSafe(msg.c_str());
      }
    }
    gGlobalArrayPersistentOnRerunCallRrtUnmapDevicePtr.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRrtReleaseDevicePtr) {
      RRContext   context = (RRContext)element.storage[0];
      RRDevicePtr handle  = (RRDevicePtr)element.storage[1];

      RRError status = rrReleaseDevicePtr(context, handle);
      if (status != RR_SUCCESS) {
        std::string msg;
        msg += "[REDGPU] rrReleaseDevicePtr on rerun call returned RRError != RR_SUCCESS for RRContext ";
        msg += std::to_string((uint64_t)context);
        msg += ", handle ";
        msg += std::to_string((uint64_t)handle);
        _gsPrintThreadSafe(msg.c_str());
      }
    }
    gGlobalArrayPersistentOnRerunCallRrtReleaseDevicePtr.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRrtDestroyContext) {
      RRContext context = (RRContext)element.storage[0];

      RRError status = rrDestroyContext(context);
      if (status != RR_SUCCESS) {
        std::string msg;
        msg += "[REDGPU] rrDestroyContext on rerun call returned RRError != RR_SUCCESS for RRContext ";
        msg += std::to_string((uint64_t)context);
        _gsPrintThreadSafe(msg.c_str());
      }
    }
    gGlobalArrayPersistentOnRerunCallRrtDestroyContext.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedDestroyGpuToCpuSignal) {
      RedContext              context = (RedContext)element.storage[0];
      RedHandleGpu            gpu     = (RedHandleGpu)element.storage[1];
      RedHandleGpuToCpuSignal handle  = (RedHandleGpuToCpuSignal)element.storage[2];

      redDestroyGpuToCpuSignal(context, gpu, handle, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedDestroyGpuToCpuSignal.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedDestroyGpuSignal) {
      RedContext         context = (RedContext)element.storage[0];
      RedHandleGpu       gpu     = (RedHandleGpu)element.storage[1];
      RedHandleGpuSignal handle  = (RedHandleGpuSignal)element.storage[2];

      redDestroyGpuSignal(context, gpu, handle, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedDestroyGpuSignal.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedDestroyCpuSignal) {
      RedContext         context = (RedContext)element.storage[0];
      RedHandleGpu       gpu     = (RedHandleGpu)element.storage[1];
      RedHandleCpuSignal handle  = (RedHandleCpuSignal)element.storage[2];

      redDestroyCpuSignal(context, gpu, handle, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedDestroyCpuSignal.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedDestroyCalls) {
      RedContext           context = (RedContext)element.storage[0];
      RedHandleGpu         gpu     = (RedHandleGpu)element.storage[1];
      RedHandleCalls       handle  = (RedHandleCalls)element.storage[2];
      RedHandleCallsMemory memory  = (RedHandleCallsMemory)element.storage[3];

      redDestroyCalls(context, gpu, handle, memory, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedDestroyCalls.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedDestroyProcedureParameters) {
      RedContext                   context = (RedContext)element.storage[0];
      RedHandleGpu                 gpu     = (RedHandleGpu)element.storage[1];
      RedHandleProcedureParameters handle  = (RedHandleProcedureParameters)element.storage[2];

      redDestroyProcedureParameters(context, gpu, handle, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedDestroyProcedureParameters.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedDestroyProcedureCache) {
      RedContext              context = (RedContext)element.storage[0];
      RedHandleGpu            gpu     = (RedHandleGpu)element.storage[1];
      RedHandleProcedureCache handle  = (RedHandleProcedureCache)element.storage[2];

      redDestroyProcedureCache(context, gpu, handle, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedDestroyProcedureCache.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedDestroyProcedure) {
      RedContext         context = (RedContext)element.storage[0];
      RedHandleGpu       gpu     = (RedHandleGpu)element.storage[1];
      RedHandleProcedure handle  = (RedHandleProcedure)element.storage[2];

      redDestroyProcedure(context, gpu, handle, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedDestroyProcedure.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedDestroyGpuCode) {
      RedContext       context = (RedContext)element.storage[0];
      RedHandleGpu     gpu     = (RedHandleGpu)element.storage[1];
      RedHandleGpuCode handle  = (RedHandleGpuCode)element.storage[2];

      redDestroyGpuCode(context, gpu, handle, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedDestroyGpuCode.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedDestroyOutput) {
      RedContext      context = (RedContext)element.storage[0];
      RedHandleGpu    gpu     = (RedHandleGpu)element.storage[1];
      RedHandleOutput handle  = (RedHandleOutput)element.storage[2];

      redDestroyOutput(context, gpu, handle, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedDestroyOutput.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedDestroyOutputDeclaration) {
      RedContext                 context = (RedContext)element.storage[0];
      RedHandleGpu               gpu     = (RedHandleGpu)element.storage[1];
      RedHandleOutputDeclaration handle  = (RedHandleOutputDeclaration)element.storage[2];

      redDestroyOutputDeclaration(context, gpu, handle, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedDestroyOutputDeclaration.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedDestroySampler) {
      RedContext       context = (RedContext)element.storage[0];
      RedHandleGpu     gpu     = (RedHandleGpu)element.storage[1];
      RedHandleSampler handle  = (RedHandleSampler)element.storage[2];

      redDestroySampler(context, gpu, handle, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedDestroySampler.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedDestroyTexture) {
      RedContext       context = (RedContext)element.storage[0];
      RedHandleGpu     gpu     = (RedHandleGpu)element.storage[1];
      RedHandleTexture handle  = (RedHandleTexture)element.storage[2];

      redDestroyTexture(context, gpu, handle, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedDestroyTexture.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedDestroyImage) {
      RedContext     context = (RedContext)element.storage[0];
      RedHandleGpu   gpu     = (RedHandleGpu)element.storage[1];
      RedHandleImage handle  = (RedHandleImage)element.storage[2];

      redDestroyImage(context, gpu, handle, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedDestroyImage.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedDestroyArray) {
      RedContext     context = (RedContext)element.storage[0];
      RedHandleGpu   gpu     = (RedHandleGpu)element.storage[1];
      RedHandleArray handle  = (RedHandleArray)element.storage[2];

      redDestroyArray(context, gpu, handle, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedDestroyArray.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedDestroyArrayTimestamp) {
      RedContext              context = (RedContext)element.storage[0];
      RedHandleGpu            gpu     = (RedHandleGpu)element.storage[1];
      RedHandleArrayTimestamp handle  = (RedHandleArrayTimestamp)element.storage[2];

      redDestroyArrayTimestamp(context, gpu, handle, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedDestroyArrayTimestamp.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedStructsMemoryFree) {
      RedContext             context = (RedContext)element.storage[0];
      RedHandleGpu           gpu     = (RedHandleGpu)element.storage[1];
      RedHandleStructsMemory handle  = (RedHandleStructsMemory)element.storage[2];

      redStructsMemoryFree(context, gpu, handle, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedStructsMemoryFree.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedDestroyStructDeclaration) {
      RedContext                 context = (RedContext)element.storage[0];
      RedHandleGpu               gpu     = (RedHandleGpu)element.storage[1];
      RedHandleStructDeclaration handle  = (RedHandleStructDeclaration)element.storage[2];

      redDestroyStructDeclaration(context, gpu, handle, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedDestroyStructDeclaration.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedMemoryFree) {
      RedContext      context = (RedContext)element.storage[0];
      RedHandleGpu    gpu     = (RedHandleGpu)element.storage[1];
      RedHandleMemory handle  = (RedHandleMemory)element.storage[2];

      redMemoryFree(context, gpu, handle, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedMemoryFree.clear();

    for (GlobalArrayPersistentOnRerunCallStorage & element : gGlobalArrayPersistentOnRerunCallRedDestroyContext) {
      RedContext context = (RedContext)element.storage[0];

      redDestroyContext(context, 0, 0, 0);
    }
    gGlobalArrayPersistentOnRerunCallRedDestroyContext.clear();

  }
  if (startupRerun == 0) {
    scriptSave("autosave.script");
  }
  free(gApeCodeCharsCurrentlyRunning);
  if (gReadScriptFromDataGameDotScript == 0) {
    gApeCodeCharsCurrentlyRunning = (char *)calloc(1, gApeCodeChars.size() + 1);
    if (gApeCodeCharsCurrentlyRunning != NULL && gApeCodeChars.size() > 0) {
      memcpy(gApeCodeCharsCurrentlyRunning, &gApeCodeChars[0], gApeCodeChars.size());
    }
  } else {
    std::string filepath = gCurrentExeDir;
    filepath += "game.script";
    std::ostringstream ss;
    ss << std::ifstream(filepath.c_str()).rdbuf();
    std::string s = ss.str();
    gApeCodeCharsCurrentlyRunning = (char *)calloc(1, s.size() + 1);
    if (gApeCodeCharsCurrentlyRunning != NULL && s.size() > 0) {
      memcpy(gApeCodeCharsCurrentlyRunning, &s[0], s.size());
    }
  }
  // Thread 2
  {
    std::string filepath = gCurrentExeDir;
    filepath += "thread2.script";
    std::ostringstream ss;
    ss << std::ifstream(filepath.c_str()).rdbuf();
    std::string s = ss.str();
    free(gApeCodeCharsCurrentlyRunningThread2);
    gApeCodeCharsCurrentlyRunningThread2 = (char *)calloc(1, s.size() + 1);
    if (gApeCodeCharsCurrentlyRunningThread2 != NULL && s.size() > 0) {
      memcpy(gApeCodeCharsCurrentlyRunningThread2, &s[0], s.size());
    }
  }
  gApeCodeCharsNextRunning                = "";
  gApeCodeCharsNextRunningThread2         = "";
  gApeErrorCheck                          = 1;
  gApeErrorCheckThread2                   = 1;
  gGameScriptNativeRecompileSignal        = startupRerun == 1 ? 0 : 1;
  gGameScriptNativeRecompileSignalThread2 = startupRerun == 1 ? 0 : 1;
}

#if defined(GAME_SCRIPT_NATIVE)

void (*libgameFrame)(void)    = 0;
void (*libthread2Frame)(void) = 0;

static void gsnLoadLibrary(int threadIndex, std::string dir) {
  profileBegin("load library");
  std::string errors;
  {
    if (threadIndex == 0) {
      std::string filepath = dir;
#if defined(__linux__)
      filepath += "libgame.so";
#elif defined(_WIN32)
      filepath += "game.dll";
#else
#error Error
#endif
      libgame = gsLoadLibrary(filepath.c_str());
      if (libgame == 0) {
        const char * errorPointer = gsLoadLibraryError(filepath.c_str());
        errors = errorPointer == 0 ? "" : errorPointer;
        gApeErrors += "[Frame ";
        gApeErrors += std::to_string(gCurrentFrame);
        gApeErrors += "]\n\n";
        gApeErrors += "gsLoadLibrary(\"";
        gApeErrors += filepath;
        gApeErrors += "\") returned NULL.\n";
        gApeErrors += errors;
        errors = "";
      } else {
        libgameFrame = (void (*)(void))gsGetProcAddress(libgame, "frame");
        if (libgameFrame == 0) {
          const char * errorPointer = gsGetProcAddressError(libgame, "frame");
          errors = errorPointer == 0 ? "" : errorPointer;
          gApeErrors += "[Frame ";
          gApeErrors += std::to_string(gCurrentFrame);
          gApeErrors += "]\n\n";
          gApeErrors += "gsGetProcAddress(\"";
          gApeErrors += filepath;
          gApeErrors += "\", \"frame\") returned NULL.\n";
          gApeErrors += "Please make sure that \"frame\" procedure is defined as \"cfn frame() { /* Your code here */ }\".\n";
          gApeErrors += errors;
          errors = "";
        }
      }
    } else {
      std::string filepath = dir;
#if defined(__linux__)
      filepath += "libthread2.so";
#elif defined(_WIN32)
      filepath += "thread2.dll";
#else
#error Error
#endif
      libthread2 = gsLoadLibrary(filepath.c_str());
      if (libthread2 == 0) {
        const char * errorPointer = gsLoadLibraryError(filepath.c_str());
        errors = errorPointer == 0 ? "" : errorPointer;
        gApeErrors += "[Game Script][Thread 2 Script Errors]";
        gApeErrors += "[Frame ";
        gApeErrors += std::to_string(gCurrentFrameThread2);
        gApeErrors += "]\n\n";
        gApeErrors += "gsLoadLibrary(\"";
        gApeErrors += filepath;
        gApeErrors += "\") returned NULL.\n";
        gApeErrors += errors;
        errors = "";
      } else {
        libthread2Frame = (void (*)(void))gsGetProcAddress(libthread2, "frame");
        if (libthread2Frame == 0) {
          const char * errorPointer = gsGetProcAddressError(libthread2, "frame");
          errors = errorPointer == 0 ? "" : errorPointer;
          gApeErrors += "[Game Script][Thread 2 Script Errors]";
          gApeErrors += "[Frame ";
          gApeErrors += std::to_string(gCurrentFrameThread2);
          gApeErrors += "]\n\n";
          gApeErrors += "gsGetProcAddress(\"";
          gApeErrors += filepath;
          gApeErrors += "\", \"frame\") returned NULL.\n";
          gApeErrors += "Please make sure that \"frame\" procedure is defined as \"cfn frame() { /* Your code here */ }\".\n";
          gApeErrors += errors;
          errors = "";
        }
      }
    }
  }
  profileEnd("load library");
}

static void mape_execute(int threadIndex, void * ape, const char * code) {
  int recompile = threadIndex == 0 ? gGameScriptNativeRecompileSignal : gGameScriptNativeRecompileSignalThread2;

  if (recompile == 0) {
    // Just continue running the current frame procedures.
    if (threadIndex == 0) {
      if (libgameFrame != 0) {
        libgameFrame();
      }
    } else {
      if (libthread2Frame != 0) {
        libthread2Frame();
      }
    }
    // Return, no need to recompile.
    return;
  }

  // Unload the previously compiled and loaded frame procedures and libraries.
  profileBegin("unload library");
  {
    if (threadIndex == 0) { libgameFrame    = 0; }
    if (threadIndex == 1) { libthread2Frame = 0; }
    if (threadIndex == 0) {
      if (libgame != 0) {
        gsFreeLibrary(libgame);
        libgame = 0;
      }
    } else {
      if (libthread2 != 0) {
        gsFreeLibrary(libthread2);
        libthread2 = 0;
      }
    }
  }
  profileEnd("unload library");

  // Save the code to either game.cpp or thread2.cpp files.
  profileBegin("save .cpp files");
  {
#if defined(__linux__)
    std::ofstream fs(threadIndex == 0 ? "/opt/GameScriptNative/game.cpp" : "/opt/GameScriptNative/thread2.cpp", std::ofstream::out);
#elif defined(_WIN32)
    std::ofstream fs(threadIndex == 0 ? "C:/GameScriptNative/game.cpp" : "C:/GameScriptNative/thread2.cpp", std::ofstream::out);
#else
#error Error
#endif
    std::string source = code;
    fs << source;
    fs << "\n";
    fs.close();
  }
  profileEnd("save .cpp files");

  // Compile and print error output, if needed.
  profileBegin("compile .cpp files");
  std::string errors;
  {
    char * output = 0;
#if defined(__linux__)
    if (threadIndex == 0) {
      redFSystem("/opt/GameScriptNative/compile_game.sh 2> /dev/stdout", &output, 0);
    } else {
      redFSystem("/opt/GameScriptNative/compile_thread2.sh 2> /dev/stdout", &output, 0);
    }
#elif defined(_WIN32)
    if (threadIndex == 0) {
      redFSystem("C:/GameScriptNative/compile_game.bat", &output, 0);
    } else {
      redFSystem("C:/GameScriptNative/compile_thread2.bat", &output, 0);
    }
#else
#error Error
#endif
    errors = output;
    redFFree(output);
  }
  if (errors != "") {
    if (threadIndex == 1) {
      gApeErrors += "[Game Script][Thread 2 Script Errors]";
    }
    gApeErrors += "[Frame ";
    gApeErrors += std::to_string(threadIndex == 0 ? gCurrentFrame : gCurrentFrameThread2);
    gApeErrors += "]\n\n";
    gApeErrors += errors;
    errors = "";
  }
  profileEnd("compile .cpp files");

  // Load the compiled libraries and frame procedures.
#if defined(__linux__)
  gsnLoadLibrary(threadIndex, "/opt/GameScriptNative/");
#elif defined(_WIN32)
  gsnLoadLibrary(threadIndex, "C:/GameScriptNative/");
#else
#error Error
#endif

  // Run the compiled and loaded frame procedures.
  if (threadIndex == 0) {
    if (libgameFrame != 0) {
      libgameFrame();
    }
  } else {
    if (libthread2Frame != 0) {
      libthread2Frame();
    }
  }

  if (threadIndex == 0) { gGameScriptNativeRecompileSignal        = 0; }
  if (threadIndex == 1) { gGameScriptNativeRecompileSignalThread2 = 0; }
}

#endif // #if defined(GAME_SCRIPT_NATIVE)

static int guiCodeEditorCallback(ImGuiInputTextCallbackData * data) {
  if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
    gApeCodeChars.resize(data->BufSize);
    data->Buf = &gApeCodeChars[0];
  }
  return 0;
}

static int guiMemoryViewerCallback(ImGuiInputTextCallbackData * data) {
#if 0
  printf("[DEBUG] ---\n");
  printf("[DEBUG] %s:\n", __FUNCTION__);
  printf("[DEBUG] data->BufSize:    %d\n", data->BufSize);
  printf("[DEBUG] data->BufTextLen: %d\n", data->BufTextLen);
  printf("[DEBUG] ---\n");
  fflush(stdout);
#endif
  if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
    gApeMemoryViewerGlobalArrayNameChars.resize(data->BufSize);
    data->Buf = &gApeMemoryViewerGlobalArrayNameChars[0];
  }
  return 0;
}

static int guiMemoryViewerIntepretBytesCallback(ImGuiInputTextCallbackData * data) {
  if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
    gApeMemoryViewerInterpretBytesChars.resize(data->BufSize);
    data->Buf = &gApeMemoryViewerInterpretBytesChars[0];
  }
  return 0;
}

static void threadF1Procedure(void) {
  std::string scriptpath = "\"";
  std::string exedir = gCurrentExeDir;
  scriptpath += exedir;
#if defined(_WIN32)
  scriptpath += "f1.bat";
#else
  scriptpath += "f1.sh";
#endif
  scriptpath += "\"";
  char * output = 0;
  redFSystem(scriptpath.c_str(), &output, 0);
  std::string text = output;
  redFFree(output);
  {
    std::lock_guard<std::mutex> __threadF1OutputTextGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_threadF1OutputTextMutex);
    gThreadF1OutputText = text;
  }
}

static void thread2Procedure(void) {
  while (gThread2StopSignal == 0) {
    if (gStopScript == 0) {
      std::string thread2FrameString;
      thread2FrameString += "thread 2 frame ";
      thread2FrameString += std::to_string(gCurrentFrameThread2);
      profileBegin(thread2FrameString.c_str());
      profileBegin("thread 2 previous script destroy");
      mape_destroy(1, gApeThread2);
      profileEnd("thread 2 previous script destroy");
      profileBegin("thread 2 script make");
      gApeThread2 = mape_make(1);
#ifdef GAME_SCRIPT_MIN
      MinScriptLang::Environment env;
#endif
      profileEnd("thread 2 script make");
#ifdef GAME_SCRIPT_C
      profileBegin("thread 2 script compile");
      mape_compile(1, gApeThread2, gApeCodeCharsCurrentlyRunningThread2);
      profileEnd("thread 2 script compile");
#endif // #ifdef GAME_SCRIPT_C
#ifdef GAME_SCRIPT
      profileBegin("thread 2 script set procedures");
      mape_set_native_function(1, gApeThread2, "getCurrentFrameThread2",                   _gsCProcedureGetCurrentFrameThread2,                   NULL);
      mape_set_native_function(1, gApeThread2, "setCurrentFrameThread2",                   _gsCProcedureSetCurrentFrameThread2,                   NULL);
      mape_set_native_function(1, gApeThread2, "printConsole",                             _gsCProcedurePrintConsole,                             NULL); // Thread-safe.
      mape_set_native_function(1, gApeThread2, "getExeDirectoryPath",                      _gsCProcedureGetExeDirectoryPath,                      NULL); // Thread-safe.
      mape_set_native_function(1, gApeThread2, "globalSharedArrayPersistentNew8Bit",       _gsCProcedureGlobalSharedArrayPersistentNew8Bit,       NULL); // Thread-safe.
      mape_set_native_function(1, gApeThread2, "globalSharedArrayPersistentGetBytesCount", _gsCProcedureGlobalSharedArrayPersistentGetBytesCount, NULL); // Thread-safe.
      mape_set_native_function(1, gApeThread2, "globalSharedArrayPersistentGetPointer",    _gsCProcedureGlobalSharedArrayPersistentGetPointer,    NULL); // Thread-safe.
      mape_set_native_function(1, gApeThread2, "pointerGetBool",                           _gsCProcedurePointerGetBool,                           NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetString",                         _gsCProcedurePointerGetString,                         NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetSubstring",                      _gsCProcedurePointerGetSubstring,                      NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetNumber",                         _gsCProcedurePointerGetNumber,                         NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetInteger",                        _gsCProcedurePointerGetInteger,                        NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetUnsignedInteger",                _gsCProcedurePointerGetUnsignedInteger,                NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetInteger8Bit",                    _gsCProcedurePointerGetInteger8Bit,                    NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetUnsignedInteger8Bit",            _gsCProcedurePointerGetUnsignedInteger8Bit,            NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetAtOffsetNumber",                 _gsCProcedurePointerGetAtOffsetNumber,                 NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetAtOffsetInteger",                _gsCProcedurePointerGetAtOffsetInteger,                NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetAtOffsetUnsignedInteger",        _gsCProcedurePointerGetAtOffsetUnsignedInteger,        NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetAtOffsetInteger16Bit",           _gsCProcedurePointerGetAtOffsetInteger16Bit,           NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetAtOffsetUnsignedInteger16Bit",   _gsCProcedurePointerGetAtOffsetUnsignedInteger16Bit,   NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetAtOffsetNumber64Bit",            _gsCProcedurePointerGetAtOffsetNumber64Bit,            NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetAtOffsetInteger64Bit",           _gsCProcedurePointerGetAtOffsetInteger64Bit,           NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetAtOffsetUnsignedInteger64Bit",   _gsCProcedurePointerGetAtOffsetUnsignedInteger64Bit,   NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetBool",                           _gsCProcedurePointerSetBool,                           NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetString",                         _gsCProcedurePointerSetString,                         NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetStringExcludingNullChar",        _gsCProcedurePointerSetStringExcludingNullChar,        NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetSubstring",                      _gsCProcedurePointerSetSubstring,                      NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetNumber",                         _gsCProcedurePointerSetNumber,                         NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetInteger",                        _gsCProcedurePointerSetInteger,                        NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetUnsignedInteger",                _gsCProcedurePointerSetUnsignedInteger,                NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetInteger8Bit",                    _gsCProcedurePointerSetInteger8Bit,                    NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetUnsignedInteger8Bit",            _gsCProcedurePointerSetUnsignedInteger8Bit,            NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetAtOffsetNumber",                 _gsCProcedurePointerSetAtOffsetNumber,                 NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetAtOffsetInteger",                _gsCProcedurePointerSetAtOffsetInteger,                NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetAtOffsetUnsignedInteger",        _gsCProcedurePointerSetAtOffsetUnsignedInteger,        NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetAtOffsetInteger16Bit",           _gsCProcedurePointerSetAtOffsetInteger16Bit,           NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetAtOffsetUnsignedInteger16Bit",   _gsCProcedurePointerSetAtOffsetUnsignedInteger16Bit,   NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetAtOffsetNumber64Bit",            _gsCProcedurePointerSetAtOffsetNumber64Bit,            NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetAtOffsetInteger64Bit",           _gsCProcedurePointerSetAtOffsetInteger64Bit,           NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetAtOffsetUnsignedInteger64Bit",   _gsCProcedurePointerSetAtOffsetUnsignedInteger64Bit,   NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetRaw8Bit",                        _gsCProcedurePointerGetRaw8Bit,                        NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetRaw16Bit",                       _gsCProcedurePointerGetRaw16Bit,                       NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetRaw32Bit",                       _gsCProcedurePointerGetRaw32Bit,                       NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetRaw64Bit",                       _gsCProcedurePointerGetRaw64Bit,                       NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetRaw8Bit",                        _gsCProcedurePointerSetRaw8Bit,                        NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetRaw16Bit",                       _gsCProcedurePointerSetRaw16Bit,                       NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetRaw32Bit",                       _gsCProcedurePointerSetRaw32Bit,                       NULL);
      mape_set_native_function(1, gApeThread2, "pointerSetRaw64Bit",                       _gsCProcedurePointerSetRaw64Bit,                       NULL);
      mape_set_native_function(1, gApeThread2, "pointerIsNull",                            _gsCProcedurePointerIsNull,                            NULL);
      mape_set_native_function(1, gApeThread2, "pointerGetNull",                           _gsCProcedurePointerGetNull,                           NULL);
      mape_set_native_function(1, gApeThread2, "pointersAreEqual",                         _gsCProcedurePointersAreEqual,                         NULL);
      mape_set_native_function(1, gApeThread2, "pointerOffsetByBytes",                     _gsCProcedurePointerOffsetByBytes,                     NULL);
      mape_set_native_function(1, gApeThread2, "dynamicArrayGet",                          _gsCProcedureDynamicArrayGet,                          NULL);
      mape_set_native_function(1, gApeThread2, "dynamicArraySet",                          _gsCProcedureDynamicArraySet,                          NULL);
      mape_set_native_function(1, gApeThread2, "dynamicArrayAppend",                       _gsCProcedureDynamicArrayAppend,                       NULL);
      mape_set_native_function(1, gApeThread2, "dynamicArrayRemoveAt",                     _gsCProcedureDynamicArrayRemoveAt,                     NULL);
      mape_set_native_function(1, gApeThread2, "dynamicArrayRemoveLast",                   _gsCProcedureDynamicArrayRemoveLast,                   NULL);
      mape_set_native_function(1, gApeThread2, "dynamicArrayGetSize",                      _gsCProcedureDynamicArrayGetSize,                      NULL);
      mape_set_native_function(1, gApeThread2, "memset",                                   _gsCProcedureMemset,                                   NULL);
      mape_set_native_function(1, gApeThread2, "memcpy",                                   _gsCProcedureMemcpy,                                   NULL);
      mape_set_native_function(1, gApeThread2, "memcmp",                                   _gsCProcedureMemcmp,                                   NULL);
      mape_set_native_function(1, gApeThread2, "threadSafeMemset",                         _gsCProcedureThreadSafeMemset,                         NULL); // Thread-safe memory.
      mape_set_native_function(1, gApeThread2, "threadSafeMemcpy",                         _gsCProcedureThreadSafeMemcpy,                         NULL); // Thread-safe memory.
      mape_set_native_function(1, gApeThread2, "threadSafeMemcmp",                         _gsCProcedureThreadSafeMemcmp,                         NULL); // Thread-safe memory.
      mape_set_native_function(1, gApeThread2, "threadWaitForEqualUint64Value",            _gsCProcedureThreadWaitForEqualUint64Value,            NULL); // Thread-safe memory.
      mape_set_native_function(1, gApeThread2, "threadWaitForEqualOrMoreThanUint64Value",  _gsCProcedureThreadWaitForEqualOrMoreThanUint64Value,  NULL); // Thread-safe memory.
      mape_set_native_function(1, gApeThread2, "threadWaitForThread1FrameToFinish",        _gsCProcedureThreadWaitForThread1FrameToFinish,        NULL);
      mape_set_native_function(1, gApeThread2, "strlenWithNullChar",                       _gsCProcedureStrlenWithNullChar,                       NULL);
      mape_set_native_function(1, gApeThread2, "boolToNumber",                             _gsCProcedureBoolToNumber,                             NULL);
      mape_set_native_function(1, gApeThread2, "boolToString",                             _gsCProcedureBoolToString,                             NULL);
      mape_set_native_function(1, gApeThread2, "numberFromRaw8BitInteger",                 _gsCProcedureNumberFromRaw8BitInteger,                 NULL);
      mape_set_native_function(1, gApeThread2, "numberFromRaw8BitUnsignedInteger",         _gsCProcedureNumberFromRaw8BitUnsignedInteger,         NULL);
      mape_set_native_function(1, gApeThread2, "numberFromRaw16BitInteger",                _gsCProcedureNumberFromRaw16BitInteger,                NULL);
      mape_set_native_function(1, gApeThread2, "numberFromRaw16BitUnsignedInteger",        _gsCProcedureNumberFromRaw16BitUnsignedInteger,        NULL);
      mape_set_native_function(1, gApeThread2, "numberFromRaw32BitInteger",                _gsCProcedureNumberFromRaw32BitInteger,                NULL);
      mape_set_native_function(1, gApeThread2, "numberFromRaw32BitUnsignedInteger",        _gsCProcedureNumberFromRaw32BitUnsignedInteger,        NULL);
      mape_set_native_function(1, gApeThread2, "numberFromRaw32BitFloat",                  _gsCProcedureNumberFromRaw32BitFloat,                  NULL);
      mape_set_native_function(1, gApeThread2, "numberFromRaw64BitInteger",                _gsCProcedureNumberFromRaw64BitInteger,                NULL);
      mape_set_native_function(1, gApeThread2, "numberFromRaw64BitUnsignedInteger",        _gsCProcedureNumberFromRaw64BitUnsignedInteger,        NULL);
      mape_set_native_function(1, gApeThread2, "numberToBool",                             _gsCProcedureNumberToBool,                             NULL);
      mape_set_native_function(1, gApeThread2, "numberToString",                           _gsCProcedureNumberToString,                           NULL);
      mape_set_native_function(1, gApeThread2, "numberToBinaryString",                     _gsCProcedureNumberToBinaryString,                     NULL);
      mape_set_native_function(1, gApeThread2, "numberWholePartToString",                  _gsCProcedureNumberWholePartToString,                  NULL);
      mape_set_native_function(1, gApeThread2, "stringCharToNumber",                       _gsCProcedureStringCharToNumber,                       NULL);
      mape_set_native_function(1, gApeThread2, "stringToNumberArray",                      _gsCProcedureStringToNumberArray,                      NULL);
      mape_set_native_function(1, gApeThread2, "interpretStringToInteger",                 _gsCProcedureInterpretStringToInteger,                 NULL);
      mape_set_native_function(1, gApeThread2, "interpretStringToFloat",                   _gsCProcedureInterpretStringToFloat,                   NULL);
      mape_set_native_function(1, gApeThread2, "interpretStringToDouble",                  _gsCProcedureInterpretStringToDouble,                  NULL);
      mape_set_native_function(1, gApeThread2, "stringReadFromFile",                       _gsCProcedureStringReadFromFile,                       NULL);
      mape_set_native_function(1, gApeThread2, "stringWriteToFile",                        _gsCProcedureStringWriteToFile,                        NULL);
      mape_set_native_function(1, gApeThread2, "stringAppendToFile",                       _gsCProcedureStringAppendToFile,                       NULL);
      mape_set_native_function(1, gApeThread2, "binaryGetByteSizeOfFile",                  _gsCProcedureBinaryGetByteSizeOfFile,                  NULL);
      mape_set_native_function(1, gApeThread2, "binaryReadFromFile",                       _gsCProcedureBinaryReadFromFile,                       NULL);
      mape_set_native_function(1, gApeThread2, "binaryWriteToFile",                        _gsCProcedureBinaryWriteToFile,                        NULL);
      mape_set_native_function(1, gApeThread2, "meshGetVerticesCount",                     _gsCProcedureMeshGetVerticesCount,                     NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshGetColorsCount",                       _gsCProcedureMeshGetColorsCount,                       NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshGetTexCoordsCount",                    _gsCProcedureMeshGetTexCoordsCount,                    NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshGetIndicesCount",                      _gsCProcedureMeshGetIndicesCount,                      NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshAddVertex",                            _gsCProcedureMeshAddVertex,                            NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshAddColor",                             _gsCProcedureMeshAddColor,                             NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshAddTexCoord",                          _gsCProcedureMeshAddTexCoord,                          NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshAddIndex",                             _gsCProcedureMeshAddIndex,                             NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshRemoveVertex",                         _gsCProcedureMeshRemoveVertex,                         NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshRemoveColor",                          _gsCProcedureMeshRemoveColor,                          NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshRemoveTexCoord",                       _gsCProcedureMeshRemoveTexCoord,                       NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshRemoveIndex",                          _gsCProcedureMeshRemoveIndex,                          NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshClear",                                _gsCProcedureMeshClear,                                NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshClearVertices",                        _gsCProcedureMeshClearVertices,                        NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshClearColors",                          _gsCProcedureMeshClearColors,                          NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshClearTexCoords",                       _gsCProcedureMeshClearTexCoords,                       NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshClearIndices",                         _gsCProcedureMeshClearIndices,                         NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshGetVerticesPointer",                   _gsCProcedureMeshGetVerticesPointer,                   NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshGetColorsPointer",                     _gsCProcedureMeshGetColorsPointer,                     NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshGetTexCoordsPointer",                  _gsCProcedureMeshGetTexCoordsPointer,                  NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshGetIndicesPointer",                    _gsCProcedureMeshGetIndicesPointer,                    NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshMergeDuplicateVertices",               _gsCProcedureMeshMergeDuplicateVertices,               NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshSetupIndicesAuto",                     _gsCProcedureMeshSetupIndicesAuto,                     NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "meshAddTriangle",                          _gsCProcedureMeshAddTriangle,                          NULL); // Two threads must not access the same mesh handle at the same time.
      mape_set_native_function(1, gApeThread2, "imageGetWidth",                            _gsCProcedureImageGetWidth,                            NULL); // Two threads must not access the same image handle at the same time.
      mape_set_native_function(1, gApeThread2, "imageGetHeight",                           _gsCProcedureImageGetHeight,                           NULL); // Two threads must not access the same image handle at the same time.
      mape_set_native_function(1, gApeThread2, "imageGetBitsPerPixel",                     _gsCProcedureImageGetBitsPerPixel,                     NULL); // Two threads must not access the same image handle at the same time.
      mape_set_native_function(1, gApeThread2, "imageGetImageType",                        _gsCProcedureImageGetImageType,                        NULL); // Two threads must not access the same image handle at the same time.
      mape_set_native_function(1, gApeThread2, "imageGetPixelsPointer",                    _gsCProcedureImageGetPixelsPointer,                    NULL); // Two threads must not access the same image handle at the same time.
      mape_set_native_function(1, gApeThread2, "profileBegin",                             _gsCProcedureProfileBegin,                             NULL); // Thread-safe.
      mape_set_native_function(1, gApeThread2, "profileEnd",                               _gsCProcedureProfileEnd,                               NULL); // Thread-safe.
      mape_set_native_function(1, gApeThread2, "systemCommand",                            _gsCProcedureSystemCommand,                            NULL);
      mape_set_native_function(1, gApeThread2, "getUniqueNumber",                          _gsCProcedureGetUniqueNumber,                          NULL); // Thread-safe.
      mape_set_native_function(1, gApeThread2, "getUint64Max",                             _gsCProcedureGetUint64Max,                             NULL); // Thread-safe.
      mape_set_native_function(1, gApeThread2, "getLibGameHandle",                         _gsCProcedureGetLibGameHandle,                         NULL);
      mape_set_native_function(1, gApeThread2, "getLibThread2Handle",                      _gsCProcedureGetLibThread2Handle,                      NULL);
      mape_set_native_function(1, gApeThread2, "getGlfwWindowHandle",                      _gsCProcedureGetGlfwWindowHandle,                      NULL);
      mape_set_native_function(1, gApeThread2, "getLastDragAndDropCounter",                _gsCProcedureGetLastDragAndDropCounter,                NULL);
      mape_set_native_function(1, gApeThread2, "getLastDragAndDropFilepathsCount",         _gsCProcedureGetLastDragAndDropFilepathsCount,         NULL);
      mape_set_native_function(1, gApeThread2, "getLastDragAndDropFilepath",               _gsCProcedureGetLastDragAndDropFilepath,               NULL);
      mape_set_native_function(1, gApeThread2, "getLastDragAndDropPositionX",              _gsCProcedureGetLastDragAndDropPositionX,              NULL);
      mape_set_native_function(1, gApeThread2, "getLastDragAndDropPositionY",              _gsCProcedureGetLastDragAndDropPositionY,              NULL);
      mape_set_native_function(1, gApeThread2, "githubR_lyehLz4xEncode",                        _gsCProcedureGithubR_lyehLz4xEncode,                        NULL);
      mape_set_native_function(1, gApeThread2, "githubR_lyehLz4xDecode",                        _gsCProcedureGithubR_lyehLz4xDecode,                        NULL);
      mape_set_native_function(1, gApeThread2, "githubR_lyehLz4xBoundsEncodeOutBytesCount",     _gsCProcedureGithubR_lyehLz4xBoundsEncodeOutBytesCount,     NULL);
      mape_set_native_function(1, gApeThread2, "githubR_lyehUlzEncode",                         _gsCProcedureGithubR_lyehUlzEncode,                         NULL);
      mape_set_native_function(1, gApeThread2, "githubR_lyehUlzDecode",                         _gsCProcedureGithubR_lyehUlzDecode,                         NULL);
      mape_set_native_function(1, gApeThread2, "githubR_lyehUlzBoundsEncodeOutBytesCount",      _gsCProcedureGithubR_lyehUlzBoundsEncodeOutBytesCount,      NULL);
      mape_set_native_function(1, gApeThread2, "getThread2ScriptString",                        _gsCProcedureGetThread2ScriptString,                        NULL);
      mape_set_native_function(1, gApeThread2, "setThread2ScriptStringForNextFrame",            _gsCProcedureSetThread2ScriptStringForNextFrame,            NULL);
      mape_set_native_function(1, gApeThread2, "setThread2ScriptStringForNextFrameFromPointer", _gsCProcedureSetThread2ScriptStringForNextFrameFromPointer, NULL);
      mape_set_native_function(1, gApeThread2, "libGameScriptExternalProcedureCall2",           _gsCProcedureLibGameScriptExternalProcedureCall2,           NULL);
      mape_set_native_function(1, gApeThread2, "libGameScriptExternalProcedureCall3",           _gsCProcedureLibGameScriptExternalProcedureCall3,           NULL);
      mape_set_native_function(1, gApeThread2, "asin",                                          _gsCProcedureAsin,                                          NULL);
      mape_set_native_function(1, gApeThread2, "acos",                                          _gsCProcedureAcos,                                          NULL);
      mape_set_native_function(1, gApeThread2, "atan",                                          _gsCProcedureAtan,                                          NULL);
      mape_set_native_function(1, gApeThread2, "atan2",                                         _gsCProcedureAtan2,                                         NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesGetCount",                                          _gsCProcedureGlobalMeshesGetCount,                                          NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesPersistentGetCount",                                _gsCProcedureGlobalMeshesPersistentGetCount,                                NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesGetMeshLabelByMeshIndex",                           _gsCProcedureGlobalMeshesGetMeshLabelByMeshIndex,                           NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesPersistentGetMeshLabelByMeshIndex",                 _gsCProcedureGlobalMeshesPersistentGetMeshLabelByMeshIndex,                 NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesGetMeshHandleByMeshIndex",                          _gsCProcedureGlobalMeshesGetMeshHandleByMeshIndex,                          NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesPersistentGetMeshHandleByMeshIndex",                _gsCProcedureGlobalMeshesPersistentGetMeshHandleByMeshIndex,                NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesGetHaveVerticesChangedMeshIndexesCount",            _gsCProcedureGlobalMeshesGetHaveVerticesChangedMeshIndexesCount,            NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesGetHaveColorsChangedMeshIndexesCount",              _gsCProcedureGlobalMeshesGetHaveColorsChangedMeshIndexesCount,              NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesGetHaveTexCoordsChangedMeshIndexesCount",           _gsCProcedureGlobalMeshesGetHaveTexCoordsChangedMeshIndexesCount,           NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesGetHaveIndicesChangedMeshIndexesCount",             _gsCProcedureGlobalMeshesGetHaveIndicesChangedMeshIndexesCount,             NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesPersistentGetHaveVerticesChangedMeshIndexesCount",  _gsCProcedureGlobalMeshesPersistentGetHaveVerticesChangedMeshIndexesCount,  NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesPersistentGetHaveColorsChangedMeshIndexesCount",    _gsCProcedureGlobalMeshesPersistentGetHaveColorsChangedMeshIndexesCount,    NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesPersistentGetHaveTexCoordsChangedMeshIndexesCount", _gsCProcedureGlobalMeshesPersistentGetHaveTexCoordsChangedMeshIndexesCount, NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesPersistentGetHaveIndicesChangedMeshIndexesCount",   _gsCProcedureGlobalMeshesPersistentGetHaveIndicesChangedMeshIndexesCount,   NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesGetHaveVerticesChangedMeshIndexes",                 _gsCProcedureGlobalMeshesGetHaveVerticesChangedMeshIndexes,                 NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesGetHaveColorsChangedMeshIndexes",                   _gsCProcedureGlobalMeshesGetHaveColorsChangedMeshIndexes,                   NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesGetHaveTexCoordsChangedMeshIndexes",                _gsCProcedureGlobalMeshesGetHaveTexCoordsChangedMeshIndexes,                NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesGetHaveIndicesChangedMeshIndexes",                  _gsCProcedureGlobalMeshesGetHaveIndicesChangedMeshIndexes,                  NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesPersistentGetHaveVerticesChangedMeshIndexes",       _gsCProcedureGlobalMeshesPersistentGetHaveVerticesChangedMeshIndexes,       NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesPersistentGetHaveColorsChangedMeshIndexes",         _gsCProcedureGlobalMeshesPersistentGetHaveColorsChangedMeshIndexes,         NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesPersistentGetHaveTexCoordsChangedMeshIndexes",      _gsCProcedureGlobalMeshesPersistentGetHaveTexCoordsChangedMeshIndexes,      NULL);
      mape_set_native_function(1, gApeThread2, "globalMeshesPersistentGetHaveIndicesChangedMeshIndexes",        _gsCProcedureGlobalMeshesPersistentGetHaveIndicesChangedMeshIndexes,        NULL);
      mape_set_native_function(1, gApeThread2, "globalKeyPropertyGetKeyLabelsCount",                            _gsCProcedureGlobalKeyPropertyGetKeyLabelsCount,                            NULL);
      mape_set_native_function(1, gApeThread2, "globalKeyPropertyIsKeyLabelExists",                             _gsCProcedureGlobalKeyPropertyIsKeyLabelExists,                             NULL);
      mape_set_native_function(1, gApeThread2, "globalKeyPropertyGetKeyLabelByKeyIndex",                        _gsCProcedureGlobalKeyPropertyGetKeyLabelByKeyIndex,                        NULL);
      mape_set_native_function(1, gApeThread2, "globalKeyPropertyGetKeyPropertyLabelsCount",                    _gsCProcedureGlobalKeyPropertyGetKeyPropertyLabelsCount,                    NULL);
      mape_set_native_function(1, gApeThread2, "globalKeyPropertyIsKeyPropertyLabelExists",                     _gsCProcedureGlobalKeyPropertyIsKeyPropertyLabelExists,                     NULL);
      mape_set_native_function(1, gApeThread2, "globalKeyPropertyGetKeyPropertyLabelByPropertyIndex",           _gsCProcedureGlobalKeyPropertyGetKeyPropertyLabelByPropertyIndex,           NULL);
      mape_set_native_function(1, gApeThread2, "globalKeyPropertyRemoveKey",                                    _gsCProcedureGlobalKeyPropertyRemoveKey,                                    NULL);
      mape_set_native_function(1, gApeThread2, "globalKeyPropertyRemoveAllKeys",                                _gsCProcedureGlobalKeyPropertyRemoveAllKeys,                                NULL);
      mape_set_native_function(1, gApeThread2, "globalKeyPropertyRemoveProperty",                               _gsCProcedureGlobalKeyPropertyRemoveProperty,                               NULL);
      mape_set_native_function(1, gApeThread2, "globalKeyPropertyRemoveAllProperties",                          _gsCProcedureGlobalKeyPropertyRemoveAllProperties,                          NULL);
      mape_set_native_function(1, gApeThread2, "globalKeyPropertySetString",                                    _gsCProcedureGlobalKeyPropertySetString,                                    NULL);
      mape_set_native_function(1, gApeThread2, "globalKeyPropertySetNumber",                                    _gsCProcedureGlobalKeyPropertySetNumber,                                    NULL);
      mape_set_native_function(1, gApeThread2, "globalKeyPropertySetBool",                                      _gsCProcedureGlobalKeyPropertySetBool,                                      NULL);
      mape_set_native_function(1, gApeThread2, "globalKeyPropertyGetString",                                    _gsCProcedureGlobalKeyPropertyGetString,                                    NULL);
      mape_set_native_function(1, gApeThread2, "globalKeyPropertyGetNumber",                                    _gsCProcedureGlobalKeyPropertyGetNumber,                                    NULL);
      mape_set_native_function(1, gApeThread2, "globalKeyPropertyGetBool",                                      _gsCProcedureGlobalKeyPropertyGetBool,                                      NULL);
      if (gEmbreeIsEnabled == 1) {
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fGetSizeOfInBytes",            _gsCProcedureErtAffineSpace3fGetSizeOfInBytes,              NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fSetDefaultInitialize",        _gsCProcedureErtAffineSpace3fSetDefaultInitialize,          NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fSetInitialize",               _gsCProcedureErtAffineSpace3fSetInitialize,                 NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fSetLookAtPoint",              _gsCProcedureErtAffineSpace3fSetLookAtPoint,                NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fScale",                       _gsCProcedureErtAffineSpace3fScale,                         NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fTranslate",                   _gsCProcedureErtAffineSpace3fTranslate,                     NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fRotate",                      _gsCProcedureErtAffineSpace3fRotate,                        NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fGetLVXX",                     _gsCProcedureErtAffineSpace3fGetLVXX,                       NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fGetLVXY",                     _gsCProcedureErtAffineSpace3fGetLVXY,                       NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fGetLVXZ",                     _gsCProcedureErtAffineSpace3fGetLVXZ,                       NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fGetLVYX",                     _gsCProcedureErtAffineSpace3fGetLVYX,                       NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fGetLVYY",                     _gsCProcedureErtAffineSpace3fGetLVYY,                       NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fGetLVYZ",                     _gsCProcedureErtAffineSpace3fGetLVYZ,                       NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fGetLVZX",                     _gsCProcedureErtAffineSpace3fGetLVZX,                       NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fGetLVZY",                     _gsCProcedureErtAffineSpace3fGetLVZY,                       NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fGetLVZZ",                     _gsCProcedureErtAffineSpace3fGetLVZZ,                       NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fGetPX",                       _gsCProcedureErtAffineSpace3fGetPX,                         NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fGetPY",                       _gsCProcedureErtAffineSpace3fGetPY,                         NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fGetPZ",                       _gsCProcedureErtAffineSpace3fGetPZ,                         NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fCopyFromArray",               _gsCProcedureErtAffineSpace3fCopyFromArray,                 NULL);
        mape_set_native_function(1, gApeThread2, "ertAffineSpace3fCopyToArray",                 _gsCProcedureErtAffineSpace3fCopyToArray,                   NULL);
        mape_set_native_function(1, gApeThread2, "ertCreateDevice",                             _gsCProcedureErtCreateDevice,                               NULL);
        mape_set_native_function(1, gApeThread2, "ertDestroyDevice",                            _gsCProcedureErtDestroyDevice,                              NULL);
        mape_set_native_function(1, gApeThread2, "ertNewCamera",                                _gsCProcedureErtNewCamera,                                  NULL);
        mape_set_native_function(1, gApeThread2, "ertNewData",                                  _gsCProcedureErtNewData,                                    NULL);
        mape_set_native_function(1, gApeThread2, "ertNewDataFromFile",                          _gsCProcedureErtNewDataFromFile,                            NULL);
        mape_set_native_function(1, gApeThread2, "ertNewImage",                                 _gsCProcedureErtNewImage,                                   NULL);
        mape_set_native_function(1, gApeThread2, "ertNewImageFromFile",                         _gsCProcedureErtNewImageFromFile,                           NULL);
        mape_set_native_function(1, gApeThread2, "ertNewTexture",                               _gsCProcedureErtNewTexture,                                 NULL);
        mape_set_native_function(1, gApeThread2, "ertNewMaterial",                              _gsCProcedureErtNewMaterial,                                NULL);
        mape_set_native_function(1, gApeThread2, "ertNewShape",                                 _gsCProcedureErtNewShape,                                   NULL);
        mape_set_native_function(1, gApeThread2, "ertNewLight",                                 _gsCProcedureErtNewLight,                                   NULL);
        mape_set_native_function(1, gApeThread2, "ertNewShapePrimitive",                        _gsCProcedureErtNewShapePrimitive,                          NULL);
        mape_set_native_function(1, gApeThread2, "ertNewLightPrimitive",                        _gsCProcedureErtNewLightPrimitive,                          NULL);
        mape_set_native_function(1, gApeThread2, "ertTransformPrimitive",                       _gsCProcedureErtTransformPrimitive,                         NULL);
        mape_set_native_function(1, gApeThread2, "ertNewScene",                                 _gsCProcedureErtNewScene,                                   NULL);
        mape_set_native_function(1, gApeThread2, "ertNewToneMapper",                            _gsCProcedureErtNewToneMapper,                              NULL);
        mape_set_native_function(1, gApeThread2, "ertNewRenderer",                              _gsCProcedureErtNewRenderer,                                NULL);
        mape_set_native_function(1, gApeThread2, "ertNewFrameBuffer",                           _gsCProcedureErtNewFrameBuffer,                             NULL);
        mape_set_native_function(1, gApeThread2, "ertGetFrameBufferWidth",                      _gsCProcedureErtGetFrameBufferWidth,                        NULL);
        mape_set_native_function(1, gApeThread2, "ertGetFrameBufferHeight",                     _gsCProcedureErtGetFrameBufferHeight,                       NULL);
        mape_set_native_function(1, gApeThread2, "ertMapFrameBuffer",                           _gsCProcedureErtMapFrameBuffer,                             NULL);
        mape_set_native_function(1, gApeThread2, "ertUnmapFrameBuffer",                         _gsCProcedureErtUnmapFrameBuffer,                           NULL);
        mape_set_native_function(1, gApeThread2, "ertSwapBuffers",                              _gsCProcedureErtSwapBuffers,                                NULL);
        mape_set_native_function(1, gApeThread2, "ertIncRef",                                   _gsCProcedureErtIncRef,                                     NULL);
        mape_set_native_function(1, gApeThread2, "ertDecRef",                                   _gsCProcedureErtDecRef,                                     NULL);
        mape_set_native_function(1, gApeThread2, "ertSetBool1",                                 _gsCProcedureErtSetBool1,                                   NULL);
        mape_set_native_function(1, gApeThread2, "ertSetBool2",                                 _gsCProcedureErtSetBool2,                                   NULL);
        mape_set_native_function(1, gApeThread2, "ertSetBool3",                                 _gsCProcedureErtSetBool3,                                   NULL);
        mape_set_native_function(1, gApeThread2, "ertSetBool4",                                 _gsCProcedureErtSetBool4,                                   NULL);
        mape_set_native_function(1, gApeThread2, "ertSetInt1",                                  _gsCProcedureErtSetInt1,                                    NULL);
        mape_set_native_function(1, gApeThread2, "ertSetInt2",                                  _gsCProcedureErtSetInt2,                                    NULL);
        mape_set_native_function(1, gApeThread2, "ertSetInt3",                                  _gsCProcedureErtSetInt3,                                    NULL);
        mape_set_native_function(1, gApeThread2, "ertSetInt4",                                  _gsCProcedureErtSetInt4,                                    NULL);
        mape_set_native_function(1, gApeThread2, "ertSetFloat1",                                _gsCProcedureErtSetFloat1,                                  NULL);
        mape_set_native_function(1, gApeThread2, "ertSetFloat2",                                _gsCProcedureErtSetFloat2,                                  NULL);
        mape_set_native_function(1, gApeThread2, "ertSetFloat3",                                _gsCProcedureErtSetFloat3,                                  NULL);
        mape_set_native_function(1, gApeThread2, "ertSetFloat4",                                _gsCProcedureErtSetFloat4,                                  NULL);
        mape_set_native_function(1, gApeThread2, "ertSetArray",                                 _gsCProcedureErtSetArray,                                   NULL);
        mape_set_native_function(1, gApeThread2, "ertSetString",                                _gsCProcedureErtSetString,                                  NULL);
        mape_set_native_function(1, gApeThread2, "ertSetImage",                                 _gsCProcedureErtSetImage,                                   NULL);
        mape_set_native_function(1, gApeThread2, "ertSetTexture",                               _gsCProcedureErtSetTexture,                                 NULL);
        mape_set_native_function(1, gApeThread2, "ertSetTransform",                             _gsCProcedureErtSetTransform,                               NULL);
        mape_set_native_function(1, gApeThread2, "ertClear",                                    _gsCProcedureErtClear,                                      NULL);
        mape_set_native_function(1, gApeThread2, "ertCommit",                                   _gsCProcedureErtCommit,                                     NULL);
        mape_set_native_function(1, gApeThread2, "ertRenderFrame",                              _gsCProcedureErtRenderFrame,                                NULL);
        mape_set_native_function(1, gApeThread2, "ertPick",                                     _gsCProcedureErtPick,                                       NULL);
        mape_set_native_function(1, gApeThread2, "ertInitializeRayStruct",                      _gsCProcedureErtInitializeRayStruct,                        NULL);
        mape_set_native_function(1, gApeThread2, "ertInitializeRayStructForCameraPixelSample",  _gsCProcedureErtInitializeRayStructForCameraPixelSample,    NULL);
        mape_set_native_function(1, gApeThread2, "ertSceneIntersectRayStructToHitStruct",       _gsCProcedureErtSceneIntersectRayStructToHitStruct,         NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallErtDecRef",                        _gsCProcedureOnRerunCallErtDecRef,                          NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallErtDestroyDevice",                 _gsCProcedureOnRerunCallErtDestroyDevice,                   NULL);
      }
      if (gRedGpuIsEnabled == 1) {
        mape_set_native_function(1, gApeThread2, "getRedStructsCount",                          _gsCProcedureGetRedStructsCount,                            NULL);
        mape_set_native_function(1, gApeThread2, "getRedStructName",                            _gsCProcedureGetRedStructName,                              NULL);
        mape_set_native_function(1, gApeThread2, "getRedStructMembersCount",                    _gsCProcedureGetRedStructMembersCount,                      NULL);
        mape_set_native_function(1, gApeThread2, "getRedStructMemberName",                      _gsCProcedureGetRedStructMemberName,                        NULL);
        mape_set_native_function(1, gApeThread2, "redStructSizeof",                             _gsCProcedureRedStructSizeof,                               NULL);
        mape_set_native_function(1, gApeThread2, "redStructMemberSizeof",                       _gsCProcedureRedStructMemberSizeof,                         NULL);
        mape_set_native_function(1, gApeThread2, "redStructMemberOffsetof",                     _gsCProcedureRedStructMemberOffsetof,                       NULL);
        mape_set_native_function(1, gApeThread2, "redStructMemberTypeof",                       _gsCProcedureRedStructMemberTypeof,                         NULL);
        mape_set_native_function(1, gApeThread2, "redCreateContext",                            _gsCProcedureRedCreateContext,                              NULL);
        mape_set_native_function(1, gApeThread2, "redCreateContextWithRayTracingFeatureLevel1", _gsCProcedureRedCreateContextWithRayTracingFeatureLevel1,   NULL);
        mape_set_native_function(1, gApeThread2, "redCreateContextWithRayTracingFeatureLevel2", _gsCProcedureRedCreateContextWithRayTracingFeatureLevel2,   NULL);
        mape_set_native_function(1, gApeThread2, "redHandleContextGetProcAddr",                 _gsCProcedureRedHandleContextGetProcAddr,                   NULL);
        mape_set_native_function(1, gApeThread2, "redMemoryGetBudget",                          _gsCProcedureRedMemoryGetBudget,                            NULL);
        mape_set_native_function(1, gApeThread2, "redMemoryAllocate",                           _gsCProcedureRedMemoryAllocate,                             NULL);
        mape_set_native_function(1, gApeThread2, "redMemoryAllocateMappable",                   _gsCProcedureRedMemoryAllocateMappable,                     NULL);
        mape_set_native_function(1, gApeThread2, "redMemoryFree",                               _gsCProcedureRedMemoryFree,                                 NULL);
        mape_set_native_function(1, gApeThread2, "redMemorySet",                                _gsCProcedureRedMemorySet,                                  NULL);
        mape_set_native_function(1, gApeThread2, "redMemoryMap",                                _gsCProcedureRedMemoryMap,                                  NULL);
        mape_set_native_function(1, gApeThread2, "redMemoryUnmap",                              _gsCProcedureRedMemoryUnmap,                                NULL);
        mape_set_native_function(1, gApeThread2, "redMemoryNonCoherentFlush",                   _gsCProcedureRedMemoryNonCoherentFlush,                     NULL);
        mape_set_native_function(1, gApeThread2, "redMemoryNonCoherentInvalidate",              _gsCProcedureRedMemoryNonCoherentInvalidate,                NULL);
        mape_set_native_function(1, gApeThread2, "redStructsMemoryAllocate",                    _gsCProcedureRedStructsMemoryAllocate,                      NULL);
        mape_set_native_function(1, gApeThread2, "redStructsMemoryAllocateSamplers",            _gsCProcedureRedStructsMemoryAllocateSamplers,              NULL);
        mape_set_native_function(1, gApeThread2, "redStructsMemorySuballocateStructs",          _gsCProcedureRedStructsMemorySuballocateStructs,            NULL);
        mape_set_native_function(1, gApeThread2, "redStructsMemoryReset",                       _gsCProcedureRedStructsMemoryReset,                         NULL);
        mape_set_native_function(1, gApeThread2, "redStructsMemoryFree",                        _gsCProcedureRedStructsMemoryFree,                          NULL);
        mape_set_native_function(1, gApeThread2, "redStructsSet",                               _gsCProcedureRedStructsSet,                                 NULL);
        mape_set_native_function(1, gApeThread2, "redCreateArray",                              _gsCProcedureRedCreateArray,                                NULL);
        mape_set_native_function(1, gApeThread2, "redCreateImage",                              _gsCProcedureRedCreateImage,                                NULL);
        mape_set_native_function(1, gApeThread2, "redCreateSampler",                            _gsCProcedureRedCreateSampler,                              NULL);
        mape_set_native_function(1, gApeThread2, "redCreateTexture",                            _gsCProcedureRedCreateTexture,                              NULL);
        mape_set_native_function(1, gApeThread2, "redCreateGpuCode",                            _gsCProcedureRedCreateGpuCode,                              NULL);
        mape_set_native_function(1, gApeThread2, "redCreateOutputDeclaration",                  _gsCProcedureRedCreateOutputDeclaration,                    NULL);
        mape_set_native_function(1, gApeThread2, "redCreateStructDeclaration",                  _gsCProcedureRedCreateStructDeclaration,                    NULL);
        mape_set_native_function(1, gApeThread2, "redCreateProcedureParameters",                _gsCProcedureRedCreateProcedureParameters,                  NULL);
        mape_set_native_function(1, gApeThread2, "redCreateProcedureCache",                     _gsCProcedureRedCreateProcedureCache,                       NULL);
        mape_set_native_function(1, gApeThread2, "redCreateProcedure",                          _gsCProcedureRedCreateProcedure,                            NULL);
        mape_set_native_function(1, gApeThread2, "redCreateProcedureCompute",                   _gsCProcedureRedCreateProcedureCompute,                     NULL);
        mape_set_native_function(1, gApeThread2, "redCreateOutput",                             _gsCProcedureRedCreateOutput,                               NULL);
        mape_set_native_function(1, gApeThread2, "redCreateCpuSignal",                          _gsCProcedureRedCreateCpuSignal,                            NULL);
        mape_set_native_function(1, gApeThread2, "redCreateGpuSignal",                          _gsCProcedureRedCreateGpuSignal,                            NULL);
        mape_set_native_function(1, gApeThread2, "redCreateGpuToCpuSignal",                     _gsCProcedureRedCreateGpuToCpuSignal,                       NULL);
        mape_set_native_function(1, gApeThread2, "redCreateCalls",                              _gsCProcedureRedCreateCalls,                                NULL);
        mape_set_native_function(1, gApeThread2, "redCreateCallsReusable",                      _gsCProcedureRedCreateCallsReusable,                        NULL);
        mape_set_native_function(1, gApeThread2, "redDestroyContext",                           _gsCProcedureRedDestroyContext,                             NULL);
        mape_set_native_function(1, gApeThread2, "redDestroyArray",                             _gsCProcedureRedDestroyArray,                               NULL);
        mape_set_native_function(1, gApeThread2, "redDestroyImage",                             _gsCProcedureRedDestroyImage,                               NULL);
        mape_set_native_function(1, gApeThread2, "redDestroySampler",                           _gsCProcedureRedDestroySampler,                             NULL);
        mape_set_native_function(1, gApeThread2, "redDestroyTexture",                           _gsCProcedureRedDestroyTexture,                             NULL);
        mape_set_native_function(1, gApeThread2, "redDestroyGpuCode",                           _gsCProcedureRedDestroyGpuCode,                             NULL);
        mape_set_native_function(1, gApeThread2, "redDestroyOutputDeclaration",                 _gsCProcedureRedDestroyOutputDeclaration,                   NULL);
        mape_set_native_function(1, gApeThread2, "redDestroyStructDeclaration",                 _gsCProcedureRedDestroyStructDeclaration,                   NULL);
        mape_set_native_function(1, gApeThread2, "redDestroyProcedureParameters",               _gsCProcedureRedDestroyProcedureParameters,                 NULL);
        mape_set_native_function(1, gApeThread2, "redDestroyProcedureCache",                    _gsCProcedureRedDestroyProcedureCache,                      NULL);
        mape_set_native_function(1, gApeThread2, "redDestroyProcedure",                         _gsCProcedureRedDestroyProcedure,                           NULL);
        mape_set_native_function(1, gApeThread2, "redDestroyOutput",                            _gsCProcedureRedDestroyOutput,                              NULL);
        mape_set_native_function(1, gApeThread2, "redDestroyCpuSignal",                         _gsCProcedureRedDestroyCpuSignal,                           NULL);
        mape_set_native_function(1, gApeThread2, "redDestroyGpuSignal",                         _gsCProcedureRedDestroyGpuSignal,                           NULL);
        mape_set_native_function(1, gApeThread2, "redDestroyGpuToCpuSignal",                    _gsCProcedureRedDestroyGpuToCpuSignal,                      NULL);
        mape_set_native_function(1, gApeThread2, "redDestroyCalls",                             _gsCProcedureRedDestroyCalls,                               NULL);
        mape_set_native_function(1, gApeThread2, "redProcedureCacheGetBlob",                    _gsCProcedureRedProcedureCacheGetBlob,                      NULL);
        mape_set_native_function(1, gApeThread2, "redProcedureCacheMergeCaches",                _gsCProcedureRedProcedureCacheMergeCaches,                  NULL);
        mape_set_native_function(1, gApeThread2, "redCpuSignalGetStatus",                       _gsCProcedureRedCpuSignalGetStatus,                         NULL);
        mape_set_native_function(1, gApeThread2, "redCpuSignalWait",                            _gsCProcedureRedCpuSignalWait,                              NULL);
        mape_set_native_function(1, gApeThread2, "redCpuSignalUnsignal",                        _gsCProcedureRedCpuSignalUnsignal,                          NULL);
        mape_set_native_function(1, gApeThread2, "redGpuToCpuSignalGetStatus",                  _gsCProcedureRedGpuToCpuSignalGetStatus,                    NULL);
        mape_set_native_function(1, gApeThread2, "redGpuToCpuSignalUnsignal",                   _gsCProcedureRedGpuToCpuSignalUnsignal,                     NULL);
        mape_set_native_function(1, gApeThread2, "redCallsSet",                                 _gsCProcedureRedCallsSet,                                   NULL);
        mape_set_native_function(1, gApeThread2, "redCallsEnd",                                 _gsCProcedureRedCallsEnd,                                   NULL);
        mape_set_native_function(1, gApeThread2, "redGetCallProceduresAndAddresses",            _gsCProcedureRedGetCallProceduresAndAddresses,              NULL);
        mape_set_native_function(1, gApeThread2, "redCallGpuToCpuSignalSignal",                 _gsCProcedureRedCallGpuToCpuSignalSignal,                   NULL);
        mape_set_native_function(1, gApeThread2, "redCallCopyArrayToArray",                     _gsCProcedureRedCallCopyArrayToArray,                       NULL);
        mape_set_native_function(1, gApeThread2, "redCallCopyImageToImage",                     _gsCProcedureRedCallCopyImageToImage,                       NULL);
        mape_set_native_function(1, gApeThread2, "redCallCopyArrayToImage",                     _gsCProcedureRedCallCopyArrayToImage,                       NULL);
        mape_set_native_function(1, gApeThread2, "redCallCopyImageToArray",                     _gsCProcedureRedCallCopyImageToArray,                       NULL);
        mape_set_native_function(1, gApeThread2, "redCallProcedure",                            _gsCProcedureRedCallProcedure,                              NULL);
        mape_set_native_function(1, gApeThread2, "redCallProcedureIndexed",                     _gsCProcedureRedCallProcedureIndexed,                       NULL);
        mape_set_native_function(1, gApeThread2, "redCallProcedureCompute",                     _gsCProcedureRedCallProcedureCompute,                       NULL);
        mape_set_native_function(1, gApeThread2, "redCallSetProcedure",                         _gsCProcedureRedCallSetProcedure,                           NULL);
        mape_set_native_function(1, gApeThread2, "redCallSetProcedureIndices",                  _gsCProcedureRedCallSetProcedureIndices,                    NULL);
        mape_set_native_function(1, gApeThread2, "redCallSetProcedureParametersVariables",      _gsCProcedureRedCallSetProcedureParametersVariables,        NULL);
        mape_set_native_function(1, gApeThread2, "redCallSetProcedureParametersStructs",        _gsCProcedureRedCallSetProcedureParametersStructs,          NULL);
        mape_set_native_function(1, gApeThread2, "redCallSetProcedureParametersHandles",        _gsCProcedureRedCallSetProcedureParametersHandles,          NULL);
        mape_set_native_function(1, gApeThread2, "redCallSetDynamicDepthBias",                  _gsCProcedureRedCallSetDynamicDepthBias,                    NULL);
        mape_set_native_function(1, gApeThread2, "redCallSetDynamicDepthBounds",                _gsCProcedureRedCallSetDynamicDepthBounds,                  NULL);
        mape_set_native_function(1, gApeThread2, "redCallSetDynamicStencilCompareMask",         _gsCProcedureRedCallSetDynamicStencilCompareMask,           NULL);
        mape_set_native_function(1, gApeThread2, "redCallSetDynamicStencilWriteMask",           _gsCProcedureRedCallSetDynamicStencilWriteMask,             NULL);
        mape_set_native_function(1, gApeThread2, "redCallSetDynamicStencilReference",           _gsCProcedureRedCallSetDynamicStencilReference,             NULL);
        mape_set_native_function(1, gApeThread2, "redCallSetDynamicBlendConstants",             _gsCProcedureRedCallSetDynamicBlendConstants,               NULL);
        mape_set_native_function(1, gApeThread2, "redCallSetDynamicViewport",                   _gsCProcedureRedCallSetDynamicViewport,                     NULL);
        mape_set_native_function(1, gApeThread2, "redCallSetDynamicScissor",                    _gsCProcedureRedCallSetDynamicScissor,                      NULL);
        mape_set_native_function(1, gApeThread2, "redCallSetStructsMemory",                     _gsCProcedureRedCallSetStructsMemory,                       NULL);
        mape_set_native_function(1, gApeThread2, "redCallSetProcedureParameters",               _gsCProcedureRedCallSetProcedureParameters,                 NULL);
        mape_set_native_function(1, gApeThread2, "redCallSetProcedureOutput",                   _gsCProcedureRedCallSetProcedureOutput,                     NULL);
        mape_set_native_function(1, gApeThread2, "redCallEndProcedureOutput",                   _gsCProcedureRedCallEndProcedureOutput,                     NULL);
        mape_set_native_function(1, gApeThread2, "redCallUsageAliasOrderBarrier",               _gsCProcedureRedCallUsageAliasOrderBarrier,                 NULL);
        mape_set_native_function(1, gApeThread2, "redCallMark",                                 _gsCProcedureRedCallMark,                                   NULL);
        mape_set_native_function(1, gApeThread2, "redCallMarkSet",                              _gsCProcedureRedCallMarkSet,                                NULL);
        mape_set_native_function(1, gApeThread2, "redCallMarkEnd",                              _gsCProcedureRedCallMarkEnd,                                NULL);
        mape_set_native_function(1, gApeThread2, "redQueueSubmit",                              _gsCProcedureRedQueueSubmit,                                NULL);
        mape_set_native_function(1, gApeThread2, "redMark",                                     _gsCProcedureRedMark,                                       NULL);
        mape_set_native_function(1, gApeThread2, "redMarkSet",                                  _gsCProcedureRedMarkSet,                                    NULL);
        mape_set_native_function(1, gApeThread2, "redMarkEnd",                                  _gsCProcedureRedMarkEnd,                                    NULL);
        mape_set_native_function(1, gApeThread2, "redCreateProcedureComputingLanguage",         _gsCProcedureRedCreateProcedureComputingLanguage,           NULL);
        mape_set_native_function(1, gApeThread2, "redCreateArrayTimestamp",                     _gsCProcedureRedCreateArrayTimestamp,                       NULL);
        mape_set_native_function(1, gApeThread2, "redDestroyArrayTimestamp",                    _gsCProcedureRedDestroyArrayTimestamp,                      NULL);
        mape_set_native_function(1, gApeThread2, "redCallArrayTimestampWrite",                  _gsCProcedureRedCallArrayTimestampWrite,                    NULL);
        mape_set_native_function(1, gApeThread2, "redArrayTimestampRead",                       _gsCProcedureRedArrayTimestampRead,                         NULL);
        mape_set_native_function(1, gApeThread2, "getRrtStructsCount",                          _gsCProcedureGetRrtStructsCount,                            NULL);
        mape_set_native_function(1, gApeThread2, "getRrtStructName",                            _gsCProcedureGetRrtStructName,                              NULL);
        mape_set_native_function(1, gApeThread2, "getRrtStructMembersCount",                    _gsCProcedureGetRrtStructMembersCount,                      NULL);
        mape_set_native_function(1, gApeThread2, "getRrtStructMemberName",                      _gsCProcedureGetRrtStructMemberName,                        NULL);
        mape_set_native_function(1, gApeThread2, "rrtStructSizeof",                             _gsCProcedureRrtStructSizeof,                               NULL);
        mape_set_native_function(1, gApeThread2, "rrtStructMemberSizeof",                       _gsCProcedureRrtStructMemberSizeof,                         NULL);
        mape_set_native_function(1, gApeThread2, "rrtStructMemberOffsetof",                     _gsCProcedureRrtStructMemberOffsetof,                       NULL);
        mape_set_native_function(1, gApeThread2, "rrtStructMemberTypeof",                       _gsCProcedureRrtStructMemberTypeof,                         NULL);
        mape_set_native_function(1, gApeThread2, "rrtCreateContext",                            _gsCProcedureRrtCreateContext,                              NULL);
        mape_set_native_function(1, gApeThread2, "rrtDestroyContext",                           _gsCProcedureRrtDestroyContext,                             NULL);
        mape_set_native_function(1, gApeThread2, "rrtSetLogLevel",                              _gsCProcedureRrtSetLogLevel,                                NULL);
        mape_set_native_function(1, gApeThread2, "rrtSetLogFile",                               _gsCProcedureRrtSetLogFile,                                 NULL);
        mape_set_native_function(1, gApeThread2, "rrtCmdBuildGeometry",                         _gsCProcedureRrtCmdBuildGeometry,                           NULL);
        mape_set_native_function(1, gApeThread2, "rrtGetGeometryBuildMemoryRequirements",       _gsCProcedureRrtGetGeometryBuildMemoryRequirements,         NULL);
        mape_set_native_function(1, gApeThread2, "rrtCmdBuildScene",                            _gsCProcedureRrtCmdBuildScene,                              NULL);
        mape_set_native_function(1, gApeThread2, "rrtGetSceneBuildMemoryRequirements",          _gsCProcedureRrtGetSceneBuildMemoryRequirements,            NULL);
        mape_set_native_function(1, gApeThread2, "rrtCmdIntersect",                             _gsCProcedureRrtCmdIntersect,                               NULL);
        mape_set_native_function(1, gApeThread2, "rrtGetTraceMemoryRequirements",               _gsCProcedureRrtGetTraceMemoryRequirements,                 NULL);
        mape_set_native_function(1, gApeThread2, "rrtAllocateCommandStream",                    _gsCProcedureRrtAllocateCommandStream,                      NULL);
        mape_set_native_function(1, gApeThread2, "rrtReleaseCommandStream",                     _gsCProcedureRrtReleaseCommandStream,                       NULL);
        mape_set_native_function(1, gApeThread2, "rrtSumbitCommandStream",                      _gsCProcedureRrtSumbitCommandStream,                        NULL);
        mape_set_native_function(1, gApeThread2, "rrtReleaseEvent",                             _gsCProcedureRrtReleaseEvent,                               NULL);
        mape_set_native_function(1, gApeThread2, "rrtWaitEvent",                                _gsCProcedureRrtWaitEvent,                                  NULL);
        mape_set_native_function(1, gApeThread2, "rrtReleaseDevicePtr",                         _gsCProcedureRrtReleaseDevicePtr,                           NULL);
        mape_set_native_function(1, gApeThread2, "rrtReleaseExternalCommandStream",             _gsCProcedureRrtReleaseExternalCommandStream,               NULL);
        mape_set_native_function(1, gApeThread2, "rrtGetDevicePtrFromVkBuffer",                 _gsCProcedureRrtGetDevicePtrFromVkBuffer,                   NULL);
        mape_set_native_function(1, gApeThread2, "rrtCreateContextVk",                          _gsCProcedureRrtCreateContextVk,                            NULL);
        mape_set_native_function(1, gApeThread2, "rrtGetCommandStreamFromVkCommandBuffer",      _gsCProcedureRrtGetCommandStreamFromVkCommandBuffer,        NULL);
        mape_set_native_function(1, gApeThread2, "rrtAllocateDeviceBuffer",                     _gsCProcedureRrtAllocateDeviceBuffer,                       NULL);
        mape_set_native_function(1, gApeThread2, "rrtMapDevicePtr",                             _gsCProcedureRrtMapDevicePtr,                               NULL);
        mape_set_native_function(1, gApeThread2, "rrtUnmapDevicePtr",                           _gsCProcedureRrtUnmapDevicePtr,                             NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedCpuSignalWait",                 _gsCProcedureOnRerunCallRedCpuSignalWait,                   NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedMemoryFree",                    _gsCProcedureOnRerunCallRedMemoryFree,                      NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedStructsMemoryFree",             _gsCProcedureOnRerunCallRedStructsMemoryFree,               NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedDestroyContext",                _gsCProcedureOnRerunCallRedDestroyContext,                  NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedDestroyArray",                  _gsCProcedureOnRerunCallRedDestroyArray,                    NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedDestroyImage",                  _gsCProcedureOnRerunCallRedDestroyImage,                    NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedDestroySampler",                _gsCProcedureOnRerunCallRedDestroySampler,                  NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedDestroyTexture",                _gsCProcedureOnRerunCallRedDestroyTexture,                  NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedDestroyGpuCode",                _gsCProcedureOnRerunCallRedDestroyGpuCode,                  NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedDestroyOutputDeclaration",      _gsCProcedureOnRerunCallRedDestroyOutputDeclaration,        NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedDestroyStructDeclaration",      _gsCProcedureOnRerunCallRedDestroyStructDeclaration,        NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedDestroyProcedureParameters",    _gsCProcedureOnRerunCallRedDestroyProcedureParameters,      NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedDestroyProcedureCache",         _gsCProcedureOnRerunCallRedDestroyProcedureCache,           NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedDestroyProcedure",              _gsCProcedureOnRerunCallRedDestroyProcedure,                NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedDestroyOutput",                 _gsCProcedureOnRerunCallRedDestroyOutput,                   NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedDestroyCpuSignal",              _gsCProcedureOnRerunCallRedDestroyCpuSignal,                NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedDestroyGpuSignal",              _gsCProcedureOnRerunCallRedDestroyGpuSignal,                NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedDestroyGpuToCpuSignal",         _gsCProcedureOnRerunCallRedDestroyGpuToCpuSignal,           NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedDestroyCalls",                  _gsCProcedureOnRerunCallRedDestroyCalls,                    NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRedDestroyArrayTimestamp",         _gsCProcedureOnRerunCallRedDestroyArrayTimestamp,           NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRrtDestroyContext",                _gsCProcedureOnRerunCallRrtDestroyContext,                  NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRrtReleaseCommandStream",          _gsCProcedureOnRerunCallRrtReleaseCommandStream,            NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRrtReleaseEvent",                  _gsCProcedureOnRerunCallRrtReleaseEvent,                    NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRrtWaitEvent",                     _gsCProcedureOnRerunCallRrtWaitEvent,                       NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRrtReleaseDevicePtr",              _gsCProcedureOnRerunCallRrtReleaseDevicePtr,                NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRrtReleaseExternalCommandStream",  _gsCProcedureOnRerunCallRrtReleaseExternalCommandStream,    NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallRrtUnmapDevicePtr",                _gsCProcedureOnRerunCallRrtUnmapDevicePtr,                  NULL);
      }
      if (gXatlasIsEnabled == 1) {
        mape_set_native_function(1, gApeThread2, "getXatlasStructsCount",                       _gsCProcedureGetXatlasStructsCount,                         NULL);
        mape_set_native_function(1, gApeThread2, "getXatlasStructName",                         _gsCProcedureGetXatlasStructName,                           NULL);
        mape_set_native_function(1, gApeThread2, "getXatlasStructMembersCount",                 _gsCProcedureGetXatlasStructMembersCount,                   NULL);
        mape_set_native_function(1, gApeThread2, "getXatlasStructMemberName",                   _gsCProcedureGetXatlasStructMemberName,                     NULL);
        mape_set_native_function(1, gApeThread2, "xatlasStructSizeof",                          _gsCProcedureXatlasStructSizeof,                            NULL);
        mape_set_native_function(1, gApeThread2, "xatlasStructMemberSizeof",                    _gsCProcedureXatlasStructMemberSizeof,                      NULL);
        mape_set_native_function(1, gApeThread2, "xatlasStructMemberOffsetof",                  _gsCProcedureXatlasStructMemberOffsetof,                    NULL);
        mape_set_native_function(1, gApeThread2, "xatlasStructMemberTypeof",                    _gsCProcedureXatlasStructMemberTypeof,                      NULL);
        mape_set_native_function(1, gApeThread2, "xatlasMeshDeclInit",                          _gsCProcedureXatlasMeshDeclInit,                            NULL);
        mape_set_native_function(1, gApeThread2, "xatlasUvMeshDeclInit",                        _gsCProcedureXatlasUvMeshDeclInit,                          NULL);
        mape_set_native_function(1, gApeThread2, "xatlasChartOptionsInit",                      _gsCProcedureXatlasChartOptionsInit,                        NULL);
        mape_set_native_function(1, gApeThread2, "xatlasPackOptionsInit",                       _gsCProcedureXatlasPackOptionsInit,                         NULL);
        mape_set_native_function(1, gApeThread2, "xatlasCreate",                                _gsCProcedureXatlasCreate,                                  NULL);
        mape_set_native_function(1, gApeThread2, "xatlasDestroy",                               _gsCProcedureXatlasDestroy,                                 NULL);
        mape_set_native_function(1, gApeThread2, "xatlasAddMesh",                               _gsCProcedureXatlasAddMesh,                                 NULL);
        mape_set_native_function(1, gApeThread2, "xatlasAddMeshJoin",                           _gsCProcedureXatlasAddMeshJoin,                             NULL);
        mape_set_native_function(1, gApeThread2, "xatlasAddUvMesh",                             _gsCProcedureXatlasAddUvMesh,                               NULL);
        mape_set_native_function(1, gApeThread2, "xatlasComputeCharts",                         _gsCProcedureXatlasComputeCharts,                           NULL);
        mape_set_native_function(1, gApeThread2, "xatlasPackCharts",                            _gsCProcedureXatlasPackCharts,                              NULL);
        mape_set_native_function(1, gApeThread2, "xatlasGenerate",                              _gsCProcedureXatlasGenerate,                                NULL);
        mape_set_native_function(1, gApeThread2, "onRerunCallXatlasDestroy",                    _gsCProcedureOnRerunCallXatlasDestroy,                      NULL);
      }
      if (gFbxIsEnabled == 1) {
        mape_set_native_function(1, gApeThread2, "fbxNew",                                      _gsCProcedureFbxNew,                                        NULL);
        mape_set_native_function(1, gApeThread2, "fbxNewFromFile",                              _gsCProcedureFbxNewFromFile,                                NULL);
        mape_set_native_function(1, gApeThread2, "fbxDelete",                                   _gsCProcedureFbxDelete,                                     NULL);
        mape_set_native_function(1, gApeThread2, "fbxDeleteAll",                                _gsCProcedureFbxDeleteAll,                                  NULL);
        mape_set_native_function(1, gApeThread2, "fbxGetHandle",                                _gsCProcedureFbxGetHandle,                                  NULL);
        mape_set_native_function(1, gApeThread2, "fbxCopyToFbx",                                _gsCProcedureFbxCopyToFbx,                                  NULL);
        mape_set_native_function(1, gApeThread2, "fbxClear",                                    _gsCProcedureFbxClear,                                      NULL);
        mape_set_native_function(1, gApeThread2, "fbxEarlyUpdate",                              _gsCProcedureFbxEarlyUpdate,                                NULL);
        mape_set_native_function(1, gApeThread2, "fbxLateUpdate",                               _gsCProcedureFbxLateUpdate,                                 NULL);
        mape_set_native_function(1, gApeThread2, "fbxGetMeshesCount",                           _gsCProcedureFbxGetMeshesCount,                             NULL);
        mape_set_native_function(1, gApeThread2, "fbxGetMesh",                                  _gsCProcedureFbxGetMesh,                                    NULL);
        mape_set_native_function(1, gApeThread2, "fbxGetMeshName",                              _gsCProcedureFbxGetMeshName,                                NULL);
        mape_set_native_function(1, gApeThread2, "fbxGetRootBonesCount",                        _gsCProcedureFbxGetRootBonesCount,                          NULL);
        mape_set_native_function(1, gApeThread2, "fbxGetRootBone",                              _gsCProcedureFbxGetRootBone,                                NULL);
        mape_set_native_function(1, gApeThread2, "fbxBoneGetName",                              _gsCProcedureFbxBoneGetName,                                NULL);
        mape_set_native_function(1, gApeThread2, "fbxBoneGetChildBonesCount",                   _gsCProcedureFbxBoneGetChildBonesCount,                     NULL);
        mape_set_native_function(1, gApeThread2, "fbxBoneGetChildBone",                         _gsCProcedureFbxBoneGetChildBone,                           NULL);
        mape_set_native_function(1, gApeThread2, "fbxBoneGetChildBoneByNameRecursively",        _gsCProcedureFbxBoneGetChildBoneByNameRecursively,          NULL);
        mape_set_native_function(1, gApeThread2, "fbxBoneGetVector",                            _gsCProcedureFbxBoneGetVector,                              NULL);
        mape_set_native_function(1, gApeThread2, "fbxBoneGetVersor",                            _gsCProcedureFbxBoneGetVersor,                              NULL);
        mape_set_native_function(1, gApeThread2, "fbxBoneGetScale",                             _gsCProcedureFbxBoneGetScale,                               NULL);
        mape_set_native_function(1, gApeThread2, "fbxBoneGetSideVector",                        _gsCProcedureFbxBoneGetSideVector,                          NULL);
        mape_set_native_function(1, gApeThread2, "fbxBoneGetUpVector",                          _gsCProcedureFbxBoneGetUpVector,                            NULL);
        mape_set_native_function(1, gApeThread2, "fbxBoneGetLookAtVector",                      _gsCProcedureFbxBoneGetLookAtVector,                        NULL);
        mape_set_native_function(1, gApeThread2, "fbxBoneGetTransformMatrix",                   _gsCProcedureFbxBoneGetTransformMatrix,                     NULL);
        mape_set_native_function(1, gApeThread2, "fbxBoneSetVector",                            _gsCProcedureFbxBoneSetVector,                              NULL);
        mape_set_native_function(1, gApeThread2, "fbxBoneSetVersor",                            _gsCProcedureFbxBoneSetVersor,                              NULL);
        mape_set_native_function(1, gApeThread2, "fbxBoneSetScale",                             _gsCProcedureFbxBoneSetScale,                               NULL);
        mape_set_native_function(1, gApeThread2, "fbxBoneRotate",                               _gsCProcedureFbxBoneRotate,                                 NULL);
        mape_set_native_function(1, gApeThread2, "fbxBoneLookAt",                               _gsCProcedureFbxBoneLookAt,                                 NULL);
      }
#if defined(GAME_SCRIPT_MIN)
      mape_set_native_function(1, gApeThread2, "sqrt",  _minCProcedureSqrt,  NULL);
      mape_set_native_function(1, gApeThread2, "pow",   _minCProcedurePow,   NULL);
      mape_set_native_function(1, gApeThread2, "sin",   _minCProcedureSin,   NULL);
      mape_set_native_function(1, gApeThread2, "cos",   _minCProcedureCos,   NULL);
      mape_set_native_function(1, gApeThread2, "tan",   _minCProcedureTan,   NULL);
      mape_set_native_function(1, gApeThread2, "log",   _minCProcedureLog,   NULL);
      mape_set_native_function(1, gApeThread2, "ceil",  _minCProcedureCeil,  NULL);
      mape_set_native_function(1, gApeThread2, "floor", _minCProcedureFloor, NULL);
      mape_set_native_function(1, gApeThread2, "abs",   _minCProcedureAbs,   NULL);
#endif
#if defined(GAME_SCRIPT_C)
      mape_set_native_function(1, gApeThread2, "malloc", malloc, NULL);
      mape_set_native_function(1, gApeThread2, "free",   free,   NULL);
      mape_set_native_function(1, gApeThread2, "memset", memset, NULL);
      mape_set_native_function(1, gApeThread2, "memcpy", memcpy, NULL);
      mape_set_native_function(1, gApeThread2, "memcmp", memcmp, NULL);
      mape_set_native_function(1, gApeThread2, "sqrtf",  sqrtf,  NULL);
      mape_set_native_function(1, gApeThread2, "powf",   powf,   NULL);
      mape_set_native_function(1, gApeThread2, "sinf",   sinf,   NULL);
      mape_set_native_function(1, gApeThread2, "cosf",   cosf,   NULL);
      mape_set_native_function(1, gApeThread2, "tanf",   tanf,   NULL);
      mape_set_native_function(1, gApeThread2, "logf",   logf,   NULL);
      mape_set_native_function(1, gApeThread2, "ceilf",  ceilf,  NULL);
      mape_set_native_function(1, gApeThread2, "floorf", floorf, NULL);
      mape_set_native_function(1, gApeThread2, "fabsf",  fabsf,  NULL);
#endif
      profileEnd("thread 2 script set procedures");
#endif // #ifdef GAME_SCRIPT
      profileBegin("thread 2 script execute");
      mape_execute(1, gApeThread2, gApeCodeCharsCurrentlyRunningThread2);
      profileEnd("thread 2 script execute");
      // Set the user provided next script.
      if (gApeCodeCharsNextRunningThread2 != "") {
        profileBegin("thread 2 set next script");
        gGameScriptNativeRecompileSignalThread2 = 1;
        free(gApeCodeCharsCurrentlyRunningThread2);
        gApeCodeCharsCurrentlyRunningThread2 = (char *)calloc(1, gApeCodeCharsNextRunningThread2.size() + 1);
        if (gApeCodeCharsCurrentlyRunningThread2 != NULL && gApeCodeCharsNextRunningThread2.size() > 0) {
          memcpy(gApeCodeCharsCurrentlyRunningThread2, &gApeCodeCharsNextRunningThread2[0], gApeCodeCharsNextRunningThread2.size());
        }
        gApeCodeCharsNextRunningThread2 = "";
        gApeErrorCheckThread2 = 2;
        profileEnd("thread 2 set next script");
      }
      if (gApeErrorCheckThread2 >= 1) {
        if (gApeErrorCheckThread2 == 1) {
          gApeErrorCheckThread2 = 0;
        }
        if (gApeErrorCheckThread2 == 2) {
          gApeErrorCheckThread2 = 1;
        }
        profileBegin("thread 2 check script errors");
        std::string errors;
        if (ape_has_errors(gApeThread2)) {
          errors += "[Game Script][Thread 2 Script Errors]";
          errors += "[Frame ";
          errors += std::to_string(gCurrentFrameThread2);
          errors += "]\n\n";
          for (int i = 0; i < ape_errors_count(gApeThread2); i += 1) {
            const ape_error_t * err = ape_get_error(gApeThread2, i);
            char * error = ape_error_serialize(gApeThread2, err);
            std::string errorString = error;
            errors += errorString;
            ape_free_allocated(gApeThread2, error);
          }
          ape_clear_errors(gApeThread2);
        }
        if (errors != "") {
          _gsPrintThreadSafe(errors.c_str());
        }
        profileEnd("thread 2 check script errors");
      }
      gCurrentFrameThread2 += 1;
      profileEnd(thread2FrameString.c_str());
    } else {
#if defined(_WIN32)
      _mm_pause();
#else
      __asm __volatile("pause");
#endif
    }
  }
}

void theexit(void) {
  if (gThreadF1 != 0) {
    if (redFThreadIsRunning(gThreadF1[0]) == 1) {
      redFThreadWaitFor(gThreadF1[0], 1, -1);
    }
  }
  if (gThread2 != 0) {
    gThread2StopSignal = 1;
    if (redFThreadIsRunning(gThread2[0]) == 1) {
      redFThreadWaitFor(gThread2[0], 1, -1);
    }
  }
}

void setup(void) {
  profileBegin("setup");

  gF1CommandOptions.resize(4096);

  gThreadF1 = redFCreateThread(1);
  if (gThreadF1 != 0) {
    redFThreadSetProcedure(gThreadF1[0], threadF1Procedure);
  }

  gThread2 = redFCreateThread(1);
  if (gThread2 != 0) {
    redFThreadSetProcedure(gThread2[0], thread2Procedure);
  }

#if defined(__linux__)
  gExternalLibraryHandle = dlopen("/opt/GameScript/libgame_script_external_procedure.so", RTLD_NOW | RTLD_GLOBAL);
  if (gExternalLibraryHandle == 0) {
    std::string filepath = gCurrentExeDir;
    filepath += "libgame_script_external_procedure.so";
    gExternalLibraryHandle = dlopen(filepath.c_str(), RTLD_NOW | RTLD_GLOBAL);
  }
  if (gExternalLibraryHandle != 0) {
    gExternalLibraryProcedureCall2 = (void (*)(double, double))dlsym(gExternalLibraryHandle, "libGameScriptExternalProcedureCall2");
    gExternalLibraryProcedureCall3 = (void (*)(double, double, double))dlsym(gExternalLibraryHandle, "libGameScriptExternalProcedureCall3");
  }
#elif defined(_WIN32)
  gExternalLibraryHandle = LoadLibraryA("C:/GameScript/game_script_external_procedure.dll");
  if (gExternalLibraryHandle == 0) {
    gExternalLibraryHandle = LoadLibraryA("game_script_external_procedure.dll");
  }
  if (gExternalLibraryHandle != 0) {
    gExternalLibraryProcedureCall2 = (void (*)(double, double))GetProcAddress((HMODULE)gExternalLibraryHandle, "libGameScriptExternalProcedureCall2");
    gExternalLibraryProcedureCall3 = (void (*)(double, double, double))GetProcAddress((HMODULE)gExternalLibraryHandle, "libGameScriptExternalProcedureCall3");
  }
#else
#error Error
#endif

  srand(time(NULL));
  redFDisableArbTex(); // https://forum.openframeworks.cc/t/what-does-ofdisablearbtex-do/26377
  redFEnableFramebufferSRGBGammaCorrection();
  redFEnable(0x884F); // GL_TEXTURE_CUBE_MAP_SEAMLESS, https://www.khronos.org/opengl/wiki/Cubemap_Texture#Seamless_cubemap
  redFClipControl(0x8CA1, 0x935F); // GL_LOWER_LEFT, GL_ZERO_TO_ONE

  redFSetWindowTitle(GAME_SCRIPT_WINDOW_TITLE);
  redFSetEscapeQuitsApp(0);
  redFSetVerticalSync(1);

  gGuiImgui = redFCreateImgui(1);
  redFImguiSetup(gGuiImgui[0]);
  ImGuiIO * io = igGetIO();
  io->FontGlobalScale = gImguiFontGlobalScale;
  io->ConfigFlags    |= ImGuiConfigFlags_NavEnableKeyboard;
  ImGuiStyle * style = igGetStyle();
  style->Colors[ImGuiCol_WindowBg].w = 0.99f;

#if defined(GAME_SCRIPT_NATIVE)
  // https://github.com/ocornut/imgui/issues/707#issuecomment-670976818

  ImVec4 bgColor;          bgColor.x          = 37/255.f; bgColor.y          = 37/255.f; bgColor.z          = 38/255.f; bgColor.w          = 0.99f;
  ImVec4 lightBgColor;     lightBgColor.x     = 82/255.f; lightBgColor.y     = 82/255.f; lightBgColor.z     = 85/255.f; lightBgColor.w     = 1.f;
  ImVec4 veryLightBgColor; veryLightBgColor.x = 90/255.f; veryLightBgColor.y = 90/255.f; veryLightBgColor.z = 95/255.f; veryLightBgColor.w = 1.f;

  ImVec4 panelColor;       panelColor.x = 61/255.f; panelColor.y = 61/255.f; panelColor.z = 65/255.f; panelColor.w = 1.f;
  ImVec4 panelHoverColor   = style->Colors[ImGuiCol_FrameBgHovered];
  ImVec4 panelActiveColor  = style->Colors[ImGuiCol_TextSelectedBg];
  panelHoverColor.w = 0.99f;

  ImVec4 textColor;         textColor.x         = 255/255.f; textColor.y         = 255/255.f; textColor.z         = 255/255.f; textColor.w         = 1.f;
  ImVec4 textDisabledColor; textDisabledColor.x = 151/255.f; textDisabledColor.y = 151/255.f; textDisabledColor.z = 151/255.f; textDisabledColor.w = 1.f;
  ImVec4 borderColor;       borderColor.x       =  78/255.f; borderColor.y       =  78/255.f; borderColor.z       =  78/255.f; borderColor.w       = 1.f;

  ImVec4 bgColorCollapsed = bgColor;
  bgColorCollapsed.w = style->Colors[ImGuiCol_TitleBgCollapsed].w;

  style->Colors[ImGuiCol_Text]                 = textColor;
  style->Colors[ImGuiCol_TextDisabled]         = textDisabledColor;
  style->Colors[ImGuiCol_TextSelectedBg]       = panelActiveColor;
  style->Colors[ImGuiCol_WindowBg]             = bgColor;
  style->Colors[ImGuiCol_ChildBg]              = bgColor;
  style->Colors[ImGuiCol_PopupBg]              = bgColor;
  style->Colors[ImGuiCol_Border]               = borderColor;
  style->Colors[ImGuiCol_BorderShadow]         = borderColor;
  style->Colors[ImGuiCol_FrameBg]              = panelColor;
  style->Colors[ImGuiCol_FrameBgHovered]       = panelHoverColor;
  style->Colors[ImGuiCol_FrameBgActive]        = panelActiveColor;
  style->Colors[ImGuiCol_TitleBg]              = bgColor;
  style->Colors[ImGuiCol_TitleBgActive]        = panelHoverColor;
  style->Colors[ImGuiCol_TitleBgCollapsed]     = bgColorCollapsed;
  style->Colors[ImGuiCol_MenuBarBg]            = panelColor;
  style->Colors[ImGuiCol_ScrollbarBg]          = panelColor;
  style->Colors[ImGuiCol_ScrollbarGrab]        = lightBgColor;
  style->Colors[ImGuiCol_ScrollbarGrabHovered] = veryLightBgColor;
  style->Colors[ImGuiCol_ScrollbarGrabActive]  = veryLightBgColor;
  style->Colors[ImGuiCol_CheckMark]            = panelActiveColor;
  style->Colors[ImGuiCol_SliderGrab]           = panelHoverColor;
  style->Colors[ImGuiCol_SliderGrabActive]     = panelActiveColor;
  style->Colors[ImGuiCol_Button]               = panelColor;
  style->Colors[ImGuiCol_ButtonHovered]        = panelHoverColor;
  style->Colors[ImGuiCol_ButtonActive]         = panelHoverColor;
  style->Colors[ImGuiCol_Header]               = panelColor;
  style->Colors[ImGuiCol_HeaderHovered]        = panelHoverColor;
  style->Colors[ImGuiCol_HeaderActive]         = panelActiveColor;
  style->Colors[ImGuiCol_Separator]            = borderColor;
  style->Colors[ImGuiCol_SeparatorHovered]     = borderColor;
  style->Colors[ImGuiCol_SeparatorActive]      = borderColor;
  style->Colors[ImGuiCol_ResizeGrip]           = bgColor;
  style->Colors[ImGuiCol_ResizeGripHovered]    = panelColor;
  style->Colors[ImGuiCol_ResizeGripActive]     = lightBgColor;
  style->Colors[ImGuiCol_PlotLines]            = panelActiveColor;
  style->Colors[ImGuiCol_PlotLinesHovered]     = panelHoverColor;
  style->Colors[ImGuiCol_PlotHistogram]        = panelActiveColor;
  style->Colors[ImGuiCol_PlotHistogramHovered] = panelHoverColor;
  style->Colors[ImGuiCol_DragDropTarget]       = bgColor;
  style->Colors[ImGuiCol_NavHighlight]         = bgColor;
  style->Colors[ImGuiCol_DockingPreview]       = panelActiveColor;
  style->Colors[ImGuiCol_Tab]                  = bgColor;
  style->Colors[ImGuiCol_TabActive]            = panelActiveColor;
  style->Colors[ImGuiCol_TabUnfocused]         = bgColor;
  style->Colors[ImGuiCol_TabUnfocusedActive]   = panelActiveColor;
  style->Colors[ImGuiCol_TabHovered]           = panelHoverColor;

  style->WindowRounding    = 0.0f;
  style->ChildRounding     = 0.0f;
  style->FrameRounding     = 0.0f;
  style->GrabRounding      = 0.0f;
  style->PopupRounding     = 0.0f;
  style->ScrollbarRounding = 0.0f;
  style->TabRounding       = 0.0f;
#endif

  gCamera = redFCreateFirstPersonCamera(1);
  redFFirstPersonCameraSetMoveSpeed(gCamera[0], 0.25f);
  redFCameraSetupPerspective(redFFirstPersonCameraCastToCamera(gCamera[0]), 0, 60, 0.005f, 10000.0f, 0, 0);
  redFNodeSetGlobalPosition(redFFirstPersonCameraCastToNode(gCamera[0]), 0, 0, 10);

  apeScriptRerun(1);
  scriptLoad("autosave.script");

  profileEnd("setup");
}

void update(void) {
  profileBegin("update");
  glfwPollEvents();
  profileEnd("update");
}

void draw(void) {
  profileBegin("draw");
  std::string thread1FrameString;
  thread1FrameString += "thread 1 frame ";
  thread1FrameString += std::to_string(gCurrentFrame);
  profileBegin(thread1FrameString.c_str());

  if (gRunScriptOnce == 1) {
    gStopScript = 0;
  }
  if (gFullscreenExclusive == 0) {
    if (gFullscreenF11Override == 0) {
      if (gGameMode == 0) {
        gFullscreen = 0;
      }
      if (gFullscreen == 1) {
        redFSetFullscreen(1);
      } else {
        redFSetFullscreen(0);
      }
    } else {
      if (gFullscreenF11OverrideOnce == 1) {
        redFSetFullscreen(1);
        gFullscreenF11OverrideOnce = 0;
      }
    }
  }

  redFEnableDepthTest();
  redFEnableBlendMode(REDF_BLEND_MODE_ALPHA);
  redFEnableAlphaBlending();
  if (gPreviousGameMode == 0 && gGameMode == 1) {
    gDefaultCameraEnabled = 1;
  }
  redFFirstPersonCameraBegin(gCamera[0]);
  int setRerunTo0 = 0;
  if (gRerun == 1) {
    setRerunTo0 = 1;
  }
  if (gStopScript == 0) {
    profileBegin("previous script destroy");
    mape_destroy(0, gApe);
    profileEnd("previous script destroy");
    profileBegin("script make");
    gApe = mape_make(0);
#ifdef GAME_SCRIPT_MIN
    MinScriptLang::Environment env;
#endif
    profileEnd("script make");
#ifdef GAME_SCRIPT_C
    profileBegin("script compile");
    mape_compile(0, gApe, gApeCodeCharsCurrentlyRunning);
    profileEnd("script compile");
#endif // #ifdef GAME_SCRIPT_C
#ifdef GAME_SCRIPT
    profileBegin("script set procedures");
    mape_set_native_function(0, gApe, "printConsole",                             _gsCProcedurePrintConsole,                             NULL);
    mape_set_native_function(0, gApe, "printDraw",                                _gsCProcedurePrintDraw,                                NULL);
    mape_set_native_function(0, gApe, "windowSetTitle",                           _gsCProcedureWindowSetTitle,                           NULL);
    mape_set_native_function(0, gApe, "windowGetWidth",                           _gsCProcedureWindowGetWidth,                           NULL);
    mape_set_native_function(0, gApe, "windowGetHeight",                          _gsCProcedureWindowGetHeight,                          NULL);
    mape_set_native_function(0, gApe, "windowSetWidthHeight",                     _gsCProcedureWindowSetWidthHeight,                     NULL);
    mape_set_native_function(0, gApe, "windowSetFullscreen",                      _gsCProcedureWindowSetFullscreen,                      NULL);
    mape_set_native_function(0, gApe, "windowIsFocused",                          _gsCProcedureWindowIsFocused,                          NULL);
    mape_set_native_function(0, gApe, "windowIsHovered",                          _gsCProcedureWindowIsHovered,                          NULL);
    mape_set_native_function(0, gApe, "windowIsMinimized",                        _gsCProcedureWindowIsMinimized,                        NULL);
    mape_set_native_function(0, gApe, "windowIsHidden",                           _gsCProcedureWindowIsHidden,                           NULL);
    mape_set_native_function(0, gApe, "windowHide",                               _gsCProcedureWindowHide,                               NULL);
    mape_set_native_function(0, gApe, "windowShow",                               _gsCProcedureWindowShow,                               NULL);
    mape_set_native_function(0, gApe, "windowRequestAttention",                   _gsCProcedureWindowRequestAttention,                   NULL);
    mape_set_native_function(0, gApe, "drawPoint",                                _gsCProcedureDrawPoint,                                NULL);
    mape_set_native_function(0, gApe, "drawLine",                                 _gsCProcedureDrawLine,                                 NULL);
    mape_set_native_function(0, gApe, "drawTriangle",                             _gsCProcedureDrawTriangle,                             NULL);
    mape_set_native_function(0, gApe, "drawTriangleWireframe",                    _gsCProcedureDrawTriangleWireframe,                    NULL);
    mape_set_native_function(0, gApe, "drawSphere",                               _gsCProcedureDrawSphere,                               NULL);
    mape_set_native_function(0, gApe, "drawSphereWireframe",                      _gsCProcedureDrawSphereWireframe,                      NULL);
    mape_set_native_function(0, gApe, "drawDebugText",                            _gsCProcedureDrawDebugText,                            NULL);
    mape_set_native_function(0, gApe, "drawDebugTextAtPoint",                     _gsCProcedureDrawDebugTextAtPoint,                     NULL);
    mape_set_native_function(0, gApe, "isRerun",                                  _gsCProcedureIsRerun,                                  NULL);
    mape_set_native_function(0, gApe, "getCurrentFrame",                          _gsCProcedureGetCurrentFrame,                          NULL);
    mape_set_native_function(0, gApe, "setCurrentFrame",                          _gsCProcedureSetCurrentFrame,                          NULL);
    mape_set_native_function(0, gApe, "getRandomNumber",                          _gsCProcedureGetRandomNumber,                          NULL);
    mape_set_native_function(0, gApe, "getExeDirectoryPath",                      _gsCProcedureGetExeDirectoryPath,                      NULL);
    mape_set_native_function(0, gApe, "isLinux",                                  _gsCProcedureIsLinux,                                  NULL);
    mape_set_native_function(0, gApe, "isWindows",                                _gsCProcedureIsWindows,                                NULL);
    mape_set_native_function(0, gApe, "isInGameMode",                             _gsCProcedureIsInGameMode,                             NULL);
    mape_set_native_function(0, gApe, "defaultCameraDefaultControlDisable",       _gsCProcedureDefaultCameraDefaultControlDisable,       NULL);
    mape_set_native_function(0, gApe, "defaultCameraDefaultControlEnable",        _gsCProcedureDefaultCameraDefaultControlEnable,        NULL);
    mape_set_native_function(0, gApe, "defaultCameraDefaultControlForceEnable",   _gsCProcedureDefaultCameraDefaultControlForceEnable,   NULL);
    mape_set_native_function(0, gApe, "defaultCameraDefaultControlIsEnabled",     _gsCProcedureDefaultCameraDefaultControlIsEnabled,     NULL);
    mape_set_native_function(0, gApe, "defaultCameraSetMoveSpeed",                _gsCProcedureDefaultCameraSetMoveSpeed,                NULL);
    mape_set_native_function(0, gApe, "defaultCameraSetRollSpeed",                _gsCProcedureDefaultCameraSetRollSpeed,                NULL);
    mape_set_native_function(0, gApe, "defaultCameraSetMouseSensitivity",         _gsCProcedureDefaultCameraSetMouseSensitivity,         NULL);
    mape_set_native_function(0, gApe, "defaultCameraGetVector",                   _gsCProcedureDefaultCameraGetVector,                   NULL);
    mape_set_native_function(0, gApe, "defaultCameraGetVersor",                   _gsCProcedureDefaultCameraGetVersor,                   NULL);
    mape_set_native_function(0, gApe, "defaultCameraSetVector",                   _gsCProcedureDefaultCameraSetVector,                   NULL);
    mape_set_native_function(0, gApe, "defaultCameraSetVersor",                   _gsCProcedureDefaultCameraSetVersor,                   NULL);
    mape_set_native_function(0, gApe, "defaultCameraRotate",                      _gsCProcedureDefaultCameraRotate,                      NULL);
    mape_set_native_function(0, gApe, "defaultCameraLookAt",                      _gsCProcedureDefaultCameraLookAt,                      NULL);
    mape_set_native_function(0, gApe, "defaultCameraSetFOV",                      _gsCProcedureDefaultCameraSetFOV,                      NULL);
    mape_set_native_function(0, gApe, "defaultCameraSetNearClip",                 _gsCProcedureDefaultCameraSetNearClip,                 NULL);
    mape_set_native_function(0, gApe, "defaultCameraSetFarClip",                  _gsCProcedureDefaultCameraSetFarClip,                  NULL);
    mape_set_native_function(0, gApe, "defaultCameraSetProjectionMode",           _gsCProcedureDefaultCameraSetProjectionMode,           NULL);
    mape_set_native_function(0, gApe, "defaultCameraSetAspectRatio",              _gsCProcedureDefaultCameraSetAspectRatio,              NULL);
    mape_set_native_function(0, gApe, "defaultCameraSetForceAspectRatio",         _gsCProcedureDefaultCameraSetForceAspectRatio,         NULL);
    mape_set_native_function(0, gApe, "defaultCameraSetLensOffset",               _gsCProcedureDefaultCameraSetLensOffset,               NULL);
    mape_set_native_function(0, gApe, "defaultCameraSetupPerspective",            _gsCProcedureDefaultCameraSetupPerspective,            NULL);
    mape_set_native_function(0, gApe, "defaultCameraSetupOffAxisViewPortal",      _gsCProcedureDefaultCameraSetupOffAxisViewPortal,      NULL);
    mape_set_native_function(0, gApe, "defaultCameraSetVFlip",                    _gsCProcedureDefaultCameraSetVFlip,                    NULL);
    mape_set_native_function(0, gApe, "defaultCameraScreenToWorld",               _gsCProcedureDefaultCameraScreenToWorld,               NULL);
    mape_set_native_function(0, gApe, "defaultCameraWorldToScreen",               _gsCProcedureDefaultCameraWorldToScreen,               NULL);
    mape_set_native_function(0, gApe, "defaultCameraGetSideVector",               _gsCProcedureDefaultCameraGetSideVector,               NULL);
    mape_set_native_function(0, gApe, "defaultCameraGetUpVector",                 _gsCProcedureDefaultCameraGetUpVector,                 NULL);
    mape_set_native_function(0, gApe, "defaultCameraGetLookAtVector",             _gsCProcedureDefaultCameraGetLookAtVector,             NULL);
    mape_set_native_function(0, gApe, "defaultCameraGetProjectionMatrix",         _gsCProcedureDefaultCameraGetProjectionMatrix,         NULL);
    mape_set_native_function(0, gApe, "defaultCameraGetModelViewMatrix",          _gsCProcedureDefaultCameraGetModelViewMatrix,          NULL);
    mape_set_native_function(0, gApe, "defaultCameraGetModelViewProjectionMatrix",_gsCProcedureDefaultCameraGetModelViewProjectionMatrix,NULL);
    mape_set_native_function(0, gApe, "defaultCameraSetControlKeys",              _gsCProcedureDefaultCameraSetControlKeys,              NULL);
    mape_set_native_function(0, gApe, "setBackgroundColor",                       _gsCProcedureSetBackgroundColor,                       NULL);
    mape_set_native_function(0, gApe, "setViewport",                              _gsCProcedureSetViewport,                              NULL);
    mape_set_native_function(0, gApe, "alphaBlendingEnable",                      _gsCProcedureAlphaBlendingEnable,                      NULL);
    mape_set_native_function(0, gApe, "alphaBlendingDisable",                     _gsCProcedureAlphaBlendingDisable,                     NULL);
    mape_set_native_function(0, gApe, "blendModeEnable",                          _gsCProcedureBlendModeEnable,                          NULL);
    mape_set_native_function(0, gApe, "blendModeDisable",                         _gsCProcedureBlendModeDisable,                         NULL);
    mape_set_native_function(0, gApe, "depthTestEnable",                          _gsCProcedureDepthTestEnable,                          NULL);
    mape_set_native_function(0, gApe, "depthTestDisable",                         _gsCProcedureDepthTestDisable,                         NULL);
    mape_set_native_function(0, gApe, "cullingEnable",                            _gsCProcedureCullingEnable,                            NULL);
    mape_set_native_function(0, gApe, "cullingDisable",                           _gsCProcedureCullingDisable,                           NULL);
    mape_set_native_function(0, gApe, "clear",                                    _gsCProcedureClear,                                    NULL);
    mape_set_native_function(0, gApe, "clearAlpha",                               _gsCProcedureClearAlpha,                               NULL);
    mape_set_native_function(0, gApe, "clearDepth",                               _gsCProcedureClearDepth,                               NULL);
    mape_set_native_function(0, gApe, "saveScreenRawToMemory",                    _gsCProcedureSaveScreenRawToMemory,                    NULL);
    mape_set_native_function(0, gApe, "globalArrayNew8Bit",                       _gsCProcedureGlobalArrayNew8Bit,                       NULL);
    mape_set_native_function(0, gApe, "globalArrayPersistentNew8Bit",             _gsCProcedureGlobalArrayPersistentNew8Bit,             NULL);
    mape_set_native_function(0, gApe, "globalArrayDelete",                        _gsCProcedureGlobalArrayDelete,                        NULL);
    mape_set_native_function(0, gApe, "globalArrayPersistentDelete",              _gsCProcedureGlobalArrayPersistentDelete,              NULL);
    mape_set_native_function(0, gApe, "globalArrayDeleteAll",                     _gsCProcedureGlobalArrayDeleteAll,                     NULL);
    mape_set_native_function(0, gApe, "globalArrayPersistentDeleteAll",           _gsCProcedureGlobalArrayPersistentDeleteAll,           NULL);
    mape_set_native_function(0, gApe, "globalArrayGetBytesCount",                 _gsCProcedureGlobalArrayGetBytesCount,                 NULL);
    mape_set_native_function(0, gApe, "globalArrayGetPointer",                    _gsCProcedureGlobalArrayGetPointer,                    NULL);
    mape_set_native_function(0, gApe, "globalArrayPersistentGetBytesCount",       _gsCProcedureGlobalArrayPersistentGetBytesCount,       NULL);
    mape_set_native_function(0, gApe, "globalArrayPersistentGetPointer",          _gsCProcedureGlobalArrayPersistentGetPointer,          NULL);
    mape_set_native_function(0, gApe, "globalSharedArrayPersistentNew8Bit",       _gsCProcedureGlobalSharedArrayPersistentNew8Bit,       NULL);
    mape_set_native_function(0, gApe, "globalSharedArrayPersistentGetBytesCount", _gsCProcedureGlobalSharedArrayPersistentGetBytesCount, NULL);
    mape_set_native_function(0, gApe, "globalSharedArrayPersistentGetPointer",    _gsCProcedureGlobalSharedArrayPersistentGetPointer,    NULL);
    mape_set_native_function(0, gApe, "pointerGetBool",                           _gsCProcedurePointerGetBool,                           NULL);
    mape_set_native_function(0, gApe, "pointerGetString",                         _gsCProcedurePointerGetString,                         NULL);
    mape_set_native_function(0, gApe, "pointerGetSubstring",                      _gsCProcedurePointerGetSubstring,                      NULL);
    mape_set_native_function(0, gApe, "pointerGetNumber",                         _gsCProcedurePointerGetNumber,                         NULL);
    mape_set_native_function(0, gApe, "pointerGetInteger",                        _gsCProcedurePointerGetInteger,                        NULL);
    mape_set_native_function(0, gApe, "pointerGetUnsignedInteger",                _gsCProcedurePointerGetUnsignedInteger,                NULL);
    mape_set_native_function(0, gApe, "pointerGetInteger8Bit",                    _gsCProcedurePointerGetInteger8Bit,                    NULL);
    mape_set_native_function(0, gApe, "pointerGetUnsignedInteger8Bit",            _gsCProcedurePointerGetUnsignedInteger8Bit,            NULL);
    mape_set_native_function(0, gApe, "pointerGetAtOffsetNumber",                 _gsCProcedurePointerGetAtOffsetNumber,                 NULL);
    mape_set_native_function(0, gApe, "pointerGetAtOffsetInteger",                _gsCProcedurePointerGetAtOffsetInteger,                NULL);
    mape_set_native_function(0, gApe, "pointerGetAtOffsetUnsignedInteger",        _gsCProcedurePointerGetAtOffsetUnsignedInteger,        NULL);
    mape_set_native_function(0, gApe, "pointerGetAtOffsetInteger16Bit",           _gsCProcedurePointerGetAtOffsetInteger16Bit,           NULL);
    mape_set_native_function(0, gApe, "pointerGetAtOffsetUnsignedInteger16Bit",   _gsCProcedurePointerGetAtOffsetUnsignedInteger16Bit,   NULL);
    mape_set_native_function(0, gApe, "pointerGetAtOffsetNumber64Bit",            _gsCProcedurePointerGetAtOffsetNumber64Bit,            NULL);
    mape_set_native_function(0, gApe, "pointerGetAtOffsetInteger64Bit",           _gsCProcedurePointerGetAtOffsetInteger64Bit,           NULL);
    mape_set_native_function(0, gApe, "pointerGetAtOffsetUnsignedInteger64Bit",   _gsCProcedurePointerGetAtOffsetUnsignedInteger64Bit,   NULL);
    mape_set_native_function(0, gApe, "pointerSetBool",                           _gsCProcedurePointerSetBool,                           NULL);
    mape_set_native_function(0, gApe, "pointerSetString",                         _gsCProcedurePointerSetString,                         NULL);
    mape_set_native_function(0, gApe, "pointerSetStringExcludingNullChar",        _gsCProcedurePointerSetStringExcludingNullChar,        NULL);
    mape_set_native_function(0, gApe, "pointerSetSubstring",                      _gsCProcedurePointerSetSubstring,                      NULL);
    mape_set_native_function(0, gApe, "pointerSetNumber",                         _gsCProcedurePointerSetNumber,                         NULL);
    mape_set_native_function(0, gApe, "pointerSetInteger",                        _gsCProcedurePointerSetInteger,                        NULL);
    mape_set_native_function(0, gApe, "pointerSetUnsignedInteger",                _gsCProcedurePointerSetUnsignedInteger,                NULL);
    mape_set_native_function(0, gApe, "pointerSetInteger8Bit",                    _gsCProcedurePointerSetInteger8Bit,                    NULL);
    mape_set_native_function(0, gApe, "pointerSetUnsignedInteger8Bit",            _gsCProcedurePointerSetUnsignedInteger8Bit,            NULL);
    mape_set_native_function(0, gApe, "pointerSetAtOffsetNumber",                 _gsCProcedurePointerSetAtOffsetNumber,                 NULL);
    mape_set_native_function(0, gApe, "pointerSetAtOffsetInteger",                _gsCProcedurePointerSetAtOffsetInteger,                NULL);
    mape_set_native_function(0, gApe, "pointerSetAtOffsetUnsignedInteger",        _gsCProcedurePointerSetAtOffsetUnsignedInteger,        NULL);
    mape_set_native_function(0, gApe, "pointerSetAtOffsetInteger16Bit",           _gsCProcedurePointerSetAtOffsetInteger16Bit,           NULL);
    mape_set_native_function(0, gApe, "pointerSetAtOffsetUnsignedInteger16Bit",   _gsCProcedurePointerSetAtOffsetUnsignedInteger16Bit,   NULL);
    mape_set_native_function(0, gApe, "pointerSetAtOffsetNumber64Bit",            _gsCProcedurePointerSetAtOffsetNumber64Bit,            NULL);
    mape_set_native_function(0, gApe, "pointerSetAtOffsetInteger64Bit",           _gsCProcedurePointerSetAtOffsetInteger64Bit,           NULL);
    mape_set_native_function(0, gApe, "pointerSetAtOffsetUnsignedInteger64Bit",   _gsCProcedurePointerSetAtOffsetUnsignedInteger64Bit,   NULL);
    mape_set_native_function(0, gApe, "pointerGetRaw8Bit",                        _gsCProcedurePointerGetRaw8Bit,                        NULL);
    mape_set_native_function(0, gApe, "pointerGetRaw16Bit",                       _gsCProcedurePointerGetRaw16Bit,                       NULL);
    mape_set_native_function(0, gApe, "pointerGetRaw32Bit",                       _gsCProcedurePointerGetRaw32Bit,                       NULL);
    mape_set_native_function(0, gApe, "pointerGetRaw64Bit",                       _gsCProcedurePointerGetRaw64Bit,                       NULL);
    mape_set_native_function(0, gApe, "pointerSetRaw8Bit",                        _gsCProcedurePointerSetRaw8Bit,                        NULL);
    mape_set_native_function(0, gApe, "pointerSetRaw16Bit",                       _gsCProcedurePointerSetRaw16Bit,                       NULL);
    mape_set_native_function(0, gApe, "pointerSetRaw32Bit",                       _gsCProcedurePointerSetRaw32Bit,                       NULL);
    mape_set_native_function(0, gApe, "pointerSetRaw64Bit",                       _gsCProcedurePointerSetRaw64Bit,                       NULL);
    mape_set_native_function(0, gApe, "pointerIsNull",                            _gsCProcedurePointerIsNull,                            NULL);
    mape_set_native_function(0, gApe, "pointerGetNull",                           _gsCProcedurePointerGetNull,                           NULL);
    mape_set_native_function(0, gApe, "pointersAreEqual",                         _gsCProcedurePointersAreEqual,                         NULL);
    mape_set_native_function(0, gApe, "pointerOffsetByBytes",                     _gsCProcedurePointerOffsetByBytes,                     NULL);
    mape_set_native_function(0, gApe, "pointerDrawPixels",                        _gsCProcedurePointerDrawPixels,                        NULL);
    mape_set_native_function(0, gApe, "globalDynamicArrayNew",                    _gsCProcedureGlobalDynamicArrayNew,                    NULL);
    mape_set_native_function(0, gApe, "globalDynamicArrayPersistentNew",          _gsCProcedureGlobalDynamicArrayPersistentNew,          NULL);
    mape_set_native_function(0, gApe, "globalDynamicArrayDelete",                 _gsCProcedureGlobalDynamicArrayDelete,                 NULL);
    mape_set_native_function(0, gApe, "globalDynamicArrayPersistentDelete",       _gsCProcedureGlobalDynamicArrayPersistentDelete,       NULL);
    mape_set_native_function(0, gApe, "globalDynamicArrayDeleteAll",              _gsCProcedureGlobalDynamicArrayDeleteAll,              NULL);
    mape_set_native_function(0, gApe, "globalDynamicArrayPersistentDeleteAll",    _gsCProcedureGlobalDynamicArrayPersistentDeleteAll,    NULL);
    mape_set_native_function(0, gApe, "globalDynamicArrayGetHandle",              _gsCProcedureGlobalDynamicArrayGetHandle,              NULL);
    mape_set_native_function(0, gApe, "globalDynamicArrayPersistentGetHandle",    _gsCProcedureGlobalDynamicArrayPersistentGetHandle,    NULL);
    mape_set_native_function(0, gApe, "dynamicArrayGet",                          _gsCProcedureDynamicArrayGet,                          NULL);
    mape_set_native_function(0, gApe, "dynamicArraySet",                          _gsCProcedureDynamicArraySet,                          NULL);
    mape_set_native_function(0, gApe, "dynamicArrayAppend",                       _gsCProcedureDynamicArrayAppend,                       NULL);
    mape_set_native_function(0, gApe, "dynamicArrayRemoveAt",                     _gsCProcedureDynamicArrayRemoveAt,                     NULL);
    mape_set_native_function(0, gApe, "dynamicArrayRemoveLast",                   _gsCProcedureDynamicArrayRemoveLast,                   NULL);
    mape_set_native_function(0, gApe, "dynamicArrayGetSize",                      _gsCProcedureDynamicArrayGetSize,                      NULL);
    mape_set_native_function(0, gApe, "memset",                                   _gsCProcedureMemset,                                   NULL);
    mape_set_native_function(0, gApe, "memcpy",                                   _gsCProcedureMemcpy,                                   NULL);
    mape_set_native_function(0, gApe, "memcmp",                                   _gsCProcedureMemcmp,                                   NULL);
    mape_set_native_function(0, gApe, "threadSafeMemset",                         _gsCProcedureThreadSafeMemset,                         NULL);
    mape_set_native_function(0, gApe, "threadSafeMemcpy",                         _gsCProcedureThreadSafeMemcpy,                         NULL);
    mape_set_native_function(0, gApe, "threadSafeMemcmp",                         _gsCProcedureThreadSafeMemcmp,                         NULL);
    mape_set_native_function(0, gApe, "threadWaitForEqualUint64Value",            _gsCProcedureThreadWaitForEqualUint64Value,            NULL);
    mape_set_native_function(0, gApe, "threadWaitForEqualOrMoreThanUint64Value",  _gsCProcedureThreadWaitForEqualOrMoreThanUint64Value,  NULL);
    mape_set_native_function(0, gApe, "threadWaitForThread2FrameToFinish",        _gsCProcedureThreadWaitForThread2FrameToFinish,        NULL);
    mape_set_native_function(0, gApe, "strlenWithNullChar",                       _gsCProcedureStrlenWithNullChar,                       NULL);
    mape_set_native_function(0, gApe, "keyboardGetGlfwKeyEvent",                  _gsCProcedureKeyboardGetGlfwKeyEvent,                  NULL);
    mape_set_native_function(0, gApe, "keyboardGetGlfwKeyModifiers",              _gsCProcedureKeyboardGetGlfwKeyModifiers,              NULL);
    mape_set_native_function(0, gApe, "keyboardGetGlfwCodepointString",           _gsCProcedureKeyboardGetGlfwCodepointString,           NULL);
    mape_set_native_function(0, gApe, "mouseGlfwSetInputMode",                    _gsCProcedureMouseGlfwSetInputMode,                    NULL);
    mape_set_native_function(0, gApe, "mouseSetXY",                               _gsCProcedureMouseSetXY,                               NULL);
    mape_set_native_function(0, gApe, "mouseGetX",                                _gsCProcedureMouseGetX,                                NULL);
    mape_set_native_function(0, gApe, "mouseGetY",                                _gsCProcedureMouseGetY,                                NULL);
    mape_set_native_function(0, gApe, "mouseGetPreviousX",                        _gsCProcedureMouseGetPreviousX,                        NULL);
    mape_set_native_function(0, gApe, "mouseGetPreviousY",                        _gsCProcedureMouseGetPreviousY,                        NULL);
    mape_set_native_function(0, gApe, "mouseGetMoveEvent",                        _gsCProcedureMouseGetMoveEvent,                        NULL);
    mape_set_native_function(0, gApe, "mouseGetButtonIsPressed",                  _gsCProcedureMouseGetButtonIsPressed,                  NULL);
    mape_set_native_function(0, gApe, "mouseGetButtonIsPressedAndHeld",           _gsCProcedureMouseGetButtonIsPressedAndHeld,           NULL);
    mape_set_native_function(0, gApe, "mouseGetButtonIsReleased",                 _gsCProcedureMouseGetButtonIsReleased,                 NULL);
    mape_set_native_function(0, gApe, "mouseGetWheelScroll",                      _gsCProcedureMouseGetWheelScroll,                      NULL);
    mape_set_native_function(0, gApe, "gamepadIsPresent",                         _gsCProcedureGamepadIsPresent,                         NULL);
    mape_set_native_function(0, gApe, "gamepadGet15Buttons6AxesNumbers",          _gsCProcedureGamepadGet15Buttons6AxesNumbers,          NULL);
    mape_set_native_function(0, gApe, "gamepadGetName",                           _gsCProcedureGamepadGetName,                           NULL);
    mape_set_native_function(0, gApe, "gamepadGetGUID",                           _gsCProcedureGamepadGetGUID,                           NULL);
    mape_set_native_function(0, gApe, "gamepadUpdateGamecontrollerdbTxt",         _gsCProcedureGamepadUpdateGamecontrollerdbTxt,         NULL);
    mape_set_native_function(0, gApe, "boolToNumber",                             _gsCProcedureBoolToNumber,                             NULL);
    mape_set_native_function(0, gApe, "boolToString",                             _gsCProcedureBoolToString,                             NULL);
    mape_set_native_function(0, gApe, "numberFromRaw8BitInteger",                 _gsCProcedureNumberFromRaw8BitInteger,                NULL);
    mape_set_native_function(0, gApe, "numberFromRaw8BitUnsignedInteger",         _gsCProcedureNumberFromRaw8BitUnsignedInteger,        NULL);
    mape_set_native_function(0, gApe, "numberFromRaw16BitInteger",                _gsCProcedureNumberFromRaw16BitInteger,                NULL);
    mape_set_native_function(0, gApe, "numberFromRaw16BitUnsignedInteger",        _gsCProcedureNumberFromRaw16BitUnsignedInteger,        NULL);
    mape_set_native_function(0, gApe, "numberFromRaw32BitInteger",                _gsCProcedureNumberFromRaw32BitInteger,                NULL);
    mape_set_native_function(0, gApe, "numberFromRaw32BitUnsignedInteger",        _gsCProcedureNumberFromRaw32BitUnsignedInteger,        NULL);
    mape_set_native_function(0, gApe, "numberFromRaw32BitFloat",                  _gsCProcedureNumberFromRaw32BitFloat,                  NULL);
    mape_set_native_function(0, gApe, "numberFromRaw64BitInteger",                _gsCProcedureNumberFromRaw64BitInteger,                NULL);
    mape_set_native_function(0, gApe, "numberFromRaw64BitUnsignedInteger",        _gsCProcedureNumberFromRaw64BitUnsignedInteger,        NULL);
    mape_set_native_function(0, gApe, "numberToBool",                             _gsCProcedureNumberToBool,                             NULL);
    mape_set_native_function(0, gApe, "numberToString",                           _gsCProcedureNumberToString,                           NULL);
    mape_set_native_function(0, gApe, "numberToBinaryString",                     _gsCProcedureNumberToBinaryString,                     NULL);
    mape_set_native_function(0, gApe, "numberWholePartToString",                  _gsCProcedureNumberWholePartToString,                  NULL);
    mape_set_native_function(0, gApe, "stringCharToNumber",                       _gsCProcedureStringCharToNumber,                       NULL);
    mape_set_native_function(0, gApe, "stringToNumberArray",                      _gsCProcedureStringToNumberArray,                      NULL);
    mape_set_native_function(0, gApe, "interpretStringToInteger",                 _gsCProcedureInterpretStringToInteger,                 NULL);
    mape_set_native_function(0, gApe, "interpretStringToFloat",                   _gsCProcedureInterpretStringToFloat,                   NULL);
    mape_set_native_function(0, gApe, "interpretStringToDouble",                  _gsCProcedureInterpretStringToDouble,                  NULL);
    mape_set_native_function(0, gApe, "stringReadFromFile",                       _gsCProcedureStringReadFromFile,                       NULL);
    mape_set_native_function(0, gApe, "stringWriteToFile",                        _gsCProcedureStringWriteToFile,                        NULL);
    mape_set_native_function(0, gApe, "stringAppendToFile",                       _gsCProcedureStringAppendToFile,                       NULL);
    mape_set_native_function(0, gApe, "binaryGetByteSizeOfFile",                  _gsCProcedureBinaryGetByteSizeOfFile,                  NULL);
    mape_set_native_function(0, gApe, "binaryReadFromFile",                       _gsCProcedureBinaryReadFromFile,                       NULL);
    mape_set_native_function(0, gApe, "binaryWriteToFile",                        _gsCProcedureBinaryWriteToFile,                        NULL);
    mape_set_native_function(0, gApe, "getClipboardString",                       _gsCProcedureGetClipboardString,                       NULL);
    mape_set_native_function(0, gApe, "setClipboardString",                       _gsCProcedureSetClipboardString,                       NULL);
    mape_set_native_function(0, gApe, "gizmoSetMode",                             _gsCProcedureGizmoSetMode,                             NULL);
    mape_set_native_function(0, gApe, "gizmoGetVector",                           _gsCProcedureGizmoGetVector,                           NULL);
    mape_set_native_function(0, gApe, "gizmoGetVersor",                           _gsCProcedureGizmoGetVersor,                           NULL);
    mape_set_native_function(0, gApe, "gizmoGetScale",                            _gsCProcedureGizmoGetScale,                            NULL);
    mape_set_native_function(0, gApe, "gizmoSetVector",                           _gsCProcedureGizmoSetVector,                           NULL);
    mape_set_native_function(0, gApe, "gizmoSetVersor",                           _gsCProcedureGizmoSetVersor,                           NULL);
    mape_set_native_function(0, gApe, "gizmoSetScale",                            _gsCProcedureGizmoSetScale,                            NULL);
    mape_set_native_function(0, gApe, "gizmoSetDrawScale",                        _gsCProcedureGizmoSetDrawScale,                        NULL);
    mape_set_native_function(0, gApe, "gizmoSetDrawColors",                       _gsCProcedureGizmoSetDrawColors,                       NULL);
    mape_set_native_function(0, gApe, "gizmoDelete",                              _gsCProcedureGizmoDelete,                              NULL);
    mape_set_native_function(0, gApe, "gizmoDeleteAll",                           _gsCProcedureGizmoDeleteAll,                           NULL);
    mape_set_native_function(0, gApe, "getLastFrameTime",                         _gsCProcedureGetLastFrameTime,                         NULL);
    mape_set_native_function(0, gApe, "getSystemTimeMillis",                      _gsCProcedureGetSystemTimeMillis,                      NULL);
    mape_set_native_function(0, gApe, "getSystemTimeMicros",                      _gsCProcedureGetSystemTimeMicros,                      NULL);
    mape_set_native_function(0, gApe, "getUnixTime",                              _gsCProcedureGetUnixTime,                              NULL);
    mape_set_native_function(0, gApe, "framebufferBegin",                         _gsCProcedureFramebufferBegin,                         NULL);
    mape_set_native_function(0, gApe, "framebufferEnd",                           _gsCProcedureFramebufferEnd,                           NULL);
    mape_set_native_function(0, gApe, "framebufferDraw",                          _gsCProcedureFramebufferDraw,                          NULL);
    mape_set_native_function(0, gApe, "framebufferClear",                         _gsCProcedureFramebufferClear,                         NULL);
    mape_set_native_function(0, gApe, "framebufferCopyToImage",                   _gsCProcedureFramebufferCopyToImage,                   NULL);
    mape_set_native_function(0, gApe, "framebufferDelete",                        _gsCProcedureFramebufferDelete,                        NULL);
    mape_set_native_function(0, gApe, "framebufferDeleteAll",                     _gsCProcedureFramebufferDeleteAll,                     NULL);
    mape_set_native_function(0, gApe, "meshNew",                                  _gsCProcedureMeshNew,                                  NULL);
    mape_set_native_function(0, gApe, "meshPersistentNew",                        _gsCProcedureMeshPersistentNew,                        NULL);
    mape_set_native_function(0, gApe, "meshDelete",                               _gsCProcedureMeshDelete,                               NULL);
    mape_set_native_function(0, gApe, "meshPersistentDelete",                     _gsCProcedureMeshPersistentDelete,                     NULL);
    mape_set_native_function(0, gApe, "meshDeleteAll",                            _gsCProcedureMeshDeleteAll,                            NULL);
    mape_set_native_function(0, gApe, "meshPersistentDeleteAll",                  _gsCProcedureMeshPersistentDeleteAll,                  NULL);
    mape_set_native_function(0, gApe, "meshGetHandle",                            _gsCProcedureMeshGetHandle,                            NULL);
    mape_set_native_function(0, gApe, "meshPersistentGetHandle",                  _gsCProcedureMeshPersistentGetHandle,                  NULL);
    mape_set_native_function(0, gApe, "meshIsUsingColors",                        _gsCProcedureMeshIsUsingColors,                        NULL);
    mape_set_native_function(0, gApe, "meshIsUsingTextures",                      _gsCProcedureMeshIsUsingTextures,                      NULL);
    mape_set_native_function(0, gApe, "meshIsUsingIndices",                       _gsCProcedureMeshIsUsingIndices,                       NULL);
    mape_set_native_function(0, gApe, "meshEnableColors",                         _gsCProcedureMeshEnableColors,                         NULL);
    mape_set_native_function(0, gApe, "meshEnableTextures",                       _gsCProcedureMeshEnableTextures,                       NULL);
    mape_set_native_function(0, gApe, "meshEnableIndices",                        _gsCProcedureMeshEnableIndices,                        NULL);
    mape_set_native_function(0, gApe, "meshDisableColors",                        _gsCProcedureMeshDisableColors,                        NULL);
    mape_set_native_function(0, gApe, "meshDisableTextures",                      _gsCProcedureMeshDisableTextures,                      NULL);
    mape_set_native_function(0, gApe, "meshDisableIndices",                       _gsCProcedureMeshDisableIndices,                       NULL);
    mape_set_native_function(0, gApe, "meshHasVertices",                          _gsCProcedureMeshHasVertices,                          NULL);
    mape_set_native_function(0, gApe, "meshHasColors",                            _gsCProcedureMeshHasColors,                            NULL);
    mape_set_native_function(0, gApe, "meshHasTexCoords",                         _gsCProcedureMeshHasTexCoords,                         NULL);
    mape_set_native_function(0, gApe, "meshHasIndices",                           _gsCProcedureMeshHasIndices,                           NULL);
    mape_set_native_function(0, gApe, "meshGetVerticesCount",                     _gsCProcedureMeshGetVerticesCount,                     NULL);
    mape_set_native_function(0, gApe, "meshGetColorsCount",                       _gsCProcedureMeshGetColorsCount,                       NULL);
    mape_set_native_function(0, gApe, "meshGetTexCoordsCount",                    _gsCProcedureMeshGetTexCoordsCount,                    NULL);
    mape_set_native_function(0, gApe, "meshGetIndicesCount",                      _gsCProcedureMeshGetIndicesCount,                      NULL);
    mape_set_native_function(0, gApe, "meshHaveVerticesChanged",                  _gsCProcedureMeshHaveVerticesChanged,                  NULL);
    mape_set_native_function(0, gApe, "meshHaveColorsChanged",                    _gsCProcedureMeshHaveColorsChanged,                    NULL);
    mape_set_native_function(0, gApe, "meshHaveTexCoordsChanged",                 _gsCProcedureMeshHaveTexCoordsChanged,                 NULL);
    mape_set_native_function(0, gApe, "meshHaveIndicesChanged",                   _gsCProcedureMeshHaveIndicesChanged,                   NULL);
    mape_set_native_function(0, gApe, "meshAddVertex",                            _gsCProcedureMeshAddVertex,                            NULL);
    mape_set_native_function(0, gApe, "meshAddColor",                             _gsCProcedureMeshAddColor,                             NULL);
    mape_set_native_function(0, gApe, "meshAddTexCoord",                          _gsCProcedureMeshAddTexCoord,                          NULL);
    mape_set_native_function(0, gApe, "meshAddIndex",                             _gsCProcedureMeshAddIndex,                             NULL);
    mape_set_native_function(0, gApe, "meshRemoveVertex",                         _gsCProcedureMeshRemoveVertex,                         NULL);
    mape_set_native_function(0, gApe, "meshRemoveColor",                          _gsCProcedureMeshRemoveColor,                          NULL);
    mape_set_native_function(0, gApe, "meshRemoveTexCoord",                       _gsCProcedureMeshRemoveTexCoord,                       NULL);
    mape_set_native_function(0, gApe, "meshRemoveIndex",                          _gsCProcedureMeshRemoveIndex,                          NULL);
    mape_set_native_function(0, gApe, "meshClear",                                _gsCProcedureMeshClear,                                NULL);
    mape_set_native_function(0, gApe, "meshClearVertices",                        _gsCProcedureMeshClearVertices,                        NULL);
    mape_set_native_function(0, gApe, "meshClearColors",                          _gsCProcedureMeshClearColors,                          NULL);
    mape_set_native_function(0, gApe, "meshClearTexCoords",                       _gsCProcedureMeshClearTexCoords,                       NULL);
    mape_set_native_function(0, gApe, "meshClearIndices",                         _gsCProcedureMeshClearIndices,                         NULL);
    mape_set_native_function(0, gApe, "meshGetVerticesPointer",                   _gsCProcedureMeshGetVerticesPointer,                   NULL);
    mape_set_native_function(0, gApe, "meshGetColorsPointer",                     _gsCProcedureMeshGetColorsPointer,                     NULL);
    mape_set_native_function(0, gApe, "meshGetTexCoordsPointer",                  _gsCProcedureMeshGetTexCoordsPointer,                  NULL);
    mape_set_native_function(0, gApe, "meshGetIndicesPointer",                    _gsCProcedureMeshGetIndicesPointer,                    NULL);
    mape_set_native_function(0, gApe, "meshMergeDuplicateVertices",               _gsCProcedureMeshMergeDuplicateVertices,               NULL);
    mape_set_native_function(0, gApe, "meshSetupIndicesAuto",                     _gsCProcedureMeshSetupIndicesAuto,                     NULL);
    mape_set_native_function(0, gApe, "meshAddTriangle",                          _gsCProcedureMeshAddTriangle,                          NULL);
    mape_set_native_function(0, gApe, "meshDraw",                                 _gsCProcedureMeshDraw,                                 NULL);
    mape_set_native_function(0, gApe, "meshDrawWithColor",                        _gsCProcedureMeshDrawWithColor,                        NULL);
    mape_set_native_function(0, gApe, "meshDrawDebugVertices",                    _gsCProcedureMeshDrawDebugVertices,                    NULL);
    mape_set_native_function(0, gApe, "meshDrawDebugColors",                      _gsCProcedureMeshDrawDebugColors,                      NULL);
    mape_set_native_function(0, gApe, "meshDrawDebugTexCoords",                   _gsCProcedureMeshDrawDebugTexCoords,                   NULL);
    mape_set_native_function(0, gApe, "meshDrawDebugIndices",                     _gsCProcedureMeshDrawDebugIndices,                     NULL);
    mape_set_native_function(0, gApe, "meshDrawDebugRayTraceIndices",             _gsCProcedureMeshDrawDebugRayTraceIndices,             NULL);
    mape_set_native_function(0, gApe, "meshImporterGetMeshesCount",               _gsCProcedureMeshImporterGetMeshesCount,               NULL);
    mape_set_native_function(0, gApe, "meshImporterGetMeshName",                  _gsCProcedureMeshImporterGetMeshName,                  NULL);
    mape_set_native_function(0, gApe, "meshImporterGetMesh",                      _gsCProcedureMeshImporterGetMesh,                      NULL);
    mape_set_native_function(0, gApe, "meshImporterDelete",                       _gsCProcedureMeshImporterDelete,                       NULL);
    mape_set_native_function(0, gApe, "meshImporterDeleteAll",                    _gsCProcedureMeshImporterDeleteAll,                    NULL);
    mape_set_native_function(0, gApe, "imageNew",                                 _gsCProcedureImageNew,                                 NULL);
    mape_set_native_function(0, gApe, "imagePersistentNew",                       _gsCProcedureImagePersistentNew,                       NULL);
    mape_set_native_function(0, gApe, "imageNewFromFile",                         _gsCProcedureImageNewFromFile,                         NULL);
    mape_set_native_function(0, gApe, "imagePersistentNewFromFile",               _gsCProcedureImagePersistentNewFromFile,               NULL);
    mape_set_native_function(0, gApe, "imageDelete",                              _gsCProcedureImageDelete,                              NULL);
    mape_set_native_function(0, gApe, "imagePersistentDelete",                    _gsCProcedureImagePersistentDelete,                    NULL);
    mape_set_native_function(0, gApe, "imageDeleteAll",                           _gsCProcedureImageDeleteAll,                           NULL);
    mape_set_native_function(0, gApe, "imagePersistentDeleteAll",                 _gsCProcedureImagePersistentDeleteAll,                 NULL);
    mape_set_native_function(0, gApe, "imageGetHandle",                           _gsCProcedureImageGetHandle,                           NULL);
    mape_set_native_function(0, gApe, "imagePersistentGetHandle",                 _gsCProcedureImagePersistentGetHandle,                 NULL);
    mape_set_native_function(0, gApe, "imageLoadFromMemory",                      _gsCProcedureImageLoadFromMemory,                      NULL);
    mape_set_native_function(0, gApe, "imageClear",                               _gsCProcedureImageClear,                               NULL);
    mape_set_native_function(0, gApe, "imageHasMipmap",                           _gsCProcedureImageHasMipmap,                           NULL);
    mape_set_native_function(0, gApe, "imageMipmapDisable",                       _gsCProcedureImageMipmapDisable,                       NULL);
    mape_set_native_function(0, gApe, "imageMipmapEnable",                        _gsCProcedureImageMipmapEnable,                        NULL);
    mape_set_native_function(0, gApe, "imageMipmapGenerate",                      _gsCProcedureImageMipmapGenerate,                      NULL);
    mape_set_native_function(0, gApe, "imageSetTextureMinMagFilter",              _gsCProcedureImageSetTextureMinMagFilter,              NULL);
    mape_set_native_function(0, gApe, "imageSetTextureWrap",                      _gsCProcedureImageSetTextureWrap,                      NULL);
    mape_set_native_function(0, gApe, "imageSetTextureMaxAnisotropy",             _gsCProcedureImageSetTextureMaxAnisotropy,             NULL);
    mape_set_native_function(0, gApe, "imageGetWidth",                            _gsCProcedureImageGetWidth,                            NULL);
    mape_set_native_function(0, gApe, "imageGetHeight",                           _gsCProcedureImageGetHeight,                           NULL);
    mape_set_native_function(0, gApe, "imageGetBitsPerPixel",                     _gsCProcedureImageGetBitsPerPixel,                     NULL);
    mape_set_native_function(0, gApe, "imageGetImageType",                        _gsCProcedureImageGetImageType,                        NULL);
    mape_set_native_function(0, gApe, "imageGetPixelsPointer",                    _gsCProcedureImageGetPixelsPointer,                    NULL);
    mape_set_native_function(0, gApe, "imageGetColor",                            _gsCProcedureImageGetColor,                            NULL);
    mape_set_native_function(0, gApe, "imageSetColor",                            _gsCProcedureImageSetColor,                            NULL);
    mape_set_native_function(0, gApe, "imageGammaCorrect",                        _gsCProcedureImageGammaCorrect,                        NULL);
    mape_set_native_function(0, gApe, "imageUpdate",                              _gsCProcedureImageUpdate,                              NULL);
    mape_set_native_function(0, gApe, "imageBind",                                _gsCProcedureImageBind,                                NULL);
    mape_set_native_function(0, gApe, "imageUnbind",                              _gsCProcedureImageUnbind,                              NULL);
    mape_set_native_function(0, gApe, "imageDraw",                                _gsCProcedureImageDraw,                                NULL);
    mape_set_native_function(0, gApe, "imageDrawSubsection",                      _gsCProcedureImageDrawSubsection,                      NULL);
    mape_set_native_function(0, gApe, "shaderBegin",                              _gsCProcedureShaderBegin,                              NULL);
    mape_set_native_function(0, gApe, "shaderEnd",                                _gsCProcedureShaderEnd,                                NULL);
    mape_set_native_function(0, gApe, "shaderSetUniform4f",                       _gsCProcedureShaderSetUniform4f,                       NULL);
    mape_set_native_function(0, gApe, "shaderSetUniform4fv",                      _gsCProcedureShaderSetUniform4fv,                      NULL);
    mape_set_native_function(0, gApe, "shaderSetUniformMatrix4f",                 _gsCProcedureShaderSetUniformMatrix4f,                 NULL);
    mape_set_native_function(0, gApe, "shaderSetUniformImage",                    _gsCProcedureShaderSetUniformImage,                    NULL);
    mape_set_native_function(0, gApe, "shaderDelete",                             _gsCProcedureShaderDelete,                             NULL);
    mape_set_native_function(0, gApe, "shaderDeleteAll",                          _gsCProcedureShaderDeleteAll,                          NULL);
    mape_set_native_function(0, gApe, "soundPlayerNew",                           _gsCProcedureSoundPlayerNew,                           NULL);
    mape_set_native_function(0, gApe, "soundPlayerPersistentNew",                 _gsCProcedureSoundPlayerPersistentNew,                 NULL);
    mape_set_native_function(0, gApe, "soundPlayerDelete",                        _gsCProcedureSoundPlayerDelete,                        NULL);
    mape_set_native_function(0, gApe, "soundPlayerPersistentDelete",              _gsCProcedureSoundPlayerPersistentDelete,              NULL);
    mape_set_native_function(0, gApe, "soundPlayerDeleteAll",                     _gsCProcedureSoundPlayerDeleteAll,                     NULL);
    mape_set_native_function(0, gApe, "soundPlayerPersistentDeleteAll",           _gsCProcedureSoundPlayerPersistentDeleteAll,           NULL);
    mape_set_native_function(0, gApe, "soundPlayerGetHandle",                     _gsCProcedureSoundPlayerGetHandle,                     NULL);
    mape_set_native_function(0, gApe, "soundPlayerPersistentGetHandle",           _gsCProcedureSoundPlayerPersistentGetHandle,           NULL);
    mape_set_native_function(0, gApe, "soundPlayerLoad",                          _gsCProcedureSoundPlayerLoad,                          NULL);
    mape_set_native_function(0, gApe, "soundPlayerUnload",                        _gsCProcedureSoundPlayerUnload,                        NULL);
    mape_set_native_function(0, gApe, "soundPlayerPlay",                          _gsCProcedureSoundPlayerPlay,                          NULL);
    mape_set_native_function(0, gApe, "soundPlayerStop",                          _gsCProcedureSoundPlayerStop,                          NULL);
    mape_set_native_function(0, gApe, "soundPlayerSetVolume",                     _gsCProcedureSoundPlayerSetVolume,                     NULL);
    mape_set_native_function(0, gApe, "soundPlayerSetPan",                        _gsCProcedureSoundPlayerSetPan,                        NULL);
    mape_set_native_function(0, gApe, "soundPlayerSetSpeed",                      _gsCProcedureSoundPlayerSetSpeed,                      NULL);
    mape_set_native_function(0, gApe, "soundPlayerSetPaused",                     _gsCProcedureSoundPlayerSetPaused,                     NULL);
    mape_set_native_function(0, gApe, "soundPlayerSetLoop",                       _gsCProcedureSoundPlayerSetLoop,                       NULL);
    mape_set_native_function(0, gApe, "soundPlayerSetMultiPlay",                  _gsCProcedureSoundPlayerSetMultiPlay,                  NULL);
    mape_set_native_function(0, gApe, "soundPlayerSetPosition",                   _gsCProcedureSoundPlayerSetPosition,                   NULL);
    mape_set_native_function(0, gApe, "soundPlayerSetPositionMS",                 _gsCProcedureSoundPlayerSetPositionMS,                 NULL);
    mape_set_native_function(0, gApe, "soundPlayerGetPositionMS",                 _gsCProcedureSoundPlayerGetPositionMS,                 NULL);
    mape_set_native_function(0, gApe, "soundPlayerGetPosition",                   _gsCProcedureSoundPlayerGetPosition,                   NULL);
    mape_set_native_function(0, gApe, "soundPlayerIsPlaying",                     _gsCProcedureSoundPlayerIsPlaying,                     NULL);
    mape_set_native_function(0, gApe, "soundPlayerGetSpeed",                      _gsCProcedureSoundPlayerGetSpeed,                      NULL);
    mape_set_native_function(0, gApe, "soundPlayerGetPan",                        _gsCProcedureSoundPlayerGetPan,                        NULL);
    mape_set_native_function(0, gApe, "soundPlayerGetVolume",                     _gsCProcedureSoundPlayerGetVolume,                     NULL);
    mape_set_native_function(0, gApe, "soundPlayerIsLoaded",                      _gsCProcedureSoundPlayerIsLoaded,                      NULL);
    mape_set_native_function(0, gApe, "soundSetVolume",                           _gsCProcedureSoundSetVolume,                           NULL);
    mape_set_native_function(0, gApe, "soundShutdown",                            _gsCProcedureSoundShutdown,                            NULL);
    mape_set_native_function(0, gApe, "soundStopAll",                             _gsCProcedureSoundStopAll,                             NULL);
    mape_set_native_function(0, gApe, "soundUpdate",                              _gsCProcedureSoundUpdate,                              NULL);
    mape_set_native_function(0, gApe, "imguiBegin",                               _gsCProcedureImguiBegin,                               NULL);
    mape_set_native_function(0, gApe, "imguiEnd",                                 _gsCProcedureImguiEnd,                                 NULL);
    mape_set_native_function(0, gApe, "imguiWindowBegin",                         _gsCProcedureImguiWindowBegin,                         NULL);
    mape_set_native_function(0, gApe, "imguiWindowEnd",                           _gsCProcedureImguiWindowEnd,                           NULL);
    mape_set_native_function(0, gApe, "imguiButton",                              _gsCProcedureImguiButton,                              NULL);
    mape_set_native_function(0, gApe, "imguiText",                                _gsCProcedureImguiText,                                NULL);
    mape_set_native_function(0, gApe, "imguiTextMultiline",                       _gsCProcedureImguiTextMultiline,                       NULL);
    mape_set_native_function(0, gApe, "imguiInputText",                           _gsCProcedureImguiInputText,                           NULL);
    mape_set_native_function(0, gApe, "imguiInputTextMultiline",                  _gsCProcedureImguiInputTextMultiline,                  NULL);
    mape_set_native_function(0, gApe, "profileBegin",                             _gsCProcedureProfileBegin,                             NULL);
    mape_set_native_function(0, gApe, "profileEnd",                               _gsCProcedureProfileEnd,                               NULL);
    mape_set_native_function(0, gApe, "systemCommand",                            _gsCProcedureSystemCommand,                            NULL);
    mape_set_native_function(0, gApe, "glGetIntegerv",                            _gsCProcedureGlGetIntegerv,                            NULL);
    mape_set_native_function(0, gApe, "getUniqueNumber",                          _gsCProcedureGetUniqueNumber,                          NULL);
    mape_set_native_function(0, gApe, "getUint64Max",                             _gsCProcedureGetUint64Max,                             NULL);
    mape_set_native_function(0, gApe, "getLibGameHandle",                         _gsCProcedureGetLibGameHandle,                         NULL);
    mape_set_native_function(0, gApe, "getLibThread2Handle",                      _gsCProcedureGetLibThread2Handle,                      NULL);
    mape_set_native_function(0, gApe, "getGlfwWindowHandle",                      _gsCProcedureGetGlfwWindowHandle,                      NULL);
    mape_set_native_function(0, gApe, "getLastDragAndDropCounter",                _gsCProcedureGetLastDragAndDropCounter,                NULL);
    mape_set_native_function(0, gApe, "getLastDragAndDropFilepathsCount",         _gsCProcedureGetLastDragAndDropFilepathsCount,         NULL);
    mape_set_native_function(0, gApe, "getLastDragAndDropFilepath",               _gsCProcedureGetLastDragAndDropFilepath,               NULL);
    mape_set_native_function(0, gApe, "getLastDragAndDropPositionX",              _gsCProcedureGetLastDragAndDropPositionX,              NULL);
    mape_set_native_function(0, gApe, "getLastDragAndDropPositionY",              _gsCProcedureGetLastDragAndDropPositionY,              NULL);
    mape_set_native_function(0, gApe, "githubR_lyehLz4xEncode",                        _gsCProcedureGithubR_lyehLz4xEncode,                        NULL);
    mape_set_native_function(0, gApe, "githubR_lyehLz4xDecode",                        _gsCProcedureGithubR_lyehLz4xDecode,                        NULL);
    mape_set_native_function(0, gApe, "githubR_lyehLz4xBoundsEncodeOutBytesCount",     _gsCProcedureGithubR_lyehLz4xBoundsEncodeOutBytesCount,     NULL);
    mape_set_native_function(0, gApe, "githubR_lyehUlzEncode",                         _gsCProcedureGithubR_lyehUlzEncode,                         NULL);
    mape_set_native_function(0, gApe, "githubR_lyehUlzDecode",                         _gsCProcedureGithubR_lyehUlzDecode,                         NULL);
    mape_set_native_function(0, gApe, "githubR_lyehUlzBoundsEncodeOutBytesCount",      _gsCProcedureGithubR_lyehUlzBoundsEncodeOutBytesCount,      NULL);
    mape_set_native_function(0, gApe, "thread2Run",                                    _gsCProcedureThread2Run,                                    NULL);
    mape_set_native_function(0, gApe, "thread2StopAndWaitFor",                         _gsCProcedureThread2StopAndWaitFor,                         NULL);
    mape_set_native_function(0, gApe, "thread2IsRunning",                              _gsCProcedureThread2IsRunning,                              NULL);
    mape_set_native_function(0, gApe, "getGameScriptString",                           _gsCProcedureGetGameScriptString,                           NULL);
    mape_set_native_function(0, gApe, "setGameScriptStringForNextFrame",               _gsCProcedureSetGameScriptStringForNextFrame,               NULL);
    mape_set_native_function(0, gApe, "setGameScriptStringForNextFrameFromPointer",    _gsCProcedureSetGameScriptStringForNextFrameFromPointer,    NULL);
    mape_set_native_function(0, gApe, "getThread2ScriptString",                        _gsCProcedureGetThread2ScriptString,                        NULL);
    mape_set_native_function(0, gApe, "setThread2ScriptStringForNextFrame",            _gsCProcedureSetThread2ScriptStringForNextFrame,            NULL);
    mape_set_native_function(0, gApe, "setThread2ScriptStringForNextFrameFromPointer", _gsCProcedureSetThread2ScriptStringForNextFrameFromPointer, NULL);
    mape_set_native_function(0, gApe, "libGameScriptExternalProcedureReload",          _gsCProcedureLibGameScriptExternalProcedureReload,          NULL);
    mape_set_native_function(0, gApe, "libGameScriptExternalProcedureCall2",           _gsCProcedureLibGameScriptExternalProcedureCall2,           NULL);
    mape_set_native_function(0, gApe, "libGameScriptExternalProcedureCall3",           _gsCProcedureLibGameScriptExternalProcedureCall3,           NULL);
    mape_set_native_function(0, gApe, "programGetArgumentsCount",                      _gsCProcedureProgramGetArgumentsCount,                      NULL);
    mape_set_native_function(0, gApe, "programGetArgument",                            _gsCProcedureProgramGetArgument,                            NULL);
    mape_set_native_function(0, gApe, "programClose",                                  _gsCProcedureProgramClose,                                  NULL);
    mape_set_native_function(0, gApe, "asin",                                          _gsCProcedureAsin,                                          NULL);
    mape_set_native_function(0, gApe, "acos",                                          _gsCProcedureAcos,                                          NULL);
    mape_set_native_function(0, gApe, "atan",                                          _gsCProcedureAtan,                                          NULL);
    mape_set_native_function(0, gApe, "atan2",                                         _gsCProcedureAtan2,                                         NULL);
    mape_set_native_function(0, gApe, "globalMeshesGetCount",                                          _gsCProcedureGlobalMeshesGetCount,                                          NULL);
    mape_set_native_function(0, gApe, "globalMeshesPersistentGetCount",                                _gsCProcedureGlobalMeshesPersistentGetCount,                                NULL);
    mape_set_native_function(0, gApe, "globalMeshesGetMeshLabelByMeshIndex",                           _gsCProcedureGlobalMeshesGetMeshLabelByMeshIndex,                           NULL);
    mape_set_native_function(0, gApe, "globalMeshesPersistentGetMeshLabelByMeshIndex",                 _gsCProcedureGlobalMeshesPersistentGetMeshLabelByMeshIndex,                 NULL);
    mape_set_native_function(0, gApe, "globalMeshesGetMeshHandleByMeshIndex",                          _gsCProcedureGlobalMeshesGetMeshHandleByMeshIndex,                          NULL);
    mape_set_native_function(0, gApe, "globalMeshesPersistentGetMeshHandleByMeshIndex",                _gsCProcedureGlobalMeshesPersistentGetMeshHandleByMeshIndex,                NULL);
    mape_set_native_function(0, gApe, "globalMeshesGetHaveVerticesChangedMeshIndexesCount",            _gsCProcedureGlobalMeshesGetHaveVerticesChangedMeshIndexesCount,            NULL);
    mape_set_native_function(0, gApe, "globalMeshesGetHaveColorsChangedMeshIndexesCount",              _gsCProcedureGlobalMeshesGetHaveColorsChangedMeshIndexesCount,              NULL);
    mape_set_native_function(0, gApe, "globalMeshesGetHaveTexCoordsChangedMeshIndexesCount",           _gsCProcedureGlobalMeshesGetHaveTexCoordsChangedMeshIndexesCount,           NULL);
    mape_set_native_function(0, gApe, "globalMeshesGetHaveIndicesChangedMeshIndexesCount",             _gsCProcedureGlobalMeshesGetHaveIndicesChangedMeshIndexesCount,             NULL);
    mape_set_native_function(0, gApe, "globalMeshesPersistentGetHaveVerticesChangedMeshIndexesCount",  _gsCProcedureGlobalMeshesPersistentGetHaveVerticesChangedMeshIndexesCount,  NULL);
    mape_set_native_function(0, gApe, "globalMeshesPersistentGetHaveColorsChangedMeshIndexesCount",    _gsCProcedureGlobalMeshesPersistentGetHaveColorsChangedMeshIndexesCount,    NULL);
    mape_set_native_function(0, gApe, "globalMeshesPersistentGetHaveTexCoordsChangedMeshIndexesCount", _gsCProcedureGlobalMeshesPersistentGetHaveTexCoordsChangedMeshIndexesCount, NULL);
    mape_set_native_function(0, gApe, "globalMeshesPersistentGetHaveIndicesChangedMeshIndexesCount",   _gsCProcedureGlobalMeshesPersistentGetHaveIndicesChangedMeshIndexesCount,   NULL);
    mape_set_native_function(0, gApe, "globalMeshesGetHaveVerticesChangedMeshIndexes",                 _gsCProcedureGlobalMeshesGetHaveVerticesChangedMeshIndexes,                 NULL);
    mape_set_native_function(0, gApe, "globalMeshesGetHaveColorsChangedMeshIndexes",                   _gsCProcedureGlobalMeshesGetHaveColorsChangedMeshIndexes,                   NULL);
    mape_set_native_function(0, gApe, "globalMeshesGetHaveTexCoordsChangedMeshIndexes",                _gsCProcedureGlobalMeshesGetHaveTexCoordsChangedMeshIndexes,                NULL);
    mape_set_native_function(0, gApe, "globalMeshesGetHaveIndicesChangedMeshIndexes",                  _gsCProcedureGlobalMeshesGetHaveIndicesChangedMeshIndexes,                  NULL);
    mape_set_native_function(0, gApe, "globalMeshesPersistentGetHaveVerticesChangedMeshIndexes",       _gsCProcedureGlobalMeshesPersistentGetHaveVerticesChangedMeshIndexes,       NULL);
    mape_set_native_function(0, gApe, "globalMeshesPersistentGetHaveColorsChangedMeshIndexes",         _gsCProcedureGlobalMeshesPersistentGetHaveColorsChangedMeshIndexes,         NULL);
    mape_set_native_function(0, gApe, "globalMeshesPersistentGetHaveTexCoordsChangedMeshIndexes",      _gsCProcedureGlobalMeshesPersistentGetHaveTexCoordsChangedMeshIndexes,      NULL);
    mape_set_native_function(0, gApe, "globalMeshesPersistentGetHaveIndicesChangedMeshIndexes",        _gsCProcedureGlobalMeshesPersistentGetHaveIndicesChangedMeshIndexes,        NULL);
    mape_set_native_function(0, gApe, "globalKeyPropertyGetKeyLabelsCount",                            _gsCProcedureGlobalKeyPropertyGetKeyLabelsCount,                            NULL);
    mape_set_native_function(0, gApe, "globalKeyPropertyIsKeyLabelExists",                             _gsCProcedureGlobalKeyPropertyIsKeyLabelExists,                             NULL);
    mape_set_native_function(0, gApe, "globalKeyPropertyGetKeyLabelByKeyIndex",                        _gsCProcedureGlobalKeyPropertyGetKeyLabelByKeyIndex,                        NULL);
    mape_set_native_function(0, gApe, "globalKeyPropertyGetKeyPropertyLabelsCount",                    _gsCProcedureGlobalKeyPropertyGetKeyPropertyLabelsCount,                    NULL);
    mape_set_native_function(0, gApe, "globalKeyPropertyIsKeyPropertyLabelExists",                     _gsCProcedureGlobalKeyPropertyIsKeyPropertyLabelExists,                     NULL);
    mape_set_native_function(0, gApe, "globalKeyPropertyGetKeyPropertyLabelByPropertyIndex",           _gsCProcedureGlobalKeyPropertyGetKeyPropertyLabelByPropertyIndex,           NULL);
    mape_set_native_function(0, gApe, "globalKeyPropertyRemoveKey",                                    _gsCProcedureGlobalKeyPropertyRemoveKey,                                    NULL);
    mape_set_native_function(0, gApe, "globalKeyPropertyRemoveAllKeys",                                _gsCProcedureGlobalKeyPropertyRemoveAllKeys,                                NULL);
    mape_set_native_function(0, gApe, "globalKeyPropertyRemoveProperty",                               _gsCProcedureGlobalKeyPropertyRemoveProperty,                               NULL);
    mape_set_native_function(0, gApe, "globalKeyPropertyRemoveAllProperties",                          _gsCProcedureGlobalKeyPropertyRemoveAllProperties,                          NULL);
    mape_set_native_function(0, gApe, "globalKeyPropertySetString",                                    _gsCProcedureGlobalKeyPropertySetString,                                    NULL);
    mape_set_native_function(0, gApe, "globalKeyPropertySetNumber",                                    _gsCProcedureGlobalKeyPropertySetNumber,                                    NULL);
    mape_set_native_function(0, gApe, "globalKeyPropertySetBool",                                      _gsCProcedureGlobalKeyPropertySetBool,                                      NULL);
    mape_set_native_function(0, gApe, "globalKeyPropertyGetString",                                    _gsCProcedureGlobalKeyPropertyGetString,                                    NULL);
    mape_set_native_function(0, gApe, "globalKeyPropertyGetNumber",                                    _gsCProcedureGlobalKeyPropertyGetNumber,                                    NULL);
    mape_set_native_function(0, gApe, "globalKeyPropertyGetBool",                                      _gsCProcedureGlobalKeyPropertyGetBool,                                      NULL);
    if (gEmbreeIsEnabled == 1) {
      mape_set_native_function(0, gApe, "ertAffineSpace3fGetSizeOfInBytes",            _gsCProcedureErtAffineSpace3fGetSizeOfInBytes,              NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fSetDefaultInitialize",        _gsCProcedureErtAffineSpace3fSetDefaultInitialize,          NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fSetInitialize",               _gsCProcedureErtAffineSpace3fSetInitialize,                 NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fSetLookAtPoint",              _gsCProcedureErtAffineSpace3fSetLookAtPoint,                NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fScale",                       _gsCProcedureErtAffineSpace3fScale,                         NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fTranslate",                   _gsCProcedureErtAffineSpace3fTranslate,                     NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fRotate",                      _gsCProcedureErtAffineSpace3fRotate,                        NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fGetLVXX",                     _gsCProcedureErtAffineSpace3fGetLVXX,                       NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fGetLVXY",                     _gsCProcedureErtAffineSpace3fGetLVXY,                       NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fGetLVXZ",                     _gsCProcedureErtAffineSpace3fGetLVXZ,                       NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fGetLVYX",                     _gsCProcedureErtAffineSpace3fGetLVYX,                       NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fGetLVYY",                     _gsCProcedureErtAffineSpace3fGetLVYY,                       NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fGetLVYZ",                     _gsCProcedureErtAffineSpace3fGetLVYZ,                       NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fGetLVZX",                     _gsCProcedureErtAffineSpace3fGetLVZX,                       NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fGetLVZY",                     _gsCProcedureErtAffineSpace3fGetLVZY,                       NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fGetLVZZ",                     _gsCProcedureErtAffineSpace3fGetLVZZ,                       NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fGetPX",                       _gsCProcedureErtAffineSpace3fGetPX,                         NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fGetPY",                       _gsCProcedureErtAffineSpace3fGetPY,                         NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fGetPZ",                       _gsCProcedureErtAffineSpace3fGetPZ,                         NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fCopyFromArray",               _gsCProcedureErtAffineSpace3fCopyFromArray,                 NULL);
      mape_set_native_function(0, gApe, "ertAffineSpace3fCopyToArray",                 _gsCProcedureErtAffineSpace3fCopyToArray,                   NULL);
      mape_set_native_function(0, gApe, "ertCreateDevice",                             _gsCProcedureErtCreateDevice,                               NULL);
      mape_set_native_function(0, gApe, "ertDestroyDevice",                            _gsCProcedureErtDestroyDevice,                              NULL);
      mape_set_native_function(0, gApe, "ertNewCamera",                                _gsCProcedureErtNewCamera,                                  NULL);
      mape_set_native_function(0, gApe, "ertNewData",                                  _gsCProcedureErtNewData,                                    NULL);
      mape_set_native_function(0, gApe, "ertNewDataFromFile",                          _gsCProcedureErtNewDataFromFile,                            NULL);
      mape_set_native_function(0, gApe, "ertNewImage",                                 _gsCProcedureErtNewImage,                                   NULL);
      mape_set_native_function(0, gApe, "ertNewImageFromFile",                         _gsCProcedureErtNewImageFromFile,                           NULL);
      mape_set_native_function(0, gApe, "ertNewTexture",                               _gsCProcedureErtNewTexture,                                 NULL);
      mape_set_native_function(0, gApe, "ertNewMaterial",                              _gsCProcedureErtNewMaterial,                                NULL);
      mape_set_native_function(0, gApe, "ertNewShape",                                 _gsCProcedureErtNewShape,                                   NULL);
      mape_set_native_function(0, gApe, "ertNewLight",                                 _gsCProcedureErtNewLight,                                   NULL);
      mape_set_native_function(0, gApe, "ertNewShapePrimitive",                        _gsCProcedureErtNewShapePrimitive,                          NULL);
      mape_set_native_function(0, gApe, "ertNewLightPrimitive",                        _gsCProcedureErtNewLightPrimitive,                          NULL);
      mape_set_native_function(0, gApe, "ertTransformPrimitive",                       _gsCProcedureErtTransformPrimitive,                         NULL);
      mape_set_native_function(0, gApe, "ertNewScene",                                 _gsCProcedureErtNewScene,                                   NULL);
      mape_set_native_function(0, gApe, "ertNewToneMapper",                            _gsCProcedureErtNewToneMapper,                              NULL);
      mape_set_native_function(0, gApe, "ertNewRenderer",                              _gsCProcedureErtNewRenderer,                                NULL);
      mape_set_native_function(0, gApe, "ertNewFrameBuffer",                           _gsCProcedureErtNewFrameBuffer,                             NULL);
      mape_set_native_function(0, gApe, "ertGetFrameBufferWidth",                      _gsCProcedureErtGetFrameBufferWidth,                        NULL);
      mape_set_native_function(0, gApe, "ertGetFrameBufferHeight",                     _gsCProcedureErtGetFrameBufferHeight,                       NULL);
      mape_set_native_function(0, gApe, "ertMapFrameBuffer",                           _gsCProcedureErtMapFrameBuffer,                             NULL);
      mape_set_native_function(0, gApe, "ertUnmapFrameBuffer",                         _gsCProcedureErtUnmapFrameBuffer,                           NULL);
      mape_set_native_function(0, gApe, "ertSwapBuffers",                              _gsCProcedureErtSwapBuffers,                                NULL);
      mape_set_native_function(0, gApe, "ertIncRef",                                   _gsCProcedureErtIncRef,                                     NULL);
      mape_set_native_function(0, gApe, "ertDecRef",                                   _gsCProcedureErtDecRef,                                     NULL);
      mape_set_native_function(0, gApe, "ertSetBool1",                                 _gsCProcedureErtSetBool1,                                   NULL);
      mape_set_native_function(0, gApe, "ertSetBool2",                                 _gsCProcedureErtSetBool2,                                   NULL);
      mape_set_native_function(0, gApe, "ertSetBool3",                                 _gsCProcedureErtSetBool3,                                   NULL);
      mape_set_native_function(0, gApe, "ertSetBool4",                                 _gsCProcedureErtSetBool4,                                   NULL);
      mape_set_native_function(0, gApe, "ertSetInt1",                                  _gsCProcedureErtSetInt1,                                    NULL);
      mape_set_native_function(0, gApe, "ertSetInt2",                                  _gsCProcedureErtSetInt2,                                    NULL);
      mape_set_native_function(0, gApe, "ertSetInt3",                                  _gsCProcedureErtSetInt3,                                    NULL);
      mape_set_native_function(0, gApe, "ertSetInt4",                                  _gsCProcedureErtSetInt4,                                    NULL);
      mape_set_native_function(0, gApe, "ertSetFloat1",                                _gsCProcedureErtSetFloat1,                                  NULL);
      mape_set_native_function(0, gApe, "ertSetFloat2",                                _gsCProcedureErtSetFloat2,                                  NULL);
      mape_set_native_function(0, gApe, "ertSetFloat3",                                _gsCProcedureErtSetFloat3,                                  NULL);
      mape_set_native_function(0, gApe, "ertSetFloat4",                                _gsCProcedureErtSetFloat4,                                  NULL);
      mape_set_native_function(0, gApe, "ertSetArray",                                 _gsCProcedureErtSetArray,                                   NULL);
      mape_set_native_function(0, gApe, "ertSetString",                                _gsCProcedureErtSetString,                                  NULL);
      mape_set_native_function(0, gApe, "ertSetImage",                                 _gsCProcedureErtSetImage,                                   NULL);
      mape_set_native_function(0, gApe, "ertSetTexture",                               _gsCProcedureErtSetTexture,                                 NULL);
      mape_set_native_function(0, gApe, "ertSetTransform",                             _gsCProcedureErtSetTransform,                               NULL);
      mape_set_native_function(0, gApe, "ertClear",                                    _gsCProcedureErtClear,                                      NULL);
      mape_set_native_function(0, gApe, "ertCommit",                                   _gsCProcedureErtCommit,                                     NULL);
      mape_set_native_function(0, gApe, "ertRenderFrame",                              _gsCProcedureErtRenderFrame,                                NULL);
      mape_set_native_function(0, gApe, "ertPick",                                     _gsCProcedureErtPick,                                       NULL);
      mape_set_native_function(0, gApe, "ertInitializeRayStruct",                      _gsCProcedureErtInitializeRayStruct,                        NULL);
      mape_set_native_function(0, gApe, "ertInitializeRayStructForCameraPixelSample",  _gsCProcedureErtInitializeRayStructForCameraPixelSample,    NULL);
      mape_set_native_function(0, gApe, "ertSceneIntersectRayStructToHitStruct",       _gsCProcedureErtSceneIntersectRayStructToHitStruct,         NULL);
      mape_set_native_function(0, gApe, "onRerunCallErtDecRef",                        _gsCProcedureOnRerunCallErtDecRef,                          NULL);
      mape_set_native_function(0, gApe, "onRerunCallErtDestroyDevice",                 _gsCProcedureOnRerunCallErtDestroyDevice,                   NULL);
    }
    if (gRedGpuIsEnabled == 1) {
      mape_set_native_function(0, gApe, "getRedStructsCount",                          _gsCProcedureGetRedStructsCount,                            NULL);
      mape_set_native_function(0, gApe, "getRedStructName",                            _gsCProcedureGetRedStructName,                              NULL);
      mape_set_native_function(0, gApe, "getRedStructMembersCount",                    _gsCProcedureGetRedStructMembersCount,                      NULL);
      mape_set_native_function(0, gApe, "getRedStructMemberName",                      _gsCProcedureGetRedStructMemberName,                        NULL);
      mape_set_native_function(0, gApe, "redStructSizeof",                             _gsCProcedureRedStructSizeof,                               NULL);
      mape_set_native_function(0, gApe, "redStructMemberSizeof",                       _gsCProcedureRedStructMemberSizeof,                         NULL);
      mape_set_native_function(0, gApe, "redStructMemberOffsetof",                     _gsCProcedureRedStructMemberOffsetof,                       NULL);
      mape_set_native_function(0, gApe, "redStructMemberTypeof",                       _gsCProcedureRedStructMemberTypeof,                         NULL);
      mape_set_native_function(0, gApe, "redCreateContext",                            _gsCProcedureRedCreateContext,                              NULL);
      mape_set_native_function(0, gApe, "redCreateContextWithRayTracingFeatureLevel1", _gsCProcedureRedCreateContextWithRayTracingFeatureLevel1,   NULL);
      mape_set_native_function(0, gApe, "redCreateContextWithRayTracingFeatureLevel2", _gsCProcedureRedCreateContextWithRayTracingFeatureLevel2,   NULL);
      mape_set_native_function(0, gApe, "redHandleContextGetProcAddr",                 _gsCProcedureRedHandleContextGetProcAddr,                   NULL);
      mape_set_native_function(0, gApe, "redMemoryGetBudget",                          _gsCProcedureRedMemoryGetBudget,                            NULL);
      mape_set_native_function(0, gApe, "redMemoryAllocate",                           _gsCProcedureRedMemoryAllocate,                             NULL);
      mape_set_native_function(0, gApe, "redMemoryAllocateMappable",                   _gsCProcedureRedMemoryAllocateMappable,                     NULL);
      mape_set_native_function(0, gApe, "redMemoryFree",                               _gsCProcedureRedMemoryFree,                                 NULL);
      mape_set_native_function(0, gApe, "redMemorySet",                                _gsCProcedureRedMemorySet,                                  NULL);
      mape_set_native_function(0, gApe, "redMemoryMap",                                _gsCProcedureRedMemoryMap,                                  NULL);
      mape_set_native_function(0, gApe, "redMemoryUnmap",                              _gsCProcedureRedMemoryUnmap,                                NULL);
      mape_set_native_function(0, gApe, "redMemoryNonCoherentFlush",                   _gsCProcedureRedMemoryNonCoherentFlush,                     NULL);
      mape_set_native_function(0, gApe, "redMemoryNonCoherentInvalidate",              _gsCProcedureRedMemoryNonCoherentInvalidate,                NULL);
      mape_set_native_function(0, gApe, "redStructsMemoryAllocate",                    _gsCProcedureRedStructsMemoryAllocate,                      NULL);
      mape_set_native_function(0, gApe, "redStructsMemoryAllocateSamplers",            _gsCProcedureRedStructsMemoryAllocateSamplers,              NULL);
      mape_set_native_function(0, gApe, "redStructsMemorySuballocateStructs",          _gsCProcedureRedStructsMemorySuballocateStructs,            NULL);
      mape_set_native_function(0, gApe, "redStructsMemoryReset",                       _gsCProcedureRedStructsMemoryReset,                         NULL);
      mape_set_native_function(0, gApe, "redStructsMemoryFree",                        _gsCProcedureRedStructsMemoryFree,                          NULL);
      mape_set_native_function(0, gApe, "redStructsSet",                               _gsCProcedureRedStructsSet,                                 NULL);
      mape_set_native_function(0, gApe, "redCreateArray",                              _gsCProcedureRedCreateArray,                                NULL);
      mape_set_native_function(0, gApe, "redCreateImage",                              _gsCProcedureRedCreateImage,                                NULL);
      mape_set_native_function(0, gApe, "redCreateSampler",                            _gsCProcedureRedCreateSampler,                              NULL);
      mape_set_native_function(0, gApe, "redCreateTexture",                            _gsCProcedureRedCreateTexture,                              NULL);
      mape_set_native_function(0, gApe, "redCreateGpuCode",                            _gsCProcedureRedCreateGpuCode,                              NULL);
      mape_set_native_function(0, gApe, "redCreateOutputDeclaration",                  _gsCProcedureRedCreateOutputDeclaration,                    NULL);
      mape_set_native_function(0, gApe, "redCreateStructDeclaration",                  _gsCProcedureRedCreateStructDeclaration,                    NULL);
      mape_set_native_function(0, gApe, "redCreateProcedureParameters",                _gsCProcedureRedCreateProcedureParameters,                  NULL);
      mape_set_native_function(0, gApe, "redCreateProcedureCache",                     _gsCProcedureRedCreateProcedureCache,                       NULL);
      mape_set_native_function(0, gApe, "redCreateProcedure",                          _gsCProcedureRedCreateProcedure,                            NULL);
      mape_set_native_function(0, gApe, "redCreateProcedureCompute",                   _gsCProcedureRedCreateProcedureCompute,                     NULL);
      mape_set_native_function(0, gApe, "redCreateOutput",                             _gsCProcedureRedCreateOutput,                               NULL);
      mape_set_native_function(0, gApe, "redCreateCpuSignal",                          _gsCProcedureRedCreateCpuSignal,                            NULL);
      mape_set_native_function(0, gApe, "redCreateGpuSignal",                          _gsCProcedureRedCreateGpuSignal,                            NULL);
      mape_set_native_function(0, gApe, "redCreateGpuToCpuSignal",                     _gsCProcedureRedCreateGpuToCpuSignal,                       NULL);
      mape_set_native_function(0, gApe, "redCreateCalls",                              _gsCProcedureRedCreateCalls,                                NULL);
      mape_set_native_function(0, gApe, "redCreateCallsReusable",                      _gsCProcedureRedCreateCallsReusable,                        NULL);
      mape_set_native_function(0, gApe, "redDestroyContext",                           _gsCProcedureRedDestroyContext,                             NULL);
      mape_set_native_function(0, gApe, "redDestroyArray",                             _gsCProcedureRedDestroyArray,                               NULL);
      mape_set_native_function(0, gApe, "redDestroyImage",                             _gsCProcedureRedDestroyImage,                               NULL);
      mape_set_native_function(0, gApe, "redDestroySampler",                           _gsCProcedureRedDestroySampler,                             NULL);
      mape_set_native_function(0, gApe, "redDestroyTexture",                           _gsCProcedureRedDestroyTexture,                             NULL);
      mape_set_native_function(0, gApe, "redDestroyGpuCode",                           _gsCProcedureRedDestroyGpuCode,                             NULL);
      mape_set_native_function(0, gApe, "redDestroyOutputDeclaration",                 _gsCProcedureRedDestroyOutputDeclaration,                   NULL);
      mape_set_native_function(0, gApe, "redDestroyStructDeclaration",                 _gsCProcedureRedDestroyStructDeclaration,                   NULL);
      mape_set_native_function(0, gApe, "redDestroyProcedureParameters",               _gsCProcedureRedDestroyProcedureParameters,                 NULL);
      mape_set_native_function(0, gApe, "redDestroyProcedureCache",                    _gsCProcedureRedDestroyProcedureCache,                      NULL);
      mape_set_native_function(0, gApe, "redDestroyProcedure",                         _gsCProcedureRedDestroyProcedure,                           NULL);
      mape_set_native_function(0, gApe, "redDestroyOutput",                            _gsCProcedureRedDestroyOutput,                              NULL);
      mape_set_native_function(0, gApe, "redDestroyCpuSignal",                         _gsCProcedureRedDestroyCpuSignal,                           NULL);
      mape_set_native_function(0, gApe, "redDestroyGpuSignal",                         _gsCProcedureRedDestroyGpuSignal,                           NULL);
      mape_set_native_function(0, gApe, "redDestroyGpuToCpuSignal",                    _gsCProcedureRedDestroyGpuToCpuSignal,                      NULL);
      mape_set_native_function(0, gApe, "redDestroyCalls",                             _gsCProcedureRedDestroyCalls,                               NULL);
      mape_set_native_function(0, gApe, "redProcedureCacheGetBlob",                    _gsCProcedureRedProcedureCacheGetBlob,                      NULL);
      mape_set_native_function(0, gApe, "redProcedureCacheMergeCaches",                _gsCProcedureRedProcedureCacheMergeCaches,                  NULL);
      mape_set_native_function(0, gApe, "redCpuSignalGetStatus",                       _gsCProcedureRedCpuSignalGetStatus,                         NULL);
      mape_set_native_function(0, gApe, "redCpuSignalWait",                            _gsCProcedureRedCpuSignalWait,                              NULL);
      mape_set_native_function(0, gApe, "redCpuSignalUnsignal",                        _gsCProcedureRedCpuSignalUnsignal,                          NULL);
      mape_set_native_function(0, gApe, "redGpuToCpuSignalGetStatus",                  _gsCProcedureRedGpuToCpuSignalGetStatus,                    NULL);
      mape_set_native_function(0, gApe, "redGpuToCpuSignalUnsignal",                   _gsCProcedureRedGpuToCpuSignalUnsignal,                     NULL);
      mape_set_native_function(0, gApe, "redCallsSet",                                 _gsCProcedureRedCallsSet,                                   NULL);
      mape_set_native_function(0, gApe, "redCallsEnd",                                 _gsCProcedureRedCallsEnd,                                   NULL);
      mape_set_native_function(0, gApe, "redGetCallProceduresAndAddresses",            _gsCProcedureRedGetCallProceduresAndAddresses,              NULL);
      mape_set_native_function(0, gApe, "redCallGpuToCpuSignalSignal",                 _gsCProcedureRedCallGpuToCpuSignalSignal,                   NULL);
      mape_set_native_function(0, gApe, "redCallCopyArrayToArray",                     _gsCProcedureRedCallCopyArrayToArray,                       NULL);
      mape_set_native_function(0, gApe, "redCallCopyImageToImage",                     _gsCProcedureRedCallCopyImageToImage,                       NULL);
      mape_set_native_function(0, gApe, "redCallCopyArrayToImage",                     _gsCProcedureRedCallCopyArrayToImage,                       NULL);
      mape_set_native_function(0, gApe, "redCallCopyImageToArray",                     _gsCProcedureRedCallCopyImageToArray,                       NULL);
      mape_set_native_function(0, gApe, "redCallProcedure",                            _gsCProcedureRedCallProcedure,                              NULL);
      mape_set_native_function(0, gApe, "redCallProcedureIndexed",                     _gsCProcedureRedCallProcedureIndexed,                       NULL);
      mape_set_native_function(0, gApe, "redCallProcedureCompute",                     _gsCProcedureRedCallProcedureCompute,                       NULL);
      mape_set_native_function(0, gApe, "redCallSetProcedure",                         _gsCProcedureRedCallSetProcedure,                           NULL);
      mape_set_native_function(0, gApe, "redCallSetProcedureIndices",                  _gsCProcedureRedCallSetProcedureIndices,                    NULL);
      mape_set_native_function(0, gApe, "redCallSetProcedureParametersVariables",      _gsCProcedureRedCallSetProcedureParametersVariables,        NULL);
      mape_set_native_function(0, gApe, "redCallSetProcedureParametersStructs",        _gsCProcedureRedCallSetProcedureParametersStructs,          NULL);
      mape_set_native_function(0, gApe, "redCallSetProcedureParametersHandles",        _gsCProcedureRedCallSetProcedureParametersHandles,          NULL);
      mape_set_native_function(0, gApe, "redCallSetDynamicDepthBias",                  _gsCProcedureRedCallSetDynamicDepthBias,                    NULL);
      mape_set_native_function(0, gApe, "redCallSetDynamicDepthBounds",                _gsCProcedureRedCallSetDynamicDepthBounds,                  NULL);
      mape_set_native_function(0, gApe, "redCallSetDynamicStencilCompareMask",         _gsCProcedureRedCallSetDynamicStencilCompareMask,           NULL);
      mape_set_native_function(0, gApe, "redCallSetDynamicStencilWriteMask",           _gsCProcedureRedCallSetDynamicStencilWriteMask,             NULL);
      mape_set_native_function(0, gApe, "redCallSetDynamicStencilReference",           _gsCProcedureRedCallSetDynamicStencilReference,             NULL);
      mape_set_native_function(0, gApe, "redCallSetDynamicBlendConstants",             _gsCProcedureRedCallSetDynamicBlendConstants,               NULL);
      mape_set_native_function(0, gApe, "redCallSetDynamicViewport",                   _gsCProcedureRedCallSetDynamicViewport,                     NULL);
      mape_set_native_function(0, gApe, "redCallSetDynamicScissor",                    _gsCProcedureRedCallSetDynamicScissor,                      NULL);
      mape_set_native_function(0, gApe, "redCallSetStructsMemory",                     _gsCProcedureRedCallSetStructsMemory,                       NULL);
      mape_set_native_function(0, gApe, "redCallSetProcedureParameters",               _gsCProcedureRedCallSetProcedureParameters,                 NULL);
      mape_set_native_function(0, gApe, "redCallSetProcedureOutput",                   _gsCProcedureRedCallSetProcedureOutput,                     NULL);
      mape_set_native_function(0, gApe, "redCallEndProcedureOutput",                   _gsCProcedureRedCallEndProcedureOutput,                     NULL);
      mape_set_native_function(0, gApe, "redCallUsageAliasOrderBarrier",               _gsCProcedureRedCallUsageAliasOrderBarrier,                 NULL);
      mape_set_native_function(0, gApe, "redCallMark",                                 _gsCProcedureRedCallMark,                                   NULL);
      mape_set_native_function(0, gApe, "redCallMarkSet",                              _gsCProcedureRedCallMarkSet,                                NULL);
      mape_set_native_function(0, gApe, "redCallMarkEnd",                              _gsCProcedureRedCallMarkEnd,                                NULL);
      mape_set_native_function(0, gApe, "redQueueSubmit",                              _gsCProcedureRedQueueSubmit,                                NULL);
      mape_set_native_function(0, gApe, "redMark",                                     _gsCProcedureRedMark,                                       NULL);
      mape_set_native_function(0, gApe, "redMarkSet",                                  _gsCProcedureRedMarkSet,                                    NULL);
      mape_set_native_function(0, gApe, "redMarkEnd",                                  _gsCProcedureRedMarkEnd,                                    NULL);
      mape_set_native_function(0, gApe, "redCreateProcedureComputingLanguage",         _gsCProcedureRedCreateProcedureComputingLanguage,           NULL);
      mape_set_native_function(0, gApe, "redCreateArrayTimestamp",                     _gsCProcedureRedCreateArrayTimestamp,                       NULL);
      mape_set_native_function(0, gApe, "redDestroyArrayTimestamp",                    _gsCProcedureRedDestroyArrayTimestamp,                      NULL);
      mape_set_native_function(0, gApe, "redCallArrayTimestampWrite",                  _gsCProcedureRedCallArrayTimestampWrite,                    NULL);
      mape_set_native_function(0, gApe, "redArrayTimestampRead",                       _gsCProcedureRedArrayTimestampRead,                         NULL);
      mape_set_native_function(0, gApe, "getRrtStructsCount",                          _gsCProcedureGetRrtStructsCount,                            NULL);
      mape_set_native_function(0, gApe, "getRrtStructName",                            _gsCProcedureGetRrtStructName,                              NULL);
      mape_set_native_function(0, gApe, "getRrtStructMembersCount",                    _gsCProcedureGetRrtStructMembersCount,                      NULL);
      mape_set_native_function(0, gApe, "getRrtStructMemberName",                      _gsCProcedureGetRrtStructMemberName,                        NULL);
      mape_set_native_function(0, gApe, "rrtStructSizeof",                             _gsCProcedureRrtStructSizeof,                               NULL);
      mape_set_native_function(0, gApe, "rrtStructMemberSizeof",                       _gsCProcedureRrtStructMemberSizeof,                         NULL);
      mape_set_native_function(0, gApe, "rrtStructMemberOffsetof",                     _gsCProcedureRrtStructMemberOffsetof,                       NULL);
      mape_set_native_function(0, gApe, "rrtStructMemberTypeof",                       _gsCProcedureRrtStructMemberTypeof,                         NULL);
      mape_set_native_function(0, gApe, "rrtCreateContext",                            _gsCProcedureRrtCreateContext,                              NULL);
      mape_set_native_function(0, gApe, "rrtDestroyContext",                           _gsCProcedureRrtDestroyContext,                             NULL);
      mape_set_native_function(0, gApe, "rrtSetLogLevel",                              _gsCProcedureRrtSetLogLevel,                                NULL);
      mape_set_native_function(0, gApe, "rrtSetLogFile",                               _gsCProcedureRrtSetLogFile,                                 NULL);
      mape_set_native_function(0, gApe, "rrtCmdBuildGeometry",                         _gsCProcedureRrtCmdBuildGeometry,                           NULL);
      mape_set_native_function(0, gApe, "rrtGetGeometryBuildMemoryRequirements",       _gsCProcedureRrtGetGeometryBuildMemoryRequirements,         NULL);
      mape_set_native_function(0, gApe, "rrtCmdBuildScene",                            _gsCProcedureRrtCmdBuildScene,                              NULL);
      mape_set_native_function(0, gApe, "rrtGetSceneBuildMemoryRequirements",          _gsCProcedureRrtGetSceneBuildMemoryRequirements,            NULL);
      mape_set_native_function(0, gApe, "rrtCmdIntersect",                             _gsCProcedureRrtCmdIntersect,                               NULL);
      mape_set_native_function(0, gApe, "rrtGetTraceMemoryRequirements",               _gsCProcedureRrtGetTraceMemoryRequirements,                 NULL);
      mape_set_native_function(0, gApe, "rrtAllocateCommandStream",                    _gsCProcedureRrtAllocateCommandStream,                      NULL);
      mape_set_native_function(0, gApe, "rrtReleaseCommandStream",                     _gsCProcedureRrtReleaseCommandStream,                       NULL);
      mape_set_native_function(0, gApe, "rrtSumbitCommandStream",                      _gsCProcedureRrtSumbitCommandStream,                        NULL);
      mape_set_native_function(0, gApe, "rrtReleaseEvent",                             _gsCProcedureRrtReleaseEvent,                               NULL);
      mape_set_native_function(0, gApe, "rrtWaitEvent",                                _gsCProcedureRrtWaitEvent,                                  NULL);
      mape_set_native_function(0, gApe, "rrtReleaseDevicePtr",                         _gsCProcedureRrtReleaseDevicePtr,                           NULL);
      mape_set_native_function(0, gApe, "rrtReleaseExternalCommandStream",             _gsCProcedureRrtReleaseExternalCommandStream,               NULL);
      mape_set_native_function(0, gApe, "rrtGetDevicePtrFromVkBuffer",                 _gsCProcedureRrtGetDevicePtrFromVkBuffer,                   NULL);
      mape_set_native_function(0, gApe, "rrtCreateContextVk",                          _gsCProcedureRrtCreateContextVk,                            NULL);
      mape_set_native_function(0, gApe, "rrtGetCommandStreamFromVkCommandBuffer",      _gsCProcedureRrtGetCommandStreamFromVkCommandBuffer,        NULL);
      mape_set_native_function(0, gApe, "rrtAllocateDeviceBuffer",                     _gsCProcedureRrtAllocateDeviceBuffer,                       NULL);
      mape_set_native_function(0, gApe, "rrtMapDevicePtr",                             _gsCProcedureRrtMapDevicePtr,                               NULL);
      mape_set_native_function(0, gApe, "rrtUnmapDevicePtr",                           _gsCProcedureRrtUnmapDevicePtr,                             NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedCpuSignalWait",                 _gsCProcedureOnRerunCallRedCpuSignalWait,                   NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedMemoryFree",                    _gsCProcedureOnRerunCallRedMemoryFree,                      NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedStructsMemoryFree",             _gsCProcedureOnRerunCallRedStructsMemoryFree,               NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedDestroyContext",                _gsCProcedureOnRerunCallRedDestroyContext,                  NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedDestroyArray",                  _gsCProcedureOnRerunCallRedDestroyArray,                    NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedDestroyImage",                  _gsCProcedureOnRerunCallRedDestroyImage,                    NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedDestroySampler",                _gsCProcedureOnRerunCallRedDestroySampler,                  NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedDestroyTexture",                _gsCProcedureOnRerunCallRedDestroyTexture,                  NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedDestroyGpuCode",                _gsCProcedureOnRerunCallRedDestroyGpuCode,                  NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedDestroyOutputDeclaration",      _gsCProcedureOnRerunCallRedDestroyOutputDeclaration,        NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedDestroyStructDeclaration",      _gsCProcedureOnRerunCallRedDestroyStructDeclaration,        NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedDestroyProcedureParameters",    _gsCProcedureOnRerunCallRedDestroyProcedureParameters,      NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedDestroyProcedureCache",         _gsCProcedureOnRerunCallRedDestroyProcedureCache,           NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedDestroyProcedure",              _gsCProcedureOnRerunCallRedDestroyProcedure,                NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedDestroyOutput",                 _gsCProcedureOnRerunCallRedDestroyOutput,                   NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedDestroyCpuSignal",              _gsCProcedureOnRerunCallRedDestroyCpuSignal,                NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedDestroyGpuSignal",              _gsCProcedureOnRerunCallRedDestroyGpuSignal,                NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedDestroyGpuToCpuSignal",         _gsCProcedureOnRerunCallRedDestroyGpuToCpuSignal,           NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedDestroyCalls",                  _gsCProcedureOnRerunCallRedDestroyCalls,                    NULL);
      mape_set_native_function(0, gApe, "onRerunCallRedDestroyArrayTimestamp",         _gsCProcedureOnRerunCallRedDestroyArrayTimestamp,           NULL);
      mape_set_native_function(0, gApe, "onRerunCallRrtDestroyContext",                _gsCProcedureOnRerunCallRrtDestroyContext,                  NULL);
      mape_set_native_function(0, gApe, "onRerunCallRrtReleaseCommandStream",          _gsCProcedureOnRerunCallRrtReleaseCommandStream,            NULL);
      mape_set_native_function(0, gApe, "onRerunCallRrtReleaseEvent",                  _gsCProcedureOnRerunCallRrtReleaseEvent,                    NULL);
      mape_set_native_function(0, gApe, "onRerunCallRrtWaitEvent",                     _gsCProcedureOnRerunCallRrtWaitEvent,                       NULL);
      mape_set_native_function(0, gApe, "onRerunCallRrtReleaseDevicePtr",              _gsCProcedureOnRerunCallRrtReleaseDevicePtr,                NULL);
      mape_set_native_function(0, gApe, "onRerunCallRrtReleaseExternalCommandStream",  _gsCProcedureOnRerunCallRrtReleaseExternalCommandStream,    NULL);
      mape_set_native_function(0, gApe, "onRerunCallRrtUnmapDevicePtr",                _gsCProcedureOnRerunCallRrtUnmapDevicePtr,                  NULL);
    }
    if (gXatlasIsEnabled == 1) {
      mape_set_native_function(0, gApe, "getXatlasStructsCount",                       _gsCProcedureGetXatlasStructsCount,                         NULL);
      mape_set_native_function(0, gApe, "getXatlasStructName",                         _gsCProcedureGetXatlasStructName,                           NULL);
      mape_set_native_function(0, gApe, "getXatlasStructMembersCount",                 _gsCProcedureGetXatlasStructMembersCount,                   NULL);
      mape_set_native_function(0, gApe, "getXatlasStructMemberName",                   _gsCProcedureGetXatlasStructMemberName,                     NULL);
      mape_set_native_function(0, gApe, "xatlasStructSizeof",                          _gsCProcedureXatlasStructSizeof,                            NULL);
      mape_set_native_function(0, gApe, "xatlasStructMemberSizeof",                    _gsCProcedureXatlasStructMemberSizeof,                      NULL);
      mape_set_native_function(0, gApe, "xatlasStructMemberOffsetof",                  _gsCProcedureXatlasStructMemberOffsetof,                    NULL);
      mape_set_native_function(0, gApe, "xatlasStructMemberTypeof",                    _gsCProcedureXatlasStructMemberTypeof,                      NULL);
      mape_set_native_function(0, gApe, "xatlasMeshDeclInit",                          _gsCProcedureXatlasMeshDeclInit,                            NULL);
      mape_set_native_function(0, gApe, "xatlasUvMeshDeclInit",                        _gsCProcedureXatlasUvMeshDeclInit,                          NULL);
      mape_set_native_function(0, gApe, "xatlasChartOptionsInit",                      _gsCProcedureXatlasChartOptionsInit,                        NULL);
      mape_set_native_function(0, gApe, "xatlasPackOptionsInit",                       _gsCProcedureXatlasPackOptionsInit,                         NULL);
      mape_set_native_function(0, gApe, "xatlasCreate",                                _gsCProcedureXatlasCreate,                                  NULL);
      mape_set_native_function(0, gApe, "xatlasDestroy",                               _gsCProcedureXatlasDestroy,                                 NULL);
      mape_set_native_function(0, gApe, "xatlasAddMesh",                               _gsCProcedureXatlasAddMesh,                                 NULL);
      mape_set_native_function(0, gApe, "xatlasAddMeshJoin",                           _gsCProcedureXatlasAddMeshJoin,                             NULL);
      mape_set_native_function(0, gApe, "xatlasAddUvMesh",                             _gsCProcedureXatlasAddUvMesh,                               NULL);
      mape_set_native_function(0, gApe, "xatlasComputeCharts",                         _gsCProcedureXatlasComputeCharts,                           NULL);
      mape_set_native_function(0, gApe, "xatlasPackCharts",                            _gsCProcedureXatlasPackCharts,                              NULL);
      mape_set_native_function(0, gApe, "xatlasGenerate",                              _gsCProcedureXatlasGenerate,                                NULL);
      mape_set_native_function(0, gApe, "onRerunCallXatlasDestroy",                    _gsCProcedureOnRerunCallXatlasDestroy,                      NULL);
    }
    if (gFbxIsEnabled == 1) {
      mape_set_native_function(0, gApe, "fbxNew",                                      _gsCProcedureFbxNew,                                        NULL);
      mape_set_native_function(0, gApe, "fbxNewFromFile",                              _gsCProcedureFbxNewFromFile,                                NULL);
      mape_set_native_function(0, gApe, "fbxDelete",                                   _gsCProcedureFbxDelete,                                     NULL);
      mape_set_native_function(0, gApe, "fbxDeleteAll",                                _gsCProcedureFbxDeleteAll,                                  NULL);
      mape_set_native_function(0, gApe, "fbxGetHandle",                                _gsCProcedureFbxGetHandle,                                  NULL);
      mape_set_native_function(0, gApe, "fbxCopyToFbx",                                _gsCProcedureFbxCopyToFbx,                                  NULL);
      mape_set_native_function(0, gApe, "fbxClear",                                    _gsCProcedureFbxClear,                                      NULL);
      mape_set_native_function(0, gApe, "fbxEarlyUpdate",                              _gsCProcedureFbxEarlyUpdate,                                NULL);
      mape_set_native_function(0, gApe, "fbxLateUpdate",                               _gsCProcedureFbxLateUpdate,                                 NULL);
      mape_set_native_function(0, gApe, "fbxGetMeshesCount",                           _gsCProcedureFbxGetMeshesCount,                             NULL);
      mape_set_native_function(0, gApe, "fbxGetMesh",                                  _gsCProcedureFbxGetMesh,                                    NULL);
      mape_set_native_function(0, gApe, "fbxGetMeshName",                              _gsCProcedureFbxGetMeshName,                                NULL);
      mape_set_native_function(0, gApe, "fbxGetRootBonesCount",                        _gsCProcedureFbxGetRootBonesCount,                          NULL);
      mape_set_native_function(0, gApe, "fbxGetRootBone",                              _gsCProcedureFbxGetRootBone,                                NULL);
      mape_set_native_function(0, gApe, "fbxBoneGetName",                              _gsCProcedureFbxBoneGetName,                                NULL);
      mape_set_native_function(0, gApe, "fbxBoneGetChildBonesCount",                   _gsCProcedureFbxBoneGetChildBonesCount,                     NULL);
      mape_set_native_function(0, gApe, "fbxBoneGetChildBone",                         _gsCProcedureFbxBoneGetChildBone,                           NULL);
      mape_set_native_function(0, gApe, "fbxBoneGetChildBoneByNameRecursively",        _gsCProcedureFbxBoneGetChildBoneByNameRecursively,          NULL);
      mape_set_native_function(0, gApe, "fbxBoneGetVector",                            _gsCProcedureFbxBoneGetVector,                              NULL);
      mape_set_native_function(0, gApe, "fbxBoneGetVersor",                            _gsCProcedureFbxBoneGetVersor,                              NULL);
      mape_set_native_function(0, gApe, "fbxBoneGetScale",                             _gsCProcedureFbxBoneGetScale,                               NULL);
      mape_set_native_function(0, gApe, "fbxBoneGetSideVector",                        _gsCProcedureFbxBoneGetSideVector,                          NULL);
      mape_set_native_function(0, gApe, "fbxBoneGetUpVector",                          _gsCProcedureFbxBoneGetUpVector,                            NULL);
      mape_set_native_function(0, gApe, "fbxBoneGetLookAtVector",                      _gsCProcedureFbxBoneGetLookAtVector,                        NULL);
      mape_set_native_function(0, gApe, "fbxBoneGetTransformMatrix",                   _gsCProcedureFbxBoneGetTransformMatrix,                     NULL);
      mape_set_native_function(0, gApe, "fbxBoneSetVector",                            _gsCProcedureFbxBoneSetVector,                              NULL);
      mape_set_native_function(0, gApe, "fbxBoneSetVersor",                            _gsCProcedureFbxBoneSetVersor,                              NULL);
      mape_set_native_function(0, gApe, "fbxBoneSetScale",                             _gsCProcedureFbxBoneSetScale,                               NULL);
      mape_set_native_function(0, gApe, "fbxBoneRotate",                               _gsCProcedureFbxBoneRotate,                                 NULL);
      mape_set_native_function(0, gApe, "fbxBoneLookAt",                               _gsCProcedureFbxBoneLookAt,                                 NULL);
    }
#if defined(GAME_SCRIPT_MIN)
    mape_set_native_function(0, gApe, "sqrt",  _minCProcedureSqrt,  NULL);
    mape_set_native_function(0, gApe, "pow",   _minCProcedurePow,   NULL);
    mape_set_native_function(0, gApe, "sin",   _minCProcedureSin,   NULL);
    mape_set_native_function(0, gApe, "cos",   _minCProcedureCos,   NULL);
    mape_set_native_function(0, gApe, "tan",   _minCProcedureTan,   NULL);
    mape_set_native_function(0, gApe, "log",   _minCProcedureLog,   NULL);
    mape_set_native_function(0, gApe, "ceil",  _minCProcedureCeil,  NULL);
    mape_set_native_function(0, gApe, "floor", _minCProcedureFloor, NULL);
    mape_set_native_function(0, gApe, "abs",   _minCProcedureAbs,   NULL);
#endif
#if defined(GAME_SCRIPT_C)
    mape_set_native_function(0, gApe, "malloc", malloc, NULL);
    mape_set_native_function(0, gApe, "free",   free,   NULL);
    mape_set_native_function(0, gApe, "memset", memset, NULL);
    mape_set_native_function(0, gApe, "memcpy", memcpy, NULL);
    mape_set_native_function(0, gApe, "memcmp", memcmp, NULL);
    mape_set_native_function(0, gApe, "sqrtf",  sqrtf,  NULL);
    mape_set_native_function(0, gApe, "powf",   powf,   NULL);
    mape_set_native_function(0, gApe, "sinf",   sinf,   NULL);
    mape_set_native_function(0, gApe, "cosf",   cosf,   NULL);
    mape_set_native_function(0, gApe, "tanf",   tanf,   NULL);
    mape_set_native_function(0, gApe, "logf",   logf,   NULL);
    mape_set_native_function(0, gApe, "ceilf",  ceilf,  NULL);
    mape_set_native_function(0, gApe, "floorf", floorf, NULL);
    mape_set_native_function(0, gApe, "fabsf",  fabsf,  NULL);
#endif
    profileEnd("script set procedures");
#endif // #ifdef GAME_SCRIPT
    profileBegin("script execute");
    mape_execute(0, gApe, gApeCodeCharsCurrentlyRunning);
    profileEnd("script execute");
    // Set the user provided next script.
    if (gApeCodeCharsNextRunning != "") {
      profileBegin("set next script");
      gGameScriptNativeRecompileSignal = 1;
      free(gApeCodeCharsCurrentlyRunning);
      gApeCodeCharsCurrentlyRunning = (char *)calloc(1, gApeCodeCharsNextRunning.size() + 1);
      if (gApeCodeCharsCurrentlyRunning != NULL && gApeCodeCharsNextRunning.size() > 0) {
        memcpy(gApeCodeCharsCurrentlyRunning, &gApeCodeCharsNextRunning[0], gApeCodeCharsNextRunning.size());
      }
      gApeCodeCharsNextRunning = "";
      gApeErrorCheck = 2;
      profileEnd("set next script");
    }
  }
  if (setRerunTo0 == 1) {
    gRerun = 0;
  }
  redFDisableCulling();
  redFColorMask(1, 1, 1, 1);
  redFSetColor(255, 255, 255, 255);
  redFFirstPersonCameraEnd(gCamera[0]);
  {
    redFDisableDepthTest();
    redFDisableBlendMode();
    redFDisableAlphaBlending();
    profileBegin("draw framebuffers");
    for (uint64_t i = 0, count = gApeDrawFbos.size(); i < count; i += 1) {
      ApeDrawFbo * draw = &gApeDrawFbos[i];
      redFFboDraw(draw->handle, 0, draw->x, draw->y, draw->width, draw->height);
    }
    profileEnd("draw framebuffers");
    profileBegin("draw images");
    for (uint64_t i = 0, count = gApeDrawImages.size(); i < count; i += 1) {
      ApeDrawImage * draw = &gApeDrawImages[i];
      redFImageDraw(draw->handle, draw->x, draw->y, draw->z, draw->w, draw->h);
    }
    profileEnd("draw images");
    profileBegin("draw images subsections");
    for (uint64_t i = 0, count = gApeDrawImagesSubsections.size(); i < count; i += 1) {
      ApeDrawImageSubsection * draw = &gApeDrawImagesSubsections[i];
      redFImageDrawSubsection(draw->handle, draw->x, draw->y, draw->z, draw->w, draw->h, draw->sx, draw->sy, draw->sw, draw->sh);
    }
    profileEnd("draw images subsections");
  }
  redFFirstPersonCameraBegin(gCamera[0]);
  {
    redFEnableDepthTest();
    redFEnableBlendMode(REDF_BLEND_MODE_ALPHA);
    redFEnableAlphaBlending();
    profileBegin("draw gizmos");
    for (auto & gizmo : gApeGizmos) {
      redFManipulatorDraw(gizmo.second[0], redFFirstPersonCameraCastToCamera(gCamera[0]));
    }
    profileEnd("draw gizmos");
  }
  redFFirstPersonCameraEnd(gCamera[0]);
  redFDisableDepthTest();
  if (gPreviousGameMode == 1 && gGameMode == 0) {
    glfwSetInputMode((GLFWwindow *)redFGetGLFWwindowPointer(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }
  if (gGameMode == 0) {
    gDefaultCameraEnabled = 0;
  }
  if (gPreviousDefaultCameraEnabled == 0 && gDefaultCameraEnabled == 1) {
    redFFirstPersonCameraControlEnable(gCamera[0]);
  } else if (gPreviousDefaultCameraEnabled == 1 && gDefaultCameraEnabled == 0) {
    redFFirstPersonCameraControlDisable(gCamera[0]);
  }
  profileBegin("draw triangles labels");
  for (uint64_t i = 0, count = gApeDrawLabelStackTriangles.size(); i < count; i += 1) {
    ApeDrawLabelTriangle * draw = &gApeDrawLabelStackTriangles[i];
    if (draw->label != "") {
      {
        std::string label = draw->label;
        label += " x0: ";
        label += std::to_string(draw->x0);
        label += " y0: ";
        label += std::to_string(draw->y0);
        label += " z0: ";
        label += std::to_string(draw->z0);
        redFDrawBitmapStringHighlightFromCamera(label.c_str(), draw->x0, draw->y0, draw->z0, 0, 0, 0, 85, 255, 255, 255, 255, redFFirstPersonCameraCastToCamera(gCamera[0]));
      }
      {
        std::string label = draw->label;
        label += " x1: ";
        label += std::to_string(draw->x1);
        label += " y1: ";
        label += std::to_string(draw->y1);
        label += " z1: ";
        label += std::to_string(draw->z1);
        redFDrawBitmapStringHighlightFromCamera(label.c_str(), draw->x1, draw->y1, draw->z1, 0, 0, 0, 85, 255, 255, 255, 255, redFFirstPersonCameraCastToCamera(gCamera[0]));
      }
      {
        std::string label = draw->label;
        label += " x2: ";
        label += std::to_string(draw->x2);
        label += " y2: ";
        label += std::to_string(draw->y2);
        label += " z2: ";
        label += std::to_string(draw->z2);
        redFDrawBitmapStringHighlightFromCamera(label.c_str(), draw->x2, draw->y2, draw->z2, 0, 0, 0, 85, 255, 255, 255, 255, redFFirstPersonCameraCastToCamera(gCamera[0]));
      }
    }
  }
  profileEnd("draw triangles labels");
  profileBegin("draw lines labels");
  for (uint64_t i = 0, count = gApeDrawLabelStackLines.size(); i < count; i += 1) {
    ApeDrawLabelLine * draw = &gApeDrawLabelStackLines[i];
    if (draw->label != "") {
      {
        std::string label = draw->label;
        label += " x0: ";
        label += std::to_string(draw->x0);
        label += " y0: ";
        label += std::to_string(draw->y0);
        label += " z0: ";
        label += std::to_string(draw->z0);
        redFDrawBitmapStringHighlightFromCamera(label.c_str(), draw->x0, draw->y0, draw->z0, 0, 0, 0, 85, 255, 255, 255, 255, redFFirstPersonCameraCastToCamera(gCamera[0]));
      }
      {
        std::string label = draw->label;
        label += " x1: ";
        label += std::to_string(draw->x1);
        label += " y1: ";
        label += std::to_string(draw->y1);
        label += " z1: ";
        label += std::to_string(draw->z1);
        redFDrawBitmapStringHighlightFromCamera(label.c_str(), draw->x1, draw->y1, draw->z1, 0, 0, 0, 85, 255, 255, 255, 255, redFFirstPersonCameraCastToCamera(gCamera[0]));
      }
    }
  }
  profileEnd("draw lines labels");
  profileBegin("draw points labels");
  for (uint64_t i = 0, count = gApeDrawLabelStackPoints.size(); i < count; i += 1) {
    ApeDrawLabelPoint * draw = &gApeDrawLabelStackPoints[i];
    if (draw->label != "") {
      std::string label = draw->label;
      label += " x: ";
      label += std::to_string(draw->x);
      label += " y: ";
      label += std::to_string(draw->y);
      label += " z: ";
      label += std::to_string(draw->z);
      redFDrawBitmapStringHighlightFromCamera(label.c_str(), draw->x, draw->y, draw->z, 0, 0, 0, 85, 255, 255, 255, 255, redFFirstPersonCameraCastToCamera(gCamera[0]));
    }
  }
  profileEnd("draw points labels");
  profileBegin("draw debug text labels");
  for (uint64_t i = 0, count = gApeDrawLabelStackDebugTexts.size(); i < count; i += 1) {
    ApeDrawLabelDebugText * draw = &gApeDrawLabelStackDebugTexts[i];
    if (draw->label != "") {
      std::string label = draw->label;
      if (draw->r == 255 && draw->g == 255 && draw->b == 255 && draw->a == 0) {
        redFDrawBitmapString(label.c_str(), draw->x, draw->y, 0);
      } else {
        redFDrawBitmapStringHighlight(label.c_str(), draw->x, draw->y, 0, 0, 0, 0, draw->a, draw->r, draw->g, draw->b, 255);
      }
    }
  }
  profileEnd("draw debug text labels");
  profileBegin("draw mesh labels");
  for (uint64_t i = 0, count = gApeDrawLabelStackMeshes.size(); i < count; i += 1) {
    ApeDrawLabelMesh * draw = &gApeDrawLabelStackMeshes[i];
    const float filterDistance             = draw->filterDistance;
    const int   raytraceHighlightTriangles = draw->raytraceHighlightTriangles;
    const float cameraX = redFNodeGetGlobalPositionX(redFFirstPersonCameraCastToNode(gCamera[0]));
    const float cameraY = redFNodeGetGlobalPositionY(redFFirstPersonCameraCastToNode(gCamera[0]));
    const float cameraZ = redFNodeGetGlobalPositionZ(redFFirstPersonCameraCastToNode(gCamera[0]));
    if (draw->drawLabelsForAttribute == APE_DRAW_LABEL_MESH_VERTEX_ATTRIBUTE_NONE) {
      continue;
    } else if (draw->drawLabelsForAttribute == APE_DRAW_LABEL_MESH_VERTEX_ATTRIBUTE_VERTICES) {
      float3 * vertices = (float3 *)redFMeshGetVerticesPointer(draw->handle);
      if (vertices == 0) {
        std::string label;
        label += "[meshDrawDebugVertices] Mesh \"";
        label += draw->label;
        label += "\" has no vertices.";
        redFDrawBitmapStringHighlight(label.c_str(), 4, 14, 0, 85, 0, 0, 255, 255, 255, 255, 255);
      } else {
        for (uint64_t j = 0, verticesCount = redFMeshGetNumVertices(draw->handle); j < verticesCount; j += 1) {
          float x = vertices[j].x;
          float y = vertices[j].y;
          float z = vertices[j].z;
          {
            std::string label;
            label += " x: ";
            label += std::to_string(x);
            label += " y: ";
            label += std::to_string(y);
            label += " z: ";
            label += std::to_string(z);
            redFDrawBitmapStringHighlightFromCamera(label.c_str(), x, y, z, 0, 0, 0, 85, 255, 255, 255, 255, redFFirstPersonCameraCastToCamera(gCamera[0]));
          }
        }
      }
    } else if (draw->drawLabelsForAttribute == APE_DRAW_LABEL_MESH_VERTEX_ATTRIBUTE_COLORS) {
      float3 * vertices = (float3 *)redFMeshGetVerticesPointer(draw->handle);
      float4 * colors   = (float4 *)redFMeshGetColorsPointer(draw->handle);
      if (colors == 0) {
        std::string label;
        label += "[meshDrawDebugColors] Mesh \"";
        label += draw->label;
        label += "\" has no vertex colors.";
        redFDrawBitmapStringHighlight(label.c_str(), 4, 14, 0, 85, 0, 0, 255, 255, 255, 255, 255);
      } else {
        for (uint64_t j = 0, verticesCount = redFMeshGetNumVertices(draw->handle); j < verticesCount; j += 1) {
          float x = vertices[j].x;
          float y = vertices[j].y;
          float z = vertices[j].z;
          float r = colors[j].x;
          float g = colors[j].y;
          float b = colors[j].z;
          float a = colors[j].w;
          {
            std::string label;
            label += " r: ";
            label += std::to_string(r);
            label += " g: ";
            label += std::to_string(g);
            label += " b: ";
            label += std::to_string(b);
            label += " a: ";
            label += std::to_string(a);
            redFDrawBitmapStringHighlightFromCamera(label.c_str(), x, y, z, 0, 0, 0, 85, 255, 255, 255, 255, redFFirstPersonCameraCastToCamera(gCamera[0]));
          }
        }
      }
    } else if (draw->drawLabelsForAttribute == APE_DRAW_LABEL_MESH_VERTEX_ATTRIBUTE_TEXCOORDS) {
      float3 * vertices  = (float3 *)redFMeshGetVerticesPointer(draw->handle);
      float2 * texcoords = (float2 *)redFMeshGetTexCoordsPointer(draw->handle);
      if (texcoords == 0) {
        std::string label;
        label += "[meshDrawDebugTexCoords] Mesh \"";
        label += draw->label;
        label += "\" has no vertex texture coordinates.";
        redFDrawBitmapStringHighlight(label.c_str(), 4, 14, 0, 85, 0, 0, 255, 255, 255, 255, 255);
      } else {
        for (uint64_t j = 0, verticesCount = redFMeshGetNumVertices(draw->handle); j < verticesCount; j += 1) {
          float x = vertices[j].x;
          float y = vertices[j].y;
          float z = vertices[j].z;
          float u = texcoords[j].x;
          float v = texcoords[j].y;
          {
            std::string label;
            label += " u: ";
            label += std::to_string(u);
            label += " v: ";
            label += std::to_string(v);
            redFDrawBitmapStringHighlightFromCamera(label.c_str(), x, y, z, 0, 0, 0, 85, 255, 255, 255, 255, redFFirstPersonCameraCastToCamera(gCamera[0]));
          }
        }
      }
    } else if (draw->drawLabelsForAttribute == APE_DRAW_LABEL_MESH_VERTEX_ATTRIBUTE_INDICES) {
      float3   * vertices = (float3 *)redFMeshGetVerticesPointer(draw->handle);
      unsigned * indices  = redFMeshGetIndexPointer(draw->handle);
      if (indices == 0) {
        std::string label;
        label += "[meshDrawDebugIndices] Mesh \"";
        label += draw->label;
        label += "\" has no vertex indices.";
        redFDrawBitmapStringHighlight(label.c_str(), 4, 14, 0, 85, 0, 0, 255, 255, 255, 255, 255);
      } else {
        for (uint64_t j = 0, indicesCount = redFMeshGetNumIndices(draw->handle) / 3; j < indicesCount; j += 1) {
          unsigned index0 = indices[j * 3 + 0];
          unsigned index1 = indices[j * 3 + 1];
          unsigned index2 = indices[j * 3 + 2];
          float x0 = vertices[index0].x;
          float y0 = vertices[index0].y;
          float z0 = vertices[index0].z;
          float x1 = vertices[index1].x;
          float y1 = vertices[index1].y;
          float z1 = vertices[index1].z;
          float x2 = vertices[index2].x;
          float y2 = vertices[index2].y;
          float z2 = vertices[index2].z;
          if (filterDistance == 0) {
            {
              std::string label;
              label += " index0: ";
              label += std::to_string(index0);
              label += " x: ";
              label += std::to_string(x0);
              label += " y: ";
              label += std::to_string(y0);
              label += " z: ";
              label += std::to_string(z0);
              label += " triangle index: ";
              label += std::to_string(j);
              redFDrawBitmapStringHighlightFromCamera(label.c_str(), x0, y0, z0, 0, 0, 0, 85, 255, 255, 255, 255, redFFirstPersonCameraCastToCamera(gCamera[0]));
            }
            {
              std::string label;
              label += " index1: ";
              label += std::to_string(index1);
              label += " x: ";
              label += std::to_string(x1);
              label += " y: ";
              label += std::to_string(y1);
              label += " z: ";
              label += std::to_string(z1);
              redFDrawBitmapStringHighlightFromCamera(label.c_str(), x1, y1, z1, 0, 0, 0, 85, 255, 255, 255, 255, redFFirstPersonCameraCastToCamera(gCamera[0]));
            }
            {
              std::string label;
              label += " index2: ";
              label += std::to_string(index2);
              label += " x: ";
              label += std::to_string(x2);
              label += " y: ";
              label += std::to_string(y2);
              label += " z: ";
              label += std::to_string(z2);
              redFDrawBitmapStringHighlightFromCamera(label.c_str(), x2, y2, z2, 0, 0, 0, 85, 255, 255, 255, 255, redFFirstPersonCameraCastToCamera(gCamera[0]));
            }
          } else {
            float dx0 = x0 - cameraX;
            float dy0 = y0 - cameraY;
            float dz0 = z0 - cameraZ;
            float distance0 = sqrt(dx0*dx0 + dy0*dy0 + dz0*dz0);
            float dx1 = x1 - cameraX;
            float dy1 = y1 - cameraY;
            float dz1 = z1 - cameraZ;
            float distance1 = sqrt(dx1*dx1 + dy1*dy1 + dz1*dz1);
            float dx2 = x2 - cameraX;
            float dy2 = y2 - cameraY;
            float dz2 = z2 - cameraZ;
            float distance2 = sqrt(dx2*dx2 + dy2*dy2 + dz2*dz2);
            if (distance0 <= filterDistance && distance1 <= filterDistance && distance2 <= filterDistance) {
              if (raytraceHighlightTriangles == 1) {
                float rox = redFNodeGetGlobalPositionX(redFFirstPersonCameraCastToNode(gCamera[0]));
                float roy = redFNodeGetGlobalPositionY(redFFirstPersonCameraCastToNode(gCamera[0]));
                float roz = redFNodeGetGlobalPositionZ(redFFirstPersonCameraCastToNode(gCamera[0]));
                float rvx = redFNodeGetLookAtDirX(redFFirstPersonCameraCastToNode(gCamera[0]));
                float rvy = redFNodeGetLookAtDirY(redFFirstPersonCameraCastToNode(gCamera[0]));
                float rvz = redFNodeGetLookAtDirZ(redFFirstPersonCameraCastToNode(gCamera[0]));
                std::vector<float> intersectionPoint = rayTriangleIntersection(rox, roy, roz, rvx, rvy, rvz, x0, y0, z0, x1, y1, z1, x2, y2, z2);
                if (intersectionPoint[3] != 0) {
                  redFFirstPersonCameraBegin(gCamera[0]);
                  redFSetColor(255, 0, 255, 85);
                  redFDrawTriangle(x0, y0, z0, x1, y1, z1, x2, y2, z2);
                  redFSetColor(255, 255, 255, 255);
                  redFFirstPersonCameraEnd(gCamera[0]);
                  if (distance0 == 0) { distance0 = 0.00001f; }
                  if (distance1 == 0) { distance1 = 0.00001f; }
                  if (distance2 == 0) { distance2 = 0.00001f; }
                  {
                    std::string label;
                    label += " index0: ";
                    label += std::to_string(index0);
                    label += " x: ";
                    label += std::to_string(x0);
                    label += " y: ";
                    label += std::to_string(y0);
                    label += " z: ";
                    label += std::to_string(z0);
                    label += " triangle index: ";
                    label += std::to_string(j);
                    redFDrawBitmapStringHighlightFromCamera(label.c_str(), x0, y0, z0, 0, 0, 0, 85, 255, 255, 255, 255, redFFirstPersonCameraCastToCamera(gCamera[0]));
                  }
                  {
                    std::string label;
                    label += " index1: ";
                    label += std::to_string(index1);
                    label += " x: ";
                    label += std::to_string(x1);
                    label += " y: ";
                    label += std::to_string(y1);
                    label += " z: ";
                    label += std::to_string(z1);
                    redFDrawBitmapStringHighlightFromCamera(label.c_str(), x1, y1, z1, 0, 0, 0, 85, 255, 255, 255, 255, redFFirstPersonCameraCastToCamera(gCamera[0]));
                  }
                  {
                    std::string label;
                    label += " index2: ";
                    label += std::to_string(index2);
                    label += " x: ";
                    label += std::to_string(x2);
                    label += " y: ";
                    label += std::to_string(y2);
                    label += " z: ";
                    label += std::to_string(z2);
                    redFDrawBitmapStringHighlightFromCamera(label.c_str(), x2, y2, z2, 0, 0, 0, 85, 255, 255, 255, 255, redFFirstPersonCameraCastToCamera(gCamera[0]));
                  }
                }
              } else {
                {
                  std::string label;
                  label += " index0: ";
                  label += std::to_string(index0);
                  label += " x: ";
                  label += std::to_string(x0);
                  label += " y: ";
                  label += std::to_string(y0);
                  label += " z: ";
                  label += std::to_string(z0);
                  label += " triangle index: ";
                  label += std::to_string(j);
                  redFDrawBitmapStringHighlightFromCamera(label.c_str(), x0, y0, z0, 0, 0, 0, 85, 255, 255, 255, 255, redFFirstPersonCameraCastToCamera(gCamera[0]));
                }
                {
                  std::string label;
                  label += " index1: ";
                  label += std::to_string(index1);
                  label += " x: ";
                  label += std::to_string(x1);
                  label += " y: ";
                  label += std::to_string(y1);
                  label += " z: ";
                  label += std::to_string(z1);
                  redFDrawBitmapStringHighlightFromCamera(label.c_str(), x1, y1, z1, 0, 0, 0, 85, 255, 255, 255, 255, redFFirstPersonCameraCastToCamera(gCamera[0]));
                }
                {
                  std::string label;
                  label += " index2: ";
                  label += std::to_string(index2);
                  label += " x: ";
                  label += std::to_string(x2);
                  label += " y: ";
                  label += std::to_string(y2);
                  label += " z: ";
                  label += std::to_string(z2);
                  redFDrawBitmapStringHighlightFromCamera(label.c_str(), x2, y2, z2, 0, 0, 0, 85, 255, 255, 255, 255, redFFirstPersonCameraCastToCamera(gCamera[0]));
                }
              }
            }
          }
        }
      }
    }
  }
  profileEnd("draw mesh labels");
  profileBegin("draw gizmo labels");
  for (auto & gizmo : gApeGizmos) {
    if (gizmo.first != "") {
      if (gizmo.first[0] != '_') {
        if (redFManipulatorIsEnabled(gizmo.second[0]) == 1) {
          float vector3[3];
          redFManipulatorGetTranslation(gizmo.second[0], vector3);
          std::string label = gizmo.first;
          label += " x: ";
          label += std::to_string(vector3[0]);
          label += " y: ";
          label += std::to_string(vector3[1]);
          label += " z: ";
          label += std::to_string(vector3[2]);
          redFDrawBitmapStringHighlightFromCamera(label.c_str(), vector3[0], vector3[1], vector3[2], 0, 0, 0, 85, 255, 255, 255, 255, redFFirstPersonCameraCastToCamera(gCamera[0]));
        }
      }
    }
  }
  profileEnd("draw gizmo labels");
  if (gStopScript == 0) {
  } else {
    redFDrawBitmapStringHighlight("SCRIPT WAS STOPPED WITH F7 KEY. PRESS F9 KEY TO CONTINUE RUNNING THE SCRIPT.", 4, 14, 0, 85, 0, 0, 255, 255, 255, 255, 255);
  }

  profileBegin("imgui");
  if (gGameMode == 1) {
    ImGuiIO * io = igGetIO();
    io->InputQueueCharacters.Size = 0;
  } else {
    redFPushStyle();
    redFDisableCulling();
    redFDisableLighting();
    redFDisableDepthTest();
    redFDisableBlendMode();
    redFDisableAlphaBlending();
    redFImguiBegin(gGuiImgui[0]);
#if 0
    static int demoWindowIsOpen = 1;
    igShowDemoWindow((bool *)&demoWindowIsOpen);
#endif
    static int f1WindowIsOpen = 1;
    if (gF1WindowIsShownFromNowOn == 1) {
      if (igBegin("F1", (bool *)&f1WindowIsOpen, 0)) {
        ImVec2 f1WindowSize = {800, 400};
        igSetWindowSizeVec2(f1WindowSize, ImGuiCond_FirstUseEver);
        if (redFThreadIsRunning(gThreadF1[0]) == 1) {
#if defined(_WIN32)
          igText("f1.bat is running...");
#else
          igText("f1.sh is running...");
#endif
          igSeparator();
        }
        igInputText("f1_options.txt", &gF1CommandOptions[0], 4096, 0, 0, 0);
        ImVec2 inputSize = {};
        inputSize.x = -1;
        inputSize.y = -1;
        {
          std::lock_guard<std::mutex> __threadF1OutputTextGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_threadF1OutputTextMutex);
          igInputTextMultiline(" F1", &gThreadF1OutputText[0], gThreadF1OutputText.size(), inputSize, ImGuiInputTextFlags_ReadOnly, 0, 0);
        }
      }
      igEnd();
    }
    static int apeScriptWindowIsOpen = 1;
    if (igBegin("Game (F3)", (bool *)&apeScriptWindowIsOpen, 0)) {
      ImVec2 apeWindowSize = {1100, 600};
      igSetWindowSizeVec2(apeWindowSize, ImGuiCond_FirstUseEver);
      ImVec2 buttonSize = {};
      if (igButton("Rerun (F5)", buttonSize)) {
        apeScriptRerun(0);
        if (gStopScript == 1) {
          gRunScriptOnce = 2;
        }
        if (gStopScript == 0) {
          gCurrentFrame -= 1; // NOTE(Constantine): Workaround, since the next gCurrentFrame += 1 must set it to 0.
        }
      }
      igSameLine(0, 14);
      igCheckbox("Run from game.script", (bool *)&gReadScriptFromDataGameDotScript);
      igSameLine(0, 14);
      igText("| Current frame: %lu", gCurrentFrame == (uint64_t)-1 ? 0 : gCurrentFrame);
      {
        if (gApeErrorCheck >= 1) {
          if (gApeErrorCheck == 1) {
            gApeErrorCheck = 0;
          }
          if (gApeErrorCheck == 2) {
            gApeErrorCheck = 1;
          }
          if (ape_has_errors(gApe)) {
            gApeErrors += "[Frame ";
            gApeErrors += std::to_string(gCurrentFrame);
            gApeErrors += "]\n\n";
            for (int i = 0; i < ape_errors_count(gApe); i += 1) {
              const ape_error_t * err = ape_get_error(gApe, i);
              char * error = ape_error_serialize(gApe, err);
              std::string errorString = error;
              gApeErrors += errorString;
              ape_free_allocated(gApe, error);
            }
            ape_clear_errors(gApe);
          }
        }
        if (gApeErrors != "" && gF2Toggle == 1) {
          ImVec2 inputSize = {};
          inputSize.x = -1;
          inputSize.y = 200;
          igInputTextMultiline(" Error", &gApeErrors[0], gApeErrors.size(), inputSize, ImGuiInputTextFlags_ReadOnly, 0, 0);
        }
      }
      if (igIsKeyPressed(igGetKeyIndex(ImGuiKey_Escape), 0)) {
      } else {
        ImVec2 inputSize = {};
        inputSize.x = -1;
        inputSize.y = -1;
        igInputTextMultiline(" Script", &gApeCodeChars[0], gApeCodeChars.size(), inputSize, ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CallbackResize, guiCodeEditorCallback, 0);
      }
    }
    igEnd();
    static int apeMemoryViewerWindowIsOpen                  = 1;
    static int apeMemoryViewerWindowGlobalArrayIsShared     = 0;
    static int apeMemoryViewerWindowGlobalArrayIsPersistent = 0;
    static int apeMemoryViewerWindowBytesRangeLimit         = 1;
    static int apeMemoryViewerWindowBytesRangeLimitFirst    = 0;
    static int apeMemoryViewerWindowBytesRangeLimitCount    = 8;
    static int apeMemoryViewerWindowBytesPerRow             = 8;
    if (igBegin("Memory viewer", (bool *)&apeMemoryViewerWindowIsOpen, 0)) {
      {
        ImVec2 pos  = {};
        ImVec2 size = {};
        size.x = 850;
        size.y = 500;
        igSetWindowPosVec2(pos, ImGuiCond_FirstUseEver);
        igSetWindowSizeVec2(size, ImGuiCond_FirstUseEver);
        igSetWindowCollapsedBool(true, ImGuiCond_FirstUseEver);
      }
      igInputText("Global array name", &gApeMemoryViewerGlobalArrayNameChars[0], gApeMemoryViewerGlobalArrayNameChars.size(), ImGuiInputTextFlags_CallbackResize, guiMemoryViewerCallback, 0);
      igCheckbox("Global array is shared", (bool *)&apeMemoryViewerWindowGlobalArrayIsShared);
      igCheckbox("Global array is persistent", (bool *)&apeMemoryViewerWindowGlobalArrayIsPersistent);
      igInputInt("Bytes per row", &apeMemoryViewerWindowBytesPerRow, 1, 1, 0);
      igInputInt("Bytes range limit first", &apeMemoryViewerWindowBytesRangeLimitFirst, 1, 1, 0);
      igInputInt("Bytes range limit count", &apeMemoryViewerWindowBytesRangeLimitCount, 1, 1, 0);
      if (igTreeNodeStr("Bits interpretation")) {
        igInputText("Bytes", &gApeMemoryViewerInterpretBytesChars[0], gApeMemoryViewerInterpretBytesChars.size(), ImGuiInputTextFlags_CallbackResize, guiMemoryViewerIntepretBytesCallback, 0);
        char char65FromUser[65]       = {};
        char char65ReintepretedTo[65] = {};
        for (size_t i = 0, j = 0; i < gApeMemoryViewerInterpretBytesChars.size(); i += 1) {
          if (j == 64) {
            break;
          }
          char c = gApeMemoryViewerInterpretBytesChars[i];
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
        igInputText("Bytes interpreted to bits", char65ReintepretedTo, 65, ImGuiInputTextFlags_ReadOnly, 0, 0);
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
          igInputText("Bytes interpreted to char", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
          as.clear();
        }
        {
          uint8_t bb;
          memcpy((void *)&bb, (void *)&b, sizeof(uint8_t));
          as += std::to_string(bb);
          igInputText("Bytes interpreted to uint8_t", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
          as.clear();
        }
        {
          uint16_t bb;
          memcpy((void *)&bb, (void *)&b, sizeof(uint16_t));
          as += std::to_string(bb);
          igInputText("Bytes interpreted to uint16_t", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
          as.clear();
        }
        {
          uint32_t bb;
          memcpy((void *)&bb, (void *)&b, sizeof(uint32_t));
          as += std::to_string(bb);
          igInputText("Bytes interpreted to uint32_t", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
          as.clear();
        }
        {
          uint64_t bb;
          memcpy((void *)&bb, (void *)&b, sizeof(uint64_t));
          as += std::to_string(bb);
          igInputText("Bytes interpreted to uint64_t", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
          as.clear();
        }
        {
          int8_t bb;
          memcpy((void *)&bb, (void *)&b, sizeof(int8_t));
          as += std::to_string(bb);
          igInputText("Bytes interpreted to int8_t", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
          as.clear();
        }
        {
          int16_t bb;
          memcpy((void *)&bb, (void *)&b, sizeof(int16_t));
          as += std::to_string(bb);
          igInputText("Bytes interpreted to int16_t", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
          as.clear();
        }
        {
          int32_t bb;
          memcpy((void *)&bb, (void *)&b, sizeof(int32_t));
          as += std::to_string(bb);
          igInputText("Bytes interpreted to int32_t", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
          as.clear();
        }
        {
          int64_t bb;
          memcpy((void *)&bb, (void *)&b, sizeof(int64_t));
          as += std::to_string(bb);
          igInputText("Bytes interpreted to int64_t", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
          as.clear();
        }
        {
          float bb;
          memcpy((void *)&bb, (void *)&b, sizeof(float));
          as += std::to_string(bb);
          igInputText("Bytes interpreted to float", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
          as.clear();
        }
        {
          double bb;
          memcpy((void *)&bb, (void *)&b, sizeof(double));
          as += std::to_string(bb);
          igInputText("Bytes interpreted to double", &as[0], as.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
          as.clear();
        }
        igTreePop();
      }
      if (apeMemoryViewerWindowBytesPerRow <= 0) {
        apeMemoryViewerWindowBytesPerRow = 1;
      }
      if (apeMemoryViewerWindowBytesRangeLimitFirst < 0) {
        apeMemoryViewerWindowBytesRangeLimitFirst = 0;
      }
      if (apeMemoryViewerWindowBytesRangeLimitCount < 0) {
        apeMemoryViewerWindowBytesRangeLimitCount = 0;
      }
      {
        std::string key = gApeMemoryViewerGlobalArrayNameChars;
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
        if (apeMemoryViewerWindowGlobalArrayIsPersistent == 0) {
          pointer = (unsigned char *)gApeGlobalArrayPointer[keyQuery];
        } else {
          if (apeMemoryViewerWindowGlobalArrayIsShared == 0) {
            pointer = (unsigned char *)gApeGlobalArrayPersistentPointer[keyQuery];
          } else {
            pointer = (unsigned char *)gApeGlobalSharedArrayPersistentPointer[keyQuery];
          }
        }
#if 0
        if (apeMemoryViewerWindowGlobalArrayIsPersistent == 0) {
          printf("DEBUG: key        == \"%s\"\n", key.c_str());
          printf("DEBUG: key.size() == %lu\n",    key.size());
          printf("DEBUG: pointer    == %p\n",     pointer);
          for (auto & kv : gApeGlobalArrayPointer) {
            printf("DEBUG: gApeGlobalArrayPointer key: \"%s\" (size: %lu), value: %p\n", kv.first.c_str(), kv.first.size(), kv.second);
          }
          fflush(stdout);
        } else {
          if (apeMemoryViewerWindowGlobalArrayIsShared == 0) {
            printf("DEBUG: key        == \"%s\"\n", key.c_str());
            printf("DEBUG: key.size() == %lu\n",    key.size());
            printf("DEBUG: pointer    == %p\n",     pointer);
            for (auto & kv : gApeGlobalArrayPersistentPointer) {
              printf("DEBUG: gApeGlobalArrayPersistentPointer key: \"%s\" (size: %lu), value: %p\n", kv.first.c_str(), kv.first.size(), kv.second);
            }
            fflush(stdout);
          } else {
            printf("DEBUG: key        == \"%s\"\n", key.c_str());
            printf("DEBUG: key.size() == %lu\n",    key.size());
            printf("DEBUG: pointer    == %p\n",     pointer);
            for (auto & kv : gApeGlobalSharedArrayPersistentPointer) {
              printf("DEBUG: gApeGlobalSharedArrayPersistentPointer key: \"%s\" (size: %lu), value: %p\n", kv.first.c_str(), kv.first.size(), kv.second);
            }
            fflush(stdout);
          }
        }
#endif
        if (pointer != 0) {
          // Found the global array.
          uint64_t bytesCount = 0;
          if (apeMemoryViewerWindowGlobalArrayIsPersistent == 0) {
            bytesCount = gApeGlobalArrayBytesCount[keyQuery];
          } else {
            if (apeMemoryViewerWindowGlobalArrayIsShared == 0) {
              bytesCount = gApeGlobalArrayPersistentBytesCount[keyQuery];
            } else {
              bytesCount = gApeGlobalSharedArrayPersistentBytesCount[keyQuery];
            }
          }
          if (bytesCount > 0) {
            // Bytes count is valid.
            uint64_t bytesStart = 0;
            uint64_t bytesEnd   = bytesCount;
            if (apeMemoryViewerWindowBytesRangeLimit == 1) {
              // 0 1 2 3 4 . . : Count 5
              //     ^       ^
              // first 2
              // count 4
              // range 5 - 2 = 3
              bytesStart = apeMemoryViewerWindowBytesRangeLimitFirst;
              if (bytesStart > (bytesCount-1)) {
                bytesStart = bytesCount-1;
              }
              uint64_t bytesCountRange = bytesCount - bytesStart;
              bytesEnd = apeMemoryViewerWindowBytesRangeLimitCount;
              if (bytesEnd > bytesCountRange) {
                bytesEnd = bytesCountRange;
              }
            }
            unsigned char * pointerSubrange = &pointer[bytesStart];
            pointer = pointerSubrange;
            std::string rowName = address_to_hex_string((uint64_t)(void *)pointer);
            std::string rowString;
            for (uint64_t i = 0; i < bytesEnd; i += 1) {
              uint64_t row = i % apeMemoryViewerWindowBytesPerRow;
              if (row == 0 && i != 0) {
                // New row then.
                igInputText(rowName.c_str(), &rowString[0], rowString.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
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
              igInputText(rowName.c_str(), &rowString[0], rowString.size(), ImGuiInputTextFlags_ReadOnly, 0, 0);
              rowString = std::string();
            }
          }
        }
      }
    }
    igEnd();
    redFImguiEnd(gGuiImgui[0]);
    redFPopStyle();
  }
  profileEnd("imgui");

  profileBegin("state reset");
  gPreviousGameMode             = gGameMode;
  gPreviousDefaultCameraEnabled = gDefaultCameraEnabled;
  gDefaultCameraForceEnabled    = 0;
  gGlfwCodepointCharacter       = 0;
  gMouseEvent                   = 0;
  gMouseButtonIsPressed[0]      = 0;
  gMouseButtonIsPressed[1]      = 0;
  gMouseButtonIsPressed[2]      = 0;
  gMouseButtonIsPressed[3]      = 0;
  gMouseButtonIsPressed[4]      = 0;
  gMouseButtonIsPressed[5]      = 0;
  gMouseButtonIsPressed[6]      = 0;
  gMouseButtonIsPressed[7]      = 0;
  gMouseButtonIsReleased[0]     = 0;
  gMouseButtonIsReleased[1]     = 0;
  gMouseButtonIsReleased[2]     = 0;
  gMouseButtonIsReleased[3]     = 0;
  gMouseButtonIsReleased[4]     = 0;
  gMouseButtonIsReleased[5]     = 0;
  gMouseButtonIsReleased[6]     = 0;
  gMouseButtonIsReleased[7]     = 0;
  gMouseWheelScroll             = 0;
  for (auto & v : gGlfwKeyModifiers) {
    if (v.second == 2) {
      v.second = 0;
    }
  }
  for (auto & v : gGlfwKeyEvent) {
    if (v.second == 2) {
      v.second = 0;
    }
  }
  gApeDrawLabelStackDebugTexts.clear();
  gApeDrawLabelStackPoints.clear();
  gApeDrawLabelStackLines.clear();
  gApeDrawLabelStackTriangles.clear();
  gApeDrawLabelStackMeshes.clear();
  gApeDrawFbos.clear();
  gApeDrawImages.clear();
  gApeDrawImagesSubsections.clear();
  if (gStopScript == 0) {
    gCurrentFrame += 1;
  }
  if (gRunScriptOnce == 1) {
    gRunScriptOnce = 0;
    gStopScript    = 1;
  }
  if (gRunScriptOnce == 2) {
    gRunScriptOnce = 1;
  }
  profileEnd("state reset");

  profileEnd(thread1FrameString.c_str());
  profileEnd("draw");
}

static void keyPressed(RedFHandleEventParametersKey parameters) {
  {
    int      keycode   = redFEventParametersKeyGetKeycode(parameters);
    int      modifiers = redFEventParametersKeyGetModifiers(parameters);
    unsigned codepoint = redFEventParametersKeyGetCodepoint(parameters);
    if (modifiers == GLFW_MOD_SHIFT) {
      char c = (char)codepoint;
      if ((c >= 97) && (c <= 122)) {
        char character = c;
        c = character ^ 0x20;
      }
      else if (c == '`')  { c = '~'; }
      else if (c == '1')  { c = '!'; }
      else if (c == '2')  { c = '@'; }
      else if (c == '3')  { c = '#'; }
      else if (c == '4')  { c = '$'; }
      else if (c == '5')  { c = '%'; }
      else if (c == '6')  { c = '^'; }
      else if (c == '7')  { c = '&'; }
      else if (c == '8')  { c = '*'; }
      else if (c == '9')  { c = '('; }
      else if (c == '0')  { c = ')'; }
      else if (c == '-')  { c = '_'; }
      else if (c == '=')  { c = '+'; }
      else if (c == '[')  { c = '{'; }
      else if (c == ']')  { c = '}'; }
      else if (c == ';')  { c = ':'; }
      else if (c == '\'') { c = '"'; }
      else if (c == '\\') { c = '|'; }
      else if (c == ',')  { c = '<'; }
      else if (c == '.')  { c = '>'; }
      else if (c == '/')  { c = '?'; }
      else if (c == '<')  { c = '>'; }
      codepoint = (unsigned)c;
    }
    gGlfwKeyEvent[keycode]     = 1;
    gGlfwKeyModifiers[keycode] = modifiers;
    gGlfwCodepointCharacter    = codepoint;
  }

  if (gDisableDefaultFkeys == 0) {
    if (redFEventParametersKeyGetKeycode(parameters) == GLFW_KEY_F1) {
      if (gF1WindowIsShownFromNowOn == 0) {
        gF1WindowIsShownFromNowOn = 1;
      } else {
        if (redFThreadIsRunning(gThreadF1[0]) == 0) {
          scriptSave("f1.script");
          f1CommandOptionsSave("f1_options.txt");
          redFThreadStart(gThreadF1[0]);
        }
      }
    } else if (redFEventParametersKeyGetKeycode(parameters) == GLFW_KEY_F2) {
      gF2Toggle = gF2Toggle == 1 ? 0 : 1;
    } else if (redFEventParametersKeyGetKeycode(parameters) == GLFW_KEY_F3) {
      gGameMode = gGameMode == 1 ? 0 : 1;
    } else if (redFEventParametersKeyGetKeycode(parameters) == GLFW_KEY_F5) {
      apeScriptRerun(0);
      if (gStopScript == 1) {
        gRunScriptOnce = 2;
      }
    } else if (redFEventParametersKeyGetKeycode(parameters) == GLFW_KEY_F7) {
      gStopScript = 1;
    } else if (redFEventParametersKeyGetKeycode(parameters) == GLFW_KEY_F9) {
      gStopScript = 0;
    } else if (redFEventParametersKeyGetKeycode(parameters) == GLFW_KEY_F11) {
      gFullscreenF11Override     = gFullscreenF11Override == 1 ? 0 : 1;
      gFullscreenF11OverrideOnce = 1;
    }
  }
}

static void keyReleased(RedFHandleEventParametersKey parameters) {
  {
    int keycode   = redFEventParametersKeyGetKeycode(parameters);
    int modifiers = redFEventParametersKeyGetModifiers(parameters);
    gGlfwKeyEvent[keycode]     = 2;
    gGlfwKeyModifiers[keycode] = modifiers;
  }
}

static void mouseMoved(RedFHandleEventParametersMouse parameters) {
  unsigned previousEvent = gMouseEvent;
  if (previousEvent != ((unsigned)REDF_MOUSE_EVENT_TYPE_ENTERED + 1) &&
      previousEvent != ((unsigned)REDF_MOUSE_EVENT_TYPE_EXITED  + 1))
  {
    gMouseEvent = (unsigned)redFEventParametersMouseGetEventType(parameters) + 1;
  }
}

static void mouseDragged(RedFHandleEventParametersMouse parameters) {
  gMouseEvent = (unsigned)redFEventParametersMouseGetEventType(parameters) + 1;
}

static void mousePressed(RedFHandleEventParametersMouse parameters) {
  gMouseButtonIsPressed[redFEventParametersMouseGetButton(parameters)] = 1;
}

static void mouseReleased(RedFHandleEventParametersMouse parameters) {
  gMouseButtonIsReleased[redFEventParametersMouseGetButton(parameters)] = 1;
}

static void mouseScrolled(RedFHandleEventParametersMouse parameters) {
  gMouseWheelScroll = redFEventParametersMouseGetScrollY(parameters);
}

static void mouseEntered(RedFHandleEventParametersMouse parameters) {
  gMouseEvent = (unsigned)redFEventParametersMouseGetEventType(parameters) + 1;
}

static void mouseExited(RedFHandleEventParametersMouse parameters) {
  gMouseEvent = (unsigned)redFEventParametersMouseGetEventType(parameters) + 1;
}

static void dragged(RedFHandleEventParametersDrag parameters) {
  gDragAndDropPositionX = redFEventParametersDragGetPositionX(parameters);
  gDragAndDropPositionY = redFEventParametersDragGetPositionY(parameters);
  gDragAndDropFilepaths.clear();
  for (uint64_t i = 0, count = redFEventParametersDragGetFilesCount(parameters); i < count; i += 1) {
    std::string s = redFEventParametersDragGetFile(parameters, i);
    gDragAndDropFilepaths.push_back(s);
  }
  gDragAndDropCounter += 1;
}

int main(int argumentsCount, const char ** arguments) {
#ifdef __linux__
  redFGetCurrentExeDir(&gCurrentExeDir, 0);
#else
  gCurrentExeDir = (char *)calloc(1, 1);
#endif
  int width             = 1800;
  int height            = 900;
  int windowIsDecorated = 1;
  int useOpenGL32       = 1;
  for (int i = 0; i < argumentsCount; i += 1) {
    std::string arg = std::string(arguments[i]);
    gProgramArguments.push_back(arg);
    if (i > 0) {
      if (arg == "--help") {
        printf("OPTIONS:"                                "\n");
        printf("  --game-mode"                           "\n");
        printf("  --fullscreen"                          "\n");
        printf("  --width <value>"                       "\n");
        printf("  --height <value>"                      "\n");
        printf("  --set-imgui-font-global-scale <value>" "\n");
        printf("  --disable-default-fkeys"               "\n");
        printf("  --disable-window-decorations"          "\n");
        printf("  --enable-opengl21"                     "\n");
        printf("  --disable-embree-procedures"           "\n");
        printf("  --disable-redgpu-procedures"           "\n");
        printf("  --disable-xatlas-procedures"           "\n");
        printf("  --disable-fbx-procedures"              "\n");
        printf("  --set-directory-path <value>"          "\n");
#if defined(GAME_SCRIPT_NATIVE)
        printf("  --load-game-library-at-start"          "\n");
        printf("  --load-thread2-library-at-start"       "\n");
#endif
        fflush(stdout);
        exit(0);
      } else if (arg == "--game-mode") {
        gGameMode = 1;
        scriptLoad("game.script");
      } else if (arg == "--fullscreen") {
        gFullscreenExclusive = 1; // NOTE(Constantine): fullscreen means game mode fullscreen here, standard fullscreen can be achieved with pressing F11 key or calling windowSetFullscreen() script procedure.
      } else if (arg == "--width") {
        if (i + 1 < argumentsCount) {
          std::string nextArg = std::string(arguments[i + 1]);
          width = std::stoi(nextArg);
        }
      } else if (arg == "--height") {
        if (i + 1 < argumentsCount) {
          std::string nextArg = std::string(arguments[i + 1]);
          height = std::stoi(nextArg);
        }
      } else if (arg == "--set-imgui-font-global-scale") {
        if (i + 1 < argumentsCount) {
          std::string nextArg = std::string(arguments[i + 1]);
          gImguiFontGlobalScale = std::stof(nextArg);
        }
      } else if (arg == "--disable-default-fkeys") {
        gDisableDefaultFkeys = 1;
      } else if (arg == "--disable-window-decorations") {
        windowIsDecorated = 0;
      } else if (arg == "--enable-opengl21") {
        useOpenGL32 = 0;
      } else if (arg == "--disable-embree-procedures") {
        gEmbreeIsEnabled = 0;
      } else if (arg == "--disable-redgpu-procedures") {
        gRedGpuIsEnabled = 0;
      } else if (arg == "--disable-xatlas-procedures") {
        gXatlasIsEnabled = 0;
      } else if (arg == "--disable-fbx-procedures") {
        gFbxIsEnabled = 0;
      } else if (arg == "--set-directory-path") {
        if (i + 1 < argumentsCount) {
#if defined(_WIN32)
          gCurrentExeDir = _strdup(arguments[i + 1]);
#else
          gCurrentExeDir = strdup(arguments[i + 1]);
#endif
        }
#if defined(GAME_SCRIPT_NATIVE)
      } else if (arg == "--load-game-library-at-start") {
        std::string dir = gCurrentExeDir;

#if defined(__linux__)
        gsnLoadLibrary(0, dir);
#elif defined(_WIN32)
        gsnLoadLibrary(0, dir);
#else
#error Error
#endif

      } else if (arg == "--load-thread2-library-at-start") {
        std::string dir = gCurrentExeDir;

#if defined(__linux__)
        gsnLoadLibrary(1, dir);
#elif defined(_WIN32)
        gsnLoadLibrary(1, dir);
#else
#error Error
#endif

#endif // #if defined(GAME_SCRIPT_NATIVE)
      }
    }
  }
  RedFEvents events = {};
  events.setup         = setup;
  events.update        = update;
  events.draw          = draw;
  events.exit          = theexit;
  events.keyPressed    = keyPressed;
  events.keyReleased   = keyReleased;
  events.mouseMoved    = mouseMoved;
  events.mouseDragged  = mouseDragged;
  events.mousePressed  = mousePressed;
  events.mouseReleased = mouseReleased;
  events.mouseScrolled = mouseScrolled;
  events.mouseEntered  = mouseEntered;
  events.mouseExited   = mouseExited;
  events.dragged       = dragged;
  redFMain(&events, width, height, gFullscreenExclusive == 1 ? REDF_WINDOW_MODE_GAME_MODE : REDF_WINDOW_MODE_WINDOW, useOpenGL32, windowIsDecorated, 1, MSAA_SAMPLES_COUNT, 0, 0);
  scriptSave("autosave.script");
}

#if defined(GAME_SCRIPT_NATIVE)
#include "backward.cpp"
#endif

#if 0
```
let sizeofFloat = 4;
defaultCameraDefaultControlDisable();
let p = globalArrayNew8Bit("trianglePosition", 2 * sizeofFloat);
let g = gamepadGet15Buttons6AxesNumbers(0);
let BUTTON_A            = 0;
let BUTTON_B            = 1;
let BUTTON_X            = 2;
let BUTTON_Y            = 3;
let BUTTON_LEFT_BUMPER  = 4;
let BUTTON_RIGHT_BUMPER = 5;
let BUTTON_BACK         = 6;
let BUTTON_START        = 7;
let BUTTON_GUIDE        = 8;
let BUTTON_LEFT_THUMB   = 9;
let BUTTON_RIGHT_THUMB  = 10;
let BUTTON_DPAD_UP      = 11;
let BUTTON_DPAD_RIGHT   = 12;
let BUTTON_DPAD_DOWN    = 13;
let BUTTON_DPAD_LEFT    = 14;
let AXIS_LEFT_X         = 15;
let AXIS_LEFT_Y         = 16;
let AXIS_RIGHT_X        = 17;
let AXIS_RIGHT_Y        = 18;
let AXIS_LEFT_TRIGGER   = 19;
let AXIS_RIGHT_TRIGGER  = 20;
var x = pointerGetNumber(p, 0);
var y = pointerGetNumber(p, 1);
var xdiff = g[15];
var ydiff = g[16];
if (xdiff > -0.05 && xdiff < 0.05) {
    xdiff = 0;
}
if (ydiff > -0.05 && ydiff < 0.05) {
    ydiff = 0;
}
xdiff *= 0.1;
ydiff *= 0.1;
x += xdiff;
y -= ydiff;
pointerSetNumber(p, 0, x);
pointerSetNumber(p, 1, y);
drawTriangle(" ", 0+x,0+y,0, 0+x,1+y,0, 1+x,0.5+y,0, 255,45,85,255);
```

```
let sizeofFloat = 4;
defaultCameraDefaultControlDisable();
mouseGlfwSetInputMode(2);
let p = globalArrayNew8Bit("trianglePosition", 2 * sizeofFloat);
var x = pointerGetNumber(p, 0);
var y = pointerGetNumber(p, 1);
var xdiff = (mouseGetX() - mouseGetPreviousX()) * 0.01;
var ydiff = (mouseGetY() - mouseGetPreviousY()) * 0.01;
if (mouseGetMoveEvent() != 2 && mouseGetMoveEvent() != 4) {
    xdiff = 0;
    ydiff = 0;
}
x += xdiff;
y -= ydiff;
pointerSetNumber(p, 0, x);
pointerSetNumber(p, 1, y);
drawTriangle(" ", 0+x,0+y,0, 0+x,1+y,0, 1+x,0.5+y,0, 255,45,85,255);
```

```
let sizeofFloat = 4;
let p = globalArrayNew8Bit("test", 40 * sizeofFloat);
for (var i = 0; i < globalArrayGetBytesCount("test") / sizeofFloat; i += 1) {
    pointerSetNumber(p, i, i + 42);
    drawDebugText("Value: " + numberToString(pointerGetNumber(p, i)), 0,i*20, 255,255,255,255);
}
```

```
defaultCameraDefaultControlDisable();
let mouseEvent = mouseGetMoveEvent();
drawDebugText("Mouse event: " + numberToString(mouseEvent), 0,0, 255,255,255,255);
if (mouseEvent == 2) {
  drawDebugText("MOVED", 0,2*20, 0,0,255,255);
}
if (mouseEvent == 4) {
  drawDebugText("DRAGGED", 0,4*20, 255,0,0,255);
}
if (mouseEvent == 6) {
  drawDebugText("ENTERED", 0,6*20, 0,255,0,255);
}
if (mouseEvent == 7) {
  drawDebugText("EXITED", 0,7*20, 255,0,0,255);
}
```

```
defaultCameraSetVector(0, 40, 0);
framebufferBegin("X", 900,900, true);
setBackgroundColor(25, 0, 10, 255);
drawSphereWireframe(0,0,0, 50, 255,0,85,255);
framebufferEnd("X");

defaultCameraSetVector(0, -80, 0);
framebufferBegin("Y", 900,900, true);
setBackgroundColor(10, 0, 25, 255);
drawSphereWireframe(0,0,0, 50, 255,0,85,255);
framebufferEnd("Y");

framebufferDraw("X", 0,  0, 900, 900);
framebufferDraw("Y", 900,0, 900, 900);
```

```
let sizeofUint = 4;
let p = globalArrayNew8Bit("p", 1 * sizeofUint);
pointerSetUnsignedInteger(p, 0, 42);
printDraw(numberToBinaryString(pointerGetRaw32Bit(p, 0 * sizeofUint)));
```

```
let s = "Hello!";
let p = globalArrayNew8Bit("p", strlenWithNullChar(s));
pointerSetString(p, 0, s);
printDraw("String length: " + numberToString(strlenWithNullChar(s)) + "\n" + "String: " + pointerGetString(p) + "\n");
```

```
let m = meshNew("m");
if (getCurrentFrame() == 0) {
  meshAddVertex(m, 0, 0, 0);
  meshAddVertex(m, 1, 0, 0);
  meshAddVertex(m, 0, 1, 0);
}
meshDraw(m, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0);
```

```
let m = meshNew("m");
if (getCurrentFrame() == 0) {
  meshAddVertex(m, 0, 0, 0);
  meshAddColor(m, 1, 0, 0, 1);
  meshAddVertex(m, 0, 0, 0);
  meshAddColor(m, 0, 1, 0, 1);
  meshAddVertex(m, 0, 0, 0);
  meshAddColor(m, 0, 0, 1, 1);
}
let p = meshGetVerticesPointer(m);
pointerSetNumber(p, 3, 5);
pointerSetNumber(p, 7, 5);
meshDraw(m, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0);
```

```
let m = meshNew("m");
if (getCurrentFrame() == 0) {
    meshAddVertex(m, 0, 0, 0);
    meshAddColor(m, 1, 0, 0, 1);
    meshAddVertex(m, 5, 0, 0);
    meshAddColor(m, 0, 1, 0, 1);
    meshAddVertex(m, 0, 5, 0);
    meshAddColor(m, 0, 0, 1, 1);
}
meshDraw(m, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0);
```

```
let m = meshNew("m");
meshDraw(m, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0);
meshDrawDebugVertices("m");
```

```
let m = meshNew("m");
if (getCurrentFrame() == 0) {
  meshAddVertex(m, 0, 0, 0);
  meshAddColor(m, 1, 0, 0, 1);
  meshAddVertex(m, 5, 0, 0);
  meshAddColor(m, 0, 1, 0, 1);
  meshAddVertex(m, 0, 5, 0);
  meshAddColor(m, 0, 0, 1, 1);
}
meshDraw(m, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0);
meshDrawDebugVertices("m");
```

```
let m = meshNew("m");
if (getCurrentFrame() == 0) {
  meshAddVertex(m, 0, 0, 0);
  meshAddColor(m, 1, 0, 0, 1);
  meshAddVertex(m, 5, 0, 0);
  meshAddColor(m, 0, 1, 0, 1);
  meshAddVertex(m, 0, 5, 0);
  meshAddColor(m, 0, 0, 1, 1);
  meshAddVertex(m, 5, 5, 0);
  meshAddColor(m, 1, 1, 0, 1);

  meshAddIndex(m, 0);
  meshAddIndex(m, 1);
  meshAddIndex(m, 2);
  meshAddIndex(m, 1);
  meshAddIndex(m, 2);
  meshAddIndex(m, 3);
}
meshDraw(m, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0);
meshDrawDebugIndices("m");
```

```
let m = meshNew("m");
if (getCurrentFrame() == 0) {
    meshAddVertex(m, 0, 0, 0);
    meshAddColor(m, 1, 0, 0, 1);
    meshAddTexCoord(m, 0, 0);
    meshAddVertex(m, 5, 0, 0);
    meshAddColor(m, 0, 1, 0, 1);
    meshAddTexCoord(m, 1, 0);
    meshAddVertex(m, 0, 5, 0);
    meshAddColor(m, 0, 0, 1, 1);
    meshAddTexCoord(m, 0, 1);
    meshAddVertex(m, 5, 5, 0);
    meshAddColor(m, 1, 1, 0, 1);
    meshAddTexCoord(m, 1, 1);

    meshAddIndex(m, 0);
    meshAddIndex(m, 1);
    meshAddIndex(m, 2);
    meshAddIndex(m, 1);
    meshAddIndex(m, 2);
    meshAddIndex(m, 3);
}
meshDraw(m, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0);
meshDrawDebugIndices("m");
```

```
let img = imageNewFromFile("img", "/home/constantine/Pictures/image.jpg");
imageSetTextureMinMagFilter(img, 9728, 9728);
imageSetTextureWrap(img, 10497, 10497);
if (0) {
  if (0) {
    imageGammaCorrect(img);
    imageUpdate(img);
  }
  if (0) {
    for (var y = 0; y < imageGetHeight(img); y += 1) {
      for (var x = 0; x < imageGetWidth(img); x += 1) {
        var color = imageGetColor(img, x, y);
        var r = color[0] / 255;
        var g = color[1] / 255;
        var b = color[2] / 255;
        r *= r;
        g *= g;
        b *= b;
        imageSetColor(img, x, y,
          r*255,
          g*255,
          b*255,
          color[3]
        );
      }
    }
    imageUpdate(img);
  }
}

let m = meshNew("m");
if (getCurrentFrame() == 0) {
    meshAddVertex(m, 0, 0, 0);
    meshAddColor(m, 1, 1, 1, 1);
    meshAddTexCoord(m, 0, 2);
    meshAddVertex(m, 5, 0, 0);
    meshAddColor(m, 1, 1, 1, 1);
    meshAddTexCoord(m, 2, 2);
    meshAddVertex(m, 0, 5, 0);
    meshAddColor(m, 1, 1, 1, 1);
    meshAddTexCoord(m, 0, 0);
    meshAddVertex(m, 5, 5, 0);
    meshAddColor(m, 1, 1, 1, 1);
    meshAddTexCoord(m, 2, 0);

    meshAddIndex(m, 0);
    meshAddIndex(m, 1);
    meshAddIndex(m, 2);
    meshAddIndex(m, 1);
    meshAddIndex(m, 2);
    meshAddIndex(m, 3);
}

imageSetColor(img, 0, 0, 255, 0, 0, 255);
imageUpdate(img);

imageBind(img);
meshDraw(m, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0);
imageUnbind(img);

meshDrawDebugTexCoords("m");
```

```
let img = imageNew("img", 512, 512);
imageSetTextureMinMagFilter(img, 9729, 9729);
imageSetTextureWrap(img, 10497, 10497);

let m = meshNew("m");
if (getCurrentFrame() == 0) {
    meshAddVertex(m, 0, 0, 0);
    meshAddColor(m, 1, 1, 1, 1);
    meshAddTexCoord(m, 0, 2);
    meshAddVertex(m, 5, 0, 0);
    meshAddColor(m, 1, 1, 1, 1);
    meshAddTexCoord(m, 2, 2);
    meshAddVertex(m, 0, 5, 0);
    meshAddColor(m, 1, 1, 1, 1);
    meshAddTexCoord(m, 0, 0);
    meshAddVertex(m, 5, 5, 0);
    meshAddColor(m, 1, 1, 1, 1);
    meshAddTexCoord(m, 2, 0);
    meshAddIndex(m, 0);
    meshAddIndex(m, 1);
    meshAddIndex(m, 2);
    meshAddIndex(m, 1);
    meshAddIndex(m, 2);
    meshAddIndex(m, 3);
}

imageSetColor(img, 0, 0, 255, 0, 0, 255);
imageUpdate(img);

framebufferBegin("X", 512,512, true);
setBackgroundColor(25, 0, 10, 255);
drawSphereWireframe(0,0,0, 50, 255,0,85,255);
framebufferEnd("X");

framebufferDraw("X", 0, 0, 512, 512);
framebufferCopyToImage("X", img);

imageBind(img);
meshDraw(m, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0);
imageUnbind(img);

meshDrawDebugTexCoords("m");
```

```
let v = binaryGetByteSizeOfFile("/opt/RedGpuSDK/libredgpu.so");
printDraw(numberToString(v));
```

```
let sizeofUint = 4;
let p = globalArrayNew8Bit("p", 6 * sizeofUint);
pointerSetUnsignedInteger(p, 0, 4);
pointerSetUnsignedInteger(p, 1, 8);
pointerSetUnsignedInteger(p, 2, 15);
pointerSetUnsignedInteger(p, 3, 16);
pointerSetUnsignedInteger(p, 4, 23);
pointerSetUnsignedInteger(p, 5, 42);
binaryWriteToFile(p, 0, 6 * sizeofUint, "/tmp/gamescript.binary");

let x = globalArrayNew8Bit("x", 6 * sizeofUint);
binaryReadFromFile("/tmp/gamescript.binary", x, 0);
printDraw("0: " + numberToBinaryString(pointerGetRaw32Bit(x, 0 * sizeofUint)) + "\n" +
          "1: " + numberToBinaryString(pointerGetRaw32Bit(x, 1 * sizeofUint)) + "\n" +
          "2: " + numberToBinaryString(pointerGetRaw32Bit(x, 2 * sizeofUint)) + "\n" +
          "3: " + numberToBinaryString(pointerGetRaw32Bit(x, 3 * sizeofUint)) + "\n" +
          "4: " + numberToBinaryString(pointerGetRaw32Bit(x, 4 * sizeofUint)) + "\n" +
          "5: " + numberToBinaryString(pointerGetRaw32Bit(x, 5 * sizeofUint)));

// $ xxd -b -c 4 /tmp/gamescript.binary
// 00000000: 00000100 00000000 00000000 00000000  ....
// 00000004: 00001000 00000000 00000000 00000000  ....
// 00000008: 00001111 00000000 00000000 00000000  ....
// 0000000c: 00010000 00000000 00000000 00000000  ....
// 00000010: 00010111 00000000 00000000 00000000  ....
// 00000014: 00101010 00000000 00000000 00000000  *...
```

```
#if 0
cd /opt/GameScript/
rm -f libgame_script_external_procedure.so
gcc -shared -fPIC lib.c -o libgame_script_external_procedure.so
exit
#endif

// lib.c

#include <stdio.h>

void libGameScriptExternalProcedureCall2(double x, double y) {
  printf("CALLING libGameScriptExternalProcedureCall2 WITH %f AND %f\n", x, y);
  fflush(stdout);
}

void libGameScriptExternalProcedureCall3(double x, double y, double z) {
  printf("CALLING libGameScriptExternalProcedureCall3 WITH %f AND %f AND %f\n", x, y, z);
  fflush(stdout);
}
```

```
let maxVertexTextureImageUnits = globalArrayNew8Bit("maxVertexTextureImageUnits", 1 * 4);
glGetIntegerv(35660, maxVertexTextureImageUnits, 0); // GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS
printDraw(numberToString(pointerGetUnsignedInteger(maxVertexTextureImageUnits, 0)));
```

```
fn NumberArray() {
    return [];
}

let suzanne = meshNew("suzanne");
if (getCurrentFrame() == 0) {
    let verticesString = stringReadFromFile("/home/constantine/Documents/suzanne.txt");
    let verticesCount = (strlenWithNullChar(verticesString)-1) / 10;
    //printDraw(numberToString(verticesCount));
    let stringNumber = globalArrayNew8Bit("stringNumber", 11);
    var vertex = NumberArray();
    append(vertex, 0);
    append(vertex, 0);
    append(vertex, 0);
    for (var i = 0; i < verticesCount; i += 1) {
        pointerSetSubstring(stringNumber, 0, verticesString, i*10, 10);
        vertex[i % 3] = interpretStringToFloat(pointerGetString(stringNumber));
        if (i % 3 == 2) {
            meshAddVertex(suzanne, vertex[0], vertex[1], vertex[2]);
            meshAddColor(suzanne, i / verticesCount, 0, 0, 1);
        }
    }
}
meshDraw(suzanne, 0, 1,1,1, 0,0,0, 0,0,0,0);
//meshDrawDebugVertices("suzanne");
```

```
drawTriangle("", 0,0,0, 1,0,0, 0,1,0, 0, 0, 255, 255);
let meshesFile = "/home/constantine/Documents/mesh.obj";
let meshes = globalArrayNew8Bit("meshes", meshImporterGetMeshesCount(meshesFile) * 8);
if (getCurrentFrame() == 0) {
    for (var i = 0; i < meshImporterGetMeshesCount(meshesFile); i += 1) {
        pointerSetRaw64Bit(meshes, i * 8, meshNew(numberToString(i)));
        meshImporterGetMesh(meshesFile, i, pointerGetRaw64Bit(meshes, i * 8));
    }
    for (var i = 0; i < meshImporterGetMeshesCount(meshesFile); i += 1) {
        let m  = pointerGetRaw64Bit(meshes, i * 8);
        let mv = meshGetVerticesPointer(m);
        for (var v = 0; v < meshGetVerticesCount(m); v += 1) {
            var c = pointerGetNumber(mv, v * 3 + 1);
            c -= 2000;  // Height start
            c *= 0.001;
            meshAddColor(m, c, c, c, 255);
        }
    }
}
for (var i = 0; i < meshImporterGetMeshesCount(meshesFile); i += 1) {
    meshDraw(pointerGetRaw64Bit(meshes, i * 8), 0, 1,1,1, 0,0,0, 0,0,0,0);
}
defaultCameraSetMoveSpeed(10);
```

```
drawTriangle("", 0,0,0, 1,0,0, 0,1,0, 0, 0, 255, 255);
let meshesFile = "/home/constantine/Documents/mesh.obj";
let meshes = globalArrayNew8Bit("meshes", meshImporterGetMeshesCount(meshesFile) * 8);
if (getCurrentFrame() == 0) {
    for (var i = 0; i < meshImporterGetMeshesCount(meshesFile); i += 1) {
        pointerSetRaw64Bit(meshes, i * 8, meshNew(numberToString(i)));
        meshImporterGetMesh(meshesFile, i, pointerGetRaw64Bit(meshes, i * 8));
    }
    for (var i = 0; i < meshImporterGetMeshesCount(meshesFile); i += 1) {
        let m  = pointerGetRaw64Bit(meshes, i * 8);
        let mv = meshGetVerticesPointer(m);
        for (var v = 0; v < meshGetVerticesCount(m); v += 1) {
            let x = pointerGetNumber(mv, v * 3 + 0);
            let y = pointerGetNumber(mv, v * 3 + 1);
            let z = pointerGetNumber(mv, v * 3 + 2);
            let cameraPos = defaultCameraGetVector();
            let rdx = cameraPos[0] - x - 25;
            let rdy = cameraPos[1] - y;
            let rdz = cameraPos[2] - z;
            let gdx = cameraPos[0] - x + 25;
            let gdy = cameraPos[1] - y;
            let gdz = cameraPos[2] - z;
            let bdx = cameraPos[0] - x;
            let bdy = cameraPos[1] - y;
            let bdz = cameraPos[2] - z;
            let r = 1 / (sqrt(rdx*rdx + rdy*rdy + rdz*rdz) * 0.1);
            let g = 1 / (sqrt(gdx*gdx + gdy*gdy + gdz*gdz) * 0.1);
            let b = 1 / (sqrt(bdx*bdx + bdy*bdy + bdz*bdz) * 0.1);
            meshAddColor(m, r, g, b, 255);
        }
    }
}
for (var i = 0; i < meshImporterGetMeshesCount(meshesFile); i += 1) {
    meshDraw(pointerGetRaw64Bit(meshes, i * 8), 0, 1,1,1, 0,0,0, 0,0,0,0);
}
defaultCameraSetMoveSpeed(10);
```

```
fn NumberArray() {
    return [];
}

let suzanneRed  = meshNew("suzanneRed");
let suzanneBlue = meshNew("suzanneBlue");
if (getCurrentFrame() == 0) {
    let verticesString = stringReadFromFile("/home/constantine/Documents/suzanne.txt");
    let verticesCount = (strlenWithNullChar(verticesString)-1) / 10;
    //printDraw(numberToString(verticesCount));
    let stringNumber = globalArrayNew8Bit("stringNumber", 11);
    var vertex = NumberArray();
    append(vertex, 0);
    append(vertex, 0);
    append(vertex, 0);
    for (var i = 0; i < verticesCount; i += 1) {
        pointerSetSubstring(stringNumber, 0, verticesString, i*10, 10);
        vertex[i % 3] = interpretStringToFloat(pointerGetString(stringNumber));
        if (i % 3 == 2) {
            meshAddVertex(suzanneRed, vertex[0], vertex[1], vertex[2]);
            meshAddColor(suzanneRed, i / verticesCount, 0, 0, 1);

            meshAddVertex(suzanneBlue, vertex[0], vertex[1], vertex[2]);
            meshAddColor(suzanneBlue, 0, 0, i / verticesCount, 1);
        }
    }
}

meshDraw(suzanneBlue, 0, 1,1,1, 3,0,0, 0,0,0,0);
clearDepth();
meshDraw(suzanneRed, 0, 1,1,1, 0,0,0, 0,0,0,0);
```

```
// game.script

// Recording example.

// Hardcoded for 1800x900 window resolution!
// Change "/home/constantine/Documents/suzanne.txt" path to suzanne.txt on your filesystem (https://github.com/procedural/suzanne/blob/main/suzanne.txt).

fn NumberArray() {
  return [];
}

thread2Run();

let suzanneRed  = meshNew("suzanneRed");
let suzanneBlue = meshNew("suzanneBlue");
if (getCurrentFrame() == 0) {
    let verticesString = stringReadFromFile("/home/constantine/Documents/suzanne.txt");
    let verticesCount = (strlenWithNullChar(verticesString)-1) / 10;
    //printDraw(numberToString(verticesCount));
    let stringNumber = globalArrayNew8Bit("stringNumber", 11);
    var vertex = NumberArray();
    append(vertex, 0);
    append(vertex, 0);
    append(vertex, 0);
    for (var i = 0; i < verticesCount; i += 1) {
        pointerSetSubstring(stringNumber, 0, verticesString, i*10, 10);
        vertex[i % 3] = interpretStringToFloat(pointerGetString(stringNumber));
        if (i % 3 == 2) {
            meshAddVertex(suzanneRed, vertex[0], vertex[1], vertex[2]);
            meshAddColor(suzanneRed, i / verticesCount, 0, 0, 1);

            meshAddVertex(suzanneBlue, vertex[0], vertex[1], vertex[2]);
            meshAddColor(suzanneBlue, 0, 0, i / verticesCount, 1);
        }
    }
}

meshDraw(suzanneBlue, 0, 1,1,1, 3,0,0, 0,0,0,0);
clearDepth();
meshDraw(suzanneRed, 0, 1,1,1, 0,0,0, 0,0,0,0);

{
  let compressionLevel = 0;
  let imageBytesCount = 1800 * 900 * 4;
  let image = globalSharedArrayPersistentNew8Bit("image", imageBytesCount);
  let imageEncBytesCount = githubR_lyehUlzBoundsEncodeOutBytesCount(imageBytesCount, compressionLevel);
  let imageEnc = globalSharedArrayPersistentNew8Bit("imageEnc", 4 + imageEncBytesCount);

  if (getCurrentFrame() > 0) {
    threadWaitForThread2FrameToFinish(getCurrentFrame()-1);
  }

  saveScreenRawToMemory(0, 0, 1800, 900, image);
}
```
```
// thread2.script

// Recording example, thread 2.

// Hardcoded for 1800x900 window resolution!

let compressionLevel   = 0;
let imageBytesCount    = 1800 * 900 * 4;
let image              = globalSharedArrayPersistentNew8Bit("image", imageBytesCount);
let imageEncBytesCount = githubR_lyehUlzBoundsEncodeOutBytesCount(imageBytesCount, compressionLevel);
let imageEnc           = globalSharedArrayPersistentNew8Bit("imageEnc", 4 + imageEncBytesCount);

pointerSetUnsignedInteger(imageEnc, 0, imageBytesCount);
var imageCompressedBytesCount = githubR_lyehUlzEncode(image, 0, imageBytesCount, imageEnc, 4, imageEncBytesCount, compressionLevel);

binaryWriteToFile(imageEnc, 0, 4 + imageCompressedBytesCount, numberToString(getCurrentFrameThread2()) + ".binary");
```
```
// game.script

// Recorded compressed image binary reader example.

// Hardcoded for 1800x900 recorded compressed image binaries!
// Change "/home/constantine/Desktop/1.000000.binary" path to your recorded compressed image binary.

let filepath        = "/home/constantine/Desktop/1.000000.binary";
let bytesCount      = binaryGetByteSizeOfFile(filepath);
let imageCompressed = globalArrayNew8Bit("imageCompressed", bytesCount);
binaryReadFromFile(filepath, imageCompressed, 0);

let imageBytesCount = pointerGetUnsignedInteger(imageCompressed, 0);
let image           = globalArrayNew8Bit("image", imageBytesCount);

githubR_lyehUlzDecode(imageCompressed, 4, bytesCount, image, 0, imageBytesCount);

let img = imageNew("img", 1800, 900);
if (getCurrentFrame() == 0) {
    for (var j = 0; j < 900; j += 1) {
        for (var i = 0; i < 1800; i += 1) {
            imageSetColor(img, i, j,
                pointerGetUnsignedInteger8Bit(image, (j * 1800 * 4) + (i * 4) + 0),
                pointerGetUnsignedInteger8Bit(image, (j * 1800 * 4) + (i * 4) + 1),
                pointerGetUnsignedInteger8Bit(image, (j * 1800 * 4) + (i * 4) + 2),
                pointerGetUnsignedInteger8Bit(image, (j * 1800 * 4) + (i * 4) + 3)
            );
        }
    }
    imageUpdate(img);
}

let m = meshNew("m");
if (getCurrentFrame() == 0) {
    meshAddVertex(m, 0, 0, 0);
    meshAddTexCoord(m, 0, 0);

    meshAddVertex(m, 5*2.0, 0, 0);
    meshAddTexCoord(m, 1, 0);

    meshAddVertex(m, 0, 5, 0);
    meshAddTexCoord(m, 0, 1);

    meshAddVertex(m, 5*2.0, 5, 0);
    meshAddTexCoord(m, 1, 1);

    meshAddIndex(m, 0);
    meshAddIndex(m, 1);
    meshAddIndex(m, 2);
    meshAddIndex(m, 1);
    meshAddIndex(m, 2);
    meshAddIndex(m, 3);
}
imageBind(img);
meshDraw(m, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0);
imageUnbind(img);
meshDrawDebugTexCoords("m");
```
```
// game.script

// Gamma corrected

let filepath        = "/home/constantine/Desktop/1.000000.binary";
let bytesCount      = binaryGetByteSizeOfFile(filepath);
let imageCompressed = globalArrayNew8Bit("imageCompressed", bytesCount);
binaryReadFromFile(filepath, imageCompressed, 0);

let imageBytesCount = pointerGetUnsignedInteger(imageCompressed, 0);
let image           = globalArrayNew8Bit("image", imageBytesCount);

githubR_lyehUlzDecode(imageCompressed, 4, bytesCount, image, 0, imageBytesCount);

let img = imageNew("img", 1800, 900);
if (getCurrentFrame() == 0) {
    for (var j = 0; j < 900; j += 1) {
        for (var i = 0; i < 1800; i += 1) {
            var r = pointerGetUnsignedInteger8Bit(image, (j * 1800 * 4) + (i * 4) + 0);
            var g = pointerGetUnsignedInteger8Bit(image, (j * 1800 * 4) + (i * 4) + 1);
            var b = pointerGetUnsignedInteger8Bit(image, (j * 1800 * 4) + (i * 4) + 2);
            var a = pointerGetUnsignedInteger8Bit(image, (j * 1800 * 4) + (i * 4) + 3);
            r /= 255; r = pow(r, 2.2); r *= 255;
            g /= 255; g = pow(g, 2.2); g *= 255;
            b /= 255; b = pow(b, 2.2); b *= 255;
            imageSetColor(img, i, j, r, g, b, a);
        }
    }
    imageUpdate(img);
}

let m = meshNew("m");
if (getCurrentFrame() == 0) {
    meshAddVertex(m, 0, 0, 0);
    meshAddTexCoord(m, 0, 0);
    meshAddVertex(m, 5*2.0, 0, 0);
    meshAddTexCoord(m, 1, 0);
    meshAddVertex(m, 0, 5, 0);
    meshAddTexCoord(m, 0, 1);
    meshAddVertex(m, 5*2.0, 5, 0);
    meshAddTexCoord(m, 1, 1);
    meshAddIndex(m, 0);
    meshAddIndex(m, 1);
    meshAddIndex(m, 2);
    meshAddIndex(m, 1);
    meshAddIndex(m, 2);
    meshAddIndex(m, 3);
}
imageBind(img);
meshDraw(m, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0);
imageUnbind(img);
meshDrawDebugTexCoords("m");
```

```
fn NumberArray() {
    return [];
}

defaultCameraSetMoveSpeed(0.05);

setCurrentFrame(0);

let suzanne = meshNew("suzanne");
if (getCurrentFrame() == 0) {
    let verticesString = stringReadFromFile("/home/constantine/Documents/suzanne.txt");
    var verticesComponentsCount = (strlenWithNullChar(verticesString)-1) / 10;
    //verticesComponentsCount = 1 * 9; // Debug N triangles
    //printDraw(numberToString(verticesCount));
    let stringNumber = globalArrayNew8Bit("stringNumber", 11);
    var vertex = NumberArray();
    append(vertex, 0);
    append(vertex, 0);
    append(vertex, 0);
    for (var i = 0; i < verticesComponentsCount; i += 1) {
        pointerSetSubstring(stringNumber, 0, verticesString, i*10, 10);
        vertex[i % 3] = interpretStringToFloat(pointerGetString(stringNumber));
        if (i % 3 == 2) {
            meshAddVertex(suzanne, vertex[0], vertex[1], vertex[2]);
            meshAddColor(suzanne, i / verticesComponentsCount, 0, 0, 1);
        }
    }
    // Compute and draw normals
    {
        let v = meshGetVerticesPointer(suzanne);
        for (var i = 0; i < verticesComponentsCount / 9; i += 1) {
            let x0 = pointerGetNumber(v, i * 9 + 0);
            let y0 = pointerGetNumber(v, i * 9 + 1);
            let z0 = pointerGetNumber(v, i * 9 + 2);

            let x1 = pointerGetNumber(v, i * 9 + 3);
            let y1 = pointerGetNumber(v, i * 9 + 4);
            let z1 = pointerGetNumber(v, i * 9 + 5);

            let x2 = pointerGetNumber(v, i * 9 + 6);
            let y2 = pointerGetNumber(v, i * 9 + 7);
            let z2 = pointerGetNumber(v, i * 9 + 8);

            let pointSize = 0.5;

            drawPoint("", x0, y0, z0, pointSize, 255,0,255,255);
            drawPoint("", x1, y1, z1, pointSize, 0,255,0,255);
            drawPoint("", x2, y2, z2, pointSize, 0,0,255,255);

            // 0 --- 1
            //   \ /
            //    2
            //
            // d10 = 1 - 0
            // d20 = 2 - 0
            // normal = d10 cross d20

            let d10x = x1 - x0;
            let d10y = y1 - y0;
            let d10z = z1 - z0;

            let d20x = x2 - x0;
            let d20y = y2 - y0;
            let d20z = z2 - z0;

            var nx = d20y*d10z - d10y*d20z;
            var ny = d20z*d10x - d10z*d20x;
            var nz = d20x*d10y - d10x*d20y;

            let l = sqrt(nx*nx + ny*ny + nz*nz);

            nx /= l;
            ny /= l;
            nz /= l;

            let normalDrawLength = 0.04;

            nx *= normalDrawLength;
            ny *= normalDrawLength;
            nz *= normalDrawLength;

            let drawOffset = 0.02;

            var x0o = x0 - ((x0-x1)*drawOffset) - ((x0-x2)*drawOffset);
            var y0o = y0 - ((y0-y1)*drawOffset) - ((y0-y2)*drawOffset);
            var z0o = z0 - ((z0-z1)*drawOffset) - ((z0-z2)*drawOffset);

            var x1o = x1 - ((x1-x2)*drawOffset) - ((x1-x0)*drawOffset);
            var y1o = y1 - ((y1-y2)*drawOffset) - ((y1-y0)*drawOffset);
            var z1o = z1 - ((z1-z2)*drawOffset) - ((z1-z0)*drawOffset);

            var x2o = x2 - ((x2-x0)*drawOffset) - ((x2-x1)*drawOffset);
            var y2o = y2 - ((y2-y0)*drawOffset) - ((y2-y1)*drawOffset);
            var z2o = z2 - ((z2-z0)*drawOffset) - ((z2-z1)*drawOffset);

            drawLine("", x0o,y0o,z0o, nx+x0o,ny+y0o,nz+z0o, 2, 255,0,255,255);
            drawLine("", x1o,y1o,z1o, nx+x1o,ny+y1o,nz+z1o, 2, 0,255,0,255);
            drawLine("", x2o,y2o,z2o, nx+x2o,ny+y2o,nz+z2o, 2, 0,0,255,255);
        }
    }
}
meshDraw(suzanne, 0, 1,1,1, 0,0,0, 0,0,0,0);
```

```
fn NumberArray() {
    return [];
}

defaultCameraSetMoveSpeed(0.025);

//setCurrentFrame(0);

let suzanne = meshNew("suzanne");
let verticesString = stringReadFromFile("/home/constantine/Documents/suzanne.txt");
var verticesComponentsCount = (strlenWithNullChar(verticesString)-1) / 10;

let trianglesNormal = globalArrayPersistentNew8Bit("trianglesNormal", (verticesComponentsCount / 9) * 3 * 4);

if (getCurrentFrame() == 0) {
    //verticesComponentsCount = 3 * 9; // Debug N triangles
    //printDraw(numberToString(verticesCount));
    let stringNumber = globalArrayNew8Bit("stringNumber", 11);
    var vertex = NumberArray();
    append(vertex, 0);
    append(vertex, 0);
    append(vertex, 0);
    for (var i = 0; i < verticesComponentsCount; i += 1) {
        pointerSetSubstring(stringNumber, 0, verticesString, i*10, 10);
        vertex[i % 3] = interpretStringToFloat(pointerGetString(stringNumber));
        if (i % 3 == 2) {
            meshAddVertex(suzanne, vertex[0], vertex[1], vertex[2]);
            meshAddColor(suzanne, i / verticesComponentsCount, 0, 0, 1);
        }
    }
    // Generate array of triangle per-vertex normals
    {
        let v = meshGetVerticesPointer(suzanne);
        for (var i = 0; i < verticesComponentsCount / 9; i += 1) {
            let x0 = pointerGetNumber(v, i * 9 + 0);
            let y0 = pointerGetNumber(v, i * 9 + 1);
            let z0 = pointerGetNumber(v, i * 9 + 2);

            let x1 = pointerGetNumber(v, i * 9 + 3);
            let y1 = pointerGetNumber(v, i * 9 + 4);
            let z1 = pointerGetNumber(v, i * 9 + 5);

            let x2 = pointerGetNumber(v, i * 9 + 6);
            let y2 = pointerGetNumber(v, i * 9 + 7);
            let z2 = pointerGetNumber(v, i * 9 + 8);

            let pointSize = 0.5;

            drawPoint("", x0, y0, z0, pointSize, 255,0,255,255);
            drawPoint("", x1, y1, z1, pointSize, 0,255,0,255);
            drawPoint("", x2, y2, z2, pointSize, 0,0,255,255);

            // 0 --- 1
            //   \ /
            //    2
            //
            // d10 = 1 - 0
            // d20 = 2 - 0
            // normal = d10 cross d20

            let d10x = x1 - x0;
            let d10y = y1 - y0;
            let d10z = z1 - z0;

            let d20x = x2 - x0;
            let d20y = y2 - y0;
            let d20z = z2 - z0;

            var nx = d20y*d10z - d10y*d20z;
            var ny = d20z*d10x - d10z*d20x;
            var nz = d20x*d10y - d10x*d20y;

            let l = sqrt(nx*nx + ny*ny + nz*nz);

            nx /= l;
            ny /= l;
            nz /= l;

            pointerSetNumber(trianglesNormal, i * 3 + 0, nx);
            pointerSetNumber(trianglesNormal, i * 3 + 1, ny);
            pointerSetNumber(trianglesNormal, i * 3 + 2, nz);

            let normalDrawLength = 0.04;

            nx *= normalDrawLength;
            ny *= normalDrawLength;
            nz *= normalDrawLength;

            let drawOffset = 0.02;

            var x0o = x0 - ((x0-x1)*drawOffset) - ((x0-x2)*drawOffset);
            var y0o = y0 - ((y0-y1)*drawOffset) - ((y0-y2)*drawOffset);
            var z0o = z0 - ((z0-z1)*drawOffset) - ((z0-z2)*drawOffset);

            var x1o = x1 - ((x1-x2)*drawOffset) - ((x1-x0)*drawOffset);
            var y1o = y1 - ((y1-y2)*drawOffset) - ((y1-y0)*drawOffset);
            var z1o = z1 - ((z1-z2)*drawOffset) - ((z1-z0)*drawOffset);

            var x2o = x2 - ((x2-x0)*drawOffset) - ((x2-x1)*drawOffset);
            var y2o = y2 - ((y2-y0)*drawOffset) - ((y2-y1)*drawOffset);
            var z2o = z2 - ((z2-z0)*drawOffset) - ((z2-z1)*drawOffset);

            drawLine("", x0o,y0o,z0o, nx+x0o,ny+y0o,nz+z0o, 2, 255,0,255,255);
            drawLine("", x1o,y1o,z1o, nx+x1o,ny+y1o,nz+z1o, 2, 0,255,0,255);
            drawLine("", x2o,y2o,z2o, nx+x2o,ny+y2o,nz+z2o, 2, 0,0,255,255);
        }
    }
}

//meshDraw(suzanne, 0, 1,1,1, 0,0,0, 0,0,0,0);

{
    let v = meshGetVerticesPointer(suzanne);
    for (var i = 0; i < verticesComponentsCount / 9; i += 1) {
        let x0 = pointerGetNumber(v, i * 9 + 0);
        let y0 = pointerGetNumber(v, i * 9 + 1);
        let z0 = pointerGetNumber(v, i * 9 + 2);

        let x1 = pointerGetNumber(v, i * 9 + 3);
        let y1 = pointerGetNumber(v, i * 9 + 4);
        let z1 = pointerGetNumber(v, i * 9 + 5);

        let x2 = pointerGetNumber(v, i * 9 + 6);
        let y2 = pointerGetNumber(v, i * 9 + 7);
        let z2 = pointerGetNumber(v, i * 9 + 8);

        var nx = pointerGetNumber(trianglesNormal, i * 3 + 0);
        var ny = pointerGetNumber(trianglesNormal, i * 3 + 1);
        var nz = pointerGetNumber(trianglesNormal, i * 3 + 2);

        // https://blender.stackexchange.com/questions/187129/eevee-normal-pass-remap-negative-values/
        if (nx < 0) { nx *= -1; }
        if (ny < 0) { ny *= -1; }
        if (nz < 0) { nz *= -1; }

        drawTriangle("", x0, y0, z0, x1, y1, z1, x2, y2, z2, nx*255,ny*255,nz*255,255);
    }
}
```

```
defaultCameraDefaultControlDisable();
defaultCameraSetProjectionMode(1);
defaultCameraSetVector(0, 0, 1);

let m = meshNew("m");
if (getCurrentFrame() == 0) {
    meshAddVertex(m,-windowGetWidth()/2,-windowGetHeight()/2, 0);
    meshAddVertex(m, windowGetWidth()/2,-windowGetHeight()/2, 0);
    meshAddVertex(m,-windowGetWidth()/2, windowGetHeight()/2, 0);
    meshAddVertex(m, windowGetWidth()/2, windowGetHeight()/2, 0);

    meshAddColor(m, 1, 0, 0, 1);
    meshAddColor(m, 0, 1, 0, 1);
    meshAddColor(m, 0, 0, 1, 1);
    meshAddColor(m, 1, 1, 0, 1);

    meshAddIndex(m, 0);
    meshAddIndex(m, 1);
    meshAddIndex(m, 2);
    meshAddIndex(m, 1);
    meshAddIndex(m, 2);
    meshAddIndex(m, 3);
}

meshDraw(m, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0);
```
```
defaultCameraDefaultControlDisable();
defaultCameraSetProjectionMode(0);
defaultCameraSetVector(0, 0, 1);

{
    let topLeftX     =-1;
    let topLeftY     = 1;
    let topLeftZ     = 0;
    let bottomLeftX  =-1;
    let bottomLeftY  =-1;
    let bottomLeftZ  = 0;
    let bottomRightX = 1;
    let bottomRightY =-1;
    let bottomRightZ = 0;
    defaultCameraSetupOffAxisViewPortal(topLeftX, topLeftY, topLeftZ, bottomLeftX, bottomLeftY, bottomLeftZ, bottomRightX, bottomRightY, bottomRightZ);
}

let m = meshNew("m");
if (getCurrentFrame() == 0) {
    meshAddVertex(m,-1,-1, 0);
    meshAddVertex(m, 1,-1, 0);
    meshAddVertex(m,-1, 1, 0);
    meshAddVertex(m, 1, 1, 0);

    meshAddColor(m, 1, 0, 0, 1);
    meshAddColor(m, 0, 1, 0, 1);
    meshAddColor(m, 0, 0, 1, 1);
    meshAddColor(m, 1, 1, 0, 1);

    meshAddIndex(m, 0);
    meshAddIndex(m, 1);
    meshAddIndex(m, 2);
    meshAddIndex(m, 1);
    meshAddIndex(m, 2);
    meshAddIndex(m, 3);
}

meshDraw(m, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0);
```
```
defaultCameraSetProjectionMode(0);

if (getCurrentFrame() == 0) {
    defaultCameraSetVector(0, 0, 1);
    let topLeftX     =-1;
    let topLeftY     = 1;
    let topLeftZ     = 0;
    let bottomLeftX  =-1;
    let bottomLeftY  =-1;
    let bottomLeftZ  = 0;
    let bottomRightX = 1;
    let bottomRightY =-1;
    let bottomRightZ = 0;
    defaultCameraSetupOffAxisViewPortal(topLeftX, topLeftY, topLeftZ, bottomLeftX, bottomLeftY, bottomLeftZ, bottomRightX, bottomRightY, bottomRightZ);
}

let m = meshNew("m");
if (getCurrentFrame() == 0) {
    meshAddVertex(m,-1,-1, 0);
    meshAddVertex(m, 1,-1, 0);
    meshAddVertex(m,-1, 1, 0);
    meshAddVertex(m, 1, 1, 0);

    meshAddColor(m, 1, 0, 0, 1);
    meshAddColor(m, 0, 1, 0, 1);
    meshAddColor(m, 0, 0, 1, 1);
    meshAddColor(m, 1, 1, 0, 1);

    meshAddIndex(m, 0);
    meshAddIndex(m, 1);
    meshAddIndex(m, 2);
    meshAddIndex(m, 1);
    meshAddIndex(m, 2);
    meshAddIndex(m, 3);
}

meshDraw(m, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0);
```

```
fn defaultCameraGamepadControlEnable() {
    let BUTTON_A            = 0;
    let BUTTON_B            = 1;
    let BUTTON_X            = 2;
    let BUTTON_Y            = 3;
    let BUTTON_LEFT_BUMPER  = 4;
    let BUTTON_RIGHT_BUMPER = 5;
    let BUTTON_BACK         = 6;
    let BUTTON_START        = 7;
    let BUTTON_GUIDE        = 8;
    let BUTTON_LEFT_THUMB   = 9;
    let BUTTON_RIGHT_THUMB  = 10;
    let BUTTON_DPAD_UP      = 11;
    let BUTTON_DPAD_RIGHT   = 12;
    let BUTTON_DPAD_DOWN    = 13;
    let BUTTON_DPAD_LEFT    = 14;
    let AXIS_LEFT_X         = 15;
    let AXIS_LEFT_Y         = 16;
    let AXIS_RIGHT_X        = 17;
    let AXIS_RIGHT_Y        = 18;
    let AXIS_LEFT_TRIGGER   = 19;
    let AXIS_RIGHT_TRIGGER  = 20;
    let g  = gamepadGet15Buttons6AxesNumbers(0);
    let p  = defaultCameraGetVector();
    let dx = defaultCameraGetSideVector();
    let dy = defaultCameraGetUpVector();
    let dz = defaultCameraGetLookAtVector();
    let axisDeadZone    = 0.15;
    let triggerDeadZone = 0.0;
    let speedRotate     = 1.5;
    let speedMove       = 0.1;

    var xl = g[17];
    var yl = g[18];
    if (xl > -axisDeadZone && xl < axisDeadZone) {
        xl = 0;
    }
    if (yl > -axisDeadZone && yl < axisDeadZone) {
        yl = 0;
    }
    xl *= speedRotate;
    yl *= speedRotate;
    defaultCameraRotate(0, 1, 0, -xl);
    defaultCameraRotate(dx[0], dx[1], dx[2], -yl);

    var xr = g[15];
    var yr = g[16];
    if (xr > -axisDeadZone && xr < axisDeadZone) {
        xr = 0;
    }
    if (yr > -axisDeadZone && yr < axisDeadZone) {
        yr = 0;
    }
    xr *= speedMove;
    yr *= speedMove;
    var yt = 0.0;
    if (g[19] > triggerDeadZone) {
        yt -= g[19] * speedMove;
    }
    if (g[20] > triggerDeadZone) {
        yt += g[20] * speedMove;
    }
    defaultCameraSetVector(p[0] + (dz[0]*-yr) + (dx[0]*xr), p[1] + (dz[1]*-yr) + (dx[1]*xr) + yt, p[2] + (dz[2]*-yr) + (dx[2]*xr));
}

fn NumberArray() {
    return [];
}

defaultCameraDefaultControlDisable();
defaultCameraGamepadControlEnable();

let suzanne = meshNew("suzanne");
if (getCurrentFrame() == 0) {
    let verticesString = stringReadFromFile("/home/constantine/Documents/suzanne.txt");
    let verticesComponentsCount = (strlenWithNullChar(verticesString)-1) / 10;
    //printDraw(numberToString(verticesComponentsCount));
    let stringNumber = globalArrayNew8Bit("stringNumber", 11);
    var vertex = NumberArray();
    append(vertex, 0);
    append(vertex, 0);
    append(vertex, 0);
    for (var i = 0; i < verticesComponentsCount; i += 1) {
        pointerSetSubstring(stringNumber, 0, verticesString, i*10, 10);
        vertex[i % 3] = interpretStringToFloat(pointerGetString(stringNumber));
        if (i % 3 == 2) {
            meshAddVertex(suzanne, vertex[0], vertex[1], vertex[2]);
            meshAddColor(suzanne, i / verticesComponentsCount, 0, 0, 1);
        }
    }
}
meshDraw(suzanne, 0, 1,1,1, 0,0,0, 0,0,0,0);
```

```
fn NumberArray() {
    return [];
}

fn triangleGetNormal(x0, y0, z0, x1, y1, z1, x2, y2, z2) {
  // 0 --- 1
  //   \ /
  //    2
  //
  // d10 = 1 - 0
  // d20 = 2 - 0
  // normal = d10 cross d20

  let d10x = x1 - x0;
  let d10y = y1 - y0;
  let d10z = z1 - z0;

  let d20x = x2 - x0;
  let d20y = y2 - y0;
  let d20z = z2 - z0;

  var nx = d20y*d10z - d10y*d20z;
  var ny = d20z*d10x - d10z*d20x;
  var nz = d20x*d10y - d10x*d20y;

  let l = sqrt(nx*nx + ny*ny + nz*nz);

  nx /= l;
  ny /= l;
  nz /= l;

  var out = NumberArray();
  append(out, nx);
  append(out, ny);
  append(out, nz);
  return out;
}
```
```
drawTriangle("", 0,0,0, 1,0,0, 0,1,0, 0, 0, 255, 255);
let meshesFile = "/home/constantine/Documents/mesh.obj";
let meshes = globalArrayNew8Bit("meshes", meshImporterGetMeshesCount(meshesFile) * 8);
if (getCurrentFrame() == 0) {
    for (var i = 0; i < meshImporterGetMeshesCount(meshesFile); i += 1) {
        pointerSetRaw64Bit(meshes, i * 8, meshNew(numberToString(i)));
        meshImporterGetMesh(meshesFile, i, pointerGetRaw64Bit(meshes, i * 8));
    }
    for (var j = 0; j < meshImporterGetMeshesCount(meshesFile); j += 1) {
        let m = pointerGetRaw64Bit(meshes, j * 8);
        for (var i = 0; i < meshGetVerticesCount(m); i += 1) {
          meshAddColor(m, 0, 0, 0, 255);
        }
        let mv = meshGetVerticesPointer(m);
        let mi = meshGetIndicesPointer(m);
        let mc = meshGetColorsPointer(m);

        for (var i = 0; i < meshGetIndicesCount(m) / 3; i += 1) {
            let i0 = pointerGetUnsignedInteger(mi, i * 3 + 0);
            let i1 = pointerGetUnsignedInteger(mi, i * 3 + 1);
            let i2 = pointerGetUnsignedInteger(mi, i * 3 + 2);

            let x0 = pointerGetNumber(mv, i0 * 3 + 0);
            let y0 = pointerGetNumber(mv, i0 * 3 + 1);
            let z0 = pointerGetNumber(mv, i0 * 3 + 2);
            let x1 = pointerGetNumber(mv, i1 * 3 + 0);
            let y1 = pointerGetNumber(mv, i1 * 3 + 1);
            let z1 = pointerGetNumber(mv, i1 * 3 + 2);
            let x2 = pointerGetNumber(mv, i2 * 3 + 0);
            let y2 = pointerGetNumber(mv, i2 * 3 + 1);
            let z2 = pointerGetNumber(mv, i2 * 3 + 2);

            let triangleNormal = triangleGetNormal(x0, y0, z0, x1, y1, z1, x2, y2, z2);
            var nx = triangleNormal[0];
            var ny = triangleNormal[1];
            var nz = triangleNormal[2];

            // https://blender.stackexchange.com/questions/187129/eevee-normal-pass-remap-negative-values/
            if (nx < 0) { nx *= -1; }
            if (ny < 0) { ny *= -1; }
            if (nz < 0) { nz *= -1; }

            pointerSetNumber(mc, i0 * 4 + 0, nx);
            pointerSetNumber(mc, i0 * 4 + 1, ny);
            pointerSetNumber(mc, i0 * 4 + 2, nz);
            pointerSetNumber(mc, i1 * 4 + 0, nx);
            pointerSetNumber(mc, i1 * 4 + 1, ny);
            pointerSetNumber(mc, i1 * 4 + 2, nz);
            pointerSetNumber(mc, i2 * 4 + 0, nx);
            pointerSetNumber(mc, i2 * 4 + 1, ny);
            pointerSetNumber(mc, i2 * 4 + 2, nz);
        }
    }
}
for (var i = 0; i < meshImporterGetMeshesCount(meshesFile); i += 1) {
    meshDraw(pointerGetRaw64Bit(meshes, i * 8), 0, 1,1,1, 0,0,0, 0,0,0,0);
}
defaultCameraSetMoveSpeed(10);
defaultCameraSetMouseSensitivity(0.4);
defaultCameraSetNearClip(5);
defaultCameraSetFarClip(5000);
```

```
fn meshConvertToIndexMesh(mesh) {
    meshClearIndices(mesh);
    for (var i = 0; i < meshGetVerticesCount(mesh) / 3; i += 1) {
        meshAddTriangle(mesh, i * 3 + 0, i * 3 + 1, i * 3 + 2);
    }
}
```

```
fn crossProduct(x0, y0, z0, x1, y1, z1) {
	let x = y0 * z1 - y1 * z0
	let y = z0 * x1 - z1 * x0
	let z = x0 * y1 - x1 * y0
	return [x, y, z]
}

fn dotProduct(x0, y0, z0, x1, y1, z1) {
	return x0 * x1 + y0 * y1 + z0 * z1
}

// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
fn rayTriangleIntersection(rayOriginX, rayOriginY, rayOriginZ, rayVectorX, rayVectorY, rayVectorZ, trianglev0x, trianglev0y, trianglev0z, trianglev1x, trianglev1y, trianglev1z, trianglev2x, trianglev2y, trianglev2z) {
	let epsilon = 0.0000001
	let vertex0x = trianglev0x
	let vertex0y = trianglev0y
	let vertex0z = trianglev0z
	let vertex1x = trianglev1x
	let vertex1y = trianglev1y
	let vertex1z = trianglev1z
	let vertex2x = trianglev2x
	let vertex2y = trianglev2y
	let vertex2z = trianglev2z
	let edge1x = vertex1x - vertex0x
	let edge1y = vertex1y - vertex0y
	let edge1z = vertex1z - vertex0z
	let edge2x = vertex2x - vertex0x
	let edge2y = vertex2y - vertex0y
	let edge2z = vertex2z - vertex0z
	let hv = crossProduct(rayVectorX, rayVectorY, rayVectorZ, edge2x, edge2y, edge2z)
	let hx = hv[0]
	let hy = hv[1]
	let hz = hv[2]
	let a = dotProduct(edge1x, edge1y, edge1z, hx, hy, hz)
	if (a > -epsilon && a < epsilon) {
		return [0, 0, 0, 0] // This ray is parallel to this triangle.
	}
	let f = 1.0 / a
	let sx = rayOriginX - vertex0x
	let sy = rayOriginY - vertex0y
	let sz = rayOriginZ - vertex0z
	let u = f * dotProduct(sx, sy, sz, hx, hy, hz)
	if (u < 0.0 || u > 1.0) {
		return [0, 0, 0, 0]
	}
	let qv = crossProduct(sx, sy, sz, edge1x, edge1y, edge1z)
	let qx = qv[0]
	let qy = qv[1]
	let qz = qv[2]
	let v = f * dotProduct(rayVectorX, rayVectorY, rayVectorZ, qx, qy, qz)
	if (v < 0.0 || u + v > 1.0) {
		return [0, 0, 0, 0]
	}
	// At this stage we can compute t to find out where the intersection point is on the line.
	let t = f * dotProduct(edge2x, edge2y, edge2z, qx, qy, qz)
	if (t > epsilon) {
		// Ray intersection
		let outIntersectionPointX = rayOriginX + rayVectorX * t
		let outIntersectionPointY = rayOriginY + rayVectorY * t
		let outIntersectionPointZ = rayOriginZ + rayVectorZ * t
		return [outIntersectionPointX, outIntersectionPointY, outIntersectionPointZ, 1]
	} else {
		// This means that there is a line intersection but not a ray intersection.
		return [0, 0, 0, 0]
	}
}

defaultCameraSetMoveSpeed(0.01)

let suzanne = meshNew("suzanne")
var verticesComponentsCount = 0
if (getCurrentFrame() == 0) {
	let verticesString = stringReadFromFile(getExeDirectoryPath() + "data/suzanne.txt")
	verticesComponentsCount = (strlenWithNullChar(verticesString)-1) / 10
	//printDraw(numberToString(verticesCount))
	let stringNumber = globalArrayNew8Bit("stringNumber", 11)
	var vertex = [0, 0, 0]
	for (var i = 0; i < verticesComponentsCount; i += 1) {
		pointerSetSubstring(stringNumber, 0, verticesString, i*10, 10)
		vertex[i % 3] = interpretStringToFloat(pointerGetString(stringNumber))
		if (i % 3 == 2) {
			meshAddVertex(suzanne, vertex[0], vertex[1], vertex[2])
			meshAddColor(suzanne, i / verticesComponentsCount, 0, 0, 1)
		}
	}
}

meshDraw(suzanne, 1, 1,1,1, 0,0,0, 0,0,0,0)

let intersectionPointsMaxPossibleCount = 64
let intersectionPoints = globalArrayNew8Bit("intersectionPoints", intersectionPointsMaxPossibleCount * 3 * 4)
let intersectionPointsCount = globalArrayNew8Bit("intersectionPointsCount", 1 * 4)
let oro = globalArrayNew8Bit("oro", 1 * 3 * 4)
let orv = globalArrayNew8Bit("orv", 1 * 3 * 4)
if (getCurrentFrame() == 0) {
	let ro = defaultCameraGetVector()
	let rv = defaultCameraGetLookAtVector()

	pointerSetNumber(oro, 0, ro[0])
	pointerSetNumber(oro, 1, ro[1])
	pointerSetNumber(oro, 2, ro[2])
	pointerSetNumber(orv, 0, rv[0])
	pointerSetNumber(orv, 1, rv[1])
	pointerSetNumber(orv, 2, rv[2])

	let v = meshGetVerticesPointer(suzanne)
	for (var i = 0; i < verticesComponentsCount / 9; i += 1) {
		let x0 = pointerGetNumber(v, i * 9 + 0)
		let y0 = pointerGetNumber(v, i * 9 + 1)
		let z0 = pointerGetNumber(v, i * 9 + 2)

		let x1 = pointerGetNumber(v, i * 9 + 3)
		let y1 = pointerGetNumber(v, i * 9 + 4)
		let z1 = pointerGetNumber(v, i * 9 + 5)

		let x2 = pointerGetNumber(v, i * 9 + 6)
		let y2 = pointerGetNumber(v, i * 9 + 7)
		let z2 = pointerGetNumber(v, i * 9 + 8)

		let intersectionPoint = rayTriangleIntersection(ro[0], ro[1], ro[2], rv[0], rv[1], rv[2], x0, y0, z0, x1, y1, z1, x2, y2, z2)

		if (intersectionPoint[3] != 0) {
			//drawPoint("intersectionPoint", intersectionPoint[0], intersectionPoint[1], intersectionPoint[2], 1, 255, 0, 255, 255)
			pointerSetNumber(intersectionPoints, pointerGetUnsignedInteger(intersectionPointsCount, 0) * 3 + 0, intersectionPoint[0])
			pointerSetNumber(intersectionPoints, pointerGetUnsignedInteger(intersectionPointsCount, 0) * 3 + 1, intersectionPoint[1])
			pointerSetNumber(intersectionPoints, pointerGetUnsignedInteger(intersectionPointsCount, 0) * 3 + 2, intersectionPoint[2])
			let oldValue = pointerGetUnsignedInteger(intersectionPointsCount, 0)
			pointerSetUnsignedInteger(intersectionPointsCount, 0, oldValue + 1)
		}
	}
}

{
	let x = pointerGetNumber(oro, 0)
	let y = pointerGetNumber(oro, 1)
	let z = pointerGetNumber(oro, 2)
	drawPoint("Ray origin", x, y, z, 1, 0, 0, 255, 255)
}
drawLine("",
	pointerGetNumber(oro, 0),
	pointerGetNumber(oro, 1),
	pointerGetNumber(oro, 2),
	pointerGetNumber(oro, 0) + (pointerGetNumber(orv, 0) * 1000),
	pointerGetNumber(oro, 1) + (pointerGetNumber(orv, 1) * 1000),
	pointerGetNumber(oro, 2) + (pointerGetNumber(orv, 2) * 1000),
	1, 0, 0, 255, 255
)
for (var i = 0; i < pointerGetUnsignedInteger(intersectionPointsCount, 0); i += 1) {
	let x = pointerGetNumber(intersectionPoints, i * 3 + 0)
	let y = pointerGetNumber(intersectionPoints, i * 3 + 1)
	let z = pointerGetNumber(intersectionPoints, i * 3 + 2)
	drawPoint("Intersection point", x, y, z, 1, 255, 0, 255, 255)
}
```
```
// For Game Script from Jan 2, 2022.

fn NumberArray() {
	return [];
}

fn meshConvertToIndexMesh(mesh) { // Number
	meshClearIndices(mesh);
	for (var i = 0; i < meshGetVerticesCount(mesh) / 3; i += 1) {
		meshAddTriangle(mesh, i * 3 + 0, i * 3 + 1, i * 3 + 2);
	}
}

printDraw("Frame: " + numberToString(getCurrentFrame()));

{
	let cameraVector = defaultCameraGetVector();
	let cameraVersor = defaultCameraGetVersor();
	if (cameraVector[0] == 0 && cameraVector[1] == 0 && cameraVector[2] == 10 &&
	    cameraVersor[0] == 0 && cameraVersor[1] == 0 && cameraVersor[2] == 0  && cameraVersor[3] == 1)
	{
		defaultCameraSetVector(-3.359291, 0.254475,-3.232193);
		defaultCameraSetVersor( 0.003961, 0.978337, 0.018788, -0.206169);
	}
}

if (false) {
	printDraw(
		numberToString(defaultCameraGetVector()[0]) + " " +
		numberToString(defaultCameraGetVector()[1]) + " " +
		numberToString(defaultCameraGetVector()[2]) + " " +
		numberToString(defaultCameraGetVersor()[0]) + " " +
		numberToString(defaultCameraGetVersor()[1]) + " " +
		numberToString(defaultCameraGetVersor()[2]) + " " +
		numberToString(defaultCameraGetVersor()[3])
	);
}

defaultCameraSetMoveSpeed(0.025);

//setCurrentFrame(0);

let suzanne = meshNew("suzanne");
let verticesString = stringReadFromFile("data/suzanne.txt");
var verticesComponentsCount = (strlenWithNullChar(verticesString)-1) / 10;

let trianglesNormal = globalArrayPersistentNew8Bit("trianglesNormal", (verticesComponentsCount / 9) * 3 * 4);
let verticesNormal = globalArrayPersistentNew8Bit("verticesNormal", verticesComponentsCount * 4);

if (getCurrentFrame() == 0) {
	//verticesComponentsCount = 3 * 9; // Debug N triangles
	//printDraw(numberToString(verticesCount));
	let stringNumber = globalArrayNew8Bit("stringNumber", 11);
	var vertex = NumberArray();
	append(vertex, 0);
	append(vertex, 0);
	append(vertex, 0);
	for (var i = 0; i < verticesComponentsCount; i += 1) {
		pointerSetSubstring(stringNumber, 0, verticesString, i*10, 10);
		vertex[i % 3] = interpretStringToFloat(pointerGetString(stringNumber));
		if (i % 3 == 2) {
			meshAddVertex(suzanne, vertex[0], vertex[1], vertex[2]);
			meshAddColor(suzanne, i / verticesComponentsCount, i / verticesComponentsCount, i / verticesComponentsCount, 1);
		}
	}
	// Generate array of triangle per-vertex normals
	{
		let v = meshGetVerticesPointer(suzanne);
		for (var i = 0; i < verticesComponentsCount / 9; i += 1) {
			let x0 = pointerGetNumber(v, i * 9 + 0);
			let y0 = pointerGetNumber(v, i * 9 + 1);
			let z0 = pointerGetNumber(v, i * 9 + 2);

			let x1 = pointerGetNumber(v, i * 9 + 3);
			let y1 = pointerGetNumber(v, i * 9 + 4);
			let z1 = pointerGetNumber(v, i * 9 + 5);

			let x2 = pointerGetNumber(v, i * 9 + 6);
			let y2 = pointerGetNumber(v, i * 9 + 7);
			let z2 = pointerGetNumber(v, i * 9 + 8);

			let pointSize = 0.5;

			drawPoint("", x0, y0, z0, pointSize, 255,0,255,255);
			drawPoint("", x1, y1, z1, pointSize, 0,255,0,255);
			drawPoint("", x2, y2, z2, pointSize, 0,0,255,255);

			// 0 --- 1
			//   \ /
			//    2
			//
			// d10 = 1 - 0
			// d20 = 2 - 0
			// normal = d10 cross d20

			let d10x = x1 - x0;
			let d10y = y1 - y0;
			let d10z = z1 - z0;

			let d20x = x2 - x0;
			let d20y = y2 - y0;
			let d20z = z2 - z0;

			var nx = d20y*d10z - d10y*d20z;
			var ny = d20z*d10x - d10z*d20x;
			var nz = d20x*d10y - d10x*d20y;

			let l = sqrt(nx*nx + ny*ny + nz*nz);

			nx /= l;
			ny /= l;
			nz /= l;

			pointerSetNumber(trianglesNormal, i * 3 + 0, nx);
			pointerSetNumber(trianglesNormal, i * 3 + 1, ny);
			pointerSetNumber(trianglesNormal, i * 3 + 2, nz);

			let normalDrawLength = 0.04;

			nx *= normalDrawLength;
			ny *= normalDrawLength;
			nz *= normalDrawLength;

			let drawOffset = 0.02;

			var x0o = x0 - ((x0-x1)*drawOffset) - ((x0-x2)*drawOffset);
			var y0o = y0 - ((y0-y1)*drawOffset) - ((y0-y2)*drawOffset);
			var z0o = z0 - ((z0-z1)*drawOffset) - ((z0-z2)*drawOffset);

			var x1o = x1 - ((x1-x2)*drawOffset) - ((x1-x0)*drawOffset);
			var y1o = y1 - ((y1-y2)*drawOffset) - ((y1-y0)*drawOffset);
			var z1o = z1 - ((z1-z2)*drawOffset) - ((z1-z0)*drawOffset);

			var x2o = x2 - ((x2-x0)*drawOffset) - ((x2-x1)*drawOffset);
			var y2o = y2 - ((y2-y0)*drawOffset) - ((y2-y1)*drawOffset);
			var z2o = z2 - ((z2-z0)*drawOffset) - ((z2-z1)*drawOffset);

			drawLine("", x0o,y0o,z0o, nx+x0o,ny+y0o,nz+z0o, 2, 255,0,255,255);
			drawLine("", x1o,y1o,z1o, nx+x1o,ny+y1o,nz+z1o, 2, 0,255,0,255);
			drawLine("", x2o,y2o,z2o, nx+x2o,ny+y2o,nz+z2o, 2, 0,0,255,255);
		}
	}
}

{
	let v = meshGetVerticesPointer(suzanne);
	for (var i = 0; i < verticesComponentsCount / 9; i += 1) {
		let x0 = pointerGetNumber(v, i * 9 + 0);
		let y0 = pointerGetNumber(v, i * 9 + 1);
		let z0 = pointerGetNumber(v, i * 9 + 2);

		let x1 = pointerGetNumber(v, i * 9 + 3);
		let y1 = pointerGetNumber(v, i * 9 + 4);
		let z1 = pointerGetNumber(v, i * 9 + 5);

		let x2 = pointerGetNumber(v, i * 9 + 6);
		let y2 = pointerGetNumber(v, i * 9 + 7);
		let z2 = pointerGetNumber(v, i * 9 + 8);

		var nx = pointerGetNumber(trianglesNormal, i * 3 + 0);
		var ny = pointerGetNumber(trianglesNormal, i * 3 + 1);
		var nz = pointerGetNumber(trianglesNormal, i * 3 + 2);

		pointerSetNumber(verticesNormal, i * 9 + 0, nx);
		pointerSetNumber(verticesNormal, i * 9 + 1, ny);
		pointerSetNumber(verticesNormal, i * 9 + 2, nz);

		pointerSetNumber(verticesNormal, i * 9 + 3, nx);
		pointerSetNumber(verticesNormal, i * 9 + 4, ny);
		pointerSetNumber(verticesNormal, i * 9 + 5, nz);

		pointerSetNumber(verticesNormal, i * 9 + 6, nx);
		pointerSetNumber(verticesNormal, i * 9 + 7, ny);
		pointerSetNumber(verticesNormal, i * 9 + 8, nz);

		// https://blender.stackexchange.com/questions/187129/eevee-normal-pass-remap-negative-values/
		if (nx < 0) { nx *= -1; }
		if (ny < 0) { ny *= -1; }
		if (nz < 0) { nz *= -1; }

		//drawTriangle("", x0, y0, z0, x1, y1, z1, x2, y2, z2, nx*255,ny*255,nz*255,255);
	}
}

if (getCurrentFrame() == 0) {
	meshConvertToIndexMesh(suzanne);
}

let currentMode = globalArrayPersistentNew8Bit("currentRenderMode", 1 * 4);
if (mouseGetButtonIsPressed(2)) { // Change current render mode: right mouse button
	var v = pointerGetUnsignedInteger(currentMode, 0);
	v = v == 0 ? 1 : 0;
	pointerSetUnsignedInteger(currentMode, 0, v);
	if (v == 1) {
		setCurrentFrame(0);
	}
}
if (pointerGetUnsignedInteger(currentMode, 0) == 0) {
	// https://discord.gg/D7pKPw4kFf, https://discord.com/channels/908452801678561291/908452802165112885/918489067543466054
	if (windowIsFocused() && windowIsHovered()) {
		if (mouseGetMoveEvent() == 2) {
			defaultCameraDefaultControlEnable();
		}
	} else {
		defaultCameraDefaultControlDisable();
	}
} else {
	defaultCameraDefaultControlDisable();
}

if (isRerun() == true) {
	if (pointerIsNull(globalArrayPersistentGetPointer("devicep")) == false) {
		var handles = NumberArray();

		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("rendererp"), 0)); globalArrayPersistentDelete("rendererp");
		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("tonemapperp"), 0)); globalArrayPersistentDelete("tonemapperp");
		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("framebufferp"), 0)); globalArrayPersistentDelete("framebufferp");
		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("camerap"), 0)); globalArrayPersistentDelete("camerap");
		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("hdrimagep"), 0)); globalArrayPersistentDelete("hdrimagep");
		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("hdrilightp"), 0)); globalArrayPersistentDelete("hdrilightp");
		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("hdrilightprimp"), 0)); globalArrayPersistentDelete("hdrilightprimp");
		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("light0p"), 0)); globalArrayPersistentDelete("light0p");
		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("light1p"), 0)); globalArrayPersistentDelete("light1p");
		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("light0primp"), 0)); globalArrayPersistentDelete("light0primp");
		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("light1primp"), 0)); globalArrayPersistentDelete("light1primp");
		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("groundmaterialp"), 0)); globalArrayPersistentDelete("groundmaterialp");
		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("materialp"), 0)); globalArrayPersistentDelete("materialp");
		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("glassmaterialp"), 0)); globalArrayPersistentDelete("glassmaterialp");
		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("groundshapep"), 0)); globalArrayPersistentDelete("groundshapep");
		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("shapep"), 0)); globalArrayPersistentDelete("shapep");
		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("groundshapeprimp"), 0)); globalArrayPersistentDelete("groundshapeprimp");
		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("shape0primp"), 0)); globalArrayPersistentDelete("shape0primp");
		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("shape1primp"), 0)); globalArrayPersistentDelete("shape1primp");
		append(handles, pointerGetRaw64Bit(globalArrayPersistentGetPointer("scenep"), 0)); globalArrayPersistentDelete("scenep");

		let device = pointerGetRaw64Bit(globalArrayPersistentGetPointer("devicep"), 0); globalArrayPersistentDelete("devicep");

		if (pointerIsNull(device) == false) {
			for (var i = 0; i < len(handles); i += 1) {
				if (pointerIsNull(handles[i]) == false) {
					ertDecRef(device, handles[i]);
				}
			}
			ertDestroyDevice(device);
		}
	}
}
let devicep = globalArrayPersistentNew8Bit("devicep", 8);
var device = pointerGetRaw64Bit(devicep, 0);
if (pointerIsNull(device) == true) {
	device = ertCreateDevice("default", 0);
	pointerSetRaw64Bit(devicep, 0, device);
}
let rendererp = globalArrayPersistentNew8Bit("rendererp", 8);
var renderer = pointerGetRaw64Bit(rendererp, 0);
if (pointerIsNull(renderer) == true) {
	renderer = ertNewRenderer(device, "pathtracer");
	pointerSetRaw64Bit(rendererp, 0, renderer);
	ertSetInt1(device, renderer, "maxDepth", 20);
	ertSetInt1(device, renderer, "sampler.spp", 1);
	ertSetFloat1(device, renderer, "clampRadianceIfMoreThan", 10.0);
	ertSetFloat1(device, renderer, "clampRadianceTo", 5.0);
	ertCommit(device, renderer);
}
let tonemapperp = globalArrayPersistentNew8Bit("tonemapperp", 8);
var tonemapper = pointerGetRaw64Bit(tonemapperp, 0);
if (pointerIsNull(tonemapper) == true) {
	tonemapper = ertNewToneMapper(device, "default");
	pointerSetRaw64Bit(tonemapperp, 0, tonemapper);
	ertSetFloat1(device, tonemapper, "gamma", 1.0);
	ertCommit(device, tonemapper);
}
let framebufferp = globalArrayPersistentNew8Bit("framebufferp", 8);
var framebuffer = pointerGetRaw64Bit(framebufferp, 0);
if (pointerIsNull(framebuffer) == true) {
	framebuffer = ertNewFrameBuffer(device, "RGB_FLOAT32", 1800, 900, 1);
	pointerSetRaw64Bit(framebufferp, 0, framebuffer);
}
let camerap = globalArrayPersistentNew8Bit("camerap", 8);
var camera = pointerGetRaw64Bit(camerap, 0);
if (pointerIsNull(camera) == true) {
	camera = ertNewCamera(device, "depthoffield");
	pointerSetRaw64Bit(camerap, 0, camera);
}
let hdrimagep = globalArrayPersistentNew8Bit("hdrimagep", 8);
var hdrimage = pointerGetRaw64Bit(hdrimagep, 0);
if (pointerIsNull(hdrimage) == true) {
	hdrimage = ertNewImageFromFile(device, "data/lines.ppm");
	pointerSetRaw64Bit(hdrimagep, 0, hdrimage);
}
let hdrilightp = globalArrayPersistentNew8Bit("hdrilightp", 8);
var hdrilight = pointerGetRaw64Bit(hdrilightp, 0);
if (pointerIsNull(hdrilight) == true) {
	hdrilight = ertNewLight(device, "hdrilight");
	pointerSetRaw64Bit(hdrilightp, 0, hdrilight);
	ertSetImage(device, hdrilight, "image", hdrimage);
}
ertSetFloat3(device, hdrilight, "L", 0.005, 0.005, 0.005);
ertCommit(device, hdrilight);
let hdrilightprimp = globalArrayPersistentNew8Bit("hdrilightprimp", 8);
var hdrilightprim = pointerGetRaw64Bit(hdrilightprimp, 0);
if (pointerIsNull(hdrilightprim) == true) {
	hdrilightprim = ertNewLightPrimitive(device, hdrilight, pointerGetNull(), 0);
	pointerSetRaw64Bit(hdrilightprimp, 0, hdrilightprim);
}
let light0p = globalArrayPersistentNew8Bit("light0p", 8);
var light0 = pointerGetRaw64Bit(light0p, 0);
if (pointerIsNull(light0) == true) {
	light0 = ertNewLight(device, "trianglelight");
	pointerSetRaw64Bit(light0p, 0, light0);
}
let l00x =  1.0;
let l00y = -1.0;
let l00z =  1.5;
let l01x = -2.0;
let l01y =  5.0;
let l01z =  1.5;
let l02x = -5.0;
let l02y =  5.0;
let l02z =  1.5;
ertSetFloat3(device, light0, "v0", l00x, l00y, l00z);
ertSetFloat3(device, light0, "v1", l01x, l01y, l01z);
ertSetFloat3(device, light0, "v2", l02x, l02y, l02z);
ertSetFloat3(device, light0, "L", 2.0, 2.0, 0.8);
ertCommit(device, light0);
let light1p = globalArrayPersistentNew8Bit("light1p", 8);
var light1 = pointerGetRaw64Bit(light1p, 0);
if (pointerIsNull(light1) == true) {
	light1 = ertNewLight(device, "trianglelight");
	pointerSetRaw64Bit(light1p, 0, light1);
}
let l10x =  1.0;
let l10y = -1.0;
let l10z =  1.5;
let l11x = -5.0;
let l11y =  5.0;
let l11z =  1.5;
let l12x = -2.0;
let l12y = -1.0;
let l12z =  1.5;
ertSetFloat3(device, light1, "v0", l10x, l10y, l10z);
ertSetFloat3(device, light1, "v1", l11x, l11y, l11z);
ertSetFloat3(device, light1, "v2", l12x, l12y, l12z);
ertSetFloat3(device, light1, "L", 2.0, 2.0, 0.8);
ertCommit(device, light1);
let light0primp = globalArrayPersistentNew8Bit("light0primp", 8);
var light0prim = pointerGetRaw64Bit(light0primp, 0);
if (pointerIsNull(light0prim) == true) {
	light0prim = ertNewLightPrimitive(device, light0, pointerGetNull(), 0);
	pointerSetRaw64Bit(light0primp, 0, light0prim);
}
let light1primp = globalArrayPersistentNew8Bit("light1primp", 8);
var light1prim = pointerGetRaw64Bit(light1primp, 0);
if (pointerIsNull(light1prim) == true) {
	light1prim = ertNewLightPrimitive(device, light1, pointerGetNull(), 0);
	pointerSetRaw64Bit(light1primp, 0, light1prim);
}
let groundmaterialp = globalArrayPersistentNew8Bit("groundmaterialp", 8);
var groundmaterial = pointerGetRaw64Bit(groundmaterialp, 0);
if (pointerIsNull(groundmaterial) == true) {
	groundmaterial = ertNewMaterial(device, "Matte");
	pointerSetRaw64Bit(groundmaterialp, 0, groundmaterial);
	ertSetFloat3(device, groundmaterial, "reflectance", 1.0, 0.15, 0.15);
	ertCommit(device, groundmaterial);
}
let materialp = globalArrayPersistentNew8Bit("materialp", 8);
var material = pointerGetRaw64Bit(materialp, 0);
if (pointerIsNull(material) == true) {
	material = ertNewMaterial(device, "Matte");
	pointerSetRaw64Bit(materialp, 0, material);
	ertSetFloat3(device, material, "reflectance", 1.0, 1.0, 1.0);
	ertCommit(device, material);
}
let glassmaterialp = globalArrayPersistentNew8Bit("glassmaterialp", 8);
var glassmaterial = pointerGetRaw64Bit(glassmaterialp, 0);
if (pointerIsNull(glassmaterial) == true) {
	glassmaterial = ertNewMaterial(device, "Glass");
	pointerSetRaw64Bit(glassmaterialp, 0, glassmaterial);
}
ertSetFloat3(device, glassmaterial, "transmission", 1.0, 1.0, 1.0);
ertSetFloat1(device, glassmaterial, "etaOutside", 1.0);
ertSetFloat1(device, glassmaterial, "etaInside", 1.15);
ertCommit(device, glassmaterial);
let groundshapep = globalArrayPersistentNew8Bit("groundshapep", 8);
var groundshape = pointerGetRaw64Bit(groundshapep, 0);
if (pointerIsNull(groundshape) == true) {
	groundshape = ertNewShape(device, "trianglemesh");
	pointerSetRaw64Bit(groundshapep, 0, groundshape);
	let groundPositions = globalArrayNew8Bit("groundPositions", 4 * (3 * 4));
	let groundNormals = globalArrayNew8Bit("groundNormals", 4 * (3 * 4));
	let groundIndices = globalArrayNew8Bit("groundIndices", 6 * 4);
	pointerSetNumber(groundPositions, 0 * 3 + 0,-100.0);
	pointerSetNumber(groundPositions, 0 * 3 + 1,-1.0);
	pointerSetNumber(groundPositions, 0 * 3 + 2,-100.0);
	pointerSetNumber(groundPositions, 1 * 3 + 0, 100.0);
	pointerSetNumber(groundPositions, 1 * 3 + 1,-1.0);
	pointerSetNumber(groundPositions, 1 * 3 + 2,-100.0);
	pointerSetNumber(groundPositions, 2 * 3 + 0,-100.0);
	pointerSetNumber(groundPositions, 2 * 3 + 1,-1.0);
	pointerSetNumber(groundPositions, 2 * 3 + 2, 100.0);
	pointerSetNumber(groundPositions, 3 * 3 + 0, 100.0);
	pointerSetNumber(groundPositions, 3 * 3 + 1,-1.0);
	pointerSetNumber(groundPositions, 3 * 3 + 2, 100.0);
	pointerSetNumber(groundNormals, 0 * 3 + 0, 0.0);
	pointerSetNumber(groundNormals, 0 * 3 + 1, 1.0);
	pointerSetNumber(groundNormals, 0 * 3 + 2, 0.0);
	pointerSetNumber(groundNormals, 1 * 3 + 0, 0.0);
	pointerSetNumber(groundNormals, 1 * 3 + 1, 1.0);
	pointerSetNumber(groundNormals, 1 * 3 + 2, 0.0);
	pointerSetNumber(groundNormals, 2 * 3 + 0, 0.0);
	pointerSetNumber(groundNormals, 2 * 3 + 1, 1.0);
	pointerSetNumber(groundNormals, 2 * 3 + 2, 0.0);
	pointerSetNumber(groundNormals, 3 * 3 + 0, 0.0);
	pointerSetNumber(groundNormals, 3 * 3 + 1, 1.0);
	pointerSetNumber(groundNormals, 3 * 3 + 2, 0.0);
	pointerSetUnsignedInteger(groundIndices, 0, 0);
	pointerSetUnsignedInteger(groundIndices, 1, 1);
	pointerSetUnsignedInteger(groundIndices, 2, 2);
	pointerSetUnsignedInteger(groundIndices, 3, 1);
	pointerSetUnsignedInteger(groundIndices, 4, 3);
	pointerSetUnsignedInteger(groundIndices, 5, 2);
	let positions = ertNewData(device, "immutable_managed", 4 * (3 * 4), groundPositions, 0);
	let normals = ertNewData(device, "immutable_managed", 4 * (3 * 4), groundNormals, 0);
	let indices = ertNewData(device, "immutable_managed", 6 * 4, groundIndices, 0);
	ertSetArray(device, groundshape, "positions", "float3", positions, 4, 3 * 4, 0);
	ertSetArray(device, groundshape, "normals", "float3", normals, 4, 3 * 4, 0);
	ertSetArray(device, groundshape, "indices", "int3", indices, 6 / 3, 3 * 4, 0);
	ertCommit(device, groundshape);
	ertClear(device, groundshape);
}
let shapep = globalArrayPersistentNew8Bit("shapep", 8);
var shape = pointerGetRaw64Bit(shapep, 0);
if (pointerIsNull(shape) == true) {
	shape = ertNewShape(device, "trianglemesh");
	pointerSetRaw64Bit(shapep, 0, shape);
	let positions = ertNewData(device, "immutable_managed", meshGetVerticesCount(suzanne) * (3 * 4), meshGetVerticesPointer(suzanne), 0);
	let normals = ertNewData(device, "immutable_managed", meshGetVerticesCount(suzanne) * (3 * 4), verticesNormal, 0);
	let indices = ertNewData(device, "immutable_managed", meshGetIndicesCount(suzanne) * 4, meshGetIndicesPointer(suzanne), 0);
	ertSetArray(device, shape, "positions", "float3", positions, meshGetVerticesCount(suzanne), 3 * 4, 0);
	ertSetArray(device, shape, "normals", "float3", normals, meshGetVerticesCount(suzanne), 3 * 4, 0);
	ertSetArray(device, shape, "indices", "int3", indices, meshGetIndicesCount(suzanne) / 3, 3 * 4, 0);
	ertCommit(device, shape);
	ertClear(device, shape);
}
let groundshapeprimp = globalArrayPersistentNew8Bit("groundshapeprimp", 8);
var groundshapeprim = pointerGetRaw64Bit(groundshapeprimp, 0);
if (pointerIsNull(groundshapeprim) == true) {
	groundshapeprim = ertNewShapePrimitive(device, groundshape, groundmaterial, pointerGetNull(), 0);
	pointerSetRaw64Bit(groundshapeprimp, 0, groundshapeprim);
}
let shape0primp = globalArrayPersistentNew8Bit("shape0primp", 8);
var shape0prim = pointerGetRaw64Bit(shape0primp, 0);
if (pointerIsNull(shape0prim) == true) {
	shape0prim = ertNewShapePrimitive(device, shape, material, pointerGetNull(), 0);
	pointerSetRaw64Bit(shape0primp, 0, shape0prim);
}
let shape1primp = globalArrayPersistentNew8Bit("shape1primp", 8);
var shape1prim = pointerGetRaw64Bit(shape1primp, 0);
if (pointerIsNull(shape1prim) == true) {
	let shape1Matrix = globalArrayNew8Bit("shape1Matrix", ertAffineSpace3fGetSizeOfInBytes());
	ertAffineSpace3fSetDefaultInitialize(shape1Matrix, 0);
	ertAffineSpace3fTranslate(shape1Matrix, 0, -3, 0, 0);
	let shape1MatrixArray = globalArrayNew8Bit("shape1MatrixArray", 12 * 4);
	ertAffineSpace3fCopyToArray(shape1Matrix, 0, shape1MatrixArray, 0);
	shape1prim = ertNewShapePrimitive(device, shape, glassmaterial, shape1MatrixArray, 0);
	pointerSetRaw64Bit(shape1primp, 0, shape1prim);
}
let primitivesCount = 6.0;
let primitives = globalArrayNew8Bit("primitives", primitivesCount * 8);
pointerSetRaw64Bit(primitives, 0 * 8, groundshapeprim);
pointerSetRaw64Bit(primitives, 1 * 8, shape0prim);
pointerSetRaw64Bit(primitives, 2 * 8, shape1prim);
pointerSetRaw64Bit(primitives, 3 * 8, hdrilightprim);
pointerSetRaw64Bit(primitives, 4 * 8, light0prim);
pointerSetRaw64Bit(primitives, 5 * 8, light1prim);
let scenep = globalArrayPersistentNew8Bit("scenep", 8);
var scene = pointerGetRaw64Bit(scenep, 0);
if (pointerIsNull(scene) == true) {
	scene = ertNewScene(device, "default default", primitives, 0, primitivesCount);
	pointerSetRaw64Bit(scenep, 0, scene);
}
let cameraMatrix = globalArrayNew8Bit("cameraMatrix", ertAffineSpace3fGetSizeOfInBytes());
var p = defaultCameraGetVector();
var t = defaultCameraGetLookAtVector();
var u = defaultCameraGetUpVector();
ertAffineSpace3fSetLookAtPoint(cameraMatrix, 0, p[0], p[1], p[2], p[0]+t[0], p[1]+t[1], p[2]+t[2], -u[0], -u[1], -u[2]); // NOTE(Constantine): Intentionally inverted up vector to GL draw upside down.
let cameraMatrixArray = globalArrayNew8Bit("cameraMatrixArray", 12 * 4);
ertAffineSpace3fCopyToArray(cameraMatrix, 0, cameraMatrixArray, 0);
ertSetTransform(device, camera, "local2world", cameraMatrixArray, 0);
ertSetFloat1(device, camera, "angle", 60);
ertSetFloat1(device, camera, "aspectRatio", 1800.0 / 900.0);
ertSetFloat1(device, camera, "focalDistance", 10);
ertSetFloat1(device, camera, "lensRadius", 0.001);
ertCommit(device, camera);

meshDraw(suzanne, 0, 1,1,1, 0,0,0, 0,0,0,0);
meshDraw(suzanne, 0, 1,1,1,-3,0,0, 0,0,0,0);
{
	let groundPositions = globalArrayGetPointer("groundPositions");
	drawTriangle("",
		pointerGetNumber(groundPositions, 0 * 3 + 0),
		pointerGetNumber(groundPositions, 0 * 3 + 1),
		pointerGetNumber(groundPositions, 0 * 3 + 2),
		pointerGetNumber(groundPositions, 1 * 3 + 0),
		pointerGetNumber(groundPositions, 1 * 3 + 1),
		pointerGetNumber(groundPositions, 1 * 3 + 2),
		pointerGetNumber(groundPositions, 2 * 3 + 0),
		pointerGetNumber(groundPositions, 2 * 3 + 1),
		pointerGetNumber(groundPositions, 2 * 3 + 2),
		255, 255 * 0.15, 255 * 0.15, 255
	);
	drawTriangle("",
		pointerGetNumber(groundPositions, 1 * 3 + 0),
		pointerGetNumber(groundPositions, 1 * 3 + 1),
		pointerGetNumber(groundPositions, 1 * 3 + 2),
		pointerGetNumber(groundPositions, 3 * 3 + 0),
		pointerGetNumber(groundPositions, 3 * 3 + 1),
		pointerGetNumber(groundPositions, 3 * 3 + 2),
		pointerGetNumber(groundPositions, 2 * 3 + 0),
		pointerGetNumber(groundPositions, 2 * 3 + 1),
		pointerGetNumber(groundPositions, 2 * 3 + 2),
		255, 255 * 0.15, 255 * 0.15, 255
	);
	drawTriangle("",
		pointerGetNumber(groundPositions, 0 * 3 + 0),
		pointerGetNumber(groundPositions, 0 * 3 + 1),
		pointerGetNumber(groundPositions, 0 * 3 + 2),
		pointerGetNumber(groundPositions, 1 * 3 + 0),
		pointerGetNumber(groundPositions, 1 * 3 + 1),
		pointerGetNumber(groundPositions, 1 * 3 + 2),
		pointerGetNumber(groundPositions, 2 * 3 + 0),
		pointerGetNumber(groundPositions, 2 * 3 + 1),
		pointerGetNumber(groundPositions, 2 * 3 + 2),
		255, 255 * 0.15, 255 * 0.15, 255
	);
	drawTriangle("", l00x, l00y, l00z, l01x, l01y, l01z, l02x, l02y, l02z, 255, 255, 255 * 0.8, 255);
	drawTriangle("", l10x, l10y, l10z, l11x, l11y, l11z, l12x, l12y, l12z, 255, 255, 255 * 0.8, 255);
}

if (pointerGetUnsignedInteger(currentMode, 0) == 1) {
	ertRenderFrame(device, renderer, camera, scene, tonemapper, framebuffer, getCurrentFrame());
	ertSwapBuffers(device, framebuffer);
	let fbp = ertMapFrameBuffer(device, framebuffer);
	pointerDrawPixels(fbp, 0, 1800, 900, 6408, 5126); // GL_RGBA, GL_FLOAT
	ertUnmapFrameBuffer(device, framebuffer);
}
```
```
fn NumberArray() {
        return [];
}

fn smoothMeshNormals(meshHandle, verticesNormalArrayHandle) { // Number, Number
    let vertices = meshGetVerticesPointer(meshHandle);
    let verticesCount = meshGetVerticesCount(meshHandle);
    let repeatIdsLabel = "smoothMeshNormalsRepeatIDs" + numberToString(getRandomNumber());
    let repeatIds = globalArrayNew8Bit(repeatIdsLabel, verticesCount * 4);
    var index = 1;
    for (var j = 0; j < verticesCount; j += 1) {
        let id = pointerGetUnsignedInteger(repeatIds, j);
        if (id > 0) {
            continue;
        }
        let findX = pointerGetNumber(vertices, j * 3 + 0);
        let findY = pointerGetNumber(vertices, j * 3 + 1);
        let findZ = pointerGetNumber(vertices, j * 3 + 2);
        var averageNormalsVertexIndices = NumberArray();
        for (var i = 0; i < verticesCount; i += 1) {
            if (i == j) {
                append(averageNormalsVertexIndices, i);
                continue;
            }
            let x = pointerGetNumber(vertices, i * 3 + 0);
            if (x == findX) {
                let y = pointerGetNumber(vertices, i * 3 + 1);
                if (y == findY) {
                    let z = pointerGetNumber(vertices, i * 3 + 2);
                    if (z == findZ) {
                        append(averageNormalsVertexIndices, i);
                        continue;
                    }
                }
            }
        }
        {
            let averageNormalsVertexIndicesCount = len(averageNormalsVertexIndices);
            var averagedNormalX = 0.0;
            var averagedNormalY = 0.0;
            var averagedNormalZ = 0.0;
            for (var i = 0; i < averageNormalsVertexIndicesCount; i += 1) {
                averagedNormalX += pointerGetNumber(verticesNormalArrayHandle, averageNormalsVertexIndices[i] * 3 + 0);
                averagedNormalY += pointerGetNumber(verticesNormalArrayHandle, averageNormalsVertexIndices[i] * 3 + 1);
                averagedNormalZ += pointerGetNumber(verticesNormalArrayHandle, averageNormalsVertexIndices[i] * 3 + 2);
            }
            averagedNormalX /= averageNormalsVertexIndicesCount;
            averagedNormalY /= averageNormalsVertexIndicesCount;
            averagedNormalZ /= averageNormalsVertexIndicesCount;
            for (var i = 0; i < averageNormalsVertexIndicesCount; i += 1) {
                pointerSetNumber(verticesNormalArrayHandle, averageNormalsVertexIndices[i] * 3 + 0, averagedNormalX);
                pointerSetNumber(verticesNormalArrayHandle, averageNormalsVertexIndices[i] * 3 + 1, averagedNormalY);
                pointerSetNumber(verticesNormalArrayHandle, averageNormalsVertexIndices[i] * 3 + 2, averagedNormalZ);
            }
            for (var i = 0; i < averageNormalsVertexIndicesCount; i += 1) {
                pointerSetNumber(repeatIds, averageNormalsVertexIndices[i], index);
            }
        }
        index += 1;
    }
    globalArrayDelete(repeatIdsLabel);
}

defaultCameraSetMoveSpeed(0.025);

//setCurrentFrame(0);

let suzanne = meshNew("suzanne");
let verticesString = stringReadFromFile("/home/constantine/Documents/suzanne.txt");
var verticesComponentsCount = (strlenWithNullChar(verticesString)-1) / 10;

let trianglesNormal = globalArrayPersistentNew8Bit("trianglesNormal", (verticesComponentsCount / 9) * 3 * 4);
let verticesNormal = globalArrayPersistentNew8Bit("verticesNormal", verticesComponentsCount * 4);

if (getCurrentFrame() == 0) {
    //verticesComponentsCount = 3 * 9; // Debug N triangles
    //printDraw(numberToString(verticesCount));
    let stringNumber = globalArrayNew8Bit("stringNumber", 11);
    var vertex = NumberArray();
    append(vertex, 0);
    append(vertex, 0);
    append(vertex, 0);
    for (var i = 0; i < verticesComponentsCount; i += 1) {
        pointerSetSubstring(stringNumber, 0, verticesString, i*10, 10);
        vertex[i % 3] = interpretStringToFloat(pointerGetString(stringNumber));
        if (i % 3 == 2) {
            meshAddVertex(suzanne, vertex[0], vertex[1], vertex[2]);
            //meshAddColor(suzanne, i / verticesComponentsCount, 0, 0, 1);
        }
    }
    // Generate array of triangle per-vertex normals
    {
        let v = meshGetVerticesPointer(suzanne);
        for (var i = 0; i < verticesComponentsCount / 9; i += 1) {
            let x0 = pointerGetNumber(v, i * 9 + 0);
            let y0 = pointerGetNumber(v, i * 9 + 1);
            let z0 = pointerGetNumber(v, i * 9 + 2);

            let x1 = pointerGetNumber(v, i * 9 + 3);
            let y1 = pointerGetNumber(v, i * 9 + 4);
            let z1 = pointerGetNumber(v, i * 9 + 5);

            let x2 = pointerGetNumber(v, i * 9 + 6);
            let y2 = pointerGetNumber(v, i * 9 + 7);
            let z2 = pointerGetNumber(v, i * 9 + 8);

            let pointSize = 0.5;

            drawPoint("", x0, y0, z0, pointSize, 255,0,255,255);
            drawPoint("", x1, y1, z1, pointSize, 0,255,0,255);
            drawPoint("", x2, y2, z2, pointSize, 0,0,255,255);

            // 0 --- 1
            //   \ /
            //    2
            //
            // d10 = 1 - 0
            // d20 = 2 - 0
            // normal = d10 cross d20

            let d10x = x1 - x0;
            let d10y = y1 - y0;
            let d10z = z1 - z0;

            let d20x = x2 - x0;
            let d20y = y2 - y0;
            let d20z = z2 - z0;

            var nx = d20y*d10z - d10y*d20z;
            var ny = d20z*d10x - d10z*d20x;
            var nz = d20x*d10y - d10x*d20y;

            let l = sqrt(nx*nx + ny*ny + nz*nz);

            nx /= l;
            ny /= l;
            nz /= l;

            pointerSetNumber(trianglesNormal, i * 3 + 0, nx);
            pointerSetNumber(trianglesNormal, i * 3 + 1, ny);
            pointerSetNumber(trianglesNormal, i * 3 + 2, nz);

            let normalDrawLength = 0.04;

            nx *= normalDrawLength;
            ny *= normalDrawLength;
            nz *= normalDrawLength;

            let drawOffset = 0.02;

            var x0o = x0 - ((x0-x1)*drawOffset) - ((x0-x2)*drawOffset);
            var y0o = y0 - ((y0-y1)*drawOffset) - ((y0-y2)*drawOffset);
            var z0o = z0 - ((z0-z1)*drawOffset) - ((z0-z2)*drawOffset);

            var x1o = x1 - ((x1-x2)*drawOffset) - ((x1-x0)*drawOffset);
            var y1o = y1 - ((y1-y2)*drawOffset) - ((y1-y0)*drawOffset);
            var z1o = z1 - ((z1-z2)*drawOffset) - ((z1-z0)*drawOffset);

            var x2o = x2 - ((x2-x0)*drawOffset) - ((x2-x1)*drawOffset);
            var y2o = y2 - ((y2-y0)*drawOffset) - ((y2-y1)*drawOffset);
            var z2o = z2 - ((z2-z0)*drawOffset) - ((z2-z1)*drawOffset);

            drawLine("", x0o,y0o,z0o, nx+x0o,ny+y0o,nz+z0o, 2, 255,0,255,255);
            drawLine("", x1o,y1o,z1o, nx+x1o,ny+y1o,nz+z1o, 2, 0,255,0,255);
            drawLine("", x2o,y2o,z2o, nx+x2o,ny+y2o,nz+z2o, 2, 0,0,255,255);
        }
    }
}

{
    let v = meshGetVerticesPointer(suzanne);
    for (var i = 0; i < verticesComponentsCount / 9; i += 1) {
        let x0 = pointerGetNumber(v, i * 9 + 0);
        let y0 = pointerGetNumber(v, i * 9 + 1);
        let z0 = pointerGetNumber(v, i * 9 + 2);

        let x1 = pointerGetNumber(v, i * 9 + 3);
        let y1 = pointerGetNumber(v, i * 9 + 4);
        let z1 = pointerGetNumber(v, i * 9 + 5);

        let x2 = pointerGetNumber(v, i * 9 + 6);
        let y2 = pointerGetNumber(v, i * 9 + 7);
        let z2 = pointerGetNumber(v, i * 9 + 8);

        var nx = pointerGetNumber(trianglesNormal, i * 3 + 0);
        var ny = pointerGetNumber(trianglesNormal, i * 3 + 1);
        var nz = pointerGetNumber(trianglesNormal, i * 3 + 2);

        pointerSetNumber(verticesNormal, i * 9 + 0, nx);
        pointerSetNumber(verticesNormal, i * 9 + 1, ny);
        pointerSetNumber(verticesNormal, i * 9 + 2, nz);

        pointerSetNumber(verticesNormal, i * 9 + 3, nx);
        pointerSetNumber(verticesNormal, i * 9 + 4, ny);
        pointerSetNumber(verticesNormal, i * 9 + 5, nz);

        pointerSetNumber(verticesNormal, i * 9 + 6, nx);
        pointerSetNumber(verticesNormal, i * 9 + 7, ny);
        pointerSetNumber(verticesNormal, i * 9 + 8, nz);

        // https://blender.stackexchange.com/questions/187129/eevee-normal-pass-remap-negative-values/
        if (nx < 0) { nx *= -1; }
        if (ny < 0) { ny *= -1; }
        if (nz < 0) { nz *= -1; }

        //drawTriangle("", x0, y0, z0, x1, y1, z1, x2, y2, z2, nx*255,ny*255,nz*255,255);
    }
}

if (getCurrentFrame() == 0) {
        smoothMeshNormals(suzanne, verticesNormal);
}

if (getCurrentFrame() == 0) {
	for (var i = 0; i < meshGetVerticesCount(suzanne); i += 1) {
		var r = pointerGetNumber(verticesNormal, i * 3 + 0);
		var g = pointerGetNumber(verticesNormal, i * 3 + 1);
		var b = pointerGetNumber(verticesNormal, i * 3 + 2);
		// https://blender.stackexchange.com/questions/187129/eevee-normal-pass-remap-negative-values/
		if (r < 0) { r *= -1; }
		if (g < 0) { g *= -1; }
		if (b < 0) { b *= -1; }
		meshAddColor(suzanne, r, g, b, 1);
	}
}

meshDraw(suzanne, 0, 1,1,1, 0,0,0, 0,0,0,0);
```
```
var v = defaultCameraGetVector();

printDraw(numberToString(v[0]) + " " + numberToString(v[1]) + " " + numberToString(v[2]));

drawTriangle("tri", 0,0,0, 1,0,0, 0,1,0, 255,0,0,255);
```
#endif

// NOTES(Constantine):
// * Gizmos and Mesh Importers are persistent.
// * The Ape programming language Game Script uses uses double precision numbers for the Number type, which limits byte ranges and other whole numbers to the max value of MAX_SAFE_INTEGER that is equal to 9007199254740991.
// * When using --set-directory-path command line flag, make sure to end the path to a directory with / character.
// * C++'s auto keyword sometimes incorrectly assigns an integer type to a variable in expressions like var x = 0;, so if you need a double, prefer to explicitly set the variables to doubles, like this: var x = 0.0;.
// * Default background color is 200, 200, 200, 255
// * Default camera perspective and position:
//     defaultCameraSetupPerspective(false, 60, 0.005, 10000, 0, 0);
//     defaultCameraSetVector(0, 0, 10);

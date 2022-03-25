#if defined(_WIN32)
#define LZ4X_C // Include C implementation
#define ULZ_C  // Include C implementation
#endif
#include "gamescript.h"

#ifndef GS_API
#define GS_API
#endif

GSN_WIN_IMPORT float                                                    gImguiFontGlobalScale;
GSN_WIN_IMPORT int                                                      gReadScriptFromDataGameDotScript;
GSN_WIN_IMPORT int                                                      gDisableDefaultFkeys;
GSN_WIN_IMPORT int                                                      gFullscreenExclusive;
GSN_WIN_IMPORT int                                                      gFullscreenF11Override;
GSN_WIN_IMPORT int                                                      gFullscreenF11OverrideOnce;
GSN_WIN_IMPORT int                                                      gFullscreen;
GSN_WIN_IMPORT int                                                      gF1WindowIsShownFromNowOn;
GSN_WIN_IMPORT volatile uint64_t                                        gStopScript;
GSN_WIN_IMPORT int                                                      gRunScriptOnce;
GSN_WIN_IMPORT int                                                      gRerun;
GSN_WIN_IMPORT volatile uint64_t                                        gCurrentFrame;
GSN_WIN_IMPORT volatile uint64_t                                        gCurrentFrameThread2;
GSN_WIN_IMPORT RedFHandleImgui *                                        gGuiImgui;
GSN_WIN_IMPORT int                                                      gPreviousGameMode;
GSN_WIN_IMPORT int                                                      gGameMode;
GSN_WIN_IMPORT int                                                      gPreviousDefaultCameraEnabled;
GSN_WIN_IMPORT int                                                      gDefaultCameraEnabled;
GSN_WIN_IMPORT int                                                      gDefaultCameraForceEnabled;
GSN_WIN_IMPORT RedFHandleFirstPersonCamera *                            gCamera;
GSN_WIN_IMPORT ape_t *                                                  gApe;
GSN_WIN_IMPORT ape_t *                                                  gApeThread2;
GSN_WIN_IMPORT char *                                                   gApeCodeCharsCurrentlyRunning;
GSN_WIN_IMPORT char *                                                   gApeCodeCharsCurrentlyRunningThread2;
GSN_WIN_IMPORT int                                                      gApeErrorCheck;
GSN_WIN_IMPORT int                                                      gApeErrorCheckThread2;
GSN_WIN_IMPORT int                                                      gF2Toggle;
GSN_WIN_IMPORT int                                                      gGameScriptNativeRecompileSignal;
GSN_WIN_IMPORT int                                                      gGameScriptNativeRecompileSignalThread2;
GSN_WIN_IMPORT std::string                                              gApeCodeCharsNextRunning;
GSN_WIN_IMPORT std::string                                              gApeCodeCharsNextRunningThread2;
GSN_WIN_IMPORT std::string                                              gApeCodeChars;
GSN_WIN_IMPORT std::string                                              gApeMemoryViewerGlobalArrayNameChars;
GSN_WIN_IMPORT std::string                                              gApeMemoryViewerInterpretBytesChars;
GSN_WIN_IMPORT std::string                                              gApeErrors;
GSN_WIN_IMPORT std::vector<ApeDrawLabelDebugText>                       gApeDrawLabelStackDebugTexts;
GSN_WIN_IMPORT std::vector<ApeDrawLabelPoint>                           gApeDrawLabelStackPoints;
GSN_WIN_IMPORT std::vector<ApeDrawLabelLine>                            gApeDrawLabelStackLines;
GSN_WIN_IMPORT std::vector<ApeDrawLabelTriangle>                        gApeDrawLabelStackTriangles;
GSN_WIN_IMPORT std::vector<ApeDrawLabelMesh>                            gApeDrawLabelStackMeshes;
GSN_WIN_IMPORT std::vector<ApeDrawFbo>                                  gApeDrawFbos;
GSN_WIN_IMPORT std::vector<ApeDrawImage>                                gApeDrawImages;
GSN_WIN_IMPORT std::vector<ApeDrawImageSubsection>                      gApeDrawImagesSubsections;
GSN_WIN_IMPORT void *                                                   gExternalLibraryHandle;
GSN_WIN_IMPORT void                                                   (*gExternalLibraryProcedureCall2)(double, double);
GSN_WIN_IMPORT void                                                   (*gExternalLibraryProcedureCall3)(double, double, double);
GSN_WIN_IMPORT std::vector<std::string>                                 gProgramArguments;
GSN_WIN_IMPORT char *                                                   gCurrentExeDir;
GSN_WIN_IMPORT char *                                                   gClipboard;
GSN_WIN_IMPORT std::unordered_map<int/*keycode*/, int/*event*/>         gGlfwKeyEvent;
GSN_WIN_IMPORT std::unordered_map<int/*keycode*/, int/*mdofiers*/>      gGlfwKeyModifiers;
GSN_WIN_IMPORT unsigned                                                 gGlfwCodepointCharacter;
GSN_WIN_IMPORT std::unordered_map<std::string, uint64_t>                gApeGlobalArrayBytesCount;
GSN_WIN_IMPORT std::unordered_map<std::string, void *>                  gApeGlobalArrayPointer;
GSN_WIN_IMPORT std::unordered_map<std::string, uint64_t>                gApeGlobalArrayPersistentBytesCount;
GSN_WIN_IMPORT std::unordered_map<std::string, void *>                  gApeGlobalArrayPersistentPointer;
GSN_WIN_IMPORT std::unordered_map<std::string, uint64_t>                gApeGlobalSharedArrayPersistentBytesCount;
GSN_WIN_IMPORT std::unordered_map<std::string, void *>                  gApeGlobalSharedArrayPersistentPointer;
GSN_WIN_IMPORT std::unordered_map<std::string, std::vector<double> *>   gApeGlobalDynamicArray;
GSN_WIN_IMPORT std::unordered_map<std::string, std::vector<double> *>   gApeGlobalDynamicArrayPersistent;
GSN_WIN_IMPORT unsigned                                                 gMouseEvent;
GSN_WIN_IMPORT int                                                      gMouseButtonIsPressed[8];
GSN_WIN_IMPORT int                                                      gMouseButtonIsReleased[8];
GSN_WIN_IMPORT float                                                    gMouseWheelScroll;
GSN_WIN_IMPORT std::unordered_map<std::string, RedFHandleManipulator *> gApeGizmos;
GSN_WIN_IMPORT std::unordered_map<std::string, RedFHandleFbo *>         gApeFbos;
GSN_WIN_IMPORT std::map<std::string, RedFHandleMesh *>                  gApeMeshes;
GSN_WIN_IMPORT std::map<std::string, RedFHandleMesh *>                  gApeMeshesPersistent;
GSN_WIN_IMPORT std::unordered_map<std::string, RedFHandleAssimp *>      gApeAssimpPersistent;
GSN_WIN_IMPORT std::unordered_map<std::string, RedFHandleImage *>       gApeImages;
GSN_WIN_IMPORT std::unordered_map<std::string, RedFHandleImage *>       gApeImagesPersistent;
GSN_WIN_IMPORT std::unordered_map<std::string, RedFHandleShader *>      gApeShaders;
GSN_WIN_IMPORT std::unordered_map<std::string, RedFHandleSoundPlayer *> gApeSoundPlayers;
GSN_WIN_IMPORT std::unordered_map<std::string, RedFHandleSoundPlayer *> gApeSoundPlayersPersistent;
GSN_WIN_IMPORT std::unordered_map<std::string, RedFHandleFbx *>         gApeFbxs;
GSN_WIN_IMPORT std::map<std::string, std::map<std::string, GlobalKeyPropery> > gKeyProperties;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallErtDecRef;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallErtDestroyDevice;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedCpuSignalWait;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedMemoryFree;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedStructsMemoryFree;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyContext;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyArray;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyImage;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroySampler;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyTexture;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyGpuCode;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyOutputDeclaration;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyStructDeclaration;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyProcedureParameters;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyProcedureCache;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyProcedure;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyOutput;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyCpuSignal;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyGpuSignal;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyGpuToCpuSignal;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyCalls;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRedDestroyArrayTimestamp;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRrtDestroyContext;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRrtReleaseCommandStream;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRrtReleaseEvent;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRrtWaitEvent;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRrtReleaseDevicePtr;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRrtReleaseExternalCommandStream;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallRrtUnmapDevicePtr;
GSN_WIN_IMPORT std::vector<GlobalArrayPersistentOnRerunCallStorage>     gGlobalArrayPersistentOnRerunCallXatlasDestroy;
GSN_WIN_IMPORT std::string                                              gF1CommandOptions;
GSN_WIN_IMPORT std::string                                              gThreadF1OutputText;
GSN_WIN_IMPORT RedFHandleThread *                                       gThreadF1;
GSN_WIN_IMPORT RedFHandleThread *                                       gThread2;
GSN_WIN_IMPORT volatile uint64_t                                        gThread2StopSignal;
GSN_WIN_IMPORT volatile uint64_t                                        gUniqueNumber;
GSN_WIN_IMPORT int                                                      gEmbreeIsEnabled;
GSN_WIN_IMPORT int                                                      gRedGpuIsEnabled;
GSN_WIN_IMPORT int                                                      gXatlasIsEnabled;
GSN_WIN_IMPORT int                                                      gFbxIsEnabled;
GSN_WIN_IMPORT std::mutex                                               __GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_thread2PrintGuardAndSerializeMutex;
GSN_WIN_IMPORT std::mutex                                               __GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_thread2GlobalSharedArrayPersistentGuardAndSerializeMutex;
GSN_WIN_IMPORT std::mutex                                               __GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_thread2ThreadSafeMemoryGuardAndSerializeMutex;
GSN_WIN_IMPORT std::mutex                                               __GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex;
GSN_WIN_IMPORT std::mutex                                               __GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_fbxsMutex;
GSN_WIN_IMPORT std::mutex                                               __GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_threadF1OutputTextMutex;
GSN_WIN_IMPORT volatile uint64_t                                        gDragAndDropCounter;
GSN_WIN_IMPORT float                                                    gDragAndDropPositionX;
GSN_WIN_IMPORT float                                                    gDragAndDropPositionY;
GSN_WIN_IMPORT std::vector<std::string>                                 gDragAndDropFilepaths;
#if defined(GAME_SCRIPT_NATIVE)
GSN_WIN_IMPORT void *                                                   libgame;
GSN_WIN_IMPORT void *                                                   libthread2;
#endif

typedef enum GsStructMemberType {
  GS_STRUCT_MEMBER_TYPE_INVALID      = 0,
  GS_STRUCT_MEMBER_TYPE_STRUCT       = 1,
  GS_STRUCT_MEMBER_TYPE_VOID_POINTER = 2,
  GS_STRUCT_MEMBER_TYPE_CHAR_POINTER = 3,
  GS_STRUCT_MEMBER_TYPE_UCHAR        = 4,
  GS_STRUCT_MEMBER_TYPE_CHAR         = 5,
  GS_STRUCT_MEMBER_TYPE_BOOL         = 6,
  GS_STRUCT_MEMBER_TYPE_U32          = 7,
  GS_STRUCT_MEMBER_TYPE_I32          = 8,
  GS_STRUCT_MEMBER_TYPE_F32          = 9,
  GS_STRUCT_MEMBER_TYPE_SIZE_T       = 10,
  GS_STRUCT_MEMBER_TYPE_U64          = 11,
} GsStructMemberType;

// Internal procedures

static inline double _gsPointerToNumber(void * voidpointer) {
  GsInternalUnionConverter c;
  c.voidpointer = voidpointer;
  return c.number;
}

static inline void * _gsNumberToPointer(double number) {
  GsInternalUnionConverter c;
  c.number = number;
  return c.voidpointer;
}

static void _gsDrawPoint(std::string label, float x, float y, float z, float size, int r, int g, int b, int a) {
  if (size != 0) {
    redFSetColor(r, g, b, a);
    redFDrawPoint(x, y, z, size * 0.01f, redFFirstPersonCameraCastToCamera(gCamera[0]));
  }
  if (label != "") {
    ApeDrawLabelPoint draw;
    draw.x     = x;
    draw.y     = y;
    draw.z     = z;
    draw.label = label;
    gApeDrawLabelStackPoints.push_back(draw);
  }
}

static void _gsDrawLine(std::string label, float x0, float y0, float z0, float x1, float y1, float z1, float width, int r, int g, int b, int a) {
  redFSetColor(r, g, b, a);
  redFSetLineWidth(width);
  redFDrawLine(x0, y0, z0, x1, y1, z1);
  if (label != "") {
    ApeDrawLabelLine draw;
    draw.x0    = x0;
    draw.y0    = y0;
    draw.z0    = z0;
    draw.x1    = x1;
    draw.y1    = y1;
    draw.z1    = z1;
    draw.label = label;
    gApeDrawLabelStackLines.push_back(draw);
  }
}

static void _gsDrawTriangle(std::string label, int isWireframe, float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, int r, int g, int b, int a) {
  redFSetColor(r, g, b, a);
  if (isWireframe == 1) {
    redFNoFill();
    redFSetLineWidth(2);
  }
  redFDrawTriangle(x0, y0, z0, x1, y1, z1, x2, y2, z2);
  if (isWireframe == 1) {
    redFFill();
  }
  if (label != "") {
    ApeDrawLabelTriangle draw;
    draw.x0    = x0;
    draw.y0    = y0;
    draw.z0    = z0;
    draw.x1    = x1;
    draw.y1    = y1;
    draw.z1    = z1;
    draw.x2    = x2;
    draw.y2    = y2;
    draw.z2    = z2;
    draw.label = label;
    gApeDrawLabelStackTriangles.push_back(draw);
  }
}

static void _gsImageGammaCorrect(RedFHandleImage handle) {
  for (int y = 0, xcount = redFImageGetWidth(handle), ycount = redFImageGetHeight(handle); y < ycount; y += 1) {
    for (int x = 0; x < xcount; x += 1) {
      unsigned char color[4];
      redFImageGetColor(handle, x, y, &color[0], &color[1], &color[2], &color[3]);
      float r = (float)color[0] / 255.f;
      float g = (float)color[1] / 255.f;
      float b = (float)color[2] / 255.f;
      r *= r;
      g *= g;
      b *= b;
      redFImageSetColor(handle, x, y,
        (unsigned char)(r * 255.f),
        (unsigned char)(g * 255.f),
        (unsigned char)(b * 255.f),
        color[3]
      );
    }
  }
}

static void _gsImageClear(RedFHandleImage handle, int alphaValue0to255) {
  for (int y = 0, xcount = redFImageGetWidth(handle), ycount = redFImageGetHeight(handle); y < ycount; y += 1) {
    for (int x = 0; x < xcount; x += 1) {
      redFImageSetColor(handle, x, y, 0, 0, 0, alphaValue0to255);
    }
  }
  redFImageUpdate(handle);
}

// External procedures

#if defined(GAME_SCRIPT_MIN)
#define GS_C_PROCEDURE_RETURN_TYPE() MinScriptLang::Value
#define GS_C_PROCEDURE_PARAMETERS() (MinScriptLang::Environment & env, const MinScriptLang::PlaceInCode & place, std::vector<MinScriptLang::Value> && args)
#define getArgAs_BEGIN(PROCEDURE_NAME) MINSL_LOAD_ARG_BEGIN(PROCEDURE_NAME);
#define getArgAs_Bool(VARIABLE_TYPE, VARIABLE_NAME, ARG)    MINSL_LOAD_ARG_NUMBER(_gs_##VARIABLE_NAME); VARIABLE_TYPE VARIABLE_NAME = (VARIABLE_TYPE)(_gs_##VARIABLE_NAME == 0.0 ? false : true); _i += 1
#define getArgAs_Double(VARIABLE_TYPE, VARIABLE_NAME, ARG)  MINSL_LOAD_ARG_NUMBER(_gs_##VARIABLE_NAME); VARIABLE_TYPE VARIABLE_NAME = (VARIABLE_TYPE)_gs_##VARIABLE_NAME; _i += 1
#define getArgAs_Pointer(VARIABLE_TYPE, VARIABLE_NAME, ARG) MINSL_LOAD_ARG_NUMBER(_gs_##VARIABLE_NAME); VARIABLE_TYPE VARIABLE_NAME = (VARIABLE_TYPE)_gsNumberToPointer(_gs_##VARIABLE_NAME); _i += 1
#define getArgAs_CChars(VARIABLE_TYPE, VARIABLE_NAME, ARG)  MINSL_LOAD_ARG_STRING(_gs_##VARIABLE_NAME); VARIABLE_TYPE VARIABLE_NAME = _gs_##VARIABLE_NAME.c_str(); _i += 1
#define getArgAs_String(VARIABLE_TYPE, VARIABLE_NAME, ARG)  MINSL_LOAD_ARG_STRING(VARIABLE_NAME); _i += 1
#define getArgAs_END MINSL_LOAD_ARG_END();
#define ape_object_t MinScriptLang::Value
#define ape_object_make_null() MinScriptLang::Value{}
#define ape_object_make_bool(a) MinScriptLang::Value{(a) == true ? 1.0 : 0.0}
#define ape_object_make_number(a) MinScriptLang::Value{(a)}
static inline MinScriptLang::Value ape_object_make_string(void * ape, const char * cstr) {
  auto output = MinScriptLang::Value{std::string()};
  if (cstr != 0) {
    output.GetString() = cstr;
  }
  return output;
}
#define mape_object_make_array(a, b) MinScriptLang::Value{std::make_shared<MinScriptLang::Array>()}
#define mape_object_add_array_number(a, b, c) (b).GetArray()->Items.push_back(MinScriptLang::Value{(c)})
void * ape  = 0;
void * argc = 0;
#elif defined(GAME_SCRIPT_C)

static inline void * ape_object_make_null() {
  return 0;
}

static inline void * ape_object_make_bool(bool x) {
  GsInternalUnionConverter c;
  c.boolean = x;
  return c.voidpointer;
}

static inline void * ape_object_make_number(double x) {
  GsInternalUnionConverter c;
  c.number = x;
  return c.voidpointer;
}

static inline void * ape_object_make_string(void * ape, const char * x) {
#if defined(_WIN32)
  return (void *)_strdup(x);
#else
  return (void *)strdup(x);
#endif
}

static inline bool ape_object_get_bool(void * x) {
  GsInternalUnionConverter c;
  c.voidpointer = x;
  return c.boolean;
}

static inline double ape_object_get_number(void * x) {
  GsInternalUnionConverter c;
  c.voidpointer = x;
  return c.number;
}

static inline const char * ape_object_get_string(void * x) {
  return (const char *)x;
}

static inline void * mape_object_make_array(void * ape, uint64_t count) {
  return calloc(1, count * sizeof(double));
}

static inline void mape_object_add_array_number(uint64_t arrayIndex, void * array, double number) {
  if (array != 0) {
    double * p = (double *)array;
    p[arrayIndex] = number;
  }
}

static inline bool _getArgAs_Bool(void * arg) {
  return ape_object_get_bool(arg);
}
static inline double _getArgAs_Double(void * arg) {
  return ape_object_get_number(arg);
}
static inline void * _getArgAs_Pointer(void * arg) {
  return _gsNumberToPointer(ape_object_get_number(arg));
}
static inline const char * _getArgAs_String(void * arg) {
  return ape_object_get_string(arg);
}
#define GS_C_PROCEDURE_RETURN_TYPE() void *
#define GS_C_PROCEDURE_PARAMETERS() (void * ape, void * data, int argc, void ** args)
#define getArgAs_BEGIN(PROCEDURE_NAME)
#define getArgAs_Bool(VARIABLE_TYPE, VARIABLE_NAME, ARG)    VARIABLE_TYPE VARIABLE_NAME = (VARIABLE_TYPE)_getArgAs_Bool(ARG)
#define getArgAs_Double(VARIABLE_TYPE, VARIABLE_NAME, ARG)  VARIABLE_TYPE VARIABLE_NAME = (VARIABLE_TYPE)_getArgAs_Double(ARG)
#define getArgAs_Pointer(VARIABLE_TYPE, VARIABLE_NAME, ARG) VARIABLE_TYPE VARIABLE_NAME = (VARIABLE_TYPE)_getArgAs_Pointer(ARG)
#define getArgAs_CChars(VARIABLE_TYPE, VARIABLE_NAME, ARG)  VARIABLE_TYPE VARIABLE_NAME = (VARIABLE_TYPE)_getArgAs_String(ARG)
#define getArgAs_String(VARIABLE_TYPE, VARIABLE_NAME, ARG)  VARIABLE_TYPE VARIABLE_NAME = (VARIABLE_TYPE)_getArgAs_String(ARG)
#define getArgAs_END
#else
static inline bool _getArgAs_Bool(ape_object_t arg) {
  return ape_object_get_bool(arg);
}
static inline double _getArgAs_Double(ape_object_t arg) {
  return ape_object_get_number(arg);
}
static inline void * _getArgAs_Pointer(ape_object_t arg) {
  return _gsNumberToPointer(ape_object_get_number(arg));
}
static inline const char * _getArgAs_String(ape_object_t arg) {
  return ape_object_get_string(arg);
}
#define GS_C_PROCEDURE_RETURN_TYPE() ape_object_t
#define GS_C_PROCEDURE_PARAMETERS() (ape_t * ape, void * data, int argc, ape_object_t * args)
#define getArgAs_BEGIN(PROCEDURE_NAME)
#define getArgAs_Bool(VARIABLE_TYPE, VARIABLE_NAME, ARG)    VARIABLE_TYPE VARIABLE_NAME = (VARIABLE_TYPE)_getArgAs_Bool(ARG)
#define getArgAs_Double(VARIABLE_TYPE, VARIABLE_NAME, ARG)  VARIABLE_TYPE VARIABLE_NAME = (VARIABLE_TYPE)_getArgAs_Double(ARG)
#define getArgAs_Pointer(VARIABLE_TYPE, VARIABLE_NAME, ARG) VARIABLE_TYPE VARIABLE_NAME = (VARIABLE_TYPE)_getArgAs_Pointer(ARG)
#define getArgAs_CChars(VARIABLE_TYPE, VARIABLE_NAME, ARG)  VARIABLE_TYPE VARIABLE_NAME = (VARIABLE_TYPE)_getArgAs_String(ARG)
#define getArgAs_String(VARIABLE_TYPE, VARIABLE_NAME, ARG)  VARIABLE_TYPE VARIABLE_NAME = (VARIABLE_TYPE)_getArgAs_String(ARG)
#define getArgAs_END
#endif

GSN_WIN_IMPORT void * _gsVkGetInstanceProcAddr(void * instance, const char * name);
GSN_WIN_IMPORT void   _gsPrintThreadSafe(const char * astring);

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePrintConsole GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*string*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("printConsole")
  getArgAs_CChars(const char *, astring, args[_i++]);
  getArgAs_END

  _gsPrintThreadSafe(astring);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePrintDraw GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*string*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("printDraw")
  getArgAs_String(std::string, astring, args[_i++]);
  getArgAs_END

  if (astring != "") {
    ApeDrawLabelDebugText draw;
    draw.x     = 4;
    draw.y     = 14;
    draw.r     = 255;
    draw.g     = 255;
    draw.b     = 255;
    draw.a     = 255;
    draw.label = astring;
    gApeDrawLabelStackDebugTexts.push_back(draw);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureWindowSetTitle GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*title*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("windowSetTitle")
  getArgAs_CChars(const char *, title, args[_i++]);
  getArgAs_END

  redFSetWindowTitle(title);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureWindowGetWidth GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)redFGetWidth());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureWindowGetHeight GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)redFGetHeight());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureWindowSetWidthHeight GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*width*/,
    APE_OBJECT_NUMBER/*height*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("windowSetWidthHeight")
  getArgAs_Double(int, width,  args[_i++]);
  getArgAs_Double(int, height, args[_i++]);
  getArgAs_END

  redFSetWindowShape(width, height);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureWindowSetFullscreen GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_BOOL/*fullscreen*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("windowSetFullscreen")
  getArgAs_Bool(int, fullscreen, args[_i++]);
  getArgAs_END

  if (gGameMode == 1) {
    gFullscreen = fullscreen;
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureWindowIsFocused GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_bool((bool)glfwGetWindowAttrib((GLFWwindow *)redFGetGLFWwindowPointer(), GLFW_FOCUSED));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureWindowIsHovered GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_bool((bool)glfwGetWindowAttrib((GLFWwindow *)redFGetGLFWwindowPointer(), GLFW_HOVERED));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureWindowIsMinimized GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_bool((bool)glfwGetWindowAttrib((GLFWwindow *)redFGetGLFWwindowPointer(), GLFW_ICONIFIED));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureWindowIsHidden GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  int visible = glfwGetWindowAttrib((GLFWwindow *)redFGetGLFWwindowPointer(), GLFW_VISIBLE);

  return ape_object_make_bool((bool)(visible == 1 ? 0 : 1));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureWindowHide GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  if (gGameMode == 1) {
    glfwHideWindow((GLFWwindow *)redFGetGLFWwindowPointer());
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureWindowShow GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  glfwShowWindow((GLFWwindow *)redFGetGLFWwindowPointer());

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureWindowRequestAttention GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  glfwRequestWindowAttention((GLFWwindow *)redFGetGLFWwindowPointer());

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDrawPoint GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/,
    APE_OBJECT_NUMBER/*size*/,
    APE_OBJECT_NUMBER/*r*/,
    APE_OBJECT_NUMBER/*g*/,
    APE_OBJECT_NUMBER/*b*/,
    APE_OBJECT_NUMBER/*a*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("drawPoint")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_Double(float,       x,     args[_i++]);
  getArgAs_Double(float,       y,     args[_i++]);
  getArgAs_Double(float,       z,     args[_i++]);
  getArgAs_Double(float,       size,  args[_i++]);
  getArgAs_Double(int,         r,     args[_i++]);
  getArgAs_Double(int,         g,     args[_i++]);
  getArgAs_Double(int,         b,     args[_i++]);
  getArgAs_Double(int,         a,     args[_i++]);
  getArgAs_END

  _gsDrawPoint(label, x, y, z, size, r, g, b, a);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDrawLine GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*x0*/,
    APE_OBJECT_NUMBER/*y0*/,
    APE_OBJECT_NUMBER/*z0*/,
    APE_OBJECT_NUMBER/*x1*/,
    APE_OBJECT_NUMBER/*y1*/,
    APE_OBJECT_NUMBER/*z1*/,
    APE_OBJECT_NUMBER/*width*/,
    APE_OBJECT_NUMBER/*r*/,
    APE_OBJECT_NUMBER/*g*/,
    APE_OBJECT_NUMBER/*b*/,
    APE_OBJECT_NUMBER/*a*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("drawLine")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_Double(float,       x0,    args[_i++]);
  getArgAs_Double(float,       y0,    args[_i++]);
  getArgAs_Double(float,       z0,    args[_i++]);
  getArgAs_Double(float,       x1,    args[_i++]);
  getArgAs_Double(float,       y1,    args[_i++]);
  getArgAs_Double(float,       z1,    args[_i++]);
  getArgAs_Double(float,       width, args[_i++]);
  getArgAs_Double(int,         r,     args[_i++]);
  getArgAs_Double(int,         g,     args[_i++]);
  getArgAs_Double(int,         b,     args[_i++]);
  getArgAs_Double(int,         a,     args[_i++]);
  getArgAs_END

  _gsDrawLine(label, x0, y0, z0, x1, y1, z1, width, r, g, b, a);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDrawTriangle GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*x0*/,
    APE_OBJECT_NUMBER/*y0*/,
    APE_OBJECT_NUMBER/*z0*/,
    APE_OBJECT_NUMBER/*x1*/,
    APE_OBJECT_NUMBER/*y1*/,
    APE_OBJECT_NUMBER/*z1*/,
    APE_OBJECT_NUMBER/*x2*/,
    APE_OBJECT_NUMBER/*y2*/,
    APE_OBJECT_NUMBER/*z2*/,
    APE_OBJECT_NUMBER/*r*/,
    APE_OBJECT_NUMBER/*g*/,
    APE_OBJECT_NUMBER/*b*/,
    APE_OBJECT_NUMBER/*a*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("drawTriangle")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_Double(float,       x0,    args[_i++]);
  getArgAs_Double(float,       y0,    args[_i++]);
  getArgAs_Double(float,       z0,    args[_i++]);
  getArgAs_Double(float,       x1,    args[_i++]);
  getArgAs_Double(float,       y1,    args[_i++]);
  getArgAs_Double(float,       z1,    args[_i++]);
  getArgAs_Double(float,       x2,    args[_i++]);
  getArgAs_Double(float,       y2,    args[_i++]);
  getArgAs_Double(float,       z2,    args[_i++]);
  getArgAs_Double(int,         r,     args[_i++]);
  getArgAs_Double(int,         g,     args[_i++]);
  getArgAs_Double(int,         b,     args[_i++]);
  getArgAs_Double(int,         a,     args[_i++]);
  getArgAs_END

  _gsDrawTriangle(label, 0, x0, y0, z0, x1, y1, z1, x2, y2, z2, r, g, b, a);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDrawTriangleWireframe GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*x0*/,
    APE_OBJECT_NUMBER/*y0*/,
    APE_OBJECT_NUMBER/*z0*/,
    APE_OBJECT_NUMBER/*x1*/,
    APE_OBJECT_NUMBER/*y1*/,
    APE_OBJECT_NUMBER/*z1*/,
    APE_OBJECT_NUMBER/*x2*/,
    APE_OBJECT_NUMBER/*y2*/,
    APE_OBJECT_NUMBER/*z2*/,
    APE_OBJECT_NUMBER/*r*/,
    APE_OBJECT_NUMBER/*g*/,
    APE_OBJECT_NUMBER/*b*/,
    APE_OBJECT_NUMBER/*a*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("drawTriangleWireframe")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_Double(float,       x0,    args[_i++]);
  getArgAs_Double(float,       y0,    args[_i++]);
  getArgAs_Double(float,       z0,    args[_i++]);
  getArgAs_Double(float,       x1,    args[_i++]);
  getArgAs_Double(float,       y1,    args[_i++]);
  getArgAs_Double(float,       z1,    args[_i++]);
  getArgAs_Double(float,       x2,    args[_i++]);
  getArgAs_Double(float,       y2,    args[_i++]);
  getArgAs_Double(float,       z2,    args[_i++]);
  getArgAs_Double(int,         r,     args[_i++]);
  getArgAs_Double(int,         g,     args[_i++]);
  getArgAs_Double(int,         b,     args[_i++]);
  getArgAs_Double(int,         a,     args[_i++]);
  getArgAs_END

  _gsDrawTriangle(label, 1, x0, y0, z0, x1, y1, z1, x2, y2, z2, r, g, b, a);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDrawSphere GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/,
    APE_OBJECT_NUMBER/*size*/,
    APE_OBJECT_NUMBER/*r*/,
    APE_OBJECT_NUMBER/*g*/,
    APE_OBJECT_NUMBER/*b*/,
    APE_OBJECT_NUMBER/*a*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("drawSphere")
  getArgAs_Double(float, x,    args[_i++]);
  getArgAs_Double(float, y,    args[_i++]);
  getArgAs_Double(float, z,    args[_i++]);
  getArgAs_Double(float, size, args[_i++]);
  getArgAs_Double(float, r,    args[_i++]);
  getArgAs_Double(float, g,    args[_i++]);
  getArgAs_Double(float, b,    args[_i++]);
  getArgAs_Double(float, a,    args[_i++]);
  getArgAs_END

  redFSetColor(r, g, b, a);
  redFDrawSphere(x, y, z, size);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDrawSphereWireframe GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/,
    APE_OBJECT_NUMBER/*size*/,
    APE_OBJECT_NUMBER/*r*/,
    APE_OBJECT_NUMBER/*g*/,
    APE_OBJECT_NUMBER/*b*/,
    APE_OBJECT_NUMBER/*a*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("drawSphereWireframe")
  getArgAs_Double(float, x,    args[_i++]);
  getArgAs_Double(float, y,    args[_i++]);
  getArgAs_Double(float, z,    args[_i++]);
  getArgAs_Double(float, size, args[_i++]);
  getArgAs_Double(float, r,    args[_i++]);
  getArgAs_Double(float, g,    args[_i++]);
  getArgAs_Double(float, b,    args[_i++]);
  getArgAs_Double(float, a,    args[_i++]);
  getArgAs_END

  redFSetColor(r, g, b, a);
  redFNoFill();
  redFSetLineWidth(2);
  redFDrawSphere(x, y, z, size);
  redFFill();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDrawDebugText GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*r*/,
    APE_OBJECT_NUMBER/*g*/,
    APE_OBJECT_NUMBER/*b*/,
    APE_OBJECT_NUMBER/*a*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("drawDebugText")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_Double(float,       x,     args[_i++]);
  getArgAs_Double(float,       y,     args[_i++]);
  getArgAs_Double(float,       r,     args[_i++]);
  getArgAs_Double(float,       g,     args[_i++]);
  getArgAs_Double(float,       b,     args[_i++]);
  getArgAs_Double(float,       a,     args[_i++]);
  getArgAs_END

  if (label != "") {
    ApeDrawLabelDebugText draw;
    draw.x     = x + 4;
    draw.y     = y + 14;
    draw.r     = r;
    draw.g     = g;
    draw.b     = b;
    draw.a     = a;
    draw.label = label;
    gApeDrawLabelStackDebugTexts.push_back(draw);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDrawDebugTextAtPoint GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("drawDebugTextAtPoint")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_Double(float,       x,     args[_i++]);
  getArgAs_Double(float,       y,     args[_i++]);
  getArgAs_Double(float,       z,     args[_i++]);
  getArgAs_END

  _gsDrawPoint(label, x, y, z, 0, 0, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureIsRerun GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_bool((bool)gRerun);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetCurrentFrame GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)gCurrentFrame);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetCurrentFrameThread2 GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)gCurrentFrameThread2);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSetCurrentFrame GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*frame*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("setCurrentFrame")
  getArgAs_Double(uint64_t, frame, args[_i++]);
  getArgAs_END

  gCurrentFrame = frame;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSetCurrentFrameThread2 GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*frame*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("setCurrentFrameThread2")
  getArgAs_Double(uint64_t, frame, args[_i++]);
  getArgAs_END

  gCurrentFrameThread2 = frame;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetRandomNumber GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)rand());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetExeDirectoryPath GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_string(ape, gCurrentExeDir);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureIsLinux GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

#if defined(__linux__)
  return ape_object_make_bool(true);
#else
  return ape_object_make_bool(false);
#endif
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureIsWindows GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

#ifdef _WIN32
  return ape_object_make_bool(true);
#else
  return ape_object_make_bool(false);
#endif
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureIsInGameMode GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_bool((bool)gGameMode);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraDefaultControlDisable GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  if (gDefaultCameraForceEnabled == 0) {
    gDefaultCameraEnabled = 0;
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraDefaultControlEnable GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  gDefaultCameraEnabled = 1;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraDefaultControlForceEnable GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  gDefaultCameraEnabled      = 1;
  gDefaultCameraForceEnabled = 1;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraDefaultControlIsEnabled GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_bool((bool)gDefaultCameraEnabled);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraSetMoveSpeed GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*speed*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraSetMoveSpeed")
  getArgAs_Double(float, speed, args[_i++]);
  getArgAs_END

  redFFirstPersonCameraSetMoveSpeed(gCamera[0], speed);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraSetRollSpeed GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*speed*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraSetRollSpeed")
  getArgAs_Double(float, speed, args[_i++]);
  getArgAs_END

  redFFirstPersonCameraSetRollSpeed(gCamera[0], speed);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraSetMouseSensitivity GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*sensitivity*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraSetMouseSensitivity")
  getArgAs_Double(float, sensitivity, args[_i++]);
  getArgAs_END

  redFFirstPersonCameraSetSensitivity(gCamera[0], sensitivity);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraGetVector GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  RedFHandleNode node  = redFFirstPersonCameraCastToNode(gCamera[0]);
  ape_object_t   array = mape_object_make_array(ape, 3);
  mape_object_add_array_number(0, array, (double)redFNodeGetGlobalPositionX(node));
  mape_object_add_array_number(1, array, (double)redFNodeGetGlobalPositionY(node));
  mape_object_add_array_number(2, array, (double)redFNodeGetGlobalPositionZ(node));
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraGetVersor GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  RedFHandleNode node  = redFFirstPersonCameraCastToNode(gCamera[0]);
  ape_object_t   array = mape_object_make_array(ape, 4);
  mape_object_add_array_number(0, array, (double)redFNodeGetGlobalOrientationQuaternionX(node));
  mape_object_add_array_number(1, array, (double)redFNodeGetGlobalOrientationQuaternionY(node));
  mape_object_add_array_number(2, array, (double)redFNodeGetGlobalOrientationQuaternionZ(node));
  mape_object_add_array_number(3, array, (double)redFNodeGetGlobalOrientationQuaternionW(node));
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraSetVector GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraSetVector")
  getArgAs_Double(float, x, args[_i++]);
  getArgAs_Double(float, y, args[_i++]);
  getArgAs_Double(float, z, args[_i++]);
  getArgAs_END

  if (gDefaultCameraForceEnabled == 0) {
    redFNodeSetGlobalPosition(redFFirstPersonCameraCastToNode(gCamera[0]), x, y, z);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraSetVersor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/,
    APE_OBJECT_NUMBER/*w*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraSetVersor")
  getArgAs_Double(float, x, args[_i++]);
  getArgAs_Double(float, y, args[_i++]);
  getArgAs_Double(float, z, args[_i++]);
  getArgAs_Double(float, w, args[_i++]);
  getArgAs_END

  if (gDefaultCameraForceEnabled == 0) {
    redFNodeSetGlobalOrientationQuaternion(redFFirstPersonCameraCastToNode(gCamera[0]), x, y, z, w);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraRotate GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*rotationX*/,
    APE_OBJECT_NUMBER/*rotationY*/,
    APE_OBJECT_NUMBER/*rotationZ*/,
    APE_OBJECT_NUMBER/*rotationDeg*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraRotate")
  getArgAs_Double(float, rotationX,   args[_i++]);
  getArgAs_Double(float, rotationY,   args[_i++]);
  getArgAs_Double(float, rotationZ,   args[_i++]);
  getArgAs_Double(float, rotationDeg, args[_i++]);
  getArgAs_END

  redFNodeRotateDeg(redFFirstPersonCameraCastToNode(gCamera[0]), rotationDeg, rotationX, rotationY, rotationZ);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraLookAt GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/,
    APE_OBJECT_NUMBER/*upX*/,
    APE_OBJECT_NUMBER/*upY*/,
    APE_OBJECT_NUMBER/*upZ*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraLookAt")
  getArgAs_Double(float, x,   args[_i++]);
  getArgAs_Double(float, y,   args[_i++]);
  getArgAs_Double(float, z,   args[_i++]);
  getArgAs_Double(float, upX, args[_i++]);
  getArgAs_Double(float, upY, args[_i++]);
  getArgAs_Double(float, upZ, args[_i++]);
  getArgAs_END

  redFNodeLookAt(redFFirstPersonCameraCastToNode(gCamera[0]), x, y, z, upX, upY, upZ);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraSetFOV GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*fov*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraSetFOV")
  getArgAs_Double(float, fov, args[_i++]);
  getArgAs_END

  redFCameraSetFov(redFFirstPersonCameraCastToCamera(gCamera[0]), fov);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraSetNearClip GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*near*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraSetNearClip")
  getArgAs_Double(float, Near, args[_i++]);
  getArgAs_END

  redFCameraSetNearClip(redFFirstPersonCameraCastToCamera(gCamera[0]), Near);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraSetFarClip GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*far*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraSetFarClip")
  getArgAs_Double(float, Far, args[_i++]);
  getArgAs_END

  redFCameraSetFarClip(redFFirstPersonCameraCastToCamera(gCamera[0]), Far);
  if (Far == -1) {
    redFSetClearDepthValue(0);
    redFSetDepthFunc(GL_GREATER);
  } else {
    redFSetClearDepthValue(1);
    redFSetDepthFunc(GL_LESS);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraSetProjectionMode GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*mode*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraSetProjectionMode")
  getArgAs_Double(int, mode, args[_i++]);
  getArgAs_END

  if (mode == 0) {
    redFCameraDisableOrtho(redFFirstPersonCameraCastToCamera(gCamera[0]));
  } else if (mode == 1) {
    redFCameraEnableOrtho(redFFirstPersonCameraCastToCamera(gCamera[0]));
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraSetAspectRatio GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aspectRatio*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraSetAspectRatio")
  getArgAs_Double(float, aspectRatio, args[_i++]);
  getArgAs_END

  redFCameraSetAspectRatio(redFFirstPersonCameraCastToCamera(gCamera[0]), aspectRatio);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraSetForceAspectRatio GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_BOOL/*forceAspectRatio*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraSetForceAspectRatio")
  getArgAs_Bool(bool, forceAspectRatio, args[_i++]);
  getArgAs_END

  redFCameraSetForceAspectRatio(redFFirstPersonCameraCastToCamera(gCamera[0]), (RedFBool32)forceAspectRatio);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraSetLensOffset GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*lensOffsetX*/,
    APE_OBJECT_NUMBER/*lensOffsetY*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraSetLensOffset")
  getArgAs_Double(float, lensOffsetX, args[_i++]);
  getArgAs_Double(float, lensOffsetY, args[_i++]);
  getArgAs_END

  redFCameraSetLensOffset(redFFirstPersonCameraCastToCamera(gCamera[0]), lensOffsetX, lensOffsetY);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraSetupPerspective GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_BOOL/*vflip*/,
    APE_OBJECT_NUMBER/*fov*/,
    APE_OBJECT_NUMBER/*nearDist*/,
    APE_OBJECT_NUMBER/*farDist*/,
    APE_OBJECT_NUMBER/*lensOffsetX*/,
    APE_OBJECT_NUMBER/*lensOffsetY*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraSetupPerspective")
  getArgAs_Bool(bool,    vflip,       args[_i++]);
  getArgAs_Double(float, fov,         args[_i++]);
  getArgAs_Double(float, nearDist,    args[_i++]);
  getArgAs_Double(float, farDist,     args[_i++]);
  getArgAs_Double(float, lensOffsetX, args[_i++]);
  getArgAs_Double(float, lensOffsetY, args[_i++]);
  getArgAs_END

  redFCameraSetupPerspective(redFFirstPersonCameraCastToCamera(gCamera[0]), (RedFBool32)vflip, fov, nearDist, farDist, lensOffsetX, lensOffsetY);
  if (farDist == -1) {
    redFSetClearDepthValue(0);
    redFSetDepthFunc(GL_GREATER);
  } else {
    redFSetClearDepthValue(1);
    redFSetDepthFunc(GL_LESS);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraSetupOffAxisViewPortal GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*topLeftX*/,
    APE_OBJECT_NUMBER/*topLeftY*/,
    APE_OBJECT_NUMBER/*topLeftZ*/,
    APE_OBJECT_NUMBER/*bottomLeftX*/,
    APE_OBJECT_NUMBER/*bottomLeftY*/,
    APE_OBJECT_NUMBER/*bottomLeftZ*/,
    APE_OBJECT_NUMBER/*bottomRightX*/,
    APE_OBJECT_NUMBER/*bottomRightY*/,
    APE_OBJECT_NUMBER/*bottomRightZ*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraSetupOffAxisViewPortal")
  getArgAs_Double(float, topLeftX,     args[_i++]);
  getArgAs_Double(float, topLeftY,     args[_i++]);
  getArgAs_Double(float, topLeftZ,     args[_i++]);
  getArgAs_Double(float, bottomLeftX,  args[_i++]);
  getArgAs_Double(float, bottomLeftY,  args[_i++]);
  getArgAs_Double(float, bottomLeftZ,  args[_i++]);
  getArgAs_Double(float, bottomRightX, args[_i++]);
  getArgAs_Double(float, bottomRightY, args[_i++]);
  getArgAs_Double(float, bottomRightZ, args[_i++]);
  getArgAs_END

  redFCameraSetupOffAxisViewPortal(redFFirstPersonCameraCastToCamera(gCamera[0]), topLeftX, topLeftY, topLeftZ, bottomLeftX, bottomLeftY, bottomLeftZ, bottomRightX, bottomRightY, bottomRightZ);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraSetVFlip GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_BOOL/*vflip*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraSetVFlip")
  getArgAs_Bool(bool, vflip, args[_i++]);
  getArgAs_END

  redFCameraSetVFlip(redFFirstPersonCameraCastToCamera(gCamera[0]), (RedFBool32)vflip);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraScreenToWorld GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*screenX*/,
    APE_OBJECT_NUMBER/*screenY*/,
    APE_OBJECT_NUMBER/*screenZ*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraScreenToWorld")
  getArgAs_Double(float, screenX, args[_i++]);
  getArgAs_Double(float, screenY, args[_i++]);
  getArgAs_Double(float, screenZ, args[_i++]);
  getArgAs_END

  float vector3[3];
  redFCameraScreenToWorld(redFFirstPersonCameraCastToCamera(gCamera[0]), screenX, screenY, screenZ, vector3);

  ape_object_t array = mape_object_make_array(ape, 3);
  mape_object_add_array_number(0, array, (double)vector3[0]);
  mape_object_add_array_number(1, array, (double)vector3[1]);
  mape_object_add_array_number(2, array, (double)vector3[2]);
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraWorldToScreen GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*worldX*/,
    APE_OBJECT_NUMBER/*worldY*/,
    APE_OBJECT_NUMBER/*worldZ*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraWorldToScreen")
  getArgAs_Double(float, worldX, args[_i++]);
  getArgAs_Double(float, worldY, args[_i++]);
  getArgAs_Double(float, worldZ, args[_i++]);
  getArgAs_END

  float vector3[3];
  redFCameraWorldToScreen(redFFirstPersonCameraCastToCamera(gCamera[0]), worldX, worldY, worldZ, vector3);

  ape_object_t array = mape_object_make_array(ape, 3);
  mape_object_add_array_number(0, array, (double)vector3[0]);
  mape_object_add_array_number(1, array, (double)vector3[1]);
  mape_object_add_array_number(2, array, (double)vector3[2]);
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraGetSideVector GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  RedFHandleNode node  = redFFirstPersonCameraCastToNode(gCamera[0]);
  ape_object_t   array = mape_object_make_array(ape, 3);
  mape_object_add_array_number(0, array, (double)redFNodeGetSideDirX(node));
  mape_object_add_array_number(1, array, (double)redFNodeGetSideDirY(node));
  mape_object_add_array_number(2, array, (double)redFNodeGetSideDirZ(node));
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraGetUpVector GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  RedFHandleNode node  = redFFirstPersonCameraCastToNode(gCamera[0]);
  ape_object_t   array = mape_object_make_array(ape, 3);
  mape_object_add_array_number(0, array, (double)redFNodeGetUpDirX(node));
  mape_object_add_array_number(1, array, (double)redFNodeGetUpDirY(node));
  mape_object_add_array_number(2, array, (double)redFNodeGetUpDirZ(node));
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraGetLookAtVector GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  RedFHandleNode node  = redFFirstPersonCameraCastToNode(gCamera[0]);
  ape_object_t   array = mape_object_make_array(ape, 3);
  mape_object_add_array_number(0, array, (double)redFNodeGetLookAtDirX(node));
  mape_object_add_array_number(1, array, (double)redFNodeGetLookAtDirY(node));
  mape_object_add_array_number(2, array, (double)redFNodeGetLookAtDirZ(node));
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraGetProjectionMatrix GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*outPointer*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraGetProjectionMatrix")
  getArgAs_Pointer(void *, outPointer, args[_i++]);
  getArgAs_END

  redFCameraGetProjectionMatrix(redFFirstPersonCameraCastToCamera(gCamera[0]), outPointer);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraGetModelViewMatrix GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*outPointer*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraGetModelViewMatrix")
  getArgAs_Pointer(void *, outPointer, args[_i++]);
  getArgAs_END

  redFCameraGetModelViewMatrix(redFFirstPersonCameraCastToCamera(gCamera[0]), outPointer);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraGetModelViewProjectionMatrix GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*outPointer*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraGetModelViewProjectionMatrix")
  getArgAs_Pointer(void *, outPointer, args[_i++]);
  getArgAs_END

  redFCameraGetModelViewProjectionMatrix(redFFirstPersonCameraCastToCamera(gCamera[0]), outPointer);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDefaultCameraSetControlKeys GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*up*/,
    APE_OBJECT_NUMBER/*down*/,
    APE_OBJECT_NUMBER/*left*/,
    APE_OBJECT_NUMBER/*right*/,
    APE_OBJECT_NUMBER/*forward*/,
    APE_OBJECT_NUMBER/*backward*/,
    APE_OBJECT_NUMBER/*rollLeft*/,
    APE_OBJECT_NUMBER/*rollRight*/,
    APE_OBJECT_NUMBER/*rollReset*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("defaultCameraSetControlKeys")
  getArgAs_Double(int, up,        args[_i++]);
  getArgAs_Double(int, down,      args[_i++]);
  getArgAs_Double(int, left,      args[_i++]);
  getArgAs_Double(int, right,     args[_i++]);
  getArgAs_Double(int, forward,   args[_i++]);
  getArgAs_Double(int, backward,  args[_i++]);
  getArgAs_Double(int, rollLeft,  args[_i++]);
  getArgAs_Double(int, rollRight, args[_i++]);
  getArgAs_Double(int, rollReset, args[_i++]);
  getArgAs_END

  redFFirstPersonCameraSetKeyUp(gCamera[0], up);
  redFFirstPersonCameraSetKeyDown(gCamera[0], down);
  redFFirstPersonCameraSetKeyLeft(gCamera[0], left);
  redFFirstPersonCameraSetKeyRight(gCamera[0], right);
  redFFirstPersonCameraSetKeyForward(gCamera[0], forward);
  redFFirstPersonCameraSetKeyBackward(gCamera[0], backward);
  redFFirstPersonCameraSetKeyRollLeft(gCamera[0], rollLeft);
  redFFirstPersonCameraSetKeyRollRight(gCamera[0], rollRight);
  redFFirstPersonCameraSetKeyRollReset(gCamera[0], rollReset);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSetBackgroundColor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*r*/,
    APE_OBJECT_NUMBER/*g*/,
    APE_OBJECT_NUMBER/*b*/,
    APE_OBJECT_NUMBER/*a*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("setBackgroundColor")
  getArgAs_Double(int, r, args[_i++]);
  getArgAs_Double(int, g, args[_i++]);
  getArgAs_Double(int, b, args[_i++]);
  getArgAs_Double(int, a, args[_i++]);
  getArgAs_END

  redFBackground(r, g, b, a);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSetViewport GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*width*/,
    APE_OBJECT_NUMBER/*height*/,
    APE_OBJECT_BOOL/*vflip*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("setViewport")
  getArgAs_Double(float, x,      args[_i++]);
  getArgAs_Double(float, y,      args[_i++]);
  getArgAs_Double(float, width,  args[_i++]);
  getArgAs_Double(float, height, args[_i++]);
  getArgAs_Bool(bool,    vflip,  args[_i++]);
  getArgAs_END

  redFViewport(x, y, width, height, vflip);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureAlphaBlendingEnable GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  redFEnableAlphaBlending();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureAlphaBlendingDisable GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  redFDisableAlphaBlending();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureBlendModeEnable GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*mode*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("blendModeEnable")
  getArgAs_Double(int, mode, args[_i++]);
  getArgAs_END

  redFEnableBlendMode((RedFBlendMode)mode);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureBlendModeDisable GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  redFDisableBlendMode();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDepthTestEnable GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  redFEnableDepthTest();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDepthTestDisable GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  redFDisableDepthTest();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureCullingEnable GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*mode*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("cullingEnable")
  getArgAs_Double(int, mode, args[_i++]);
  getArgAs_END

  int glMode = 0x0405; // GL_BACK
  if (mode == 1) {
    glMode = 0x0404;   // GL_FRONT
  }

  redFEnableCulling(glMode);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureCullingDisable GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  redFDisableCulling();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureClear GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*r*/,
    APE_OBJECT_NUMBER/*g*/,
    APE_OBJECT_NUMBER/*b*/,
    APE_OBJECT_NUMBER/*a*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("clear")
  getArgAs_Double(float, r, args[_i++]);
  getArgAs_Double(float, g, args[_i++]);
  getArgAs_Double(float, b, args[_i++]);
  getArgAs_Double(float, a, args[_i++]);
  getArgAs_END

  redFClear(r, g, b, a);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureClearAlpha GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  redFClearAlpha();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureClearDepth GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  redFColorMask(0, 0, 0, 0);
  redFClear(0, 0, 0, 0);
  redFColorMask(1, 1, 1, 1);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSaveScreenRawToMemory GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*width*/,
    APE_OBJECT_NUMBER/*height*/,
    APE_OBJECT_NUMBER/*out8BitRGBAPixels*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("saveScreenRawToMemory")
  getArgAs_Double(int,     x,                 args[_i++]);
  getArgAs_Double(int,     y,                 args[_i++]);
  getArgAs_Double(int,     width,             args[_i++]);
  getArgAs_Double(int,     height,            args[_i++]);
  getArgAs_Pointer(void *, out8BitRGBAPixels, args[_i++]);
  getArgAs_END

  redFSaveScreenRawToMemory(x, y, width, height, out8BitRGBAPixels);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalArrayNew8Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*count*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalArrayNew8Bit")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_Double(uint64_t,    count, args[_i++]);
  getArgAs_END

  {
    void * possiblyAlreadyExistingPointer = gApeGlobalArrayPointer[label];
    if (possiblyAlreadyExistingPointer != 0) {
      return ape_object_make_number(_gsPointerToNumber(possiblyAlreadyExistingPointer));
    }
  }

  if (count == 0) {
    return ape_object_make_number(0.0);
  }

  void * pointer = calloc(1, count * sizeof(unsigned char));
  gApeGlobalArrayBytesCount[label] = count;
  gApeGlobalArrayPointer[label]    = pointer;

  return ape_object_make_number(_gsPointerToNumber(pointer));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalArrayPersistentNew8Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*count*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalArrayPersistentNew8Bit")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_Double(uint64_t,    count, args[_i++]);
  getArgAs_END

  {
    void * possiblyAlreadyExistingPointer = gApeGlobalArrayPersistentPointer[label];
    if (possiblyAlreadyExistingPointer != 0) {
      return ape_object_make_number(_gsPointerToNumber(possiblyAlreadyExistingPointer));
    }
  }

  if (count == 0) {
    return ape_object_make_number(0.0);
  }

  void * pointer = calloc(1, count * sizeof(unsigned char));
  gApeGlobalArrayPersistentBytesCount[label] = count;
  gApeGlobalArrayPersistentPointer[label]    = pointer;

  return ape_object_make_number(_gsPointerToNumber(pointer));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalArrayDelete GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalArrayDelete")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  void * pointer = gApeGlobalArrayPointer[label];
  free(pointer);

  gApeGlobalArrayBytesCount.erase(label);
  gApeGlobalArrayPointer.erase(label);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalArrayPersistentDelete GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalArrayPersistentDelete")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  void * pointer = gApeGlobalArrayPersistentPointer[label];
  free(pointer);

  gApeGlobalArrayPersistentBytesCount.erase(label);
  gApeGlobalArrayPersistentPointer.erase(label);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalArrayDeleteAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  for (auto & kv : gApeGlobalArrayPointer) {
    free(kv.second);
  }

  gApeGlobalArrayBytesCount.clear();
  gApeGlobalArrayPointer.clear();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalArrayPersistentDeleteAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  for (auto & kv : gApeGlobalArrayPersistentPointer) {
    free(kv.second);
  }

  gApeGlobalArrayPersistentBytesCount.clear();
  gApeGlobalArrayPersistentPointer.clear();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalArrayGetBytesCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalArrayGetBytesCount")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)gApeGlobalArrayBytesCount[label]);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalArrayGetPointer GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalArrayGetPointer")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  return ape_object_make_number(_gsPointerToNumber(gApeGlobalArrayPointer[label]));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalArrayPersistentGetBytesCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalArrayPersistentGetBytesCount")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)gApeGlobalArrayPersistentBytesCount[label]);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalArrayPersistentGetPointer GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalArrayPersistentGetPointer")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  return ape_object_make_number(_gsPointerToNumber(gApeGlobalArrayPersistentPointer[label]));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalSharedArrayPersistentNew8Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*count*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalSharedArrayPersistentNew8Bit")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_Double(uint64_t,    count, args[_i++]);
  getArgAs_END

  volatile void * pointer = 0;
  {
    std::lock_guard<std::mutex> __thread2GlobalSharedArrayPersistentGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_thread2GlobalSharedArrayPersistentGuardAndSerializeMutex);

    void * possiblyAlreadyExistingPointer = gApeGlobalSharedArrayPersistentPointer[label];
    if (possiblyAlreadyExistingPointer != 0) {
      pointer = possiblyAlreadyExistingPointer;
    } else {
      if (count != 0) {
        pointer = calloc(1, count * sizeof(unsigned char));
        gApeGlobalSharedArrayPersistentBytesCount[label] = count;
        gApeGlobalSharedArrayPersistentPointer[label]    = (void *)pointer;
      }
    }
  }

  return ape_object_make_number(_gsPointerToNumber((void *)pointer));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalSharedArrayPersistentGetBytesCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalSharedArrayPersistentGetBytesCount")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  volatile double out = 0;
  {
    std::lock_guard<std::mutex> __thread2GlobalSharedArrayPersistentGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_thread2GlobalSharedArrayPersistentGuardAndSerializeMutex);
    out = (double)gApeGlobalSharedArrayPersistentBytesCount[label];
  }

  return ape_object_make_number(out);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalSharedArrayPersistentGetPointer GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalSharedArrayPersistentGetPointer")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  volatile double out = 0;
  {
    std::lock_guard<std::mutex> __thread2GlobalSharedArrayPersistentGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_thread2GlobalSharedArrayPersistentGuardAndSerializeMutex);
    out = _gsPointerToNumber(gApeGlobalSharedArrayPersistentPointer[label]);
  }

  return ape_object_make_number(out);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetBool GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*index*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetBool")
  getArgAs_Pointer(unsigned char *, pointer, args[_i++]);
  getArgAs_Double(uint64_t,         i,       args[_i++]);
  getArgAs_END

  return ape_object_make_bool((bool)pointer[i]);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetString GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetString")
  getArgAs_Pointer(const char *, pointer, args[_i++]);
  getArgAs_END

  return ape_object_make_string(ape, pointer);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetSubstring GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*stringFirst*/,
    APE_OBJECT_NUMBER/*stringCount*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetSubstring")
  getArgAs_Pointer(const char *, pointer,     args[_i++]);
  getArgAs_Double(uint64_t,      stringFirst, args[_i++]);
  getArgAs_Double(uint64_t,      stringCount, args[_i++]);
  getArgAs_END

  if (stringCount == 0) {
    return ape_object_make_string(ape, "");
  }

  std::string substring;
  substring.resize(stringCount);
  for (uint64_t i = 0; i < stringCount; i += 1) {
    substring[i] = pointer[stringFirst+i];
  }

  return ape_object_make_string(ape, substring.c_str());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetNumber GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*index*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetNumber")
  getArgAs_Pointer(float *, pointer, args[_i++]);
  getArgAs_Double(uint64_t, i,       args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)pointer[i]);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetInteger GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*index*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetInteger")
  getArgAs_Pointer(int *,   pointer, args[_i++]);
  getArgAs_Double(uint64_t, i,       args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)pointer[i]);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetUnsignedInteger GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*index*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetUnsignedInteger")
  getArgAs_Pointer(unsigned *, pointer, args[_i++]);
  getArgAs_Double(uint64_t,    i,       args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)pointer[i]);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetInteger8Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*index*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetInteger8Bit")
  getArgAs_Pointer(int8_t *, pointer, args[_i++]);
  getArgAs_Double(uint64_t,  i,       args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)pointer[i]);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetUnsignedInteger8Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*index*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetUnsignedInteger8Bit")
  getArgAs_Pointer(unsigned char *, pointer, args[_i++]);
  getArgAs_Double(uint64_t,         i,       args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)pointer[i]);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetBool GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*index*/,
    APE_OBJECT_BOOL/*value*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetBool")
  getArgAs_Pointer(unsigned char *, pointer, args[_i++]);
  getArgAs_Double(uint64_t,         i,       args[_i++]);
  getArgAs_Bool(unsigned char,      v,       args[_i++]);
  getArgAs_END

  pointer[i] = v;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetString GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerCharsFirst*/,
    APE_OBJECT_STRING/*value*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetString")
  getArgAs_Pointer(char *,      pointer,           args[_i++]);
  getArgAs_Double(uint64_t,     pointerCharsFirst, args[_i++]);
  getArgAs_CChars(const char *, value,             args[_i++]);
  getArgAs_END

  {
    uint64_t i = 0;
    while (1) {
      char c = value[i];
      pointer[pointerCharsFirst+i] = c;
      if (c == 0) {
        break;
      }
      i += 1;
    }
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetStringExcludingNullChar GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerCharsFirst*/,
    APE_OBJECT_STRING/*value*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetStringExcludingNullChar")
  getArgAs_Pointer(char *,      pointer,           args[_i++]);
  getArgAs_Double(uint64_t,     pointerCharsFirst, args[_i++]);
  getArgAs_CChars(const char *, value,             args[_i++]);
  getArgAs_END

  {
    uint64_t i = 0;
    while (1) {
      char c = value[i];
      if (c == 0) {
        break;
      }
      pointer[pointerCharsFirst+i] = c;
      i += 1;
    }
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetSubstring GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerCharsFirst*/,
    APE_OBJECT_STRING/*string*/,
    APE_OBJECT_NUMBER/*stringFirst*/,
    APE_OBJECT_NUMBER/*stringCount*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetSubstring")
  getArgAs_Pointer(char *,      pointer,           args[_i++]);
  getArgAs_Double(uint64_t,     pointerCharsFirst, args[_i++]);
  getArgAs_CChars(const char *, astring,           args[_i++]);
  getArgAs_Double(uint64_t,     astringFirst,      args[_i++]);
  getArgAs_Double(uint64_t,     astringCount,      args[_i++]);
  getArgAs_END

  if (astringCount > 0) {
    uint64_t i = 0;
    while (1) {
      char c = astring[astringFirst+i];
      pointer[pointerCharsFirst+i] = c;
      i += 1;
      if (i == astringCount) {
        break;
      }
    }
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetNumber GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*index*/,
    APE_OBJECT_NUMBER/*value*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetNumber")
  getArgAs_Pointer(float *, pointer, args[_i++]);
  getArgAs_Double(uint64_t, i,       args[_i++]);
  getArgAs_Double(float,    v,       args[_i++]);
  getArgAs_END

  pointer[i] = v;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetInteger GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*index*/,
    APE_OBJECT_NUMBER/*value*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetInteger")
  getArgAs_Pointer(int *,   pointer, args[_i++]);
  getArgAs_Double(uint64_t, i,       args[_i++]);
  getArgAs_Double(int,      v,       args[_i++]);
  getArgAs_END

  pointer[i] = v;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetUnsignedInteger GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*index*/,
    APE_OBJECT_NUMBER/*value*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetUnsignedInteger")
  getArgAs_Pointer(unsigned *, pointer, args[_i++]);
  getArgAs_Double(uint64_t,    i,       args[_i++]);
  getArgAs_Double(unsigned,    v,       args[_i++]);
  getArgAs_END

  pointer[i] = v;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetInteger8Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*index*/,
    APE_OBJECT_NUMBER/*value*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetInteger8Bit")
  getArgAs_Pointer(int8_t *, pointer, args[_i++]);
  getArgAs_Double(uint64_t,  i,       args[_i++]);
  getArgAs_Double(int8_t,    v,       args[_i++]);
  getArgAs_END

  pointer[i] = v;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetUnsignedInteger8Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*index*/,
    APE_OBJECT_NUMBER/*value*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetUnsignedInteger8Bit")
  getArgAs_Pointer(unsigned char *, pointer, args[_i++]);
  getArgAs_Double(uint64_t,         i,       args[_i++]);
  getArgAs_Double(unsigned char,    v,       args[_i++]);
  getArgAs_END

  pointer[i] = v;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetAtOffsetNumber GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetAtOffsetNumber")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  float * p = (float *)(void *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number((double)p[0]);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetAtOffsetNumber64Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetAtOffsetNumber64Bit")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  double * p = (double *)(void *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number(p[0]);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetAtOffsetInteger GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetAtOffsetInteger")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  int * p = (int *)(void *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number((double)p[0]);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetAtOffsetUnsignedInteger GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetAtOffsetUnsignedInteger")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  unsigned * p = (unsigned *)(void *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number((double)p[0]);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetAtOffsetInteger16Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetAtOffsetInteger16Bit")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  int16_t * p = (int16_t *)(void *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number((double)p[0]);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetAtOffsetInteger64Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetAtOffsetInteger64Bit")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  int64_t * p = (int64_t *)(void *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number((double)p[0]);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetAtOffsetUnsignedInteger16Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetAtOffsetUnsignedInteger16Bit")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  uint16_t * p = (uint16_t *)(void *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number((double)p[0]);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetAtOffsetUnsignedInteger64Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetAtOffsetUnsignedInteger64Bit")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  uint64_t * p = (uint64_t *)(void *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number((double)p[0]);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetAtOffsetNumber GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/,
    APE_OBJECT_NUMBER/*value*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetAtOffsetNumber")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_Double(float,            v,                 args[_i++]);
  getArgAs_END

  float * p = (float *)(void *)(&pointer[pointerBytesFirst]);

  p[0] = v;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetAtOffsetNumber64Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/,
    APE_OBJECT_NUMBER/*value*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetAtOffsetNumber64Bit")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_Double(double,           v,                 args[_i++]);
  getArgAs_END

  double * p = (double *)(void *)(&pointer[pointerBytesFirst]);

  p[0] = v;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetAtOffsetInteger GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/,
    APE_OBJECT_NUMBER/*value*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetAtOffsetInteger")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_Double(int,              v,                 args[_i++]);
  getArgAs_END

  int * p = (int *)(void *)(&pointer[pointerBytesFirst]);

  p[0] = v;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetAtOffsetUnsignedInteger GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/,
    APE_OBJECT_NUMBER/*value*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetAtOffsetUnsignedInteger")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_Double(unsigned,         v,                 args[_i++]);
  getArgAs_END

  unsigned * p = (unsigned *)(void *)(&pointer[pointerBytesFirst]);

  p[0] = v;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetAtOffsetInteger16Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/,
    APE_OBJECT_NUMBER/*value*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetAtOffsetInteger16Bit")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_Double(int16_t,          v,                 args[_i++]);
  getArgAs_END

  int16_t * p = (int16_t *)(void *)(&pointer[pointerBytesFirst]);

  p[0] = v;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetAtOffsetInteger64Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/,
    APE_OBJECT_NUMBER/*value*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetAtOffsetInteger64Bit")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_Double(int64_t,          v,                 args[_i++]);
  getArgAs_END

  int64_t * p = (int64_t *)(void *)(&pointer[pointerBytesFirst]);

  p[0] = v;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetAtOffsetUnsignedInteger16Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/,
    APE_OBJECT_NUMBER/*value*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetAtOffsetUnsignedInteger16Bit")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_Double(uint16_t,         v,                 args[_i++]);
  getArgAs_END

  uint16_t * p = (uint16_t *)(void *)(&pointer[pointerBytesFirst]);

  p[0] = v;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetAtOffsetUnsignedInteger64Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/,
    APE_OBJECT_NUMBER/*value*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetAtOffsetUnsignedInteger64Bit")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_Double(uint64_t,         v,                 args[_i++]);
  getArgAs_END

  uint64_t * p = (uint64_t *)(void *)(&pointer[pointerBytesFirst]);

  p[0] = v;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetRaw8Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*bytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetRaw8Bit")
  getArgAs_Pointer(unsigned char *, pointer, args[_i++]);
  getArgAs_Double(uint64_t,         i,       args[_i++]);
  getArgAs_END

  double number = 0;
  memcpy((void *)&number, (void *)&pointer[i], sizeof(unsigned char));

  return ape_object_make_number(number);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetRaw16Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*bytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetRaw16Bit")
  getArgAs_Pointer(unsigned char *, pointer, args[_i++]);
  getArgAs_Double(uint64_t,         i,       args[_i++]);
  getArgAs_END

  double number = 0;
  memcpy((void *)&number, (void *)&pointer[i], sizeof(uint16_t));

  return ape_object_make_number(number);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetRaw32Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*bytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetRaw32Bit")
  getArgAs_Pointer(unsigned char *, pointer, args[_i++]);
  getArgAs_Double(uint64_t,         i,       args[_i++]);
  getArgAs_END

  double number = 0;
  memcpy((void *)&number, (void *)&pointer[i], sizeof(unsigned));

  return ape_object_make_number(number);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetRaw64Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*bytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerGetRaw64Bit")
  getArgAs_Pointer(unsigned char *, pointer, args[_i++]);
  getArgAs_Double(uint64_t,         i,       args[_i++]);
  getArgAs_END

  double number = 0;
  memcpy((void *)&number, (void *)&pointer[i], sizeof(uint64_t));

  return ape_object_make_number(number);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetRaw8Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*bytesFirst*/,
    APE_OBJECT_NUMBER/*rawBitsAsDouble*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetRaw8Bit")
  getArgAs_Pointer(unsigned char *, pointer, args[_i++]);
  getArgAs_Double(uint64_t,         i,       args[_i++]);
  getArgAs_Double(double,           number,  args[_i++]);
  getArgAs_END

  memcpy((void *)&pointer[i], (void *)&number, sizeof(unsigned char));

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetRaw16Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*bytesFirst*/,
    APE_OBJECT_NUMBER/*rawBitsAsDouble*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetRaw16Bit")
  getArgAs_Pointer(unsigned char *, pointer, args[_i++]);
  getArgAs_Double(uint64_t,         i,       args[_i++]);
  getArgAs_Double(double,           number,  args[_i++]);
  getArgAs_END

  memcpy((void *)&pointer[i], (void *)&number, sizeof(uint16_t));

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetRaw32Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*bytesFirst*/,
    APE_OBJECT_NUMBER/*rawBitsAsDouble*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetRaw32Bit")
  getArgAs_Pointer(unsigned char *, pointer, args[_i++]);
  getArgAs_Double(uint64_t,         i,       args[_i++]);
  getArgAs_Double(double,           number,  args[_i++]);
  getArgAs_END

  memcpy((void *)&pointer[i], (void *)&number, sizeof(unsigned));

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerSetRaw64Bit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*bytesFirst*/,
    APE_OBJECT_NUMBER/*rawBitsAsDouble*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerSetRaw64Bit")
  getArgAs_Pointer(unsigned char *, pointer, args[_i++]);
  getArgAs_Double(uint64_t,         i,       args[_i++]);
  getArgAs_Double(double,           number,  args[_i++]);
  getArgAs_END

  memcpy((void *)&pointer[i], (void *)&number, sizeof(uint64_t));

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerIsNull GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerIsNull")
  getArgAs_Pointer(void *, pointer, args[_i++]);
  getArgAs_END

  return ape_object_make_bool(pointer == NULL);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerGetNull GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number(_gsPointerToNumber(0));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointersAreEqual GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointerA*/,
    APE_OBJECT_NUMBER/*pointerB*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointersAreEqual")
  getArgAs_Pointer(void *, pointerA, args[_i++]);
  getArgAs_Pointer(void *, pointerB, args[_i++]);
  getArgAs_END

  return ape_object_make_bool(pointerA == pointerB);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerOffsetByBytes GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*bytesOffset*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerOffsetByBytes")
  getArgAs_Pointer(unsigned char *, pointer, args[_i++]);
  getArgAs_Double(int64_t,          offset,  args[_i++]);
  getArgAs_END

  pointer += offset;

  return ape_object_make_number(_gsPointerToNumber((void *)pointer));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePointerDrawPixels GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesOffset*/,
    APE_OBJECT_NUMBER/*pixelsWidth*/,
    APE_OBJECT_NUMBER/*pixelsHeight*/,
    APE_OBJECT_NUMBER/*pixelsFormat*/,
    APE_OBJECT_NUMBER/*pixelsType*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("pointerDrawPixels")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_Double(int,              width,             args[_i++]);
  getArgAs_Double(int,              height,            args[_i++]);
  getArgAs_Double(unsigned,         format,            args[_i++]);
  getArgAs_Double(unsigned,         type,              args[_i++]);
  getArgAs_END

  void (*drawPixels)(int width, int height, unsigned format, unsigned type, void * data) = (void (*)(int, int, unsigned, unsigned, void *))glfwGetProcAddress("glDrawPixels");
  if (drawPixels != 0) {
    drawPixels(width, height, format, type, &pointer[pointerBytesFirst]);
  }

  return ape_object_make_bool(drawPixels != 0);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalDynamicArrayNew GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalDynamicArrayNew")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  {
    void * possiblyAlreadyExistingPointer = gApeGlobalDynamicArray[label];
    if (possiblyAlreadyExistingPointer != 0) {
      return ape_object_make_number(_gsPointerToNumber(possiblyAlreadyExistingPointer));
    }
  }

  std::vector<double> * pointer = new(std::nothrow) std::vector<double>();
  gApeGlobalDynamicArray[label] = pointer;

  return ape_object_make_number(_gsPointerToNumber(pointer));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalDynamicArrayPersistentNew GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalDynamicArrayPersistentNew")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  {
    void * possiblyAlreadyExistingPointer = gApeGlobalDynamicArrayPersistent[label];
    if (possiblyAlreadyExistingPointer != 0) {
      return ape_object_make_number(_gsPointerToNumber(possiblyAlreadyExistingPointer));
    }
  }

  std::vector<double> * pointer = new(std::nothrow) std::vector<double>();
  gApeGlobalDynamicArrayPersistent[label] = pointer;

  return ape_object_make_number(_gsPointerToNumber(pointer));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalDynamicArrayDelete GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalDynamicArrayDelete")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  std::vector<double> * pointer = gApeGlobalDynamicArray[label];
  delete pointer;

  gApeGlobalDynamicArray.erase(label);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalDynamicArrayPersistentDelete GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalDynamicArrayPersistentDelete")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  std::vector<double> * pointer = gApeGlobalDynamicArrayPersistent[label];
  delete pointer;

  gApeGlobalDynamicArrayPersistent.erase(label);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalDynamicArrayDeleteAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  for (auto & kv : gApeGlobalDynamicArray) {
    delete kv.second;
  }

  gApeGlobalDynamicArray.clear();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalDynamicArrayPersistentDeleteAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  for (auto & kv : gApeGlobalDynamicArrayPersistent) {
    delete kv.second;
  }

  gApeGlobalDynamicArrayPersistent.clear();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalDynamicArrayGetHandle GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalDynamicArrayGetHandle")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  return ape_object_make_number(_gsPointerToNumber(gApeGlobalDynamicArray[label]));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalDynamicArrayPersistentGetHandle GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalDynamicArrayPersistentGetHandle")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  return ape_object_make_number(_gsPointerToNumber(gApeGlobalDynamicArrayPersistent[label]));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDynamicArrayGet GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*index*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("dynamicArrayGet")
  getArgAs_Pointer(std::vector<double> *, dynamicArray, args[_i++]);
  getArgAs_Double(uint64_t,               index,        args[_i++]);
  getArgAs_END

  return ape_object_make_number(dynamicArray[0][index]);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDynamicArraySet GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*index*/,
    APE_OBJECT_NUMBER/*value*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("dynamicArraySet")
  getArgAs_Pointer(std::vector<double> *, dynamicArray, args[_i++]);
  getArgAs_Double(uint64_t,               index,        args[_i++]);
  getArgAs_Double(double,                 value,        args[_i++]);
  getArgAs_END

  dynamicArray[0][index] = value;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDynamicArrayAppend GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*value*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("dynamicArrayAppend")
  getArgAs_Pointer(std::vector<double> *, dynamicArray, args[_i++]);
  getArgAs_Double(double,                 value,        args[_i++]);
  getArgAs_END

  dynamicArray->push_back(value);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDynamicArrayRemoveAt GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*index*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("dynamicArrayRemoveAt")
  getArgAs_Pointer(std::vector<double> *, dynamicArray, args[_i++]);
  getArgAs_Double(uint64_t,               index,        args[_i++]);
  getArgAs_END

  return ape_object_make_bool(dynamicArray->erase(dynamicArray->begin() + index) != dynamicArray->end());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDynamicArrayRemoveLast GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("dynamicArrayRemoveLast")
  getArgAs_Pointer(std::vector<double> *, dynamicArray, args[_i++]);
  getArgAs_END

  dynamicArray->pop_back();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDynamicArrayGetSize GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("dynamicArrayGetSize")
  getArgAs_Pointer(std::vector<double> *, dynamicArray, args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)dynamicArray->size());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMemset GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/,
    APE_OBJECT_NUMBER/*ucharValue*/,
    APE_OBJECT_NUMBER/*bytesCount*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("memset")
  getArgAs_Pointer(unsigned char *, pointer,    args[_i++]);
  getArgAs_Double(uint64_t,         bytesFirst, args[_i++]);
  getArgAs_Double(unsigned char,    value,      args[_i++]);
  getArgAs_Double(uint64_t,         bytesCount, args[_i++]);
  getArgAs_END

  memset(&pointer[bytesFirst], value, bytesCount);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMemcpy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointerTarget*/,
    APE_OBJECT_NUMBER/*pointerTargetBytesFirst*/,
    APE_OBJECT_NUMBER/*pointerSource*/,
    APE_OBJECT_NUMBER/*pointerSourceBytesFirst*/,
    APE_OBJECT_NUMBER/*bytesCount*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("memcpy")
  getArgAs_Pointer(unsigned char *, target,           args[_i++]);
  getArgAs_Double(uint64_t,         targetBytesFirst, args[_i++]);
  getArgAs_Pointer(unsigned char *, source,           args[_i++]);
  getArgAs_Double(uint64_t,         sourceBytesFirst, args[_i++]);
  getArgAs_Double(uint64_t,         bytesCount,       args[_i++]);
  getArgAs_END

  memcpy(&target[targetBytesFirst], &source[sourceBytesFirst], bytesCount);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMemcmp GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointerA*/,
    APE_OBJECT_NUMBER/*pointerABytesFirst*/,
    APE_OBJECT_NUMBER/*pointerB*/,
    APE_OBJECT_NUMBER/*pointerBBytesFirst*/,
    APE_OBJECT_NUMBER/*bytesCount*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("memcmp")
  getArgAs_Pointer(unsigned char *, a,           args[_i++]);
  getArgAs_Double(uint64_t,         aBytesFirst, args[_i++]);
  getArgAs_Pointer(unsigned char *, b,           args[_i++]);
  getArgAs_Double(uint64_t,         bBytesFirst, args[_i++]);
  getArgAs_Double(uint64_t,         bytesCount,  args[_i++]);
  getArgAs_END

  bool result = memcmp(&a[aBytesFirst], &b[bBytesFirst], bytesCount) == 0 ? true : false;

  return ape_object_make_bool(result);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureThreadSafeMemset GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/,
    APE_OBJECT_NUMBER/*ucharValue*/,
    APE_OBJECT_NUMBER/*bytesCount*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("threadSafeMemset")
  getArgAs_Pointer(unsigned char *, pointer,    args[_i++]);
  getArgAs_Double(uint64_t,         bytesFirst, args[_i++]);
  getArgAs_Double(unsigned char,    value,      args[_i++]);
  getArgAs_Double(uint64_t,         bytesCount, args[_i++]);
  getArgAs_END

  {
    std::lock_guard<std::mutex> __thread2ThreadSafeMemoryGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_thread2ThreadSafeMemoryGuardAndSerializeMutex);
    memset(&pointer[bytesFirst], value, bytesCount);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureThreadSafeMemcpy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointerTarget*/,
    APE_OBJECT_NUMBER/*pointerTargetBytesFirst*/,
    APE_OBJECT_NUMBER/*pointerSource*/,
    APE_OBJECT_NUMBER/*pointerSourceBytesFirst*/,
    APE_OBJECT_NUMBER/*bytesCount*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("threadSafeMemcpy")
  getArgAs_Pointer(unsigned char *, target,           args[_i++]);
  getArgAs_Double(uint64_t,         targetBytesFirst, args[_i++]);
  getArgAs_Pointer(unsigned char *, source,           args[_i++]);
  getArgAs_Double(uint64_t,         sourceBytesFirst, args[_i++]);
  getArgAs_Double(uint64_t,         bytesCount,       args[_i++]);
  getArgAs_END

  {
    std::lock_guard<std::mutex> __thread2ThreadSafeMemoryGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_thread2ThreadSafeMemoryGuardAndSerializeMutex);
    memcpy(&target[targetBytesFirst], &source[sourceBytesFirst], bytesCount);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureThreadSafeMemcmp GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointerA*/,
    APE_OBJECT_NUMBER/*pointerABytesFirst*/,
    APE_OBJECT_NUMBER/*pointerB*/,
    APE_OBJECT_NUMBER/*pointerBBytesFirst*/,
    APE_OBJECT_NUMBER/*bytesCount*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("threadSafeMemcmp")
  getArgAs_Pointer(unsigned char *, a,           args[_i++]);
  getArgAs_Double(uint64_t,         aBytesFirst, args[_i++]);
  getArgAs_Pointer(unsigned char *, b,           args[_i++]);
  getArgAs_Double(uint64_t,         bBytesFirst, args[_i++]);
  getArgAs_Double(uint64_t,         bytesCount,  args[_i++]);
  getArgAs_END

  volatile bool result = false;
  {
    std::lock_guard<std::mutex> __thread2ThreadSafeMemoryGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_thread2ThreadSafeMemoryGuardAndSerializeMutex);
    result = memcmp(&a[aBytesFirst], &b[bBytesFirst], bytesCount) == 0 ? true : false;
  }

  return ape_object_make_bool(result);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureThreadWaitForEqualUint64Value GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointerA*/,
    APE_OBJECT_NUMBER/*pointerABytesFirst*/,
    APE_OBJECT_NUMBER/*pointerB*/,
    APE_OBJECT_NUMBER/*pointerBBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("threadWaitForEqualUint64Value")
  getArgAs_Pointer(unsigned char *, pointerA,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerABytesFirst, args[_i++]);
  getArgAs_Pointer(unsigned char *, pointerB,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBBytesFirst, args[_i++]);
  getArgAs_END

  volatile uint64_t * a = (volatile uint64_t *)(void *)&pointerA[pointerABytesFirst];
  volatile uint64_t * b = (volatile uint64_t *)(void *)&pointerB[pointerBBytesFirst];

  std::string profileMarkString;
  profileMarkString += "threadWaitForEqualUint64Value initial values, pointerA: ";
  profileMarkString += std::to_string(a[0]);
  profileMarkString += " == pointerB: ";
  profileMarkString += std::to_string(b[0]);
  profileBegin(profileMarkString.c_str());

  while (a[0] != b[0] && gThread2StopSignal == 0) {
#if defined(_WIN32)
    _mm_pause();
#else
    __asm __volatile("pause");
#endif
  }

  profileEnd(profileMarkString.c_str());

  return ape_object_make_bool(gThread2StopSignal == 0 ? true : false);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureThreadWaitForEqualOrMoreThanUint64Value GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointerA*/,
    APE_OBJECT_NUMBER/*pointerABytesFirst*/,
    APE_OBJECT_NUMBER/*pointerB*/,
    APE_OBJECT_NUMBER/*pointerBBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("threadWaitForEqualOrMoreThanUint64Value")
  getArgAs_Pointer(unsigned char *, pointerA,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerABytesFirst, args[_i++]);
  getArgAs_Pointer(unsigned char *, pointerB,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBBytesFirst, args[_i++]);
  getArgAs_END

  volatile uint64_t * a = (volatile uint64_t *)(void *)&pointerA[pointerABytesFirst];
  volatile uint64_t * b = (volatile uint64_t *)(void *)&pointerB[pointerBBytesFirst];

  std::string profileMarkString;
  profileMarkString += "threadWaitForEqualOrMoreThanUint64Value initial values, pointerA: ";
  profileMarkString += std::to_string(a[0]);
  profileMarkString += " >= pointerB: ";
  profileMarkString += std::to_string(b[0]);
  profileBegin(profileMarkString.c_str());

  while (a[0] < b[0] && gThread2StopSignal == 0) {
#if defined(_WIN32)
    _mm_pause();
#else
    __asm __volatile("pause");
#endif
  }

  profileEnd(profileMarkString.c_str());

  return ape_object_make_bool(gThread2StopSignal == 0 ? true : false);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureThreadWaitForThread2FrameToFinish GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*waitForThread2Frame*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("threadWaitForThread2FrameToFinish")
  getArgAs_Double(uint64_t, waitForThread2Frame, args[_i++]);
  getArgAs_END

  std::string profileMarkString;
  profileMarkString += "threadWaitForThread2FrameToFinish, waiting for frame: ";
  profileMarkString += std::to_string(waitForThread2Frame);
  profileBegin(profileMarkString.c_str());

  while (gCurrentFrameThread2 <= waitForThread2Frame && gThread2StopSignal == 0) {
#if defined(_WIN32)
    _mm_pause();
#else
    __asm __volatile("pause");
#endif
  }

  profileEnd(profileMarkString.c_str());

  return ape_object_make_bool(gThread2StopSignal == 0 ? true : false);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureThreadWaitForThread1FrameToFinish GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*waitForThread1Frame*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("threadWaitForThread1FrameToFinish")
  getArgAs_Double(uint64_t, waitForThread1Frame, args[_i++]);
  getArgAs_END

  std::string profileMarkString;
  profileMarkString += "threadWaitForThread1FrameToFinish, waiting for frame: ";
  profileMarkString += std::to_string(waitForThread1Frame);
  profileBegin(profileMarkString.c_str());

  while (gCurrentFrame <= waitForThread1Frame && gThread2StopSignal == 0) {
#if defined(_WIN32)
    _mm_pause();
#else
    __asm __volatile("pause");
#endif
  }

  profileEnd(profileMarkString.c_str());

  return ape_object_make_bool(gThread2StopSignal == 0 ? true : false);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureStrlenWithNullChar GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*string*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("strlenWithNullChar")
  getArgAs_CChars(const char *, astring, args[_i++]);
  getArgAs_END

  if (astring == NULL) {
    return ape_object_make_number(0.0);
  }

  return ape_object_make_number((double)(strlen(astring) + 1));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureKeyboardGetGlfwKeyEvent GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*keycode*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("keyboardGetGlfwKeyEvent")
  getArgAs_Double(int, keycode, args[_i++]);
  getArgAs_END

  int event = 0;
  if (gGameMode == 1) {
    event = gGlfwKeyEvent[keycode];
  }

  return ape_object_make_number((double)event);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureKeyboardGetGlfwKeyModifiers GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*keycode*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("keyboardGetGlfwKeyModifiers")
  getArgAs_Double(int, keycode, args[_i++]);
  getArgAs_END

  int modifiers = 0;
  if (gGameMode == 1) {
    modifiers = gGlfwKeyModifiers[keycode];
  }

  return ape_object_make_number((double)modifiers);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureKeyboardGetGlfwCodepointString GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  unsigned codepoint = 0;
  if (gGameMode == 1) {
    codepoint = gGlfwCodepointCharacter;
  }

  char codepointString[2] = {};
  if (codepoint != 0) {
    codepointString[0] = (char)codepoint;
  }

  return ape_object_make_string(ape, codepointString);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMouseGlfwSetInputMode GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*mode*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("mouseGlfwSetInputMode")
  getArgAs_Double(int, mode, args[_i++]);
  getArgAs_END

  if (mode < 0 || mode > 2) {
    return ape_object_make_null();
  }

  const int modes[3] = {
    GLFW_CURSOR_NORMAL,
    GLFW_CURSOR_HIDDEN,
    GLFW_CURSOR_DISABLED,
  };

  if (gGameMode == 1) {
    glfwSetInputMode((GLFWwindow *)redFGetGLFWwindowPointer(), GLFW_CURSOR, modes[mode]);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMouseSetXY GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("mouseSetXY")
  getArgAs_Double(double, x, args[_i++]);
  getArgAs_Double(double, y, args[_i++]);
  getArgAs_END

  if (gGameMode == 1) {
    glfwSetCursorPos((GLFWwindow *)redFGetGLFWwindowPointer(), x, y);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMouseGetX GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  double v = 0;
  if (gGameMode == 1) {
    v = (double)redFGetMouseX();
  }

  return ape_object_make_number(v);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMouseGetY GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  double v = 0;
  if (gGameMode == 1) {
    v = (double)redFGetMouseY();
  }

  return ape_object_make_number(v);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMouseGetPreviousX GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  double v = 0;
  if (gGameMode == 1) {
    v = (double)redFGetPreviousMouseX();
  }

  return ape_object_make_number(v);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMouseGetPreviousY GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  double v = 0;
  if (gGameMode == 1) {
    v = (double)redFGetPreviousMouseY();
  }

  return ape_object_make_number(v);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMouseGetMoveEvent GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  unsigned mouseEvent = 0;
  if (gGameMode == 1) {
    mouseEvent = gMouseEvent;
  }

  return ape_object_make_number((double)mouseEvent);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMouseGetButtonIsPressed GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*button*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("mouseGetButtonIsPressed")
  getArgAs_Double(int, button, args[_i++]);
  getArgAs_END

  if (button < 0 || button > 7) {
    return ape_object_make_bool(false);
  }

  int isPressed = 0;
  if (gGameMode == 1) {
    isPressed = gMouseButtonIsPressed[button];
  }

  return ape_object_make_bool((bool)isPressed);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMouseGetButtonIsPressedAndHeld GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*button*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("mouseGetButtonIsPressedAndHeld")
  getArgAs_Double(int, button, args[_i++]);
  getArgAs_END

  if (button < 0 || button > 7) {
    return ape_object_make_bool(false);
  }

  RedFBool32 isPressed = 0;
  if (gGameMode == 1) {
    isPressed = redFGetMousePressed(button);
  }

  return ape_object_make_bool((bool)isPressed);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMouseGetButtonIsReleased GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*button*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("mouseGetButtonIsReleased")
  getArgAs_Double(int, button, args[_i++]);
  getArgAs_END

  if (button < 0 || button > 7) {
    return ape_object_make_bool(false);
  }

  int isReleased = 0;
  if (gGameMode == 1) {
    isReleased = gMouseButtonIsReleased[button];
  }

  return ape_object_make_bool((bool)isReleased);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMouseGetWheelScroll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  float wheelScroll = 0;
  if (gGameMode == 1) {
    wheelScroll = gMouseWheelScroll;
  }

  return ape_object_make_number((double)wheelScroll);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGamepadIsPresent GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*gamepadId0to15*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("gamepadIsPresent")
  getArgAs_Double(int, gamepadId, args[_i++]);
  getArgAs_END

  return ape_object_make_bool((bool)glfwJoystickIsGamepad(gamepadId));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGamepadGet15Buttons6AxesNumbers GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*gamepadId0to15*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("gamepadGet15Buttons6AxesNumbers")
  getArgAs_Double(int, gamepadId, args[_i++]);
  getArgAs_END

  GLFWgamepadstate state = {};
  int status = glfwGetGamepadState(gamepadId, &state);

  ape_object_t array = mape_object_make_array(ape, 21);
  mape_object_add_array_number(0,  array, (double)state.buttons[0]);
  mape_object_add_array_number(1,  array, (double)state.buttons[1]);
  mape_object_add_array_number(2,  array, (double)state.buttons[2]);
  mape_object_add_array_number(3,  array, (double)state.buttons[3]);
  mape_object_add_array_number(4,  array, (double)state.buttons[4]);
  mape_object_add_array_number(5,  array, (double)state.buttons[5]);
  mape_object_add_array_number(6,  array, (double)state.buttons[6]);
  mape_object_add_array_number(7,  array, (double)state.buttons[7]);
  mape_object_add_array_number(8,  array, (double)state.buttons[8]);
  mape_object_add_array_number(9,  array, (double)state.buttons[9]);
  mape_object_add_array_number(10, array, (double)state.buttons[10]);
  mape_object_add_array_number(11, array, (double)state.buttons[11]);
  mape_object_add_array_number(12, array, (double)state.buttons[12]);
  mape_object_add_array_number(13, array, (double)state.buttons[13]);
  mape_object_add_array_number(14, array, (double)state.buttons[14]);
  mape_object_add_array_number(15, array, (double)state.axes[0]);
  mape_object_add_array_number(16, array, (double)state.axes[1]);
  mape_object_add_array_number(17, array, (double)state.axes[2]);
  mape_object_add_array_number(18, array, (double)state.axes[3]);
  mape_object_add_array_number(19, array, (double)state.axes[4]);
  mape_object_add_array_number(20, array, (double)state.axes[5]);
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGamepadGetName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*gamepadId0to15*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("gamepadGetName")
  getArgAs_Double(int, gamepadId, args[_i++]);
  getArgAs_END

  return ape_object_make_string(ape, glfwGetGamepadName(gamepadId));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGamepadGetGUID GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*gamepadId0to15*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("gamepadGetGUID")
  getArgAs_Double(int, gamepadId, args[_i++]);
  getArgAs_END

  return ape_object_make_string(ape, glfwGetJoystickGUID(gamepadId));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGamepadUpdateGamecontrollerdbTxt GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*gamepadId0to15*/,
    APE_OBJECT_STRING/*mappings*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("gamepadUpdateGamecontrollerdbTxt")
  getArgAs_Double(int,          gamepadId, args[_i++]);
  getArgAs_CChars(const char *, mappings,  args[_i++]);
  getArgAs_END

  return ape_object_make_bool((bool)glfwUpdateGamepadMappings(mappings));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureBoolToNumber GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_BOOL/*boolean*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("boolToNumber")
  getArgAs_Bool(int, boolean, args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)boolean);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureBoolToString GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_BOOL/*boolean*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("boolToString")
  getArgAs_Bool(int, boolean, args[_i++]);
  getArgAs_END

  std::string boolToString = std::to_string(boolean);

  return ape_object_make_string(ape, boolToString.c_str());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureNumberFromRaw8BitInteger GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*raw8BitInteger*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("numberFromRaw8BitInteger")
  getArgAs_Double(double, raw, args[_i++]);
  getArgAs_END

  GsInternalUnionConverter c;
  c.number = raw;
  return ape_object_make_number((double)c.integer8Bit);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureNumberFromRaw8BitUnsignedInteger GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*raw8BitUnsignedInteger*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("numberFromRaw8BitUnsignedInteger")
  getArgAs_Double(double, raw, args[_i++]);
  getArgAs_END

  GsInternalUnionConverter c;
  c.number = raw;
  return ape_object_make_number((double)c.unsignedInteger8Bit);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureNumberFromRaw16BitInteger GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*raw16BitInteger*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("numberFromRaw16BitInteger")
  getArgAs_Double(double, raw, args[_i++]);
  getArgAs_END

  GsInternalUnionConverter c;
  c.number = raw;
  return ape_object_make_number((double)c.integer16Bit);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureNumberFromRaw16BitUnsignedInteger GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*raw16BitUnsignedInteger*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("numberFromRaw16BitUnsignedInteger")
  getArgAs_Double(double, raw, args[_i++]);
  getArgAs_END

  GsInternalUnionConverter c;
  c.number = raw;
  return ape_object_make_number((double)c.unsignedInteger16Bit);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureNumberFromRaw32BitInteger GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*raw32BitInteger*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("numberFromRaw32BitInteger")
  getArgAs_Double(double, raw, args[_i++]);
  getArgAs_END

  GsInternalUnionConverter c;
  c.number = raw;
  return ape_object_make_number((double)c.integer);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureNumberFromRaw32BitUnsignedInteger GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*raw32BitUnsignedInteger*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("numberFromRaw32BitUnsignedInteger")
  getArgAs_Double(double, raw, args[_i++]);
  getArgAs_END

  GsInternalUnionConverter c;
  c.number = raw;
  return ape_object_make_number((double)c.unsignedInteger);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureNumberFromRaw32BitFloat GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*raw32BitFloat*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("numberFromRaw32BitFloat")
  getArgAs_Double(double, raw, args[_i++]);
  getArgAs_END

  GsInternalUnionConverter c;
  c.number = raw;
  return ape_object_make_number((double)c.afloat);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureNumberFromRaw64BitInteger GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*raw64BitInteger*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("numberFromRaw64BitInteger")
  getArgAs_Double(double, raw, args[_i++]);
  getArgAs_END

  GsInternalUnionConverter c;
  c.number = raw;
  return ape_object_make_number((double)c.integer64Bit);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureNumberFromRaw64BitUnsignedInteger GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*raw64BitUnsignedInteger*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("numberFromRaw64BitUnsignedInteger")
  getArgAs_Double(double, raw, args[_i++]);
  getArgAs_END

  GsInternalUnionConverter c;
  c.number = raw;
  return ape_object_make_number((double)c.unsignedInteger64Bit);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureNumberToBool GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*number*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("numberToBool")
  getArgAs_Double(double, number, args[_i++]);
  getArgAs_END

  return ape_object_make_bool(number == 0 ? false : true);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureNumberToString GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*number*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("numberToString")
  getArgAs_Double(double, number, args[_i++]);
  getArgAs_END

  std::string numberToString = std::to_string(number);

  return ape_object_make_string(ape, numberToString.c_str());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureNumberToBinaryString GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*number*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("numberToBinaryString")
  getArgAs_Double(double, number, args[_i++]);
  getArgAs_END

  uint64_t b = ((uint64_t *)(void *)&number)[0];

  char char65[65];
  char65[0]  = (b & REDGPU_B64(1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[1]  = (b & REDGPU_B64(0100,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[2]  = (b & REDGPU_B64(0010,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[3]  = (b & REDGPU_B64(0001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[4]  = (b & REDGPU_B64(0000,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[5]  = (b & REDGPU_B64(0000,0100,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[6]  = (b & REDGPU_B64(0000,0010,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[7]  = (b & REDGPU_B64(0000,0001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[8]  = (b & REDGPU_B64(0000,0000,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[9]  = (b & REDGPU_B64(0000,0000,0100,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[10] = (b & REDGPU_B64(0000,0000,0010,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[11] = (b & REDGPU_B64(0000,0000,0001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[12] = (b & REDGPU_B64(0000,0000,0000,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[13] = (b & REDGPU_B64(0000,0000,0000,0100,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[14] = (b & REDGPU_B64(0000,0000,0000,0010,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[15] = (b & REDGPU_B64(0000,0000,0000,0001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[16] = (b & REDGPU_B64(0000,0000,0000,0000,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[17] = (b & REDGPU_B64(0000,0000,0000,0000,0100,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[18] = (b & REDGPU_B64(0000,0000,0000,0000,0010,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[19] = (b & REDGPU_B64(0000,0000,0000,0000,0001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[20] = (b & REDGPU_B64(0000,0000,0000,0000,0000,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[21] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0100,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[22] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0010,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[23] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[24] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[25] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0100,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[26] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0010,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[27] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0001,0000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[28] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,1000,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[29] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0100,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[30] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0010,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[31] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0001,0000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[32] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,1000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[33] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0100,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[34] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0010,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[35] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0001,0000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[36] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,1000,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[37] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0100,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[38] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0010,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[39] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0001,0000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[40] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,1000,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[41] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0100,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[42] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0010,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[43] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0001,0000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[44] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,1000,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[45] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0100,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[46] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0010,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[47] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0001,0000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[48] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,1000,0000,0000,0000)) == 0 ? '0' : '1';
  char65[49] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0100,0000,0000,0000)) == 0 ? '0' : '1';
  char65[50] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0010,0000,0000,0000)) == 0 ? '0' : '1';
  char65[51] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0001,0000,0000,0000)) == 0 ? '0' : '1';
  char65[52] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,1000,0000,0000)) == 0 ? '0' : '1';
  char65[53] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0100,0000,0000)) == 0 ? '0' : '1';
  char65[54] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0010,0000,0000)) == 0 ? '0' : '1';
  char65[55] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0001,0000,0000)) == 0 ? '0' : '1';
  char65[56] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,1000,0000)) == 0 ? '0' : '1';
  char65[57] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0100,0000)) == 0 ? '0' : '1';
  char65[58] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0010,0000)) == 0 ? '0' : '1';
  char65[59] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0001,0000)) == 0 ? '0' : '1';
  char65[60] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,1000)) == 0 ? '0' : '1';
  char65[61] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0100)) == 0 ? '0' : '1';
  char65[62] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0010)) == 0 ? '0' : '1';
  char65[63] = (b & REDGPU_B64(0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0001)) == 0 ? '0' : '1';
  char65[64] = 0;

  return ape_object_make_string(ape, char65);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureNumberWholePartToString GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*number*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("numberWholePartToString")
  getArgAs_Double(int64_t, number, args[_i++]);
  getArgAs_END

  std::string numberToString = std::to_string(number);

  return ape_object_make_string(ape, numberToString.c_str());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureStringCharToNumber GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*string*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("stringCharToNumber")
  getArgAs_CChars(const char *, astring, args[_i++]);
  getArgAs_END

  if (astring == 0) {
    return ape_object_make_number(0.0);
  } else {
    return ape_object_make_number((double)astring[0]);
  }
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureStringToNumberArray GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*string*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("stringToNumberArray")
  getArgAs_String(std::string, astring, args[_i++]);
  getArgAs_END

  ape_object_t array = mape_object_make_array(ape, astring.length() + 1);
  for (size_t i = 0, count = astring.length(); i < count; i += 1) {
    mape_object_add_array_number(i, array, (double)astring[i]);
  }
  mape_object_add_array_number(astring.length(), array, 0.0);
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureInterpretStringToInteger GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*string*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("interpretStringToInteger")
  getArgAs_CChars(const char *, astring, args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)std::stoi(astring));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureInterpretStringToFloat GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*string*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("interpretStringToFloat")
  getArgAs_CChars(const char *, astring, args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)std::stof(astring));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureInterpretStringToDouble GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*string*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("interpretStringToDouble")
  getArgAs_CChars(const char *, astring, args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)std::stod(astring));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureStringReadFromFile GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*filepath*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("stringReadFromFile")
  getArgAs_CChars(const char *, filepath, args[_i++]);
  getArgAs_END

  std::ostringstream ss;
  ss << std::ifstream(filepath).rdbuf();
  std::string s = ss.str();

  return ape_object_make_string(ape, s.c_str());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureStringWriteToFile GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*string*/,
    APE_OBJECT_STRING/*filepath*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("stringWriteToFile")
  getArgAs_CChars(const char *, s,        args[_i++]);
  getArgAs_CChars(const char *, filepath, args[_i++]);
  getArgAs_END

  std::ofstream fs(filepath, std::ofstream::out);
  fs << s;
  fs.close();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureStringAppendToFile GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*string*/,
    APE_OBJECT_STRING/*filepath*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("stringAppendToFile")
  getArgAs_CChars(const char *, s,        args[_i++]);
  getArgAs_CChars(const char *, filepath, args[_i++]);
  getArgAs_END

  std::ofstream fs(filepath, std::ofstream::app);
  fs << s;
  fs.close();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureBinaryGetByteSizeOfFile GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*filepath*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("binaryGetByteSizeOfFile")
  getArgAs_CChars(const char *, filepath, args[_i++]);
  getArgAs_END

  std::ifstream fs(filepath, std::ifstream::binary | std::ifstream::ate);
  double bytesCount = (double)fs.tellg();
  fs.close();

  return ape_object_make_number(bytesCount);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureBinaryReadFromFile GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*filepath*/,
    APE_OBJECT_NUMBER/*writeToPointer*/,
    APE_OBJECT_NUMBER/*writeToPointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("binaryReadFromFile")
  getArgAs_CChars(const char *,     filepath,   args[_i++]);
  getArgAs_Pointer(unsigned char *, pointer,    args[_i++]);
  getArgAs_Double(uint64_t,         bytesFirst, args[_i++]);
  getArgAs_END

  std::ifstream fs(filepath, std::ifstream::binary);
  std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(fs), {});
  memcpy((void *)&pointer[bytesFirst], &buffer[0], buffer.size());
  fs.close();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureBinaryWriteToFile GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/,
    APE_OBJECT_NUMBER/*pointerBytesCount*/,
    APE_OBJECT_STRING/*writeToFilepath*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("binaryWriteToFile")
  getArgAs_Pointer(const char *, pointer,    args[_i++]);
  getArgAs_Double(uint64_t,      bytesFirst, args[_i++]);
  getArgAs_Double(uint64_t,      bytesCount, args[_i++]);
  getArgAs_CChars(const char *,  filepath,   args[_i++]);
  getArgAs_END

  std::ofstream fs(filepath, std::ofstream::binary | std::ofstream::out);
  fs.write(&pointer[bytesFirst], bytesCount);
  fs.close();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetClipboardString GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  redFFree(gClipboard);
  redFGetClipboardStringChars(&gClipboard, 0);

  return ape_object_make_string(ape, gClipboard);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSetClipboardString GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*clipboard*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("setClipboardString")
  getArgAs_CChars(const char *, clipboard, args[_i++]);
  getArgAs_END

  redFSetClipboardString(clipboard);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGizmoSetMode GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*mode*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("gizmoSetMode")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_Double(int,         mode,  args[_i++]);
  getArgAs_END

  RedFHandleManipulator * handle = gApeGizmos[label];
  if (handle == 0) {
    handle = redFCreateManipulator(1);
    if (handle == 0) {
      return ape_object_make_null();
    }
    gApeGizmos[label] = handle;
  }

  if (mode == 1 || mode == 2 || mode == 3) {
    redFManipulatorEnable(handle[0]);
  } else {
    redFManipulatorDisable(handle[0]);
  }

  if (mode == 1) {
    redFManipulatorSetManipulatorType(handle[0], REDF_MANIPULATOR_TYPE_TRANSLATION);
  } else if (mode == 2) {
    redFManipulatorSetManipulatorType(handle[0], REDF_MANIPULATOR_TYPE_ROTATION);
  } else if (mode == 3){
    redFManipulatorSetManipulatorType(handle[0], REDF_MANIPULATOR_TYPE_SCALE);
  } else {
    redFManipulatorSetManipulatorType(handle[0], REDF_MANIPULATOR_TYPE_NONE);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGizmoGetVector GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("gizmoGetVector")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleManipulator * handle = gApeGizmos[label];
  if (handle == 0) {
    handle = redFCreateManipulator(1);
    if (handle == 0) {
      ape_object_t array = mape_object_make_array(ape, 3);
      mape_object_add_array_number(0, array, 0.0);
      mape_object_add_array_number(1, array, 0.0);
      mape_object_add_array_number(2, array, 0.0);
      return array;
    }
    gApeGizmos[label] = handle;
  }

  float vector3[3];
  redFManipulatorGetTranslation(handle[0], vector3);

  ape_object_t array = mape_object_make_array(ape, 3);
  mape_object_add_array_number(0, array, (double)vector3[0]);
  mape_object_add_array_number(1, array, (double)vector3[1]);
  mape_object_add_array_number(2, array, (double)vector3[2]);
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGizmoGetVersor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("gizmoGetVersor")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleManipulator * handle = gApeGizmos[label];
  if (handle == 0) {
    handle = redFCreateManipulator(1);
    if (handle == 0) {
      ape_object_t array = mape_object_make_array(ape, 4);
      mape_object_add_array_number(0, array, 0.0);
      mape_object_add_array_number(1, array, 0.0);
      mape_object_add_array_number(2, array, 0.0);
      mape_object_add_array_number(3, array, 0.0);
      return array;
    }
    gApeGizmos[label] = handle;
  }

  float versor4[4];
  redFManipulatorGetRotationQuaternion(handle[0], versor4);

  ape_object_t array = mape_object_make_array(ape, 4);
  mape_object_add_array_number(0, array, (double)versor4[0]);
  mape_object_add_array_number(1, array, (double)versor4[1]);
  mape_object_add_array_number(2, array, (double)versor4[2]);
  mape_object_add_array_number(3, array, (double)versor4[3]);
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGizmoGetScale GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("gizmoGetScale")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleManipulator * handle = gApeGizmos[label];
  if (handle == 0) {
    handle = redFCreateManipulator(1);
    if (handle == 0) {
      ape_object_t array = mape_object_make_array(ape, 3);
      mape_object_add_array_number(0, array, 0.0);
      mape_object_add_array_number(1, array, 0.0);
      mape_object_add_array_number(2, array, 0.0);
      return array;
    }
    gApeGizmos[label] = handle;
  }

  float vector3[3];
  redFManipulatorGetScale(handle[0], vector3);

  ape_object_t array = mape_object_make_array(ape, 3);
  mape_object_add_array_number(0, array, (double)vector3[0]);
  mape_object_add_array_number(1, array, (double)vector3[1]);
  mape_object_add_array_number(2, array, (double)vector3[2]);
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGizmoSetVector GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("gizmoSetVector")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_Double(float,       x,     args[_i++]);
  getArgAs_Double(float,       y,     args[_i++]);
  getArgAs_Double(float,       z,     args[_i++]);
  getArgAs_END

  RedFHandleManipulator * handle = gApeGizmos[label];
  if (handle == 0) {
    handle = redFCreateManipulator(1);
    if (handle == 0) {
      return ape_object_make_null();
    }
    gApeGizmos[label] = handle;
  }

  redFManipulatorSetTranslation(handle[0], x, y, z);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGizmoSetVersor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/,
    APE_OBJECT_NUMBER/*w*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("gizmoSetVersor")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_Double(float,       x,     args[_i++]);
  getArgAs_Double(float,       y,     args[_i++]);
  getArgAs_Double(float,       z,     args[_i++]);
  getArgAs_Double(float,       w,     args[_i++]);
  getArgAs_END

  RedFHandleManipulator * handle = gApeGizmos[label];
  if (handle == 0) {
    handle = redFCreateManipulator(1);
    if (handle == 0) {
      return ape_object_make_null();
    }
    gApeGizmos[label] = handle;
  }

  redFManipulatorSetRotation(handle[0], x, y, z, w);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGizmoSetScale GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("gizmoSetScale")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_Double(float,       x,     args[_i++]);
  getArgAs_Double(float,       y,     args[_i++]);
  getArgAs_Double(float,       z,     args[_i++]);
  getArgAs_END

  RedFHandleManipulator * handle = gApeGizmos[label];
  if (handle == 0) {
    handle = redFCreateManipulator(1);
    if (handle == 0) {
      return ape_object_make_null();
    }
    gApeGizmos[label] = handle;
  }

  redFManipulatorSetScale(handle[0], x, y, z);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGizmoSetDrawScale GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*scale*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("gizmoSetDrawScale")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_Double(float,       scale, args[_i++]);
  getArgAs_END

  RedFHandleManipulator * handle = gApeGizmos[label];
  if (handle == 0) {
    handle = redFCreateManipulator(1);
    if (handle == 0) {
      return ape_object_make_null();
    }
    gApeGizmos[label] = handle;
  }

  redFManipulatorSetManipulatorScale(handle[0], scale);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGizmoSetDrawColors GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*xr*/,
    APE_OBJECT_NUMBER/*xg*/,
    APE_OBJECT_NUMBER/*xb*/,
    APE_OBJECT_NUMBER/*xa*/,
    APE_OBJECT_NUMBER/*yr*/,
    APE_OBJECT_NUMBER/*yg*/,
    APE_OBJECT_NUMBER/*yb*/,
    APE_OBJECT_NUMBER/*ya*/,
    APE_OBJECT_NUMBER/*zr*/,
    APE_OBJECT_NUMBER/*zg*/,
    APE_OBJECT_NUMBER/*zb*/,
    APE_OBJECT_NUMBER/*za*/,
    APE_OBJECT_NUMBER/*wr*/,
    APE_OBJECT_NUMBER/*wg*/,
    APE_OBJECT_NUMBER/*wb*/,
    APE_OBJECT_NUMBER/*wa*/,
    APE_OBJECT_NUMBER/*selectr*/,
    APE_OBJECT_NUMBER/*selectg*/,
    APE_OBJECT_NUMBER/*selectb*/,
    APE_OBJECT_NUMBER/*selecta*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("gizmoSetDrawColors")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_Double(int,         xr,    args[_i++]);
  getArgAs_Double(int,         xg,    args[_i++]);
  getArgAs_Double(int,         xb,    args[_i++]);
  getArgAs_Double(int,         xa,    args[_i++]);
  getArgAs_Double(int,         yr,    args[_i++]);
  getArgAs_Double(int,         yg,    args[_i++]);
  getArgAs_Double(int,         yb,    args[_i++]);
  getArgAs_Double(int,         ya,    args[_i++]);
  getArgAs_Double(int,         zr,    args[_i++]);
  getArgAs_Double(int,         zg,    args[_i++]);
  getArgAs_Double(int,         zb,    args[_i++]);
  getArgAs_Double(int,         za,    args[_i++]);
  getArgAs_Double(int,         wr,    args[_i++]);
  getArgAs_Double(int,         wg,    args[_i++]);
  getArgAs_Double(int,         wb,    args[_i++]);
  getArgAs_Double(int,         wa,    args[_i++]);
  getArgAs_Double(int,         sr,    args[_i++]);
  getArgAs_Double(int,         sg,    args[_i++]);
  getArgAs_Double(int,         sb,    args[_i++]);
  getArgAs_Double(int,         sa,    args[_i++]);
  getArgAs_END

  RedFHandleManipulator * handle = gApeGizmos[label];
  if (handle == 0) {
    handle = redFCreateManipulator(1);
    if (handle == 0) {
      return ape_object_make_null();
    }
    gApeGizmos[label] = handle;
  }

  redFManipulatorSetManipulatorColors(handle[0], xr, xg, xb, xa, yr, yg, yb, ya, zr, zg, zb, za, wr, wg, wb, wa, sr, sg, sb, sa);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGizmoDelete GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("gizmoDelete")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleManipulator * handle = gApeGizmos[label];
  redFDestroyManipulator(handle);

  gApeGizmos.erase(label);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGizmoDeleteAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  for (auto & kv : gApeGizmos) {
    redFDestroyManipulator(kv.second);
  }

  gApeGizmos.clear();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetLastFrameTime GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number(redFGetLastFrameTime());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetSystemTimeMillis GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)redFGetSystemTimeMillis());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetSystemTimeMicros GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)redFGetSystemTimeMicros());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetUnixTime GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)redFGetUnixTime());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFramebufferBegin GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*width*/,
    APE_OBJECT_NUMBER/*height*/,
    APE_OBJECT_BOOL/*setupScreenDefaultIs1*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("framebufferBegin")
  getArgAs_String(std::string, label,                 args[_i++]);
  getArgAs_Double(int,         width,                 args[_i++]);
  getArgAs_Double(int,         height,                args[_i++]);
  getArgAs_Bool(bool,          setupScreenDefaultIs1, args[_i++]);
  getArgAs_END

  RedFHandleFbo * handle = gApeFbos[label];
  if (handle == 0) {
    handle = redFCreateFbo(1);
    if (handle != 0) {
      gApeFbos[label] = handle;
      redFFboAllocate(handle[0], width, height, MSAA_SAMPLES_COUNT, 0);
      redFFboSetTextureMinMagFilter(handle[0], 0, GL_LINEAR, GL_LINEAR);
    }
  }

  if (handle != 0) {
    redFPushStyle();
    redFFboBegin(handle[0], (RedFBool32)setupScreenDefaultIs1);
    redFFirstPersonCameraBegin(gCamera[0]);
  }

  return ape_object_make_bool(handle != 0);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFramebufferEnd GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("framebufferEnd")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleFbo * handle = gApeFbos[label];

  if (handle != 0) {
    redFFirstPersonCameraEnd(gCamera[0]);
    redFFboEnd(handle[0]);
    redFPopStyle();
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFramebufferDraw GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*width*/,
    APE_OBJECT_NUMBER/*height*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("framebufferDraw")
  getArgAs_String(std::string, label,  args[_i++]);
  getArgAs_Double(float,       x,      args[_i++]);
  getArgAs_Double(float,       y,      args[_i++]);
  getArgAs_Double(float,       width,  args[_i++]);
  getArgAs_Double(float,       height, args[_i++]);
  getArgAs_END

  RedFHandleFbo * handle = gApeFbos[label];

  if (handle != 0) {
    ApeDrawFbo draw;
    draw.handle = handle[0];
    draw.x      = x;
    draw.y      = y;
    draw.width  = width;
    draw.height = height;
    gApeDrawFbos.push_back(draw);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFramebufferClear GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("framebufferClear")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleFbo * handle = gApeFbos[label];

  if (handle != 0) {
    redFFboClear(handle[0]);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFramebufferCopyToImage GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*image*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("framebufferCopyToImage")
  getArgAs_String(std::string,        label,       args[_i++]);
  getArgAs_Pointer(RedFHandleImage *, imageHandle, args[_i++]);
  getArgAs_END

  RedFHandleFbo * handle = gApeFbos[label];

  if (handle != 0) {
    redFFboReadToImage(handle[0], 0, imageHandle[0]);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFramebufferDelete GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("framebufferDelete")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleFbo * handle = gApeFbos[label];
  redFDestroyFbo(handle);

  gApeFbos.erase(label);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFramebufferDeleteAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  for (auto & kv : gApeFbos) {
    redFDestroyFbo(kv.second);
  }

  gApeFbos.clear();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshNew GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshNew")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleMesh * handles = gApeMeshes[label];
  if (handles == 0) {
    handles = redFCreateMesh(1);
    if (handles != 0) {
      gApeMeshes[label] = handles;
    }
  }

  RedFHandleMesh handle = 0;
  if (handles != 0) {
    handle = handles[0];
  }

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshPersistentNew GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshPersistentNew")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleMesh * handles = gApeMeshesPersistent[label];
  if (handles == 0) {
    handles = redFCreateMesh(1);
    if (handles != 0) {
      gApeMeshesPersistent[label] = handles;
    }
  }

  RedFHandleMesh handle = 0;
  if (handles != 0) {
    handle = handles[0];
  }

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshDelete GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshDelete")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleMesh * handle = gApeMeshes[label];
  redFDestroyMesh(handle);

  gApeMeshes.erase(label);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshPersistentDelete GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshPersistentDelete")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleMesh * handle = gApeMeshesPersistent[label];
  redFDestroyMesh(handle);

  gApeMeshesPersistent.erase(label);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshDeleteAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  for (auto & kv : gApeMeshes) {
    redFDestroyMesh(kv.second);
  }

  gApeMeshes.clear();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshPersistentDeleteAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  for (auto & kv : gApeMeshesPersistent) {
    redFDestroyMesh(kv.second);
  }

  gApeMeshesPersistent.clear();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshGetHandle GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshGetHandle")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleMesh * handles = gApeMeshes[label];
  RedFHandleMesh   handle  = 0;
  if (handles != 0) {
    handle = handles[0];
  }

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshPersistentGetHandle GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshPersistentGetHandle")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleMesh * handles = gApeMeshesPersistent[label];
  RedFHandleMesh   handle  = 0;
  if (handles != 0) {
    handle = handles[0];
  }

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshIsUsingColors GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshIsUsingColors")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_bool((bool)redFMeshUsingColors(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshIsUsingTextures GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshIsUsingTextures")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_bool((bool)redFMeshUsingTextures(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshIsUsingIndices GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshIsUsingIndices")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_bool((bool)redFMeshUsingIndices(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshEnableColors GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshEnableColors")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  redFMeshEnableColors(handle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshEnableTextures GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshEnableTextures")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  redFMeshEnableTextures(handle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshEnableIndices GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshEnableIndices")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  redFMeshEnableIndices(handle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshDisableColors GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshDisableColors")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  redFMeshDisableColors(handle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshDisableTextures GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshDisableTextures")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  redFMeshDisableTextures(handle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshDisableIndices GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshDisableIndices")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  redFMeshDisableIndices(handle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshHasVertices GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshHasVertices")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_bool((bool)redFMeshHasVertices(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshHasColors GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshHasColors")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_bool((bool)redFMeshHasColors(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshHasTexCoords GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshHasTexCoords")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_bool((bool)redFMeshHasTexCoords(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshHasIndices GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshHasIndices")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_bool((bool)redFMeshHasIndices(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshGetVerticesCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshGetVerticesCount")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)redFMeshGetNumVertices(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshGetColorsCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshGetColorsCount")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)redFMeshGetNumColors(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshGetTexCoordsCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshGetTexCoordsCount")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)redFMeshGetNumTexCoords(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshGetIndicesCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshGetIndicesCount")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)redFMeshGetNumIndices(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshHaveVerticesChanged GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshHaveVerticesChanged")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_bool((bool)redFMeshHaveVertsChanged(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshHaveColorsChanged GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshHaveColorsChanged")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_bool((bool)redFMeshHaveColorsChanged(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshHaveTexCoordsChanged GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshHaveTexCoordsChanged")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_bool((bool)redFMeshHaveTexCoordsChanged(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshHaveIndicesChanged GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshHaveIndicesChanged")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_bool((bool)redFMeshHaveIndicesChanged(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshAddVertex GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshAddVertex")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_Double(float,           x,      args[_i++]);
  getArgAs_Double(float,           y,      args[_i++]);
  getArgAs_Double(float,           z,      args[_i++]);
  getArgAs_END

  redFMeshAddVertex(handle, x, y, z);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshAddColor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*r*/,
    APE_OBJECT_NUMBER/*g*/,
    APE_OBJECT_NUMBER/*b*/,
    APE_OBJECT_NUMBER/*a*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshAddColor")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_Double(float,           r,      args[_i++]);
  getArgAs_Double(float,           g,      args[_i++]);
  getArgAs_Double(float,           b,      args[_i++]);
  getArgAs_Double(float,           a,      args[_i++]);
  getArgAs_END

  redFMeshAddColor(handle, r, g, b, a);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshAddTexCoord GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*u*/,
    APE_OBJECT_NUMBER/*v*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshAddTexCoord")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_Double(float,           u,      args[_i++]);
  getArgAs_Double(float,           v,      args[_i++]);
  getArgAs_END

  redFMeshAddTexCoord(handle, u, v);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshAddIndex GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*index*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshAddIndex")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_Double(unsigned,        index,  args[_i++]);
  getArgAs_END

  redFMeshAddIndex(handle, index);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshRemoveVertex GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*index*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshRemoveVertex")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_Double(unsigned,        index,  args[_i++]);
  getArgAs_END

  redFMeshRemoveVertex(handle, index);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshRemoveColor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*index*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshRemoveColor")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_Double(unsigned,        index,  args[_i++]);
  getArgAs_END

  redFMeshRemoveColor(handle, index);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshRemoveTexCoord GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*index*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshRemoveTexCoord")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_Double(unsigned,        index,  args[_i++]);
  getArgAs_END

  redFMeshRemoveTexCoord(handle, index);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshRemoveIndex GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*index*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshRemoveIndex")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_Double(unsigned,        index,  args[_i++]);
  getArgAs_END

  redFMeshRemoveIndex(handle, index);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshClear GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshClear")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  redFMeshClear(handle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshClearVertices GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshClearVertices")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  redFMeshClearVertices(handle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshClearColors GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshClearColors")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  redFMeshClearColors(handle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshClearTexCoords GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshClearTexCoords")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  redFMeshClearTexCoords(handle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshClearIndices GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshClearIndices")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  redFMeshClearIndices(handle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshGetVerticesPointer GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshGetVerticesPointer")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_number(_gsPointerToNumber(redFMeshGetVerticesPointer(handle)));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshGetColorsPointer GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshGetColorsPointer")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_number(_gsPointerToNumber(redFMeshGetColorsPointer(handle)));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshGetTexCoordsPointer GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshGetTexCoordsPointer")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_number(_gsPointerToNumber(redFMeshGetTexCoordsPointer(handle)));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshGetIndicesPointer GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshGetIndicesPointer")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_number(_gsPointerToNumber(redFMeshGetIndexPointer(handle)));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshMergeDuplicateVertices GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshMergeDuplicateVertices")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  redFMeshMergeDuplicateVertices(handle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshSetupIndicesAuto GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshSetupIndicesAuto")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_END

  redFMeshSetupIndicesAuto(handle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshAddTriangle GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*verticesArrayIndex1*/,
    APE_OBJECT_NUMBER/*verticesArrayIndex2*/,
    APE_OBJECT_NUMBER/*verticesArrayIndex3*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshAddTriangle")
  getArgAs_Pointer(RedFHandleMesh, handle, args[_i++]);
  getArgAs_Double(unsigned,        i,      args[_i++]);
  getArgAs_Double(unsigned,        j,      args[_i++]);
  getArgAs_Double(unsigned,        k,      args[_i++]);
  getArgAs_END

  redFMeshAddTriangle(handle, i, j, k);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshDraw GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*renderMode*/,
    APE_OBJECT_NUMBER/*scaleX*/,
    APE_OBJECT_NUMBER/*scaleY*/,
    APE_OBJECT_NUMBER/*scaleZ*/,
    APE_OBJECT_NUMBER/*vectorX*/,
    APE_OBJECT_NUMBER/*vectorY*/,
    APE_OBJECT_NUMBER/*vectorZ*/,
    APE_OBJECT_NUMBER/*rotationX*/,
    APE_OBJECT_NUMBER/*rotationY*/,
    APE_OBJECT_NUMBER/*rotationZ*/,
    APE_OBJECT_NUMBER/*rotationDeg*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshDraw")
  getArgAs_Pointer(RedFHandleMesh, handle,      args[_i++]);
  getArgAs_Double(unsigned,        drawMode,    args[_i++]);
  getArgAs_Double(float,           scaleX,      args[_i++]);
  getArgAs_Double(float,           scaleY,      args[_i++]);
  getArgAs_Double(float,           scaleZ,      args[_i++]);
  getArgAs_Double(float,           vectorX,     args[_i++]);
  getArgAs_Double(float,           vectorY,     args[_i++]);
  getArgAs_Double(float,           vectorZ,     args[_i++]);
  getArgAs_Double(float,           rotationX,   args[_i++]);
  getArgAs_Double(float,           rotationY,   args[_i++]);
  getArgAs_Double(float,           rotationZ,   args[_i++]);
  getArgAs_Double(float,           rotationDeg, args[_i++]);
  getArgAs_END

  RedFPolyRenderMode renderMode = REDF_POLY_RENDER_MODE_FILL;
  if (drawMode == 1) {
    renderMode = REDF_POLY_RENDER_MODE_WIREFRAME;
  } else if (drawMode == 2) {
    renderMode = REDF_POLY_RENDER_MODE_POINTS;
  }

  redFSetColor(255, 255, 255, 255);
  redFSetLineWidth(1);
  redFPushMatrix();
  redFTranslate(vectorX, vectorY, vectorZ);
  redFRotateDeg(rotationDeg, rotationX, rotationY, rotationZ);
  redFScale(scaleX, scaleY, scaleZ);
  redFMeshDrawWithRenderMode(handle, renderMode);
  redFPopMatrix();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshDrawWithColor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*renderMode*/,
    APE_OBJECT_NUMBER/*scaleX*/,
    APE_OBJECT_NUMBER/*scaleY*/,
    APE_OBJECT_NUMBER/*scaleZ*/,
    APE_OBJECT_NUMBER/*vectorX*/,
    APE_OBJECT_NUMBER/*vectorY*/,
    APE_OBJECT_NUMBER/*vectorZ*/,
    APE_OBJECT_NUMBER/*rotationX*/,
    APE_OBJECT_NUMBER/*rotationY*/,
    APE_OBJECT_NUMBER/*rotationZ*/,
    APE_OBJECT_NUMBER/*rotationDeg*/,
    APE_OBJECT_NUMBER/*r0to255*/,
    APE_OBJECT_NUMBER/*g0to255*/,
    APE_OBJECT_NUMBER/*b0to255*/,
    APE_OBJECT_NUMBER/*a0to255*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshDrawWithColor")
  getArgAs_Pointer(RedFHandleMesh, handle,      args[_i++]);
  getArgAs_Double(unsigned,        drawMode,    args[_i++]);
  getArgAs_Double(float,           scaleX,      args[_i++]);
  getArgAs_Double(float,           scaleY,      args[_i++]);
  getArgAs_Double(float,           scaleZ,      args[_i++]);
  getArgAs_Double(float,           vectorX,     args[_i++]);
  getArgAs_Double(float,           vectorY,     args[_i++]);
  getArgAs_Double(float,           vectorZ,     args[_i++]);
  getArgAs_Double(float,           rotationX,   args[_i++]);
  getArgAs_Double(float,           rotationY,   args[_i++]);
  getArgAs_Double(float,           rotationZ,   args[_i++]);
  getArgAs_Double(float,           rotationDeg, args[_i++]);
  getArgAs_Double(int,             r,           args[_i++]);
  getArgAs_Double(int,             g,           args[_i++]);
  getArgAs_Double(int,             b,           args[_i++]);
  getArgAs_Double(int,             a,           args[_i++]);
  getArgAs_END

  RedFPolyRenderMode renderMode = REDF_POLY_RENDER_MODE_FILL;
  if (drawMode == 1) {
    renderMode = REDF_POLY_RENDER_MODE_WIREFRAME;
  } else if (drawMode == 2) {
    renderMode = REDF_POLY_RENDER_MODE_POINTS;
  }

  redFSetColor(r, g, b, a);
  redFSetLineWidth(1);
  redFPushMatrix();
  redFTranslate(vectorX, vectorY, vectorZ);
  redFRotateDeg(rotationDeg, rotationX, rotationY, rotationZ);
  redFScale(scaleX, scaleY, scaleZ);
  redFMeshDrawWithRenderMode(handle, renderMode);
  redFPopMatrix();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshDrawDebugVertices GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshDrawDebugVertices")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleMesh * handle = gApeMeshes[label];

  if (handle != 0) {
    ApeDrawLabelMesh draw;
    draw.handle                     = handle[0];
    draw.drawLabelsForAttribute     = APE_DRAW_LABEL_MESH_VERTEX_ATTRIBUTE_VERTICES;
    draw.filterDistance             = 0;
    draw.raytraceHighlightTriangles = 0;
    draw.label                      = label;
    gApeDrawLabelStackMeshes.push_back(draw);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshDrawDebugColors GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshDrawDebugColors")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleMesh * handle = gApeMeshes[label];

  if (handle != 0) {
    ApeDrawLabelMesh draw;
    draw.handle                     = handle[0];
    draw.drawLabelsForAttribute     = APE_DRAW_LABEL_MESH_VERTEX_ATTRIBUTE_COLORS;
    draw.filterDistance             = 0;
    draw.raytraceHighlightTriangles = 0;
    draw.label                      = label;
    gApeDrawLabelStackMeshes.push_back(draw);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshDrawDebugTexCoords GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshDrawDebugTexCoords")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleMesh * handle = gApeMeshes[label];

  if (handle != 0) {
    ApeDrawLabelMesh draw;
    draw.handle                     = handle[0];
    draw.drawLabelsForAttribute     = APE_DRAW_LABEL_MESH_VERTEX_ATTRIBUTE_TEXCOORDS;
    draw.filterDistance             = 0;
    draw.raytraceHighlightTriangles = 0;
    draw.label                      = label;
    gApeDrawLabelStackMeshes.push_back(draw);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshDrawDebugIndices GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshDrawDebugIndices")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleMesh * handle = gApeMeshes[label];

  if (handle != 0) {
    ApeDrawLabelMesh draw;
    draw.handle                     = handle[0];
    draw.drawLabelsForAttribute     = APE_DRAW_LABEL_MESH_VERTEX_ATTRIBUTE_INDICES;
    draw.filterDistance             = 0;
    draw.raytraceHighlightTriangles = 0;
    draw.label                      = label;
    gApeDrawLabelStackMeshes.push_back(draw);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshDrawDebugRayTraceIndices GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*maxShowDistanceToDefaultCamera*/,
    APE_OBJECT_BOOL/*raytraceHighlightTrianglesDefaultCameraLooksAt*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshDrawDebugRayTraceIndices")
  getArgAs_String(std::string, label,                      args[_i++]);
  getArgAs_Double(float,       distance,                   args[_i++]);
  getArgAs_Bool(int,           raytraceHighlightTriangles, args[_i++]);
  getArgAs_END

  RedFHandleMesh * handle = gApeMeshes[label];

  if (handle != 0) {
    ApeDrawLabelMesh draw;
    draw.handle                     = handle[0];
    draw.drawLabelsForAttribute     = APE_DRAW_LABEL_MESH_VERTEX_ATTRIBUTE_INDICES;
    draw.filterDistance             = distance;
    draw.raytraceHighlightTriangles = raytraceHighlightTriangles;
    draw.label                      = label;
    gApeDrawLabelStackMeshes.push_back(draw);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshImporterGetMeshesCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*meshFilepath*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshImporterGetMeshesCount")
  getArgAs_String(std::string, meshFilepath, args[_i++]);
  getArgAs_END

  RedFHandleAssimp * handle = gApeAssimpPersistent[meshFilepath];
  if (handle == 0) {
    handle = redFCreateAssimp(1);
    if (handle == 0) {
      return ape_object_make_number(0.0);
    }
    RedFBool32 loaded = redFAssimpLoadModel(handle[0], meshFilepath.c_str(), 1);
    if (loaded == 0) {
      redFDestroyAssimp(handle);
      return ape_object_make_number(0.0);
    }
    gApeAssimpPersistent[meshFilepath] = handle;
  }

  return ape_object_make_number((double)redFAssimpGetNumMeshes(handle[0]));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshImporterGetMeshName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*meshFilepath*/,
    APE_OBJECT_NUMBER/*meshIndex*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshImporterGetMeshName")
  getArgAs_String(std::string, meshFilepath, args[_i++]);
  getArgAs_Double(uint64_t,    meshIndex,    args[_i++]);
  getArgAs_END

  RedFHandleAssimp * handle = gApeAssimpPersistent[meshFilepath];
  if (handle == 0) {
    handle = redFCreateAssimp(1);
    if (handle == 0) {
      return ape_object_make_string(ape, "");
    }
    RedFBool32 loaded = redFAssimpLoadModel(handle[0], meshFilepath.c_str(), 1);
    if (loaded == 0) {
      redFDestroyAssimp(handle);
      return ape_object_make_string(ape, "");
    }
    gApeAssimpPersistent[meshFilepath] = handle;
  }

  uint64_t meshNameCharsCount = 0;
  redFAssimpGetMeshName(handle[0], meshIndex, &meshNameCharsCount, 0);
  std::string meshName(meshNameCharsCount, '\0');
  redFAssimpGetMeshName(handle[0], meshIndex, &meshNameCharsCount, &meshName[0]);

  return ape_object_make_string(ape, meshName.c_str());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshImporterGetMesh GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*meshFilepath*/,
    APE_OBJECT_NUMBER/*meshIndex*/,
    APE_OBJECT_NUMBER/*writeToMesh*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshImporterGetMesh")
  getArgAs_String(std::string,     meshFilepath, args[_i++]);
  getArgAs_Double(uint64_t,        meshIndex,    args[_i++]);
  getArgAs_Pointer(RedFHandleMesh, meshHandle,   args[_i++]);
  getArgAs_END

  if (meshHandle == 0) {
    return ape_object_make_null();
  }

  RedFHandleAssimp * handle = gApeAssimpPersistent[meshFilepath];
  if (handle == 0) {
    handle = redFCreateAssimp(1);
    if (handle == 0) {
      return ape_object_make_null();
    }
    RedFBool32 loaded = redFAssimpLoadModel(handle[0], meshFilepath.c_str(), 1);
    if (loaded == 0) {
      redFDestroyAssimp(handle);
      return ape_object_make_null();
    }
    gApeAssimpPersistent[meshFilepath] = handle;
  }

  redFAssimpGetMesh(handle[0], meshIndex, meshHandle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshImporterDelete GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*meshFilepath*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("meshImporterDelete")
  getArgAs_String(std::string, meshFilepath, args[_i++]);
  getArgAs_END

  RedFHandleAssimp * handle = gApeAssimpPersistent[meshFilepath];
  redFDestroyAssimp(handle);

  gApeAssimpPersistent.erase(meshFilepath);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMeshImporterDeleteAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  for (auto & kv : gApeAssimpPersistent) {
    redFDestroyAssimp(kv.second);
  }

  gApeAssimpPersistent.clear();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageNew GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*width*/,
    APE_OBJECT_NUMBER/*height*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageNew")
  getArgAs_String(std::string, label,  args[_i++]);
  getArgAs_Double(int,         width,  args[_i++]);
  getArgAs_Double(int,         height, args[_i++]);
  getArgAs_END

  RedFHandleImage * handle = gApeImages[label];
  if (handle == 0) {
    handle = redFCreateImage(1);
    if (handle != 0) {
      gApeImages[label] = handle;
      redFImageAllocate(handle[0], width, height, REDF_IMAGE_TYPE_COLOR_ALPHA_RGBA);
      _gsImageClear(handle[0], 255);
    }
  }

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImagePersistentNew GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_NUMBER/*width*/,
    APE_OBJECT_NUMBER/*height*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imagePersistentNew")
  getArgAs_String(std::string, label,  args[_i++]);
  getArgAs_Double(int,         width,  args[_i++]);
  getArgAs_Double(int,         height, args[_i++]);
  getArgAs_END

  RedFHandleImage * handle = gApeImagesPersistent[label];
  if (handle == 0) {
    handle = redFCreateImage(1);
    if (handle != 0) {
      gApeImagesPersistent[label] = handle;
      redFImageAllocate(handle[0], width, height, REDF_IMAGE_TYPE_COLOR_ALPHA_RGBA);
      _gsImageClear(handle[0], 255);
    }
  }

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageNewFromFile GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_STRING/*filepath*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageNewFromFile")
  getArgAs_String(std::string,  label,    args[_i++]);
  getArgAs_CChars(const char *, filepath, args[_i++]);
  getArgAs_END

  RedFHandleImage * handle = gApeImages[label];
  if (handle == 0) {
    handle = redFCreateImage(1);
    if (handle != 0) {
      RedFBool32 loaded = redFImageLoad(handle[0], filepath);
      if (loaded == 0) {
        redFDestroyImage(handle);
        handle = 0;
      } else {
        gApeImages[label] = handle;
        _gsImageGammaCorrect(handle[0]);
        redFImageUpdate(handle[0]);
      }
    }
  }

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImagePersistentNewFromFile GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_STRING/*filepath*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imagePersistentNewFromFile")
  getArgAs_String(std::string,  label,    args[_i++]);
  getArgAs_CChars(const char *, filepath, args[_i++]);
  getArgAs_END

  RedFHandleImage * handle = gApeImagesPersistent[label];
  if (handle == 0) {
    handle = redFCreateImage(1);
    if (handle != 0) {
      RedFBool32 loaded = redFImageLoad(handle[0], filepath);
      if (loaded == 0) {
        redFDestroyImage(handle);
        handle = 0;
      } else {
        gApeImagesPersistent[label] = handle;
        _gsImageGammaCorrect(handle[0]);
        redFImageUpdate(handle[0]);
      }
    }
  }

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageDelete GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageDelete")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleImage * handle = gApeImages[label];
  redFDestroyImage(handle);

  gApeImages.erase(label);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImagePersistentDelete GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imagePersistentDelete")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleImage * handle = gApeImagesPersistent[label];
  redFDestroyImage(handle);

  gApeImagesPersistent.erase(label);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageDeleteAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  for (auto & kv : gApeImages) {
    redFDestroyImage(kv.second);
  }

  gApeImages.clear();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImagePersistentDeleteAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  for (auto & kv : gApeImagesPersistent) {
    redFDestroyImage(kv.second);
  }

  gApeImagesPersistent.clear();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageGetHandle GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageGetHandle")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleImage * handle = gApeImages[label];

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImagePersistentGetHandle GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imagePersistentGetHandle")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleImage * handle = gApeImagesPersistent[label];

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageLoadFromMemory GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/,
    APE_OBJECT_NUMBER/*pointerBytesCount*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageLoadFromMemory")
  getArgAs_Pointer(RedFHandleImage *, handle,     args[_i++]);
  getArgAs_Pointer(const char *,      pointer,    args[_i++]);
  getArgAs_Double(uint64_t,           bytesFirst, args[_i++]);
  getArgAs_Double(uint64_t,           bytesCount, args[_i++]);
  getArgAs_END

  return ape_object_make_bool((bool)redFImageLoadFromMemory(handle[0], bytesCount, &pointer[bytesFirst]));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageClear GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*alphaValue0to255*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageClear")
  getArgAs_Pointer(RedFHandleImage *, handle,           args[_i++]);
  getArgAs_Double(int,                alphaValue0to255, args[_i++]);
  getArgAs_END

  _gsImageClear(handle[0], alphaValue0to255);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageSetTextureMinMagFilter GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*minFilter*/,
    APE_OBJECT_NUMBER/*magFilter*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageSetTextureMinMagFilter")
  getArgAs_Pointer(RedFHandleImage *, handle,    args[_i++]);
  getArgAs_Double(int,                minFilter, args[_i++]);
  getArgAs_Double(int,                magFilter, args[_i++]);
  getArgAs_END

  redFImageSetTextureMinMagFilter(handle[0], minFilter, magFilter);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageSetTextureWrap GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*wrapX*/,
    APE_OBJECT_NUMBER/*wrapY*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageSetTextureWrap")
  getArgAs_Pointer(RedFHandleImage *, handle, args[_i++]);
  getArgAs_Double(int,                wrapX,  args[_i++]);
  getArgAs_Double(int,                wrapY,  args[_i++]);
  getArgAs_END

  redFImageSetTextureWrap(handle[0], wrapX, wrapY);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageSetTextureMaxAnisotropy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*maxAnisotropy*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageSetTextureMaxAnisotropy")
  getArgAs_Pointer(RedFHandleImage *, handle,        args[_i++]);
  getArgAs_Double(int,                maxAnisotropy, args[_i++]);
  getArgAs_END

  redFImageSetTextureMaxAnisotropy(handle[0], maxAnisotropy);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageGetWidth GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageGetWidth")
  getArgAs_Pointer(RedFHandleImage *, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)redFImageGetWidth(handle[0]));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageGetHeight GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageGetHeight")
  getArgAs_Pointer(RedFHandleImage *, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)redFImageGetHeight(handle[0]));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageGetBitsPerPixel GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageGetBitsPerPixel")
  getArgAs_Pointer(RedFHandleImage *, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)redFImageGetBitsPerPixel(handle[0]));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageGetImageType GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageGetImageType")
  getArgAs_Pointer(RedFHandleImage *, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)redFImageGetImageType(handle[0]));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageGetPixelsPointer GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageGetPixelsPointer")
  getArgAs_Pointer(RedFHandleImage *, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_number(_gsPointerToNumber(redFImageGetPixelsPointer(handle[0])));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageGetColor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageGetColor")
  getArgAs_Pointer(RedFHandleImage *, handle, args[_i++]);
  getArgAs_Double(int,                x,      args[_i++]);
  getArgAs_Double(int,                y,      args[_i++]);
  getArgAs_END

  unsigned char r = 0;
  unsigned char g = 0;
  unsigned char b = 0;
  unsigned char a = 0;
  redFImageGetColor(handle[0], x, y, &r, &g, &b, &a);

  ape_object_t array = mape_object_make_array(ape, 4);
  mape_object_add_array_number(0, array, (double)r);
  mape_object_add_array_number(1, array, (double)g);
  mape_object_add_array_number(2, array, (double)b);
  mape_object_add_array_number(3, array, (double)a);
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageSetColor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*r*/,
    APE_OBJECT_NUMBER/*g*/,
    APE_OBJECT_NUMBER/*b*/,
    APE_OBJECT_NUMBER/*a*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageSetColor")
  getArgAs_Pointer(RedFHandleImage *, handle, args[_i++]);
  getArgAs_Double(int,                x,      args[_i++]);
  getArgAs_Double(int,                y,      args[_i++]);
  getArgAs_Double(int,                r,      args[_i++]);
  getArgAs_Double(int,                g,      args[_i++]);
  getArgAs_Double(int,                b,      args[_i++]);
  getArgAs_Double(int,                a,      args[_i++]);
  getArgAs_END

  redFImageSetColor(handle[0], x, y, r, g, b, a);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageGammaCorrect GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageGammaCorrect")
  getArgAs_Pointer(RedFHandleImage *, handle, args[_i++]);
  getArgAs_END

  _gsImageGammaCorrect(handle[0]);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageHasMipmap GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageHasMipmap")
  getArgAs_Pointer(RedFHandleImage *, handle, args[_i++]);
  getArgAs_END

  return ape_object_make_bool((bool)redFImageHasMipmap(handle[0]));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageMipmapDisable GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageMipmapDisable")
  getArgAs_Pointer(RedFHandleImage *, handle, args[_i++]);
  getArgAs_END

  redFImageMipmapDisable(handle[0]);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageMipmapEnable GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageMipmapEnable")
  getArgAs_Pointer(RedFHandleImage *, handle, args[_i++]);
  getArgAs_END

  redFImageMipmapEnable(handle[0]);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageMipmapGenerate GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageMipmapGenerate")
  getArgAs_Pointer(RedFHandleImage *, handle, args[_i++]);
  getArgAs_END

  redFImageMipmapGenerate(handle[0]);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageUpdate GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageUpdate")
  getArgAs_Pointer(RedFHandleImage *, handle, args[_i++]);
  getArgAs_END

  redFImageUpdate(handle[0]);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageBind GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageBind")
  getArgAs_Pointer(RedFHandleImage *, handle, args[_i++]);
  getArgAs_END

  redFImageBind(handle[0]);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageUnbind GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageUnbind")
  getArgAs_Pointer(RedFHandleImage *, handle, args[_i++]);
  getArgAs_END

  redFImageUnbind(handle[0]);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageDraw GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/,
    APE_OBJECT_NUMBER/*w*/,
    APE_OBJECT_NUMBER/*h*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageDraw")
  getArgAs_Pointer(RedFHandleImage *, handle, args[_i++]);
  getArgAs_Double(float,              x,      args[_i++]);
  getArgAs_Double(float,              y,      args[_i++]);
  getArgAs_Double(float,              z,      args[_i++]);
  getArgAs_Double(float,              w,      args[_i++]);
  getArgAs_Double(float,              h,      args[_i++]);
  getArgAs_END

  if (handle != 0) {
    ApeDrawImage draw;
    draw.handle = handle[0];
    draw.x      = x;
    draw.y      = y;
    draw.z      = z;
    draw.w      = w;
    draw.h      = h;
    gApeDrawImages.push_back(draw);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImageDrawSubsection GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/,
    APE_OBJECT_NUMBER/*w*/,
    APE_OBJECT_NUMBER/*h*/,
    APE_OBJECT_NUMBER/*sx*/,
    APE_OBJECT_NUMBER/*sy*/,
    APE_OBJECT_NUMBER/*sw*/,
    APE_OBJECT_NUMBER/*sh*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imageDrawSubsection")
  getArgAs_Pointer(RedFHandleImage *, handle, args[_i++]);
  getArgAs_Double(float,              x,      args[_i++]);
  getArgAs_Double(float,              y,      args[_i++]);
  getArgAs_Double(float,              z,      args[_i++]);
  getArgAs_Double(float,              w,      args[_i++]);
  getArgAs_Double(float,              h,      args[_i++]);
  getArgAs_Double(float,              sx,     args[_i++]);
  getArgAs_Double(float,              sy,     args[_i++]);
  getArgAs_Double(float,              sw,     args[_i++]);
  getArgAs_Double(float,              sh,     args[_i++]);
  getArgAs_END

  if (handle != 0) {
    ApeDrawImageSubsection draw;
    draw.handle = handle[0];
    draw.x      = x;
    draw.y      = y;
    draw.z      = z;
    draw.w      = w;
    draw.h      = h;
    draw.sx     = sx;
    draw.sy     = sy;
    draw.sw     = sw;
    draw.sh     = sh;
    gApeDrawImagesSubsections.push_back(draw);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureShaderBegin GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_STRING/*filepathShaderVert*/,
    APE_OBJECT_STRING/*filepathShaderFrag*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("shaderBegin")
  getArgAs_String(std::string,  label,              args[_i++]);
  getArgAs_CChars(const char *, filepathShaderVert, args[_i++]);
  getArgAs_CChars(const char *, filepathShaderFrag, args[_i++]);
  getArgAs_END

  bool loaded = true;

  RedFHandleShader * handle = gApeShaders[label];
  if (handle == 0) {
    handle = redFCreateShader(1);
    if (handle == 0) {
      loaded = false;
    } else {
      loaded = (bool)redFShaderLoad(handle[0], filepathShaderVert, filepathShaderFrag);
      if (loaded == false) {
        redFDestroyShader(handle);
      } else {
        gApeShaders[label] = handle;
      }
    }
  }

  if (loaded == true) {
    redFShaderBegin(handle[0]);
  }

  return ape_object_make_bool(loaded);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureShaderEnd GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("shaderEnd")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleShader * handle = gApeShaders[label];

  if (handle != 0) {
    redFShaderEnd(handle[0]);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureShaderSetUniform4f GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_STRING/*uniformName*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/,
    APE_OBJECT_NUMBER/*w*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("shaderSetUniform4f")
  getArgAs_String(std::string,  label,       args[_i++]);
  getArgAs_CChars(const char *, uniformName, args[_i++]);
  getArgAs_Double(float,        x,           args[_i++]);
  getArgAs_Double(float,        y,           args[_i++]);
  getArgAs_Double(float,        z,           args[_i++]);
  getArgAs_Double(float,        w,           args[_i++]);
  getArgAs_END

  RedFHandleShader * handle = gApeShaders[label];

  if (handle != 0) {
    redFShaderSetUniform4f(handle[0], uniformName, x, y, z, w);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureShaderSetUniform4fv GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_STRING/*uniformName*/,
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*count*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("shaderSetUniform4fv")
  getArgAs_String(std::string,  label,       args[_i++]);
  getArgAs_CChars(const char *, uniformName, args[_i++]);
  getArgAs_Pointer(void *,      pointer,     args[_i++]);
  getArgAs_Double(int,          count,       args[_i++]);
  getArgAs_END

  RedFHandleShader * handle = gApeShaders[label];

  if (handle != 0) {
    redFShaderSetUniform4fv(handle[0], uniformName, pointer, count);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureShaderSetUniformMatrix4f GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_STRING/*uniformName*/,
    APE_OBJECT_NUMBER/*pointer*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("shaderSetUniformMatrix4f")
  getArgAs_String(std::string,  label,       args[_i++]);
  getArgAs_CChars(const char *, uniformName, args[_i++]);
  getArgAs_Pointer(void *,      pointer,     args[_i++]);
  getArgAs_END

  RedFHandleShader * handle = gApeShaders[label];

  if (handle != 0) {
    redFShaderSetUniformMatrix4f(handle[0], uniformName, pointer);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureShaderSetUniformImage GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_STRING/*uniformName*/,
    APE_OBJECT_NUMBER/*imageHandle*/,
    APE_OBJECT_NUMBER/*textureLocation*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("shaderSetUniformImage")
  getArgAs_String(std::string,        label,           args[_i++]);
  getArgAs_CChars(const char *,       uniformName,     args[_i++]);
  getArgAs_Pointer(RedFHandleImage *, imageHandle,     args[_i++]);
  getArgAs_Double(int,                textureLocation, args[_i++]);
  getArgAs_END

  RedFHandleShader * handle = gApeShaders[label];

  if (handle != 0) {
    redFShaderSetUniformImage(handle[0], uniformName, imageHandle[0], textureLocation);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureShaderDelete GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("shaderDelete")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleShader * handle = gApeShaders[label];
  redFDestroyShader(handle);

  gApeShaders.erase(label);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureShaderDeleteAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  for (auto & kv : gApeShaders) {
    redFDestroyShader(kv.second);
  }

  gApeShaders.clear();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerNew GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerNew")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleSoundPlayer * handle = gApeSoundPlayers[label];
  if (handle == 0) {
    handle = redFCreateSoundPlayer(1);
    if (handle != 0) {
      gApeSoundPlayers[label] = handle;
    }
  }

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerPersistentNew GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerPersistentNew")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleSoundPlayer * handle = gApeSoundPlayersPersistent[label];
  if (handle == 0) {
    handle = redFCreateSoundPlayer(1);
    if (handle != 0) {
      gApeSoundPlayersPersistent[label] = handle;
    }
  }

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerDelete GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerDelete")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleSoundPlayer * handle = gApeSoundPlayers[label];
  redFDestroySoundPlayer(handle);

  gApeSoundPlayers.erase(label);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerPersistentDelete GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerPersistentDelete")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleSoundPlayer * handle = gApeSoundPlayersPersistent[label];
  redFDestroySoundPlayer(handle);

  gApeSoundPlayersPersistent.erase(label);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerDeleteAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  for (auto & kv : gApeSoundPlayers) {
    redFDestroySoundPlayer(kv.second);
  }

  gApeSoundPlayers.clear();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerPersistentDeleteAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  for (auto & kv : gApeSoundPlayersPersistent) {
    redFDestroySoundPlayer(kv.second);
  }

  gApeSoundPlayersPersistent.clear();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerGetHandle GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerGetHandle")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleSoundPlayer * handle = gApeSoundPlayers[label];

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerPersistentGetHandle GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerPersistentGetHandle")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleSoundPlayer * handle = gApeSoundPlayersPersistent[label];

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerLoad GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_STRING/*filepath*/,
    APE_OBJECT_BOOL/*streamDefaultIsFalse*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerLoad")
  getArgAs_Pointer(RedFHandleSoundPlayer *, handle,               args[_i++]);
  getArgAs_CChars(const char *,             filepath,             args[_i++]);
  getArgAs_Bool(RedFBool32,                 streamDefaultIsFalse, args[_i++]);
  getArgAs_END

  RedFBool32 loaded = redFSoundPlayerIsLoaded(handle[0]);
  if (loaded == 0) {
    loaded = redFSoundPlayerLoad(handle[0], filepath, streamDefaultIsFalse);
  }

  return ape_object_make_bool((bool)loaded);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerUnload GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerUnload")
  getArgAs_Pointer(RedFHandleSoundPlayer *, handle, args[_i++]);
  getArgAs_END

  redFSoundPlayerUnload(handle[0]);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerPlay GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerPlay")
  getArgAs_Pointer(RedFHandleSoundPlayer *, handle, args[_i++]);
  getArgAs_END

  redFSoundPlayerPlay(handle[0]);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerStop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerStop")
  getArgAs_Pointer(RedFHandleSoundPlayer *, handle, args[_i++]);
  getArgAs_END

  redFSoundPlayerStop(handle[0]);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerSetVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*volume0to1*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerSetVolume")
  getArgAs_Pointer(RedFHandleSoundPlayer *, handle,     args[_i++]);
  getArgAs_Double(float,                    volume0to1, args[_i++]);
  getArgAs_END

  redFSoundPlayerSetVolume(handle[0], volume0to1);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerSetPan GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*panMinus1to1*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerSetPan")
  getArgAs_Pointer(RedFHandleSoundPlayer *, handle,       args[_i++]);
  getArgAs_Double(float,                    panMinus1to1, args[_i++]);
  getArgAs_END

  redFSoundPlayerSetPan(handle[0], panMinus1to1);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerSetSpeed GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*speedDefaultIs1*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerSetSpeed")
  getArgAs_Pointer(RedFHandleSoundPlayer *, handle,          args[_i++]);
  getArgAs_Double(float,                    speedDefaultIs1, args[_i++]);
  getArgAs_END

  redFSoundPlayerSetSpeed(handle[0], speedDefaultIs1);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerSetPaused GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_BOOL/*paused*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerSetPaused")
  getArgAs_Pointer(RedFHandleSoundPlayer *, handle, args[_i++]);
  getArgAs_Bool(RedFBool32,                 paused, args[_i++]);
  getArgAs_END

  redFSoundPlayerSetPaused(handle[0], paused);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerSetLoop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_BOOL/*loop*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerSetLoop")
  getArgAs_Pointer(RedFHandleSoundPlayer *, handle, args[_i++]);
  getArgAs_Bool(RedFBool32,                 loop,   args[_i++]);
  getArgAs_END

  redFSoundPlayerSetLoop(handle[0], loop);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerSetMultiPlay GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_BOOL/*multiplay*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerSetMultiPlay")
  getArgAs_Pointer(RedFHandleSoundPlayer *, handle,    args[_i++]);
  getArgAs_Bool(RedFBool32,                 multiplay, args[_i++]);
  getArgAs_END

  redFSoundPlayerSetMultiPlay(handle[0], multiplay);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerSetPosition GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*percent0to1*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerSetPosition")
  getArgAs_Pointer(RedFHandleSoundPlayer *, handle,      args[_i++]);
  getArgAs_Double(float,                    percent0to1, args[_i++]);
  getArgAs_END

  redFSoundPlayerSetPosition(handle[0], percent0to1);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerSetPositionMS GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*milliseconds*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerSetPositionMS")
  getArgAs_Pointer(RedFHandleSoundPlayer *, handle,       args[_i++]);
  getArgAs_Double(int,                      milliseconds, args[_i++]);
  getArgAs_END

  redFSoundPlayerSetPositionMS(handle[0], milliseconds);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerGetPositionMS GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerGetPositionMS")
  getArgAs_Pointer(RedFHandleSoundPlayer *, handle, args[_i++]);
  getArgAs_END

  int out = redFSoundPlayerGetPositionMS(handle[0]);

  return ape_object_make_number((double)out);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerGetPosition GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerGetPosition")
  getArgAs_Pointer(RedFHandleSoundPlayer *, handle, args[_i++]);
  getArgAs_END

  float out = redFSoundPlayerGetPosition(handle[0]);

  return ape_object_make_number((double)out);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerIsPlaying GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerIsPlaying")
  getArgAs_Pointer(RedFHandleSoundPlayer *, handle, args[_i++]);
  getArgAs_END

  RedFBool32 out = redFSoundPlayerIsPlaying(handle[0]);

  return ape_object_make_bool((bool)out);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerGetSpeed GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerGetSpeed")
  getArgAs_Pointer(RedFHandleSoundPlayer *, handle, args[_i++]);
  getArgAs_END

  float out = redFSoundPlayerGetSpeed(handle[0]);

  return ape_object_make_number((double)out);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerGetPan GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerGetPan")
  getArgAs_Pointer(RedFHandleSoundPlayer *, handle, args[_i++]);
  getArgAs_END

  float out = redFSoundPlayerGetPan(handle[0]);

  return ape_object_make_number((double)out);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerGetVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerGetVolume")
  getArgAs_Pointer(RedFHandleSoundPlayer *, handle, args[_i++]);
  getArgAs_END

  float out = redFSoundPlayerGetVolume(handle[0]);

  return ape_object_make_number((double)out);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundPlayerIsLoaded GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundPlayerIsLoaded")
  getArgAs_Pointer(RedFHandleSoundPlayer *, handle, args[_i++]);
  getArgAs_END

  RedFBool32 out = redFSoundPlayerIsLoaded(handle[0]);

  return ape_object_make_bool((bool)out);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundSetVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*volume0to1*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("soundSetVolume")
  getArgAs_Double(float, volume0to1, args[_i++]);
  getArgAs_END

  redFSoundSetVolume(volume0to1);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundShutdown GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  redFSoundShutdown();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundStopAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  redFSoundStopAll();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSoundUpdate GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  redFSoundUpdate();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImguiBegin GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  if (gGameMode == 0) {
    return ape_object_make_null();
  }

  redFPushStyle();
  redFDisableCulling();
  redFDisableLighting();
  redFDisableDepthTest();
  redFDisableBlendMode();
  redFDisableAlphaBlending();
  redFImguiBegin(gGuiImgui[0]);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImguiEnd GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  if (gGameMode == 0) {
    return ape_object_make_null();
  }

  redFImguiEnd(gGuiImgui[0]);
  redFPopStyle();
  redFEnableDepthTest();
  redFEnableBlendMode(REDF_BLEND_MODE_ALPHA);
  redFEnableAlphaBlending();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImguiWindowBegin GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*windowName*/,
    APE_OBJECT_NUMBER/*outPointerToWindowIsOpenBool*/,
    APE_OBJECT_NUMBER/*outPointerToWindowIsOpenBoolBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  if (gGameMode == 0) {
    return ape_object_make_bool(false);
  }

  getArgAs_BEGIN("imguiWindowBegin")
  getArgAs_CChars(const char *,     windowName,           args[_i++]);
  getArgAs_Pointer(unsigned char *, outPointer,           args[_i++]);
  getArgAs_Double(uint64_t,         outPointerBytesFirst, args[_i++]);
  getArgAs_END

  return ape_object_make_bool(igBegin(windowName, (bool *)&outPointer[outPointerBytesFirst], 0));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImguiWindowEnd GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  if (gGameMode == 0) {
    return ape_object_make_null();
  }

  igEnd();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImguiButton GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*buttonName*/,
    APE_OBJECT_NUMBER/*buttonWidth*/,
    APE_OBJECT_NUMBER/*buttonHeight*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  if (gGameMode == 0) {
    return ape_object_make_bool(false);
  }

  getArgAs_BEGIN("imguiButton")
  getArgAs_CChars(const char *, buttonName,   args[_i++]);
  getArgAs_Double(float,        buttonWidth,  args[_i++]);
  getArgAs_Double(float,        buttonHeight, args[_i++]);
  getArgAs_END

  ImVec2 buttonSize;
  buttonSize.x = buttonWidth;
  buttonSize.y = buttonHeight;
  return ape_object_make_bool(igButton(buttonName, buttonSize));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImguiText GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*text*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  if (gGameMode == 0) {
    return ape_object_make_null();
  }

  getArgAs_BEGIN("imguiText")
  getArgAs_CChars(const char *, text, args[_i++]);
  getArgAs_END

  igText("%s", text);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImguiTextMultiline GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*textFieldName*/,
    APE_OBJECT_STRING/*text*/,
    APE_OBJECT_NUMBER/*textFieldWidth*/,
    APE_OBJECT_NUMBER/*textFieldHeight*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  if (gGameMode == 0) {
    return ape_object_make_bool(false);
  }

  getArgAs_BEGIN("imguiTextMultiline")
  getArgAs_CChars(const char *, textFieldName,   args[_i++]);
  getArgAs_String(std::string,  text,            args[_i++]);
  getArgAs_Double(float,        textFieldWidth,  args[_i++]);
  getArgAs_Double(float,        textFieldHeight, args[_i++]);
  getArgAs_END

  ImVec2 textFieldSize;
  textFieldSize.x = textFieldWidth;
  textFieldSize.y = textFieldHeight;
  return ape_object_make_bool(igInputTextMultiline(textFieldName, &text[0], text.size(), textFieldSize, ImGuiInputTextFlags_ReadOnly, 0, 0));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImguiInputText GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*textFieldName*/,
    APE_OBJECT_NUMBER/*outPointerToString*/,
    APE_OBJECT_NUMBER/*outPointerToStringBytesFirst*/,
    APE_OBJECT_NUMBER/*outPointerToStringBytesCountMax*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  if (gGameMode == 0) {
    return ape_object_make_bool(false);
  }

  getArgAs_BEGIN("imguiInputText")
  getArgAs_CChars(const char *, textFieldName,           args[_i++]);
  getArgAs_Pointer(char *,      outPointer,              args[_i++]);
  getArgAs_Double(uint64_t,     outPointerBytesFirst,    args[_i++]);
  getArgAs_Double(uint64_t,     outPointerBytesCountMax, args[_i++]);
  getArgAs_END

  return ape_object_make_bool(igInputText(textFieldName, &outPointer[outPointerBytesFirst], outPointerBytesCountMax, 0, 0, 0));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImguiInputTextMultiline GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*textFieldName*/,
    APE_OBJECT_NUMBER/*outPointerToString*/,
    APE_OBJECT_NUMBER/*outPointerToStringBytesFirst*/,
    APE_OBJECT_NUMBER/*outPointerToStringBytesCountMax*/,
    APE_OBJECT_NUMBER/*textFieldWidth*/,
    APE_OBJECT_NUMBER/*textFieldHeight*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  if (gGameMode == 0) {
    return ape_object_make_bool(false);
  }

  getArgAs_BEGIN("imguiInputTextMultiline")
  getArgAs_CChars(const char *, textFieldName,           args[_i++]);
  getArgAs_Pointer(char *,      outPointer,              args[_i++]);
  getArgAs_Double(uint64_t,     outPointerBytesFirst,    args[_i++]);
  getArgAs_Double(uint64_t,     outPointerBytesCountMax, args[_i++]);
  getArgAs_Double(float,        textFieldWidth,          args[_i++]);
  getArgAs_Double(float,        textFieldHeight,         args[_i++]);
  getArgAs_END

  ImVec2 textFieldSize;
  textFieldSize.x = textFieldWidth;
  textFieldSize.y = textFieldHeight;
  return ape_object_make_bool(igInputTextMultiline(textFieldName, &outPointer[outPointerBytesFirst], outPointerBytesCountMax, textFieldSize, 0, 0, 0));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureProfileBegin GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*mark*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("profileBegin")
  getArgAs_CChars(const char *, mark, args[_i++]);
  getArgAs_END

  profileBegin(mark);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureProfileEnd GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*mark*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("profileEnd")
  getArgAs_CChars(const char *, mark, args[_i++]);
  getArgAs_END

  profileEnd(mark);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSystemCommand GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*command*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("systemCommand")
  getArgAs_CChars(const char *, command, args[_i++]);
  getArgAs_END

  char * output = 0;
  redFSystem(command, &output, 0);
  std::string outputString = output;
  redFFree(output);

  return ape_object_make_string(ape, outputString.c_str());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlGetIntegerv GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*enum*/,
    APE_OBJECT_NUMBER/*outPointer*/,
    APE_OBJECT_NUMBER/*outPointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("glGetIntegerv")
  getArgAs_Double(unsigned,         anenum,               args[_i++]);
  getArgAs_Pointer(unsigned char *, outPointer,           args[_i++]);
  getArgAs_Double(uint64_t,         outPointerBytesFirst, args[_i++]);
  getArgAs_END

  void (*getIntegerv)(unsigned anenum, void * outPointer) = (void (*)(unsigned, void *))glfwGetProcAddress("glGetIntegerv");
  if (getIntegerv != 0) {
    getIntegerv(anenum, &outPointer[outPointerBytesFirst]);
  }

  return ape_object_make_bool(getIntegerv != 0);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetUniqueNumber GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

#ifdef _WIN32
#define redInternalInterlockedExchangeAdd64(ADDRESS, INCREMENT) InterlockedExchangeAdd64((volatile LONG64 *)ADDRESS, INCREMENT)
#endif
#ifdef __linux__
#define redInternalInterlockedExchangeAdd64(ADDRESS, INCREMENT) __sync_fetch_and_add(ADDRESS, INCREMENT)
#endif

  volatile uint64_t number = redInternalInterlockedExchangeAdd64(&gUniqueNumber, 1);

  return ape_object_make_number((double)number);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetUint64Max GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)((uint64_t)-1));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetLibGameHandle GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

#if defined(GAME_SCRIPT_NATIVE)
  return ape_object_make_number(_gsPointerToNumber(libgame));
#else
  return ape_object_make_number(0.0);
#endif
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetLibThread2Handle GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

#if defined(GAME_SCRIPT_NATIVE)
  return ape_object_make_number(_gsPointerToNumber(libthread2));
#else
  return ape_object_make_number(0.0);
#endif
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetGlfwWindowHandle GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number(_gsPointerToNumber(redFGetGLFWwindowPointer()));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetLastDragAndDropCounter GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)gDragAndDropCounter);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetLastDragAndDropFilepathsCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)gDragAndDropFilepaths.size());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetLastDragAndDropFilepath GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*filepathIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("getLastDragAndDropFilepath")
  getArgAs_Double(uint64_t, filepathIndex, args[_i++]);
  getArgAs_END

  return ape_object_make_string(ape, gDragAndDropFilepaths[filepathIndex].c_str());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetLastDragAndDropPositionX GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)gDragAndDropPositionX);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetLastDragAndDropPositionY GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)gDragAndDropPositionY);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGithubR_lyehLz4xEncode GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/,
    APE_OBJECT_NUMBER/*pointerBytesCount*/,
    APE_OBJECT_NUMBER/*outPointer*/,
    APE_OBJECT_NUMBER/*outPointerBytesFirst*/,
    APE_OBJECT_NUMBER/*outPointerBytesCount*/,
    APE_OBJECT_NUMBER/*flags*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("githubR_lyehLz4xEncode")
  getArgAs_Pointer(const unsigned char *, pointer,              args[_i++]);
  getArgAs_Double(unsigned,               pointerBytesFirst,    args[_i++]);
  getArgAs_Double(unsigned,               pointerBytesCount,    args[_i++]);
  getArgAs_Pointer(unsigned char *,       outPointer,           args[_i++]);
  getArgAs_Double(unsigned,               outPointerBytesFirst, args[_i++]);
  getArgAs_Double(unsigned,               outPointerBytesCount, args[_i++]);
  getArgAs_Double(unsigned,               flags,                args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)lz4x_encode(&pointer[pointerBytesFirst], pointerBytesCount, &outPointer[outPointerBytesFirst], outPointerBytesCount, flags));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGithubR_lyehLz4xDecode GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/,
    APE_OBJECT_NUMBER/*pointerBytesCount*/,
    APE_OBJECT_NUMBER/*outPointer*/,
    APE_OBJECT_NUMBER/*outPointerBytesFirst*/,
    APE_OBJECT_NUMBER/*outPointerBytesCount*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("githubR_lyehLz4xDecode")
  getArgAs_Pointer(const unsigned char *, pointer,              args[_i++]);
  getArgAs_Double(unsigned,               pointerBytesFirst,    args[_i++]);
  getArgAs_Double(unsigned,               pointerBytesCount,    args[_i++]);
  getArgAs_Pointer(unsigned char *,       outPointer,           args[_i++]);
  getArgAs_Double(unsigned,               outPointerBytesFirst, args[_i++]);
  getArgAs_Double(unsigned,               outPointerBytesCount, args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)lz4x_decode(&pointer[pointerBytesFirst], pointerBytesCount, &outPointer[outPointerBytesFirst], outPointerBytesCount));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGithubR_lyehLz4xBoundsEncodeOutBytesCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*bytesCount*/,
    APE_OBJECT_NUMBER/*flags*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("githubR_lyehLz4xBoundsEncodeOutBytesCount")
  getArgAs_Double(unsigned, bytesCount, args[_i++]);
  getArgAs_Double(unsigned, flags,      args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)lz4x_bounds(bytesCount, flags));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGithubR_lyehUlzEncode GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/,
    APE_OBJECT_NUMBER/*pointerBytesCount*/,
    APE_OBJECT_NUMBER/*outPointer*/,
    APE_OBJECT_NUMBER/*outPointerBytesFirst*/,
    APE_OBJECT_NUMBER/*outPointerBytesCount*/,
    APE_OBJECT_NUMBER/*flags*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("githubR_lyehUlzEncode")
  getArgAs_Pointer(const unsigned char *, pointer,              args[_i++]);
  getArgAs_Double(unsigned,               pointerBytesFirst,    args[_i++]);
  getArgAs_Double(unsigned,               pointerBytesCount,    args[_i++]);
  getArgAs_Pointer(unsigned char *,       outPointer,           args[_i++]);
  getArgAs_Double(unsigned,               outPointerBytesFirst, args[_i++]);
  getArgAs_Double(unsigned,               outPointerBytesCount, args[_i++]);
  getArgAs_Double(unsigned,               flags,                args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)ulz_encode(&pointer[pointerBytesFirst], pointerBytesCount, &outPointer[outPointerBytesFirst], outPointerBytesCount, flags));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGithubR_lyehUlzDecode GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/,
    APE_OBJECT_NUMBER/*pointerBytesCount*/,
    APE_OBJECT_NUMBER/*outPointer*/,
    APE_OBJECT_NUMBER/*outPointerBytesFirst*/,
    APE_OBJECT_NUMBER/*outPointerBytesCount*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("githubR_lyehUlzDecode")
  getArgAs_Pointer(const unsigned char *, pointer,              args[_i++]);
  getArgAs_Double(unsigned,               pointerBytesFirst,    args[_i++]);
  getArgAs_Double(unsigned,               pointerBytesCount,    args[_i++]);
  getArgAs_Pointer(unsigned char *,       outPointer,           args[_i++]);
  getArgAs_Double(unsigned,               outPointerBytesFirst, args[_i++]);
  getArgAs_Double(unsigned,               outPointerBytesCount, args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)ulz_decode(&pointer[pointerBytesFirst], pointerBytesCount, &outPointer[outPointerBytesFirst], outPointerBytesCount));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGithubR_lyehUlzBoundsEncodeOutBytesCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*bytesCount*/,
    APE_OBJECT_NUMBER/*flags*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("githubR_lyehUlzBoundsEncodeOutBytesCount")
  getArgAs_Double(unsigned, bytesCount, args[_i++]);
  getArgAs_Double(unsigned, flags,      args[_i++]);
  getArgAs_END

  return ape_object_make_number((double)ulz_bounds(bytesCount, flags));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureThread2Run GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  if (gThread2 != 0) {
    if (redFThreadIsRunning(gThread2[0]) == 0) {
      gThread2StopSignal = 0;
      redFThreadStart(gThread2[0]);
    }
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureThread2StopAndWaitFor GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  if (gThread2 != 0) {
    gThread2StopSignal = 1;
    if (redFThreadIsRunning(gThread2[0]) == 1) {
      redFThreadWaitFor(gThread2[0], 1, -1);
    }
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureThread2IsRunning GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  bool isRunning = false;
  if (gThread2 != 0) {
    isRunning = (bool)redFThreadIsRunning(gThread2[0]);
  }

  return ape_object_make_bool(isRunning);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetGameScriptString GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  if (gApeCodeCharsCurrentlyRunning != 0) {
    return ape_object_make_string(ape, gApeCodeCharsCurrentlyRunning);
  } else {
    return ape_object_make_string(ape, "");
  }
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSetGameScriptStringForNextFrame GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*script*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("setGameScriptStringForNextFrame")
  getArgAs_CChars(const char *, script, args[_i++]);
  getArgAs_END

  gApeCodeCharsNextRunning = script;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSetGameScriptStringForNextFrameFromPointer GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("setGameScriptStringForNextFrameFromPointer")
  getArgAs_Pointer(const char *, script,           args[_i++]);
  getArgAs_Double(uint64_t,      scriptBytesFirst, args[_i++]);
  getArgAs_END

  gApeCodeCharsNextRunning = &script[scriptBytesFirst];

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetThread2ScriptString GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  if (gApeCodeCharsCurrentlyRunningThread2 != 0) {
    return ape_object_make_string(ape, gApeCodeCharsCurrentlyRunningThread2);
  } else {
    return ape_object_make_string(ape, "");
  }
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSetThread2ScriptStringForNextFrame GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*script*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("setThread2ScriptStringForNextFrame")
  getArgAs_CChars(const char *, script, args[_i++]);
  getArgAs_END

  gApeCodeCharsNextRunningThread2 = script;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSetThread2ScriptStringForNextFrameFromPointer GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("setThread2ScriptStringForNextFrameFromPointer")
  getArgAs_Pointer(const char *, script,           args[_i++]);
  getArgAs_Double(uint64_t,      scriptBytesFirst, args[_i++]);
  getArgAs_END

  gApeCodeCharsNextRunningThread2 = &script[scriptBytesFirst];

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureLibGameScriptExternalProcedureReload GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_BOOL/*printErrors*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("libGameScriptExternalProcedureReload")
  getArgAs_Bool(bool, printErrors, args[_i++]);
  getArgAs_END

#if defined(__linux__)
  if (gExternalLibraryHandle != 0) {
    dlclose(gExternalLibraryHandle);
    gExternalLibraryHandle = 0;
  }
  gExternalLibraryHandle = dlopen("/opt/GameScript/libgame_script_external_procedure.so", RTLD_NOW | RTLD_GLOBAL);
  if (gExternalLibraryHandle == 0) {
    std::string filepath = gCurrentExeDir;
    filepath += "libgame_script_external_procedure.so";
    gExternalLibraryHandle = dlopen(filepath.c_str(), RTLD_NOW | RTLD_GLOBAL);
  }
  if (gExternalLibraryHandle != 0) {
    gExternalLibraryProcedureCall2 = (void (*)(double, double))dlsym(gExternalLibraryHandle, "libGameScriptExternalProcedureCall2");
    gExternalLibraryProcedureCall3 = (void (*)(double, double, double))dlsym(gExternalLibraryHandle, "libGameScriptExternalProcedureCall3");
  } else {
    if (printErrors == true) {
      _gsPrintThreadSafe("[Game Script][libGameScriptExternalProcedureReload][dlopen(\"/opt/GameScript/libgame_script_external_procedure.so\") returned NULL]\n");
      _gsPrintThreadSafe(dlerror());
    }
  }
#elif defined(_WIN32)
  if (gExternalLibraryHandle != 0) {
    FreeLibrary((HMODULE)gExternalLibraryHandle);
    gExternalLibraryHandle = 0;
  }
  gExternalLibraryHandle = LoadLibraryA("C:/GameScript/game_script_external_procedure.dll");
  if (gExternalLibraryHandle == 0) {
    gExternalLibraryHandle = LoadLibraryA("game_script_external_procedure.dll");
  }
  if (gExternalLibraryHandle != 0) {
    gExternalLibraryProcedureCall2 = (void (*)(double, double))GetProcAddress((HMODULE)gExternalLibraryHandle, "libGameScriptExternalProcedureCall2");
    gExternalLibraryProcedureCall3 = (void (*)(double, double, double))GetProcAddress((HMODULE)gExternalLibraryHandle, "libGameScriptExternalProcedureCall3");
  }
#else
#error Implement
#endif

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureLibGameScriptExternalProcedureCall2 GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*parameter1*/,
    APE_OBJECT_NUMBER/*parameter2*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("libGameScriptExternalProcedureCall2")
  getArgAs_Double(double, parameter1, args[_i++]);
  getArgAs_Double(double, parameter2, args[_i++]);
  getArgAs_END

  if (gExternalLibraryProcedureCall2 != 0) {
    gExternalLibraryProcedureCall2(parameter1, parameter2);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureLibGameScriptExternalProcedureCall3 GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*parameter1*/,
    APE_OBJECT_NUMBER/*parameter2*/,
    APE_OBJECT_NUMBER/*parameter3*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("libGameScriptExternalProcedureCall3")
  getArgAs_Double(double, parameter1, args[_i++]);
  getArgAs_Double(double, parameter2, args[_i++]);
  getArgAs_Double(double, parameter3, args[_i++]);
  getArgAs_END

  if (gExternalLibraryProcedureCall3 != 0) {
    gExternalLibraryProcedureCall3(parameter1, parameter2, parameter3);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureProgramGetArgumentsCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)gProgramArguments.size());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureProgramGetArgument GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*index*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("programGetArgument")
  getArgAs_Double(uint64_t, index, args[_i++]);
  getArgAs_END

  return ape_object_make_string(ape, gProgramArguments[index].c_str());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureProgramClose GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  glfwSetWindowShouldClose((GLFWwindow *)redFGetGLFWwindowPointer(), 1);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureAsin GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*x*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("asin")
  getArgAs_Double(double, x, args[_i++]);
  getArgAs_END

  return ape_object_make_number(asin(x));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureAcos GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*x*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("acos")
  getArgAs_Double(double, x, args[_i++]);
  getArgAs_END

  return ape_object_make_number(acos(x));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureAtan GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*x*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("atan")
  getArgAs_Double(double, x, args[_i++]);
  getArgAs_END

  return ape_object_make_number(atan(x));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureAtan2 GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*x*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("atan2")
  getArgAs_Double(double, y, args[_i++]);
  getArgAs_Double(double, x, args[_i++]);
  getArgAs_END

  return ape_object_make_number(atan2(y, x));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fGetSizeOfInBytes GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)(sizeof(embree::AffineSpace3f)));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fSetDefaultInitialize GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*outPointer*/,
    APE_OBJECT_NUMBER/*outPointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fSetDefaultInitialize")
  getArgAs_Pointer(unsigned char *, outPointer,           args[_i++]);
  getArgAs_Double(uint64_t,         outPointerBytesFirst, args[_i++]);
  getArgAs_END

  embree::AffineSpace3f * pointer = (embree::AffineSpace3f *)(&outPointer[outPointerBytesFirst]);
  embree::AffineSpace3f   value   = embree::AffineSpace3f(embree::one);
  pointer[0] = value;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fSetInitialize GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*outPointer*/,
    APE_OBJECT_NUMBER/*outPointerBytesFirst*/,
    APE_OBJECT_NUMBER/*v0*/,
    APE_OBJECT_NUMBER/*v1*/,
    APE_OBJECT_NUMBER/*v2*/,
    APE_OBJECT_NUMBER/*v3*/,
    APE_OBJECT_NUMBER/*v4*/,
    APE_OBJECT_NUMBER/*v5*/,
    APE_OBJECT_NUMBER/*v6*/,
    APE_OBJECT_NUMBER/*v7*/,
    APE_OBJECT_NUMBER/*v8*/,
    APE_OBJECT_NUMBER/*v9*/,
    APE_OBJECT_NUMBER/*v10*/,
    APE_OBJECT_NUMBER/*v11*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fSetInitialize")
  getArgAs_Pointer(unsigned char *, outPointer,           args[_i++]);
  getArgAs_Double(uint64_t,         outPointerBytesFirst, args[_i++]);
  getArgAs_Double(float,            v0,                   args[_i++]);
  getArgAs_Double(float,            v1,                   args[_i++]);
  getArgAs_Double(float,            v2,                   args[_i++]);
  getArgAs_Double(float,            v3,                   args[_i++]);
  getArgAs_Double(float,            v4,                   args[_i++]);
  getArgAs_Double(float,            v5,                   args[_i++]);
  getArgAs_Double(float,            v6,                   args[_i++]);
  getArgAs_Double(float,            v7,                   args[_i++]);
  getArgAs_Double(float,            v8,                   args[_i++]);
  getArgAs_Double(float,            v9,                   args[_i++]);
  getArgAs_Double(float,            v10,                  args[_i++]);
  getArgAs_Double(float,            v11,                  args[_i++]);
  getArgAs_END

  embree::AffineSpace3f * pointer = (embree::AffineSpace3f *)(&outPointer[outPointerBytesFirst]);
  embree::AffineSpace3f   value   = embree::AffineSpace3f(
    embree::LinearSpace3f(v0, v1, v2,
                          v3, v4, v5,
                          v6, v7, v8),
            embree::Vec3f(v9,v10,v11)
  );
  pointer[0] = value;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fSetLookAtPoint GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*outPointer*/,
    APE_OBJECT_NUMBER/*outPointerBytesFirst*/,
    APE_OBJECT_NUMBER/*posX*/,
    APE_OBJECT_NUMBER/*posY*/,
    APE_OBJECT_NUMBER/*posZ*/,
    APE_OBJECT_NUMBER/*targetX*/,
    APE_OBJECT_NUMBER/*targetY*/,
    APE_OBJECT_NUMBER/*targetZ*/,
    APE_OBJECT_NUMBER/*upX*/,
    APE_OBJECT_NUMBER/*upY*/,
    APE_OBJECT_NUMBER/*upZ*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fSetLookAtPoint")
  getArgAs_Pointer(unsigned char *, outPointer,           args[_i++]);
  getArgAs_Double(uint64_t,         outPointerBytesFirst, args[_i++]);
  getArgAs_Double(float,            posX,                 args[_i++]);
  getArgAs_Double(float,            posY,                 args[_i++]);
  getArgAs_Double(float,            posZ,                 args[_i++]);
  getArgAs_Double(float,            targetX,              args[_i++]);
  getArgAs_Double(float,            targetY,              args[_i++]);
  getArgAs_Double(float,            targetZ,              args[_i++]);
  getArgAs_Double(float,            upX,                  args[_i++]);
  getArgAs_Double(float,            upY,                  args[_i++]);
  getArgAs_Double(float,            upZ,                  args[_i++]);
  getArgAs_END

  embree::AffineSpace3f * pointer = (embree::AffineSpace3f *)(&outPointer[outPointerBytesFirst]);
  embree::AffineSpace3f   value   = embree::AffineSpace3f::lookAtPoint(embree::Vec3f(posX, posY, posZ), embree::Vec3f(targetX, targetY, targetZ), embree::Vec3f(upX, upY, upZ));
  pointer[0] = value;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fScale GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*outPointer*/,
    APE_OBJECT_NUMBER/*outPointerBytesFirst*/,
    APE_OBJECT_NUMBER/*scaleX*/,
    APE_OBJECT_NUMBER/*scaleY*/,
    APE_OBJECT_NUMBER/*scaleZ*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fScale")
  getArgAs_Pointer(unsigned char *, outPointer,           args[_i++]);
  getArgAs_Double(uint64_t,         outPointerBytesFirst, args[_i++]);
  getArgAs_Double(float,            scaleX,               args[_i++]);
  getArgAs_Double(float,            scaleY,               args[_i++]);
  getArgAs_Double(float,            scaleZ,               args[_i++]);
  getArgAs_END

  embree::AffineSpace3f * pointer  = (embree::AffineSpace3f *)(&outPointer[outPointerBytesFirst]);
  embree::AffineSpace3f   value    = embree::AffineSpace3f::scale(embree::Vec3f(scaleX, scaleY, scaleZ));
  embree::AffineSpace3f   oldValue = pointer[0];
  embree::AffineSpace3f   newValue = oldValue * value;
  pointer[0] = newValue;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fTranslate GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*outPointer*/,
    APE_OBJECT_NUMBER/*outPointerBytesFirst*/,
    APE_OBJECT_NUMBER/*translateX*/,
    APE_OBJECT_NUMBER/*translateY*/,
    APE_OBJECT_NUMBER/*translateZ*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fTranslate")
  getArgAs_Pointer(unsigned char *, outPointer,           args[_i++]);
  getArgAs_Double(uint64_t,         outPointerBytesFirst, args[_i++]);
  getArgAs_Double(float,            translateX,           args[_i++]);
  getArgAs_Double(float,            translateY,           args[_i++]);
  getArgAs_Double(float,            translateZ,           args[_i++]);
  getArgAs_END

  embree::AffineSpace3f * pointer  = (embree::AffineSpace3f *)(&outPointer[outPointerBytesFirst]);
  embree::AffineSpace3f   value    = embree::AffineSpace3f::translate(embree::Vec3f(translateX, translateY, translateZ));
  embree::AffineSpace3f   oldValue = pointer[0];
  embree::AffineSpace3f   newValue = oldValue * value;
  pointer[0] = newValue;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fRotate GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*outPointer*/,
    APE_OBJECT_NUMBER/*outPointerBytesFirst*/,
    APE_OBJECT_NUMBER/*rotatePosX*/,
    APE_OBJECT_NUMBER/*rotatePosY*/,
    APE_OBJECT_NUMBER/*rotatePosZ*/,
    APE_OBJECT_NUMBER/*rotateAxisX*/,
    APE_OBJECT_NUMBER/*rotateAxisY*/,
    APE_OBJECT_NUMBER/*rotateAxisZ*/,
    APE_OBJECT_NUMBER/*rotateAngle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fRotate")
  getArgAs_Pointer(unsigned char *, outPointer,           args[_i++]);
  getArgAs_Double(uint64_t,         outPointerBytesFirst, args[_i++]);
  getArgAs_Double(float,            rotatePosX,           args[_i++]);
  getArgAs_Double(float,            rotatePosY,           args[_i++]);
  getArgAs_Double(float,            rotatePosZ,           args[_i++]);
  getArgAs_Double(float,            rotateAxisX,          args[_i++]);
  getArgAs_Double(float,            rotateAxisY,          args[_i++]);
  getArgAs_Double(float,            rotateAxisZ,          args[_i++]);
  getArgAs_Double(float,            rotateAngle,          args[_i++]);
  getArgAs_END

  embree::AffineSpace3f * pointer  = (embree::AffineSpace3f *)(&outPointer[outPointerBytesFirst]);
  embree::AffineSpace3f   value    = embree::AffineSpace3f::rotate(embree::Vec3f(rotatePosX, rotatePosY, rotatePosZ), embree::Vec3f(rotateAxisX, rotateAxisY, rotateAxisZ), rotateAngle);
  embree::AffineSpace3f   oldValue = pointer[0];
  embree::AffineSpace3f   newValue = value * oldValue;
  pointer[0] = newValue;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fGetLVXX GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fGetLVXX")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  embree::AffineSpace3f * p = (embree::AffineSpace3f *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number(p[0].l.vx.x);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fGetLVXY GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fGetLVXY")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  embree::AffineSpace3f * p = (embree::AffineSpace3f *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number(p[0].l.vx.y);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fGetLVXZ GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fGetLVXZ")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  embree::AffineSpace3f * p = (embree::AffineSpace3f *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number(p[0].l.vx.z);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fGetLVYX GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fGetLVYX")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  embree::AffineSpace3f * p = (embree::AffineSpace3f *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number(p[0].l.vy.x);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fGetLVYY GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fGetLVYY")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  embree::AffineSpace3f * p = (embree::AffineSpace3f *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number(p[0].l.vy.y);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fGetLVYZ GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fGetLVYZ")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  embree::AffineSpace3f * p = (embree::AffineSpace3f *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number(p[0].l.vy.z);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fGetLVZX GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fGetLVZX")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  embree::AffineSpace3f * p = (embree::AffineSpace3f *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number(p[0].l.vz.x);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fGetLVZY GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fGetLVZY")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  embree::AffineSpace3f * p = (embree::AffineSpace3f *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number(p[0].l.vz.y);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fGetLVZZ GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fGetLVZZ")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  embree::AffineSpace3f * p = (embree::AffineSpace3f *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number(p[0].l.vz.z);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fGetPX GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fGetPX")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  embree::AffineSpace3f * p = (embree::AffineSpace3f *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number(p[0].p.x);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fGetPY GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fGetPY")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  embree::AffineSpace3f * p = (embree::AffineSpace3f *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number(p[0].p.y);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fGetPZ GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointer*/,
    APE_OBJECT_NUMBER/*pointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fGetPZ")
  getArgAs_Pointer(unsigned char *, pointer,           args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst, args[_i++]);
  getArgAs_END

  embree::AffineSpace3f * p = (embree::AffineSpace3f *)(&pointer[pointerBytesFirst]);

  return ape_object_make_number(p[0].p.z);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fCopyFromArray GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*in12FloatsPointer*/,
    APE_OBJECT_NUMBER/*in12FloatsPointerBytesFirst*/,
    APE_OBJECT_NUMBER/*outAffineSpace3fPointer*/,
    APE_OBJECT_NUMBER/*outAffineSpace3fPointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fCopyFromArray")
  getArgAs_Pointer(unsigned char *, pointer,              args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst,    args[_i++]);
  getArgAs_Pointer(unsigned char *, outPointer,           args[_i++]);
  getArgAs_Double(uint64_t,         outPointerBytesFirst, args[_i++]);
  getArgAs_END

  embree::AffineSpace3f   newValue = embree::copyFromArray((const float *)(&pointer[pointerBytesFirst]));
  embree::AffineSpace3f * p        = (embree::AffineSpace3f *)(&outPointer[outPointerBytesFirst]);
  p[0] = newValue;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtAffineSpace3fCopyToArray GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*inAffineSpace3fPointer*/,
    APE_OBJECT_NUMBER/*inAffineSpace3fPointerBytesFirst*/,
    APE_OBJECT_NUMBER/*out12FloatsPointer*/,
    APE_OBJECT_NUMBER/*out12FloatsPointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertAffineSpace3fCopyToArray")
  getArgAs_Pointer(unsigned char *, pointer,              args[_i++]);
  getArgAs_Double(uint64_t,         pointerBytesFirst,    args[_i++]);
  getArgAs_Pointer(unsigned char *, outPointer,           args[_i++]);
  getArgAs_Double(uint64_t,         outPointerBytesFirst, args[_i++]);
  getArgAs_END

  embree::AffineSpace3f * ap    = (embree::AffineSpace3f *)(&pointer[pointerBytesFirst]);
  float *                 p     = (float *)(&outPointer[outPointerBytesFirst]);
  embree::AffineSpace3f   value = ap[0];

  embree::Array12f array = embree::copyToArray(value);

  for (int i = 0; i < 12; i += 1) {
    p[i] = array.values[i];
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtCreateDevice GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*typeDefaultIsdefault*/,
    APE_OBJECT_NUMBER/*numThreadsDefaultIs0*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertCreateDevice")
  getArgAs_CChars(const char *, type,       args[_i++]);
  getArgAs_Double(size_t,       numThreads, args[_i++]);
  getArgAs_END

  embree::Device * handle = embree::Device::rtCreateDevice(type, numThreads);

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtDestroyDevice GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertDestroyDevice")
  getArgAs_Pointer(embree::Device *, handle, args[_i++]);
  getArgAs_END

  delete handle;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtNewCamera GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_STRING/*type*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertNewCamera")
  getArgAs_Pointer(embree::Device *, device, args[_i++]);
  getArgAs_CChars(const char *,      type,   args[_i++]);
  getArgAs_END

  void * handle = (void *)device->rtNewCamera(type);

  return ape_object_make_number(_gsPointerToNumber(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtNewData GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_STRING/*type*/,
    APE_OBJECT_NUMBER/*bytes*/,
    APE_OBJECT_NUMBER/*dataPointer*/,
    APE_OBJECT_NUMBER/*dataPointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertNewData")
  getArgAs_Pointer(embree::Device *, device,                args[_i++]);
  getArgAs_CChars(const char *,      type,                  args[_i++]);
  getArgAs_Double(size_t,            bytes,                 args[_i++]);
  getArgAs_Pointer(unsigned char *,  dataPointer,           args[_i++]);
  getArgAs_Double(uint64_t,          dataPointerBytesFirst, args[_i++]);
  getArgAs_END

  void * _data = NULL;
  if (dataPointer != NULL) {
    _data = (void *)&dataPointer[dataPointerBytesFirst];
  }

  void * handle = (void *)device->rtNewData(type, bytes, (const void *)_data);

  return ape_object_make_number(_gsPointerToNumber(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtNewDataFromFile GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_STRING/*type*/,
    APE_OBJECT_STRING/*file*/,
    APE_OBJECT_NUMBER/*offset*/,
    APE_OBJECT_NUMBER/*bytes*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertNewDataFromFile")
  getArgAs_Pointer(embree::Device *, device,                args[_i++]);
  getArgAs_CChars(const char *,      type,                  args[_i++]);
  getArgAs_CChars(const char *,      file,                  args[_i++]);
  getArgAs_Double(size_t,            offset,                args[_i++]);
  getArgAs_Double(size_t,            bytes,                 args[_i++]);
  getArgAs_END

  void * handle = (void *)device->rtNewDataFromFile(type, file, offset, bytes);

  return ape_object_make_number(_gsPointerToNumber(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtNewImage GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_STRING/*type*/,
    APE_OBJECT_NUMBER/*width*/,
    APE_OBJECT_NUMBER/*height*/,
    APE_OBJECT_NUMBER/*dataPointer*/,
    APE_OBJECT_NUMBER/*dataPointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertNewImage")
  getArgAs_Pointer(embree::Device *, device,                args[_i++]);
  getArgAs_CChars(const char *,      type,                  args[_i++]);
  getArgAs_Double(size_t,            width,                 args[_i++]);
  getArgAs_Double(size_t,            height,                args[_i++]);
  getArgAs_Pointer(unsigned char *,  dataPointer,           args[_i++]);
  getArgAs_Double(uint64_t,          dataPointerBytesFirst, args[_i++]);
  getArgAs_END

  void * _data = NULL;
  if (dataPointer != NULL) {
    _data = (void *)&dataPointer[dataPointerBytesFirst];
  }

  void * handle = (void *)device->rtNewImage(type, width, height, (const void *)_data);

  return ape_object_make_number(_gsPointerToNumber(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtNewImageFromFile GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_STRING/*file*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertNewImageFromFile")
  getArgAs_Pointer(embree::Device *, device, args[_i++]);
  getArgAs_CChars(const char *,      file,   args[_i++]);
  getArgAs_END

  void * handle = (void *)device->rtNewImageFromFile(file);

  return ape_object_make_number(_gsPointerToNumber(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtNewTexture GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_STRING/*type*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertNewTexture")
  getArgAs_Pointer(embree::Device *, device, args[_i++]);
  getArgAs_CChars(const char *,      type,   args[_i++]);
  getArgAs_END

  void * handle = (void *)device->rtNewTexture(type);

  return ape_object_make_number(_gsPointerToNumber(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtNewMaterial GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_STRING/*type*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertNewMaterial")
  getArgAs_Pointer(embree::Device *, device, args[_i++]);
  getArgAs_CChars(const char *,      type,   args[_i++]);
  getArgAs_END

  void * handle = (void *)device->rtNewMaterial(type);

  return ape_object_make_number(_gsPointerToNumber(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtNewShape GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_STRING/*type*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertNewShape")
  getArgAs_Pointer(embree::Device *, device, args[_i++]);
  getArgAs_CChars(const char *,      type,   args[_i++]);
  getArgAs_END

  void * handle = (void *)device->rtNewShape(type);

  return ape_object_make_number(_gsPointerToNumber(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtNewLight GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_STRING/*type*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertNewLight")
  getArgAs_Pointer(embree::Device *, device, args[_i++]);
  getArgAs_CChars(const char *,      type,   args[_i++]);
  getArgAs_END

  void * handle = (void *)device->rtNewLight(type);

  return ape_object_make_number(_gsPointerToNumber(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtNewShapePrimitive GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*shapeHandle*/,
    APE_OBJECT_NUMBER/*materialHandle*/,
    APE_OBJECT_NUMBER/*transformPointer*/,
    APE_OBJECT_NUMBER/*transformPointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertNewShapePrimitive")
  getArgAs_Pointer(embree::Device *,           device,                     args[_i++]);
  getArgAs_Pointer(embree::Device::RTShape,    shape,                      args[_i++]);
  getArgAs_Pointer(embree::Device::RTMaterial, material,                   args[_i++]);
  getArgAs_Pointer(unsigned char *,            transformPointer,           args[_i++]);
  getArgAs_Double(uint64_t,                    transformPointerBytesFirst, args[_i++]);
  getArgAs_END

  void * transform = NULL;
  if (transformPointer != NULL) {
    transform = (void *)&transformPointer[transformPointerBytesFirst];
  }

  void * handle = (void *)device->rtNewShapePrimitive(shape, material, (const float *)transform);

  return ape_object_make_number(_gsPointerToNumber(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtNewLightPrimitive GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*lightHandle*/,
    APE_OBJECT_NUMBER/*transformPointer*/,
    APE_OBJECT_NUMBER/*transformPointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertNewLightPrimitive")
  getArgAs_Pointer(embree::Device *,        device,                     args[_i++]);
  getArgAs_Pointer(embree::Device::RTLight, light,                      args[_i++]);
  getArgAs_Pointer(unsigned char *,         transformPointer,           args[_i++]);
  getArgAs_Double(uint64_t,                 transformPointerBytesFirst, args[_i++]);
  getArgAs_END

  void * transform = NULL;
  if (transformPointer != NULL) {
    transform = (void *)&transformPointer[transformPointerBytesFirst];
  }

  void * handle = (void *)device->rtNewLightPrimitive(light, (const float *)transform);

  return ape_object_make_number(_gsPointerToNumber(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtTransformPrimitive GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*primitiveHandle*/,
    APE_OBJECT_NUMBER/*transformPointer*/,
    APE_OBJECT_NUMBER/*transformPointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertTransformPrimitive")
  getArgAs_Pointer(embree::Device *,            device,                     args[_i++]);
  getArgAs_Pointer(embree::Device::RTPrimitive, primitive,                  args[_i++]);
  getArgAs_Pointer(unsigned char *,             transformPointer,           args[_i++]);
  getArgAs_Double(uint64_t,                     transformPointerBytesFirst, args[_i++]);
  getArgAs_END

  void * transform = NULL;
  if (transformPointer != NULL) {
    transform = (void *)&transformPointer[transformPointerBytesFirst];
  }

  void * handle = (void *)device->rtTransformPrimitive(primitive, (const float *)transform);

  return ape_object_make_number(_gsPointerToNumber(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtNewScene GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_STRING/*type*/,
    APE_OBJECT_NUMBER/*primitiveHandlesPointer*/,
    APE_OBJECT_NUMBER/*primitiveHandlesPointerBytesFirst*/,
    APE_OBJECT_NUMBER/*size*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertNewScene")
  getArgAs_Pointer(embree::Device *, device,                            args[_i++]);
  getArgAs_CChars(const char *,      type,                              args[_i++]);
  getArgAs_Pointer(unsigned char *,  primitiveHandlesPointer,           args[_i++]);
  getArgAs_Double(uint64_t,          primitiveHandlesPointerBytesFirst, args[_i++]);
  getArgAs_Double(size_t,            size,                              args[_i++]);
  getArgAs_END

  void * primitiveHandles = NULL;
  if (primitiveHandlesPointer != NULL) {
    primitiveHandles = (void *)&primitiveHandlesPointer[primitiveHandlesPointerBytesFirst];
  }

  void * handle = (void *)device->rtNewScene(type, (embree::Device::RTPrimitive *)primitiveHandles, size);

  return ape_object_make_number(_gsPointerToNumber(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtNewToneMapper GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_STRING/*type*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertNewToneMapper")
  getArgAs_Pointer(embree::Device *, device, args[_i++]);
  getArgAs_CChars(const char *,      type,   args[_i++]);
  getArgAs_END

  void * handle = (void *)device->rtNewToneMapper(type);

  return ape_object_make_number(_gsPointerToNumber(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtNewRenderer GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_STRING/*type*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertNewRenderer")
  getArgAs_Pointer(embree::Device *, device, args[_i++]);
  getArgAs_CChars(const char *,      type,   args[_i++]);
  getArgAs_END

  void * handle = (void *)device->rtNewRenderer(type);

  return ape_object_make_number(_gsPointerToNumber(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtNewFrameBuffer GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_STRING/*type*/,
    APE_OBJECT_NUMBER/*width*/,
    APE_OBJECT_NUMBER/*height*/,
    APE_OBJECT_NUMBER/*buffersDefaultIs1*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertNewFrameBuffer")
  getArgAs_Pointer(embree::Device *, device,  args[_i++]);
  getArgAs_CChars(const char *,      type,    args[_i++]);
  getArgAs_Double(size_t,            width,   args[_i++]);
  getArgAs_Double(size_t,            height,  args[_i++]);
  getArgAs_Double(size_t,            buffers, args[_i++]);
  getArgAs_END

  void * handle = (void *)device->rtNewFrameBuffer(type, width, height, buffers);

  return ape_object_make_number(_gsPointerToNumber(handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtGetFrameBufferWidth GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*frameBufferHandle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertGetFrameBufferWidth")
  getArgAs_Pointer(embree::Device *,              device,      args[_i++]);
  getArgAs_Pointer(embree::Device::RTFrameBuffer, frameBuffer, args[_i++]);
  getArgAs_END

  size_t width  = 0;
  size_t height = 0;
  device->rtGetFrameBufferSize(frameBuffer, width, height);

  return ape_object_make_number((double)width);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtGetFrameBufferHeight GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*frameBufferHandle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertGetFrameBufferHeight")
  getArgAs_Pointer(embree::Device *,              device,      args[_i++]);
  getArgAs_Pointer(embree::Device::RTFrameBuffer, frameBuffer, args[_i++]);
  getArgAs_END

  size_t width  = 0;
  size_t height = 0;
  device->rtGetFrameBufferSize(frameBuffer, width, height);

  return ape_object_make_number((double)height);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtMapFrameBuffer GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*frameBufferHandle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertMapFrameBuffer")
  getArgAs_Pointer(embree::Device *,              device,      args[_i++]);
  getArgAs_Pointer(embree::Device::RTFrameBuffer, frameBuffer, args[_i++]);
  getArgAs_END

  void * pointer = device->rtMapFrameBuffer(frameBuffer);

  return ape_object_make_number(_gsPointerToNumber(pointer));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtUnmapFrameBuffer GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*frameBufferHandle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertUnmapFrameBuffer")
  getArgAs_Pointer(embree::Device *,              device,      args[_i++]);
  getArgAs_Pointer(embree::Device::RTFrameBuffer, frameBuffer, args[_i++]);
  getArgAs_END

  device->rtUnmapFrameBuffer(frameBuffer);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtSwapBuffers GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*frameBufferHandle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertSwapBuffers")
  getArgAs_Pointer(embree::Device *,              device,      args[_i++]);
  getArgAs_Pointer(embree::Device::RTFrameBuffer, frameBuffer, args[_i++]);
  getArgAs_END

  device->rtSwapBuffers(frameBuffer);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtIncRef GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertIncRef")
  getArgAs_Pointer(embree::Device *,         device, args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle, args[_i++]);
  getArgAs_END

  device->rtIncRef(handle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtDecRef GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertDecRef")
  getArgAs_Pointer(embree::Device *,         device, args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle, args[_i++]);
  getArgAs_END

  device->rtDecRef(handle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtSetBool1 GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_BOOL/*x*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertSetBool1")
  getArgAs_Pointer(embree::Device *,         device,   args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle,   args[_i++]);
  getArgAs_CChars(const char *,              property, args[_i++]);
  getArgAs_Bool(bool,                        x,        args[_i++]);
  getArgAs_END

  device->rtSetBool1(handle, property, x);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtSetBool2 GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_BOOL/*x*/,
    APE_OBJECT_BOOL/*y*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertSetBool2")
  getArgAs_Pointer(embree::Device *,         device,   args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle,   args[_i++]);
  getArgAs_CChars(const char *,              property, args[_i++]);
  getArgAs_Bool(bool,                        x,        args[_i++]);
  getArgAs_Bool(bool,                        y,        args[_i++]);
  getArgAs_END

  device->rtSetBool2(handle, property, x, y);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtSetBool3 GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_BOOL/*x*/,
    APE_OBJECT_BOOL/*y*/,
    APE_OBJECT_BOOL/*z*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertSetBool3")
  getArgAs_Pointer(embree::Device *,         device,   args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle,   args[_i++]);
  getArgAs_CChars(const char *,              property, args[_i++]);
  getArgAs_Bool(bool,                        x,        args[_i++]);
  getArgAs_Bool(bool,                        y,        args[_i++]);
  getArgAs_Bool(bool,                        z,        args[_i++]);
  getArgAs_END

  device->rtSetBool3(handle, property, x, y, z);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtSetBool4 GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_BOOL/*x*/,
    APE_OBJECT_BOOL/*y*/,
    APE_OBJECT_BOOL/*z*/,
    APE_OBJECT_BOOL/*w*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertSetBool4")
  getArgAs_Pointer(embree::Device *,         device,   args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle,   args[_i++]);
  getArgAs_CChars(const char *,              property, args[_i++]);
  getArgAs_Bool(bool,                        x,        args[_i++]);
  getArgAs_Bool(bool,                        y,        args[_i++]);
  getArgAs_Bool(bool,                        z,        args[_i++]);
  getArgAs_Bool(bool,                        w,        args[_i++]);
  getArgAs_END

  device->rtSetBool4(handle, property, x, y, z, w);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtSetInt1 GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_NUMBER/*x*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertSetInt1")
  getArgAs_Pointer(embree::Device *,         device,   args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle,   args[_i++]);
  getArgAs_CChars(const char *,              property, args[_i++]);
  getArgAs_Double(int,                       x,        args[_i++]);
  getArgAs_END

  device->rtSetInt1(handle, property, x);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtSetInt2 GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertSetInt2")
  getArgAs_Pointer(embree::Device *,         device,   args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle,   args[_i++]);
  getArgAs_CChars(const char *,              property, args[_i++]);
  getArgAs_Double(int,                       x,        args[_i++]);
  getArgAs_Double(int,                       y,        args[_i++]);
  getArgAs_END

  device->rtSetInt2(handle, property, x, y);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtSetInt3 GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertSetInt3")
  getArgAs_Pointer(embree::Device *,         device,   args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle,   args[_i++]);
  getArgAs_CChars(const char *,              property, args[_i++]);
  getArgAs_Double(int,                       x,        args[_i++]);
  getArgAs_Double(int,                       y,        args[_i++]);
  getArgAs_Double(int,                       z,        args[_i++]);
  getArgAs_END

  device->rtSetInt3(handle, property, x, y, z);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtSetInt4 GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/,
    APE_OBJECT_NUMBER/*w*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertSetInt4")
  getArgAs_Pointer(embree::Device *,         device,   args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle,   args[_i++]);
  getArgAs_CChars(const char *,              property, args[_i++]);
  getArgAs_Double(int,                       x,        args[_i++]);
  getArgAs_Double(int,                       y,        args[_i++]);
  getArgAs_Double(int,                       z,        args[_i++]);
  getArgAs_Double(int,                       w,        args[_i++]);
  getArgAs_END

  device->rtSetInt4(handle, property, x, y, z, w);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtSetFloat1 GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_NUMBER/*x*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertSetFloat1")
  getArgAs_Pointer(embree::Device *,         device,   args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle,   args[_i++]);
  getArgAs_CChars(const char *,              property, args[_i++]);
  getArgAs_Double(float,                     x,        args[_i++]);
  getArgAs_END

  device->rtSetFloat1(handle, property, x);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtSetFloat2 GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertSetFloat2")
  getArgAs_Pointer(embree::Device *,         device,   args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle,   args[_i++]);
  getArgAs_CChars(const char *,              property, args[_i++]);
  getArgAs_Double(float,                     x,        args[_i++]);
  getArgAs_Double(float,                     y,        args[_i++]);
  getArgAs_END

  device->rtSetFloat2(handle, property, x, y);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtSetFloat3 GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertSetFloat3")
  getArgAs_Pointer(embree::Device *,         device,   args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle,   args[_i++]);
  getArgAs_CChars(const char *,              property, args[_i++]);
  getArgAs_Double(float,                     x,        args[_i++]);
  getArgAs_Double(float,                     y,        args[_i++]);
  getArgAs_Double(float,                     z,        args[_i++]);
  getArgAs_END

  device->rtSetFloat3(handle, property, x, y, z);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtSetFloat4 GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/,
    APE_OBJECT_NUMBER/*w*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertSetFloat4")
  getArgAs_Pointer(embree::Device *,         device,   args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle,   args[_i++]);
  getArgAs_CChars(const char *,              property, args[_i++]);
  getArgAs_Double(float,                     x,        args[_i++]);
  getArgAs_Double(float,                     y,        args[_i++]);
  getArgAs_Double(float,                     z,        args[_i++]);
  getArgAs_Double(float,                     w,        args[_i++]);
  getArgAs_END

  device->rtSetFloat4(handle, property, x, y, z, w);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtSetArray GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_STRING/*type*/,
    APE_OBJECT_NUMBER/*dataHandle*/,
    APE_OBJECT_NUMBER/*size*/,
    APE_OBJECT_NUMBER/*stride*/,
    APE_OBJECT_NUMBER/*ofs*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertSetArray")
  getArgAs_Pointer(embree::Device *,         device,   args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle,   args[_i++]);
  getArgAs_CChars(const char *,              property, args[_i++]);
  getArgAs_CChars(const char *,              type,     args[_i++]);
  getArgAs_Pointer(embree::Device::RTData,   _data,    args[_i++]);
  getArgAs_Double(size_t,                    size,     args[_i++]);
  getArgAs_Double(size_t,                    stride,   args[_i++]);
  getArgAs_Double(size_t,                    ofs,      args[_i++]);
  getArgAs_END

  device->rtSetArray(handle, property, type, _data, size, stride, ofs);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtSetString GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_STRING/*str*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertSetString")
  getArgAs_Pointer(embree::Device *,         device,   args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle,   args[_i++]);
  getArgAs_CChars(const char *,              property, args[_i++]);
  getArgAs_CChars(const char *,              str,      args[_i++]);
  getArgAs_END

  device->rtSetString(handle, property, str);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtSetImage GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_NUMBER/*imageHandle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertSetImage")
  getArgAs_Pointer(embree::Device *,         device,   args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle,   args[_i++]);
  getArgAs_CChars(const char *,              property, args[_i++]);
  getArgAs_Pointer(embree::Device::RTImage,  image,    args[_i++]);
  getArgAs_END

  device->rtSetImage(handle, property, image);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtSetTexture GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_NUMBER/*textureHandle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertSetTexture")
  getArgAs_Pointer(embree::Device *,          device,   args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle,  handle,   args[_i++]);
  getArgAs_CChars(const char *,               property, args[_i++]);
  getArgAs_Pointer(embree::Device::RTTexture, texture,  args[_i++]);
  getArgAs_END

  device->rtSetTexture(handle, property, texture);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtSetTransform GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_NUMBER/*transformPointer*/,
    APE_OBJECT_NUMBER/*transformPointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertSetTransform")
  getArgAs_Pointer(embree::Device *,         device,            args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle,            args[_i++]);
  getArgAs_CChars(const char *,              property,          args[_i++]);
  getArgAs_Pointer(unsigned char *,          pointer,           args[_i++]);
  getArgAs_Double(uint64_t,                  pointerBytesFirst, args[_i++]);
  getArgAs_END

  device->rtSetTransform(handle, property, (const float *)&pointer[pointerBytesFirst]);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtClear GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertClear")
  getArgAs_Pointer(embree::Device *,         device, args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle, args[_i++]);
  getArgAs_END

  device->rtClear(handle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtCommit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertCommit")
  getArgAs_Pointer(embree::Device *,         device, args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle, args[_i++]);
  getArgAs_END

  device->rtCommit(handle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtRenderFrame GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*rendererHandle*/,
    APE_OBJECT_NUMBER/*cameraHandle*/,
    APE_OBJECT_NUMBER/*sceneHandle*/,
    APE_OBJECT_NUMBER/*toneMapperHandle*/,
    APE_OBJECT_NUMBER/*frameBufferHandle*/,
    APE_OBJECT_NUMBER/*accumulate*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertRenderFrame")
  getArgAs_Pointer(embree::Device *,              device,      args[_i++]);
  getArgAs_Pointer(embree::Device::RTRenderer,    renderer,    args[_i++]);
  getArgAs_Pointer(embree::Device::RTCamera,      camera,      args[_i++]);
  getArgAs_Pointer(embree::Device::RTScene,       scene,       args[_i++]);
  getArgAs_Pointer(embree::Device::RTToneMapper,  toneMapper,  args[_i++]);
  getArgAs_Pointer(embree::Device::RTFrameBuffer, frameBuffer, args[_i++]);
  getArgAs_Double(int,                            accumulate,  args[_i++]);
  getArgAs_END

  device->rtRenderFrame(renderer, camera, scene, toneMapper, frameBuffer, accumulate);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtPick GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*cameraHandle*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*sceneHandle*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertPick")
  getArgAs_Pointer(embree::Device *,         device, args[_i++]);
  getArgAs_Pointer(embree::Device::RTCamera, camera, args[_i++]);
  getArgAs_Double(float,                     x,      args[_i++]);
  getArgAs_Double(float,                     y,      args[_i++]);
  getArgAs_Pointer(embree::Device::RTScene,  scene,  args[_i++]);
  getArgAs_END

  float px = 0;
  float py = 0;
  float pz = 0;
  bool  boolean = device->rtPick(camera, x, y, scene, px, py, pz);

  ape_object_t array = mape_object_make_array(ape, 4);
  mape_object_add_array_number(0, array, (double)px);
  mape_object_add_array_number(1, array, (double)py);
  mape_object_add_array_number(2, array, (double)pz);
  mape_object_add_array_number(3, array, (double)(boolean == true ? 1 : 0));
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtInitializeRayStruct GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*orgX*/,
    APE_OBJECT_NUMBER/*orgY*/,
    APE_OBJECT_NUMBER/*orgZ*/,
    APE_OBJECT_NUMBER/*dirX*/,
    APE_OBJECT_NUMBER/*dirY*/,
    APE_OBJECT_NUMBER/*dirZ*/,
    APE_OBJECT_NUMBER/*nearDefaultIs0*/,
    APE_OBJECT_NUMBER/*farDefaultIsEmbreeInf*/,
    APE_OBJECT_NUMBER/*timeDefaultIs0*/,
    APE_OBJECT_NUMBER/*outRayStructPointer*/,
    APE_OBJECT_NUMBER/*outRayStructPointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertInitializeRayStruct")
  getArgAs_Pointer(embree::Device *, device,               args[_i++]);
  getArgAs_Double(float,             orgX,                 args[_i++]);
  getArgAs_Double(float,             orgY,                 args[_i++]);
  getArgAs_Double(float,             orgZ,                 args[_i++]);
  getArgAs_Double(float,             dirX,                 args[_i++]);
  getArgAs_Double(float,             dirY,                 args[_i++]);
  getArgAs_Double(float,             dirZ,                 args[_i++]);
  getArgAs_Double(float,             near,                 args[_i++]);
  getArgAs_Double(float,             far,                  args[_i++]);
  getArgAs_Double(float,             time,                 args[_i++]);
  getArgAs_Pointer(unsigned char *,  outPointer,           args[_i++]);
  getArgAs_Double(uint64_t,          outPointerBytesFirst, args[_i++]);
  getArgAs_END

  device->ertxInitializeRayStruct(orgX, orgY, orgZ, dirX, dirY, dirZ, near, far, time, (void *)&outPointer[outPointerBytesFirst]);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtInitializeRayStructForCameraPixelSample GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*cameraHandle*/,
    APE_OBJECT_NUMBER/*pixelXFrom0To1*/,
    APE_OBJECT_NUMBER/*pixelYFrom0To1*/,
    APE_OBJECT_NUMBER/*pixelSamplePosXFrom0ToExcluded1DefaultIs0Point5*/,
    APE_OBJECT_NUMBER/*pixelSamplePosYFrom0ToExcluded1DefaultIs0Point5*/,
    APE_OBJECT_NUMBER/*outRayStructPointer*/,
    APE_OBJECT_NUMBER/*outRayStructPointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertInitializeRayStructForCameraPixelSample")
  getArgAs_Pointer(embree::Device *,         device,               args[_i++]);
  getArgAs_Pointer(embree::Device::RTCamera, camera,               args[_i++]);
  getArgAs_Double(float,                     pixelX,               args[_i++]);
  getArgAs_Double(float,                     pixelY,               args[_i++]);
  getArgAs_Double(float,                     pixelSamplePosX,      args[_i++]);
  getArgAs_Double(float,                     pixelSamplePosY,      args[_i++]);
  getArgAs_Pointer(unsigned char *,          outPointer,           args[_i++]);
  getArgAs_Double(uint64_t,                  outPointerBytesFirst, args[_i++]);
  getArgAs_END

  device->ertxInitializeRayStructForCameraPixelSample(camera, pixelX, pixelY, pixelSamplePosX, pixelSamplePosY, (void *)&outPointer[outPointerBytesFirst]);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureErtSceneIntersectRayStructToHitStruct GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*sceneHandle*/,
    APE_OBJECT_NUMBER/*inRayStructPointer*/,
    APE_OBJECT_NUMBER/*inRayStructPointerBytesFirst*/,
    APE_OBJECT_NUMBER/*outHitStructPointer*/,
    APE_OBJECT_NUMBER/*outHitStructPointerBytesFirst*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("ertSceneIntersectRayStructToHitStruct")
  getArgAs_Pointer(embree::Device *,        device,                        args[_i++]);
  getArgAs_Pointer(embree::Device::RTScene, scene,                         args[_i++]);
  getArgAs_Pointer(unsigned char *,         rayStructPointer,              args[_i++]);
  getArgAs_Double(uint64_t,                 rayStructPointerBytesFirst,    args[_i++]);
  getArgAs_Pointer(unsigned char *,         outHitStructPointer,           args[_i++]);
  getArgAs_Double(uint64_t,                 outHitStructPointerBytesFirst, args[_i++]);
  getArgAs_END

  device->ertxSceneIntersectRayStructToHitStruct(scene, (void *)&rayStructPointer[rayStructPointerBytesFirst], (void *)&outHitStructPointer[outHitStructPointerBytesFirst]);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallErtDecRef GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallErtDecRef")
  getArgAs_Pointer(embree::Device *,         device, args[_i++]);
  getArgAs_Pointer(embree::Device::RTHandle, handle, args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)device;
  element.storage[1] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallErtDecRef.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallErtDestroyDevice GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*deviceHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallErtDestroyDevice")
  getArgAs_Pointer(embree::Device *, device, args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)device;
  gGlobalArrayPersistentOnRerunCallErtDestroyDevice.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedMemoryFree GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedMemoryFree")
  getArgAs_Pointer(RedContext,      context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,    gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleMemory, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)gpu;
  element.storage[2] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRedMemoryFree.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedStructsMemoryFree GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedStructsMemoryFree")
  getArgAs_Pointer(RedContext,             context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,           gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleStructsMemory, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)gpu;
  element.storage[2] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRedStructsMemoryFree.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedCpuSignalWait GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedCpuSignalWait")
  getArgAs_Pointer(RedContext,         context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,       gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleCpuSignal, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)gpu;
  element.storage[2] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRedCpuSignalWait.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedDestroyGpuToCpuSignal GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedDestroyGpuToCpuSignal")
  getArgAs_Pointer(RedContext,              context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,            gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleGpuToCpuSignal, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)gpu;
  element.storage[2] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRedDestroyGpuToCpuSignal.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedDestroyGpuSignal GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedDestroyGpuSignal")
  getArgAs_Pointer(RedContext,         context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,       gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleGpuSignal, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)gpu;
  element.storage[2] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRedDestroyGpuSignal.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedDestroyCpuSignal GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedDestroyCpuSignal")
  getArgAs_Pointer(RedContext,         context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,       gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleCpuSignal, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)gpu;
  element.storage[2] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRedDestroyCpuSignal.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedDestroyCalls GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*callsHandle*/,
    APE_OBJECT_NUMBER/*callsMemoryHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedDestroyCalls")
  getArgAs_Pointer(RedContext,           context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,         gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleCalls,       handle,  args[_i++]);
  getArgAs_Pointer(RedHandleCallsMemory, memory,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)gpu;
  element.storage[2] = (void *)handle;
  element.storage[3] = (void *)memory;
  gGlobalArrayPersistentOnRerunCallRedDestroyCalls.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedDestroyOutputDeclaration GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedDestroyOutputDeclaration")
  getArgAs_Pointer(RedContext,                 context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,               gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleOutputDeclaration, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)gpu;
  element.storage[2] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRedDestroyOutputDeclaration.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedDestroyOutput GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedDestroyOutput")
  getArgAs_Pointer(RedContext,      context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,    gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleOutput, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)gpu;
  element.storage[2] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRedDestroyOutput.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedDestroyStructDeclaration GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedDestroyStructDeclaration")
  getArgAs_Pointer(RedContext,                 context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,               gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleStructDeclaration, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)gpu;
  element.storage[2] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRedDestroyStructDeclaration.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedDestroySampler GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedDestroySampler")
  getArgAs_Pointer(RedContext,       context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,     gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleSampler, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)gpu;
  element.storage[2] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRedDestroySampler.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedDestroyTexture GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedDestroyTexture")
  getArgAs_Pointer(RedContext,       context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,     gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleTexture, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)gpu;
  element.storage[2] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRedDestroyTexture.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedDestroyImage GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedDestroyImage")
  getArgAs_Pointer(RedContext,     context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,   gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleImage, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)gpu;
  element.storage[2] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRedDestroyImage.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedDestroyArray GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedDestroyArray")
  getArgAs_Pointer(RedContext,     context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,   gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleArray, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)gpu;
  element.storage[2] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRedDestroyArray.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedDestroyArrayTimestamp GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedDestroyArrayTimestamp")
  getArgAs_Pointer(RedContext,              context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,            gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleArrayTimestamp, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)gpu;
  element.storage[2] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRedDestroyArrayTimestamp.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRrtDestroyContext GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*rrcontext*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRrtDestroyContext")
  getArgAs_Pointer(RRContext, context, args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  gGlobalArrayPersistentOnRerunCallRrtDestroyContext.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRrtReleaseCommandStream GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*rrcontext*/,
    APE_OBJECT_NUMBER/*rrcommandStream*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRrtReleaseCommandStream")
  getArgAs_Pointer(RRContext,       context, args[_i++]);
  getArgAs_Pointer(RRCommandStream, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRrtReleaseCommandStream.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRrtReleaseEvent GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*rrcontext*/,
    APE_OBJECT_NUMBER/*rrevent*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRrtReleaseEvent")
  getArgAs_Pointer(RRContext, context, args[_i++]);
  getArgAs_Pointer(RREvent,   handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRrtReleaseEvent.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRrtWaitEvent GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*rrcontext*/,
    APE_OBJECT_NUMBER/*rrevent*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRrtWaitEvent")
  getArgAs_Pointer(RRContext, context, args[_i++]);
  getArgAs_Pointer(RREvent,   handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRrtWaitEvent.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRrtReleaseDevicePtr GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*rrcontext*/,
    APE_OBJECT_NUMBER/*rrdevicePointer*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRrtReleaseDevicePtr")
  getArgAs_Pointer(RRContext,   context, args[_i++]);
  getArgAs_Pointer(RRDevicePtr, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRrtReleaseDevicePtr.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRrtReleaseExternalCommandStream GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*rrcontext*/,
    APE_OBJECT_NUMBER/*rrcommandStream*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRrtReleaseExternalCommandStream")
  getArgAs_Pointer(RRContext,       context, args[_i++]);
  getArgAs_Pointer(RRCommandStream, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRrtReleaseExternalCommandStream.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRrtUnmapDevicePtr GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*rrcontext*/,
    APE_OBJECT_NUMBER/*rrdevicePointer*/,
    APE_OBJECT_NUMBER/*outMappingPointer*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRrtUnmapDevicePtr")
  getArgAs_Pointer(RRContext,   context,       args[_i++]);
  getArgAs_Pointer(RRDevicePtr, devicePointer, args[_i++]);
  getArgAs_Pointer(void **,     handle,        args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)devicePointer;
  element.storage[2] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRrtUnmapDevicePtr.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedDestroyProcedureCache GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedDestroyProcedureCache")
  getArgAs_Pointer(RedContext,              context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,            gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleProcedureCache, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)gpu;
  element.storage[2] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRedDestroyProcedureCache.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedDestroyGpuCode GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedDestroyGpuCode")
  getArgAs_Pointer(RedContext,       context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,     gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleGpuCode, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)gpu;
  element.storage[2] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRedDestroyGpuCode.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedDestroyProcedure GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedDestroyProcedure")
  getArgAs_Pointer(RedContext,         context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,       gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleProcedure, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)gpu;
  element.storage[2] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRedDestroyProcedure.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedDestroyProcedureParameters GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedDestroyProcedureParameters")
  getArgAs_Pointer(RedContext,                   context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,                 gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleProcedureParameters, handle,  args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  element.storage[1] = (void *)gpu;
  element.storage[2] = (void *)handle;
  gGlobalArrayPersistentOnRerunCallRedDestroyProcedureParameters.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallRedDestroyContext GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallRedDestroyContext")
  getArgAs_Pointer(RedContext, context, args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)context;
  gGlobalArrayPersistentOnRerunCallRedDestroyContext.push_back(element);

  return ape_object_make_null();
}

static RedBool32 redHelperDebugCallback(RedDebugCallbackSeverity severity, RedDebugCallbackTypeBitflags types, const RedDebugCallbackData * data, RedContext context) {
  const unsigned statusCode    = data->statusCode;
  const char *   messageIdName = data->messageIdName == NULL ? "" : data->messageIdName;
  const char *   message       = data->message       == NULL ? "" : data->message;
  std::string msg;
  msg += "[REDGPU][";
  msg += messageIdName;
  msg += "]: ";
  msg += message;
  msg += " (statusCode: ";
  msg += std::to_string(statusCode);
  msg += ")\n";
  for (unsigned i = 0; i < data->handleInfosCount; i += 1) {
    msg += "[REDGPU][";
    msg += messageIdName;
    msg += "]: handleInfos[";
    msg += std::to_string(i);
    msg += "].handleType: ";
    msg += std::to_string(data->handleInfos[i].handleType);
    msg += "\n";

    msg += "[REDGPU][";
    msg += messageIdName;
    msg += "]: handleInfos[";
    msg += std::to_string(i);
    msg += "].handle:     ";
    msg += std::to_string((uint64_t)data->handleInfos[i].handle);
    msg += "\n";

    msg += "[REDGPU][";
    msg += messageIdName;
    msg += "]: handleInfos[";
    msg += std::to_string(i);
    msg += "].handleName: \"";
    msg += data->handleInfos[i].handleName == NULL ? "" : data->handleInfos[i].handleName;
    msg += "\"\n";
  }
  _gsPrintThreadSafe(msg.c_str());
  return 0;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetRedStructsCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  uint64_t count = 0;

#define GS_MACRO_RED_STRUCT(STRUCTURE) count += 1;

  GS_MACRO_RED_STRUCT(RedArray)
  GS_MACRO_RED_STRUCT(RedImage)
  GS_MACRO_RED_STRUCT(RedOutput)
  GS_MACRO_RED_STRUCT(RedCalls)
  GS_MACRO_RED_STRUCT(RedMemoryType)
  GS_MACRO_RED_STRUCT(RedMemoryHeap)
  GS_MACRO_RED_STRUCT(RedQueueCopyLimits)
  GS_MACRO_RED_STRUCT(RedImageFormatLimitsDimensions)
  GS_MACRO_RED_STRUCT(RedImageFormatLimits)
  GS_MACRO_RED_STRUCT(RedImageFormatFeatures)
  GS_MACRO_RED_STRUCT(RedGpuInfo)
  GS_MACRO_RED_STRUCT(RedStatuses)
  GS_MACRO_RED_STRUCT(RedTypeContext)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoIterator)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoAdditionalInfo0)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoDriverProperties)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoResolveDepthStencil)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoProcedureParametersHandles)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoRasterizationMode)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoFormalMemoryModel)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoRayTracing)
  GS_MACRO_RED_STRUCT(RedMemoryBudget)
  GS_MACRO_RED_STRUCT(RedMemoryArray)
  GS_MACRO_RED_STRUCT(RedMemoryImage)
  GS_MACRO_RED_STRUCT(RedMappableMemoryRange)
  GS_MACRO_RED_STRUCT(RedStructMemberTexture)
  GS_MACRO_RED_STRUCT(RedStructMemberArray)
  GS_MACRO_RED_STRUCT(RedStructMember)
  GS_MACRO_RED_STRUCT(RedContextOptionalSettingsIterator)
  GS_MACRO_RED_STRUCT(RedContextOptionalSettings0)
  GS_MACRO_RED_STRUCT(RedHandleInfo)
  GS_MACRO_RED_STRUCT(RedDebugCallbackData)
  GS_MACRO_RED_STRUCT(RedMemoryAllocationTag)
  GS_MACRO_RED_STRUCT(RedOutputDeclarationMembers)
  GS_MACRO_RED_STRUCT(RedOutputDeclarationMembersResolveSources)
  GS_MACRO_RED_STRUCT(RedStructDeclarationMember)
  GS_MACRO_RED_STRUCT(RedStructDeclarationMemberArrayRO)
  GS_MACRO_RED_STRUCT(RedProcedureParametersDeclaration)
  GS_MACRO_RED_STRUCT(RedProcedureState)
  GS_MACRO_RED_STRUCT(RedProcedureStateExtensionIterator)
  GS_MACRO_RED_STRUCT(RedProcedureStateExtensionRasterizationMode)
  GS_MACRO_RED_STRUCT(RedOutputMembers)
  GS_MACRO_RED_STRUCT(RedOutputMembersResolveTargets)
  GS_MACRO_RED_STRUCT(RedCopyArrayRange)
  GS_MACRO_RED_STRUCT(RedCopyImageParts)
  GS_MACRO_RED_STRUCT(RedCopyImageOffset)
  GS_MACRO_RED_STRUCT(RedCopyImageExtent)
  GS_MACRO_RED_STRUCT(RedCopyImageRange)
  GS_MACRO_RED_STRUCT(RedCopyArrayImageRange)
  GS_MACRO_RED_STRUCT(RedProcedureParametersHandleArray)
  GS_MACRO_RED_STRUCT(RedProcedureParametersHandle)
  GS_MACRO_RED_STRUCT(RedCallProceduresAndAddresses)
  GS_MACRO_RED_STRUCT(RedInlineOutput)
  GS_MACRO_RED_STRUCT(RedColorsClearValuesFloat)
  GS_MACRO_RED_STRUCT(RedColorsClearValuesSint)
  GS_MACRO_RED_STRUCT(RedColorsClearValuesUint)
  GS_MACRO_RED_STRUCT(RedUsageArray)
  GS_MACRO_RED_STRUCT(RedUsageImage)
  GS_MACRO_RED_STRUCT(RedAlias)
  GS_MACRO_RED_STRUCT(RedOrder)
  GS_MACRO_RED_STRUCT(RedGpuTimeline)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1)
  GS_MACRO_RED_STRUCT(RedProcedureComputingLanguageStateExtensionIterator)
  GS_MACRO_RED_STRUCT(RedProcedureComputingLanguageSpecializationConstant)
  GS_MACRO_RED_STRUCT(RedProcedureComputingLanguageStateExtensionSpecializationConstants)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoArrayTimestamp)

#undef GS_MACRO_RED_STRUCT

  return ape_object_make_number((double)count);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetRedStructName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*index*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("getRedStructName")
  getArgAs_Double(uint64_t, index, args[_i++]);
  getArgAs_END

  uint64_t count = 0;

#define GS_MACRO_RED_STRUCT(STRUCTURE) \
  if (index == count) { \
    return ape_object_make_string(ape, #STRUCTURE); \
  } \
  count += 1;

  GS_MACRO_RED_STRUCT(RedArray)
  GS_MACRO_RED_STRUCT(RedImage)
  GS_MACRO_RED_STRUCT(RedOutput)
  GS_MACRO_RED_STRUCT(RedCalls)
  GS_MACRO_RED_STRUCT(RedMemoryType)
  GS_MACRO_RED_STRUCT(RedMemoryHeap)
  GS_MACRO_RED_STRUCT(RedQueueCopyLimits)
  GS_MACRO_RED_STRUCT(RedImageFormatLimitsDimensions)
  GS_MACRO_RED_STRUCT(RedImageFormatLimits)
  GS_MACRO_RED_STRUCT(RedImageFormatFeatures)
  GS_MACRO_RED_STRUCT(RedGpuInfo)
  GS_MACRO_RED_STRUCT(RedStatuses)
  GS_MACRO_RED_STRUCT(RedTypeContext)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoIterator)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoAdditionalInfo0)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoDriverProperties)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoResolveDepthStencil)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoProcedureParametersHandles)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoRasterizationMode)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoFormalMemoryModel)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoRayTracing)
  GS_MACRO_RED_STRUCT(RedMemoryBudget)
  GS_MACRO_RED_STRUCT(RedMemoryArray)
  GS_MACRO_RED_STRUCT(RedMemoryImage)
  GS_MACRO_RED_STRUCT(RedMappableMemoryRange)
  GS_MACRO_RED_STRUCT(RedStructMemberTexture)
  GS_MACRO_RED_STRUCT(RedStructMemberArray)
  GS_MACRO_RED_STRUCT(RedStructMember)
  GS_MACRO_RED_STRUCT(RedContextOptionalSettingsIterator)
  GS_MACRO_RED_STRUCT(RedContextOptionalSettings0)
  GS_MACRO_RED_STRUCT(RedHandleInfo)
  GS_MACRO_RED_STRUCT(RedDebugCallbackData)
  GS_MACRO_RED_STRUCT(RedMemoryAllocationTag)
  GS_MACRO_RED_STRUCT(RedOutputDeclarationMembers)
  GS_MACRO_RED_STRUCT(RedOutputDeclarationMembersResolveSources)
  GS_MACRO_RED_STRUCT(RedStructDeclarationMember)
  GS_MACRO_RED_STRUCT(RedStructDeclarationMemberArrayRO)
  GS_MACRO_RED_STRUCT(RedProcedureParametersDeclaration)
  GS_MACRO_RED_STRUCT(RedProcedureState)
  GS_MACRO_RED_STRUCT(RedProcedureStateExtensionIterator)
  GS_MACRO_RED_STRUCT(RedProcedureStateExtensionRasterizationMode)
  GS_MACRO_RED_STRUCT(RedOutputMembers)
  GS_MACRO_RED_STRUCT(RedOutputMembersResolveTargets)
  GS_MACRO_RED_STRUCT(RedCopyArrayRange)
  GS_MACRO_RED_STRUCT(RedCopyImageParts)
  GS_MACRO_RED_STRUCT(RedCopyImageOffset)
  GS_MACRO_RED_STRUCT(RedCopyImageExtent)
  GS_MACRO_RED_STRUCT(RedCopyImageRange)
  GS_MACRO_RED_STRUCT(RedCopyArrayImageRange)
  GS_MACRO_RED_STRUCT(RedProcedureParametersHandleArray)
  GS_MACRO_RED_STRUCT(RedProcedureParametersHandle)
  GS_MACRO_RED_STRUCT(RedCallProceduresAndAddresses)
  GS_MACRO_RED_STRUCT(RedInlineOutput)
  GS_MACRO_RED_STRUCT(RedColorsClearValuesFloat)
  GS_MACRO_RED_STRUCT(RedColorsClearValuesSint)
  GS_MACRO_RED_STRUCT(RedColorsClearValuesUint)
  GS_MACRO_RED_STRUCT(RedUsageArray)
  GS_MACRO_RED_STRUCT(RedUsageImage)
  GS_MACRO_RED_STRUCT(RedAlias)
  GS_MACRO_RED_STRUCT(RedOrder)
  GS_MACRO_RED_STRUCT(RedGpuTimeline)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1)
  GS_MACRO_RED_STRUCT(RedProcedureComputingLanguageStateExtensionIterator)
  GS_MACRO_RED_STRUCT(RedProcedureComputingLanguageSpecializationConstant)
  GS_MACRO_RED_STRUCT(RedProcedureComputingLanguageStateExtensionSpecializationConstants)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoArrayTimestamp)

#undef GS_MACRO_RED_STRUCT

  return ape_object_make_string(ape, "");
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedStructSizeof GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*structName*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redStructSizeof")
  getArgAs_CChars(const char *, structName, args[_i++]);
  getArgAs_END

  const size_t structNameBytesCount = strlen(structName) + 1;

#define GS_MACRO_RED_STRUCT(STRUCTURE) \
  if (structNameBytesCount == sizeof(#STRUCTURE)) { \
    if (memcmp(structName, #STRUCTURE, structNameBytesCount) == 0) { \
      return ape_object_make_number((double)sizeof(STRUCTURE)); \
    } \
  }

  GS_MACRO_RED_STRUCT(RedArray)
  GS_MACRO_RED_STRUCT(RedImage)
  GS_MACRO_RED_STRUCT(RedOutput)
  GS_MACRO_RED_STRUCT(RedCalls)
  GS_MACRO_RED_STRUCT(RedMemoryType)
  GS_MACRO_RED_STRUCT(RedMemoryHeap)
  GS_MACRO_RED_STRUCT(RedQueueCopyLimits)
  GS_MACRO_RED_STRUCT(RedImageFormatLimitsDimensions)
  GS_MACRO_RED_STRUCT(RedImageFormatLimits)
  GS_MACRO_RED_STRUCT(RedImageFormatFeatures)
  GS_MACRO_RED_STRUCT(RedGpuInfo)
  GS_MACRO_RED_STRUCT(RedStatuses)
  GS_MACRO_RED_STRUCT(RedTypeContext)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoIterator)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoAdditionalInfo0)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoDriverProperties)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoResolveDepthStencil)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoProcedureParametersHandles)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoRasterizationMode)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoFormalMemoryModel)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoRayTracing)
  GS_MACRO_RED_STRUCT(RedMemoryBudget)
  GS_MACRO_RED_STRUCT(RedMemoryArray)
  GS_MACRO_RED_STRUCT(RedMemoryImage)
  GS_MACRO_RED_STRUCT(RedMappableMemoryRange)
  GS_MACRO_RED_STRUCT(RedStructMemberTexture)
  GS_MACRO_RED_STRUCT(RedStructMemberArray)
  GS_MACRO_RED_STRUCT(RedStructMember)
  GS_MACRO_RED_STRUCT(RedContextOptionalSettingsIterator)
  GS_MACRO_RED_STRUCT(RedContextOptionalSettings0)
  GS_MACRO_RED_STRUCT(RedHandleInfo)
  GS_MACRO_RED_STRUCT(RedDebugCallbackData)
  GS_MACRO_RED_STRUCT(RedMemoryAllocationTag)
  GS_MACRO_RED_STRUCT(RedOutputDeclarationMembers)
  GS_MACRO_RED_STRUCT(RedOutputDeclarationMembersResolveSources)
  GS_MACRO_RED_STRUCT(RedStructDeclarationMember)
  GS_MACRO_RED_STRUCT(RedStructDeclarationMemberArrayRO)
  GS_MACRO_RED_STRUCT(RedProcedureParametersDeclaration)
  GS_MACRO_RED_STRUCT(RedProcedureState)
  GS_MACRO_RED_STRUCT(RedProcedureStateExtensionIterator)
  GS_MACRO_RED_STRUCT(RedProcedureStateExtensionRasterizationMode)
  GS_MACRO_RED_STRUCT(RedOutputMembers)
  GS_MACRO_RED_STRUCT(RedOutputMembersResolveTargets)
  GS_MACRO_RED_STRUCT(RedCopyArrayRange)
  GS_MACRO_RED_STRUCT(RedCopyImageParts)
  GS_MACRO_RED_STRUCT(RedCopyImageOffset)
  GS_MACRO_RED_STRUCT(RedCopyImageExtent)
  GS_MACRO_RED_STRUCT(RedCopyImageRange)
  GS_MACRO_RED_STRUCT(RedCopyArrayImageRange)
  GS_MACRO_RED_STRUCT(RedProcedureParametersHandleArray)
  GS_MACRO_RED_STRUCT(RedProcedureParametersHandle)
  GS_MACRO_RED_STRUCT(RedCallProceduresAndAddresses)
  GS_MACRO_RED_STRUCT(RedInlineOutput)
  GS_MACRO_RED_STRUCT(RedColorsClearValuesFloat)
  GS_MACRO_RED_STRUCT(RedColorsClearValuesSint)
  GS_MACRO_RED_STRUCT(RedColorsClearValuesUint)
  GS_MACRO_RED_STRUCT(RedUsageArray)
  GS_MACRO_RED_STRUCT(RedUsageImage)
  GS_MACRO_RED_STRUCT(RedAlias)
  GS_MACRO_RED_STRUCT(RedOrder)
  GS_MACRO_RED_STRUCT(RedGpuTimeline)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1)
  GS_MACRO_RED_STRUCT(RedProcedureComputingLanguageStateExtensionIterator)
  GS_MACRO_RED_STRUCT(RedProcedureComputingLanguageSpecializationConstant)
  GS_MACRO_RED_STRUCT(RedProcedureComputingLanguageStateExtensionSpecializationConstants)
  GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoArrayTimestamp)

#undef GS_MACRO_RED_STRUCT

  return ape_object_make_number((double)((uint64_t)-1));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetRedStructMembersCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  uint64_t count = 0;

#define GS_MACRO_RED_STRUCT_MEMBER(GS_TYPE, TYPE, STRUCTURE, MEMBER) count += 1;

  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedArray, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedArray, memoryBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedArray, memoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedArray, memoryTypesSupported)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleImage, RedImage, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedImage, memoryBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedImage, memoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImage, memoryTypesSupported)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleOutput, RedOutput, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutput, width)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutput, height)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutput, depthStencilEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutput, colorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleCalls, RedCalls, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleCallsMemory, RedCalls, memory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedCalls, reusable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryType, memoryHeapIndex)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isGpuVram)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isCpuMappable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isCpuCoherent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isCpuCached)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryHeap, memoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryHeap, isGpuVram)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedQueueCopyLimits, copyBlockTexelsCountWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedQueueCopyLimits, copyBlockTexelsCountHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedQueueCopyLimits, copyBlockTexelsCountDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimitsDimensions, maxWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimitsDimensions, maxHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimitsDimensions, maxDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedImageFormatLimitsDimensions, RedImageFormatLimits, maxDimensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimits, maxLevelsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimits, maxLayersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedImageFormatLimits, supportedMultisampleCounts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedImageFormatLimits, maxBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, RedStatus, RedImageFormatLimits, status)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsCopyR)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsCopyW)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureRO)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureRW)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsOutputDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsOutputColor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureROFilteringLinear)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureRWAtomics)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsOutputColorBlend)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleGpu, RedGpuInfo, gpu)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleGpuDevice, RedGpuInfo, gpuDevice)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedGpuInfo, gpuName)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuType, RedGpuInfo, gpuType)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, gpuVendorId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, gpuDeviceId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, gpuDriverVersion)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfo, gpuProcedureCacheUuid)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, memoryTypesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedMemoryType *, RedGpuInfo, memoryTypes)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const char **, RedGpuInfo, memoryTypesDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, memoryHeapsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedMemoryHeap *, RedGpuInfo, memoryHeaps)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const char **, RedGpuInfo, memoryHeapsDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, queuesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleQueue *, RedGpuInfo, queues)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const char **, RedGpuInfo, queuesDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedGpuInfo, queuesFamilyIndex)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedBool32 *, RedGpuInfo, queuesCanCopy)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedBool32 *, RedGpuInfo, queuesCanDraw)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedBool32 *, RedGpuInfo, queuesCanCompute)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedQueueCopyLimits *, RedGpuInfo, queuesCopyLimits)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxMemoryAllocateCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minMemoryAllocateBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, maxMemoryAllocateBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minMemoryNonCoherentBlockBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxCreateSamplerCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minMemoryPageSeparationArrayImageBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minArrayROCStructMemberRangeBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, maxArrayROCStructMemberRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minArrayRORWStructMemberRangeBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, maxArrayRORWStructMemberRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxArrayIndexUint32Value)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensions1D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensions2D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensions3D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensionsCube)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageLayersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxSamplerMipLodBias)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxSamplerAnisotropy)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsSamplerFilteringMagMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsSamplerFilteringMip)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxOutputWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxOutputHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxOutputColorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForOutputDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForOutputStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForOutputColor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForEmptyOutput)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructSlotsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageArrayROCsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageArrayRORWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageSamplersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageTextureROsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageTextureRWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageAllResourcesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructArrayROCsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructArrayRORWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructSamplersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructTextureROsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructTextureRWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxProcedureParametersVariablesBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxViewportDimensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, minViewportBoundsRange)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxViewportBoundsRange)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsViewportCoordinates)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsViewportBounds)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxPerStageClipDistances)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxPerStageCullDistances)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxPerStageClipAndCullDistances)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxVertexOutputLocationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentInputLocationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentOutputColorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentOutputColorsCountBlendDualSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentOutputResourcesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeSharedMemoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeWorkgroupsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeWorkgroupInvocationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeWorkgroupDimensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedGpuInfo, minImageSampleImageFetchOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageSampleImageFetchOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedGpuInfo, minImageGatherOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageGatherOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, minInterpolateAtOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxInterpolateAtOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsInterpolateAtOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, optimalCopyArrayImageRangeArrayBytesFirstBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, optimalCopyArrayImageRangeArrayTexelsCountToNextRowBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsWsi)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsMemoryGetBudget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsFullArrayIndexUint32Value)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsSamplerAnisotropy)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsTextureDimensionsCubeLayered)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateRasterizationDepthClamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateRasterizationDepthBiasDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateRasterizationDepthBiasClamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateMultisampleSampleShading)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateMultisampleAlphaToOne)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateDepthTestBoundsTest)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateDepthTestBoundsTestDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateStencilTestFrontAndBackDynamicCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateStencilTestFrontAndBackDynamicWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateBlendLogicOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateOutputColorsBlendVaryingPerColor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateOutputColorsBlendDualSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsMultisampleEmptyOutputVariableMultisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsMultisampleStandardSampleLocations)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeWritesAndAtomicsInStageVertex)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeWritesAndAtomicsInStageFragment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeImageGatherExtended)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWExtendedFormats)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWMultisample)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWReadWithoutFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWWriteWithoutFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfArrayROCs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfArrayRORWs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfSamplers)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfTextureROs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfTextureRWs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeClipDistance)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeCullDistance)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeInt64)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeFloat64)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeMinLod)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions1D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions2D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions2DMultisample)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions2DWithTextureDimensionsCubeAndCubeLayered)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions3D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions3DWithTextureDimensions2DAnd2DLayered)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatFeatures *, RedGpuInfo, imageFormatsFeatures)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfo, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, RedStatus, RedStatuses, status)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStatuses, statusCode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusHresult)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureId, RedStatuses, statusProcedureId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedStatuses, statusFile)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusLine)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, RedStatus, RedStatuses, statusError)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStatuses, statusErrorCode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusErrorHresult)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureId, RedStatuses, statusErrorProcedureId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedStatuses, statusErrorFile)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusErrorLine)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedStatuses, statusErrorDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedTypeContext, gpusCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedGpuInfo *, RedTypeContext, gpus)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedStatuses *, RedTypeContext, gpusStatuses)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleContext, RedTypeContext, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, void *, RedTypeContext, userData)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfoOptionalInfoIterator, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoAdditionalInfo0, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoAdditionalInfo0, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsArraysImagesUsageBeforeMemorySet)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfArrays)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfImages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfImagesMultisample)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfImagesDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoDriverProperties, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoDriverProperties, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedDriverId, RedGpuInfoOptionalInfoDriverProperties, id)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedGpuInfoOptionalInfoDriverProperties, name)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedGpuInfoOptionalInfoDriverProperties, info)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionMajor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionMinor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionSubminor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionPatch)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoResolveDepthStencil, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoResolveDepthStencil, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthSampleIndexZero)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthAverage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilSampleIndexZero)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilAverage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveIndependentNone)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveIndependent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoProcedureParametersHandles, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoProcedureParametersHandles, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoProcedureParametersHandles, supportsProcedureParametersHandles)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfoOptionalInfoProcedureParametersHandles, maxProcedureParametersHandlesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoRasterizationMode, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoRasterizationMode, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsRasterizationModeOverestimate)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsRasterizationModeUnderestimate)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsGuaranteedZeroAreaBackFacingTriangles)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsGpuCodeFullyCoveredEXT)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoFormalMemoryModel, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoFormalMemoryModel, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoFormalMemoryModel, supportsFormalMemoryModel)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoFormalMemoryModel, supportsFormalMemoryModelGpuScopeSynchronization)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoFormalMemoryModel, supportsFormalMemoryModelAvailabilityAndVisibilityChains)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoRayTracing, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoRayTracing, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRayTracing, supportsRayTracing)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryBudget, setTo1000237000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMemoryBudget, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryBudget, memoryHeapsBudget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryBudget, memoryHeapsUsage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryArray, setTo1000157000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMemoryArray, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedMemoryArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleMemory, RedMemoryArray, memory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryArray, memoryBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryImage, setTo1000157001)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMemoryImage, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleImage, RedMemoryImage, image)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleMemory, RedMemoryImage, memory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryImage, memoryBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMappableMemoryRange, setTo6)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMappableMemoryRange, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleMemory, RedMappableMemoryRange, mappableMemory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMappableMemoryRange, mappableMemoryRangeBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMappableMemoryRange, mappableMemoryRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleSampler, RedStructMemberTexture, sampler)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedStructMemberTexture, texture)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMemberTexture, setTo1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedStructMemberArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedStructMemberArray, arrayRangeBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedStructMemberArray, arrayRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, setTo35)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedStructMember, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleStruct, RedStructMember, structure)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, first)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, count)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStructMemberType, RedStructMember, type)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedStructMemberTexture *, RedStructMember, textures)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedStructMemberArray *, RedStructMember, arrays)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedStructMember, setTo00)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedContextOptionalSettingsIterator, settings)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedContextOptionalSettingsIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedContextOptionalSettings, RedContextOptionalSettings0, settings)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedContextOptionalSettings0, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedContextOptionalSettings0, skipCheckingContextLayers)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedContextOptionalSettings0, skipCheckingContextExtensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedContextOptionalSettings0, gpusExposeOnlyOneQueue)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedHandleInfo, _0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedHandleInfo, _1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedHandleType, RedHandleInfo, handleType)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedHandleInfo, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedHandleInfo, handleName)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, _0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedDebugCallbackData, _1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, statusCode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedDebugCallbackData, messageIdName)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedDebugCallbackData, statusHresult)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedDebugCallbackData, message)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, _2)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedDebugCallbackData, _3)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, _4)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedDebugCallbackData, _5)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, handleInfosCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleInfo *, RedDebugCallbackData, handleInfos)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedMemoryAllocationTag, tag)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembers, depthStencilEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedFormat, RedOutputDeclarationMembers, depthStencilFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflag, RedOutputDeclarationMembers, depthStencilMultisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedSetProcedureOutputOp, RedOutputDeclarationMembers, depthStencilDepthSetProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedEndProcedureOutputOp, RedOutputDeclarationMembers, depthStencilDepthEndProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedSetProcedureOutputOp, RedOutputDeclarationMembers, depthStencilStencilSetProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedEndProcedureOutputOp, RedOutputDeclarationMembers, depthStencilStencilEndProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembers, depthStencilSharesMemoryWithAnotherMember)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutputDeclarationMembers, colorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedFormat, RedOutputDeclarationMembers, colorsFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflag, RedOutputDeclarationMembers, colorsMultisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedSetProcedureOutputOp, RedOutputDeclarationMembers, colorsSetProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedEndProcedureOutputOp, RedOutputDeclarationMembers, colorsEndProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembers, colorsSharesMemoryWithAnotherMember)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedResolveMode, RedOutputDeclarationMembersResolveSources, resolveModeDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedResolveMode, RedOutputDeclarationMembersResolveSources, resolveModeStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembersResolveSources, resolveDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembersResolveSources, resolveColors)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructDeclarationMember, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStructMemberType, RedStructDeclarationMember, type)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructDeclarationMember, count)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedVisibleToStageBitflags, RedStructDeclarationMember, visibleToStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleSampler *, RedStructDeclarationMember, inlineSampler)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructDeclarationMemberArrayRO, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersDeclaration, variablesSlot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedVisibleToStageBitflags, RedProcedureParametersDeclaration, variablesVisibleToStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersDeclaration, variablesBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersDeclaration, structsDeclarationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleStructDeclaration, RedProcedureParametersDeclaration, structsDeclarations)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleStructDeclaration, RedProcedureParametersDeclaration, handlesDeclaration)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedPrimitiveTopology, RedProcedureState, inputAssemblyTopology)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, inputAssemblyPrimitiveRestartEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, viewportDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticX)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticY)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticDepthMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticDepthMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, scissorDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedProcedureState, scissorStaticX)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedProcedureState, scissorStaticY)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, scissorStaticWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, scissorStaticHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDepthClampEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDiscardAllPrimitivesEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCullMode, RedProcedureState, rasterizationCullMode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedFrontFace, RedProcedureState, rasterizationFrontFace)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDepthBiasEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDepthBiasDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, rasterizationDepthBiasStaticConstantFactor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, rasterizationDepthBiasStaticClamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, rasterizationDepthBiasStaticSlopeFactor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflag, RedProcedureState, multisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedProcedureState, multisampleSampleMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, multisampleSampleShadingEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, multisampleSampleShadingMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, multisampleAlphaToCoverageEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, multisampleAlphaToOneEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestDepthWriteEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCompareOp, RedProcedureState, depthTestDepthCompareOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestBoundsTestEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestBoundsTestDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, depthTestBoundsTestStaticMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, depthTestBoundsTestStaticMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestFrontStencilTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestFrontStencilTestPassDepthTestPassOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestFrontStencilTestPassDepthTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCompareOp, RedProcedureState, stencilTestFrontCompareOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestBackStencilTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestBackStencilTestPassDepthTestPassOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestBackStencilTestPassDepthTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCompareOp, RedProcedureState, stencilTestBackCompareOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestFrontAndBackDynamicCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestFrontAndBackDynamicWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestFrontAndBackDynamicReference)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, stencilTestFrontAndBackStaticCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, stencilTestFrontAndBackStaticWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, stencilTestFrontAndBackStaticReference)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, blendLogicOpEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedLogicOp, RedProcedureState, blendLogicOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, blendConstantsDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, blendConstantsStatic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, outputColorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedColorComponentBitflags, RedProcedureState, outputColorsWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, outputColorsBlendEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendColorFactorSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendColorFactorTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendOp, RedProcedureState, outputColorsBlendColorOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendAlphaFactorSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendAlphaFactorTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendOp, RedProcedureState, outputColorsBlendAlphaOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureStateExtensionIterator, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureStateExtensionIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureStateExtension, RedProcedureStateExtensionRasterizationMode, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureStateExtensionRasterizationMode, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedRasterizationMode, RedProcedureStateExtensionRasterizationMode, rasterizationMode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembers, depthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutputMembers, colorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembers, colors)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembersResolveTargets, depthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembersResolveTargets, colors)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayRange, arrayRBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayRange, arrayWBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayRange, bytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedImagePartBitflags, RedCopyImageParts, allParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageParts, level)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageParts, layersFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageParts, layersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedCopyImageOffset, texelX)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedCopyImageOffset, texelY)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedCopyImageOffset, texelZ)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageExtent, texelsCountWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageExtent, texelsCountHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageExtent, texelsCountDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageParts, RedCopyImageRange, imageRParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageOffset, RedCopyImageRange, imageROffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageParts, RedCopyImageRange, imageWParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageOffset, RedCopyImageRange, imageWOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageExtent, RedCopyImageRange, extent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayImageRange, arrayBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyArrayImageRange, arrayTexelsCountToNextRow)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyArrayImageRange, arrayTexelsCountToNextLayerOr3DDepthSliceDividedByTexelsCountToNextRow)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageParts, RedCopyArrayImageRange, imageParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageOffset, RedCopyArrayImageRange, imageOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageExtent, RedCopyArrayImageRange, imageExtent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedProcedureParametersHandleArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedProcedureParametersHandleArray, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedProcedureParametersHandleArray, setToMaxValue)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, setTo35)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureParametersHandle, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedProcedureParametersHandle, setTo00)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, setTo000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, setTo1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureParametersHandleType, RedProcedureParametersHandle, type)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureParametersHandle, setTo0000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedProcedureParametersHandleArray *, RedProcedureParametersHandle, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureParametersHandle, setTo00000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallGpuToCpuSignalSignal, RedCallProceduresAndAddresses, redCallGpuToCpuSignalSignal)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyArrayToArray, RedCallProceduresAndAddresses, redCallCopyArrayToArray)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyImageToImage, RedCallProceduresAndAddresses, redCallCopyImageToImage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyArrayToImage, RedCallProceduresAndAddresses, redCallCopyArrayToImage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyImageToArray, RedCallProceduresAndAddresses, redCallCopyImageToArray)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallProcedure, RedCallProceduresAndAddresses, redCallProcedure)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallProcedureIndexed, RedCallProceduresAndAddresses, redCallProcedureIndexed)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallProcedureCompute, RedCallProceduresAndAddresses, redCallProcedureCompute)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedure, RedCallProceduresAndAddresses, redCallSetProcedure)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureIndices, RedCallProceduresAndAddresses, redCallSetProcedureIndices)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureParametersVariables, RedCallProceduresAndAddresses, redCallSetProcedureParametersVariables)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureParametersStructs, RedCallProceduresAndAddresses, redCallSetProcedureParametersStructs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureParametersHandles, RedCallProceduresAndAddresses, redCallSetProcedureParametersHandles)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicDepthBias, RedCallProceduresAndAddresses, redCallSetDynamicDepthBias)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicDepthBounds, RedCallProceduresAndAddresses, redCallSetDynamicDepthBounds)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicStencilCompareMask, RedCallProceduresAndAddresses, redCallSetDynamicStencilCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicStencilWriteMask, RedCallProceduresAndAddresses, redCallSetDynamicStencilWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicStencilReference, RedCallProceduresAndAddresses, redCallSetDynamicStencilReference)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicBlendConstants, RedCallProceduresAndAddresses, redCallSetDynamicBlendConstants)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetDynamicViewport, RedCallProceduresAndAddresses, redCallSetDynamicViewport)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetDynamicScissor, RedCallProceduresAndAddresses, redCallSetDynamicScissor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetStructsMemory, RedCallProceduresAndAddresses, redCallSetStructsMemory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetProcedureParameters, RedCallProceduresAndAddresses, redCallSetProcedureParameters)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetProcedureOutput, RedCallProceduresAndAddresses, redCallSetProcedureOutput)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallEndProcedureOutput, RedCallProceduresAndAddresses, redCallEndProcedureOutput)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallUsageAliasOrderBarrier, RedCallProceduresAndAddresses, redCallUsageAliasOrderBarrier)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallMark, RedCallProceduresAndAddresses, redCallMark)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallMarkSet, RedCallProceduresAndAddresses, redCallMarkSet)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallMarkEnd, RedCallProceduresAndAddresses, redCallMarkEnd)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedOutputMembers *, RedInlineOutput, outputMembers)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedOutputMembersResolveTargets *, RedInlineOutput, outputMembersResolveTargets)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, r)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, g)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, b)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, a)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, r)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, g)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, b)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, a)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, r)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, g)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, b)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, a)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedUsageArray, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageArray, oldAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageArray, newAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageArray, oldAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageArray, newAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageArray, queueFamilyIndexSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageArray, queueFamilyIndexTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedUsageArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedUsageArray, arrayBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedUsageArray, arrayBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedUsageImage, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageImage, oldAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageImage, newAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageImage, oldAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageImage, newAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedState, RedUsageImage, oldState)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedState, RedUsageImage, newState)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, queueFamilyIndexSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, queueFamilyIndexTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleImage, RedUsageImage, image)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedImagePartBitflags, RedUsageImage, imageAllParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLevelsFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLevelsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLayersFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLayersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedAlias, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedAlias, oldResourceHandle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedAlias, newResourceHandle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedOrder, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedOrder, resourceHandle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, setTo4)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedGpuTimeline, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, waitForAndUnsignalGpuSignalsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleGpuSignal *, RedGpuTimeline, waitForAndUnsignalGpuSignals)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedGpuTimeline, setTo65536)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, callsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleCalls *, RedGpuTimeline, calls)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, signalGpuSignalsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleGpuSignal *, RedGpuTimeline, signalGpuSignals)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo1, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, supportsComputingLanguageFeatureLevel1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageStateExtensionIterator, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageSpecializationConstant, specId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageSpecializationConstant, specDataBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureComputingLanguageSpecializationConstant, specDataBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureComputingLanguageStateExtension, RedProcedureComputingLanguageStateExtensionSpecializationConstants, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedProcedureComputingLanguageSpecializationConstant *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specDataBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specData)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo2, RedGpuInfoOptionalInfoArrayTimestamp, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoArrayTimestamp, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoArrayTimestamp, supportsArrayTimestamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedGpuInfoOptionalInfoArrayTimestamp, queuesPrecisionBits64BitTicksCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfoOptionalInfoArrayTimestamp, nanosecondsPerTick)

#undef GS_MACRO_RED_STRUCT_MEMBER

  return ape_object_make_number((double)count);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetRedStructMemberName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*index*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("getRedStructMemberName")
  getArgAs_Double(uint64_t, index, args[_i++]);
  getArgAs_END

  uint64_t count = 0;

#define GS_MACRO_RED_STRUCT_MEMBER(GS_TYPE, TYPE, STRUCTURE, MEMBER) \
  if (index == count) { \
    return ape_object_make_string(ape, #STRUCTURE "." #MEMBER); \
  } \
  count += 1;

  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedArray, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedArray, memoryBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedArray, memoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedArray, memoryTypesSupported)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleImage, RedImage, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedImage, memoryBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedImage, memoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImage, memoryTypesSupported)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleOutput, RedOutput, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutput, width)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutput, height)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutput, depthStencilEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutput, colorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleCalls, RedCalls, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleCallsMemory, RedCalls, memory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedCalls, reusable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryType, memoryHeapIndex)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isGpuVram)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isCpuMappable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isCpuCoherent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isCpuCached)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryHeap, memoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryHeap, isGpuVram)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedQueueCopyLimits, copyBlockTexelsCountWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedQueueCopyLimits, copyBlockTexelsCountHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedQueueCopyLimits, copyBlockTexelsCountDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimitsDimensions, maxWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimitsDimensions, maxHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimitsDimensions, maxDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedImageFormatLimitsDimensions, RedImageFormatLimits, maxDimensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimits, maxLevelsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimits, maxLayersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedImageFormatLimits, supportedMultisampleCounts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedImageFormatLimits, maxBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, RedStatus, RedImageFormatLimits, status)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsCopyR)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsCopyW)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureRO)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureRW)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsOutputDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsOutputColor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureROFilteringLinear)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureRWAtomics)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsOutputColorBlend)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleGpu, RedGpuInfo, gpu)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleGpuDevice, RedGpuInfo, gpuDevice)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedGpuInfo, gpuName)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuType, RedGpuInfo, gpuType)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, gpuVendorId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, gpuDeviceId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, gpuDriverVersion)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfo, gpuProcedureCacheUuid)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, memoryTypesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedMemoryType *, RedGpuInfo, memoryTypes)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const char **, RedGpuInfo, memoryTypesDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, memoryHeapsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedMemoryHeap *, RedGpuInfo, memoryHeaps)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const char **, RedGpuInfo, memoryHeapsDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, queuesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleQueue *, RedGpuInfo, queues)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const char **, RedGpuInfo, queuesDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedGpuInfo, queuesFamilyIndex)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedBool32 *, RedGpuInfo, queuesCanCopy)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedBool32 *, RedGpuInfo, queuesCanDraw)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedBool32 *, RedGpuInfo, queuesCanCompute)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedQueueCopyLimits *, RedGpuInfo, queuesCopyLimits)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxMemoryAllocateCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minMemoryAllocateBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, maxMemoryAllocateBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minMemoryNonCoherentBlockBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxCreateSamplerCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minMemoryPageSeparationArrayImageBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minArrayROCStructMemberRangeBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, maxArrayROCStructMemberRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minArrayRORWStructMemberRangeBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, maxArrayRORWStructMemberRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxArrayIndexUint32Value)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensions1D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensions2D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensions3D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensionsCube)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageLayersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxSamplerMipLodBias)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxSamplerAnisotropy)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsSamplerFilteringMagMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsSamplerFilteringMip)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxOutputWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxOutputHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxOutputColorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForOutputDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForOutputStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForOutputColor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForEmptyOutput)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructSlotsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageArrayROCsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageArrayRORWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageSamplersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageTextureROsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageTextureRWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageAllResourcesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructArrayROCsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructArrayRORWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructSamplersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructTextureROsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructTextureRWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxProcedureParametersVariablesBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxViewportDimensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, minViewportBoundsRange)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxViewportBoundsRange)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsViewportCoordinates)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsViewportBounds)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxPerStageClipDistances)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxPerStageCullDistances)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxPerStageClipAndCullDistances)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxVertexOutputLocationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentInputLocationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentOutputColorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentOutputColorsCountBlendDualSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentOutputResourcesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeSharedMemoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeWorkgroupsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeWorkgroupInvocationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeWorkgroupDimensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedGpuInfo, minImageSampleImageFetchOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageSampleImageFetchOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedGpuInfo, minImageGatherOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageGatherOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, minInterpolateAtOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxInterpolateAtOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsInterpolateAtOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, optimalCopyArrayImageRangeArrayBytesFirstBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, optimalCopyArrayImageRangeArrayTexelsCountToNextRowBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsWsi)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsMemoryGetBudget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsFullArrayIndexUint32Value)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsSamplerAnisotropy)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsTextureDimensionsCubeLayered)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateRasterizationDepthClamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateRasterizationDepthBiasDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateRasterizationDepthBiasClamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateMultisampleSampleShading)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateMultisampleAlphaToOne)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateDepthTestBoundsTest)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateDepthTestBoundsTestDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateStencilTestFrontAndBackDynamicCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateStencilTestFrontAndBackDynamicWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateBlendLogicOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateOutputColorsBlendVaryingPerColor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateOutputColorsBlendDualSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsMultisampleEmptyOutputVariableMultisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsMultisampleStandardSampleLocations)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeWritesAndAtomicsInStageVertex)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeWritesAndAtomicsInStageFragment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeImageGatherExtended)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWExtendedFormats)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWMultisample)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWReadWithoutFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWWriteWithoutFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfArrayROCs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfArrayRORWs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfSamplers)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfTextureROs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfTextureRWs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeClipDistance)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeCullDistance)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeInt64)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeFloat64)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeMinLod)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions1D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions2D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions2DMultisample)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions2DWithTextureDimensionsCubeAndCubeLayered)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions3D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions3DWithTextureDimensions2DAnd2DLayered)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatFeatures *, RedGpuInfo, imageFormatsFeatures)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfo, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, RedStatus, RedStatuses, status)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStatuses, statusCode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusHresult)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureId, RedStatuses, statusProcedureId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedStatuses, statusFile)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusLine)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, RedStatus, RedStatuses, statusError)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStatuses, statusErrorCode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusErrorHresult)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureId, RedStatuses, statusErrorProcedureId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedStatuses, statusErrorFile)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusErrorLine)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedStatuses, statusErrorDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedTypeContext, gpusCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedGpuInfo *, RedTypeContext, gpus)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedStatuses *, RedTypeContext, gpusStatuses)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleContext, RedTypeContext, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, void *, RedTypeContext, userData)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfoOptionalInfoIterator, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoAdditionalInfo0, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoAdditionalInfo0, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsArraysImagesUsageBeforeMemorySet)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfArrays)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfImages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfImagesMultisample)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfImagesDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoDriverProperties, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoDriverProperties, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedDriverId, RedGpuInfoOptionalInfoDriverProperties, id)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedGpuInfoOptionalInfoDriverProperties, name)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedGpuInfoOptionalInfoDriverProperties, info)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionMajor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionMinor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionSubminor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionPatch)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoResolveDepthStencil, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoResolveDepthStencil, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthSampleIndexZero)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthAverage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilSampleIndexZero)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilAverage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveIndependentNone)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveIndependent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoProcedureParametersHandles, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoProcedureParametersHandles, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoProcedureParametersHandles, supportsProcedureParametersHandles)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfoOptionalInfoProcedureParametersHandles, maxProcedureParametersHandlesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoRasterizationMode, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoRasterizationMode, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsRasterizationModeOverestimate)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsRasterizationModeUnderestimate)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsGuaranteedZeroAreaBackFacingTriangles)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsGpuCodeFullyCoveredEXT)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoFormalMemoryModel, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoFormalMemoryModel, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoFormalMemoryModel, supportsFormalMemoryModel)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoFormalMemoryModel, supportsFormalMemoryModelGpuScopeSynchronization)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoFormalMemoryModel, supportsFormalMemoryModelAvailabilityAndVisibilityChains)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoRayTracing, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoRayTracing, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRayTracing, supportsRayTracing)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryBudget, setTo1000237000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMemoryBudget, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryBudget, memoryHeapsBudget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryBudget, memoryHeapsUsage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryArray, setTo1000157000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMemoryArray, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedMemoryArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleMemory, RedMemoryArray, memory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryArray, memoryBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryImage, setTo1000157001)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMemoryImage, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleImage, RedMemoryImage, image)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleMemory, RedMemoryImage, memory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryImage, memoryBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMappableMemoryRange, setTo6)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMappableMemoryRange, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleMemory, RedMappableMemoryRange, mappableMemory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMappableMemoryRange, mappableMemoryRangeBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMappableMemoryRange, mappableMemoryRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleSampler, RedStructMemberTexture, sampler)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedStructMemberTexture, texture)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMemberTexture, setTo1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedStructMemberArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedStructMemberArray, arrayRangeBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedStructMemberArray, arrayRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, setTo35)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedStructMember, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleStruct, RedStructMember, structure)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, first)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, count)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStructMemberType, RedStructMember, type)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedStructMemberTexture *, RedStructMember, textures)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedStructMemberArray *, RedStructMember, arrays)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedStructMember, setTo00)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedContextOptionalSettingsIterator, settings)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedContextOptionalSettingsIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedContextOptionalSettings, RedContextOptionalSettings0, settings)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedContextOptionalSettings0, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedContextOptionalSettings0, skipCheckingContextLayers)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedContextOptionalSettings0, skipCheckingContextExtensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedContextOptionalSettings0, gpusExposeOnlyOneQueue)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedHandleInfo, _0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedHandleInfo, _1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedHandleType, RedHandleInfo, handleType)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedHandleInfo, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedHandleInfo, handleName)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, _0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedDebugCallbackData, _1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, statusCode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedDebugCallbackData, messageIdName)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedDebugCallbackData, statusHresult)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedDebugCallbackData, message)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, _2)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedDebugCallbackData, _3)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, _4)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedDebugCallbackData, _5)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, handleInfosCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleInfo *, RedDebugCallbackData, handleInfos)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedMemoryAllocationTag, tag)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembers, depthStencilEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedFormat, RedOutputDeclarationMembers, depthStencilFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflag, RedOutputDeclarationMembers, depthStencilMultisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedSetProcedureOutputOp, RedOutputDeclarationMembers, depthStencilDepthSetProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedEndProcedureOutputOp, RedOutputDeclarationMembers, depthStencilDepthEndProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedSetProcedureOutputOp, RedOutputDeclarationMembers, depthStencilStencilSetProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedEndProcedureOutputOp, RedOutputDeclarationMembers, depthStencilStencilEndProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembers, depthStencilSharesMemoryWithAnotherMember)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutputDeclarationMembers, colorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedFormat, RedOutputDeclarationMembers, colorsFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflag, RedOutputDeclarationMembers, colorsMultisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedSetProcedureOutputOp, RedOutputDeclarationMembers, colorsSetProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedEndProcedureOutputOp, RedOutputDeclarationMembers, colorsEndProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembers, colorsSharesMemoryWithAnotherMember)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedResolveMode, RedOutputDeclarationMembersResolveSources, resolveModeDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedResolveMode, RedOutputDeclarationMembersResolveSources, resolveModeStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembersResolveSources, resolveDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembersResolveSources, resolveColors)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructDeclarationMember, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStructMemberType, RedStructDeclarationMember, type)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructDeclarationMember, count)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedVisibleToStageBitflags, RedStructDeclarationMember, visibleToStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleSampler *, RedStructDeclarationMember, inlineSampler)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructDeclarationMemberArrayRO, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersDeclaration, variablesSlot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedVisibleToStageBitflags, RedProcedureParametersDeclaration, variablesVisibleToStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersDeclaration, variablesBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersDeclaration, structsDeclarationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleStructDeclaration, RedProcedureParametersDeclaration, structsDeclarations)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleStructDeclaration, RedProcedureParametersDeclaration, handlesDeclaration)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedPrimitiveTopology, RedProcedureState, inputAssemblyTopology)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, inputAssemblyPrimitiveRestartEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, viewportDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticX)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticY)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticDepthMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticDepthMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, scissorDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedProcedureState, scissorStaticX)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedProcedureState, scissorStaticY)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, scissorStaticWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, scissorStaticHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDepthClampEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDiscardAllPrimitivesEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCullMode, RedProcedureState, rasterizationCullMode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedFrontFace, RedProcedureState, rasterizationFrontFace)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDepthBiasEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDepthBiasDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, rasterizationDepthBiasStaticConstantFactor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, rasterizationDepthBiasStaticClamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, rasterizationDepthBiasStaticSlopeFactor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflag, RedProcedureState, multisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedProcedureState, multisampleSampleMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, multisampleSampleShadingEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, multisampleSampleShadingMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, multisampleAlphaToCoverageEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, multisampleAlphaToOneEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestDepthWriteEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCompareOp, RedProcedureState, depthTestDepthCompareOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestBoundsTestEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestBoundsTestDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, depthTestBoundsTestStaticMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, depthTestBoundsTestStaticMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestFrontStencilTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestFrontStencilTestPassDepthTestPassOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestFrontStencilTestPassDepthTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCompareOp, RedProcedureState, stencilTestFrontCompareOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestBackStencilTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestBackStencilTestPassDepthTestPassOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestBackStencilTestPassDepthTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCompareOp, RedProcedureState, stencilTestBackCompareOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestFrontAndBackDynamicCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestFrontAndBackDynamicWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestFrontAndBackDynamicReference)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, stencilTestFrontAndBackStaticCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, stencilTestFrontAndBackStaticWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, stencilTestFrontAndBackStaticReference)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, blendLogicOpEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedLogicOp, RedProcedureState, blendLogicOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, blendConstantsDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, blendConstantsStatic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, outputColorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedColorComponentBitflags, RedProcedureState, outputColorsWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, outputColorsBlendEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendColorFactorSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendColorFactorTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendOp, RedProcedureState, outputColorsBlendColorOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendAlphaFactorSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendAlphaFactorTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendOp, RedProcedureState, outputColorsBlendAlphaOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureStateExtensionIterator, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureStateExtensionIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureStateExtension, RedProcedureStateExtensionRasterizationMode, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureStateExtensionRasterizationMode, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedRasterizationMode, RedProcedureStateExtensionRasterizationMode, rasterizationMode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembers, depthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutputMembers, colorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembers, colors)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembersResolveTargets, depthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembersResolveTargets, colors)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayRange, arrayRBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayRange, arrayWBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayRange, bytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedImagePartBitflags, RedCopyImageParts, allParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageParts, level)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageParts, layersFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageParts, layersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedCopyImageOffset, texelX)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedCopyImageOffset, texelY)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedCopyImageOffset, texelZ)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageExtent, texelsCountWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageExtent, texelsCountHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageExtent, texelsCountDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageParts, RedCopyImageRange, imageRParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageOffset, RedCopyImageRange, imageROffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageParts, RedCopyImageRange, imageWParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageOffset, RedCopyImageRange, imageWOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageExtent, RedCopyImageRange, extent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayImageRange, arrayBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyArrayImageRange, arrayTexelsCountToNextRow)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyArrayImageRange, arrayTexelsCountToNextLayerOr3DDepthSliceDividedByTexelsCountToNextRow)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageParts, RedCopyArrayImageRange, imageParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageOffset, RedCopyArrayImageRange, imageOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageExtent, RedCopyArrayImageRange, imageExtent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedProcedureParametersHandleArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedProcedureParametersHandleArray, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedProcedureParametersHandleArray, setToMaxValue)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, setTo35)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureParametersHandle, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedProcedureParametersHandle, setTo00)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, setTo000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, setTo1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureParametersHandleType, RedProcedureParametersHandle, type)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureParametersHandle, setTo0000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedProcedureParametersHandleArray *, RedProcedureParametersHandle, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureParametersHandle, setTo00000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallGpuToCpuSignalSignal, RedCallProceduresAndAddresses, redCallGpuToCpuSignalSignal)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyArrayToArray, RedCallProceduresAndAddresses, redCallCopyArrayToArray)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyImageToImage, RedCallProceduresAndAddresses, redCallCopyImageToImage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyArrayToImage, RedCallProceduresAndAddresses, redCallCopyArrayToImage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyImageToArray, RedCallProceduresAndAddresses, redCallCopyImageToArray)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallProcedure, RedCallProceduresAndAddresses, redCallProcedure)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallProcedureIndexed, RedCallProceduresAndAddresses, redCallProcedureIndexed)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallProcedureCompute, RedCallProceduresAndAddresses, redCallProcedureCompute)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedure, RedCallProceduresAndAddresses, redCallSetProcedure)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureIndices, RedCallProceduresAndAddresses, redCallSetProcedureIndices)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureParametersVariables, RedCallProceduresAndAddresses, redCallSetProcedureParametersVariables)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureParametersStructs, RedCallProceduresAndAddresses, redCallSetProcedureParametersStructs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureParametersHandles, RedCallProceduresAndAddresses, redCallSetProcedureParametersHandles)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicDepthBias, RedCallProceduresAndAddresses, redCallSetDynamicDepthBias)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicDepthBounds, RedCallProceduresAndAddresses, redCallSetDynamicDepthBounds)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicStencilCompareMask, RedCallProceduresAndAddresses, redCallSetDynamicStencilCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicStencilWriteMask, RedCallProceduresAndAddresses, redCallSetDynamicStencilWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicStencilReference, RedCallProceduresAndAddresses, redCallSetDynamicStencilReference)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicBlendConstants, RedCallProceduresAndAddresses, redCallSetDynamicBlendConstants)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetDynamicViewport, RedCallProceduresAndAddresses, redCallSetDynamicViewport)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetDynamicScissor, RedCallProceduresAndAddresses, redCallSetDynamicScissor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetStructsMemory, RedCallProceduresAndAddresses, redCallSetStructsMemory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetProcedureParameters, RedCallProceduresAndAddresses, redCallSetProcedureParameters)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetProcedureOutput, RedCallProceduresAndAddresses, redCallSetProcedureOutput)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallEndProcedureOutput, RedCallProceduresAndAddresses, redCallEndProcedureOutput)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallUsageAliasOrderBarrier, RedCallProceduresAndAddresses, redCallUsageAliasOrderBarrier)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallMark, RedCallProceduresAndAddresses, redCallMark)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallMarkSet, RedCallProceduresAndAddresses, redCallMarkSet)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallMarkEnd, RedCallProceduresAndAddresses, redCallMarkEnd)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedOutputMembers *, RedInlineOutput, outputMembers)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedOutputMembersResolveTargets *, RedInlineOutput, outputMembersResolveTargets)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, r)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, g)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, b)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, a)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, r)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, g)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, b)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, a)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, r)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, g)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, b)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, a)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedUsageArray, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageArray, oldAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageArray, newAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageArray, oldAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageArray, newAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageArray, queueFamilyIndexSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageArray, queueFamilyIndexTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedUsageArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedUsageArray, arrayBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedUsageArray, arrayBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedUsageImage, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageImage, oldAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageImage, newAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageImage, oldAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageImage, newAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedState, RedUsageImage, oldState)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedState, RedUsageImage, newState)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, queueFamilyIndexSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, queueFamilyIndexTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleImage, RedUsageImage, image)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedImagePartBitflags, RedUsageImage, imageAllParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLevelsFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLevelsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLayersFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLayersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedAlias, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedAlias, oldResourceHandle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedAlias, newResourceHandle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedOrder, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedOrder, resourceHandle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, setTo4)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedGpuTimeline, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, waitForAndUnsignalGpuSignalsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleGpuSignal *, RedGpuTimeline, waitForAndUnsignalGpuSignals)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedGpuTimeline, setTo65536)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, callsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleCalls *, RedGpuTimeline, calls)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, signalGpuSignalsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleGpuSignal *, RedGpuTimeline, signalGpuSignals)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo1, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, supportsComputingLanguageFeatureLevel1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageStateExtensionIterator, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageSpecializationConstant, specId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageSpecializationConstant, specDataBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureComputingLanguageSpecializationConstant, specDataBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureComputingLanguageStateExtension, RedProcedureComputingLanguageStateExtensionSpecializationConstants, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedProcedureComputingLanguageSpecializationConstant *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specDataBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specData)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo2, RedGpuInfoOptionalInfoArrayTimestamp, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoArrayTimestamp, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoArrayTimestamp, supportsArrayTimestamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedGpuInfoOptionalInfoArrayTimestamp, queuesPrecisionBits64BitTicksCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfoOptionalInfoArrayTimestamp, nanosecondsPerTick)

#undef GS_MACRO_RED_STRUCT_MEMBER

  return ape_object_make_string(ape, "");
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedStructMemberSizeof GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*structName*/,
    APE_OBJECT_STRING/*structMemberName*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redStructMemberSizeof")
  getArgAs_CChars(const char *, structName, args[_i++]);
  getArgAs_CChars(const char *, memberName, args[_i++]);
  getArgAs_END

  const size_t structNameBytesCount = strlen(structName) + 1;
  const size_t memberNameBytesCount = strlen(memberName) + 1;

#define GS_MACRO_RED_STRUCT_MEMBER(GS_TYPE, TYPE, STRUCTURE, MEMBER) \
  if (structNameBytesCount == sizeof(#STRUCTURE)) { \
    if (memberNameBytesCount == sizeof(#MEMBER)) { \
      if (memcmp(structName, #STRUCTURE, structNameBytesCount) == 0) { \
        if (memcmp(memberName, #MEMBER, memberNameBytesCount) == 0) { \
          return ape_object_make_number((double)sizeof(((STRUCTURE *)0)->MEMBER)); \
        } \
      } \
    } \
  }

  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedArray, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedArray, memoryBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedArray, memoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedArray, memoryTypesSupported)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleImage, RedImage, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedImage, memoryBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedImage, memoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImage, memoryTypesSupported)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleOutput, RedOutput, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutput, width)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutput, height)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutput, depthStencilEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutput, colorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleCalls, RedCalls, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleCallsMemory, RedCalls, memory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedCalls, reusable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryType, memoryHeapIndex)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isGpuVram)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isCpuMappable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isCpuCoherent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isCpuCached)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryHeap, memoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryHeap, isGpuVram)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedQueueCopyLimits, copyBlockTexelsCountWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedQueueCopyLimits, copyBlockTexelsCountHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedQueueCopyLimits, copyBlockTexelsCountDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimitsDimensions, maxWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimitsDimensions, maxHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimitsDimensions, maxDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedImageFormatLimitsDimensions, RedImageFormatLimits, maxDimensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimits, maxLevelsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimits, maxLayersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedImageFormatLimits, supportedMultisampleCounts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedImageFormatLimits, maxBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, RedStatus, RedImageFormatLimits, status)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsCopyR)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsCopyW)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureRO)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureRW)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsOutputDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsOutputColor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureROFilteringLinear)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureRWAtomics)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsOutputColorBlend)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleGpu, RedGpuInfo, gpu)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleGpuDevice, RedGpuInfo, gpuDevice)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedGpuInfo, gpuName)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuType, RedGpuInfo, gpuType)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, gpuVendorId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, gpuDeviceId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, gpuDriverVersion)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfo, gpuProcedureCacheUuid)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, memoryTypesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedMemoryType *, RedGpuInfo, memoryTypes)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const char **, RedGpuInfo, memoryTypesDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, memoryHeapsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedMemoryHeap *, RedGpuInfo, memoryHeaps)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const char **, RedGpuInfo, memoryHeapsDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, queuesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleQueue *, RedGpuInfo, queues)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const char **, RedGpuInfo, queuesDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedGpuInfo, queuesFamilyIndex)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedBool32 *, RedGpuInfo, queuesCanCopy)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedBool32 *, RedGpuInfo, queuesCanDraw)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedBool32 *, RedGpuInfo, queuesCanCompute)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedQueueCopyLimits *, RedGpuInfo, queuesCopyLimits)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxMemoryAllocateCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minMemoryAllocateBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, maxMemoryAllocateBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minMemoryNonCoherentBlockBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxCreateSamplerCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minMemoryPageSeparationArrayImageBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minArrayROCStructMemberRangeBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, maxArrayROCStructMemberRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minArrayRORWStructMemberRangeBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, maxArrayRORWStructMemberRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxArrayIndexUint32Value)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensions1D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensions2D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensions3D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensionsCube)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageLayersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxSamplerMipLodBias)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxSamplerAnisotropy)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsSamplerFilteringMagMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsSamplerFilteringMip)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxOutputWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxOutputHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxOutputColorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForOutputDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForOutputStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForOutputColor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForEmptyOutput)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructSlotsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageArrayROCsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageArrayRORWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageSamplersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageTextureROsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageTextureRWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageAllResourcesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructArrayROCsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructArrayRORWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructSamplersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructTextureROsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructTextureRWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxProcedureParametersVariablesBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxViewportDimensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, minViewportBoundsRange)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxViewportBoundsRange)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsViewportCoordinates)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsViewportBounds)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxPerStageClipDistances)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxPerStageCullDistances)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxPerStageClipAndCullDistances)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxVertexOutputLocationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentInputLocationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentOutputColorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentOutputColorsCountBlendDualSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentOutputResourcesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeSharedMemoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeWorkgroupsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeWorkgroupInvocationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeWorkgroupDimensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedGpuInfo, minImageSampleImageFetchOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageSampleImageFetchOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedGpuInfo, minImageGatherOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageGatherOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, minInterpolateAtOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxInterpolateAtOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsInterpolateAtOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, optimalCopyArrayImageRangeArrayBytesFirstBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, optimalCopyArrayImageRangeArrayTexelsCountToNextRowBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsWsi)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsMemoryGetBudget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsFullArrayIndexUint32Value)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsSamplerAnisotropy)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsTextureDimensionsCubeLayered)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateRasterizationDepthClamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateRasterizationDepthBiasDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateRasterizationDepthBiasClamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateMultisampleSampleShading)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateMultisampleAlphaToOne)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateDepthTestBoundsTest)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateDepthTestBoundsTestDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateStencilTestFrontAndBackDynamicCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateStencilTestFrontAndBackDynamicWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateBlendLogicOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateOutputColorsBlendVaryingPerColor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateOutputColorsBlendDualSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsMultisampleEmptyOutputVariableMultisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsMultisampleStandardSampleLocations)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeWritesAndAtomicsInStageVertex)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeWritesAndAtomicsInStageFragment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeImageGatherExtended)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWExtendedFormats)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWMultisample)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWReadWithoutFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWWriteWithoutFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfArrayROCs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfArrayRORWs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfSamplers)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfTextureROs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfTextureRWs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeClipDistance)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeCullDistance)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeInt64)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeFloat64)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeMinLod)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions1D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions2D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions2DMultisample)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions2DWithTextureDimensionsCubeAndCubeLayered)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions3D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions3DWithTextureDimensions2DAnd2DLayered)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatFeatures *, RedGpuInfo, imageFormatsFeatures)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfo, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, RedStatus, RedStatuses, status)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStatuses, statusCode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusHresult)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureId, RedStatuses, statusProcedureId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedStatuses, statusFile)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusLine)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, RedStatus, RedStatuses, statusError)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStatuses, statusErrorCode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusErrorHresult)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureId, RedStatuses, statusErrorProcedureId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedStatuses, statusErrorFile)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusErrorLine)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedStatuses, statusErrorDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedTypeContext, gpusCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedGpuInfo *, RedTypeContext, gpus)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedStatuses *, RedTypeContext, gpusStatuses)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleContext, RedTypeContext, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, void *, RedTypeContext, userData)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfoOptionalInfoIterator, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoAdditionalInfo0, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoAdditionalInfo0, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsArraysImagesUsageBeforeMemorySet)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfArrays)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfImages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfImagesMultisample)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfImagesDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoDriverProperties, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoDriverProperties, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedDriverId, RedGpuInfoOptionalInfoDriverProperties, id)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedGpuInfoOptionalInfoDriverProperties, name)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedGpuInfoOptionalInfoDriverProperties, info)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionMajor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionMinor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionSubminor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionPatch)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoResolveDepthStencil, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoResolveDepthStencil, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthSampleIndexZero)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthAverage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilSampleIndexZero)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilAverage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveIndependentNone)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveIndependent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoProcedureParametersHandles, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoProcedureParametersHandles, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoProcedureParametersHandles, supportsProcedureParametersHandles)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfoOptionalInfoProcedureParametersHandles, maxProcedureParametersHandlesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoRasterizationMode, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoRasterizationMode, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsRasterizationModeOverestimate)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsRasterizationModeUnderestimate)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsGuaranteedZeroAreaBackFacingTriangles)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsGpuCodeFullyCoveredEXT)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoFormalMemoryModel, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoFormalMemoryModel, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoFormalMemoryModel, supportsFormalMemoryModel)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoFormalMemoryModel, supportsFormalMemoryModelGpuScopeSynchronization)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoFormalMemoryModel, supportsFormalMemoryModelAvailabilityAndVisibilityChains)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoRayTracing, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoRayTracing, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRayTracing, supportsRayTracing)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryBudget, setTo1000237000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMemoryBudget, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryBudget, memoryHeapsBudget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryBudget, memoryHeapsUsage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryArray, setTo1000157000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMemoryArray, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedMemoryArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleMemory, RedMemoryArray, memory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryArray, memoryBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryImage, setTo1000157001)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMemoryImage, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleImage, RedMemoryImage, image)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleMemory, RedMemoryImage, memory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryImage, memoryBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMappableMemoryRange, setTo6)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMappableMemoryRange, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleMemory, RedMappableMemoryRange, mappableMemory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMappableMemoryRange, mappableMemoryRangeBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMappableMemoryRange, mappableMemoryRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleSampler, RedStructMemberTexture, sampler)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedStructMemberTexture, texture)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMemberTexture, setTo1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedStructMemberArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedStructMemberArray, arrayRangeBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedStructMemberArray, arrayRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, setTo35)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedStructMember, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleStruct, RedStructMember, structure)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, first)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, count)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStructMemberType, RedStructMember, type)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedStructMemberTexture *, RedStructMember, textures)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedStructMemberArray *, RedStructMember, arrays)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedStructMember, setTo00)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedContextOptionalSettingsIterator, settings)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedContextOptionalSettingsIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedContextOptionalSettings, RedContextOptionalSettings0, settings)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedContextOptionalSettings0, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedContextOptionalSettings0, skipCheckingContextLayers)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedContextOptionalSettings0, skipCheckingContextExtensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedContextOptionalSettings0, gpusExposeOnlyOneQueue)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedHandleInfo, _0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedHandleInfo, _1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedHandleType, RedHandleInfo, handleType)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedHandleInfo, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedHandleInfo, handleName)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, _0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedDebugCallbackData, _1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, statusCode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedDebugCallbackData, messageIdName)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedDebugCallbackData, statusHresult)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedDebugCallbackData, message)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, _2)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedDebugCallbackData, _3)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, _4)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedDebugCallbackData, _5)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, handleInfosCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleInfo *, RedDebugCallbackData, handleInfos)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedMemoryAllocationTag, tag)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembers, depthStencilEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedFormat, RedOutputDeclarationMembers, depthStencilFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflag, RedOutputDeclarationMembers, depthStencilMultisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedSetProcedureOutputOp, RedOutputDeclarationMembers, depthStencilDepthSetProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedEndProcedureOutputOp, RedOutputDeclarationMembers, depthStencilDepthEndProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedSetProcedureOutputOp, RedOutputDeclarationMembers, depthStencilStencilSetProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedEndProcedureOutputOp, RedOutputDeclarationMembers, depthStencilStencilEndProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembers, depthStencilSharesMemoryWithAnotherMember)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutputDeclarationMembers, colorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedFormat, RedOutputDeclarationMembers, colorsFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflag, RedOutputDeclarationMembers, colorsMultisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedSetProcedureOutputOp, RedOutputDeclarationMembers, colorsSetProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedEndProcedureOutputOp, RedOutputDeclarationMembers, colorsEndProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembers, colorsSharesMemoryWithAnotherMember)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedResolveMode, RedOutputDeclarationMembersResolveSources, resolveModeDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedResolveMode, RedOutputDeclarationMembersResolveSources, resolveModeStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembersResolveSources, resolveDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembersResolveSources, resolveColors)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructDeclarationMember, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStructMemberType, RedStructDeclarationMember, type)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructDeclarationMember, count)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedVisibleToStageBitflags, RedStructDeclarationMember, visibleToStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleSampler *, RedStructDeclarationMember, inlineSampler)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructDeclarationMemberArrayRO, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersDeclaration, variablesSlot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedVisibleToStageBitflags, RedProcedureParametersDeclaration, variablesVisibleToStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersDeclaration, variablesBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersDeclaration, structsDeclarationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleStructDeclaration, RedProcedureParametersDeclaration, structsDeclarations)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleStructDeclaration, RedProcedureParametersDeclaration, handlesDeclaration)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedPrimitiveTopology, RedProcedureState, inputAssemblyTopology)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, inputAssemblyPrimitiveRestartEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, viewportDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticX)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticY)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticDepthMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticDepthMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, scissorDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedProcedureState, scissorStaticX)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedProcedureState, scissorStaticY)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, scissorStaticWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, scissorStaticHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDepthClampEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDiscardAllPrimitivesEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCullMode, RedProcedureState, rasterizationCullMode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedFrontFace, RedProcedureState, rasterizationFrontFace)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDepthBiasEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDepthBiasDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, rasterizationDepthBiasStaticConstantFactor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, rasterizationDepthBiasStaticClamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, rasterizationDepthBiasStaticSlopeFactor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflag, RedProcedureState, multisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedProcedureState, multisampleSampleMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, multisampleSampleShadingEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, multisampleSampleShadingMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, multisampleAlphaToCoverageEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, multisampleAlphaToOneEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestDepthWriteEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCompareOp, RedProcedureState, depthTestDepthCompareOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestBoundsTestEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestBoundsTestDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, depthTestBoundsTestStaticMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, depthTestBoundsTestStaticMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestFrontStencilTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestFrontStencilTestPassDepthTestPassOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestFrontStencilTestPassDepthTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCompareOp, RedProcedureState, stencilTestFrontCompareOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestBackStencilTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestBackStencilTestPassDepthTestPassOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestBackStencilTestPassDepthTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCompareOp, RedProcedureState, stencilTestBackCompareOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestFrontAndBackDynamicCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestFrontAndBackDynamicWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestFrontAndBackDynamicReference)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, stencilTestFrontAndBackStaticCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, stencilTestFrontAndBackStaticWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, stencilTestFrontAndBackStaticReference)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, blendLogicOpEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedLogicOp, RedProcedureState, blendLogicOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, blendConstantsDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, blendConstantsStatic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, outputColorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedColorComponentBitflags, RedProcedureState, outputColorsWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, outputColorsBlendEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendColorFactorSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendColorFactorTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendOp, RedProcedureState, outputColorsBlendColorOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendAlphaFactorSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendAlphaFactorTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendOp, RedProcedureState, outputColorsBlendAlphaOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureStateExtensionIterator, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureStateExtensionIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureStateExtension, RedProcedureStateExtensionRasterizationMode, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureStateExtensionRasterizationMode, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedRasterizationMode, RedProcedureStateExtensionRasterizationMode, rasterizationMode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembers, depthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutputMembers, colorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembers, colors)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembersResolveTargets, depthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembersResolveTargets, colors)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayRange, arrayRBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayRange, arrayWBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayRange, bytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedImagePartBitflags, RedCopyImageParts, allParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageParts, level)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageParts, layersFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageParts, layersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedCopyImageOffset, texelX)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedCopyImageOffset, texelY)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedCopyImageOffset, texelZ)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageExtent, texelsCountWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageExtent, texelsCountHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageExtent, texelsCountDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageParts, RedCopyImageRange, imageRParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageOffset, RedCopyImageRange, imageROffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageParts, RedCopyImageRange, imageWParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageOffset, RedCopyImageRange, imageWOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageExtent, RedCopyImageRange, extent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayImageRange, arrayBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyArrayImageRange, arrayTexelsCountToNextRow)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyArrayImageRange, arrayTexelsCountToNextLayerOr3DDepthSliceDividedByTexelsCountToNextRow)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageParts, RedCopyArrayImageRange, imageParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageOffset, RedCopyArrayImageRange, imageOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageExtent, RedCopyArrayImageRange, imageExtent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedProcedureParametersHandleArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedProcedureParametersHandleArray, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedProcedureParametersHandleArray, setToMaxValue)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, setTo35)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureParametersHandle, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedProcedureParametersHandle, setTo00)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, setTo000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, setTo1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureParametersHandleType, RedProcedureParametersHandle, type)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureParametersHandle, setTo0000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedProcedureParametersHandleArray *, RedProcedureParametersHandle, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureParametersHandle, setTo00000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallGpuToCpuSignalSignal, RedCallProceduresAndAddresses, redCallGpuToCpuSignalSignal)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyArrayToArray, RedCallProceduresAndAddresses, redCallCopyArrayToArray)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyImageToImage, RedCallProceduresAndAddresses, redCallCopyImageToImage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyArrayToImage, RedCallProceduresAndAddresses, redCallCopyArrayToImage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyImageToArray, RedCallProceduresAndAddresses, redCallCopyImageToArray)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallProcedure, RedCallProceduresAndAddresses, redCallProcedure)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallProcedureIndexed, RedCallProceduresAndAddresses, redCallProcedureIndexed)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallProcedureCompute, RedCallProceduresAndAddresses, redCallProcedureCompute)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedure, RedCallProceduresAndAddresses, redCallSetProcedure)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureIndices, RedCallProceduresAndAddresses, redCallSetProcedureIndices)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureParametersVariables, RedCallProceduresAndAddresses, redCallSetProcedureParametersVariables)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureParametersStructs, RedCallProceduresAndAddresses, redCallSetProcedureParametersStructs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureParametersHandles, RedCallProceduresAndAddresses, redCallSetProcedureParametersHandles)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicDepthBias, RedCallProceduresAndAddresses, redCallSetDynamicDepthBias)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicDepthBounds, RedCallProceduresAndAddresses, redCallSetDynamicDepthBounds)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicStencilCompareMask, RedCallProceduresAndAddresses, redCallSetDynamicStencilCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicStencilWriteMask, RedCallProceduresAndAddresses, redCallSetDynamicStencilWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicStencilReference, RedCallProceduresAndAddresses, redCallSetDynamicStencilReference)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicBlendConstants, RedCallProceduresAndAddresses, redCallSetDynamicBlendConstants)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetDynamicViewport, RedCallProceduresAndAddresses, redCallSetDynamicViewport)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetDynamicScissor, RedCallProceduresAndAddresses, redCallSetDynamicScissor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetStructsMemory, RedCallProceduresAndAddresses, redCallSetStructsMemory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetProcedureParameters, RedCallProceduresAndAddresses, redCallSetProcedureParameters)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetProcedureOutput, RedCallProceduresAndAddresses, redCallSetProcedureOutput)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallEndProcedureOutput, RedCallProceduresAndAddresses, redCallEndProcedureOutput)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallUsageAliasOrderBarrier, RedCallProceduresAndAddresses, redCallUsageAliasOrderBarrier)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallMark, RedCallProceduresAndAddresses, redCallMark)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallMarkSet, RedCallProceduresAndAddresses, redCallMarkSet)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallMarkEnd, RedCallProceduresAndAddresses, redCallMarkEnd)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedOutputMembers *, RedInlineOutput, outputMembers)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedOutputMembersResolveTargets *, RedInlineOutput, outputMembersResolveTargets)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, r)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, g)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, b)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, a)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, r)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, g)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, b)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, a)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, r)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, g)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, b)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, a)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedUsageArray, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageArray, oldAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageArray, newAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageArray, oldAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageArray, newAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageArray, queueFamilyIndexSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageArray, queueFamilyIndexTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedUsageArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedUsageArray, arrayBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedUsageArray, arrayBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedUsageImage, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageImage, oldAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageImage, newAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageImage, oldAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageImage, newAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedState, RedUsageImage, oldState)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedState, RedUsageImage, newState)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, queueFamilyIndexSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, queueFamilyIndexTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleImage, RedUsageImage, image)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedImagePartBitflags, RedUsageImage, imageAllParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLevelsFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLevelsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLayersFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLayersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedAlias, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedAlias, oldResourceHandle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedAlias, newResourceHandle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedOrder, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedOrder, resourceHandle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, setTo4)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedGpuTimeline, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, waitForAndUnsignalGpuSignalsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleGpuSignal *, RedGpuTimeline, waitForAndUnsignalGpuSignals)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedGpuTimeline, setTo65536)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, callsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleCalls *, RedGpuTimeline, calls)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, signalGpuSignalsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleGpuSignal *, RedGpuTimeline, signalGpuSignals)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo1, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, supportsComputingLanguageFeatureLevel1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageStateExtensionIterator, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageSpecializationConstant, specId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageSpecializationConstant, specDataBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureComputingLanguageSpecializationConstant, specDataBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureComputingLanguageStateExtension, RedProcedureComputingLanguageStateExtensionSpecializationConstants, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedProcedureComputingLanguageSpecializationConstant *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specDataBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specData)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo2, RedGpuInfoOptionalInfoArrayTimestamp, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoArrayTimestamp, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoArrayTimestamp, supportsArrayTimestamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedGpuInfoOptionalInfoArrayTimestamp, queuesPrecisionBits64BitTicksCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfoOptionalInfoArrayTimestamp, nanosecondsPerTick)

#undef GS_MACRO_RED_STRUCT_MEMBER

  return ape_object_make_number((double)((uint64_t)-1));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedStructMemberOffsetof GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*structName*/,
    APE_OBJECT_STRING/*structMemberName*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redStructMemberOffsetof")
  getArgAs_CChars(const char *, structName, args[_i++]);
  getArgAs_CChars(const char *, memberName, args[_i++]);
  getArgAs_END

  const size_t structNameBytesCount = strlen(structName) + 1;
  const size_t memberNameBytesCount = strlen(memberName) + 1;

#define GS_MACRO_RED_STRUCT_MEMBER(GS_TYPE, TYPE, STRUCTURE, MEMBER) \
  if (structNameBytesCount == sizeof(#STRUCTURE)) { \
    if (memberNameBytesCount == sizeof(#MEMBER)) { \
      if (memcmp(structName, #STRUCTURE, structNameBytesCount) == 0) { \
        if (memcmp(memberName, #MEMBER, memberNameBytesCount) == 0) { \
          return ape_object_make_number((double)offsetof(STRUCTURE, MEMBER)); \
        } \
      } \
    } \
  }

  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedArray, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedArray, memoryBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedArray, memoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedArray, memoryTypesSupported)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleImage, RedImage, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedImage, memoryBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedImage, memoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImage, memoryTypesSupported)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleOutput, RedOutput, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutput, width)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutput, height)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutput, depthStencilEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutput, colorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleCalls, RedCalls, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleCallsMemory, RedCalls, memory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedCalls, reusable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryType, memoryHeapIndex)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isGpuVram)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isCpuMappable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isCpuCoherent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isCpuCached)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryHeap, memoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryHeap, isGpuVram)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedQueueCopyLimits, copyBlockTexelsCountWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedQueueCopyLimits, copyBlockTexelsCountHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedQueueCopyLimits, copyBlockTexelsCountDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimitsDimensions, maxWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimitsDimensions, maxHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimitsDimensions, maxDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedImageFormatLimitsDimensions, RedImageFormatLimits, maxDimensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimits, maxLevelsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimits, maxLayersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedImageFormatLimits, supportedMultisampleCounts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedImageFormatLimits, maxBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, RedStatus, RedImageFormatLimits, status)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsCopyR)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsCopyW)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureRO)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureRW)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsOutputDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsOutputColor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureROFilteringLinear)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureRWAtomics)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsOutputColorBlend)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleGpu, RedGpuInfo, gpu)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleGpuDevice, RedGpuInfo, gpuDevice)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedGpuInfo, gpuName)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuType, RedGpuInfo, gpuType)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, gpuVendorId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, gpuDeviceId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, gpuDriverVersion)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfo, gpuProcedureCacheUuid)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, memoryTypesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedMemoryType *, RedGpuInfo, memoryTypes)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const char **, RedGpuInfo, memoryTypesDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, memoryHeapsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedMemoryHeap *, RedGpuInfo, memoryHeaps)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const char **, RedGpuInfo, memoryHeapsDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, queuesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleQueue *, RedGpuInfo, queues)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const char **, RedGpuInfo, queuesDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedGpuInfo, queuesFamilyIndex)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedBool32 *, RedGpuInfo, queuesCanCopy)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedBool32 *, RedGpuInfo, queuesCanDraw)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedBool32 *, RedGpuInfo, queuesCanCompute)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedQueueCopyLimits *, RedGpuInfo, queuesCopyLimits)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxMemoryAllocateCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minMemoryAllocateBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, maxMemoryAllocateBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minMemoryNonCoherentBlockBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxCreateSamplerCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minMemoryPageSeparationArrayImageBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minArrayROCStructMemberRangeBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, maxArrayROCStructMemberRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minArrayRORWStructMemberRangeBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, maxArrayRORWStructMemberRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxArrayIndexUint32Value)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensions1D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensions2D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensions3D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensionsCube)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageLayersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxSamplerMipLodBias)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxSamplerAnisotropy)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsSamplerFilteringMagMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsSamplerFilteringMip)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxOutputWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxOutputHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxOutputColorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForOutputDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForOutputStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForOutputColor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForEmptyOutput)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructSlotsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageArrayROCsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageArrayRORWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageSamplersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageTextureROsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageTextureRWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageAllResourcesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructArrayROCsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructArrayRORWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructSamplersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructTextureROsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructTextureRWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxProcedureParametersVariablesBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxViewportDimensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, minViewportBoundsRange)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxViewportBoundsRange)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsViewportCoordinates)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsViewportBounds)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxPerStageClipDistances)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxPerStageCullDistances)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxPerStageClipAndCullDistances)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxVertexOutputLocationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentInputLocationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentOutputColorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentOutputColorsCountBlendDualSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentOutputResourcesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeSharedMemoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeWorkgroupsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeWorkgroupInvocationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeWorkgroupDimensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedGpuInfo, minImageSampleImageFetchOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageSampleImageFetchOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedGpuInfo, minImageGatherOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageGatherOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, minInterpolateAtOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxInterpolateAtOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsInterpolateAtOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, optimalCopyArrayImageRangeArrayBytesFirstBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, optimalCopyArrayImageRangeArrayTexelsCountToNextRowBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsWsi)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsMemoryGetBudget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsFullArrayIndexUint32Value)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsSamplerAnisotropy)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsTextureDimensionsCubeLayered)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateRasterizationDepthClamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateRasterizationDepthBiasDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateRasterizationDepthBiasClamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateMultisampleSampleShading)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateMultisampleAlphaToOne)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateDepthTestBoundsTest)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateDepthTestBoundsTestDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateStencilTestFrontAndBackDynamicCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateStencilTestFrontAndBackDynamicWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateBlendLogicOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateOutputColorsBlendVaryingPerColor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateOutputColorsBlendDualSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsMultisampleEmptyOutputVariableMultisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsMultisampleStandardSampleLocations)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeWritesAndAtomicsInStageVertex)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeWritesAndAtomicsInStageFragment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeImageGatherExtended)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWExtendedFormats)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWMultisample)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWReadWithoutFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWWriteWithoutFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfArrayROCs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfArrayRORWs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfSamplers)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfTextureROs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfTextureRWs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeClipDistance)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeCullDistance)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeInt64)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeFloat64)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeMinLod)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions1D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions2D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions2DMultisample)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions2DWithTextureDimensionsCubeAndCubeLayered)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions3D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions3DWithTextureDimensions2DAnd2DLayered)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatFeatures *, RedGpuInfo, imageFormatsFeatures)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfo, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, RedStatus, RedStatuses, status)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStatuses, statusCode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusHresult)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureId, RedStatuses, statusProcedureId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedStatuses, statusFile)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusLine)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, RedStatus, RedStatuses, statusError)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStatuses, statusErrorCode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusErrorHresult)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureId, RedStatuses, statusErrorProcedureId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedStatuses, statusErrorFile)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusErrorLine)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedStatuses, statusErrorDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedTypeContext, gpusCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedGpuInfo *, RedTypeContext, gpus)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedStatuses *, RedTypeContext, gpusStatuses)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleContext, RedTypeContext, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, void *, RedTypeContext, userData)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfoOptionalInfoIterator, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoAdditionalInfo0, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoAdditionalInfo0, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsArraysImagesUsageBeforeMemorySet)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfArrays)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfImages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfImagesMultisample)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfImagesDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoDriverProperties, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoDriverProperties, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedDriverId, RedGpuInfoOptionalInfoDriverProperties, id)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedGpuInfoOptionalInfoDriverProperties, name)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedGpuInfoOptionalInfoDriverProperties, info)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionMajor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionMinor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionSubminor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionPatch)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoResolveDepthStencil, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoResolveDepthStencil, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthSampleIndexZero)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthAverage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilSampleIndexZero)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilAverage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveIndependentNone)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveIndependent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoProcedureParametersHandles, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoProcedureParametersHandles, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoProcedureParametersHandles, supportsProcedureParametersHandles)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfoOptionalInfoProcedureParametersHandles, maxProcedureParametersHandlesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoRasterizationMode, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoRasterizationMode, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsRasterizationModeOverestimate)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsRasterizationModeUnderestimate)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsGuaranteedZeroAreaBackFacingTriangles)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsGpuCodeFullyCoveredEXT)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoFormalMemoryModel, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoFormalMemoryModel, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoFormalMemoryModel, supportsFormalMemoryModel)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoFormalMemoryModel, supportsFormalMemoryModelGpuScopeSynchronization)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoFormalMemoryModel, supportsFormalMemoryModelAvailabilityAndVisibilityChains)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoRayTracing, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoRayTracing, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRayTracing, supportsRayTracing)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryBudget, setTo1000237000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMemoryBudget, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryBudget, memoryHeapsBudget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryBudget, memoryHeapsUsage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryArray, setTo1000157000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMemoryArray, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedMemoryArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleMemory, RedMemoryArray, memory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryArray, memoryBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryImage, setTo1000157001)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMemoryImage, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleImage, RedMemoryImage, image)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleMemory, RedMemoryImage, memory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryImage, memoryBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMappableMemoryRange, setTo6)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMappableMemoryRange, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleMemory, RedMappableMemoryRange, mappableMemory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMappableMemoryRange, mappableMemoryRangeBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMappableMemoryRange, mappableMemoryRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleSampler, RedStructMemberTexture, sampler)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedStructMemberTexture, texture)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMemberTexture, setTo1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedStructMemberArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedStructMemberArray, arrayRangeBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedStructMemberArray, arrayRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, setTo35)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedStructMember, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleStruct, RedStructMember, structure)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, first)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, count)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStructMemberType, RedStructMember, type)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedStructMemberTexture *, RedStructMember, textures)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedStructMemberArray *, RedStructMember, arrays)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedStructMember, setTo00)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedContextOptionalSettingsIterator, settings)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedContextOptionalSettingsIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedContextOptionalSettings, RedContextOptionalSettings0, settings)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedContextOptionalSettings0, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedContextOptionalSettings0, skipCheckingContextLayers)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedContextOptionalSettings0, skipCheckingContextExtensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedContextOptionalSettings0, gpusExposeOnlyOneQueue)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedHandleInfo, _0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedHandleInfo, _1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedHandleType, RedHandleInfo, handleType)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedHandleInfo, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedHandleInfo, handleName)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, _0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedDebugCallbackData, _1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, statusCode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedDebugCallbackData, messageIdName)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedDebugCallbackData, statusHresult)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedDebugCallbackData, message)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, _2)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedDebugCallbackData, _3)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, _4)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedDebugCallbackData, _5)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, handleInfosCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleInfo *, RedDebugCallbackData, handleInfos)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedMemoryAllocationTag, tag)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembers, depthStencilEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedFormat, RedOutputDeclarationMembers, depthStencilFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflag, RedOutputDeclarationMembers, depthStencilMultisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedSetProcedureOutputOp, RedOutputDeclarationMembers, depthStencilDepthSetProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedEndProcedureOutputOp, RedOutputDeclarationMembers, depthStencilDepthEndProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedSetProcedureOutputOp, RedOutputDeclarationMembers, depthStencilStencilSetProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedEndProcedureOutputOp, RedOutputDeclarationMembers, depthStencilStencilEndProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembers, depthStencilSharesMemoryWithAnotherMember)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutputDeclarationMembers, colorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedFormat, RedOutputDeclarationMembers, colorsFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflag, RedOutputDeclarationMembers, colorsMultisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedSetProcedureOutputOp, RedOutputDeclarationMembers, colorsSetProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedEndProcedureOutputOp, RedOutputDeclarationMembers, colorsEndProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembers, colorsSharesMemoryWithAnotherMember)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedResolveMode, RedOutputDeclarationMembersResolveSources, resolveModeDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedResolveMode, RedOutputDeclarationMembersResolveSources, resolveModeStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembersResolveSources, resolveDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembersResolveSources, resolveColors)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructDeclarationMember, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStructMemberType, RedStructDeclarationMember, type)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructDeclarationMember, count)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedVisibleToStageBitflags, RedStructDeclarationMember, visibleToStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleSampler *, RedStructDeclarationMember, inlineSampler)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructDeclarationMemberArrayRO, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersDeclaration, variablesSlot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedVisibleToStageBitflags, RedProcedureParametersDeclaration, variablesVisibleToStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersDeclaration, variablesBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersDeclaration, structsDeclarationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleStructDeclaration, RedProcedureParametersDeclaration, structsDeclarations)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleStructDeclaration, RedProcedureParametersDeclaration, handlesDeclaration)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedPrimitiveTopology, RedProcedureState, inputAssemblyTopology)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, inputAssemblyPrimitiveRestartEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, viewportDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticX)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticY)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticDepthMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticDepthMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, scissorDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedProcedureState, scissorStaticX)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedProcedureState, scissorStaticY)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, scissorStaticWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, scissorStaticHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDepthClampEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDiscardAllPrimitivesEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCullMode, RedProcedureState, rasterizationCullMode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedFrontFace, RedProcedureState, rasterizationFrontFace)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDepthBiasEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDepthBiasDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, rasterizationDepthBiasStaticConstantFactor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, rasterizationDepthBiasStaticClamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, rasterizationDepthBiasStaticSlopeFactor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflag, RedProcedureState, multisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedProcedureState, multisampleSampleMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, multisampleSampleShadingEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, multisampleSampleShadingMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, multisampleAlphaToCoverageEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, multisampleAlphaToOneEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestDepthWriteEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCompareOp, RedProcedureState, depthTestDepthCompareOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestBoundsTestEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestBoundsTestDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, depthTestBoundsTestStaticMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, depthTestBoundsTestStaticMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestFrontStencilTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestFrontStencilTestPassDepthTestPassOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestFrontStencilTestPassDepthTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCompareOp, RedProcedureState, stencilTestFrontCompareOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestBackStencilTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestBackStencilTestPassDepthTestPassOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestBackStencilTestPassDepthTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCompareOp, RedProcedureState, stencilTestBackCompareOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestFrontAndBackDynamicCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestFrontAndBackDynamicWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestFrontAndBackDynamicReference)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, stencilTestFrontAndBackStaticCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, stencilTestFrontAndBackStaticWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, stencilTestFrontAndBackStaticReference)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, blendLogicOpEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedLogicOp, RedProcedureState, blendLogicOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, blendConstantsDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, blendConstantsStatic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, outputColorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedColorComponentBitflags, RedProcedureState, outputColorsWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, outputColorsBlendEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendColorFactorSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendColorFactorTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendOp, RedProcedureState, outputColorsBlendColorOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendAlphaFactorSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendAlphaFactorTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendOp, RedProcedureState, outputColorsBlendAlphaOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureStateExtensionIterator, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureStateExtensionIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureStateExtension, RedProcedureStateExtensionRasterizationMode, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureStateExtensionRasterizationMode, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedRasterizationMode, RedProcedureStateExtensionRasterizationMode, rasterizationMode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembers, depthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutputMembers, colorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembers, colors)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembersResolveTargets, depthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembersResolveTargets, colors)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayRange, arrayRBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayRange, arrayWBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayRange, bytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedImagePartBitflags, RedCopyImageParts, allParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageParts, level)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageParts, layersFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageParts, layersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedCopyImageOffset, texelX)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedCopyImageOffset, texelY)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedCopyImageOffset, texelZ)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageExtent, texelsCountWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageExtent, texelsCountHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageExtent, texelsCountDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageParts, RedCopyImageRange, imageRParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageOffset, RedCopyImageRange, imageROffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageParts, RedCopyImageRange, imageWParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageOffset, RedCopyImageRange, imageWOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageExtent, RedCopyImageRange, extent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayImageRange, arrayBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyArrayImageRange, arrayTexelsCountToNextRow)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyArrayImageRange, arrayTexelsCountToNextLayerOr3DDepthSliceDividedByTexelsCountToNextRow)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageParts, RedCopyArrayImageRange, imageParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageOffset, RedCopyArrayImageRange, imageOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageExtent, RedCopyArrayImageRange, imageExtent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedProcedureParametersHandleArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedProcedureParametersHandleArray, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedProcedureParametersHandleArray, setToMaxValue)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, setTo35)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureParametersHandle, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedProcedureParametersHandle, setTo00)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, setTo000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, setTo1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureParametersHandleType, RedProcedureParametersHandle, type)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureParametersHandle, setTo0000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedProcedureParametersHandleArray *, RedProcedureParametersHandle, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureParametersHandle, setTo00000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallGpuToCpuSignalSignal, RedCallProceduresAndAddresses, redCallGpuToCpuSignalSignal)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyArrayToArray, RedCallProceduresAndAddresses, redCallCopyArrayToArray)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyImageToImage, RedCallProceduresAndAddresses, redCallCopyImageToImage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyArrayToImage, RedCallProceduresAndAddresses, redCallCopyArrayToImage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyImageToArray, RedCallProceduresAndAddresses, redCallCopyImageToArray)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallProcedure, RedCallProceduresAndAddresses, redCallProcedure)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallProcedureIndexed, RedCallProceduresAndAddresses, redCallProcedureIndexed)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallProcedureCompute, RedCallProceduresAndAddresses, redCallProcedureCompute)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedure, RedCallProceduresAndAddresses, redCallSetProcedure)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureIndices, RedCallProceduresAndAddresses, redCallSetProcedureIndices)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureParametersVariables, RedCallProceduresAndAddresses, redCallSetProcedureParametersVariables)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureParametersStructs, RedCallProceduresAndAddresses, redCallSetProcedureParametersStructs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureParametersHandles, RedCallProceduresAndAddresses, redCallSetProcedureParametersHandles)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicDepthBias, RedCallProceduresAndAddresses, redCallSetDynamicDepthBias)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicDepthBounds, RedCallProceduresAndAddresses, redCallSetDynamicDepthBounds)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicStencilCompareMask, RedCallProceduresAndAddresses, redCallSetDynamicStencilCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicStencilWriteMask, RedCallProceduresAndAddresses, redCallSetDynamicStencilWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicStencilReference, RedCallProceduresAndAddresses, redCallSetDynamicStencilReference)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicBlendConstants, RedCallProceduresAndAddresses, redCallSetDynamicBlendConstants)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetDynamicViewport, RedCallProceduresAndAddresses, redCallSetDynamicViewport)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetDynamicScissor, RedCallProceduresAndAddresses, redCallSetDynamicScissor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetStructsMemory, RedCallProceduresAndAddresses, redCallSetStructsMemory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetProcedureParameters, RedCallProceduresAndAddresses, redCallSetProcedureParameters)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetProcedureOutput, RedCallProceduresAndAddresses, redCallSetProcedureOutput)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallEndProcedureOutput, RedCallProceduresAndAddresses, redCallEndProcedureOutput)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallUsageAliasOrderBarrier, RedCallProceduresAndAddresses, redCallUsageAliasOrderBarrier)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallMark, RedCallProceduresAndAddresses, redCallMark)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallMarkSet, RedCallProceduresAndAddresses, redCallMarkSet)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallMarkEnd, RedCallProceduresAndAddresses, redCallMarkEnd)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedOutputMembers *, RedInlineOutput, outputMembers)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedOutputMembersResolveTargets *, RedInlineOutput, outputMembersResolveTargets)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, r)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, g)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, b)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, a)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, r)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, g)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, b)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, a)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, r)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, g)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, b)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, a)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedUsageArray, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageArray, oldAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageArray, newAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageArray, oldAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageArray, newAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageArray, queueFamilyIndexSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageArray, queueFamilyIndexTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedUsageArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedUsageArray, arrayBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedUsageArray, arrayBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedUsageImage, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageImage, oldAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageImage, newAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageImage, oldAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageImage, newAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedState, RedUsageImage, oldState)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedState, RedUsageImage, newState)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, queueFamilyIndexSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, queueFamilyIndexTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleImage, RedUsageImage, image)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedImagePartBitflags, RedUsageImage, imageAllParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLevelsFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLevelsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLayersFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLayersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedAlias, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedAlias, oldResourceHandle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedAlias, newResourceHandle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedOrder, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedOrder, resourceHandle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, setTo4)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedGpuTimeline, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, waitForAndUnsignalGpuSignalsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleGpuSignal *, RedGpuTimeline, waitForAndUnsignalGpuSignals)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedGpuTimeline, setTo65536)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, callsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleCalls *, RedGpuTimeline, calls)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, signalGpuSignalsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleGpuSignal *, RedGpuTimeline, signalGpuSignals)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo1, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, supportsComputingLanguageFeatureLevel1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageStateExtensionIterator, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageSpecializationConstant, specId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageSpecializationConstant, specDataBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureComputingLanguageSpecializationConstant, specDataBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureComputingLanguageStateExtension, RedProcedureComputingLanguageStateExtensionSpecializationConstants, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedProcedureComputingLanguageSpecializationConstant *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specDataBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specData)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo2, RedGpuInfoOptionalInfoArrayTimestamp, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoArrayTimestamp, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoArrayTimestamp, supportsArrayTimestamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedGpuInfoOptionalInfoArrayTimestamp, queuesPrecisionBits64BitTicksCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfoOptionalInfoArrayTimestamp, nanosecondsPerTick)

#undef GS_MACRO_RED_STRUCT_MEMBER

  return ape_object_make_number((double)((uint64_t)-1));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedStructMemberTypeof GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*structName*/,
    APE_OBJECT_STRING/*structMemberName*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redStructMemberTypeof")
  getArgAs_CChars(const char *, structName, args[_i++]);
  getArgAs_CChars(const char *, memberName, args[_i++]);
  getArgAs_END

  const size_t structNameBytesCount = strlen(structName) + 1;
  const size_t memberNameBytesCount = strlen(memberName) + 1;

#define GS_MACRO_RED_STRUCT_MEMBER(GS_TYPE, TYPE, STRUCTURE, MEMBER) \
  if (structNameBytesCount == sizeof(#STRUCTURE)) { \
    if (memberNameBytesCount == sizeof(#MEMBER)) { \
      if (memcmp(structName, #STRUCTURE, structNameBytesCount) == 0) { \
        if (memcmp(memberName, #MEMBER, memberNameBytesCount) == 0) { \
          return ape_object_make_number((double)GS_TYPE); \
        } \
      } \
    } \
  }

  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedArray, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedArray, memoryBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedArray, memoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedArray, memoryTypesSupported)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleImage, RedImage, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedImage, memoryBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedImage, memoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImage, memoryTypesSupported)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleOutput, RedOutput, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutput, width)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutput, height)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutput, depthStencilEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutput, colorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleCalls, RedCalls, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleCallsMemory, RedCalls, memory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedCalls, reusable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryType, memoryHeapIndex)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isGpuVram)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isCpuMappable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isCpuCoherent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryType, isCpuCached)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryHeap, memoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedMemoryHeap, isGpuVram)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedQueueCopyLimits, copyBlockTexelsCountWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedQueueCopyLimits, copyBlockTexelsCountHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedQueueCopyLimits, copyBlockTexelsCountDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimitsDimensions, maxWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimitsDimensions, maxHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimitsDimensions, maxDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedImageFormatLimitsDimensions, RedImageFormatLimits, maxDimensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimits, maxLevelsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedImageFormatLimits, maxLayersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedImageFormatLimits, supportedMultisampleCounts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedImageFormatLimits, maxBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, RedStatus, RedImageFormatLimits, status)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsCopyR)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsCopyW)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureRO)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureRW)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsOutputDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsOutputColor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureROFilteringLinear)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsTextureRWAtomics)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedImageFormatFeatures, supportsOutputColorBlend)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleGpu, RedGpuInfo, gpu)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleGpuDevice, RedGpuInfo, gpuDevice)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedGpuInfo, gpuName)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuType, RedGpuInfo, gpuType)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, gpuVendorId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, gpuDeviceId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, gpuDriverVersion)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfo, gpuProcedureCacheUuid)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, memoryTypesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedMemoryType *, RedGpuInfo, memoryTypes)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const char **, RedGpuInfo, memoryTypesDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, memoryHeapsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedMemoryHeap *, RedGpuInfo, memoryHeaps)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const char **, RedGpuInfo, memoryHeapsDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, queuesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleQueue *, RedGpuInfo, queues)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const char **, RedGpuInfo, queuesDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedGpuInfo, queuesFamilyIndex)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedBool32 *, RedGpuInfo, queuesCanCopy)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedBool32 *, RedGpuInfo, queuesCanDraw)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedBool32 *, RedGpuInfo, queuesCanCompute)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedQueueCopyLimits *, RedGpuInfo, queuesCopyLimits)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxMemoryAllocateCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minMemoryAllocateBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, maxMemoryAllocateBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minMemoryNonCoherentBlockBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxCreateSamplerCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minMemoryPageSeparationArrayImageBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minArrayROCStructMemberRangeBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, maxArrayROCStructMemberRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, minArrayRORWStructMemberRangeBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, maxArrayRORWStructMemberRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxArrayIndexUint32Value)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensions1D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensions2D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensions3D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageDimensionsCube)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageLayersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxSamplerMipLodBias)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxSamplerAnisotropy)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsSamplerFilteringMagMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsSamplerFilteringMip)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxOutputWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxOutputHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxOutputColorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForOutputDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForOutputStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForOutputColor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflags, RedGpuInfo, supportedMultisampleCountsForEmptyOutput)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructSlotsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageArrayROCsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageArrayRORWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageSamplersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageTextureROsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageTextureRWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructPerStageAllResourcesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructArrayROCsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructArrayRORWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructSamplersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructTextureROsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxStructTextureRWsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxProcedureParametersVariablesBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxViewportDimensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, minViewportBoundsRange)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxViewportBoundsRange)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsViewportCoordinates)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsViewportBounds)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxPerStageClipDistances)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxPerStageCullDistances)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxPerStageClipAndCullDistances)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxVertexOutputLocationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentInputLocationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentOutputColorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentOutputColorsCountBlendDualSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxFragmentOutputResourcesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeSharedMemoryBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeWorkgroupsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeWorkgroupInvocationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxComputeWorkgroupDimensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedGpuInfo, minImageSampleImageFetchOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageSampleImageFetchOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedGpuInfo, minImageGatherOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, maxImageGatherOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, minInterpolateAtOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfo, maxInterpolateAtOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfo, precisionBitsInterpolateAtOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, optimalCopyArrayImageRangeArrayBytesFirstBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedGpuInfo, optimalCopyArrayImageRangeArrayTexelsCountToNextRowBytesAlignment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsWsi)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsMemoryGetBudget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsFullArrayIndexUint32Value)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsSamplerAnisotropy)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsTextureDimensionsCubeLayered)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateRasterizationDepthClamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateRasterizationDepthBiasDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateRasterizationDepthBiasClamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateMultisampleSampleShading)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateMultisampleAlphaToOne)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateDepthTestBoundsTest)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateDepthTestBoundsTestDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateStencilTestFrontAndBackDynamicCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateStencilTestFrontAndBackDynamicWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateBlendLogicOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateOutputColorsBlendVaryingPerColor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsProcedureStateOutputColorsBlendDualSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsMultisampleEmptyOutputVariableMultisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsMultisampleStandardSampleLocations)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeWritesAndAtomicsInStageVertex)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeWritesAndAtomicsInStageFragment)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeImageGatherExtended)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWExtendedFormats)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWMultisample)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWReadWithoutFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeTextureRWWriteWithoutFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfArrayROCs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfArrayRORWs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfSamplers)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfTextureROs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeDynamicallyIndexableArraysOfTextureRWs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeClipDistance)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeCullDistance)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeInt64)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeFloat64)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfo, supportsGpuCodeMinLod)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions1D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions2D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions2DMultisample)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions2DWithTextureDimensionsCubeAndCubeLayered)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions3D)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatLimits *, RedGpuInfo, imageFormatsLimitsImageDimensions3DWithTextureDimensions2DAnd2DLayered)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedImageFormatFeatures *, RedGpuInfo, imageFormatsFeatures)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfo, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, RedStatus, RedStatuses, status)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStatuses, statusCode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusHresult)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureId, RedStatuses, statusProcedureId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedStatuses, statusFile)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusLine)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, RedStatus, RedStatuses, statusError)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStatuses, statusErrorCode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusErrorHresult)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureId, RedStatuses, statusErrorProcedureId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedStatuses, statusErrorFile)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedStatuses, statusErrorLine)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedStatuses, statusErrorDescription)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedTypeContext, gpusCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedGpuInfo *, RedTypeContext, gpus)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedStatuses *, RedTypeContext, gpusStatuses)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleContext, RedTypeContext, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, void *, RedTypeContext, userData)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfoOptionalInfoIterator, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoAdditionalInfo0, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoAdditionalInfo0, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsArraysImagesUsageBeforeMemorySet)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfArrays)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfImages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfImagesMultisample)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoAdditionalInfo0, supportsInitialQueueFamilyIndexSetToMaxValueForSimultaneousQueueAccessOfImagesDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoDriverProperties, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoDriverProperties, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedDriverId, RedGpuInfoOptionalInfoDriverProperties, id)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedGpuInfoOptionalInfoDriverProperties, name)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedGpuInfoOptionalInfoDriverProperties, info)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionMajor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionMinor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionSubminor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_UCHAR, unsigned char, RedGpuInfoOptionalInfoDriverProperties, compliantWithConformanceTestSuiteVersionPatch)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoResolveDepthStencil, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoResolveDepthStencil, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthSampleIndexZero)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthAverage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeDepthMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilSampleIndexZero)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilAverage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveModeStencilMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveIndependentNone)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoResolveDepthStencil, supportsResolveIndependent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoProcedureParametersHandles, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoProcedureParametersHandles, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoProcedureParametersHandles, supportsProcedureParametersHandles)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuInfoOptionalInfoProcedureParametersHandles, maxProcedureParametersHandlesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoRasterizationMode, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoRasterizationMode, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsRasterizationModeOverestimate)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsRasterizationModeUnderestimate)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsGuaranteedZeroAreaBackFacingTriangles)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRasterizationMode, supportsGpuCodeFullyCoveredEXT)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoFormalMemoryModel, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoFormalMemoryModel, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoFormalMemoryModel, supportsFormalMemoryModel)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoFormalMemoryModel, supportsFormalMemoryModelGpuScopeSynchronization)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoFormalMemoryModel, supportsFormalMemoryModelAvailabilityAndVisibilityChains)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo, RedGpuInfoOptionalInfoRayTracing, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoRayTracing, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoRayTracing, supportsRayTracing)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryBudget, setTo1000237000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMemoryBudget, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryBudget, memoryHeapsBudget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryBudget, memoryHeapsUsage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryArray, setTo1000157000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMemoryArray, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedMemoryArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleMemory, RedMemoryArray, memory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryArray, memoryBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMemoryImage, setTo1000157001)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMemoryImage, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleImage, RedMemoryImage, image)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleMemory, RedMemoryImage, memory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMemoryImage, memoryBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedMappableMemoryRange, setTo6)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedMappableMemoryRange, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleMemory, RedMappableMemoryRange, mappableMemory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMappableMemoryRange, mappableMemoryRangeBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedMappableMemoryRange, mappableMemoryRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleSampler, RedStructMemberTexture, sampler)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedStructMemberTexture, texture)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMemberTexture, setTo1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedStructMemberArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedStructMemberArray, arrayRangeBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedStructMemberArray, arrayRangeBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, setTo35)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedStructMember, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleStruct, RedStructMember, structure)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, first)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructMember, count)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStructMemberType, RedStructMember, type)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedStructMemberTexture *, RedStructMember, textures)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedStructMemberArray *, RedStructMember, arrays)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedStructMember, setTo00)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedContextOptionalSettingsIterator, settings)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedContextOptionalSettingsIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedContextOptionalSettings, RedContextOptionalSettings0, settings)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedContextOptionalSettings0, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedContextOptionalSettings0, skipCheckingContextLayers)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedContextOptionalSettings0, skipCheckingContextExtensions)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedContextOptionalSettings0, gpusExposeOnlyOneQueue)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedHandleInfo, _0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedHandleInfo, _1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedHandleType, RedHandleInfo, handleType)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedHandleInfo, handle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedHandleInfo, handleName)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, _0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedDebugCallbackData, _1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, statusCode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedDebugCallbackData, messageIdName)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedDebugCallbackData, statusHresult)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR_POINTER, const char *, RedDebugCallbackData, message)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, _2)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedDebugCallbackData, _3)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, _4)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedDebugCallbackData, _5)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedDebugCallbackData, handleInfosCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleInfo *, RedDebugCallbackData, handleInfos)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_CHAR, char, RedMemoryAllocationTag, tag)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembers, depthStencilEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedFormat, RedOutputDeclarationMembers, depthStencilFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflag, RedOutputDeclarationMembers, depthStencilMultisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedSetProcedureOutputOp, RedOutputDeclarationMembers, depthStencilDepthSetProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedEndProcedureOutputOp, RedOutputDeclarationMembers, depthStencilDepthEndProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedSetProcedureOutputOp, RedOutputDeclarationMembers, depthStencilStencilSetProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedEndProcedureOutputOp, RedOutputDeclarationMembers, depthStencilStencilEndProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembers, depthStencilSharesMemoryWithAnotherMember)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutputDeclarationMembers, colorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedFormat, RedOutputDeclarationMembers, colorsFormat)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflag, RedOutputDeclarationMembers, colorsMultisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedSetProcedureOutputOp, RedOutputDeclarationMembers, colorsSetProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedEndProcedureOutputOp, RedOutputDeclarationMembers, colorsEndProcedureOutputOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembers, colorsSharesMemoryWithAnotherMember)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedResolveMode, RedOutputDeclarationMembersResolveSources, resolveModeDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedResolveMode, RedOutputDeclarationMembersResolveSources, resolveModeStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembersResolveSources, resolveDepthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedOutputDeclarationMembersResolveSources, resolveColors)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructDeclarationMember, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStructMemberType, RedStructDeclarationMember, type)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructDeclarationMember, count)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedVisibleToStageBitflags, RedStructDeclarationMember, visibleToStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleSampler *, RedStructDeclarationMember, inlineSampler)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedStructDeclarationMemberArrayRO, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersDeclaration, variablesSlot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedVisibleToStageBitflags, RedProcedureParametersDeclaration, variablesVisibleToStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersDeclaration, variablesBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersDeclaration, structsDeclarationsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleStructDeclaration, RedProcedureParametersDeclaration, structsDeclarations)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleStructDeclaration, RedProcedureParametersDeclaration, handlesDeclaration)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedPrimitiveTopology, RedProcedureState, inputAssemblyTopology)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, inputAssemblyPrimitiveRestartEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, viewportDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticX)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticY)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticDepthMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, viewportStaticDepthMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, scissorDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedProcedureState, scissorStaticX)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedProcedureState, scissorStaticY)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, scissorStaticWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, scissorStaticHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDepthClampEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDiscardAllPrimitivesEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCullMode, RedProcedureState, rasterizationCullMode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedFrontFace, RedProcedureState, rasterizationFrontFace)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDepthBiasEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, rasterizationDepthBiasDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, rasterizationDepthBiasStaticConstantFactor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, rasterizationDepthBiasStaticClamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, rasterizationDepthBiasStaticSlopeFactor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedMultisampleCountBitflag, RedProcedureState, multisampleCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedProcedureState, multisampleSampleMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, multisampleSampleShadingEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, multisampleSampleShadingMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, multisampleAlphaToCoverageEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, multisampleAlphaToOneEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestDepthWriteEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCompareOp, RedProcedureState, depthTestDepthCompareOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestBoundsTestEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, depthTestBoundsTestDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, depthTestBoundsTestStaticMin)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, depthTestBoundsTestStaticMax)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestFrontStencilTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestFrontStencilTestPassDepthTestPassOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestFrontStencilTestPassDepthTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCompareOp, RedProcedureState, stencilTestFrontCompareOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestBackStencilTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestBackStencilTestPassDepthTestPassOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedStencilOp, RedProcedureState, stencilTestBackStencilTestPassDepthTestFailOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedCompareOp, RedProcedureState, stencilTestBackCompareOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestFrontAndBackDynamicCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestFrontAndBackDynamicWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, stencilTestFrontAndBackDynamicReference)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, stencilTestFrontAndBackStaticCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, stencilTestFrontAndBackStaticWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, stencilTestFrontAndBackStaticReference)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, blendLogicOpEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedLogicOp, RedProcedureState, blendLogicOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, blendConstantsDynamic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedProcedureState, blendConstantsStatic)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureState, outputColorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedColorComponentBitflags, RedProcedureState, outputColorsWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedProcedureState, outputColorsBlendEnable)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendColorFactorSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendColorFactorTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendOp, RedProcedureState, outputColorsBlendColorOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendAlphaFactorSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendFactor, RedProcedureState, outputColorsBlendAlphaFactorTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBlendOp, RedProcedureState, outputColorsBlendAlphaOp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureStateExtensionIterator, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureStateExtensionIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureStateExtension, RedProcedureStateExtensionRasterizationMode, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureStateExtensionRasterizationMode, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedRasterizationMode, RedProcedureStateExtensionRasterizationMode, rasterizationMode)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembers, depthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedOutputMembers, colorsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembers, colors)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembersResolveTargets, depthStencil)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleTexture, RedOutputMembersResolveTargets, colors)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayRange, arrayRBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayRange, arrayWBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayRange, bytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedImagePartBitflags, RedCopyImageParts, allParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageParts, level)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageParts, layersFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageParts, layersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedCopyImageOffset, texelX)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedCopyImageOffset, texelY)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedCopyImageOffset, texelZ)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageExtent, texelsCountWidth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageExtent, texelsCountHeight)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyImageExtent, texelsCountDepth)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageParts, RedCopyImageRange, imageRParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageOffset, RedCopyImageRange, imageROffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageParts, RedCopyImageRange, imageWParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageOffset, RedCopyImageRange, imageWOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageExtent, RedCopyImageRange, extent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedCopyArrayImageRange, arrayBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyArrayImageRange, arrayTexelsCountToNextRow)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedCopyArrayImageRange, arrayTexelsCountToNextLayerOr3DDepthSliceDividedByTexelsCountToNextRow)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageParts, RedCopyArrayImageRange, imageParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageOffset, RedCopyArrayImageRange, imageOffset)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_STRUCT, RedCopyImageExtent, RedCopyArrayImageRange, imageExtent)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedProcedureParametersHandleArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedProcedureParametersHandleArray, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedProcedureParametersHandleArray, setToMaxValue)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, setTo35)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureParametersHandle, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedProcedureParametersHandle, setTo00)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, slot)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, setTo000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureParametersHandle, setTo1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureParametersHandleType, RedProcedureParametersHandle, type)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureParametersHandle, setTo0000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedProcedureParametersHandleArray *, RedProcedureParametersHandle, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureParametersHandle, setTo00000)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallGpuToCpuSignalSignal, RedCallProceduresAndAddresses, redCallGpuToCpuSignalSignal)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyArrayToArray, RedCallProceduresAndAddresses, redCallCopyArrayToArray)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyImageToImage, RedCallProceduresAndAddresses, redCallCopyImageToImage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyArrayToImage, RedCallProceduresAndAddresses, redCallCopyArrayToImage)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallCopyImageToArray, RedCallProceduresAndAddresses, redCallCopyImageToArray)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallProcedure, RedCallProceduresAndAddresses, redCallProcedure)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallProcedureIndexed, RedCallProceduresAndAddresses, redCallProcedureIndexed)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallProcedureCompute, RedCallProceduresAndAddresses, redCallProcedureCompute)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedure, RedCallProceduresAndAddresses, redCallSetProcedure)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureIndices, RedCallProceduresAndAddresses, redCallSetProcedureIndices)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureParametersVariables, RedCallProceduresAndAddresses, redCallSetProcedureParametersVariables)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureParametersStructs, RedCallProceduresAndAddresses, redCallSetProcedureParametersStructs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetProcedureParametersHandles, RedCallProceduresAndAddresses, redCallSetProcedureParametersHandles)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicDepthBias, RedCallProceduresAndAddresses, redCallSetDynamicDepthBias)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicDepthBounds, RedCallProceduresAndAddresses, redCallSetDynamicDepthBounds)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicStencilCompareMask, RedCallProceduresAndAddresses, redCallSetDynamicStencilCompareMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicStencilWriteMask, RedCallProceduresAndAddresses, redCallSetDynamicStencilWriteMask)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicStencilReference, RedCallProceduresAndAddresses, redCallSetDynamicStencilReference)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureCallSetDynamicBlendConstants, RedCallProceduresAndAddresses, redCallSetDynamicBlendConstants)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetDynamicViewport, RedCallProceduresAndAddresses, redCallSetDynamicViewport)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetDynamicScissor, RedCallProceduresAndAddresses, redCallSetDynamicScissor)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetStructsMemory, RedCallProceduresAndAddresses, redCallSetStructsMemory)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetProcedureParameters, RedCallProceduresAndAddresses, redCallSetProcedureParameters)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallSetProcedureOutput, RedCallProceduresAndAddresses, redCallSetProcedureOutput)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallEndProcedureOutput, RedCallProceduresAndAddresses, redCallEndProcedureOutput)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallUsageAliasOrderBarrier, RedCallProceduresAndAddresses, redCallUsageAliasOrderBarrier)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallMark, RedCallProceduresAndAddresses, redCallMark)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallMarkSet, RedCallProceduresAndAddresses, redCallMarkSet)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedTypeProcedureAddressCallMarkEnd, RedCallProceduresAndAddresses, redCallMarkEnd)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedOutputMembers *, RedInlineOutput, outputMembers)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedOutputMembersResolveTargets *, RedInlineOutput, outputMembersResolveTargets)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, r)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, g)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, b)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedColorsClearValuesFloat, a)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, r)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, g)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, b)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, RedColorsClearValuesSint, a)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, r)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, g)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, b)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedColorsClearValuesUint, a)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedUsageArray, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageArray, oldAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageArray, newAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageArray, oldAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageArray, newAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageArray, queueFamilyIndexSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageArray, queueFamilyIndexTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleArray, RedUsageArray, array)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedUsageArray, arrayBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedUsageArray, arrayBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedUsageImage, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageImage, oldAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessStageBitflags, RedUsageImage, newAccessStages)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageImage, oldAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedAccessBitflags, RedUsageImage, newAccess)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedState, RedUsageImage, oldState)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedState, RedUsageImage, newState)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, queueFamilyIndexSource)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, queueFamilyIndexTarget)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RedHandleImage, RedUsageImage, image)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedImagePartBitflags, RedUsageImage, imageAllParts)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLevelsFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLevelsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLayersFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedUsageImage, imageLayersCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedAlias, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedAlias, oldResourceHandle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedAlias, newResourceHandle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBarrierSplit, RedOrder, barrierSplit)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U64, uint64_t, RedOrder, resourceHandle)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, setTo4)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedGpuTimeline, setTo0)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, waitForAndUnsignalGpuSignalsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleGpuSignal *, RedGpuTimeline, waitForAndUnsignalGpuSignals)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedGpuTimeline, setTo65536)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, callsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleCalls *, RedGpuTimeline, calls)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedGpuTimeline, signalGpuSignalsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedHandleGpuSignal *, RedGpuTimeline, signalGpuSignals)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo1, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, supportsComputingLanguageFeatureLevel1)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageStateExtensionIterator, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionIterator, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageSpecializationConstant, specId)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageSpecializationConstant, specDataBytesFirst)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureComputingLanguageSpecializationConstant, specDataBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureComputingLanguageStateExtension, RedProcedureComputingLanguageStateExtensionSpecializationConstants, extension)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specsCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedProcedureComputingLanguageSpecializationConstant *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specs)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specDataBytesCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specData)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo2, RedGpuInfoOptionalInfoArrayTimestamp, optionalInfo)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoArrayTimestamp, next)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoArrayTimestamp, supportsArrayTimestamp)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, RedGpuInfoOptionalInfoArrayTimestamp, queuesPrecisionBits64BitTicksCount)
  GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RedGpuInfoOptionalInfoArrayTimestamp, nanosecondsPerTick)

#undef GS_MACRO_RED_STRUCT_MEMBER

  return ape_object_make_number(0.0);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateContext GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_BOOL/*enableDebugMode*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateContext")
  getArgAs_Bool(RedBool32, enableDebugMode, args[_i++]);
  getArgAs_END

  unsigned extensions[] = {
    RED_SDK_EXTENSION_PROCEDURE_PARAMETERS_HANDLES,
    RED_SDK_EXTENSION_ARRAY_TIMESTAMP,
  };
  RedContextOptionalSettingsContextFromVkGetInstanceProcAddr settingsGetInstanceProcAddr = {};
  settingsGetInstanceProcAddr.settings            = RED_CONTEXT_OPTIONAL_SETTINGS_CONTEXT_FROM_VK_GET_INSTANCE_PROC_ADDR;
  settingsGetInstanceProcAddr.next                = 0;
  settingsGetInstanceProcAddr.getInstanceProcAddr = (void *)_gsVkGetInstanceProcAddr;
  RedContext context = 0;
  redCreateContext(malloc, free, 0, 0, enableDebugMode == 1 ? redHelperDebugCallback : 0, RED_SDK_VERSION_1_0_135, sizeof(extensions) / sizeof(extensions[0]), extensions, 0, 0, 0, 0, &settingsGetInstanceProcAddr, &context, 0, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)context));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateContextWithRayTracingFeatureLevel1 GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_BOOL/*enableDebugMode*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateContextWithRayTracingFeatureLevel1")
  getArgAs_Bool(RedBool32, enableDebugMode, args[_i++]);
  getArgAs_END

  unsigned extensions[] = {
    RED_SDK_EXTENSION_ADDITIONAL_INFO_0,
    RED_SDK_EXTENSION_DRIVER_PROPERTIES,
    RED_SDK_EXTENSION_RESOLVE_DEPTH_STENCIL,
    RED_SDK_EXTENSION_DEDICATE_MEMORY,
    RED_SDK_EXTENSION_PROCEDURE_PARAMETERS_HANDLES,
    RED_SDK_EXTENSION_BATCH_MEMORY_SET,
    RED_SDK_EXTENSION_RASTERIZATION_MODE,
    RED_SDK_EXTENSION_FORMAL_MEMORY_MODEL,
    RED_SDK_EXTENSION_RAY_TRACING,
    RED_SDK_EXTENSION_COMPUTING_LANGUAGE_FEATURE_LEVEL_1,
    RED_SDK_EXTENSION_ARRAY_TIMESTAMP,
  };
  RedContextOptionalSettingsContextFromVkGetInstanceProcAddr settingsGetInstanceProcAddr = {};
  settingsGetInstanceProcAddr.settings            = RED_CONTEXT_OPTIONAL_SETTINGS_CONTEXT_FROM_VK_GET_INSTANCE_PROC_ADDR;
  settingsGetInstanceProcAddr.next                = 0;
  settingsGetInstanceProcAddr.getInstanceProcAddr = (void *)_gsVkGetInstanceProcAddr;
  RedContext context = 0;
  redCreateContext(malloc, free, 0, 0, enableDebugMode == 1 ? redHelperDebugCallback : 0, RED_SDK_VERSION_1_0_135, sizeof(extensions) / sizeof(extensions[0]), extensions, 0, 0, 0, 0, &settingsGetInstanceProcAddr, &context, 0, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)context));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateContextWithRayTracingFeatureLevel2 GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_BOOL/*enableDebugMode*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateContextWithRayTracingFeatureLevel2")
  getArgAs_Bool(RedBool32, enableDebugMode, args[_i++]);
  getArgAs_END

  unsigned extensions[] = {
    RED_SDK_EXTENSION_ADDITIONAL_INFO_0,
    RED_SDK_EXTENSION_DRIVER_PROPERTIES,
    RED_SDK_EXTENSION_RESOLVE_DEPTH_STENCIL,
    RED_SDK_EXTENSION_DEDICATE_MEMORY,
    RED_SDK_EXTENSION_PROCEDURE_PARAMETERS_HANDLES,
    RED_SDK_EXTENSION_BATCH_MEMORY_SET,
    RED_SDK_EXTENSION_RASTERIZATION_MODE,
    RED_SDK_EXTENSION_FORMAL_MEMORY_MODEL,
    RED_SDK_EXTENSION_RAY_TRACING,
    RED_SDK_EXTENSION_COMPUTING_LANGUAGE_FEATURE_LEVEL_1,
    RED_SDK_EXTENSION_ARRAY_TIMESTAMP,
    16, // RED_SDK_EXTENSION_RAY_TRACING_X
  };
  RedContextOptionalSettingsContextFromVkGetInstanceProcAddr settingsGetInstanceProcAddr = {};
  settingsGetInstanceProcAddr.settings            = RED_CONTEXT_OPTIONAL_SETTINGS_CONTEXT_FROM_VK_GET_INSTANCE_PROC_ADDR;
  settingsGetInstanceProcAddr.next                = 0;
  settingsGetInstanceProcAddr.getInstanceProcAddr = (void *)_gsVkGetInstanceProcAddr;
  RedContext context = 0;
  redCreateContext(malloc, free, 0, 0, enableDebugMode == 1 ? redHelperDebugCallback : 0, RED_SDK_VERSION_1_0_135, sizeof(extensions) / sizeof(extensions[0]), extensions, 0, 0, 0, 0, &settingsGetInstanceProcAddr, &context, 0, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)context));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedHandleContextGetProcAddr GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*contextHandle*/,
    APE_OBJECT_STRING/*procedureName*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redHandleContextGetProcAddr")
  getArgAs_Pointer(RedHandleContext, contextHandle, args[_i++]);
  getArgAs_CChars(const char *,      procedureName, args[_i++]);
  getArgAs_END

  void * address = _gsVkGetInstanceProcAddr((void *)contextHandle, procedureName);

  return ape_object_make_number(_gsPointerToNumber(address));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedMemoryGetBudget GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*outMemoryBudget*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redMemoryGetBudget")
  getArgAs_Pointer(RedContext,        context,         args[_i++]);
  getArgAs_Pointer(RedHandleGpu,      gpu,             args[_i++]);
  getArgAs_Pointer(RedMemoryBudget *, outMemoryBudget, args[_i++]);
  getArgAs_Pointer(RedStatuses *,     outStatuses,     args[_i++]);
  getArgAs_END

  redMemoryGetBudget(context, gpu, outMemoryBudget, outStatuses, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedMemoryAllocate GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*bytesCount*/,
    APE_OBJECT_NUMBER/*memoryTypeIndex*/,
    APE_OBJECT_NUMBER/*dedicateToArray*/,
    APE_OBJECT_NUMBER/*dedicateToImage*/,
    APE_OBJECT_NUMBER/*memoryBitflags*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redMemoryAllocate")
  getArgAs_Pointer(RedContext,     context,         args[_i++]);
  getArgAs_Pointer(RedHandleGpu,   gpu,             args[_i++]);
  getArgAs_CChars(const char *,    handleName,      args[_i++]);
  getArgAs_Double(uint64_t,        bytesCount,      args[_i++]);
  getArgAs_Double(unsigned,        memoryTypeIndex, args[_i++]);
  getArgAs_Pointer(RedHandleArray, dedicateToArray, args[_i++]);
  getArgAs_Pointer(RedHandleImage, dedicateToImage, args[_i++]);
  getArgAs_Double(unsigned,        memoryBitflags,  args[_i++]);
  getArgAs_Pointer(RedStatuses *,  outStatuses,     args[_i++]);
  getArgAs_END

  RedHandleMemory handle = 0;
  redMemoryAllocate(context, gpu, handleName, bytesCount, memoryTypeIndex, dedicateToArray, dedicateToImage, memoryBitflags, &handle, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedMemoryAllocateMappable GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_BOOL/*dedicate*/,
    APE_OBJECT_NUMBER/*array*/,
    APE_OBJECT_NUMBER/*arrayMemoryBytesCount*/,
    APE_OBJECT_NUMBER/*memoryTypeIndex*/,
    APE_OBJECT_NUMBER/*memoryBitflags*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redMemoryAllocateMappable")
  getArgAs_Pointer(RedContext,     context,               args[_i++]);
  getArgAs_Pointer(RedHandleGpu,   gpu,                   args[_i++]);
  getArgAs_CChars(const char *,    handleName,            args[_i++]);
  getArgAs_Bool(RedBool32,         dedicate,              args[_i++]);
  getArgAs_Pointer(RedHandleArray, array,                 args[_i++]);
  getArgAs_Double(uint64_t,        arrayMemoryBytesCount, args[_i++]);
  getArgAs_Double(unsigned,        memoryTypeIndex,       args[_i++]);
  getArgAs_Double(unsigned,        memoryBitflags,        args[_i++]);
  getArgAs_Pointer(RedStatuses *,  outStatuses,           args[_i++]);
  getArgAs_END

  RedHandleMemory handle = 0;
  redMemoryAllocateMappable(context, gpu, handleName, dedicate, array, arrayMemoryBytesCount, memoryTypeIndex, memoryBitflags, &handle, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedMemoryFree GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*memory*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redMemoryFree")
  getArgAs_Pointer(RedContext,      context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,    gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleMemory, memory,  args[_i++]);
  getArgAs_END

  redMemoryFree(context, gpu, memory, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedMemorySet GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*memoryArraysCount*/,
    APE_OBJECT_NUMBER/*memoryArrays*/,
    APE_OBJECT_NUMBER/*memoryImagesCount*/,
    APE_OBJECT_NUMBER/*memoryImages*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redMemorySet")
  getArgAs_Pointer(RedContext,             context,           args[_i++]);
  getArgAs_Pointer(RedHandleGpu,           gpu,               args[_i++]);
  getArgAs_Double(unsigned,                memoryArraysCount, args[_i++]);
  getArgAs_Pointer(const RedMemoryArray *, memoryArrays,      args[_i++]);
  getArgAs_Double(unsigned,                memoryImagesCount, args[_i++]);
  getArgAs_Pointer(const RedMemoryImage *, memoryImages,      args[_i++]);
  getArgAs_Pointer(RedStatuses *,          outStatuses,       args[_i++]);
  getArgAs_END

  redMemorySet(context, gpu, memoryArraysCount, memoryArrays, memoryImagesCount, memoryImages, outStatuses, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedMemoryMap GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*mappableMemory*/,
    APE_OBJECT_NUMBER/*mappableMemoryBytesFirst*/,
    APE_OBJECT_NUMBER/*mappableMemoryBytesCount*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redMemoryMap")
  getArgAs_Pointer(RedContext,      context,                  args[_i++]);
  getArgAs_Pointer(RedHandleGpu,    gpu,                      args[_i++]);
  getArgAs_Pointer(RedHandleMemory, mappableMemory,           args[_i++]);;
  getArgAs_Double(uint64_t,         mappableMemoryBytesFirst, args[_i++]);;
  getArgAs_Double(uint64_t,         mappableMemoryBytesCount, args[_i++]);;
  getArgAs_Pointer(RedStatuses *,   outStatuses,              args[_i++]);;
  getArgAs_END

  void * pointer = 0;
  redMemoryMap(context, gpu, mappableMemory, mappableMemoryBytesFirst, mappableMemoryBytesCount, &pointer, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber(pointer));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedMemoryUnmap GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*mappableMemory*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redMemoryUnmap")
  getArgAs_Pointer(RedContext,      context,        args[_i++]);
  getArgAs_Pointer(RedHandleGpu,    gpu,            args[_i++]);
  getArgAs_Pointer(RedHandleMemory, mappableMemory, args[_i++]);
  getArgAs_END

  redMemoryUnmap(context, gpu, mappableMemory, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedMemoryNonCoherentFlush GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*mappableMemoryRangesCount*/,
    APE_OBJECT_NUMBER/*mappableMemoryRanges*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redMemoryNonCoherentFlush")
  getArgAs_Pointer(RedContext,                     context,                   args[_i++]);
  getArgAs_Pointer(RedHandleGpu,                   gpu,                       args[_i++]);
  getArgAs_Double(unsigned,                        mappableMemoryRangesCount, args[_i++]);
  getArgAs_Pointer(const RedMappableMemoryRange *, mappableMemoryRanges,      args[_i++]);
  getArgAs_Pointer(RedStatuses *,                  outStatuses,               args[_i++]);
  getArgAs_END

  redMemoryNonCoherentFlush(context, gpu, mappableMemoryRangesCount, mappableMemoryRanges, outStatuses, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedMemoryNonCoherentInvalidate GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*mappableMemoryRangesCount*/,
    APE_OBJECT_NUMBER/*mappableMemoryRanges*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redMemoryNonCoherentInvalidate")
  getArgAs_Pointer(RedContext,                     context,                   args[_i++]);
  getArgAs_Pointer(RedHandleGpu,                   gpu,                       args[_i++]);
  getArgAs_Double(unsigned,                        mappableMemoryRangesCount, args[_i++]);
  getArgAs_Pointer(const RedMappableMemoryRange *, mappableMemoryRanges,      args[_i++]);
  getArgAs_Pointer(RedStatuses *,                  outStatuses,               args[_i++]);
  getArgAs_END

  redMemoryNonCoherentInvalidate(context, gpu, mappableMemoryRangesCount, mappableMemoryRanges, outStatuses, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedStructsMemoryAllocate GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*maxStructsCount*/,
    APE_OBJECT_NUMBER/*maxStructsMembersOfTypeArrayROConstantCount*/,
    APE_OBJECT_NUMBER/*maxStructsMembersOfTypeArrayROOrArrayRWCount*/,
    APE_OBJECT_NUMBER/*maxStructsMembersOfTypeTextureROCount*/,
    APE_OBJECT_NUMBER/*maxStructsMembersOfTypeTextureRWCount*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redStructsMemoryAllocate")
  getArgAs_Pointer(RedContext,    context,                                      args[_i++]);
  getArgAs_Pointer(RedHandleGpu,  gpu,                                          args[_i++]);
  getArgAs_CChars(const char *,   handleName,                                   args[_i++]);
  getArgAs_Double(unsigned,       maxStructsCount,                              args[_i++]);
  getArgAs_Double(unsigned,       maxStructsMembersOfTypeArrayROConstantCount,  args[_i++]);
  getArgAs_Double(unsigned,       maxStructsMembersOfTypeArrayROOrArrayRWCount, args[_i++]);
  getArgAs_Double(unsigned,       maxStructsMembersOfTypeTextureROCount,        args[_i++]);
  getArgAs_Double(unsigned,       maxStructsMembersOfTypeTextureRWCount,        args[_i++]);
  getArgAs_Pointer(RedStatuses *, outStatuses,                                  args[_i++]);
  getArgAs_END

  RedHandleStructsMemory handle = 0;
  redStructsMemoryAllocate(context, gpu, handleName, maxStructsCount, maxStructsMembersOfTypeArrayROConstantCount, maxStructsMembersOfTypeArrayROOrArrayRWCount, maxStructsMembersOfTypeTextureROCount, maxStructsMembersOfTypeTextureRWCount, &handle, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedStructsMemoryAllocateSamplers GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*maxStructsCount*/,
    APE_OBJECT_NUMBER/*maxStructsMembersOfTypeSamplerCount*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redStructsMemoryAllocateSamplers")
  getArgAs_Pointer(RedContext,    context,                             args[_i++]);
  getArgAs_Pointer(RedHandleGpu,  gpu,                                 args[_i++]);
  getArgAs_CChars(const char *,   handleName,                          args[_i++]);
  getArgAs_Double(unsigned,       maxStructsCount,                     args[_i++]);
  getArgAs_Double(unsigned,       maxStructsMembersOfTypeSamplerCount, args[_i++]);
  getArgAs_Pointer(RedStatuses *, outStatuses,                         args[_i++]);
  getArgAs_END

  RedHandleStructsMemory handle = 0;
  redStructsMemoryAllocateSamplers(context, gpu, handleName, maxStructsCount, maxStructsMembersOfTypeSamplerCount, &handle, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedStructsMemorySuballocateStructs GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*handleNames*/,
    APE_OBJECT_NUMBER/*structsMemory*/,
    APE_OBJECT_NUMBER/*structsDeclarationsCount*/,
    APE_OBJECT_NUMBER/*structsDeclarations*/,
    APE_OBJECT_NUMBER/*outStructs*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redStructsMemorySuballocateStructs")
  getArgAs_Pointer(RedContext,                         context,                  args[_i++]);
  getArgAs_Pointer(RedHandleGpu,                       gpu,                      args[_i++]);
  getArgAs_Pointer(const char **,                      handleNames,              args[_i++]);
  getArgAs_Pointer(RedHandleStructsMemory,             structsMemory,            args[_i++]);
  getArgAs_Double(unsigned,                            structsDeclarationsCount, args[_i++]);
  getArgAs_Pointer(const RedHandleStructDeclaration *, structsDeclarations,      args[_i++]);
  getArgAs_Pointer(RedHandleStruct *,                  outStructs,               args[_i++]);
  getArgAs_Pointer(RedStatuses *,                      outStatuses,              args[_i++]);
  getArgAs_END

  redStructsMemorySuballocateStructs(context, gpu, handleNames, structsMemory, structsDeclarationsCount, structsDeclarations, outStructs, outStatuses, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedStructsMemoryReset GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*structsMemory*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redStructsMemoryReset")
  getArgAs_Pointer(RedContext,             context,       args[_i++]);
  getArgAs_Pointer(RedHandleGpu,           gpu,           args[_i++]);
  getArgAs_Pointer(RedHandleStructsMemory, structsMemory, args[_i++]);
  getArgAs_Pointer(RedStatuses *,          outStatuses,   args[_i++]);
  getArgAs_END

  redStructsMemoryReset(context, gpu, structsMemory, outStatuses, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedStructsMemoryFree GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*structsMemory*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redStructsMemoryFree")
  getArgAs_Pointer(RedContext,             context,       args[_i++]);
  getArgAs_Pointer(RedHandleGpu,           gpu,           args[_i++]);
  getArgAs_Pointer(RedHandleStructsMemory, structsMemory, args[_i++]);
  getArgAs_END

  redStructsMemoryFree(context, gpu, structsMemory, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedStructsSet GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*structsMembersCount*/,
    APE_OBJECT_NUMBER/*structsMembers*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redStructsSet")
  getArgAs_Pointer(RedContext,              context,             args[_i++]);
  getArgAs_Pointer(RedHandleGpu,            gpu,                 args[_i++]);
  getArgAs_Double(unsigned,                 structsMembersCount, args[_i++]);
  getArgAs_Pointer(const RedStructMember *, structsMembers,      args[_i++]);
  getArgAs_END

  redStructsSet(context, gpu, structsMembersCount, structsMembers, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateArray GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*type*/,
    APE_OBJECT_NUMBER/*bytesCount*/,
    APE_OBJECT_NUMBER/*structuredBufferElementBytesCount*/,
    APE_OBJECT_NUMBER/*initialAccess*/,
    APE_OBJECT_NUMBER/*initialQueueFamilyIndex*/,
    APE_OBJECT_BOOL/*dedicate*/,
    APE_OBJECT_NUMBER/*outArray*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateArray")
  getArgAs_Pointer(RedContext,       context,                           args[_i++]);
  getArgAs_Pointer(RedHandleGpu,     gpu,                               args[_i++]);
  getArgAs_CChars(const char *,      handleName,                        args[_i++]);
  getArgAs_Double(RedArrayType,      type,                              args[_i++]);
  getArgAs_Double(uint64_t,          bytesCount,                        args[_i++]);
  getArgAs_Double(uint64_t,          structuredBufferElementBytesCount, args[_i++]);
  getArgAs_Double(RedAccessBitflags, initialAccess,                     args[_i++]);
  getArgAs_Double(unsigned,          initialQueueFamilyIndex,           args[_i++]);
  getArgAs_Bool(RedBool32,           dedicate,                          args[_i++]);
  getArgAs_Pointer(RedArray *,       outArray,                          args[_i++]);
  getArgAs_Pointer(RedStatuses *,    outStatuses,                       args[_i++]);
  getArgAs_END

  redCreateArray(context, gpu, handleName, type, bytesCount, structuredBufferElementBytesCount, initialAccess, initialQueueFamilyIndex, dedicate, outArray, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)outArray->handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateImage GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*dimensions*/,
    APE_OBJECT_NUMBER/*format*/,
    APE_OBJECT_NUMBER/*width*/,
    APE_OBJECT_NUMBER/*height*/,
    APE_OBJECT_NUMBER/*depth*/,
    APE_OBJECT_NUMBER/*levelsCount*/,
    APE_OBJECT_NUMBER/*layersCount*/,
    APE_OBJECT_NUMBER/*multisampleCount*/,
    APE_OBJECT_NUMBER/*restrictToAccess*/,
    APE_OBJECT_NUMBER/*initialAccess*/,
    APE_OBJECT_NUMBER/*initialQueueFamilyIndex*/,
    APE_OBJECT_BOOL/*dedicate*/,
    APE_OBJECT_NUMBER/*outImage*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateImage")
  getArgAs_Pointer(RedContext,                context,                 args[_i++]);
  getArgAs_Pointer(RedHandleGpu,              gpu,                     args[_i++]);
  getArgAs_CChars(const char *,               handleName,              args[_i++]);
  getArgAs_Double(RedImageDimensions,         dimensions,              args[_i++]);
  getArgAs_Double(RedFormat,                  format,                  args[_i++]);
  getArgAs_Double(unsigned,                   width,                   args[_i++]);
  getArgAs_Double(unsigned,                   height,                  args[_i++]);
  getArgAs_Double(unsigned,                   depth,                   args[_i++]);
  getArgAs_Double(unsigned,                   levelsCount,             args[_i++]);
  getArgAs_Double(unsigned,                   layersCount,             args[_i++]);
  getArgAs_Double(RedMultisampleCountBitflag, multisampleCount,        args[_i++]);
  getArgAs_Double(RedAccessBitflags,          restrictToAccess,        args[_i++]);
  getArgAs_Double(RedAccessBitflags,          initialAccess,           args[_i++]);
  getArgAs_Double(unsigned,                   initialQueueFamilyIndex, args[_i++]);
  getArgAs_Bool(RedBool32,                    dedicate,                args[_i++]);
  getArgAs_Pointer(RedImage *,                outImage,                args[_i++]);
  getArgAs_Pointer(RedStatuses *,             outStatuses,             args[_i++]);
  getArgAs_END

  redCreateImage(context, gpu, handleName, dimensions, format, width, height, depth, levelsCount, layersCount, multisampleCount, restrictToAccess, initialAccess, initialQueueFamilyIndex, dedicate, outImage, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)outImage->handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateSampler GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*filteringMag*/,
    APE_OBJECT_NUMBER/*filteringMin*/,
    APE_OBJECT_NUMBER/*filteringMip*/,
    APE_OBJECT_NUMBER/*behaviorOutsideTextureCoordinateU*/,
    APE_OBJECT_NUMBER/*behaviorOutsideTextureCoordinateV*/,
    APE_OBJECT_NUMBER/*behaviorOutsideTextureCoordinateW*/,
    APE_OBJECT_NUMBER/*mipLodBias*/,
    APE_OBJECT_BOOL/*enableAnisotropy*/,
    APE_OBJECT_NUMBER/*maxAnisotropy*/,
    APE_OBJECT_BOOL/*enableCompare*/,
    APE_OBJECT_NUMBER/*compareOp*/,
    APE_OBJECT_NUMBER/*minLod*/,
    APE_OBJECT_NUMBER/*maxLod*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateSampler")
  getArgAs_Pointer(RedContext,                                context,                           args[_i++]);
  getArgAs_Pointer(RedHandleGpu,                              gpu,                               args[_i++]);
  getArgAs_CChars(const char *,                               handleName,                        args[_i++]);
  getArgAs_Double(RedSamplerFiltering,                        filteringMag,                      args[_i++]);
  getArgAs_Double(RedSamplerFiltering,                        filteringMin,                      args[_i++]);
  getArgAs_Double(RedSamplerFilteringMip,                     filteringMip,                      args[_i++]);
  getArgAs_Double(RedSamplerBehaviorOutsideTextureCoordinate, behaviorOutsideTextureCoordinateU, args[_i++]);
  getArgAs_Double(RedSamplerBehaviorOutsideTextureCoordinate, behaviorOutsideTextureCoordinateV, args[_i++]);
  getArgAs_Double(RedSamplerBehaviorOutsideTextureCoordinate, behaviorOutsideTextureCoordinateW, args[_i++]);
  getArgAs_Double(float,                                      mipLodBias,                        args[_i++]);
  getArgAs_Bool(RedBool32,                                    enableAnisotropy,                  args[_i++]);
  getArgAs_Double(float,                                      maxAnisotropy,                     args[_i++]);
  getArgAs_Bool(RedBool32,                                    enableCompare,                     args[_i++]);
  getArgAs_Double(RedCompareOp,                               compareOp,                         args[_i++]);
  getArgAs_Double(float,                                      minLod,                            args[_i++]);
  getArgAs_Double(float,                                      maxLod,                            args[_i++]);
  getArgAs_Pointer(RedStatuses *,                             outStatuses,                       args[_i++]);
  getArgAs_END

  RedHandleSampler handle = 0;
  redCreateSampler(context, gpu, handleName, filteringMag, filteringMin, filteringMip, behaviorOutsideTextureCoordinateU, behaviorOutsideTextureCoordinateV, behaviorOutsideTextureCoordinateW, mipLodBias, enableAnisotropy, maxAnisotropy, enableCompare, compareOp, minLod, maxLod, &handle, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateTexture GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*image*/,
    APE_OBJECT_NUMBER/*parts*/,
    APE_OBJECT_NUMBER/*dimensions*/,
    APE_OBJECT_NUMBER/*format*/,
    APE_OBJECT_NUMBER/*levelsFirst*/,
    APE_OBJECT_NUMBER/*levelsCount*/,
    APE_OBJECT_NUMBER/*layersFirst*/,
    APE_OBJECT_NUMBER/*layersCount*/,
    APE_OBJECT_NUMBER/*restrictToAccess*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateTexture")
  getArgAs_Pointer(RedContext,          context,          args[_i++]);
  getArgAs_Pointer(RedHandleGpu,        gpu,              args[_i++]);
  getArgAs_CChars(const char *,         handleName,       args[_i++]);
  getArgAs_Pointer(RedHandleImage,      image,            args[_i++]);
  getArgAs_Double(RedImagePartBitflags, parts,            args[_i++]);
  getArgAs_Double(RedTextureDimensions, dimensions,       args[_i++]);
  getArgAs_Double(RedFormat,            format,           args[_i++]);
  getArgAs_Double(unsigned,             levelsFirst,      args[_i++]);
  getArgAs_Double(unsigned,             levelsCount,      args[_i++]);
  getArgAs_Double(unsigned,             layersFirst,      args[_i++]);
  getArgAs_Double(unsigned,             layersCount,      args[_i++]);
  getArgAs_Double(RedAccessBitflags,    restrictToAccess, args[_i++]);
  getArgAs_Pointer(RedStatuses *,       outStatuses,      args[_i++]);
  getArgAs_END

  RedHandleTexture handle = 0;
  redCreateTexture(context, gpu, handleName, image, parts, dimensions, format, levelsFirst, levelsCount, layersFirst, layersCount, restrictToAccess, &handle, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateGpuCode GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*irBytesCount*/,
    APE_OBJECT_NUMBER/*ir*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateGpuCode")
  getArgAs_Pointer(RedContext,    context,      args[_i++]);
  getArgAs_Pointer(RedHandleGpu,  gpu,          args[_i++]);
  getArgAs_CChars(const char *,   handleName,   args[_i++]);
  getArgAs_Double(uint64_t,       irBytesCount, args[_i++]);
  getArgAs_Pointer(const void *,  ir,           args[_i++]);
  getArgAs_Pointer(RedStatuses *, outStatuses,  args[_i++]);
  getArgAs_END

  RedHandleGpuCode handle = 0;
  redCreateGpuCode(context, gpu, handleName, irBytesCount, ir, &handle, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateOutputDeclaration GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*outputDeclarationMembers*/,
    APE_OBJECT_NUMBER/*outputDeclarationMembersResolveSources*/,
    APE_OBJECT_BOOL/*dependencyByRegion*/,
    APE_OBJECT_BOOL/*dependencyByRegionAllowUsageAliasOrderBarriers*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateOutputDeclaration")
  getArgAs_Pointer(RedContext,                                        context,                                        args[_i++]);
  getArgAs_Pointer(RedHandleGpu,                                      gpu,                                            args[_i++]);
  getArgAs_CChars(const char *,                                       handleName,                                     args[_i++]);
  getArgAs_Pointer(const RedOutputDeclarationMembers *,               outputDeclarationMembers,                       args[_i++]);
  getArgAs_Pointer(const RedOutputDeclarationMembersResolveSources *, outputDeclarationMembersResolveSources,         args[_i++]);
  getArgAs_Bool(RedBool32,                                            dependencyByRegion,                             args[_i++]);
  getArgAs_Bool(RedBool32,                                            dependencyByRegionAllowUsageAliasOrderBarriers, args[_i++]);
  getArgAs_Pointer(RedStatuses *,                                     outStatuses,                                    args[_i++]);
  getArgAs_END

  RedHandleOutputDeclaration handle = 0;
  redCreateOutputDeclaration(context, gpu, handleName, outputDeclarationMembers, outputDeclarationMembersResolveSources, dependencyByRegion, dependencyByRegionAllowUsageAliasOrderBarriers, &handle, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateStructDeclaration GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*structDeclarationMembersCount*/,
    APE_OBJECT_NUMBER/*structDeclarationMembers*/,
    APE_OBJECT_NUMBER/*structDeclarationMembersArrayROCount*/,
    APE_OBJECT_NUMBER/*structDeclarationMembersArrayRO*/,
    APE_OBJECT_BOOL/*procedureParametersHandlesDeclaration*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateStructDeclaration")
  getArgAs_Pointer(RedContext,                                context,                               args[_i++]);
  getArgAs_Pointer(RedHandleGpu,                              gpu,                                   args[_i++]);
  getArgAs_CChars(const char *,                               handleName,                            args[_i++]);
  getArgAs_Double(unsigned,                                   structDeclarationMembersCount,         args[_i++]);
  getArgAs_Pointer(const RedStructDeclarationMember *,        structDeclarationMembers,              args[_i++]);
  getArgAs_Double(unsigned,                                   structDeclarationMembersArrayROCount,  args[_i++]);
  getArgAs_Pointer(const RedStructDeclarationMemberArrayRO *, structDeclarationMembersArrayRO,       args[_i++]);
  getArgAs_Bool(RedBool32,                                    procedureParametersHandlesDeclaration, args[_i++]);
  getArgAs_Pointer(RedStatuses *,                             outStatuses,                           args[_i++]);
  getArgAs_END

  RedHandleStructDeclaration handle = 0;
  redCreateStructDeclaration(context, gpu, handleName, structDeclarationMembersCount, structDeclarationMembers, structDeclarationMembersArrayROCount, structDeclarationMembersArrayRO, procedureParametersHandlesDeclaration, &handle, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateProcedureParameters GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*procedureParametersDeclaration*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateProcedureParameters")
  getArgAs_Pointer(RedContext,                                context,                        args[_i++]);
  getArgAs_Pointer(RedHandleGpu,                              gpu,                            args[_i++]);
  getArgAs_CChars(const char *,                               handleName,                     args[_i++]);
  getArgAs_Pointer(const RedProcedureParametersDeclaration *, procedureParametersDeclaration, args[_i++]);
  getArgAs_Pointer(RedStatuses *,                             outStatuses,                    args[_i++]);
  getArgAs_END

  RedHandleProcedureParameters handle = 0;
  redCreateProcedureParameters(context, gpu, handleName, procedureParametersDeclaration, &handle, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateProcedureCache GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*fromBlobBytesCount*/,
    APE_OBJECT_NUMBER/*fromBlob*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateProcedureCache")
  getArgAs_Pointer(RedContext,    context,            args[_i++]);
  getArgAs_Pointer(RedHandleGpu,  gpu,                args[_i++]);
  getArgAs_CChars(const char *,   handleName,         args[_i++]);
  getArgAs_Double(uint64_t,       fromBlobBytesCount, args[_i++]);
  getArgAs_Pointer(const void *,  fromBlob,           args[_i++]);
  getArgAs_Pointer(RedStatuses *, outStatuses,        args[_i++]);
  getArgAs_END

  RedHandleProcedureCache handle = 0;
  redCreateProcedureCache(context, gpu, handleName, fromBlobBytesCount, fromBlob, &handle, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateProcedure GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*procedureCache*/,
    APE_OBJECT_NUMBER/*outputDeclaration*/,
    APE_OBJECT_NUMBER/*procedureParameters*/,
    APE_OBJECT_STRING/*gpuCodeVertexMainProcedureName*/,
    APE_OBJECT_NUMBER/*gpuCodeVertex*/,
    APE_OBJECT_STRING/*gpuCodeFragmentMainProcedureName*/,
    APE_OBJECT_NUMBER/*gpuCodeFragment*/,
    APE_OBJECT_NUMBER/*state*/,
    APE_OBJECT_NUMBER/*stateExtension*/,
    APE_OBJECT_BOOL/*deriveBase*/,
    APE_OBJECT_NUMBER/*deriveFrom*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateProcedure")
  getArgAs_Pointer(RedContext,                   context,                          args[_i++]);
  getArgAs_Pointer(RedHandleGpu,                 gpu,                              args[_i++]);
  getArgAs_CChars(const char *,                  handleName,                       args[_i++]);
  getArgAs_Pointer(RedHandleProcedureCache,      procedureCache,                   args[_i++]);
  getArgAs_Pointer(RedHandleOutputDeclaration,   outputDeclaration,                args[_i++]);
  getArgAs_Pointer(RedHandleProcedureParameters, procedureParameters,              args[_i++]);
  getArgAs_CChars(const char *,                  gpuCodeVertexMainProcedureName,   args[_i++]);
  getArgAs_Pointer(RedHandleGpuCode,             gpuCodeVertex,                    args[_i++]);
  getArgAs_CChars(const char *,                  gpuCodeFragmentMainProcedureName, args[_i++]);
  getArgAs_Pointer(RedHandleGpuCode,             gpuCodeFragment,                  args[_i++]);
  getArgAs_Pointer(const RedProcedureState *,    state,                            args[_i++]);
  getArgAs_Pointer(const void *,                 stateExtension,                   args[_i++]);
  getArgAs_Bool(RedBool32,                       deriveBase,                       args[_i++]);
  getArgAs_Pointer(RedHandleProcedure,           deriveFrom,                       args[_i++]);
  getArgAs_Pointer(RedStatuses *,                outStatuses,                      args[_i++]);
  getArgAs_END

  RedHandleProcedure handle = 0;
  redCreateProcedure(context, gpu, handleName, procedureCache, outputDeclaration, procedureParameters, gpuCodeVertexMainProcedureName, gpuCodeVertex, gpuCodeFragmentMainProcedureName, gpuCodeFragment, state, stateExtension, deriveBase, deriveFrom, &handle, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateProcedureCompute GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*procedureCache*/,
    APE_OBJECT_NUMBER/*procedureParameters*/,
    APE_OBJECT_STRING/*gpuCodeMainProcedureName*/,
    APE_OBJECT_NUMBER/*gpuCode*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateProcedureCompute")
  getArgAs_Pointer(RedContext,                   context,                  args[_i++]);
  getArgAs_Pointer(RedHandleGpu,                 gpu,                      args[_i++]);
  getArgAs_CChars(const char *,                  handleName,               args[_i++]);
  getArgAs_Pointer(RedHandleProcedureCache,      procedureCache,           args[_i++]);
  getArgAs_Pointer(RedHandleProcedureParameters, procedureParameters,      args[_i++]);
  getArgAs_CChars(const char *,                  gpuCodeMainProcedureName, args[_i++]);
  getArgAs_Pointer(RedHandleGpuCode,             gpuCode,                  args[_i++]);
  getArgAs_Pointer(RedStatuses *,                outStatuses,              args[_i++]);
  getArgAs_END

  RedHandleProcedure handle = 0;
  redCreateProcedureCompute(context, gpu, handleName, procedureCache, procedureParameters, gpuCodeMainProcedureName, gpuCode, &handle, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateOutput GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*outputDeclaration*/,
    APE_OBJECT_NUMBER/*outputMembers*/,
    APE_OBJECT_NUMBER/*outputMembersResolveTargets*/,
    APE_OBJECT_NUMBER/*width*/,
    APE_OBJECT_NUMBER/*height*/,
    APE_OBJECT_NUMBER/*outOutput*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateOutput")
  getArgAs_Pointer(RedContext,                             context,                     args[_i++]);
  getArgAs_Pointer(RedHandleGpu,                           gpu,                         args[_i++]);
  getArgAs_CChars(const char *,                            handleName,                  args[_i++]);
  getArgAs_Pointer(RedHandleOutputDeclaration,             outputDeclaration,           args[_i++]);
  getArgAs_Pointer(const RedOutputMembers *,               outputMembers,               args[_i++]);
  getArgAs_Pointer(const RedOutputMembersResolveTargets *, outputMembersResolveTargets, args[_i++]);
  getArgAs_Double(unsigned,                                width,                       args[_i++]);
  getArgAs_Double(unsigned,                                height,                      args[_i++]);
  getArgAs_Pointer(RedOutput *,                            outOutput,                   args[_i++]);
  getArgAs_Pointer(RedStatuses *,                          outStatuses,                 args[_i++]);
  getArgAs_END

  redCreateOutput(context, gpu, handleName, outputDeclaration, outputMembers, outputMembersResolveTargets, width, height, outOutput, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)outOutput->handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateCpuSignal GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_BOOL/*createSignaled*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateCpuSignal")
  getArgAs_Pointer(RedContext,    context,        args[_i++]);
  getArgAs_Pointer(RedHandleGpu,  gpu,            args[_i++]);
  getArgAs_CChars(const char *,   handleName,     args[_i++]);
  getArgAs_Bool(RedBool32,        createSignaled, args[_i++]);
  getArgAs_Pointer(RedStatuses *, outStatuses,    args[_i++]);
  getArgAs_END

  RedHandleCpuSignal handle = 0;
  redCreateCpuSignal(context, gpu, handleName, createSignaled, &handle, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateGpuSignal GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateGpuSignal")
  getArgAs_Pointer(RedContext,    context,     args[_i++]);
  getArgAs_Pointer(RedHandleGpu,  gpu,         args[_i++]);
  getArgAs_CChars(const char *,   handleName,  args[_i++]);
  getArgAs_Pointer(RedStatuses *, outStatuses, args[_i++]);
  getArgAs_END

  RedHandleGpuSignal handle = 0;
  redCreateGpuSignal(context, gpu, handleName, &handle, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateGpuToCpuSignal GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateGpuToCpuSignal")
  getArgAs_Pointer(RedContext,    context,     args[_i++]);
  getArgAs_Pointer(RedHandleGpu,  gpu,         args[_i++]);
  getArgAs_CChars(const char *,   handleName,  args[_i++]);
  getArgAs_Pointer(RedStatuses *, outStatuses, args[_i++]);
  getArgAs_END

  RedHandleGpuToCpuSignal handle = 0;
  redCreateGpuToCpuSignal(context, gpu, handleName, &handle, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateCalls GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*queueFamilyIndex*/,
    APE_OBJECT_NUMBER/*outCalls*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateCalls")
  getArgAs_Pointer(RedContext,    context,          args[_i++]);
  getArgAs_Pointer(RedHandleGpu,  gpu,              args[_i++]);
  getArgAs_CChars(const char *,   handleName,       args[_i++]);
  getArgAs_Double(unsigned,       queueFamilyIndex, args[_i++]);
  getArgAs_Pointer(RedCalls *,    outCalls,         args[_i++]);
  getArgAs_Pointer(RedStatuses *, outStatuses,      args[_i++]);
  getArgAs_END

  redCreateCalls(context, gpu, handleName, queueFamilyIndex, outCalls, outStatuses, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateCallsReusable GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*queueFamilyIndex*/,
    APE_OBJECT_NUMBER/*outCalls*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateCallsReusable")
  getArgAs_Pointer(RedContext,    context,          args[_i++]);
  getArgAs_Pointer(RedHandleGpu,  gpu,              args[_i++]);
  getArgAs_CChars(const char *,   handleName,       args[_i++]);
  getArgAs_Double(unsigned,       queueFamilyIndex, args[_i++]);
  getArgAs_Pointer(RedCalls *,    outCalls,         args[_i++]);
  getArgAs_Pointer(RedStatuses *, outStatuses,      args[_i++]);
  getArgAs_END

  redCreateCallsReusable(context, gpu, handleName, queueFamilyIndex, outCalls, outStatuses, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedDestroyContext GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redDestroyContext")
  getArgAs_Pointer(RedContext, context, args[_i++]);
  getArgAs_END

  redDestroyContext(context, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedDestroyArray GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*array*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redDestroyArray")
  getArgAs_Pointer(RedContext,     context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,   gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleArray, handle,  args[_i++]);
  getArgAs_END

  redDestroyArray(context, gpu, handle, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedDestroyImage GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*image*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redDestroyImage")
  getArgAs_Pointer(RedContext,     context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,   gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleImage, handle,  args[_i++]);
  getArgAs_END

  redDestroyImage(context, gpu, handle, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedDestroySampler GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*sampler*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redDestroySampler")
  getArgAs_Pointer(RedContext,       context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,     gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleSampler, handle,  args[_i++]);
  getArgAs_END

  redDestroySampler(context, gpu, handle, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedDestroyTexture GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*texture*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redDestroyTexture")
  getArgAs_Pointer(RedContext,       context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,     gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleTexture, handle,  args[_i++]);
  getArgAs_END

  redDestroyTexture(context, gpu, handle, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedDestroyGpuCode GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*gpuCode*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redDestroyGpuCode")
  getArgAs_Pointer(RedContext,       context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,     gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleGpuCode, handle,  args[_i++]);
  getArgAs_END

  redDestroyGpuCode(context, gpu, handle, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedDestroyOutputDeclaration GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*outputDeclaration*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redDestroyOutputDeclaration")
  getArgAs_Pointer(RedContext,                 context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,               gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleOutputDeclaration, handle,  args[_i++]);
  getArgAs_END

  redDestroyOutputDeclaration(context, gpu, handle, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedDestroyStructDeclaration GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*structDeclaration*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redDestroyStructDeclaration")
  getArgAs_Pointer(RedContext,                 context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,               gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleStructDeclaration, handle,  args[_i++]);
  getArgAs_END

  redDestroyStructDeclaration(context, gpu, handle, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedDestroyProcedureParameters GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*procedureParameters*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redDestroyProcedureParameters")
  getArgAs_Pointer(RedContext,                   context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,                 gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleProcedureParameters, handle,  args[_i++]);
  getArgAs_END

  redDestroyProcedureParameters(context, gpu, handle, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedDestroyProcedureCache GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*procedureCache*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redDestroyProcedureCache")
  getArgAs_Pointer(RedContext,              context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,            gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleProcedureCache, handle,  args[_i++]);
  getArgAs_END

  redDestroyProcedureCache(context, gpu, handle, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedDestroyProcedure GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*procedure*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redDestroyProcedure")
  getArgAs_Pointer(RedContext,         context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,       gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleProcedure, handle,  args[_i++]);
  getArgAs_END

  redDestroyProcedure(context, gpu, handle, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedDestroyOutput GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*output*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redDestroyOutput")
  getArgAs_Pointer(RedContext,      context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,    gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleOutput, handle,  args[_i++]);
  getArgAs_END

  redDestroyOutput(context, gpu, handle, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedDestroyCpuSignal GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*cpuSignal*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redDestroyCpuSignal")
  getArgAs_Pointer(RedContext,         context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,       gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleCpuSignal, handle,  args[_i++]);
  getArgAs_END

  redDestroyCpuSignal(context, gpu, handle, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedDestroyGpuSignal GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*gpuSignal*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redDestroyGpuSignal")
  getArgAs_Pointer(RedContext,         context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,       gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleGpuSignal, handle,  args[_i++]);
  getArgAs_END

  redDestroyGpuSignal(context, gpu, handle, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedDestroyGpuToCpuSignal GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*gpuToCpuSignal*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redDestroyGpuToCpuSignal")
  getArgAs_Pointer(RedContext,              context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,            gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleGpuToCpuSignal, handle,  args[_i++]);
  getArgAs_END

  redDestroyGpuToCpuSignal(context, gpu, handle, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedDestroyCalls GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*callsMemory*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redDestroyCalls")
  getArgAs_Pointer(RedContext,           context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,         gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleCalls,       handle,  args[_i++]);
  getArgAs_Pointer(RedHandleCallsMemory, memory,  args[_i++]);
  getArgAs_END

  redDestroyCalls(context, gpu, handle, memory, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedProcedureCacheGetBlob GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*procedureCache*/,
    APE_OBJECT_NUMBER/*outBlobBytesCount*/,
    APE_OBJECT_NUMBER/*outBlob*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redProcedureCacheGetBlob")
  getArgAs_Pointer(RedContext,              context,           args[_i++]);
  getArgAs_Pointer(RedHandleGpu,            gpu,               args[_i++]);
  getArgAs_Pointer(RedHandleProcedureCache, procedureCache,    args[_i++]);
  getArgAs_Pointer(uint64_t *,              outBlobBytesCount, args[_i++]);
  getArgAs_Pointer(void *,                  outBlob,           args[_i++]);
  getArgAs_Pointer(RedStatuses *,           outStatuses,       args[_i++]);
  getArgAs_END

  redProcedureCacheGetBlob(context, gpu, procedureCache, outBlobBytesCount, outBlob, outStatuses, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedProcedureCacheMergeCaches GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*sourceProcedureCachesCount*/,
    APE_OBJECT_NUMBER/*sourceProcedureCaches*/,
    APE_OBJECT_NUMBER/*targetProcedureCache*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redProcedureCacheMergeCaches")
  getArgAs_Pointer(RedContext,                      context,                    args[_i++]);
  getArgAs_Pointer(RedHandleGpu,                    gpu,                        args[_i++]);
  getArgAs_Double(unsigned,                         sourceProcedureCachesCount, args[_i++]);
  getArgAs_Pointer(const RedHandleProcedureCache *, sourceProcedureCaches,      args[_i++]);
  getArgAs_Pointer(RedHandleProcedureCache,         targetProcedureCache,       args[_i++]);
  getArgAs_Pointer(RedStatuses *,                   outStatuses,                args[_i++]);
  getArgAs_END

  redProcedureCacheMergeCaches(context, gpu, sourceProcedureCachesCount, sourceProcedureCaches, targetProcedureCache, outStatuses, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCpuSignalGetStatus GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*cpuSignal*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCpuSignalGetStatus")
  getArgAs_Pointer(RedContext,         context,   args[_i++]);
  getArgAs_Pointer(RedHandleGpu,       gpu,       args[_i++]);
  getArgAs_Pointer(RedHandleCpuSignal, cpuSignal, args[_i++]);
  getArgAs_END

  RedStatus status = RED_STATUS_SUCCESS;
  redCpuSignalGetStatus(context, gpu, cpuSignal, &status, 0, 0, 0);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCpuSignalWait GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*cpuSignalsCount*/,
    APE_OBJECT_NUMBER/*cpuSignals*/,
    APE_OBJECT_BOOL/*waitAll*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCpuSignalWait")
  getArgAs_Pointer(RedContext,                 context,         args[_i++]);
  getArgAs_Pointer(RedHandleGpu,               gpu,             args[_i++]);
  getArgAs_Double(unsigned,                    cpuSignalsCount, args[_i++]);
  getArgAs_Pointer(const RedHandleCpuSignal *, cpuSignals,      args[_i++]);
  getArgAs_Bool(RedBool32,                     waitAll,         args[_i++]);
  getArgAs_Pointer(RedStatuses *,              outStatuses,     args[_i++]);
  getArgAs_END

  redCpuSignalWait(context, gpu, cpuSignalsCount, cpuSignals, waitAll, outStatuses, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCpuSignalUnsignal GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*cpuSignalsCount*/,
    APE_OBJECT_NUMBER/*cpuSignals*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCpuSignalUnsignal")
  getArgAs_Pointer(RedContext,                 context,         args[_i++]);
  getArgAs_Pointer(RedHandleGpu,               gpu,             args[_i++]);
  getArgAs_Double(unsigned,                    cpuSignalsCount, args[_i++]);
  getArgAs_Pointer(const RedHandleCpuSignal *, cpuSignals,      args[_i++]);
  getArgAs_Pointer(RedStatuses *,              outStatuses,     args[_i++]);
  getArgAs_END

  redCpuSignalUnsignal(context, gpu, cpuSignalsCount, cpuSignals, outStatuses, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedGpuToCpuSignalGetStatus GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*gpuToCpuSignal*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redGpuToCpuSignalGetStatus")
  getArgAs_Pointer(RedContext,              context,        args[_i++]);
  getArgAs_Pointer(RedHandleGpu,            gpu,            args[_i++]);
  getArgAs_Pointer(RedHandleGpuToCpuSignal, gpuToCpuSignal, args[_i++]);
  getArgAs_END

  RedStatus status = RED_STATUS_SUCCESS;
  redGpuToCpuSignalGetStatus(context, gpu, gpuToCpuSignal, &status, 0, 0, 0);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedGpuToCpuSignalUnsignal GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*gpuToCpuSignal*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redGpuToCpuSignalUnsignal")
  getArgAs_Pointer(RedContext,              context,        args[_i++]);
  getArgAs_Pointer(RedHandleGpu,            gpu,            args[_i++]);
  getArgAs_Pointer(RedHandleGpuToCpuSignal, gpuToCpuSignal, args[_i++]);
  getArgAs_Pointer(RedStatuses *,           outStatuses,    args[_i++]);
  getArgAs_END

  redGpuToCpuSignalUnsignal(context, gpu, gpuToCpuSignal, outStatuses, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallsSet GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*callsMemory*/,
    APE_OBJECT_BOOL/*callsReusable*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallsSet")
  getArgAs_Pointer(RedContext,           context,       args[_i++]);
  getArgAs_Pointer(RedHandleGpu,         gpu,           args[_i++]);
  getArgAs_Pointer(RedHandleCalls,       calls,         args[_i++]);
  getArgAs_Pointer(RedHandleCallsMemory, callsMemory,   args[_i++]);
  getArgAs_Bool(RedBool32,               callsReusable, args[_i++]);
  getArgAs_Pointer(RedStatuses *,        outStatuses,   args[_i++]);
  getArgAs_END

  redCallsSet(context, gpu, calls, callsMemory, callsReusable, outStatuses, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallsEnd GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*callsMemory*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallsEnd")
  getArgAs_Pointer(RedContext,           context,       args[_i++]);
  getArgAs_Pointer(RedHandleGpu,         gpu,           args[_i++]);
  getArgAs_Pointer(RedHandleCalls,       calls,         args[_i++]);
  getArgAs_Pointer(RedHandleCallsMemory, callsMemory,   args[_i++]);
  getArgAs_Pointer(RedStatuses *,        outStatuses,   args[_i++]);
  getArgAs_END

  redCallsEnd(context, gpu, calls, callsMemory, outStatuses, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedGetCallProceduresAndAddresses GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*outCallProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redGetCallProceduresAndAddresses")
  getArgAs_Pointer(RedContext,                      context,                       args[_i++]);
  getArgAs_Pointer(RedHandleGpu,                    gpu,                           args[_i++]);
  getArgAs_Pointer(RedCallProceduresAndAddresses *, outCallProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedStatuses *,                   outStatuses,                   args[_i++]);
  getArgAs_END

  redGetCallProceduresAndAddresses(context, gpu, outCallProceduresAndAddresses, outStatuses, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallGpuToCpuSignalSignal GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*signalGpuToCpuSignal*/,
    APE_OBJECT_NUMBER/*setTo8192*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallGpuToCpuSignalSignal")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Pointer(RedHandleGpuToCpuSignal,         signalGpuToCpuSignal,       args[_i++]);
  getArgAs_Double(unsigned,                         setTo8192,                  args[_i++]);
  getArgAs_END

  callProceduresAndAddresses->redCallGpuToCpuSignalSignal(calls, signalGpuToCpuSignal, setTo8192);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallCopyArrayToArray GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*arrayR*/,
    APE_OBJECT_NUMBER/*arrayW*/,
    APE_OBJECT_NUMBER/*rangesCount*/,
    APE_OBJECT_NUMBER/*ranges*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallCopyArrayToArray")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Pointer(RedHandleArray,                  arrayR,                     args[_i++]);
  getArgAs_Pointer(RedHandleArray,                  arrayW,                     args[_i++]);
  getArgAs_Double(unsigned,                         rangesCount,                args[_i++]);
  getArgAs_Pointer(const RedCopyArrayRange *,       ranges,                     args[_i++]);
  getArgAs_END

  callProceduresAndAddresses->redCallCopyArrayToArray(calls, arrayR, arrayW, rangesCount, ranges);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallCopyImageToImage GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*imageR*/,
    APE_OBJECT_NUMBER/*setTo1*/,
    APE_OBJECT_NUMBER/*imageW*/,
    APE_OBJECT_NUMBER/*setTo01*/,
    APE_OBJECT_NUMBER/*rangesCount*/,
    APE_OBJECT_NUMBER/*ranges*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallCopyImageToImage")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Pointer(RedHandleImage,                  imageR,                     args[_i++]);
  getArgAs_Double(unsigned,                         setTo1,                     args[_i++]);
  getArgAs_Pointer(RedHandleImage,                  imageW,                     args[_i++]);
  getArgAs_Double(unsigned,                         setTo01,                    args[_i++]);
  getArgAs_Double(unsigned,                         rangesCount,                args[_i++]);
  getArgAs_Pointer(const RedCopyImageRange *,       ranges,                     args[_i++]);
  getArgAs_END

  callProceduresAndAddresses->redCallCopyImageToImage(calls, imageR, setTo1, imageW, setTo01, rangesCount, ranges);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallCopyArrayToImage GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*arrayR*/,
    APE_OBJECT_NUMBER/*imageW*/,
    APE_OBJECT_NUMBER/*setTo1*/,
    APE_OBJECT_NUMBER/*rangesCount*/,
    APE_OBJECT_NUMBER/*ranges*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallCopyArrayToImage")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Pointer(RedHandleArray,                  arrayR,                     args[_i++]);
  getArgAs_Pointer(RedHandleImage,                  imageW,                     args[_i++]);
  getArgAs_Double(unsigned,                         setTo01,                    args[_i++]);
  getArgAs_Double(unsigned,                         rangesCount,                args[_i++]);
  getArgAs_Pointer(const RedCopyArrayImageRange *,  ranges,                     args[_i++]);
  getArgAs_END

  callProceduresAndAddresses->redCallCopyArrayToImage(calls, arrayR, imageW, setTo01, rangesCount, ranges);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallCopyImageToArray GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*imageR*/,
    APE_OBJECT_NUMBER/*setTo1*/,
    APE_OBJECT_NUMBER/*arrayW*/,
    APE_OBJECT_NUMBER/*rangesCount*/,
    APE_OBJECT_NUMBER/*ranges*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallCopyImageToArray")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Pointer(RedHandleImage,                  imageR,                     args[_i++]);
  getArgAs_Double(unsigned,                         setTo01,                    args[_i++]);
  getArgAs_Pointer(RedHandleArray,                  arrayW,                     args[_i++]);
  getArgAs_Double(unsigned,                         rangesCount,                args[_i++]);
  getArgAs_Pointer(const RedCopyArrayImageRange *,  ranges,                     args[_i++]);
  getArgAs_END

  callProceduresAndAddresses->redCallCopyImageToArray(calls, imageR, setTo01, arrayW, rangesCount, ranges);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallProcedure GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*vertexCount*/,
    APE_OBJECT_NUMBER/*instanceCount*/,
    APE_OBJECT_NUMBER/*vertexFirst*/,
    APE_OBJECT_NUMBER/*instanceFirst*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallProcedure")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Double(unsigned,                         vertexCount,                args[_i++]);
  getArgAs_Double(unsigned,                         instanceCount,              args[_i++]);
  getArgAs_Double(unsigned,                         vertexFirst,                args[_i++]);
  getArgAs_Double(unsigned,                         instanceFirst,              args[_i++]);
  getArgAs_END

  callProceduresAndAddresses->redCallProcedure(calls, vertexCount, instanceCount, vertexFirst, instanceFirst);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallProcedureIndexed GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*indexCount*/,
    APE_OBJECT_NUMBER/*instanceCount*/,
    APE_OBJECT_NUMBER/*indexFirst*/,
    APE_OBJECT_NUMBER/*vertexBase*/,
    APE_OBJECT_NUMBER/*instanceFirst*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallProcedureIndexed")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Double(unsigned,                         indexCount,                 args[_i++]);
  getArgAs_Double(unsigned,                         instanceCount,              args[_i++]);
  getArgAs_Double(unsigned,                         indexFirst,                 args[_i++]);
  getArgAs_Double(unsigned,                         vertexBase,                 args[_i++]);
  getArgAs_Double(unsigned,                         instanceFirst,              args[_i++]);
  getArgAs_END

  callProceduresAndAddresses->redCallProcedureIndexed(calls, indexCount, instanceCount, indexFirst, vertexBase, instanceFirst);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallProcedureCompute GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*workgroupsCountX*/,
    APE_OBJECT_NUMBER/*workgroupsCountY*/,
    APE_OBJECT_NUMBER/*workgroupsCountZ*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallProcedureCompute")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Double(unsigned,                         workgroupsCountX,           args[_i++]);
  getArgAs_Double(unsigned,                         workgroupsCountY,           args[_i++]);
  getArgAs_Double(unsigned,                         workgroupsCountZ,           args[_i++]);
  getArgAs_END

  callProceduresAndAddresses->redCallProcedureCompute(calls, workgroupsCountX, workgroupsCountY, workgroupsCountZ);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallSetProcedure GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*procedureType*/,
    APE_OBJECT_NUMBER/*procedure*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallSetProcedure")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Double(RedProcedureType,                 procedureType,              args[_i++]);
  getArgAs_Pointer(RedHandleProcedure,              procedure,                  args[_i++]);
  getArgAs_END

  callProceduresAndAddresses->redCallSetProcedure(calls, procedureType, procedure);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallSetProcedureIndices GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*array*/,
    APE_OBJECT_NUMBER/*setTo0*/,
    APE_OBJECT_NUMBER/*setTo1*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallSetProcedureIndices")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Pointer(RedHandleArray,                  array,                      args[_i++]);
  getArgAs_Double(unsigned,                         setTo0,                     args[_i++]);
  getArgAs_Double(unsigned,                         setTo1,                     args[_i++]);
  getArgAs_END

  callProceduresAndAddresses->redCallSetProcedureIndices(calls, array, setTo0, setTo1);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallSetProcedureParametersVariables GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*procedureParameters*/,
    APE_OBJECT_NUMBER/*visibleToStages*/,
    APE_OBJECT_NUMBER/*variablesBytesFirst*/,
    APE_OBJECT_NUMBER/*dataBytesCount*/,
    APE_OBJECT_NUMBER/*data*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallSetProcedureParametersVariables")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Pointer(RedHandleProcedureParameters,    procedureParameters,        args[_i++]);
  getArgAs_Double(RedVisibleToStageBitflags,        visibleToStages,            args[_i++]);
  getArgAs_Double(unsigned,                         variablesBytesFirst,        args[_i++]);
  getArgAs_Double(unsigned,                         dataBytesCount,             args[_i++]);
  getArgAs_Pointer(const void *,                    _data,                      args[_i++]);
  getArgAs_END

  callProceduresAndAddresses->redCallSetProcedureParametersVariables(calls, procedureParameters, visibleToStages, variablesBytesFirst, dataBytesCount, _data);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallSetProcedureParametersStructs GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*procedureType*/,
    APE_OBJECT_NUMBER/*procedureParameters*/,
    APE_OBJECT_NUMBER/*procedureParametersDeclarationStructsDeclarationsFirst*/,
    APE_OBJECT_NUMBER/*structsCount*/,
    APE_OBJECT_NUMBER/*structs*/,
    APE_OBJECT_NUMBER/*setTo0*/,
    APE_OBJECT_NUMBER/*setTo00*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallSetProcedureParametersStructs")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses,                             args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                                                  args[_i++]);
  getArgAs_Double(RedProcedureType,                 procedureType,                                          args[_i++]);
  getArgAs_Pointer(RedHandleProcedureParameters,    procedureParameters,                                    args[_i++]);
  getArgAs_Double(unsigned,                         procedureParametersDeclarationStructsDeclarationsFirst, args[_i++]);
  getArgAs_Double(unsigned,                         structsCount,                                           args[_i++]);
  getArgAs_Pointer(const RedHandleStruct *,         structs,                                                args[_i++]);
  getArgAs_Double(unsigned,                         setTo0,                                                 args[_i++]);
  getArgAs_Double(size_t,                           setTo00,                                                args[_i++]);
  getArgAs_END

  callProceduresAndAddresses->redCallSetProcedureParametersStructs(calls, procedureType, procedureParameters, procedureParametersDeclarationStructsDeclarationsFirst, structsCount, structs, setTo0, setTo00);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallSetProcedureParametersHandles GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*procedureType*/,
    APE_OBJECT_NUMBER/*procedureParameters*/,
    APE_OBJECT_NUMBER/*procedureParametersDeclarationStructsDeclarationsCount*/,
    APE_OBJECT_NUMBER/*handlesCount*/,
    APE_OBJECT_NUMBER/*handles*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallSetProcedureParametersHandles")
  getArgAs_Pointer(RedCallProceduresAndAddresses *,      callProceduresAndAddresses,                             args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                       calls,                                                  args[_i++]);
  getArgAs_Double(RedProcedureType,                      procedureType,                                          args[_i++]);
  getArgAs_Pointer(RedHandleProcedureParameters,         procedureParameters,                                    args[_i++]);
  getArgAs_Double(unsigned,                              procedureParametersDeclarationStructsDeclarationsCount, args[_i++]);
  getArgAs_Double(unsigned,                              handlesCount,                                           args[_i++]);
  getArgAs_Pointer(const RedProcedureParametersHandle *, handles,                                                args[_i++]);
  getArgAs_END

  callProceduresAndAddresses->redCallSetProcedureParametersHandles(calls, procedureType, procedureParameters, procedureParametersDeclarationStructsDeclarationsCount, handlesCount, handles);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallSetDynamicDepthBias GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*constantFactor*/,
    APE_OBJECT_NUMBER/*clamp*/,
    APE_OBJECT_NUMBER/*slopeFactor*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallSetDynamicDepthBias")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Double(float,                            constantFactor,             args[_i++]);
  getArgAs_Double(float,                            clamp,                      args[_i++]);
  getArgAs_Double(float,                            slopeFactor,                args[_i++]);
  getArgAs_END

  callProceduresAndAddresses->redCallSetDynamicDepthBias(calls, constantFactor, clamp, slopeFactor);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallSetDynamicDepthBounds GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*min*/,
    APE_OBJECT_NUMBER/*max*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallSetDynamicDepthBounds")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Double(float,                            min,                        args[_i++]);
  getArgAs_Double(float,                            max,                        args[_i++]);
  getArgAs_END

  callProceduresAndAddresses->redCallSetDynamicDepthBounds(calls, min, max);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallSetDynamicStencilCompareMask GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*face*/,
    APE_OBJECT_NUMBER/*compareMask*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallSetDynamicStencilCompareMask")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Double(RedStencilFace,                   face,                       args[_i++]);
  getArgAs_Double(unsigned,                         compareMask,                args[_i++]);
  getArgAs_END

  callProceduresAndAddresses->redCallSetDynamicStencilCompareMask(calls, face, compareMask);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallSetDynamicStencilWriteMask GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*face*/,
    APE_OBJECT_NUMBER/*writeMask*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallSetDynamicStencilWriteMask")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Double(RedStencilFace,                   face,                       args[_i++]);
  getArgAs_Double(unsigned,                         writeMask,                  args[_i++]);
  getArgAs_END

  callProceduresAndAddresses->redCallSetDynamicStencilWriteMask(calls, face, writeMask);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallSetDynamicStencilReference GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*face*/,
    APE_OBJECT_NUMBER/*reference*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallSetDynamicStencilReference")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Double(RedStencilFace,                   face,                       args[_i++]);
  getArgAs_Double(unsigned,                         reference,                  args[_i++]);
  getArgAs_END

  callProceduresAndAddresses->redCallSetDynamicStencilReference(calls, face, reference);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallSetDynamicBlendConstants GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*blendConstants*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallSetDynamicBlendConstants")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Pointer(const float *,                   blendConstants,             args[_i++]);
  getArgAs_END

  callProceduresAndAddresses->redCallSetDynamicBlendConstants(calls, blendConstants);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallSetDynamicViewport GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*width*/,
    APE_OBJECT_NUMBER/*height*/,
    APE_OBJECT_NUMBER/*depthMin*/,
    APE_OBJECT_NUMBER/*depthMax*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallSetDynamicViewport")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Double(float,                            x,                          args[_i++]);
  getArgAs_Double(float,                            y,                          args[_i++]);
  getArgAs_Double(float,                            width,                      args[_i++]);
  getArgAs_Double(float,                            height,                     args[_i++]);
  getArgAs_Double(float,                            depthMin,                   args[_i++]);
  getArgAs_Double(float,                            depthMax,                   args[_i++]);
  getArgAs_END

  redCallSetDynamicViewport(callProceduresAndAddresses->redCallSetDynamicViewport, calls, x, y, width, height, depthMin, depthMax);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallSetDynamicScissor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*width*/,
    APE_OBJECT_NUMBER/*height*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallSetDynamicScissor")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Double(int,                              x,                          args[_i++]);
  getArgAs_Double(int,                              y,                          args[_i++]);
  getArgAs_Double(unsigned,                         width,                      args[_i++]);
  getArgAs_Double(unsigned,                         height,                     args[_i++]);
  getArgAs_END

  redCallSetDynamicScissor(callProceduresAndAddresses->redCallSetDynamicScissor, calls, x, y, width, height);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallSetStructsMemory GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*structsMemory*/,
    APE_OBJECT_NUMBER/*structsMemorySamplers*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallSetStructsMemory")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Pointer(RedHandleStructsMemory,          structsMemory,              args[_i++]);
  getArgAs_Pointer(RedHandleStructsMemory,          structsMemorySamplers,      args[_i++]);
  getArgAs_END

  redCallSetStructsMemory(callProceduresAndAddresses->redCallSetStructsMemory, calls, structsMemory, structsMemorySamplers);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallSetProcedureParameters GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*procedureType*/,
    APE_OBJECT_NUMBER/*procedureParameters*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallSetProcedureParameters")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Double(RedProcedureType,                 procedureType,              args[_i++]);
  getArgAs_Pointer(RedHandleProcedureParameters,    procedureParameters,        args[_i++]);
  getArgAs_END

  redCallSetProcedureParameters(callProceduresAndAddresses->redCallSetProcedureParameters, calls, procedureType, procedureParameters);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallSetProcedureOutput GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*outputDeclaration*/,
    APE_OBJECT_NUMBER/*output*/,
    APE_OBJECT_NUMBER/*inlineOutput*/,
    APE_OBJECT_NUMBER/*outputWidth*/,
    APE_OBJECT_NUMBER/*outputHeight*/,
    APE_OBJECT_BOOL/*outputDepthStencilEnable*/,
    APE_OBJECT_NUMBER/*outputColorsCount*/,
    APE_OBJECT_NUMBER/*depthClearValue*/,
    APE_OBJECT_NUMBER/*stencilClearValue*/,
    APE_OBJECT_NUMBER/*colorsClearValuesFloat*/,
    APE_OBJECT_NUMBER/*colorsClearValuesSint*/,
    APE_OBJECT_NUMBER/*colorsClearValuesUint*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallSetProcedureOutput")
  getArgAs_Pointer(RedCallProceduresAndAddresses *,   callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                    calls,                      args[_i++]);
  getArgAs_Pointer(RedHandleOutputDeclaration,        outputDeclaration,          args[_i++]);
  getArgAs_Pointer(RedHandleOutput,                   output,                     args[_i++]);
  getArgAs_Pointer(RedInlineOutput *,                 inlineOutput,               args[_i++]);
  getArgAs_Double(unsigned,                           outputWidth,                args[_i++]);
  getArgAs_Double(unsigned,                           outputHeight,               args[_i++]);
  getArgAs_Bool(RedBool32,                            outputDepthStencilEnable,   args[_i++]);
  getArgAs_Double(unsigned,                           outputColorsCount,          args[_i++]);
  getArgAs_Double(float,                              depthClearValue,            args[_i++]);
  getArgAs_Double(unsigned,                           stencilClearValue,          args[_i++]);
  getArgAs_Pointer(const RedColorsClearValuesFloat *, colorsClearValuesFloat,     args[_i++]);
  getArgAs_Pointer(const RedColorsClearValuesSint *,  colorsClearValuesSint,      args[_i++]);
  getArgAs_Pointer(const RedColorsClearValuesUint *,  colorsClearValuesUint,      args[_i++]);
  getArgAs_END

  redCallSetProcedureOutput(callProceduresAndAddresses->redCallSetProcedureOutput, calls, outputDeclaration, output, inlineOutput, outputWidth, outputHeight, outputDepthStencilEnable, outputColorsCount, depthClearValue, stencilClearValue, colorsClearValuesFloat, colorsClearValuesSint, colorsClearValuesUint);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallEndProcedureOutput GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallEndProcedureOutput")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_END

  redCallEndProcedureOutput(callProceduresAndAddresses->redCallEndProcedureOutput, calls);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallUsageAliasOrderBarrier GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*arrayUsagesCount*/,
    APE_OBJECT_NUMBER/*arrayUsages*/,
    APE_OBJECT_NUMBER/*imageUsagesCount*/,
    APE_OBJECT_NUMBER/*imageUsages*/,
    APE_OBJECT_NUMBER/*aliasesCount*/,
    APE_OBJECT_NUMBER/*aliases*/,
    APE_OBJECT_NUMBER/*ordersCount*/,
    APE_OBJECT_NUMBER/*orders*/,
    APE_OBJECT_BOOL/*dependencyByRegion*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallUsageAliasOrderBarrier")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_Pointer(RedContext,                      context,                    args[_i++]);
  getArgAs_Double(unsigned,                         arrayUsagesCount,           args[_i++]);
  getArgAs_Pointer(const RedUsageArray *,           arrayUsages,                args[_i++]);
  getArgAs_Double(unsigned,                         imageUsagesCount,           args[_i++]);
  getArgAs_Pointer(const RedUsageImage *,           imageUsages,                args[_i++]);
  getArgAs_Double(unsigned,                         aliasesCount,               args[_i++]);
  getArgAs_Pointer(const RedAlias *,                aliases,                    args[_i++]);
  getArgAs_Double(unsigned,                         ordersCount,                args[_i++]);
  getArgAs_Pointer(const RedOrder *,                orders,                     args[_i++]);
  getArgAs_Bool(RedBool32,                          dependencyByRegion,         args[_i++]);
  getArgAs_END

  redCallUsageAliasOrderBarrier(callProceduresAndAddresses->redCallUsageAliasOrderBarrier, calls, context, arrayUsagesCount, arrayUsages, imageUsagesCount, imageUsages, aliasesCount, aliases, ordersCount, orders, dependencyByRegion);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallMark GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_STRING/*mark*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallMark")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_CChars(const char *,                     mark,                       args[_i++]);
  getArgAs_END

  redCallMark(callProceduresAndAddresses->redCallMark, calls, mark);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallMarkSet GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_STRING/*mark*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallMarkSet")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_CChars(const char *,                     mark,                       args[_i++]);
  getArgAs_END

  redCallMarkSet(callProceduresAndAddresses->redCallMarkSet, calls, mark);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallMarkEnd GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*callProceduresAndAddresses*/,
    APE_OBJECT_NUMBER/*calls*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallMarkEnd")
  getArgAs_Pointer(RedCallProceduresAndAddresses *, callProceduresAndAddresses, args[_i++]);
  getArgAs_Pointer(RedHandleCalls,                  calls,                      args[_i++]);
  getArgAs_END

  redCallMarkEnd(callProceduresAndAddresses->redCallMarkEnd, calls);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedQueueSubmit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*queue*/,
    APE_OBJECT_NUMBER/*timelinesCount*/,
    APE_OBJECT_NUMBER/*timelines*/,
    APE_OBJECT_NUMBER/*signalCpuSignal*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redQueueSubmit")
  getArgAs_Pointer(RedContext,             context,         args[_i++]);
  getArgAs_Pointer(RedHandleGpu,           gpu,             args[_i++]);
  getArgAs_Pointer(RedHandleQueue,         queue,           args[_i++]);
  getArgAs_Double(unsigned,                timelinesCount,  args[_i++]);
  getArgAs_Pointer(const RedGpuTimeline *, timelines,       args[_i++]);
  getArgAs_Pointer(RedHandleCpuSignal,     signalCpuSignal, args[_i++]);
  getArgAs_Pointer(RedStatuses *,          outStatuses,     args[_i++]);
  getArgAs_END

  redQueueSubmit(context, gpu, queue, timelinesCount, timelines, signalCpuSignal, outStatuses, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedMark GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*mark*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redMark")
  getArgAs_CChars(const char *, mark, args[_i++]);
  getArgAs_END

  redMark(mark, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedMarkSet GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*mark*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redMarkSet")
  getArgAs_CChars(const char *, mark, args[_i++]);
  getArgAs_END

  redMarkSet(mark, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedMarkEnd GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  redMarkEnd(0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateProcedureComputingLanguage GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*procedureCache*/,
    APE_OBJECT_NUMBER/*procedureParameters*/,
    APE_OBJECT_STRING/*gpuCodeMainProcedureName*/,
    APE_OBJECT_NUMBER/*gpuCode*/,
    APE_OBJECT_NUMBER/*stateExtension*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateProcedureComputingLanguage")
  getArgAs_Pointer(RedContext,                   context,                  args[_i++]);
  getArgAs_Pointer(RedHandleGpu,                 gpu,                      args[_i++]);
  getArgAs_CChars(const char *,                  handleName,               args[_i++]);
  getArgAs_Pointer(RedHandleProcedureCache,      procedureCache,           args[_i++]);
  getArgAs_Pointer(RedHandleProcedureParameters, procedureParameters,      args[_i++]);
  getArgAs_CChars(const char *,                  gpuCodeMainProcedureName, args[_i++]);
  getArgAs_Pointer(RedHandleGpuCode,             gpuCode,                  args[_i++]);
  getArgAs_Pointer(const void *,                 stateExtension,           args[_i++]);
  getArgAs_Pointer(RedStatuses *,                outStatuses,              args[_i++]);
  getArgAs_END

  RedHandleProcedure handle = 0;
  redCreateProcedureComputingLanguage(context, gpu, handleName, procedureCache, procedureParameters, gpuCodeMainProcedureName, gpuCode, stateExtension, &handle, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCreateArrayTimestamp GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_STRING/*handleName*/,
    APE_OBJECT_NUMBER/*count*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCreateArrayTimestamp")
  getArgAs_Pointer(RedContext,    context,     args[_i++]);
  getArgAs_Pointer(RedHandleGpu,  gpu,         args[_i++]);
  getArgAs_CChars(const char *,   handleName,  args[_i++]);
  getArgAs_Double(unsigned,       count,       args[_i++]);
  getArgAs_Pointer(RedStatuses *, outStatuses, args[_i++]);
  getArgAs_END

  RedHandleArrayTimestamp handle = 0;
  redCreateArrayTimestamp(context, gpu, handleName, count, &handle, outStatuses, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedDestroyArrayTimestamp GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*arrayTimestamp*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redDestroyArrayTimestamp")
  getArgAs_Pointer(RedContext,              context, args[_i++]);
  getArgAs_Pointer(RedHandleGpu,            gpu,     args[_i++]);
  getArgAs_Pointer(RedHandleArrayTimestamp, handle,  args[_i++]);
  getArgAs_END

  redDestroyArrayTimestamp(context, gpu, handle, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedCallArrayTimestampWrite GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*calls*/,
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*arrayTimestamp*/,
    APE_OBJECT_NUMBER/*index*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redCallArrayTimestampWrite")
  getArgAs_Pointer(RedHandleCalls,          calls,          args[_i++]);
  getArgAs_Pointer(RedContext,              context,        args[_i++]);
  getArgAs_Pointer(RedHandleArrayTimestamp, arrayTimestamp, args[_i++]);
  getArgAs_Double(unsigned,                 index,          args[_i++]);
  getArgAs_END

  redCallArrayTimestampWrite(calls, context, arrayTimestamp, index);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRedArrayTimestampRead GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*gpu*/,
    APE_OBJECT_NUMBER/*arrayTimestamp*/,
    APE_OBJECT_NUMBER/*rangeFirst*/,
    APE_OBJECT_NUMBER/*rangeCount*/,
    APE_OBJECT_NUMBER/*out64BitTicksCounts*/,
    APE_OBJECT_NUMBER/*outStatuses*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("redArrayTimestampRead")
  getArgAs_Pointer(RedContext,              context,             args[_i++]);
  getArgAs_Pointer(RedHandleGpu,            gpu,                 args[_i++]);
  getArgAs_Pointer(RedHandleArrayTimestamp, arrayTimestamp,      args[_i++]);
  getArgAs_Double(unsigned,                 rangeFirst,          args[_i++]);
  getArgAs_Double(unsigned,                 rangeCount,          args[_i++]);
  getArgAs_Pointer(void *,                  out64BitTicksCounts, args[_i++]);
  getArgAs_Pointer(RedStatuses *,           outStatuses,         args[_i++]);
  getArgAs_END

  redArrayTimestampRead(context, gpu, arrayTimestamp, rangeFirst, rangeCount, out64BitTicksCounts, outStatuses, 0, 0, 0);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetRrtStructsCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  uint64_t count = 0;

#define GS_MACRO_RRT_STRUCT(STRUCTURE) count += 1;

  GS_MACRO_RRT_STRUCT(RRRay)
  GS_MACRO_RRT_STRUCT(RRHit)
  GS_MACRO_RRT_STRUCT(RRBuildOptions)
  GS_MACRO_RRT_STRUCT(RRTriangleMeshPrimitive)
  GS_MACRO_RRT_STRUCT(RRAABBListPrimitive)
  GS_MACRO_RRT_STRUCT(RRGeometryBuildInput)
  GS_MACRO_RRT_STRUCT(RRInstance)
  GS_MACRO_RRT_STRUCT(RRSceneBuildInput)
  GS_MACRO_RRT_STRUCT(RRMemoryRequirements)

#undef GS_MACRO_RRT_STRUCT

  return ape_object_make_number((double)count);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetRrtStructName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*index*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("getRrtStructName")
  getArgAs_Double(uint64_t, index, args[_i++]);
  getArgAs_END

  uint64_t count = 0;

#define GS_MACRO_RRT_STRUCT(STRUCTURE) \
  if (index == count) { \
    return ape_object_make_string(ape, #STRUCTURE); \
  } \
  count += 1;

  GS_MACRO_RRT_STRUCT(RRRay)
  GS_MACRO_RRT_STRUCT(RRHit)
  GS_MACRO_RRT_STRUCT(RRBuildOptions)
  GS_MACRO_RRT_STRUCT(RRTriangleMeshPrimitive)
  GS_MACRO_RRT_STRUCT(RRAABBListPrimitive)
  GS_MACRO_RRT_STRUCT(RRGeometryBuildInput)
  GS_MACRO_RRT_STRUCT(RRInstance)
  GS_MACRO_RRT_STRUCT(RRSceneBuildInput)
  GS_MACRO_RRT_STRUCT(RRMemoryRequirements)

#undef GS_MACRO_RRT_STRUCT

  return ape_object_make_string(ape, "");
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtStructSizeof GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*structName*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtStructSizeof")
  getArgAs_CChars(const char *, structName, args[_i++]);
  getArgAs_END

  const size_t structNameBytesCount = strlen(structName) + 1;

#define GS_MACRO_RRT_STRUCT(STRUCTURE) \
  if (structNameBytesCount == sizeof(#STRUCTURE)) { \
    if (memcmp(structName, #STRUCTURE, structNameBytesCount) == 0) { \
      return ape_object_make_number((double)sizeof(STRUCTURE)); \
    } \
  }

  GS_MACRO_RRT_STRUCT(RRRay)
  GS_MACRO_RRT_STRUCT(RRHit)
  GS_MACRO_RRT_STRUCT(RRBuildOptions)
  GS_MACRO_RRT_STRUCT(RRTriangleMeshPrimitive)
  GS_MACRO_RRT_STRUCT(RRAABBListPrimitive)
  GS_MACRO_RRT_STRUCT(RRGeometryBuildInput)
  GS_MACRO_RRT_STRUCT(RRInstance)
  GS_MACRO_RRT_STRUCT(RRSceneBuildInput)
  GS_MACRO_RRT_STRUCT(RRMemoryRequirements)

#undef GS_MACRO_RRT_STRUCT

  return ape_object_make_number((double)((uint64_t)-1));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetRrtStructMembersCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  uint64_t count = 0;

#define GS_MACRO_RRT_STRUCT_MEMBER(GS_TYPE, TYPE, STRUCTURE, MEMBER) count += 1;

  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, origin)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, min_t)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, direction)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, max_t)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRHit, uv)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRHit, inst_id)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRHit, prim_id)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RRBuildFlags, RRBuildOptions, build_flags)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, void *, RRBuildOptions, backend_specific_info)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRTriangleMeshPrimitive, vertices)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRTriangleMeshPrimitive, vertex_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRTriangleMeshPrimitive, vertex_stride)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRTriangleMeshPrimitive, triangle_indices)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRTriangleMeshPrimitive, triangle_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RRIndexType, RRTriangleMeshPrimitive, index_type)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRAABBListPrimitive, aabbs)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRAABBListPrimitive, aabb_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRAABBListPrimitive, aabb_stride)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RRPrimitiveType, RRGeometryBuildInput, primitive_type)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRGeometryBuildInput, primitive_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRTriangleMeshPrimitive *, RRGeometryBuildInput, triangle_mesh_primitives)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRAABBListPrimitive *, RRGeometryBuildInput, aabb_primitives)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRInstance, geometry)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRInstance, transform)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RRInstance *, RRSceneBuildInput, instances)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRSceneBuildInput, instance_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RRMemoryRequirements, temporary_build_buffer_size)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RRMemoryRequirements, temporary_update_buffer_size)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RRMemoryRequirements, result_buffer_size)

#undef GS_MACRO_RRT_STRUCT_MEMBER

  return ape_object_make_number((double)count);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetRrtStructMemberName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*index*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("getRrtStructMemberName")
  getArgAs_Double(uint64_t, index, args[_i++]);
  getArgAs_END

  uint64_t count = 0;

#define GS_MACRO_RRT_STRUCT_MEMBER(GS_TYPE, TYPE, STRUCTURE, MEMBER) \
  if (index == count) { \
    return ape_object_make_string(ape, #STRUCTURE "." #MEMBER); \
  } \
  count += 1;

  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, origin)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, min_t)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, direction)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, max_t)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRHit, uv)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRHit, inst_id)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRHit, prim_id)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RRBuildFlags, RRBuildOptions, build_flags)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, void *, RRBuildOptions, backend_specific_info)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRTriangleMeshPrimitive, vertices)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRTriangleMeshPrimitive, vertex_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRTriangleMeshPrimitive, vertex_stride)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRTriangleMeshPrimitive, triangle_indices)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRTriangleMeshPrimitive, triangle_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RRIndexType, RRTriangleMeshPrimitive, index_type)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRAABBListPrimitive, aabbs)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRAABBListPrimitive, aabb_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRAABBListPrimitive, aabb_stride)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RRPrimitiveType, RRGeometryBuildInput, primitive_type)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRGeometryBuildInput, primitive_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRTriangleMeshPrimitive *, RRGeometryBuildInput, triangle_mesh_primitives)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRAABBListPrimitive *, RRGeometryBuildInput, aabb_primitives)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRInstance, geometry)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRInstance, transform)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RRInstance *, RRSceneBuildInput, instances)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRSceneBuildInput, instance_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RRMemoryRequirements, temporary_build_buffer_size)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RRMemoryRequirements, temporary_update_buffer_size)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RRMemoryRequirements, result_buffer_size)

#undef GS_MACRO_RRT_STRUCT_MEMBER

  return ape_object_make_string(ape, "");
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtStructMemberSizeof GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*structName*/,
    APE_OBJECT_STRING/*structMemberName*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtStructMemberSizeof")
  getArgAs_CChars(const char *, structName, args[_i++]);
  getArgAs_CChars(const char *, memberName, args[_i++]);
  getArgAs_END

  const size_t structNameBytesCount = strlen(structName) + 1;
  const size_t memberNameBytesCount = strlen(memberName) + 1;

#define GS_MACRO_RRT_STRUCT_MEMBER(GS_TYPE, TYPE, STRUCTURE, MEMBER) \
  if (structNameBytesCount == sizeof(#STRUCTURE)) { \
    if (memberNameBytesCount == sizeof(#MEMBER)) { \
      if (memcmp(structName, #STRUCTURE, structNameBytesCount) == 0) { \
        if (memcmp(memberName, #MEMBER, memberNameBytesCount) == 0) { \
          return ape_object_make_number((double)sizeof(((STRUCTURE *)0)->MEMBER)); \
        } \
      } \
    } \
  }

  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, origin)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, min_t)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, direction)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, max_t)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRHit, uv)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRHit, inst_id)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRHit, prim_id)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RRBuildFlags, RRBuildOptions, build_flags)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, void *, RRBuildOptions, backend_specific_info)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRTriangleMeshPrimitive, vertices)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRTriangleMeshPrimitive, vertex_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRTriangleMeshPrimitive, vertex_stride)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRTriangleMeshPrimitive, triangle_indices)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRTriangleMeshPrimitive, triangle_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RRIndexType, RRTriangleMeshPrimitive, index_type)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRAABBListPrimitive, aabbs)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRAABBListPrimitive, aabb_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRAABBListPrimitive, aabb_stride)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RRPrimitiveType, RRGeometryBuildInput, primitive_type)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRGeometryBuildInput, primitive_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRTriangleMeshPrimitive *, RRGeometryBuildInput, triangle_mesh_primitives)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRAABBListPrimitive *, RRGeometryBuildInput, aabb_primitives)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRInstance, geometry)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRInstance, transform)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RRInstance *, RRSceneBuildInput, instances)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRSceneBuildInput, instance_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RRMemoryRequirements, temporary_build_buffer_size)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RRMemoryRequirements, temporary_update_buffer_size)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RRMemoryRequirements, result_buffer_size)

#undef GS_MACRO_RRT_STRUCT_MEMBER

  return ape_object_make_number((double)((uint64_t)-1));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtStructMemberOffsetof GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*structName*/,
    APE_OBJECT_STRING/*structMemberName*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtStructMemberOffsetof")
  getArgAs_CChars(const char *, structName, args[_i++]);
  getArgAs_CChars(const char *, memberName, args[_i++]);
  getArgAs_END

  const size_t structNameBytesCount = strlen(structName) + 1;
  const size_t memberNameBytesCount = strlen(memberName) + 1;

#define GS_MACRO_RRT_STRUCT_MEMBER(GS_TYPE, TYPE, STRUCTURE, MEMBER) \
  if (structNameBytesCount == sizeof(#STRUCTURE)) { \
    if (memberNameBytesCount == sizeof(#MEMBER)) { \
      if (memcmp(structName, #STRUCTURE, structNameBytesCount) == 0) { \
        if (memcmp(memberName, #MEMBER, memberNameBytesCount) == 0) { \
          return ape_object_make_number((double)offsetof(STRUCTURE, MEMBER)); \
        } \
      } \
    } \
  }

  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, origin)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, min_t)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, direction)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, max_t)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRHit, uv)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRHit, inst_id)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRHit, prim_id)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RRBuildFlags, RRBuildOptions, build_flags)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, void *, RRBuildOptions, backend_specific_info)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRTriangleMeshPrimitive, vertices)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRTriangleMeshPrimitive, vertex_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRTriangleMeshPrimitive, vertex_stride)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRTriangleMeshPrimitive, triangle_indices)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRTriangleMeshPrimitive, triangle_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RRIndexType, RRTriangleMeshPrimitive, index_type)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRAABBListPrimitive, aabbs)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRAABBListPrimitive, aabb_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRAABBListPrimitive, aabb_stride)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RRPrimitiveType, RRGeometryBuildInput, primitive_type)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRGeometryBuildInput, primitive_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRTriangleMeshPrimitive *, RRGeometryBuildInput, triangle_mesh_primitives)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRAABBListPrimitive *, RRGeometryBuildInput, aabb_primitives)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRInstance, geometry)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRInstance, transform)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RRInstance *, RRSceneBuildInput, instances)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRSceneBuildInput, instance_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RRMemoryRequirements, temporary_build_buffer_size)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RRMemoryRequirements, temporary_update_buffer_size)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RRMemoryRequirements, result_buffer_size)

#undef GS_MACRO_RRT_STRUCT_MEMBER

  return ape_object_make_number((double)((uint64_t)-1));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtStructMemberTypeof GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*structName*/,
    APE_OBJECT_STRING/*structMemberName*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtStructMemberTypeof")
  getArgAs_CChars(const char *, structName, args[_i++]);
  getArgAs_CChars(const char *, memberName, args[_i++]);
  getArgAs_END

  const size_t structNameBytesCount = strlen(structName) + 1;
  const size_t memberNameBytesCount = strlen(memberName) + 1;

#define GS_MACRO_RRT_STRUCT_MEMBER(GS_TYPE, TYPE, STRUCTURE, MEMBER) \
  if (structNameBytesCount == sizeof(#STRUCTURE)) { \
    if (memberNameBytesCount == sizeof(#MEMBER)) { \
      if (memcmp(structName, #STRUCTURE, structNameBytesCount) == 0) { \
        if (memcmp(memberName, #MEMBER, memberNameBytesCount) == 0) { \
          return ape_object_make_number((double)GS_TYPE); \
        } \
      } \
    } \
  }

  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, origin)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, min_t)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, direction)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRRay, max_t)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRHit, uv)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRHit, inst_id)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRHit, prim_id)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RRBuildFlags, RRBuildOptions, build_flags)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, void *, RRBuildOptions, backend_specific_info)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRTriangleMeshPrimitive, vertices)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRTriangleMeshPrimitive, vertex_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRTriangleMeshPrimitive, vertex_stride)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRTriangleMeshPrimitive, triangle_indices)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRTriangleMeshPrimitive, triangle_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RRIndexType, RRTriangleMeshPrimitive, index_type)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRAABBListPrimitive, aabbs)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRAABBListPrimitive, aabb_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRAABBListPrimitive, aabb_stride)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RRPrimitiveType, RRGeometryBuildInput, primitive_type)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRGeometryBuildInput, primitive_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRTriangleMeshPrimitive *, RRGeometryBuildInput, triangle_mesh_primitives)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRAABBListPrimitive *, RRGeometryBuildInput, aabb_primitives)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, RRDevicePtr, RRInstance, geometry)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, RRInstance, transform)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RRInstance *, RRSceneBuildInput, instances)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, uint32_t, RRSceneBuildInput, instance_count)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RRMemoryRequirements, temporary_build_buffer_size)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RRMemoryRequirements, temporary_update_buffer_size)
  GS_MACRO_RRT_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RRMemoryRequirements, result_buffer_size)

#undef GS_MACRO_RRT_STRUCT_MEMBER

  return ape_object_make_number(0.0);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtCreateContext GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*apiVersion*/,
    APE_OBJECT_NUMBER/*api*/,
    APE_OBJECT_NUMBER/*outContext*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtCreateContext")
  getArgAs_Double(uint32_t,     apiVersion, args[_i++]);
  getArgAs_Double(RRApi,        api,        args[_i++]);
  getArgAs_Pointer(RRContext *, outContext, args[_i++]);
  getArgAs_END

  RRError status = rrCreateContext(apiVersion, api, outContext);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtDestroyContext GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtDestroyContext")
  getArgAs_Pointer(RRContext, context, args[_i++]);
  getArgAs_END

  RRError status = rrDestroyContext(context);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtSetLogLevel GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*logLevel*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtSetLogLevel")
  getArgAs_Double(RRLogLevel, logLevel, args[_i++]);
  getArgAs_END

  RRError status = rrSetLogLevel(logLevel);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtSetLogFile GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*filename*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtSetLogFile")
  getArgAs_CChars(const char *, filename, args[_i++]);
  getArgAs_END

  RRError status = rrSetLogFile(filename);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtCmdBuildGeometry GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*buildOperation*/,
    APE_OBJECT_NUMBER/*buildInput*/,
    APE_OBJECT_NUMBER/*buildOptions*/,
    APE_OBJECT_NUMBER/*temporaryBuffer*/,
    APE_OBJECT_NUMBER/*geometryBuffer*/,
    APE_OBJECT_NUMBER/*commandStream*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtCmdBuildGeometry")
  getArgAs_Pointer(RRContext,                    context,         args[_i++]);
  getArgAs_Double(RRBuildOperation,              buildOperation,  args[_i++]);
  getArgAs_Pointer(const RRGeometryBuildInput *, buildInput,      args[_i++]);
  getArgAs_Pointer(const RRBuildOptions *,       buildOptions,    args[_i++]);
  getArgAs_Pointer(RRDevicePtr,                  temporaryBuffer, args[_i++]);
  getArgAs_Pointer(RRDevicePtr,                  geometryBuffer,  args[_i++]);
  getArgAs_Pointer(RRCommandStream,              commandStream,   args[_i++]);
  getArgAs_END

  RRError status = rrCmdBuildGeometry(context, buildOperation, buildInput, buildOptions, temporaryBuffer, geometryBuffer, commandStream);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtGetGeometryBuildMemoryRequirements GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*buildInput*/,
    APE_OBJECT_NUMBER/*buildOptions*/,
    APE_OBJECT_NUMBER/*outMemoryRequirements*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtGetGeometryBuildMemoryRequirements")
  getArgAs_Pointer(RRContext,                    context,               args[_i++]);
  getArgAs_Pointer(const RRGeometryBuildInput *, buildInput,            args[_i++]);
  getArgAs_Pointer(const RRBuildOptions *,       buildOptions,          args[_i++]);
  getArgAs_Pointer(RRMemoryRequirements *,       outMemoryRequirements, args[_i++]);
  getArgAs_END

  RRError status = rrGetGeometryBuildMemoryRequirements(context, buildInput, buildOptions, outMemoryRequirements);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtCmdBuildScene GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*buildInput*/,
    APE_OBJECT_NUMBER/*buildOptions*/,
    APE_OBJECT_NUMBER/*temporaryBuffer*/,
    APE_OBJECT_NUMBER/*sceneBuffer*/,
    APE_OBJECT_NUMBER/*commandStream*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtCmdBuildScene")
  getArgAs_Pointer(RRContext,                 context,         args[_i++]);
  getArgAs_Pointer(const RRSceneBuildInput *, buildInput,      args[_i++]);
  getArgAs_Pointer(const RRBuildOptions *,    buildOptions,    args[_i++]);
  getArgAs_Pointer(RRDevicePtr,               temporaryBuffer, args[_i++]);
  getArgAs_Pointer(RRDevicePtr,               sceneBuffer,     args[_i++]);
  getArgAs_Pointer(RRCommandStream,           commandStream,   args[_i++]);
  getArgAs_END

  RRError status = rrCmdBuildScene(context, buildInput, buildOptions, temporaryBuffer, sceneBuffer, commandStream);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtGetSceneBuildMemoryRequirements GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*buildInput*/,
    APE_OBJECT_NUMBER/*buildOptions*/,
    APE_OBJECT_NUMBER/*outMemoryRequirements*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtGetSceneBuildMemoryRequirements")
  getArgAs_Pointer(RRContext,                 context,               args[_i++]);
  getArgAs_Pointer(const RRSceneBuildInput *, buildInput,            args[_i++]);
  getArgAs_Pointer(const RRBuildOptions *,    buildOptions,          args[_i++]);
  getArgAs_Pointer(RRMemoryRequirements *,    outMemoryRequirements, args[_i++]);
  getArgAs_END

  RRError status = rrGetSceneBuildMemoryRequirements(context, buildInput, buildOptions, outMemoryRequirements);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtCmdIntersect GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*sceneBuffer*/,
    APE_OBJECT_NUMBER/*query*/,
    APE_OBJECT_NUMBER/*rays*/,
    APE_OBJECT_NUMBER/*rayCount*/,
    APE_OBJECT_NUMBER/*indirectRayCount*/,
    APE_OBJECT_NUMBER/*queryOutput*/,
    APE_OBJECT_NUMBER/*hits*/,
    APE_OBJECT_NUMBER/*scratch*/,
    APE_OBJECT_NUMBER/*commandStream*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtCmdIntersect")
  getArgAs_Pointer(RRContext,             context,          args[_i++]);
  getArgAs_Pointer(RRDevicePtr,           sceneBuffer,      args[_i++]);
  getArgAs_Double(RRIntersectQuery,       query,            args[_i++]);
  getArgAs_Pointer(RRDevicePtr,           rays,             args[_i++]);
  getArgAs_Double(uint32_t,               rayCount,         args[_i++]);
  getArgAs_Pointer(RRDevicePtr,           indirectRayCount, args[_i++]);
  getArgAs_Double(RRIntersectQueryOutput, queryOutput,      args[_i++]);
  getArgAs_Pointer(RRDevicePtr,           hits,             args[_i++]);
  getArgAs_Pointer(RRDevicePtr,           scratch,          args[_i++]);
  getArgAs_Pointer(RRCommandStream,       commandStream,    args[_i++]);
  getArgAs_END

  RRError status = rrCmdIntersect(context, sceneBuffer, query, rays, rayCount, indirectRayCount, queryOutput, hits, scratch, commandStream);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtGetTraceMemoryRequirements GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*rayCount*/,
    APE_OBJECT_NUMBER/*outScratchSize*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtGetTraceMemoryRequirements")
  getArgAs_Pointer(RRContext, context,        args[_i++]);
  getArgAs_Double(uint32_t,   rayCount,       args[_i++]);
  getArgAs_Pointer(size_t *,  outScratchSize, args[_i++]);
  getArgAs_END

  RRError status = rrGetTraceMemoryRequirements(context, rayCount, outScratchSize);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtAllocateCommandStream GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*outCommandStream*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtAllocateCommandStream")
  getArgAs_Pointer(RRContext,         context,          args[_i++]);
  getArgAs_Pointer(RRCommandStream *, outCommandStream, args[_i++]);
  getArgAs_END

  RRError status = rrAllocateCommandStream(context, outCommandStream);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtReleaseCommandStream GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*commandStream*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtReleaseCommandStream")
  getArgAs_Pointer(RRContext,       context,       args[_i++]);
  getArgAs_Pointer(RRCommandStream, commandStream, args[_i++]);
  getArgAs_END

  RRError status = rrReleaseCommandStream(context, commandStream);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtSumbitCommandStream GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*commandStream*/,
    APE_OBJECT_NUMBER/*waitEvent*/,
    APE_OBJECT_NUMBER/*outEvent*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtSumbitCommandStream")
  getArgAs_Pointer(RRContext,       context,       args[_i++]);
  getArgAs_Pointer(RRCommandStream, commandStream, args[_i++]);
  getArgAs_Pointer(RREvent,         waitEvent,     args[_i++]);
  getArgAs_Pointer(RREvent *,       outEvent,      args[_i++]);
  getArgAs_END

  RRError status = rrSumbitCommandStream(context, commandStream, waitEvent, outEvent);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtReleaseEvent GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*event*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtReleaseEvent")
  getArgAs_Pointer(RRContext, context, args[_i++]);
  getArgAs_Pointer(RREvent,   event,   args[_i++]);
  getArgAs_END

  RRError status = rrReleaseEvent(context, event);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtWaitEvent GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*event*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtWaitEvent")
  getArgAs_Pointer(RRContext, context, args[_i++]);
  getArgAs_Pointer(RREvent,   event,   args[_i++]);
  getArgAs_END

  RRError status = rrWaitEvent(context, event);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtReleaseDevicePtr GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*devicePointer*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtReleaseDevicePtr")
  getArgAs_Pointer(RRContext,   context,       args[_i++]);
  getArgAs_Pointer(RRDevicePtr, devicePointer, args[_i++]);
  getArgAs_END

  RRError status = rrReleaseDevicePtr(context, devicePointer);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtReleaseExternalCommandStream GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*commandStream*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtReleaseExternalCommandStream")
  getArgAs_Pointer(RRContext,       context,       args[_i++]);
  getArgAs_Pointer(RRCommandStream, commandStream, args[_i++]);
  getArgAs_END

  RRError status = rrReleaseExternalCommandStream(context, commandStream);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtGetDevicePtrFromVkBuffer GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*resource*/,
    APE_OBJECT_NUMBER/*offset*/,
    APE_OBJECT_NUMBER/*outDevicePointer*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtGetDevicePtrFromVkBuffer")
  getArgAs_Pointer(RRContext,      context,          args[_i++]);
  getArgAs_Pointer(RedHandleArray, resource,         args[_i++]);
  getArgAs_Double(size_t,          offset,           args[_i++]);
  getArgAs_Pointer(RRDevicePtr *,  outDevicePointer, args[_i++]);
  getArgAs_END

  RRError status = rrGetDevicePtrFromVkBuffer(context, resource, offset, outDevicePointer);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtCreateContextVk GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*apiVersion*/,
    APE_OBJECT_NUMBER/*device*/,
    APE_OBJECT_NUMBER/*physicalDevice*/,
    APE_OBJECT_NUMBER/*commandQueue*/,
    APE_OBJECT_NUMBER/*queueFamilyIndex*/,
    APE_OBJECT_NUMBER/*outContext*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtCreateContextVk")
  getArgAs_Double(uint32_t,            apiVersion,       args[_i++]);
  getArgAs_Pointer(RedHandleGpu,       device,           args[_i++]);
  getArgAs_Pointer(RedHandleGpuDevice, physicalDevice,   args[_i++]);
  getArgAs_Pointer(RedHandleQueue,     commandQueue,     args[_i++]);
  getArgAs_Double(uint32_t,            queueFamilyIndex, args[_i++]);
  getArgAs_Pointer(RRContext *,        outContext,       args[_i++]);
  getArgAs_END

  RRError status = rrCreateContextVk(apiVersion, device, physicalDevice, commandQueue, queueFamilyIndex, outContext);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtGetCommandStreamFromVkCommandBuffer GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*commandBuffer*/,
    APE_OBJECT_NUMBER/*outCommandStream*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtGetCommandStreamFromVkCommandBuffer")
  getArgAs_Pointer(RRContext,         context,          args[_i++]);
  getArgAs_Pointer(RedHandleCalls,    commandBuffer,    args[_i++]);
  getArgAs_Pointer(RRCommandStream *, outCommandStream, args[_i++]);
  getArgAs_END

  RRError status = rrGetCommandStreamFromVkCommandBuffer(context, commandBuffer, outCommandStream);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtAllocateDeviceBuffer GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*size*/,
    APE_OBJECT_NUMBER/*outDevicePointer*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtAllocateDeviceBuffer")
  getArgAs_Pointer(RRContext,     context,          args[_i++]);
  getArgAs_Double(size_t,         size,             args[_i++]);
  getArgAs_Pointer(RRDevicePtr *, outDevicePointer, args[_i++]);
  getArgAs_END

  RRError status = rrAllocateDeviceBuffer(context, size, outDevicePointer);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtMapDevicePtr GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*devicePointer*/,
    APE_OBJECT_NUMBER/*outMappingPointer*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtMapDevicePtr")
  getArgAs_Pointer(RRContext,   context,           args[_i++]);
  getArgAs_Pointer(RRDevicePtr, devicePointer,     args[_i++]);
  getArgAs_Pointer(void **,     outMappingPointer, args[_i++]);
  getArgAs_END

  RRError status = rrMapDevicePtr(context, devicePointer, outMappingPointer);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureRrtUnmapDevicePtr GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*context*/,
    APE_OBJECT_NUMBER/*devicePointer*/,
    APE_OBJECT_NUMBER/*outMappingPointer*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("rrtUnmapDevicePtr")
  getArgAs_Pointer(RRContext,   context,           args[_i++]);
  getArgAs_Pointer(RRDevicePtr, devicePointer,     args[_i++]);
  getArgAs_Pointer(void **,     outMappingPointer, args[_i++]);
  getArgAs_END

  RRError status = rrUnmapDevicePtr(context, devicePointer, outMappingPointer);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesGetCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)gApeMeshes.size());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesPersistentGetCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)gApeMeshesPersistent.size());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesGetMeshLabelByMeshIndex GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*index*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalMeshesGetMeshLabelByMeshIndex")
  getArgAs_Double(uint64_t, index, args[_i++]);
  getArgAs_END

  auto e = gApeMeshes.begin();
  for (uint64_t i = 0; i < index; i += 1) {
    ++e;
  }

  return ape_object_make_string(ape, e->first.c_str());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesPersistentGetMeshLabelByMeshIndex GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*index*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalMeshesPersistentGetMeshLabelByMeshIndex")
  getArgAs_Double(uint64_t, index, args[_i++]);
  getArgAs_END

  auto e = gApeMeshesPersistent.begin();
  for (uint64_t i = 0; i < index; i += 1) {
    ++e;
  }

  return ape_object_make_string(ape, e->first.c_str());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesGetMeshHandleByMeshIndex GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*index*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalMeshesGetMeshHandleByMeshIndex")
  getArgAs_Double(uint64_t, index, args[_i++]);
  getArgAs_END

  auto e = gApeMeshes.begin();
  for (uint64_t i = 0; i < index; i += 1) {
    ++e;
  }

  return ape_object_make_number(_gsPointerToNumber((void *)e->second));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesPersistentGetMeshHandleByMeshIndex GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*index*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalMeshesPersistentGetMeshHandleByMeshIndex")
  getArgAs_Double(uint64_t, index, args[_i++]);
  getArgAs_END

  auto e = gApeMeshesPersistent.begin();
  for (uint64_t i = 0; i < index; i += 1) {
    ++e;
  }

  return ape_object_make_number(_gsPointerToNumber((void *)e->second));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesGetHaveVerticesChangedMeshIndexesCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  uint64_t count = 0;

  for (auto & e : gApeMeshes) {
    if (redFMeshHaveVertsChanged(e.second[0]) == 1) {
      count += 1;
    }
  }

  return ape_object_make_number((double)count);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesGetHaveColorsChangedMeshIndexesCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  uint64_t count = 0;

  for (auto & e : gApeMeshes) {
    if (redFMeshHaveColorsChanged(e.second[0]) == 1) {
      count += 1;
    }
  }

  return ape_object_make_number((double)count);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesGetHaveTexCoordsChangedMeshIndexesCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  uint64_t count = 0;

  for (auto & e : gApeMeshes) {
    if (redFMeshHaveTexCoordsChanged(e.second[0]) == 1) {
      count += 1;
    }
  }

  return ape_object_make_number((double)count);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesGetHaveIndicesChangedMeshIndexesCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  uint64_t count = 0;

  for (auto & e : gApeMeshes) {
    if (redFMeshHaveIndicesChanged(e.second[0]) == 1) {
      count += 1;
    }
  }

  return ape_object_make_number((double)count);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesPersistentGetHaveVerticesChangedMeshIndexesCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  uint64_t count = 0;

  for (auto & e : gApeMeshesPersistent) {
    if (redFMeshHaveVertsChanged(e.second[0]) == 1) {
      count += 1;
    }
  }

  return ape_object_make_number((double)count);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesPersistentGetHaveColorsChangedMeshIndexesCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  uint64_t count = 0;

  for (auto & e : gApeMeshesPersistent) {
    if (redFMeshHaveColorsChanged(e.second[0]) == 1) {
      count += 1;
    }
  }

  return ape_object_make_number((double)count);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesPersistentGetHaveTexCoordsChangedMeshIndexesCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  uint64_t count = 0;

  for (auto & e : gApeMeshesPersistent) {
    if (redFMeshHaveTexCoordsChanged(e.second[0]) == 1) {
      count += 1;
    }
  }

  return ape_object_make_number((double)count);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesPersistentGetHaveIndicesChangedMeshIndexesCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  uint64_t count = 0;

  for (auto & e : gApeMeshesPersistent) {
    if (redFMeshHaveIndicesChanged(e.second[0]) == 1) {
      count += 1;
    }
  }

  return ape_object_make_number((double)count);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesGetHaveVerticesChangedMeshIndexes GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*count*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalMeshesGetHaveVerticesChangedMeshIndexes")
  getArgAs_Double(uint64_t, count, args[_i++]);
  getArgAs_END

  ape_object_t array = mape_object_make_array(ape, count);
  uint64_t i = 0;
  uint64_t j = 0;
  for (auto & e : gApeMeshes) {
    if (redFMeshHaveVertsChanged(e.second[0]) == 1) {
      mape_object_add_array_number(i, array, (double)j);
      i += 1;
    }
    j += 1;
  }
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesGetHaveColorsChangedMeshIndexes GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*count*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalMeshesGetHaveColorsChangedMeshIndexes")
  getArgAs_Double(uint64_t, count, args[_i++]);
  getArgAs_END

  ape_object_t array = mape_object_make_array(ape, count);
  uint64_t i = 0;
  uint64_t j = 0;
  for (auto & e : gApeMeshes) {
    if (redFMeshHaveColorsChanged(e.second[0]) == 1) {
      mape_object_add_array_number(i, array, (double)j);
      i += 1;
    }
    j += 1;
  }
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesGetHaveTexCoordsChangedMeshIndexes GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*count*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalMeshesGetHaveTexCoordsChangedMeshIndexes")
  getArgAs_Double(uint64_t, count, args[_i++]);
  getArgAs_END

  ape_object_t array = mape_object_make_array(ape, count);
  uint64_t i = 0;
  uint64_t j = 0;
  for (auto & e : gApeMeshes) {
    if (redFMeshHaveTexCoordsChanged(e.second[0]) == 1) {
      mape_object_add_array_number(i, array, (double)j);
      i += 1;
    }
    j += 1;
  }
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesGetHaveIndicesChangedMeshIndexes GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*count*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalMeshesGetHaveIndicesChangedMeshIndexes")
  getArgAs_Double(uint64_t, count, args[_i++]);
  getArgAs_END

  ape_object_t array = mape_object_make_array(ape, count);
  uint64_t i = 0;
  uint64_t j = 0;
  for (auto & e : gApeMeshes) {
    if (redFMeshHaveIndicesChanged(e.second[0]) == 1) {
      mape_object_add_array_number(i, array, (double)j);
      i += 1;
    }
    j += 1;
  }
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesPersistentGetHaveVerticesChangedMeshIndexes GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*count*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalMeshesPersistentGetHaveVerticesChangedMeshIndexes")
  getArgAs_Double(uint64_t, count, args[_i++]);
  getArgAs_END

  ape_object_t array = mape_object_make_array(ape, count);
  uint64_t i = 0;
  uint64_t j = 0;
  for (auto & e : gApeMeshesPersistent) {
    if (redFMeshHaveVertsChanged(e.second[0]) == 1) {
      mape_object_add_array_number(i, array, (double)j);
      i += 1;
    }
    j += 1;
  }
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesPersistentGetHaveColorsChangedMeshIndexes GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*count*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalMeshesPersistentGetHaveColorsChangedMeshIndexes")
  getArgAs_Double(uint64_t, count, args[_i++]);
  getArgAs_END

  ape_object_t array = mape_object_make_array(ape, count);
  uint64_t i = 0;
  uint64_t j = 0;
  for (auto & e : gApeMeshesPersistent) {
    if (redFMeshHaveColorsChanged(e.second[0]) == 1) {
      mape_object_add_array_number(i, array, (double)j);
      i += 1;
    }
    j += 1;
  }
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesPersistentGetHaveTexCoordsChangedMeshIndexes GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*count*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalMeshesPersistentGetHaveTexCoordsChangedMeshIndexes")
  getArgAs_Double(uint64_t, count, args[_i++]);
  getArgAs_END

  ape_object_t array = mape_object_make_array(ape, count);
  uint64_t i = 0;
  uint64_t j = 0;
  for (auto & e : gApeMeshesPersistent) {
    if (redFMeshHaveTexCoordsChanged(e.second[0]) == 1) {
      mape_object_add_array_number(i, array, (double)j);
      i += 1;
    }
    j += 1;
  }
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalMeshesPersistentGetHaveIndicesChangedMeshIndexes GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*count*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalMeshesPersistentGetHaveIndicesChangedMeshIndexes")
  getArgAs_Double(uint64_t, count, args[_i++]);
  getArgAs_END

  ape_object_t array = mape_object_make_array(ape, count);
  uint64_t i = 0;
  uint64_t j = 0;
  for (auto & e : gApeMeshesPersistent) {
    if (redFMeshHaveIndicesChanged(e.second[0]) == 1) {
      mape_object_add_array_number(i, array, (double)j);
      i += 1;
    }
    j += 1;
  }
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalKeyPropertyGetKeyLabelsCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  double out = 0;
  {
    std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
    out = (double)gKeyProperties.size();
  }

  return ape_object_make_number(out);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalKeyPropertyIsKeyLabelExists GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*key*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalKeyPropertyIsKeyLabelExists")
  getArgAs_String(std::string, key, args[_i++]);
  getArgAs_END

  bool exists = false;
  {
    std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
    exists = gKeyProperties.find(key) != gKeyProperties.end();
  }

  return ape_object_make_bool(exists);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalKeyPropertyGetKeyLabelByKeyIndex GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*index*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalKeyPropertyGetKeyLabelByKeyIndex")
  getArgAs_Double(uint64_t, index, args[_i++]);
  getArgAs_END

  std::string out;
  {
    std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
    auto e = gKeyProperties.begin();
    for (uint64_t i = 0; i < index; i += 1) {
      ++e;
    }
    out = e->first;
  }

  return ape_object_make_string(ape, out.c_str());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalKeyPropertyGetKeyPropertyLabelsCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*key*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalKeyPropertyGetKeyPropertyLabelsCount")
  getArgAs_String(std::string, key, args[_i++]);
  getArgAs_END

  double out = 0;
  {
    std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
    out = (double)gKeyProperties[key].size();
  }

  return ape_object_make_number(out);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalKeyPropertyIsKeyPropertyLabelExists GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*key*/,
    APE_OBJECT_STRING/*property*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalKeyPropertyIsKeyPropertyLabelExists")
  getArgAs_String(std::string, key,      args[_i++]);
  getArgAs_String(std::string, property, args[_i++]);
  getArgAs_END

  bool exists = false;
  {
    std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
    exists = gKeyProperties[key].find(property) != gKeyProperties[key].end();
  }

  return ape_object_make_bool(exists);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalKeyPropertyGetKeyPropertyLabelByPropertyIndex GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*key*/,
    APE_OBJECT_NUMBER/*index*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalKeyPropertyGetKeyPropertyLabelByPropertyIndex")
  getArgAs_String(std::string, key,   args[_i++]);
  getArgAs_Double(uint64_t,    index, args[_i++]);
  getArgAs_END

  std::string out;
  {
    std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
    auto e = gKeyProperties[key].begin();
    for (uint64_t i = 0; i < index; i += 1) {
      ++e;
    }
    out = e->first;
  }

  return ape_object_make_string(ape, out.c_str());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalKeyPropertyRemoveKey GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*key*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalKeyPropertyRemoveKey")
  getArgAs_String(std::string, key, args[_i++]);
  getArgAs_END

  {
    std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
    gKeyProperties.erase(key);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalKeyPropertyRemoveAllKeys GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  {
    std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
    gKeyProperties.clear();
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalKeyPropertyRemoveProperty GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*key*/,
    APE_OBJECT_STRING/*property*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalKeyPropertyRemoveProperty")
  getArgAs_String(std::string, key,      args[_i++]);
  getArgAs_String(std::string, property, args[_i++]);
  getArgAs_END

  {
    std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
    gKeyProperties[key].erase(property);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalKeyPropertyRemoveAllProperties GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*key*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalKeyPropertyRemoveAllProperties")
  getArgAs_String(std::string, key, args[_i++]);
  getArgAs_END

  {
    std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
    gKeyProperties[key].clear();
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalKeyPropertySetString GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*key*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_STRING/*value*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalKeyPropertySetString")
  getArgAs_String(std::string, key,      args[_i++]);
  getArgAs_String(std::string, property, args[_i++]);
  getArgAs_String(std::string, value,    args[_i++]);
  getArgAs_END

  {
    std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
    gKeyProperties[key][property].astring = value;
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalKeyPropertySetNumber GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*key*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_NUMBER/*value*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalKeyPropertySetNumber")
  getArgAs_String(std::string, key,      args[_i++]);
  getArgAs_String(std::string, property, args[_i++]);
  getArgAs_Double(double,      value,    args[_i++]);
  getArgAs_END

  {
    std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
    gKeyProperties[key][property].number = value;
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalKeyPropertySetBool GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*key*/,
    APE_OBJECT_STRING/*property*/,
    APE_OBJECT_BOOL/*value*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalKeyPropertySetBool")
  getArgAs_String(std::string, key,      args[_i++]);
  getArgAs_String(std::string, property, args[_i++]);
  getArgAs_Bool(unsigned char, value,    args[_i++]);
  getArgAs_END

  {
    std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
    gKeyProperties[key][property].boolean = value;
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalKeyPropertyGetString GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*key*/,
    APE_OBJECT_STRING/*property*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalKeyPropertyGetString")
  getArgAs_String(std::string, key,      args[_i++]);
  getArgAs_String(std::string, property, args[_i++]);
  getArgAs_END

  std::string value;
  {
    std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
    value = gKeyProperties[key][property].astring;
  }

  return ape_object_make_string(ape, value.c_str());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalKeyPropertyGetNumber GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*key*/,
    APE_OBJECT_STRING/*property*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalKeyPropertyGetNumber")
  getArgAs_String(std::string, key,      args[_i++]);
  getArgAs_String(std::string, property, args[_i++]);
  getArgAs_END

  double value = 0;
  {
    std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
    value = gKeyProperties[key][property].number;
  }

  return ape_object_make_number(value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalKeyPropertyGetBool GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*key*/,
    APE_OBJECT_STRING/*property*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("globalKeyPropertyGetBool")
  getArgAs_String(std::string, key,      args[_i++]);
  getArgAs_String(std::string, property, args[_i++]);
  getArgAs_END

  unsigned char value = 0;
  {
    std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
    value = gKeyProperties[key][property].boolean;
  }

  return ape_object_make_bool(value == 0 ? false : true);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetXatlasStructsCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  uint64_t count = 0;

#define GS_MACRO_XATLAS_STRUCT(STRUCTURE) count += 1;

  GS_MACRO_XATLAS_STRUCT(XatlasChart)
  GS_MACRO_XATLAS_STRUCT(XatlasVertex)
  GS_MACRO_XATLAS_STRUCT(XatlasMesh)
  GS_MACRO_XATLAS_STRUCT(XatlasAtlas)
  GS_MACRO_XATLAS_STRUCT(XatlasMeshDecl)
  GS_MACRO_XATLAS_STRUCT(XatlasUvMeshDecl)
  GS_MACRO_XATLAS_STRUCT(XatlasChartOptions)
  GS_MACRO_XATLAS_STRUCT(XatlasPackOptions)

#undef GS_MACRO_XATLAS_STRUCT

  return ape_object_make_number((double)count);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetXatlasStructName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*index*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("getXatlasStructName")
  getArgAs_Double(uint64_t, index, args[_i++]);
  getArgAs_END

  uint64_t count = 0;

#define GS_MACRO_XATLAS_STRUCT(STRUCTURE) \
  if (index == count) { \
    return ape_object_make_string(ape, #STRUCTURE); \
  } \
  count += 1;

  GS_MACRO_XATLAS_STRUCT(XatlasChart)
  GS_MACRO_XATLAS_STRUCT(XatlasVertex)
  GS_MACRO_XATLAS_STRUCT(XatlasMesh)
  GS_MACRO_XATLAS_STRUCT(XatlasAtlas)
  GS_MACRO_XATLAS_STRUCT(XatlasMeshDecl)
  GS_MACRO_XATLAS_STRUCT(XatlasUvMeshDecl)
  GS_MACRO_XATLAS_STRUCT(XatlasChartOptions)
  GS_MACRO_XATLAS_STRUCT(XatlasPackOptions)

#undef GS_MACRO_XATLAS_STRUCT

  return ape_object_make_string(ape, "");
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureXatlasStructSizeof GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*structName*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("xatlasStructSizeof")
  getArgAs_CChars(const char *, structName, args[_i++]);
  getArgAs_END

  const size_t structNameBytesCount = strlen(structName) + 1;

#define GS_MACRO_XATLAS_STRUCT(STRUCTURE) \
  if (structNameBytesCount == sizeof(#STRUCTURE)) { \
    if (memcmp(structName, #STRUCTURE, structNameBytesCount) == 0) { \
      return ape_object_make_number((double)sizeof(STRUCTURE)); \
    } \
  }

  GS_MACRO_XATLAS_STRUCT(XatlasChart)
  GS_MACRO_XATLAS_STRUCT(XatlasVertex)
  GS_MACRO_XATLAS_STRUCT(XatlasMesh)
  GS_MACRO_XATLAS_STRUCT(XatlasAtlas)
  GS_MACRO_XATLAS_STRUCT(XatlasMeshDecl)
  GS_MACRO_XATLAS_STRUCT(XatlasUvMeshDecl)
  GS_MACRO_XATLAS_STRUCT(XatlasChartOptions)
  GS_MACRO_XATLAS_STRUCT(XatlasPackOptions)

#undef GS_MACRO_XATLAS_STRUCT

  return ape_object_make_number((double)((uint64_t)-1));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetXatlasStructMembersCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  uint64_t count = 0;

#define GS_MACRO_XATLAS_STRUCT_MEMBER(GS_TYPE, TYPE, STRUCTURE, MEMBER) count += 1;

  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, unsigned *, XatlasChart, faceArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChart, atlasIndex)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChart, faceCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, XatlasChartType, XatlasChart, type)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChart, material)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasVertex, atlasIndex)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasVertex, chartIndex)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasVertex, uv)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasVertex, xref)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasChart *, XatlasMesh, chartArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, unsigned *, XatlasMesh, indexArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasVertex *, XatlasMesh, vertexArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMesh, chartCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMesh, indexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMesh, vertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, unsigned *, XatlasAtlas, image)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasMesh *, XatlasAtlas, meshes)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, float *, XatlasAtlas, utilization)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, width)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, height)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, atlasCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, chartCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, meshCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasAtlas, texelsPerUnit)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, vertexPositionData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, vertexNormalData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, vertexUvData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, indexData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const bool *, XatlasMeshDecl, faceIgnoreData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, XatlasMeshDecl, faceMaterialData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned char *, XatlasMeshDecl, faceVertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexPositionStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexNormalStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexUvStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, indexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasMeshDecl, indexOffset)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, faceCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, XatlasIndexFormat, XatlasMeshDecl, indexFormat)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasMeshDecl, epsilon)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasUvMeshDecl, vertexUvData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasUvMeshDecl, indexData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, XatlasUvMeshDecl, faceMaterialData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasUvMeshDecl, vertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasUvMeshDecl, vertexStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasUvMeshDecl, indexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasUvMeshDecl, indexOffset)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, XatlasIndexFormat, XatlasUvMeshDecl, indexFormat)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasFuncParameterize, XatlasChartOptions, paramFunc)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, maxChartArea)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, maxBoundaryLength)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, normalDeviationWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, roundnessWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, straightnessWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, normalSeamWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, maxCost)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChartOptions, maxIterations)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasChartOptions, useInputMeshUvs)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasChartOptions, fixWinding)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasPackOptions, maxChartSize)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasPackOptions, padding)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasPackOptions, texelsPerUnit)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasPackOptions, resolution)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, bilinear)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, blockAlign)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, bruteForce)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, createImage)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, rotateChartsToAxis)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, rotateCharts)

#undef GS_MACRO_XATLAS_STRUCT_MEMBER

  return ape_object_make_number((double)count);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetXatlasStructMemberName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*index*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("getXatlasStructMemberName")
  getArgAs_Double(uint64_t, index, args[_i++]);
  getArgAs_END

  uint64_t count = 0;

#define GS_MACRO_XATLAS_STRUCT_MEMBER(GS_TYPE, TYPE, STRUCTURE, MEMBER) \
  if (index == count) { \
    return ape_object_make_string(ape, #STRUCTURE "." #MEMBER); \
  } \
  count += 1;

  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, unsigned *, XatlasChart, faceArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChart, atlasIndex)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChart, faceCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, XatlasChartType, XatlasChart, type)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChart, material)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasVertex, atlasIndex)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasVertex, chartIndex)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasVertex, uv)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasVertex, xref)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasChart *, XatlasMesh, chartArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, unsigned *, XatlasMesh, indexArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasVertex *, XatlasMesh, vertexArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMesh, chartCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMesh, indexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMesh, vertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, unsigned *, XatlasAtlas, image)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasMesh *, XatlasAtlas, meshes)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, float *, XatlasAtlas, utilization)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, width)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, height)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, atlasCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, chartCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, meshCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasAtlas, texelsPerUnit)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, vertexPositionData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, vertexNormalData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, vertexUvData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, indexData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const bool *, XatlasMeshDecl, faceIgnoreData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, XatlasMeshDecl, faceMaterialData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned char *, XatlasMeshDecl, faceVertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexPositionStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexNormalStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexUvStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, indexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasMeshDecl, indexOffset)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, faceCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, XatlasIndexFormat, XatlasMeshDecl, indexFormat)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasMeshDecl, epsilon)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasUvMeshDecl, vertexUvData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasUvMeshDecl, indexData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, XatlasUvMeshDecl, faceMaterialData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasUvMeshDecl, vertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasUvMeshDecl, vertexStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasUvMeshDecl, indexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasUvMeshDecl, indexOffset)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, XatlasIndexFormat, XatlasUvMeshDecl, indexFormat)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasFuncParameterize, XatlasChartOptions, paramFunc)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, maxChartArea)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, maxBoundaryLength)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, normalDeviationWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, roundnessWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, straightnessWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, normalSeamWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, maxCost)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChartOptions, maxIterations)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasChartOptions, useInputMeshUvs)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasChartOptions, fixWinding)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasPackOptions, maxChartSize)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasPackOptions, padding)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasPackOptions, texelsPerUnit)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasPackOptions, resolution)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, bilinear)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, blockAlign)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, bruteForce)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, createImage)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, rotateChartsToAxis)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, rotateCharts)

#undef GS_MACRO_XATLAS_STRUCT_MEMBER

  return ape_object_make_string(ape, "");
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureXatlasStructMemberSizeof GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*structName*/,
    APE_OBJECT_STRING/*structMemberName*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("xatlasStructMemberSizeof")
  getArgAs_CChars(const char *, structName, args[_i++]);
  getArgAs_CChars(const char *, memberName, args[_i++]);
  getArgAs_END

  const size_t structNameBytesCount = strlen(structName) + 1;
  const size_t memberNameBytesCount = strlen(memberName) + 1;

#define GS_MACRO_XATLAS_STRUCT_MEMBER(GS_TYPE, TYPE, STRUCTURE, MEMBER) \
  if (structNameBytesCount == sizeof(#STRUCTURE)) { \
    if (memberNameBytesCount == sizeof(#MEMBER)) { \
      if (memcmp(structName, #STRUCTURE, structNameBytesCount) == 0) { \
        if (memcmp(memberName, #MEMBER, memberNameBytesCount) == 0) { \
          return ape_object_make_number((double)sizeof(((STRUCTURE *)0)->MEMBER)); \
        } \
      } \
    } \
  }

  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, unsigned *, XatlasChart, faceArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChart, atlasIndex)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChart, faceCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, XatlasChartType, XatlasChart, type)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChart, material)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasVertex, atlasIndex)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasVertex, chartIndex)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasVertex, uv)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasVertex, xref)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasChart *, XatlasMesh, chartArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, unsigned *, XatlasMesh, indexArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasVertex *, XatlasMesh, vertexArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMesh, chartCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMesh, indexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMesh, vertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, unsigned *, XatlasAtlas, image)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasMesh *, XatlasAtlas, meshes)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, float *, XatlasAtlas, utilization)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, width)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, height)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, atlasCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, chartCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, meshCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasAtlas, texelsPerUnit)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, vertexPositionData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, vertexNormalData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, vertexUvData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, indexData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const bool *, XatlasMeshDecl, faceIgnoreData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, XatlasMeshDecl, faceMaterialData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned char *, XatlasMeshDecl, faceVertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexPositionStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexNormalStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexUvStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, indexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasMeshDecl, indexOffset)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, faceCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, XatlasIndexFormat, XatlasMeshDecl, indexFormat)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasMeshDecl, epsilon)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasUvMeshDecl, vertexUvData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasUvMeshDecl, indexData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, XatlasUvMeshDecl, faceMaterialData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasUvMeshDecl, vertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasUvMeshDecl, vertexStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasUvMeshDecl, indexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasUvMeshDecl, indexOffset)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, XatlasIndexFormat, XatlasUvMeshDecl, indexFormat)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasFuncParameterize, XatlasChartOptions, paramFunc)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, maxChartArea)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, maxBoundaryLength)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, normalDeviationWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, roundnessWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, straightnessWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, normalSeamWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, maxCost)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChartOptions, maxIterations)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasChartOptions, useInputMeshUvs)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasChartOptions, fixWinding)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasPackOptions, maxChartSize)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasPackOptions, padding)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasPackOptions, texelsPerUnit)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasPackOptions, resolution)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, bilinear)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, blockAlign)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, bruteForce)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, createImage)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, rotateChartsToAxis)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, rotateCharts)

#undef GS_MACRO_XATLAS_STRUCT_MEMBER

  return ape_object_make_number((double)((uint64_t)-1));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureXatlasStructMemberOffsetof GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*structName*/,
    APE_OBJECT_STRING/*structMemberName*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("xatlasStructMemberOffsetof")
  getArgAs_CChars(const char *, structName, args[_i++]);
  getArgAs_CChars(const char *, memberName, args[_i++]);
  getArgAs_END

  const size_t structNameBytesCount = strlen(structName) + 1;
  const size_t memberNameBytesCount = strlen(memberName) + 1;

#define GS_MACRO_XATLAS_STRUCT_MEMBER(GS_TYPE, TYPE, STRUCTURE, MEMBER) \
  if (structNameBytesCount == sizeof(#STRUCTURE)) { \
    if (memberNameBytesCount == sizeof(#MEMBER)) { \
      if (memcmp(structName, #STRUCTURE, structNameBytesCount) == 0) { \
        if (memcmp(memberName, #MEMBER, memberNameBytesCount) == 0) { \
          return ape_object_make_number((double)offsetof(STRUCTURE, MEMBER)); \
        } \
      } \
    } \
  }

  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, unsigned *, XatlasChart, faceArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChart, atlasIndex)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChart, faceCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, XatlasChartType, XatlasChart, type)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChart, material)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasVertex, atlasIndex)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasVertex, chartIndex)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasVertex, uv)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasVertex, xref)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasChart *, XatlasMesh, chartArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, unsigned *, XatlasMesh, indexArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasVertex *, XatlasMesh, vertexArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMesh, chartCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMesh, indexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMesh, vertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, unsigned *, XatlasAtlas, image)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasMesh *, XatlasAtlas, meshes)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, float *, XatlasAtlas, utilization)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, width)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, height)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, atlasCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, chartCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, meshCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasAtlas, texelsPerUnit)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, vertexPositionData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, vertexNormalData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, vertexUvData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, indexData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const bool *, XatlasMeshDecl, faceIgnoreData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, XatlasMeshDecl, faceMaterialData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned char *, XatlasMeshDecl, faceVertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexPositionStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexNormalStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexUvStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, indexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasMeshDecl, indexOffset)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, faceCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, XatlasIndexFormat, XatlasMeshDecl, indexFormat)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasMeshDecl, epsilon)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasUvMeshDecl, vertexUvData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasUvMeshDecl, indexData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, XatlasUvMeshDecl, faceMaterialData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasUvMeshDecl, vertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasUvMeshDecl, vertexStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasUvMeshDecl, indexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasUvMeshDecl, indexOffset)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, XatlasIndexFormat, XatlasUvMeshDecl, indexFormat)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasFuncParameterize, XatlasChartOptions, paramFunc)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, maxChartArea)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, maxBoundaryLength)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, normalDeviationWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, roundnessWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, straightnessWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, normalSeamWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, maxCost)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChartOptions, maxIterations)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasChartOptions, useInputMeshUvs)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasChartOptions, fixWinding)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasPackOptions, maxChartSize)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasPackOptions, padding)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasPackOptions, texelsPerUnit)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasPackOptions, resolution)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, bilinear)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, blockAlign)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, bruteForce)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, createImage)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, rotateChartsToAxis)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, rotateCharts)

#undef GS_MACRO_XATLAS_STRUCT_MEMBER

  return ape_object_make_number((double)((uint64_t)-1));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureXatlasStructMemberTypeof GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*structName*/,
    APE_OBJECT_STRING/*structMemberName*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("xatlasStructMemberTypeof")
  getArgAs_CChars(const char *, structName, args[_i++]);
  getArgAs_CChars(const char *, memberName, args[_i++]);
  getArgAs_END

  const size_t structNameBytesCount = strlen(structName) + 1;
  const size_t memberNameBytesCount = strlen(memberName) + 1;

#define GS_MACRO_XATLAS_STRUCT_MEMBER(GS_TYPE, TYPE, STRUCTURE, MEMBER) \
  if (structNameBytesCount == sizeof(#STRUCTURE)) { \
    if (memberNameBytesCount == sizeof(#MEMBER)) { \
      if (memcmp(structName, #STRUCTURE, structNameBytesCount) == 0) { \
        if (memcmp(memberName, #MEMBER, memberNameBytesCount) == 0) { \
          return ape_object_make_number((double)GS_TYPE); \
        } \
      } \
    } \
  }

  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, unsigned *, XatlasChart, faceArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChart, atlasIndex)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChart, faceCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, XatlasChartType, XatlasChart, type)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChart, material)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasVertex, atlasIndex)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasVertex, chartIndex)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasVertex, uv)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasVertex, xref)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasChart *, XatlasMesh, chartArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, unsigned *, XatlasMesh, indexArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasVertex *, XatlasMesh, vertexArray)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMesh, chartCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMesh, indexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMesh, vertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, unsigned *, XatlasAtlas, image)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasMesh *, XatlasAtlas, meshes)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, float *, XatlasAtlas, utilization)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, width)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, height)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, atlasCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, chartCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasAtlas, meshCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasAtlas, texelsPerUnit)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, vertexPositionData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, vertexNormalData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, vertexUvData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasMeshDecl, indexData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const bool *, XatlasMeshDecl, faceIgnoreData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, XatlasMeshDecl, faceMaterialData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned char *, XatlasMeshDecl, faceVertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexPositionStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexNormalStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, vertexUvStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, indexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasMeshDecl, indexOffset)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasMeshDecl, faceCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, XatlasIndexFormat, XatlasMeshDecl, indexFormat)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasMeshDecl, epsilon)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasUvMeshDecl, vertexUvData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, XatlasUvMeshDecl, indexData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const unsigned *, XatlasUvMeshDecl, faceMaterialData)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasUvMeshDecl, vertexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasUvMeshDecl, vertexStride)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasUvMeshDecl, indexCount)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_I32, int, XatlasUvMeshDecl, indexOffset)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, XatlasIndexFormat, XatlasUvMeshDecl, indexFormat)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, XatlasFuncParameterize, XatlasChartOptions, paramFunc)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, maxChartArea)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, maxBoundaryLength)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, normalDeviationWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, roundnessWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, straightnessWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, normalSeamWeight)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasChartOptions, maxCost)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasChartOptions, maxIterations)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasChartOptions, useInputMeshUvs)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasChartOptions, fixWinding)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasPackOptions, maxChartSize)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasPackOptions, padding)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_F32, float, XatlasPackOptions, texelsPerUnit)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, XatlasPackOptions, resolution)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, bilinear)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, blockAlign)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, bruteForce)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, createImage)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, rotateChartsToAxis)
  GS_MACRO_XATLAS_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_BOOL, bool, XatlasPackOptions, rotateCharts)

#undef GS_MACRO_XATLAS_STRUCT_MEMBER

  return ape_object_make_number(0.0);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureXatlasMeshDeclInit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointerToXatlasMeshDecl*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("xatlasMeshDeclInit")
  getArgAs_Pointer(XatlasMeshDecl *, pointer, args[_i++]);
  getArgAs_END

  xatlasMeshDeclInit(pointer);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureXatlasUvMeshDeclInit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointerToXatlasUvMeshDecl*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("xatlasUvMeshDeclInit")
  getArgAs_Pointer(XatlasUvMeshDecl *, pointer, args[_i++]);
  getArgAs_END

  xatlasUvMeshDeclInit(pointer);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureXatlasChartOptionsInit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointerToXatlasChartOptions*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("xatlasChartOptionsInit")
  getArgAs_Pointer(XatlasChartOptions *, pointer, args[_i++]);
  getArgAs_END

  xatlasChartOptionsInit(pointer);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureXatlasPackOptionsInit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*pointerToXatlasPackOptions*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("xatlasPackOptionsInit")
  getArgAs_Pointer(XatlasPackOptions *, pointer, args[_i++]);
  getArgAs_END

  xatlasPackOptionsInit(pointer);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureXatlasCreate GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  XatlasAtlas * out = xatlasCreate();

  return ape_object_make_number(_gsPointerToNumber((void *)out));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureXatlasDestroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*xatlas*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("xatlasDestroy")
  getArgAs_Pointer(XatlasAtlas *, xatlas, args[_i++]);
  getArgAs_END

  xatlasDestroy(xatlas);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureXatlasAddMesh GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*xatlas*/,
    APE_OBJECT_NUMBER/*pointerToXatlasMeshDecl*/,
    APE_OBJECT_NUMBER/*meshCountHint*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("xatlasAddMesh")
  getArgAs_Pointer(XatlasAtlas *,          xatlas,        args[_i++]);
  getArgAs_Pointer(const XatlasMeshDecl *, meshDecl,      args[_i++]);
  getArgAs_Double(unsigned,                meshCountHint, args[_i++]);
  getArgAs_END

  XatlasAddMeshError status = xatlasAddMesh(xatlas, meshDecl, meshCountHint);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureXatlasAddMeshJoin GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*xatlas*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("xatlasAddMeshJoin")
  getArgAs_Pointer(XatlasAtlas *, xatlas, args[_i++]);
  getArgAs_END

  xatlasAddMeshJoin(xatlas);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureXatlasAddUvMesh GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*xatlas*/,
    APE_OBJECT_NUMBER/*pointerToXatlasUvMeshDecl*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("xatlasAddUvMesh")
  getArgAs_Pointer(XatlasAtlas *,            xatlas, args[_i++]);
  getArgAs_Pointer(const XatlasUvMeshDecl *, decl,   args[_i++]);
  getArgAs_END

  XatlasAddMeshError status = xatlasAddUvMesh(xatlas, decl);

  return ape_object_make_number((double)status);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureXatlasComputeCharts GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*xatlas*/,
    APE_OBJECT_NUMBER/*pointerToXatlasChartOptions*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("xatlasComputeCharts")
  getArgAs_Pointer(XatlasAtlas *,              xatlas,       args[_i++]);
  getArgAs_Pointer(const XatlasChartOptions *, chartOptions, args[_i++]);
  getArgAs_END

  xatlasComputeCharts(xatlas, chartOptions);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureXatlasPackCharts GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*xatlas*/,
    APE_OBJECT_NUMBER/*pointerToXatlasPackOptions*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("xatlasPackCharts")
  getArgAs_Pointer(XatlasAtlas *,             xatlas,      args[_i++]);
  getArgAs_Pointer(const XatlasPackOptions *, packOptions, args[_i++]);
  getArgAs_END

  xatlasPackCharts(xatlas, packOptions);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureXatlasGenerate GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*xatlas*/,
    APE_OBJECT_NUMBER/*pointerToXatlasChartOptions*/,
    APE_OBJECT_NUMBER/*pointerToXatlasPackOptions*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("xatlasGenerate")
  getArgAs_Pointer(XatlasAtlas *,              xatlas,       args[_i++]);
  getArgAs_Pointer(const XatlasChartOptions *, chartOptions, args[_i++]);
  getArgAs_Pointer(const XatlasPackOptions *,  packOptions,  args[_i++]);
  getArgAs_END

  xatlasGenerate(xatlas, chartOptions, packOptions);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureOnRerunCallXatlasDestroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*xatlas*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("onRerunCallXatlasDestroy")
  getArgAs_Pointer(XatlasAtlas *, xatlas, args[_i++]);
  getArgAs_END

  GlobalArrayPersistentOnRerunCallStorage element = {};
  element.storage[0] = (void *)xatlas;
  gGlobalArrayPersistentOnRerunCallXatlasDestroy.push_back(element);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxNew GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxNew")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleFbx * handle = 0;
  {
    std::lock_guard<std::mutex> __fbxsGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_fbxsMutex);
    handle = gApeFbxs[label];
  }
  if (handle == 0) {
    handle = redFCreateFbx(1);
    if (handle != 0) {
      std::lock_guard<std::mutex> __fbxsGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_fbxsMutex);
      gApeFbxs[label] = handle;
    }
  }

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxNewFromFile GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
    APE_OBJECT_STRING/*filepath*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxNewFromFile")
  getArgAs_String(std::string,  label,    args[_i++]);
  getArgAs_CChars(const char *, filepath, args[_i++]);
  getArgAs_END

  RedFHandleFbx * handle = 0;
  {
    std::lock_guard<std::mutex> __fbxsGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_fbxsMutex);
    handle = gApeFbxs[label];
  }
  if (handle == 0) {
    handle = redFCreateFbx(1);
    if (handle != 0) {
      RedFBool32 loaded = redFFbxLoad(handle[0], filepath);
      if (loaded == 0) {
        redFDestroyFbx(handle);
        handle = 0;
      } else {
        std::lock_guard<std::mutex> __fbxsGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_fbxsMutex);
        gApeFbxs[label] = handle;
      }
    }
  }

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxDelete GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxDelete")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleFbx * handle = 0;
  {
    std::lock_guard<std::mutex> __fbxsGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_fbxsMutex);
    handle = gApeFbxs[label];
    gApeFbxs.erase(label);
  }
  redFDestroyFbx(handle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxDeleteAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  {
    std::lock_guard<std::mutex> __fbxsGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_fbxsMutex);
    for (auto & kv : gApeFbxs) {
      redFDestroyFbx(kv.second);
    }
    gApeFbxs.clear();
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxGetHandle GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*label*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxGetHandle")
  getArgAs_String(std::string, label, args[_i++]);
  getArgAs_END

  RedFHandleFbx * handle = 0;
  {
    std::lock_guard<std::mutex> __fbxsGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_fbxsMutex);
    handle = gApeFbxs[label];
  }

  return ape_object_make_number(_gsPointerToNumber((void *)handle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxCopyToFbx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handleCopyFrom*/,
    APE_OBJECT_NUMBER/*handleCopyTo*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxCopyToFbx")
  getArgAs_Pointer(RedFHandleFbx *, handleCopyFrom, args[_i++]);
  getArgAs_Pointer(RedFHandleFbx *, handleCopyTo,   args[_i++]);
  getArgAs_END

  redFFbxCopyToFbx(handleCopyFrom[0], handleCopyTo[0]);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxClear GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxClear")
  getArgAs_Pointer(RedFHandleFbx *, handle, args[_i++]);
  getArgAs_END

  redFFbxClear(handle[0]);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxEarlyUpdate GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxEarlyUpdate")
  getArgAs_Pointer(RedFHandleFbx *, handle, args[_i++]);
  getArgAs_END

  redFFbxEarlyUpdate(handle[0]);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxLateUpdate GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxLateUpdate")
  getArgAs_Pointer(RedFHandleFbx *, handle, args[_i++]);
  getArgAs_END

  redFFbxLateUpdate(handle[0]);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxGetMeshesCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxGetMeshesCount")
  getArgAs_Pointer(RedFHandleFbx *, handle, args[_i++]);
  getArgAs_END

  int count = redFFbxGetMeshesCount(handle[0]);

  return ape_object_make_number((double)count);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxGetMesh GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*meshIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxGetMesh")
  getArgAs_Pointer(RedFHandleFbx *, handle,    args[_i++]);
  getArgAs_Double(int,              meshIndex, args[_i++]);
  getArgAs_END

  RedFHandleMesh meshHandle = redFFbxGetMesh(handle[0], meshIndex);

  return ape_object_make_number(_gsPointerToNumber((void *)meshHandle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxGetMeshName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*meshIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxGetMeshName")
  getArgAs_Pointer(RedFHandleFbx *, handle,    args[_i++]);
  getArgAs_Double(int,              meshIndex, args[_i++]);
  getArgAs_END

  uint64_t meshNameCharsCount = 0;
  redFFbxGetMeshName(handle[0], meshIndex, &meshNameCharsCount, 0);
  std::string meshName(meshNameCharsCount, '\0');
  redFFbxGetMeshName(handle[0], meshIndex, &meshNameCharsCount, &meshName[0]);

  return ape_object_make_string(ape, meshName.c_str());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxGetRootBonesCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxGetRootBonesCount")
  getArgAs_Pointer(RedFHandleFbx *, handle, args[_i++]);
  getArgAs_END

  int count = redFFbxGetRootBonesCount(handle[0]);

  return ape_object_make_number((double)count);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxGetRootBone GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*rootBoneIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxGetRootBone")
  getArgAs_Pointer(RedFHandleFbx *, handle,        args[_i++]);
  getArgAs_Double(int,              rootBoneIndex, args[_i++]);
  getArgAs_END

  RedFHandleFbxBone boneHandle = redFFbxGetRootBone(handle[0], rootBoneIndex);

  return ape_object_make_number(_gsPointerToNumber((void *)boneHandle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxBoneGetName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxBoneGetName")
  getArgAs_Pointer(RedFHandleFbxBone, handle, args[_i++]);
  getArgAs_END

  uint64_t boneNameCharsCount = 0;
  redFFbxBoneGetName(handle, &boneNameCharsCount, 0);
  std::string boneName(boneNameCharsCount, '\0');
  redFFbxBoneGetName(handle, &boneNameCharsCount, &boneName[0]);

  return ape_object_make_string(ape, boneName.c_str());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxBoneGetChildBonesCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxBoneGetChildBonesCount")
  getArgAs_Pointer(RedFHandleFbxBone, handle, args[_i++]);
  getArgAs_END

  int count = redFFbxBoneGetChildBonesCount(handle);

  return ape_object_make_number((double)count);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxBoneGetChildBone GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*childBoneIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxBoneGetChildBone")
  getArgAs_Pointer(RedFHandleFbxBone, handle,         args[_i++]);
  getArgAs_Double(int,                childBoneIndex, args[_i++]);
  getArgAs_END

  RedFHandleFbxBone boneHandle = redFFbxBoneGetChildBone(handle, childBoneIndex);

  return ape_object_make_number(_gsPointerToNumber((void *)boneHandle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxBoneGetChildBoneByNameRecursively GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_STRING/*boneName*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxBoneGetChildBoneByNameRecursively")
  getArgAs_Pointer(RedFHandleFbxBone, handle,   args[_i++]);
  getArgAs_CChars(const char *,       boneName, args[_i++]);
  getArgAs_END

  RedFHandleFbxBone boneHandle = redFFbxBoneGetChildBoneByNameRecursively(handle, boneName);

  return ape_object_make_number(_gsPointerToNumber((void *)boneHandle));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxBoneGetVector GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxBoneGetVector")
  getArgAs_Pointer(RedFHandleFbxBone, handle, args[_i++]);
  getArgAs_END

  RedFHandleNode node = redFFbxBoneCastToNode(handle);

  ape_object_t array = mape_object_make_array(ape, 3);
  mape_object_add_array_number(0, array, (double)redFNodeGetGlobalPositionX(node));
  mape_object_add_array_number(1, array, (double)redFNodeGetGlobalPositionY(node));
  mape_object_add_array_number(2, array, (double)redFNodeGetGlobalPositionZ(node));
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxBoneGetVersor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxBoneGetVersor")
  getArgAs_Pointer(RedFHandleFbxBone, handle, args[_i++]);
  getArgAs_END

  RedFHandleNode node = redFFbxBoneCastToNode(handle);

  ape_object_t array = mape_object_make_array(ape, 4);
  mape_object_add_array_number(0, array, (double)redFNodeGetGlobalOrientationQuaternionX(node));
  mape_object_add_array_number(1, array, (double)redFNodeGetGlobalOrientationQuaternionY(node));
  mape_object_add_array_number(2, array, (double)redFNodeGetGlobalOrientationQuaternionZ(node));
  mape_object_add_array_number(3, array, (double)redFNodeGetGlobalOrientationQuaternionW(node));
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxBoneGetScale GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxBoneGetScale")
  getArgAs_Pointer(RedFHandleFbxBone, handle, args[_i++]);
  getArgAs_END

  RedFHandleNode node = redFFbxBoneCastToNode(handle);

  ape_object_t array = mape_object_make_array(ape, 3);
  mape_object_add_array_number(0, array, (double)redFNodeGetScaleX(node));
  mape_object_add_array_number(1, array, (double)redFNodeGetScaleY(node));
  mape_object_add_array_number(2, array, (double)redFNodeGetScaleZ(node));
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxBoneGetSideVector GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxBoneGetSideVector")
  getArgAs_Pointer(RedFHandleFbxBone, handle, args[_i++]);
  getArgAs_END

  RedFHandleNode node = redFFbxBoneCastToNode(handle);

  ape_object_t array = mape_object_make_array(ape, 3);
  mape_object_add_array_number(0, array, (double)redFNodeGetSideDirX(node));
  mape_object_add_array_number(1, array, (double)redFNodeGetSideDirY(node));
  mape_object_add_array_number(2, array, (double)redFNodeGetSideDirZ(node));
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxBoneGetUpVector GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxBoneGetUpVector")
  getArgAs_Pointer(RedFHandleFbxBone, handle, args[_i++]);
  getArgAs_END

  RedFHandleNode node = redFFbxBoneCastToNode(handle);

  ape_object_t array = mape_object_make_array(ape, 3);
  mape_object_add_array_number(0, array, (double)redFNodeGetUpDirX(node));
  mape_object_add_array_number(1, array, (double)redFNodeGetUpDirY(node));
  mape_object_add_array_number(2, array, (double)redFNodeGetUpDirZ(node));
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxBoneGetLookAtVector GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxBoneGetLookAtVector")
  getArgAs_Pointer(RedFHandleFbxBone, handle, args[_i++]);
  getArgAs_END

  RedFHandleNode node = redFFbxBoneCastToNode(handle);

  ape_object_t array = mape_object_make_array(ape, 3);
  mape_object_add_array_number(0, array, (double)redFNodeGetLookAtDirX(node));
  mape_object_add_array_number(1, array, (double)redFNodeGetLookAtDirY(node));
  mape_object_add_array_number(2, array, (double)redFNodeGetLookAtDirZ(node));
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxBoneGetTransformMatrix GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*outPointer*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxBoneGetTransformMatrix")
  getArgAs_Pointer(RedFHandleFbxBone, handle,     args[_i++]);
  getArgAs_Pointer(void *,            outPointer, args[_i++]);
  getArgAs_END

  RedFHandleNode node = redFFbxBoneCastToNode(handle);

  redFNodeGetGlobalTransformMatrix(node, outPointer);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxBoneSetVector GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxBoneSetVector")
  getArgAs_Pointer(RedFHandleFbxBone, handle, args[_i++]);
  getArgAs_Double(float,              x,      args[_i++]);
  getArgAs_Double(float,              y,      args[_i++]);
  getArgAs_Double(float,              z,      args[_i++]);
  getArgAs_END

  RedFHandleNode node = redFFbxBoneCastToNode(handle);

  redFNodeSetGlobalPosition(node, x, y, z);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxBoneSetVersor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/,
    APE_OBJECT_NUMBER/*w*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxBoneSetVersor")
  getArgAs_Pointer(RedFHandleFbxBone, handle, args[_i++]);
  getArgAs_Double(float,              x,      args[_i++]);
  getArgAs_Double(float,              y,      args[_i++]);
  getArgAs_Double(float,              z,      args[_i++]);
  getArgAs_Double(float,              w,      args[_i++]);
  getArgAs_END

  RedFHandleNode node = redFFbxBoneCastToNode(handle);

  redFNodeSetGlobalOrientationQuaternion(node, x, y, z, w);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxBoneSetScale GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxBoneSetScale")
  getArgAs_Pointer(RedFHandleFbxBone, handle, args[_i++]);
  getArgAs_Double(float,              x,      args[_i++]);
  getArgAs_Double(float,              y,      args[_i++]);
  getArgAs_Double(float,              z,      args[_i++]);
  getArgAs_END

  RedFHandleNode node = redFFbxBoneCastToNode(handle);

  redFNodeSetScale(node, x, y, z);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxBoneRotate GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*rotationX*/,
    APE_OBJECT_NUMBER/*rotationY*/,
    APE_OBJECT_NUMBER/*rotationZ*/,
    APE_OBJECT_NUMBER/*rotationDeg*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxBoneRotate")
  getArgAs_Pointer(RedFHandleFbxBone, handle,      args[_i++]);
  getArgAs_Double(float,              rotationX,   args[_i++]);
  getArgAs_Double(float,              rotationY,   args[_i++]);
  getArgAs_Double(float,              rotationZ,   args[_i++]);
  getArgAs_Double(float,              rotationDeg, args[_i++]);
  getArgAs_END

  RedFHandleNode node = redFFbxBoneCastToNode(handle);

  redFNodeRotateDeg(node, rotationDeg, rotationX, rotationY, rotationZ);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureFbxBoneLookAt GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*handle*/,
    APE_OBJECT_NUMBER/*x*/,
    APE_OBJECT_NUMBER/*y*/,
    APE_OBJECT_NUMBER/*z*/,
    APE_OBJECT_NUMBER/*upX*/,
    APE_OBJECT_NUMBER/*upY*/,
    APE_OBJECT_NUMBER/*upZ*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("fbxBoneLookAt")
  getArgAs_Pointer(RedFHandleFbxBone, handle, args[_i++]);
  getArgAs_Double(float,              x,      args[_i++]);
  getArgAs_Double(float,              y,      args[_i++]);
  getArgAs_Double(float,              z,      args[_i++]);
  getArgAs_Double(float,              upX,    args[_i++]);
  getArgAs_Double(float,              upY,    args[_i++]);
  getArgAs_Double(float,              upZ,    args[_i++]);
  getArgAs_END

  RedFHandleNode node = redFFbxBoneCastToNode(handle);

  redFNodeLookAt(node, x, y, z, upX, upY, upZ);

  return ape_object_make_null();
}

#if defined(GAME_SCRIPT_MIN)
GS_API GS_C_PROCEDURE_RETURN_TYPE() _minCProcedureSqrt GS_C_PROCEDURE_PARAMETERS() {
  int _i = 0;

  getArgAs_BEGIN("sqrt")
  getArgAs_Double(double, x, args[_i++]);
  getArgAs_END

  return ape_object_make_number(sqrt(x));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _minCProcedurePow GS_C_PROCEDURE_PARAMETERS() {
  int _i = 0;

  getArgAs_BEGIN("pow")
  getArgAs_Double(double, x, args[_i++]);
  getArgAs_Double(double, y, args[_i++]);
  getArgAs_END

  return ape_object_make_number(pow(x, y));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _minCProcedureSin GS_C_PROCEDURE_PARAMETERS() {
  int _i = 0;

  getArgAs_BEGIN("sin")
  getArgAs_Double(double, x, args[_i++]);
  getArgAs_END

  return ape_object_make_number(sin(x));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _minCProcedureCos GS_C_PROCEDURE_PARAMETERS() {
  int _i = 0;

  getArgAs_BEGIN("cos")
  getArgAs_Double(double, x, args[_i++]);
  getArgAs_END

  return ape_object_make_number(cos(x));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _minCProcedureTan GS_C_PROCEDURE_PARAMETERS() {
  int _i = 0;

  getArgAs_BEGIN("tan")
  getArgAs_Double(double, x, args[_i++]);
  getArgAs_END

  return ape_object_make_number(tan(x));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _minCProcedureLog GS_C_PROCEDURE_PARAMETERS() {
  int _i = 0;

  getArgAs_BEGIN("log")
  getArgAs_Double(double, x, args[_i++]);
  getArgAs_END

  return ape_object_make_number(log(x));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _minCProcedureCeil GS_C_PROCEDURE_PARAMETERS() {
  int _i = 0;

  getArgAs_BEGIN("ceil")
  getArgAs_Double(double, x, args[_i++]);
  getArgAs_END

  return ape_object_make_number(ceil(x));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _minCProcedureFloor GS_C_PROCEDURE_PARAMETERS() {
  int _i = 0;

  getArgAs_BEGIN("floor")
  getArgAs_Double(double, x, args[_i++]);
  getArgAs_END

  return ape_object_make_number(floor(x));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _minCProcedureAbs GS_C_PROCEDURE_PARAMETERS() {
  int _i = 0;

  getArgAs_BEGIN("abs")
  getArgAs_Double(double, x, args[_i++]);
  getArgAs_END

  return ape_object_make_number(abs(x));
}
#endif // #if defined(GAME_SCRIPT_MIN)

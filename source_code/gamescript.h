#pragma once

#define MSAA_SAMPLES_COUNT 4

#ifndef GAME_SCRIPT_NATIVE
#define GAME_SCRIPT
#endif

#if defined(_WIN32) && defined(GAME_SCRIPT_NATIVE)
#define GSN_WIN_IMPORT __declspec(dllimport)
#else
#define GSN_WIN_IMPORT extern
#endif

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#if defined(__MINGW32__)
#include <windows.h>
#endif
#if defined(__linux__) || defined(__MINGW32__)
#include "dependencies/redgpu/framework/redgpu_f.h"
#include "dependencies/redgpu/framework/cimgui.h"
#include "dependencies/redgpu/framework/glfw3.h"
#include "dependencies/procedural/profile/profile.h"
#elif defined(_WIN32) && !defined(__MINGW32__)
#pragma comment(lib, "C:/github/redgpu/framework/redgpu_fdll.lib")
#pragma comment(lib, "C:/github/redgpu/framework/glfw3dll.lib")
#pragma comment(lib, "C:/github/procedural/profile/profiledll.lib")
#pragma comment(lib, "C:/Users/Constantine/Desktop/game_script_source_code/redgpu.lib")
#pragma comment(lib, "C:/Users/Constantine/Desktop/game_script_source_code/xatlas.lib")
#pragma comment(lib, "C:/RedGpuSDK/radeonraysdll.lib")
#include <windows.h>
#include "C:/github/redgpu/framework/redgpu_f.h"
#include "C:/github/redgpu/framework/cimgui.h"
#include "C:/github/redgpu/framework/glfw3.h"
#include "C:/github/procedural/profile/profile.h"
#else
#error Implement
#endif
#include <new>           // For new, std::nothrow
#include <unordered_map> // For std::unordered_map
#include <mutex>         // For std::mutex
#include <string>        // For std::string, std::to_string
#include <vector>        // For std::vector
#include <sstream>       // For std::ostringstream
#include <fstream>       // For std::ifstream, std::ofstream
#include <cstddef>       // For offsetof
#include <malloc.h>      // For calloc
#include <string.h>      // For memcpy
#include <stdio.h>       // For printf, fflush
#include <time.h>        // For srand, time
#include <math.h>        // For asin, acos, atan, atan2
#if defined(__linux__)
#include <dlfcn.h>       // For dlopen, dlerror, dlsym
#endif
#if defined(_WIN32) && !defined(__MINGW32__)
#include "C:/github/r-lyeh/stdpack.c/src/lz4x.c"
#include "C:/github/r-lyeh/stdpack.c/src/ulz.c"
#endif
#if defined(__linux__) || defined(__MINGW32__)
#include "dependencies/r-lyeh/stdpack.c/src/lz4x.c"
#include "dependencies/r-lyeh/stdpack.c/src/ulz.c"
#endif
#if 1 // REDGPU
#if defined(_WIN32) && !defined(__MINGW32__)
#include "C:/RedGpuSDK/redgpu.h"
#include "C:/RedGpuSDK/redgpu_computing_language.h"
#include "C:/RedGpuSDK/redgpu_array_timestamp.h"
#include "C:/RedGpuSDK/redgpu_context_from_vk.h"
#include "C:/RedGpuSDK/radeonrays.h"
#include "C:/RedGpuSDK/radeonrays_redgpu.h"
#endif
#if defined(__linux__) || defined(__MINGW32__)
#include "dependencies/redgpu/RedGpuSDK/redgpu.h"
#include "dependencies/redgpu/RedGpuSDK/redgpu_computing_language.h"
#include "dependencies/redgpu/RedGpuSDK/redgpu_array_timestamp.h"
#include "dependencies/redgpu/RedGpuSDK/redgpu_context_from_vk.h"
#include "dependencies/redgpu/RedGpuSDK/radeonrays.h"
#include "dependencies/redgpu/RedGpuSDK/radeonrays_redgpu.h"
#endif
#endif
#if 1 // Embree
#if defined(_WIN32) && !defined(__MINGW32__)
#include <immintrin.h>
#endif
#if defined(__linux__) || defined(__MINGW32__)
#include <x86intrin.h>
#endif
#include "embree/include/sys/platform.h"
#include "embree/include/sys/filename.h"
#include "embree/include/sys/ref.h"
#include "embree/include/lexers/streamfilters.h"
#include "embree/include/lexers/parsestream.h"
#include "embree/include/loaders/loaders.h"
#include "embree/include/math/stlmath.h"
#include "embree/include/math/vec2.h"
#include "embree/include/math/vec3.h"
#include "embree/include/math/vec4.h"
#include "embree/include/math/col3.h"
#include "embree/include/math/affinespace.h"
#include "embree/include/image/image.h"
#include "embree/include/renderer/api/device.h"
#include "embree/include/renderer/api/handle.h"
#endif // Embree
#if 1 // Xatlas
#include "xatlas.h"
#endif // Xatlas

typedef union GsInternalUnionConverter {
  bool     boolean;
  int8_t   integer8Bit;
  uint8_t  unsignedInteger8Bit;
  int16_t  integer16Bit;
  uint16_t unsignedInteger16Bit;
  int      integer;
  unsigned unsignedInteger;
  float    afloat;
  int64_t  integer64Bit;
  uint64_t unsignedInteger64Bit;
  double   number;
  void *   voidpointer;
} GsInternalUnionConverter;

// NOTE(Constantine): I don't know where to place it.
GSN_WIN_IMPORT std::mutex __GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_minScriptLangErrorMutex;

#if defined(GAME_SCRIPT_MIN)

#include "minscriptlang.hpp"

#define ape_t void
#define ape_error_t void
#define ape_object_get_bool(a) false
#define ape_object_get_number(a) 0.0
#define ape_object_get_string(a) ""
#define ape_check_args(a, b, c, d, e, f) true
#define APE_OBJECT_BOOL 0
#define APE_OBJECT_NUMBER 0
#define APE_OBJECT_STRING 0
#define mape_make(a) 0
#define mape_destroy(a, b)
#define ape_has_errors(a) false
#define ape_errors_count(a) 0
#define ape_get_error(a, b) 0
#define ape_error_serialize(a, b) 0
#define ape_free_allocated(a, b)
#define ape_clear_errors(a)
// NOTE(Constantine): 2 threads assumption, will bite me in the ass in future.
#define mape_execute(THREAD_INDEX, b, CODE) \
  try { \
    env.Execute(CODE); \
  } catch (MinScriptLang::Error & exceptionError) { \
    std::lock_guard<std::mutex> __minScriptLangErrorGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_minScriptLangErrorMutex); \
    gApeErrors = ""; \
    if (THREAD_INDEX == 1) { \
      gApeErrors += "[Game Script][Thread 2 Script Errors]"; \
    } \
    gApeErrors += "[Frame "; \
    if (THREAD_INDEX == 0) { \
      gApeErrors += std::to_string(gCurrentFrame); \
    } else { \
      gApeErrors += std::to_string(gCurrentFrameThread2); \
    } \
    gApeErrors += "]\n\n"; \
    gApeErrors += "["; \
    gApeErrors += std::to_string(exceptionError.GetPlace().Row); \
    gApeErrors += ":"; \
    gApeErrors += std::to_string(exceptionError.GetPlace().Column); \
    gApeErrors += "] "; \
    gApeErrors += exceptionError.GetMessage_(); \
  }
#define mape_set_native_function(a, b, PROCEDURE_NAME, PROCEDURE, c) env.GlobalScope.GetOrCreateValue(PROCEDURE_NAME) = MinScriptLang::Value{PROCEDURE}

#elif defined(GAME_SCRIPT_C)

#if defined(GAME_SCRIPT_C)
GSN_WIN_IMPORT void * gTCCStateCache[2];
GSN_WIN_IMPORT int    gTCCStateRerun[2];
GSN_WIN_IMPORT void (*gTCCStateCacheFrameFunction)(void);
GSN_WIN_IMPORT void (*gTCCStateCacheFrameFunctionThread2)(void);
#endif

#include "libtcc.h"

#define ape_t TCCState
#define ape_object_t void *
#define ape_error_t void
#define ape_check_args(a, b, c, d, e, f) true
#define APE_OBJECT_BOOL 0
#define APE_OBJECT_NUMBER 0
#define APE_OBJECT_STRING 0
#define ape_has_errors(a) false
#define ape_errors_count(a) 0
#define ape_get_error(a, b) 0
#define ape_error_serialize(a, b) 0
#define ape_free_allocated(a, b)
#define ape_clear_errors(a)

static inline void mape_destroy(int threadIndex, TCCState * state) {
  if (gTCCStateRerun[threadIndex] == 1) {
    if (state != 0) {
      tcc_delete(state);
    }
  }
}

void tccMessageCallback(void * opaque, const char * msg);

static inline TCCState * mape_make(int threadIndex) {
  TCCState * state = (TCCState *)gTCCStateCache[threadIndex];
  if (gTCCStateRerun[threadIndex] == 1) {
    if (threadIndex == 0) {
      gTCCStateCacheFrameFunction = 0;
    } else {
      gTCCStateCacheFrameFunctionThread2 = 0;
    }
    state = tcc_new();
    tcc_set_output_type(state, TCC_OUTPUT_MEMORY);
    tcc_set_error_func(state, 0, tccMessageCallback);
    gTCCStateCache[threadIndex] = (void *)state;
  }
  return state;
}

#define mape_compile(THREAD_INDEX, STATE, CODE) \
  if (gTCCStateRerun[THREAD_INDEX] == 1) { \
    int status = tcc_compile_string(STATE, CODE); \
    if (status == -1) { \
      gTCCStateRerun[THREAD_INDEX] = 0; \
    } \
  }

#define mape_set_native_function(THREAD_INDEX, STATE, PROCEDURE_NAME, PROCEDURE, anull) if (gTCCStateRerun[THREAD_INDEX] == 1) { tcc_add_symbol(STATE, #PROCEDURE, (const void *)PROCEDURE); }

// NOTE(Constantine): 2 threads assumption, will bite me in the ass in future.
#define mape_execute(THREAD_INDEX, STATE, CODE) \
  { \
    if (gTCCStateRerun[THREAD_INDEX] == 1) { \
      if (tcc_relocate(STATE, TCC_RELOCATE_AUTO) < 0) { \
        std::lock_guard<std::mutex> __minScriptLangErrorGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_minScriptLangErrorMutex); \
        if (THREAD_INDEX == 1) { \
          gApeErrors += "[Thread 2 Script Error]\n"; \
        } \
        gApeErrors += "Error: tcc_relocate returned < 0.\n"; \
      } \
      if (THREAD_INDEX == 0) { \
        gTCCStateCacheFrameFunction = (void (*)(void))tcc_get_symbol(STATE, "frame"); \
      } else { \
        gTCCStateCacheFrameFunctionThread2 = (void (*)(void))tcc_get_symbol(STATE, "frame"); \
      } \
    } \
    if (THREAD_INDEX == 0) { \
      if (gTCCStateCacheFrameFunction != 0) { \
        gTCCStateCacheFrameFunction(); \
      } else { \
        if (gTCCStateRerun[THREAD_INDEX] == 1) { \
          std::lock_guard<std::mutex> __minScriptLangErrorGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_minScriptLangErrorMutex); \
          gApeErrors += "Error: no \"frame\" procedure found.\nPlease make sure that \"frame\" procedure is defined as \"void frame() { /* Your code here */ }\".\n"; \
        } \
      } \
    } else { \
      if (gTCCStateCacheFrameFunctionThread2 != 0) { \
        gTCCStateCacheFrameFunctionThread2(); \
      } else {\
        if (gTCCStateRerun[THREAD_INDEX] == 1) { \
          std::lock_guard<std::mutex> __minScriptLangErrorGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_minScriptLangErrorMutex); \
          gApeErrors += "[Thread 2 Script Error]\n"; \
          gApeErrors += "Error: no \"frame\" procedure found.\nPlease make sure that \"frame\" procedure is defined as \"void frame() { /* Your code here */ }\".\n"; \
        } \
      } \
    } \
    gTCCStateRerun[THREAD_INDEX] = 0; \
  }

#elif defined(GAME_SCRIPT_NATIVE)

typedef void ape_t;
typedef void ape_error_t;
typedef void * ape_object_t;
#define APE_OBJECT_BOOL 0
#define APE_OBJECT_NUMBER 0
#define APE_OBJECT_STRING 0
#define mape_make(a) 0
#define mape_destroy(a, b)
#define ape_check_args(a, b, c, d, e, f) (true)
#define mape_set_native_function(a, b, c, d, e)
#define ape_has_errors(a) 0
#define ape_errors_count(a) 0
#define ape_get_error(a, b) 0
#define ape_error_serialize(a, b) 0
#define ape_free_allocated(a, b)
#define ape_clear_errors(a)

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

static inline void * ape_object_make_string(ape_t * ape, const char * x) {
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

static inline ape_object_t mape_object_make_array(ape_t * ape, uint64_t count) {
  return (ape_object_t)calloc(1, count * sizeof(double));
}

static inline void mape_object_add_array_number(uint64_t arrayIndex, ape_object_t array, double number) {
  if (array != 0) {
    double * p = (double *)array;
    p[arrayIndex] = number;
  }
}

#elif defined(GAME_SCRIPT)

#include "ape/ape.h"
#ifdef APE_CHECK_ARGS
#undef APE_CHECK_ARGS
#endif
#define mape_destroy(threadIndex, ape) ape_destroy(ape)
#define mape_make(threadIndex) ape_make()
#define mape_execute(threadIndex, ape, script) ape_execute(ape, script)
#define mape_object_make_array(ape, count) ape_object_make_array(ape)
#define mape_object_add_array_number(arrayIndex, array, number) ape_object_add_array_number(array, number)

#else

#error Error

#endif

#define REDGPU_B4_0000 0
#define REDGPU_B4_0001 1
#define REDGPU_B4_0010 2
#define REDGPU_B4_0011 3
#define REDGPU_B4_0100 4
#define REDGPU_B4_0101 5
#define REDGPU_B4_0110 6
#define REDGPU_B4_0111 7
#define REDGPU_B4_1000 8
#define REDGPU_B4_1001 9
#define REDGPU_B4_1010 a
#define REDGPU_B4_1011 b
#define REDGPU_B4_1100 c
#define REDGPU_B4_1101 d
#define REDGPU_B4_1110 e
#define REDGPU_B4_1111 f
#define REDGPU_B4_TO_HEX(b) REDGPU_B4_##b
#if defined(_WIN32) && !defined(__MINGW32__)
#define REDGPU_B8_HEX_MERGE(a,b) 0x##a##b
#define REDGPU_B8_HEX(a,b) REDGPU_B8_HEX_MERGE(a,b)
#define REDGPU_B8(a,b) REDGPU_B8_HEX(REDGPU_B4_TO_HEX(a),REDGPU_B4_TO_HEX(b))
#else
#define REDGPU_B8(a,b) 0b##a##b
#endif
#if defined(_WIN32) && !defined(__MINGW32__)
#define REDGPU_B64_HEX_MERGE(a,b,c,d,e,f,g,h,a1,b1,c1,d1,e1,f1,g1,h1) 0x##a##b##c##d##e##f##g##h##a1##b1##c1##d1##e1##f1##g1##h1
#define REDGPU_B64_HEX(a,b,c,d,e,f,g,h,a1,b1,c1,d1,e1,f1,g1,h1) REDGPU_B64_HEX_MERGE(a,b,c,d,e,f,g,h,a1,b1,c1,d1,e1,f1,g1,h1)
#define REDGPU_B64(a,b,c,d,e,f,g,h,a1,b1,c1,d1,e1,f1,g1,h1) REDGPU_B64_HEX(REDGPU_B4_TO_HEX(a),REDGPU_B4_TO_HEX(b),REDGPU_B4_TO_HEX(c),REDGPU_B4_TO_HEX(d),REDGPU_B4_TO_HEX(e),REDGPU_B4_TO_HEX(f),REDGPU_B4_TO_HEX(g),REDGPU_B4_TO_HEX(h),REDGPU_B4_TO_HEX(a1),REDGPU_B4_TO_HEX(b1),REDGPU_B4_TO_HEX(c1),REDGPU_B4_TO_HEX(d1),REDGPU_B4_TO_HEX(e1),REDGPU_B4_TO_HEX(f1),REDGPU_B4_TO_HEX(g1),REDGPU_B4_TO_HEX(h1))
#else
#define REDGPU_B64(a,b,c,d,e,f,g,h,a1,b1,c1,d1,e1,f1,g1,h1) 0b##a##b##c##d##e##f##g##h##a1##b1##c1##d1##e1##f1##g1##h1
#endif

typedef struct ApeDrawLabelDebugText {
  float       x;
  float       y;
  float       r;
  float       g;
  float       b;
  float       a;
  std::string label;
} ApeDrawLabelDebugText;

typedef struct ApeDrawLabelPoint {
  float       x;
  float       y;
  float       z;
  std::string label;
} ApeDrawLabelPoint;

typedef struct ApeDrawLabelLine {
  float       x0;
  float       y0;
  float       z0;
  float       x1;
  float       y1;
  float       z1;
  std::string label;
} ApeDrawLabelLine;

typedef struct ApeDrawLabelTriangle {
  float       x0;
  float       y0;
  float       z0;
  float       x1;
  float       y1;
  float       z1;
  float       x2;
  float       y2;
  float       z2;
  std::string label;
} ApeDrawLabelTriangle;

typedef enum ApeDrawLabelMeshVertexAttribute {
  APE_DRAW_LABEL_MESH_VERTEX_ATTRIBUTE_NONE      = 0,
  APE_DRAW_LABEL_MESH_VERTEX_ATTRIBUTE_VERTICES  = 1,
  APE_DRAW_LABEL_MESH_VERTEX_ATTRIBUTE_COLORS    = 2,
  APE_DRAW_LABEL_MESH_VERTEX_ATTRIBUTE_TEXCOORDS = 3,
  APE_DRAW_LABEL_MESH_VERTEX_ATTRIBUTE_INDICES   = 4,
} ApeDrawLabelMeshVertexAttribute;

typedef struct float2 {
  float x;
  float y;
} float2;

typedef struct float3 {
  float x;
  float y;
  float z;
} float3;

typedef struct float4 {
  float x;
  float y;
  float z;
  float w;
} float4;

typedef struct ApeDrawLabelMesh {
  RedFHandleMesh                  handle;
  ApeDrawLabelMeshVertexAttribute drawLabelsForAttribute;
  float                           filterDistance;
  int                             raytraceHighlightTriangles;
  std::string                     label;
} ApeDrawLabelMesh;

typedef struct ApeDrawFbo {
  RedFHandleFbo handle;
  float         x;
  float         y;
  float         width;
  float         height;
} ApeDrawFbo;

typedef struct ApeDrawImage {
  RedFHandleImage handle;
  float           x;
  float           y;
  float           z;
  float           w;
  float           h;
} ApeDrawImage;

typedef struct ApeDrawImageSubsection {
  RedFHandleImage handle;
  float           x;
  float           y;
  float           z;
  float           w;
  float           h;
  float           sx;
  float           sy;
  float           sw;
  float           sh;
} ApeDrawImageSubsection;

typedef struct GlobalArrayPersistentOnRerunCallStorage {
  void * storage[4];
} GlobalArrayPersistentOnRerunCallStorage;

typedef struct GlobalKeyPropery {
  unsigned char boolean;
  double        number;
  std::string   astring;
} GlobalKeyPropery;

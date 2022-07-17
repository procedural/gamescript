#include <vector>
#include <unordered_map>
#include <mutex>
#ifdef _WIN32
#include <Windows.h>
#include <chrono>
#else
#include <dlfcn.h>
#endif

#include <soloud_c.h>

// REDGPU includes
#ifdef _WIN32
#include "C:/RedGpuSDK/redgpu.h"
#include "C:/RedGpuSDK/redgpu_wsi.h"
#include "C:/RedGpuSDK/redgpu_array_timestamp.h"
#else
#include "/opt/RedGpuSDK/redgpu.h"
#include "/opt/RedGpuSDK/redgpu_wsi.h"
#include "/opt/RedGpuSDK/redgpu_array_timestamp.h"
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

typedef struct GsKeyEvent {
  volatile uint64_t uniqueKeyId;

  int32_t  deviceId;
  int32_t  source;

  int32_t  action;
  int32_t  flags;
  int32_t  keyCode;
  int32_t  scanCode;
  int32_t  metaState;
  int32_t  repeatCount;
  int64_t  downTime;
  int64_t  eventTime;
} GsKeyEvent;

typedef struct GsMotionEventPointer {
  int32_t pointerId;
  int32_t toolType;
  float   rawX;
  float   rawY;
  float   x;
  float   y;
  float   pressure;
  float   size;
  float   touchMajor;
  float   touchMinor;
  float   toolMajor;
  float   toolMinor;
  float   orientation;
} GsMotionEventPointer;

typedef struct GsMotionEvent {
  volatile uint64_t uniqueMotionId;

  int32_t  deviceId;
  int32_t  source;

  int32_t  action;
  int32_t  flags;
  int32_t  metaState;
  int32_t  buttonState;
  int32_t  edgeFlags;
  int64_t  downTime;
  int64_t  eventTime;
  float    xOffset;
  float    yOffset;
  float    xPrecision;
  float    yPrecision;
  std::vector<GsMotionEventPointer> pointers;
} GsMotionEvent;

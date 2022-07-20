#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <time.h>

#include "ape.h"
#include "script.h"

// NOTE(Constantine): Global variables and procedures from main.cpp.
extern bool                       g_windowsHideAll;
extern bool                       g_windowShowCodeErrors;
extern bool                       g_windowForceShowCodeErrors;
extern std::string                g_codeString;
extern std::string                g_codeStringCopied;
extern bool                       g_runDefaultViewportClearCommands;
extern bool                       g_runScript;
extern std::string                g_codeErrorsString;
extern std::string                g_consoleString;
extern std::mutex                 __g_b042ff2_gsKeyEventsGuardAndSerializeMutex;
extern std::mutex                 __g_b042ff2_gsMotionEventsGuardAndSerializeMutex;
extern volatile uint64_t          g_keyEventsUniqueIdCounter;
extern uint64_t                   g_keyEventsCircularBufferMaxCount;
extern std::vector<GsKeyEvent>    g_keyEvents;
extern volatile uint64_t          g_motionEventsUniqueIdCounter;
extern uint64_t                   g_motionEventsCircularBufferMaxCount;
extern std::vector<GsMotionEvent> g_motionEvents;
extern void *                     gExternalLibraryHandle;
extern void                     (*gExternalLibraryProcedureCall2)(double, double);
extern void                     (*gExternalLibraryProcedureCall3)(double, double, double);
extern bool                       g_frame0CacheEnable;
extern bool                       g_frame0CacheStartPositionIsDirty;
extern uint64_t                   g_frame0CacheStartPosition;
extern bool                       g_compileMode;
extern bool                       g_enableCustomRendering;
static ape_program_t *            g_ape_compiled_program = 0;
extern std::string                g_installedLocationPath;
extern std::string                g_localFolderPath;
extern std::string                g_localCacheFolderPath;
extern std::string                g_temporaryFolderPath;

std::string fileRead   (const char * filepath);
void        fileWrite  (const char * filepath, const char * writeString);
void        fileAppend (const char * filepath, const char * appendString);

// NOTE(Constantine): Global variables.
ape_t *  g_ape          = 0;
uint64_t g_currentFrame = 0;

// NOTE(Constantine): Internals start.

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

#define GS_API
#define GS_C_PROCEDURE_RETURN_TYPE() ape_object_t
#define GS_C_PROCEDURE_PARAMETERS() (ape_t * ape, void * data, int argc, ape_object_t * args)
#define getArgAs_BEGIN(PROCEDURE_NAME)
#define getArgAs_Bool(VARIABLE_TYPE, VARIABLE_NAME, ARG)    VARIABLE_TYPE VARIABLE_NAME = (VARIABLE_TYPE)_getArgAs_Bool(ARG)
#define getArgAs_Double(VARIABLE_TYPE, VARIABLE_NAME, ARG)  VARIABLE_TYPE VARIABLE_NAME = (VARIABLE_TYPE)_getArgAs_Double(ARG)
#define getArgAs_Pointer(VARIABLE_TYPE, VARIABLE_NAME, ARG) VARIABLE_TYPE VARIABLE_NAME = (VARIABLE_TYPE)_getArgAs_Pointer(ARG)
#define getArgAs_CChars(VARIABLE_TYPE, VARIABLE_NAME, ARG)  VARIABLE_TYPE VARIABLE_NAME = (VARIABLE_TYPE)_getArgAs_String(ARG)
#define getArgAs_String(VARIABLE_TYPE, VARIABLE_NAME, ARG)  VARIABLE_TYPE VARIABLE_NAME = (VARIABLE_TYPE)_getArgAs_String(ARG)
#define getArgAs_END
#define mape_object_make_array(ape, count) ape_object_make_array(ape)
#define mape_object_add_array_number(arrayIndex, array, number) ape_object_add_array_number(array, number)

// NOTE(Constantine): Internals end.

typedef struct GlobalKeyPropery {
  unsigned char boolean;
  double        number;
  std::string   astring;
} GlobalKeyPropery;

volatile uint64_t                                      gUniqueNumber = 0;
std::unordered_map<std::string, uint64_t>              gGlobalArrayBytesCount;
std::unordered_map<std::string, void *>                gGlobalArrayPointer;
std::unordered_map<std::string, uint64_t>              gGlobalArrayPersistentBytesCount;
std::unordered_map<std::string, void *>                gGlobalArrayPersistentPointer;
std::unordered_map<std::string, uint64_t>              gGlobalSharedArrayPersistentBytesCount;
std::unordered_map<std::string, void *>                gGlobalSharedArrayPersistentPointer;
std::unordered_map<std::string, std::vector<double> *> gGlobalDynamicArray;
std::unordered_map<std::string, std::vector<double> *> gGlobalDynamicArrayPersistent;
std::map<std::string, std::map<std::string, GlobalKeyPropery> > gKeyProperties;

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureStringDownloadFromUrl GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*url*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("stringDownloadFromUrl")
  getArgAs_CChars(const char *, url, args[_i++]);
  getArgAs_END

  std::string out;

  // NOTE(Constantine): Not supported for now.

  return ape_object_make_string(ape, out.c_str());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureDeviceGetOrientation GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  int32_t orientation = 0;

  // NOTE(Constantine): Not supported for now.

  return ape_object_make_number((double)orientation);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureKeyEventsGetUniqueIdCounter GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  volatile uint64_t counter = 0;
  {
    std::lock_guard<std::mutex> __gsKeyEventsGuardAndSerializeMutexScopeGuard(__g_b042ff2_gsKeyEventsGuardAndSerializeMutex);

    counter = g_keyEventsUniqueIdCounter;
  }

  return ape_object_make_number((double)counter);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMotionEventsGetUniqueIdCounter GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  volatile uint64_t counter = 0;
  {
    std::lock_guard<std::mutex> __gsMotionEventsGuardAndSerializeMutexScopeGuard(__g_b042ff2_gsMotionEventsGuardAndSerializeMutex);

    counter = g_motionEventsUniqueIdCounter;
  }

  return ape_object_make_number((double)counter);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureKeyEventsGetCircularBufferMaxCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  volatile uint64_t maxCount = 0;
  {
    std::lock_guard<std::mutex> __gsKeyEventsGuardAndSerializeMutexScopeGuard(__g_b042ff2_gsKeyEventsGuardAndSerializeMutex);

    maxCount = g_keyEventsCircularBufferMaxCount;
  }

  return ape_object_make_number((double)maxCount);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMotionEventsGetCircularBufferMaxCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  volatile uint64_t maxCount = 0;
  {
    std::lock_guard<std::mutex> __gsMotionEventsGuardAndSerializeMutexScopeGuard(__g_b042ff2_gsMotionEventsGuardAndSerializeMutex);

    maxCount = g_motionEventsCircularBufferMaxCount;
  }

  return ape_object_make_number((double)maxCount);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureKeyEventsSetCircularBufferMaxCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*maxCount*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("keyEventsSetCircularBufferMaxCount")
  getArgAs_Double(uint64_t, maxCount, args[_i++]);
  getArgAs_END

  {
    std::lock_guard<std::mutex> __gsKeyEventsGuardAndSerializeMutexScopeGuard(__g_b042ff2_gsKeyEventsGuardAndSerializeMutex);

    g_keyEventsCircularBufferMaxCount = maxCount;
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMotionEventsSetCircularBufferMaxCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*maxCount*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("motionEventsSetCircularBufferMaxCount")
  getArgAs_Double(uint64_t, maxCount, args[_i++]);
  getArgAs_END

  {
    std::lock_guard<std::mutex> __gsMotionEventsGuardAndSerializeMutexScopeGuard(__g_b042ff2_gsMotionEventsGuardAndSerializeMutex);

    g_motionEventsCircularBufferMaxCount = maxCount;
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureKeyEventsGetEvent GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*keyEventsCircularBufferIndex*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("keyEventsGetEvent")
  getArgAs_Double(uint64_t, keyEventsCircularBufferIndex, args[_i++]);
  getArgAs_END

  GsKeyEvent anevent = {};
  {
    std::lock_guard<std::mutex> __gsKeyEventsGuardAndSerializeMutexScopeGuard(__g_b042ff2_gsKeyEventsGuardAndSerializeMutex);

    anevent = g_keyEvents[keyEventsCircularBufferIndex];
  }

  ape_object_t array = mape_object_make_array(ape, 11);
  mape_object_add_array_number(0, array, (double)anevent.uniqueKeyId);
  mape_object_add_array_number(1, array, (double)anevent.deviceId);
  mape_object_add_array_number(2, array, (double)anevent.source);
  mape_object_add_array_number(3, array, (double)anevent.action);
  mape_object_add_array_number(4, array, (double)anevent.flags);
  mape_object_add_array_number(5, array, (double)anevent.keyCode);
  mape_object_add_array_number(6, array, (double)anevent.scanCode);
  mape_object_add_array_number(7, array, (double)anevent.metaState);
  mape_object_add_array_number(8, array, (double)anevent.repeatCount);
  mape_object_add_array_number(9, array, (double)anevent.downTime);
  mape_object_add_array_number(10, array, (double)anevent.eventTime);
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMotionEventsGetEvent GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*motionEventsCircularBufferIndex*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("motionEventsGetEvent")
  getArgAs_Double(uint64_t, motionEventsCircularBufferIndex, args[_i++]);
  getArgAs_END

  GsMotionEvent anevent = {};
  {
    std::lock_guard<std::mutex> __gsMotionEventsGuardAndSerializeMutexScopeGuard(__g_b042ff2_gsMotionEventsGuardAndSerializeMutex);

    anevent = g_motionEvents[motionEventsCircularBufferIndex];
  }

  ape_object_t array = mape_object_make_array(ape, 15);
  mape_object_add_array_number(0, array, (double)anevent.uniqueMotionId);
  mape_object_add_array_number(1, array, (double)anevent.deviceId);
  mape_object_add_array_number(2, array, (double)anevent.source);
  mape_object_add_array_number(3, array, (double)anevent.action);
  mape_object_add_array_number(4, array, (double)anevent.flags);
  mape_object_add_array_number(5, array, (double)anevent.metaState);
  mape_object_add_array_number(6, array, (double)anevent.buttonState);
  mape_object_add_array_number(7, array, (double)anevent.edgeFlags);
  mape_object_add_array_number(8, array, (double)anevent.downTime);
  mape_object_add_array_number(9, array, (double)anevent.eventTime);
  mape_object_add_array_number(10, array, (double)anevent.xOffset);
  mape_object_add_array_number(11, array, (double)anevent.yOffset);
  mape_object_add_array_number(12, array, (double)anevent.xPrecision);
  mape_object_add_array_number(13, array, (double)anevent.yPrecision);
  mape_object_add_array_number(14, array, (double)anevent.pointers.size());
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureMotionEventsGetEventPointer GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*motionEventsCircularBufferIndex*/,
    APE_OBJECT_NUMBER/*pointerIndex*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("motionEventsGetEvent")
  getArgAs_Double(uint64_t, motionEventsCircularBufferIndex, args[_i++]);
  getArgAs_Double(uint64_t, pointerIndex, args[_i++]);
  getArgAs_END

  GsMotionEventPointer pointer = {};
  {
    std::lock_guard<std::mutex> __gsMotionEventsGuardAndSerializeMutexScopeGuard(__g_b042ff2_gsMotionEventsGuardAndSerializeMutex);

    pointer = g_motionEvents[motionEventsCircularBufferIndex].pointers[pointerIndex];
  }

  ape_object_t array = mape_object_make_array(ape, 13);
  mape_object_add_array_number(0, array, (double)pointer.pointerId);
  mape_object_add_array_number(1, array, (double)pointer.toolType);
  mape_object_add_array_number(2, array, (double)pointer.rawX);
  mape_object_add_array_number(3, array, (double)pointer.rawY);
  mape_object_add_array_number(4, array, (double)pointer.x);
  mape_object_add_array_number(5, array, (double)pointer.y);
  mape_object_add_array_number(6, array, (double)pointer.pressure);
  mape_object_add_array_number(7, array, (double)pointer.size);
  mape_object_add_array_number(8, array, (double)pointer.touchMajor);
  mape_object_add_array_number(9, array, (double)pointer.touchMinor);
  mape_object_add_array_number(10, array, (double)pointer.toolMajor);
  mape_object_add_array_number(11, array, (double)pointer.toolMinor);
  mape_object_add_array_number(12, array, (double)pointer.orientation);
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePrintConsoleClear GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  g_consoleString.clear();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedurePrintConsole GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*string*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("printConsole")
  getArgAs_CChars(const char *, astring, args[_i++]);
  getArgAs_END

  std::string cppstring = astring;
  g_consoleString += cppstring;

  return ape_object_make_null();
}

void * getInitDataPointer();

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetGameScriptRedGpuVersionInitDataPointer GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number(_gsPointerToNumber(getInitDataPointer()));
}

void * getWindowDataPointer();

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetGameScriptRedGpuVersionWindowDataPointer GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number(_gsPointerToNumber(getWindowDataPointer()));
}

void windowSetTitle(const char * title);

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureWindowSetTitle GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*title*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("windowSetTitle")
  getArgAs_CChars(const char *, title, args[_i++]);
  getArgAs_END

  windowSetTitle(title);

  return ape_object_make_null();
}

float windowGetWidth();

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureWindowGetWidth GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)windowGetWidth());
}

float windowGetHeight();

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureWindowGetHeight GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)windowGetHeight());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetCurrentFrame GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)g_currentFrame);
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

  g_currentFrame = frame;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetRandomNumber GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)rand());
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureIsLinux GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

#if defined(__ANDROID__)
  return ape_object_make_bool(false);
#elif defined(__linux__)
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

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureIsAndroid GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

#ifdef __ANDROID__
  return ape_object_make_bool(true);
#else
  return ape_object_make_bool(false);
#endif
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureIsWindowsPlatform GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

#ifdef __ANDROID__
  return ape_object_make_bool(false);
#else
  return ape_object_make_bool(true);
#endif
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSetAllWindowsHidden GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_BOOL/*enable*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("setAllWindowsHidden")
  getArgAs_Bool(bool, enable, args[_i++]);
  getArgAs_END

  g_windowsHideAll = enable;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureAreAllWindowsHidden GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_bool(g_windowsHideAll);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureToggleDefaultViewportClearCommands GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_BOOL/*enable*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("toggleDefaultViewportClearCommands")
  getArgAs_Bool(bool, enable, args[_i++]);
  getArgAs_END

  g_runDefaultViewportClearCommands = enable;

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
    void * possiblyAlreadyExistingPointer = gGlobalArrayPointer[label];
    if (possiblyAlreadyExistingPointer != 0) {
      return ape_object_make_number(_gsPointerToNumber(possiblyAlreadyExistingPointer));
    }
  }

  if (count == 0) {
    return ape_object_make_number(0.0);
  }

  void * pointer = calloc(1, count * sizeof(unsigned char));
  gGlobalArrayBytesCount[label] = count;
  gGlobalArrayPointer[label]    = pointer;

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
    void * possiblyAlreadyExistingPointer = gGlobalArrayPersistentPointer[label];
    if (possiblyAlreadyExistingPointer != 0) {
      return ape_object_make_number(_gsPointerToNumber(possiblyAlreadyExistingPointer));
    }
  }

  if (count == 0) {
    return ape_object_make_number(0.0);
  }

  void * pointer = calloc(1, count * sizeof(unsigned char));
  gGlobalArrayPersistentBytesCount[label] = count;
  gGlobalArrayPersistentPointer[label]    = pointer;

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

  void * pointer = gGlobalArrayPointer[label];
  free(pointer);

  gGlobalArrayBytesCount.erase(label);
  gGlobalArrayPointer.erase(label);

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

  void * pointer = gGlobalArrayPersistentPointer[label];
  free(pointer);

  gGlobalArrayPersistentBytesCount.erase(label);
  gGlobalArrayPersistentPointer.erase(label);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalArrayDeleteAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  for (auto & kv : gGlobalArrayPointer) {
    free(kv.second);
  }

  gGlobalArrayBytesCount.clear();
  gGlobalArrayPointer.clear();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalArrayPersistentDeleteAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  for (auto & kv : gGlobalArrayPersistentPointer) {
    free(kv.second);
  }

  gGlobalArrayPersistentBytesCount.clear();
  gGlobalArrayPersistentPointer.clear();

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

  return ape_object_make_number((double)gGlobalArrayBytesCount[label]);
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

  return ape_object_make_number(_gsPointerToNumber(gGlobalArrayPointer[label]));
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

  return ape_object_make_number((double)gGlobalArrayPersistentBytesCount[label]);
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

  return ape_object_make_number(_gsPointerToNumber(gGlobalArrayPersistentPointer[label]));
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
    void * possiblyAlreadyExistingPointer = gGlobalDynamicArray[label];
    if (possiblyAlreadyExistingPointer != 0) {
      return ape_object_make_number(_gsPointerToNumber(possiblyAlreadyExistingPointer));
    }
  }

  std::vector<double> * pointer = new(std::nothrow) std::vector<double>();
  gGlobalDynamicArray[label] = pointer;

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
    void * possiblyAlreadyExistingPointer = gGlobalDynamicArrayPersistent[label];
    if (possiblyAlreadyExistingPointer != 0) {
      return ape_object_make_number(_gsPointerToNumber(possiblyAlreadyExistingPointer));
    }
  }

  std::vector<double> * pointer = new(std::nothrow) std::vector<double>();
  gGlobalDynamicArrayPersistent[label] = pointer;

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

  std::vector<double> * pointer = gGlobalDynamicArray[label];
  delete pointer;

  gGlobalDynamicArray.erase(label);

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

  std::vector<double> * pointer = gGlobalDynamicArrayPersistent[label];
  delete pointer;

  gGlobalDynamicArrayPersistent.erase(label);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalDynamicArrayDeleteAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  for (auto & kv : gGlobalDynamicArray) {
    delete kv.second;
  }

  gGlobalDynamicArray.clear();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalDynamicArrayPersistentDeleteAll GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  for (auto & kv : gGlobalDynamicArrayPersistent) {
    delete kv.second;
  }

  gGlobalDynamicArrayPersistent.clear();

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

  return ape_object_make_number(_gsPointerToNumber(gGlobalDynamicArray[label]));
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

  return ape_object_make_number(_gsPointerToNumber(gGlobalDynamicArrayPersistent[label]));
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

int gamepadIsPresent(int gamepadId);

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGamepadIsPresent GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*gamepadId0to15*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("gamepadIsPresent")
  getArgAs_Double(int, gamepadId, args[_i++]);
  getArgAs_END

  int isPresent = gamepadIsPresent(gamepadId);

  return ape_object_make_bool((bool)isPresent);
}

void gamepadGet15Buttons6AxesNumbers(int gamepadId, double * out15Buttons, double * out6Axes);

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGamepadGet15Buttons6AxesNumbers GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*gamepadId0to15*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("gamepadGet15Buttons6AxesNumbers")
  getArgAs_Double(int, gamepadId, args[_i++]);
  getArgAs_END

  double buttons[15] = {};
  double axes[6]     = {};

  gamepadGet15Buttons6AxesNumbers(gamepadId, buttons, axes);

  ape_object_t array = mape_object_make_array(ape, 21);
  mape_object_add_array_number(0,  array, buttons[0]);
  mape_object_add_array_number(1,  array, buttons[1]);
  mape_object_add_array_number(2,  array, buttons[2]);
  mape_object_add_array_number(3,  array, buttons[3]);
  mape_object_add_array_number(4,  array, buttons[4]);
  mape_object_add_array_number(5,  array, buttons[5]);
  mape_object_add_array_number(6,  array, buttons[6]);
  mape_object_add_array_number(7,  array, buttons[7]);
  mape_object_add_array_number(8,  array, buttons[8]);
  mape_object_add_array_number(9,  array, buttons[9]);
  mape_object_add_array_number(10, array, buttons[10]);
  mape_object_add_array_number(11, array, buttons[11]);
  mape_object_add_array_number(12, array, buttons[12]);
  mape_object_add_array_number(13, array, buttons[13]);
  mape_object_add_array_number(14, array, buttons[14]);
  mape_object_add_array_number(15, array, axes[0]);
  mape_object_add_array_number(16, array, axes[1]);
  mape_object_add_array_number(17, array, axes[2]);
  mape_object_add_array_number(18, array, axes[3]);
  mape_object_add_array_number(19, array, axes[4]);
  mape_object_add_array_number(20, array, axes[5]);
  return array;
}

int gamepadUpdateGamepadMappings(const char * mappings);

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGamepadUpdateGamecontrollerdbTxt GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*gamepadId0to15*/,
    APE_OBJECT_STRING/*mappings*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("gamepadUpdateGamecontrollerdbTxt")
  getArgAs_Double(int,          gamepadId, args[_i++]); // NOTE(Constantine): Just noticed gamepadId is not needed here. Will have to leave it as is for API stability.
  getArgAs_CChars(const char *, mappings,  args[_i++]);
  getArgAs_END

  int success = gamepadUpdateGamepadMappings(mappings);

  return ape_object_make_bool((bool)success);
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

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetTimeClockRealTimeSecAndNsec GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  struct timespec t = {};
#if defined(__linux__) || defined(__ANDROID__)
  clock_gettime(CLOCK_REALTIME, &t);
#endif

  ape_object_t array = mape_object_make_array(ape, 2);
  mape_object_add_array_number(0, array, (double)t.tv_sec);
  mape_object_add_array_number(1, array, (double)t.tv_nsec);
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetTimeClockMonotonicSecAndNsec GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  struct timespec t = {};
#if defined(__linux__) || defined(__ANDROID__)
  clock_gettime(CLOCK_MONOTONIC, &t);
#endif

  ape_object_t array = mape_object_make_array(ape, 2);
  mape_object_add_array_number(0, array, (double)t.tv_sec);
  mape_object_add_array_number(1, array, (double)t.tv_nsec);
  return array;
}

void igSetStyleColor(uint64_t colorIndex, float r, float g, float b, float a);
bool igBegin(const char * name, bool * p_open, int flags);
void igEnd();
bool igButton(const char * label, float sizeX, float sizeY);
void igTextUnformatted(const char * text);
bool igInputTextMultiline(const char * label, char * buf, size_t buf_size, float sizeX, float sizeY, int flags, void * callback, void * user_data);
bool igInputText(const char * label, char * buf, size_t buf_size, int flags, void * callback, void * user_data);
void igRender();

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImguiSetStyleColor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*colorIndex*/,
    APE_OBJECT_NUMBER/*r*/,
    APE_OBJECT_NUMBER/*g*/,
    APE_OBJECT_NUMBER/*b*/,
    APE_OBJECT_NUMBER/*a*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imguiSetStyleColor")
  getArgAs_Double(uint64_t, colorIndex, args[_i++]);
  getArgAs_Double(float, r, args[_i++]);
  getArgAs_Double(float, g, args[_i++]);
  getArgAs_Double(float, b, args[_i++]);
  getArgAs_Double(float, a, args[_i++]);
  getArgAs_END

  igSetStyleColor(colorIndex, r, g, b, a);

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

  getArgAs_BEGIN("imguiWindowBegin")
  getArgAs_CChars(const char *,     windowName,           args[_i++]);
  getArgAs_Pointer(unsigned char *, outPointer,           args[_i++]);
  getArgAs_Double(uint64_t,         outPointerBytesFirst, args[_i++]);
  getArgAs_END

  return ape_object_make_bool(igBegin(windowName, (bool *)&outPointer[outPointerBytesFirst], 0));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImguiWindowEnd GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

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

  getArgAs_BEGIN("imguiButton")
  getArgAs_CChars(const char *, buttonName,   args[_i++]);
  getArgAs_Double(float,        buttonWidth,  args[_i++]);
  getArgAs_Double(float,        buttonHeight, args[_i++]);
  getArgAs_END

  return ape_object_make_bool(igButton(buttonName, buttonWidth, buttonHeight));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureImguiTextUnformatted GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*text*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("imguiTextUnformatted")
  getArgAs_CChars(const char *, text, args[_i++]);
  getArgAs_END

  igTextUnformatted(text);

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

  getArgAs_BEGIN("imguiTextMultiline")
  getArgAs_CChars(const char *, textFieldName,   args[_i++]);
  getArgAs_String(std::string,  text,            args[_i++]);
  getArgAs_Double(float,        textFieldWidth,  args[_i++]);
  getArgAs_Double(float,        textFieldHeight, args[_i++]);
  getArgAs_END

  return ape_object_make_bool(igInputTextMultiline(textFieldName, &text[0], text.size(), textFieldWidth, textFieldHeight, 1 << 14/*ImGuiInputTextFlags_ReadOnly*/, 0, 0));
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

  getArgAs_BEGIN("imguiInputTextMultiline")
  getArgAs_CChars(const char *, textFieldName,           args[_i++]);
  getArgAs_Pointer(char *,      outPointer,              args[_i++]);
  getArgAs_Double(uint64_t,     outPointerBytesFirst,    args[_i++]);
  getArgAs_Double(uint64_t,     outPointerBytesCountMax, args[_i++]);
  getArgAs_Double(float,        textFieldWidth,          args[_i++]);
  getArgAs_Double(float,        textFieldHeight,         args[_i++]);
  getArgAs_END

  return ape_object_make_bool(igInputTextMultiline(textFieldName, &outPointer[outPointerBytesFirst], outPointerBytesCountMax, textFieldWidth, textFieldHeight, 0, 0, 0));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGameScriptRedGpuVersionGetEnableCustomRendering GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_bool(g_enableCustomRendering);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGameScriptRedGpuVersionSetEnableCustomRendering GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_BOOL/*enable*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("gameScriptRedGpuVersionSetEnableCustomRendering")
  getArgAs_Bool(bool, enable, args[_i++]);
  getArgAs_END

  g_enableCustomRendering = enable;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGameScriptRedGpuVersionImguiRender GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  igRender();

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetUniqueNumber GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  gUniqueNumber += 1;

  return ape_object_make_number((double)gUniqueNumber);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetUint64Max GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_number((double)((uint64_t)-1));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetGameScriptString GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  if (g_codeString.empty() == false) {
    return ape_object_make_string(ape, g_codeString.c_str());
  } else {
    return ape_object_make_string(ape, "");
  }
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSetGameScriptString GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*script*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("setGameScriptString")
  getArgAs_CChars(const char *, script, args[_i++]);
  getArgAs_END

  g_frame0CacheStartPositionIsDirty = true;
  g_codeString = script;

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

#if defined(__linux__) || defined(__ANDROID__)
  if (gExternalLibraryHandle != 0) {
    dlclose(gExternalLibraryHandle);
    gExternalLibraryHandle = 0;
  }
#if defined(__ANDROID__)
  gExternalLibraryHandle = dlopen("/storage/emulated/0/Download/libgame_script_external_procedure.so", RTLD_NOW | RTLD_GLOBAL);
#elif defined(__linux__)
  gExternalLibraryHandle = dlopen("libgame_script_external_procedure.so", RTLD_NOW | RTLD_GLOBAL);
#endif
  if (gExternalLibraryHandle != 0) {
    gExternalLibraryProcedureCall2 = (void (*)(double, double))dlsym(gExternalLibraryHandle, "libGameScriptExternalProcedureCall2");
    gExternalLibraryProcedureCall3 = (void (*)(double, double, double))dlsym(gExternalLibraryHandle, "libGameScriptExternalProcedureCall3");
  } else {
    if (printErrors == true) {
#if defined(__ANDROID__)
      g_codeErrorsString += "[Game Script][libGameScriptExternalProcedureReload][dlopen(\"/storage/emulated/0/Download/libgame_script_external_procedure.so\") returned NULL]\n";
#elif defined(__linux__)
      g_codeErrorsString += "[Game Script][libGameScriptExternalProcedureReload][dlopen(\"libgame_script_external_procedure.so\") returned NULL]\n";
#endif
      std::string error = dlerror();
      g_codeErrorsString += error;
    }
  }
#endif

#if defined(_WIN32)
  if (gExternalLibraryHandle != 0) {
    FreeLibrary((HMODULE)gExternalLibraryHandle);
    gExternalLibraryHandle = 0;
  }
  gExternalLibraryHandle = LoadLibraryA("game_script_external_procedure.dll");
  if (gExternalLibraryHandle != 0) {
    gExternalLibraryProcedureCall2 = (void (*)(double, double))GetProcAddress((HMODULE)gExternalLibraryHandle, "libGameScriptExternalProcedureCall2");
    gExternalLibraryProcedureCall3 = (void (*)(double, double, double))GetProcAddress((HMODULE)gExternalLibraryHandle, "libGameScriptExternalProcedureCall3");
  } else {
    if (printErrors == true) {
      g_codeErrorsString += "[Game Script][libGameScriptExternalProcedureReload][LoadLibraryA(\"game_script_external_procedure.dll\") returned NULL]\n";
    }
  }
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
  g_codeErrorsString += msg;
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
  //GS_MACRO_RED_STRUCT(RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1)
  //GS_MACRO_RED_STRUCT(RedProcedureComputingLanguageStateExtensionIterator)
  //GS_MACRO_RED_STRUCT(RedProcedureComputingLanguageSpecializationConstant)
  //GS_MACRO_RED_STRUCT(RedProcedureComputingLanguageStateExtensionSpecializationConstants)
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
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo1, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, optionalInfo)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, next)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, supportsComputingLanguageFeatureLevel1)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageStateExtensionIterator, extension)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionIterator, next)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageSpecializationConstant, specId)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageSpecializationConstant, specDataBytesFirst)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureComputingLanguageSpecializationConstant, specDataBytesCount)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureComputingLanguageStateExtension, RedProcedureComputingLanguageStateExtensionSpecializationConstants, extension)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, next)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specsCount)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedProcedureComputingLanguageSpecializationConstant *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specs)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specDataBytesCount)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specData)
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
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedGpuInfoOptionalInfo1, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, optionalInfo)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, next)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedBool32, RedGpuInfoOptionalInfoComputingLanguageFeatureLevel1, supportsComputingLanguageFeatureLevel1)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageStateExtensionIterator, extension)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionIterator, next)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageSpecializationConstant, specId)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageSpecializationConstant, specDataBytesFirst)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureComputingLanguageSpecializationConstant, specDataBytesCount)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, RedProcedureComputingLanguageStateExtension, RedProcedureComputingLanguageStateExtensionSpecializationConstants, extension)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, next)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_U32, unsigned, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specsCount)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const RedProcedureComputingLanguageSpecializationConstant *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specs)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_SIZE_T, size_t, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specDataBytesCount)
  //GS_MACRO_RED_STRUCT_MEMBER(GS_STRUCT_MEMBER_TYPE_VOID_POINTER, const void *, RedProcedureComputingLanguageStateExtensionSpecializationConstants, specData)
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
  RedContext context = 0;
  redCreateContext(malloc, free, 0, 0, enableDebugMode == 1 ? redHelperDebugCallback : 0, RED_SDK_VERSION_1_0_135, sizeof(extensions) / sizeof(extensions[0]), extensions, 0, 0, 0, 0, 0, &context, 0, 0, 0, 0);

  return ape_object_make_number(_gsPointerToNumber((void *)context));
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
  getArgAs_Pointer(RedHandleMemory, mappableMemory,           args[_i++]);
  getArgAs_Double(uint64_t,         mappableMemoryBytesFirst, args[_i++]);
  getArgAs_Double(uint64_t,         mappableMemoryBytesCount, args[_i++]);
  getArgAs_Pointer(RedStatuses *,   outStatuses,              args[_i++]);
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

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalKeyPropertyGetKeyLabelsCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  double out = 0;
  {
    //std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
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
    //std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
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
    //std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
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
    //std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
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
    //std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
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
    //std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
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
    //std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
    gKeyProperties.erase(key);
  }

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGlobalKeyPropertyRemoveAllKeys GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  {
    //std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
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
    //std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
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
    //std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
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
    //std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
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
    //std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
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
    //std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
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
    //std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
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
    //std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
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
    //std::lock_guard<std::mutex> __keyPropertiesGuardAndSerializeMutexScopeGuard(__GAME_SCRIPT_GLOBAL_79733b2c98923d0b376d9a922e0fac4e44beb2e6_keyPropertiesMutex);
    value = gKeyProperties[key][property].boolean;
  }

  return ape_object_make_bool(value == 0 ? false : true);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_destroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_destroy")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  Soloud_destroy(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_create GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  void * value = Soloud_create();

  return ape_object_make_number(_gsPointerToNumber(value));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_initEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aFlags*/,
    APE_OBJECT_NUMBER/*aBackend*/,
    APE_OBJECT_NUMBER/*aSamplerate*/,
    APE_OBJECT_NUMBER/*aBufferSize*/,
    APE_OBJECT_NUMBER/*aChannels*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_initEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aFlags, args[_i++]);
  getArgAs_Double(unsigned, aBackend, args[_i++]);
  getArgAs_Double(unsigned, aSamplerate, args[_i++]);
  getArgAs_Double(unsigned, aBufferSize, args[_i++]);
  getArgAs_Double(unsigned, aChannels, args[_i++]);
  getArgAs_END

  int value = Soloud_initEx(aClassPtr, aFlags, aBackend, aSamplerate, aBufferSize, aChannels);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_deinit GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_deinit")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  Soloud_deinit(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getVersion GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getVersion")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  unsigned value = Soloud_getVersion(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getErrorString GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aErrorCode*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getErrorString")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aErrorCode, args[_i++]);
  getArgAs_END

  const char * value = Soloud_getErrorString(aClassPtr, aErrorCode);

  return ape_object_make_string(ape, value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getBackendId GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getBackendId")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  unsigned value = Soloud_getBackendId(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getBackendString GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getBackendString")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  const char * value = Soloud_getBackendString(aClassPtr);

  return ape_object_make_string(ape, value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getBackendChannels GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getBackendChannels")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  unsigned value = Soloud_getBackendChannels(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getBackendSamplerate GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getBackendSamplerate")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  unsigned value = Soloud_getBackendSamplerate(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getBackendBufferSize GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getBackendBufferSize")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  unsigned value = Soloud_getBackendBufferSize(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setSpeakerPosition GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aChannel*/,
    APE_OBJECT_NUMBER/*aX*/,
    APE_OBJECT_NUMBER/*aY*/,
    APE_OBJECT_NUMBER/*aZ*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setSpeakerPosition")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aChannel, args[_i++]);
  getArgAs_Double(float, aX, args[_i++]);
  getArgAs_Double(float, aY, args[_i++]);
  getArgAs_Double(float, aZ, args[_i++]);
  getArgAs_END

  int value = Soloud_setSpeakerPosition(aClassPtr, aChannel, aX, aY, aZ);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getSpeakerPosition GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aChannel*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getSpeakerPosition")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aChannel, args[_i++]);
  getArgAs_END

  float x = 0;
  float y = 0;
  float z = 0;
  int value = Soloud_getSpeakerPosition(aClassPtr, aChannel, &x, &y, &z);

  ape_object_t array = mape_object_make_array(ape, 4);
  mape_object_add_array_number(0, array, (double)x);
  mape_object_add_array_number(1, array, (double)y);
  mape_object_add_array_number(2, array, (double)z);
  mape_object_add_array_number(3, array, (double)value);
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_playEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aSound*/,
    APE_OBJECT_NUMBER/*aVolume*/,
    APE_OBJECT_NUMBER/*aPan*/,
    APE_OBJECT_NUMBER/*aPaused*/,
    APE_OBJECT_NUMBER/*aBus*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_playEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioSource *, aSound, args[_i++]);
  getArgAs_Double(float, aVolume, args[_i++]);
  getArgAs_Double(float, aPan, args[_i++]);
  getArgAs_Double(int, aPaused, args[_i++]);
  getArgAs_Double(unsigned, aBus, args[_i++]);
  getArgAs_END

  unsigned value = Soloud_playEx(aClassPtr, aSound, aVolume, aPan, aPaused, aBus);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_playClockedEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aSoundTime*/,
    APE_OBJECT_NUMBER/*aSound*/,
    APE_OBJECT_NUMBER/*aVolume*/,
    APE_OBJECT_NUMBER/*aPan*/,
    APE_OBJECT_NUMBER/*aBus*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_playClockedEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(double, aSoundTime, args[_i++]);
  getArgAs_Pointer(AudioSource *, aSound, args[_i++]);
  getArgAs_Double(float, aVolume, args[_i++]);
  getArgAs_Double(float, aPan, args[_i++]);
  getArgAs_Double(unsigned, aBus, args[_i++]);
  getArgAs_END

  unsigned value = Soloud_playClockedEx(aClassPtr, aSoundTime, aSound, aVolume, aPan, aBus);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_play3dEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aSound*/,
    APE_OBJECT_NUMBER/*aPosX*/,
    APE_OBJECT_NUMBER/*aPosY*/,
    APE_OBJECT_NUMBER/*aPosZ*/,
    APE_OBJECT_NUMBER/*aVelX*/,
    APE_OBJECT_NUMBER/*aVelY*/,
    APE_OBJECT_NUMBER/*aVelZ*/,
    APE_OBJECT_NUMBER/*aVolume*/,
    APE_OBJECT_NUMBER/*aPaused*/,
    APE_OBJECT_NUMBER/*aBus*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_play3dEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioSource *, aSound, args[_i++]);
  getArgAs_Double(float, aPosX, args[_i++]);
  getArgAs_Double(float, aPosY, args[_i++]);
  getArgAs_Double(float, aPosZ, args[_i++]);
  getArgAs_Double(float, aVelX, args[_i++]);
  getArgAs_Double(float, aVelY, args[_i++]);
  getArgAs_Double(float, aVelZ, args[_i++]);
  getArgAs_Double(float, aVolume, args[_i++]);
  getArgAs_Double(int, aPaused, args[_i++]);
  getArgAs_Double(unsigned, aBus, args[_i++]);
  getArgAs_END

  unsigned value = Soloud_play3dEx(aClassPtr, aSound, aPosX, aPosY, aPosZ, aVelX, aVelY, aVelZ, aVolume, aPaused, aBus);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_play3dClockedEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aSoundTime*/,
    APE_OBJECT_NUMBER/*aSound*/,
    APE_OBJECT_NUMBER/*aPosX*/,
    APE_OBJECT_NUMBER/*aPosY*/,
    APE_OBJECT_NUMBER/*aPosZ*/,
    APE_OBJECT_NUMBER/*aVelX*/,
    APE_OBJECT_NUMBER/*aVelY*/,
    APE_OBJECT_NUMBER/*aVelZ*/,
    APE_OBJECT_NUMBER/*aVolume*/,
    APE_OBJECT_NUMBER/*aBus*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_play3dClockedEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(double, aSoundTime, args[_i++]);
  getArgAs_Pointer(AudioSource *, aSound, args[_i++]);
  getArgAs_Double(float, aPosX, args[_i++]);
  getArgAs_Double(float, aPosY, args[_i++]);
  getArgAs_Double(float, aPosZ, args[_i++]);
  getArgAs_Double(float, aVelX, args[_i++]);
  getArgAs_Double(float, aVelY, args[_i++]);
  getArgAs_Double(float, aVelZ, args[_i++]);
  getArgAs_Double(float, aVolume, args[_i++]);
  getArgAs_Double(unsigned, aBus, args[_i++]);
  getArgAs_END

  unsigned value = Soloud_play3dClockedEx(aClassPtr, aSoundTime, aSound, aPosX, aPosY, aPosZ, aVelX, aVelY, aVelZ, aVolume, aBus);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_playBackgroundEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aSound*/,
    APE_OBJECT_NUMBER/*aVolume*/,
    APE_OBJECT_NUMBER/*aPaused*/,
    APE_OBJECT_NUMBER/*aBus*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_playBackgroundEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioSource *, aSound, args[_i++]);
  getArgAs_Double(float, aVolume, args[_i++]);
  getArgAs_Double(int, aPaused, args[_i++]);
  getArgAs_Double(unsigned, aBus, args[_i++]);
  getArgAs_END

  unsigned value = Soloud_playBackgroundEx(aClassPtr, aSound, aVolume, aPaused, aBus);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_seek GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aSeconds*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_seek")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(double, aSeconds, args[_i++]);
  getArgAs_END

  int value = Soloud_seek(aClassPtr, aVoiceHandle, aSeconds);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_stop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_stop")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_END

  Soloud_stop(aClassPtr, aVoiceHandle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_stopAll GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_stopAll")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  Soloud_stopAll(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_stopAudioSource GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aSound*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_stopAudioSource")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioSource *, aSound, args[_i++]);
  getArgAs_END

  Soloud_stopAudioSource(aClassPtr, aSound);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_countAudioSource GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aSound*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_countAudioSource")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioSource *, aSound, args[_i++]);
  getArgAs_END

  int value = Soloud_countAudioSource(aClassPtr, aSound);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setFilterParameter GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aFilterId*/,
    APE_OBJECT_NUMBER/*aAttributeId*/,
    APE_OBJECT_NUMBER/*aValue*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setFilterParameter")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(unsigned, aFilterId, args[_i++]);
  getArgAs_Double(unsigned, aAttributeId, args[_i++]);
  getArgAs_Double(float, aValue, args[_i++]);
  getArgAs_END

  Soloud_setFilterParameter(aClassPtr, aVoiceHandle, aFilterId, aAttributeId, aValue);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getFilterParameter GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aFilterId*/,
    APE_OBJECT_NUMBER/*aAttributeId*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getFilterParameter")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(unsigned, aFilterId, args[_i++]);
  getArgAs_Double(unsigned, aAttributeId, args[_i++]);
  getArgAs_END

  float value = Soloud_getFilterParameter(aClassPtr, aVoiceHandle, aFilterId, aAttributeId);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_fadeFilterParameter GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aFilterId*/,
    APE_OBJECT_NUMBER/*aAttributeId*/,
    APE_OBJECT_NUMBER/*aTo*/,
    APE_OBJECT_NUMBER/*aTime*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_fadeFilterParameter")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(unsigned, aFilterId, args[_i++]);
  getArgAs_Double(unsigned, aAttributeId, args[_i++]);
  getArgAs_Double(float, aTo, args[_i++]);
  getArgAs_Double(double, aTime, args[_i++]);
  getArgAs_END

  Soloud_fadeFilterParameter(aClassPtr, aVoiceHandle, aFilterId, aAttributeId, aTo, aTime);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_oscillateFilterParameter GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aFilterId*/,
    APE_OBJECT_NUMBER/*aAttributeId*/,
    APE_OBJECT_NUMBER/*aFrom*/,
    APE_OBJECT_NUMBER/*aTo*/,
    APE_OBJECT_NUMBER/*aTime*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_oscillateFilterParameter")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(unsigned, aFilterId, args[_i++]);
  getArgAs_Double(unsigned, aAttributeId, args[_i++]);
  getArgAs_Double(float, aFrom, args[_i++]);
  getArgAs_Double(float, aTo, args[_i++]);
  getArgAs_Double(double, aTime, args[_i++]);
  getArgAs_END

  Soloud_oscillateFilterParameter(aClassPtr, aVoiceHandle, aFilterId, aAttributeId, aFrom, aTo, aTime);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getStreamTime GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getStreamTime")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_END

  double value = Soloud_getStreamTime(aClassPtr, aVoiceHandle);

  return ape_object_make_number(value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getStreamPosition GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getStreamPosition")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_END

  double value = Soloud_getStreamPosition(aClassPtr, aVoiceHandle);

  return ape_object_make_number(value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getPause GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getPause")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_END

  int value = Soloud_getPause(aClassPtr, aVoiceHandle);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getVolume")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_END

  float value = Soloud_getVolume(aClassPtr, aVoiceHandle);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getOverallVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getOverallVolume")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_END

  float value = Soloud_getOverallVolume(aClassPtr, aVoiceHandle);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getPan GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getPan")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_END

  float value = Soloud_getPan(aClassPtr, aVoiceHandle);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getSamplerate GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getSamplerate")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_END

  float value = Soloud_getSamplerate(aClassPtr, aVoiceHandle);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getProtectVoice GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getProtectVoice")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_END

  int value = Soloud_getProtectVoice(aClassPtr, aVoiceHandle);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getActiveVoiceCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getActiveVoiceCount")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  unsigned value = Soloud_getActiveVoiceCount(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getVoiceCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getVoiceCount")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  unsigned value = Soloud_getVoiceCount(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_isValidVoiceHandle GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_isValidVoiceHandle")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_END

  int value = Soloud_isValidVoiceHandle(aClassPtr, aVoiceHandle);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getRelativePlaySpeed GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getRelativePlaySpeed")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_END

  float value = Soloud_getRelativePlaySpeed(aClassPtr, aVoiceHandle);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getPostClipScaler GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getPostClipScaler")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  float value = Soloud_getPostClipScaler(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getMainResampler GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getMainResampler")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  unsigned value = Soloud_getMainResampler(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getGlobalVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getGlobalVolume")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  float value = Soloud_getGlobalVolume(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getMaxActiveVoiceCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getMaxActiveVoiceCount")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  unsigned value = Soloud_getMaxActiveVoiceCount(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getLooping GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getLooping")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_END

  int value = Soloud_getLooping(aClassPtr, aVoiceHandle);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getAutoStop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getAutoStop")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_END

  int value = Soloud_getAutoStop(aClassPtr, aVoiceHandle);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getLoopPoint GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getLoopPoint")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_END

  double value = Soloud_getLoopPoint(aClassPtr, aVoiceHandle);

  return ape_object_make_number(value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setLoopPoint GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aLoopPoint*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setLoopPoint")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(double, aLoopPoint, args[_i++]);
  getArgAs_END

  Soloud_setLoopPoint(aClassPtr, aVoiceHandle, aLoopPoint);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setLooping GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aLooping*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setLooping")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(int, aLooping, args[_i++]);
  getArgAs_END

  Soloud_setLooping(aClassPtr, aVoiceHandle, aLooping);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setAutoStop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aAutoStop*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setAutoStop")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(int, aAutoStop, args[_i++]);
  getArgAs_END

  Soloud_setAutoStop(aClassPtr, aVoiceHandle, aAutoStop);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setMaxActiveVoiceCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceCount*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setMaxActiveVoiceCount")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceCount, args[_i++]);
  getArgAs_END

  int value = Soloud_setMaxActiveVoiceCount(aClassPtr, aVoiceCount);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setInaudibleBehavior GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aMustTick*/,
    APE_OBJECT_NUMBER/*aKill*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setInaudibleBehavior")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(int, aMustTick, args[_i++]);
  getArgAs_Double(int, aKill, args[_i++]);
  getArgAs_END

  Soloud_setInaudibleBehavior(aClassPtr, aVoiceHandle, aMustTick, aKill);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setGlobalVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVolume*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setGlobalVolume")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aVolume, args[_i++]);
  getArgAs_END

  Soloud_setGlobalVolume(aClassPtr, aVolume);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setPostClipScaler GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aScaler*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setPostClipScaler")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aScaler, args[_i++]);
  getArgAs_END

  Soloud_setPostClipScaler(aClassPtr, aScaler);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setMainResampler GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aResampler*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setMainResampler")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aResampler, args[_i++]);
  getArgAs_END

  Soloud_setMainResampler(aClassPtr, aResampler);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setPause GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aPause*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setPause")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(int, aPause, args[_i++]);
  getArgAs_END

  Soloud_setPause(aClassPtr, aVoiceHandle, aPause);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setPauseAll GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aPause*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setPauseAll")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aPause, args[_i++]);
  getArgAs_END

  Soloud_setPauseAll(aClassPtr, aPause);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setRelativePlaySpeed GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aSpeed*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setRelativePlaySpeed")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(float, aSpeed, args[_i++]);
  getArgAs_END

  int value = Soloud_setRelativePlaySpeed(aClassPtr, aVoiceHandle, aSpeed);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setProtectVoice GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aProtect*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setProtectVoice")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(int, aProtect, args[_i++]);
  getArgAs_END

  Soloud_setProtectVoice(aClassPtr, aVoiceHandle, aProtect);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setSamplerate GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aSamplerate*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setSamplerate")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(float, aSamplerate, args[_i++]);
  getArgAs_END

  Soloud_setSamplerate(aClassPtr, aVoiceHandle, aSamplerate);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setPan GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aPan*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setPan")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(float, aPan, args[_i++]);
  getArgAs_END

  Soloud_setPan(aClassPtr, aVoiceHandle, aPan);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setPanAbsolute GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aLVolume*/,
    APE_OBJECT_NUMBER/*aRVolume*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setPanAbsolute")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(float, aLVolume, args[_i++]);
  getArgAs_Double(float, aRVolume, args[_i++]);
  getArgAs_END

  Soloud_setPanAbsolute(aClassPtr, aVoiceHandle, aLVolume, aRVolume);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setChannelVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aChannel*/,
    APE_OBJECT_NUMBER/*aVolume*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setChannelVolume")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(unsigned, aChannel, args[_i++]);
  getArgAs_Double(float, aVolume, args[_i++]);
  getArgAs_END

  Soloud_setChannelVolume(aClassPtr, aVoiceHandle, aChannel, aVolume);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aVolume*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setVolume")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(float, aVolume, args[_i++]);
  getArgAs_END

  Soloud_setVolume(aClassPtr, aVoiceHandle, aVolume);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setDelaySamples GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aSamples*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setDelaySamples")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(unsigned, aSamples, args[_i++]);
  getArgAs_END

  Soloud_setDelaySamples(aClassPtr, aVoiceHandle, aSamples);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_fadeVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aTo*/,
    APE_OBJECT_NUMBER/*aTime*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_fadeVolume")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(float, aTo, args[_i++]);
  getArgAs_Double(double, aTime, args[_i++]);
  getArgAs_END

  Soloud_fadeVolume(aClassPtr, aVoiceHandle, aTo, aTime);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_fadePan GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aTo*/,
    APE_OBJECT_NUMBER/*aTime*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_fadePan")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(float, aTo, args[_i++]);
  getArgAs_Double(double, aTime, args[_i++]);
  getArgAs_END

  Soloud_fadePan(aClassPtr, aVoiceHandle, aTo, aTime);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_fadeRelativePlaySpeed GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aTo*/,
    APE_OBJECT_NUMBER/*aTime*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_fadeRelativePlaySpeed")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(float, aTo, args[_i++]);
  getArgAs_Double(double, aTime, args[_i++]);
  getArgAs_END

  Soloud_fadeRelativePlaySpeed(aClassPtr, aVoiceHandle, aTo, aTime);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_fadeGlobalVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aTo*/,
    APE_OBJECT_NUMBER/*aTime*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_fadeGlobalVolume")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aTo, args[_i++]);
  getArgAs_Double(double, aTime, args[_i++]);
  getArgAs_END

  Soloud_fadeGlobalVolume(aClassPtr, aTo, aTime);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_schedulePause GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aTime*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_schedulePause")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(double, aTime, args[_i++]);
  getArgAs_END

  Soloud_schedulePause(aClassPtr, aVoiceHandle, aTime);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_scheduleStop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aTime*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_scheduleStop")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(double, aTime, args[_i++]);
  getArgAs_END

  Soloud_scheduleStop(aClassPtr, aVoiceHandle, aTime);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_oscillateVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aFrom*/,
    APE_OBJECT_NUMBER/*aTo*/,
    APE_OBJECT_NUMBER/*aTime*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_oscillateVolume")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(float, aFrom, args[_i++]);
  getArgAs_Double(float, aTo, args[_i++]);
  getArgAs_Double(double, aTime, args[_i++]);
  getArgAs_END

  Soloud_oscillateVolume(aClassPtr, aVoiceHandle, aFrom, aTo, aTime);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_oscillatePan GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aFrom*/,
    APE_OBJECT_NUMBER/*aTo*/,
    APE_OBJECT_NUMBER/*aTime*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_oscillatePan")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(float, aFrom, args[_i++]);
  getArgAs_Double(float, aTo, args[_i++]);
  getArgAs_Double(double, aTime, args[_i++]);
  getArgAs_END

  Soloud_oscillatePan(aClassPtr, aVoiceHandle, aFrom, aTo, aTime);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_oscillateRelativePlaySpeed GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aFrom*/,
    APE_OBJECT_NUMBER/*aTo*/,
    APE_OBJECT_NUMBER/*aTime*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_oscillateRelativePlaySpeed")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(float, aFrom, args[_i++]);
  getArgAs_Double(float, aTo, args[_i++]);
  getArgAs_Double(double, aTime, args[_i++]);
  getArgAs_END

  Soloud_oscillateRelativePlaySpeed(aClassPtr, aVoiceHandle, aFrom, aTo, aTime);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_oscillateGlobalVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aFrom*/,
    APE_OBJECT_NUMBER/*aTo*/,
    APE_OBJECT_NUMBER/*aTime*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_oscillateGlobalVolume")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aFrom, args[_i++]);
  getArgAs_Double(float, aTo, args[_i++]);
  getArgAs_Double(double, aTime, args[_i++]);
  getArgAs_END

  Soloud_oscillateGlobalVolume(aClassPtr, aFrom, aTo, aTime);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setGlobalFilter GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aFilterId*/,
    APE_OBJECT_NUMBER/*aFilter*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setGlobalFilter")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aFilterId, args[_i++]);
  getArgAs_Pointer(Filter *, aFilter, args[_i++]);
  getArgAs_END

  Soloud_setGlobalFilter(aClassPtr, aFilterId, aFilter);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_setVisualizationEnable GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aEnable*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_setVisualizationEnable")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aEnable, args[_i++]);
  getArgAs_END

  Soloud_setVisualizationEnable(aClassPtr, aEnable);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_calcFFT GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_calcFFT")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  float * value = Soloud_calcFFT(aClassPtr);

  ape_object_t array = mape_object_make_array(ape, 256);
  for (int i = 0; i < 256; i += 1) {
    mape_object_add_array_number(i, array, (double)value[i]);
  }
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getWave GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getWave")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  float * value = Soloud_getWave(aClassPtr);

  ape_object_t array = mape_object_make_array(ape, 256);
  for (int i = 0; i < 256; i += 1) {
    mape_object_add_array_number(i, array, (double)value[i]);
  }
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getApproximateVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aChannel*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getApproximateVolume")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aChannel, args[_i++]);
  getArgAs_END

  float value = Soloud_getApproximateVolume(aClassPtr, aChannel);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getLoopCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getLoopCount")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_END

  unsigned value = Soloud_getLoopCount(aClassPtr, aVoiceHandle);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_getInfo GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aInfoKey*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_getInfo")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(unsigned, aInfoKey, args[_i++]);
  getArgAs_END

  float value = Soloud_getInfo(aClassPtr, aVoiceHandle, aInfoKey);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_createVoiceGroup GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_createVoiceGroup")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  unsigned value = Soloud_createVoiceGroup(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_destroyVoiceGroup GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceGroupHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_destroyVoiceGroup")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceGroupHandle, args[_i++]);
  getArgAs_END

  int value = Soloud_destroyVoiceGroup(aClassPtr, aVoiceGroupHandle);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_addVoiceToGroup GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceGroupHandle*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_addVoiceToGroup")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceGroupHandle, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_END

  int value = Soloud_addVoiceToGroup(aClassPtr, aVoiceGroupHandle, aVoiceHandle);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_isVoiceGroup GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceGroupHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_isVoiceGroup")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceGroupHandle, args[_i++]);
  getArgAs_END

  int value = Soloud_isVoiceGroup(aClassPtr, aVoiceGroupHandle);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_isVoiceGroupEmpty GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceGroupHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_isVoiceGroupEmpty")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceGroupHandle, args[_i++]);
  getArgAs_END

  int value = Soloud_isVoiceGroupEmpty(aClassPtr, aVoiceGroupHandle);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_update3dAudio GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_update3dAudio")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  Soloud_update3dAudio(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_set3dSoundSpeed GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aSpeed*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_set3dSoundSpeed")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aSpeed, args[_i++]);
  getArgAs_END

  int value = Soloud_set3dSoundSpeed(aClassPtr, aSpeed);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_get3dSoundSpeed GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_get3dSoundSpeed")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  float value = Soloud_get3dSoundSpeed(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_set3dListenerParametersEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aPosX*/,
    APE_OBJECT_NUMBER/*aPosY*/,
    APE_OBJECT_NUMBER/*aPosZ*/,
    APE_OBJECT_NUMBER/*aAtX*/,
    APE_OBJECT_NUMBER/*aAtY*/,
    APE_OBJECT_NUMBER/*aAtZ*/,
    APE_OBJECT_NUMBER/*aUpX*/,
    APE_OBJECT_NUMBER/*aUpY*/,
    APE_OBJECT_NUMBER/*aUpZ*/,
    APE_OBJECT_NUMBER/*aVelocityX*/,
    APE_OBJECT_NUMBER/*aVelocityY*/,
    APE_OBJECT_NUMBER/*aVelocityZ*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_set3dListenerParametersEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aPosX, args[_i++]);
  getArgAs_Double(float, aPosY, args[_i++]);
  getArgAs_Double(float, aPosZ, args[_i++]);
  getArgAs_Double(float, aAtX, args[_i++]);
  getArgAs_Double(float, aAtY, args[_i++]);
  getArgAs_Double(float, aAtZ, args[_i++]);
  getArgAs_Double(float, aUpX, args[_i++]);
  getArgAs_Double(float, aUpY, args[_i++]);
  getArgAs_Double(float, aUpZ, args[_i++]);
  getArgAs_Double(float, aVelocityX, args[_i++]);
  getArgAs_Double(float, aVelocityY, args[_i++]);
  getArgAs_Double(float, aVelocityZ, args[_i++]);
  getArgAs_END

  Soloud_set3dListenerParametersEx(aClassPtr, aPosX, aPosY, aPosZ, aAtX, aAtY, aAtZ, aUpX, aUpY, aUpZ, aVelocityX, aVelocityY, aVelocityZ);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_set3dListenerPosition GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aPosX*/,
    APE_OBJECT_NUMBER/*aPosY*/,
    APE_OBJECT_NUMBER/*aPosZ*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_set3dListenerPosition")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aPosX, args[_i++]);
  getArgAs_Double(float, aPosY, args[_i++]);
  getArgAs_Double(float, aPosZ, args[_i++]);
  getArgAs_END

  Soloud_set3dListenerPosition(aClassPtr, aPosX, aPosY, aPosZ);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_set3dListenerAt GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAtX*/,
    APE_OBJECT_NUMBER/*aAtY*/,
    APE_OBJECT_NUMBER/*aAtZ*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_set3dListenerAt")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aAtX, args[_i++]);
  getArgAs_Double(float, aAtY, args[_i++]);
  getArgAs_Double(float, aAtZ, args[_i++]);
  getArgAs_END

  Soloud_set3dListenerAt(aClassPtr, aAtX, aAtY, aAtZ);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_set3dListenerUp GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aUpX*/,
    APE_OBJECT_NUMBER/*aUpY*/,
    APE_OBJECT_NUMBER/*aUpZ*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_set3dListenerUp")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aUpX, args[_i++]);
  getArgAs_Double(float, aUpY, args[_i++]);
  getArgAs_Double(float, aUpZ, args[_i++]);
  getArgAs_END

  Soloud_set3dListenerUp(aClassPtr, aUpX, aUpY, aUpZ);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_set3dListenerVelocity GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVelocityX*/,
    APE_OBJECT_NUMBER/*aVelocityY*/,
    APE_OBJECT_NUMBER/*aVelocityZ*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_set3dListenerVelocity")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aVelocityX, args[_i++]);
  getArgAs_Double(float, aVelocityY, args[_i++]);
  getArgAs_Double(float, aVelocityZ, args[_i++]);
  getArgAs_END

  Soloud_set3dListenerVelocity(aClassPtr, aVelocityX, aVelocityY, aVelocityZ);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_set3dSourceParametersEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aPosX*/,
    APE_OBJECT_NUMBER/*aPosY*/,
    APE_OBJECT_NUMBER/*aPosZ*/,
    APE_OBJECT_NUMBER/*aVelocityX*/,
    APE_OBJECT_NUMBER/*aVelocityY*/,
    APE_OBJECT_NUMBER/*aVelocityZ*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_set3dSourceParametersEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(float, aPosX, args[_i++]);
  getArgAs_Double(float, aPosY, args[_i++]);
  getArgAs_Double(float, aPosZ, args[_i++]);
  getArgAs_Double(float, aVelocityX, args[_i++]);
  getArgAs_Double(float, aVelocityY, args[_i++]);
  getArgAs_Double(float, aVelocityZ, args[_i++]);
  getArgAs_END

  Soloud_set3dSourceParametersEx(aClassPtr, aVoiceHandle, aPosX, aPosY, aPosZ, aVelocityX, aVelocityY, aVelocityZ);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_set3dSourcePosition GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aPosX*/,
    APE_OBJECT_NUMBER/*aPosY*/,
    APE_OBJECT_NUMBER/*aPosZ*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_set3dSourcePosition")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(float, aPosX, args[_i++]);
  getArgAs_Double(float, aPosY, args[_i++]);
  getArgAs_Double(float, aPosZ, args[_i++]);
  getArgAs_END

  Soloud_set3dSourcePosition(aClassPtr, aVoiceHandle, aPosX, aPosY, aPosZ);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_set3dSourceVelocity GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aVelocityX*/,
    APE_OBJECT_NUMBER/*aVelocityY*/,
    APE_OBJECT_NUMBER/*aVelocityZ*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_set3dSourceVelocity")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(float, aVelocityX, args[_i++]);
  getArgAs_Double(float, aVelocityY, args[_i++]);
  getArgAs_Double(float, aVelocityZ, args[_i++]);
  getArgAs_END

  Soloud_set3dSourceVelocity(aClassPtr, aVoiceHandle, aVelocityX, aVelocityY, aVelocityZ);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_set3dSourceMinMaxDistance GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aMinDistance*/,
    APE_OBJECT_NUMBER/*aMaxDistance*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_set3dSourceMinMaxDistance")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(float, aMinDistance, args[_i++]);
  getArgAs_Double(float, aMaxDistance, args[_i++]);
  getArgAs_END

  Soloud_set3dSourceMinMaxDistance(aClassPtr, aVoiceHandle, aMinDistance, aMaxDistance);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_set3dSourceAttenuation GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aAttenuationModel*/,
    APE_OBJECT_NUMBER/*aAttenuationRolloffFactor*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_set3dSourceAttenuation")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(unsigned, aAttenuationModel, args[_i++]);
  getArgAs_Double(float, aAttenuationRolloffFactor, args[_i++]);
  getArgAs_END

  Soloud_set3dSourceAttenuation(aClassPtr, aVoiceHandle, aAttenuationModel, aAttenuationRolloffFactor);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_set3dSourceDopplerFactor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
    APE_OBJECT_NUMBER/*aDopplerFactor*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_set3dSourceDopplerFactor")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_Double(float, aDopplerFactor, args[_i++]);
  getArgAs_END

  Soloud_set3dSourceDopplerFactor(aClassPtr, aVoiceHandle, aDopplerFactor);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_mix GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aBuffer*/,
    APE_OBJECT_NUMBER/*aSamples*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_mix")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(float *, aBuffer, args[_i++]);
  getArgAs_Double(unsigned, aSamples, args[_i++]);
  getArgAs_END

  Soloud_mix(aClassPtr, aBuffer, aSamples);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSoloud_mixSigned16 GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aBuffer*/,
    APE_OBJECT_NUMBER/*aSamples*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSoloud_mixSigned16")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(short *, aBuffer, args[_i++]);
  getArgAs_Double(unsigned, aSamples, args[_i++]);
  getArgAs_END

  Soloud_mixSigned16(aClassPtr, aBuffer, aSamples);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBassboostFilter_destroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBassboostFilter_destroy")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  BassboostFilter_destroy(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBassboostFilter_getParamCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBassboostFilter_getParamCount")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  int value = BassboostFilter_getParamCount(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBassboostFilter_getParamName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBassboostFilter_getParamName")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  const char * value = BassboostFilter_getParamName(aClassPtr, aParamIndex);

  return ape_object_make_string(ape, value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBassboostFilter_getParamType GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBassboostFilter_getParamType")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  unsigned value = BassboostFilter_getParamType(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBassboostFilter_getParamMax GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBassboostFilter_getParamMax")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = BassboostFilter_getParamMax(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBassboostFilter_getParamMin GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBassboostFilter_getParamMin")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = BassboostFilter_getParamMin(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBassboostFilter_setParams GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aBoost*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBassboostFilter_setParams")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aBoost, args[_i++]);
  getArgAs_END

  int value = BassboostFilter_setParams(aClassPtr, aBoost);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBassboostFilter_create GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  void * value = BassboostFilter_create();

  return ape_object_make_number(_gsPointerToNumber(value));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBiquadResonantFilter_destroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBiquadResonantFilter_destroy")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  BiquadResonantFilter_destroy(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBiquadResonantFilter_getParamCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBiquadResonantFilter_getParamCount")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  int value = BiquadResonantFilter_getParamCount(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBiquadResonantFilter_getParamName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBiquadResonantFilter_getParamName")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  const char * value = BiquadResonantFilter_getParamName(aClassPtr, aParamIndex);

  return ape_object_make_string(ape, value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBiquadResonantFilter_getParamType GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBiquadResonantFilter_getParamType")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  unsigned value = BiquadResonantFilter_getParamType(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBiquadResonantFilter_getParamMax GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBiquadResonantFilter_getParamMax")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = BiquadResonantFilter_getParamMax(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBiquadResonantFilter_getParamMin GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBiquadResonantFilter_getParamMin")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = BiquadResonantFilter_getParamMin(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBiquadResonantFilter_create GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  void * value = BiquadResonantFilter_create();

  return ape_object_make_number(_gsPointerToNumber(value));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBiquadResonantFilter_setParams GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aType*/,
    APE_OBJECT_NUMBER/*aFrequency*/,
    APE_OBJECT_NUMBER/*aResonance*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBiquadResonantFilter_setParams")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aType, args[_i++]);
  getArgAs_Double(float, aFrequency, args[_i++]);
  getArgAs_Double(float, aResonance, args[_i++]);
  getArgAs_END

  int value = BiquadResonantFilter_setParams(aClassPtr, aType, aFrequency, aResonance);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_destroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_destroy")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  Bus_destroy(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_create GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  void * value = Bus_create();

  return ape_object_make_number(_gsPointerToNumber(value));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_setFilter GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aFilterId*/,
    APE_OBJECT_NUMBER/*aFilter*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_setFilter")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aFilterId, args[_i++]);
  getArgAs_Pointer(Filter *, aFilter, args[_i++]);
  getArgAs_END

  Bus_setFilter(aClassPtr, aFilterId, aFilter);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_playEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aSound*/,
    APE_OBJECT_NUMBER/*aVolume*/,
    APE_OBJECT_NUMBER/*aPan*/,
    APE_OBJECT_NUMBER/*aPaused*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_playEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioSource *, aSound, args[_i++]);
  getArgAs_Double(float, aVolume, args[_i++]);
  getArgAs_Double(float, aPan, args[_i++]);
  getArgAs_Double(int, aPaused, args[_i++]);
  getArgAs_END

  unsigned value = Bus_playEx(aClassPtr, aSound, aVolume, aPan, aPaused);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_playClockedEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aSoundTime*/,
    APE_OBJECT_NUMBER/*aSound*/,
    APE_OBJECT_NUMBER/*aVolume*/,
    APE_OBJECT_NUMBER/*aPan*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_playClockedEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(double, aSoundTime, args[_i++]);
  getArgAs_Pointer(AudioSource *, aSound, args[_i++]);
  getArgAs_Double(float, aVolume, args[_i++]);
  getArgAs_Double(float, aPan, args[_i++]);
  getArgAs_END

  unsigned value = Bus_playClockedEx(aClassPtr, aSoundTime, aSound, aVolume, aPan);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_play3dEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aSound*/,
    APE_OBJECT_NUMBER/*aPosX*/,
    APE_OBJECT_NUMBER/*aPosY*/,
    APE_OBJECT_NUMBER/*aPosZ*/,
    APE_OBJECT_NUMBER/*aVelX*/,
    APE_OBJECT_NUMBER/*aVelY*/,
    APE_OBJECT_NUMBER/*aVelZ*/,
    APE_OBJECT_NUMBER/*aVolume*/,
    APE_OBJECT_NUMBER/*aPaused*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_play3dEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioSource *, aSound, args[_i++]);
  getArgAs_Double(float, aPosX, args[_i++]);
  getArgAs_Double(float, aPosY, args[_i++]);
  getArgAs_Double(float, aPosZ, args[_i++]);
  getArgAs_Double(float, aVelX, args[_i++]);
  getArgAs_Double(float, aVelY, args[_i++]);
  getArgAs_Double(float, aVelZ, args[_i++]);
  getArgAs_Double(float, aVolume, args[_i++]);
  getArgAs_Double(int, aPaused, args[_i++]);
  getArgAs_END

  unsigned value = Bus_play3dEx(aClassPtr, aSound, aPosX, aPosY, aPosZ, aVelX, aVelY, aVelZ, aVolume, aPaused);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_play3dClockedEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aSoundTime*/,
    APE_OBJECT_NUMBER/*aSound*/,
    APE_OBJECT_NUMBER/*aPosX*/,
    APE_OBJECT_NUMBER/*aPosY*/,
    APE_OBJECT_NUMBER/*aPosZ*/,
    APE_OBJECT_NUMBER/*aVelX*/,
    APE_OBJECT_NUMBER/*aVelY*/,
    APE_OBJECT_NUMBER/*aVelZ*/,
    APE_OBJECT_NUMBER/*aVolume*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_play3dClockedEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(double, aSoundTime, args[_i++]);
  getArgAs_Pointer(AudioSource *, aSound, args[_i++]);
  getArgAs_Double(float, aPosX, args[_i++]);
  getArgAs_Double(float, aPosY, args[_i++]);
  getArgAs_Double(float, aPosZ, args[_i++]);
  getArgAs_Double(float, aVelX, args[_i++]);
  getArgAs_Double(float, aVelY, args[_i++]);
  getArgAs_Double(float, aVelZ, args[_i++]);
  getArgAs_Double(float, aVolume, args[_i++]);
  getArgAs_END

  unsigned value = Bus_play3dClockedEx(aClassPtr, aSoundTime, aSound, aPosX, aPosY, aPosZ, aVelX, aVelY, aVelZ, aVolume);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_setChannels GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aChannels*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_setChannels")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aChannels, args[_i++]);
  getArgAs_END

  int value = Bus_setChannels(aClassPtr, aChannels);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_setVisualizationEnable GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aEnable*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_setVisualizationEnable")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aEnable, args[_i++]);
  getArgAs_END

  Bus_setVisualizationEnable(aClassPtr, aEnable);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_annexSound GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVoiceHandle*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_annexSound")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aVoiceHandle, args[_i++]);
  getArgAs_END

  Bus_annexSound(aClassPtr, aVoiceHandle);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_calcFFT GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_calcFFT")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  float * value = Bus_calcFFT(aClassPtr);

  ape_object_t array = mape_object_make_array(ape, 256);
  for (int i = 0; i < 256; i += 1) {
    mape_object_add_array_number(i, array, (double)value[i]);
  }
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_getWave GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_getWave")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  float * value = Bus_getWave(aClassPtr);

  ape_object_t array = mape_object_make_array(ape, 256);
  for (int i = 0; i < 256; i += 1) {
    mape_object_add_array_number(i, array, (double)value[i]);
  }
  return array;
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_getApproximateVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aChannel*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_getApproximateVolume")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aChannel, args[_i++]);
  getArgAs_END

  float value = Bus_getApproximateVolume(aClassPtr, aChannel);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_getActiveVoiceCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_getActiveVoiceCount")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  unsigned value = Bus_getActiveVoiceCount(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_getResampler GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_getResampler")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  unsigned value = Bus_getResampler(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_setResampler GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aResampler*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_setResampler")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aResampler, args[_i++]);
  getArgAs_END

  Bus_setResampler(aClassPtr, aResampler);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_setVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVolume*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_setVolume")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aVolume, args[_i++]);
  getArgAs_END

  Bus_setVolume(aClassPtr, aVolume);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_setLooping GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aLoop*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_setLooping")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aLoop, args[_i++]);
  getArgAs_END

  Bus_setLooping(aClassPtr, aLoop);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_setAutoStop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAutoStop*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_setAutoStop")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aAutoStop, args[_i++]);
  getArgAs_END

  Bus_setAutoStop(aClassPtr, aAutoStop);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_set3dMinMaxDistance GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMinDistance*/,
    APE_OBJECT_NUMBER/*aMaxDistance*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_set3dMinMaxDistance")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aMinDistance, args[_i++]);
  getArgAs_Double(float, aMaxDistance, args[_i++]);
  getArgAs_END

  Bus_set3dMinMaxDistance(aClassPtr, aMinDistance, aMaxDistance);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_set3dAttenuation GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAttenuationModel*/,
    APE_OBJECT_NUMBER/*aAttenuationRolloffFactor*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_set3dAttenuation")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aAttenuationModel, args[_i++]);
  getArgAs_Double(float, aAttenuationRolloffFactor, args[_i++]);
  getArgAs_END

  Bus_set3dAttenuation(aClassPtr, aAttenuationModel, aAttenuationRolloffFactor);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_set3dDopplerFactor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aDopplerFactor*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_set3dDopplerFactor")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aDopplerFactor, args[_i++]);
  getArgAs_END

  Bus_set3dDopplerFactor(aClassPtr, aDopplerFactor);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_set3dListenerRelative GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aListenerRelative*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_set3dListenerRelative")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aListenerRelative, args[_i++]);
  getArgAs_END

  Bus_set3dListenerRelative(aClassPtr, aListenerRelative);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_set3dDistanceDelay GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aDistanceDelay*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_set3dDistanceDelay")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aDistanceDelay, args[_i++]);
  getArgAs_END

  Bus_set3dDistanceDelay(aClassPtr, aDistanceDelay);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_set3dColliderEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aCollider*/,
    APE_OBJECT_NUMBER/*aUserData*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_set3dColliderEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioCollider *, aCollider, args[_i++]);
  getArgAs_Double(int, aUserData, args[_i++]);
  getArgAs_END

  Bus_set3dColliderEx(aClassPtr, aCollider, aUserData);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_set3dAttenuator GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAttenuator*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_set3dAttenuator")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioAttenuator *, aAttenuator, args[_i++]);
  getArgAs_END

  Bus_set3dAttenuator(aClassPtr, aAttenuator);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_setInaudibleBehavior GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMustTick*/,
    APE_OBJECT_NUMBER/*aKill*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_setInaudibleBehavior")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aMustTick, args[_i++]);
  getArgAs_Double(int, aKill, args[_i++]);
  getArgAs_END

  Bus_setInaudibleBehavior(aClassPtr, aMustTick, aKill);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_setLoopPoint GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aLoopPoint*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_setLoopPoint")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(double, aLoopPoint, args[_i++]);
  getArgAs_END

  Bus_setLoopPoint(aClassPtr, aLoopPoint);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_getLoopPoint GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_getLoopPoint")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  double value = Bus_getLoopPoint(aClassPtr);

  return ape_object_make_number(value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlBus_stop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slBus_stop")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  Bus_stop(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlDCRemovalFilter_destroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slDCRemovalFilter_destroy")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  DCRemovalFilter_destroy(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlDCRemovalFilter_create GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  void * value = DCRemovalFilter_create();

  return ape_object_make_number(_gsPointerToNumber(value));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlDCRemovalFilter_setParamsEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aLength*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slDCRemovalFilter_setParamsEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aLength, args[_i++]);
  getArgAs_END

  int value = DCRemovalFilter_setParamsEx(aClassPtr, aLength);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlDCRemovalFilter_getParamCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slDCRemovalFilter_getParamCount")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  int value = DCRemovalFilter_getParamCount(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlDCRemovalFilter_getParamName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slDCRemovalFilter_getParamName")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  const char * value = DCRemovalFilter_getParamName(aClassPtr, aParamIndex);

  return ape_object_make_string(ape, value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlDCRemovalFilter_getParamType GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slDCRemovalFilter_getParamType")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  unsigned value = DCRemovalFilter_getParamType(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlDCRemovalFilter_getParamMax GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slDCRemovalFilter_getParamMax")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = DCRemovalFilter_getParamMax(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlDCRemovalFilter_getParamMin GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slDCRemovalFilter_getParamMin")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = DCRemovalFilter_getParamMin(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlEchoFilter_destroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slEchoFilter_destroy")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  EchoFilter_destroy(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlEchoFilter_getParamCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slEchoFilter_getParamCount")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  int value = EchoFilter_getParamCount(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlEchoFilter_getParamName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slEchoFilter_getParamName")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  const char * value = EchoFilter_getParamName(aClassPtr, aParamIndex);

  return ape_object_make_string(ape, value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlEchoFilter_getParamType GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slEchoFilter_getParamType")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  unsigned value = EchoFilter_getParamType(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlEchoFilter_getParamMax GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slEchoFilter_getParamMax")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = EchoFilter_getParamMax(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlEchoFilter_getParamMin GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slEchoFilter_getParamMin")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = EchoFilter_getParamMin(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlEchoFilter_create GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  void * value = EchoFilter_create();

  return ape_object_make_number(_gsPointerToNumber(value));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlEchoFilter_setParamsEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aDelay*/,
    APE_OBJECT_NUMBER/*aDecay*/,
    APE_OBJECT_NUMBER/*aFilter*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slEchoFilter_setParamsEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aDelay, args[_i++]);
  getArgAs_Double(float, aDecay, args[_i++]);
  getArgAs_Double(float, aFilter, args[_i++]);
  getArgAs_END

  int value = EchoFilter_setParamsEx(aClassPtr, aDelay, aDecay, aFilter);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFFTFilter_destroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFFTFilter_destroy")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  FFTFilter_destroy(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFFTFilter_create GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  void * value = FFTFilter_create();

  return ape_object_make_number(_gsPointerToNumber(value));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFFTFilter_getParamCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFFTFilter_getParamCount")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  int value = FFTFilter_getParamCount(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFFTFilter_getParamName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFFTFilter_getParamName")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  const char * value = FFTFilter_getParamName(aClassPtr, aParamIndex);

  return ape_object_make_string(ape, value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFFTFilter_getParamType GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFFTFilter_getParamType")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  unsigned value = FFTFilter_getParamType(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFFTFilter_getParamMax GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFFTFilter_getParamMax")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = FFTFilter_getParamMax(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFFTFilter_getParamMin GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFFTFilter_getParamMin")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = FFTFilter_getParamMin(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFlangerFilter_destroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFlangerFilter_destroy")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  FlangerFilter_destroy(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFlangerFilter_getParamCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFlangerFilter_getParamCount")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  int value = FlangerFilter_getParamCount(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFlangerFilter_getParamName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFlangerFilter_getParamName")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  const char * value = FlangerFilter_getParamName(aClassPtr, aParamIndex);

  return ape_object_make_string(ape, value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFlangerFilter_getParamType GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFlangerFilter_getParamType")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  unsigned value = FlangerFilter_getParamType(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFlangerFilter_getParamMax GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFlangerFilter_getParamMax")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = FlangerFilter_getParamMax(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFlangerFilter_getParamMin GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFlangerFilter_getParamMin")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = FlangerFilter_getParamMin(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}


GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFlangerFilter_create GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  void * value = FlangerFilter_create();

  return ape_object_make_number(_gsPointerToNumber(value));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFlangerFilter_setParams GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aDelay*/,
    APE_OBJECT_NUMBER/*aFreq*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFlangerFilter_setParams")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aDelay, args[_i++]);
  getArgAs_Double(float, aFreq, args[_i++]);
  getArgAs_END

  int value = FlangerFilter_setParams(aClassPtr, aDelay, aFreq);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFreeverbFilter_destroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFreeverbFilter_destroy")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  FreeverbFilter_destroy(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFreeverbFilter_getParamCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFreeverbFilter_getParamCount")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  int value = FreeverbFilter_getParamCount(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFreeverbFilter_getParamName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFreeverbFilter_getParamName")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  const char * value = FreeverbFilter_getParamName(aClassPtr, aParamIndex);

  return ape_object_make_string(ape, value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFreeverbFilter_getParamType GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFreeverbFilter_getParamType")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  unsigned value = FreeverbFilter_getParamType(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFreeverbFilter_getParamMax GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFreeverbFilter_getParamMax")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = FreeverbFilter_getParamMax(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFreeverbFilter_getParamMin GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFreeverbFilter_getParamMin")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = FreeverbFilter_getParamMin(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFreeverbFilter_create GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  void * value = FreeverbFilter_create();

  return ape_object_make_number(_gsPointerToNumber(value));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlFreeverbFilter_setParams GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMode*/,
    APE_OBJECT_NUMBER/*aRoomSize*/,
    APE_OBJECT_NUMBER/*aDamp*/,
    APE_OBJECT_NUMBER/*aWidth*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slFreeverbFilter_setParams")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aMode, args[_i++]);
  getArgAs_Double(float, aRoomSize, args[_i++]);
  getArgAs_Double(float, aDamp, args[_i++]);
  getArgAs_Double(float, aWidth, args[_i++]);
  getArgAs_END

  int value = FreeverbFilter_setParams(aClassPtr, aMode, aRoomSize, aDamp, aWidth);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlLofiFilter_destroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slLofiFilter_destroy")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  LofiFilter_destroy(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlLofiFilter_getParamCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slLofiFilter_getParamCount")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  int value = LofiFilter_getParamCount(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlLofiFilter_getParamName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slLofiFilter_getParamName")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  const char * value = LofiFilter_getParamName(aClassPtr, aParamIndex);

  return ape_object_make_string(ape, value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlLofiFilter_getParamType GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slLofiFilter_getParamType")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  unsigned value = LofiFilter_getParamType(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlLofiFilter_getParamMax GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slLofiFilter_getParamMax")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = LofiFilter_getParamMax(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlLofiFilter_getParamMin GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slLofiFilter_getParamMin")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = LofiFilter_getParamMin(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlLofiFilter_create GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  void * value = LofiFilter_create();

  return ape_object_make_number(_gsPointerToNumber(value));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlLofiFilter_setParams GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aSampleRate*/,
    APE_OBJECT_NUMBER/*aBitdepth*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slLofiFilter_setParams")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aSampleRate, args[_i++]);
  getArgAs_Double(float, aBitdepth, args[_i++]);
  getArgAs_END

  int value = LofiFilter_setParams(aClassPtr, aSampleRate, aBitdepth);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_destroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slMonotone_destroy")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  Monotone_destroy(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_create GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  void * value = Monotone_create();

  return ape_object_make_number(_gsPointerToNumber(value));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_setParamsEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aHardwareChannels*/,
    APE_OBJECT_NUMBER/*aWaveform*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slMonotone_setParamsEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aHardwareChannels, args[_i++]);
  getArgAs_Double(int, aWaveform, args[_i++]);
  getArgAs_END

  int value = Monotone_setParamsEx(aClassPtr, aHardwareChannels, aWaveform);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_load GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_STRING/*aFilename*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slMonotone_load")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_CChars(const char *, aFilename, args[_i++]);
  getArgAs_END

  int value = Monotone_load(aClassPtr, aFilename);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_loadMemEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMem*/,
    APE_OBJECT_NUMBER/*aLength*/,
    APE_OBJECT_NUMBER/*aCopy*/,
    APE_OBJECT_NUMBER/*aTakeOwnership*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slMonotone_loadMemEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(const unsigned char *, aMem, args[_i++]);
  getArgAs_Double(unsigned, aLength, args[_i++]);
  getArgAs_Double(int, aCopy, args[_i++]);
  getArgAs_Double(int, aTakeOwnership, args[_i++]);
  getArgAs_END

  int value = Monotone_loadMemEx(aClassPtr, aMem, aLength, aCopy, aTakeOwnership);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_setVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVolume*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slMonotone_setVolume")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aVolume, args[_i++]);
  getArgAs_END

  Monotone_setVolume(aClassPtr, aVolume);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_setLooping GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aLoop*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slMonotone_setLooping")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aLoop, args[_i++]);
  getArgAs_END

  Monotone_setLooping(aClassPtr, aLoop);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_setAutoStop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAutoStop*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slMonotone_setAutoStop")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aAutoStop, args[_i++]);
  getArgAs_END

  Monotone_setAutoStop(aClassPtr, aAutoStop);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_set3dMinMaxDistance GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMinDistance*/,
    APE_OBJECT_NUMBER/*aMaxDistance*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slMonotone_set3dMinMaxDistance")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aMinDistance, args[_i++]);
  getArgAs_Double(float, aMaxDistance, args[_i++]);
  getArgAs_END

  Monotone_set3dMinMaxDistance(aClassPtr, aMinDistance, aMaxDistance);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_set3dAttenuation GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAttenuationModel*/,
    APE_OBJECT_NUMBER/*aAttenuationRolloffFactor*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slMonotone_set3dAttenuation")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aAttenuationModel, args[_i++]);
  getArgAs_Double(float, aAttenuationRolloffFactor, args[_i++]);
  getArgAs_END

  Monotone_set3dAttenuation(aClassPtr, aAttenuationModel, aAttenuationRolloffFactor);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_set3dDopplerFactor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aDopplerFactor*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slMonotone_set3dDopplerFactor")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aDopplerFactor, args[_i++]);
  getArgAs_END

  Monotone_set3dDopplerFactor(aClassPtr, aDopplerFactor);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_set3dListenerRelative GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aListenerRelative*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slMonotone_set3dListenerRelative")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aListenerRelative, args[_i++]);
  getArgAs_END

  Monotone_set3dListenerRelative(aClassPtr, aListenerRelative);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_set3dDistanceDelay GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aDistanceDelay*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slMonotone_set3dDistanceDelay")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aDistanceDelay, args[_i++]);
  getArgAs_END

  Monotone_set3dDistanceDelay(aClassPtr, aDistanceDelay);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_set3dColliderEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aCollider*/,
    APE_OBJECT_NUMBER/*aUserData*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slMonotone_set3dColliderEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioCollider *, aCollider, args[_i++]);
  getArgAs_Double(int, aUserData, args[_i++]);
  getArgAs_END

  Monotone_set3dColliderEx(aClassPtr, aCollider, aUserData);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_set3dAttenuator GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAttenuator*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slMonotone_set3dAttenuator")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioAttenuator *, aAttenuator, args[_i++]);
  getArgAs_END

  Monotone_set3dAttenuator(aClassPtr, aAttenuator);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_setInaudibleBehavior GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMustTick*/,
    APE_OBJECT_NUMBER/*aKill*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slMonotone_setInaudibleBehavior")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aMustTick, args[_i++]);
  getArgAs_Double(int, aKill, args[_i++]);
  getArgAs_END

  Monotone_setInaudibleBehavior(aClassPtr, aMustTick, aKill);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_setLoopPoint GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aLoopPoint*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slMonotone_setLoopPoint")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(double, aLoopPoint, args[_i++]);
  getArgAs_END

  Monotone_setLoopPoint(aClassPtr, aLoopPoint);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_getLoopPoint GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slMonotone_getLoopPoint")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  double value = Monotone_getLoopPoint(aClassPtr);

  return ape_object_make_number(value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_setFilter GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aFilterId*/,
    APE_OBJECT_NUMBER/*aFilter*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slMonotone_setFilter")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aFilterId, args[_i++]);
  getArgAs_Pointer(Filter *, aFilter, args[_i++]);
  getArgAs_END

  Monotone_setFilter(aClassPtr, aFilterId, aFilter);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlMonotone_stop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slMonotone_stop")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  Monotone_stop(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_destroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_destroy")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  Queue_destroy(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_create GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  void * value = Queue_create();

  return ape_object_make_number(_gsPointerToNumber(value));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_play GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aSound*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_play")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioSource *, aSound, args[_i++]);
  getArgAs_END

  int value = Queue_play(aClassPtr, aSound);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_getQueueCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_getQueueCount")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  unsigned value = Queue_getQueueCount(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_isCurrentlyPlaying GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aSound*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_isCurrentlyPlaying")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioSource *, aSound, args[_i++]);
  getArgAs_END

  int value = Queue_isCurrentlyPlaying(aClassPtr, aSound);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_setParamsFromAudioSource GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aSound*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_setParamsFromAudioSource")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioSource *, aSound, args[_i++]);
  getArgAs_END

  int value = Queue_setParamsFromAudioSource(aClassPtr, aSound);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_setParamsEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aSamplerate*/,
    APE_OBJECT_NUMBER/*aChannels*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_setParamsEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aSamplerate, args[_i++]);
  getArgAs_Double(unsigned, aChannels, args[_i++]);
  getArgAs_END

  int value = Queue_setParamsEx(aClassPtr, aSamplerate, aChannels);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_setVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVolume*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_setVolume")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aVolume, args[_i++]);
  getArgAs_END

  Queue_setVolume(aClassPtr, aVolume);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_setLooping GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aLoop*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_setLooping")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aLoop, args[_i++]);
  getArgAs_END

  Queue_setLooping(aClassPtr, aLoop);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_setAutoStop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAutoStop*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_setAutoStop")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aAutoStop, args[_i++]);
  getArgAs_END

  Queue_setAutoStop(aClassPtr, aAutoStop);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_set3dMinMaxDistance GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMinDistance*/,
    APE_OBJECT_NUMBER/*aMaxDistance*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_set3dMinMaxDistance")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aMinDistance, args[_i++]);
  getArgAs_Double(float, aMaxDistance, args[_i++]);
  getArgAs_END

  Queue_set3dMinMaxDistance(aClassPtr, aMinDistance, aMaxDistance);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_set3dAttenuation GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAttenuationModel*/,
    APE_OBJECT_NUMBER/*aAttenuationRolloffFactor*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_set3dAttenuation")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aAttenuationModel, args[_i++]);
  getArgAs_Double(float, aAttenuationRolloffFactor, args[_i++]);
  getArgAs_END

  Queue_set3dAttenuation(aClassPtr, aAttenuationModel, aAttenuationRolloffFactor);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_set3dDopplerFactor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aDopplerFactor*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_set3dDopplerFactor")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aDopplerFactor, args[_i++]);
  getArgAs_END

  Queue_set3dDopplerFactor(aClassPtr, aDopplerFactor);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_set3dListenerRelative GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aListenerRelative*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_set3dListenerRelative")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aListenerRelative, args[_i++]);
  getArgAs_END

  Queue_set3dListenerRelative(aClassPtr, aListenerRelative);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_set3dDistanceDelay GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aDistanceDelay*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_set3dDistanceDelay")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aDistanceDelay, args[_i++]);
  getArgAs_END

  Queue_set3dDistanceDelay(aClassPtr, aDistanceDelay);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_set3dColliderEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aCollider*/,
    APE_OBJECT_NUMBER/*aUserData*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_set3dColliderEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioCollider *, aCollider, args[_i++]);
  getArgAs_Double(int, aUserData, args[_i++]);
  getArgAs_END

  Queue_set3dColliderEx(aClassPtr, aCollider, aUserData);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_set3dAttenuator GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAttenuator*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_set3dAttenuator")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioAttenuator *, aAttenuator, args[_i++]);
  getArgAs_END

  Queue_set3dAttenuator(aClassPtr, aAttenuator);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_setInaudibleBehavior GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMustTick*/,
    APE_OBJECT_NUMBER/*aKill*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_setInaudibleBehavior")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aMustTick, args[_i++]);
  getArgAs_Double(int, aKill, args[_i++]);
  getArgAs_END

  Queue_setInaudibleBehavior(aClassPtr, aMustTick, aKill);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_setLoopPoint GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aLoopPoint*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_setLoopPoint")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(double, aLoopPoint, args[_i++]);
  getArgAs_END

  Queue_setLoopPoint(aClassPtr, aLoopPoint);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_getLoopPoint GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_getLoopPoint")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  double value = Queue_getLoopPoint(aClassPtr);

  return ape_object_make_number(value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_setFilter GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aFilterId*/,
    APE_OBJECT_NUMBER/*aFilter*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_setFilter")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aFilterId, args[_i++]);
  getArgAs_Pointer(Filter *, aFilter, args[_i++]);
  getArgAs_END

  Queue_setFilter(aClassPtr, aFilterId, aFilter);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlQueue_stop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slQueue_stop")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  Queue_stop(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlRobotizeFilter_destroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slRobotizeFilter_destroy")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  RobotizeFilter_destroy(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlRobotizeFilter_getParamCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slRobotizeFilter_getParamCount")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  int value = RobotizeFilter_getParamCount(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlRobotizeFilter_getParamName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slRobotizeFilter_getParamName")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  const char * value = RobotizeFilter_getParamName(aClassPtr, aParamIndex);

  return ape_object_make_string(ape, value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlRobotizeFilter_getParamType GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slRobotizeFilter_getParamType")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  unsigned value = RobotizeFilter_getParamType(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlRobotizeFilter_getParamMax GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slRobotizeFilter_getParamMax")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = RobotizeFilter_getParamMax(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlRobotizeFilter_getParamMin GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slRobotizeFilter_getParamMin")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = RobotizeFilter_getParamMin(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlRobotizeFilter_setParams GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aFreq*/,
    APE_OBJECT_NUMBER/*aWaveform*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slRobotizeFilter_setParams")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aFreq, args[_i++]);
  getArgAs_Double(int, aWaveform, args[_i++]);
  getArgAs_END

  RobotizeFilter_setParams(aClassPtr, aFreq, aWaveform);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlRobotizeFilter_create GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  void * value = RobotizeFilter_create();

  return ape_object_make_number(_gsPointerToNumber(value));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_destroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_destroy")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  Sfxr_destroy(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_create GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  void * value = Sfxr_create();

  return ape_object_make_number(_gsPointerToNumber(value));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_resetParams GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_resetParams")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  Sfxr_resetParams(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_loadParams GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_STRING/*aFilename*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_loadParams")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_CChars(const char *, aFilename, args[_i++]);
  getArgAs_END

  int value = Sfxr_loadParams(aClassPtr, aFilename);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_loadParamsMemEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMem*/,
    APE_OBJECT_NUMBER/*aLength*/,
    APE_OBJECT_NUMBER/*aCopy*/,
    APE_OBJECT_NUMBER/*aTakeOwnership*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_loadParamsMemEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(unsigned char *, aMem, args[_i++]);
  getArgAs_Double(unsigned, aLength, args[_i++]);
  getArgAs_Double(int, aCopy, args[_i++]);
  getArgAs_Double(int, aTakeOwnership, args[_i++]);
  getArgAs_END

  int value = Sfxr_loadParamsMemEx(aClassPtr, aMem, aLength, aCopy, aTakeOwnership);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_loadPreset GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aPresetNo*/,
    APE_OBJECT_NUMBER/*aRandSeed*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_loadPreset")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aPresetNo, args[_i++]);
  getArgAs_Double(int, aRandSeed, args[_i++]);
  getArgAs_END

  int value = Sfxr_loadPreset(aClassPtr, aPresetNo, aRandSeed);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_setVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVolume*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_setVolume")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aVolume, args[_i++]);
  getArgAs_END

  Sfxr_setVolume(aClassPtr, aVolume);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_setLooping GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aLoop*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_setLooping")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aLoop, args[_i++]);
  getArgAs_END

  Sfxr_setLooping(aClassPtr, aLoop);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_setAutoStop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAutoStop*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_setAutoStop")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aAutoStop, args[_i++]);
  getArgAs_END

  Sfxr_setAutoStop(aClassPtr, aAutoStop);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_set3dMinMaxDistance GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMinDistance*/,
    APE_OBJECT_NUMBER/*aMaxDistance*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_set3dMinMaxDistance")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aMinDistance, args[_i++]);
  getArgAs_Double(float, aMaxDistance, args[_i++]);
  getArgAs_END

  Sfxr_set3dMinMaxDistance(aClassPtr, aMinDistance, aMaxDistance);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_set3dAttenuation GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAttenuationModel*/,
    APE_OBJECT_NUMBER/*aAttenuationRolloffFactor*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_set3dAttenuation")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aAttenuationModel, args[_i++]);
  getArgAs_Double(float, aAttenuationRolloffFactor, args[_i++]);
  getArgAs_END

  Sfxr_set3dAttenuation(aClassPtr, aAttenuationModel, aAttenuationRolloffFactor);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_set3dDopplerFactor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aDopplerFactor*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_set3dDopplerFactor")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aDopplerFactor, args[_i++]);
  getArgAs_END

  Sfxr_set3dDopplerFactor(aClassPtr, aDopplerFactor);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_set3dListenerRelative GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aListenerRelative*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_set3dListenerRelative")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aListenerRelative, args[_i++]);
  getArgAs_END

  Sfxr_set3dListenerRelative(aClassPtr, aListenerRelative);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_set3dDistanceDelay GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aDistanceDelay*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_set3dDistanceDelay")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aDistanceDelay, args[_i++]);
  getArgAs_END

  Sfxr_set3dDistanceDelay(aClassPtr, aDistanceDelay);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_set3dColliderEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aCollider*/,
    APE_OBJECT_NUMBER/*aUserData*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_set3dColliderEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioCollider *, aCollider, args[_i++]);
  getArgAs_Double(int, aUserData, args[_i++]);
  getArgAs_END

  Sfxr_set3dColliderEx(aClassPtr, aCollider, aUserData);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_set3dAttenuator GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAttenuator*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_set3dAttenuator")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioAttenuator *, aAttenuator, args[_i++]);
  getArgAs_END

  Sfxr_set3dAttenuator(aClassPtr, aAttenuator);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_setInaudibleBehavior GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMustTick*/,
    APE_OBJECT_NUMBER/*aKill*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_setInaudibleBehavior")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aMustTick, args[_i++]);
  getArgAs_Double(int, aKill, args[_i++]);
  getArgAs_END

  Sfxr_setInaudibleBehavior(aClassPtr, aMustTick, aKill);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_setLoopPoint GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aLoopPoint*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_setLoopPoint")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(double, aLoopPoint, args[_i++]);
  getArgAs_END

  Sfxr_setLoopPoint(aClassPtr, aLoopPoint);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_getLoopPoint GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_getLoopPoint")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  double value = Sfxr_getLoopPoint(aClassPtr);

  return ape_object_make_number(value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_setFilter GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aFilterId*/,
    APE_OBJECT_NUMBER/*aFilter*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_setFilter")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aFilterId, args[_i++]);
  getArgAs_Pointer(Filter *, aFilter, args[_i++]);
  getArgAs_END

  Sfxr_setFilter(aClassPtr, aFilterId, aFilter);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSfxr_stop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSfxr_stop")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  Sfxr_stop(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSpeech_destroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSpeech_destroy")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  Speech_destroy(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSpeech_create GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  void * value = Speech_create();

  return ape_object_make_number(_gsPointerToNumber(value));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSpeech_setText GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_STRING/*aText*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSpeech_setText")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_CChars(const char *, aText, args[_i++]);
  getArgAs_END

  int value = Speech_setText(aClassPtr, aText);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSpeech_setParamsEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aBaseFrequency*/,
    APE_OBJECT_NUMBER/*aBaseSpeed*/,
    APE_OBJECT_NUMBER/*aBaseDeclination*/,
    APE_OBJECT_NUMBER/*aBaseWaveform*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSpeech_setParamsEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aBaseFrequency, args[_i++]);
  getArgAs_Double(float, aBaseSpeed, args[_i++]);
  getArgAs_Double(float, aBaseDeclination, args[_i++]);
  getArgAs_Double(int, aBaseWaveform, args[_i++]);
  getArgAs_END

  int value = Speech_setParamsEx(aClassPtr, aBaseFrequency, aBaseSpeed, aBaseDeclination, aBaseWaveform);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSpeech_setVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVolume*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSpeech_setVolume")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aVolume, args[_i++]);
  getArgAs_END

  Speech_setVolume(aClassPtr, aVolume);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSpeech_setLooping GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aLoop*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSpeech_setLooping")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aLoop, args[_i++]);
  getArgAs_END

  Speech_setLooping(aClassPtr, aLoop);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSpeech_setAutoStop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAutoStop*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSpeech_setAutoStop")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aAutoStop, args[_i++]);
  getArgAs_END

  Speech_setAutoStop(aClassPtr, aAutoStop);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSpeech_set3dMinMaxDistance GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMinDistance*/,
    APE_OBJECT_NUMBER/*aMaxDistance*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSpeech_set3dMinMaxDistance")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aMinDistance, args[_i++]);
  getArgAs_Double(float, aMaxDistance, args[_i++]);
  getArgAs_END

  Speech_set3dMinMaxDistance(aClassPtr, aMinDistance, aMaxDistance);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSpeech_set3dAttenuation GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAttenuationModel*/,
    APE_OBJECT_NUMBER/*aAttenuationRolloffFactor*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSpeech_set3dAttenuation")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aAttenuationModel, args[_i++]);
  getArgAs_Double(float, aAttenuationRolloffFactor, args[_i++]);
  getArgAs_END

  Speech_set3dAttenuation(aClassPtr, aAttenuationModel, aAttenuationRolloffFactor);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSpeech_set3dDopplerFactor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aDopplerFactor*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSpeech_set3dDopplerFactor")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aDopplerFactor, args[_i++]);
  getArgAs_END

  Speech_set3dDopplerFactor(aClassPtr, aDopplerFactor);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSpeech_set3dListenerRelative GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aListenerRelative*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSpeech_set3dListenerRelative")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aListenerRelative, args[_i++]);
  getArgAs_END

  Speech_set3dListenerRelative(aClassPtr, aListenerRelative);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSpeech_set3dDistanceDelay GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aDistanceDelay*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSpeech_set3dDistanceDelay")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aDistanceDelay, args[_i++]);
  getArgAs_END

  Speech_set3dDistanceDelay(aClassPtr, aDistanceDelay);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSpeech_set3dColliderEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aCollider*/,
    APE_OBJECT_NUMBER/*aUserData*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSpeech_set3dColliderEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioCollider *, aCollider, args[_i++]);
  getArgAs_Double(int, aUserData, args[_i++]);
  getArgAs_END

  Speech_set3dColliderEx(aClassPtr, aCollider, aUserData);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSpeech_set3dAttenuator GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAttenuator*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSpeech_set3dAttenuator")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioAttenuator *, aAttenuator, args[_i++]);
  getArgAs_END

  Speech_set3dAttenuator(aClassPtr, aAttenuator);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSpeech_setInaudibleBehavior GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMustTick*/,
    APE_OBJECT_NUMBER/*aKill*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSpeech_setInaudibleBehavior")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aMustTick, args[_i++]);
  getArgAs_Double(int, aKill, args[_i++]);
  getArgAs_END

  Speech_setInaudibleBehavior(aClassPtr, aMustTick, aKill);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSpeech_setLoopPoint GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aLoopPoint*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSpeech_setLoopPoint")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(double, aLoopPoint, args[_i++]);
  getArgAs_END

  Speech_setLoopPoint(aClassPtr, aLoopPoint);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSpeech_getLoopPoint GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSpeech_getLoopPoint")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  double value = Speech_getLoopPoint(aClassPtr);

  return ape_object_make_number(value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSpeech_setFilter GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aFilterId*/,
    APE_OBJECT_NUMBER/*aFilter*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSpeech_setFilter")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aFilterId, args[_i++]);
  getArgAs_Pointer(Filter *, aFilter, args[_i++]);
  getArgAs_END

  Speech_setFilter(aClassPtr, aFilterId, aFilter);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlSpeech_stop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slSpeech_stop")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  Speech_stop(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_destroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_destroy")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  Wav_destroy(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_create GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  void * value = Wav_create();

  return ape_object_make_number(_gsPointerToNumber(value));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_load GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_STRING/*aFilename*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_load")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_CChars(const char *, aFilename, args[_i++]);
  getArgAs_END

  int value = Wav_load(aClassPtr, aFilename);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_loadMemEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMem*/,
    APE_OBJECT_NUMBER/*aLength*/,
    APE_OBJECT_NUMBER/*aCopy*/,
    APE_OBJECT_NUMBER/*aTakeOwnership*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_loadMemEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(const unsigned char *, aMem, args[_i++]);
  getArgAs_Double(unsigned, aLength, args[_i++]);
  getArgAs_Double(int, aCopy, args[_i++]);
  getArgAs_Double(int, aTakeOwnership, args[_i++]);
  getArgAs_END

  int value = Wav_loadMemEx(aClassPtr, aMem, aLength, aCopy, aTakeOwnership);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_loadRawWave8Ex GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMem*/,
    APE_OBJECT_NUMBER/*aLength*/,
    APE_OBJECT_NUMBER/*aSamplerate*/,
    APE_OBJECT_NUMBER/*aChannels*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_loadRawWave8Ex")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(unsigned char *, aMem, args[_i++]);
  getArgAs_Double(unsigned, aLength, args[_i++]);
  getArgAs_Double(float, aSamplerate, args[_i++]);
  getArgAs_Double(unsigned, aChannels, args[_i++]);
  getArgAs_END

  int value = Wav_loadRawWave8Ex(aClassPtr, aMem, aLength, aSamplerate, aChannels);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_loadRawWave16Ex GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMem*/,
    APE_OBJECT_NUMBER/*aLength*/,
    APE_OBJECT_NUMBER/*aSamplerate*/,
    APE_OBJECT_NUMBER/*aChannels*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_loadRawWave16Ex")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(short *, aMem, args[_i++]);
  getArgAs_Double(unsigned, aLength, args[_i++]);
  getArgAs_Double(float, aSamplerate, args[_i++]);
  getArgAs_Double(unsigned, aChannels, args[_i++]);
  getArgAs_END

  int value = Wav_loadRawWave16Ex(aClassPtr, aMem, aLength, aSamplerate, aChannels);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_loadRawWaveEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMem*/,
    APE_OBJECT_NUMBER/*aLength*/,
    APE_OBJECT_NUMBER/*aSamplerate*/,
    APE_OBJECT_NUMBER/*aChannels*/,
    APE_OBJECT_NUMBER/*aCopy*/,
    APE_OBJECT_NUMBER/*aTakeOwnership*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_loadRawWaveEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(float *, aMem, args[_i++]);
  getArgAs_Double(unsigned, aLength, args[_i++]);
  getArgAs_Double(float, aSamplerate, args[_i++]);
  getArgAs_Double(unsigned, aChannels, args[_i++]);
  getArgAs_Double(int, aCopy, args[_i++]);
  getArgAs_Double(int, aTakeOwnership, args[_i++]);
  getArgAs_END

  int value = Wav_loadRawWaveEx(aClassPtr, aMem, aLength, aSamplerate, aChannels, aCopy, aTakeOwnership);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_getLength GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_getLength")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  double value = Wav_getLength(aClassPtr);

  return ape_object_make_number(value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_setVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVolume*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_setVolume")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aVolume, args[_i++]);
  getArgAs_END

  Wav_setVolume(aClassPtr, aVolume);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_setLooping GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aLoop*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_setLooping")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aLoop, args[_i++]);
  getArgAs_END

  Wav_setLooping(aClassPtr, aLoop);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_setAutoStop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAutoStop*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_setAutoStop")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aAutoStop, args[_i++]);
  getArgAs_END

  Wav_setAutoStop(aClassPtr, aAutoStop);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_set3dMinMaxDistance GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMinDistance*/,
    APE_OBJECT_NUMBER/*aMaxDistance*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_set3dMinMaxDistance")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aMinDistance, args[_i++]);
  getArgAs_Double(float, aMaxDistance, args[_i++]);
  getArgAs_END

  Wav_set3dMinMaxDistance(aClassPtr, aMinDistance, aMaxDistance);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_set3dAttenuation GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAttenuationModel*/,
    APE_OBJECT_NUMBER/*aAttenuationRolloffFactor*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_set3dAttenuation")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aAttenuationModel, args[_i++]);
  getArgAs_Double(float, aAttenuationRolloffFactor, args[_i++]);
  getArgAs_END

  Wav_set3dAttenuation(aClassPtr, aAttenuationModel, aAttenuationRolloffFactor);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_set3dDopplerFactor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aDopplerFactor*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_set3dDopplerFactor")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aDopplerFactor, args[_i++]);
  getArgAs_END

  Wav_set3dDopplerFactor(aClassPtr, aDopplerFactor);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_set3dListenerRelative GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aListenerRelative*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_set3dListenerRelative")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aListenerRelative, args[_i++]);
  getArgAs_END

  Wav_set3dListenerRelative(aClassPtr, aListenerRelative);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_set3dDistanceDelay GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aDistanceDelay*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_set3dDistanceDelay")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aDistanceDelay, args[_i++]);
  getArgAs_END

  Wav_set3dDistanceDelay(aClassPtr, aDistanceDelay);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_set3dColliderEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aCollider*/,
    APE_OBJECT_NUMBER/*aUserData*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_set3dColliderEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioCollider *, aCollider, args[_i++]);
  getArgAs_Double(int, aUserData, args[_i++]);
  getArgAs_END

  Wav_set3dColliderEx(aClassPtr, aCollider, aUserData);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_set3dAttenuator GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAttenuator*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_set3dAttenuator")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioAttenuator *, aAttenuator, args[_i++]);
  getArgAs_END

  Wav_set3dAttenuator(aClassPtr, aAttenuator);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_setInaudibleBehavior GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMustTick*/,
    APE_OBJECT_NUMBER/*aKill*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_setInaudibleBehavior")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aMustTick, args[_i++]);
  getArgAs_Double(int, aKill, args[_i++]);
  getArgAs_END

  Wav_setInaudibleBehavior(aClassPtr, aMustTick, aKill);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_setLoopPoint GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aLoopPoint*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_setLoopPoint")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(double, aLoopPoint, args[_i++]);
  getArgAs_END

  Wav_setLoopPoint(aClassPtr, aLoopPoint);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_getLoopPoint GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_getLoopPoint")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  double value = Wav_getLoopPoint(aClassPtr);

  return ape_object_make_number(value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_setFilter GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aFilterId*/,
    APE_OBJECT_NUMBER/*aFilter*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_setFilter")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aFilterId, args[_i++]);
  getArgAs_Pointer(Filter *, aFilter, args[_i++]);
  getArgAs_END

  Wav_setFilter(aClassPtr, aFilterId, aFilter);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWav_stop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWav_stop")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  Wav_stop(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWaveShaperFilter_destroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWaveShaperFilter_destroy")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  WaveShaperFilter_destroy(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWaveShaperFilter_setParams GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAmount*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWaveShaperFilter_setParams")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aAmount, args[_i++]);
  getArgAs_END

  int value = WaveShaperFilter_setParams(aClassPtr, aAmount);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWaveShaperFilter_create GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  void * value = WaveShaperFilter_create();

  return ape_object_make_number(_gsPointerToNumber(value));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWaveShaperFilter_getParamCount GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWaveShaperFilter_getParamCount")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  int value = WaveShaperFilter_getParamCount(aClassPtr);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWaveShaperFilter_getParamName GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWaveShaperFilter_getParamName")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  const char * value = WaveShaperFilter_getParamName(aClassPtr, aParamIndex);

  return ape_object_make_string(ape, value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWaveShaperFilter_getParamType GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWaveShaperFilter_getParamType")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  unsigned value = WaveShaperFilter_getParamType(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWaveShaperFilter_getParamMax GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWaveShaperFilter_getParamMax")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = WaveShaperFilter_getParamMax(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWaveShaperFilter_getParamMin GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aParamIndex*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWaveShaperFilter_getParamMin")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aParamIndex, args[_i++]);
  getArgAs_END

  float value = WaveShaperFilter_getParamMin(aClassPtr, aParamIndex);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_destroy GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_destroy")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  WavStream_destroy(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_create GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  void * value = WavStream_create();

  return ape_object_make_number(_gsPointerToNumber(value));
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_load GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_STRING/*aFilename*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_load")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_CChars(const char *, aFilename, args[_i++]);
  getArgAs_END

  int value = WavStream_load(aClassPtr, aFilename);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_loadMemEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aData*/,
    APE_OBJECT_NUMBER/*aDataLen*/,
    APE_OBJECT_NUMBER/*aCopy*/,
    APE_OBJECT_NUMBER/*aTakeOwnership*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_loadMemEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(const unsigned char *, aData, args[_i++]);
  getArgAs_Double(unsigned, aDataLen, args[_i++]);
  getArgAs_Double(int, aCopy, args[_i++]);
  getArgAs_Double(int, aTakeOwnership, args[_i++]);
  getArgAs_END

  int value = WavStream_loadMemEx(aClassPtr, aData, aDataLen, aCopy, aTakeOwnership);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_loadToMem GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_STRING/*aFilename*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_loadToMem")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_CChars(const char *, aFilename, args[_i++]);
  getArgAs_END

  int value = WavStream_loadToMem(aClassPtr, aFilename);

  return ape_object_make_number((double)value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_getLength GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_getLength")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  double value = WavStream_getLength(aClassPtr);

  return ape_object_make_number(value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_setVolume GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aVolume*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_setVolume")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aVolume, args[_i++]);
  getArgAs_END

  WavStream_setVolume(aClassPtr, aVolume);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_setLooping GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aLoop*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_setLooping")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aLoop, args[_i++]);
  getArgAs_END

  WavStream_setLooping(aClassPtr, aLoop);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_setAutoStop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAutoStop*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_setAutoStop")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aAutoStop, args[_i++]);
  getArgAs_END

  WavStream_setAutoStop(aClassPtr, aAutoStop);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_set3dMinMaxDistance GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMinDistance*/,
    APE_OBJECT_NUMBER/*aMaxDistance*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_set3dMinMaxDistance")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aMinDistance, args[_i++]);
  getArgAs_Double(float, aMaxDistance, args[_i++]);
  getArgAs_END

  WavStream_set3dMinMaxDistance(aClassPtr, aMinDistance, aMaxDistance);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_set3dAttenuation GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAttenuationModel*/,
    APE_OBJECT_NUMBER/*aAttenuationRolloffFactor*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_set3dAttenuation")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aAttenuationModel, args[_i++]);
  getArgAs_Double(float, aAttenuationRolloffFactor, args[_i++]);
  getArgAs_END

  WavStream_set3dAttenuation(aClassPtr, aAttenuationModel, aAttenuationRolloffFactor);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_set3dDopplerFactor GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aDopplerFactor*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_set3dDopplerFactor")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(float, aDopplerFactor, args[_i++]);
  getArgAs_END

  WavStream_set3dDopplerFactor(aClassPtr, aDopplerFactor);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_set3dListenerRelative GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aListenerRelative*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_set3dListenerRelative")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aListenerRelative, args[_i++]);
  getArgAs_END

  WavStream_set3dListenerRelative(aClassPtr, aListenerRelative);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_set3dDistanceDelay GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aDistanceDelay*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_set3dDistanceDelay")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aDistanceDelay, args[_i++]);
  getArgAs_END

  WavStream_set3dDistanceDelay(aClassPtr, aDistanceDelay);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_set3dColliderEx GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aCollider*/,
    APE_OBJECT_NUMBER/*aUserData*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_set3dColliderEx")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioCollider *, aCollider, args[_i++]);
  getArgAs_Double(int, aUserData, args[_i++]);
  getArgAs_END

  WavStream_set3dColliderEx(aClassPtr, aCollider, aUserData);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_set3dAttenuator GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aAttenuator*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_set3dAttenuator")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Pointer(AudioAttenuator *, aAttenuator, args[_i++]);
  getArgAs_END

  WavStream_set3dAttenuator(aClassPtr, aAttenuator);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_setInaudibleBehavior GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aMustTick*/,
    APE_OBJECT_NUMBER/*aKill*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_setInaudibleBehavior")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(int, aMustTick, args[_i++]);
  getArgAs_Double(int, aKill, args[_i++]);
  getArgAs_END

  WavStream_setInaudibleBehavior(aClassPtr, aMustTick, aKill);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_setLoopPoint GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aLoopPoint*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_setLoopPoint")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(double, aLoopPoint, args[_i++]);
  getArgAs_END

  WavStream_setLoopPoint(aClassPtr, aLoopPoint);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_getLoopPoint GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_getLoopPoint")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  double value = WavStream_getLoopPoint(aClassPtr);

  return ape_object_make_number(value);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_setFilter GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
    APE_OBJECT_NUMBER/*aFilterId*/,
    APE_OBJECT_NUMBER/*aFilter*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_setFilter")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_Double(unsigned, aFilterId, args[_i++]);
  getArgAs_Pointer(Filter *, aFilter, args[_i++]);
  getArgAs_END

  WavStream_setFilter(aClassPtr, aFilterId, aFilter);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSlWavStream_stop GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_NUMBER/*aClassPtr*/,
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("slWavStream_stop")
  getArgAs_Pointer(void *, aClassPtr, args[_i++]);
  getArgAs_END

  WavStream_stop(aClassPtr);

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetCopiedCodeString GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  if (g_codeStringCopied.empty() == false) {
    return ape_object_make_string(ape, g_codeStringCopied.c_str());
  } else {
    return ape_object_make_string(ape, "");
  }
}

#ifdef __ANDROID__
#else
void setClipboard(const char * text);
#endif

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSetCopiedCodeString GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*code*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("setCopiedCodeString")
  getArgAs_CChars(const char *, code, args[_i++]);
  getArgAs_END

  g_codeStringCopied = code;
#ifdef __ANDROID__
#else
  setClipboard(g_codeStringCopied.c_str());
#endif

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetCodeErrorsString GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  if (g_codeErrorsString.empty() == false) {
    return ape_object_make_string(ape, g_codeErrorsString.c_str());
  } else {
    return ape_object_make_string(ape, "");
  }
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureCodeErrorsAppendString GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_STRING/*codeError*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("codeErrorsAppendString")
  getArgAs_String(std::string, codeError, args[_i++]);
  getArgAs_END

  g_codeErrorsString += codeError;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureCodeErrorsForceShowWindow GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_BOOL/*forceShow*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("codeErrorsForceShowWindow")
  getArgAs_Bool(bool, forceShow, args[_i++]);
  getArgAs_END

  g_windowForceShowCodeErrors = forceShow;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureStopRunningCodeAfterThisFrame GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  g_runScript = false;

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetWindowsPlatformInstalledLocationPathString GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  // NOTE(Constantine): Not supported for now.

  return ape_object_make_string(ape, "");
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetWindowsPlatformLocalFolderPathString GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  // NOTE(Constantine): Not supported for now.

  return ape_object_make_string(ape, "");
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetWindowsPlatformLocalCacheFolderPathString GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  // NOTE(Constantine): Not supported for now.

  return ape_object_make_string(ape, "");
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetWindowsPlatformTemporaryFolderPathString GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  // NOTE(Constantine): Not supported for now.

  return ape_object_make_string(ape, "");
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetTimeClockNowSinceEpoch100NsecCount GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

#if defined(__linux__) || defined(__ANDROID__)
  return ape_object_make_number(0);
#else
  auto count = std::chrono::system_clock::now().time_since_epoch().count();

  return ape_object_make_number((double)count);
#endif
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetRightGamepadStickAsArrowKeys GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  // NOTE(Constantine): Not used.

  return ape_object_make_bool(false);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSetRightGamepadStickAsArrowKeys GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_BOOL/*enable*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("setRightGamepadStickAsArrowKeys")
  getArgAs_Bool(bool, enable, args[_i++]);
  getArgAs_END

  // NOTE(Constantine): Not used.

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetControlUiWithGamepad GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  // NOTE(Constantine): Not used.

  return ape_object_make_bool(false);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSetControlUiWithGamepad GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_BOOL/*enable*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("setControlUiWithGamepad")
  getArgAs_Bool(bool, enable, args[_i++]);
  getArgAs_END

  // NOTE(Constantine): Not used.

  return ape_object_make_null();
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureGetFrame0Cache GS_C_PROCEDURE_PARAMETERS() {
  if (!ape_check_args(ape, true, argc, args, 0, 0)) { return ape_object_make_null(); }

  return ape_object_make_bool(g_frame0CacheEnable);
}

GS_API GS_C_PROCEDURE_RETURN_TYPE() _gsCProcedureSetFrame0Cache GS_C_PROCEDURE_PARAMETERS() {
  int APE_ARGS[] = {
    APE_OBJECT_BOOL/*enable*/
  };
  if (!ape_check_args(ape, true, argc, args, sizeof(APE_ARGS) / sizeof(int), APE_ARGS)) { return ape_object_make_null(); }

  int _i = 0;

  getArgAs_BEGIN("setFrame0Cache")
  getArgAs_Bool(bool, enable, args[_i++]);
  getArgAs_END

  g_frame0CacheEnable = enable;
  g_frame0CacheStartPositionIsDirty = true;

  return ape_object_make_null();
}

void mape_set_c_procedures() {
  // Game Script REDGPU Version:
  mape_set_native_function(0, g_ape, "getGameScriptRedGpuVersionInitDataPointer", _gsCProcedureGetGameScriptRedGpuVersionInitDataPointer, NULL);
  mape_set_native_function(0, g_ape, "getGameScriptRedGpuVersionWindowDataPointer", _gsCProcedureGetGameScriptRedGpuVersionWindowDataPointer, NULL);
  mape_set_native_function(0, g_ape, "gameScriptRedGpuVersionGetEnableCustomRendering", _gsCProcedureGameScriptRedGpuVersionGetEnableCustomRendering, NULL);
  mape_set_native_function(0, g_ape, "gameScriptRedGpuVersionSetEnableCustomRendering", _gsCProcedureGameScriptRedGpuVersionSetEnableCustomRendering, NULL);
  mape_set_native_function(0, g_ape, "gameScriptRedGpuVersionImguiRender", _gsCProcedureGameScriptRedGpuVersionImguiRender, NULL);
  // Game Script for Windows Platform
  mape_set_native_function(0, g_ape, "isWindowsPlatform", _gsCProcedureIsWindowsPlatform, NULL);
  mape_set_native_function(0, g_ape, "setAllWindowsHidden", _gsCProcedureSetAllWindowsHidden, NULL);
  //mape_set_native_function(0, g_ape, "getGamepadsCount", _gsCProcedureGetGamepadsCount, NULL);
  mape_set_native_function(0, g_ape, "getWindowsPlatformInstalledLocationPathString", _gsCProcedureGetWindowsPlatformInstalledLocationPathString, NULL);
  mape_set_native_function(0, g_ape, "getWindowsPlatformLocalFolderPathString", _gsCProcedureGetWindowsPlatformLocalFolderPathString, NULL);
  mape_set_native_function(0, g_ape, "getWindowsPlatformLocalCacheFolderPathString", _gsCProcedureGetWindowsPlatformLocalCacheFolderPathString, NULL);
  mape_set_native_function(0, g_ape, "getWindowsPlatformTemporaryFolderPathString", _gsCProcedureGetWindowsPlatformTemporaryFolderPathString, NULL);
  mape_set_native_function(0, g_ape, "getTimeClockNowSinceEpoch100NsecCount", _gsCProcedureGetTimeClockNowSinceEpoch100NsecCount, NULL);
  mape_set_native_function(0, g_ape, "getRightGamepadStickAsArrowKeys", _gsCProcedureGetRightGamepadStickAsArrowKeys, NULL);
  mape_set_native_function(0, g_ape, "setRightGamepadStickAsArrowKeys", _gsCProcedureSetRightGamepadStickAsArrowKeys, NULL);
  mape_set_native_function(0, g_ape, "getControlUiWithGamepad", _gsCProcedureGetControlUiWithGamepad, NULL);
  mape_set_native_function(0, g_ape, "setControlUiWithGamepad", _gsCProcedureSetControlUiWithGamepad, NULL);
  // Game Script for Android
  mape_set_native_function(0, g_ape, "printConsoleClear", _gsCProcedurePrintConsoleClear, NULL);
  mape_set_native_function(0, g_ape, "isAndroid", _gsCProcedureIsAndroid, NULL);
  mape_set_native_function(0, g_ape, "areAllWindowsHidden", _gsCProcedureAreAllWindowsHidden, NULL);
  mape_set_native_function(0, g_ape, "toggleDefaultViewportClearCommands", _gsCProcedureToggleDefaultViewportClearCommands, NULL);
  mape_set_native_function(0, g_ape, "getTimeClockRealTimeSecAndNsec", _gsCProcedureGetTimeClockRealTimeSecAndNsec, NULL);
  mape_set_native_function(0, g_ape, "getTimeClockMonotonicSecAndNsec", _gsCProcedureGetTimeClockMonotonicSecAndNsec, NULL);
  mape_set_native_function(0, g_ape, "stringDownloadFromUrl", _gsCProcedureStringDownloadFromUrl, NULL);
  mape_set_native_function(0, g_ape, "deviceGetOrientation", _gsCProcedureDeviceGetOrientation, NULL);
  mape_set_native_function(0, g_ape, "keyEventsGetUniqueIdCounter", _gsCProcedureKeyEventsGetUniqueIdCounter, NULL);
  mape_set_native_function(0, g_ape, "motionEventsGetUniqueIdCounter", _gsCProcedureMotionEventsGetUniqueIdCounter, NULL);
  mape_set_native_function(0, g_ape, "keyEventsGetCircularBufferMaxCount", _gsCProcedureKeyEventsGetCircularBufferMaxCount, NULL);
  mape_set_native_function(0, g_ape, "motionEventsGetCircularBufferMaxCount", _gsCProcedureMotionEventsGetCircularBufferMaxCount, NULL);
  mape_set_native_function(0, g_ape, "keyEventsSetCircularBufferMaxCount", _gsCProcedureKeyEventsSetCircularBufferMaxCount, NULL);
  mape_set_native_function(0, g_ape, "motionEventsSetCircularBufferMaxCount", _gsCProcedureMotionEventsSetCircularBufferMaxCount, NULL);
  mape_set_native_function(0, g_ape, "keyEventsGetEvent", _gsCProcedureKeyEventsGetEvent, NULL);
  mape_set_native_function(0, g_ape, "motionEventsGetEvent", _gsCProcedureMotionEventsGetEvent, NULL);
  mape_set_native_function(0, g_ape, "motionEventsGetEventPointer", _gsCProcedureMotionEventsGetEventPointer, NULL);
  mape_set_native_function(0, g_ape, "imguiSetStyleColor", _gsCProcedureImguiSetStyleColor, NULL);
  mape_set_native_function(0, g_ape, "imguiTextUnformatted", _gsCProcedureImguiTextUnformatted, NULL);
  mape_set_native_function(0, g_ape, "setGameScriptString", _gsCProcedureSetGameScriptString, NULL);
  mape_set_native_function(0, g_ape, "getCopiedCodeString", _gsCProcedureGetCopiedCodeString, NULL);
  mape_set_native_function(0, g_ape, "setCopiedCodeString", _gsCProcedureSetCopiedCodeString, NULL);
  mape_set_native_function(0, g_ape, "getCodeErrorsString", _gsCProcedureGetCodeErrorsString, NULL);
  mape_set_native_function(0, g_ape, "codeErrorsAppendString", _gsCProcedureCodeErrorsAppendString, NULL);
  mape_set_native_function(0, g_ape, "codeErrorsForceShowWindow", _gsCProcedureCodeErrorsForceShowWindow, NULL);
  mape_set_native_function(0, g_ape, "stopRunningCodeAfterThisFrame", _gsCProcedureStopRunningCodeAfterThisFrame, NULL);
  mape_set_native_function(0, g_ape, "getFrame0Cache", _gsCProcedureGetFrame0Cache, NULL);
  mape_set_native_function(0, g_ape, "setFrame0Cache", _gsCProcedureSetFrame0Cache, NULL);
  //mape_set_native_function(0, g_ape, "sg_struct_sizeof", _gsCProcedure_sg_struct_sizeof, NULL);
  //mape_set_native_function(0, g_ape, "sg_struct_member_sizeof", _gsCProcedure_sg_struct_member_sizeof, NULL);
  //mape_set_native_function(0, g_ape, "sg_struct_member_offsetof", _gsCProcedure_sg_struct_member_offsetof, NULL);
  //mape_set_native_function(0, g_ape, "sg_setup", _gsCProcedure_sg_setup, NULL);
  //mape_set_native_function(0, g_ape, "sg_shutdown", _gsCProcedure_sg_shutdown, NULL);
  //mape_set_native_function(0, g_ape, "sg_isvalid", _gsCProcedure_sg_isvalid, NULL);
  //mape_set_native_function(0, g_ape, "sg_reset_state_cache", _gsCProcedure_sg_reset_state_cache, NULL);
  //mape_set_native_function(0, g_ape, "sg_push_debug_group", _gsCProcedure_sg_push_debug_group, NULL);
  //mape_set_native_function(0, g_ape, "sg_pop_debug_group", _gsCProcedure_sg_pop_debug_group, NULL);
  //mape_set_native_function(0, g_ape, "sg_make_buffer", _gsCProcedure_sg_make_buffer, NULL);
  //mape_set_native_function(0, g_ape, "sg_make_image", _gsCProcedure_sg_make_image, NULL);
  //mape_set_native_function(0, g_ape, "sg_make_shader", _gsCProcedure_sg_make_shader, NULL);
  //mape_set_native_function(0, g_ape, "sg_make_pipeline", _gsCProcedure_sg_make_pipeline, NULL);
  //mape_set_native_function(0, g_ape, "sg_make_pass", _gsCProcedure_sg_make_pass, NULL);
  //mape_set_native_function(0, g_ape, "sg_destroy_buffer", _gsCProcedure_sg_destroy_buffer, NULL);
  //mape_set_native_function(0, g_ape, "sg_destroy_image", _gsCProcedure_sg_destroy_image, NULL);
  //mape_set_native_function(0, g_ape, "sg_destroy_shader", _gsCProcedure_sg_destroy_shader, NULL);
  //mape_set_native_function(0, g_ape, "sg_destroy_pipeline", _gsCProcedure_sg_destroy_pipeline, NULL);
  //mape_set_native_function(0, g_ape, "sg_destroy_pass", _gsCProcedure_sg_destroy_pass, NULL);
  //mape_set_native_function(0, g_ape, "sg_update_buffer", _gsCProcedure_sg_update_buffer, NULL);
  //mape_set_native_function(0, g_ape, "sg_update_image", _gsCProcedure_sg_update_image, NULL);
  //mape_set_native_function(0, g_ape, "sg_append_buffer", _gsCProcedure_sg_append_buffer, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_buffer_overflow", _gsCProcedure_sg_query_buffer_overflow, NULL);
  //mape_set_native_function(0, g_ape, "sg_begin_default_pass", _gsCProcedure_sg_begin_default_pass, NULL);
  //mape_set_native_function(0, g_ape, "sg_begin_default_passf", _gsCProcedure_sg_begin_default_passf, NULL);
  //mape_set_native_function(0, g_ape, "sg_begin_pass", _gsCProcedure_sg_begin_pass, NULL);
  //mape_set_native_function(0, g_ape, "sg_apply_viewport", _gsCProcedure_sg_apply_viewport, NULL);
  //mape_set_native_function(0, g_ape, "sg_apply_viewportf", _gsCProcedure_sg_apply_viewportf, NULL);
  //mape_set_native_function(0, g_ape, "sg_apply_scissor_rect", _gsCProcedure_sg_apply_scissor_rect, NULL);
  //mape_set_native_function(0, g_ape, "sg_apply_scissor_rectf", _gsCProcedure_sg_apply_scissor_rectf, NULL);
  //mape_set_native_function(0, g_ape, "sg_apply_pipeline", _gsCProcedure_sg_apply_pipeline, NULL);
  //mape_set_native_function(0, g_ape, "sg_apply_bindings", _gsCProcedure_sg_apply_bindings, NULL);
  //mape_set_native_function(0, g_ape, "sg_apply_uniforms", _gsCProcedure_sg_apply_uniforms, NULL);
  //mape_set_native_function(0, g_ape, "sg_draw", _gsCProcedure_sg_draw, NULL);
  //mape_set_native_function(0, g_ape, "sg_end_pass", _gsCProcedure_sg_end_pass, NULL);
  //mape_set_native_function(0, g_ape, "sg_commit", _gsCProcedure_sg_commit, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_desc", _gsCProcedure_sg_query_desc, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_backend", _gsCProcedure_sg_query_backend, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_features", _gsCProcedure_sg_query_features, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_limits", _gsCProcedure_sg_query_limits, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_pixelformat", _gsCProcedure_sg_query_pixelformat, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_buffer_state", _gsCProcedure_sg_query_buffer_state, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_image_state", _gsCProcedure_sg_query_image_state, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_shader_state", _gsCProcedure_sg_query_shader_state, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_pipeline_state", _gsCProcedure_sg_query_pipeline_state, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_pass_state", _gsCProcedure_sg_query_pass_state, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_buffer_info", _gsCProcedure_sg_query_buffer_info, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_image_info", _gsCProcedure_sg_query_image_info, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_shader_info", _gsCProcedure_sg_query_shader_info, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_pipeline_info", _gsCProcedure_sg_query_pipeline_info, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_pass_info", _gsCProcedure_sg_query_pass_info, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_buffer_defaults", _gsCProcedure_sg_query_buffer_defaults, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_image_defaults", _gsCProcedure_sg_query_image_defaults, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_shader_defaults", _gsCProcedure_sg_query_shader_defaults, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_pipeline_defaults", _gsCProcedure_sg_query_pipeline_defaults, NULL);
  //mape_set_native_function(0, g_ape, "sg_query_pass_defaults", _gsCProcedure_sg_query_pass_defaults, NULL);
  //mape_set_native_function(0, g_ape, "sg_alloc_buffer", _gsCProcedure_sg_alloc_buffer, NULL);
  //mape_set_native_function(0, g_ape, "sg_alloc_image", _gsCProcedure_sg_alloc_image, NULL);
  //mape_set_native_function(0, g_ape, "sg_alloc_shader", _gsCProcedure_sg_alloc_shader, NULL);
  //mape_set_native_function(0, g_ape, "sg_alloc_pipeline", _gsCProcedure_sg_alloc_pipeline, NULL);
  //mape_set_native_function(0, g_ape, "sg_alloc_pass", _gsCProcedure_sg_alloc_pass, NULL);
  //mape_set_native_function(0, g_ape, "sg_dealloc_buffer", _gsCProcedure_sg_dealloc_buffer, NULL);
  //mape_set_native_function(0, g_ape, "sg_dealloc_image", _gsCProcedure_sg_dealloc_image, NULL);
  //mape_set_native_function(0, g_ape, "sg_dealloc_shader", _gsCProcedure_sg_dealloc_shader, NULL);
  //mape_set_native_function(0, g_ape, "sg_dealloc_pipeline", _gsCProcedure_sg_dealloc_pipeline, NULL);
  //mape_set_native_function(0, g_ape, "sg_dealloc_pass", _gsCProcedure_sg_dealloc_pass, NULL);
  //mape_set_native_function(0, g_ape, "sg_init_buffer", _gsCProcedure_sg_init_buffer, NULL);
  //mape_set_native_function(0, g_ape, "sg_init_image", _gsCProcedure_sg_init_image, NULL);
  //mape_set_native_function(0, g_ape, "sg_init_shader", _gsCProcedure_sg_init_shader, NULL);
  //mape_set_native_function(0, g_ape, "sg_init_pipeline", _gsCProcedure_sg_init_pipeline, NULL);
  //mape_set_native_function(0, g_ape, "sg_init_pass", _gsCProcedure_sg_init_pass, NULL);
  //mape_set_native_function(0, g_ape, "sg_uninit_buffer", _gsCProcedure_sg_uninit_buffer, NULL);
  //mape_set_native_function(0, g_ape, "sg_uninit_image", _gsCProcedure_sg_uninit_image, NULL);
  //mape_set_native_function(0, g_ape, "sg_uninit_shader", _gsCProcedure_sg_uninit_shader, NULL);
  //mape_set_native_function(0, g_ape, "sg_uninit_pipeline", _gsCProcedure_sg_uninit_pipeline, NULL);
  //mape_set_native_function(0, g_ape, "sg_uninit_pass", _gsCProcedure_sg_uninit_pass, NULL);
  //mape_set_native_function(0, g_ape, "sg_fail_buffer", _gsCProcedure_sg_fail_buffer, NULL);
  //mape_set_native_function(0, g_ape, "sg_fail_image", _gsCProcedure_sg_fail_image, NULL);
  //mape_set_native_function(0, g_ape, "sg_fail_shader", _gsCProcedure_sg_fail_shader, NULL);
  //mape_set_native_function(0, g_ape, "sg_fail_pipeline", _gsCProcedure_sg_fail_pipeline, NULL);
  //mape_set_native_function(0, g_ape, "sg_fail_pass", _gsCProcedure_sg_fail_pass, NULL);
  //mape_set_native_function(0, g_ape, "sg_setup_context", _gsCProcedure_sg_setup_context, NULL);
  //mape_set_native_function(0, g_ape, "sg_activate_context", _gsCProcedure_sg_activate_context, NULL);
  //mape_set_native_function(0, g_ape, "sg_discard_context", _gsCProcedure_sg_discard_context, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_destroy", _gsCProcedureSlSoloud_destroy, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_create", _gsCProcedureSlSoloud_create, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_initEx", _gsCProcedureSlSoloud_initEx, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_deinit", _gsCProcedureSlSoloud_deinit, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getVersion", _gsCProcedureSlSoloud_getVersion, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getErrorString", _gsCProcedureSlSoloud_getErrorString, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getBackendId", _gsCProcedureSlSoloud_getBackendId, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getBackendString", _gsCProcedureSlSoloud_getBackendString, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getBackendChannels", _gsCProcedureSlSoloud_getBackendChannels, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getBackendSamplerate", _gsCProcedureSlSoloud_getBackendSamplerate, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getBackendBufferSize", _gsCProcedureSlSoloud_getBackendBufferSize, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setSpeakerPosition", _gsCProcedureSlSoloud_setSpeakerPosition, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getSpeakerPosition", _gsCProcedureSlSoloud_getSpeakerPosition, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_playEx", _gsCProcedureSlSoloud_playEx, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_playClockedEx", _gsCProcedureSlSoloud_playClockedEx, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_play3dEx", _gsCProcedureSlSoloud_play3dEx, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_play3dClockedEx", _gsCProcedureSlSoloud_play3dClockedEx, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_playBackgroundEx", _gsCProcedureSlSoloud_playBackgroundEx, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_seek", _gsCProcedureSlSoloud_seek, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_stop", _gsCProcedureSlSoloud_stop, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_stopAll", _gsCProcedureSlSoloud_stopAll, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_stopAudioSource", _gsCProcedureSlSoloud_stopAudioSource, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_countAudioSource", _gsCProcedureSlSoloud_countAudioSource, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setFilterParameter", _gsCProcedureSlSoloud_setFilterParameter, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getFilterParameter", _gsCProcedureSlSoloud_getFilterParameter, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_fadeFilterParameter", _gsCProcedureSlSoloud_fadeFilterParameter, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_oscillateFilterParameter", _gsCProcedureSlSoloud_oscillateFilterParameter, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getStreamTime", _gsCProcedureSlSoloud_getStreamTime, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getStreamPosition", _gsCProcedureSlSoloud_getStreamPosition, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getPause", _gsCProcedureSlSoloud_getPause, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getVolume", _gsCProcedureSlSoloud_getVolume, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getOverallVolume", _gsCProcedureSlSoloud_getOverallVolume, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getPan", _gsCProcedureSlSoloud_getPan, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getSamplerate", _gsCProcedureSlSoloud_getSamplerate, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getProtectVoice", _gsCProcedureSlSoloud_getProtectVoice, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getActiveVoiceCount", _gsCProcedureSlSoloud_getActiveVoiceCount, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getVoiceCount", _gsCProcedureSlSoloud_getVoiceCount, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_isValidVoiceHandle", _gsCProcedureSlSoloud_isValidVoiceHandle, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getRelativePlaySpeed", _gsCProcedureSlSoloud_getRelativePlaySpeed, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getPostClipScaler", _gsCProcedureSlSoloud_getPostClipScaler, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getMainResampler", _gsCProcedureSlSoloud_getMainResampler, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getGlobalVolume", _gsCProcedureSlSoloud_getGlobalVolume, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getMaxActiveVoiceCount", _gsCProcedureSlSoloud_getMaxActiveVoiceCount, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getLooping", _gsCProcedureSlSoloud_getLooping, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getAutoStop", _gsCProcedureSlSoloud_getAutoStop, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getLoopPoint", _gsCProcedureSlSoloud_getLoopPoint, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setLoopPoint", _gsCProcedureSlSoloud_setLoopPoint, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setLooping", _gsCProcedureSlSoloud_setLooping, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setAutoStop", _gsCProcedureSlSoloud_setAutoStop, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setMaxActiveVoiceCount", _gsCProcedureSlSoloud_setMaxActiveVoiceCount, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setInaudibleBehavior", _gsCProcedureSlSoloud_setInaudibleBehavior, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setGlobalVolume", _gsCProcedureSlSoloud_setGlobalVolume, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setPostClipScaler", _gsCProcedureSlSoloud_setPostClipScaler, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setMainResampler", _gsCProcedureSlSoloud_setMainResampler, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setPause", _gsCProcedureSlSoloud_setPause, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setPauseAll", _gsCProcedureSlSoloud_setPauseAll, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setRelativePlaySpeed", _gsCProcedureSlSoloud_setRelativePlaySpeed, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setProtectVoice", _gsCProcedureSlSoloud_setProtectVoice, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setSamplerate", _gsCProcedureSlSoloud_setSamplerate, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setPan", _gsCProcedureSlSoloud_setPan, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setPanAbsolute", _gsCProcedureSlSoloud_setPanAbsolute, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setChannelVolume", _gsCProcedureSlSoloud_setChannelVolume, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setVolume", _gsCProcedureSlSoloud_setVolume, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setDelaySamples", _gsCProcedureSlSoloud_setDelaySamples, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_fadeVolume", _gsCProcedureSlSoloud_fadeVolume, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_fadePan", _gsCProcedureSlSoloud_fadePan, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_fadeRelativePlaySpeed", _gsCProcedureSlSoloud_fadeRelativePlaySpeed, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_fadeGlobalVolume", _gsCProcedureSlSoloud_fadeGlobalVolume, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_schedulePause", _gsCProcedureSlSoloud_schedulePause, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_scheduleStop", _gsCProcedureSlSoloud_scheduleStop, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_oscillateVolume", _gsCProcedureSlSoloud_oscillateVolume, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_oscillatePan", _gsCProcedureSlSoloud_oscillatePan, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_oscillateRelativePlaySpeed", _gsCProcedureSlSoloud_oscillateRelativePlaySpeed, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_oscillateGlobalVolume", _gsCProcedureSlSoloud_oscillateGlobalVolume, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setGlobalFilter", _gsCProcedureSlSoloud_setGlobalFilter, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_setVisualizationEnable", _gsCProcedureSlSoloud_setVisualizationEnable, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_calcFFT", _gsCProcedureSlSoloud_calcFFT, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getWave", _gsCProcedureSlSoloud_getWave, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getApproximateVolume", _gsCProcedureSlSoloud_getApproximateVolume, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getLoopCount", _gsCProcedureSlSoloud_getLoopCount, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_getInfo", _gsCProcedureSlSoloud_getInfo, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_createVoiceGroup", _gsCProcedureSlSoloud_createVoiceGroup, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_destroyVoiceGroup", _gsCProcedureSlSoloud_destroyVoiceGroup, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_addVoiceToGroup", _gsCProcedureSlSoloud_addVoiceToGroup, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_isVoiceGroup", _gsCProcedureSlSoloud_isVoiceGroup, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_isVoiceGroupEmpty", _gsCProcedureSlSoloud_isVoiceGroupEmpty, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_update3dAudio", _gsCProcedureSlSoloud_update3dAudio, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_set3dSoundSpeed", _gsCProcedureSlSoloud_set3dSoundSpeed, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_get3dSoundSpeed", _gsCProcedureSlSoloud_get3dSoundSpeed, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_set3dListenerParametersEx", _gsCProcedureSlSoloud_set3dListenerParametersEx, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_set3dListenerPosition", _gsCProcedureSlSoloud_set3dListenerPosition, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_set3dListenerAt", _gsCProcedureSlSoloud_set3dListenerAt, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_set3dListenerUp", _gsCProcedureSlSoloud_set3dListenerUp, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_set3dListenerVelocity", _gsCProcedureSlSoloud_set3dListenerVelocity, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_set3dSourceParametersEx", _gsCProcedureSlSoloud_set3dSourceParametersEx, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_set3dSourcePosition", _gsCProcedureSlSoloud_set3dSourcePosition, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_set3dSourceVelocity", _gsCProcedureSlSoloud_set3dSourceVelocity, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_set3dSourceMinMaxDistance", _gsCProcedureSlSoloud_set3dSourceMinMaxDistance, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_set3dSourceAttenuation", _gsCProcedureSlSoloud_set3dSourceAttenuation, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_set3dSourceDopplerFactor", _gsCProcedureSlSoloud_set3dSourceDopplerFactor, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_mix", _gsCProcedureSlSoloud_mix, NULL);
  mape_set_native_function(0, g_ape, "slSoloud_mixSigned16", _gsCProcedureSlSoloud_mixSigned16, NULL);
  mape_set_native_function(0, g_ape, "slBassboostFilter_destroy", _gsCProcedureSlBassboostFilter_destroy, NULL);
  mape_set_native_function(0, g_ape, "slBassboostFilter_getParamCount", _gsCProcedureSlBassboostFilter_getParamCount, NULL);
  mape_set_native_function(0, g_ape, "slBassboostFilter_getParamName", _gsCProcedureSlBassboostFilter_getParamName, NULL);
  mape_set_native_function(0, g_ape, "slBassboostFilter_getParamType", _gsCProcedureSlBassboostFilter_getParamType, NULL);
  mape_set_native_function(0, g_ape, "slBassboostFilter_getParamMax", _gsCProcedureSlBassboostFilter_getParamMax, NULL);
  mape_set_native_function(0, g_ape, "slBassboostFilter_getParamMin", _gsCProcedureSlBassboostFilter_getParamMin, NULL);
  mape_set_native_function(0, g_ape, "slBassboostFilter_setParams", _gsCProcedureSlBassboostFilter_setParams, NULL);
  mape_set_native_function(0, g_ape, "slBassboostFilter_create", _gsCProcedureSlBassboostFilter_create, NULL);
  mape_set_native_function(0, g_ape, "slBiquadResonantFilter_destroy", _gsCProcedureSlBiquadResonantFilter_destroy, NULL);
  mape_set_native_function(0, g_ape, "slBiquadResonantFilter_getParamCount", _gsCProcedureSlBiquadResonantFilter_getParamCount, NULL);
  mape_set_native_function(0, g_ape, "slBiquadResonantFilter_getParamName", _gsCProcedureSlBiquadResonantFilter_getParamName, NULL);
  mape_set_native_function(0, g_ape, "slBiquadResonantFilter_getParamType", _gsCProcedureSlBiquadResonantFilter_getParamType, NULL);
  mape_set_native_function(0, g_ape, "slBiquadResonantFilter_getParamMax", _gsCProcedureSlBiquadResonantFilter_getParamMax, NULL);
  mape_set_native_function(0, g_ape, "slBiquadResonantFilter_getParamMin", _gsCProcedureSlBiquadResonantFilter_getParamMin, NULL);
  mape_set_native_function(0, g_ape, "slBiquadResonantFilter_create", _gsCProcedureSlBiquadResonantFilter_create, NULL);
  mape_set_native_function(0, g_ape, "slBiquadResonantFilter_setParams", _gsCProcedureSlBiquadResonantFilter_setParams, NULL);
  mape_set_native_function(0, g_ape, "slBus_destroy", _gsCProcedureSlBus_destroy, NULL);
  mape_set_native_function(0, g_ape, "slBus_create", _gsCProcedureSlBus_create, NULL);
  mape_set_native_function(0, g_ape, "slBus_setFilter", _gsCProcedureSlBus_setFilter, NULL);
  mape_set_native_function(0, g_ape, "slBus_playEx", _gsCProcedureSlBus_playEx, NULL);
  mape_set_native_function(0, g_ape, "slBus_playClockedEx", _gsCProcedureSlBus_playClockedEx, NULL);
  mape_set_native_function(0, g_ape, "slBus_play3dEx", _gsCProcedureSlBus_play3dEx, NULL);
  mape_set_native_function(0, g_ape, "slBus_play3dClockedEx", _gsCProcedureSlBus_play3dClockedEx, NULL);
  mape_set_native_function(0, g_ape, "slBus_setChannels", _gsCProcedureSlBus_setChannels, NULL);
  mape_set_native_function(0, g_ape, "slBus_setVisualizationEnable", _gsCProcedureSlBus_setVisualizationEnable, NULL);
  mape_set_native_function(0, g_ape, "slBus_annexSound", _gsCProcedureSlBus_annexSound, NULL);
  mape_set_native_function(0, g_ape, "slBus_calcFFT", _gsCProcedureSlBus_calcFFT, NULL);
  mape_set_native_function(0, g_ape, "slBus_getWave", _gsCProcedureSlBus_getWave, NULL);
  mape_set_native_function(0, g_ape, "slBus_getApproximateVolume", _gsCProcedureSlBus_getApproximateVolume, NULL);
  mape_set_native_function(0, g_ape, "slBus_getActiveVoiceCount", _gsCProcedureSlBus_getActiveVoiceCount, NULL);
  mape_set_native_function(0, g_ape, "slBus_getResampler", _gsCProcedureSlBus_getResampler, NULL);
  mape_set_native_function(0, g_ape, "slBus_setResampler", _gsCProcedureSlBus_setResampler, NULL);
  mape_set_native_function(0, g_ape, "slBus_setVolume", _gsCProcedureSlBus_setVolume, NULL);
  mape_set_native_function(0, g_ape, "slBus_setLooping", _gsCProcedureSlBus_setLooping, NULL);
  mape_set_native_function(0, g_ape, "slBus_setAutoStop", _gsCProcedureSlBus_setAutoStop, NULL);
  mape_set_native_function(0, g_ape, "slBus_set3dMinMaxDistance", _gsCProcedureSlBus_set3dMinMaxDistance, NULL);
  mape_set_native_function(0, g_ape, "slBus_set3dAttenuation", _gsCProcedureSlBus_set3dAttenuation, NULL);
  mape_set_native_function(0, g_ape, "slBus_set3dDopplerFactor", _gsCProcedureSlBus_set3dDopplerFactor, NULL);
  mape_set_native_function(0, g_ape, "slBus_set3dListenerRelative", _gsCProcedureSlBus_set3dListenerRelative, NULL);
  mape_set_native_function(0, g_ape, "slBus_set3dDistanceDelay", _gsCProcedureSlBus_set3dDistanceDelay, NULL);
  mape_set_native_function(0, g_ape, "slBus_set3dColliderEx", _gsCProcedureSlBus_set3dColliderEx, NULL);
  mape_set_native_function(0, g_ape, "slBus_set3dAttenuator", _gsCProcedureSlBus_set3dAttenuator, NULL);
  mape_set_native_function(0, g_ape, "slBus_setInaudibleBehavior", _gsCProcedureSlBus_setInaudibleBehavior, NULL);
  mape_set_native_function(0, g_ape, "slBus_setLoopPoint", _gsCProcedureSlBus_setLoopPoint, NULL);
  mape_set_native_function(0, g_ape, "slBus_getLoopPoint", _gsCProcedureSlBus_getLoopPoint, NULL);
  mape_set_native_function(0, g_ape, "slBus_stop", _gsCProcedureSlBus_stop, NULL);
  mape_set_native_function(0, g_ape, "slDCRemovalFilter_destroy", _gsCProcedureSlDCRemovalFilter_destroy, NULL);
  mape_set_native_function(0, g_ape, "slDCRemovalFilter_create", _gsCProcedureSlDCRemovalFilter_create, NULL);
  mape_set_native_function(0, g_ape, "slDCRemovalFilter_setParamsEx", _gsCProcedureSlDCRemovalFilter_setParamsEx, NULL);
  mape_set_native_function(0, g_ape, "slDCRemovalFilter_getParamCount", _gsCProcedureSlDCRemovalFilter_getParamCount, NULL);
  mape_set_native_function(0, g_ape, "slDCRemovalFilter_getParamName", _gsCProcedureSlDCRemovalFilter_getParamName, NULL);
  mape_set_native_function(0, g_ape, "slDCRemovalFilter_getParamType", _gsCProcedureSlDCRemovalFilter_getParamType, NULL);
  mape_set_native_function(0, g_ape, "slDCRemovalFilter_getParamMax", _gsCProcedureSlDCRemovalFilter_getParamMax, NULL);
  mape_set_native_function(0, g_ape, "slDCRemovalFilter_getParamMin", _gsCProcedureSlDCRemovalFilter_getParamMin, NULL);
  mape_set_native_function(0, g_ape, "slEchoFilter_destroy", _gsCProcedureSlEchoFilter_destroy, NULL);
  mape_set_native_function(0, g_ape, "slEchoFilter_getParamCount", _gsCProcedureSlEchoFilter_getParamCount, NULL);
  mape_set_native_function(0, g_ape, "slEchoFilter_getParamName", _gsCProcedureSlEchoFilter_getParamName, NULL);
  mape_set_native_function(0, g_ape, "slEchoFilter_getParamType", _gsCProcedureSlEchoFilter_getParamType, NULL);
  mape_set_native_function(0, g_ape, "slEchoFilter_getParamMax", _gsCProcedureSlEchoFilter_getParamMax, NULL);
  mape_set_native_function(0, g_ape, "slEchoFilter_getParamMin", _gsCProcedureSlEchoFilter_getParamMin, NULL);
  mape_set_native_function(0, g_ape, "slEchoFilter_create", _gsCProcedureSlEchoFilter_create, NULL);
  mape_set_native_function(0, g_ape, "slEchoFilter_setParamsEx", _gsCProcedureSlEchoFilter_setParamsEx, NULL);
  mape_set_native_function(0, g_ape, "slFFTFilter_destroy", _gsCProcedureSlFFTFilter_destroy, NULL);
  mape_set_native_function(0, g_ape, "slFFTFilter_create", _gsCProcedureSlFFTFilter_create, NULL);
  mape_set_native_function(0, g_ape, "slFFTFilter_getParamCount", _gsCProcedureSlFFTFilter_getParamCount, NULL);
  mape_set_native_function(0, g_ape, "slFFTFilter_getParamName", _gsCProcedureSlFFTFilter_getParamName, NULL);
  mape_set_native_function(0, g_ape, "slFFTFilter_getParamType", _gsCProcedureSlFFTFilter_getParamType, NULL);
  mape_set_native_function(0, g_ape, "slFFTFilter_getParamMax", _gsCProcedureSlFFTFilter_getParamMax, NULL);
  mape_set_native_function(0, g_ape, "slFFTFilter_getParamMin", _gsCProcedureSlFFTFilter_getParamMin, NULL);
  mape_set_native_function(0, g_ape, "slFlangerFilter_destroy", _gsCProcedureSlFlangerFilter_destroy, NULL);
  mape_set_native_function(0, g_ape, "slFlangerFilter_getParamCount", _gsCProcedureSlFlangerFilter_getParamCount, NULL);
  mape_set_native_function(0, g_ape, "slFlangerFilter_getParamName", _gsCProcedureSlFlangerFilter_getParamName, NULL);
  mape_set_native_function(0, g_ape, "slFlangerFilter_getParamType", _gsCProcedureSlFlangerFilter_getParamType, NULL);
  mape_set_native_function(0, g_ape, "slFlangerFilter_getParamMax", _gsCProcedureSlFlangerFilter_getParamMax, NULL);
  mape_set_native_function(0, g_ape, "slFlangerFilter_getParamMin", _gsCProcedureSlFlangerFilter_getParamMin, NULL);
  mape_set_native_function(0, g_ape, "slFlangerFilter_create", _gsCProcedureSlFlangerFilter_create, NULL);
  mape_set_native_function(0, g_ape, "slFlangerFilter_setParams", _gsCProcedureSlFlangerFilter_setParams, NULL);
  mape_set_native_function(0, g_ape, "slFreeverbFilter_destroy", _gsCProcedureSlFreeverbFilter_destroy, NULL);
  mape_set_native_function(0, g_ape, "slFreeverbFilter_getParamCount", _gsCProcedureSlFreeverbFilter_getParamCount, NULL);
  mape_set_native_function(0, g_ape, "slFreeverbFilter_getParamName", _gsCProcedureSlFreeverbFilter_getParamName, NULL);
  mape_set_native_function(0, g_ape, "slFreeverbFilter_getParamType", _gsCProcedureSlFreeverbFilter_getParamType, NULL);
  mape_set_native_function(0, g_ape, "slFreeverbFilter_getParamMax", _gsCProcedureSlFreeverbFilter_getParamMax, NULL);
  mape_set_native_function(0, g_ape, "slFreeverbFilter_getParamMin", _gsCProcedureSlFreeverbFilter_getParamMin, NULL);
  mape_set_native_function(0, g_ape, "slFreeverbFilter_create", _gsCProcedureSlFreeverbFilter_create, NULL);
  mape_set_native_function(0, g_ape, "slFreeverbFilter_setParams", _gsCProcedureSlFreeverbFilter_setParams, NULL);
  mape_set_native_function(0, g_ape, "slLofiFilter_destroy", _gsCProcedureSlLofiFilter_destroy, NULL);
  mape_set_native_function(0, g_ape, "slLofiFilter_getParamCount", _gsCProcedureSlLofiFilter_getParamCount, NULL);
  mape_set_native_function(0, g_ape, "slLofiFilter_getParamName", _gsCProcedureSlLofiFilter_getParamName, NULL);
  mape_set_native_function(0, g_ape, "slLofiFilter_getParamType", _gsCProcedureSlLofiFilter_getParamType, NULL);
  mape_set_native_function(0, g_ape, "slLofiFilter_getParamMax", _gsCProcedureSlLofiFilter_getParamMax, NULL);
  mape_set_native_function(0, g_ape, "slLofiFilter_getParamMin", _gsCProcedureSlLofiFilter_getParamMin, NULL);
  mape_set_native_function(0, g_ape, "slLofiFilter_create", _gsCProcedureSlLofiFilter_create, NULL);
  mape_set_native_function(0, g_ape, "slLofiFilter_setParams", _gsCProcedureSlLofiFilter_setParams, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_destroy", _gsCProcedureSlMonotone_destroy, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_create", _gsCProcedureSlMonotone_create, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_setParamsEx", _gsCProcedureSlMonotone_setParamsEx, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_load", _gsCProcedureSlMonotone_load, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_loadMemEx", _gsCProcedureSlMonotone_loadMemEx, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_setVolume", _gsCProcedureSlMonotone_setVolume, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_setLooping", _gsCProcedureSlMonotone_setLooping, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_setAutoStop", _gsCProcedureSlMonotone_setAutoStop, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_set3dMinMaxDistance", _gsCProcedureSlMonotone_set3dMinMaxDistance, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_set3dAttenuation", _gsCProcedureSlMonotone_set3dAttenuation, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_set3dDopplerFactor", _gsCProcedureSlMonotone_set3dDopplerFactor, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_set3dListenerRelative", _gsCProcedureSlMonotone_set3dListenerRelative, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_set3dDistanceDelay", _gsCProcedureSlMonotone_set3dDistanceDelay, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_set3dColliderEx", _gsCProcedureSlMonotone_set3dColliderEx, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_set3dAttenuator", _gsCProcedureSlMonotone_set3dAttenuator, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_setInaudibleBehavior", _gsCProcedureSlMonotone_setInaudibleBehavior, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_setLoopPoint", _gsCProcedureSlMonotone_setLoopPoint, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_getLoopPoint", _gsCProcedureSlMonotone_getLoopPoint, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_setFilter", _gsCProcedureSlMonotone_setFilter, NULL);
  mape_set_native_function(0, g_ape, "slMonotone_stop", _gsCProcedureSlMonotone_stop, NULL);
  mape_set_native_function(0, g_ape, "slQueue_destroy", _gsCProcedureSlQueue_destroy, NULL);
  mape_set_native_function(0, g_ape, "slQueue_create", _gsCProcedureSlQueue_create, NULL);
  mape_set_native_function(0, g_ape, "slQueue_play", _gsCProcedureSlQueue_play, NULL);
  mape_set_native_function(0, g_ape, "slQueue_getQueueCount", _gsCProcedureSlQueue_getQueueCount, NULL);
  mape_set_native_function(0, g_ape, "slQueue_isCurrentlyPlaying", _gsCProcedureSlQueue_isCurrentlyPlaying, NULL);
  mape_set_native_function(0, g_ape, "slQueue_setParamsFromAudioSource", _gsCProcedureSlQueue_setParamsFromAudioSource, NULL);
  mape_set_native_function(0, g_ape, "slQueue_setParamsEx", _gsCProcedureSlQueue_setParamsEx, NULL);
  mape_set_native_function(0, g_ape, "slQueue_setVolume", _gsCProcedureSlQueue_setVolume, NULL);
  mape_set_native_function(0, g_ape, "slQueue_setLooping", _gsCProcedureSlQueue_setLooping, NULL);
  mape_set_native_function(0, g_ape, "slQueue_setAutoStop", _gsCProcedureSlQueue_setAutoStop, NULL);
  mape_set_native_function(0, g_ape, "slQueue_set3dMinMaxDistance", _gsCProcedureSlQueue_set3dMinMaxDistance, NULL);
  mape_set_native_function(0, g_ape, "slQueue_set3dAttenuation", _gsCProcedureSlQueue_set3dAttenuation, NULL);
  mape_set_native_function(0, g_ape, "slQueue_set3dDopplerFactor", _gsCProcedureSlQueue_set3dDopplerFactor, NULL);
  mape_set_native_function(0, g_ape, "slQueue_set3dListenerRelative", _gsCProcedureSlQueue_set3dListenerRelative, NULL);
  mape_set_native_function(0, g_ape, "slQueue_set3dDistanceDelay", _gsCProcedureSlQueue_set3dDistanceDelay, NULL);
  mape_set_native_function(0, g_ape, "slQueue_set3dColliderEx", _gsCProcedureSlQueue_set3dColliderEx, NULL);
  mape_set_native_function(0, g_ape, "slQueue_set3dAttenuator", _gsCProcedureSlQueue_set3dAttenuator, NULL);
  mape_set_native_function(0, g_ape, "slQueue_setInaudibleBehavior", _gsCProcedureSlQueue_setInaudibleBehavior, NULL);
  mape_set_native_function(0, g_ape, "slQueue_setLoopPoint", _gsCProcedureSlQueue_setLoopPoint, NULL);
  mape_set_native_function(0, g_ape, "slQueue_getLoopPoint", _gsCProcedureSlQueue_getLoopPoint, NULL);
  mape_set_native_function(0, g_ape, "slQueue_setFilter", _gsCProcedureSlQueue_setFilter, NULL);
  mape_set_native_function(0, g_ape, "slQueue_stop", _gsCProcedureSlQueue_stop, NULL);
  mape_set_native_function(0, g_ape, "slRobotizeFilter_destroy", _gsCProcedureSlRobotizeFilter_destroy, NULL);
  mape_set_native_function(0, g_ape, "slRobotizeFilter_getParamCount", _gsCProcedureSlRobotizeFilter_getParamCount, NULL);
  mape_set_native_function(0, g_ape, "slRobotizeFilter_getParamName", _gsCProcedureSlRobotizeFilter_getParamName, NULL);
  mape_set_native_function(0, g_ape, "slRobotizeFilter_getParamType", _gsCProcedureSlRobotizeFilter_getParamType, NULL);
  mape_set_native_function(0, g_ape, "slRobotizeFilter_getParamMax", _gsCProcedureSlRobotizeFilter_getParamMax, NULL);
  mape_set_native_function(0, g_ape, "slRobotizeFilter_getParamMin", _gsCProcedureSlRobotizeFilter_getParamMin, NULL);
  mape_set_native_function(0, g_ape, "slRobotizeFilter_setParams", _gsCProcedureSlRobotizeFilter_setParams, NULL);
  mape_set_native_function(0, g_ape, "slRobotizeFilter_create", _gsCProcedureSlRobotizeFilter_create, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_destroy", _gsCProcedureSlSfxr_destroy, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_create", _gsCProcedureSlSfxr_create, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_resetParams", _gsCProcedureSlSfxr_resetParams, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_loadParams", _gsCProcedureSlSfxr_loadParams, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_loadParamsMemEx", _gsCProcedureSlSfxr_loadParamsMemEx, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_loadPreset", _gsCProcedureSlSfxr_loadPreset, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_setVolume", _gsCProcedureSlSfxr_setVolume, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_setLooping", _gsCProcedureSlSfxr_setLooping, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_setAutoStop", _gsCProcedureSlSfxr_setAutoStop, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_set3dMinMaxDistance", _gsCProcedureSlSfxr_set3dMinMaxDistance, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_set3dAttenuation", _gsCProcedureSlSfxr_set3dAttenuation, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_set3dDopplerFactor", _gsCProcedureSlSfxr_set3dDopplerFactor, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_set3dListenerRelative", _gsCProcedureSlSfxr_set3dListenerRelative, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_set3dDistanceDelay", _gsCProcedureSlSfxr_set3dDistanceDelay, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_set3dColliderEx", _gsCProcedureSlSfxr_set3dColliderEx, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_set3dAttenuator", _gsCProcedureSlSfxr_set3dAttenuator, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_setInaudibleBehavior", _gsCProcedureSlSfxr_setInaudibleBehavior, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_setLoopPoint", _gsCProcedureSlSfxr_setLoopPoint, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_getLoopPoint", _gsCProcedureSlSfxr_getLoopPoint, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_setFilter", _gsCProcedureSlSfxr_setFilter, NULL);
  mape_set_native_function(0, g_ape, "slSfxr_stop", _gsCProcedureSlSfxr_stop, NULL);
  mape_set_native_function(0, g_ape, "slSpeech_destroy", _gsCProcedureSlSpeech_destroy, NULL);
  mape_set_native_function(0, g_ape, "slSpeech_create", _gsCProcedureSlSpeech_create, NULL);
  mape_set_native_function(0, g_ape, "slSpeech_setText", _gsCProcedureSlSpeech_setText, NULL);
  mape_set_native_function(0, g_ape, "slSpeech_setParamsEx", _gsCProcedureSlSpeech_setParamsEx, NULL);
  mape_set_native_function(0, g_ape, "slSpeech_setVolume", _gsCProcedureSlSpeech_setVolume, NULL);
  mape_set_native_function(0, g_ape, "slSpeech_setLooping", _gsCProcedureSlSpeech_setLooping, NULL);
  mape_set_native_function(0, g_ape, "slSpeech_setAutoStop", _gsCProcedureSlSpeech_setAutoStop, NULL);
  mape_set_native_function(0, g_ape, "slSpeech_set3dMinMaxDistance", _gsCProcedureSlSpeech_set3dMinMaxDistance, NULL);
  mape_set_native_function(0, g_ape, "slSpeech_set3dAttenuation", _gsCProcedureSlSpeech_set3dAttenuation, NULL);
  mape_set_native_function(0, g_ape, "slSpeech_set3dDopplerFactor", _gsCProcedureSlSpeech_set3dDopplerFactor, NULL);
  mape_set_native_function(0, g_ape, "slSpeech_set3dListenerRelative", _gsCProcedureSlSpeech_set3dListenerRelative, NULL);
  mape_set_native_function(0, g_ape, "slSpeech_set3dDistanceDelay", _gsCProcedureSlSpeech_set3dDistanceDelay, NULL);
  mape_set_native_function(0, g_ape, "slSpeech_set3dColliderEx", _gsCProcedureSlSpeech_set3dColliderEx, NULL);
  mape_set_native_function(0, g_ape, "slSpeech_set3dAttenuator", _gsCProcedureSlSpeech_set3dAttenuator, NULL);
  mape_set_native_function(0, g_ape, "slSpeech_setInaudibleBehavior", _gsCProcedureSlSpeech_setInaudibleBehavior, NULL);
  mape_set_native_function(0, g_ape, "slSpeech_setLoopPoint", _gsCProcedureSlSpeech_setLoopPoint, NULL);
  mape_set_native_function(0, g_ape, "slSpeech_getLoopPoint", _gsCProcedureSlSpeech_getLoopPoint, NULL);
  mape_set_native_function(0, g_ape, "slSpeech_setFilter", _gsCProcedureSlSpeech_setFilter, NULL);
  mape_set_native_function(0, g_ape, "slSpeech_stop", _gsCProcedureSlSpeech_stop, NULL);
  mape_set_native_function(0, g_ape, "slWav_destroy", _gsCProcedureSlWav_destroy, NULL);
  mape_set_native_function(0, g_ape, "slWav_create", _gsCProcedureSlWav_create, NULL);
  mape_set_native_function(0, g_ape, "slWav_load", _gsCProcedureSlWav_load, NULL);
  mape_set_native_function(0, g_ape, "slWav_loadMemEx", _gsCProcedureSlWav_loadMemEx, NULL);
  mape_set_native_function(0, g_ape, "slWav_loadRawWave8Ex", _gsCProcedureSlWav_loadRawWave8Ex, NULL);
  mape_set_native_function(0, g_ape, "slWav_loadRawWave16Ex", _gsCProcedureSlWav_loadRawWave16Ex, NULL);
  mape_set_native_function(0, g_ape, "slWav_loadRawWaveEx", _gsCProcedureSlWav_loadRawWaveEx, NULL);
  mape_set_native_function(0, g_ape, "slWav_getLength", _gsCProcedureSlWav_getLength, NULL);
  mape_set_native_function(0, g_ape, "slWav_setVolume", _gsCProcedureSlWav_setVolume, NULL);
  mape_set_native_function(0, g_ape, "slWav_setLooping", _gsCProcedureSlWav_setLooping, NULL);
  mape_set_native_function(0, g_ape, "slWav_setAutoStop", _gsCProcedureSlWav_setAutoStop, NULL);
  mape_set_native_function(0, g_ape, "slWav_set3dMinMaxDistance", _gsCProcedureSlWav_set3dMinMaxDistance, NULL);
  mape_set_native_function(0, g_ape, "slWav_set3dAttenuation", _gsCProcedureSlWav_set3dAttenuation, NULL);
  mape_set_native_function(0, g_ape, "slWav_set3dDopplerFactor", _gsCProcedureSlWav_set3dDopplerFactor, NULL);
  mape_set_native_function(0, g_ape, "slWav_set3dListenerRelative", _gsCProcedureSlWav_set3dListenerRelative, NULL);
  mape_set_native_function(0, g_ape, "slWav_set3dDistanceDelay", _gsCProcedureSlWav_set3dDistanceDelay, NULL);
  mape_set_native_function(0, g_ape, "slWav_set3dColliderEx", _gsCProcedureSlWav_set3dColliderEx, NULL);
  mape_set_native_function(0, g_ape, "slWav_set3dAttenuator", _gsCProcedureSlWav_set3dAttenuator, NULL);
  mape_set_native_function(0, g_ape, "slWav_setInaudibleBehavior", _gsCProcedureSlWav_setInaudibleBehavior, NULL);
  mape_set_native_function(0, g_ape, "slWav_setLoopPoint", _gsCProcedureSlWav_setLoopPoint, NULL);
  mape_set_native_function(0, g_ape, "slWav_getLoopPoint", _gsCProcedureSlWav_getLoopPoint, NULL);
  mape_set_native_function(0, g_ape, "slWav_setFilter", _gsCProcedureSlWav_setFilter, NULL);
  mape_set_native_function(0, g_ape, "slWav_stop", _gsCProcedureSlWav_stop, NULL);
  mape_set_native_function(0, g_ape, "slWaveShaperFilter_destroy", _gsCProcedureSlWaveShaperFilter_destroy, NULL);
  mape_set_native_function(0, g_ape, "slWaveShaperFilter_setParams", _gsCProcedureSlWaveShaperFilter_setParams, NULL);
  mape_set_native_function(0, g_ape, "slWaveShaperFilter_create", _gsCProcedureSlWaveShaperFilter_create, NULL);
  mape_set_native_function(0, g_ape, "slWaveShaperFilter_getParamCount", _gsCProcedureSlWaveShaperFilter_getParamCount, NULL);
  mape_set_native_function(0, g_ape, "slWaveShaperFilter_getParamName", _gsCProcedureSlWaveShaperFilter_getParamName, NULL);
  mape_set_native_function(0, g_ape, "slWaveShaperFilter_getParamType", _gsCProcedureSlWaveShaperFilter_getParamType, NULL);
  mape_set_native_function(0, g_ape, "slWaveShaperFilter_getParamMax", _gsCProcedureSlWaveShaperFilter_getParamMax, NULL);
  mape_set_native_function(0, g_ape, "slWaveShaperFilter_getParamMin", _gsCProcedureSlWaveShaperFilter_getParamMin, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_destroy", _gsCProcedureSlWavStream_destroy, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_create", _gsCProcedureSlWavStream_create, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_load", _gsCProcedureSlWavStream_load, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_loadMemEx", _gsCProcedureSlWavStream_loadMemEx, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_loadToMem", _gsCProcedureSlWavStream_loadToMem, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_getLength", _gsCProcedureSlWavStream_getLength, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_setVolume", _gsCProcedureSlWavStream_setVolume, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_setLooping", _gsCProcedureSlWavStream_setLooping, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_setAutoStop", _gsCProcedureSlWavStream_setAutoStop, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_set3dMinMaxDistance", _gsCProcedureSlWavStream_set3dMinMaxDistance, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_set3dAttenuation", _gsCProcedureSlWavStream_set3dAttenuation, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_set3dDopplerFactor", _gsCProcedureSlWavStream_set3dDopplerFactor, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_set3dListenerRelative", _gsCProcedureSlWavStream_set3dListenerRelative, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_set3dDistanceDelay", _gsCProcedureSlWavStream_set3dDistanceDelay, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_set3dColliderEx", _gsCProcedureSlWavStream_set3dColliderEx, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_set3dAttenuator", _gsCProcedureSlWavStream_set3dAttenuator, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_setInaudibleBehavior", _gsCProcedureSlWavStream_setInaudibleBehavior, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_setLoopPoint", _gsCProcedureSlWavStream_setLoopPoint, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_getLoopPoint", _gsCProcedureSlWavStream_getLoopPoint, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_setFilter", _gsCProcedureSlWavStream_setFilter, NULL);
  mape_set_native_function(0, g_ape, "slWavStream_stop", _gsCProcedureSlWavStream_stop, NULL);
  // Game Script:
  mape_set_native_function(0, g_ape, "printConsole",                             _gsCProcedurePrintConsole,                             NULL);
  //mape_set_native_function(0, g_ape, "printDraw",                                _gsCProcedurePrintDraw,                                NULL);
  mape_set_native_function(0, g_ape, "windowSetTitle",                           _gsCProcedureWindowSetTitle,                           NULL);
  mape_set_native_function(0, g_ape, "windowGetWidth",                           _gsCProcedureWindowGetWidth,                           NULL);
  mape_set_native_function(0, g_ape, "windowGetHeight",                          _gsCProcedureWindowGetHeight,                          NULL);
  //mape_set_native_function(0, g_ape, "windowSetWidthHeight",                     _gsCProcedureWindowSetWidthHeight,                     NULL);
  //mape_set_native_function(0, g_ape, "windowSetFullscreen",                      _gsCProcedureWindowSetFullscreen,                      NULL);
  //mape_set_native_function(0, g_ape, "windowIsFocused",                          _gsCProcedureWindowIsFocused,                          NULL);
  //mape_set_native_function(0, g_ape, "windowIsHovered",                          _gsCProcedureWindowIsHovered,                          NULL);
  //mape_set_native_function(0, g_ape, "windowIsMinimized",                        _gsCProcedureWindowIsMinimized,                        NULL);
  //mape_set_native_function(0, g_ape, "windowIsHidden",                           _gsCProcedureWindowIsHidden,                           NULL);
  //mape_set_native_function(0, g_ape, "windowHide",                               _gsCProcedureWindowHide,                               NULL);
  //mape_set_native_function(0, g_ape, "windowShow",                               _gsCProcedureWindowShow,                               NULL);
  //mape_set_native_function(0, g_ape, "windowRequestAttention",                   _gsCProcedureWindowRequestAttention,                   NULL);
  //mape_set_native_function(0, g_ape, "drawPoint",                                _gsCProcedureDrawPoint,                                NULL);
  //mape_set_native_function(0, g_ape, "drawLine",                                 _gsCProcedureDrawLine,                                 NULL);
  //mape_set_native_function(0, g_ape, "drawTriangle",                             _gsCProcedureDrawTriangle,                             NULL);
  //mape_set_native_function(0, g_ape, "drawTriangleWireframe",                    _gsCProcedureDrawTriangleWireframe,                    NULL);
  //mape_set_native_function(0, g_ape, "drawSphere",                               _gsCProcedureDrawSphere,                               NULL);
  //mape_set_native_function(0, g_ape, "drawSphereWireframe",                      _gsCProcedureDrawSphereWireframe,                      NULL);
  //mape_set_native_function(0, g_ape, "drawDebugText",                            _gsCProcedureDrawDebugText,                            NULL);
  //mape_set_native_function(0, g_ape, "drawDebugTextAtPoint",                     _gsCProcedureDrawDebugTextAtPoint,                     NULL);
  //mape_set_native_function(0, g_ape, "isRerun",                                  _gsCProcedureIsRerun,                                  NULL);
  mape_set_native_function(0, g_ape, "getCurrentFrame",                          _gsCProcedureGetCurrentFrame,                          NULL);
  mape_set_native_function(0, g_ape, "setCurrentFrame",                          _gsCProcedureSetCurrentFrame,                          NULL);
  mape_set_native_function(0, g_ape, "getRandomNumber",                          _gsCProcedureGetRandomNumber,                          NULL);
  //mape_set_native_function(0, g_ape, "getExeDirectoryPath",                      _gsCProcedureGetExeDirectoryPath,                      NULL);
  mape_set_native_function(0, g_ape, "isLinux",                                  _gsCProcedureIsLinux,                                  NULL);
  mape_set_native_function(0, g_ape, "isWindows",                                _gsCProcedureIsWindows,                                NULL);
  //mape_set_native_function(0, g_ape, "isInGameMode",                             _gsCProcedureIsInGameMode,                             NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraDefaultControlDisable",       _gsCProcedureDefaultCameraDefaultControlDisable,       NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraDefaultControlEnable",        _gsCProcedureDefaultCameraDefaultControlEnable,        NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraDefaultControlForceEnable",   _gsCProcedureDefaultCameraDefaultControlForceEnable,   NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraDefaultControlIsEnabled",     _gsCProcedureDefaultCameraDefaultControlIsEnabled,     NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraSetMoveSpeed",                _gsCProcedureDefaultCameraSetMoveSpeed,                NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraSetRollSpeed",                _gsCProcedureDefaultCameraSetRollSpeed,                NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraSetMouseSensitivity",         _gsCProcedureDefaultCameraSetMouseSensitivity,         NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraGetVector",                   _gsCProcedureDefaultCameraGetVector,                   NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraGetVersor",                   _gsCProcedureDefaultCameraGetVersor,                   NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraSetVector",                   _gsCProcedureDefaultCameraSetVector,                   NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraSetVersor",                   _gsCProcedureDefaultCameraSetVersor,                   NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraRotate",                      _gsCProcedureDefaultCameraRotate,                      NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraLookAt",                      _gsCProcedureDefaultCameraLookAt,                      NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraSetFOV",                      _gsCProcedureDefaultCameraSetFOV,                      NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraSetNearClip",                 _gsCProcedureDefaultCameraSetNearClip,                 NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraSetFarClip",                  _gsCProcedureDefaultCameraSetFarClip,                  NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraSetProjectionMode",           _gsCProcedureDefaultCameraSetProjectionMode,           NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraSetAspectRatio",              _gsCProcedureDefaultCameraSetAspectRatio,              NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraSetForceAspectRatio",         _gsCProcedureDefaultCameraSetForceAspectRatio,         NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraSetLensOffset",               _gsCProcedureDefaultCameraSetLensOffset,               NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraSetupPerspective",            _gsCProcedureDefaultCameraSetupPerspective,            NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraSetupOffAxisViewPortal",      _gsCProcedureDefaultCameraSetupOffAxisViewPortal,      NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraSetVFlip",                    _gsCProcedureDefaultCameraSetVFlip,                    NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraScreenToWorld",               _gsCProcedureDefaultCameraScreenToWorld,               NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraWorldToScreen",               _gsCProcedureDefaultCameraWorldToScreen,               NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraGetSideVector",               _gsCProcedureDefaultCameraGetSideVector,               NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraGetUpVector",                 _gsCProcedureDefaultCameraGetUpVector,                 NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraGetLookAtVector",             _gsCProcedureDefaultCameraGetLookAtVector,             NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraGetProjectionMatrix",         _gsCProcedureDefaultCameraGetProjectionMatrix,         NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraGetModelViewMatrix",          _gsCProcedureDefaultCameraGetModelViewMatrix,          NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraGetModelViewProjectionMatrix",_gsCProcedureDefaultCameraGetModelViewProjectionMatrix,NULL);
  //mape_set_native_function(0, g_ape, "defaultCameraSetControlKeys",              _gsCProcedureDefaultCameraSetControlKeys,              NULL);
  //mape_set_native_function(0, g_ape, "setBackgroundColor",                       _gsCProcedureSetBackgroundColor,                       NULL);
  //mape_set_native_function(0, g_ape, "setViewport",                              _gsCProcedureSetViewport,                              NULL);
  //mape_set_native_function(0, g_ape, "alphaBlendingEnable",                      _gsCProcedureAlphaBlendingEnable,                      NULL);
  //mape_set_native_function(0, g_ape, "alphaBlendingDisable",                     _gsCProcedureAlphaBlendingDisable,                     NULL);
  //mape_set_native_function(0, g_ape, "blendModeEnable",                          _gsCProcedureBlendModeEnable,                          NULL);
  //mape_set_native_function(0, g_ape, "blendModeDisable",                         _gsCProcedureBlendModeDisable,                         NULL);
  //mape_set_native_function(0, g_ape, "depthTestEnable",                          _gsCProcedureDepthTestEnable,                          NULL);
  //mape_set_native_function(0, g_ape, "depthTestDisable",                         _gsCProcedureDepthTestDisable,                         NULL);
  //mape_set_native_function(0, g_ape, "cullingEnable",                            _gsCProcedureCullingEnable,                            NULL);
  //mape_set_native_function(0, g_ape, "cullingDisable",                           _gsCProcedureCullingDisable,                           NULL);
  //mape_set_native_function(0, g_ape, "clear",                                    _gsCProcedureClear,                                    NULL);
  //mape_set_native_function(0, g_ape, "clearAlpha",                               _gsCProcedureClearAlpha,                               NULL);
  //mape_set_native_function(0, g_ape, "clearDepth",                               _gsCProcedureClearDepth,                               NULL);
  //mape_set_native_function(0, g_ape, "saveScreenRawToMemory",                    _gsCProcedureSaveScreenRawToMemory,                    NULL);
  mape_set_native_function(0, g_ape, "globalArrayNew8Bit",                       _gsCProcedureGlobalArrayNew8Bit,                       NULL);
  mape_set_native_function(0, g_ape, "globalArrayPersistentNew8Bit",             _gsCProcedureGlobalArrayPersistentNew8Bit,             NULL);
  mape_set_native_function(0, g_ape, "globalArrayDelete",                        _gsCProcedureGlobalArrayDelete,                        NULL);
  mape_set_native_function(0, g_ape, "globalArrayPersistentDelete",              _gsCProcedureGlobalArrayPersistentDelete,              NULL);
  mape_set_native_function(0, g_ape, "globalArrayDeleteAll",                     _gsCProcedureGlobalArrayDeleteAll,                     NULL);
  mape_set_native_function(0, g_ape, "globalArrayPersistentDeleteAll",           _gsCProcedureGlobalArrayPersistentDeleteAll,           NULL);
  mape_set_native_function(0, g_ape, "globalArrayGetBytesCount",                 _gsCProcedureGlobalArrayGetBytesCount,                 NULL);
  mape_set_native_function(0, g_ape, "globalArrayGetPointer",                    _gsCProcedureGlobalArrayGetPointer,                    NULL);
  mape_set_native_function(0, g_ape, "globalArrayPersistentGetBytesCount",       _gsCProcedureGlobalArrayPersistentGetBytesCount,       NULL);
  mape_set_native_function(0, g_ape, "globalArrayPersistentGetPointer",          _gsCProcedureGlobalArrayPersistentGetPointer,          NULL);
  //mape_set_native_function(0, g_ape, "globalSharedArrayPersistentNew8Bit",       _gsCProcedureGlobalSharedArrayPersistentNew8Bit,       NULL);
  //mape_set_native_function(0, g_ape, "globalSharedArrayPersistentGetBytesCount", _gsCProcedureGlobalSharedArrayPersistentGetBytesCount, NULL);
  //mape_set_native_function(0, g_ape, "globalSharedArrayPersistentGetPointer",    _gsCProcedureGlobalSharedArrayPersistentGetPointer,    NULL);
  mape_set_native_function(0, g_ape, "pointerGetBool",                           _gsCProcedurePointerGetBool,                           NULL);
  mape_set_native_function(0, g_ape, "pointerGetString",                         _gsCProcedurePointerGetString,                         NULL);
  mape_set_native_function(0, g_ape, "pointerGetSubstring",                      _gsCProcedurePointerGetSubstring,                      NULL);
  mape_set_native_function(0, g_ape, "pointerGetNumber",                         _gsCProcedurePointerGetNumber,                         NULL);
  mape_set_native_function(0, g_ape, "pointerGetInteger",                        _gsCProcedurePointerGetInteger,                        NULL);
  mape_set_native_function(0, g_ape, "pointerGetUnsignedInteger",                _gsCProcedurePointerGetUnsignedInteger,                NULL);
  mape_set_native_function(0, g_ape, "pointerGetInteger8Bit",                    _gsCProcedurePointerGetInteger8Bit,                    NULL);
  mape_set_native_function(0, g_ape, "pointerGetUnsignedInteger8Bit",            _gsCProcedurePointerGetUnsignedInteger8Bit,            NULL);
  mape_set_native_function(0, g_ape, "pointerGetAtOffsetNumber",                 _gsCProcedurePointerGetAtOffsetNumber,                 NULL);
  mape_set_native_function(0, g_ape, "pointerGetAtOffsetInteger",                _gsCProcedurePointerGetAtOffsetInteger,                NULL);
  mape_set_native_function(0, g_ape, "pointerGetAtOffsetUnsignedInteger",        _gsCProcedurePointerGetAtOffsetUnsignedInteger,        NULL);
  mape_set_native_function(0, g_ape, "pointerGetAtOffsetInteger16Bit",           _gsCProcedurePointerGetAtOffsetInteger16Bit,           NULL);
  mape_set_native_function(0, g_ape, "pointerGetAtOffsetUnsignedInteger16Bit",   _gsCProcedurePointerGetAtOffsetUnsignedInteger16Bit,   NULL);
  mape_set_native_function(0, g_ape, "pointerGetAtOffsetNumber64Bit",            _gsCProcedurePointerGetAtOffsetNumber64Bit,            NULL);
  mape_set_native_function(0, g_ape, "pointerGetAtOffsetInteger64Bit",           _gsCProcedurePointerGetAtOffsetInteger64Bit,           NULL);
  mape_set_native_function(0, g_ape, "pointerGetAtOffsetUnsignedInteger64Bit",   _gsCProcedurePointerGetAtOffsetUnsignedInteger64Bit,   NULL);
  mape_set_native_function(0, g_ape, "pointerSetBool",                           _gsCProcedurePointerSetBool,                           NULL);
  mape_set_native_function(0, g_ape, "pointerSetString",                         _gsCProcedurePointerSetString,                         NULL);
  mape_set_native_function(0, g_ape, "pointerSetStringExcludingNullChar",        _gsCProcedurePointerSetStringExcludingNullChar,        NULL);
  mape_set_native_function(0, g_ape, "pointerSetSubstring",                      _gsCProcedurePointerSetSubstring,                      NULL);
  mape_set_native_function(0, g_ape, "pointerSetNumber",                         _gsCProcedurePointerSetNumber,                         NULL);
  mape_set_native_function(0, g_ape, "pointerSetInteger",                        _gsCProcedurePointerSetInteger,                        NULL);
  mape_set_native_function(0, g_ape, "pointerSetUnsignedInteger",                _gsCProcedurePointerSetUnsignedInteger,                NULL);
  mape_set_native_function(0, g_ape, "pointerSetInteger8Bit",                    _gsCProcedurePointerSetInteger8Bit,                    NULL);
  mape_set_native_function(0, g_ape, "pointerSetUnsignedInteger8Bit",            _gsCProcedurePointerSetUnsignedInteger8Bit,            NULL);
  mape_set_native_function(0, g_ape, "pointerSetAtOffsetNumber",                 _gsCProcedurePointerSetAtOffsetNumber,                 NULL);
  mape_set_native_function(0, g_ape, "pointerSetAtOffsetInteger",                _gsCProcedurePointerSetAtOffsetInteger,                NULL);
  mape_set_native_function(0, g_ape, "pointerSetAtOffsetUnsignedInteger",        _gsCProcedurePointerSetAtOffsetUnsignedInteger,        NULL);
  mape_set_native_function(0, g_ape, "pointerSetAtOffsetInteger16Bit",           _gsCProcedurePointerSetAtOffsetInteger16Bit,           NULL);
  mape_set_native_function(0, g_ape, "pointerSetAtOffsetUnsignedInteger16Bit",   _gsCProcedurePointerSetAtOffsetUnsignedInteger16Bit,   NULL);
  mape_set_native_function(0, g_ape, "pointerSetAtOffsetNumber64Bit",            _gsCProcedurePointerSetAtOffsetNumber64Bit,            NULL);
  mape_set_native_function(0, g_ape, "pointerSetAtOffsetInteger64Bit",           _gsCProcedurePointerSetAtOffsetInteger64Bit,           NULL);
  mape_set_native_function(0, g_ape, "pointerSetAtOffsetUnsignedInteger64Bit",   _gsCProcedurePointerSetAtOffsetUnsignedInteger64Bit,   NULL);
  mape_set_native_function(0, g_ape, "pointerGetRaw8Bit",                        _gsCProcedurePointerGetRaw8Bit,                        NULL);
  mape_set_native_function(0, g_ape, "pointerGetRaw16Bit",                       _gsCProcedurePointerGetRaw16Bit,                       NULL);
  mape_set_native_function(0, g_ape, "pointerGetRaw32Bit",                       _gsCProcedurePointerGetRaw32Bit,                       NULL);
  mape_set_native_function(0, g_ape, "pointerGetRaw64Bit",                       _gsCProcedurePointerGetRaw64Bit,                       NULL);
  mape_set_native_function(0, g_ape, "pointerSetRaw8Bit",                        _gsCProcedurePointerSetRaw8Bit,                        NULL);
  mape_set_native_function(0, g_ape, "pointerSetRaw16Bit",                       _gsCProcedurePointerSetRaw16Bit,                       NULL);
  mape_set_native_function(0, g_ape, "pointerSetRaw32Bit",                       _gsCProcedurePointerSetRaw32Bit,                       NULL);
  mape_set_native_function(0, g_ape, "pointerSetRaw64Bit",                       _gsCProcedurePointerSetRaw64Bit,                       NULL);
  mape_set_native_function(0, g_ape, "pointerIsNull",                            _gsCProcedurePointerIsNull,                            NULL);
  mape_set_native_function(0, g_ape, "pointerGetNull",                           _gsCProcedurePointerGetNull,                           NULL);
  mape_set_native_function(0, g_ape, "pointersAreEqual",                         _gsCProcedurePointersAreEqual,                         NULL);
  mape_set_native_function(0, g_ape, "pointerOffsetByBytes",                     _gsCProcedurePointerOffsetByBytes,                     NULL);
  //mape_set_native_function(0, g_ape, "pointerDrawPixels",                        _gsCProcedurePointerDrawPixels,                        NULL);
  mape_set_native_function(0, g_ape, "globalDynamicArrayNew",                    _gsCProcedureGlobalDynamicArrayNew,                    NULL);
  mape_set_native_function(0, g_ape, "globalDynamicArrayPersistentNew",          _gsCProcedureGlobalDynamicArrayPersistentNew,          NULL);
  mape_set_native_function(0, g_ape, "globalDynamicArrayDelete",                 _gsCProcedureGlobalDynamicArrayDelete,                 NULL);
  mape_set_native_function(0, g_ape, "globalDynamicArrayPersistentDelete",       _gsCProcedureGlobalDynamicArrayPersistentDelete,       NULL);
  mape_set_native_function(0, g_ape, "globalDynamicArrayDeleteAll",              _gsCProcedureGlobalDynamicArrayDeleteAll,              NULL);
  mape_set_native_function(0, g_ape, "globalDynamicArrayPersistentDeleteAll",    _gsCProcedureGlobalDynamicArrayPersistentDeleteAll,    NULL);
  mape_set_native_function(0, g_ape, "globalDynamicArrayGetHandle",              _gsCProcedureGlobalDynamicArrayGetHandle,              NULL);
  mape_set_native_function(0, g_ape, "globalDynamicArrayPersistentGetHandle",    _gsCProcedureGlobalDynamicArrayPersistentGetHandle,    NULL);
  mape_set_native_function(0, g_ape, "dynamicArrayGet",                          _gsCProcedureDynamicArrayGet,                          NULL);
  mape_set_native_function(0, g_ape, "dynamicArraySet",                          _gsCProcedureDynamicArraySet,                          NULL);
  mape_set_native_function(0, g_ape, "dynamicArrayAppend",                       _gsCProcedureDynamicArrayAppend,                       NULL);
  mape_set_native_function(0, g_ape, "dynamicArrayRemoveAt",                     _gsCProcedureDynamicArrayRemoveAt,                     NULL);
  mape_set_native_function(0, g_ape, "dynamicArrayRemoveLast",                   _gsCProcedureDynamicArrayRemoveLast,                   NULL);
  mape_set_native_function(0, g_ape, "dynamicArrayGetSize",                      _gsCProcedureDynamicArrayGetSize,                      NULL);
  mape_set_native_function(0, g_ape, "memset",                                   _gsCProcedureMemset,                                   NULL);
  mape_set_native_function(0, g_ape, "memcpy",                                   _gsCProcedureMemcpy,                                   NULL);
  mape_set_native_function(0, g_ape, "memcmp",                                   _gsCProcedureMemcmp,                                   NULL);
  //mape_set_native_function(0, g_ape, "threadSafeMemset",                         _gsCProcedureThreadSafeMemset,                         NULL);
  //mape_set_native_function(0, g_ape, "threadSafeMemcpy",                         _gsCProcedureThreadSafeMemcpy,                         NULL);
  //mape_set_native_function(0, g_ape, "threadSafeMemcmp",                         _gsCProcedureThreadSafeMemcmp,                         NULL);
  //mape_set_native_function(0, g_ape, "threadWaitForEqualUint64Value",            _gsCProcedureThreadWaitForEqualUint64Value,            NULL);
  //mape_set_native_function(0, g_ape, "threadWaitForEqualOrMoreThanUint64Value",  _gsCProcedureThreadWaitForEqualOrMoreThanUint64Value,  NULL);
  //mape_set_native_function(0, g_ape, "threadWaitForThread2FrameToFinish",        _gsCProcedureThreadWaitForThread2FrameToFinish,        NULL);
  mape_set_native_function(0, g_ape, "strlenWithNullChar",                       _gsCProcedureStrlenWithNullChar,                       NULL);
  //mape_set_native_function(0, g_ape, "keyboardGetGlfwKeyEvent",                  _gsCProcedureKeyboardGetGlfwKeyEvent,                  NULL);
  //mape_set_native_function(0, g_ape, "keyboardGetGlfwKeyModifiers",              _gsCProcedureKeyboardGetGlfwKeyModifiers,              NULL);
  //mape_set_native_function(0, g_ape, "keyboardGetGlfwCodepointString",           _gsCProcedureKeyboardGetGlfwCodepointString,           NULL);
  //mape_set_native_function(0, g_ape, "mouseGlfwSetInputMode",                    _gsCProcedureMouseGlfwSetInputMode,                    NULL);
  //mape_set_native_function(0, g_ape, "mouseSetXY",                               _gsCProcedureMouseSetXY,                               NULL);
  //mape_set_native_function(0, g_ape, "mouseGetX",                                _gsCProcedureMouseGetX,                                NULL);
  //mape_set_native_function(0, g_ape, "mouseGetY",                                _gsCProcedureMouseGetY,                                NULL);
  //mape_set_native_function(0, g_ape, "mouseGetPreviousX",                        _gsCProcedureMouseGetPreviousX,                        NULL);
  //mape_set_native_function(0, g_ape, "mouseGetPreviousY",                        _gsCProcedureMouseGetPreviousY,                        NULL);
  //mape_set_native_function(0, g_ape, "mouseGetMoveEvent",                        _gsCProcedureMouseGetMoveEvent,                        NULL);
  //mape_set_native_function(0, g_ape, "mouseGetButtonIsPressed",                  _gsCProcedureMouseGetButtonIsPressed,                  NULL);
  //mape_set_native_function(0, g_ape, "mouseGetButtonIsPressedAndHeld",           _gsCProcedureMouseGetButtonIsPressedAndHeld,           NULL);
  //mape_set_native_function(0, g_ape, "mouseGetButtonIsReleased",                 _gsCProcedureMouseGetButtonIsReleased,                 NULL);
  //mape_set_native_function(0, g_ape, "mouseGetWheelScroll",                      _gsCProcedureMouseGetWheelScroll,                      NULL);
  mape_set_native_function(0, g_ape, "gamepadIsPresent",                         _gsCProcedureGamepadIsPresent,                         NULL);
  mape_set_native_function(0, g_ape, "gamepadGet15Buttons6AxesNumbers",          _gsCProcedureGamepadGet15Buttons6AxesNumbers,          NULL);
  //mape_set_native_function(0, g_ape, "gamepadGetName",                           _gsCProcedureGamepadGetName,                           NULL);
  //mape_set_native_function(0, g_ape, "gamepadGetGUID",                           _gsCProcedureGamepadGetGUID,                           NULL);
  mape_set_native_function(0, g_ape, "gamepadUpdateGamecontrollerdbTxt",         _gsCProcedureGamepadUpdateGamecontrollerdbTxt,         NULL);
  mape_set_native_function(0, g_ape, "boolToNumber",                             _gsCProcedureBoolToNumber,                             NULL);
  mape_set_native_function(0, g_ape, "boolToString",                             _gsCProcedureBoolToString,                             NULL);
  mape_set_native_function(0, g_ape, "numberFromRaw8BitInteger",                 _gsCProcedureNumberFromRaw8BitInteger,                NULL);
  mape_set_native_function(0, g_ape, "numberFromRaw8BitUnsignedInteger",         _gsCProcedureNumberFromRaw8BitUnsignedInteger,        NULL);
  mape_set_native_function(0, g_ape, "numberFromRaw16BitInteger",                _gsCProcedureNumberFromRaw16BitInteger,                NULL);
  mape_set_native_function(0, g_ape, "numberFromRaw16BitUnsignedInteger",        _gsCProcedureNumberFromRaw16BitUnsignedInteger,        NULL);
  mape_set_native_function(0, g_ape, "numberFromRaw32BitInteger",                _gsCProcedureNumberFromRaw32BitInteger,                NULL);
  mape_set_native_function(0, g_ape, "numberFromRaw32BitUnsignedInteger",        _gsCProcedureNumberFromRaw32BitUnsignedInteger,        NULL);
  mape_set_native_function(0, g_ape, "numberFromRaw32BitFloat",                  _gsCProcedureNumberFromRaw32BitFloat,                  NULL);
  mape_set_native_function(0, g_ape, "numberFromRaw64BitInteger",                _gsCProcedureNumberFromRaw64BitInteger,                NULL);
  mape_set_native_function(0, g_ape, "numberFromRaw64BitUnsignedInteger",        _gsCProcedureNumberFromRaw64BitUnsignedInteger,        NULL);
  mape_set_native_function(0, g_ape, "numberToBool",                             _gsCProcedureNumberToBool,                             NULL);
  mape_set_native_function(0, g_ape, "numberToString",                           _gsCProcedureNumberToString,                           NULL);
  mape_set_native_function(0, g_ape, "numberToBinaryString",                     _gsCProcedureNumberToBinaryString,                     NULL);
  mape_set_native_function(0, g_ape, "numberWholePartToString",                  _gsCProcedureNumberWholePartToString,                  NULL);
  mape_set_native_function(0, g_ape, "stringCharToNumber",                       _gsCProcedureStringCharToNumber,                       NULL);
  mape_set_native_function(0, g_ape, "stringToNumberArray",                      _gsCProcedureStringToNumberArray,                      NULL);
  mape_set_native_function(0, g_ape, "interpretStringToInteger",                 _gsCProcedureInterpretStringToInteger,                 NULL);
  mape_set_native_function(0, g_ape, "interpretStringToFloat",                   _gsCProcedureInterpretStringToFloat,                   NULL);
  mape_set_native_function(0, g_ape, "interpretStringToDouble",                  _gsCProcedureInterpretStringToDouble,                  NULL);
  mape_set_native_function(0, g_ape, "stringReadFromFile",                       _gsCProcedureStringReadFromFile,                       NULL);
  mape_set_native_function(0, g_ape, "stringWriteToFile",                        _gsCProcedureStringWriteToFile,                        NULL);
  mape_set_native_function(0, g_ape, "stringAppendToFile",                       _gsCProcedureStringAppendToFile,                       NULL);
  mape_set_native_function(0, g_ape, "binaryGetByteSizeOfFile",                  _gsCProcedureBinaryGetByteSizeOfFile,                  NULL);
  mape_set_native_function(0, g_ape, "binaryReadFromFile",                       _gsCProcedureBinaryReadFromFile,                       NULL);
  mape_set_native_function(0, g_ape, "binaryWriteToFile",                        _gsCProcedureBinaryWriteToFile,                        NULL);
  //mape_set_native_function(0, g_ape, "getClipboardString",                       _gsCProcedureGetClipboardString,                       NULL);
  //mape_set_native_function(0, g_ape, "setClipboardString",                       _gsCProcedureSetClipboardString,                       NULL);
  //mape_set_native_function(0, g_ape, "gizmoSetMode",                             _gsCProcedureGizmoSetMode,                             NULL);
  //mape_set_native_function(0, g_ape, "gizmoGetVector",                           _gsCProcedureGizmoGetVector,                           NULL);
  //mape_set_native_function(0, g_ape, "gizmoGetVersor",                           _gsCProcedureGizmoGetVersor,                           NULL);
  //mape_set_native_function(0, g_ape, "gizmoGetScale",                            _gsCProcedureGizmoGetScale,                            NULL);
  //mape_set_native_function(0, g_ape, "gizmoSetVector",                           _gsCProcedureGizmoSetVector,                           NULL);
  //mape_set_native_function(0, g_ape, "gizmoSetVersor",                           _gsCProcedureGizmoSetVersor,                           NULL);
  //mape_set_native_function(0, g_ape, "gizmoSetScale",                            _gsCProcedureGizmoSetScale,                            NULL);
  //mape_set_native_function(0, g_ape, "gizmoSetDrawScale",                        _gsCProcedureGizmoSetDrawScale,                        NULL);
  //mape_set_native_function(0, g_ape, "gizmoSetDrawColors",                       _gsCProcedureGizmoSetDrawColors,                       NULL);
  //mape_set_native_function(0, g_ape, "gizmoDelete",                              _gsCProcedureGizmoDelete,                              NULL);
  //mape_set_native_function(0, g_ape, "gizmoDeleteAll",                           _gsCProcedureGizmoDeleteAll,                           NULL);
  //mape_set_native_function(0, g_ape, "getLastFrameTime",                         _gsCProcedureGetLastFrameTime,                         NULL);
  //mape_set_native_function(0, g_ape, "getSystemTimeMillis",                      _gsCProcedureGetSystemTimeMillis,                      NULL);
  //mape_set_native_function(0, g_ape, "getSystemTimeMicros",                      _gsCProcedureGetSystemTimeMicros,                      NULL);
  //mape_set_native_function(0, g_ape, "getUnixTime",                              _gsCProcedureGetUnixTime,                              NULL);
  //mape_set_native_function(0, g_ape, "framebufferBegin",                         _gsCProcedureFramebufferBegin,                         NULL);
  //mape_set_native_function(0, g_ape, "framebufferEnd",                           _gsCProcedureFramebufferEnd,                           NULL);
  //mape_set_native_function(0, g_ape, "framebufferDraw",                          _gsCProcedureFramebufferDraw,                          NULL);
  //mape_set_native_function(0, g_ape, "framebufferClear",                         _gsCProcedureFramebufferClear,                         NULL);
  //mape_set_native_function(0, g_ape, "framebufferCopyToImage",                   _gsCProcedureFramebufferCopyToImage,                   NULL);
  //mape_set_native_function(0, g_ape, "framebufferDelete",                        _gsCProcedureFramebufferDelete,                        NULL);
  //mape_set_native_function(0, g_ape, "framebufferDeleteAll",                     _gsCProcedureFramebufferDeleteAll,                     NULL);
  //mape_set_native_function(0, g_ape, "meshNew",                                  _gsCProcedureMeshNew,                                  NULL);
  //mape_set_native_function(0, g_ape, "meshPersistentNew",                        _gsCProcedureMeshPersistentNew,                        NULL);
  //mape_set_native_function(0, g_ape, "meshDelete",                               _gsCProcedureMeshDelete,                               NULL);
  //mape_set_native_function(0, g_ape, "meshPersistentDelete",                     _gsCProcedureMeshPersistentDelete,                     NULL);
  //mape_set_native_function(0, g_ape, "meshDeleteAll",                            _gsCProcedureMeshDeleteAll,                            NULL);
  //mape_set_native_function(0, g_ape, "meshPersistentDeleteAll",                  _gsCProcedureMeshPersistentDeleteAll,                  NULL);
  //mape_set_native_function(0, g_ape, "meshGetHandle",                            _gsCProcedureMeshGetHandle,                            NULL);
  //mape_set_native_function(0, g_ape, "meshPersistentGetHandle",                  _gsCProcedureMeshPersistentGetHandle,                  NULL);
  //mape_set_native_function(0, g_ape, "meshIsUsingColors",                        _gsCProcedureMeshIsUsingColors,                        NULL);
  //mape_set_native_function(0, g_ape, "meshIsUsingTextures",                      _gsCProcedureMeshIsUsingTextures,                      NULL);
  //mape_set_native_function(0, g_ape, "meshIsUsingIndices",                       _gsCProcedureMeshIsUsingIndices,                       NULL);
  //mape_set_native_function(0, g_ape, "meshEnableColors",                         _gsCProcedureMeshEnableColors,                         NULL);
  //mape_set_native_function(0, g_ape, "meshEnableTextures",                       _gsCProcedureMeshEnableTextures,                       NULL);
  //mape_set_native_function(0, g_ape, "meshEnableIndices",                        _gsCProcedureMeshEnableIndices,                        NULL);
  //mape_set_native_function(0, g_ape, "meshDisableColors",                        _gsCProcedureMeshDisableColors,                        NULL);
  //mape_set_native_function(0, g_ape, "meshDisableTextures",                      _gsCProcedureMeshDisableTextures,                      NULL);
  //mape_set_native_function(0, g_ape, "meshDisableIndices",                       _gsCProcedureMeshDisableIndices,                       NULL);
  //mape_set_native_function(0, g_ape, "meshHasVertices",                          _gsCProcedureMeshHasVertices,                          NULL);
  //mape_set_native_function(0, g_ape, "meshHasColors",                            _gsCProcedureMeshHasColors,                            NULL);
  //mape_set_native_function(0, g_ape, "meshHasTexCoords",                         _gsCProcedureMeshHasTexCoords,                         NULL);
  //mape_set_native_function(0, g_ape, "meshHasIndices",                           _gsCProcedureMeshHasIndices,                           NULL);
  //mape_set_native_function(0, g_ape, "meshGetVerticesCount",                     _gsCProcedureMeshGetVerticesCount,                     NULL);
  //mape_set_native_function(0, g_ape, "meshGetColorsCount",                       _gsCProcedureMeshGetColorsCount,                       NULL);
  //mape_set_native_function(0, g_ape, "meshGetTexCoordsCount",                    _gsCProcedureMeshGetTexCoordsCount,                    NULL);
  //mape_set_native_function(0, g_ape, "meshGetIndicesCount",                      _gsCProcedureMeshGetIndicesCount,                      NULL);
  //mape_set_native_function(0, g_ape, "meshHaveVerticesChanged",                  _gsCProcedureMeshHaveVerticesChanged,                  NULL);
  //mape_set_native_function(0, g_ape, "meshHaveColorsChanged",                    _gsCProcedureMeshHaveColorsChanged,                    NULL);
  //mape_set_native_function(0, g_ape, "meshHaveTexCoordsChanged",                 _gsCProcedureMeshHaveTexCoordsChanged,                 NULL);
  //mape_set_native_function(0, g_ape, "meshHaveIndicesChanged",                   _gsCProcedureMeshHaveIndicesChanged,                   NULL);
  //mape_set_native_function(0, g_ape, "meshAddVertex",                            _gsCProcedureMeshAddVertex,                            NULL);
  //mape_set_native_function(0, g_ape, "meshAddColor",                             _gsCProcedureMeshAddColor,                             NULL);
  //mape_set_native_function(0, g_ape, "meshAddTexCoord",                          _gsCProcedureMeshAddTexCoord,                          NULL);
  //mape_set_native_function(0, g_ape, "meshAddIndex",                             _gsCProcedureMeshAddIndex,                             NULL);
  //mape_set_native_function(0, g_ape, "meshRemoveVertex",                         _gsCProcedureMeshRemoveVertex,                         NULL);
  //mape_set_native_function(0, g_ape, "meshRemoveColor",                          _gsCProcedureMeshRemoveColor,                          NULL);
  //mape_set_native_function(0, g_ape, "meshRemoveTexCoord",                       _gsCProcedureMeshRemoveTexCoord,                       NULL);
  //mape_set_native_function(0, g_ape, "meshRemoveIndex",                          _gsCProcedureMeshRemoveIndex,                          NULL);
  //mape_set_native_function(0, g_ape, "meshClear",                                _gsCProcedureMeshClear,                                NULL);
  //mape_set_native_function(0, g_ape, "meshClearVertices",                        _gsCProcedureMeshClearVertices,                        NULL);
  //mape_set_native_function(0, g_ape, "meshClearColors",                          _gsCProcedureMeshClearColors,                          NULL);
  //mape_set_native_function(0, g_ape, "meshClearTexCoords",                       _gsCProcedureMeshClearTexCoords,                       NULL);
  //mape_set_native_function(0, g_ape, "meshClearIndices",                         _gsCProcedureMeshClearIndices,                         NULL);
  //mape_set_native_function(0, g_ape, "meshGetVerticesPointer",                   _gsCProcedureMeshGetVerticesPointer,                   NULL);
  //mape_set_native_function(0, g_ape, "meshGetColorsPointer",                     _gsCProcedureMeshGetColorsPointer,                     NULL);
  //mape_set_native_function(0, g_ape, "meshGetTexCoordsPointer",                  _gsCProcedureMeshGetTexCoordsPointer,                  NULL);
  //mape_set_native_function(0, g_ape, "meshGetIndicesPointer",                    _gsCProcedureMeshGetIndicesPointer,                    NULL);
  //mape_set_native_function(0, g_ape, "meshMergeDuplicateVertices",               _gsCProcedureMeshMergeDuplicateVertices,               NULL);
  //mape_set_native_function(0, g_ape, "meshSetupIndicesAuto",                     _gsCProcedureMeshSetupIndicesAuto,                     NULL);
  //mape_set_native_function(0, g_ape, "meshAddTriangle",                          _gsCProcedureMeshAddTriangle,                          NULL);
  //mape_set_native_function(0, g_ape, "meshDraw",                                 _gsCProcedureMeshDraw,                                 NULL);
  //mape_set_native_function(0, g_ape, "meshDrawWithColor",                        _gsCProcedureMeshDrawWithColor,                        NULL);
  //mape_set_native_function(0, g_ape, "meshDrawDebugVertices",                    _gsCProcedureMeshDrawDebugVertices,                    NULL);
  //mape_set_native_function(0, g_ape, "meshDrawDebugColors",                      _gsCProcedureMeshDrawDebugColors,                      NULL);
  //mape_set_native_function(0, g_ape, "meshDrawDebugTexCoords",                   _gsCProcedureMeshDrawDebugTexCoords,                   NULL);
  //mape_set_native_function(0, g_ape, "meshDrawDebugIndices",                     _gsCProcedureMeshDrawDebugIndices,                     NULL);
  //mape_set_native_function(0, g_ape, "meshDrawDebugRayTraceIndices",             _gsCProcedureMeshDrawDebugRayTraceIndices,             NULL);
  //mape_set_native_function(0, g_ape, "meshImporterGetMeshesCount",               _gsCProcedureMeshImporterGetMeshesCount,               NULL);
  //mape_set_native_function(0, g_ape, "meshImporterGetMeshName",                  _gsCProcedureMeshImporterGetMeshName,                  NULL);
  //mape_set_native_function(0, g_ape, "meshImporterGetMesh",                      _gsCProcedureMeshImporterGetMesh,                      NULL);
  //mape_set_native_function(0, g_ape, "meshImporterDelete",                       _gsCProcedureMeshImporterDelete,                       NULL);
  //mape_set_native_function(0, g_ape, "meshImporterDeleteAll",                    _gsCProcedureMeshImporterDeleteAll,                    NULL);
  //mape_set_native_function(0, g_ape, "imageNew",                                 _gsCProcedureImageNew,                                 NULL);
  //mape_set_native_function(0, g_ape, "imagePersistentNew",                       _gsCProcedureImagePersistentNew,                       NULL);
  //mape_set_native_function(0, g_ape, "imageNewFromFile",                         _gsCProcedureImageNewFromFile,                         NULL);
  //mape_set_native_function(0, g_ape, "imagePersistentNewFromFile",               _gsCProcedureImagePersistentNewFromFile,               NULL);
  //mape_set_native_function(0, g_ape, "imageDelete",                              _gsCProcedureImageDelete,                              NULL);
  //mape_set_native_function(0, g_ape, "imagePersistentDelete",                    _gsCProcedureImagePersistentDelete,                    NULL);
  //mape_set_native_function(0, g_ape, "imageDeleteAll",                           _gsCProcedureImageDeleteAll,                           NULL);
  //mape_set_native_function(0, g_ape, "imagePersistentDeleteAll",                 _gsCProcedureImagePersistentDeleteAll,                 NULL);
  //mape_set_native_function(0, g_ape, "imageGetHandle",                           _gsCProcedureImageGetHandle,                           NULL);
  //mape_set_native_function(0, g_ape, "imagePersistentGetHandle",                 _gsCProcedureImagePersistentGetHandle,                 NULL);
  //mape_set_native_function(0, g_ape, "imageLoadFromMemory",                      _gsCProcedureImageLoadFromMemory,                      NULL);
  //mape_set_native_function(0, g_ape, "imageClear",                               _gsCProcedureImageClear,                               NULL);
  //mape_set_native_function(0, g_ape, "imageHasMipmap",                           _gsCProcedureImageHasMipmap,                           NULL);
  //mape_set_native_function(0, g_ape, "imageMipmapDisable",                       _gsCProcedureImageMipmapDisable,                       NULL);
  //mape_set_native_function(0, g_ape, "imageMipmapEnable",                        _gsCProcedureImageMipmapEnable,                        NULL);
  //mape_set_native_function(0, g_ape, "imageMipmapGenerate",                      _gsCProcedureImageMipmapGenerate,                      NULL);
  //mape_set_native_function(0, g_ape, "imageSetTextureMinMagFilter",              _gsCProcedureImageSetTextureMinMagFilter,              NULL);
  //mape_set_native_function(0, g_ape, "imageSetTextureWrap",                      _gsCProcedureImageSetTextureWrap,                      NULL);
  //mape_set_native_function(0, g_ape, "imageSetTextureMaxAnisotropy",             _gsCProcedureImageSetTextureMaxAnisotropy,             NULL);
  //mape_set_native_function(0, g_ape, "imageGetWidth",                            _gsCProcedureImageGetWidth,                            NULL);
  //mape_set_native_function(0, g_ape, "imageGetHeight",                           _gsCProcedureImageGetHeight,                           NULL);
  //mape_set_native_function(0, g_ape, "imageGetBitsPerPixel",                     _gsCProcedureImageGetBitsPerPixel,                     NULL);
  //mape_set_native_function(0, g_ape, "imageGetImageType",                        _gsCProcedureImageGetImageType,                        NULL);
  //mape_set_native_function(0, g_ape, "imageGetPixelsPointer",                    _gsCProcedureImageGetPixelsPointer,                    NULL);
  //mape_set_native_function(0, g_ape, "imageGetColor",                            _gsCProcedureImageGetColor,                            NULL);
  //mape_set_native_function(0, g_ape, "imageSetColor",                            _gsCProcedureImageSetColor,                            NULL);
  //mape_set_native_function(0, g_ape, "imageGammaCorrect",                        _gsCProcedureImageGammaCorrect,                        NULL);
  //mape_set_native_function(0, g_ape, "imageUpdate",                              _gsCProcedureImageUpdate,                              NULL);
  //mape_set_native_function(0, g_ape, "imageBind",                                _gsCProcedureImageBind,                                NULL);
  //mape_set_native_function(0, g_ape, "imageUnbind",                              _gsCProcedureImageUnbind,                              NULL);
  //mape_set_native_function(0, g_ape, "imageDraw",                                _gsCProcedureImageDraw,                                NULL);
  //mape_set_native_function(0, g_ape, "imageDrawSubsection",                      _gsCProcedureImageDrawSubsection,                      NULL);
  //mape_set_native_function(0, g_ape, "shaderBegin",                              _gsCProcedureShaderBegin,                              NULL);
  //mape_set_native_function(0, g_ape, "shaderEnd",                                _gsCProcedureShaderEnd,                                NULL);
  //mape_set_native_function(0, g_ape, "shaderSetUniform4f",                       _gsCProcedureShaderSetUniform4f,                       NULL);
  //mape_set_native_function(0, g_ape, "shaderSetUniform4fv",                      _gsCProcedureShaderSetUniform4fv,                      NULL);
  //mape_set_native_function(0, g_ape, "shaderSetUniformMatrix4f",                 _gsCProcedureShaderSetUniformMatrix4f,                 NULL);
  //mape_set_native_function(0, g_ape, "shaderSetUniformImage",                    _gsCProcedureShaderSetUniformImage,                    NULL);
  //mape_set_native_function(0, g_ape, "shaderDelete",                             _gsCProcedureShaderDelete,                             NULL);
  //mape_set_native_function(0, g_ape, "shaderDeleteAll",                          _gsCProcedureShaderDeleteAll,                          NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerNew",                           _gsCProcedureSoundPlayerNew,                           NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerPersistentNew",                 _gsCProcedureSoundPlayerPersistentNew,                 NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerDelete",                        _gsCProcedureSoundPlayerDelete,                        NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerPersistentDelete",              _gsCProcedureSoundPlayerPersistentDelete,              NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerDeleteAll",                     _gsCProcedureSoundPlayerDeleteAll,                     NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerPersistentDeleteAll",           _gsCProcedureSoundPlayerPersistentDeleteAll,           NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerGetHandle",                     _gsCProcedureSoundPlayerGetHandle,                     NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerPersistentGetHandle",           _gsCProcedureSoundPlayerPersistentGetHandle,           NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerLoad",                          _gsCProcedureSoundPlayerLoad,                          NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerUnload",                        _gsCProcedureSoundPlayerUnload,                        NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerPlay",                          _gsCProcedureSoundPlayerPlay,                          NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerStop",                          _gsCProcedureSoundPlayerStop,                          NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerSetVolume",                     _gsCProcedureSoundPlayerSetVolume,                     NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerSetPan",                        _gsCProcedureSoundPlayerSetPan,                        NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerSetSpeed",                      _gsCProcedureSoundPlayerSetSpeed,                      NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerSetPaused",                     _gsCProcedureSoundPlayerSetPaused,                     NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerSetLoop",                       _gsCProcedureSoundPlayerSetLoop,                       NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerSetMultiPlay",                  _gsCProcedureSoundPlayerSetMultiPlay,                  NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerSetPosition",                   _gsCProcedureSoundPlayerSetPosition,                   NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerSetPositionMS",                 _gsCProcedureSoundPlayerSetPositionMS,                 NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerGetPositionMS",                 _gsCProcedureSoundPlayerGetPositionMS,                 NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerGetPosition",                   _gsCProcedureSoundPlayerGetPosition,                   NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerIsPlaying",                     _gsCProcedureSoundPlayerIsPlaying,                     NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerGetSpeed",                      _gsCProcedureSoundPlayerGetSpeed,                      NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerGetPan",                        _gsCProcedureSoundPlayerGetPan,                        NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerGetVolume",                     _gsCProcedureSoundPlayerGetVolume,                     NULL);
  //mape_set_native_function(0, g_ape, "soundPlayerIsLoaded",                      _gsCProcedureSoundPlayerIsLoaded,                      NULL);
  //mape_set_native_function(0, g_ape, "soundSetVolume",                           _gsCProcedureSoundSetVolume,                           NULL);
  //mape_set_native_function(0, g_ape, "soundShutdown",                            _gsCProcedureSoundShutdown,                            NULL);
  //mape_set_native_function(0, g_ape, "soundStopAll",                             _gsCProcedureSoundStopAll,                             NULL);
  //mape_set_native_function(0, g_ape, "soundUpdate",                              _gsCProcedureSoundUpdate,                              NULL);
  //mape_set_native_function(0, g_ape, "imguiBegin",                               _gsCProcedureImguiBegin,                               NULL);
  //mape_set_native_function(0, g_ape, "imguiEnd",                                 _gsCProcedureImguiEnd,                                 NULL);
  mape_set_native_function(0, g_ape, "imguiWindowBegin",                         _gsCProcedureImguiWindowBegin,                         NULL);
  mape_set_native_function(0, g_ape, "imguiWindowEnd",                           _gsCProcedureImguiWindowEnd,                           NULL);
  mape_set_native_function(0, g_ape, "imguiButton",                              _gsCProcedureImguiButton,                              NULL);
  //mape_set_native_function(0, g_ape, "imguiText",                                _gsCProcedureImguiText,                                NULL);
  mape_set_native_function(0, g_ape, "imguiTextMultiline",                       _gsCProcedureImguiTextMultiline,                       NULL);
  mape_set_native_function(0, g_ape, "imguiInputText",                           _gsCProcedureImguiInputText,                           NULL);
  mape_set_native_function(0, g_ape, "imguiInputTextMultiline",                  _gsCProcedureImguiInputTextMultiline,                  NULL);
  //mape_set_native_function(0, g_ape, "profileBegin",                             _gsCProcedureProfileBegin,                             NULL);
  //mape_set_native_function(0, g_ape, "profileEnd",                               _gsCProcedureProfileEnd,                               NULL);
  //mape_set_native_function(0, g_ape, "systemCommand",                            _gsCProcedureSystemCommand,                            NULL);
  //mape_set_native_function(0, g_ape, "glGetIntegerv",                            _gsCProcedureGlGetIntegerv,                            NULL);
  mape_set_native_function(0, g_ape, "getUniqueNumber",                          _gsCProcedureGetUniqueNumber,                          NULL);
  mape_set_native_function(0, g_ape, "getUint64Max",                             _gsCProcedureGetUint64Max,                             NULL);
  //mape_set_native_function(0, g_ape, "getLibGameHandle",                         _gsCProcedureGetLibGameHandle,                         NULL);
  //mape_set_native_function(0, g_ape, "getLibThread2Handle",                      _gsCProcedureGetLibThread2Handle,                      NULL);
  //mape_set_native_function(0, g_ape, "getGlfwWindowHandle",                      _gsCProcedureGetGlfwWindowHandle,                      NULL);
  //mape_set_native_function(0, g_ape, "getLastDragAndDropCounter",                _gsCProcedureGetLastDragAndDropCounter,                NULL);
  //mape_set_native_function(0, g_ape, "getLastDragAndDropFilepathsCount",         _gsCProcedureGetLastDragAndDropFilepathsCount,         NULL);
  //mape_set_native_function(0, g_ape, "getLastDragAndDropFilepath",               _gsCProcedureGetLastDragAndDropFilepath,               NULL);
  //mape_set_native_function(0, g_ape, "getLastDragAndDropPositionX",              _gsCProcedureGetLastDragAndDropPositionX,              NULL);
  //mape_set_native_function(0, g_ape, "getLastDragAndDropPositionY",              _gsCProcedureGetLastDragAndDropPositionY,              NULL);
  //mape_set_native_function(0, g_ape, "githubR_lyehLz4xEncode",                        _gsCProcedureGithubR_lyehLz4xEncode,                        NULL);
  //mape_set_native_function(0, g_ape, "githubR_lyehLz4xDecode",                        _gsCProcedureGithubR_lyehLz4xDecode,                        NULL);
  //mape_set_native_function(0, g_ape, "githubR_lyehLz4xBoundsEncodeOutBytesCount",     _gsCProcedureGithubR_lyehLz4xBoundsEncodeOutBytesCount,     NULL);
  //mape_set_native_function(0, g_ape, "githubR_lyehUlzEncode",                         _gsCProcedureGithubR_lyehUlzEncode,                         NULL);
  //mape_set_native_function(0, g_ape, "githubR_lyehUlzDecode",                         _gsCProcedureGithubR_lyehUlzDecode,                         NULL);
  //mape_set_native_function(0, g_ape, "githubR_lyehUlzBoundsEncodeOutBytesCount",      _gsCProcedureGithubR_lyehUlzBoundsEncodeOutBytesCount,      NULL);
  //mape_set_native_function(0, g_ape, "thread2Run",                                    _gsCProcedureThread2Run,                                    NULL);
  //mape_set_native_function(0, g_ape, "thread2StopAndWaitFor",                         _gsCProcedureThread2StopAndWaitFor,                         NULL);
  //mape_set_native_function(0, g_ape, "thread2IsRunning",                              _gsCProcedureThread2IsRunning,                              NULL);
  mape_set_native_function(0, g_ape, "getGameScriptString",                           _gsCProcedureGetGameScriptString,                           NULL);
  //mape_set_native_function(0, g_ape, "setGameScriptStringForNextFrame",               _gsCProcedureSetGameScriptStringForNextFrame,               NULL);
  //mape_set_native_function(0, g_ape, "setGameScriptStringForNextFrameFromPointer",    _gsCProcedureSetGameScriptStringForNextFrameFromPointer,    NULL);
  //mape_set_native_function(0, g_ape, "getThread2ScriptString",                        _gsCProcedureGetThread2ScriptString,                        NULL);
  //mape_set_native_function(0, g_ape, "setThread2ScriptStringForNextFrame",            _gsCProcedureSetThread2ScriptStringForNextFrame,            NULL);
  //mape_set_native_function(0, g_ape, "setThread2ScriptStringForNextFrameFromPointer", _gsCProcedureSetThread2ScriptStringForNextFrameFromPointer, NULL);
  mape_set_native_function(0, g_ape, "libGameScriptExternalProcedureReload",          _gsCProcedureLibGameScriptExternalProcedureReload,          NULL);
  mape_set_native_function(0, g_ape, "libGameScriptExternalProcedureCall2",           _gsCProcedureLibGameScriptExternalProcedureCall2,           NULL);
  mape_set_native_function(0, g_ape, "libGameScriptExternalProcedureCall3",           _gsCProcedureLibGameScriptExternalProcedureCall3,           NULL);
  //mape_set_native_function(0, g_ape, "programGetArgumentsCount",                      _gsCProcedureProgramGetArgumentsCount,                      NULL);
  //mape_set_native_function(0, g_ape, "programGetArgument",                            _gsCProcedureProgramGetArgument,                            NULL);
  //mape_set_native_function(0, g_ape, "programClose",                                  _gsCProcedureProgramClose,                                  NULL);
  mape_set_native_function(0, g_ape, "asin",                                          _gsCProcedureAsin,                                          NULL);
  mape_set_native_function(0, g_ape, "acos",                                          _gsCProcedureAcos,                                          NULL);
  mape_set_native_function(0, g_ape, "atan",                                          _gsCProcedureAtan,                                          NULL);
  mape_set_native_function(0, g_ape, "atan2",                                         _gsCProcedureAtan2,                                         NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesGetCount",                                          _gsCProcedureGlobalMeshesGetCount,                                          NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesPersistentGetCount",                                _gsCProcedureGlobalMeshesPersistentGetCount,                                NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesGetMeshLabelByMeshIndex",                           _gsCProcedureGlobalMeshesGetMeshLabelByMeshIndex,                           NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesPersistentGetMeshLabelByMeshIndex",                 _gsCProcedureGlobalMeshesPersistentGetMeshLabelByMeshIndex,                 NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesGetMeshHandleByMeshIndex",                          _gsCProcedureGlobalMeshesGetMeshHandleByMeshIndex,                          NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesPersistentGetMeshHandleByMeshIndex",                _gsCProcedureGlobalMeshesPersistentGetMeshHandleByMeshIndex,                NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesGetHaveVerticesChangedMeshIndexesCount",            _gsCProcedureGlobalMeshesGetHaveVerticesChangedMeshIndexesCount,            NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesGetHaveColorsChangedMeshIndexesCount",              _gsCProcedureGlobalMeshesGetHaveColorsChangedMeshIndexesCount,              NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesGetHaveTexCoordsChangedMeshIndexesCount",           _gsCProcedureGlobalMeshesGetHaveTexCoordsChangedMeshIndexesCount,           NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesGetHaveIndicesChangedMeshIndexesCount",             _gsCProcedureGlobalMeshesGetHaveIndicesChangedMeshIndexesCount,             NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesPersistentGetHaveVerticesChangedMeshIndexesCount",  _gsCProcedureGlobalMeshesPersistentGetHaveVerticesChangedMeshIndexesCount,  NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesPersistentGetHaveColorsChangedMeshIndexesCount",    _gsCProcedureGlobalMeshesPersistentGetHaveColorsChangedMeshIndexesCount,    NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesPersistentGetHaveTexCoordsChangedMeshIndexesCount", _gsCProcedureGlobalMeshesPersistentGetHaveTexCoordsChangedMeshIndexesCount, NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesPersistentGetHaveIndicesChangedMeshIndexesCount",   _gsCProcedureGlobalMeshesPersistentGetHaveIndicesChangedMeshIndexesCount,   NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesGetHaveVerticesChangedMeshIndexes",                 _gsCProcedureGlobalMeshesGetHaveVerticesChangedMeshIndexes,                 NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesGetHaveColorsChangedMeshIndexes",                   _gsCProcedureGlobalMeshesGetHaveColorsChangedMeshIndexes,                   NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesGetHaveTexCoordsChangedMeshIndexes",                _gsCProcedureGlobalMeshesGetHaveTexCoordsChangedMeshIndexes,                NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesGetHaveIndicesChangedMeshIndexes",                  _gsCProcedureGlobalMeshesGetHaveIndicesChangedMeshIndexes,                  NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesPersistentGetHaveVerticesChangedMeshIndexes",       _gsCProcedureGlobalMeshesPersistentGetHaveVerticesChangedMeshIndexes,       NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesPersistentGetHaveColorsChangedMeshIndexes",         _gsCProcedureGlobalMeshesPersistentGetHaveColorsChangedMeshIndexes,         NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesPersistentGetHaveTexCoordsChangedMeshIndexes",      _gsCProcedureGlobalMeshesPersistentGetHaveTexCoordsChangedMeshIndexes,      NULL);
  //mape_set_native_function(0, g_ape, "globalMeshesPersistentGetHaveIndicesChangedMeshIndexes",        _gsCProcedureGlobalMeshesPersistentGetHaveIndicesChangedMeshIndexes,        NULL);
  mape_set_native_function(0, g_ape, "globalKeyPropertyGetKeyLabelsCount",                            _gsCProcedureGlobalKeyPropertyGetKeyLabelsCount,                            NULL);
  mape_set_native_function(0, g_ape, "globalKeyPropertyIsKeyLabelExists",                             _gsCProcedureGlobalKeyPropertyIsKeyLabelExists,                             NULL);
  mape_set_native_function(0, g_ape, "globalKeyPropertyGetKeyLabelByKeyIndex",                        _gsCProcedureGlobalKeyPropertyGetKeyLabelByKeyIndex,                        NULL);
  mape_set_native_function(0, g_ape, "globalKeyPropertyGetKeyPropertyLabelsCount",                    _gsCProcedureGlobalKeyPropertyGetKeyPropertyLabelsCount,                    NULL);
  mape_set_native_function(0, g_ape, "globalKeyPropertyIsKeyPropertyLabelExists",                     _gsCProcedureGlobalKeyPropertyIsKeyPropertyLabelExists,                     NULL);
  mape_set_native_function(0, g_ape, "globalKeyPropertyGetKeyPropertyLabelByPropertyIndex",           _gsCProcedureGlobalKeyPropertyGetKeyPropertyLabelByPropertyIndex,           NULL);
  mape_set_native_function(0, g_ape, "globalKeyPropertyRemoveKey",                                    _gsCProcedureGlobalKeyPropertyRemoveKey,                                    NULL);
  mape_set_native_function(0, g_ape, "globalKeyPropertyRemoveAllKeys",                                _gsCProcedureGlobalKeyPropertyRemoveAllKeys,                                NULL);
  mape_set_native_function(0, g_ape, "globalKeyPropertyRemoveProperty",                               _gsCProcedureGlobalKeyPropertyRemoveProperty,                               NULL);
  mape_set_native_function(0, g_ape, "globalKeyPropertyRemoveAllProperties",                          _gsCProcedureGlobalKeyPropertyRemoveAllProperties,                          NULL);
  mape_set_native_function(0, g_ape, "globalKeyPropertySetString",                                    _gsCProcedureGlobalKeyPropertySetString,                                    NULL);
  mape_set_native_function(0, g_ape, "globalKeyPropertySetNumber",                                    _gsCProcedureGlobalKeyPropertySetNumber,                                    NULL);
  mape_set_native_function(0, g_ape, "globalKeyPropertySetBool",                                      _gsCProcedureGlobalKeyPropertySetBool,                                      NULL);
  mape_set_native_function(0, g_ape, "globalKeyPropertyGetString",                                    _gsCProcedureGlobalKeyPropertyGetString,                                    NULL);
  mape_set_native_function(0, g_ape, "globalKeyPropertyGetNumber",                                    _gsCProcedureGlobalKeyPropertyGetNumber,                                    NULL);
  mape_set_native_function(0, g_ape, "globalKeyPropertyGetBool",                                      _gsCProcedureGlobalKeyPropertyGetBool,                                      NULL);
  mape_set_native_function(0, g_ape, "getRedStructsCount",                          _gsCProcedureGetRedStructsCount,                            NULL);
  mape_set_native_function(0, g_ape, "getRedStructName",                            _gsCProcedureGetRedStructName,                              NULL);
  mape_set_native_function(0, g_ape, "getRedStructMembersCount",                    _gsCProcedureGetRedStructMembersCount,                      NULL);
  mape_set_native_function(0, g_ape, "getRedStructMemberName",                      _gsCProcedureGetRedStructMemberName,                        NULL);
  mape_set_native_function(0, g_ape, "redStructSizeof",                             _gsCProcedureRedStructSizeof,                               NULL);
  mape_set_native_function(0, g_ape, "redStructMemberSizeof",                       _gsCProcedureRedStructMemberSizeof,                         NULL);
  mape_set_native_function(0, g_ape, "redStructMemberOffsetof",                     _gsCProcedureRedStructMemberOffsetof,                       NULL);
  mape_set_native_function(0, g_ape, "redStructMemberTypeof",                       _gsCProcedureRedStructMemberTypeof,                         NULL);
  mape_set_native_function(0, g_ape, "redCreateContext",                            _gsCProcedureRedCreateContext,                              NULL);
  //mape_set_native_function(0, g_ape, "redCreateContextWithRayTracingFeatureLevel1", _gsCProcedureRedCreateContextWithRayTracingFeatureLevel1,   NULL);
  //mape_set_native_function(0, g_ape, "redCreateContextWithRayTracingFeatureLevel2", _gsCProcedureRedCreateContextWithRayTracingFeatureLevel2,   NULL);
  //mape_set_native_function(0, g_ape, "redHandleContextGetProcAddr",                 _gsCProcedureRedHandleContextGetProcAddr,                   NULL);
  mape_set_native_function(0, g_ape, "redMemoryGetBudget",                          _gsCProcedureRedMemoryGetBudget,                            NULL);
  mape_set_native_function(0, g_ape, "redMemoryAllocate",                           _gsCProcedureRedMemoryAllocate,                             NULL);
  mape_set_native_function(0, g_ape, "redMemoryAllocateMappable",                   _gsCProcedureRedMemoryAllocateMappable,                     NULL);
  mape_set_native_function(0, g_ape, "redMemoryFree",                               _gsCProcedureRedMemoryFree,                                 NULL);
  mape_set_native_function(0, g_ape, "redMemorySet",                                _gsCProcedureRedMemorySet,                                  NULL);
  mape_set_native_function(0, g_ape, "redMemoryMap",                                _gsCProcedureRedMemoryMap,                                  NULL);
  mape_set_native_function(0, g_ape, "redMemoryUnmap",                              _gsCProcedureRedMemoryUnmap,                                NULL);
  mape_set_native_function(0, g_ape, "redMemoryNonCoherentFlush",                   _gsCProcedureRedMemoryNonCoherentFlush,                     NULL);
  mape_set_native_function(0, g_ape, "redMemoryNonCoherentInvalidate",              _gsCProcedureRedMemoryNonCoherentInvalidate,                NULL);
  mape_set_native_function(0, g_ape, "redStructsMemoryAllocate",                    _gsCProcedureRedStructsMemoryAllocate,                      NULL);
  mape_set_native_function(0, g_ape, "redStructsMemoryAllocateSamplers",            _gsCProcedureRedStructsMemoryAllocateSamplers,              NULL);
  mape_set_native_function(0, g_ape, "redStructsMemorySuballocateStructs",          _gsCProcedureRedStructsMemorySuballocateStructs,            NULL);
  mape_set_native_function(0, g_ape, "redStructsMemoryReset",                       _gsCProcedureRedStructsMemoryReset,                         NULL);
  mape_set_native_function(0, g_ape, "redStructsMemoryFree",                        _gsCProcedureRedStructsMemoryFree,                          NULL);
  mape_set_native_function(0, g_ape, "redStructsSet",                               _gsCProcedureRedStructsSet,                                 NULL);
  mape_set_native_function(0, g_ape, "redCreateArray",                              _gsCProcedureRedCreateArray,                                NULL);
  mape_set_native_function(0, g_ape, "redCreateImage",                              _gsCProcedureRedCreateImage,                                NULL);
  mape_set_native_function(0, g_ape, "redCreateSampler",                            _gsCProcedureRedCreateSampler,                              NULL);
  mape_set_native_function(0, g_ape, "redCreateTexture",                            _gsCProcedureRedCreateTexture,                              NULL);
  mape_set_native_function(0, g_ape, "redCreateGpuCode",                            _gsCProcedureRedCreateGpuCode,                              NULL);
  mape_set_native_function(0, g_ape, "redCreateOutputDeclaration",                  _gsCProcedureRedCreateOutputDeclaration,                    NULL);
  mape_set_native_function(0, g_ape, "redCreateStructDeclaration",                  _gsCProcedureRedCreateStructDeclaration,                    NULL);
  mape_set_native_function(0, g_ape, "redCreateProcedureParameters",                _gsCProcedureRedCreateProcedureParameters,                  NULL);
  mape_set_native_function(0, g_ape, "redCreateProcedureCache",                     _gsCProcedureRedCreateProcedureCache,                       NULL);
  mape_set_native_function(0, g_ape, "redCreateProcedure",                          _gsCProcedureRedCreateProcedure,                            NULL);
  mape_set_native_function(0, g_ape, "redCreateProcedureCompute",                   _gsCProcedureRedCreateProcedureCompute,                     NULL);
  mape_set_native_function(0, g_ape, "redCreateOutput",                             _gsCProcedureRedCreateOutput,                               NULL);
  mape_set_native_function(0, g_ape, "redCreateCpuSignal",                          _gsCProcedureRedCreateCpuSignal,                            NULL);
  mape_set_native_function(0, g_ape, "redCreateGpuSignal",                          _gsCProcedureRedCreateGpuSignal,                            NULL);
  mape_set_native_function(0, g_ape, "redCreateGpuToCpuSignal",                     _gsCProcedureRedCreateGpuToCpuSignal,                       NULL);
  mape_set_native_function(0, g_ape, "redCreateCalls",                              _gsCProcedureRedCreateCalls,                                NULL);
  mape_set_native_function(0, g_ape, "redCreateCallsReusable",                      _gsCProcedureRedCreateCallsReusable,                        NULL);
  mape_set_native_function(0, g_ape, "redDestroyContext",                           _gsCProcedureRedDestroyContext,                             NULL);
  mape_set_native_function(0, g_ape, "redDestroyArray",                             _gsCProcedureRedDestroyArray,                               NULL);
  mape_set_native_function(0, g_ape, "redDestroyImage",                             _gsCProcedureRedDestroyImage,                               NULL);
  mape_set_native_function(0, g_ape, "redDestroySampler",                           _gsCProcedureRedDestroySampler,                             NULL);
  mape_set_native_function(0, g_ape, "redDestroyTexture",                           _gsCProcedureRedDestroyTexture,                             NULL);
  mape_set_native_function(0, g_ape, "redDestroyGpuCode",                           _gsCProcedureRedDestroyGpuCode,                             NULL);
  mape_set_native_function(0, g_ape, "redDestroyOutputDeclaration",                 _gsCProcedureRedDestroyOutputDeclaration,                   NULL);
  mape_set_native_function(0, g_ape, "redDestroyStructDeclaration",                 _gsCProcedureRedDestroyStructDeclaration,                   NULL);
  mape_set_native_function(0, g_ape, "redDestroyProcedureParameters",               _gsCProcedureRedDestroyProcedureParameters,                 NULL);
  mape_set_native_function(0, g_ape, "redDestroyProcedureCache",                    _gsCProcedureRedDestroyProcedureCache,                      NULL);
  mape_set_native_function(0, g_ape, "redDestroyProcedure",                         _gsCProcedureRedDestroyProcedure,                           NULL);
  mape_set_native_function(0, g_ape, "redDestroyOutput",                            _gsCProcedureRedDestroyOutput,                              NULL);
  mape_set_native_function(0, g_ape, "redDestroyCpuSignal",                         _gsCProcedureRedDestroyCpuSignal,                           NULL);
  mape_set_native_function(0, g_ape, "redDestroyGpuSignal",                         _gsCProcedureRedDestroyGpuSignal,                           NULL);
  mape_set_native_function(0, g_ape, "redDestroyGpuToCpuSignal",                    _gsCProcedureRedDestroyGpuToCpuSignal,                      NULL);
  mape_set_native_function(0, g_ape, "redDestroyCalls",                             _gsCProcedureRedDestroyCalls,                               NULL);
  mape_set_native_function(0, g_ape, "redProcedureCacheGetBlob",                    _gsCProcedureRedProcedureCacheGetBlob,                      NULL);
  mape_set_native_function(0, g_ape, "redProcedureCacheMergeCaches",                _gsCProcedureRedProcedureCacheMergeCaches,                  NULL);
  mape_set_native_function(0, g_ape, "redCpuSignalGetStatus",                       _gsCProcedureRedCpuSignalGetStatus,                         NULL);
  mape_set_native_function(0, g_ape, "redCpuSignalWait",                            _gsCProcedureRedCpuSignalWait,                              NULL);
  mape_set_native_function(0, g_ape, "redCpuSignalUnsignal",                        _gsCProcedureRedCpuSignalUnsignal,                          NULL);
  mape_set_native_function(0, g_ape, "redGpuToCpuSignalGetStatus",                  _gsCProcedureRedGpuToCpuSignalGetStatus,                    NULL);
  mape_set_native_function(0, g_ape, "redGpuToCpuSignalUnsignal",                   _gsCProcedureRedGpuToCpuSignalUnsignal,                     NULL);
  mape_set_native_function(0, g_ape, "redCallsSet",                                 _gsCProcedureRedCallsSet,                                   NULL);
  mape_set_native_function(0, g_ape, "redCallsEnd",                                 _gsCProcedureRedCallsEnd,                                   NULL);
  mape_set_native_function(0, g_ape, "redGetCallProceduresAndAddresses",            _gsCProcedureRedGetCallProceduresAndAddresses,              NULL);
  mape_set_native_function(0, g_ape, "redCallGpuToCpuSignalSignal",                 _gsCProcedureRedCallGpuToCpuSignalSignal,                   NULL);
  mape_set_native_function(0, g_ape, "redCallCopyArrayToArray",                     _gsCProcedureRedCallCopyArrayToArray,                       NULL);
  mape_set_native_function(0, g_ape, "redCallCopyImageToImage",                     _gsCProcedureRedCallCopyImageToImage,                       NULL);
  mape_set_native_function(0, g_ape, "redCallCopyArrayToImage",                     _gsCProcedureRedCallCopyArrayToImage,                       NULL);
  mape_set_native_function(0, g_ape, "redCallCopyImageToArray",                     _gsCProcedureRedCallCopyImageToArray,                       NULL);
  mape_set_native_function(0, g_ape, "redCallProcedure",                            _gsCProcedureRedCallProcedure,                              NULL);
  mape_set_native_function(0, g_ape, "redCallProcedureIndexed",                     _gsCProcedureRedCallProcedureIndexed,                       NULL);
  mape_set_native_function(0, g_ape, "redCallProcedureCompute",                     _gsCProcedureRedCallProcedureCompute,                       NULL);
  mape_set_native_function(0, g_ape, "redCallSetProcedure",                         _gsCProcedureRedCallSetProcedure,                           NULL);
  mape_set_native_function(0, g_ape, "redCallSetProcedureIndices",                  _gsCProcedureRedCallSetProcedureIndices,                    NULL);
  mape_set_native_function(0, g_ape, "redCallSetProcedureParametersVariables",      _gsCProcedureRedCallSetProcedureParametersVariables,        NULL);
  mape_set_native_function(0, g_ape, "redCallSetProcedureParametersStructs",        _gsCProcedureRedCallSetProcedureParametersStructs,          NULL);
  mape_set_native_function(0, g_ape, "redCallSetProcedureParametersHandles",        _gsCProcedureRedCallSetProcedureParametersHandles,          NULL);
  mape_set_native_function(0, g_ape, "redCallSetDynamicDepthBias",                  _gsCProcedureRedCallSetDynamicDepthBias,                    NULL);
  mape_set_native_function(0, g_ape, "redCallSetDynamicDepthBounds",                _gsCProcedureRedCallSetDynamicDepthBounds,                  NULL);
  mape_set_native_function(0, g_ape, "redCallSetDynamicStencilCompareMask",         _gsCProcedureRedCallSetDynamicStencilCompareMask,           NULL);
  mape_set_native_function(0, g_ape, "redCallSetDynamicStencilWriteMask",           _gsCProcedureRedCallSetDynamicStencilWriteMask,             NULL);
  mape_set_native_function(0, g_ape, "redCallSetDynamicStencilReference",           _gsCProcedureRedCallSetDynamicStencilReference,             NULL);
  mape_set_native_function(0, g_ape, "redCallSetDynamicBlendConstants",             _gsCProcedureRedCallSetDynamicBlendConstants,               NULL);
  mape_set_native_function(0, g_ape, "redCallSetDynamicViewport",                   _gsCProcedureRedCallSetDynamicViewport,                     NULL);
  mape_set_native_function(0, g_ape, "redCallSetDynamicScissor",                    _gsCProcedureRedCallSetDynamicScissor,                      NULL);
  mape_set_native_function(0, g_ape, "redCallSetStructsMemory",                     _gsCProcedureRedCallSetStructsMemory,                       NULL);
  mape_set_native_function(0, g_ape, "redCallSetProcedureParameters",               _gsCProcedureRedCallSetProcedureParameters,                 NULL);
  mape_set_native_function(0, g_ape, "redCallSetProcedureOutput",                   _gsCProcedureRedCallSetProcedureOutput,                     NULL);
  mape_set_native_function(0, g_ape, "redCallEndProcedureOutput",                   _gsCProcedureRedCallEndProcedureOutput,                     NULL);
  mape_set_native_function(0, g_ape, "redCallUsageAliasOrderBarrier",               _gsCProcedureRedCallUsageAliasOrderBarrier,                 NULL);
  mape_set_native_function(0, g_ape, "redCallMark",                                 _gsCProcedureRedCallMark,                                   NULL);
  mape_set_native_function(0, g_ape, "redCallMarkSet",                              _gsCProcedureRedCallMarkSet,                                NULL);
  mape_set_native_function(0, g_ape, "redCallMarkEnd",                              _gsCProcedureRedCallMarkEnd,                                NULL);
  mape_set_native_function(0, g_ape, "redQueueSubmit",                              _gsCProcedureRedQueueSubmit,                                NULL);
  mape_set_native_function(0, g_ape, "redMark",                                     _gsCProcedureRedMark,                                       NULL);
  mape_set_native_function(0, g_ape, "redMarkSet",                                  _gsCProcedureRedMarkSet,                                    NULL);
  mape_set_native_function(0, g_ape, "redMarkEnd",                                  _gsCProcedureRedMarkEnd,                                    NULL);
  //mape_set_native_function(0, g_ape, "redCreateProcedureComputingLanguage",         _gsCProcedureRedCreateProcedureComputingLanguage,           NULL);
  mape_set_native_function(0, g_ape, "redCreateArrayTimestamp",                     _gsCProcedureRedCreateArrayTimestamp,                       NULL);
  mape_set_native_function(0, g_ape, "redDestroyArrayTimestamp",                    _gsCProcedureRedDestroyArrayTimestamp,                      NULL);
  mape_set_native_function(0, g_ape, "redCallArrayTimestampWrite",                  _gsCProcedureRedCallArrayTimestampWrite,                    NULL);
  mape_set_native_function(0, g_ape, "redArrayTimestampRead",                       _gsCProcedureRedArrayTimestampRead,                         NULL);
}

void scriptCheckForErrors() {
  if (g_ape != 0) {
    if (ape_has_errors(g_ape)) {
      for (int i = 0; i < ape_errors_count(g_ape); i += 1) {
        const ape_error_t * err = ape_get_error(g_ape, i);
        char * error = ape_error_serialize(g_ape, err);
        std::string errorString = error;
        g_codeErrorsString += errorString;
        ape_free_allocated(g_ape, error);
      }
      ape_clear_errors(g_ape);
      if (g_codeErrorsString.empty() == false) {
        g_windowShowCodeErrors = true;
      }
    }
  }
}

void scriptDestroyContext() {
  ape_destroy(g_ape);
  g_ape = 0;
  g_ape_compiled_program = 0;
}

void scriptCompileProgram() {
  g_codeErrorsString.clear();
  scriptDestroyContext();
  g_ape = ape_make();
  mape_set_c_procedures();
  g_ape_compiled_program = ape_compile(g_ape, g_codeString.c_str());
  scriptCheckForErrors();
}

void scriptTick() {
  if (g_compileMode == false) {
    if (g_currentFrame == 0) {
      g_codeErrorsString.clear();
    }

    scriptDestroyContext();
    g_ape = ape_make();
    mape_set_c_procedures();

    if (g_frame0CacheEnable == true) {
      const char * code = g_codeString.c_str();
      if (g_frame0CacheStartPositionIsDirty == true) {
        g_frame0CacheStartPositionIsDirty = false;
        g_frame0CacheStartPosition        = 0;
        const size_t size = g_codeString.size();
        for (size_t i = 0; i < size; i += 1) {
          if (code[i] == '@') {
            g_frame0CacheStartPosition = i + 1;
            if (g_frame0CacheStartPosition >= size) {
              g_frame0CacheStartPosition = size - 1;
            }
            break;
          }
        }
      }
      if (g_currentFrame == 0) {
        ape_execute(g_ape, code);
      } else {
        ape_execute(g_ape, &code[g_frame0CacheStartPosition]);
      }
    } else {
      ape_execute(g_ape, g_codeString.c_str());
    }

    scriptCheckForErrors();
  } else {
    if (g_ape_compiled_program != 0) {
      ape_execute_program(g_ape, g_ape_compiled_program);
    }
  }

  for (auto & kv : gGlobalArrayPointer) {
    free(kv.second);
  }
  for (auto & kv : gGlobalDynamicArray) {
    delete kv.second;
  }
  gGlobalArrayBytesCount.clear();
  gGlobalArrayPointer.clear();
  gGlobalDynamicArray.clear();

  g_currentFrame += 1;
}

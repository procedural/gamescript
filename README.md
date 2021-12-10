# Game Script

![game_script_screenshot](https://user-images.githubusercontent.com/28234322/141370424-192f786b-2ea2-4ae0-91a2-e0b2333a0edb.png)

# Download here: [procedural.itch.io/gamescript](https://procedural.itch.io/gamescript)

## Join the official Game Script Discord server for news, updates, code examples and more! https://discord.gg/D7pKPw4kFf

Install
-------

* Download and extract GameScript folder, double click on the `game_script.exe` file on Windows 7 (64-bit) or higher.
* Download and extract GameScript folder, double click on the `game_script.desktop` file on Ubuntu 16.04 (64-bit) or higher.

## [🐞 Report a bug or an issue here](https://github.com/procedural/gamescript/issues)

Hotkeys
-------

* `F3`: toggle between script and game mode.
* `F5`: rerun the script.
* `F7`: pause running the script.
* `F9`: continue running the script.
* `F11`: toggle fullscreen mode.
* `Ctrl` + `Tab`: switch between windows in script mode.
* `Alt` + `Ctrl`, arrow keys: move between UI elements with keyboard in script mode.
* `W`: fly forward in game mode.
* `S`: fly back in game mode.
* `A`: fly left in game mode.
* `D`: fly right in game mode.
* `E`: fly up in game mode.
* `Q`: fly down in game mode.
* `T`: roll camera left in game mode.
* `Y`: roll camera right in game mode.
* `R`: reset camera roll in game mode.

List of available script functions
----------------------------------

```javascript
fn printConsole(String string)
fn printDraw(String string)
fn windowSetTitle(String title)
fn windowGetWidth() -> Number width
fn windowGetHeight() -> Number height
fn windowSetWidthHeight(Number width, Number height)
fn windowSetFullscreen(Bool fullscreen)
fn windowIsFocused() -> Bool isFocused
fn windowIsHovered() -> Bool isHovered
fn windowIsMinimized() -> Bool isMinimized
fn windowIsHidden() -> Bool isHidden
fn windowHide()
fn windowShow()
fn windowRequestAttention()
fn drawPoint(String label, Number x, Number y, Number z, Number size, Number r0to255, Number g0to255, Number b0to255, Number a0to255)
fn drawLine(String label, Number x0, Number y0, Number z0, Number x1, Number y1, Number z1, Number width, Number r0to255, Number g0to255, Number b0to255, Number a0to255)
fn drawTriangle(String label, Number x0, Number y0, Number z0, Number x1, Number y1, Number z1, Number x2, Number y2, Number z2, Number r0to255, Number g0to255, Number b0to255, Number a0to255)
fn drawTriangleWireframe(String label, Number x0, Number y0, Number z0, Number x1, Number y1, Number z1, Number x2, Number y2, Number z2, Number r0to255, Number g0to255, Number b0to255, Number a0to255)
fn drawSphere(Number x, Number y, Number z, Number size, Number r0to255, Number g0to255, Number b0to255, Number a0to255)
fn drawSphereWireframe(Number x, Number y, Number z, Number size, Number r0to255, Number g0to255, Number b0to255, Number a0to255)
fn drawDebugText(String label, Number x, Number y, Number r0to255, Number g0to255, Number b0to255, Number a0to255)
fn drawDebugTextAtPoint(String label, Number x, Number y, Number z)
fn isRerun() -> Bool isRerun
fn getCurrentFrame() -> Number frame
fn setCurrentFrame(Number frame)
fn getRandomNumber() -> Number number
fn getExeDirectoryPath() -> String path
fn isLinux() -> Bool isLinux
fn isWindows() -> Bool isWindows
fn isInGameMode() -> Bool isInGameMode
fn defaultCameraDefaultControlDisable()
fn defaultCameraDefaultControlEnable()
fn defaultCameraDefaultControlForceEnable()
fn defaultCameraDefaultControlIsEnabled() -> Bool isEnabled
fn defaultCameraSetMoveSpeed(Number speed)
fn defaultCameraSetRollSpeed(Number speed)
fn defaultCameraSetMouseSensitivity(Number sensitivity)
fn defaultCameraGetVector() -> Number position [3] {x, y, z}
fn defaultCameraGetVersor() -> Number quaternion [4] {x, y, z, w}
fn defaultCameraSetVector(Number x, Number y, Number z)
fn defaultCameraSetVersor(Number x, Number y, Number z, Number w)
fn defaultCameraRotate(Number rotationAxisX, Number rotationAxisY, Number rotationAxisZ, Number rotationAngleDeg)
fn defaultCameraLookAt(Number x, Number y, Number z, Number upX, Number upY, Number upZ)
fn defaultCameraSetFOV(Number fov)
fn defaultCameraSetNearClip(Number near)
fn defaultCameraSetFarClip(Number far)
fn defaultCameraSetProjectionMode(Number mode)
fn defaultCameraSetAspectRatio(Number aspectRatio)
fn defaultCameraSetForceAspectRatio(Bool forceAspectRatio)
fn defaultCameraSetLensOffset(Number lensOffsetX, Number lensOffsetY)
fn defaultCameraSetupPerspective(Bool vflip, Number fov, Number nearDist, Number farDist, Number lensOffsetX, Number lensOffsetY)
fn defaultCameraSetupOffAxisViewPortal(Number topLeftX, Number topLeftY, Number topLeftZ, Number bottomLeftX, Number bottomLeftY, Number bottomLeftZ, Number bottomRightX, Number bottomRightY, Number bottomRightZ)
fn defaultCameraSetVFlip(Bool vflip)
fn defaultCameraScreenToWorld(Number screenX, Number screenY, Number screenZ) -> Number worldPosition [3] {x, y, z}
fn defaultCameraWorldToScreen(Number worldX, Number worldY, Number worldZ) -> Number screenPosition [3] {x, y, z}
fn defaultCameraGetSideVector() -> Number sideVector [3] {x, y, z}
fn defaultCameraGetUpVector() -> Number upVector [3] {x, y, z}
fn defaultCameraGetLookAtVector() -> Number lookAtVector [3] {x, y, z}
fn defaultCameraSetControlKeys(Number up, Number down, Number left, Number right, Number forward, Number backward, Number rollLeft, Number rollRight, Number rollReset)
fn setBackgroundColor(Number r0to255, Number g0to255, Number b0to255, Number a0to255)
fn setViewport(Number x, Number y, Number width, Number height, Bool vflip)
fn alphaBlendingEnable()
fn alphaBlendingDisable()
fn blendModeEnable(Number mode)
fn blendModeDisable()
fn depthTestEnable()
fn depthTestDisable()
fn cullingEnable(Number mode)
fn cullingDisable()
fn clear(Number r0to1, Number g0to1, Number b0to1, Number a0to1)
fn clearAlpha()
fn clearDepth()
fn saveScreenRawToMemory(Number x, Number y, Number width, Number height, Number out8BitRGBAPixels)
fn globalArrayNew8Bit(String label, Number count) -> Number pointer
fn globalArrayPersistentNew8Bit(String label, Number count) -> Number pointer
fn globalArrayDelete(String label)
fn globalArrayPersistentDelete(String label)
fn globalArrayDeleteAll()
fn globalArrayPersistentDeleteAll()
fn globalArrayGetBytesCount(String label) -> Number bytesCount
fn globalArrayGetPointer(String label) -> Number pointer
fn globalArrayPersistentGetBytesCount(String label) -> Number bytesCount
fn globalArrayPersistentGetPointer(String label) -> Number pointer
fn globalSharedArrayPersistentNew8Bit(String label, Number count) -> Number pointer
fn globalSharedArrayPersistentGetBytesCount(String label) -> Number bytesCount
fn globalSharedArrayPersistentGetPointer(String label) -> Number pointer
fn pointerGetBool(Number pointerTo8BitBools, Number index) -> Bool value
fn pointerGetString(Number pointer) -> String string
fn pointerGetSubstring(Number pointer, Number pointerCharsFirst, Number charsCount) -> String string
fn pointerGetNumber(Number pointerTo32BitFloats, Number index) -> Number value
fn pointerGetInteger(Number pointerTo32BitInts, Number index) -> Number value
fn pointerGetUnsignedInteger(Number pointerTo32BitUints, Number index) -> Number value
fn pointerGetUnsignedInteger8Bit(Number pointerTo8BitUints, Number index) -> Number value
fn pointerSetBool(Number pointerTo8BitBools, Number index, Bool value)
fn pointerSetString(Number pointer, Number pointerCharsFirst, String string)
fn pointerSetStringExcludingNullChar(Number pointer, Number pointerCharsFirst, String string)
fn pointerSetSubstring(Number pointer, Number pointerCharsFirst, String string, Number stringCharsFirst, Number stringCharsCount)
fn pointerSetNumber(Number pointerTo32BitFloats, Number index, Number value)
fn pointerSetInteger(Number pointerTo32BitInts, Number index, Number value)
fn pointerSetUnsignedInteger(Number pointerTo32BitUints, Number index, Number value)
fn pointerSetUnsignedInteger8Bit(Number pointerTo8BitUints, Number index, Number value)
fn pointerGetRaw8Bit(Number pointer, Number bytesFirst) -> Number raw8BitsAsDouble
fn pointerGetRaw16Bit(Number pointer, Number bytesFirst) -> Number raw16BitsAsDouble
fn pointerGetRaw32Bit(Number pointer, Number bytesFirst) -> Number raw32BitsAsDouble
fn pointerGetRaw64Bit(Number pointer, Number bytesFirst) -> Number raw64BitsAsDouble
fn pointerSetRaw8Bit(Number pointer, Number bytesFirst, Number raw8BitsAsDouble)
fn pointerSetRaw16Bit(Number pointer, Number bytesFirst, Number raw16BitsAsDouble)
fn pointerSetRaw32Bit(Number pointer, Number bytesFirst, Number raw32BitsAsDouble)
fn pointerSetRaw64Bit(Number pointer, Number bytesFirst, Number raw64BitsAsDouble)
fn globalDynamicArrayNew(String label) -> Number handle
fn globalDynamicArrayPersistentNew(String label) -> Number handle
fn globalDynamicArrayDelete(String label)
fn globalDynamicArrayPersistentDelete(String label)
fn globalDynamicArrayDeleteAll()
fn globalDynamicArrayPersistentDeleteAll()
fn globalDynamicArrayGetHandle(String label) -> Number handle
fn globalDynamicArrayPersistentGetHandle(String label) -> Number handle
fn dynamicArrayGet(Number handle, Number index) -> Number value
fn dynamicArraySet(Number handle, Number index, Number value)
fn dynamicArrayAppend(Number handle, Number value)
fn dynamicArrayRemoveAt(Number handle, Number index) -> Bool success
fn dynamicArrayRemoveLast(Number handle)
fn dynamicArrayGetSize(Number handle) -> Number size
fn memset(Number pointer, Number pointerBytesFirst, Number value8Bit, Number bytesCount)
fn memcpy(Number pointerTarget, Number pointerTargetBytesFirst, Number pointerSource, Number pointerSourceBytesFirst, Number bytesCount)
fn memcmp(Number pointerA, Number pointerABytesFirst, Number pointerB, Number pointerBBytesFirst, Number bytesCount) -> Bool areEqual
fn threadSafeMemset(Number pointer, Number pointerBytesFirst, Number value8Bit, Number bytesCount)
fn threadSafeMemcpy(Number pointerTarget, Number pointerTargetBytesFirst, Number pointerSource, Number pointerSourceBytesFirst, Number bytesCount)
fn threadSafeMemcmp(Number pointerA, Number pointerABytesFirst, Number pointerB, Number pointerBBytesFirst, Number bytesCount) -> Bool areEqual
fn threadWaitForEqualUint64Value(Number pointerA, Number pointerABytesFirst, Number pointerB, Number pointerBBytesFirst) -> Bool trueIfFinishedFalseIfAborted
fn threadWaitForEqualOrMoreThanUint64Value(Number pointerA, Number pointerABytesFirst, Number pointerB, Number pointerBBytesFirst) -> Bool trueIfFinishedFalseIfAborted
fn threadWaitForThread2FrameToFinish(Number thread2Frame) -> Bool trueIfFinishedFalseIfAborted
fn strlenWithNullChar(String string) -> Number length
fn keyboardGetGlfwKeyEvent(Number glfwKey) -> Number keyEvent
fn keyboardGetGlfwKeyModifiers(Number glfwKey) -> Number keyModifiers
fn keyboardGetGlfwCodepointString() -> String codepoint
fn mouseGlfwSetInputMode(Number mode)
fn mouseSetXY(Number x, Number y)
fn mouseGetX() -> Number x
fn mouseGetY() -> Number y
fn mouseGetPreviousX() -> Number x
fn mouseGetPreviousY() -> Number y
fn mouseGetMoveEvent() -> Number mouseEvent
fn mouseGetButtonIsPressed(Number button) -> Bool buttonIsPressed
fn mouseGetButtonIsPressedAndHeld(Number button) -> Bool buttonIsPressedAndHeld
fn mouseGetButtonIsReleased(Number button) -> Bool buttonIsReleased
fn mouseGetWheelScroll() -> Number scroll
fn gamepadIsPresent(Number gamepadId0to15) -> Bool gamepadIsPresent
fn gamepadGet15Buttons6AxesNumbers(Number gamepadId0to15) -> Number buttonsAndAxes [21] {a, b, x, y, leftBumper, rightBumper, back, start, guide, leftThumb, rightThumb, dpadUp, dpadRight, dpadDown, dpadLeft, axisLeftX, axisLeftY, axisRightX, axisRightY, leftTrigger, rightTrigger}
fn gamepadGetName(Number gamepadId0to15) -> String name
fn gamepadGetGUID(Number gamepadId0to15) -> String GUID
fn gamepadUpdateGamecontrollerdbTxt(Number gamepadId0to15, String mappings) -> Bool success
fn boolToNumber(Bool boolean) -> Number number
fn boolToString(Bool boolean) -> String string
fn numberToBool(Number number) -> Bool boolean
fn numberToString(Number number) -> String string
fn numberToBinaryString(Number number) -> String string
fn numberWholePartToString(Number number) -> String string
fn stringCharToNumber(String string) -> Number charNumber
fn stringToNumberArray(String string) -> Number array []
fn interpretStringToInteger(String string) -> Number integer
fn interpretStringToFloat(String string) -> Number float
fn interpretStringToDouble(String string) -> Number double
fn stringReadFromFile(String filepath) -> String string
fn stringWriteToFile(String string, String filepath)
fn stringAppendToFile(String string, String filepath)
fn binaryGetByteSizeOfFile(String filepath) -> Number bytesCount
fn binaryReadFromFile(String filepath, Number writeToPointer, Number writeToPointerBytesFirst)
fn binaryWriteToFile(Number pointer, Number pointerBytesFirst, Number pointerBytesCount, String writeToFilepath)
fn getClipboardString() -> String clipboard
fn setClipboardString(String clipboard)
fn gizmoSetMode(String label, Number mode)
fn gizmoGetVector(String label) -> Number position [3] {x, y, z}
fn gizmoGetVersor(String label) -> Number quaternion [4] {x, y, z, w}
fn gizmoGetScale(String label) -> Number scale [3] {x, y, z}
fn gizmoSetVector(String label, Number x, Number y, Number z)
fn gizmoSetVersor(String label, Number x, Number y, Number z, Number w)
fn gizmoSetScale(String label, Number x, Number y, Number z)
fn gizmoSetDrawScale(String label, Number scale)
fn gizmoSetDrawColors(String label, Number xr, Number xg, Number xb, Number xa, Number yr, Number yg, Number yb, Number ya, Number zr, Number zg, Number zb, Number za, Number wr, Number wg, Number wb, Number wa, Number selectr, Number selectg, Number selectb, Number selecta)
fn gizmoDelete(String label)
fn gizmoDeleteAll()
fn getLastFrameTime() -> Number lastFrameTime
fn getSystemTimeMillis() -> Number ms
fn getSystemTimeMicros() -> Number us
fn getUnixTime() -> Number unixTime
fn framebufferBegin(String label, Number width, Number height, Bool setupScreenDefaultIs1) -> Bool framebufferIsValid
fn framebufferEnd(String label)
fn framebufferDraw(String label, Number x, Number y, Number width, Number height)
fn framebufferClear(String label)
fn framebufferCopyToImage(String label, Number image)
fn framebufferDelete(String label)
fn framebufferDeleteAll()
fn meshNew(String label) -> Number handle
fn meshPersistentNew(String label) -> Number handle
fn meshDelete(String label)
fn meshPersistentDelete(String label)
fn meshDeleteAll()
fn meshPersistentDeleteAll()
fn meshGetHandle(String label) -> Number handle
fn meshPersistentGetHandle(String label) -> Number handle
fn meshIsUsingColors(Number handle) -> Bool boolean
fn meshIsUsingTextures(Number handle) -> Bool boolean
fn meshIsUsingIndices(Number handle) -> Bool boolean
fn meshEnableColors(Number handle)
fn meshEnableTextures(Number handle)
fn meshEnableIndices(Number handle)
fn meshDisableColors(Number handle)
fn meshDisableTextures(Number handle)
fn meshDisableIndices(Number handle)
fn meshHasVertices(Number handle) -> Bool boolean
fn meshHasColors(Number handle) -> Bool boolean
fn meshHasTexCoords(Number handle) -> Bool boolean
fn meshHasIndices(Number handle) -> Bool boolean
fn meshGetVerticesCount(Number handle) -> Number count
fn meshGetColorsCount(Number handle) -> Number count
fn meshGetTexCoordsCount(Number handle) -> Number count
fn meshGetIndicesCount(Number handle) -> Number count
fn meshHaveVerticesChanged(Number handle) -> Bool boolean
fn meshHaveColorsChanged(Number handle) -> Bool boolean
fn meshHaveTexCoordsChanged(Number handle) -> Bool boolean
fn meshHaveIndicesChanged(Number handle) -> Bool boolean
fn meshAddVertex(Number handle, Number x, Number y, Number z)
fn meshAddColor(Number handle, Number r0to1, Number g0to1, Number b0to1, Number a0to1)
fn meshAddTexCoord(Number handle, Number u, Number v)
fn meshAddIndex(Number handle, Number index)
fn meshRemoveVertex(Number handle, Number index)
fn meshRemoveColor(Number handle, Number index)
fn meshRemoveTexCoord(Number handle, Number index)
fn meshRemoveIndex(Number handle, Number index)
fn meshClear(Number handle)
fn meshClearVertices(Number handle)
fn meshClearColors(Number handle)
fn meshClearTexCoords(Number handle)
fn meshClearIndices(Number handle)
fn meshGetVerticesPointer(Number handle) -> Number pointer
fn meshGetColorsPointer(Number handle) -> Number pointer
fn meshGetTexCoordsPointer(Number handle) -> Number pointer
fn meshGetIndicesPointer(Number handle) -> Number pointer
fn meshMergeDuplicateVertices(Number handle)
fn meshSetupIndicesAuto(Number handle)
fn meshAddTriangle(Number handle, Number verticesArrayIndex1, Number verticesArrayIndex2, Number verticesArrayIndex3)
fn meshDraw(Number handle, Number renderMode, Number scaleX, Number scaleY, Number scaleZ, Number vectorX, Number vectorY, Number vectorZ, Number rotationAxisX, Number rotationAxisY, Number rotationAxisZ, Number rotationAngleDeg)
fn meshDrawDebugVertices(String label)
fn meshDrawDebugColors(String label)
fn meshDrawDebugTexCoords(String label)
fn meshDrawDebugIndices(String label)
fn meshDrawDebugRayTraceIndices(String label, Number maxShowDistanceToDefaultCamera, Bool raytraceHighlightTrianglesDefaultCameraLooksAt)
fn meshImporterGetMeshesCount(String meshFilepath) -> Number count
fn meshImporterGetMeshName(String meshFilepath, Number meshIndex) -> String name
fn meshImporterGetMesh(String meshFilepath, Number meshIndex, Number writeToMesh)
fn meshImporterDelete(String meshFilepath)
fn meshImporterDeleteAll()
fn imageNew(String label, Number width, Number height) -> Number handle
fn imagePersistentNew(String label, Number width, Number height) -> Number handle
fn imageNewFromFile(String label, String filepath) -> Number handle
fn imagePersistentNewFromFile(String label, String filepath) -> Number handle
fn imageDelete(String label)
fn imagePersistentDelete(String label)
fn imageDeleteAll()
fn imagePersistentDeleteAll()
fn imageGetHandle(String label) -> Number handle
fn imagePersistentGetHandle(String label) -> Number handle
fn imageLoadFromMemory(Number handle, Number pointer, Number pointerBytesFirst, Number pointerBytesCount) -> Bool success
fn imageClear(Number handle, Number alpha0to255)
fn imageSetTextureMinMagFilter(Number handle, Number minFilter, Number magFilter)
fn imageSetTextureWrap(Number handle, Number wrapX, Number wrapY)
fn imageGetWidth(Number handle) -> Number width
fn imageGetHeight(Number handle) -> Number height
fn imageGetBitsPerPixel(Number handle) -> Number bitsPerPixel
fn imageGetImageType(Number handle) -> Number imageType
fn imageGetPixelsPointer(Number handle) -> Number pointerToPixels
fn imageGetColor(Number handle, Number x, Number y) -> Number color [4] {r0To255, g0To255, b0To255, a0To255}
fn imageSetColor(Number handle, Number x, Number y, Number r0to255, Number g0to255, Number b0to255, Number a0to255)
fn imageGammaCorrect(Number handle)
fn imageUpdate(Number handle)
fn imageBind(Number handle)
fn imageUnbind(Number handle)
fn shaderBegin(String label, String filepathShaderVert, String filepathShaderFrag) -> Bool shadersAreValid
fn shaderEnd(String label)
fn shaderSetUniform4f(String label, String uniformName, Number x, Number y, Number z, Number w)
fn shaderSetUniformImage(String label, String uniformName, Number imageHandle, Number textureLocation)
fn shaderDelete(String label)
fn shaderDeleteAll()
fn soundPlayerNew(String label) -> Number handle
fn soundPlayerDelete(String label)
fn soundPlayerDeleteAll()
fn soundPlayerGetHandle(String label) -> Number handle
fn soundPlayerLoad(Number handle, String filepath, Bool streamDefaultIsFalse) -> Bool success
fn soundPlayerUnload(Number handle)
fn soundPlayerPlay(Number handle)
fn soundPlayerStop(Number handle)
fn soundPlayerSetVolume(Number handle, Number volume0to1)
fn soundPlayerSetPan(Number handle, Number panMinus1to1)
fn soundPlayerSetSpeed(Number handle, Number speedDefaultIs1)
fn soundPlayerSetPaused(Number handle, Bool paused)
fn soundPlayerSetLoop(Number handle, Bool loop)
fn soundPlayerSetMultiPlay(Number handle, Bool multiplay)
fn soundPlayerSetPosition(Number handle, Number percent0to1)
fn soundPlayerGetPosition(Number handle) -> Number percent0to1
fn soundPlayerSetPositionMS(Number handle, Number milliseconds)
fn soundPlayerGetPositionMS(Number handle) -> Number milliseconds
fn soundPlayerIsPlaying(Number handle) -> Bool isPlaying
fn soundPlayerGetSpeed(Number handle) -> Number speed
fn soundPlayerGetPan(Number handle) -> Number pan
fn soundPlayerGetVolume(Number handle) -> Number volume
fn soundPlayerIsLoaded(Number handle) -> Bool isLoaded
fn soundSetVolume(Number volume0to1)
fn soundShutdown()
fn soundStopAll()
fn soundUpdate()
fn imguiBegin()
fn imguiEnd()
fn imguiWindowBegin(String windowName, Number outPointerToWindowIsOpenBool, Number outPointerToWindowIsOpenBoolBytesFirst) -> Bool state
fn imguiWindowEnd()
fn imguiButton(String buttonName, Number buttonWidth, Number buttonHeight) -> Bool state
fn imguiText(String text)
fn imguiTextMultiline(String textFieldName, String text, Number textFieldWidth, Number textFieldHeight) -> Bool state
fn imguiInputText(String textFieldName, Number outPointerToString, Number outPointerToStringBytesFirst, Number outPointerToStringBytesCountMax) -> Bool state
fn imguiInputTextMultiline(String textFieldName, Number outPointerToString, Number outPointerToStringBytesFirst, Number outPointerToStringBytesCountMax, Number textFieldWidth, Number textFieldHeight) -> Bool state
fn profileBegin(String mark)
fn profileEnd(String mark)
fn systemCommand(String command) -> String output
fn glGetIntegerv(Number enum, Number outPointer, Number outPointerBytesFirst) -> Bool success
fn githubR_lyehLz4xEncode(Number pointer, Number pointerBytesFirst, Number pointerBytesCount, Number outPointer, Number outPointerBytesFirst, Number outPointerBytesCount, Number flags) -> Number value
fn githubR_lyehLz4xDecode(Number pointer, Number pointerBytesFirst, Number pointerBytesCount, Number outPointer, Number outPointerBytesFirst, Number outPointerBytesCount) -> Number value
fn githubR_lyehLz4xBoundsEncodeOutBytesCount(Number bytesCount, Number flags) -> Number value
fn githubR_lyehUlzEncode(Number pointer, Number pointerBytesFirst, Number pointerBytesCount, Number outPointer, Number outPointerBytesFirst, Number outPointerBytesCount, Number flags) -> Number value
fn githubR_lyehUlzDecode(Number pointer, Number pointerBytesFirst, Number pointerBytesCount, Number outPointer, Number outPointerBytesFirst, Number outPointerBytesCount) -> Number value
fn githubR_lyehUlzBoundsEncodeOutBytesCount(Number bytesCount, Number flags) -> Number value
fn thread2Run()
fn thread2StopAndWaitFor()
fn thread2IsRunning() -> Bool isRunning
fn getGameScriptString() -> String script
fn setGameScriptStringForNextFrame(String string)
fn setGameScriptStringForNextFrameFromPointer(Number pointer, Number pointerBytesFirst)
fn getThread2ScriptString() -> String script
fn setThread2ScriptStringForNextFrame(String string)
fn setThread2ScriptStringForNextFrameFromPointer(Number pointer, Number pointerBytesFirst)
fn libGameScriptExternalProcedureReload(Bool printErrors)
fn libGameScriptExternalProcedureCall2(Number parameter1, Number parameter2)
fn libGameScriptExternalProcedureCall3(Number parameter1, Number parameter2, Number parameter3)
fn programGetArgumentsCount() -> Number argumentsCount
fn programGetArgument(Number index) -> String argument
fn programClose()
```

List of constants
-----------------

```javascript
let DEFAULT_CAMERA_SET_PROJECTION_MODE_PERSPECTIVE  = 0;
let DEFAULT_CAMERA_SET_PROJECTION_MODE_ORTHOGRAPHIC = 1;

let BLEND_MODE_ENABLE_ALPHA    = 1;
let BLEND_MODE_ENABLE_ADD      = 2;
let BLEND_MODE_ENABLE_SUBTRACT = 3;
let BLEND_MODE_ENABLE_MULTIPLY = 4;
let BLEND_MODE_ENABLE_SCREEN   = 5;

let CULLING_ENABLE_BACK  = 0;
let CULLING_ENABLE_FRONT = 1;

let KEYBOARD_GET_GLFW_KEY_EVENT_NONE     = 0;
let KEYBOARD_GET_GLFW_KEY_EVENT_PRESSED  = 1;
let KEYBOARD_GET_GLFW_KEY_EVENT_RELEASED = 2;

let MOUSE_GLFW_SET_INPUT_MODE_NORMAL   = 0;
let MOUSE_GLFW_SET_INPUT_MODE_HIDDEN   = 1;
let MOUSE_GLFW_SET_INPUT_MODE_DISABLED = 2;

let MOUSE_GET_MOVE_EVENT_NONE     = 0;
let MOUSE_GET_MOVE_EVENT_MOVED    = 2;
let MOUSE_GET_MOVE_EVENT_DRAGGED  = 4;
let MOUSE_GET_MOVE_EVENT_ENTERED  = 6;
let MOUSE_GET_MOVE_EVENT_EXITED   = 7;

let GAMEPAD_BUTTON_A            = 0;
let GAMEPAD_BUTTON_B            = 1;
let GAMEPAD_BUTTON_X            = 2;
let GAMEPAD_BUTTON_Y            = 3;
let GAMEPAD_BUTTON_LEFT_BUMPER  = 4;
let GAMEPAD_BUTTON_RIGHT_BUMPER = 5;
let GAMEPAD_BUTTON_BACK         = 6;
let GAMEPAD_BUTTON_START        = 7;
let GAMEPAD_BUTTON_GUIDE        = 8;
let GAMEPAD_BUTTON_LEFT_THUMB   = 9;
let GAMEPAD_BUTTON_RIGHT_THUMB  = 10;
let GAMEPAD_BUTTON_DPAD_UP      = 11;
let GAMEPAD_BUTTON_DPAD_RIGHT   = 12;
let GAMEPAD_BUTTON_DPAD_DOWN    = 13;
let GAMEPAD_BUTTON_DPAD_LEFT    = 14;
let GAMEPAD_AXIS_LEFT_X         = 15;
let GAMEPAD_AXIS_LEFT_Y         = 16;
let GAMEPAD_AXIS_RIGHT_X        = 17;
let GAMEPAD_AXIS_RIGHT_Y        = 18;
let GAMEPAD_AXIS_LEFT_TRIGGER   = 19;
let GAMEPAD_AXIS_RIGHT_TRIGGER  = 20;

let GIZMO_SET_MODE_NONE        = 0;
let GIZMO_SET_MODE_TRANSLATION = 1;
let GIZMO_SET_MODE_ROTATION    = 2;
let GIZMO_SET_MODE_SCALE       = 3;

let MESH_DRAW_RENDER_MODE_FILL      = 0;
let MESH_DRAW_RENDER_MODE_WIREFRAME = 1;
let MESH_DRAW_RENDER_MODE_POINTS    = 2;

let IMAGE_GET_IMAGE_TYPE_GRAYSCALE        = 0;
let IMAGE_GET_IMAGE_TYPE_COLOR_RGB        = 1;
let IMAGE_GET_IMAGE_TYPE_COLOR_ALPHA_RGBA = 2;
let IMAGE_GET_IMAGE_TYPE_UNDEFINED        = 3;
```

List of available script functions of thread 2
----------------------------------------------

```javascript
fn getCurrentFrameThread2() -> Number frameOfThread2
fn setCurrentFrameThread2(Number frameOfThread2)
fn printConsole(String string) // Thread-safe.
fn getExeDirectoryPath() -> String path // Thread-safe.
fn globalSharedArrayPersistentNew8Bit(String label, Number count) -> Number pointer // Thread-safe.
fn globalSharedArrayPersistentGetBytesCount(String label) -> Number bytesCount // Thread-safe.
fn globalSharedArrayPersistentGetPointer(String label) -> Number pointer // Thread-safe.
fn pointerGetBool(Number pointerTo8BitBools, Number index) -> Bool value
fn pointerGetString(Number pointer) -> String string
fn pointerGetSubstring(Number pointer, Number pointerCharsFirst, Number charsCount) -> String string
fn pointerGetNumber(Number pointerTo32BitFloats, Number index) -> Number value
fn pointerGetInteger(Number pointerTo32BitInts, Number index) -> Number value
fn pointerGetUnsignedInteger(Number pointerTo32BitUints, Number index) -> Number value
fn pointerGetUnsignedInteger8Bit(Number pointerTo8BitUints, Number index) -> Number value
fn pointerSetBool(Number pointerTo8BitBools, Number index, Bool value)
fn pointerSetString(Number pointer, Number pointerCharsFirst, String string)
fn pointerSetStringExcludingNullChar(Number pointer, Number pointerCharsFirst, String string)
fn pointerSetSubstring(Number pointer, Number pointerCharsFirst, String string, Number stringCharsFirst, Number stringCharsCount)
fn pointerSetNumber(Number pointerTo32BitFloats, Number index, Number value)
fn pointerSetInteger(Number pointerTo32BitInts, Number index, Number value)
fn pointerSetUnsignedInteger(Number pointerTo32BitUints, Number index, Number value)
fn pointerSetUnsignedInteger8Bit(Number pointerTo8BitUints, Number index, Number value)
fn pointerGetRaw8Bit(Number pointer, Number bytesFirst) -> Number raw8BitsAsDouble
fn pointerGetRaw16Bit(Number pointer, Number bytesFirst) -> Number raw16BitsAsDouble
fn pointerGetRaw32Bit(Number pointer, Number bytesFirst) -> Number raw32BitsAsDouble
fn pointerGetRaw64Bit(Number pointer, Number bytesFirst) -> Number raw64BitsAsDouble
fn pointerSetRaw8Bit(Number pointer, Number bytesFirst, Number raw8BitsAsDouble)
fn pointerSetRaw16Bit(Number pointer, Number bytesFirst, Number raw16BitsAsDouble)
fn pointerSetRaw32Bit(Number pointer, Number bytesFirst, Number raw32BitsAsDouble)
fn pointerSetRaw64Bit(Number pointer, Number bytesFirst, Number raw64BitsAsDouble)
fn memset(Number pointer, Number pointerBytesFirst, Number value8Bit, Number bytesCount)
fn memcpy(Number pointerTarget, Number pointerTargetBytesFirst, Number pointerSource, Number pointerSourceBytesFirst, Number bytesCount)
fn memcmp(Number pointerA, Number pointerABytesFirst, Number pointerB, Number pointerBBytesFirst, Number bytesCount) -> Bool areEqual
fn threadSafeMemset(Number pointer, Number pointerBytesFirst, Number value8Bit, Number bytesCount) // Thread-safe memory.
fn threadSafeMemcpy(Number pointerTarget, Number pointerTargetBytesFirst, Number pointerSource, Number pointerSourceBytesFirst, Number bytesCount) // Thread-safe memory.
fn threadSafeMemcmp(Number pointerA, Number pointerABytesFirst, Number pointerB, Number pointerBBytesFirst, Number bytesCount) -> Bool areEqual // Thread-safe memory.
fn threadWaitForEqualUint64Value(Number pointerA, Number pointerABytesFirst, Number pointerB, Number pointerBBytesFirst) -> Bool trueIfFinishedFalseIfAborted // Thread-safe memory.
fn threadWaitForEqualOrMoreThanUint64Value(Number pointerA, Number pointerABytesFirst, Number pointerB, Number pointerBBytesFirst) -> Bool trueIfFinishedFalseIfAborted // Thread-safe memory.
fn threadWaitForThread1FrameToFinish(Number thread1Frame) -> Bool trueIfFinishedFalseIfAborted
fn strlenWithNullChar(String string) -> Number length
fn boolToNumber(Bool boolean) -> Number number
fn boolToString(Bool boolean) -> String string
fn numberToBool(Number number) -> Bool boolean
fn numberToString(Number number) -> String string
fn numberToBinaryString(Number number) -> String string
fn numberWholePartToString(Number number) -> String string
fn stringCharToNumber(String string) -> Number charNumber
fn stringToNumberArray(String string) -> Number array []
fn interpretStringToInteger(String string) -> Number integer
fn interpretStringToFloat(String string) -> Number float
fn interpretStringToDouble(String string) -> Number double
fn stringReadFromFile(String filepath) -> String string
fn stringWriteToFile(String string, String filepath)
fn stringAppendToFile(String string, String filepath)
fn binaryGetByteSizeOfFile(String filepath) -> Number bytesCount
fn binaryReadFromFile(String filepath, Number writeToPointer, Number writeToPointerBytesFirst)
fn binaryWriteToFile(Number pointer, Number pointerBytesFirst, Number pointerBytesCount, String writeToFilepath)
fn meshGetVerticesCount(Number handle) -> Number count // Two threads must not access the same mesh handle at the same time.
fn meshGetColorsCount(Number handle) -> Number count // Two threads must not access the same mesh handle at the same time.
fn meshGetTexCoordsCount(Number handle) -> Number count // Two threads must not access the same mesh handle at the same time.
fn meshGetIndicesCount(Number handle) -> Number count // Two threads must not access the same mesh handle at the same time.
fn meshAddVertex(Number handle, Number x, Number y, Number z) // Two threads must not access the same mesh handle at the same time.
fn meshAddColor(Number handle, Number r0to1, Number g0to1, Number b0to1, Number a0to1) // Two threads must not access the same mesh handle at the same time.
fn meshAddTexCoord(Number handle, Number u, Number v) // Two threads must not access the same mesh handle at the same time.
fn meshAddIndex(Number handle, Number index) // Two threads must not access the same mesh handle at the same time.
fn meshRemoveVertex(Number handle, Number index) // Two threads must not access the same mesh handle at the same time.
fn meshRemoveColor(Number handle, Number index) // Two threads must not access the same mesh handle at the same time.
fn meshRemoveTexCoord(Number handle, Number index) // Two threads must not access the same mesh handle at the same time.
fn meshRemoveIndex(Number handle, Number index) // Two threads must not access the same mesh handle at the same time.
fn meshClear(Number handle) // Two threads must not access the same mesh handle at the same time.
fn meshClearVertices(Number handle) // Two threads must not access the same mesh handle at the same time.
fn meshClearColors(Number handle) // Two threads must not access the same mesh handle at the same time.
fn meshClearTexCoords(Number handle) // Two threads must not access the same mesh handle at the same time.
fn meshClearIndices(Number handle) // Two threads must not access the same mesh handle at the same time.
fn meshGetVerticesPointer(Number handle) -> Number pointer // Two threads must not access the same mesh handle at the same time.
fn meshGetColorsPointer(Number handle) -> Number pointer // Two threads must not access the same mesh handle at the same time.
fn meshGetTexCoordsPointer(Number handle) -> Number pointer // Two threads must not access the same mesh handle at the same time.
fn meshGetIndicesPointer(Number handle) -> Number pointer // Two threads must not access the same mesh handle at the same time.
fn meshMergeDuplicateVertices(Number handle) // Two threads must not access the same mesh handle at the same time.
fn meshSetupIndicesAuto(Number handle) // Two threads must not access the same mesh handle at the same time.
fn meshAddTriangle(Number handle, Number verticesArrayIndex1, Number verticesArrayIndex2, Number verticesArrayIndex3) // Two threads must not access the same mesh handle at the same time.
fn imageGetWidth(Number handle) -> Number width // Two threads must not access the same image handle at the same time.
fn imageGetHeight(Number handle) -> Number height // Two threads must not access the same image handle at the same time.
fn imageGetBitsPerPixel(Number handle) -> Number bitsPerPixel // Two threads must not access the same image handle at the same time.
fn imageGetImageType(Number handle) -> Number imageType // Two threads must not access the same image handle at the same time.
fn imageGetPixelsPointer(Number handle) -> Number pointerToPixels // Two threads must not access the same image handle at the same time.
fn profileBegin(String mark) // Thread-safe.
fn profileEnd(String mark) // Thread-safe.
fn systemCommand(String command) -> String output
fn githubR_lyehLz4xEncode(Number pointer, Number pointerBytesFirst, Number pointerBytesCount, Number outPointer, Number outPointerBytesFirst, Number outPointerBytesCount, Number flags) -> Number value
fn githubR_lyehLz4xDecode(Number pointer, Number pointerBytesFirst, Number pointerBytesCount, Number outPointer, Number outPointerBytesFirst, Number outPointerBytesCount) -> Number value
fn githubR_lyehLz4xBoundsEncodeOutBytesCount(Number bytesCount, Number flags) -> Number value
fn githubR_lyehUlzEncode(Number pointer, Number pointerBytesFirst, Number pointerBytesCount, Number outPointer, Number outPointerBytesFirst, Number outPointerBytesCount, Number flags) -> Number value
fn githubR_lyehUlzDecode(Number pointer, Number pointerBytesFirst, Number pointerBytesCount, Number outPointer, Number outPointerBytesFirst, Number outPointerBytesCount) -> Number value
fn githubR_lyehUlzBoundsEncodeOutBytesCount(Number bytesCount, Number flags) -> Number value
fn getThread2ScriptString() -> String script
fn setThread2ScriptStringForNextFrame(String string)
fn setThread2ScriptStringForNextFrameFromPointer(Number pointer, Number pointerBytesFirst)
fn libGameScriptExternalProcedureCall2(Number parameter1, Number parameter2)
fn libGameScriptExternalProcedureCall3(Number parameter1, Number parameter2, Number parameter3)
```

[Game Script](https://procedural.itch.io/gamescript) uses the Ape programming language v0.14.0 by Krzysztof Gabis, you can read more about it in my public fork of his Github repo here: https://github.com/procedural/script

[Game Script Native](https://procedural.itch.io/gamescriptnative) uses standard C++14.

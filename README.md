# Game Script

![game_script_screenshot](https://user-images.githubusercontent.com/28234322/141370424-192f786b-2ea2-4ae0-91a2-e0b2333a0edb.png)

![game_script_ray tracing screenshot](https://user-images.githubusercontent.com/28234322/147890504-471ad97d-9e3a-43f3-83b0-3c4aaab883c2.png)

# Download here: [procedural.itch.io/gamescript](https://procedural.itch.io/gamescript)

## Join the official Game Script Discord server for news, updates, code examples and more! https://discord.gg/D7pKPw4kFf

## Alternative news channel: https://t.me/gamescriptnative

Game Script is about raising the standards of what it's like to write code fast: you must be able to just double click on the program and start typing code immediately, you must be able to run the code with a single key press, and you must be able to enter the game mode, in which you can fly around in 3D space freely, like in a video game, to see your commands reliably occupy the virtual world.

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
* `F1`: run system script.
* `F2`: toggle rerun output text window.

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
fn defaultCameraGetProjectionMatrix(Number outPointer)
fn defaultCameraGetModelViewMatrix(Number outPointer)
fn defaultCameraGetModelViewProjectionMatrix(Number outPointer)
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
fn pointerGetInteger8Bit(Number pointerTo8BitInts, Number index) -> Number value
fn pointerGetUnsignedInteger8Bit(Number pointerTo8BitUints, Number index) -> Number value
fn pointerGetAtOffsetNumber(Number pointer, Number bytesFirst) -> Number value
fn pointerGetAtOffsetInteger(Number pointer, Number bytesFirst) -> Number value
fn pointerGetAtOffsetUnsignedInteger(Number pointer, Number bytesFirst) -> Number value
fn pointerGetAtOffsetInteger16Bit(Number pointer, Number bytesFirst) -> Number value
fn pointerGetAtOffsetUnsignedInteger16Bit(Number pointer, Number bytesFirst) -> Number value
fn pointerGetAtOffsetNumber64Bit(Number pointer, Number bytesFirst) -> Number value
fn pointerGetAtOffsetInteger64Bit(Number pointer, Number bytesFirst) -> Number value
fn pointerGetAtOffsetUnsignedInteger64Bit(Number pointer, Number bytesFirst) -> Number value
fn pointerSetBool(Number pointerTo8BitBools, Number index, Bool value)
fn pointerSetString(Number pointer, Number pointerCharsFirst, String string)
fn pointerSetStringExcludingNullChar(Number pointer, Number pointerCharsFirst, String string)
fn pointerSetSubstring(Number pointer, Number pointerCharsFirst, String string, Number stringCharsFirst, Number stringCharsCount)
fn pointerSetNumber(Number pointerTo32BitFloats, Number index, Number value)
fn pointerSetInteger(Number pointerTo32BitInts, Number index, Number value)
fn pointerSetUnsignedInteger(Number pointerTo32BitUints, Number index, Number value)
fn pointerSetInteger8Bit(Number pointerTo8BitInts, Number index, Number value)
fn pointerSetUnsignedInteger8Bit(Number pointerTo8BitUints, Number index, Number value)
fn pointerSetAtOffsetNumber(Number pointer, Number bytesFirst, Number value)
fn pointerSetAtOffsetInteger(Number pointer, Number bytesFirst, Number value)
fn pointerSetAtOffsetUnsignedInteger(Number pointer, Number bytesFirst, Number value)
fn pointerSetAtOffsetInteger16Bit(Number pointer, Number bytesFirst, Number value)
fn pointerSetAtOffsetUnsignedInteger16Bit(Number pointer, Number bytesFirst, Number value)
fn pointerSetAtOffsetNumber64Bit(Number pointer, Number bytesFirst, Number value)
fn pointerSetAtOffsetInteger64Bit(Number pointer, Number bytesFirst, Number value)
fn pointerSetAtOffsetUnsignedInteger64Bit(Number pointer, Number bytesFirst, Number value)
fn pointerGetRaw8Bit(Number pointer, Number bytesFirst) -> Number raw8BitsAsDouble
fn pointerGetRaw16Bit(Number pointer, Number bytesFirst) -> Number raw16BitsAsDouble
fn pointerGetRaw32Bit(Number pointer, Number bytesFirst) -> Number raw32BitsAsDouble
fn pointerGetRaw64Bit(Number pointer, Number bytesFirst) -> Number raw64BitsAsDouble
fn pointerSetRaw8Bit(Number pointer, Number bytesFirst, Number raw8BitsAsDouble)
fn pointerSetRaw16Bit(Number pointer, Number bytesFirst, Number raw16BitsAsDouble)
fn pointerSetRaw32Bit(Number pointer, Number bytesFirst, Number raw32BitsAsDouble)
fn pointerSetRaw64Bit(Number pointer, Number bytesFirst, Number raw64BitsAsDouble)
fn pointerIsNull(Number pointer) -> Bool isNull
fn pointerGetNull() -> Number nullPointer
fn pointersAreEqual(Number pointerA, Number pointerB) -> Bool areEqual
fn pointerOffsetByBytes(Number pointer, Number bytesOffset) -> Number offsettedPointer
fn pointerDrawPixels(Number pointer, Number pointerBytesOffset, Number pixelsWidth, Number pixelsHeight, Number pixelsFormat, Number pixelsType) -> Bool success // Works only with --enable-opengl21 command line flag enabled.
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
fn numberFromRaw8BitInteger(Number raw8BitInteger) -> Number number
fn numberFromRaw8BitUnsignedInteger(Number raw8BitUnsignedInteger) -> Number number
fn numberFromRaw16BitInteger(Number raw16BitInteger) -> Number number
fn numberFromRaw16BitUnsignedInteger(Number raw16BitUnsignedInteger) -> Number number
fn numberFromRaw32BitInteger(Number raw32BitInteger) -> Number number
fn numberFromRaw32BitUnsignedInteger(Number raw32BitUnsignedInteger) -> Number number
fn numberFromRaw32BitFloat(Number raw32BitFloat) -> Number number
fn numberFromRaw64BitInteger(Number raw64BitInteger) -> Number number
fn numberFromRaw64BitUnsignedInteger(Number raw64BitUnsignedInteger) -> Number number
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
fn framebufferBegin(String label, Number width, Number height, Bool setupScreenDefaultIsTrue) -> Bool framebufferIsValid
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
fn meshDrawWithColor(Number handle, Number renderMode, Number scaleX, Number scaleY, Number scaleZ, Number vectorX, Number vectorY, Number vectorZ, Number rotationAxisX, Number rotationAxisY, Number rotationAxisZ, Number rotationAngleDeg, Number r0to255, Number g0to255, Number b0to255, Number a0to255)
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
fn imageHasMipmap(Number handle) -> Bool hasMipmap
fn imageMipmapDisable(Number handle)
fn imageMipmapEnable(Number handle)
fn imageMipmapGenerate(Number handle)
fn imageSetTextureMinMagFilter(Number handle, Number minFilter, Number magFilter)
fn imageSetTextureWrap(Number handle, Number wrapX, Number wrapY)
fn imageSetTextureMaxAnisotropy(Number handle, Number maxAnisotropy)
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
fn imageDraw(Number handle, Number x, Number y, Number z, Number w, Number h)
fn imageDrawSubsection(Number handle, Number x, Number y, Number z, Number w, Number h, Number sx, Number sy, Number sw, Number sh)
fn shaderBegin(String label, String filepathShaderVert, String filepathShaderFrag) -> Bool shadersAreValid
fn shaderEnd(String label)
fn shaderSetUniform4f(String label, String uniformName, Number x, Number y, Number z, Number w)
fn shaderSetUniform4fv(String label, String uniformName, Number pointer, Number count)
fn shaderSetUniformMatrix4f(String label, String uniformName, Number pointer)
fn shaderSetUniformImage(String label, String uniformName, Number imageHandle, Number textureLocation)
fn shaderDelete(String label)
fn shaderDeleteAll()
fn soundPlayerNew(String label) -> Number handle
fn soundPlayerPersistentNew(String label) -> Number handle
fn soundPlayerDelete(String label)
fn soundPlayerPersistentDelete(String label)
fn soundPlayerDeleteAll()
fn soundPlayerPersistentDeleteAll()
fn soundPlayerGetHandle(String label) -> Number handle
fn soundPlayerPersistentGetHandle(String label) -> Number handle
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
fn getUniqueNumber() -> Number uniqueNumber
fn getUint64Max() -> Number uint64Max
fn getLibGameHandle() -> Number handle
fn getLibThread2Handle() -> Number handle
fn getGlfwWindowHandle() -> Number handle
fn getLastDragAndDropCounter() -> Number counter
fn getLastDragAndDropFilepathsCount() -> Number count
fn getLastDragAndDropFilepath(Number index) -> String filepath
fn getLastDragAndDropPositionX() -> Number x
fn getLastDragAndDropPositionY() -> Number y
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
fn globalMeshesGetCount() -> Number count
fn globalMeshesPersistentGetCount() -> Number count
fn globalMeshesGetMeshLabelByMeshIndex(Number index) -> String label
fn globalMeshesPersistentGetMeshLabelByMeshIndex(Number index) -> String label
fn globalMeshesGetMeshHandleByMeshIndex(Number index) -> Number handle
fn globalMeshesPersistentGetMeshHandleByMeshIndex(Number index) -> Number handle
fn globalMeshesGetHaveVerticesChangedMeshIndexesCount() -> Number count
fn globalMeshesGetHaveColorsChangedMeshIndexesCount() -> Number count
fn globalMeshesGetHaveTexCoordsChangedMeshIndexesCount() -> Number count
fn globalMeshesGetHaveIndicesChangedMeshIndexesCount() -> Number count
fn globalMeshesPersistentGetHaveVerticesChangedMeshIndexesCount() -> Number count
fn globalMeshesPersistentGetHaveColorsChangedMeshIndexesCount() -> Number count
fn globalMeshesPersistentGetHaveTexCoordsChangedMeshIndexesCount() -> Number count
fn globalMeshesPersistentGetHaveIndicesChangedMeshIndexesCount() -> Number count
fn globalMeshesGetHaveVerticesChangedMeshIndexes(Number count) -> Number indexes []
fn globalMeshesGetHaveColorsChangedMeshIndexes(Number count) -> Number indexes []
fn globalMeshesGetHaveTexCoordsChangedMeshIndexes(Number count) -> Number indexes []
fn globalMeshesGetHaveIndicesChangedMeshIndexes(Number count) -> Number indexes []
fn globalMeshesPersistentGetHaveVerticesChangedMeshIndexes(Number count) -> Number indexes []
fn globalMeshesPersistentGetHaveColorsChangedMeshIndexes(Number count) -> Number indexes []
fn globalMeshesPersistentGetHaveTexCoordsChangedMeshIndexes(Number count) -> Number indexes []
fn globalMeshesPersistentGetHaveIndicesChangedMeshIndexes(Number count) -> Number indexes []
fn globalKeyPropertyGetKeyLabelsCount() -> Number count
fn globalKeyPropertyIsKeyLabelExists(String key) -> Bool exists
fn globalKeyPropertyGetKeyLabelByKeyIndex(Number index) -> String label
fn globalKeyPropertyGetKeyPropertyLabelsCount(String key) -> Number count
fn globalKeyPropertyIsKeyPropertyLabelExists(String key, String property) -> Bool exists
fn globalKeyPropertyGetKeyPropertyLabelByPropertyIndex(String key, Number index) -> String label
fn globalKeyPropertyRemoveKey(String key)
fn globalKeyPropertyRemoveAllKeys()
fn globalKeyPropertyRemoveProperty(String key, String property)
fn globalKeyPropertyRemoveAllProperties(String key)
fn globalKeyPropertySetString(String key, String property, String value)
fn globalKeyPropertySetNumber(String key, String property, Number value)
fn globalKeyPropertySetBool(String key, String property, Bool value)
fn globalKeyPropertyGetString(String key, String property) -> String value
fn globalKeyPropertyGetNumber(String key, String property) -> Number value
fn globalKeyPropertyGetBool(String key, String property) -> Bool value
fn ertAffineSpace3fGetSizeOfInBytes() -> Number sizeOfInBytes
fn ertAffineSpace3fSetDefaultInitialize(Number outPointer, Number outPointerBytesFirst)
fn ertAffineSpace3fSetInitialize(Number outPointer, Number outPointerBytesFirst, Number v0, Number v1, Number v2, Number v3, Number v4, Number v5, Number v6, Number v7, Number v8, Number v9, Number v10, Number v11)
fn ertAffineSpace3fSetLookAtPoint(Number outPointer, Number outPointerBytesFirst, Number posX, Number posY, Number posZ, Number targetX, Number targetY, Number targetZ, Number upX, Number upY, Number upZ)
fn ertAffineSpace3fScale(Number outPointer, Number outPointerBytesFirst, Number scaleX, Number scaleY, Number scaleZ)
fn ertAffineSpace3fTranslate(Number outPointer, Number outPointerBytesFirst, Number translateX, Number translateY, Number translateZ)
fn ertAffineSpace3fRotate(Number outPointer, Number outPointerBytesFirst, Number rotatePosX, Number rotatePosY, Number rotatePosZ, Number rotateAxisX, Number rotateAxisY, Number rotateAxisZ, Number rotateAngle)
fn ertAffineSpace3fGetLVXX(Number pointer, Number pointerBytesFirst) -> Number l_vx_x
fn ertAffineSpace3fGetLVXY(Number pointer, Number pointerBytesFirst) -> Number l_vx_y
fn ertAffineSpace3fGetLVXZ(Number pointer, Number pointerBytesFirst) -> Number l_vx_z
fn ertAffineSpace3fGetLVYX(Number pointer, Number pointerBytesFirst) -> Number l_vy_x
fn ertAffineSpace3fGetLVYY(Number pointer, Number pointerBytesFirst) -> Number l_vy_y
fn ertAffineSpace3fGetLVYZ(Number pointer, Number pointerBytesFirst) -> Number l_vy_z
fn ertAffineSpace3fGetLVZX(Number pointer, Number pointerBytesFirst) -> Number l_vz_x
fn ertAffineSpace3fGetLVZY(Number pointer, Number pointerBytesFirst) -> Number l_vz_y
fn ertAffineSpace3fGetLVZZ(Number pointer, Number pointerBytesFirst) -> Number l_vz_z
fn ertAffineSpace3fGetPX(Number pointer, Number pointerBytesFirst) -> Number p_x
fn ertAffineSpace3fGetPY(Number pointer, Number pointerBytesFirst) -> Number p_y
fn ertAffineSpace3fGetPZ(Number pointer, Number pointerBytesFirst) -> Number p_z
fn ertAffineSpace3fCopyFromArray(Number in12FloatsPointer, Number in12FloatsPointerBytesFirst, Number outAffineSpace3fPointer, Number outAffineSpace3fPointerBytesFirst)
fn ertAffineSpace3fCopyToArray(Number inAffineSpace3fPointer, Number inAffineSpace3fPointerBytesFirst, Number out12FloatsPointer, Number out12FloatsPointerBytesFirst)
fn ertCreateDevice(String typeDefaultIsdefault, Number numThreadsDefaultIs0) -> Number deviceHandle
fn ertDestroyDevice(Number deviceHandle)
fn ertNewCamera(Number deviceHandle, String type) -> Number cameraHandle
fn ertNewData(Number deviceHandle, String type, Number bytes, Number dataPointer, Number dataPointerBytesFirst) -> Number dataHandle
fn ertNewDataFromFile(Number deviceHandle, String type, String file, Number offset, Number bytes) -> Number dataHandle
fn ertNewImage(Number deviceHandle, String type, Number width, Number height, Number dataPointer, Number dataPointerBytesFirst) -> Number imageHandle
fn ertNewImageFromFile(Number deviceHandle, String file) -> Number imageHandle
fn ertNewTexture(Number deviceHandle, String type) -> Number textureHandle
fn ertNewMaterial(Number deviceHandle, String type) -> Number materialHandle
fn ertNewShape(Number deviceHandle, String type) -> Number shapeHandle
fn ertNewLight(Number deviceHandle, String type) -> Number lightHandle
fn ertNewShapePrimitive(Number deviceHandle, Number shapeHandle, Number materialHandle, Number transformPointer, Number transformPointerBytesFirst) -> Number primitiveHandle
fn ertNewLightPrimitive(Number deviceHandle, Number lightHandle, Number transformPointer, Number transformPointerBytesFirst) -> Number primitiveHandle
fn ertTransformPrimitive(Number deviceHandle, Number primitiveHandle, Number transformPointer, Number transformPointerBytesFirst) -> Number primitiveHandle
fn ertNewScene(Number deviceHandle, String type, Number primitiveHandlesPointer, Number primitiveHandlesPointerBytesFirst, Number size) -> Number sceneHandle
fn ertNewToneMapper(Number deviceHandle, String type) -> Number toneMapperHandle
fn ertNewRenderer(Number deviceHandle, String type) -> Number rendererHandle
fn ertNewFrameBuffer(Number deviceHandle, String type, Number width, Number height, Number buffersDefaultIs1) -> Number frameBufferHandle
fn ertGetFrameBufferWidth(Number deviceHandle, Number frameBufferHandle) -> Number width
fn ertGetFrameBufferHeight(Number deviceHandle, Number frameBufferHandle) -> Number height
fn ertMapFrameBuffer(Number deviceHandle, Number frameBufferHandle) -> Number pointer
fn ertUnmapFrameBuffer(Number deviceHandle, Number frameBufferHandle)
fn ertSwapBuffers(Number deviceHandle, Number frameBufferHandle)
fn ertIncRef(Number deviceHandle, Number handle)
fn ertDecRef(Number deviceHandle, Number handle)
fn ertSetBool1(Number deviceHandle, Number handle, String property, Bool x)
fn ertSetBool2(Number deviceHandle, Number handle, String property, Bool x, Bool y)
fn ertSetBool3(Number deviceHandle, Number handle, String property, Bool x, Bool y, Bool z)
fn ertSetBool4(Number deviceHandle, Number handle, String property, Bool x, Bool y, Bool z, Bool w)
fn ertSetInt1(Number deviceHandle, Number handle, String property, Number x)
fn ertSetInt2(Number deviceHandle, Number handle, String property, Number x, Number y)
fn ertSetInt3(Number deviceHandle, Number handle, String property, Number x, Number y, Number z)
fn ertSetInt4(Number deviceHandle, Number handle, String property, Number x, Number y, Number z, Number w)
fn ertSetFloat1(Number deviceHandle, Number handle, String property, Number x)
fn ertSetFloat2(Number deviceHandle, Number handle, String property, Number x, Number y)
fn ertSetFloat3(Number deviceHandle, Number handle, String property, Number x, Number y, Number z)
fn ertSetFloat4(Number deviceHandle, Number handle, String property, Number x, Number y, Number z, Number w)
fn ertSetArray(Number deviceHandle, Number handle, String property, String type, Number dataHandle, Number size, Number stride, Number ofs)
fn ertSetString(Number deviceHandle, Number handle, String property, String str)
fn ertSetImage(Number deviceHandle, Number handle, String property, Number imageHandle)
fn ertSetTexture(Number deviceHandle, Number handle, String property, Number textureHandle)
fn ertSetTransform(Number deviceHandle, Number handle, String property, Number transformPointer, Number transformPointerBytesFirst)
fn ertClear(Number deviceHandle, Number handle)
fn ertCommit(Number deviceHandle, Number handle)
fn ertRenderFrame(Number deviceHandle, Number rendererHandle, Number cameraHandle, Number sceneHandle, Number toneMapperHandle, Number frameBufferHandle, Number accumulate)
fn ertPick(Number deviceHandle, Number cameraHandle, Number x, Number y, Number sceneHandle) -> Number point [4] {x, y, z, isHit}
fn ertInitializeRayStruct(Number deviceHandle, Number orgX, Number orgY, Number orgZ, Number dirX, Number dirY, Number dirZ, Number nearDefaultIs0, Number farDefaultIsEmbreeInf, Number timeDefaultIs0, Number outRayStructPointer, Number outRayStructPointerBytesFirst)
fn ertInitializeRayStructForCameraPixelSample(Number deviceHandle, Number cameraHandle, Number pixelXFrom0To1, Number pixelYFrom0To1, Number pixelSamplePosXFrom0ToExcluded1DefaultIs0Point5, Number pixelSamplePosYFrom0ToExcluded1DefaultIs0Point5, Number outRayStructPointer, Number outRayStructPointerBytesFirst)
fn ertSceneIntersectRayStructToHitStruct(Number deviceHandle, Number sceneHandle, Number inRayStructPointer, Number inRayStructPointerBytesFirst, Number outHitStructPointer, Number outHitStructPointerBytesFirst)
fn onRerunCallErtDecRef(Number deviceHandle, Number handle)
fn onRerunCallErtDestroyDevice(Number deviceHandle)
fn getRedStructsCount() -> Number count // See structs of redgpu.h, redgpu_array_timestamp.h, redgpu_computing_language.h
fn getRedStructName(Number index) -> String name
fn getRedStructMembersCount() -> Number count
fn getRedStructMemberName(Number index) -> String name
fn redStructSizeof(String structName) -> Number bytesCount
fn redStructMemberSizeof(String structName, String structMemberName) -> Number bytesCount
fn redStructMemberOffsetof(String structName, String structMemberName) -> Number bytesFirst
fn redStructMemberTypeof(String structName, String structMemberName) -> Number structMemberType
fn redCreateContext(Bool enableDebugMode) -> Number context
fn redCreateContextWithRayTracingFeatureLevel1(Bool enableDebugMode) -> Number context
fn redCreateContextWithRayTracingFeatureLevel2(Bool enableDebugMode) -> Number context
fn redHandleContextGetProcAddr(Number contextHandle, String procedureName) -> Number address
fn redMemoryGetBudget(Number context, Number gpuHandle, Number outMemoryBudget, Number outStatuses)
fn redMemoryAllocate(Number context, Number gpuHandle, String handleName, Number bytesCount, Number memoryTypeIndex, Number dedicateToArray, Number dedicateToImage, Number memoryBitflags, Number outStatuses) -> Number memoryHandle
fn redMemoryAllocateMappable(Number context, Number gpuHandle, String handleName, Bool dedicate, Number array, Number arrayMemoryBytesCount, Number memoryTypeIndex, Number memoryBitflags, Number outStatuses) -> Number memoryHandle
fn redMemoryFree(Number context, Number gpuHandle, Number memory)
fn redMemorySet(Number context, Number gpuHandle, Number memoryArraysCount, Number memoryArrays, Number memoryImagesCount, Number memoryImages, Number outStatuses)
fn redMemoryMap(Number context, Number gpuHandle, Number mappableMemory, Number mappableMemoryBytesFirst, Number mappableMemoryBytesCount, Number outStatuses) -> Number pointer
fn redMemoryUnmap(Number context, Number gpuHandle, Number mappableMemory)
fn redMemoryNonCoherentFlush(Number context, Number gpuHandle, Number mappableMemoryRangesCount, Number mappableMemoryRanges, Number outStatuses)
fn redMemoryNonCoherentInvalidate(Number context, Number gpuHandle, Number mappableMemoryRangesCount, Number mappableMemoryRanges, Number outStatuses)
fn redStructsMemoryAllocate(Number context, Number gpuHandle, String handleName, Number maxStructsCount, Number maxStructsMembersOfTypeArrayROConstantCount, Number maxStructsMembersOfTypeArrayROOrArrayRWCount, Number maxStructsMembersOfTypeTextureROCount, Number maxStructsMembersOfTypeTextureRWCount, Number outStatuses) -> Number structsMemoryHandle
fn redStructsMemoryAllocateSamplers(Number context, Number gpuHandle, String handleName, Number maxStructsCount, Number maxStructsMembersOfTypeSamplerCount, Number outStatuses) -> Number structsMemoryHandle
fn redStructsMemorySuballocateStructs(Number context, Number gpuHandle, Number handleNames, Number structsMemory, Number structsDeclarationsCount, Number structsDeclarations, Number outStructs, Number outStatuses)
fn redStructsMemoryReset(Number context, Number gpuHandle, Number structsMemory, Number outStatuses)
fn redStructsMemoryFree(Number context, Number gpuHandle, Number structsMemory)
fn redStructsSet(Number context, Number gpuHandle, Number structsMembersCount, Number structsMembers)
fn redCreateArray(Number context, Number gpuHandle, String handleName, Number type, Number bytesCount, Number structuredBufferElementBytesCount, Number initialAccess, Number initialQueueFamilyIndex, Bool dedicate, Number outArray, Number outStatuses) -> Number arrayHandle
fn redCreateImage(Number context, Number gpuHandle, String handleName, Number dimensions, Number format, Number width, Number height, Number depth, Number levelsCount, Number layersCount, Number multisampleCount, Number restrictToAccess, Number initialAccess, Number initialQueueFamilyIndex, Bool dedicate, Number outImage, Number outStatuses) -> Number imageHandle
fn redCreateSampler(Number context, Number gpuHandle, String handleName, Number filteringMag, Number filteringMin, Number filteringMip, Number behaviorOutsideTextureCoordinateU, Number behaviorOutsideTextureCoordinateV, Number behaviorOutsideTextureCoordinateW, Number mipLodBias, Bool enableAnisotropy, Number maxAnisotropy, Bool enableCompare, Number compareOp, Number minLod, Number maxLod, Number outStatuses) -> Number samplerHandle
fn redCreateTexture(Number context, Number gpuHandle, String handleName, Number image, Number parts, Number dimensions, Number format, Number levelsFirst, Number levelsCount, Number layersFirst, Number layersCount, Number restrictToAccess, Number outStatuses) -> Number textureHandle
fn redCreateGpuCode(Number context, Number gpuHandle, String handleName, Number irBytesCount, Number ir, Number outStatuses) -> Number gpuCodeHandle
fn redCreateOutputDeclaration(Number context, Number gpuHandle, String handleName, Number outputDeclarationMembers, Number outputDeclarationMembersResolveSources, Bool dependencyByRegion, Bool dependencyByRegionAllowUsageAliasOrderBarriers, Number outStatuses) -> Number outputDeclarationHandle
fn redCreateStructDeclaration(Number context, Number gpuHandle, String handleName, Number structDeclarationMembersCount, Number structDeclarationMembers, Number structDeclarationMembersArrayROCount, Number structDeclarationMembersArrayRO, Bool procedureParametersHandlesDeclaration, Number outStatuses) -> Number structDeclarationHandle
fn redCreateProcedureParameters(Number context, Number gpuHandle, String handleName, Number procedureParametersDeclaration, Number outStatuses) -> Number procedureParametersHandle
fn redCreateProcedureCache(Number context, Number gpuHandle, String handleName, Number fromBlobBytesCount, Number fromBlob, Number outStatuses) -> Number procedureCacheHandle
fn redCreateProcedure(Number context, Number gpuHandle, String handleName, Number procedureCache, Number outputDeclaration, Number procedureParameters, String gpuCodeVertexMainProcedureName, Number gpuCodeVertex, String gpuCodeFragmentMainProcedureName, Number gpuCodeFragment, Number state, Number stateExtension, Bool deriveBase, Number deriveFrom, Number outStatuses) -> Number procedureHandle
fn redCreateProcedureCompute(Number context, Number gpuHandle, String handleName, Number procedureCache, Number procedureParameters, String gpuCodeMainProcedureName, Number gpuCode, Number outStatuses) -> Number procedureHandle
fn redCreateOutput(Number context, Number gpuHandle, String handleName, Number outputDeclaration, Number outputMembers, Number outputMembersResolveTargets, Number width, Number height, Number outOutput, Number outStatuses) -> Number outputHandle
fn redCreateCpuSignal(Number context, Number gpuHandle, String handleName, Bool createSignaled, Number outStatuses) -> Number cpuSignalHandle
fn redCreateGpuSignal(Number context, Number gpuHandle, String handleName, Number outStatuses) -> Number gpuSignalHandle
fn redCreateGpuToCpuSignal(Number context, Number gpuHandle, String handleName, Number outStatuses) -> Number gpuToCpuHandle
fn redCreateCalls(Number context, Number gpuHandle, String handleName, Number queueFamilyIndex, Number outCalls, Number outStatuses)
fn redCreateCallsReusable(Number context, Number gpuHandle, String handleName, Number queueFamilyIndex, Number outCalls, Number outStatuses)
fn redDestroyContext(Number context)
fn redDestroyArray(Number context, Number gpuHandle, Number array)
fn redDestroyImage(Number context, Number gpuHandle, Number image)
fn redDestroySampler(Number context, Number gpuHandle, Number sampler)
fn redDestroyTexture(Number context, Number gpuHandle, Number texture)
fn redDestroyGpuCode(Number context, Number gpuHandle, Number gpuCode)
fn redDestroyOutputDeclaration(Number context, Number gpuHandle, Number outputDeclaration)
fn redDestroyStructDeclaration(Number context, Number gpuHandle, Number structDeclaration)
fn redDestroyProcedureParameters(Number context, Number gpuHandle, Number procedureParameters)
fn redDestroyProcedureCache(Number context, Number gpuHandle, Number procedureCache)
fn redDestroyProcedure(Number context, Number gpuHandle, Number procedure)
fn redDestroyOutput(Number context, Number gpuHandle, Number output)
fn redDestroyCpuSignal(Number context, Number gpuHandle, Number cpuSignal)
fn redDestroyGpuSignal(Number context, Number gpuHandle, Number gpuSignal)
fn redDestroyGpuToCpuSignal(Number context, Number gpuHandle, Number gpuToCpuSignal)
fn redDestroyCalls(Number context, Number gpuHandle, Number calls, Number callsMemory)
fn redProcedureCacheGetBlob(Number context, Number gpuHandle, Number procedureCache, Number outBlobBytesCount, Number outBlob, Number outStatuses)
fn redProcedureCacheMergeCaches(Number context, Number gpuHandle, Number sourceProcedureCachesCount, Number sourceProcedureCaches, Number targetProcedureCache, Number outStatuses)
fn redCpuSignalGetStatus(Number context, Number gpuHandle, Number cpuSignal) -> Number status
fn redCpuSignalWait(Number context, Number gpuHandle, Number cpuSignalsCount, Number cpuSignals, Bool waitAll, Number outStatuses)
fn redCpuSignalUnsignal(Number context, Number gpuHandle, Number cpuSignalsCount, Number cpuSignals, Number outStatuses)
fn redGpuToCpuSignalGetStatus(Number context, Number gpuHandle, Number gpuToCpuSignal) -> Number status
fn redGpuToCpuSignalUnsignal(Number context, Number gpuHandle, Number gpuToCpuSignal, Number outStatuses)
fn redCallsSet(Number context, Number gpuHandle, Number calls, Number callsMemory, Bool callsReusable, Number outStatuses)
fn redCallsEnd(Number context, Number gpuHandle, Number calls, Number callsMemory, Number outStatuses)
fn redGetCallProceduresAndAddresses(Number context, Number gpuHandle, Number outCallProceduresAndAddresses, Number outStatuses)
fn redCallGpuToCpuSignalSignal(Number callProceduresAndAddresses, Number calls, Number signalGpuToCpuSignal, Number setTo8192)
fn redCallCopyArrayToArray(Number callProceduresAndAddresses, Number calls, Number arrayR, Number arrayW, Number rangesCount, Number ranges)
fn redCallCopyImageToImage(Number callProceduresAndAddresses, Number calls, Number imageR, Number setTo1, Number imageW, Number setTo01, Number rangesCount, Number ranges)
fn redCallCopyArrayToImage(Number callProceduresAndAddresses, Number calls, Number arrayR, Number imageW, Number setTo1, Number rangesCount, Number ranges)
fn redCallCopyImageToArray(Number callProceduresAndAddresses, Number calls, Number imageR, Number setTo1, Number arrayW, Number rangesCount, Number ranges)
fn redCallProcedure(Number callProceduresAndAddresses, Number calls, Number vertexCount, Number instanceCount, Number vertexFirst, Number instanceFirst)
fn redCallProcedureIndexed(Number callProceduresAndAddresses, Number calls, Number indexCount, Number instanceCount, Number indexFirst, Number vertexBase, Number instanceFirst)
fn redCallProcedureCompute(Number callProceduresAndAddresses, Number calls, Number workgroupsCountX, Number workgroupsCountY, Number workgroupsCountZ)
fn redCallSetProcedure(Number callProceduresAndAddresses, Number calls, Number procedureType, Number procedure)
fn redCallSetProcedureIndices(Number callProceduresAndAddresses, Number calls, Number array, Number setTo0, Number setTo1)
fn redCallSetProcedureParametersVariables(Number callProceduresAndAddresses, Number calls, Number procedureParameters, Number visibleToStages, Number variablesBytesFirst, Number dataBytesCount, Number data)
fn redCallSetProcedureParametersStructs(Number callProceduresAndAddresses, Number calls, Number procedureType, Number procedureParameters, Number procedureParametersDeclarationStructsDeclarationsFirst, Number structsCount, Number structs, Number setTo0, Number setTo00)
fn redCallSetProcedureParametersHandles(Number callProceduresAndAddresses, Number calls, Number procedureType, Number procedureParameters, Number procedureParametersDeclarationStructsDeclarationsCount, Number handlesCount, Number handles)
fn redCallSetDynamicDepthBias(Number callProceduresAndAddresses, Number calls, Number constantFactor, Number clamp, Number slopeFactor)
fn redCallSetDynamicDepthBounds(Number callProceduresAndAddresses, Number calls, Number min, Number max)
fn redCallSetDynamicStencilCompareMask(Number callProceduresAndAddresses, Number calls, Number face, Number compareMask)
fn redCallSetDynamicStencilWriteMask(Number callProceduresAndAddresses, Number calls, Number face, Number writeMask)
fn redCallSetDynamicStencilReference(Number callProceduresAndAddresses, Number calls, Number face, Number reference)
fn redCallSetDynamicBlendConstants(Number callProceduresAndAddresses, Number calls, Number blendConstants)
fn redCallSetDynamicViewport(Number callProceduresAndAddresses, Number calls, Number x, Number y, Number width, Number height, Number depthMin, Number depthMax)
fn redCallSetDynamicScissor(Number callProceduresAndAddresses, Number calls, Number x, Number y, Number width, Number height)
fn redCallSetStructsMemory(Number callProceduresAndAddresses, Number calls, Number structsMemory, Number structsMemorySamplers)
fn redCallSetProcedureParameters(Number callProceduresAndAddresses, Number calls, Number procedureType, Number procedureParameters)
fn redCallSetProcedureOutput(Number callProceduresAndAddresses, Number calls, Number outputDeclaration, Number output, Number inlineOutput, Number outputWidth, Number outputHeight, Bool outputDepthStencilEnable, Number outputColorsCount, Number depthClearValue, Number stencilClearValue, Number colorsClearValuesFloat, Number colorsClearValuesSint, Number colorsClearValuesUint)
fn redCallEndProcedureOutput(Number callProceduresAndAddresses, Number calls)
fn redCallUsageAliasOrderBarrier(Number callProceduresAndAddresses, Number calls, Number context, Number arrayUsagesCount, Number arrayUsages, Number imageUsagesCount, Number imageUsages, Number aliasesCount, Number aliases, Number ordersCount, Number orders, Bool dependencyByRegion)
fn redCallMark(Number callProceduresAndAddresses, Number calls, String mark)
fn redCallMarkSet(Number callProceduresAndAddresses, Number calls, String mark)
fn redCallMarkEnd(Number callProceduresAndAddresses, Number calls)
fn redQueueSubmit(Number context, Number gpuHandle, Number queue, Number timelinesCount, Number timelines, Number signalCpuSignal, Number outStatuses)
fn redMark(String mark)
fn redMarkSet(String mark)
fn redMarkEnd()
fn redCreateProcedureComputingLanguage(Number context, Number gpuHandle, String handleName, Number procedureCache, Number procedureParameters, String gpuCodeMainProcedureName, Number gpuCode, Number stateExtension, Number outStatuses) -> Number procedureHandle
fn redCreateArrayTimestamp(Number context, Number gpuHandle, String handleName, Number count, Number outStatuses) -> Number arrayTimestampHandle
fn redDestroyArrayTimestamp(Number context, Number gpuHandle, Number arrayTimestamp)
fn redCallArrayTimestampWrite(Number calls, Number context, Number arrayTimestamp, Number index)
fn redArrayTimestampRead(Number context, Number gpuHandle, Number arrayTimestamp, Number rangeFirst, Number rangeCount, Number out64BitTicksCounts, Number outStatuses)
fn getRrtStructsCount() -> Number count // See structs of radeonrays.h, radeonrays_redgpu.h
fn getRrtStructName(Number index) -> String name
fn getRrtStructMembersCount() -> Number count
fn getRrtStructMemberName(Number index) -> String name
fn rrtStructSizeof(String structName) -> Number bytesCount
fn rrtStructMemberSizeof(String structName, String structMemberName) -> Number bytesCount
fn rrtStructMemberOffsetof(String structName, String structMemberName) -> Number bytesFirst
fn rrtStructMemberTypeof(String structName, String structMemberName) -> Number structMemberType
fn rrtCreateContext(Number apiVersion, Number api, Number outContext) -> Number rrerror
fn rrtDestroyContext(Number context) -> Number rrerror
fn rrtSetLogLevel(Number logLevel) -> Number rrerror
fn rrtSetLogFile(String filename) -> Number rrerror
fn rrtCmdBuildGeometry(Number context, Number buildOperation, Number buildInput, Number buildOptions, Number temporaryBuffer, Number geometryBuffer, Number commandStream) -> Number rrerror
fn rrtGetGeometryBuildMemoryRequirements(Number context, Number buildInput, Number buildOptions, Number outMemoryRequirements) -> Number rrerror
fn rrtCmdBuildScene(Number context, Number buildInput, Number buildOptions, Number temporaryBuffer, Number sceneBuffer, Number commandStream) -> Number rrerror
fn rrtGetSceneBuildMemoryRequirements(Number context, Number buildInput, Number buildOptions, Number outMemoryRequirements) -> Number rrerror
fn rrtCmdIntersect(Number context, Number sceneBuffer, Number query, Number rays, Number rayCount, Number indirectRayCount, Number queryOutput, Number hits, Number scratch, Number commandStream) -> Number rrerror
fn rrtGetTraceMemoryRequirements(Number context, Number rayCount, Number outScratchSize) -> Number rrerror
fn rrtAllocateCommandStream(Number context, Number outCommandStream) -> Number rrerror
fn rrtReleaseCommandStream(Number context, Number commandStream) -> Number rrerror
fn rrtSumbitCommandStream(Number context, Number commandStream, Number waitEvent, Number outEvent) -> Number rrerror
fn rrtReleaseEvent(Number context, Number event) -> Number rrerror
fn rrtWaitEvent(Number context, Number event) -> Number rrerror
fn rrtReleaseDevicePtr(Number context, Number devicePointer) -> Number rrerror
fn rrtReleaseExternalCommandStream(Number context, Number commandStream) -> Number rrerror
fn rrtGetDevicePtrFromVkBuffer(Number context, Number resource, Number offset, Number outDevicePointer) -> Number rrerror
fn rrtCreateContextVk(Number apiVersion, Number device, Number physicalDevice, Number commandQueue, Number queueFamilyIndex, Number outContext) -> Number rrerror
fn rrtGetCommandStreamFromVkCommandBuffer(Number context, Number commandBuffer, Number outCommandStream) -> Number rrerror
fn rrtAllocateDeviceBuffer(Number context, Number size, Number outDevicePointer)
fn rrtMapDevicePtr(Number context, Number devicePointer, Number outMappingPointer) -> Number rrerror
fn rrtUnmapDevicePtr(Number context, Number devicePointer, Number outMappingPointer) -> Number rrerror
fn onRerunCallRedCpuSignalWait(Number context, Number gpuHandle, Number handle)
fn onRerunCallRedMemoryFree(Number context, Number gpuHandle, Number handle)
fn onRerunCallRedStructsMemoryFree(Number context, Number gpuHandle, Number handle)
fn onRerunCallRedDestroyContext(Number context)
fn onRerunCallRedDestroyArray(Number context, Number gpuHandle, Number handle)
fn onRerunCallRedDestroyImage(Number context, Number gpuHandle, Number handle)
fn onRerunCallRedDestroySampler(Number context, Number gpuHandle, Number handle)
fn onRerunCallRedDestroyTexture(Number context, Number gpuHandle, Number handle)
fn onRerunCallRedDestroyGpuCode(Number context, Number gpuHandle, Number handle)
fn onRerunCallRedDestroyOutputDeclaration(Number context, Number gpuHandle, Number handle)
fn onRerunCallRedDestroyStructDeclaration(Number context, Number gpuHandle, Number handle)
fn onRerunCallRedDestroyProcedureParameters(Number context, Number gpuHandle, Number handle)
fn onRerunCallRedDestroyProcedureCache(Number context, Number gpuHandle, Number handle)
fn onRerunCallRedDestroyProcedure(Number context, Number gpuHandle, Number handle)
fn onRerunCallRedDestroyOutput(Number context, Number gpuHandle, Number handle)
fn onRerunCallRedDestroyCpuSignal(Number context, Number gpuHandle, Number handle)
fn onRerunCallRedDestroyGpuSignal(Number context, Number gpuHandle, Number handle)
fn onRerunCallRedDestroyGpuToCpuSignal(Number context, Number gpuHandle, Number handle)
fn onRerunCallRedDestroyCalls(Number context, Number gpuHandle, Number callsHandle, Number callsMemoryHandle)
fn onRerunCallRedDestroyArrayTimestamp(Number context, Number gpuHandle, Number handle)
fn onRerunCallRrtWaitEvent(Number rrcontext, Number rrevent)
fn onRerunCallRrtDestroyContext(Number rrcontext)
fn onRerunCallRrtReleaseCommandStream(Number rrcontext, Number rrcommandStream)
fn onRerunCallRrtReleaseEvent(Number rrcontext, Number rrevent)
fn onRerunCallRrtReleaseDevicePtr(Number rrcontext, Number rrdevicePointer)
fn onRerunCallRrtReleaseExternalCommandStream(Number rrcontext, Number rrcommandStream)
fn onRerunCallRrtUnmapDevicePtr(Number rrcontext, Number rrdevicePointer, Number outMappingPointer)
fn getXatlasStructsCount() -> Number count
fn getXatlasStructName(Number index) -> String name
fn getXatlasStructMembersCount() -> Number count
fn getXatlasStructMemberName(Number index) -> String name
fn xatlasStructSizeof(String structName) -> Number bytesCount
fn xatlasStructMemberSizeof(String structName, String structMemberName) -> Number bytesCount
fn xatlasStructMemberOffsetof(String structName, String structMemberName) -> Number bytesFirst
fn xatlasStructMemberTypeof(String structName, String structMemberName) -> Number structMemberType
fn xatlasMeshDeclInit(Number pointerToXatlasMeshDecl)
fn xatlasUvMeshDeclInit(Number pointerToXatlasUvMeshDecl)
fn xatlasChartOptionsInit(Number pointerToXatlasChartOptions)
fn xatlasPackOptionsInit(Number pointerToXatlasPackOptions)
fn xatlasCreate() -> Number xatlas
fn xatlasDestroy(Number xatlas)
fn xatlasAddMesh(Number xatlas, Number pointerToXatlasMeshDecl, Number meshCountHint) -> Number status
fn xatlasAddMeshJoin(Number xatlas)
fn xatlasAddUvMesh(Number xatlas, Number pointerToXatlasUvMeshDecl) -> Number status
fn xatlasComputeCharts(Number xatlas, Number pointerToXatlasChartOptions)
fn xatlasPackCharts(Number xatlas, Number pointerToXatlasPackOptions)
fn xatlasGenerate(Number xatlas, Number pointerToXatlasChartOptions, Number pointerToXatlasPackOptions)
fn onRerunCallXatlasDestroy(Number xatlas)
fn fbxNew(String label) -> Number handle
fn fbxNewFromFile(String label, String filepath) -> Number handle
fn fbxDelete(String label)
fn fbxDeleteAll()
fn fbxGetHandle(String label) -> Number handle
fn fbxCopyToFbx(Number handleCopyFrom, Number handleCopyTo)
fn fbxClear(Number handle)
fn fbxEarlyUpdate(Number handle)
fn fbxLateUpdate(Number handle)
fn fbxGetMeshesCount(Number handle) -> Number count
fn fbxGetMesh(Number handle, Number meshIndex) -> Number meshHandle
fn fbxGetMeshName(Number handle, Number meshIndex) -> String meshName
fn fbxGetRootBonesCount(Number handle) -> Number count
fn fbxGetRootBone(Number handle, Number rootBoneIndex) -> Number boneHandle
fn fbxBoneGetName(Number handle) -> String boneName
fn fbxBoneGetChildBonesCount(Number handle) -> Number count
fn fbxBoneGetChildBone(Number handle, Number childBoneIndex) -> Number boneHandle
fn fbxBoneGetChildBoneByNameRecursively(Number handle, String boneName) -> Number boneHandle
fn fbxBoneGetVector(Number handle) -> Number position [3] {x, y, z}
fn fbxBoneGetVersor(Number handle) -> Number quaternion [4] {x, y, z, w}
fn fbxBoneGetScale(Number handle) -> Number scale [3] {x, y, z}
fn fbxBoneGetSideVector(Number handle) -> Number sideVector [3] {x, y, z}
fn fbxBoneGetUpVector(Number handle) -> Number upVector [3] {x, y, z}
fn fbxBoneGetLookAtVector(Number handle) -> Number lookAtVector [3] {x, y, z}
fn fbxBoneGetTransformMatrix(Number handle, Number outPointer)
fn fbxBoneSetVector(Number handle, Number x, Number y, Number z)
fn fbxBoneSetVersor(Number handle, Number x, Number y, Number z, Number w)
fn fbxBoneSetScale(Number handle, Number x, Number y, Number z)
fn fbxBoneRotate(Number handle, Number rotationX, Number rotationY, Number rotationZ, Number rotationDeg)
fn fbxBoneLookAt(Number handle, Number x, Number y, Number z, Number upX, Number upY, Number upZ)
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

let IMAGE_SET_TEXTURE_MIN_FILTER_NEAREST                = 9728;
let IMAGE_SET_TEXTURE_MIN_FILTER_LINEAR                 = 9729;
let IMAGE_SET_TEXTURE_MIN_FILTER_NEAREST_MIPMAP_NEAREST = 9984;
let IMAGE_SET_TEXTURE_MIN_FILTER_LINEAR_MIPMAP_NEAREST  = 9985;
let IMAGE_SET_TEXTURE_MIN_FILTER_NEAREST_MIPMAP_LINEAR  = 9986;
let IMAGE_SET_TEXTURE_MIN_FILTER_LINEAR_MIPMAP_LINEAR   = 9987;

let IMAGE_SET_TEXTURE_MAG_FILTER_NEAREST = 9728;
let IMAGE_SET_TEXTURE_MAG_FILTER_LINEAR  = 9729;

let IMAGE_SET_TEXTURE_WRAP_REPEAT        = 10497;
let IMAGE_SET_TEXTURE_WRAP_CLAMP_TO_EDGE = 33071;

let IMAGE_GET_IMAGE_TYPE_GRAYSCALE        = 0;
let IMAGE_GET_IMAGE_TYPE_COLOR_RGB        = 1;
let IMAGE_GET_IMAGE_TYPE_COLOR_ALPHA_RGBA = 2;
let IMAGE_GET_IMAGE_TYPE_UNDEFINED        = 3;

let STRUCT_MEMBER_TYPE_INVALID      = 0;
let STRUCT_MEMBER_TYPE_STRUCT       = 1;
let STRUCT_MEMBER_TYPE_VOID_POINTER = 2;
let STRUCT_MEMBER_TYPE_CHAR_POINTER = 3;
let STRUCT_MEMBER_TYPE_UCHAR        = 4;
let STRUCT_MEMBER_TYPE_CHAR         = 5;
let STRUCT_MEMBER_TYPE_BOOL         = 6;
let STRUCT_MEMBER_TYPE_U32          = 7;
let STRUCT_MEMBER_TYPE_I32          = 8;
let STRUCT_MEMBER_TYPE_F32          = 9;
let STRUCT_MEMBER_TYPE_SIZE_T       = 10;
let STRUCT_MEMBER_TYPE_U64          = 11;
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
fn pointerGetInteger8Bit(Number pointerTo8BitInts, Number index) -> Number value
fn pointerGetUnsignedInteger8Bit(Number pointerTo8BitUints, Number index) -> Number value
fn pointerGetAtOffsetNumber(Number pointer, Number bytesFirst) -> Number value
fn pointerGetAtOffsetInteger(Number pointer, Number bytesFirst) -> Number value
fn pointerGetAtOffsetUnsignedInteger(Number pointer, Number bytesFirst) -> Number value
fn pointerGetAtOffsetInteger16Bit(Number pointer, Number bytesFirst) -> Number value
fn pointerGetAtOffsetUnsignedInteger16Bit(Number pointer, Number bytesFirst) -> Number value
fn pointerGetAtOffsetNumber64Bit(Number pointer, Number bytesFirst) -> Number value
fn pointerGetAtOffsetInteger64Bit(Number pointer, Number bytesFirst) -> Number value
fn pointerGetAtOffsetUnsignedInteger64Bit(Number pointer, Number bytesFirst) -> Number value
fn pointerSetBool(Number pointerTo8BitBools, Number index, Bool value)
fn pointerSetString(Number pointer, Number pointerCharsFirst, String string)
fn pointerSetStringExcludingNullChar(Number pointer, Number pointerCharsFirst, String string)
fn pointerSetSubstring(Number pointer, Number pointerCharsFirst, String string, Number stringCharsFirst, Number stringCharsCount)
fn pointerSetNumber(Number pointerTo32BitFloats, Number index, Number value)
fn pointerSetInteger(Number pointerTo32BitInts, Number index, Number value)
fn pointerSetUnsignedInteger(Number pointerTo32BitUints, Number index, Number value)
fn pointerSetInteger8Bit(Number pointerTo8BitInts, Number index, Number value)
fn pointerSetUnsignedInteger8Bit(Number pointerTo8BitUints, Number index, Number value)
fn pointerSetAtOffsetNumber(Number pointer, Number bytesFirst, Number value)
fn pointerSetAtOffsetInteger(Number pointer, Number bytesFirst, Number value)
fn pointerSetAtOffsetUnsignedInteger(Number pointer, Number bytesFirst, Number value)
fn pointerSetAtOffsetInteger16Bit(Number pointer, Number bytesFirst, Number value)
fn pointerSetAtOffsetUnsignedInteger16Bit(Number pointer, Number bytesFirst, Number value)
fn pointerSetAtOffsetNumber64Bit(Number pointer, Number bytesFirst, Number value)
fn pointerSetAtOffsetInteger64Bit(Number pointer, Number bytesFirst, Number value)
fn pointerSetAtOffsetUnsignedInteger64Bit(Number pointer, Number bytesFirst, Number value)
fn pointerGetRaw8Bit(Number pointer, Number bytesFirst) -> Number raw8BitsAsDouble
fn pointerGetRaw16Bit(Number pointer, Number bytesFirst) -> Number raw16BitsAsDouble
fn pointerGetRaw32Bit(Number pointer, Number bytesFirst) -> Number raw32BitsAsDouble
fn pointerGetRaw64Bit(Number pointer, Number bytesFirst) -> Number raw64BitsAsDouble
fn pointerSetRaw8Bit(Number pointer, Number bytesFirst, Number raw8BitsAsDouble)
fn pointerSetRaw16Bit(Number pointer, Number bytesFirst, Number raw16BitsAsDouble)
fn pointerSetRaw32Bit(Number pointer, Number bytesFirst, Number raw32BitsAsDouble)
fn pointerSetRaw64Bit(Number pointer, Number bytesFirst, Number raw64BitsAsDouble)
fn pointerIsNull(Number pointer) -> Bool isNull
fn pointerGetNull() -> Number nullPointer
fn pointersAreEqual(Number pointerA, Number pointerB) -> Bool areEqual
fn pointerOffsetByBytes(Number pointer, Number bytesOffset) -> Number offsettedPointer
fn dynamicArrayGet(Number handle, Number index) -> Number value
fn dynamicArraySet(Number handle, Number index, Number value) // Two threads must not modify the same dynamic array element at the same time.
fn dynamicArrayAppend(Number handle, Number value) // Two threads must not modify the same dynamic array at the same time.
fn dynamicArrayRemoveAt(Number handle, Number index) -> Bool success // Two threads must not modify the same dynamic array at the same time.
fn dynamicArrayRemoveLast(Number handle) // Two threads must not modify the same dynamic array at the same time.
fn dynamicArrayGetSize(Number handle) -> Number size
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
fn numberFromRaw8BitInteger(Number raw8BitInteger) -> Number number
fn numberFromRaw8BitUnsignedInteger(Number raw8BitUnsignedInteger) -> Number number
fn numberFromRaw16BitInteger(Number raw16BitInteger) -> Number number
fn numberFromRaw16BitUnsignedInteger(Number raw16BitUnsignedInteger) -> Number number
fn numberFromRaw32BitInteger(Number raw32BitInteger) -> Number number
fn numberFromRaw32BitUnsignedInteger(Number raw32BitUnsignedInteger) -> Number number
fn numberFromRaw32BitFloat(Number raw32BitFloat) -> Number number
fn numberFromRaw64BitInteger(Number raw64BitInteger) -> Number number
fn numberFromRaw64BitUnsignedInteger(Number raw64BitUnsignedInteger) -> Number number
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
fn getUniqueNumber() -> Number uniqueNumber // Thread-safe.
fn getUint64Max() -> Number uint64Max // Thread-safe.
fn getLibGameHandle() -> Number handle
fn getLibThread2Handle() -> Number handle
fn getGlfwWindowHandle() -> Number handle
fn getLastDragAndDropCounter() -> Number counter
fn getLastDragAndDropFilepathsCount() -> Number count
fn getLastDragAndDropFilepath(Number index) -> String filepath
fn getLastDragAndDropPositionX() -> Number x
fn getLastDragAndDropPositionY() -> Number y
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
fn globalMeshesGetCount() -> Number count // Not thread-safe.
fn globalMeshesPersistentGetCount() -> Number count // Not thread-safe.
fn globalMeshesGetMeshLabelByMeshIndex(Number index) -> String label // Not thread-safe.
fn globalMeshesPersistentGetMeshLabelByMeshIndex(Number index) -> String label // Not thread-safe.
fn globalMeshesGetMeshHandleByMeshIndex(Number index) -> Number handle // Not thread-safe.
fn globalMeshesPersistentGetMeshHandleByMeshIndex(Number index) -> Number handle // Not thread-safe.
fn globalMeshesGetHaveVerticesChangedMeshIndexesCount() -> Number count // Not thread-safe.
fn globalMeshesGetHaveColorsChangedMeshIndexesCount() -> Number count // Not thread-safe.
fn globalMeshesGetHaveTexCoordsChangedMeshIndexesCount() -> Number count // Not thread-safe.
fn globalMeshesGetHaveIndicesChangedMeshIndexesCount() -> Number count // Not thread-safe.
fn globalMeshesPersistentGetHaveVerticesChangedMeshIndexesCount() -> Number count // Not thread-safe.
fn globalMeshesPersistentGetHaveColorsChangedMeshIndexesCount() -> Number count // Not thread-safe.
fn globalMeshesPersistentGetHaveTexCoordsChangedMeshIndexesCount() -> Number count // Not thread-safe.
fn globalMeshesPersistentGetHaveIndicesChangedMeshIndexesCount() -> Number count // Not thread-safe.
fn globalMeshesGetHaveVerticesChangedMeshIndexes(Number count) -> Number indexes [] // Not thread-safe.
fn globalMeshesGetHaveColorsChangedMeshIndexes(Number count) -> Number indexes [] // Not thread-safe.
fn globalMeshesGetHaveTexCoordsChangedMeshIndexes(Number count) -> Number indexes [] // Not thread-safe.
fn globalMeshesGetHaveIndicesChangedMeshIndexes(Number count) -> Number indexes [] // Not thread-safe.
fn globalMeshesPersistentGetHaveVerticesChangedMeshIndexes(Number count) -> Number indexes [] // Not thread-safe.
fn globalMeshesPersistentGetHaveColorsChangedMeshIndexes(Number count) -> Number indexes [] // Not thread-safe.
fn globalMeshesPersistentGetHaveTexCoordsChangedMeshIndexes(Number count) -> Number indexes [] // Not thread-safe.
fn globalMeshesPersistentGetHaveIndicesChangedMeshIndexes(Number count) -> Number indexes [] // Not thread-safe.
fn globalKeyPropertyGetKeyLabelsCount() -> Number count // Thread-safe.
fn globalKeyPropertyIsKeyLabelExists(String key) -> Bool exists // Thread-safe.
fn globalKeyPropertyGetKeyLabelByKeyIndex(Number index) -> String label // Thread-safe.
fn globalKeyPropertyGetKeyPropertyLabelsCount(String key) -> Number count // Thread-safe.
fn globalKeyPropertyIsKeyPropertyLabelExists(String key, String property) -> Bool exists // Thread-safe.
fn globalKeyPropertyGetKeyPropertyLabelByPropertyIndex(String key, Number index) -> String label // Thread-safe.
fn globalKeyPropertyRemoveKey(String key) // Thread-safe.
fn globalKeyPropertyRemoveAllKeys() // Thread-safe.
fn globalKeyPropertyRemoveProperty(String key, String property) // Thread-safe.
fn globalKeyPropertyRemoveAllProperties(String key) // Thread-safe.
fn globalKeyPropertySetString(String key, String property, String value) // Thread-safe.
fn globalKeyPropertySetNumber(String key, String property, Number value) // Thread-safe.
fn globalKeyPropertySetBool(String key, String property, Bool value) // Thread-safe.
fn globalKeyPropertyGetString(String key, String property) -> String value // Thread-safe.
fn globalKeyPropertyGetNumber(String key, String property) -> Number value // Thread-safe.
fn globalKeyPropertyGetBool(String key, String property) -> Bool value // Thread-safe.
fn ertAffineSpace3fGetSizeOfInBytes() -> Number sizeOfInBytes
fn ertAffineSpace3fSetDefaultInitialize(Number outPointer, Number outPointerBytesFirst)
fn ertAffineSpace3fSetInitialize(Number outPointer, Number outPointerBytesFirst, Number v0, Number v1, Number v2, Number v3, Number v4, Number v5, Number v6, Number v7, Number v8, Number v9, Number v10, Number v11)
fn ertAffineSpace3fSetLookAtPoint(Number outPointer, Number outPointerBytesFirst, Number posX, Number posY, Number posZ, Number targetX, Number targetY, Number targetZ, Number upX, Number upY, Number upZ)
fn ertAffineSpace3fScale(Number outPointer, Number outPointerBytesFirst, Number scaleX, Number scaleY, Number scaleZ)
fn ertAffineSpace3fTranslate(Number outPointer, Number outPointerBytesFirst, Number translateX, Number translateY, Number translateZ)
fn ertAffineSpace3fRotate(Number outPointer, Number outPointerBytesFirst, Number rotatePosX, Number rotatePosY, Number rotatePosZ, Number rotateAxisX, Number rotateAxisY, Number rotateAxisZ, Number rotateAngle)
fn ertAffineSpace3fGetLVXX(Number pointer, Number pointerBytesFirst) -> Number l_vx_x
fn ertAffineSpace3fGetLVXY(Number pointer, Number pointerBytesFirst) -> Number l_vx_y
fn ertAffineSpace3fGetLVXZ(Number pointer, Number pointerBytesFirst) -> Number l_vx_z
fn ertAffineSpace3fGetLVYX(Number pointer, Number pointerBytesFirst) -> Number l_vy_x
fn ertAffineSpace3fGetLVYY(Number pointer, Number pointerBytesFirst) -> Number l_vy_y
fn ertAffineSpace3fGetLVYZ(Number pointer, Number pointerBytesFirst) -> Number l_vy_z
fn ertAffineSpace3fGetLVZX(Number pointer, Number pointerBytesFirst) -> Number l_vz_x
fn ertAffineSpace3fGetLVZY(Number pointer, Number pointerBytesFirst) -> Number l_vz_y
fn ertAffineSpace3fGetLVZZ(Number pointer, Number pointerBytesFirst) -> Number l_vz_z
fn ertAffineSpace3fGetPX(Number pointer, Number pointerBytesFirst) -> Number p_x
fn ertAffineSpace3fGetPY(Number pointer, Number pointerBytesFirst) -> Number p_y
fn ertAffineSpace3fGetPZ(Number pointer, Number pointerBytesFirst) -> Number p_z
fn ertAffineSpace3fCopyFromArray(Number in12FloatsPointer, Number in12FloatsPointerBytesFirst, Number outAffineSpace3fPointer, Number outAffineSpace3fPointerBytesFirst)
fn ertAffineSpace3fCopyToArray(Number inAffineSpace3fPointer, Number inAffineSpace3fPointerBytesFirst, Number out12FloatsPointer, Number out12FloatsPointerBytesFirst)
fn ertCreateDevice(String typeDefaultIsdefault, Number numThreadsDefaultIs0) -> Number deviceHandle
fn ertDestroyDevice(Number deviceHandle)
fn ertNewCamera(Number deviceHandle, String type) -> Number cameraHandle
fn ertNewData(Number deviceHandle, String type, Number bytes, Number dataPointer, Number dataPointerBytesFirst) -> Number dataHandle
fn ertNewDataFromFile(Number deviceHandle, String type, String file, Number offset, Number bytes) -> Number dataHandle
fn ertNewImage(Number deviceHandle, String type, Number width, Number height, Number dataPointer, Number dataPointerBytesFirst) -> Number imageHandle
fn ertNewImageFromFile(Number deviceHandle, String file) -> Number imageHandle
fn ertNewTexture(Number deviceHandle, String type) -> Number textureHandle
fn ertNewMaterial(Number deviceHandle, String type) -> Number materialHandle
fn ertNewShape(Number deviceHandle, String type) -> Number shapeHandle
fn ertNewLight(Number deviceHandle, String type) -> Number lightHandle
fn ertNewShapePrimitive(Number deviceHandle, Number shapeHandle, Number materialHandle, Number transformPointer, Number transformPointerBytesFirst) -> Number primitiveHandle
fn ertNewLightPrimitive(Number deviceHandle, Number lightHandle, Number transformPointer, Number transformPointerBytesFirst) -> Number primitiveHandle
fn ertTransformPrimitive(Number deviceHandle, Number primitiveHandle, Number transformPointer, Number transformPointerBytesFirst) -> Number primitiveHandle
fn ertNewScene(Number deviceHandle, String type, Number primitiveHandlesPointer, Number primitiveHandlesPointerBytesFirst, Number size) -> Number sceneHandle
fn ertNewToneMapper(Number deviceHandle, String type) -> Number toneMapperHandle
fn ertNewRenderer(Number deviceHandle, String type) -> Number rendererHandle
fn ertNewFrameBuffer(Number deviceHandle, String type, Number width, Number height, Number buffersDefaultIs1) -> Number frameBufferHandle
fn ertGetFrameBufferWidth(Number deviceHandle, Number frameBufferHandle) -> Number width
fn ertGetFrameBufferHeight(Number deviceHandle, Number frameBufferHandle) -> Number height
fn ertMapFrameBuffer(Number deviceHandle, Number frameBufferHandle) -> Number pointer
fn ertUnmapFrameBuffer(Number deviceHandle, Number frameBufferHandle)
fn ertSwapBuffers(Number deviceHandle, Number frameBufferHandle)
fn ertIncRef(Number deviceHandle, Number handle)
fn ertDecRef(Number deviceHandle, Number handle)
fn ertSetBool1(Number deviceHandle, Number handle, String property, Bool x)
fn ertSetBool2(Number deviceHandle, Number handle, String property, Bool x, Bool y)
fn ertSetBool3(Number deviceHandle, Number handle, String property, Bool x, Bool y, Bool z)
fn ertSetBool4(Number deviceHandle, Number handle, String property, Bool x, Bool y, Bool z, Bool w)
fn ertSetInt1(Number deviceHandle, Number handle, String property, Number x)
fn ertSetInt2(Number deviceHandle, Number handle, String property, Number x, Number y)
fn ertSetInt3(Number deviceHandle, Number handle, String property, Number x, Number y, Number z)
fn ertSetInt4(Number deviceHandle, Number handle, String property, Number x, Number y, Number z, Number w)
fn ertSetFloat1(Number deviceHandle, Number handle, String property, Number x)
fn ertSetFloat2(Number deviceHandle, Number handle, String property, Number x, Number y)
fn ertSetFloat3(Number deviceHandle, Number handle, String property, Number x, Number y, Number z)
fn ertSetFloat4(Number deviceHandle, Number handle, String property, Number x, Number y, Number z, Number w)
fn ertSetArray(Number deviceHandle, Number handle, String property, String type, Number dataHandle, Number size, Number stride, Number ofs)
fn ertSetString(Number deviceHandle, Number handle, String property, String str)
fn ertSetImage(Number deviceHandle, Number handle, String property, Number imageHandle)
fn ertSetTexture(Number deviceHandle, Number handle, String property, Number textureHandle)
fn ertSetTransform(Number deviceHandle, Number handle, String property, Number transformPointer, Number transformPointerBytesFirst)
fn ertClear(Number deviceHandle, Number handle)
fn ertCommit(Number deviceHandle, Number handle)
fn ertRenderFrame(Number deviceHandle, Number rendererHandle, Number cameraHandle, Number sceneHandle, Number toneMapperHandle, Number frameBufferHandle, Number accumulate)
fn ertPick(Number deviceHandle, Number cameraHandle, Number x, Number y, Number sceneHandle) -> Number point [4] {x, y, z, isHit}
fn ertInitializeRayStruct(Number deviceHandle, Number orgX, Number orgY, Number orgZ, Number dirX, Number dirY, Number dirZ, Number nearDefaultIs0, Number farDefaultIsEmbreeInf, Number timeDefaultIs0, Number outRayStructPointer, Number outRayStructPointerBytesFirst)
fn ertInitializeRayStructForCameraPixelSample(Number deviceHandle, Number cameraHandle, Number pixelXFrom0To1, Number pixelYFrom0To1, Number pixelSamplePosXFrom0ToExcluded1DefaultIs0Point5, Number pixelSamplePosYFrom0ToExcluded1DefaultIs0Point5, Number outRayStructPointer, Number outRayStructPointerBytesFirst)
fn ertSceneIntersectRayStructToHitStruct(Number deviceHandle, Number sceneHandle, Number inRayStructPointer, Number inRayStructPointerBytesFirst, Number outHitStructPointer, Number outHitStructPointerBytesFirst)
fn onRerunCallErtDecRef(Number deviceHandle, Number handle) // Not thread-safe.
fn onRerunCallErtDestroyDevice(Number deviceHandle) // Not thread-safe.
fn getRedStructsCount() -> Number count // See structs of redgpu.h, redgpu_array_timestamp.h, redgpu_computing_language.h
fn getRedStructName(Number index) -> String name
fn getRedStructMembersCount() -> Number count
fn getRedStructMemberName(Number index) -> String name
fn redStructSizeof(String structName) -> Number bytesCount
fn redStructMemberSizeof(String structName, String structMemberName) -> Number bytesCount
fn redStructMemberOffsetof(String structName, String structMemberName) -> Number bytesFirst
fn redStructMemberTypeof(String structName, String structMemberName) -> Number structMemberType
fn redCreateContext(Bool enableDebugMode) -> Number context
fn redCreateContextWithRayTracingFeatureLevel1(Bool enableDebugMode) -> Number context
fn redCreateContextWithRayTracingFeatureLevel2(Bool enableDebugMode) -> Number context
fn redHandleContextGetProcAddr(Number contextHandle, String procedureName) -> Number address
fn redMemoryGetBudget(Number context, Number gpuHandle, Number outMemoryBudget, Number outStatuses)
fn redMemoryAllocate(Number context, Number gpuHandle, String handleName, Number bytesCount, Number memoryTypeIndex, Number dedicateToArray, Number dedicateToImage, Number memoryBitflags, Number outStatuses) -> Number memoryHandle
fn redMemoryAllocateMappable(Number context, Number gpuHandle, String handleName, Bool dedicate, Number array, Number arrayMemoryBytesCount, Number memoryTypeIndex, Number memoryBitflags, Number outStatuses) -> Number memoryHandle
fn redMemoryFree(Number context, Number gpuHandle, Number memory)
fn redMemorySet(Number context, Number gpuHandle, Number memoryArraysCount, Number memoryArrays, Number memoryImagesCount, Number memoryImages, Number outStatuses)
fn redMemoryMap(Number context, Number gpuHandle, Number mappableMemory, Number mappableMemoryBytesFirst, Number mappableMemoryBytesCount, Number outStatuses) -> Number pointer
fn redMemoryUnmap(Number context, Number gpuHandle, Number mappableMemory)
fn redMemoryNonCoherentFlush(Number context, Number gpuHandle, Number mappableMemoryRangesCount, Number mappableMemoryRanges, Number outStatuses)
fn redMemoryNonCoherentInvalidate(Number context, Number gpuHandle, Number mappableMemoryRangesCount, Number mappableMemoryRanges, Number outStatuses)
fn redStructsMemoryAllocate(Number context, Number gpuHandle, String handleName, Number maxStructsCount, Number maxStructsMembersOfTypeArrayROConstantCount, Number maxStructsMembersOfTypeArrayROOrArrayRWCount, Number maxStructsMembersOfTypeTextureROCount, Number maxStructsMembersOfTypeTextureRWCount, Number outStatuses) -> Number structsMemoryHandle
fn redStructsMemoryAllocateSamplers(Number context, Number gpuHandle, String handleName, Number maxStructsCount, Number maxStructsMembersOfTypeSamplerCount, Number outStatuses) -> Number structsMemoryHandle
fn redStructsMemorySuballocateStructs(Number context, Number gpuHandle, Number handleNames, Number structsMemory, Number structsDeclarationsCount, Number structsDeclarations, Number outStructs, Number outStatuses)
fn redStructsMemoryReset(Number context, Number gpuHandle, Number structsMemory, Number outStatuses)
fn redStructsMemoryFree(Number context, Number gpuHandle, Number structsMemory)
fn redStructsSet(Number context, Number gpuHandle, Number structsMembersCount, Number structsMembers)
fn redCreateArray(Number context, Number gpuHandle, String handleName, Number type, Number bytesCount, Number structuredBufferElementBytesCount, Number initialAccess, Number initialQueueFamilyIndex, Bool dedicate, Number outArray, Number outStatuses) -> Number arrayHandle
fn redCreateImage(Number context, Number gpuHandle, String handleName, Number dimensions, Number format, Number width, Number height, Number depth, Number levelsCount, Number layersCount, Number multisampleCount, Number restrictToAccess, Number initialAccess, Number initialQueueFamilyIndex, Bool dedicate, Number outImage, Number outStatuses) -> Number imageHandle
fn redCreateSampler(Number context, Number gpuHandle, String handleName, Number filteringMag, Number filteringMin, Number filteringMip, Number behaviorOutsideTextureCoordinateU, Number behaviorOutsideTextureCoordinateV, Number behaviorOutsideTextureCoordinateW, Number mipLodBias, Bool enableAnisotropy, Number maxAnisotropy, Bool enableCompare, Number compareOp, Number minLod, Number maxLod, Number outStatuses) -> Number samplerHandle
fn redCreateTexture(Number context, Number gpuHandle, String handleName, Number image, Number parts, Number dimensions, Number format, Number levelsFirst, Number levelsCount, Number layersFirst, Number layersCount, Number restrictToAccess, Number outStatuses) -> Number textureHandle
fn redCreateGpuCode(Number context, Number gpuHandle, String handleName, Number irBytesCount, Number ir, Number outStatuses) -> Number gpuCodeHandle
fn redCreateOutputDeclaration(Number context, Number gpuHandle, String handleName, Number outputDeclarationMembers, Number outputDeclarationMembersResolveSources, Bool dependencyByRegion, Bool dependencyByRegionAllowUsageAliasOrderBarriers, Number outStatuses) -> Number outputDeclarationHandle
fn redCreateStructDeclaration(Number context, Number gpuHandle, String handleName, Number structDeclarationMembersCount, Number structDeclarationMembers, Number structDeclarationMembersArrayROCount, Number structDeclarationMembersArrayRO, Bool procedureParametersHandlesDeclaration, Number outStatuses) -> Number structDeclarationHandle
fn redCreateProcedureParameters(Number context, Number gpuHandle, String handleName, Number procedureParametersDeclaration, Number outStatuses) -> Number procedureParametersHandle
fn redCreateProcedureCache(Number context, Number gpuHandle, String handleName, Number fromBlobBytesCount, Number fromBlob, Number outStatuses) -> Number procedureCacheHandle
fn redCreateProcedure(Number context, Number gpuHandle, String handleName, Number procedureCache, Number outputDeclaration, Number procedureParameters, String gpuCodeVertexMainProcedureName, Number gpuCodeVertex, String gpuCodeFragmentMainProcedureName, Number gpuCodeFragment, Number state, Number stateExtension, Bool deriveBase, Number deriveFrom, Number outStatuses) -> Number procedureHandle
fn redCreateProcedureCompute(Number context, Number gpuHandle, String handleName, Number procedureCache, Number procedureParameters, String gpuCodeMainProcedureName, Number gpuCode, Number outStatuses) -> Number procedureHandle
fn redCreateOutput(Number context, Number gpuHandle, String handleName, Number outputDeclaration, Number outputMembers, Number outputMembersResolveTargets, Number width, Number height, Number outOutput, Number outStatuses) -> Number outputHandle
fn redCreateCpuSignal(Number context, Number gpuHandle, String handleName, Bool createSignaled, Number outStatuses) -> Number cpuSignalHandle
fn redCreateGpuSignal(Number context, Number gpuHandle, String handleName, Number outStatuses) -> Number gpuSignalHandle
fn redCreateGpuToCpuSignal(Number context, Number gpuHandle, String handleName, Number outStatuses) -> Number gpuToCpuHandle
fn redCreateCalls(Number context, Number gpuHandle, String handleName, Number queueFamilyIndex, Number outCalls, Number outStatuses)
fn redCreateCallsReusable(Number context, Number gpuHandle, String handleName, Number queueFamilyIndex, Number outCalls, Number outStatuses)
fn redDestroyContext(Number context)
fn redDestroyArray(Number context, Number gpuHandle, Number array)
fn redDestroyImage(Number context, Number gpuHandle, Number image)
fn redDestroySampler(Number context, Number gpuHandle, Number sampler)
fn redDestroyTexture(Number context, Number gpuHandle, Number texture)
fn redDestroyGpuCode(Number context, Number gpuHandle, Number gpuCode)
fn redDestroyOutputDeclaration(Number context, Number gpuHandle, Number outputDeclaration)
fn redDestroyStructDeclaration(Number context, Number gpuHandle, Number structDeclaration)
fn redDestroyProcedureParameters(Number context, Number gpuHandle, Number procedureParameters)
fn redDestroyProcedureCache(Number context, Number gpuHandle, Number procedureCache)
fn redDestroyProcedure(Number context, Number gpuHandle, Number procedure)
fn redDestroyOutput(Number context, Number gpuHandle, Number output)
fn redDestroyCpuSignal(Number context, Number gpuHandle, Number cpuSignal)
fn redDestroyGpuSignal(Number context, Number gpuHandle, Number gpuSignal)
fn redDestroyGpuToCpuSignal(Number context, Number gpuHandle, Number gpuToCpuSignal)
fn redDestroyCalls(Number context, Number gpuHandle, Number calls, Number callsMemory)
fn redProcedureCacheGetBlob(Number context, Number gpuHandle, Number procedureCache, Number outBlobBytesCount, Number outBlob, Number outStatuses)
fn redProcedureCacheMergeCaches(Number context, Number gpuHandle, Number sourceProcedureCachesCount, Number sourceProcedureCaches, Number targetProcedureCache, Number outStatuses)
fn redCpuSignalGetStatus(Number context, Number gpuHandle, Number cpuSignal) -> Number status
fn redCpuSignalWait(Number context, Number gpuHandle, Number cpuSignalsCount, Number cpuSignals, Bool waitAll, Number outStatuses)
fn redCpuSignalUnsignal(Number context, Number gpuHandle, Number cpuSignalsCount, Number cpuSignals, Number outStatuses)
fn redGpuToCpuSignalGetStatus(Number context, Number gpuHandle, Number gpuToCpuSignal) -> Number status
fn redGpuToCpuSignalUnsignal(Number context, Number gpuHandle, Number gpuToCpuSignal, Number outStatuses)
fn redCallsSet(Number context, Number gpuHandle, Number calls, Number callsMemory, Bool callsReusable, Number outStatuses)
fn redCallsEnd(Number context, Number gpuHandle, Number calls, Number callsMemory, Number outStatuses)
fn redGetCallProceduresAndAddresses(Number context, Number gpuHandle, Number outCallProceduresAndAddresses, Number outStatuses)
fn redCallGpuToCpuSignalSignal(Number callProceduresAndAddresses, Number calls, Number signalGpuToCpuSignal, Number setTo8192)
fn redCallCopyArrayToArray(Number callProceduresAndAddresses, Number calls, Number arrayR, Number arrayW, Number rangesCount, Number ranges)
fn redCallCopyImageToImage(Number callProceduresAndAddresses, Number calls, Number imageR, Number setTo1, Number imageW, Number setTo01, Number rangesCount, Number ranges)
fn redCallCopyArrayToImage(Number callProceduresAndAddresses, Number calls, Number arrayR, Number imageW, Number setTo1, Number rangesCount, Number ranges)
fn redCallCopyImageToArray(Number callProceduresAndAddresses, Number calls, Number imageR, Number setTo1, Number arrayW, Number rangesCount, Number ranges)
fn redCallProcedure(Number callProceduresAndAddresses, Number calls, Number vertexCount, Number instanceCount, Number vertexFirst, Number instanceFirst)
fn redCallProcedureIndexed(Number callProceduresAndAddresses, Number calls, Number indexCount, Number instanceCount, Number indexFirst, Number vertexBase, Number instanceFirst)
fn redCallProcedureCompute(Number callProceduresAndAddresses, Number calls, Number workgroupsCountX, Number workgroupsCountY, Number workgroupsCountZ)
fn redCallSetProcedure(Number callProceduresAndAddresses, Number calls, Number procedureType, Number procedure)
fn redCallSetProcedureIndices(Number callProceduresAndAddresses, Number calls, Number array, Number setTo0, Number setTo1)
fn redCallSetProcedureParametersVariables(Number callProceduresAndAddresses, Number calls, Number procedureParameters, Number visibleToStages, Number variablesBytesFirst, Number dataBytesCount, Number data)
fn redCallSetProcedureParametersStructs(Number callProceduresAndAddresses, Number calls, Number procedureType, Number procedureParameters, Number procedureParametersDeclarationStructsDeclarationsFirst, Number structsCount, Number structs, Number setTo0, Number setTo00)
fn redCallSetProcedureParametersHandles(Number callProceduresAndAddresses, Number calls, Number procedureType, Number procedureParameters, Number procedureParametersDeclarationStructsDeclarationsCount, Number handlesCount, Number handles)
fn redCallSetDynamicDepthBias(Number callProceduresAndAddresses, Number calls, Number constantFactor, Number clamp, Number slopeFactor)
fn redCallSetDynamicDepthBounds(Number callProceduresAndAddresses, Number calls, Number min, Number max)
fn redCallSetDynamicStencilCompareMask(Number callProceduresAndAddresses, Number calls, Number face, Number compareMask)
fn redCallSetDynamicStencilWriteMask(Number callProceduresAndAddresses, Number calls, Number face, Number writeMask)
fn redCallSetDynamicStencilReference(Number callProceduresAndAddresses, Number calls, Number face, Number reference)
fn redCallSetDynamicBlendConstants(Number callProceduresAndAddresses, Number calls, Number blendConstants)
fn redCallSetDynamicViewport(Number callProceduresAndAddresses, Number calls, Number x, Number y, Number width, Number height, Number depthMin, Number depthMax)
fn redCallSetDynamicScissor(Number callProceduresAndAddresses, Number calls, Number x, Number y, Number width, Number height)
fn redCallSetStructsMemory(Number callProceduresAndAddresses, Number calls, Number structsMemory, Number structsMemorySamplers)
fn redCallSetProcedureParameters(Number callProceduresAndAddresses, Number calls, Number procedureType, Number procedureParameters)
fn redCallSetProcedureOutput(Number callProceduresAndAddresses, Number calls, Number outputDeclaration, Number output, Number inlineOutput, Number outputWidth, Number outputHeight, Bool outputDepthStencilEnable, Number outputColorsCount, Number depthClearValue, Number stencilClearValue, Number colorsClearValuesFloat, Number colorsClearValuesSint, Number colorsClearValuesUint)
fn redCallEndProcedureOutput(Number callProceduresAndAddresses, Number calls)
fn redCallUsageAliasOrderBarrier(Number callProceduresAndAddresses, Number calls, Number context, Number arrayUsagesCount, Number arrayUsages, Number imageUsagesCount, Number imageUsages, Number aliasesCount, Number aliases, Number ordersCount, Number orders, Bool dependencyByRegion)
fn redCallMark(Number callProceduresAndAddresses, Number calls, String mark)
fn redCallMarkSet(Number callProceduresAndAddresses, Number calls, String mark)
fn redCallMarkEnd(Number callProceduresAndAddresses, Number calls)
fn redQueueSubmit(Number context, Number gpuHandle, Number queue, Number timelinesCount, Number timelines, Number signalCpuSignal, Number outStatuses)
fn redMark(String mark)
fn redMarkSet(String mark)
fn redMarkEnd()
fn redCreateProcedureComputingLanguage(Number context, Number gpuHandle, String handleName, Number procedureCache, Number procedureParameters, String gpuCodeMainProcedureName, Number gpuCode, Number stateExtension, Number outStatuses) -> Number procedureHandle
fn redCreateArrayTimestamp(Number context, Number gpuHandle, String handleName, Number count, Number outStatuses) -> Number arrayTimestampHandle
fn redDestroyArrayTimestamp(Number context, Number gpuHandle, Number arrayTimestamp)
fn redCallArrayTimestampWrite(Number calls, Number context, Number arrayTimestamp, Number index)
fn redArrayTimestampRead(Number context, Number gpuHandle, Number arrayTimestamp, Number rangeFirst, Number rangeCount, Number out64BitTicksCounts, Number outStatuses)
fn getRrtStructsCount() -> Number count // See structs of radeonrays.h, radeonrays_redgpu.h
fn getRrtStructName(Number index) -> String name
fn getRrtStructMembersCount() -> Number count
fn getRrtStructMemberName(Number index) -> String name
fn rrtStructSizeof(String structName) -> Number bytesCount
fn rrtStructMemberSizeof(String structName, String structMemberName) -> Number bytesCount
fn rrtStructMemberOffsetof(String structName, String structMemberName) -> Number bytesFirst
fn rrtStructMemberTypeof(String structName, String structMemberName) -> Number structMemberType
fn rrtCreateContext(Number apiVersion, Number api, Number outContext) -> Number rrerror
fn rrtDestroyContext(Number context) -> Number rrerror
fn rrtSetLogLevel(Number logLevel) -> Number rrerror
fn rrtSetLogFile(String filename) -> Number rrerror
fn rrtCmdBuildGeometry(Number context, Number buildOperation, Number buildInput, Number buildOptions, Number temporaryBuffer, Number geometryBuffer, Number commandStream) -> Number rrerror
fn rrtGetGeometryBuildMemoryRequirements(Number context, Number buildInput, Number buildOptions, Number outMemoryRequirements) -> Number rrerror
fn rrtCmdBuildScene(Number context, Number buildInput, Number buildOptions, Number temporaryBuffer, Number sceneBuffer, Number commandStream) -> Number rrerror
fn rrtGetSceneBuildMemoryRequirements(Number context, Number buildInput, Number buildOptions, Number outMemoryRequirements) -> Number rrerror
fn rrtCmdIntersect(Number context, Number sceneBuffer, Number query, Number rays, Number rayCount, Number indirectRayCount, Number queryOutput, Number hits, Number scratch, Number commandStream) -> Number rrerror
fn rrtGetTraceMemoryRequirements(Number context, Number rayCount, Number outScratchSize) -> Number rrerror
fn rrtAllocateCommandStream(Number context, Number outCommandStream) -> Number rrerror
fn rrtReleaseCommandStream(Number context, Number commandStream) -> Number rrerror
fn rrtSumbitCommandStream(Number context, Number commandStream, Number waitEvent, Number outEvent) -> Number rrerror
fn rrtReleaseEvent(Number context, Number event) -> Number rrerror
fn rrtWaitEvent(Number context, Number event) -> Number rrerror
fn rrtReleaseDevicePtr(Number context, Number devicePointer) -> Number rrerror
fn rrtReleaseExternalCommandStream(Number context, Number commandStream) -> Number rrerror
fn rrtGetDevicePtrFromVkBuffer(Number context, Number resource, Number offset, Number outDevicePointer) -> Number rrerror
fn rrtCreateContextVk(Number apiVersion, Number device, Number physicalDevice, Number commandQueue, Number queueFamilyIndex, Number outContext) -> Number rrerror
fn rrtGetCommandStreamFromVkCommandBuffer(Number context, Number commandBuffer, Number outCommandStream) -> Number rrerror
fn rrtAllocateDeviceBuffer(Number context, Number size, Number outDevicePointer)
fn rrtMapDevicePtr(Number context, Number devicePointer, Number outMappingPointer) -> Number rrerror
fn rrtUnmapDevicePtr(Number context, Number devicePointer, Number outMappingPointer) -> Number rrerror
fn onRerunCallRedCpuSignalWait(Number context, Number gpuHandle, Number handle) // Not thread-safe.
fn onRerunCallRedMemoryFree(Number context, Number gpuHandle, Number handle) // Not thread-safe.
fn onRerunCallRedStructsMemoryFree(Number context, Number gpuHandle, Number handle) // Not thread-safe.
fn onRerunCallRedDestroyContext(Number context) // Not thread-safe.
fn onRerunCallRedDestroyArray(Number context, Number gpuHandle, Number handle) // Not thread-safe.
fn onRerunCallRedDestroyImage(Number context, Number gpuHandle, Number handle) // Not thread-safe.
fn onRerunCallRedDestroySampler(Number context, Number gpuHandle, Number handle) // Not thread-safe.
fn onRerunCallRedDestroyTexture(Number context, Number gpuHandle, Number handle) // Not thread-safe.
fn onRerunCallRedDestroyGpuCode(Number context, Number gpuHandle, Number handle) // Not thread-safe.
fn onRerunCallRedDestroyOutputDeclaration(Number context, Number gpuHandle, Number handle) // Not thread-safe.
fn onRerunCallRedDestroyStructDeclaration(Number context, Number gpuHandle, Number handle) // Not thread-safe.
fn onRerunCallRedDestroyProcedureParameters(Number context, Number gpuHandle, Number handle) // Not thread-safe.
fn onRerunCallRedDestroyProcedureCache(Number context, Number gpuHandle, Number handle) // Not thread-safe.
fn onRerunCallRedDestroyProcedure(Number context, Number gpuHandle, Number handle) // Not thread-safe.
fn onRerunCallRedDestroyOutput(Number context, Number gpuHandle, Number handle) // Not thread-safe.
fn onRerunCallRedDestroyCpuSignal(Number context, Number gpuHandle, Number handle) // Not thread-safe.
fn onRerunCallRedDestroyGpuSignal(Number context, Number gpuHandle, Number handle) // Not thread-safe.
fn onRerunCallRedDestroyGpuToCpuSignal(Number context, Number gpuHandle, Number handle) // Not thread-safe.
fn onRerunCallRedDestroyCalls(Number context, Number gpuHandle, Number callsHandle, Number callsMemoryHandle) // Not thread-safe.
fn onRerunCallRedDestroyArrayTimestamp(Number context, Number gpuHandle, Number handle) // Not thread-safe.
fn onRerunCallRrtWaitEvent(Number rrcontext, Number rrevent) // Not thread-safe.
fn onRerunCallRrtDestroyContext(Number rrcontext) // Not thread-safe.
fn onRerunCallRrtReleaseCommandStream(Number rrcontext, Number rrcommandStream) // Not thread-safe.
fn onRerunCallRrtReleaseEvent(Number rrcontext, Number rrevent) // Not thread-safe.
fn onRerunCallRrtReleaseDevicePtr(Number rrcontext, Number rrdevicePointer) // Not thread-safe.
fn onRerunCallRrtReleaseExternalCommandStream(Number rrcontext, Number rrcommandStream) // Not thread-safe.
fn onRerunCallRrtUnmapDevicePtr(Number rrcontext, Number rrdevicePointer, Number outMappingPointer) // Not thread-safe.
fn getXatlasStructsCount() -> Number count
fn getXatlasStructName(Number index) -> String name
fn getXatlasStructMembersCount() -> Number count
fn getXatlasStructMemberName(Number index) -> String name
fn xatlasStructSizeof(String structName) -> Number bytesCount
fn xatlasStructMemberSizeof(String structName, String structMemberName) -> Number bytesCount
fn xatlasStructMemberOffsetof(String structName, String structMemberName) -> Number bytesFirst
fn xatlasStructMemberTypeof(String structName, String structMemberName) -> Number structMemberType
fn xatlasMeshDeclInit(Number pointerToXatlasMeshDecl)
fn xatlasUvMeshDeclInit(Number pointerToXatlasUvMeshDecl)
fn xatlasChartOptionsInit(Number pointerToXatlasChartOptions)
fn xatlasPackOptionsInit(Number pointerToXatlasPackOptions)
fn xatlasCreate() -> Number xatlas
fn xatlasDestroy(Number xatlas)
fn xatlasAddMesh(Number xatlas, Number pointerToXatlasMeshDecl, Number meshCountHint) -> Number status
fn xatlasAddMeshJoin(Number xatlas)
fn xatlasAddUvMesh(Number xatlas, Number pointerToXatlasUvMeshDecl) -> Number status
fn xatlasComputeCharts(Number xatlas, Number pointerToXatlasChartOptions)
fn xatlasPackCharts(Number xatlas, Number pointerToXatlasPackOptions)
fn xatlasGenerate(Number xatlas, Number pointerToXatlasChartOptions, Number pointerToXatlasPackOptions)
fn onRerunCallXatlasDestroy(Number xatlas) // Not thread-safe.
fn fbxNew(String label) -> Number handle
fn fbxNewFromFile(String label, String filepath) -> Number handle
fn fbxDelete(String label)
fn fbxDeleteAll()
fn fbxGetHandle(String label) -> Number handle
fn fbxCopyToFbx(Number handleCopyFrom, Number handleCopyTo)
fn fbxClear(Number handle)
fn fbxEarlyUpdate(Number handle)
fn fbxLateUpdate(Number handle)
fn fbxGetMeshesCount(Number handle) -> Number count
fn fbxGetMesh(Number handle, Number meshIndex) -> Number meshHandle
fn fbxGetMeshName(Number handle, Number meshIndex) -> String meshName
fn fbxGetRootBonesCount(Number handle) -> Number count
fn fbxGetRootBone(Number handle, Number rootBoneIndex) -> Number boneHandle
fn fbxBoneGetName(Number handle) -> String boneName
fn fbxBoneGetChildBonesCount(Number handle) -> Number count
fn fbxBoneGetChildBone(Number handle, Number childBoneIndex) -> Number boneHandle
fn fbxBoneGetChildBoneByNameRecursively(Number handle, String boneName) -> Number boneHandle
fn fbxBoneGetVector(Number handle) -> Number position [3] {x, y, z}
fn fbxBoneGetVersor(Number handle) -> Number quaternion [4] {x, y, z, w}
fn fbxBoneGetScale(Number handle) -> Number scale [3] {x, y, z}
fn fbxBoneGetSideVector(Number handle) -> Number sideVector [3] {x, y, z}
fn fbxBoneGetUpVector(Number handle) -> Number upVector [3] {x, y, z}
fn fbxBoneGetLookAtVector(Number handle) -> Number lookAtVector [3] {x, y, z}
fn fbxBoneGetTransformMatrix(Number handle, Number outPointer)
fn fbxBoneSetVector(Number handle, Number x, Number y, Number z)
fn fbxBoneSetVersor(Number handle, Number x, Number y, Number z, Number w)
fn fbxBoneSetScale(Number handle, Number x, Number y, Number z)
fn fbxBoneRotate(Number handle, Number rotationX, Number rotationY, Number rotationZ, Number rotationDeg)
fn fbxBoneLookAt(Number handle, Number x, Number y, Number z, Number upX, Number upY, Number upZ)
```

[Game Script](https://procedural.itch.io/gamescript) uses the Ape programming language v0.14.0 by Krzysztof Gabis, you can read more about it in my public fork of his Github repo here: https://github.com/procedural/script

[Game Script Native](https://procedural.itch.io/gamescriptnative) uses standard C++14.

[Game Script Native Swift](https://github.com/procedural/gamescript_native_swift) uses latest available Swift programming language.

## Other useful repos:

* https://github.com/procedural/gamescript_native_swift
* https://github.com/procedural/gamescript_native_clang_for_windows
* https://github.com/procedural/gamescript_raytracing
* https://github.com/procedural/gamescript_fbx_examples

# Game Script

# Download here: [procedural.itch.io/gamescript](https://procedural.itch.io/gamescript)

Join the official Game Script Discord server! https://discord.gg/D7pKPw4kFf
===========================================================================

Install
-------

* Download and extract GameScript folder, double click on the `game_script.exe` file on Windows 7 (64-bit) or higher.
* Download and extract GameScript folder, double click on the `game_script.desktop` file on Ubuntu 16.04 (64-bit) or higher.

Hotkeys
-------

* F3: toggle between script and game mode.
* F5: rerun the script.
* F7: stop running the script.
* F9: continue running the script.
* F11: toggle fullscreen mode.
* Ctrl + Tab: switch between windows in script mode.

List of available script functions
----------------------------------

```
fn print(String string)
fn printDraw(String string)
fn windowSetTitle(String title)
fn windowGetWidth() -> Number width
fn windowGetHeight() -> Number height
fn windowSetWidthHeight(Number width, Number height)
fn windowSetFullscreen(Bool fullscreen)
fn windowIsFocused() -> Bool isFocused
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
fn defaultCameraSetMoveSpeed(Number speed)
fn defaultCameraSetRollSpeed(Number speed)
fn defaultCameraGetVector() -> Number position [3] {x, y, z}
fn defaultCameraGetVersor() -> Number quaternion [4] {x, y, z, w}
fn defaultCameraSetVector(Number x, Number y, Number z)
fn defaultCameraSetVersor(Number x, Number y, Number z, Number w)
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
fn setColorMask(Bool r, Bool g, Bool b, Bool a)
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
fn pointerGetBool(Number pointer, Number index) -> Bool boolean
fn pointerGetString(Number pointer) -> String string
fn pointerGetNumber(Number pointer, Number index) -> Number number
fn pointerGetUnsignedInteger(Number pointer, Number index) -> Number unsignedInteger
fn pointerSetBool(Number pointer, Number index, Bool value)
fn pointerSetString(Number pointer, Number pointerCharsFirst, String value)
fn pointerSetNumber(Number pointer, Number index, Number value)
fn pointerSetUnsignedInteger(Number pointer, Number index, Number value)
fn pointerGetRaw8Bit(Number pointer, Number bytesFirst) -> Number raw8Bit
fn pointerGetRaw16Bit(Number pointer, Number bytesFirst) -> Number raw16Bit
fn pointerGetRaw32Bit(Number pointer, Number bytesFirst) -> Number raw32Bit
fn pointerGetRaw64Bit(Number pointer, Number bytesFirst) -> Number raw64Bit
fn pointerSetRaw8Bit(Number pointer, Number bytesFirst, Number rawBitsAsDouble)
fn pointerSetRaw16Bit(Number pointer, Number bytesFirst, Number rawBitsAsDouble)
fn pointerSetRaw32Bit(Number pointer, Number bytesFirst, Number rawBitsAsDouble)
fn pointerSetRaw64Bit(Number pointer, Number bytesFirst, Number rawBitsAsDouble)
fn memset(Number pointer, Number pointerBytesFirst, Number value8Bit, Number bytesCount)
fn memcpy(Number pointerTarget, Number pointerTargetBytesFirst, Number pointerSource, Number pointerSourceBytesFirst, Number bytesCount)
fn memcmp(Number pointerA, Number pointerABytesFirst, Number pointerB, Number pointerBBytesFirst, Number bytesCount) -> Bool areEqual
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
fn meshGetGetIndicesPointer(Number handle) -> Number pointer
fn meshMergeDuplicateVertices(Number handle)
fn meshSetupIndicesAuto(Number handle)
fn meshAddTriangle(Number handle, Number verticesArrayIndex1, Number verticesArrayIndex2, Number verticesArrayIndex3)
fn meshDraw(Number handle, Number renderMode, Number scaleX, Number scaleY, Number scaleZ, Number vectorX, Number vectorY, Number vectorZ, Number rotationX, Number rotationY, Number rotationZ, Number rotationDeg)
fn meshDrawDebugVertices(String label)
fn meshDrawDebugColors(String label)
fn meshDrawDebugTexCoords(String label)
fn meshDrawDebugIndices(String label)
fn meshImporterGetMeshesCount(String meshFilepath) -> Number count
fn meshImporterGetMeshName(String meshFilepath, Number meshIndex) -> String name
fn meshImporterGetMesh(String meshFilepath, Number meshIndex, Number writeToMesh)
fn meshImporterDelete(String meshFilepath)
fn meshImporterDeleteAll()
fn imageNew(String label, Number width, Number height) -> Number handle
fn imagePersistentNew(String label, Number width, Number height) -> Number handle
fn imageNewFromFile(String label, String filepath) -> Number handle
fn imagePersistentNewFromFile(String label, String filepath) -> Number handle
fn imageGetHandle(String label) -> Number handle
fn imagePersistentGetHandle(String label) -> Number handle
fn imageClear(Number handle, Number alpha0to255)
fn imageSetTextureMinMagFilter(Number handle, Number minFilter, Number magFilter)
fn imageSetTextureWrap(Number handle, Number wrapX, Number wrapY)
fn imageGetWidth(Number handle) -> Number width
fn imageGetHeight(Number handle) -> Number height
fn imageGetImageType(Number handle) -> Number imageType
fn imageGetColor(Number handle, Number x, Number y) -> Number [4] {r0To255, g0To255, b0To255, a0To255}
fn imageSetColor(Number handle, Number x, Number y, Number r0to255, Number g0to255, Number b0to255, Number a0to255)
fn imageUpdate(Number handle)
fn imageGammaCorrect(Number handle)
fn imageBind(Number handle)
fn imageUnbind(Number handle)
fn imageDelete(Number handle)
fn imagePersistentDelete(Number handle)
fn imageDeleteAll()
fn imagePersistentDeleteAll()
fn shaderBegin(String label, String filepathShaderVert, String filepathShaderFrag) -> Bool shadersAreValid
fn shaderEnd(String label)
fn shaderSetUniform4f(String label, String uniformName, Number x, Number y, Number z, Number w)
fn shaderSetUniformImage(String label, String uniformName, Number imageHandle, Number textureLocation)
fn shaderDelete(String label)
fn shaderDeleteAll()
fn soundPlayerNew(String label) -> Number handle
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
fn soundPlayerDelete(Number handle)
fn soundPlayerDeleteAll()
fn soundSetVolume(Number volume0to1)
fn soundShutdown()
fn soundStopAll()
fn soundUpdate()
fn profileBegin(String mark)
fn profileEnd(String mark)
fn systemCommand(String command) -> String output
fn libGameScriptExternalProcedureReload()
fn libGameScriptExternalProcedureSet(Number parameter1, Number parameter2)
fn libGameScriptExternalProcedureCall()
```

Currently, Game Script uses the Ape programming language v0.14.0 by Krzysztof Gabis, you can read more about it in my public fork of his Github repo here:

https://github.com/procedural/script

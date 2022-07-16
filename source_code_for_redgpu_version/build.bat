cl /D ImTextureID=ImU64 main.cpp imgui*.cpp /link glfw3.dll.lib opengl32.lib gdi32.lib shell32.lib C:\RedGpuSDK\redgpudll.lib
xcopy /y C:\RedGpuSDK\redgpu.dll

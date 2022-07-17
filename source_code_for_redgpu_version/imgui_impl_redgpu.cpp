// dear imgui: Renderer Backend for REDGPU
// This needs to be used along with a Platform Backend (e.g. GLFW, SDL, Win32, custom..)

// Important: on 32-bit systems, user texture binding is only supported if your imconfig file has '#define ImTextureID ImU64'.
// This is because we need ImTextureID to carry a 64-bit value and by default ImTextureID is defined as void*.
// To build this on 32-bit systems and support texture changes:
// - [Solution 1] IDE/msbuild: in "Properties/C++/Preprocessor Definitions" add 'ImTextureID=ImU64' (this is what we do in our .vcxproj files)
// - [Solution 2] IDE/msbuild: in "Properties/C++/Preprocessor Definitions" add 'IMGUI_USER_CONFIG="my_imgui_config.h"' and inside 'my_imgui_config.h' add '#define ImTextureID ImU64' and as many other options as you like.
// - [Solution 3] IDE/msbuild: edit imconfig.h and add '#define ImTextureID ImU64' (prefer solution 2 to create your own config file!)
// - [Solution 4] command-line: add '/D ImTextureID=ImU64' to your cl.exe command-line (this is what we do in our batch files)

// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui_impl_redgpu.h"
#include <stdio.h>

// Visual Studio warnings
#ifdef _MSC_VER
#pragma warning (disable: 4127) // condition expression is constant
#endif

// Reusable buffers used for rendering 1 current in-flight frame, for ImGui_ImplRedGpu_RenderDrawData()
// [Please zero-clear before use!]
struct ImGui_ImplRedGpuH_FrameRenderBuffers
{
    RedHandleMemory     VertexBufferMemory;
    RedHandleMemory     IndexBufferMemory;
    uint64_t            VertexBufferSize;
    uint64_t            IndexBufferSize;
    RedArray            VertexBuffer;
    RedArray            IndexBuffer;
};

// Each viewport will hold 1 ImGui_ImplRedGpuH_WindowRenderBuffers
// [Please zero-clear before use!]
struct ImGui_ImplRedGpuH_WindowRenderBuffers
{
    uint32_t            Index;
    uint32_t            Count;
    ImGui_ImplRedGpuH_FrameRenderBuffers*   FrameRenderBuffers;
};

// RedGpu data
struct ImGui_ImplRedGpu_Data
{
    ImGui_ImplRedGpu_InitInfo   RedGpuInitInfo;
    RedHandleOutputDeclaration  RenderPass;
    uint64_t                    BufferMemoryAlignment;
    RedHandleStructDeclaration  SamplerDescriptorSetLayout;
    RedHandleStructDeclaration  DescriptorSetLayout;
    RedHandleStructDeclaration  ImdrawvertsDescriptorSetLayout;
    RedHandleProcedureParameters PipelineLayout;
    RedHandleProcedure          Pipeline;
    uint32_t                    Subpass;
    RedHandleGpuCode            ShaderModuleVert;
    RedHandleGpuCode            ShaderModuleFrag;

    // Font data
    RedHandleSampler            FontSampler;
    RedHandleMemory             FontMemory;
    RedImage                    FontImage;
    RedHandleTexture            FontView;
    RedHandleStruct             FontSamplerDescriptorSet;
    RedHandleStruct             FontDescriptorSet;
    RedHandleMemory             UploadBufferMemory;
    RedArray                    UploadBuffer;

    // Render buffers
    ImGui_ImplRedGpuH_WindowRenderBuffers MainWindowRenderBuffers;

    ImGui_ImplRedGpu_Data()
    {
        memset((void*)this, 0, sizeof(*this));
        BufferMemoryAlignment = 256;
    }
};

// Forward Declarations
bool ImGui_ImplRedGpu_CreateDeviceObjects();
void ImGui_ImplRedGpu_DestroyDeviceObjects();
void ImGui_ImplRedGpuH_DestroyFrame(RedContext instance, uint32_t deviceIndex, RedHandleGpu device, ImGui_ImplRedGpuH_Frame* fd);
void ImGui_ImplRedGpuH_DestroyFrameSemaphores(RedContext instance, uint32_t deviceIndex, RedHandleGpu device, ImGui_ImplRedGpuH_FrameSemaphores* fsd);
void ImGui_ImplRedGpuH_DestroyFrameRenderBuffers(RedContext instance, uint32_t deviceIndex, RedHandleGpu device, ImGui_ImplRedGpuH_FrameRenderBuffers* buffers);
void ImGui_ImplRedGpuH_DestroyWindowRenderBuffers(RedContext instance, uint32_t deviceIndex, RedHandleGpu device, ImGui_ImplRedGpuH_WindowRenderBuffers* buffers);
void ImGui_ImplRedGpuH_CreateWindowSwapChain(RedContext instance, uint32_t deviceIndex, RedHandleGpuDevice physical_device, RedHandleGpu device, ImGui_ImplRedGpuH_Window* wd, int w, int h, uint32_t min_image_count);
void ImGui_ImplRedGpuH_CreateWindowCommandBuffers(RedContext instance, uint32_t deviceIndex, RedHandleGpuDevice physical_device, RedHandleGpu device, ImGui_ImplRedGpuH_Window* wd, uint32_t queue_family);

//-----------------------------------------------------------------------------
// SHADERS
//-----------------------------------------------------------------------------

/*
// C:\VulkanSDK\1.3.211.0\Bin\dxc.exe -spirv hlsl_shader.vs -T vs_6_0 -Fh hlsl_shader.vs.h

[[vk::push_constant]] struct {
  float2 scale;
  float2 translate;
} variables;

[[vk::binding(0, 2)]] ByteAddressBuffer imdrawverts;

float4 ColorConvertU32ToFloat4(uint v) {
  const float s = 1.0f / 255.0f;
  uint4 c = uint4(v & 0xff, (v >> 8) & 0xff, (v >> 16) & 0xff, v >> 24);
  return float4(c) * s;
}

struct interpolated {
  float4 pos: SV_Position;
  float4 col: Color;
  float2 uv: Uv;
};

interpolated main(uint vid: SV_VertexID, uint iid: SV_InstanceID) {
  float2 pos;
  float2 uv;
  uint   col;
  pos.x = asfloat(imdrawverts.Load((vid * 5 + 0) * 4));
  pos.y = asfloat(imdrawverts.Load((vid * 5 + 1) * 4));
  uv.x  = asfloat(imdrawverts.Load((vid * 5 + 2) * 4));
  uv.y  = asfloat(imdrawverts.Load((vid * 5 + 3) * 4));
  col   =         imdrawverts.Load((vid * 5 + 4) * 4);
  interpolated output;
  output.pos = float4(pos * variables.scale + variables.translate, 0, 1);
  output.pos.y *= -1.0f;
  output.col = ColorConvertU32ToFloat4(col);
  output.uv  = uv;
  return output;
}
*/
static unsigned char __hlsl_shader_vs_spv[] =
{
  0x03, 0x02, 0x23, 0x07, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0e, 0x00,
  0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x02, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x05, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x05, 0x00, 0x00, 0x00,
  0x58, 0x02, 0x00, 0x00, 0x05, 0x00, 0x07, 0x00, 0x06, 0x00, 0x00, 0x00,
  0x74, 0x79, 0x70, 0x65, 0x2e, 0x50, 0x75, 0x73, 0x68, 0x43, 0x6f, 0x6e,
  0x73, 0x74, 0x61, 0x6e, 0x74, 0x2e, 0x00, 0x00, 0x06, 0x00, 0x05, 0x00,
  0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x63, 0x61, 0x6c,
  0x65, 0x00, 0x00, 0x00, 0x06, 0x00, 0x06, 0x00, 0x06, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x74, 0x72, 0x61, 0x6e, 0x73, 0x6c, 0x61, 0x74,
  0x65, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x76, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6c, 0x65, 0x73, 0x00, 0x00, 0x00,
  0x05, 0x00, 0x08, 0x00, 0x08, 0x00, 0x00, 0x00, 0x74, 0x79, 0x70, 0x65,
  0x2e, 0x42, 0x79, 0x74, 0x65, 0x41, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73,
  0x42, 0x75, 0x66, 0x66, 0x65, 0x72, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00,
  0x09, 0x00, 0x00, 0x00, 0x69, 0x6d, 0x64, 0x72, 0x61, 0x77, 0x76, 0x65,
  0x72, 0x74, 0x73, 0x00, 0x05, 0x00, 0x06, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x6f, 0x75, 0x74, 0x2e, 0x76, 0x61, 0x72, 0x2e, 0x43, 0x6f, 0x6c, 0x6f,
  0x72, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x05, 0x00, 0x00, 0x00,
  0x6f, 0x75, 0x74, 0x2e, 0x76, 0x61, 0x72, 0x2e, 0x55, 0x76, 0x00, 0x00,
  0x05, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e,
  0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x0b, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x47, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x05, 0x00, 0x00, 0x00,
  0x1e, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00,
  0x09, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x47, 0x00, 0x04, 0x00, 0x09, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0x06, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x48, 0x00, 0x05, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x23, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x47, 0x00, 0x03, 0x00,
  0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00,
  0x0a, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x48, 0x00, 0x05, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x04, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
  0x47, 0x00, 0x03, 0x00, 0x08, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x15, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00,
  0x0b, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x2b, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x0f, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x15, 0x00, 0x04, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x2b, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x12, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x2b, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x16, 0x00, 0x03, 0x00, 0x15, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x15, 0x00, 0x00, 0x00,
  0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00,
  0x15, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f,
  0x2b, 0x00, 0x04, 0x00, 0x15, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
  0x81, 0x80, 0x80, 0x3b, 0x2b, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x19, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00,
  0x0b, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x2b, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x1c, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00,
  0x1d, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x1e, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00,
  0x1d, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x1e, 0x00, 0x00, 0x00,
  0x09, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x03, 0x00,
  0x0a, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x03, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00,
  0x1f, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x04, 0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x0b, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x21, 0x00, 0x00, 0x00,
  0x15, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00,
  0x22, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x04, 0x00, 0x23, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x1d, 0x00, 0x00, 0x00, 0x13, 0x00, 0x02, 0x00, 0x24, 0x00, 0x00, 0x00,
  0x21, 0x00, 0x03, 0x00, 0x25, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x04, 0x00, 0x26, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x0b, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x27, 0x00, 0x00, 0x00,
  0x09, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00,
  0x28, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x3b, 0x00, 0x04, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x09, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x1f, 0x00, 0x00, 0x00,
  0x09, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x3b, 0x00, 0x04, 0x00, 0x22, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x22, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00,
  0x23, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x03, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00,
  0x2b, 0x00, 0x04, 0x00, 0x15, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x80, 0xbf, 0x2b, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x2b, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00,
  0x1d, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x36, 0x00, 0x05, 0x00,
  0x24, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x25, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x02, 0x00, 0x2d, 0x00, 0x00, 0x00,
  0x3d, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x84, 0x00, 0x05, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x2f, 0x00, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
  0x84, 0x00, 0x05, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
  0x2e, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00, 0xc2, 0x00, 0x05, 0x00,
  0x0b, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
  0x0f, 0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00, 0x26, 0x00, 0x00, 0x00,
  0x32, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00,
  0x31, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x33, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x04, 0x00,
  0x15, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00,
  0x52, 0x00, 0x06, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00,
  0x34, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x80, 0x00, 0x05, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00,
  0x2f, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x84, 0x00, 0x05, 0x00,
  0x0b, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00,
  0x0e, 0x00, 0x00, 0x00, 0xc2, 0x00, 0x05, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x38, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
  0x41, 0x00, 0x06, 0x00, 0x26, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00,
  0x09, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00,
  0x3d, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x3a, 0x00, 0x00, 0x00,
  0x39, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x04, 0x00, 0x15, 0x00, 0x00, 0x00,
  0x3b, 0x00, 0x00, 0x00, 0x3a, 0x00, 0x00, 0x00, 0x52, 0x00, 0x06, 0x00,
  0x1d, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x00, 0x00,
  0x35, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x05, 0x00,
  0x0b, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00, 0x00,
  0x0f, 0x00, 0x00, 0x00, 0x84, 0x00, 0x05, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x3e, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00,
  0xc2, 0x00, 0x05, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00,
  0x3e, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00,
  0x26, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
  0x0d, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00,
  0x0b, 0x00, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
  0x7c, 0x00, 0x04, 0x00, 0x15, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00,
  0x41, 0x00, 0x00, 0x00, 0x52, 0x00, 0x06, 0x00, 0x1d, 0x00, 0x00, 0x00,
  0x43, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x05, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x44, 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x84, 0x00, 0x05, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00,
  0x44, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xc2, 0x00, 0x05, 0x00,
  0x0b, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00,
  0x0f, 0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00, 0x26, 0x00, 0x00, 0x00,
  0x47, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00,
  0x46, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x48, 0x00, 0x00, 0x00, 0x47, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x04, 0x00,
  0x15, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00,
  0x52, 0x00, 0x06, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x4a, 0x00, 0x00, 0x00,
  0x49, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x80, 0x00, 0x05, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x4b, 0x00, 0x00, 0x00,
  0x2f, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x84, 0x00, 0x05, 0x00,
  0x0b, 0x00, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x4b, 0x00, 0x00, 0x00,
  0x0e, 0x00, 0x00, 0x00, 0xc2, 0x00, 0x05, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x4d, 0x00, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
  0x41, 0x00, 0x06, 0x00, 0x26, 0x00, 0x00, 0x00, 0x4e, 0x00, 0x00, 0x00,
  0x09, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x4d, 0x00, 0x00, 0x00,
  0x3d, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x4f, 0x00, 0x00, 0x00,
  0x4e, 0x00, 0x00, 0x00, 0x41, 0x00, 0x05, 0x00, 0x27, 0x00, 0x00, 0x00,
  0x50, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00,
  0x3d, 0x00, 0x04, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x51, 0x00, 0x00, 0x00,
  0x50, 0x00, 0x00, 0x00, 0x85, 0x00, 0x05, 0x00, 0x1d, 0x00, 0x00, 0x00,
  0x52, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x51, 0x00, 0x00, 0x00,
  0x41, 0x00, 0x05, 0x00, 0x27, 0x00, 0x00, 0x00, 0x53, 0x00, 0x00, 0x00,
  0x07, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00,
  0x1d, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x53, 0x00, 0x00, 0x00,
  0x81, 0x00, 0x05, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00,
  0x52, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, 0x00,
  0x15, 0x00, 0x00, 0x00, 0x56, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x15, 0x00, 0x00, 0x00,
  0x57, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x50, 0x00, 0x07, 0x00, 0x21, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00,
  0x56, 0x00, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
  0x17, 0x00, 0x00, 0x00, 0x85, 0x00, 0x05, 0x00, 0x15, 0x00, 0x00, 0x00,
  0x59, 0x00, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00,
  0x52, 0x00, 0x06, 0x00, 0x21, 0x00, 0x00, 0x00, 0x5a, 0x00, 0x00, 0x00,
  0x59, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0xc7, 0x00, 0x05, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x5b, 0x00, 0x00, 0x00,
  0x4f, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0xc2, 0x00, 0x05, 0x00,
  0x0b, 0x00, 0x00, 0x00, 0x5c, 0x00, 0x00, 0x00, 0x4f, 0x00, 0x00, 0x00,
  0x1a, 0x00, 0x00, 0x00, 0xc7, 0x00, 0x05, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x5d, 0x00, 0x00, 0x00, 0x5c, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00,
  0xc2, 0x00, 0x05, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x5e, 0x00, 0x00, 0x00,
  0x4f, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x00, 0x00, 0xc7, 0x00, 0x05, 0x00,
  0x0b, 0x00, 0x00, 0x00, 0x5f, 0x00, 0x00, 0x00, 0x5e, 0x00, 0x00, 0x00,
  0x19, 0x00, 0x00, 0x00, 0xc2, 0x00, 0x05, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x60, 0x00, 0x00, 0x00, 0x4f, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
  0x50, 0x00, 0x07, 0x00, 0x28, 0x00, 0x00, 0x00, 0x61, 0x00, 0x00, 0x00,
  0x5b, 0x00, 0x00, 0x00, 0x5d, 0x00, 0x00, 0x00, 0x5f, 0x00, 0x00, 0x00,
  0x60, 0x00, 0x00, 0x00, 0x70, 0x00, 0x04, 0x00, 0x21, 0x00, 0x00, 0x00,
  0x62, 0x00, 0x00, 0x00, 0x61, 0x00, 0x00, 0x00, 0x8e, 0x00, 0x05, 0x00,
  0x21, 0x00, 0x00, 0x00, 0x63, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00,
  0x18, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x5a, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x63, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x05, 0x00, 0x00, 0x00,
  0x4a, 0x00, 0x00, 0x00, 0xfd, 0x00, 0x01, 0x00, 0x38, 0x00, 0x01, 0x00
};

/*
// C:\VulkanSDK\1.3.211.0\Bin\dxc.exe -spirv hlsl_shader.ps -T ps_6_0 -Fh hlsl_shader.ps.h

struct interpolated {
  float4 pos: SV_Position;
  float4 col: Color;
  float2 uv: Uv;
};

struct render {
  float4 color: SV_Target0;
};

[[vk::binding(0, 0)]] SamplerState sampler0;
[[vk::binding(0, 1)]] Texture2D    texture0;

render main(interpolated input) {
  render output;
  float4 col = input.col;
  col.rgb *= col.rgb;
  output.color = col * texture0.Sample(sampler0, input.uv);
  return output;
}
*/
static unsigned char __hlsl_shader_ps_spv[] =
{
  0x03, 0x02, 0x23, 0x07, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0e, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x02, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x08, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x10, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x03, 0x00, 0x05, 0x00, 0x00, 0x00, 0x58, 0x02, 0x00, 0x00,
  0x05, 0x00, 0x06, 0x00, 0x05, 0x00, 0x00, 0x00, 0x74, 0x79, 0x70, 0x65,
  0x2e, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x00, 0x00, 0x00, 0x00,
  0x05, 0x00, 0x05, 0x00, 0x06, 0x00, 0x00, 0x00, 0x73, 0x61, 0x6d, 0x70,
  0x6c, 0x65, 0x72, 0x30, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00,
  0x07, 0x00, 0x00, 0x00, 0x74, 0x79, 0x70, 0x65, 0x2e, 0x32, 0x64, 0x2e,
  0x69, 0x6d, 0x61, 0x67, 0x65, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x30,
  0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x69, 0x6e, 0x2e, 0x76, 0x61, 0x72, 0x2e, 0x43, 0x6f, 0x6c, 0x6f, 0x72,
  0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x69, 0x6e, 0x2e, 0x76, 0x61, 0x72, 0x2e, 0x55, 0x76, 0x00, 0x00, 0x00,
  0x05, 0x00, 0x07, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6f, 0x75, 0x74, 0x2e,
  0x76, 0x61, 0x72, 0x2e, 0x53, 0x56, 0x5f, 0x54, 0x61, 0x72, 0x67, 0x65,
  0x74, 0x30, 0x00, 0x00, 0x05, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x07, 0x00,
  0x09, 0x00, 0x00, 0x00, 0x74, 0x79, 0x70, 0x65, 0x2e, 0x73, 0x61, 0x6d,
  0x70, 0x6c, 0x65, 0x64, 0x2e, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x00, 0x00,
  0x47, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x1e, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x47, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00,
  0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x47, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x02, 0x00, 0x05, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x04, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x05, 0x00, 0x00, 0x00, 0x16, 0x00, 0x03, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x19, 0x00, 0x09, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x0b, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00,
  0x0d, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x0d, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x0f, 0x00, 0x00, 0x00,
  0x0b, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x04, 0x00, 0x11, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x0d, 0x00, 0x00, 0x00, 0x13, 0x00, 0x02, 0x00, 0x12, 0x00, 0x00, 0x00,
  0x21, 0x00, 0x03, 0x00, 0x13, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00,
  0x17, 0x00, 0x04, 0x00, 0x14, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x03, 0x00, 0x09, 0x00, 0x00, 0x00,
  0x07, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x0a, 0x00, 0x00, 0x00,
  0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00,
  0x0c, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x3b, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00,
  0x11, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x36, 0x00, 0x05, 0x00, 0x12, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x02, 0x00,
  0x15, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x0d, 0x00, 0x00, 0x00,
  0x16, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00,
  0x0f, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x4f, 0x00, 0x08, 0x00, 0x14, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
  0x16, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x85, 0x00, 0x05, 0x00,
  0x14, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
  0x18, 0x00, 0x00, 0x00, 0x4f, 0x00, 0x09, 0x00, 0x0d, 0x00, 0x00, 0x00,
  0x1a, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x1b, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00,
  0x05, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
  0x56, 0x00, 0x05, 0x00, 0x09, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00,
  0x1b, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x57, 0x00, 0x06, 0x00,
  0x0d, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00,
  0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x85, 0x00, 0x05, 0x00,
  0x0d, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x00, 0x00,
  0x1e, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x1f, 0x00, 0x00, 0x00, 0xfd, 0x00, 0x01, 0x00, 0x38, 0x00, 0x01, 0x00
};

//-----------------------------------------------------------------------------
// FUNCTIONS
//-----------------------------------------------------------------------------

// Backend data stored in io.BackendRendererUserData to allow support for multiple Dear ImGui contexts
// It is STRONGLY preferred that you use docking branch with multi-viewports (== single Dear ImGui context + multiple windows) instead of multiple Dear ImGui contexts.
// FIXME: multi-context support is not tested and probably dysfunctional in this backend.
static ImGui_ImplRedGpu_Data* ImGui_ImplRedGpu_GetBackendData()
{
    return ImGui::GetCurrentContext() ? (ImGui_ImplRedGpu_Data*)ImGui::GetIO().BackendRendererUserData : NULL;
}

typedef enum RedHelperMemoryType {
  RED_HELPER_MEMORY_TYPE_VRAM     = 0,
  RED_HELPER_MEMORY_TYPE_UPLOAD   = 1,
  RED_HELPER_MEMORY_TYPE_READBACK = 2,
} RedHelperMemoryType;

static uint32_t ImGui_ImplRedGpu_MemoryType(const RedGpuInfo * gpuInfo, RedHelperMemoryType memoryType, uint32_t memoryTypesSupported)
{
  const uint32_t        memoryTypesCount = gpuInfo->memoryTypesCount;
  const RedMemoryType * memoryTypes      = gpuInfo->memoryTypes;

  uint32_t memoryTypeIsSupported[32];
  memoryTypeIsSupported[0]  = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0001)) == 0 ? 0 : 1;
  memoryTypeIsSupported[1]  = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0010)) == 0 ? 0 : 1;
  memoryTypeIsSupported[2]  = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,0100)) == 0 ? 0 : 1;
  memoryTypeIsSupported[3]  = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,0000,0000,0000,0000,1000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[4]  = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,0000,0000,0000,0001,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[5]  = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,0000,0000,0000,0010,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[6]  = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,0000,0000,0000,0100,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[7]  = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,0000,0000,0000,1000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[8]  = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,0000,0000,0001,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[9]  = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,0000,0000,0010,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[10] = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,0000,0000,0100,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[11] = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,0000,0000,1000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[12] = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,0000,0001,0000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[13] = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,0000,0010,0000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[14] = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,0000,0100,0000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[15] = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,0000,1000,0000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[16] = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,0001,0000,0000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[17] = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,0010,0000,0000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[18] = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,0100,0000,0000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[19] = (memoryTypesSupported & REDGPU_B32(0000,0000,0000,1000,0000,0000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[20] = (memoryTypesSupported & REDGPU_B32(0000,0000,0001,0000,0000,0000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[21] = (memoryTypesSupported & REDGPU_B32(0000,0000,0010,0000,0000,0000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[22] = (memoryTypesSupported & REDGPU_B32(0000,0000,0100,0000,0000,0000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[23] = (memoryTypesSupported & REDGPU_B32(0000,0000,1000,0000,0000,0000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[24] = (memoryTypesSupported & REDGPU_B32(0000,0001,0000,0000,0000,0000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[25] = (memoryTypesSupported & REDGPU_B32(0000,0010,0000,0000,0000,0000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[26] = (memoryTypesSupported & REDGPU_B32(0000,0100,0000,0000,0000,0000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[27] = (memoryTypesSupported & REDGPU_B32(0000,1000,0000,0000,0000,0000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[28] = (memoryTypesSupported & REDGPU_B32(0001,0000,0000,0000,0000,0000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[29] = (memoryTypesSupported & REDGPU_B32(0010,0000,0000,0000,0000,0000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[30] = (memoryTypesSupported & REDGPU_B32(0100,0000,0000,0000,0000,0000,0000,0000)) == 0 ? 0 : 1;
  memoryTypeIsSupported[31] = (memoryTypesSupported & REDGPU_B32(1000,0000,0000,0000,0000,0000,0000,0000)) == 0 ? 0 : 1;

  if (memoryType == RED_HELPER_MEMORY_TYPE_VRAM) {
    for (uint32_t i = 0; i < memoryTypesCount; i += 1) {
      const RedMemoryType * type = &memoryTypes[i];
      if (type->isGpuVram == 1 && memoryTypeIsSupported[i] == 1) {
        return i;
      }
    }
  } else if (memoryType == RED_HELPER_MEMORY_TYPE_UPLOAD) {
    for (uint32_t i = 0; i < memoryTypesCount; i += 1) {
      const RedMemoryType * type = &memoryTypes[i];
      if (type->isCpuMappable == 1 &&
          type->isCpuCoherent == 1 &&
          type->isCpuCached   == 0 && memoryTypeIsSupported[i] == 1)
      {
        return i;
      }
    }
    for (uint32_t i = 0; i < memoryTypesCount; i += 1) {
      const RedMemoryType * type = &memoryTypes[i];
      if (type->isCpuMappable == 1 &&
          type->isCpuCoherent == 1 && memoryTypeIsSupported[i] == 1)
      {
        return i;
      }
    }
  } else if (memoryType == RED_HELPER_MEMORY_TYPE_READBACK) {
    for (uint32_t i = 0; i < memoryTypesCount; i += 1) {
      const RedMemoryType * type = &memoryTypes[i];
      if (type->isCpuMappable == 1 &&
          type->isCpuCoherent == 1 &&
          type->isCpuCached   == 1 && memoryTypeIsSupported[i] == 1)
      {
        return i;
      }
    }
    for (uint32_t i = 0; i < memoryTypesCount; i += 1) {
      const RedMemoryType * type = &memoryTypes[i];
      if (type->isCpuMappable == 1 &&
          type->isCpuCoherent == 1 && memoryTypeIsSupported[i] == 1)
      {
        return i;
      }
    }
  }

  return -1;
}

static void CreateOrResizeBuffer(RedArray * buffer_ptr, RedHandleMemory * buffer_memory_ptr, size_t new_size, bool isIndexBuffer)
{
    IM_ASSERT(buffer_ptr != NULL);
    IM_ASSERT(buffer_memory_ptr != NULL);

    RedArray buffer = buffer_ptr[0];
    RedHandleMemory buffer_memory = buffer_memory_ptr[0];

    ImGui_ImplRedGpu_Data* bd = ImGui_ImplRedGpu_GetBackendData();
    ImGui_ImplRedGpu_InitInfo* v = &bd->RedGpuInitInfo;

    if (buffer.handle != NULL)
    {
        redDestroyArray(v->Instance, v->Device, buffer.handle, __FILE__, __LINE__, NULL);
        RedArray defaults = {};
        buffer = defaults;
    }
    if (buffer_memory != NULL)
    {
        redMemoryFree(v->Instance, v->Device, buffer_memory, __FILE__, __LINE__, NULL);
        buffer_memory = NULL;
    }

    uint64_t buffer_size_aligned = ((new_size - 1) / bd->BufferMemoryAlignment + 1) * bd->BufferMemoryAlignment;

    redCreateArray(v->Instance, v->Device, NULL, isIndexBuffer == true ? RED_ARRAY_TYPE_INDEX_RO : RED_ARRAY_TYPE_ARRAY_R0, buffer_size_aligned, 0, 0, 0, 0, &buffer, NULL, __FILE__, __LINE__, NULL);

    bd->BufferMemoryAlignment = (bd->BufferMemoryAlignment > buffer.memoryBytesAlignment) ? bd->BufferMemoryAlignment : buffer.memoryBytesAlignment;

    redMemoryAllocateMappable(v->Instance, v->Device, NULL, 0, buffer.handle, buffer.memoryBytesCount, ImGui_ImplRedGpu_MemoryType(&v->Instance->gpus[v->DeviceIndex], RED_HELPER_MEMORY_TYPE_UPLOAD, buffer.memoryTypesSupported), 0, &buffer_memory, NULL, __FILE__, __LINE__, NULL);

    RedMemoryArray memoryArray = {};
    memoryArray.setTo1000157000  = 1000157000;
    memoryArray.setTo0           = 0;
    memoryArray.array            = buffer.handle;
    memoryArray.memory           = buffer_memory;
    memoryArray.memoryBytesFirst = 0;
    redMemorySet(v->Instance, v->Device, 1, &memoryArray, 0, NULL, NULL, __FILE__, __LINE__, NULL);

    buffer_ptr[0] = buffer;
    buffer_memory_ptr[0] = buffer_memory;
}

static void ImGui_ImplRedGpu_SetupRenderState(ImDrawData* draw_data, RedHandleProcedure pipeline, RedHandleCalls command_buffer, ImGui_ImplRedGpuH_FrameRenderBuffers* rb, int fb_width, int fb_height)
{
    IM_ASSERT(sizeof(ImDrawIdx) == 4);

    ImGui_ImplRedGpu_Data* bd = ImGui_ImplRedGpu_GetBackendData();
    ImGui_ImplRedGpu_InitInfo* v = &bd->RedGpuInitInfo;

    RedCallProceduresAndAddresses cpa;
    redGetCallProceduresAndAddresses(v->Instance, v->Device, &cpa, NULL, __FILE__, __LINE__, NULL);

    // Bind pipeline:
    {
        cpa.redCallSetProcedure(command_buffer, RED_PROCEDURE_TYPE_DRAW, pipeline);
    }

    // Bind Vertex And Index Buffer:
    if (draw_data->TotalVtxCount > 0)
    {
        RedProcedureParametersHandleArray parametersHandleArray = {};
        parametersHandleArray.array         = rb->VertexBuffer.handle;
        parametersHandleArray.setTo0        = 0;
        parametersHandleArray.setToMaxValue = -1;
        RedProcedureParametersHandle parametersHandle = {};
        parametersHandle.setTo35    = 35;
        parametersHandle.setTo0     = 0;
        parametersHandle.setTo00    = 0;
        parametersHandle.slot       = 0;
        parametersHandle.setTo000   = 0;
        parametersHandle.setTo1     = 1;
        parametersHandle.type       = RED_PROCEDURE_PARAMETERS_HANDLE_TYPE_ARRAY_RO_RW;
        parametersHandle.setTo0000  = 0;
        parametersHandle.array      = &parametersHandleArray;
        parametersHandle.setTo00000 = 0;
        cpa.redCallSetProcedureParametersHandles(command_buffer, RED_PROCEDURE_TYPE_DRAW, bd->PipelineLayout, 2, 1, &parametersHandle);
        cpa.redCallSetProcedureIndices(command_buffer, rb->IndexBuffer.handle, 0, 1);
    }

    // Setup viewport:
    {
        redCallSetDynamicViewport(cpa.redCallSetDynamicViewport, command_buffer, 0, 0, (float)fb_width, (float)fb_height, 0.0f, 1.0f);
    }

    // Setup scale and translation:
    // Our visible imgui space lies from draw_data->DisplayPos (top left) to draw_data->DisplayPos+data_data->DisplaySize (bottom right). DisplayPos is (0,0) for single viewport apps.
    {
        float scale[2];
        scale[0] = 2.0f / draw_data->DisplaySize.x;
        scale[1] = 2.0f / draw_data->DisplaySize.y;
        float translate[2];
        translate[0] = -1.0f - draw_data->DisplayPos.x * scale[0];
        translate[1] = -1.0f - draw_data->DisplayPos.y * scale[1];
        cpa.redCallSetProcedureParametersVariables(command_buffer, bd->PipelineLayout, RED_VISIBLE_TO_STAGE_BITFLAG_VERTEX, sizeof(float) * 0, sizeof(float) * 2, scale);
        cpa.redCallSetProcedureParametersVariables(command_buffer, bd->PipelineLayout, RED_VISIBLE_TO_STAGE_BITFLAG_VERTEX, sizeof(float) * 2, sizeof(float) * 2, translate);
    }
}

// Render function
void ImGui_ImplRedGpu_RenderDrawData(ImDrawData* draw_data, RedHandleCalls command_buffer, RedHandleProcedure pipeline)
{
    // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
    int fb_width  = (int)(draw_data->DisplaySize.x * draw_data->FramebufferScale.x);
    int fb_height = (int)(draw_data->DisplaySize.y * draw_data->FramebufferScale.y);
    if (fb_width <= 0 || fb_height <= 0)
        return;

    ImGui_ImplRedGpu_Data* bd = ImGui_ImplRedGpu_GetBackendData();
    ImGui_ImplRedGpu_InitInfo* v = &bd->RedGpuInitInfo;
    if (pipeline == NULL)
        pipeline = bd->Pipeline;

    // Allocate array to store enough vertex/index buffers
    ImGui_ImplRedGpuH_WindowRenderBuffers* wrb = &bd->MainWindowRenderBuffers;
    if (wrb->FrameRenderBuffers == NULL)
    {
        wrb->Index = 0;
        wrb->Count = v->ImageCount;
        wrb->FrameRenderBuffers = (ImGui_ImplRedGpuH_FrameRenderBuffers*)IM_ALLOC(sizeof(ImGui_ImplRedGpuH_FrameRenderBuffers) * wrb->Count);
        memset(wrb->FrameRenderBuffers, 0, sizeof(ImGui_ImplRedGpuH_FrameRenderBuffers) * wrb->Count);
    }
    IM_ASSERT(wrb->Count == v->ImageCount);
    wrb->Index = (wrb->Index + 1) % wrb->Count;
    ImGui_ImplRedGpuH_FrameRenderBuffers* rb = &wrb->FrameRenderBuffers[wrb->Index];

    if (draw_data->TotalVtxCount > 0)
    {
        // Create or resize the vertex/index buffers
        size_t vertex_size = draw_data->TotalVtxCount * sizeof(ImDrawVert);
        size_t index_size  = draw_data->TotalIdxCount * sizeof(ImDrawIdx);
        if (rb->VertexBuffer.handle == NULL || rb->VertexBuffer.memoryBytesCount < vertex_size)
            CreateOrResizeBuffer(&rb->VertexBuffer, &rb->VertexBufferMemory, vertex_size, false);
        if (rb->IndexBuffer.handle == NULL || rb->IndexBuffer.memoryBytesCount < index_size)
            CreateOrResizeBuffer(&rb->IndexBuffer, &rb->IndexBufferMemory, index_size, true);

        // Upload vertex/index data into a single contiguous GPU buffer
        volatile ImDrawVert* vtx_dst = NULL;
        volatile ImDrawIdx*  idx_dst = NULL;
        redMemoryMap(v->Instance, v->Device, rb->VertexBufferMemory, 0, rb->VertexBuffer.memoryBytesCount, (void **)&vtx_dst, NULL, __FILE__, __LINE__, NULL);
        redMemoryMap(v->Instance, v->Device, rb->IndexBufferMemory,  0, rb->IndexBuffer.memoryBytesCount,  (void **)&idx_dst, NULL, __FILE__, __LINE__, NULL);
        for (int n = 0; n < draw_data->CmdListsCount; n++)
        {
            const ImDrawList* cmd_list = draw_data->CmdLists[n];
            memcpy((void *)vtx_dst, cmd_list->VtxBuffer.Data, cmd_list->VtxBuffer.Size * sizeof(ImDrawVert));
            memcpy((void *)idx_dst, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));
            vtx_dst += cmd_list->VtxBuffer.Size;
            idx_dst += cmd_list->IdxBuffer.Size;
        }
        RedMappableMemoryRange ranges[2] = {};
        ranges[0].setTo6                        = 6;
        ranges[0].setTo0                        = 0;
        ranges[0].mappableMemory                = rb->VertexBufferMemory;
        ranges[0].mappableMemoryRangeBytesFirst = 0;
        ranges[0].mappableMemoryRangeBytesCount = -1;
        ranges[1].setTo6                        = 6;
        ranges[1].setTo0                        = 0;
        ranges[1].mappableMemory                = rb->IndexBufferMemory;
        ranges[1].mappableMemoryRangeBytesFirst = 0;
        ranges[1].mappableMemoryRangeBytesCount = -1;
        redMemoryNonCoherentFlush(v->Instance, v->Device, 2, ranges, NULL, __FILE__, __LINE__, NULL);
        redMemoryUnmap(v->Instance, v->Device, rb->VertexBufferMemory, __FILE__, __LINE__, NULL);
        redMemoryUnmap(v->Instance, v->Device, rb->IndexBufferMemory,  __FILE__, __LINE__, NULL);
        vtx_dst = NULL;
        idx_dst = NULL;
    }

    // Setup desired RedGpu state
    ImGui_ImplRedGpu_SetupRenderState(draw_data, pipeline, command_buffer, rb, fb_width, fb_height);

    // Will project scissor/clipping rectangles into framebuffer space
    ImVec2 clip_off   = draw_data->DisplayPos;       // (0,0) unless using multi-viewports
    ImVec2 clip_scale = draw_data->FramebufferScale; // (1,1) unless using retina display which are often (2,2)

    RedCallProceduresAndAddresses cpa;
    redGetCallProceduresAndAddresses(v->Instance, v->Device, &cpa, NULL, __FILE__, __LINE__, NULL);

    // Render command lists
    // (Because we merged all buffers into a single one, we maintain our own offset into them)
    int global_vtx_offset = 0;
    int global_idx_offset = 0;
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
        {
            const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
            if (pcmd->UserCallback != NULL)
            {
                // User callback, registered via ImDrawList::AddCallback()
                // (ImDrawCallback_ResetRenderState is a special callback value used by the user to request the renderer to reset render state.)
                if (pcmd->UserCallback == ImDrawCallback_ResetRenderState)
                    ImGui_ImplRedGpu_SetupRenderState(draw_data, pipeline, command_buffer, rb, fb_width, fb_height);
                else
                    pcmd->UserCallback(cmd_list, pcmd);
            }
            else
            {
                // Project scissor/clipping rectangles into framebuffer space
                ImVec2 clip_min((pcmd->ClipRect.x - clip_off.x) * clip_scale.x, (pcmd->ClipRect.y - clip_off.y) * clip_scale.y);
                ImVec2 clip_max((pcmd->ClipRect.z - clip_off.x) * clip_scale.x, (pcmd->ClipRect.w - clip_off.y) * clip_scale.y);

                // Clamp to viewport as redCallSetDynamicScissor() won't accept values that are off bounds
                if (clip_min.x < 0.0f) { clip_min.x = 0.0f; }
                if (clip_min.y < 0.0f) { clip_min.y = 0.0f; }
                if (clip_max.x > fb_width)  { clip_max.x = (float)fb_width;  }
                if (clip_max.y > fb_height) { clip_max.y = (float)fb_height; }
                if (clip_max.x <= clip_min.x || clip_max.y <= clip_min.y)
                    continue;

                // Apply scissor/clipping rectangle
                redCallSetDynamicScissor(cpa.redCallSetDynamicScissor, command_buffer, (int32_t)(clip_min.x), (int32_t)(clip_min.y), (uint32_t)(clip_max.x - clip_min.x), (uint32_t)(clip_max.y - clip_min.y));

                // Bind DescriptorSet with font or user texture
                RedHandleStruct desc_sets[2] = { bd->FontSamplerDescriptorSet, (RedHandleStruct)pcmd->TextureId };
                if (sizeof(ImTextureID) < sizeof(ImU64))
                {
                    // We don't support texture switches if ImTextureID hasn't been redefined to be 64-bit. Do a flaky check that other textures haven't been used.
                    IM_ASSERT(pcmd->TextureId == (ImTextureID)bd->FontDescriptorSet);
                    desc_sets[1] = bd->FontDescriptorSet;
                }
                cpa.redCallSetProcedureParametersStructs(command_buffer, RED_PROCEDURE_TYPE_DRAW, bd->PipelineLayout, 0, 2, desc_sets, 0, 0);

                // Draw
                cpa.redCallProcedureIndexed(command_buffer, pcmd->ElemCount, 1, pcmd->IdxOffset + global_idx_offset, pcmd->VtxOffset + global_vtx_offset, 0);
            }
        }
        global_idx_offset += cmd_list->IdxBuffer.Size;
        global_vtx_offset += cmd_list->VtxBuffer.Size;
    }

    // Note: at this point both redCallSetDynamicViewport() and redCallSetDynamicScissor() have been called.
    // Our last values will leak into user/application rendering IF:
    // - Your app uses a pipeline with RedProcedureState::viewportDynamic or RedProcedureState::scissorDynamic dynamic state
    // - And you forgot to call redCallSetDynamicViewport() and redCallSetDynamicScissor() yourself to explicitely set that state.
    // If you use RedProcedureState::viewportDynamic or RedProcedureState::scissorDynamic you are responsible for setting the values before rendering.
    // In theory we should aim to backup/restore those values but I am not sure this is possible.
    // We perform a call to redCallSetDynamicScissor() to set back a full viewport which is likely to fix things for 99% users but technically this is not perfect. (See github #4644)
    redCallSetDynamicScissor(cpa.redCallSetDynamicScissor, command_buffer, 0, 0, (uint32_t)fb_width, (uint32_t)fb_height);
}

bool ImGui_ImplRedGpu_CreateFontsTexture(RedHandleCalls command_buffer)
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplRedGpu_Data* bd = ImGui_ImplRedGpu_GetBackendData();
    ImGui_ImplRedGpu_InitInfo* v = &bd->RedGpuInitInfo;

    RedCallProceduresAndAddresses cpa;
    redGetCallProceduresAndAddresses(v->Instance, v->Device, &cpa, NULL, __FILE__, __LINE__, NULL);

    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
    size_t upload_size = width * height * 4 * sizeof(char);

    // Create the Image:
    {
        redCreateImage(v->Instance, v->Device, NULL, RED_IMAGE_DIMENSIONS_2D, RED_FORMAT_RGBA_8_8_8_8_UINT_TO_FLOAT_0_1_GAMMA_CORRECTED, width, height, 1, 1, 1, RED_MULTISAMPLE_COUNT_BITFLAG_1, 0, 0, 0, 0, &bd->FontImage, NULL, __FILE__, __LINE__, NULL);
        redMemoryAllocate(v->Instance, v->Device, NULL, bd->FontImage.memoryBytesCount, ImGui_ImplRedGpu_MemoryType(&v->Instance->gpus[v->DeviceIndex], RED_HELPER_MEMORY_TYPE_VRAM, bd->FontImage.memoryTypesSupported), 0, 0, 0, &bd->FontMemory, NULL, __FILE__, __LINE__, NULL);
        RedMemoryImage memoryImage = {};
        memoryImage.setTo1000157001  = 1000157001;
        memoryImage.setTo0           = 0;
        memoryImage.image            = bd->FontImage.handle;
        memoryImage.memory           = bd->FontMemory;
        memoryImage.memoryBytesFirst = 0;
        redMemorySet(v->Instance, v->Device, 0, NULL, 1, &memoryImage, NULL, __FILE__, __LINE__, NULL);
    }

    // Create the Image View:
    {
        redCreateTexture(v->Instance, v->Device, NULL, bd->FontImage.handle, RED_IMAGE_PART_BITFLAG_COLOR, RED_TEXTURE_DIMENSIONS_2D, RED_FORMAT_RGBA_8_8_8_8_UINT_TO_FLOAT_0_1_GAMMA_CORRECTED, 0, 1, 0, 1, 0, &bd->FontView, NULL, __FILE__, __LINE__, NULL);
    }

    // Create the Descriptor Set:
    bd->FontDescriptorSet = (RedHandleStruct)ImGui_ImplRedGpu_AddTexture(bd->FontSampler, bd->FontView);

    // Create the Upload Buffer:
    {
        redCreateArray(v->Instance, v->Device, NULL, RED_ARRAY_TYPE_ARRAY_R0, upload_size, 0, 0, 0, 0, &bd->UploadBuffer, NULL, __FILE__, __LINE__, NULL);

        bd->BufferMemoryAlignment = (bd->BufferMemoryAlignment > bd->UploadBuffer.memoryBytesAlignment) ? bd->BufferMemoryAlignment : bd->UploadBuffer.memoryBytesAlignment;

        redMemoryAllocateMappable(v->Instance, v->Device, NULL, 0, bd->UploadBuffer.handle, bd->UploadBuffer.memoryBytesCount, ImGui_ImplRedGpu_MemoryType(&v->Instance->gpus[v->DeviceIndex], RED_HELPER_MEMORY_TYPE_UPLOAD, bd->UploadBuffer.memoryTypesSupported), 0, &bd->UploadBufferMemory, NULL, __FILE__, __LINE__, NULL);

        RedMemoryArray memoryArray = {};
        memoryArray.setTo1000157000  = 1000157000;
        memoryArray.setTo0           = 0;
        memoryArray.array            = bd->UploadBuffer.handle;
        memoryArray.memory           = bd->UploadBufferMemory;
        memoryArray.memoryBytesFirst = 0;
        redMemorySet(v->Instance, v->Device, 1, &memoryArray, 0, NULL, NULL, __FILE__, __LINE__, NULL);
    }

    // Upload to Buffer:
    {
        char* map = NULL;
        redMemoryMap(v->Instance, v->Device, bd->UploadBufferMemory, 0, upload_size, (void **)&map, NULL, __FILE__, __LINE__, NULL);

        memcpy(map, pixels, upload_size);

        RedMappableMemoryRange ranges[1] = {};
        ranges[0].setTo6                        = 6;
        ranges[0].setTo0                        = 0;
        ranges[0].mappableMemory                = bd->UploadBufferMemory;
        ranges[0].mappableMemoryRangeBytesFirst = 0;
        ranges[0].mappableMemoryRangeBytesCount = -1;
        redMemoryNonCoherentFlush(v->Instance, v->Device, 1, ranges, NULL, __FILE__, __LINE__, NULL);

        redMemoryUnmap(v->Instance, v->Device, bd->UploadBufferMemory, __FILE__, __LINE__, NULL);
        map = NULL;
    }

    // Copy to Image:
    {
        RedUsageImage copy_barrier[1] = {};
        copy_barrier[0].barrierSplit           = RED_BARRIER_SPLIT_NONE;
        copy_barrier[0].oldAccessStages        = 0;
        copy_barrier[0].newAccessStages        = RED_ACCESS_STAGE_BITFLAG_COPY;
        copy_barrier[0].oldAccess              = 0;
        copy_barrier[0].newAccess              = RED_ACCESS_BITFLAG_COPY_W;
        copy_barrier[0].oldState               = RED_STATE_UNUSABLE;
        copy_barrier[0].newState               = RED_STATE_USABLE;
        copy_barrier[0].queueFamilyIndexSource = -1;
        copy_barrier[0].queueFamilyIndexTarget = -1;
        copy_barrier[0].image                  = bd->FontImage.handle;
        copy_barrier[0].imageAllParts          = RED_IMAGE_PART_BITFLAG_COLOR;
        copy_barrier[0].imageLevelsFirst       = 0;
        copy_barrier[0].imageLevelsCount       = 1;
        copy_barrier[0].imageLayersFirst       = 0;
        copy_barrier[0].imageLayersCount       = 1;
        redCallUsageAliasOrderBarrier(cpa.redCallUsageAliasOrderBarrier, command_buffer, v->Instance, 0, NULL, 1, copy_barrier, 0, NULL, 0, NULL, 0);

        RedCopyArrayImageRange copyRange        = {};
        copyRange.arrayBytesFirst               = 0;
        copyRange.arrayTexelsCountToNextRow     = 0;
        copyRange.arrayTexelsCountToNextLayerOr3DDepthSliceDividedByTexelsCountToNextRow = 0;
        copyRange.imageParts.allParts           = RED_IMAGE_PART_BITFLAG_COLOR;
        copyRange.imageParts.level              = 0;
        copyRange.imageParts.layersFirst        = 0;
        copyRange.imageParts.layersCount        = 1;
        copyRange.imageOffset.texelX            = 0;
        copyRange.imageOffset.texelY            = 0;
        copyRange.imageOffset.texelZ            = 0;
        copyRange.imageExtent.texelsCountWidth  = width;
        copyRange.imageExtent.texelsCountHeight = height;
        copyRange.imageExtent.texelsCountDepth  = 1;
        cpa.redCallCopyArrayToImage(command_buffer, bd->UploadBuffer.handle, bd->FontImage.handle, 1, 1, &copyRange);

        RedUsageImage use_barrier[1] = {};
        use_barrier[0].barrierSplit           = RED_BARRIER_SPLIT_NONE;
        use_barrier[0].oldAccessStages        = RED_ACCESS_STAGE_BITFLAG_COPY;
        use_barrier[0].newAccessStages        = RED_ACCESS_STAGE_BITFLAG_FRAGMENT;
        use_barrier[0].oldAccess              = RED_ACCESS_BITFLAG_COPY_W;
        use_barrier[0].newAccess              = RED_ACCESS_BITFLAG_STRUCT_RESOURCE_FRAGMENT_STAGE_R;
        use_barrier[0].oldState               = RED_STATE_USABLE;
        use_barrier[0].newState               = RED_STATE_USABLE;
        use_barrier[0].queueFamilyIndexSource = -1;
        use_barrier[0].queueFamilyIndexTarget = -1;
        use_barrier[0].image                  = bd->FontImage.handle;
        use_barrier[0].imageAllParts          = RED_IMAGE_PART_BITFLAG_COLOR;
        use_barrier[0].imageLevelsFirst       = 0;
        use_barrier[0].imageLevelsCount       = 1;
        use_barrier[0].imageLayersFirst       = 0;
        use_barrier[0].imageLayersCount       = 1;
        redCallUsageAliasOrderBarrier(cpa.redCallUsageAliasOrderBarrier, command_buffer, v->Instance, 0, NULL, 1, use_barrier, 0, NULL, 0, NULL, 0);
    }

    // Store our identifier
    io.Fonts->SetTexID((ImTextureID)bd->FontDescriptorSet);

    return true;
}

static void ImGui_ImplRedGpu_CreateShaderModules(RedContext instance, uint32_t deviceIndex, RedHandleGpu device)
{
    // Create the shader modules
    ImGui_ImplRedGpu_Data* bd = ImGui_ImplRedGpu_GetBackendData();
    if (bd->ShaderModuleVert == NULL)
    {
        redCreateGpuCode(instance, device, NULL,  sizeof(__hlsl_shader_vs_spv), __hlsl_shader_vs_spv, &bd->ShaderModuleVert, NULL, __FILE__, __LINE__, NULL);
    }
    if (bd->ShaderModuleFrag == NULL)
    {
        redCreateGpuCode(instance, device, NULL,  sizeof(__hlsl_shader_ps_spv), __hlsl_shader_ps_spv, &bd->ShaderModuleFrag, NULL, __FILE__, __LINE__, NULL);
    }
}

static void ImGui_ImplRedGpu_CreateFontSampler(RedContext instance, uint32_t deviceIndex, RedHandleGpu device)
{
    ImGui_ImplRedGpu_Data* bd = ImGui_ImplRedGpu_GetBackendData();
    if (bd->FontSampler)
        return;

    // Bilinear sampling is required by default. Set 'io.Fonts->Flags |= ImFontAtlasFlags_NoBakedLines' or 'style.AntiAliasedLinesUseTex = false' to allow point/nearest sampling.
    redCreateSampler(instance, device, NULL, RED_SAMPLER_FILTERING_LINEAR, RED_SAMPLER_FILTERING_LINEAR, RED_SAMPLER_FILTERING_MIP_LINEAR, RED_SAMPLER_BEHAVIOR_OUTSIDE_TEXTURE_COORDINATE_REPEAT, RED_SAMPLER_BEHAVIOR_OUTSIDE_TEXTURE_COORDINATE_REPEAT, RED_SAMPLER_BEHAVIOR_OUTSIDE_TEXTURE_COORDINATE_REPEAT, 0.0f, 0, 1.0f, 0, RED_COMPARE_OP_NEVER, -1000.0f, 1000.0f, &bd->FontSampler, NULL, __FILE__, __LINE__, NULL);
}

static void ImGui_ImplRedGpu_CreateDescriptorSetLayouts(RedContext instance, uint32_t deviceIndex, RedHandleGpu device)
{
    ImGui_ImplRedGpu_Data* bd = ImGui_ImplRedGpu_GetBackendData();
    if (bd->SamplerDescriptorSetLayout == NULL)
    {
        RedStructDeclarationMember member;
        member.slot            = 0;
        member.type            = RED_STRUCT_MEMBER_TYPE_SAMPLER;
        member.count           = 1;
        member.visibleToStages = RED_VISIBLE_TO_STAGE_BITFLAG_FRAGMENT;
        member.inlineSampler   = &bd->FontSampler; // NOTE(Constantine): Using a static sampler.
        redCreateStructDeclaration(instance, device, NULL, 1, &member, 0, NULL, 0, &bd->SamplerDescriptorSetLayout, NULL, __FILE__, __LINE__, NULL);
    }
    if (bd->DescriptorSetLayout == NULL)
    {
        RedStructDeclarationMember member;
        member.slot            = 0;
        member.type            = RED_STRUCT_MEMBER_TYPE_TEXTURE_RO;
        member.count           = 1;
        member.visibleToStages = RED_VISIBLE_TO_STAGE_BITFLAG_FRAGMENT;
        member.inlineSampler   = NULL;
        redCreateStructDeclaration(instance, device, NULL, 1, &member, 0, NULL, 0, &bd->DescriptorSetLayout, NULL, __FILE__, __LINE__, NULL);
    }
    if (bd->ImdrawvertsDescriptorSetLayout == NULL)
    {
        RedStructDeclarationMember member;
        member.slot            = 0;
        member.type            = RED_STRUCT_MEMBER_TYPE_ARRAY_RO_RW;
        member.count           = 1;
        member.visibleToStages = RED_VISIBLE_TO_STAGE_BITFLAG_VERTEX;
        member.inlineSampler   = NULL;
        RedStructDeclarationMemberArrayRO memberRO;
        memberRO.slot = 0;
        redCreateStructDeclaration(instance, device, NULL, 1, &member, 1, &memberRO, 1, &bd->ImdrawvertsDescriptorSetLayout, NULL, __FILE__, __LINE__, NULL);
    }
}

static void ImGui_ImplRedGpu_CreatePipelineLayout(RedContext instance, uint32_t deviceIndex, RedHandleGpu device)
{
    ImGui_ImplRedGpu_Data* bd = ImGui_ImplRedGpu_GetBackendData();
    if (bd->PipelineLayout)
        return;

    // Constants: we are using 'vec2 offset' and 'vec2 scale' instead of a full 3d projection matrix
    ImGui_ImplRedGpu_CreateDescriptorSetLayouts(instance, deviceIndex, device);

    RedProcedureParametersDeclaration parametersDeclaration = {};
    parametersDeclaration.variablesSlot            = 0;
    parametersDeclaration.variablesVisibleToStages = RED_VISIBLE_TO_STAGE_BITFLAG_VERTEX;
    parametersDeclaration.variablesBytesCount      = sizeof(float) * 4;
    parametersDeclaration.structsDeclarationsCount = 2;
    parametersDeclaration.structsDeclarations[0]   = bd->SamplerDescriptorSetLayout;
    parametersDeclaration.structsDeclarations[1]   = bd->DescriptorSetLayout;
    parametersDeclaration.structsDeclarations[2]   = NULL;
    parametersDeclaration.structsDeclarations[3]   = NULL;
    parametersDeclaration.structsDeclarations[4]   = NULL;
    parametersDeclaration.structsDeclarations[5]   = NULL;
    parametersDeclaration.structsDeclarations[6]   = NULL;
    parametersDeclaration.handlesDeclaration       = bd->ImdrawvertsDescriptorSetLayout;
    redCreateProcedureParameters(instance, device, NULL, &parametersDeclaration, &bd->PipelineLayout, NULL, __FILE__, __LINE__, NULL);
}

static void ImGui_ImplRedGpu_CreatePipeline(RedContext instance, uint32_t deviceIndex, RedHandleGpu device, RedHandleProcedureCache pipelineCache, RedHandleOutputDeclaration renderPass, RedMultisampleCountBitflag MSAASamples, RedHandleProcedure * pipeline, uint32_t subpass)
{
    ImGui_ImplRedGpu_Data* bd = ImGui_ImplRedGpu_GetBackendData();
    ImGui_ImplRedGpu_CreateShaderModules(instance, deviceIndex, device);

    ImGui_ImplRedGpu_CreatePipelineLayout(instance, deviceIndex, device);

    RedProcedureState state = {};
    state.inputAssemblyTopology                          = RED_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    state.inputAssemblyPrimitiveRestartEnable            = 0;
    state.viewportDynamic                                = 1;
    state.viewportStaticX                                = 0;
    state.viewportStaticY                                = 0;
    state.viewportStaticWidth                            = 0;
    state.viewportStaticHeight                           = 0;
    state.viewportStaticDepthMin                         = 0;
    state.viewportStaticDepthMax                         = 0;
    state.scissorDynamic                                 = 1;
    state.scissorStaticX                                 = 0;
    state.scissorStaticY                                 = 0;
    state.scissorStaticWidth                             = 0;
    state.scissorStaticHeight                            = 0;
    state.rasterizationDepthClampEnable                  = 0;
    state.rasterizationDiscardAllPrimitivesEnable        = 0;
    state.rasterizationCullMode                          = RED_CULL_MODE_NONE;
    state.rasterizationFrontFace                         = RED_FRONT_FACE_COUNTER_CLOCKWISE;
    state.rasterizationDepthBiasEnable                   = 0;
    state.rasterizationDepthBiasDynamic                  = 0;
    state.rasterizationDepthBiasStaticConstantFactor     = 0;
    state.rasterizationDepthBiasStaticClamp              = 0;
    state.rasterizationDepthBiasStaticSlopeFactor        = 0;
    state.multisampleCount                               = (MSAASamples != 0) ? MSAASamples : RED_MULTISAMPLE_COUNT_BITFLAG_1;
    state.multisampleSampleMask                          = NULL;
    state.multisampleSampleShadingEnable                 = 0;
    state.multisampleSampleShadingMin                    = 0;
    state.multisampleAlphaToCoverageEnable               = 0;
    state.multisampleAlphaToOneEnable                    = 0;
    state.depthTestEnable                                = 0;
    state.depthTestDepthWriteEnable                      = 0;
    state.depthTestDepthCompareOp                        = RED_COMPARE_OP_GREATER_OR_EQUAL;
    state.depthTestBoundsTestEnable                      = 0;
    state.depthTestBoundsTestDynamic                     = 0;
    state.depthTestBoundsTestStaticMin                   = 0;
    state.depthTestBoundsTestStaticMax                   = 1;
    state.stencilTestEnable                              = 0;
    state.stencilTestFrontAndBackDynamicCompareMask      = 0;
    state.stencilTestFrontAndBackDynamicWriteMask        = 0;
    state.stencilTestFrontAndBackDynamicReference        = 0;
    state.stencilTestFrontStencilTestFailOp              = RED_STENCIL_OP_KEEP;
    state.stencilTestFrontStencilTestPassDepthTestPassOp = RED_STENCIL_OP_KEEP;
    state.stencilTestFrontStencilTestPassDepthTestFailOp = RED_STENCIL_OP_KEEP;
    state.stencilTestFrontCompareOp                      = RED_COMPARE_OP_NEVER;
    state.stencilTestBackStencilTestFailOp               = RED_STENCIL_OP_KEEP;
    state.stencilTestBackStencilTestPassDepthTestPassOp  = RED_STENCIL_OP_KEEP;
    state.stencilTestBackStencilTestPassDepthTestFailOp  = RED_STENCIL_OP_KEEP;
    state.stencilTestBackCompareOp                       = RED_COMPARE_OP_NEVER;
    state.stencilTestFrontAndBackStaticCompareMask       = 0;
    state.stencilTestFrontAndBackStaticWriteMask         = 0;
    state.stencilTestFrontAndBackStaticReference         = 0;
    state.blendLogicOpEnable                             = 0;
    state.blendLogicOp                                   = RED_LOGIC_OP_CLEAR;
    state.blendConstantsDynamic                          = 0;
    state.blendConstantsStatic[0]                        = 0;
    state.blendConstantsStatic[1]                        = 0;
    state.blendConstantsStatic[2]                        = 0;
    state.blendConstantsStatic[3]                        = 0;
    state.outputColorsCount                              = 1;
    state.outputColorsWriteMask[0]                       = RED_COLOR_COMPONENT_BITFLAG_R | RED_COLOR_COMPONENT_BITFLAG_G | RED_COLOR_COMPONENT_BITFLAG_B | RED_COLOR_COMPONENT_BITFLAG_A;
    state.outputColorsWriteMask[1]                       = RED_COLOR_COMPONENT_BITFLAG_R | RED_COLOR_COMPONENT_BITFLAG_G | RED_COLOR_COMPONENT_BITFLAG_B | RED_COLOR_COMPONENT_BITFLAG_A;
    state.outputColorsWriteMask[2]                       = RED_COLOR_COMPONENT_BITFLAG_R | RED_COLOR_COMPONENT_BITFLAG_G | RED_COLOR_COMPONENT_BITFLAG_B | RED_COLOR_COMPONENT_BITFLAG_A;
    state.outputColorsWriteMask[3]                       = RED_COLOR_COMPONENT_BITFLAG_R | RED_COLOR_COMPONENT_BITFLAG_G | RED_COLOR_COMPONENT_BITFLAG_B | RED_COLOR_COMPONENT_BITFLAG_A;
    state.outputColorsWriteMask[4]                       = RED_COLOR_COMPONENT_BITFLAG_R | RED_COLOR_COMPONENT_BITFLAG_G | RED_COLOR_COMPONENT_BITFLAG_B | RED_COLOR_COMPONENT_BITFLAG_A;
    state.outputColorsWriteMask[5]                       = RED_COLOR_COMPONENT_BITFLAG_R | RED_COLOR_COMPONENT_BITFLAG_G | RED_COLOR_COMPONENT_BITFLAG_B | RED_COLOR_COMPONENT_BITFLAG_A;
    state.outputColorsWriteMask[6]                       = RED_COLOR_COMPONENT_BITFLAG_R | RED_COLOR_COMPONENT_BITFLAG_G | RED_COLOR_COMPONENT_BITFLAG_B | RED_COLOR_COMPONENT_BITFLAG_A;
    state.outputColorsWriteMask[7]                       = RED_COLOR_COMPONENT_BITFLAG_R | RED_COLOR_COMPONENT_BITFLAG_G | RED_COLOR_COMPONENT_BITFLAG_B | RED_COLOR_COMPONENT_BITFLAG_A;
    for (unsigned i = 0; i < 8; i += 1) {
      state.outputColorsBlendEnable[i]                   = 1;
      state.outputColorsBlendColorFactorSource[i]        = RED_BLEND_FACTOR_SOURCE_ALPHA;
      state.outputColorsBlendColorFactorTarget[i]        = RED_BLEND_FACTOR_ONE_MINUS_SOURCE_ALPHA;
      state.outputColorsBlendColorOp[i]                  = RED_BLEND_OP_ADD;
      state.outputColorsBlendAlphaFactorSource[i]        = RED_BLEND_FACTOR_ONE;
      state.outputColorsBlendAlphaFactorTarget[i]        = RED_BLEND_FACTOR_ONE_MINUS_SOURCE_ALPHA;
      state.outputColorsBlendAlphaOp[i]                  = RED_BLEND_OP_ADD;
    }
    redCreateProcedure(instance, device, NULL, pipelineCache, renderPass, bd->PipelineLayout, "main", bd->ShaderModuleVert, "main", bd->ShaderModuleFrag, &state, NULL, 0, NULL, pipeline, NULL, __FILE__, __LINE__, NULL);
}

bool ImGui_ImplRedGpu_CreateDeviceObjects()
{
    ImGui_ImplRedGpu_Data* bd = ImGui_ImplRedGpu_GetBackendData();
    ImGui_ImplRedGpu_InitInfo* v = &bd->RedGpuInitInfo;

    ImGui_ImplRedGpu_CreateFontSampler(v->Instance, v->DeviceIndex, v->Device);
    ImGui_ImplRedGpu_CreateDescriptorSetLayouts(v->Instance, v->DeviceIndex, v->Device);
    ImGui_ImplRedGpu_CreatePipelineLayout(v->Instance, v->DeviceIndex, v->Device);
    ImGui_ImplRedGpu_CreatePipeline(v->Instance, v->DeviceIndex, v->Device, v->PipelineCache, bd->RenderPass, v->MSAASamples, &bd->Pipeline, bd->Subpass);

    return true;
}

void    ImGui_ImplRedGpu_DestroyFontUploadObjects()
{
    ImGui_ImplRedGpu_Data* bd = ImGui_ImplRedGpu_GetBackendData();
    ImGui_ImplRedGpu_InitInfo* v = &bd->RedGpuInitInfo;
    if (bd->UploadBuffer.handle)
    {
        redDestroyArray(v->Instance, v->Device, bd->UploadBuffer.handle, __FILE__, __LINE__, NULL);
        RedArray defaults = {};
        bd->UploadBuffer = defaults;
    }
    if (bd->UploadBufferMemory)
    {
        redMemoryFree(v->Instance, v->Device, bd->UploadBufferMemory, __FILE__, __LINE__, NULL);
        bd->UploadBufferMemory = NULL;
    }
}

void    ImGui_ImplRedGpu_DestroyDeviceObjects()
{
    ImGui_ImplRedGpu_Data* bd = ImGui_ImplRedGpu_GetBackendData();
    ImGui_ImplRedGpu_InitInfo* v = &bd->RedGpuInitInfo;
    ImGui_ImplRedGpuH_DestroyWindowRenderBuffers(v->Instance, v->DeviceIndex, v->Device, &bd->MainWindowRenderBuffers);
    ImGui_ImplRedGpu_DestroyFontUploadObjects();

    if (bd->ShaderModuleVert)               { redDestroyGpuCode(v->Instance, v->Device, bd->ShaderModuleVert, __FILE__, __LINE__, NULL); bd->ShaderModuleVert = NULL; }
    if (bd->ShaderModuleFrag)               { redDestroyGpuCode(v->Instance, v->Device, bd->ShaderModuleFrag, __FILE__, __LINE__, NULL); bd->ShaderModuleFrag = NULL; }
    if (bd->FontView)                       { redDestroyTexture(v->Instance, v->Device, bd->FontView, __FILE__, __LINE__, NULL); bd->FontView = NULL; }
    if (bd->FontImage.handle)               { redDestroyImage(v->Instance, v->Device, bd->FontImage.handle, __FILE__, __LINE__, NULL); RedImage defaults = {}; bd->FontImage = defaults; }
    if (bd->FontMemory)                     { redMemoryFree(v->Instance, v->Device, bd->FontMemory, __FILE__, __LINE__, NULL); bd->FontMemory = NULL; }
    if (bd->FontSampler)                    { redDestroySampler(v->Instance, v->Device, bd->FontSampler, __FILE__, __LINE__, NULL); bd->FontSampler = NULL; }
    if (bd->SamplerDescriptorSetLayout)     { redDestroyStructDeclaration(v->Instance, v->Device, bd->SamplerDescriptorSetLayout, __FILE__, __LINE__, NULL); bd->SamplerDescriptorSetLayout = NULL; }
    if (bd->DescriptorSetLayout)            { redDestroyStructDeclaration(v->Instance, v->Device, bd->DescriptorSetLayout, __FILE__, __LINE__, NULL); bd->DescriptorSetLayout = NULL; }
    if (bd->ImdrawvertsDescriptorSetLayout) { redDestroyStructDeclaration(v->Instance, v->Device, bd->ImdrawvertsDescriptorSetLayout, __FILE__, __LINE__, NULL); bd->ImdrawvertsDescriptorSetLayout = NULL; }
    if (bd->PipelineLayout)                 { redDestroyProcedureParameters(v->Instance, v->Device, bd->PipelineLayout, __FILE__, __LINE__, NULL); bd->PipelineLayout = NULL; }
    if (bd->Pipeline)                       { redDestroyProcedure(v->Instance, v->Device, bd->Pipeline, __FILE__, __LINE__, NULL); bd->Pipeline = NULL; }
}

bool    ImGui_ImplRedGpu_Init(ImGui_ImplRedGpu_InitInfo* info, RedHandleOutputDeclaration render_pass)
{
    ImGuiIO& io = ImGui::GetIO();
    IM_ASSERT(io.BackendRendererUserData == NULL && "Already initialized a renderer backend!");

    // Setup backend capabilities flags
    ImGui_ImplRedGpu_Data* bd = IM_NEW(ImGui_ImplRedGpu_Data)();
    io.BackendRendererUserData = (void*)bd;
    io.BackendRendererName = "imgui_impl_redgpu";
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;  // We can honor the ImDrawCmd::VtxOffset field, allowing for large meshes.

    IM_ASSERT(info->Instance != NULL);
    IM_ASSERT(info->PhysicalDevice != NULL);
    IM_ASSERT(info->Device != NULL);
    IM_ASSERT(info->Queue != NULL);
    IM_ASSERT(info->DescriptorPool != NULL);
    IM_ASSERT(info->DescriptorPoolSamplers != NULL);
    IM_ASSERT(info->MinImageCount >= 2);
    IM_ASSERT(info->ImageCount >= info->MinImageCount);
    IM_ASSERT(render_pass != NULL);

    bd->RedGpuInitInfo = *info;
    bd->RenderPass = render_pass;
    bd->Subpass = info->Subpass;

    ImGui_ImplRedGpu_CreateDeviceObjects();

    return true;
}

void ImGui_ImplRedGpu_Shutdown()
{
    ImGui_ImplRedGpu_Data* bd = ImGui_ImplRedGpu_GetBackendData();
    IM_ASSERT(bd != NULL && "No renderer backend to shutdown, or already shutdown?");
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplRedGpu_DestroyDeviceObjects();
    io.BackendRendererName = NULL;
    io.BackendRendererUserData = NULL;
    IM_DELETE(bd);
}

void ImGui_ImplRedGpu_NewFrame()
{
    ImGui_ImplRedGpu_Data* bd = ImGui_ImplRedGpu_GetBackendData();
    IM_ASSERT(bd != NULL && "Did you call ImGui_ImplRedGpu_Init()?");
    IM_UNUSED(bd);
}

void ImGui_ImplRedGpu_SetMinImageCount(uint32_t min_image_count, ImGui_ImplRedGpuH_Window* wd)
{
    ImGui_ImplRedGpu_Data* bd = ImGui_ImplRedGpu_GetBackendData();
    IM_ASSERT(min_image_count >= 2);
    if (bd->RedGpuInitInfo.MinImageCount == min_image_count)
        return;

    ImGui_ImplRedGpu_InitInfo* v = &bd->RedGpuInitInfo;
    //DeviceWaitIdle(v->Instance, v->DeviceIndex, v->Device);
    for (uint32_t i = 0; i < wd->ImageCount; i++)
    {
        redCpuSignalWait(v->Instance, v->Device, 1, &wd->Frames[i].Fence, 1, NULL, __FILE__, __LINE__, NULL);
    }
    ImGui_ImplRedGpuH_DestroyWindowRenderBuffers(v->Instance, v->DeviceIndex, v->Device, &bd->MainWindowRenderBuffers);
    bd->RedGpuInitInfo.MinImageCount = min_image_count;
}

// Register a texture
// FIXME: This is experimental in the sense that we are unsure how to best design/tackle this problem, please post to https://github.com/ocornut/imgui/pull/914 if you have suggestions.
RedHandleStruct ImGui_ImplRedGpu_AddTexture(RedHandleSampler sampler, RedHandleTexture image_view)
{
    ImGui_ImplRedGpu_Data* bd = ImGui_ImplRedGpu_GetBackendData();
    ImGui_ImplRedGpu_InitInfo* v = &bd->RedGpuInitInfo;

    // Create Sampler Descriptor Set:
    RedHandleStruct sampler_descriptor_set;
    {
        redStructsMemorySuballocateStructs(v->Instance, v->Device, NULL, v->DescriptorPoolSamplers, 1, &bd->SamplerDescriptorSetLayout, &sampler_descriptor_set, NULL, __FILE__, __LINE__, NULL);
    }

    // Create Descriptor Set:
    RedHandleStruct descriptor_set;
    {
        redStructsMemorySuballocateStructs(v->Instance, v->Device, NULL, v->DescriptorPool, 1, &bd->DescriptorSetLayout, &descriptor_set, NULL, __FILE__, __LINE__, NULL);
    }

    // Update the Descriptor Set:
    {
        RedStructMember members[2] = {};
        // NOTE(Constantine): Using a static sampler.
        //RedStructMemberTexture sampler0 = {};
        //sampler0.sampler = sampler;
        //sampler0.texture = NULL;
        //sampler0.setTo1  = 1;
        //members[1].setTo35   = 35;
        //members[1].setTo0    = 0;
        //members[1].structure = sampler_descriptor_set;
        //members[1].slot      = 0;
        //members[1].first     = 0;
        //members[1].count     = 1;
        //members[1].type      = RED_STRUCT_MEMBER_TYPE_SAMPLER;
        //members[1].textures  = &sampler0;
        //members[1].arrays    = NULL;
        //members[1].setTo00   = 0;
        RedStructMemberTexture texture0 = {};
        texture0.sampler = NULL;
        texture0.texture = image_view;
        texture0.setTo1  = 1;
        members[0].setTo35   = 35;
        members[0].setTo0    = 0;
        members[0].structure = descriptor_set;
        members[0].slot      = 0;
        members[0].first     = 0;
        members[0].count     = 1;
        members[0].type      = RED_STRUCT_MEMBER_TYPE_TEXTURE_RO;
        members[0].textures  = &texture0;
        members[0].arrays    = NULL;
        members[0].setTo00   = 0;
        redStructsSet(v->Instance, v->Device, 1, members, __FILE__, __LINE__, NULL);
    }

    bd->FontSamplerDescriptorSet = sampler_descriptor_set;

    return descriptor_set;
}

//-------------------------------------------------------------------------
// Internal / Miscellaneous REDGPU Helpers
// (Used by example's main.cpp. Used by multi-viewport features. PROBABLY NOT used by your own app.)
//-------------------------------------------------------------------------

RedFormat ImGui_ImplRedGpuH_SelectSurfaceFormat()
{
    return RED_FORMAT_PRESENT_BGRA_8_8_8_8_UINT_TO_FLOAT_0_1;
}

RedPresentVsyncMode ImGui_ImplRedGpuH_SelectPresentMode()
{
    return RED_PRESENT_VSYNC_MODE_OFF;
}

void ImGui_ImplRedGpuH_CreateWindowCommandBuffers(RedContext instance, uint32_t deviceIndex, RedHandleGpuDevice physical_device, RedHandleGpu device, ImGui_ImplRedGpuH_Window* wd, uint32_t queue_family)
{
    IM_ASSERT(physical_device != NULL && device != NULL);

    // Create Command Buffers
    for (uint32_t i = 0; i < wd->ImageCount; i++)
    {
        ImGui_ImplRedGpuH_Frame* fd = &wd->Frames[i];
        ImGui_ImplRedGpuH_FrameSemaphores* fsd = &wd->FrameSemaphores[i];
        {
            redCreateCallsReusable(instance, device, NULL, queue_family, &fd->CommandBuffer, NULL, __FILE__, __LINE__, NULL);
        }
        {
            redCreateCpuSignal(instance, device, NULL, 1, &fd->Fence, NULL, __FILE__, __LINE__, NULL);
        }
        {
            redCreateGpuSignal(instance, device, NULL, &fsd->ImageAcquiredSemaphore,  NULL, __FILE__, __LINE__, NULL);
            redCreateGpuSignal(instance, device, NULL, &fsd->RenderCompleteSemaphore, NULL, __FILE__, __LINE__, NULL);
        }
    }
}

int ImGui_ImplRedGpuH_GetMinImageCountFromPresentMode(RedPresentVsyncMode present_mode)
{
    return 2;
}

// Also destroy old swap chain and in-flight frames data, if any.
void ImGui_ImplRedGpuH_CreateWindowSwapChain(RedContext instance, uint32_t deviceIndex, RedHandleGpuDevice physical_device, RedHandleGpu device, ImGui_ImplRedGpuH_Window* wd, int w, int h, uint32_t min_image_count)
{
    RedHandlePresent old_swapchain = wd->Swapchain;
    wd->Swapchain = NULL;
    //DeviceWaitIdle(instance, deviceIndex, device);
    for (uint32_t i = 0; i < wd->ImageCount; i++)
    {
        redCpuSignalWait(instance, device, 1, &wd->Frames[i].Fence, 1, NULL, __FILE__, __LINE__, NULL);
    }

    // We don't use ImGui_ImplRedGpuH_DestroyWindow() because we want to preserve the old swapchain to create the new one.
    // Destroy old Framebuffer
    for (uint32_t i = 0; i < wd->ImageCount; i++)
    {
        ImGui_ImplRedGpuH_DestroyFrame(instance, deviceIndex, device, &wd->Frames[i]);
        ImGui_ImplRedGpuH_DestroyFrameSemaphores(instance, deviceIndex, device, &wd->FrameSemaphores[i]);
    }
    IM_FREE(wd->Frames);
    IM_FREE(wd->FrameSemaphores);
    wd->Frames = NULL;
    wd->FrameSemaphores = NULL;
    wd->ImageCount = 2;
    if (wd->RenderPass)
    {
        redDestroyOutputDeclaration(instance, device, wd->RenderPass, __FILE__, __LINE__, NULL);
    }
    if (wd->Pipeline)
    {
        redDestroyProcedure(instance, device, wd->Pipeline, __FILE__, __LINE__, NULL);
    }

    // If min image count was not specified, request different count of images dependent on selected present mode
    if (min_image_count == 0)
        min_image_count = ImGui_ImplRedGpuH_GetMinImageCountFromPresentMode(wd->PresentMode);

    // Create Swapchain
    {
        RedQueueFamilyIndexGetSupportsPresentOnSurface queueFamilyIndexSupportsPresentOnSurface = {};
        queueFamilyIndexSupportsPresentOnSurface.surface = wd->Surface;
        redQueueFamilyIndexGetSupportsPresent(instance, device, 0, NULL, NULL, NULL, &queueFamilyIndexSupportsPresentOnSurface, NULL, __FILE__, __LINE__, NULL);
        RedSurfaceCurrentPropertiesAndPresentLimits surfaceCurrentPropertiesAndPresentLimits = {};
        redSurfaceGetCurrentPropertiesAndPresentLimits(instance, device, wd->Surface, &surfaceCurrentPropertiesAndPresentLimits, NULL, __FILE__, __LINE__, NULL);
        if (surfaceCurrentPropertiesAndPresentLimits.currentSurfaceWidth  != -1) { w = surfaceCurrentPropertiesAndPresentLimits.currentSurfaceWidth;  }
        if (surfaceCurrentPropertiesAndPresentLimits.currentSurfaceHeight != -1) { h = surfaceCurrentPropertiesAndPresentLimits.currentSurfaceHeight; }
        wd->Width  = w;
        wd->Height = h;
        RedHandleImage   backbuffers[2]      = {};
        RedHandleTexture backbuffers_view[2] = {};
        redCreatePresent(instance, device, instance->gpus[deviceIndex].queues[0], NULL, wd->Surface, 2, w, h, 1, RED_ACCESS_BITFLAG_OUTPUT_COLOR_W, RED_SURFACE_TRANSFORM_BITFLAG_IDENTITY, RED_SURFACE_COMPOSITE_ALPHA_BITFLAG_OPAQUE, wd->PresentMode, 1, 0, old_swapchain, &wd->Swapchain, backbuffers, backbuffers_view, NULL, __FILE__, __LINE__, NULL);

        IM_ASSERT(wd->ImageCount == 2);
        IM_ASSERT(wd->Frames == NULL);
        wd->Frames = (ImGui_ImplRedGpuH_Frame*)IM_ALLOC(sizeof(ImGui_ImplRedGpuH_Frame) * wd->ImageCount);
        wd->FrameSemaphores = (ImGui_ImplRedGpuH_FrameSemaphores*)IM_ALLOC(sizeof(ImGui_ImplRedGpuH_FrameSemaphores) * wd->ImageCount);
        memset(wd->Frames, 0, sizeof(wd->Frames[0]) * wd->ImageCount);
        memset(wd->FrameSemaphores, 0, sizeof(wd->FrameSemaphores[0]) * wd->ImageCount);
        for (uint32_t i = 0; i < wd->ImageCount; i++)
        {
            wd->Frames[i].Backbuffer     = backbuffers[i];
            wd->Frames[i].BackbufferView = backbuffers_view[i];
        }
    }
    if (old_swapchain)
    {
        redDestroyPresent(instance, device, old_swapchain, __FILE__, __LINE__, NULL);
    }

    // Create the Render Pass
    {
        RedOutputDeclarationMembers members = {};
        members.depthStencilEnable                        = 0;
        members.depthStencilFormat                        = RED_FORMAT_UNDEFINED;
        members.depthStencilMultisampleCount              = RED_MULTISAMPLE_COUNT_BITFLAG_1;
        members.depthStencilDepthSetProcedureOutputOp     = RED_SET_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.depthStencilDepthEndProcedureOutputOp     = RED_END_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.depthStencilStencilSetProcedureOutputOp   = RED_SET_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.depthStencilStencilEndProcedureOutputOp   = RED_END_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.depthStencilSharesMemoryWithAnotherMember = 0;
        members.colorsCount                               = 1;
        members.colorsFormat[0]                           = RED_FORMAT_PRESENT_BGRA_8_8_8_8_UINT_TO_FLOAT_0_1;
        members.colorsFormat[1]                           = RED_FORMAT_PRESENT_BGRA_8_8_8_8_UINT_TO_FLOAT_0_1;
        members.colorsFormat[2]                           = RED_FORMAT_PRESENT_BGRA_8_8_8_8_UINT_TO_FLOAT_0_1;
        members.colorsFormat[3]                           = RED_FORMAT_PRESENT_BGRA_8_8_8_8_UINT_TO_FLOAT_0_1;
        members.colorsFormat[4]                           = RED_FORMAT_PRESENT_BGRA_8_8_8_8_UINT_TO_FLOAT_0_1;
        members.colorsFormat[5]                           = RED_FORMAT_PRESENT_BGRA_8_8_8_8_UINT_TO_FLOAT_0_1;
        members.colorsFormat[6]                           = RED_FORMAT_PRESENT_BGRA_8_8_8_8_UINT_TO_FLOAT_0_1;
        members.colorsFormat[7]                           = RED_FORMAT_PRESENT_BGRA_8_8_8_8_UINT_TO_FLOAT_0_1;
        members.colorsMultisampleCount[0]                 = RED_MULTISAMPLE_COUNT_BITFLAG_1;
        members.colorsMultisampleCount[1]                 = RED_MULTISAMPLE_COUNT_BITFLAG_1;
        members.colorsMultisampleCount[2]                 = RED_MULTISAMPLE_COUNT_BITFLAG_1;
        members.colorsMultisampleCount[3]                 = RED_MULTISAMPLE_COUNT_BITFLAG_1;
        members.colorsMultisampleCount[4]                 = RED_MULTISAMPLE_COUNT_BITFLAG_1;
        members.colorsMultisampleCount[5]                 = RED_MULTISAMPLE_COUNT_BITFLAG_1;
        members.colorsMultisampleCount[6]                 = RED_MULTISAMPLE_COUNT_BITFLAG_1;
        members.colorsMultisampleCount[7]                 = RED_MULTISAMPLE_COUNT_BITFLAG_1;
        members.colorsSetProcedureOutputOp[0]             = wd->ClearEnable ? RED_SET_PROCEDURE_OUTPUT_OP_CLEAR : RED_SET_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.colorsSetProcedureOutputOp[1]             = wd->ClearEnable ? RED_SET_PROCEDURE_OUTPUT_OP_CLEAR : RED_SET_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.colorsSetProcedureOutputOp[2]             = wd->ClearEnable ? RED_SET_PROCEDURE_OUTPUT_OP_CLEAR : RED_SET_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.colorsSetProcedureOutputOp[3]             = wd->ClearEnable ? RED_SET_PROCEDURE_OUTPUT_OP_CLEAR : RED_SET_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.colorsSetProcedureOutputOp[4]             = wd->ClearEnable ? RED_SET_PROCEDURE_OUTPUT_OP_CLEAR : RED_SET_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.colorsSetProcedureOutputOp[5]             = wd->ClearEnable ? RED_SET_PROCEDURE_OUTPUT_OP_CLEAR : RED_SET_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.colorsSetProcedureOutputOp[6]             = wd->ClearEnable ? RED_SET_PROCEDURE_OUTPUT_OP_CLEAR : RED_SET_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.colorsSetProcedureOutputOp[7]             = wd->ClearEnable ? RED_SET_PROCEDURE_OUTPUT_OP_CLEAR : RED_SET_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.colorsEndProcedureOutputOp[0]             = RED_END_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.colorsEndProcedureOutputOp[1]             = RED_END_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.colorsEndProcedureOutputOp[2]             = RED_END_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.colorsEndProcedureOutputOp[3]             = RED_END_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.colorsEndProcedureOutputOp[4]             = RED_END_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.colorsEndProcedureOutputOp[5]             = RED_END_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.colorsEndProcedureOutputOp[6]             = RED_END_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.colorsEndProcedureOutputOp[7]             = RED_END_PROCEDURE_OUTPUT_OP_PRESERVE;
        members.colorsSharesMemoryWithAnotherMember[0]    = 0;
        members.colorsSharesMemoryWithAnotherMember[1]    = 0;
        members.colorsSharesMemoryWithAnotherMember[2]    = 0;
        members.colorsSharesMemoryWithAnotherMember[3]    = 0;
        members.colorsSharesMemoryWithAnotherMember[4]    = 0;
        members.colorsSharesMemoryWithAnotherMember[5]    = 0;
        members.colorsSharesMemoryWithAnotherMember[6]    = 0;
        members.colorsSharesMemoryWithAnotherMember[7]    = 0;
        redCreateOutputDeclaration(instance, device, NULL, &members, NULL, 0, 0, &wd->RenderPass, NULL, __FILE__, __LINE__, NULL);

        // We do not create a pipeline by default as this is also used by examples' main.cpp,
        // but secondary viewport in multi-viewport mode may want to create one with:
        //ImGui_ImplRedGpu_CreatePipeline(instance, deviceIndex, device, NULL, wd->RenderPass, RED_MULTISAMPLE_COUNT_BITFLAG_1, &wd->Pipeline, bd->Subpass);
    }

    // Create Framebuffer
    {
        for (uint32_t i = 0; i < wd->ImageCount; i++)
        {
            ImGui_ImplRedGpuH_Frame* fd = &wd->Frames[i];

            RedOutputMembers outputMembers = {};
            outputMembers.depthStencil = NULL;
            outputMembers.colorsCount  = 1;
            outputMembers.colors[0]    = fd->BackbufferView;
            outputMembers.colors[1]    = NULL;
            outputMembers.colors[2]    = NULL;
            outputMembers.colors[3]    = NULL;
            outputMembers.colors[4]    = NULL;
            outputMembers.colors[5]    = NULL;
            outputMembers.colors[6]    = NULL;
            outputMembers.colors[7]    = NULL;
            redCreateOutput(instance, device, NULL, wd->RenderPass, &outputMembers, NULL, wd->Width, wd->Height, &fd->Framebuffer, NULL, __FILE__, __LINE__, NULL);
        }
    }
}

// Create or resize window
void ImGui_ImplRedGpuH_CreateOrResizeWindow(RedContext instance, uint32_t deviceIndex, RedHandleGpuDevice physical_device, RedHandleGpu device, ImGui_ImplRedGpuH_Window* wd, uint32_t queue_family, int width, int height, uint32_t min_image_count)
{
    ImGui_ImplRedGpuH_CreateWindowSwapChain(instance, deviceIndex, physical_device, device, wd, width, height, min_image_count);
    ImGui_ImplRedGpuH_CreateWindowCommandBuffers(instance, deviceIndex, physical_device, device, wd, queue_family);
}

void ImGui_ImplRedGpuH_DestroyWindow(RedContext instance, uint32_t deviceIndex, RedHandleGpu device, ImGui_ImplRedGpuH_Window* wd)
{
    //DeviceWaitIdle(instance, deviceIndex, device);
    for (uint32_t i = 0; i < wd->ImageCount; i++)
    {
        redCpuSignalWait(instance, device, 1, &wd->Frames[i].Fence, 1, NULL, __FILE__, __LINE__, NULL);
    }

    for (uint32_t i = 0; i < wd->ImageCount; i++)
    {
        ImGui_ImplRedGpuH_DestroyFrame(instance, deviceIndex, device, &wd->Frames[i]);
        ImGui_ImplRedGpuH_DestroyFrameSemaphores(instance, deviceIndex, device, &wd->FrameSemaphores[i]);
    }
    IM_FREE(wd->Frames);
    IM_FREE(wd->FrameSemaphores);
    wd->Frames = NULL;
    wd->FrameSemaphores = NULL;
    redDestroyProcedure(instance, device, wd->Pipeline, __FILE__, __LINE__, NULL);
    redDestroyOutputDeclaration(instance, device, wd->RenderPass, __FILE__, __LINE__, NULL);
    redDestroyPresent(instance, device, wd->Swapchain, __FILE__, __LINE__, NULL);
    redDestroySurface(instance, device, wd->Surface, __FILE__, __LINE__, NULL);

    *wd = ImGui_ImplRedGpuH_Window();
}

void ImGui_ImplRedGpuH_DestroyFrame(RedContext instance, uint32_t deviceIndex, RedHandleGpu device, ImGui_ImplRedGpuH_Frame* fd)
{
    redDestroyCpuSignal(instance, device, fd->Fence, __FILE__, __LINE__, NULL);
    redDestroyCalls(instance, device, fd->CommandBuffer.handle, fd->CommandBuffer.memory, __FILE__, __LINE__, NULL);
    fd->Fence = NULL;
    RedCalls defaults = {};
    fd->CommandBuffer = defaults;

    redDestroyTexture(instance, device, fd->BackbufferView, __FILE__, __LINE__, NULL);
    redDestroyOutput(instance, device, fd->Framebuffer.handle, __FILE__, __LINE__, NULL);
}

void ImGui_ImplRedGpuH_DestroyFrameSemaphores(RedContext instance, uint32_t deviceIndex, RedHandleGpu device, ImGui_ImplRedGpuH_FrameSemaphores* fsd)
{
    redDestroyGpuSignal(instance, device, fsd->ImageAcquiredSemaphore,  __FILE__, __LINE__, NULL);
    redDestroyGpuSignal(instance, device, fsd->RenderCompleteSemaphore, __FILE__, __LINE__, NULL);
    fsd->ImageAcquiredSemaphore  = NULL;
    fsd->RenderCompleteSemaphore = NULL;
}

void ImGui_ImplRedGpuH_DestroyFrameRenderBuffers(RedContext instance, uint32_t deviceIndex, RedHandleGpu device, ImGui_ImplRedGpuH_FrameRenderBuffers* buffers)
{
    if (buffers->VertexBuffer.handle) { redDestroyArray(instance, device, buffers->VertexBuffer.handle, __FILE__, __LINE__, NULL); RedArray defaults = {}; buffers->VertexBuffer = defaults; }
    if (buffers->VertexBufferMemory)  { redMemoryFree(instance, device, buffers->VertexBufferMemory, __FILE__, __LINE__, NULL); buffers->VertexBufferMemory = NULL; }
    if (buffers->IndexBuffer.handle)  { redDestroyArray(instance, device, buffers->IndexBuffer.handle, __FILE__, __LINE__, NULL); RedArray defaults = {}; buffers->IndexBuffer = defaults; }
    if (buffers->IndexBufferMemory)   { redMemoryFree(instance, device, buffers->IndexBufferMemory, __FILE__, __LINE__, NULL); buffers->IndexBufferMemory = NULL; }
    buffers->VertexBufferSize = 0;
    buffers->IndexBufferSize  = 0;
}

void ImGui_ImplRedGpuH_DestroyWindowRenderBuffers(RedContext instance, uint32_t deviceIndex, RedHandleGpu device, ImGui_ImplRedGpuH_WindowRenderBuffers* buffers)
{
    for (uint32_t n = 0; n < buffers->Count; n++)
        ImGui_ImplRedGpuH_DestroyFrameRenderBuffers(instance, deviceIndex, device, &buffers->FrameRenderBuffers[n]);
    IM_FREE(buffers->FrameRenderBuffers);
    buffers->FrameRenderBuffers = NULL;
    buffers->Index = 0;
    buffers->Count = 0;
}

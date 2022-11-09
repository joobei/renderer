#include "rl_render_lib.h"

void Renderer::create_vertex_buffer() {
    
    cgltf_options options = {cgltf_file_type_gltf};
    cgltf_result result = cgltf_parse_file(&options, "susanne.gltf", &susanne_mesh);

    size_t susanne_size = -1;
    
    if(result == cgltf_result_success) {
        memset(&options, 0, sizeof(cgltf_options));
        cgltf_load_buffers(& options, susanne_mesh, "susanne.gltf");
        susanne_size = susanne_mesh->buffers[0].size;
    }
    else
    {
        std::cerr << "cgltf load failed " << result << std::endl;
    }

    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = susanne_size;
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(device, &bufferInfo, nullptr, &vertexBuffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to create vertex buffer!");
        }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device, vertexBuffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    if (vkAllocateMemory(device, &allocInfo, nullptr, &vertexBufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate vertex buffer memory!");
    }

    vkBindBufferMemory(device, vertexBuffer, vertexBufferMemory, 0);

    void* data;
    vkMapMemory(device, vertexBufferMemory, 0, bufferInfo.size, 0, &data);
    memcpy(data, susanne_mesh->buffers[0].data, bufferInfo.size);
    vkUnmapMemory(device, vertexBufferMemory);
}

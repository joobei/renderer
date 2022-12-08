#include "rl_render_lib.h"

void Renderer::create_index_buffer() {
    
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = susanne_mesh->buffer_views[3].size;
    bufferInfo.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;

    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(device, &bufferInfo, nullptr, &indexBuffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to create vertex buffer!");
        }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device, indexBuffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    if (vkAllocateMemory(device, &allocInfo, nullptr, &indexBufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate vertex buffer memory!");
    }

    vkBindBufferMemory(device, indexBuffer, indexBufferMemory, 0);

    void* data;
    vkMapMemory(device, indexBufferMemory, 0, bufferInfo.size, 0, &data);
    memcpy(data, susanne_mesh->buffers[1].data, bufferInfo.size);
    vkUnmapMemory(device, indexBufferMemory);
}

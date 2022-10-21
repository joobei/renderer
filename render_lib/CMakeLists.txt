set(PROJECT_NAME "render_lib")
project (${PROJECT_NAME}
VERSION 1.0
DESCRIPTION "Renderer Lib"
LANGUAGES CXX
)
find_package(Vulkan REQUIRED FATAL_ERROR)


add_subdirectory("glfw")
add_library(${PROJECT_NAME} STATIC rl_render_lib.h rl_create_command_buffers.cpp rl_create_logical_device.cpp rl_create_vertex_buffer.cpp rl_create_command_pool.cpp rl_create_render_pass.cpp rl_init.cpp rl_create_framebuffers.cpp rl_pick_physical_device.cpp rl_create_graphics_pipeline.cpp rl_create_swapchain.cpp rl_validation.cpp rl_create_image_views.cpp rl_create_sync_objects.cpp rl_draw_frame.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ../dependencies/)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS} "glfw/include" "glm")
target_link_libraries(${PROJECT_NAME} glfw ${Vulkan_LIBRARIES})
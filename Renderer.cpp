#include "render_lib/rl_render_lib.h"

class HelloTriangleApplication {
public:
//    void run() {
//        initWindow();
//        initVulkan();
//        mainLoop();
//        cleanup();
//    }

private:
    Renderer vk_renderer;

    
    void initVulkan() {
        vk_renderer.create_instance();
        vk_renderer.setup_debug_messenger();
        vk_renderer.create_surface();
        vk_renderer.pick_physical_device();
        vk_renderer.create_logical_device();
        vk_renderer.create_swap_chain();
        vk_renderer.create_image_views();
        vk_renderer.create_render_pass();
        vk_renderer.create_graphics_pipeline();
        vk_renderer.create_frame_buffers();
        vk_renderer.create_command_pool();
        vk_renderer.create_vertex_buffer();
        vk_renderer.create_command_buffers();
        vk_renderer.create_sync_objects();
    }
    
    
};

int main() {
//    HelloTriangleApplication app;
//
//    try {
//        app.run();
//    }
//    catch (const std::exception& e) {
//        std::cerr << e.what() << std::endl;
//        return EXIT_FAILURE;
//    }

    return EXIT_SUCCESS;
}


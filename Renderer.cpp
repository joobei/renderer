#include "render_lib/rl_render_lib.h"

int main() {
    Renderer vk_renderer;

    try {
        vk_renderer.initWindow();
        vk_renderer.init_vulkan();
        vk_renderer.mainLoop();
        vk_renderer.cleanup();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


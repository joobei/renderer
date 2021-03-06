# CMakeList.txt : CMake project for Renderer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(PROJECT_NAME "Renderer")

project (${PROJECT_NAME} 
VERSION 1.0
DESCRIPTION "Experimental Renderer"
LANGUAGES CXX
)

add_subdirectory("glfw")

find_package(Vulkan REQUIRED FATAL_ERROR)
message("GLSC Executable: " ${Vulkan_GLSLC_EXECUTABLE})

add_executable (${PROJECT_NAME} "Renderer.cpp")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_include_directories(${PROJECT_NAME} PUBLIC "glfw/include" ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} glfw ${Vulkan_LIBRARIES})

#file(GLOB VERT ${PROJECT_SOURCE_DIR}/shaders/*.vert)
#file(GLOB FRAG ${PROJECT_SOURCE_DIR}/shaders/*.frag)

add_custom_command(TARGET ${PROJECT_NAME}
    PRE_BUILD
    COMMAND ${Vulkan_GLSLC_EXECUTABLE} ${PROJECT_SOURCE_DIR}/shaders/shader.vert -o vert.spv
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/shaders
    USES_TERMINAL
)
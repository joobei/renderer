#Tested on Windows 10 with Visual studio 2019 and MacOS Big Sur command line build using make
#check readme for build instructions
cmake_minimum_required (VERSION 3.8)

set(PROJECT_NAME "renderer")

project (${PROJECT_NAME} 
VERSION 1.0
DESCRIPTION "Experimental Renderer"
LANGUAGES CXX
)


add_subdirectory("render_lib")

find_package(Vulkan REQUIRED FATAL_ERROR)
set(Vulkan_GLSLC_EXECUTABLE "glslc")
add_executable (${PROJECT_NAME} Renderer.cpp)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_include_directories(${PROJECT_NAME} PUBLIC)
target_link_libraries(${PROJECT_NAME} render_lib)


#Compile Shaders directly to output dir to be read
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/shaders
    COMMAND ${Vulkan_GLSLC_EXECUTABLE} -fshader-stage=vert ${PROJECT_SOURCE_DIR}/shaders/vertex.glsl -o $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/shaders/vert.spv
    COMMAND ${Vulkan_GLSLC_EXECUTABLE} -fshader-stage=frag ${PROJECT_SOURCE_DIR}/shaders/fragment.glsl -o $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/shaders/frag.spv
)



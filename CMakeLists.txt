#Tested on Windows 10 with Visual studio 2019 and MacOS Big Sur command line build using make
#check readme for build instructions
cmake_minimum_required (VERSION 3.22)

if(MSVC)
    add_compile_options(/w)
    set(Vulkan_GLSLC_EXECUTABLE glslc.exe)
elseif(UNIX)
    add_compile_options(-w)
    set(Vulkan_GLSLC_EXECUTABLE glslc)
endif()

set(PROJECT_NAME "renderer")

project (${PROJECT_NAME} 
VERSION 0.1
DESCRIPTION "Experimental Renderer"
LANGUAGES CXX
)


add_subdirectory("render_lib")

find_package(Vulkan REQUIRED)

# Build HLSL shaders
add_custom_target(shaders)

function(compile_shader SHADER_NAME SHADER_TYPE)
    add_custom_command(
        OUTPUT ${SHADER_NAME}.spv
        COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/shaders
        COMMAND ${Vulkan_GLSLC_EXECUTABLE} -fshader-stage=${SHADER_TYPE} ${PROJECT_SOURCE_DIR}/shaders/${SHADER_NAME}.glsl -o $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/shaders/${SHADER_NAME}.spv
        DEPENDS ${PROJECT_SOURCE_DIR}/shaders/${SHADER_NAME}.glsl
        VERBATIM)
endfunction()

compile_shader("vertex" "vert")
compile_shader("fragment" "frag")

add_executable (${PROJECT_NAME} Renderer.cpp vertex.spv fragment.spv)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_link_libraries(${PROJECT_NAME} render_lib)
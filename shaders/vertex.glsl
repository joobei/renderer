#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec2 inPosition;
layout(location = 0) out vec3 fragColor;


float PHI = 1.61803398874989484820459;  // Golden Ratio   

float gold_noise(in vec2 xy, in float seed){
       return fract(tan(distance(xy*PHI, xy)*seed)*xy.x);
}

void main() {
    gl_Position = vec4(inPosition, 0.0, 1.0);
    fragColor = vec3(gold_noise(inPosition,inPosition.x),gold_noise(inPosition,inPosition.x),gold_noise(inPosition,inPosition.x));
}


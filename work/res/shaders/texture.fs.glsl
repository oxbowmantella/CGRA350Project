#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D mytextureSampler;

void main(){
  color = texture(mytextureSampler,UV).rgb;
}
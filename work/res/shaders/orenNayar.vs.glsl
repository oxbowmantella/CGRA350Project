#version 330 core

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;
uniform vec3 eyePosition;
uniform vec3 lightPosition;

in vec3 vertPosition;
in vec3 vertNormal;

out vec3 fragPosition;
out vec3 fragNormal;
out vec2 vTexcoords;
out vec3 vNormal;
out vec3 vViewDir;
out vec3 vLightDir;
out float vLightDistance2;

void main() {
    fragNormal = (modelMat * vec4(vertNormal, 0)).xyz;
    vec4 worldPosition = modelMat * vec4(vertPosition, 1.0f);
    vViewDir = normalize(eyePosition - worldPosition.xyz);
    vLightDir = lightPosition - worldPosition.xyz;
    vLightDistance2 = length(vLightDir);
    vLightDir /= vLightDistance2;
    vLightDistance2 *= vLightDistance2;
    
    gl_Position = projectionMat * viewMat * modelMat * vec4(vertPosition, 1.0);

    vec4 pos = viewMat * modelMat * vec4(vertPosition, 1.0);
    fragPosition = vec3(pos) / pos.w;

    mat3 normalMat = transpose(inverse(mat3(viewMat * modelMat)));
    fragNormal = normalMat * vertNormal;
}

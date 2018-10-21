#version 330 core

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

const float r = 1.0f;
const float PI = 3.1415926535897932384626433832795;


in vec3 vertPosition;

out vec2 UV;

void main() {
    gl_Position = projectionMat * viewMat * modelMat * vec4(vertPosition, 1.0);
	vec3 d = normalize(vertPosition - vec3(0,0,0));

	float v = acos(vertPosition.y)/(PI);
	float u = acos(vertPosition.x/sin(PI*v))/(2*PI);

    UV = vec2(u,v);

}

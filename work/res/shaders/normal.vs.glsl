#version 330 core

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

const float r = 1.0f;
const float PI = 3.1415926535897932384626433832795;


in vec3 vertPosition;
in vec3 vertNormal;

out vec2 UV;
out vec3 fragPosition;
out vec3 fragNormal;

void main() {
    gl_Position = projectionMat * viewMat * modelMat * vec4(vertPosition, 1.0);
	
	float v = acos(vertPosition.z/r)/PI;
	float u = acos(vertPosition.x/(r * sin(PI*v)))/(2*PI);

    UV = vec2(u,v) ;


	vec4 pos = viewMat * modelMat * vec4(vertPosition, 1.0);
    fragPosition = vec3(pos) / pos.w;

    mat3 normalMat = transpose(inverse(mat3(viewMat * modelMat)));
    fragNormal = normalMat * vertNormal;

}

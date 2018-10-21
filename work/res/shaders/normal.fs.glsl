#version 330 core

in vec2 UV;
in vec3 fragPosition;
in vec3 fragNormal;

out vec3 color;

uniform sampler2D mytextureSampler;

const vec3 lightDir = vec3(0.25, 0.25, -1);

const vec3 ambientColor = vec3(0.05, 0.05, 0.1);
const vec3 diffuseColor = vec3(1, 1, 1);
const vec3 specColor    = vec3(0.2, 0.1, 0.1);

const float shininess = 16.0;

void main() {
    vec3 rgbNormal = texture(mytextureSampler,UV).rgb;
    vec3 normal = (rgbNormal *2 ) - 0.5;   
    normal = normalize(normal + fragNormal);

    vec3 lightDir = normalize(-lightDir);

    float lambertian = max(dot(lightDir,normal), 0.0);
    float specular = 0.0;

    if (lambertian > 0.0) {
        vec3 viewDir = normalize(-fragPosition);

        vec3 halfDir = normalize(lightDir + viewDir);
        float specAngle = max(dot(halfDir, normal), 0.0);

        specular = pow(specAngle, shininess);
    }

    vec3 fragColor = ambientColor +
        lambertian * diffuseColor +
        specular * specColor;




  color = fragColor;


}

#version 330 core
#define PI 3.141592653589793238462643383279502884197

out vec4 color;

in vec3 fragPosition;
in vec3 fragNormal;

const vec3 lightDir = vec3(0, 0, -1);

const vec3 ambientColor = vec3(0.05, 0.05, 0.1);
const vec3 diffuseColor = vec3(0.4, 0.4, 1.0);
const vec3 specColor    = vec3(0.2, 0.1, 0.1);

const float shininess = 16.0;

void main() {
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(-lightDir);
    float lr = 1;
    float roughness = 0.1;
    float lambertian = max(dot(lightDir,normal), 0.0);
    float specular = 0.0;
    float albedo = pow(roughness,2);
    vec3 viewDir = normalize(-fragPosition);
    vec3 halfDir = normalize(lightDir + viewDir);
    float specAngle = max(dot(halfDir, normal), 0.0);
    
    float LdotV = dot(lightDir, viewDir);
    float NdotL = dot(lightDir, normal);
    float NdotV = dot(normal, viewDir);
    
    float s = LdotV - NdotL * NdotV;
    float t = mix(1.0, max(NdotL,NdotV), step(0.0,s));
    
    float sigma2 = roughness * roughness;
    float A = 1.0 + sigma2 * (albedo/(sigma2 + 0.13)+0.5/(sigma2+0.33));
    float B = 0.45 * sigma2 / (sigma2 + 0.09);
    
    lr = albedo * max(0.0, NdotL)*(A*B*s/t)/PI;
    

    vec3 fragColor = ambientColor +
        lambertian * diffuseColor +
        lr * specColor;

    color = vec4(fragColor, 1.0);
}

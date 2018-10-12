#version 330 core
#define PI 3.141592653589793238462643383279502884197

out vec4 color;

in vec3 fragPosition;
in vec3 fragNormal;

const vec3 lightDir = vec3(0.25, 0.25, -1);

const vec3 ambientColor = vec3(0.05, 0.05, 0.1);
const vec3 diffuseColor = vec3(0.4, 0.4, 1.0);
const vec3 specColor    = vec3(0.2, 0.1, 0.1);

const float shininess = 16.0;

void main() {
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(-lightDir);
    vec3 viewDir = normalize(-fragPosition);
    vec3 halfDir = normalize(lightDir + viewDir);
    
    float specAngle = max(dot(halfDir, normal), 0.0);
    float lambertian = max(dot(lightDir,normal), 0.0);
    float nDotL = max(dot(lightDir,normal), 0.0);
    float rs = 1;   //old was 0.0
    float specular = 0.0;
    float roughness = 0.1;
    float k = 0.2;
    float F0 = 0.8;
    
    //if(nDotL > 0){
        vec3 H = (viewDir+lightDir)/(length(viewDir+lightDir));
        float NdotH = max(0,dot(normal, H));
        float NdotV = max(0,dot(normal, viewDir));
        float vDotH = max(0, dot(viewDir, H));
        float albedo = pow(roughness,2);
    
        float F = F0 + (1-F0)*pow(1-NdotV,5);

        float D = albedo/pow(PI*(1+pow(NdotH, 2)*(albedo-1)), 2);
        
        float G = min(1, min(2*(NdotV*NdotH/vDotH), 2*(nDotL*NdotH/vDotH)));
        
        rs = (D * F * G) / (4 * nDotL * NdotV);
    //}
    vec3 fragColor = ambientColor +
    lambertian * diffuseColor +
    rs * specColor;


    color = vec4(fragColor, 1.0);
}

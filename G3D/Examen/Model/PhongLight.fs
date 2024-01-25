#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform float Ka = 0.1f;
uniform float Kd = 0.1f;
uniform float Ks = 0.1f;
uniform float eRs = 2.0f;

void main()
{

    vec3 ambient = Ka * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 diffuse = lightColor * Kd * max(dot(norm, lightDir), 0.0);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 specular = lightColor * Ks * pow(max(dot(viewDir, reflectDir), 0.0), eRs);

    vec3 result = (ambient  + diffuse + specular) * objectColor;
	FragColor = vec4(result, 1.0);
} 
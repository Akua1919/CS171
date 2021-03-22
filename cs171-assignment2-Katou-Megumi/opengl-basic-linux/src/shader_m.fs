#version 330 core
out vec4 FragColor;


struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    sampler2D ambient;
    sampler2D diffuse;
    sampler2D specular;
}; 

#define NR_POINT_LIGHTS 4

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    mat3 TBN;
} fs_in;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform Material material;
uniform sampler2D texture1;
uniform sampler2D normalmap;


// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);



void main()
{
    vec3 normal = texture(normalmap, fs_in.TexCoords).rgb;
   normal = normal*2.0-1.0;
   normal = normalize(fs_in.TBN*normal);
   vec3 viewDir = normalize(viewPos-fs_in.FragPos);

   vec3 light_color = 0.5*CalcDirLight(dirLight, normal, viewDir);
   for (int i = 0; i < NR_POINT_LIGHTS; i++){
       light_color += CalcPointLight(pointLights[i], normal, fs_in.FragPos, viewDir);
   }

   FragColor =texture(texture1, fs_in.TexCoords)* vec4(light_color, 1.0f);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Fill these functions. And use them in main.                                                                //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// calculates the color when using a directional light.

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    ambient = light.ambient* vec3(texture(material.ambient, fs_in.TexCoords));

    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(-light.direction);
    float diff = max(dot(norm, light_dir), 0.0);
    diffuse = diff*light.diffuse* vec3(texture(material.diffuse, fs_in.TexCoords));

    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(viewDir, reflect_dir), 0.0), 36);
    specular = spec*light.specular* vec3(texture(material.specular, fs_in.TexCoords));

    return (ambient + diffuse + specular);
}



// calculates the color when using a point light.

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float distance = length(light.position-fragPos);
    float attenuation = 1.0/(light.constant+light.linear*distance+light.quadratic*distance*distance);

    ambient = light.ambient* vec3(texture(material.ambient, fs_in.TexCoords));

    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light.position-fragPos);
    float diff = max(dot(norm, light_dir), 0.0);
    diffuse = diff*light.diffuse* vec3(texture(material.diffuse, fs_in.TexCoords));

    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(viewDir, reflect_dir), 0.0), 36);
    specular = spec*light.specular* vec3(texture(material.specular, fs_in.TexCoords));

    return ambient + (diffuse + specular)*attenuation;
}
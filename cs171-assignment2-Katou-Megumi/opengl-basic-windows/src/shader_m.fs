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


#define NR_POINT_LIGHTS 4

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];


// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);



void main()
{    

   FragColor = vec4(1,0,1,0);
    
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
    return (ambient + diffuse + specular);
}



// calculates the color when using a point light.

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    return (ambient + diffuse + specular);
}



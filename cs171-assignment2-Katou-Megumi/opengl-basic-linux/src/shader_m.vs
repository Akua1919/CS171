#version 330 core

//You may need some other layouts.
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;



out VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    mat3 TBN;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()

{
	vs_out.FragPos = vec3(model * vec4(aPos,1.0));  
    gl_Position = projection * view * vec4(vs_out.FragPos, 1.0);
	vs_out.TexCoords = aTexCoords;
    vec3 T = normalize(vec3(model*vec4(tangent, 0.0)));
    vec3 B = normalize(vec3(model*vec4(bitangent, 0.0)));
    vec3 N = normalize(vec3(model*vec4(aNormal, 0.0)));
    vs_out.TBN = mat3(T, B, N);
}
#include <glad/glad.h>  
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include <iostream>
#include "../3rdLibs/glm/glm/glm.hpp"
#include "../3rdLibs/glm/glm/gtc/matrix_transform.hpp"
#include "../3rdLibs/glm/glm/gtc/type_ptr.hpp"


#include "../inc/my_texture.h"
#include "../inc/shader_m.h"
#include "tiny_obj_loader.h"



/*-----------------------------------------------------------------------*/
//Here are some mouse and keyboard function. You can change that.
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void enlarge(float* vec1, float* vec2,int num);
void setTBN(float* vec1,int i);
void transport();
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
float degreeX = (360 * lastX / 400);
float degreeY = (360 * lastY / 300);
bool firstMouse = true;
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
float OX = 0;//should be update to a new coordinate
float OY = 0;
float OZ = 0;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;
float currentFrame;
float yaw = -90.0;
float pitch = 0;


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;
	float sensitivity = 0.01f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	yaw += xoffset;
	pitch += yoffset;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	glm::vec3 front;//why not in global 
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);
	//std::cout << yaw << " " << pitch << std::endl;
}

void processInput(GLFWwindow* window)
{
	/*currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;*/
	float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void initPMV()
{
	model = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	projection = glm::perspective(glm::radians(60.0f), float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, 1000.0f);
}

void changePMV()
{
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
/*-----------------------------------------------------------------------*/



//This an function to get v, vt and vn. 
bool make_face(std::vector<float> v, std::vector<float> vt, std::vector<float> vn, std::vector<unsigned int> f,
	std::vector<glm::vec3>& points, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& uvs)
{
	if (f.size() % 3 != 0)
		return false;
	for (int i = 0; i < f.size()/3; i += 1)
	{
		int k = i * 3;
		for (int j = 0; j < 3; j++)
		{
			points.push_back(glm::vec3(v[f[k + j] * 3], v[f[k + j] * 3 + 1], v[f[k + j] * 3 + 2]));
			normals.push_back(glm::vec3(vn[f[k + j] * 3], vn[f[k + j] * 3 + 1], vn[f[k + j] * 3 + 2]));
			uvs.push_back(glm::vec2(vt[f[k + j] * 2], vt[f[k + j] * 2 + 1]));
		}
		
	}
}
void get_vec3(std::vector<float> list, std::vector<glm::vec3> &vec)
{
	int n = list.size() / 3;
	for (int i = 0; i < n; i++)
	{
		vec.push_back(glm::vec3(list[i], list[i + 1], list[i + 2]));
	}
}
void get_vec2(std::vector<float> list, std::vector<glm::vec2>& vec)
{
	int n = list.size() / 2;
	for (int i = 0; i < n; i++)
	{
		vec.push_back(glm::vec2(list[i], list[i + 1]));
	}
}

void enlarge(float* vec1, float* vec2,int num)
{
	for (int i = 0; i < num; i += 1) {
		for (int j = 0; j < 8; j++) {
			vec1[i * 14 + j] = vec2[i * 8 + j];
		}
	}
}

void setTBN(float* vec1,int i)
{
		glm::vec3 tangent;
		glm::vec3 bitangent;
		glm::vec3 e1;
		glm::vec3 e2;
		glm::vec2 uv1;
		glm::vec2 uv2;

		e1.x = vec1[(i + 1) * 14] - vec1[i * 14];
		e1.y = vec1[(i + 1) * 14 + 1] - vec1[i * 14 + 1];
		e1.z = vec1[(i + 1) * 14 + 2] - vec1[i * 14 + 2];
		e2.x = vec1[(i + 2) * 14] - vec1[i * 14];
		e2.y = vec1[(i + 2) * 14 + 1] - vec1[i * 14 + 1];
		e2.z = vec1[(i + 2) * 14 + 2] - vec1[i * 14 + 2];

		uv1.x = vec1[(i + 1) * 14 + 6] - vec1[i * 14 + 6];
		uv1.y = vec1[(i + 1) * 14 + 7] - vec1[i * 14 + 7];
		uv2.x = vec1[(i + 2) * 14 + 6] - vec1[i * 14 + 6];
		uv2.y = vec1[(i + 2) * 14 + 7] - vec1[i * 14 + 7];

		float inv = 1.0f / (uv1.x * uv2.y - uv2.x * uv1.y);

		tangent.x = inv * (uv2.y * e1.x - uv1.y * e2.x);
		tangent.y = inv * (uv2.y * e1.y - uv1.y * e2.y);
		tangent.z = inv * (uv2.y * e1.z - uv1.y * e2.z);
		tangent = glm::normalize(tangent);

		bitangent.x = inv * (-uv2.x * e1.x + uv1.x * e2.x);
		bitangent.y = inv * (-uv2.x * e1.y + uv1.x * e2.y);
		bitangent.z = inv * (-uv2.x * e1.z + uv1.x * e2.z);
		bitangent = glm::normalize(bitangent);
		
		for (int k = 0; k < 3; k++) {
			vec1[(i + k) * 14 + 8] = tangent.x;
			vec1[(i + k) * 14 + 9] = tangent.y;
			vec1[(i + k) * 14 + 10] = tangent.z;
			vec1[(i + k) * 14 + 11] = bitangent.x;
			vec1[(i + k) * 14 + 12] = bitangent.y;
			vec1[(i + k) * 14 + 13] = bitangent.z;
		}
}

void transport()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
	glEnableVertexAttribArray(4);
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	
    gladLoadGL();  
    
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Here you need to fill construct function of class Shader. And you need to understand other funtions in Shader.//
	// Then, write code in shader_m.vs, shader_m.fs and shader_m.gs to finish the tasks.                             //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Shader my_shader(
		"../src/shader_m.vs", 
		"../src/shader_m.fs"
	);
	//A shader for light visiable source
	Shader lampShader("../src/lamp.vs", "../src/lamp.fs");
	


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// tiny::LoadObj is a function to load obj file. The output is shape_t and material_t.                         //
	// "shape.mesh" is a mesh struct. "mesh.positions", "mesh.normals", "mesh.texcoords" corresponds to v,vn,vt.   //
	// For example:                                                                                                //
	// positions[0],positions[1],positions[2] -> v 0,0,1                                                           //
	// positions[3],positions[4],positions[5] -> v 0,1,0                                                           //
	// "mesh.indice" corresponds to f, but it is different from f. Each element is an index for all of v,vn,vt.    //
	// positions[0],positions[1],positions[2] -> v 0,0,1  positions[0],positions[1],positions[2] -> v 0,0,1        //
	// You can read tiny_obj_loader.h to get more specific information.                                            //
	//                                                                                                             //
	// I have write make_face for you.  It will return v, vt, vn in vec form (each element if for one point).      //
	// These informations can help you to do normal mapping.  (You can calculate tangent here)                     //
	// Since i did not assign uv for noraml map, you just need use vt as uv for normal map, but you will find it is//
	//  ugly. So please render a box to show a nice normal mapping. (Do normal mapping on obj and box)             //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string if_load_succeed = tinyobj::LoadObj(shapes, materials,
	 	"/home/xiasuan/cs171-assignment2-Katou-Megumi/model/pikaqiu.obj"
	);
	std::vector<unsigned int> obj_VBO_l, obj_VAO_l;
	float* pikaqiu;
	int vertexs;
	for (int i = 0; i < shapes.size(); i++)
	{
		
		std::vector < glm::vec3 > out_vertices;
		std::vector < glm::vec2 > out_uvs;
		std::vector < glm::vec3 > out_normals;

		// out_vertices, out_uvs, out_normals will get v, vt and vn.
		make_face(shapes[i].mesh.positions, shapes[i].mesh.texcoords, shapes[i].mesh.normals, shapes[i].mesh.indices,
			out_vertices, out_normals, out_uvs);
		
		vertexs = out_vertices.size();
		pikaqiu = new float[vertexs * 14];
		for (int j = 0; j < vertexs; j++) {
			pikaqiu[j * 14] = out_vertices[j][0];
			pikaqiu[j * 14 + 1] = out_vertices[j][1];
			pikaqiu[j * 14 + 2] = out_vertices[j][2];
			pikaqiu[j * 14 + 3] = out_normals[j][0];
			pikaqiu[j * 14 + 4] = out_normals[j][1];
			pikaqiu[j * 14 + 5] = out_normals[j][2];
			pikaqiu[j * 14 + 6] = out_uvs[j][0];
			pikaqiu[j * 14 + 7] = out_uvs[j][1];
		}
	}
	for (int i = 0; i < vertexs; i += 3) {
		setTBN(pikaqiu,i);
	}
	unsigned int pikaqiu_vbo, pikaqiu_vao;
	glGenBuffers(1, &pikaqiu_vbo);
	glGenVertexArrays(1, &pikaqiu_vao);
	glBindBuffer(GL_ARRAY_BUFFER, pikaqiu_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexs * sizeof(float) * 14,pikaqiu, GL_STATIC_DRAW);
	glBindVertexArray(pikaqiu_vao);
	transport();
	delete[] pikaqiu;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Render a box to show nice normal mapping.                                                                   //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	float vertices_cube_0[] = {

		// positions          // normals           // texture coords

		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f

	};
	//box
	float* data_cube = new float[36 * 14];
	enlarge(data_cube,vertices_cube_0,36);
	for (int i = 0; i < 36; i += 3) {
		setTBN(data_cube,i);
	}
	unsigned int box_vbo, box_vao;
	glGenBuffers(1, &box_vbo);
	glGenVertexArrays(1, &box_vao);	
	glBindBuffer(GL_ARRAY_BUFFER, box_vbo);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(float) * 14, data_cube, GL_STATIC_DRAW);
	glBindVertexArray(box_vao);
	transport();
	delete[] data_cube;

	//light source
	unsigned int light_vao, light_vbo;
	glGenVertexArrays(1, &light_vao);
	glGenBuffers(1, &light_vbo);
	glBindVertexArray(light_vao);
	glBindBuffer(GL_ARRAY_BUFFER, light_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cube_0), vertices_cube_0, GL_STATIC_DRAW);
	glBindVertexArray(light_vao);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// You need to fill this function which is defined in my_texture.h. The parameter is the path of your image.   //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	unsigned int texture_cat = loadTexture("../../model/2.jpg");
	unsigned int texture_pikaqiu = loadTexture("../../model/p_r.jpg");
	unsigned int texture_normalmap = loadTexture("../../model/normal_map.jpg");





	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Here we defined pointlights in shader and passed some parameter for you. You can take this as an example.   //
	// Or you can change it if you like.                                                                           //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glm::vec3 pointLightPositions[] = {
		glm::vec3(5.7f,  5.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};
	my_shader.use();
	my_shader.setInt("texture1", 0);
	my_shader.setInt("normalmap", 1);
	my_shader.setVec3("dirLight.direction", glm::vec3(1.01f, 1.01f, 1.01f));
	my_shader.setVec3("dirLight.ambient", glm::vec3(0.01f, 0.01f, 0.02f));
	my_shader.setVec3("dirLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	my_shader.setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	// point light 1
	my_shader.setVec3("pointLights[0].position", pointLightPositions[0]);
	my_shader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	my_shader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
	my_shader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	my_shader.setFloat("pointLights[0].constant", 1.0f);
	my_shader.setFloat("pointLights[0].linear", 0.09);
	my_shader.setFloat("pointLights[0].quadratic", 0.032);
	// point light 2
	my_shader.setVec3("pointLights[1].position", pointLightPositions[1]);
	my_shader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	my_shader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
	my_shader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	my_shader.setFloat("pointLights[1].constant", 1.0f);
	my_shader.setFloat("pointLights[1].linear", 0.09);
	my_shader.setFloat("pointLights[1].quadratic", 0.032);
	// point light 3
	my_shader.setVec3("pointLights[2].position", pointLightPositions[2]);
	my_shader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	my_shader.setVec3("pointLights[2].diffuse", 0.6f, 0.1f, 0.8f);
	my_shader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	my_shader.setFloat("pointLights[2].constant", 1.0f);
	my_shader.setFloat("pointLights[2].linear", 0.09);
	my_shader.setFloat("pointLights[2].quadratic", 0.032);
	// point light 4
	my_shader.setVec3("pointLights[3].position", pointLightPositions[3]);
	my_shader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
	my_shader.setVec3("pointLights[3].diffuse", 0.1f, 1.1f, 0.8f);
	my_shader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
	my_shader.setFloat("pointLights[3].constant", 1.0f);
	my_shader.setFloat("pointLights[3].linear", 0.09);
	my_shader.setFloat("pointLights[3].quadratic", 0.032);

	initPMV();
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		//Update Camera Matrix
		changePMV();
		glFlush();
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		glLightModeli(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		for (int i = 0; i < 4; i++) {
			lampShader.use();
			lampShader.setMat4("model", glm::translate(model, pointLightPositions[i]));
			lampShader.setMat4("view", view);
			lampShader.setMat4("projection", projection);
			glBindVertexArray(light_vao);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//  Render an object using texture and normal map.                                                             //
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		my_shader.use();
		my_shader.setVec3("material.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
		my_shader.setVec3("material.diffuse", glm::vec3(0.3f, 0.3f, 0.3f));
		my_shader.setVec3("material.specular", glm::vec3(0.8f, 0.8f, 0.8f));
		my_shader.setMat4("model", model);
		my_shader.setMat4("view", view);
		my_shader.setMat4("projection", projection);
		my_shader.setVec3("viewPos", cameraPos);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_cat);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_normalmap);
		glBindVertexArray(box_vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//  Render the object in .obj file. You need to set materials and wrap texture for objects.                    //
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		my_shader.use();
		my_shader.setVec3("material.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
		my_shader.setVec3("material.diffuse", glm::vec3(0.3f, 0.3f, 0.3f));
		my_shader.setVec3("material.specular", glm::vec3(0.8f, 0.8f, 0.8f));
		my_shader.setMat4("model", model);
		my_shader.setMat4("view", view);
		my_shader.setMat4("projection", projection);
		my_shader.setVec3("viewPos", cameraPos);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_pikaqiu);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_normalmap);
		glBindVertexArray(pikaqiu_vao);
		glDrawArrays(GL_TRIANGLES, 0, vertexs);


		/////////////////////////////////////////////////////////////////////
		
		/////////////////////////////end/////////////////////////////////////



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // -----------------------------------------------------------------
	glDeleteBuffers(1, &pikaqiu_vbo);
	glDeleteVertexArrays(1, &pikaqiu_vao);
	glDeleteBuffers(1, &box_vbo);
	glDeleteVertexArrays(1, &box_vao);
	glDeleteBuffers(1, &light_vbo);
	glDeleteVertexArrays(1, &light_vao);
    glfwTerminate();
    return 0;
}


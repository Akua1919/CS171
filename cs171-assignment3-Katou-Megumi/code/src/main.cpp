
#include <iostream>
#include <algorithm>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "parallelogram.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "directLightingIntegrator.hpp"
#include "triangleMesh.hpp"

inline float clamp(float x) { return x < 0 ? 0 : x > 1 ? 1 : x; }
inline unsigned char toInt(float x) { return (unsigned char)(pow(clamp(x), 1 / 2.2) * 255 + .5); }
int main()
{
	/*
	 * 1. Camera Setting
	 */
	Eigen::Vector3f cameraPosition(0, 0, 10);
	Eigen::Vector3f cameraLookAt(0, 0, 0);
	Eigen::Vector3f cameraUp(0, 1, 0);
	float verticalFov = 45;
	Eigen::Vector2i filmRes(1000, 1000);

	Camera camera(cameraPosition, cameraLookAt, cameraUp, verticalFov, filmRes);

	/*
	 * 2. Basic geometry setting
	 * Setting the cornell box.
	 */
	Eigen::Vector3f p_p0(-10, -10, -10);
	Eigen::Vector3f p_s0(1, 0, 0);
	Eigen::Vector3f p_s1(0, 1, 0);
	Eigen::Vector3f p_normal(0, 0, 1);
	Eigen::Vector3f p_color(0.7, 0.7, 0.7);
	Parallelogram backWall(p_p0, p_s0 * 20, p_s1 * 20, p_normal, p_color);

	p_p0 = Eigen::Vector3f(-6, -7, -11);
	p_s0 = Eigen::Vector3f(0, 0, 1);
	p_s1 = Eigen::Vector3f(0, 1, 0);
	p_normal = Eigen::Vector3f(1, 0, 0);
	p_color = Eigen::Vector3f(1, 0, 0);
	Parallelogram leftWall(p_p0, p_s0 * 20, p_s1 * 20, p_normal, p_color);

	p_p0 = Eigen::Vector3f(6, -7, -11);
	p_s0 = Eigen::Vector3f(0, 0, 1);
	p_s1 = Eigen::Vector3f(0, 1, 0);
	p_normal = Eigen::Vector3f(-1, 0, 0);
	p_color = Eigen::Vector3f(0, 1, 0);
	Parallelogram rightWall(p_p0, p_s0 * 20, p_s1 * 20, p_normal, p_color);

	p_p0 = Eigen::Vector3f(-7, -6, -11);
	p_s0 = Eigen::Vector3f(1, 0, 0);
	p_s1 = Eigen::Vector3f(0, 0, 1);
	p_normal = Eigen::Vector3f(0, 1, 0);
	p_color = Eigen::Vector3f(0.7, 0.7, 0.7);
	Parallelogram floor(p_p0, p_s0 * 20, p_s1 * 20, p_normal, p_color);

	p_p0 = Eigen::Vector3f(-7, 6, -11);
	p_s0 = Eigen::Vector3f(1, 0, 0);
	p_s1 = Eigen::Vector3f(0, 0, 1);
	p_normal = Eigen::Vector3f(0, -1, 0);
	p_color = Eigen::Vector3f(0.7, 0.7, 0.7);
	Parallelogram ceiling(p_p0, p_s0 * 20, p_s1 * 20, p_normal, p_color);

	/*
	 * 3. Triangle mesh setting
	 * Note:
	 *   `Only after you finished subdivision method can you call @TriangleMesh.subdivision(). If
	 * you choose to do ray tracing first, you should comment @TriangleMesh.subdivision() so that
	 * you can have the rendering result of a coarse mesh.
	 *   `Make sure you call methods is this order:@TriangleMesh.subdivision(),
	 * @TriangleMesh.applyTransformation(), @TriangleMesh.buildUniformGrid().
	 */

	 // The transform here for Cloud_1.obj is also suitable for Cloud_2.obj and Cloud_3.obj
	 // Change to Cloud_2.obj or Cloud_3.obj just by changing the file's position
	std::string obj_1_filePos("../resources/Cloud_1.obj");
	Eigen::Vector3f obj_1_color(1, 0.2, 0.2);
	Eigen::Affine3f obj_1_transform;
	obj_1_transform = Eigen::Translation3f(3, 1, -3) * Eigen::Scaling(0.5f);
	TriangleMesh mesh_1(obj_1_color, obj_1_filePos);
	mesh_1.subdivision(3);
	mesh_1.applyTransformation(obj_1_transform);
	mesh_1.buildUniformGrid();

	
	std::string obj_2_filePos("../resources/p.obj");
	Eigen::Vector3f obj_2_color(1, 0.2, 0.2);
	Eigen::Affine3f obj_2_transform;
	obj_2_transform = Eigen::Translation3f(3, -6.2, -6) * Eigen::Scaling(0.3f);
	TriangleMesh mesh_2(obj_2_color, obj_2_filePos);
	mesh_2.subdivision(3);
	mesh_2.applyTransformation(obj_2_transform);
	mesh_2.buildUniformGrid();

	std::string obj_3_filePos("../resources/cube_8p.obj");
	Eigen::Vector3f obj_3_color(1, 0.2, 0.2);
	Eigen::Affine3f obj_3_transform;
	obj_3_transform = Eigen::Translation3f(-2, -4, -3) * Eigen::Scaling(0.8f);
	TriangleMesh mesh_3(obj_3_color, obj_3_filePos);
	mesh_3.subdivision(3);
	mesh_3.applyTransformation(obj_3_transform);
	mesh_3.buildUniformGrid();

	std::string obj_4_filePos("../resources/surface1.obj");
	Eigen::Vector3f obj_4_color(1, 0.2, 0.2);
	Eigen::Affine3f obj_4_transform;
	obj_4_transform = Eigen::Translation3f(-1, 1.5, -4) * Eigen::Scaling(0.3f);
	obj_4_transform.rotate(Eigen::AngleAxisf(M_PIf * 0.45, Eigen::Vector3f::UnitX()));
	TriangleMesh mesh_4(obj_4_color, obj_4_filePos);
	mesh_4.subdivision(3);
	mesh_4.applyTransformation(obj_4_transform);
	mesh_4.buildUniformGrid();
	
	/*
	 * 4. Light setting
	 */
	Light light(Eigen::Vector3f(0, 5.99, 5), Eigen::Vector3f(1, 1, 1));

	/*
	 * 5. Scene integration
	 */
	Scene scene(light);
	scene.addShape(&backWall);
	scene.addShape(&leftWall);
	scene.addShape(&rightWall);
	scene.addShape(&floor);
	scene.addShape(&ceiling);
	scene.addShape(&mesh_1);
	
	scene.addShape(&mesh_2);
	scene.addShape(&mesh_3);
	scene.addShape(&mesh_4);
	
	/*
	 * 6. Select and execute integrator
	 */
	DirectLightingIntegrator integrator(&scene, &camera);
	integrator.render();

	/*
	 * 7. Output image to file
	 */
	std::string outputPath = "./output.png";
	std::vector<unsigned char> outputData;
	outputData.reserve(filmRes.x() * filmRes.y() * 3);
	for (Eigen::Vector3f v : camera.m_Film.pixelSamples)
	{
		for (int i = 0; i < 3; i++)
		{
			outputData.push_back(toInt(v[i]));
		}
	}
	stbi_flip_vertically_on_write(true);
	stbi_write_png(outputPath.c_str(), filmRes.x(), filmRes.y(), 3, outputData.data(), 0);

	return 0;
}
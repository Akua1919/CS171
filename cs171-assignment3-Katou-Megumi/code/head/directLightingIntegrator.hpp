#pragma once
#include "integrator.hpp"
#include <algorithm>
using namespace std;

class DirectLightingIntegrator : public Integrator
{
public:
	// blinn phong parameters
	float shininess = 16.0f;
	float lightPower = 15.0f;
	Eigen::Vector3f ambientColor = Eigen::Vector3f(0.1, 0.1, 0.1);
	Eigen::Vector3f specColor = Eigen::Vector3f(1.0, 1.0, 1.0);
	
	DirectLightingIntegrator(Scene* scene, Camera* camera)
		: Integrator(scene, camera)
	{
	}

	// main render loop
	void render() override
	{
		for (int dx = 0; dx < camera->m_Film.m_Res.x(); dx++)
		{
			for (int dy = 0; dy < camera->m_Film.m_Res.y(); dy++)
			{
				Ray ray = camera->generateRay(dx, dy);
				Interaction surfaceInteraction;
				if (scene->intersection(&ray, surfaceInteraction))
				{
					camera->setPixel(dx, dy, radiance(&surfaceInteraction, &ray));
				}
			}
		}
	}

	// radiance of a specific point
	Eigen::Vector3f radiance(Interaction* interaction, Ray * ray) override
	{
		Eigen::Vector3f surfaceColor = interaction->surfaceColor;
		Eigen::Vector3f lightColor = scene->light.m_Color;
		Eigen::Vector3f ambientColor(0.1, 0.1, 0.1);

		Eigen::Vector3f dist = scene->light.m_Pos - interaction->entryPoint;
		Ray shadowRay(interaction->entryPoint, dist.normalized(), 0.0001, dist.norm());
		if (scene->intersection(&shadowRay)) {
			return ambientColor.array() * surfaceColor.array();
		} else {
			Eigen::Vector3f normal = interaction->normal.normalized();
			float diff = max(normal.dot(shadowRay.m_Dir), 0.0f);
			Eigen::Vector3f view_dir = (camera->m_Pos - interaction->entryPoint).normalized();
			Eigen::Vector3f halfway_dir = (shadowRay.m_Dir + view_dir).normalized();
			float spec = pow(max(normal.dot(halfway_dir), 0.0f), shininess);
			return (ambientColor + lightColor * (diff + spec)).array() * surfaceColor.array();
		}
	}
};
#pragma once
#include "integrator.hpp"
#include "material.hpp"
#include <cmath>
#include <omp.h>

class PathTracingIntegrator : public Integrator
{
public:
	PathTracingIntegrator(Scene* scene, Camera* camera)
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
				std::vector<Eigen::Vector3f> Ls;
				bool glowing = false;
				
				Interaction isect;
				Ray ray = camera->generateRay(dx, dy);
				scene->intersection(&ray, isect);

				if (isect.lightId != -1)
				{
					camera->setPixel(dx, dy, Eigen::Vector3f(1.0f, 1.0f, 1.0f));
					glowing = true;
					break;
				}
				
				for (float sx = 0; sx < 1; sx += 1.0f / 4)
				{
					for (float sy = 0; sy < 1; sy += 1.0f / 4)
					{
						Eigen::Vector3f L(0.0f, 0.0f, 0.0f);
						Eigen::Vector3f beta(1.0f, 1.0f, 1.0f);
						Ray ray = camera->generateRay(dx + sx, dy + sy);
						
						for (int bounces = 0;  ; ++bounces)
						{
							Interaction isect;
							bool foundIsect = scene->intersection(&ray, isect);
							isect.outputDir = -ray.m_Dir;

							if (foundIsect == false ||  bounces >= 5)
							{
								break;
							}
							BRDF* mat = (BRDF*)isect.material;

							L += beta.cwiseProduct(radiance(&isect, &ray));

							isect.outputDir = -ray.m_Dir;
							float pdf = mat->sample(isect);
							Eigen::Vector3f f = mat->eval(isect);
							if (f == Eigen::Vector3f(0.0f, 0.0f, 0.0f) || pdf == 0.0f)
							{
								break;
							}
							beta = beta.cwiseProduct(f * abs(isect.inputDir.dot(isect.normal)) / pdf);
							ray.m_Ori = isect.entryPoint;
							ray.m_Dir = -isect.inputDir;

							if (bounces > 3) {
								float q = std::max((float).05, 1 - beta.y());
								if (rand()/double(RAND_MAX) < q)
								{
									break;
								}
								beta /= 1 - q;
							}
						}
						Ls.push_back(L);
					}
				}
				if (glowing == false)
				{
					Eigen::Vector3f L(0.0f, 0.0f, 0.0f);
					for (int i = 0; i < Ls.size(); i++)
						L += Ls[i];
					camera->setPixel(dx, dy, L / 16);
				}
			}
		}
	}

	// radiance of a specific point
	Eigen::Vector3f radiance(Interaction * interaction, Ray * ray) override
	{
		Eigen::Vector3f Ld(0.0f, 0.0f, 0.0f);
		Eigen::Vector3f lightPos;
		float lightPdf = 0, scatteringPdf = 0;
		Eigen::Vector3f Li = scene->lights[0]->SampleSurfacePos(lightPos, lightPdf);
		Eigen::Vector3f f = Eigen::Vector3f(1.0f, 1.0f, 1.0f);
		BRDF* mat = (BRDF*)interaction->material;

		if (!mat->isSpecular)alpha_src
		{
			if (lightPdf > 0 && Li != Eigen::Vector3f(0.0f, 0.0f, 0.0f))
			{
				interaction->inputDir = (interaction->entryPoint - lightPos).normalized();
				interaction->outputDir = -ray->m_Dir;
				scatteringPdf = abs(interaction->inputDir.dot(interaction->normal.normalized())) * (1.0f / M_PIf);
				f = mat->eval(*interaction) * abs(interaction->inputDir.dot(interaction->normal.normalized()));

				if (f != Eigen::Vector3f(0.0f, 0.0f, 0.0f))
				{
					Ray shadow(interaction->entryPoint, (lightPos - interaction->entryPoint).normalized(), 1e-5f,
						(lightPos - interaction->entryPoint).x() / (lightPos - interaction->entryPoint).normalized().x() - 1e-4f);
					if (scene->intersection(&shadow))
					{
						Li = Eigen::Vector3f(0.0f, 0.0f, 0.0f);
					}
					if (Li != Eigen::Vector3f(0.0f, 0.0f, 0.0f))
					{
						float weight = (lightPdf * lightPdf) / (lightPdf * lightPdf + scatteringPdf * scatteringPdf);
						Ld += f.cwiseProduct(Li) * weight / lightPdf;
					}
				}
			}
		}
		
		interaction->outputDir = -ray->m_Dir;
		scatteringPdf = mat->sample(*interaction);
		f = mat->eval(*interaction) * abs(interaction->inputDir.dot(interaction->normal));
		
		if (f != Eigen::Vector3f(0.0f, 0.0f, 0.0f) && scatteringPdf > 0)
		{
			float weight = 1;
			Ray toRay(interaction->entryPoint, -interaction->inputDir, 1e-3f);
			if (!mat->isSpecular)
			{
				lightPdf = 1.0f / M_PIf;
				if (scene->lights[0]->isHit(&toRay) < 0)
					return Ld;
				weight = (lightPdf * lightPdf) / (lightPdf * lightPdf + scatteringPdf * scatteringPdf);
			}

			Interaction lightIsect;
			Eigen::Vector3f Li(0.0f, 0.0f, 0.0f);
			bool found = scene->intersection(&toRay, lightIsect);

			if (scene->lights[0]->isHit(&toRay) > 0)
			{
				if (found && lightIsect.lightId != -1)
				{
					Li = Eigen::Vector3f(1.0f, 1.0f, 1.0f);
				}
			}
			if (Li != Eigen::Vector3f(0.0f, 0.0f, 0.0f))
			{
				Ld += f.cwiseProduct(Li) * weight / scatteringPdf;
			}
		}
		
		return Ld;
	};
};	
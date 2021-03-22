#pragma once
#include <Eigen/Dense>
#include <utility>
#include <cmath>
#include "ray.hpp"
#include "interaction.hpp"
#define pi 3.14159266

class Light
{
public:
	Light(Eigen::Vector3f pos, Eigen::Vector3f color)
		: m_Pos(std::move(pos)),
		m_Color(std::move(color))
	{
	}
	virtual ~Light() = default;

	// Sample a point on the light's surface, if light is not delta light
	// Set PDF and the surface position
	// Return color of light
	virtual Eigen::Vector3f SampleSurfacePos(Eigen::Vector3f& sampled_lightPos, float& pdf)=0;

	// Determine if light is hit, if light is not delta light
	virtual float isHit(Ray* ray) = 0;
	
	Eigen::Vector3f m_Pos;
	Eigen::Vector3f m_Color;
};

class AreaLight:public Light
{
public:
	AreaLight(Eigen::Vector3f pos, Eigen::Vector3f color) : Light(pos, color)
	{
	}
	
	Eigen::Vector3f SampleSurfacePos(Eigen::Vector3f& sampled_lightPos, float & pdf) override {
		float rnd1 = rand()/double(RAND_MAX);
		float rnd2 = rand()/double(RAND_MAX);
		float r = sqrtf(rnd1);
		float phi = 2.0f * pi * rnd2;
		float x = r * cosf(phi);
		float z = r * sinf(phi);
		sampled_lightPos = m_Pos + Eigen::Vector3f(x, 0.0f, z);
		pdf = 1 / (pi);
		return m_Color;
	};
	
	float isHit(Ray * ray) override {
		float t = (m_Pos - ray->m_Ori).y() / ray->m_Dir.normalized().y();
		if (t > ray->m_fMax || t < ray->m_fMin) 
		{
			return 0;
		}
		Eigen::Vector3f pos = ray->getPoint(t);
		if (pow(pos.x() - m_Pos.x(), 2) + pow(pos.z() - m_Pos.z(),2) <= 1)
		{
			return t;	
		}
		else
		{
			return 0;
		}
	};
};
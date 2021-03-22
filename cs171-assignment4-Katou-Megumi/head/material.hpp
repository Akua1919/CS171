#pragma once
#include "Eigen/Dense"
#include "interaction.hpp"
#define pi 3.14159266


float clamp(float x, float y, float z)
{
	if (x>z)
	{
		return z;
	}
	if (x<y)
	{
		return y;
	}
	return x;
}

class BRDF
{
public:
	BRDF()
	{
		isSpecular = false;
	}
	
	// Evaluate the BRDF
	// The information in @Interaction contains ray's direction, normal
	// and other information that you might need
	virtual Eigen::Vector3f eval(Interaction &_interact) = 0;
	
	// Sample a direction based on the BRDF
	// The sampled direction is stored in @Interaction
	// The PDF of this direction is returned
	virtual float sample(Interaction &_interact) = 0;
	
	// Mark if the BRDF is specular
	bool isSpecular;
};


class IdealDiffuse : public BRDF
{
public:
	
	Eigen::Vector3f eval(Interaction& _interact)
	{
		Eigen::Vector3f N = _interact.normal;
		Eigen::Vector3f V = _interact.outputDir;
		Eigen::Vector3f L = _interact.inputDir;
		float NDotL = abs(N.dot(L));
		float NDotV = abs(N.dot(V));
		if (NDotL <= 0.0f || NDotV <= 0.0f)
		{
			return Eigen::Vector3f(0.0f, 0.0f, 0.0f);
		}
		Eigen::Vector3f out = (1.0f / pi) * _interact.surfaceColor;
		return out * clamp(NDotL,0.0f,1.0f);
	};

	float sample(Interaction& _interact)
	{
		float rnd1 = rand()/double(RAND_MAX);
		float rnd2 = rand()/double(RAND_MAX);
		float r = sqrtf(rnd1);
		float phi = 2.0f * pi * rnd2;
		float x = r * cosf(phi);
		float z = r * sinf(phi);
		float y = sqrtf(fmaxf(0, 1 - x * x - z * z));
		
		_interact.inputDir = -Eigen::Vector3f(x, y, z).normalized();

		float pdf = abs(_interact.inputDir.dot(_interact.normal)) * (1.0f / pi);
		return pdf;
	}
};

class IdealSpecular : public BRDF
{
public:

	IdealSpecular() {
		isSpecular = true;
	}

	Eigen::Vector3f eval(Interaction &_interact)
	{
		return _interact.surfaceColor;
	};

	float sample(Interaction& _interact)
	{
		Eigen::Vector3f lightDir = -_interact.outputDir.normalized();
		Eigen::Vector3f reflectDir = (lightDir - 2 * (lightDir.dot(_interact.normal.normalized())) * _interact.normal.normalized()).normalized();
		_interact.inputDir = -reflectDir;
		float pdf = 1.0f;
		return pdf;
	};
};
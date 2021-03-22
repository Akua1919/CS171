#pragma once
#include <Eigen/Dense>
#include <utility>

class Light
{
public:
	Light(Eigen::Vector3f vector3_f, Eigen::Vector3f vector3_f1)
		: m_Pos(std::move(vector3_f)),
		  m_Color(std::move(vector3_f1))
	{
	}

	Eigen::Vector3f m_Pos;
	Eigen::Vector3f m_Color;
};
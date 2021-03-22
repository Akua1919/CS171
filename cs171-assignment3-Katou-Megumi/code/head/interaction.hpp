#pragma once

#include "Eigen/Dense"

class Interaction
{
public:
	// distance (in units of t) to intersection point
	float entryDist;
	// distance (in units of t) to the second intersection point(if existed)
	float exitDist;
	// position of intersection point
	Eigen::Vector3f entryPoint;
	// normal of intersection point
	Eigen::Vector3f normal;
	// barycentric coordinate of intersection point(if existed)
	Eigen::Vector2f uv;
	// color of intersection point
	Eigen::Vector3f surfaceColor;
	
	Interaction() : entryDist(-1), exitDist(-1) {}
};

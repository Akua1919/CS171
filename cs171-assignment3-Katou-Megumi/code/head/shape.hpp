#pragma once
#include <utility>
#include "aabb.hpp"
#include "interaction.hpp"

class Shape
{
public:
	AABB m_BoundingBox;
	Eigen::Vector3f color;

	Shape(Eigen::Vector3f color) : color(std::move(color)) {}
	Shape(AABB aabb, Eigen::Vector3f color) : m_BoundingBox(std::move(aabb)), color(std::move(color)) {}
	virtual ~Shape() = default;
	
	virtual bool rayIntersection(Interaction& interaction, const Ray& ray) = 0;
};

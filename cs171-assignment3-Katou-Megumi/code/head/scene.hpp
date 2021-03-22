#pragma once

#include <utility>
#include <vector>
#include "light.hpp"
#include "shape.hpp"

class Scene
{
public:
	std::vector<Shape *> shapes;
	Light light;

	explicit Scene(Light light)
		: light(std::move(light))
	{
	}

	void addShape(Shape * shape)
	{
		shapes.push_back(shape);
	}
	
	int getShapeCount() const
	{
		return shapes.size();
	}

	void addLight(Light light)
	{
		this->light = std::move(light);
	}

	bool intersection(Ray * ray, Interaction& interaction)
	{
		Interaction surfaceInteraction;
		for (Shape* shape : shapes)
		{
			Interaction curInteraction;
			if (shape->m_BoundingBox.rayIntersection(*ray, curInteraction.entryDist, curInteraction.exitDist))
			{
				curInteraction.entryPoint = ray->getPoint(curInteraction.entryDist);
				if (shape->rayIntersection(curInteraction, *ray))
				{
					if (surfaceInteraction.entryDist == -1 || curInteraction.entryDist < surfaceInteraction.entryDist)
					{
						surfaceInteraction = curInteraction;
					}
				}
			}
		}

		interaction = surfaceInteraction;
		if (surfaceInteraction.entryDist != -1 && surfaceInteraction.entryDist >= ray->m_fMin && surfaceInteraction.entryDist <= ray->m_fMax)
		{
			return true;
		}
		return false;
	}

	bool intersection(Ray * ray)
	{
		Interaction surfaceInteraction;
		for (Shape* shape : shapes)
		{
			Interaction curInteraction;
			if (shape->m_BoundingBox.rayIntersection(*ray, curInteraction.entryDist, curInteraction.exitDist))
			{
				if (shape->rayIntersection(curInteraction, *ray))
				{
					if (surfaceInteraction.entryDist == -1 || curInteraction.entryDist < surfaceInteraction.entryDist)
					{
						surfaceInteraction = curInteraction;
					}
				}
			}
		}
		
		if (surfaceInteraction.entryDist != -1 && surfaceInteraction.entryDist >= ray->m_fMin && surfaceInteraction.entryDist <= ray->m_fMax)
		{
			return true;
		}
		return false;
	}
};

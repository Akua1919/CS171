#pragma once
#include "volume.h"
#include "camera.hpp"
#include <iostream>
//https://github.com/yuki-koyama/tinycolormap
#include "tinycolormap.hpp"

class Classifier{
    public:
    virtual opticsData transfer(volumeData v_data,float dt,Camera* cam ,std::vector<Light *> lights,float grad_max_norm=1)=0;
};

class myClassifier:public Classifier{
    public:
		opticsData transfer(volumeData v_data, float dt, Camera* cam, std::vector<Light *> lights, float grad_max_norm = 1) {
			opticsData optics;
			//std::cout<< "density = "<< v_data.density <<std::endl;
			//Write your own classifier, make use of input args(may not all)
			// should set transparency and color of optics
			tinycolormap::Color color1 = tinycolormap::GetColor(v_data.density, tinycolormap::ColormapType::Jet);
			Eigen::Vector3f color = Eigen::Vector3f(color1.r(), color1.g(), color1.b());

			Eigen::Vector3f ambientColor = Eigen::Vector3f(0.2, 0.2, 0.2);
			Eigen::Vector3f Normal = v_data.gradient.normalized();
			float diff = std::max(Normal.dot(lights[0]->m_Pos), 0.0f);
			Eigen::Vector3f view_dir = (cam->m_Pos - v_data.position).normalized();
			Eigen::Vector3f halfway_dir = (lights[0]->m_Pos -v_data.position + view_dir).normalized();
			float spec = pow(std::max(Normal.dot(halfway_dir), 0.0f), 16.0f);
			color = (ambientColor + lights[0]->m_Color*(diff + spec)).cwiseProduct(color);

			if (v_data.density >= 1e-8)
			{
				optics.color = color * dt *(v_data.gradient.norm()/grad_max_norm);
			}
			
			float t = exp(-log(1.f + v_data.density)/log(2.0f)* dt);
			optics.transparency = t*Eigen::Vector3f(1.0f,1.0f,1.0f);
			
			return optics;
    }
};
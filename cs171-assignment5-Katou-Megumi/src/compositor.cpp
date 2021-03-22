#include "compositor.h"

Compositor::Compositor(){};
Compositor::~Compositor(){};
void Compositor::compositeFrontToBack(Eigen::Vector3f& color_dst,Eigen::Vector3f& alpha_dst,Eigen::Vector3f color_src,Eigen::Vector3f alpha_src){
	//Here your front to back code
	color_dst = color_dst + (Eigen::Vector3f(1.0f,1.0f,1.0f) - alpha_dst).cwiseProduct(color_src);
	alpha_dst = alpha_dst + (Eigen::Vector3f(1.0f,1.0f,1.0f) - alpha_dst).cwiseProduct(alpha_src);

};
void Compositor::compositeBackToFront(Eigen::Vector3f& color_dst,Eigen::Vector3f color_src,Eigen::Vector3f alpha_src){
    //Here your back to front code
};


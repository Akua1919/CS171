#include "opticsData.h"

    Eigen::Vector3f opticsData::getColor(){
        return this->color;
        
        // return (this->emssion+this->in_scatter);
    };
    Eigen::Vector3f opticsData:: getOpacity(){
        return Eigen::Vector3f::Ones()- this->transparency;
    };

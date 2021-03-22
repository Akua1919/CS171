#pragma once
#include <vector>
#include <string>
#include "Eigen/Dense"
#include "light.hpp"
#include <iostream>
class opticsData{
public:
    Eigen::Vector3f transparency=Eigen::Vector3f(0,0,0);
    Eigen::Vector3f color=Eigen::Vector3f(0,0,0);
    Eigen::Vector3f getColor();
    Eigen::Vector3f getOpacity();

};

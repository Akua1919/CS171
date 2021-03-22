#pragma once
#include "volume.h"
#include "opticsData.h"
#include "compositor.h"
#include "interpolator.h"
#include "classifier.h"
#include "camera.hpp"
#include "light.hpp"
#include "classifier.h"
#include <iostream>
#include <omp.h>
class Renderer{
public:
    Camera * camera=NULL;
    std::vector<Light *> lights;
    Volume * volume=NULL;
    Classifier * classifier =NULL;
    Interpolator * interpolator=NULL;
    void setCamera(Camera * cam);
    void addLight(Light * light);
    void setVolume(Volume * vol);
    void setClassifier(Classifier * classifier);
    void setInterpolator(Interpolator * interpolator);

    void renderFrontToBack(std::string imgPath);
    void renderBackToFront(std::string imgPath);
    



};

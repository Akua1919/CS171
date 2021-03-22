#pragma once
#include "volumeData.h"
#include "Eigen/Dense"
//ref https://en.wikipedia.org/wiki/Trilinear_interpolation
class Interpolator
{
public:
    virtual volumeData interpolate(Eigen::Vector3f &p, const voxel &voxel) = 0;
};
class NearestNeighbourInterpolator : public Interpolator
{
    inline volumeData interpolate(Eigen::Vector3f &p, const voxel &voxel)
    {
        //Here your NNInterpolator code
        volumeData v;
        v.position = p;
        float l = (p - voxel.c000.position).norm();
        v.density = voxel.c000.density;
        v.gradient = voxel.c000.gradient;
        if ((p - voxel.c001.position).norm() < l)
        {
           v.density = voxel.c001.density;
            v.gradient = voxel.c001.gradient;
            l = (p - voxel.c001.position).norm();
        }
        if ((p - voxel.c010.position).norm() < l)
        {
           v.density = voxel.c010.density;
            v.gradient = voxel.c010.gradient;
            l = (p - voxel.c010.position).norm();
        }
        if ((p - voxel.c100.position).norm() < l)
        {
           v.density = voxel.c100.density;
            v.gradient = voxel.c100.gradient;
            l = (p - voxel.c100.position).norm();
        }
        if ((p - voxel.c011.position).norm() < l)
        {
           v.density = voxel.c011.density;
            v.gradient = voxel.c011.gradient;
            l = (p - voxel.c011.position).norm();
        }
        if ((p - voxel.c110.position).norm() < l)
        {
           v.density = voxel.c110.density;
            v.gradient = voxel.c110.gradient;
            l = (p - voxel.c110.position).norm();
        }
        if ((p - voxel.c101.position).norm() < l)
        {
           v.density = voxel.c101.density;
            v.gradient = voxel.c101.gradient;
            l = (p - voxel.c101.position).norm();
        }
        if ((p - voxel.c111.position).norm() < l)
        {
           v.density = voxel.c111.density;
            v.gradient = voxel.c111.gradient;
            l = (p - voxel.c111.position).norm();
        }
        return v;
    };
};
class TrilinearInterpolator : public Interpolator
{

    inline volumeData interpolate(Eigen::Vector3f &p, const voxel &voxel)
    {
		volumeData v;
        v.position = p;
        //Here your TrilinearInterpolator code
        float x0 = voxel.c000.position[0];
        float x1 = voxel.c111.position[0];
        float y0 = voxel.c000.position[1];
        float y1 = voxel.c111.position[1];
        float z0 = voxel.c000.position[2];
        float z1 = voxel.c111.position[2];

       /*
        std::cout<<"c0="<<voxel.c000.density<<std::endl;
        std::cout<<"c1="<<voxel.c001.density<<std::endl;
        std::cout<<"c2="<<voxel.c010.density<<std::endl;
        std::cout<<"c3="<<voxel.c011.density<<std::endl;
        std::cout<<"c4="<<voxel.c100.density<<std::endl;
        std::cout<<"c5="<<voxel.c101.density<<std::endl;
        std::cout<<"c6="<<voxel.c110.density<<std::endl;
        std::cout<<"c7="<<voxel.c111.density<<std::endl;
        */

        float xd = (p[0]-x0)/(x1-x0);
        float yd = (p[1]-y0)/(y1-y0);
        float zd = (p[2]-z0)/(z1-z0);
        /*
        std::cout<<"xd="<<xd<<std::endl;
        std::cout<<"yd="<<yd<<std::endl;
        std::cout<<"zd="<<zd<<std::endl;
        */
        float d00 = voxel.c000.density*(1-xd) + voxel.c100.density*xd;
        float d01 = voxel.c001.density*(1-xd) + voxel.c101.density*xd;
        float d10 = voxel.c010.density*(1-xd) + voxel.c110.density*xd;
        float d11 = voxel.c011.density*(1-xd) + voxel.c111.density*xd;

        float d0 = d00*(1-yd) + d10*yd;
        float d1 = d01*(1-yd) + d11*yd;

        float d = d0*(1-zd) + d1*zd;
        
        v.density = d;

        Eigen::Vector3f g00 = voxel.c000.gradient*(1-xd) + voxel.c100.gradient*xd;
        Eigen::Vector3f g01 = voxel.c001.gradient*(1-xd) + voxel.c101.gradient*xd;
        Eigen::Vector3f g10 = voxel.c010.gradient*(1-xd) + voxel.c110.gradient*xd;
        Eigen::Vector3f g11 = voxel.c011.gradient*(1-xd) + voxel.c111.gradient*xd;

        Eigen::Vector3f g0 = g00*(1-yd) + g10*yd;
        Eigen::Vector3f g1 = g01*(1-yd) + g11*yd;
        
        Eigen::Vector3f g = g0*(1-zd) + g1*zd;

		v.gradient = g;
        //printf("d = %f\n",d);
        return v;
    };

};
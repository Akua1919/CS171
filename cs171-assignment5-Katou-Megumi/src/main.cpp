
#include <iostream>
#include <algorithm>



#include"renderer.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
void renderSingle(){
	/*
	 * 1. Volume Setting
	 */
	
	Volume vol("../data/frame00055.bin");
	/*
	 * 2. Camera Setting
	 */
	Eigen::Vector3f cameraPosition= vol.bbox.getCenter()-2.5*Eigen::Vector3f(0,0,vol.size_physics.z());
	Eigen::Vector3f cameraLookAt= vol.bbox.getCenter();
	Eigen::Vector3f cameraUp(0, 1, 0);
	float verticalFov = 45;
	Eigen::Vector2i filmRes(512, 512);

	Camera camera(cameraPosition, cameraLookAt, cameraUp, verticalFov, filmRes);
	PointLight light(cameraPosition+Eigen::Vector3f(0,5,0),Eigen::Vector3f(1,1,1));



	/*
	 * 3. Renderer Setting
	 */

	myClassifier classifer;
	TrilinearInterpolator interpolator;
	//NearestNeighbourInterpolator interpolator;

	Renderer renderer;
	renderer.setCamera(&camera);
	renderer.setVolume(&vol);
	renderer.setClassifier((Classifier *)&classifer);
	renderer.addLight((Light *)&light);
	renderer.setInterpolator((Interpolator *)&interpolator);
	
	/*
	 * 3. Render
	 */
	renderer.renderFrontToBack("./foward_pre.png");
}

void multipleRender(){
/*
	 * 1. Volume Setting
	 */
	
	Volume vol("data/test2.bin");
	/*
	 * 2. Camera Setting
	 */
	Eigen::Vector3f cameraPosition= vol.bbox.getCenter()-2.5*Eigen::Vector3f(0,0,vol.size_physics.z());
	Eigen::Vector3f cameraLookAt= vol.bbox.getCenter();
	Eigen::Vector3f cameraUp(0, 1, 0);
	float verticalFov = 45;
	Eigen::Vector2i filmRes(1024, 1024);

	Camera camera(cameraPosition, cameraLookAt, cameraUp, verticalFov, filmRes);
	PointLight light(cameraPosition+Eigen::Vector3f(0,5,0),Eigen::Vector3f(1,1,1));



	/*
	 * 3. Renderer Setting
	 */

	myClassifier classifer;
	TrilinearInterpolator interpolator;

	Renderer renderer;
	renderer.setCamera(&camera);
	renderer.setVolume(&vol);
	renderer.setClassifier((Classifier *)&classifer);
	renderer.addLight((Light *)&light);
	renderer.setInterpolator((Interpolator *)&interpolator);
	for(int frame = 50;frame<200;frame++){
		  char filein[256];
    	sprintf(filein,"data/density/density_frame_out%05d.bin",frame);
		vol=Volume (filein);
		renderer.setVolume(&vol);
		char fileout[256];
    	sprintf(fileout,"result/frame%05d.png",frame);
		renderer.renderFrontToBack(fileout);
	}
}
int main()
{
	//here you can just render a single frame.
	renderSingle();
	// or multiple frames but you need to download data from the link of assignment page, and unzip to proper folder
	// multipleRender();


	return 0;
}
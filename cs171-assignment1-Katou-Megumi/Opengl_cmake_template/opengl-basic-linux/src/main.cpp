#include <glad/glad.h>  
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#define pi M_PI


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float camera[] = { 3, 3, 3, 0, 0, 0, 0, 1, 0 };
bool firstMouseMove = true;
GLfloat lastX = SCR_WIDTH / 2.0f, lastY = SCR_HEIGHT / 2.0f;
GLfloat YAW = 0.0f;
GLfloat PITCH = 0.0f;
const float  MAX_PITCH_ANGLE = 89.0f;


void drawTri()
{
    glEnable(GL_NORMALIZE);
	glBegin(GL_TRIANGLES);

	glColor3f(0.0, 1.0, 0.0);
    glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 1);
    glNormal3f(1, 0, 0);
	glVertex3f(1, 0, 0);
    glNormal3f(0, 1, 0);
	glVertex3f(0, 1, 0);
    
	glEnd();
}

void drawQuad()
{
    glEnable(GL_NORMALIZE);
	glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glNormal3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glNormal3f(1.0f, 0.0f, 0.0f); 
    glVertex3f(1.0f, 0.0f, 0.0f); 
    glEnd();
}

void drawTetrahedron()
{
    glEnable(GL_NORMALIZE);
	glBegin(GL_TRIANGLES);
    
    glColor3f(1.0, 0.0, 0.0);
    glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
    glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
    glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 1.0);
    
    glColor3f(0.0, 1.0, 0.0);
    glNormal3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
    glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
    glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
    
    glColor3f(0.0, 0.0, 1.0);
    glNormal3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
    glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 1.0);
    glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);

    glColor3f(1.0, 1.0, 1.0);
    glNormal3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
    glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 1.0);
    glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
    
	glEnd();
}

void drawCube()
{
    glEnable(GL_NORMALIZE);
	glBegin(GL_QUADS);
    
    glColor3f(0.0, 1.0, 0.0);
    glNormal3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glNormal3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glNormal3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glNormal3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    glColor3f(0.0, 1.0, 0.0);
    glNormal3f(-1.0f, 1.0f, 1.0f); 
    glVertex3f(-1.0f, 1.0f, 1.0f); 
    glNormal3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glNormal3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glNormal3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    glColor3f(0.0, 0.0, 1.0);
    glNormal3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glNormal3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glNormal3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glNormal3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    
    glColor3f(0.0, 0.0, 1.0);
    glNormal3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glNormal3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glNormal3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
     glNormal3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    
    glColor3f(1.0, 0.0, 0.0);
    glNormal3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glNormal3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glNormal3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glNormal3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    glColor3f(1.0, 0.0, 0.0);
    glNormal3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glNormal3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glNormal3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glNormal3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    glEnd();
}


struct vertex {
    float x, y, z;
};

vertex F(float u, float v, float r = 1.5f) {
    return vertex{ cos(u) * sin(v) * r,cos(v) * r,sin(u) * sin(v) * r };
}

void drawSphere() {
    glEnable(GL_NORMALIZE);
    float startU = 0;
    float startV = 0;
    float endU = pi;
    float endV = pi *2 ;

    float UResolution = 50;
    float VResolution = 50;

    float stepU = (endU - startU) / UResolution;
    float stepV = (endV - startV) / VResolution;

    for (int i = 0; i < UResolution; i++) {
        for (int j = 0; j < VResolution; j++) {
            float u = i * stepU + startU;
            float v = j * stepV + startV;
            float un =  (i + 1) * stepU + startU;
            float vn = (j + 1) * stepV + startV;

            vertex p0 = F(u, v);
            vertex p1 = F(u, vn);
            vertex p2 = F(un, v);
            vertex p3 = F(un, vn);

            glBegin(GL_TRIANGLES);
            glColor3f(1, 0, 0);

            glNormal3f(p0.x, p0.y, p0.z);   glVertex3f(p0.x, p0.y, p0.z);
            glNormal3f(p3.x, p3.y, p3.z);   glVertex3f(p3.x, p3.y, p3.z);
            glNormal3f(p1.x, p1.y, p1.z);   glVertex3f(p1.x, p1.y, p1.z);
            
            glNormal3f(p3.x, p3.y, p3.z);   glVertex3f(p3.x, p3.y, p3.z);
            glNormal3f(p2.x, p2.y, p2.z);   glVertex3f(p2.x, p2.y, p2.z);
            glNormal3f(p0.x, p0.y, p0.z);   glVertex3f(p0.x, p0.y, p0.z);

            glEnd();
        }
    }

}

void setlight()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat position[] = { 3.0f, 3.0f, 3.0f, 1.0f };
    GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuse[] = { 0.9f, 0.2f, 0.3f, 1.0f };
    GLfloat specular[] = { 0.5f, 0.5f, 1.0f, 1.0f }; 
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
}

void setmaterial()
{
    GLfloat ambient[] = { 0.2f, 0.2f, 0.2f };
    glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
    GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f}; 
    glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
    glMaterialf(GL_FRONT,GL_SHININESS,32);
}

void setshading()
{
    glShadeModel(GL_SMOOTH);
    //glShadeModel(GL_FLAT);
}

// You should draw triangle,tetrahedra,cube,sphere  in here;
void draw(){
    //drawQuad();
	//drawTri();
	//drawTetrahedron();
    //drawCube();
    drawSphere();
}



void initPMV()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60, SCR_WIDTH / SCR_HEIGHT, 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt
	(
		3, 3, 3,
		0, 0, 0,
		0, 1, 0
	);

}

void changePMV(int action)
{
    float step = 0.0005f;
    
    if (action == 0) //前进
    {
        glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    gluPerspective(60, SCR_WIDTH / SCR_HEIGHT, 0.1, 1000);
	    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        float front[] = {camera[3] - camera[0], camera[4] - camera[1],camera[5] - camera[2]};
        camera[0] = camera[0] + step*front[0];
        camera[1] = camera[1] + step*front[1];
        camera[2] = camera[2] + step*front[2];

        gluLookAt(camera[0], camera[1], camera[2],
            camera[3], camera[4], camera[5],
            camera[6], camera[7], camera[8]);
    }
    if (action == 1)
    {
        glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    gluPerspective(60, SCR_WIDTH / SCR_HEIGHT, 0.1, 1000);
	    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        float front[] = {camera[3] - camera[0], camera[4] - camera[1],camera[5] - camera[2]};

        camera[0] = camera[0] - step*front[0];
        camera[1] = camera[1] - step*front[1];
        camera[2] = camera[2] - step*front[2];

        gluLookAt(camera[0], camera[1], camera[2],
            camera[3], camera[4], camera[5],
            camera[6], camera[7], camera[8]);
    }
    if (action == 2)
    {
        glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    gluPerspective(60, SCR_WIDTH / SCR_HEIGHT, 0.1, 1000);
	    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        float side[] = {0,0,0};
	    side[0] = cos(YAW*pi/180);
	    side[1] = 0;
	    side[2] = -sin(YAW*pi/180);
        float unit = sqrt(pow(side[0],2) + pow(side[1],2 )+ pow(side[2],2)); 
        side[0] = side[0]/unit;
	    side[1] = side[1]/unit;
	    side[2] = side[2]/unit;

        camera[0] = camera[0] - step*side[0];
        camera[1] = camera[1] - step*side[1];
        camera[2] = camera[2] - step*side[2];

        gluLookAt(camera[0], camera[1], camera[2],
            camera[3], camera[4], camera[5],
            camera[6], camera[7], camera[8]);
    }
    if (action == 3)
    {
        glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    gluPerspective(60, SCR_WIDTH / SCR_HEIGHT, 0.1, 1000);
	    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        float side[] = {0,0,0};
	    side[0] = cos(YAW*pi/180);
	    side[1] = 0;
	    side[2] = -sin(YAW*pi/180);
        float unit = sqrt(pow(side[0],2) + pow(side[1],2 )+ pow(side[2],2)); 
        side[0] = side[0]/unit;
	    side[1] = side[1]/unit;
	    side[2] = side[2]/unit;

        camera[0] = camera[0] + step*side[0];
        camera[1] = camera[1] + step*side[1];
        camera[2] = camera[2] + step*side[2];

        gluLookAt(camera[0], camera[1], camera[2],
            camera[3], camera[4], camera[5],
            camera[6], camera[7], camera[8]);
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouseMove)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouseMove = false; 
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

    xoffset *= 0.5f;
    yoffset *= 0.5f;

	lastX = xpos;
	lastY = ypos;
    
    PITCH += yoffset;
	YAW += xoffset;
    
    if (PITCH > MAX_PITCH_ANGLE)
			PITCH = MAX_PITCH_ANGLE;
    if (PITCH < -MAX_PITCH_ANGLE)
			PITCH = -MAX_PITCH_ANGLE;
	if (YAW < 0.0f)
			YAW += 360.0f;

    float front[] = {0,0,0};
	front[0] = -sin(YAW*pi/180) * cos(PITCH*pi/180);
	front[1] = sin(YAW*pi/180);
	front[2] = -cos(YAW*pi/180) * cos(PITCH*pi/180);

    glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    gluPerspective(60, SCR_WIDTH / SCR_HEIGHT, 0.1, 1000);
	    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        camera[3] =  front[0];
        camera[4] =  front[1];
        camera[5] =  front[2];

        gluLookAt(camera[0], camera[1], camera[2],
            camera[3], camera[4], camera[5],
            camera[6], camera[7], camera[8]);
    
};


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);


    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    gladLoadGL();  
    glEnable(GL_DEPTH_TEST); /* enable depth-testing */

	// /* with LESS depth-testing interprets a smaller depth value as meaning "closer" */
	glDepthFunc(GL_LESS);
    glEnable(GL_MULTISAMPLE);  
    setlight();
    setmaterial();
	initPMV();  //camera matrix
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))  //render per frame
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		//Update Camera Matrix
		//changePMV();
		//Draw all primitives, with or without lighting;
		draw();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        changePMV(0);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        changePMV(1);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        changePMV(2);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        changePMV(3);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
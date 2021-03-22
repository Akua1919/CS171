# CS171-1 Assignment1

**Introduction**

In this assignment, you are required to create your first graphics program using [OpenGL](https://www.opengl.org/). As you have learned in the course as well as the tutorials, to start up your first graphics program, you will need to use [GLFW](http://www.glfw.org/) to create a window. By default, GLFW will create a window with double buffering enabled. 

Then, you can use the basic OpenGL calls to draw 3D objects on the window as well as manipulate the cameras to navigate through the virtual scene. 

To prevent aliasing artifacts, you can also enable antialiasing in OpenGL. 

In the following, we will give you the specifics about what you need to accomplish, as well as some related guidelines in order to assist your programming.

-----

## **Note**

**Before doing the assignment, please read the materials on OpenGL programming at [site1](http://www.opengl-tutorial.org/beginners-tutorials/), [site2](http://www.songho.ca/opengl/index.html). You can also read [site3](https://learnopengl.com/) which conducts OpenGL rendering based on OpenGL Mathematics ([GLM](https://glm.g-truc.net/0.9.8/index.html)) library.**

---

## **Programming Requirements**

+ **[must]** You are required to enable the  multi-sample full-screen antialiasing  functionality of OpenGL.
+  **[must]** You are required to draw simple objects : <u>triangle</u>, <u>tetrahedron</u>, <u>cubes</u> and <u>spheres</u>.
+  **[must]** You are required to render 3D objects with Phong lighting model.
+  **[must]** You are required to manipulate  the cameras by constructing the new camera matrix with `gluLookAt(...)` and use keyboard to control the camera: you can use keyboard to translate and rotate the camera so that you can walk in the virtual scene.
+  **[optional]** You can build a shader program to support Phong shading or you can support lighting with multiple point light sources, etc.

---

## **Demonstration Requirements**

**In addition to programming, you will also need to submit a demonstration video**. 

Thing must be included in the video:

+ Explain how you achieve `antialiasing`  and show related code fragments and demonstrate the result.
+ Explain how you draw objects, show related code fragments and demonstrate the result.
+ Explain how you render 3D objects with Phong lighting model, show related code fragments and demonstrate the result.
+ Explain your implementation of `Camera Navigation` , show related code fragments and demonstrate the result.
+ For optional part, explain your implementation and show it!

<u>Additional Notification</u>:

+ **No**  silent video!  Please talk!
+ You should **only** use your Putonghua or English in your video
+ Your should **<u>try your best</u>** to give your ideas clearly
+ If any of the above requirements is not met, your scores might be deducted.

---

## **Submission**

Submission deadline: TBD

---

## **Grading rules**

+ You can also choose to do  **[optional]** items, and if you choose to do it, you will get additional scores based on the additional work you have done. But the maximum additional score will not exceed 20% of the entire score of this assignment.

+  **NO CHEATING!**  If found, all scores will be deducted .

  You are required to work alone.We fully understand implementations might be similar, but cant be identical. To avoid being misjustified, please show your understanding of your codes in your video.

+ Late submission of your assignment will subject to score deduction. 

---

## Skeleton Program

Skeleton Program will be provided once you accept the assignment link which we published in piazza. 

In tutorial videos, we will explain how to setup an OpenGL environment with our  skeleton program and some basic opengl knowledge/semantics.

---

## Implementation Guide

### 1.Setup Environment

In tutorial videos, we will explain how to setup an OpenGL environment with our  skeleton program.

You need two things in order to get started: [GLEW](http://glew.sourceforge.net/) and [GLFW](http://www.glfw.org/). GLEW is the OpenGL extension wrangler library that contains all the OpenGL API functions based on which you can call to make OpenGL draws, whereas GLFW is a multi-platform library for creating windows on which your 3D objects are drawn. 

There are specific guidelines for [building up GLEW](http://glew.sourceforge.net/build.html) or [compiling and installing GLFW](http://www.glfw.org/docs/latest/compile_guide.html), on all platforms, and you can read and follow the steps. 

To link these dependencies into your program, you only need to link the related static library (*.lib for windows, and *.a for Linux) for these dependencies, and put the associated dynamic linked library (*.dll for windows and *.so for Linux) in the executable folder for running the program.

To make your life easy, please follow our tutorial video.  Besides, we recommend to use **Visual Studio** in Windows and **VSCode** in Linux. If you are experienced developer, you can choose what you like.

### **2. Creating the window program using GLFW**

Once you have set up your environment, you can start creating your first window program using GLFW. You can take a reference from [here](http://www.glfw.org/docs/latest/quick.html) which illustrates the step-by-step process for window creation. 

Here, we only give a brief introduction based on the following basic code:

```c++
int main()
{
      glfwInit();
     
      GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
     
      if (window == NULL)
      {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
      }
      glfwMakeContextCurrent(window);
      glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
     
      glewInit();
     
      glEnable(GL_DEPTH_TEST);

      //register callback function
      //initPMV();
      while (!glfwWindowShouldClose(window))
      {

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            //...draw() function
            glfwSwapBuffers(window);
            glfwPollEvents();
      }

      glfwTerminate();

      return 0;
}
```

Here, the function `glfwInit()` initializes the GLFW library before any GLFW functions can be used, and before the application exits, GLFW should be terminated in order to free any resources allocated `glfwTerminate()`. To create a window, we use `glfwCreateWindow()`, and such a window can be associated with the OpenGL rendering context by calling `glfwMakeContextCurrent()`, which takes the window pointer as its argument. We also need to register a framebuffer size call-back function using `glfwSetFramebufferSizeCallback()` such that when the size of the specified window is changed, it will be called to reset the projection. The function `glClearColor()` set current window's background color. The `glClear()` is used to clear both color and depth buffer to its default value. The `glfwSwapBuffers()` can swap the front and back buffers of the specified window and the `glfwPollEvents()` monitors user inputs. To make correct depth order, you can enable depth test in OpenGL by `glEnable(GL_DEPTH_TEST)`. 

You can also enable multi-sample antialiasing with a call to `glfwWindowHint` and assign `GLFW_SAMPLES `with the number of samples you want, and then enable antialiasing in OpenGL with `glEnable(...)`. Search for **"OpenGL multi-sampling"** for more information online.

The function `initPMV()` is a user-defined function which you need to write to set model-view and projection matrix. It may look like this:

```c++
void initPMV()
{
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(60, SCREEN_WIDTH / SCREEN_HEIGHT, 0.1, 100);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt
      (
            3, 3, 3,
            0, 0, 0,
            0, 1, 0
      );
}
```

`glMatrixMode()` sets current matrix model. `glLoadIdentity()` sets current matrix as identity matrix. `gluPerspective()` sets up a perspective projection matrix. `gluLookAt()` defines a viewing transformation. When you create a window successfully, you can write your own `draw()` function to generate and manipulate your 3D objects.

### **3. Create meshes (tessellation) of 3D objects**

Now you can draw some 3D objects by calculating and specifying vertex coordinates of the geometries. 

Check more for drawing geometric object in OpenGL at [site1](http://www.songho.ca/opengl/gl_vertexarray.html) & [site2](https://learnopengl.com/Getting-started/Hello-Triangle).  

#### Draw Triangle 

For example, you can easily draw a triangle like this:

```c++
void drawTriangle()
{
      glBegin(GL_TRIANGLES);
      glColor3f(0.6, 0.2, 0.3);
      glVertex3f(0, 0, 1);
      glVertex3f(1, 0, 0);
      glVertex3f(0, 1, 0);
      glEnd();
}
```

The `glBegin()` and `glEnd()` functions delimit the vertices of a primitive or a group of primitives. The `glBegin` in pseudo code which uses `GL_TRIANGLES` parameter represents that vertices between `glBegin()` and `glEnd()` will in triangle order. `glColor3f` performs the clear operation on one or more buffers at the same time. `glVertex3f()` specifies a vertex in 3D.

Adding the `drawTriangle()` in the `draw()` function of the previous program, you can get a drawn triangle in your window.

#### Draw Cube

To draw the cube, we can directly draw four rectangles. In fact, OpenGL provides the method which can draw a rectangle directly. You can set `glBegin()` function's parameter `GL_QUADS `like:

```c++
glBegin(GL_QUADS);
      glNormal3f(0.0f, 0.0f, 1.0f);
      glVertex3f(0.5f, 0.5f, 0.5f);
      glVertex3f(-0.5f, 0.5f, 0.5f);
      glVertex3f(-0.5f, -0.5f, 0.5f);
      glVertex3f(0.5f, -0.5f, 0.5f); 
glEnd();
```

#### Draw Sphere 

Draw a sphere is more complicated, and there can be many methods to generate 3D sphere point. This [DrawSphere](https://stackoverflow.com/questions/7687148/drawing-sphere-in-opengl-without-using-glusphere) will help you, but you **should not use gluSphere** which is a built-in utility function for OpenGL. The simplest method to draw a sphere is to use spherical coordinates, and a sphere can be expressed by the following parametric equation:
$$
F(u, v) = [ cos(u)*sin(v)*r, cos(v)*r, sin(u)*sin(v)*r ]
$$
where:
+ r is the sphere radius;
+ u is the longitude, ranging from 0 to 2π; and
+ v is the latitude, ranging from 0 to π.

You can set a r and generate 3D point by traverse u from 0 to 2π and v from 0 to π, using a fixed step size you set, e.g., the step size can be set to π/10, but you can make this step size even smaller to get more accurate sphere. After generating data, you need know the connected relation between points. You can use triangles or quads to link these points and draw them using OpenGL. Try to think about how to create such connectivity and draw the sphere.

### **4.Rendering 3D objects with Phong lighting model**

Up to now, you will find that objects you have drawn won't appear to be 3D once it is filled with a color. The reason is that you do not have a lighting model applied to give the appropriate shading on its appearance. 

In physical world, when you look at an object's surface, your eye's perception of the color depends on the energy distributions of photons that arrive and trigger your visual cone cells. Those photons come from a light source or a combination of light sources, some of which are absorbed and the other are reflected by the surface. In addition, different surfaces may have very different reflection properties - some are shiny and preferentially reflect light in certain directions, while others scatter incoming light equally in all directions. Most surfaces are somewhere in between these two extreme cases.

In OpenGL, the lighting phenomena is approximated as if the light can be decomposed into red, green, and blue components. Thus, the color of the light sources is characterized by the amount of red, green, and blue light they emit, and the material property of surfaces is characterized by the percentage of the incoming red, green, and blue components that is reflected in various directions.

**Phong lighting model.** The OpenGL lighting model considers the lighting to be divided into three independent components: ambient, diffuse, and specular. All these components are computed independently and then added together.

OpenGL provides `glLightfv() `to set ambient, diffuse and specular component of the light, e.g.,:

```c++
GLfloat sun_light_position[] = { 0.0f, 6.0f, 0.0f, 0.0f };
GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat sun_light_specular[] = { 1.0f, 1.0f, 0.0f, 1.0f }; 
glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
```

After you define the characteristics of the light sources you want, you have to turn them on with the `glEnable()` command. You also need to call `glEnable()` with `GL_LIGHTING` as a parameter to prepare OpenGL to perform lighting calculations. 

*With OpenGL, you need to explicitly enable (or disable) lighting. If lighting isn't enabled, the current color is simply mapped onto the current vertex, and no calculations concerning normals, light sources, the lighting model, and material properties are performed.*  

Here's how to enable lighting:

```c++
glEnable(GL_LIGHTING);
```

To disable lighting, call `glDisable()` with `GL_LIGHTING` as the argument. You also need to explicitly enable each light source that you define, after you've specified the parameters for that source.

```c++
glEnable(GL_LIGHT0);
```

After you enable the light, you need to set the object material properties.

```c++
GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 1.0f, 1.0f };   
GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f }; 
GLfloat earth_mat_specular[] = { 1.0f, 0.0f, 0.0f, 1.0f };  
GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };    
GLfloat earth_mat_shininess = 30.0f;
glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
```

After defining the material properties of the object, you can define `drawObject()` function that you write to draw the object with lighting enabled. The `drawObject()` function need to specify normal for each vertex or face. For example, to define a vertex normal, you can do it like:

```c++
glNormal3f(nx, ny, nz);
glVertex3f(x, y, z);
```

And you can ask OpenGL to re-normalize the normal automatically:

```
glEnable(GL_NORMALIZE);
```

Note that normalization of normal is very important! 

Of course, you can calculate the normal to define (nx, ny, nz) based on face normal calculation which should give more reasonable shading appearance.

Here is the pseudo-code:

```c++
triangle(v1,v2,v3);
edge1 = v2-v1;
edge2 = v3-v1;
triangle.normal = cross(edge1, edge2).normalize();
```

 Also a manual normalization function could be defined as follows:

```c++
void normalize(float v[3])
{
       GLfloat d = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]+e);
       v[0] /= d; v[1] /= d; v[2] /= d;
}
```

Here, e is a small value which can be set 1e-6 to omit zero case.



### **5.Manipulating camera**

#### **Navigate in virtual world.** 

To navigate in your virtual scene, you need to change your camera from time to time. 

We only have to specify a camera position, a target position and a vector that represents the up vector in world space (the up vector we used for calculating the right vector), and the OpenGL will help you construct the view matrix by `gluLookAt(...)`. 

If we want to achieve pitch and yaw of the camera, we only need to change the target position that the camera looks at in `gluLookAt(...)`. If we want to roll the camera, we will need to change the up vector in `gluLookAt(...)`. To move the camera, we change the camera position in `gluLookAt(...)`.

#### Walk around using keyboard input. 

This can done through modifying the camera position based on its current up vector,right vector and forward vector.

#### Look around using mouse input. 

The yaw and pitch values are obtained from mouse (or controller/joystick) movement where horizontal mouse-movement affects the yaw and vertical mouse-movement affects the pitch.

When handling mouse input for a camera, there are several steps we have to take before eventually retrieving the direction vector: 

1. Calculate the mouse's offset as compared to the last frame
2. Add the map the offset values to the camera's yaw and pitch values and add to them; 
3. Add some constraints to the maximum/minimum yaw/pitch values; 
4.  Calculate the direction vector.

Check more [here](https://learnopengl.com/Getting-started/Camera) for OpenGL camera transformation.
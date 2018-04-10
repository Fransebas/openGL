//
//  glExample.cpp
//  openGlExample
//
//  Created by Centro Agdigital on 2/27/18.
//  Copyright © 2018 Fransebas. All rights reserved.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

#include "glExample.hpp"
#include "GLObject.hpp"
#include "GLEBOObject.hpp"
#include "Uniform.hpp"
#include <math.h>
#include "Texture.hpp"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/constants.hpp> // glm::pi
#include "Shader.hpp"

int init(int argc, char** argv);
void setUpMatrix();
void toI(float * matrix);
void setUpMatrix(int * rots, float * matrix);
void setUpMatrix(int * rots, float * matrix, float d);
void xRotMatrix();
void yRotMatrix();
void zRotMatrix();
void initEvents(GLFWwindow * window);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

GLuint VBO, VAO;

Shader shader = Shader("/Users/centroagdigital/Documents/Tareas/Geometria\ Analitica/openGlExample/shaders/shader.vs","/Users/centroagdigital/Documents/Tareas/Geometria\ Analitica/openGlExample/shaders/shader.fs");
Texture * textrue;
GLObject * obj;
GLObject * obj2;
GLEBOObject * objEBO;
Uniform * xRot;
Uniform * yRot;
Uniform * zRot;

double xposPrev;
double yposPrev;
double dX = 0;
double dY = 0;
bool initMouse = false;
float c = 0.001f;

float currtime = 0;
float currtimeX = 0;
float currtimeY = 0;

void processInput(GLFWwindow *window);

unsigned int indexs[] =
{
    2,0,1,
        0,3,2,
    1,6,0,
        0,6,4,
    1,2,6,
        6,2,7,
    2,3,7,
        3,5,7,
    5,6,7,
        5,4,6, // down face
    0,3,4,
        4,5,3
};

float I[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

float matrix[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

float colors[] =
{
    // front
    1.0, 1.0, 0.0, // 0
    1.0, 0.0, 0.0, // 1
    1.0, 0.0, 1.0, // 2
    0.0, 0.0, 1.0, // 3
    // back
    1.0, 0.0, 0.0, // 4
    1.0, 0.0, 0.0, // 5
    0.0, 5.0, 1.0, // 6
    1.0, 0.0, 0.0, // 7
};

float textureCoords[] =
{
    // front
    0.0, 1.0,
    0.0, 0.0,
    1.0,  1.0,
    1.0,  1.0,
    // back
    1.0, 1.0,
    1.0, 0.0,
    0.0,  1.0,
    1.0,  0.0
};

float cube[] = {
    // front
    -0.1, 0.1,  0.1,
    -0.1, 0.1,  -0.1,
    0.1,  0.1,  -0.1,
    0.1,  0.1,  0.1,
    // back
    -0.1, -0.1, 0.1,
     0.1, -0.1, 0.1,
    -0.1, -0.1, -0.1,
    0.1,  -0.1, -0.1,
};

float Vertices2[] = {
    1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    0.0f, -1.0f, 0.0f
};

float Vertices[] = {
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    0.0f,  0.5f, 0.0f   // top
};

static void RenderSceneCB(GLFWwindow *window)
{
    processInput(window);
    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    glEnableVertexAttribArray(0);
    
    
    shader.use();
    
    //obj->draw();
    objEBO->draw();
    //obj2->draw();
    textrue->bind();
    xRotMatrix();
    xRot->writeMatrix4(matrix);
    yRotMatrix();
    yRot->writeMatrix4(matrix);
    zRotMatrix();
    zRot->writeMatrix4(matrix);
    
    
    glDisableVertexAttribArray(0);
    
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


GLFWwindow * initWindow(int width, int height)
{
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow *window = glfwCreateWindow(width, height, "Window", nullptr, nullptr);
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    if(nullptr==window){
        cout << "window not initialized" << endl;
        glfwTerminate();
    }
    
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    
    if(GLEW_OK != glewInit()){
        cout  << "glewInit not initialized" << endl;
        glfwTerminate();
    }
    
    glViewport(0, 0, screenWidth, screenHeight);
    return window;
}

void xRotMatrix()
{
    currtimeX -= c*dY;
    int rots[] = {5, 6, 9,10};
    toI(matrix);
    setUpMatrix(rots, matrix);
    setUpMatrix(rots, matrix, currtimeX);
}

void yRotMatrix()
{
    currtimeY += c*dX;
    int rots[] = {0, 2, 8,10};
    toI(matrix);
    setUpMatrix(rots, matrix, currtimeY);
}

void zRotMatrix()
{
    //int rots[] = {0, 1, 4,5};
    toI(matrix);
    //setUpMatrix(rots, matrix);
}

void setUpMatrix(int * rots, float * matrix)
{
    setUpMatrix(rots, matrix, currtime);
}

void setUpMatrix(int * rots, float * matrix, float d)
{
    if (d == 0) return;
    float c = 0.001f;
    currtime += c;
    matrix[rots[0]] = cosf(d);
    matrix[rots[1]] = -sinf(d);
    matrix[rots[2]] = sinf(d);
    matrix[rots[3]] = cosf(d);
}

void toI(float * matrix)
{
    for (int i=0; i<16; i++) {
        matrix[i] = I[i];
    }
}

int init(int argc, char** argv)
{
    
    GLFWwindow * window = initWindow(800,600);
    initEvents(window);
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    textrue = new Texture("/Users/centroagdigital/Desktop/images.duckduckgo.png", true);
    
    objEBO = new GLEBOObject(indexs, (sizeof(indexs)/sizeof(*indexs)));
    objEBO->addVertex(cube, (sizeof(cube)/sizeof(*cube)), GL_STATIC_DRAW);
    objEBO->addColor(colors, (sizeof(colors)/sizeof(*colors)), GL_STATIC_DRAW);
    objEBO->addTextureCoords(textureCoords, (sizeof(textureCoords)/sizeof(*textureCoords)), GL_STATIC_DRAW);
    objEBO->initMemory();
    xRot = new Uniform(&shader, "xRot");
    yRot = new Uniform(&shader, "yRot");
    zRot = new Uniform(&shader, "zRot");
    
    shader.compile();
    xRot->read();
    yRot->read();
    zRot->read();
    
    glEnable(GL_DEPTH_TEST);
    
    while (!glfwWindowShouldClose(window))
    {
        RenderSceneCB(window);
    }
    glfwTerminate();
    
    return 0;
}

void initEvents(GLFWwindow * window)
{
    glfwSetCursorPosCallback(window, cursor_position_callback);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (!initMouse)
    {
        initMouse = true;
    } else
    {
        dX = xposPrev - xpos;
        dY = yposPrev - ypos;
    }
    
    xposPrev = xpos;
    yposPrev = ypos;
}

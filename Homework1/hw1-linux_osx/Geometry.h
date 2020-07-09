/***************************************************************************
* This file defines functions that update array-type objects that should
* then be passed onto the OpenGL shader program(s) to render the familiar
* GLUT shapes in a modern OpenGL context.
* The GLUT shapes SHOULD NOT be used in modern OpenGL due to the use of 
* deprecated (often invalid) functions. The shapes defined by GLUT are
* entirely inaccessible by the shaders due to the lack of buffer objects.
* Author: hvt001
* Written in July 2016
***************************************************************************/
#ifndef _GLUT_SHAPES_REPLACEMENT
#define _GLUT_SHAPES_REPLACEMENT

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

// These buffer objects should only be used for shapes defined in this file.
// For user-defined objects, please make separate VAOs, VBOs, etc.
extern GLuint defaultVAO, defaultVBO, defaultNBO, defaultEBO;

// The default shaders used.
extern GLuint vertexshader, fragmentshader, shaderprogram;
// Default associated variables
extern GLuint modelviewPos;
extern glm::mat4 model, view;

// Other variables
enum shape{NONE, TEAPOT, CUBE, SPHERE};
extern shape lastUsed;

void initBufferObjects();
void destroyBufferObjects();

// The actual rendering functions are defined below. Similar shapes are defined in the
// same sections.

// Teapot
// Since GLUT draws a teapot using old OpenGL, it is unusable in our modern OpenGL context
// Consequently, the teapot will be fed in as an OBJ file.
// See "Wavefront OBJ" file format on Wikipedia for more information.
extern std::vector <glm::vec3> teapotVertices;
extern std::vector <glm::vec3> teapotNormals;
extern std::vector <unsigned int> teapotIndices;
// Helper function to parse an OBJ file
void parse(const char*);

// To save time, only (re)bind the teapot buffers when needed
void bindTeapot();
void solidTeapot(float);

/*****************************************************************************************
* END OF TEAPOT SECTION
*****************************************************************************************/
#endif

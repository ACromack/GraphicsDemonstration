#include <cstdio>
#include <cstdlib>
#include <iostream>

// // GLEW - OpenGL Extension Wrangler - http://glew.sourceforge.net/
// // NOTE: include before SDL.h
#include <GL/glew.h>
#include "windows.h"

// SDL - Simple DirectMedia Layer - https://www.libsdl.org/
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

// // - OpenGL Mathematics - https://glm.g-truc.net/
#define GLM_FORCE_RADIANS // force glm to use radians
// // NOTE: must do before including GLM headers
// // NOTE: GLSL uses radians, so will do the same, for consistency
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "loadShader.h"
#include "ShaderClass.h"
#include "Triangle.h"
#include "Square.h"
#include "Circle.h"

// Background colour for the window
glm::vec3 bgColour = glm::vec3(1.0, 0.0, 0.0);

SDL_Window *win = nullptr;
SDL_GLContext glcontext;

// Functions within the main c++ file
bool initSDL(void);
bool initOGL(void);
void GameLoop(void);
void update(void);
void cleanUp(void);

// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  1.0f, 0.0f,
};

// This will identify our vertex buffer
GLuint vertexbuffer;

GLuint VertexArrayID;

// Create and compile our GLSL program from the shaders
GLuint programID;

// Get a handle for our "MVP" uniform
GLuint MatrixID;

// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
// Or, for an ortho camera :
//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

// Camera matrix
glm::mat4 View = glm::lookAt(
	glm::vec3(0, 0, 1), // Camera is at (4,3,3), in World Space
	glm::vec3(0, 0, 0), // and looks at the origin
	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
);
// Model matrix : an identity matrix (model will be at the origin)
glm::mat4 Model = glm::mat4(1.0f);

// MVP matrix : multiplication of the projection, view and model matrices
glm::mat4 MVP = Projection * View * Model;

// Create a triangle object
Triangle tri;
Square sqr1;
Circle circ(0.3f);

float rot = 0.0f;

GLuint shaderProgram_colour;
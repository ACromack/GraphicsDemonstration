//// Main code for drawing a circle with a different colour in the centre to the edge
//#include "main.h"
//
//int main(int argc, char *argv[]) {
//	//Initialise SDL
//	initSDL();
//
//	//Initialise OpenGL
//	initOGL();
//
//	//Run the "game loop"
//	GameLoop();
//
//	//Clean up the application on exit
//	cleanUp();
//	
//	return 0;
//}
//// Initialise SDL and create the window
//bool initSDL(void)
//{
//	// SDL initialise
//	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
//		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s\n",
//			SDL_GetError());
//		return 1;
//	}
//	SDL_Log("SDL initialised OK!\n");
//
//	// Window Creation - modified for OpenGL
//	win = SDL_CreateWindow("OpenGL Window", 100, 100, 800, 600,
//		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
//	if (win == nullptr) {
//		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
//			"SDL_CreateWindow init error: %s\n", SDL_GetError());
//		return 1;
//	}
//
//	return true;
//}
//
//// Initialise OpenGL and associate the context with the window
//bool initOGL(void)
//{
//	//set context attributes
//	int major = 4, minor = 3;
//
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_PROFILE_CORE); //use core profile
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); //ask for forward compatible
//	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //default, probably
//
//	// Create an OpenGL context associated with the window.
//	glcontext = SDL_GL_CreateContext(win);
//
//	if (glcontext == NULL) {
//		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
//			"SDL_GL_CreateContext init error: %s\n", SDL_GetError());
//		return 1;
//	}
//	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
//	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
//	SDL_Log("Got an OpenGL %d.%d context\n", major, minor);
//
//	//check the KHR_debug extension is supported
//	if (GL_KHR_debug)
//	{
//		std::cout << "KHR_debug supported" << std::endl;
//	}
//	//check for debug context
//	GLint c;
//	glGetIntegerv(GL_CONTEXT_FLAGS, &c);
//	if (GL_CONTEXT_FLAG_DEBUG_BIT)
//	{
//		std::cout << "OGL debug context loaded" << std::endl;
//	}
//
//	glewExperimental = GL_TRUE;
//	GLenum err = glewInit();
//
//	std::cout << "OpenGL version is " << glGetString(GL_VERSION) << std::endl;
//
//		//create shaders
//		Shader vShc("..//content//shader_vColour.vert");
//		Shader fShc("..//content//shader_vColour.frag");
//		//value = 1;
//
//		//compile the shader code
//		//1 for vertex, 2 for fragment
//		vShc.getShader(1);
//		fShc.getShader(2);
//		//value = 2;
//		
//		//
//		//Create and link the Shader program
//		shaderProgram_colour = glCreateProgram();
//		glAttachShader(shaderProgram_colour, vShc.shaderID);
//		glAttachShader(shaderProgram_colour, fShc.shaderID);
//		glLinkProgram(shaderProgram_colour);
//	
//		//delete shaders
//		glDeleteShader(vShc.shaderID);
//		glDeleteShader(fShc.shaderID);
//		//value = 3;
//
//	// Load in the shaders to programID
//	programID = LoadShaders("content/default.vert", "content/default.frag");
//
//	// Get a handle for the MVP uniform in the shaders
//	MatrixID = glGetUniformLocation(programID, "MVP");
//
//	//Model = glm::rotate(Model, -1.5708f, glm::vec3(0, 0, 1));
//	//MVP = Projection * View * Model;
//	sqr1.setBuffers();
//	tri.setBuffers();
//	circ.setBuffers();
//
//	return true;
//}
//
//// The game loop that is called every frame
//void GameLoop(void)
//{
//	//*****************************
//	//SDL handled input
//	//Any input to the program is done here
//
//	SDL_Event event;
//	bool windowOpen = true;
//
//	while (windowOpen)
//	{
//		if (SDL_PollEvent(&event))
//		{
//			switch (event.type)
//			{
//			case SDL_QUIT:
//				windowOpen = false;
//				break;
//
//
//			case SDL_KEYDOWN:
//				//if(!event.key.repeat)
//				switch (event.key.keysym.sym)
//				{
//				case SDLK_ESCAPE:
//					windowOpen = false;
//					break;
//
//					// Change the background colour to yellow
//				case SDLK_y:
//					bgColour = glm::vec3(1.0f, 1.0f, 0.0f);
//					break;
//
//					// Change the background colour to purple
//				case SDLK_p:
//					bgColour = glm::vec3(0.5f, 0.0f, 0.9f);
//					break;
//
//					// Change the background colour to red
//				case SDLK_r:
//					bgColour = glm::vec3(1.0f, 0.0f, 0.0f);
//					break;
//
//
//				default:
//					break;
//				}
//			}
//		}
//
//		update();
//
//	}
//}
//
//// Update the window and draw items to the screen
//void update(void)
//{
//	//Clear the background to the desired colour
//	glClearColor(bgColour[0], bgColour[1], bgColour[2], 1);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	rot = rot + 0.0001f;
//	Model = glm::rotate(Model, 0.001f, glm::vec3(0, 0, 1));
//	MVP = Projection * View * Model;
//
//	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
//
//
//	//glBindVertexArray(tri.VAO);
//
//	//// Draw the triangle !
//	//glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
//	//glDisableVertexAttribArray(0);
//
//	//sqr1.render();
//	// Use our shader
//	//glUseProgram(programID);
//	//tri.render();
//	glUseProgram(shaderProgram_colour);
//	circ.render();
//
//	//glUseProgram(shaderProgram_colour);
//	//sqr1.render();
//	//sqr1.render();
//
//	//tri.render();
//
//	//Swap the buffers (draw to the screen)
//	SDL_GL_SwapWindow(win);
//}
//
//// Clean up after closing the application
//void cleanUp(void)
//{
//	// Clean up
//	SDL_Log("Finished. Cleaning up and closing down\n");
//
//	// Cleanup VBO and shader
//	glDeleteBuffers(1, &vertexbuffer);
//	glDeleteProgram(programID);
//	glDeleteVertexArrays(1, &VertexArrayID);
//
//	// Once finished with OpenGL functions, the SDL_GLContext can be deleted.
//	SDL_GL_DeleteContext(glcontext);
//
//	SDL_Quit();
//}
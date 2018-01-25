#include "main.h"

int main(int argc, char *argv[]) {
	//Initialise SDL
	initSDL();

	//Initialise OpenGL
	initOGL();

	//Run the "game loop"
	GameLoop();

	//Clean up the application on exit
	cleanUp();
	
	return 0;
}

bool initSDL(void)
{
	// SDL initialise
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s\n",
			SDL_GetError());
		return 1;
	}
	SDL_Log("SDL initialised OK!\n");

	// Window Creation - modified for OpenGL
	win = SDL_CreateWindow("OpenGL Window", 100, 100, 800, 600,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (win == nullptr) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_CreateWindow init error: %s\n", SDL_GetError());
		return 1;
	}

	return true;
}

bool initOGL(void)
{
	//set context attributes
	int major = 4, minor = 3;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_PROFILE_CORE); //use core profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); //ask for forward compatible
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //default, probably

	// Create an OpenGL context associated with the window.
	glcontext = SDL_GL_CreateContext(win);

	if (glcontext == NULL) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_GL_CreateContext init error: %s\n", SDL_GetError());
		return 1;
	}
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
	SDL_Log("Got an OpenGL %d.%d context\n", major, minor);

	//check the KHR_debug extension is supported
	if (GL_KHR_debug)
	{
		std::cout << "KHR_debug supported" << std::endl;
	}
	//check for debug context
	GLint c;
	glGetIntegerv(GL_CONTEXT_FLAGS, &c);
	if (GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		std::cout << "OGL debug context loaded" << std::endl;
	}

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	std::cout << "OpenGL version is " << glGetString(GL_VERSION) << std::endl;

	return true;
}

void GameLoop(void)
{
	//*****************************
	//SDL handled input
	//Any input to the program is done here

	SDL_Event event;
	bool windowOpen = true;

	while (windowOpen)
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				windowOpen = false;
				break;


			case SDL_KEYDOWN:
				//if(!event.key.repeat)
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					windowOpen = false;
					break;

					// Change the background colour to yellow
				case SDLK_y:
					bgColour = glm::vec3(1.0f, 1.0f, 0.0f);
					break;

					// Change the background colour to purple
				case SDLK_p:
					bgColour = glm::vec3(0.5f, 0.0f, 0.9f);
					break;

					// Change the background colour to red
				case SDLK_r:
					bgColour = glm::vec3(1.0f, 0.0f, 0.0f);
					break;


				default:
					break;
				}
			}
		}

		update();

	}
}

void update(void)
{
	//Clear the background to the desired colour
	glClearColor(bgColour[0], bgColour[1], bgColour[2], 1);
	glClear(GL_COLOR_BUFFER_BIT);

	//Swap the buffers (draw to the screen)
	SDL_GL_SwapWindow(win);
}

void cleanUp(void)
{
	// Clean up
	SDL_Log("Finished. Cleaning up and closing down\n");

	// Once finished with OpenGL functions, the SDL_GLContext can be deleted.
	SDL_GL_DeleteContext(glcontext);

	SDL_Quit();
}
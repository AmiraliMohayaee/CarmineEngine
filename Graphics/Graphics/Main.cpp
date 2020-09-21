#include <Windows.h>
#include <gl/GL.h>
#include <SDL.h>
#include <iostream>


int main(int argc, char* args[])
{
	// Variables needed to create a window and link 
	// OGL and SDL together
	SDL_Window* window;
	SDL_GLContext context;

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL not initialized!" << std::endl;
	}
	else
	{
		std::cout << "SDL initialized successfully!" << std::endl;
	}


	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == -1)
	{
		std::cout << "SDL subsytems initialization failed!" << std::endl;
	}
	else
	{
		std::cout << "SDL subsytems initialization successfull!" << std::endl;
	}

	// Reserving buffer for RGBA
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	// Setting up the back and front buffers
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//set a core OpenGL context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//set a compatibility OpenGL context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	// Setting up OGL to version 4.0
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	// Creating the window
	window = SDL_CreateWindow("The First Window", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1280, 720, SDL_WINDOW_OPENGL);

	if (!window)
	{
		std::cout << "Failed to create window." << std::endl;
	}
	else
	{
		std::cout << "Window created successfully!" << std::endl;
	}

	// Setting OGL's context to the window created
	context = SDL_GL_CreateContext(window);

	if (!context)
	{
		std::cout << "Failed to set OpenGL's context to SDL window." << std::endl;
	}
	else
	{
		std::cout << "OpenGL context successfully set to SDL window" << std::endl;
	}


	while (1)
	{
		glClear(GL_COLOR_BUFFER_BIT);


		glBegin(GL_TRIANGLES);
			glColor3f(1, 0, 0);
			glVertex3f(0.0f, 0.5f, 0.0f);
			
			glColor3f(0, 1, 0);
			glVertex3f(0.5f, -0.5f, 0.0f);

			glColor3f(0, 0, 1);
			glVertex3f(-0.5f, -0.5f, 0.0f);

		glEnd();

		
		//glBegin(GL_QUADS);
		//	//top left color and vertex of quad
		//	glColor3f(1, 0, 0);
		//	glVertex3f(-0.5f, 0.5f, 0.0f);
		//	//top right color and vertex of quad
		//	glColor3f(0, 1, 0);
		//	glVertex3f(0.5f, 0.5f, 0.0f);
		//	//bottom right color and vertex of quad
		//	glColor3f(0, 0, 1);
		//	glVertex3f(0.5f, -0.5f, 0.0f);
		//	//bottom left color and vertex of quad
		//	glColor3f(0, 0, 1);
		//	glVertex3f(-0.5f, -0.5f, 0.0f);
		//glEnd();



		SDL_GL_SwapWindow(window);
	}

	//free OpenGL context
	SDL_GL_DeleteContext(context);
	//free game screen and window
	SDL_DestroyWindow(window);
	//shut down all SDL sub-systems
	SDL_Quit();


	return 0;
}
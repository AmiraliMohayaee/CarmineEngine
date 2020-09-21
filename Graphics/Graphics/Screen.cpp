#include "Screen.h"
#include <fstream>
#include <string>


Screen::Screen()
{
	window = nullptr;
	context = nullptr;
}

bool Screen::InitScreen()
{
	// temporary variables to contain variables from
	// file. tempString will hold the entirety of the 
	// file's contents
	std::string tempString;
	std::string appName;
	std::string glMode;
	int resolutionW = 0;
	int resolutionH = 0;
	int oglMajorVersion = 0;
	int oglMinorVersion = 0;
	int isFullScreen = 0;


	// Setting up the settings file which will include initialization 
	// parameters
	std::ifstream settingsFile;
	settingsFile.open("Assets/Scripts/settings.txt", std::ios_base::in);
	

	if (settingsFile.fail())
	{
		std::cout << "Problem reading Settings file." << std::endl;
		return false;
	}

	while (!settingsFile.eof())
	{
		std::getline(settingsFile, tempString);

		// Keeps a track of where we are in the file
		int pos = 0;

		if (tempString.find("AppTitle") < tempString.length())
		{
			pos = tempString.find("=");
			appName = tempString.substr(pos + 1, tempString.length());
		}

		if (tempString.find("ScreenWidth") < tempString.length())
		{
			pos = tempString.find("=");
			std::string tempwidth = tempString.substr(pos + 1, tempString.length());
			resolutionW = std::stoi(tempwidth);
		}

		if (tempString.find("ScreenHeight") < tempString.length())
		{
			pos = tempString.find("=");
			resolutionH = std::stoi(tempString.substr(pos + 1, tempString.length()));
		}

		if (tempString.find("Fullscreen") < tempString.length())
		{
			pos = tempString.find("=");
			isFullScreen = std::stoi(tempString.substr(pos + 1, tempString.length()));
		}

		if (tempString.find("OpenGLMode") < tempString.length())
		{
			pos = tempString.find("=");
			glMode = tempString.substr(pos + 1, tempString.length());
		}

		if (tempString.find("OpenGLVersion") < tempString.length())
		{
			pos = tempString.find("=");
			oglMajorVersion = std::stoi(tempString.substr(pos + 1, tempString.length()));
			pos = tempString.find(".");
			oglMinorVersion = std::stoi(tempString.substr(pos + 1, tempString.length()));
		}

	}

	// Closing file once all settings have been carried over
	settingsFile.close();

	// Initial check for SDL's status
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL not initialized!" << std::endl;
		return false;
	}
	else
	{
		std::cout << "SDL initialized successfully!" << std::endl;
	}

	// Setting up SDL modes
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == -1)
	{
		std::cout << "SDL subsytems initialization failed!" << std::endl;
		return false;
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


	if (glMode == "Core")
	{
		//set a core OpenGL context (does not accept legacy functionality)
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	}
	else if (glMode == "Compatible")
	{
		//set a compatibility OpenGL context
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	}


	// Setting up OGL to version 4.6
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, oglMajorVersion);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, oglMinorVersion);

	// Creating the window
	window = SDL_CreateWindow(appName.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		resolutionW, resolutionH,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);


	if (!window)
	{
		std::cout << "Failed to create window." << std::endl;
		return false;
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
		return false;
	}
	else
	{
		std::cout << "OpenGL context successfully set to SDL window" << std::endl;
	}


	return true;
}


void Screen::Draw()
{

}


void Screen::Update()
{
	Color color;
	Position position;

	while (1)
	{
		color.r += 0.1f;
		color.g += 0.1f;
		color.b += 0.1f;

		// Clears the frame buffer
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_QUADS);

			glBegin(GL_QUADS);
				//top left color and vertex of quad
				glColor3f(1, 0, 0);
				glVertex3f(-0.5f, 0.5f, 0.0f);

				//top right color and vertex of quad
				glColor3f(0, 1, 0);
				glVertex3f(0.5f, 0.5f, 0.0f);

				//bottom right color and vertex of quad
				glColor3f(0, 0, 1);
				glVertex3f(0.5f, -0.5f, 0.0f);

				//bottom left color and vertex of quad
				glColor3f(0, 0, 1);
				glVertex3f(-0.5f, -0.5f, 0.0f);
			glEnd();

			//glTranslatef(position.x + 0.01f, position.y, position.z);

			if (position.x == 0.5f)
			{
				glTranslatef(position.x + 0.01f, position.y + 0.0f, position.z + 0.0f);
			}

			if (position.x > 1.0f)
			{
				//position.x -= 0.1f;
				//glRotatef(1.0f, 0.0f, 1.0f, 0.0f);
				glTranslatef(position.x - 0.01f, position.y + 0.0f, position.z + 0.0f);
			}
			else if (position.x < -1.0f)
			{
				//position.x += 0.1f;
				//glRotatef(1.0f, 0.0f, 1.0f, 0.0f);
				glTranslatef(position.x + 0.01f, position.y + 0.0f, position.z + 0.0f);
			}

		glEnd();


		//// Second Tri
		//glBegin(GL_TRIANGLES);

		//	glColor3f(1, 0, 0);
		//	glVertex3f(0.0f, 0.5f, 0.0f);

		//	glColor3f(0, 1, 0);
		//	glVertex3f(0.5f, -0.5f, 0.5f);

		//	glColor3f(0, 0, 1);
		//	glVertex3f(-0.5f, -0.5f, 0.0f);

		//glEnd();




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


		// swapping buffer each frame
		SDL_GL_SwapWindow(window);
	}
}

void Screen::Shutdown()
{
	//free OpenGL context
	SDL_GL_DeleteContext(context);
	//free game screen and window
	SDL_DestroyWindow(window);
	//shut down all SDL sub-systems
	SDL_Quit();
}

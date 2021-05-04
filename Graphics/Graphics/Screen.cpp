#include "Screen.h"
#include <fstream>
#include <string>


Screen::Screen()
{
	window = nullptr;
	context = nullptr;

	m_applicationName = "";
	m_glMode = "";
	m_resolutionWidth = 0;
	m_resolutionHeight = 0;
	m_oGLMajorVersion = 0;
	m_oGLMinorVersion = 0;
	m_isFullScreen = 0;
}

Screen* Screen::Instance()
{
	static Screen* screenInstance = new Screen();

	return screenInstance;
}

bool Screen::InitScreen()
{
	//TODO Pass these into a parser
	/////////////////////////////////////////////////////////
	// Temporary File Variables
	/////////////////////////////////////////////////////////
	std::string tempString;


	/////////////////////////////////////////////////////////
	// Setting up the settings file which will include  
	// initialization parameters
	/////////////////////////////////////////////////////////
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
			m_applicationName = tempString.substr(pos + 1, tempString.length());
		}

		if (tempString.find("ScreenWidth") < tempString.length())
		{
			pos = tempString.find("=");
			std::string tempwidth = tempString.substr(pos + 1, tempString.length());
			m_resolutionWidth = std::stoi(tempwidth);
		}

		if (tempString.find("ScreenHeight") < tempString.length())
		{
			pos = tempString.find("=");
			m_resolutionHeight = std::stoi(tempString.substr(pos + 1, tempString.length()));
		}

		if (tempString.find("FullScreen") < tempString.length())
		{
			pos = tempString.find("=");
			m_isFullScreen = std::stoi(tempString.substr(pos + 1, tempString.length()));
		}

		if (tempString.find("OpenGLMode") < tempString.length())
		{
			pos = tempString.find("=");
			m_glMode = tempString.substr(pos + 1, tempString.length());
		}

		if (tempString.find("OpenGLVersion") < tempString.length())
		{
			pos = tempString.find("=");
			m_oGLMajorVersion = std::stoi(tempString.substr(pos + 1, tempString.length()));
			pos = tempString.find(".");
			m_oGLMinorVersion = std::stoi(tempString.substr(pos + 1, tempString.length()));
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


	if (m_glMode == "Core")
	{
		//set a core OpenGL context (does not accept legacy functionality)
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	}
	else if (m_glMode == "Compatible")
	{
		//set a compatibility OpenGL context
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	}

	// Setting up OGL to version 4.6
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, m_oGLMajorVersion);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, m_oGLMinorVersion);

	// Creating the window
	window = SDL_CreateWindow(m_applicationName.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		m_resolutionWidth, m_resolutionHeight,
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

	if (!gladLoadGL())
	{
		std::cout << "Failed To Load Glad Library module." << std::endl;
	}

	// Allowing the use of depth buffer
	glEnable(GL_DEPTH_TEST);

	return true;
}


void Screen::ClearBuffer()
{
	// Clears the frame buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::SwapBuffer()
{
	// swapping buffer each frame
	SDL_GL_SwapWindow(window);
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

const int Screen::GetScreenWidth()
{
	return m_resolutionWidth;
}

const int Screen::GetScreenHeight()
{
	return m_resolutionHeight;
}

/// <summary>
/// Returns the total time passed in milliseconds
/// </summary>
int Screen::GetTotalTime()
{
	return SDL_GetTicks();
}

/// <summary>
/// Returns elapsed time between ticks; This function may need to be 
/// reassessed later
/// TODO: Test Function
/// </summary>
int Screen::GetElapsedTime()
{
	int startTime = SDL_GetTicks();

	m_elapsedTime = SDL_GetTicks() - startTime;

	return m_elapsedTime;
}
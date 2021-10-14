#pragma once

#include "glad.h"
#include <SDL.h>
#include <iostream>

struct Position
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};

struct Color
{
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
};

class Screen
{
public:

	static Screen* Instance();

	bool InitScreen();

	void ClearBuffer();
	void SwapBuffer();
	void Shutdown();

	void StartUI();
	void RenderUI();
	
	const int GetScreenWidth();
	const int GetScreenHeight();

	int GetTotalTime();
	int GetElapsedTime();


private:
	Screen();
	Screen(const Screen&);
	Screen& operator=(const Screen&);

private:
	// Variables needed to create a window and link 
	// OGL and SDL together
	SDL_Window* window;
	SDL_GLContext context;

	std::string m_applicationName;
	std::string m_glMode;

	int m_elapsedTime;

	int m_resolutionWidth;
	int m_resolutionHeight;
	int m_oGLMajorVersion;
	int m_oGLMinorVersion;
	int m_isFullScreen;
};
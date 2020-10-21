#pragma once

#include "glad.h"
//#include "imgui/imgui.h"
//#include "imgui/imgui_impl_sdl.h"
//#include "imgui/imgui_impl_opengl3.h"
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


private:
	Screen();
	Screen(const Screen&);
	Screen& operator=(const Screen&);

private:
	// Variables needed to create a window and link 
	// OGL and SDL together
	SDL_Window* window;
	SDL_GLContext context;
};


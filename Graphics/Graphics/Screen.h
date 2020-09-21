#pragma once

#include <Windows.h>
#include <gl/GL.h>
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
	Screen();
	bool InitScreen();

	void Draw();
	void Update();
	void Shutdown();


private:
	// Variables needed to create a window and link 
	// OGL and SDL together
	SDL_Window* window;
	SDL_GLContext context;
};


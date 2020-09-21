#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <SDL.h>
#include <iostream>


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


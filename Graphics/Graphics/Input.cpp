#include "Input.h"
#include <iostream>

Input* Input::Instance()
{
	static Input* inputInstance = new Input();

	return inputInstance;
}

std::string Input::GetKeyCode(std::string command)
{
	
	return m_inputMessage;
}

void Input::PassKeyboardMsgDown(SDL_Event key)
{
	// Debug Checking of inputs
	std::cout << "Key Pressed!" << std::endl;
	SDL_GetScancodeFromKey(key.key.keysym.scancode);
	std::cout << "Key scancode press is: "
		<< SDL_GetScancodeName(key.key.keysym.scancode)
		<< " with the scan name of "
		<< SDL_GetKeyName(key.key.keysym.sym)
		<< std::endl;

	if (key.key.keysym.scancode == 'Q')
	{
		std::cout << "Seems liek you wanna use a Queue, heh?" << std::endl;
	}
}

void Input::PassKeyboardMsgUp(SDL_Event key)
{

}

void Input::Update()
{
	// Setting up the event type for polling
	SDL_Event events;

	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{
			case SDL_QUIT:
			{
				m_isExiting = true;
				break;
			}

			case SDL_KEYDOWN:
			{
				PassKeyboardMsgDown(events);
				break;
			}


			case SDL_KEYUP:
			{
				std::cout << "Key Released!" << std::endl;
				break;
			}

			case SDL_MOUSEMOTION:
			{
				std::cout << "Mouse motion in progress!" << std::endl;
				break;
			}
		}


	}
}


// Checking for a window exit event
bool Input::IsXClicked()
{
	return m_isExiting;
}

Input::Input()
{
	m_isExiting = false;
}

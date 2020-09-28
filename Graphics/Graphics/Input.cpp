#include "Input.h"
#include <iostream>

Input* Input::Instance()
{
	static Input* inputInstance = new Input();

	return inputInstance;
}

char Input::GetKeyCode()
{
	
	return ;
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
				std::cout << "Key Pressed!" << std::endl;
				SDL_GetScancodeFromKey(events.key.keysym.scancode);
				std::cout << "Key scancode press is: " 
					<< SDL_GetScancodeName(events.key.keysym.scancode)
					<< " with the scan name of " 
					<< SDL_GetKeyName(events.key.keysym.sym) 
					<< std::endl;
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

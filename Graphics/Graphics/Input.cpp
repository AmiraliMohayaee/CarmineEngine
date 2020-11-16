#include "Input.h"
#include "Debug.h"

Input* Input::Instance()
{
	static Input* inputInstance = new Input();

	return inputInstance;
}


void Input::PassKeyboardMsgDown(SDL_KeyboardEvent* key)
{
	// Debug Checking of inputs
	Debug::Log("Key Pressed!");
	SDL_GetScancodeFromKey(key->keysym.scancode);
	std::cout << "Key scancode press is: "
		<< SDL_GetScancodeName(key->keysym.scancode)
		<< " with the scan name of "
		<< SDL_GetKeyName(key->keysym.sym)
		<< std::endl;

	// This is not working yet
	// Why is that?
	if (key->keysym.sym == 'Q')
	{
		Debug::Log("Seems liek you wanna use a Queue, heh?");
	}
}



void Input::CheckKeyboardScancode(SDL_Scancode* scanCode)
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
				PassKeyboardMsgDown(&events.key);
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


			case SDL_MOUSEBUTTONDOWN:
			{
				Debug::Log("Mouse Button Down event detected.");
				break;
			}

			case SDL_MOUSEBUTTONUP:
			{
				Debug::Log("Mouse Button is up");
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

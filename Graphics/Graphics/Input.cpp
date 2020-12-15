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

	m_keyPressed = key->keysym.scancode;

	SDL_GetScancodeFromKey(key->keysym.scancode);
	std::cout << "Key scancode press is: "
		<< SDL_GetScancodeName(key->keysym.scancode)
		<< " with the scan name of "
		<< SDL_GetKeyName(key->keysym.sym)
		<< "with an ascii code of " << ReturnKey()
		<< std::endl;

	// This is not working yet
	// Why is that?
	if (key->keysym.sym == SDLK_q)
	{
		Debug::Log("Seems liek you wanna use a Queue, heh?");
	}

	if (key->keysym.scancode == SDL_SCANCODE_S)
	{
		Debug::Log("So, you wanna go back?");
	}
}

void Input::CheckCameraControls()
{

}

const int Input::ReturnKey()
{
	return m_keyPressed;
}

bool Input::KeyPressed()
{
	return m_isKeyPressed;
}

bool Input::KeyReleased()
{
	return m_isKeyPressed;
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


				m_isKeyPressed = true;
				
				break;
			}

			case SDL_KEYUP:
			{
				m_isKeyPressed = false;

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

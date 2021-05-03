#include "Input.h"
#include "Debug.h"

Input* Input::Instance()
{
	static Input* inputInstance = new Input();

	return inputInstance;
}


// Used for testing inputs and checking both keycodes and
// scancode recieved from a key press
void Input::PassKeyboardMsgDown(SDL_KeyboardEvent* key)
{
	// Debug Checking of inputs
	Debug::Log("Key Pressed!");

	m_keyPressed = key->keysym.scancode;

	SDL_GetScancodeFromKey(key->keysym.scancode);
	std::cout << "Key scancode press is: "
		<< SDL_GetScancodeName(key->keysym.scancode)
		<< " with the scan name of "
		<< SDL_GetKeyName(key->keysym.sym) << " and " 
		<< m_keyPressed;



	if (m_keyPressed == KEY_W)
	{
		Debug::Log("Seems liek W, heh?");
	}

}

glm::vec2 Input::GetMouseMotion()
{
	return m_mouseMotion;
}

glm::vec2 Input::GetMousePosition()
{
	return m_mousePos;
}

int Input::GetKeyPressed()
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
	// Resetting mouse motion perframe
	m_mouseMotion.x = 0.0f;
	m_mouseMotion.y = 0.0f;

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
				//PassKeyboardMsgDown(&events.key);
				
				m_keyPressed = events.key.keysym.scancode;

				m_isKeyPressed = true;
				
				break;
			}

			case SDL_KEYUP:
			{
				//Debug::Log("Key Released!");
				m_isKeyPressed = false;

				break;
			}

			case SDL_MOUSEMOTION:
			{
				//Debug::Log("Mouse motion in progress!");

				m_mouseMotion.x = events.motion.xrel;
				m_mouseMotion.y = events.motion.yrel;
				m_mousePos.x = (float)events.motion.x;
				m_mousePos.y = (float)events.motion.y;

				//Debug::Log(m_mouseMotion.x, m_mouseMotion.y, "Mouse Motion X and Y : ");
				//Debug::Log(m_mousePos.x, m_mousePos.y, "Mouse Position on screen X and Y : ");

				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{
				//Debug::Log("Mouse Button Down event detected.");

				break;
			}

			case SDL_MOUSEBUTTONUP:
			{
				//Debug::Log("Mouse Button is up");

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
	m_mouseMotion = glm::vec2();
	m_mousePos = glm::vec2();
}

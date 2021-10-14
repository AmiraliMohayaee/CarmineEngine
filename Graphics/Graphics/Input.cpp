#include "Input.h"
#include "Debug.h"

Input* Input::Instance()
{
	static Input* inputInstance = new Input();

	return inputInstance;
}

Input::Input()
{
	m_isExiting = false;
	m_mouseMotion = glm::vec2();
	m_mousePos = glm::vec2();

	m_isLeftButtonDown = false;
	m_isRightButtonDown = false;
	m_isMiddleButtonDown = false;

	m_mouseWheelMotion = 0;
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

int Input::GetMouseWheelMotion()
{
	return m_mouseWheelMotion;
}

bool Input::IsLeftButtonDown() const
{
	return m_isLeftButtonDown;
}

bool Input::IsRightButtonDown() const
{
	return m_isRightButtonDown;
}

bool Input::IsMiddleButtonDown() const
{
	return m_isMiddleButtonDown;
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

			case SDL_MOUSEWHEEL:
			{
				m_mouseWheelMotion = events.wheel.y;
			}

			// Checking which of the three main mouse
			// buttons was pressed
			case SDL_MOUSEBUTTONDOWN:
			{
				//Debug::Log("Mouse Button Down event detected.");
				
				switch (events.button.button)
				{

					case SDL_BUTTON_LEFT:
					{
						m_isLeftButtonDown = true;
						break;
					}

					case SDL_BUTTON_RIGHT:
					{
						m_isRightButtonDown = true;
						break;
					}

					case SDL_BUTTON_MIDDLE:
					{
						m_isMiddleButtonDown = true;
						break;
					}

				}

				break;
			}

			case SDL_MOUSEBUTTONUP:
			{
				//Debug::Log("Mouse Button is up");
				switch (events.button.button)
				{

					case SDL_BUTTON_LEFT:
					{
						m_isLeftButtonDown = false;
						break;
					}

					case SDL_BUTTON_RIGHT:
					{
						m_isRightButtonDown = false;
						break;
					}

					case SDL_BUTTON_MIDDLE:
					{
						m_isMiddleButtonDown = false;
						break;
					}

				}

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


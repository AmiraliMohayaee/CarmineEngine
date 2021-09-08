#pragma once

#include <SDL.h>
#include <string>
#include <gtc\matrix_transform.hpp>


enum Keys { 
	KEY_A = 4, 
	KEY_B = 5,
	KEY_C = 6, 
	KEY_D = 7, 
	KEY_E = 8, 
	KEY_F = 9,
	KEY_G = 10,
	KEY_H = 11,
	KEY_I = 12,
	KEY_J = 13,
	KEY_K = 14,
	KEY_L = 15,
	KEY_M = 16,
	KEY_N = 17,
	KEY_O = 18,
	KEY_P = 19, 
	KEY_Q = 20,
	KEY_R = 21,
	KEY_S = 22,
	KEY_T = 23,
	KEY_U = 24,
	KEY_V = 25,
	KEY_W = 26,
	KEY_X = 27,
	KEY_Y = 28,
	KEY_Z = 29,
	KEY_RIGHT = 79,
	KEY_LEFT = 80,
	KEY_DOWN = 81,
	KEY_UP = 82,
	KEY_ESC = 41,
	KEY_SPACE = 44,
	KEY_LCTRL = 224,
	KEY_LSHIFT = 225,
	KEY_LALT = 226
};


class Input
{
public:

	static Input* Instance();

public:
	void Update();
	
	// Checks the 
	void PassKeyboardMsgDown(SDL_KeyboardEvent *key);

	glm::vec2 GetMouseMotion();
	glm::vec2 GetMousePosition();
	glm::vec2 GetMouseWheel();
	
	int GetKeyPressed();
	
	bool KeyPressed();
	bool KeyReleased();

	bool IsXClicked();

private:
	Input();
	Input(const Input&);
	Input& operator=(const Input&);

private:
	
	bool m_isExiting;
	std::string m_inputMessage;

	// Return the keycode pressed according
	// to its code in the Keys enumeration
	int m_keyPressed;

	// Key Press Falg
	bool m_isKeyPressed;
	bool m_isMousePressed;

	glm::vec2 m_mouseMotion;
	glm::vec2 m_mousePos;
	glm::vec2 m_mouseWheelMotion;
};


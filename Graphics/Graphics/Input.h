#pragma once

#include <SDL.h>
#include <string>
#include <gtc\matrix_transform.hpp>


enum Keys { 
	Key_A = 4, 
	Key_B = 5,
	Key_C = 6, 
	Key_D = 7, 
	Key_E = 8, 
	Key_F = 9,
	Key_G = 10,
	Key_H = 11,
	Key_I = 12,
	Key_J = 13,
	Key_K = 14,
	Key_L = 15,
	Key_M = 16,
	Key_N = 17,
	Key_O = 18,
	Key_P = 19, 
	Key_Q = 20,
	Key_R = 21,
	Key_S = 22,
	Key_T = 23,
	Key_U = 24,
	Key_V = 25,
	Key_W = 26,
	Key_X = 27,
	Key_Y = 28,
	Key_Z = 29,
	Key_Esc = 41,
	Key_Spc = 44,
	Key_LCtrl = 224,
	Key_LShift = 225,
	Key_LAlt = 226
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
};


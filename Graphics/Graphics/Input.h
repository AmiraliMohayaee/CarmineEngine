#pragma once

#include <SDL.h>
#include <string>

enum Keys { 
	Key_A = 4, 
	Key_B = 5,
	Key_C = 6, 
	Key_D = 7, 
	Key_E = 8, 
	Key_F = 9

};


class Input
{
public:

	static Input* Instance();

public:
	void Update();
	
	// Checks the 
	void PassKeyboardMsgDown(SDL_KeyboardEvent *key);

	const int ReturnKey();
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

	int m_keyPressed;
	bool m_isKeyPressed;

};


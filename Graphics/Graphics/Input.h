#pragma once

#include <SDL.h>
#include <string>


class Input
{
public:

	static Input* Instance();

public:
	void Update();
	
	// Checks the 
	void PassKeyboardMsgDown(SDL_KeyboardEvent *key);
	void CheckKeyboardScancode(SDL_Scancode* scanCode);

	bool IsXClicked();

private:
	Input();
	Input(const Input&);
	Input& operator=(const Input&);

private:

	bool m_isExiting;
	std::string m_inputMessage;

};


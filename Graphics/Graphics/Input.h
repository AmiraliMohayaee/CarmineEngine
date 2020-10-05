#pragma once

#include <SDL.h>
#include <string>


class Input
{
public:

	static Input* Instance();

public:
	void Update();
	void Shutdown();

	// For Getting an input in simple readable string format
	// and converting and passing it into engine specific code
	std::string GetKeyCode(std::string command);
	
	void PassKeyboardMsgDown(SDL_KeyboardEvent *key);
	void PassKeyboardMsgUp(SDL_Event key);

	bool IsXClicked();

private:
	Input();
	Input(const Input&);
	Input& operator=(const Input&);

private:

	bool m_isExiting;
	std::string m_inputMessage;

};


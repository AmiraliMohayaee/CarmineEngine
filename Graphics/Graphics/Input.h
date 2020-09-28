#pragma once

#include <SDL.h>


class Input
{
public:

	static Input* Instance();

	char GetKeyCode();

	void Update();

	void Shutdown();

	bool IsXClicked();

private:
	Input();
	Input(const Input&);
	Input& operator=(const Input&);

private:

	bool m_isExiting;

};


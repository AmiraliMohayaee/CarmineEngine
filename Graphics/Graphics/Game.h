#pragma once

#include <Windows.h>
#include <SDL.h>

class Game
{
public:
	static Game* Instance();

	bool WindowInit();
	void MainLoop();
	void Shutdown();

private:
	Game();
	static Game* GetInstance;
	Game& operator=(const Game&);

private:
	bool m_isLoopRunning;

	
};


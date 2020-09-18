#include <SDL.h>
#include <iostream>


int main(int argc, char* args[])
{
	std::cout << "Test" << std::endl;

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL not initialized!" << std::endl;
	}
	else
	{
		std::cout << "SDL initialized successfully!" << std::endl;
	}

	system("pause");
	return 0;
}
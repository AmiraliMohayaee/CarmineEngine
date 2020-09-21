#include "Screen.h"
#include <iostream>


int main(int argc, char* args[])
{
	Screen screen;
	
	if (!screen.InitScreen())
	{
		return false;
		std::cout << "Failed to Initialize a screen. Check your settings file." << std::endl;
	}

	screen.Update();
	screen.Shutdown();

	return 0;
}
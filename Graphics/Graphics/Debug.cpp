#include "Debug.h"


void Debug::Log(std::string line)
{
	std::cout << line << std::endl;
}

void Debug::Log(int x, int y, int z, std::string line)
{
	std::cout << line << " " << x << ", " << y << ", " << z << std::endl;
}

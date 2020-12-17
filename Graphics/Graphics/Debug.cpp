#include "Debug.h"


void Debug::Log(std::string line)
{
	std::cout << line << std::endl;
}

void Debug::Log(std::string line, int value)
{
	std::cout << line << value << std::endl;
}

void Debug::Log(std::string line, float value)
{
	std::cout << line << value << std::endl;
}

void Debug::Log(int x, int y, std::string line)
{
	std::cout << line << " " << x << ", " << y << std::endl;
}

void Debug::Log(int x, int y, int z, std::string line)
{
	std::cout << line << " " << x << ", " << y << ", " << z << std::endl;
}

void Debug::Log(std::string line, std::string value)
{
	std::cout << line << value << std::endl;
}

void Debug::Log(std::string line, std::string value, GLuint ID)
{
	std::cout << line << value << ": " << ID << std::endl;
}

void Debug::Log(std::string line, GLuint ID)
{
	std::cout << line << ID << std::endl;
}


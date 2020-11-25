#pragma once

#include <iostream>
#include <string>
#include "glad.h"


namespace Debug
{
	void Log(std::string line);
	void Log(int x, int y, int z, std::string line);
	void Log(std::string line, std::string value);
	void Log(std::string line, std::string value, GLuint ID);
}
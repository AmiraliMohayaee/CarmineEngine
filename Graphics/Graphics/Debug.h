#pragma once

#include <iostream>
#include <string>
#include "Shader.h"

namespace Debug
{
	void Log(std::string line);
	void Log(std::string line, int value);
	void Log(int x, int y, int z, std::string line);
	void Log(std::string line, std::string value);
	void Log(std::string line, std::string value, GLuint ID);
	void Log(std::string line, GLuint ID);
}
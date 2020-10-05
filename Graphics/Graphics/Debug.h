#pragma once

#include <iostream>
#include <string>


namespace Debug
{
	void Log(std::string line);
	void Log(int x, int y, int z, std::string line);
}
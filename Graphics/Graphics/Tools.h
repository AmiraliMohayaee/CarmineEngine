#pragma once

#include <string>
#include <vector>

class Tools
{
public:

	static void RemoveCharacter(std::string& str, char character);
	static void ParseString(std::string& str, std::vector<std::string>& subStrings, char token);

};


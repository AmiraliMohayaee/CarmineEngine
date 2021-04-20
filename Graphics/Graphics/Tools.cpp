#include <iostream>
#include "Tools.h"



void Tools::RemoveCharacter(std::string& str, char character)
{
	if (!str.empty())
	{
		auto it = std::find(str.begin(), str.end(), character);

		if (it == str.end())
		{
			std::cout << "Character not found." << std::endl;
		}

		else
		{
			do
			{
				str.erase(it);
				it = std::find(str.begin(), str.end(), character);
			} while (it != str.end());
		}
	}
}

void Tools::ParseString(std::string& str, std::vector<std::string>& subStrings, char token)
{
	if (!str.empty())
	{
		size_t tokenPosition = 0;

		do
		{
			tokenPosition = str.find(token);

			if (tokenPosition > 0)
			{
				subStrings.push_back(str.substr(0, tokenPosition));
			}

			str.erase(0, tokenPosition + 1);
		} while (tokenPosition != std::string::npos);
	}

	str.clear();
}
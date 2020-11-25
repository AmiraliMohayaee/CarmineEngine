//=============================================
//	File Class for reading and writing to files
//	
//	by Amirali Mohayaee
//=============================================
#pragma once


#include <fstream>


namespace File
{
	bool ReadFromFile(std::string filename);
	bool WriteToFile(std::string filename);
	std::string ReadContentsFromFile(std::string filename);
}
#pragma once

#include "Screen.h"
#include <SDL_image.h>
#include <string>
#include <map>


class Texture
{
public:
	Texture();
	~Texture();

	static bool GetTexture(const std::string& textureID, Texture& texture);

	void Bind(); 
	void Load(const std::string& textureID, const std::string textureTag);
	void UnBind(); 
	void Unload(SDL_Surface* surface);


private:
	
	GLuint m_ID;

	// Global texture container for keeping all available textures
	static std::map<std::string, Texture>* s_textureMap;

};
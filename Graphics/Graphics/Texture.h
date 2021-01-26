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

	static Texture GetTexture(const std::string& textureID);

	bool Load(const std::string& filename, const std::string textureTag);

	void Bind(); 
	void UnBind(); 

	void Unload(SDL_Surface* surface);
	void UnloadAll();


private:
	
	GLuint m_ID;

	std::string m_tag;

	// Global texture container for keeping all available textures
	static std::map<std::string, Texture>* s_textureMap;

};
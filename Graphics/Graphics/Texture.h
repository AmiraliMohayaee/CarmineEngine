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

	bool GetTexture(const std::string& textureID, Texture& texture);

	// TODO This could be static loaded so when adding multiple objects
	static bool Load(const std::string& filename, const std::string textureTag);

	void Bind(); 
	void UnBind(); 

	// TODO Don't use the SDL type. 
	void Unload(SDL_Surface* surface);
	void UnloadAll();


private:
	
	GLuint m_ID;
	std::string m_tag;
	static std::map<std::string, Texture>* s_textureMap;

};
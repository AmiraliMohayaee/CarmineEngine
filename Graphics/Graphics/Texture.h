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
	
	// TODO This could be static loaded so when adding multiple objects
	static bool Load(const std::string& filename, const std::string textureTag);
	static void Unload(const std::string& textureID);
	static void Unload();

	GLuint GetID();
	bool GetTexture(const std::string& textureID, Texture& texture);

	void Bind();
	void UnBind();



private:

	static std::string s_rootFolderTexture;
	
	GLuint m_ID;
	std::string m_tag;
	static std::map<std::string, Texture>* s_textureMap;

};
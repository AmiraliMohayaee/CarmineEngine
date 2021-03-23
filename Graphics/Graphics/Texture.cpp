#include "Texture.h"
#include "Debug.h"

// Globally initializing the texture map in static memory
std::map<std::string, Texture>* Texture::s_textureMap = new std::map<std::string, Texture>;


Texture::Texture()
{
	m_ID = 0;
}

Texture::~Texture()
{
}


bool Texture::GetTexture(const std::string& textureID, Texture& texture)
{
	Debug::Log("Getting Texture object: ", textureID);
	auto it = s_textureMap->find(textureID);

	if (it == s_textureMap->end())
	{
		Debug::Log("Could not find texture object in texture container: ", textureID);
		return false;
	}

	texture = it->second;
	return true;
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

bool Texture::Load(const std::string& filename, const std::string textureTag)
{
	// Checking if texture already exists in the map, so we don't load it twice
	if (s_textureMap->find(textureTag) != s_textureMap->end())
	{
		Debug::Log("Texture already exists: ", textureTag);
		return false;
	}

	//if (m_ID == -1)
	//{
	//	Debug::Log("Failed to generate Texture ID for ", textureTag);
	//	return false;
	//}
	
	SDL_Surface* textureData = nullptr;
	textureData = IMG_Load(filename.c_str());

	if (!textureData)
	{
		Debug::Log("Problem loading texture data: ", filename);
		return false;
	}


	// Creating temporary texture to assign into the map
	Texture texture;


	// Generate Texture obj first before creating a surface
	// and binding it
	glGenTextures(1, &texture.m_ID);

	glBindTexture(GL_TEXTURE_2D, texture.m_ID);

		Uint8* pixels = (Uint8*)textureData->pixels;
		GLsizei width = textureData->w;
		GLsizei height = textureData->h;
		Uint8 depth = textureData->format->BytesPerPixel;
		GLint format = ((depth == 4) ? GL_RGBA : GL_RGB);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Additional environment texture setting that can be set in
		// the future
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		// (target texture dimentions, mipmap level, image format(RGB/RGBA), width&height,
		// image border, pixel data, pointer to pixel data
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

		glGenerateMipmap(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(textureData);

	Debug::Log("Texture File Loaded successfully: ", textureTag);
	texture.m_tag = textureTag;

	s_textureMap->insert(std::pair<std::string, Texture>(textureTag, texture));

	return true;
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Unload(const std::string& textureID)
{
	auto it = s_textureMap->find(textureID);

	if (it != s_textureMap->end())
	{
		glDeleteTextures(1, &(it->second.m_ID));
		s_textureMap->erase(it);
		Debug::Log(textureID + " removed");
	}

	else
	{
		Debug::Log(textureID + " not found in map");
	}
}

void Texture::Unload()
{
	Debug::Log("Clearing all loaded textures");

	// Clears the entire container of all texture objects
	s_textureMap->clear();
}

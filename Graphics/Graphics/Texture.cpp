#include "Texture.h"
#include "Debug.h"


std::map<std::string, Texture>* Texture::s_textureMap = new std::map<std::string, Texture>;


Texture::Texture()
{
	m_ID = -1;
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_ID);
}

// To-Do
bool Texture::GetTexture(const std::string& textureID, Texture& texture)
{




	return true;
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Load(const std::string& textureID, const std::string textureTag)
{
	glGenTextures(1, &m_ID);

	if (m_ID == -1)
	{
		Debug::Log("Failed to generate Texture ID for ", textureID);
	}

	
	SDL_Surface* textureData = nullptr;
	textureData = IMG_Load(textureID.c_str());

	if (!textureData)
	{
		Debug::Log("Problem loading texture data with accompanying ID: ", textureID);
	}

	Bind();

		GLsizei width = textureData->w;
		GLsizei height = textureData->h;
		Uint8* pixels = (Uint8*)textureData->pixels;
		Uint8 depth = textureData->format->BytesPerPixel;
		GLint format = ((depth == 4) ? GL_RGBA : GL_RGB);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		// (target texture dimentions, mipmap level, image format(RGB/RGBA), width&height,
		// image border, pixel data, pointer to pixel data
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

		glGenerateMipmap(GL_TEXTURE_2D);

	Unload(textureData);
	UnBind();

	
	s_textureMap->insert(std::pair<std::string, Texture>(textureID, *this));
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Unload(SDL_Surface* surface)
{
	SDL_FreeSurface(surface);
}

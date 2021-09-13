#pragma once

#include "Shader.h"
#include "Buffer.h"
#include "Object.h"


class Grid : public Object
{
public:

	Grid();
	virtual ~Grid() {}

	void SetupGridDimentions(int quadrants, int maxSize,
		float red, float green, float blue, float alpha);

	void Create();
	void Destroy();

	void Draw(const Shader& shader);
	void Update() {}
	

private:

	Buffer m_buffer;
	glm::vec4 m_color;

};
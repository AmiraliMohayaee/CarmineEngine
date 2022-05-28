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

	virtual void Create();
	virtual void Destroy();
	virtual void Draw(const Shader& shader);
	virtual void Update() {}

private:

	Buffer m_buffer;
	glm::vec4 m_color;

};
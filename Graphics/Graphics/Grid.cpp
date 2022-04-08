#include "Grid.h"

Grid::Grid()
{
	m_color = glm::vec4(1.0f);
}

void Grid::SetupGridDimentions(int quadrants, int maxSize,
	float red, float green, float blue, float alpha)
{
	// Setting up space for the buffer in accordance to the size
	// of the grid we are looking to make
	const GLint SIZE = maxSize;
	const GLint QUADRANTS = quadrants;
	const GLint BYTES_PER_LINE_VERTEX = 6 * sizeof(GLint);
	const GLint BYTES_PER_LINE_COLOR = 8 * sizeof(GLfloat);

	const int TOTAL_BYTES_VBO_VERTEX = SIZE * QUADRANTS * BYTES_PER_LINE_VERTEX;
	const int TOTAL_BYTES_VBO_COLOR = SIZE * QUADRANTS * BYTES_PER_LINE_COLOR;

	m_buffer.Create(SIZE * QUADRANTS * 2, false);
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, nullptr, TOTAL_BYTES_VBO_VERTEX);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, nullptr, TOTAL_BYTES_VBO_COLOR);


	m_color.r = red;
	m_color.g = blue;
	m_color.b = green;
	m_color.a = alpha;

	GLuint m_offsetVertex = 0;
	GLuint m_offsetColor = 0;

	//NEGATIVE X QUADRANT
	for (GLint i = 0; i < SIZE; i++)
	{
		// gridline vertices - negative X
		GLint vertices[] = { -SIZE + i, 0, SIZE,	// first vertex
							 -SIZE + i, 0, -SIZE	// second vertex
		};

		// gridline colors
		GLfloat colors[] = { m_color.r, m_color.g, m_color.b, m_color.a,
							 m_color.r, m_color.g, m_color.b, m_color.a };


		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), m_offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), m_offsetColor);

		m_offsetVertex += BYTES_PER_LINE_VERTEX;
		m_offsetColor += BYTES_PER_LINE_COLOR;
	}

	//POSITIVE X QUADRANT
	for (GLint i = 1; i <= SIZE; i++)
	{
		// gridline vertices - positive X
		GLint vertices[] = { 0 + i, 0, SIZE,	// first vertex
							 0 + i, 0, -SIZE	// second vertex
		};

		// gridline colors
		GLfloat colors[] = { m_color.r, m_color.g, m_color.b, m_color.a,
							 m_color.r, m_color.g, m_color.b, m_color.a };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), m_offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), m_offsetColor);

		m_offsetVertex += BYTES_PER_LINE_VERTEX;
		m_offsetColor += BYTES_PER_LINE_COLOR;
	}

	//NEGATIVE Z QUADRANT
	for (GLint i = 0; i < SIZE; i++)
	{
		// gridline vertices - positive X
		GLint vertices[] = { -SIZE, 0, -SIZE + i,	// first vertex
							  SIZE, 0, -SIZE + i	// second vertex
		};

		// gridline colors
		GLfloat colors[] = { m_color.r, m_color.g, m_color.b, m_color.a,
							 m_color.r, m_color.g, m_color.b, m_color.a };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), m_offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), m_offsetColor);

		m_offsetVertex += BYTES_PER_LINE_VERTEX;
		m_offsetColor += BYTES_PER_LINE_COLOR;
	}

	//POSITIVE Z QUADRANT
	for (int i = 1; i <= SIZE; i++)
	{
		// gridline vertices - positive X
		GLint vertices[] = { -SIZE, 0, 0 + i,	// first vertex
							  SIZE, 0, 0 + i	// second vertex
		};

		// gridline colors
		GLfloat colors[] = { m_color.r, m_color.g, m_color.b, m_color.a,
							 m_color.r, m_color.g, m_color.b, m_color.a };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), m_offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), m_offsetColor);

		m_offsetVertex += BYTES_PER_LINE_VERTEX;
		m_offsetColor += BYTES_PER_LINE_COLOR;
	}

}

void Grid::Create()
{
	// Setting up space for the buffer in accordance to the size
	// of the grid we are looking to make
	const GLint SIZE = 11;
	const GLint QUADRANTS = 4;
	const GLint BYTES_PER_LINE_VERTEX = 6 * sizeof(GLint);
	const GLint BYTES_PER_LINE_COLOR = 8 * sizeof(GLfloat);

	const int TOTAL_BYTES_VBO_VERTEX = SIZE * QUADRANTS * BYTES_PER_LINE_VERTEX;
	const int TOTAL_BYTES_VBO_COLOR = SIZE * QUADRANTS * BYTES_PER_LINE_COLOR;

	m_buffer.Create(SIZE * QUADRANTS * 2, false);
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, nullptr, TOTAL_BYTES_VBO_VERTEX);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, nullptr, TOTAL_BYTES_VBO_COLOR);


	m_color.r = 1.0f;
	m_color.g = 1.0f;
	m_color.b = 1.0f;
	m_color.a = 1.0f;

	GLuint m_offsetVertex = 0;
	GLuint m_offsetColor = 0;

	//NEGATIVE X QUADRANT
	for (GLint i = 0; i < SIZE; i++)
	{
		// gridline vertices - negative X
		GLint vertices[] = { -SIZE + i, 0, SIZE,	// first vertex
							 -SIZE + i, 0, -SIZE };	// second vertex
		
		// gridline colors
		GLfloat colors[] = { m_color.r, m_color.g, m_color.b, m_color.a,
							 m_color.r, m_color.g, m_color.b, m_color.a };


		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), m_offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), m_offsetColor);

		m_offsetVertex += BYTES_PER_LINE_VERTEX;
		m_offsetColor += BYTES_PER_LINE_COLOR;
	}

	//POSITIVE X QUADRANT
	for (GLint i = 1; i <= SIZE; i++)
	{
		// gridline vertices - positive X
		GLint vertices[] = { 0 + i, 0, SIZE,	// first vertex
							 0 + i, 0, -SIZE };	// second vertex
		
		// gridline colors
		GLfloat colors[] = { m_color.r, m_color.g, m_color.b, m_color.a,
							 m_color.r, m_color.g, m_color.b, m_color.a };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), m_offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), m_offsetColor);

		m_offsetVertex += BYTES_PER_LINE_VERTEX;
		m_offsetColor += BYTES_PER_LINE_COLOR;
	}

	//NEGATIVE Z QUADRANT
	for (GLint i = 0; i < SIZE; i++)
	{
		// gridline vertices - positive X
		GLint vertices[] = { -SIZE, 0, -SIZE + i,	// first vertex
							  SIZE, 0, -SIZE + i };	// second vertex
		
		// gridline colors
		GLfloat colors[] = { m_color.r, m_color.g, m_color.b, m_color.a,
							 m_color.r, m_color.g, m_color.b, m_color.a };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), m_offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), m_offsetColor);

		m_offsetVertex += BYTES_PER_LINE_VERTEX;
		m_offsetColor += BYTES_PER_LINE_COLOR;
	}

	//POSITIVE Z QUADRANT
	for (int i = 1; i <= SIZE; i++)
	{
		// gridline vertices - positive X
		GLint vertices[] = { -SIZE, 0, 0 + i,	// first vertex
							  SIZE, 0, 0 + i };	// second vertex
		
		// gridline colors
		GLfloat colors[] = { m_color.r, m_color.g, m_color.b, m_color.a,
							 m_color.r, m_color.g, m_color.b, m_color.a };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), m_offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), m_offsetColor);

		m_offsetVertex += BYTES_PER_LINE_VERTEX;
		m_offsetColor += BYTES_PER_LINE_COLOR;
	}
}

void Grid::Destroy()
{
	m_buffer.Destroy();
}


void Grid::Draw(const Shader& shader)
{
	shader.SendData("isLit", false);
	shader.SendData("isTextured", false);
	shader.SendData("model", m_transform.GetMatrix());

	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"), Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::INT);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"), Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);


	m_buffer.Render(Buffer::LINES);
}


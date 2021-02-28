#include "Grid.h"

Grid::Grid()
{
	m_modelMatrix = glm::mat4(1.0f);
}


//void Grid::SetupGridDimentions(int quadrants, float maxSize,
//	float red, float green, float blue)
//{
//	// Setting up space for the buffer in accordance to the size
//// of the grid we are looking to make
//	const int SIZE = static_cast<int>(maxSize);
//	const int QUADRANTS = quadrants;
//	const int BYTES_PER_LINE = 6 * sizeof(GLfloat);
//
//	const int TOTAL_BYTES_VBO = SIZE * QUADRANTS * BYTES_PER_LINE;
//	//TODO - Chang Magic Numbers
//	m_buffer.Create(SIZE * QUADRANTS * 2, false);
//	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, nullptr, TOTAL_BYTES_VBO);
//	m_buffer.FillVBO(Buffer::COLOR_BUFFER, nullptr, TOTAL_BYTES_VBO);
//
//
//	m_color.r = red;
//	m_color.g = green;
//	m_color.b = blue;
//
//	for (int i = 0; i < maxSize; i++)
//	{
//		// gridline vertices - negative X
//		float vertices[] = {
//			-maxSize + i, 0, maxSize,	// first vertex
//			-maxSize + i, 0, -maxSize	// second vertex
//		};
//
//		// gridline colors
//		float colors[] = {
//			m_color.r, m_color.g, m_color.b,
//			m_color.r, m_color.g, m_color.b
//		};
//
//
//		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), m_offset);
//		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), m_offset);
//
//		/*	m_buffer.BindVerticesWithSubdata(m_vertexVBO, m_vertexContainer, m_offset);
//			m_buffer.BindColorsWithSubData(m_colorsVBO, m_colorContainer, m_offset);*/
//
//		m_offset += BYTES_PER_LINE;
//	}
//
//	for (int i = 0; i < maxSize; i++)
//	{
//		// gridline vertices - positive X
//		float vertices[] = {
//			0 + (GLfloat)i, 0, maxSize,	// first vertex
//			0 + (GLfloat)i, 0, -maxSize	// second vertex
//		};
//
//		// gridline colors
//		m_colorContainer = {
//			m_color.r, m_color.g, m_color.b,
//			m_color.r, m_color.g, m_color.b
//		};
//
//		//m_buffer.BindVerticesWithSubdata(m_vertexVBO, m_vertexContainer, m_offset);
//		//m_buffer.BindColorsWithSubData(m_colorsVBO, m_colorContainer, m_offset);
//
//		m_offset += BYTES_PER_LINE;
//	}
//
//
//	for (int i = 0; i < maxSize; i++)
//	{
//		// gridline vertices - positive X
//		m_vertexContainer = {
//			-maxSize, 0, -maxSize + i,	// first vertex
//			maxSize, 0, -maxSize + i	// second vertex
//		};
//
//		// gridline colors
//		m_colorContainer = {
//			m_color.r, m_color.g, m_color.b,
//			m_color.r, m_color.g, m_color.b
//		};
//
//		//m_buffer.BindVerticesWithSubdata(m_vertexVBO, m_vertexContainer, m_offset);
//		//m_buffer.BindColorsWithSubData(m_colorsVBO, m_colorContainer, m_offset);
//
//		m_offset += BYTES_PER_LINE;
//	}
//
//
//	for (int i = 0; i < maxSize; i++)
//	{
//		// gridline vertices - positive X
//		m_vertexContainer = {
//			-maxSize, 0, 0 + static_cast<float>(i),	// first vertex
//			maxSize, 0, 0 + static_cast<float>(i)	// second vertex
//		};
//
//		// gridline colors
//		m_colorContainer = {
//			m_color.r, m_color.g, m_color.b,
//			m_color.r, m_color.g, m_color.b
//		};
//
//		/*		m_buffer.BindVerticesWithSubdata(m_vertexVBO, m_vertexContainer, m_offset);
//				m_buffer.BindColorsWithSubData(m_colorsVBO, m_colorContainer, m_offset);*/
//
//		m_offset += BYTES_PER_LINE;
//	}
//
//
//	//m_buffer.BindBufferWithDynamicDraw(m_vertexVBO, TOTAL_BYTES_VBO, m_vertexAttributeID);
//
////m_buffer.CloseVertexArray();
//}

void Grid::CreateBuffers()
{
	// Setting up space for the buffer in accordance to the size
	// of the grid we are looking to make
	const GLint SIZE = 10;
	const GLint QUADRANTS = 4;
	const GLint BYTES_PER_LINE_VERTEX = 6 * sizeof(GLint);
	const GLint BYTES_PER_LINE_COLOR = 6 * sizeof(GLfloat);

	const int TOTAL_BYTES_VBO_VERTEX = SIZE * QUADRANTS * BYTES_PER_LINE_VERTEX;
	const int TOTAL_BYTES_VBO_COLOR = SIZE * QUADRANTS * BYTES_PER_LINE_COLOR;

	//TODO - Chang Magic Numbers
	m_buffer.Create(SIZE * QUADRANTS * 2, false);
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, nullptr, TOTAL_BYTES_VBO_VERTEX);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, nullptr, TOTAL_BYTES_VBO_COLOR);


	m_color.r = 1.0f;
	m_color.g = 1.0f;
	m_color.b = 1.0f;

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
		GLfloat colors[] = { m_color.r, m_color.g, m_color.b,
							 m_color.r, m_color.g, m_color.b };


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
		GLfloat colors[] = { m_color.r, m_color.g, m_color.b,
							 m_color.r, m_color.g, m_color.b };

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
		GLfloat colors[] = { m_color.r, m_color.g, m_color.b,
							 m_color.r, m_color.g, m_color.b };

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
		GLfloat colors[] = { m_color.r, m_color.g, m_color.b,
							 m_color.r, m_color.g, m_color.b };

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), m_offsetVertex);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), m_offsetColor);

		m_offsetVertex += BYTES_PER_LINE_VERTEX;
		m_offsetColor += BYTES_PER_LINE_COLOR;
	}

	m_buffer.LinkVBO("vertexIn", Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::INT);
	m_buffer.LinkVBO("colorIn", Buffer::COLOR_BUFFER, Buffer::RGB, Buffer::FLOAT);
	//m_buffer.BindBufferWithDynamicDraw(m_vertexVBO, TOTAL_BYTES_VBO, m_vertexAttributeID);

}


void Grid::DestroyBuffers()
{
	m_buffer.Destroy();
}


void Grid::Draw()
{
	Shader::Instance()->SendUniformData("isTextured", false);
	Shader::Instance()->SendUniformData("model", m_modelMatrix);

	m_buffer.Render(Buffer::LINES);
}
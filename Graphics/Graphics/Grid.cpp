#include "Grid.h"

Grid::Grid()
{
	// a value to keep in track of where 
	// we are when filling up the buffer
	// for the grid
	m_offset = 0;

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
	const int SIZE = 10;
	const int QUADRANTS = 4;
	const int BYTES_PER_LINE = 6 * sizeof(GLfloat);

	const int TOTAL_BYTES_VBO = SIZE * QUADRANTS * BYTES_PER_LINE;
	//TODO - Chang Magic Numbers
	m_buffer.Create(SIZE * QUADRANTS * 2, false);
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, nullptr, TOTAL_BYTES_VBO);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, nullptr, TOTAL_BYTES_VBO);


	m_color.r = 1.0f;
	m_color.g = 1.0f;
	m_color.b = 1.0f;

	for (int i = 0; i < 10; i++)
	{
		// gridline vertices - negative X
		float vertices[] = {
			-10.0f + i, 0, 10.0f,	// first vertex
			-10.0f + i, 0, -10.0f	// second vertex
		};

		// gridline colors
		float colors[] = {
			m_color.r, m_color.g, m_color.b,
			m_color.r, m_color.g, m_color.b
		};


		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), m_offset);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), m_offset);

		m_offset += BYTES_PER_LINE;
	}

	for (int i = 0; i < 10; i++)
	{
		// gridline vertices - positive X
		float vertices[] = {
			0 + (GLfloat)i, 0, 10.0f,	// first vertex
			0 + (GLfloat)i, 0, -10.0f	// second vertex
		};

		// gridline colors
		float colors[] = {
			m_color.r, m_color.g, m_color.b,
			m_color.r, m_color.g, m_color.b
		};

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), m_offset);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), m_offset);

		m_offset += BYTES_PER_LINE;
	}


	for (int i = 0; i < 10; i++)
	{
		// gridline vertices - positive X
		float vertices[] = {
			-10.0f, 0, -10.0f + static_cast<float>(i),	// first vertex
			10.0f, 0, -10.0f + static_cast<float>(i)	// second vertex
		};

		// gridline colors
		float colors[] = {
			m_color.r, m_color.g, m_color.b,
			m_color.r, m_color.g, m_color.b
		};

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), m_offset);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), m_offset);


		m_offset += BYTES_PER_LINE;
	}


	for (int i = 0; i < 10; i++)
	{
		// gridline vertices - positive X
		float vertices[] = {
			-10.0f, 0, 0 + static_cast<float>(i),	// first vertex
			10.0f, 0, 0 + static_cast<float>(i)	// second vertex
		};

		// gridline colors
		float colors[] = {
			m_color.r, m_color.g, m_color.b,
			m_color.r, m_color.g, m_color.b
		};

		m_buffer.AppendVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), m_offset);
		m_buffer.AppendVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), m_offset);

		m_offset += BYTES_PER_LINE;
	}

	m_buffer.LinkVBO("vertexIn", Buffer::VERTEX_BUFFER, Buffer::XYZ);
	m_buffer.LinkVBO("colorIn", Buffer::COLOR_BUFFER, Buffer::RGB);
	//m_buffer.BindBufferWithDynamicDraw(m_vertexVBO, TOTAL_BYTES_VBO, m_vertexAttributeID);

}

void Grid::DestroyBuffers()
{
	m_buffer.Destroy();
}


void Grid::Draw()
{
	Shader::Instance()->SendUniformData("model", m_modelMatrix);

	m_buffer.Render(Buffer::LINES);
}

void Grid::Update()
{

}

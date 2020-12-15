#include "Grid.h"

Grid::Grid()
{
	m_VAO = 0;
	m_vertexVBO = 0;
	m_colorsVBO = 0;
	m_EBO = 0;

	// a value to keep in track of where 
	// we are when filling up the buffer
	// for the grid
	m_offset = 0;

	m_vertexAttributeID = 0;
	m_colorAttributeID = 0;
	m_modelUniformID = 0;

	m_modelMatrix = glm::mat4(1.0f);
}


void Grid::CreateBuffer()
{
	m_buffer.GenerateVertexArray(1, m_VAO);
	
	m_buffer.GenerateBuffer(1, m_colorsVBO);



	// Setting up space for the buffer in accordance to the size
	// of the grid we are looking to make
	const int SIZE = 10;
	const int QUADRANTS = 4;
	const int BYTES_PER_LINE = 6 * sizeof(GLfloat);

	const int TOTAL_BYTES_VBO = SIZE * QUADRANTS * BYTES_PER_LINE;

	m_buffer.CreateEmptyVBO(m_vertexVBO, TOTAL_BYTES_VBO, m_vertexAttributeID);
}


void Grid::SetupGridDimentions(int quadrants, float maxSize,
	float red, float green, float blue)
{
	m_buffer.BindVertexArray(m_VAO);


		for (int i = 0; i < maxSize; i++)
		{
			// gridline vertices
			m_vertexContainer = {
				-maxSize + i, 0, maxSize,	// first vertex
				-maxSize + i, 0, -maxSize	// second vertex
			};
		
			// gridline colors
			m_colorContainer = {
				m_color.r, m_color.g, m_color.b,
				m_color.r, m_color.g, m_color.b
			};

			m_buffer.BindVerticesWithSubdata(m_vertexVBO, m_vertexContainer, m_offset);
			m_buffer.BindColorsWithSubData(m_colorsVBO, m_colorContainer, m_offset);

			m_offset += 24;
		}

	m_buffer.CloseVertexArray();
}


void Grid::Draw()
{
	m_buffer.BindVertexArray(m_VAO);

		glDrawArrays(GL_LINE, 0, 80);

	m_buffer.CloseVertexArray();
}

void Grid::Update()
{

}

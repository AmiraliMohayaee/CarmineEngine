#include "Cube.h"
#include "Debug.h"
#include "Screen.h"
#include "Input.h"


Cube::Cube()
{
	m_VAO = 0;
	m_vertexVBO = 0;
	m_colorsVBO = 0;
	m_EBO = 0;

	m_vertexAttributeID = 0;
	m_colorAttributeID = 0;

	m_modelUniformID = 0;

	m_modelMatrix = glm::mat4(1.0f);
	//m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

Cube::~Cube()
{
	glDisableVertexAttribArray(m_colorAttributeID);
	glDisableVertexAttribArray(m_vertexAttributeID);
	glDisableVertexAttribArray(m_modelUniformID);

	glDeleteBuffers(1, &m_vertexVBO);
	glDeleteBuffers(1, &m_colorsVBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteVertexArrays(1, &m_VAO);
}

void Cube::CreateBuffers()
{
	// Seperate vertex data buffer object
	m_vertexContainer = { 
		-0.5f,  0.5f,  0.5f,       //front vertices
		0.5f,  0.5f,  0.5f,       //front vertices
		0.5f, -0.5f,  0.5f,       //front vertices
		-0.5f, -0.5f,  0.5f,       //front vertices
		
		-0.5f,  0.5f,  -0.5f,       //front vertices
		0.5f,  0.5f,  -0.5f,       //front vertices
		0.5f, -0.5f,  -0.5f,       //front vertices
		-0.5f, -0.5f,  -0.5f,       //front vertices		   
								   
		-0.5f,  0.5f, -0.5f,       //back vertices
		0.5f,  0.5f, -0.5f,       //back vertices
		0.5f, -0.5f, -0.5f,       //back vertices
		-0.5f, -0.5f, -0.5f       //back vertices

		- 0.5f,  0.5f, -0.5f,       //back vertices
		0.5f,  0.5f, -0.5f,       //back vertices
		0.5f, -0.5f, -0.5f,       //back vertices
		-0.5f, -0.5f, -0.5f       //back vertices
	};


	// Passing in color data
	m_colorContainer = {
		1.0f, 0.0f, 0.0f,            //red front face
		0.0f, 1.0f, 0.0f,            //green back face
		0.0f, 0.0f, 1.0f,            //blue left face
		0.0f, 1.0f, 1.0f,            //cyan right face
		//1.0f, 1.0f, 0.0f,            //yellow top face
		//1.0f, 0.0f, 1.0f };          //purple bottom face
	};

	// EBO indecies shared between the two triangles
	m_indiciesContainer = { 0,  1,  3,  3,  1,  2,      //front face
		4,  5,  7,  7,  5,  6,      //back face
		4,  0,  7,  7,  0,  3,      //left face
		1,  5,  2,  2,  5,  6,      //right face
		5,  1,  4,  4,  1,  0,      //top face
		6,  2,  7,  7,  2,  3     //bottom face
	};
	
	m_vertexAttributeID = Shader::Instance()->GetAttributeID("vertexIn");
	m_colorAttributeID = Shader::Instance()->GetAttributeID("colorIn");
	m_modelUniformID = Shader::Instance()->GetUniformID("model");

	Shader::Instance()->EnableVertexAttributeArray(m_vertexAttributeID);
	Shader::Instance()->EnableVertexAttributeArray(m_colorAttributeID);
	Shader::Instance()->EnableVertexAttributeArray(m_modelUniformID);
	
	m_buffer.GenerateVertexArray(1, m_VAO);
	m_buffer.GenerateBuffer(1, m_vertexVBO);
	m_buffer.GenerateBuffer(1, m_colorsVBO);
	m_buffer.GenerateBuffer(1, m_EBO);

	m_buffer.BindVertexArray(m_VAO);

		m_buffer.BindVertices(m_vertexVBO, m_vertexContainer, m_vertexAttributeID);
		m_buffer.BindColors(m_colorsVBO, m_colorContainer, m_colorAttributeID);
		m_buffer.BindEBOArray(m_EBO, m_indiciesContainer);

	m_buffer.CloseVertexArray();

}

void Cube::Draw()
{
	Shader::Instance()->SendUniformData("model", m_modelMatrix);
	
	m_buffer.BindVertexArray(m_VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	m_buffer.CloseVertexArray();
}

void Cube::Update()
{


}
#include "Cube.h"
#include "Debug.h"



Cube::Cube()
{
	m_VAO = 0;
	m_vertexVBO = 0;
	m_colorsVBO = 0;
	m_EBO = 0;

	m_vertexAttributeID = 0;
	m_colorAttributeID = 0;

	m_modelMatrix = glm::mat4(1.0f);
	//m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	m_cameraPos = glm::vec3(0, 0, 0);
	m_cameraUp = glm::vec3(0, 0, -1);
	m_cameraForward = glm::vec3(0, 1, 0);

	m_viewMatrix = glm::mat4(1.0f);
	m_viewMatrix = glm::lookAt(m_cameraPos, m_cameraUp, m_cameraForward);

	//m_cameraPos + glm::vec3(0.0f, 0.0f, -1.0f);
}

Cube::~Cube()
{
	glDisableVertexAttribArray(m_colorAttributeID);
	glDisableVertexAttribArray(m_vertexAttributeID);

	glDeleteBuffers(1, &m_vertexVBO);
	glDeleteBuffers(1, &m_colorsVBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteVertexArrays(1, &m_VAO);
}

void Cube::CreateBuffers()
{
	// Seperate vertex data buffer object
	GLfloat vertices[] = { -0.5f,  0.5f, 0.0f,
							0.5f,  0.5f, 0.0f,
							0.5f, -0.5f, 0.0f,
							-0.5f, -0.5f, 0.0f
	};

	// Passing in color data
	GLfloat colors[] = { 1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f,
						0.0f, 1.0f, 0.0f,
						0.0f, 1.0f, 1.0f
	};

	// EBO indecies shared between the two triangles
	GLfloat indicies[] = { 0, 1, 3,
		3, 1, 2
	};

	//Shader::BindAttribute()

	m_vertexAttributeID = Shader::Instance()->GetAttributeID("vertexIn");
	m_colorAttributeID = Shader::Instance()->GetAttributeID("colorIn");
	m_modelUniformID = Shader::Instance()->GetUniformID("model");
	m_viewUniformID = Shader::Instance()->GetUniformID("view");

	
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_vertexVBO);
	glGenBuffers(1, &m_colorsVBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(m_vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(m_vertexAttributeID);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		glVertexAttribPointer(m_colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(m_colorAttributeID);

		// Setting up the EBO buffer elements, which is differentiated from the regular
		// array elements
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

		Shader::Instance()->SendUniformData("view", m_viewMatrix);

	glBindVertexArray(0);

}

void Cube::Draw()
{
	glBindVertexArray(m_VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		Shader::Instance()->SendUniformData("model", m_modelMatrix);
		Shader::Instance()->SendUniformData("view", m_viewMatrix);

	glBindVertexArray(0);
}

void Cube::Update()
{
	//=============================================================
	//	Checking values of shader elements
	//=============================================================
	Debug::Log("This uniform ID check return this attribute: ",
		"Vertex ID",
		Shader::Instance()->GetAttributeID("vertexIn"));

	Debug::Log("This uniform ID check return this attribute: ",
		"Color ID",
		Shader::Instance()->GetAttributeID("colorIn"));

	Debug::Log("This uniform ID check return this: ", 
		"Model Matrix ID", 
		Shader::Instance()->GetUniformID("model"));
}
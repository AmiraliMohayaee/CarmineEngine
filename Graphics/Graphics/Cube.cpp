#include "Cube.h"
#include "Debug.h"
#include "Screen.h"


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
	GLfloat vertices[] = { -0.5f,  0.5f,  0.5f,       //front vertices
		0.5f,  0.5f,  0.5f,       //front vertices
		0.5f, -0.5f,  0.5f,       //front vertices
		-0.5f, -0.5f,  0.5f,       //front vertices
		
						 -0.5f,  0.5f,  -0.5f,       //front vertices
		0.5f,  0.5f,  -0.5f,       //front vertices
		0.5f, -0.5f,  -0.5f,       //front vertices
		-0.5f, -0.5f,  -0.5f,       //front vertices

								   
								   
								   //-0.5f,  0.5f, -0.5f,       //back vertices
		//0.5f,  0.5f, -0.5f,       //back vertices
		//0.5f, -0.5f, -0.5f,       //back vertices
		//-0.5f, -0.5f, -0.5f };     //back vertices
	};

	// Passing in color data
	GLfloat colors[] = { 1.0f, 0.0f, 0.0f,            //red front face
		0.0f, 1.0f, 0.0f,            //green back face
		0.0f, 0.0f, 1.0f,            //blue left face
		0.0f, 1.0f, 1.0f,            //cyan right face
		//1.0f, 1.0f, 0.0f,            //yellow top face
		//1.0f, 0.0f, 1.0f };          //purple bottom face
	};

	// EBO indecies shared between the two triangles
	GLuint indicies[] = { 0,  1,  3,  3,  1,  2,      //front face
		//4,  5,  7,  7,  5,  6,      //back face
		//4,  0,  7,  7,  0,  3,      //left face
		//1,  5,  2,  2,  5,  6,      //right face
		//5,  1,  4,  4,  1,  0,      //top face
		//6,  2,  7,  7,  2,  3  };   //bottom face
	};
	
	m_vertexAttributeID = Shader::Instance()->GetAttributeID("vertexIn");
	m_colorAttributeID = Shader::Instance()->GetAttributeID("colorIn");
	m_modelUniformID = Shader::Instance()->GetUniformID("model");


	glEnableVertexAttribArray(m_vertexAttributeID);
	glEnableVertexAttribArray(m_colorAttributeID);
	glEnableVertexAttribArray(m_modelUniformID);

	
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

		//Shader::Instance()->SendUniformData("view", m_viewMatrix);

	glBindVertexArray(0);



}

void Cube::Draw()
{
	Shader::Instance()->SendUniformData("model", m_modelMatrix);
	
	glBindVertexArray(m_VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Cube::Update()
{


}
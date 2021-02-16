#include "Cube.h"
#include "Debug.h"
#include "Screen.h"
#include "Input.h"


Cube::Cube()
{
	// Attributes
	//m_vertexAttributeID = 0;
	//m_colorAttributeID = 0;
	//m_textureAttributeID = 0;

	// Uniforms
	m_modelUniformID = 0;
	m_dimention = glm::vec3(1.0f);
	m_modelMatrix = glm::mat4(1.0f);
}

Cube::~Cube()
{
	//m_buffer.DisableVertexAttribute(m_colorAttributeID);
	//m_buffer.DisableVertexAttribute(m_vertexAttributeID);
	//m_buffer.DisableVertexAttribute(m_modelUniformID);
	//m_buffer.DisableVertexAttribute(m_textureAttributeID);

	//m_buffer.DeleteBuffer(m_vertexVBO);
	//m_buffer.DeleteBuffer(m_colorsVBO);
	//m_buffer.DeleteBuffer(m_textureVBO);
	//m_buffer.DeleteBuffer(m_EBO);
	//m_buffer.DeleteVertexArray(m_VAO);
}

void Cube::CreateBuffers()
{
	glm::vec3 halfDimension = m_dimention * 0.5f;

	float vertices[] = {
						-halfDimension.x, halfDimension.y, halfDimension.z,   //0
						halfDimension.x, halfDimension.y, halfDimension.z,    //1
						halfDimension.x, -halfDimension.y, halfDimension.z,    //2
						 -halfDimension.x, -halfDimension.y, halfDimension.z,   //3   //front face

						 -halfDimension.x, halfDimension.y, -halfDimension.z,   //4
						  halfDimension.x, halfDimension.y, -halfDimension.z,   //5
						  halfDimension.x, -halfDimension.y, -halfDimension.z,   //6
						 -halfDimension.x, -halfDimension.y, -halfDimension.z,  //7    //back face

						 -halfDimension.x, halfDimension.y, halfDimension.z,
						 -halfDimension.x, -halfDimension.y, halfDimension.z,
						 -halfDimension.x, -halfDimension.y, -halfDimension.z,
						 -halfDimension.x,  halfDimension.y, -halfDimension.z,   //left face

						  halfDimension.x,  halfDimension.y, halfDimension.z,
						  halfDimension.x, -halfDimension.y, halfDimension.z,
						  halfDimension.x, -halfDimension.y, -halfDimension.z,
						  halfDimension.x,  halfDimension.y, -halfDimension.z,   //right face

						  -halfDimension.x, halfDimension.y, -halfDimension.z,
						  halfDimension.x, halfDimension.y, -halfDimension.z,
						  halfDimension.x, halfDimension.y, halfDimension.z,
						  -halfDimension.x, halfDimension.y, halfDimension.z,   //top face

						 -halfDimension.x, -halfDimension.y, -halfDimension.z,
						  halfDimension.x, -halfDimension.y, -halfDimension.z,
						  halfDimension.x, -halfDimension.y, halfDimension.z,
						  -halfDimension.x, -halfDimension.y, halfDimension.z,   //bottom face
	};


	float colors[] = {
		1.0f, 0.5f, 0.5f,
		0.5f, 1.0f, 0.0f,
		0.5f, 1.0f, 0.0f,
		0.5f, 1.0f, 0.0f,  // front face

		1.0f, 0.5f, 0.6f,
		0.6f, 1.0f, 0.0f,
		0.6f, 1.0f, 0.0f,
		0.6f, 1.0f, 0.0f,  // back face

		1.0f, 0.7f, 0.7f,
		0.7f, 1.0f, 0.0f,
		0.7f, 1.0f, 0.0f,
		0.7f, 1.0f, 0.0f,  // right face

		1.0f, 0.5f, 0.4f,
		0.4f, 1.0f, 0.0f,
		0.4f, 1.0f, 0.0f,
		0.4f, 1.0f, 0.0f,  // left face

		1.0f, 0.2f, 0.2f,
		0.2f, 1.0f, 0.0f,
		0.2f, 1.0f, 0.0f,
		0.2f, 1.0f, 0.0f,  // top face

		1.0f, 0.5f, 0.8f,
		0.8f, 1.0f, 0.0f,
		0.8f, 1.0f, 0.0f,
		0.8f, 1.0f, 0.0f,  // bottom face
	};




	float indices[] = {
						0,  1,  3,  3,  1,  2,            //front face
						 4,  5,  7,  7,  5,  6,            //back face
						 8,  9,  11,  11,  9,  10,         //left face
						 12,  13,  15,  15,  13,  14,      //right face
						 16,  17,  19,  19,  17,  18,      //top face
						 20,  21,  23,  23,  21,  22       //bottom face
	};

	//m_texture.Load("Assets/Textures/Crate_1_Diffuse.png", "CRATE");
	
	m_vertexAttributeID = Shader::Instance()->GetAttributeID("vertexIn");
	m_colorAttributeID = Shader::Instance()->GetAttributeID("colorIn");
	//m_textureAttributeID = Shader::Instance()->GetAttributeID("textureIn");
	m_modelUniformID = Shader::Instance()->GetUniformID("model");

	//Shader::Instance()->EnableVertexAttributeArray(m_vertexAttributeID);
	//Shader::Instance()->EnableVertexAttributeArray(m_colorAttributeID);
	////Shader::Instance()->EnableVertexAttributeArray(m_textureAttributeID);
	//Shader::Instance()->EnableVertexAttributeArray(m_modelUniformID);

	m_VAO = 0;
	m_vertexVBO = 0;  
	m_colorsVBO = 0;
	m_EBO = 0;

	glGenBuffers(1, &m_vertexVBO);
	glGenBuffers(1, &m_colorsVBO);
	glGenBuffers(1, &m_EBO);

	//m_buffer.GenerateVertexArray(1, m_VAO);
	//m_buffer.GenerateBuffer(1, m_vertexVBO);
	//m_buffer.GenerateBuffer(1, m_colorsVBO);
	////m_buffer.GenerateBuffer(1, m_textureVBO);
	//m_buffer.GenerateBuffer(1, m_EBO);

	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(m_vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(m_vertexAttributeID);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		glVertexAttribPointer(m_colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(m_colorAttributeID);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);


	//m_buffer.BindVertexArray(m_VAO);

		//	m_buffer.BindVertices(m_vertexVBO, m_vertexContainer, m_vertexAttributeID);
		//	m_buffer.BindColors(m_colorsVBO, m_colorContainer, m_colorAttributeID);
		//	//m_buffer.BindTextures(m_textureVBO, m_uvContainer, m_textureAttributeID);
		//	m_buffer.BindEBOArray(m_EBO, m_indiciesContainer);

	//m_buffer.CloseVertexArray();

}

void Cube::Draw()
{
	Shader::Instance()->SendUniformData("model", m_modelMatrix);
	
	//m_texture.Bind();

		//m_buffer.BindVertexArray(m_VAO);

		glBindVertexArray(m_VAO);


			//glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		
		glBindVertexArray(0);

		//m_buffer.CloseVertexArray();

	//m_texture.UnBind();
}

void Cube::Update()
{


}
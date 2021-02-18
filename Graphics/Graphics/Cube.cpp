#include "Cube.h"
#include "Debug.h"
#include "Screen.h"
#include "Input.h"


Cube::Cube()
{
	// Uniforms
	m_modelUniformID = 0;
	m_dimention = glm::vec3(1.0f);
	m_modelMatrix = glm::mat4(1.0f);
}

Cube::~Cube()
{
	m_buffer.Destroy();
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
						1.0f, 1.0f, 1.0f,
					   1.0f, 1.0f, 1.0f,
						1.0f, 1.0f, 1.0f,
						1.0f, 1.0f, 1.0f,    //front face

						0.8f, 0.8f, 0.8f,
						0.8f, 0.8f, 0.8f,
						0.8f, 0.8f, 0.8f,
						0.8f, 0.8f, 0.8f,   //back face

						0.6f, 0.6f, 0.6f,
						0.6f, 0.6f, 0.6f,
						0.6f, 0.6f, 0.6f,
						0.6f, 0.6f, 0.6f,  //left face

						0.4f, 0.4f, 0.4f,
						0.4f, 0.4f, 0.4f,
						0.4f, 0.4f, 0.4f,
						0.4f, 0.4f, 0.4f,  //right face

						0.2f, 0.2f, 0.2f,
						0.2f, 0.2f, 0.2f,
						0.2f, 0.2f, 0.2f,
						0.2f, 0.2f, 0.2f,  //top face

						0.1f, 0.1f, 0.1f,
						0.1f, 0.1f, 0.1f,
						0.1f, 0.1f, 0.1f,
						0.1f, 0.1f, 0.1f   //bottom face
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
	


	m_buffer.Create(sizeof(vertices), true);
	m_buffer.FillVBO(m_buffer.VERTEX_BUFFER, vertices, sizeof(vertices));
	m_buffer.FillVBO(m_buffer.COLOR_BUFFER, colors, sizeof(colors));
	m_buffer.FillEBO(indices, sizeof(indices));

	m_buffer.LinkVBO("vertexIn", m_buffer.VERTEX_BUFFER, m_buffer.XYZ);
	m_buffer.LinkVBO("colorIn", m_buffer.COLOR_BUFFER, m_buffer.RGB);
	m_buffer.LinkEBO();

	//glGenVertexArrays(1, &m_VAO);

	//glBindVertexArray(m_VAO);

	//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//	glVertexAttribPointer(m_vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	//	glEnableVertexAttribArray(m_vertexAttributeID);

	//	glBindBuffer(GL_ARRAY_BUFFER, m_colorsVBO);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	//	glVertexAttribPointer(m_colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	//	glEnableVertexAttribArray(m_colorAttributeID);

	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glBindVertexArray(0);
}

void Cube::Draw()
{
	Shader::Instance()->SendUniformData("model", m_modelMatrix);


	m_buffer.Render(m_buffer.TRIANGLES);

	//
	//glBindVertexArray(m_VAO);

	//	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//	//glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	//	
	//glBindVertexArray(0);

}

void Cube::Update()
{


}
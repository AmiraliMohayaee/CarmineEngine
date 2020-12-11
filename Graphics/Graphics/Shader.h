//=============================================
//	Shader Manager used for managing Shader-
//	related functionalities including creating
//	and/or reading shaders
//
//	by Amirali Mohayaee
//=============================================
#pragma once

#include <../include/glm.hpp>
#include <string>
#include <map>
#include "glad.h"


class Shader
{
public:
	
	static Shader* Instance();

public:

	bool CreateProgram();
	bool CreateShaders();

	bool CompileShaders();
	bool CompileShader(std::string filename);
	void AttachShaders();
	bool LinkProgram();

	void DetachShaders();
	void DestroyShaders();
	void DestroyProgram();


	const GLuint GetShaderProgramID();

	const GLuint GetAttributeID(std::string attribute);
	const GLuint GetUniformID(std::string variable);

	void BindAttribute(std::string attribute);
	void BindUniform(std::string uniform);
	void EnableVertexAttributeArray(GLuint attribute);

	void SendUniformData(const std::string& uniform, GLint intData);
	void SendUniformData(const std::string& uniform, GLuint uintData); 
	void SendUniformData(const std::string& uniform, GLfloat floatData); 

	void SendUniformData(const std::string& uniform, GLfloat x, GLfloat y); 
	void SendUniformData(const std::string& uniform, GLfloat x, GLfloat y, GLfloat z); 
	void SendUniformData(const std::string& uniform, GLfloat x, GLfloat y, GLfloat z, GLfloat w); 
	void SendUniformData(const std::string& uniform, glm::mat4& mat);


private:
	Shader();
	Shader(const Shader&);
	Shader& operator=(const Shader&);

private:

	GLuint m_shaderProgramID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;

	// Container storing the ID and attributes of shader elements
	std::map<std::string, unsigned int> m_shaderAttributes;
	std::map<std::string, unsigned int> m_shaderUniforms;
};
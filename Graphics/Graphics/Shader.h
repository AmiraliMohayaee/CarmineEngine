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

	Shader();
	~Shader();

	const GLuint GetUniformID(std::string uniform) const;
	const GLuint GetAttributeID(std::string attribute) const;

	//bool Create(const std::string& )
	
	bool CreateProgram();
	bool CreateShaders();

	bool CompileShader(std::string filename);
	void AttachShaders();

	void DetachShaders();
	void DestroyShaders();
	void DestroyProgram();


	const GLuint GetShaderProgramID();


	void BindAttribute(std::string attribute);
	void BindUniform(std::string uniform);
	void EnableVertexAttributeArray(GLuint attribute);

	void SendUniformData(const std::string& uniform, GLint intData);
	void SendUniformData(const std::string& uniform, GLuint uintData); 
	void SendUniformData(const std::string& uniform, GLfloat floatData); 

	void SendUniformData(const std::string& uniform, GLfloat x, GLfloat y); 
	void SendUniformData(const std::string& uniform, GLfloat x, GLfloat y, GLfloat z); 
	void SendUniformData(const std::string& uniform, GLfloat x, GLfloat y, GLfloat z, GLfloat w); 
	void SendUniformData(const std::string& uniform, const glm::mat4& mat);



private:

	bool LinkProgram();
	bool CompileShaders();


	static std::string s_shaderRootFolder;

	GLuint m_shaderProgramID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;

	// Container storing the ID and attributes of shader elements
	std::map<std::string, unsigned int> m_shaderAttributes;
	std::map<std::string, unsigned int> m_shaderUniforms;

	// TODO start using multiple shader progreams
	std::map <std::string, unsigned int> m_shaderPrograms;
};
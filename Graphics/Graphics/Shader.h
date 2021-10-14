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
	void SendUniformData(const std::string& uniform, const glm::mat4& mat);


private:
	Shader();
	Shader(const Shader&);
	Shader& operator=(const Shader&);

private:

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



// TODO Revert the shader programs back to this implemntation
// after getting the singletonised one working with imgui
//class Shader
//{
//public:
//
//	Shader();
//	~Shader();
//
//	GLuint GetUniformID(const std::string& uniform) const;
//	GLuint GetAttributeID(const std::string& attribute) const;
//
//	bool Create(const std::string& vertexShaderFilename, 
//		const std::string& fragmentShaderFilename);
//	
//	void BindUniform(const std::string& uniform);
//	void BindAttribute(const std::string& attribute);
//
//	void SendData(const std::string& uniform, GLint intData) const;
//	void SendData(const std::string& uniform, GLuint uintData) const;
//	void SendData(const std::string& uniform, GLfloat floatData) const;
//	void SendData(const std::string& uniform, const glm::vec2& vec2Data) const;
//	void SendData(const std::string& uniform, const glm::vec3& vec3Data) const;
//	void SendData(const std::string& uniform, const glm::vec4& vec4Data) const;
//
//	void SendData(const std::string& uniform,
//		const glm::mat3& matrix3x3, bool transposed = false) const;
//
//	void SendData(const std::string& uniform,
//		const glm::mat4& matrix4x4, bool transposed = false) const;
//
//	void Use();
//	void Destroy();
//
//
//
//private:
//
//	bool LinkProgram();
//	bool CompileShaders(const std::string& filename);
//
//
//	static std::string s_shaderRootFolder;
//
//	static GLint s_vertexShaderID;
//	static GLint s_fragmentShaderID;
//
//	GLuint m_shaderProgramID;
//
//	// Container storing the ID and attributes of shader elements
//	std::map<std::string, GLuint> m_uniforms;
//	std::map<std::string, GLuint> m_attributes;
//
//	// TODO start using multiple shader progreams
//	std::map <std::string, unsigned int> m_shaderPrograms;
//};
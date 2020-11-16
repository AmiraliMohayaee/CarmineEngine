#pragma once

#include "glad.h"
#include <glm.hpp>
#include <string>
#include <map>


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

	const GLuint GetShaderProgramID();

	const GLuint GetAttributeID(std::string attribute);

	const GLuint BindAttribute(std::string attribute);
	const GLuint BingUniform(std::string uniform);

	void DetachShaders();
	void DestroyShaders();
	void DestroyProgram();


private:
	Shader();
	Shader(const Shader&);
	Shader& operator=(const Shader&);

private:

	GLuint m_shaderProgramID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;

	// Container storing the ID and attributes of shader elements
	std::map<char, GLuint> m_shaderValues;
};
#pragma once

#include "glad.h"
#include <string>


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

private:
	Shader();
	Shader(const Shader&);
	Shader& operator=(const Shader&);

private:

	GLuint m_shaderProgramID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;

};


#include "Shader.h"
#include <fstream>
#include <Windows.h>
#include "Utility.h"


std::string Shader::s_shaderRootFolder = "Assets/Shaders/";

GLint Shader::s_vertexShaderID = 0;
GLint Shader::s_fragmentShaderID = 0;

//======================================================================================================
Shader::Shader()
{
	m_shaderProgramID = 0;
}
//======================================================================================================
//TODO - Consider moving these as they could cause a crash!
Shader::~Shader()
{
	glDeleteShader(s_vertexShaderID);
	glDeleteShader(s_fragmentShaderID);
}
//======================================================================================================
GLuint Shader::GetUniformID(const std::string& uniform) const
{
	auto it = m_uniforms.find(uniform);
	assert(it != m_uniforms.end());
	return it->second;
}
//======================================================================================================
GLuint Shader::GetAttributeID(const std::string& attribute) const
{
	auto it = m_attributes.find(attribute);
	assert(it != m_attributes.end());
	return it->second;
}
//======================================================================================================
bool Shader::Create(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename)
{
	m_shaderProgramID = glCreateProgram();

	//If the shader program ID is 0 it means an error occurred. Possible causes are 
	//that GLAD has not been set up properly yet or your graphics card is very old
	if (m_shaderProgramID == 0)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error creating shader program. Possible causes could be a "
			"very old graphics card that does not support modern OpenGL.",
			Utility::Severity::Failure);
		return false;
	}

	if (s_vertexShaderID == 0)
	{
		s_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

		if (s_vertexShaderID == 0)
		{
			Utility::Log(Utility::Destination::WindowsMessageBox,
				"Error creating vertex shader object. Possible causes could be a "
				"very old graphics card that does not support modern OpenGL.",
				Utility::Severity::Failure);
			return false;
		}
	}

	if (s_fragmentShaderID == 0)
	{
		s_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		if (s_fragmentShaderID == 0)
		{
			Utility::Log(Utility::Destination::WindowsMessageBox,
				"Error creating fragment shader object. Possible causes could be a "
				"very old graphics card that does not support modern OpenGL.",
				Utility::Severity::Failure);
			return false;
		}
	}

	if (!CompileShaders(vertexShaderFilename))
	{
		return false;
	}

	if (!CompileShaders(fragmentShaderFilename))
	{
		return false;
	}

	if (!LinkProgram())
	{
		return false;
	}

	return true;
}
//======================================================================================================
void Shader::BindUniform(const std::string& uniform)
{
	auto it = m_uniforms.find(uniform);

	if (it == m_uniforms.end())
	{
		//Unbound shader uniforms are either 
		//not present in the shader or unused
		auto ID = glGetUniformLocation(m_shaderProgramID, uniform.c_str());
		assert(ID != -1);
		m_uniforms[uniform] = ID;
	}
}
//======================================================================================================
void Shader::BindAttribute(const std::string& attribute)
{
	auto it = m_attributes.find(attribute);

	if (it == m_attributes.end())
	{
		//Unbound shader attributes are either 
		//not present in the shader or unused
		auto ID = glGetAttribLocation(m_shaderProgramID, attribute.c_str());
		assert(ID != -1);
		m_attributes[attribute] = ID;
	}
}
//======================================================================================================
void Shader::SendData(const std::string& uniform, GLint intData) const
{
	glUniform1i(GetUniformID(uniform), intData);
}
//======================================================================================================
void Shader::SendData(const std::string& uniform, GLuint uintData) const
{
	glUniform1ui(GetUniformID(uniform), uintData);
}
//======================================================================================================
void Shader::SendData(const std::string& uniform, GLfloat floatData) const
{
	glUniform1f(GetUniformID(uniform), floatData);
}
//======================================================================================================
void Shader::SendData(const std::string& uniform, const glm::vec2& vec2Data) const
{
	glUniform2fv(GetUniformID(uniform), 1, &vec2Data.x);
}
//======================================================================================================
void Shader::SendData(const std::string& uniform, const glm::vec3& vec3Data) const
{
	glUniform3fv(GetUniformID(uniform), 1, &vec3Data.x);
}
//======================================================================================================
void Shader::SendData(const std::string& uniform, const glm::vec4& vec4Data) const
{
	glUniform4fv(GetUniformID(uniform), 1, &vec4Data.x);
}
//======================================================================================================
void Shader::SendData(const std::string& uniform,
	const glm::mat3& matrix3x3, bool transposed) const
{
	glUniformMatrix3fv(GetUniformID(uniform), 1, transposed, &matrix3x3[0][0]);
}
//======================================================================================================
void Shader::SendData(const std::string& uniform,
	const glm::mat4& matrix4x4, bool transposed) const
{
	glUniformMatrix4fv(GetUniformID(uniform), 1, transposed, &matrix4x4[0][0]);
}
//======================================================================================================
void Shader::Use()
{
	glUseProgram(m_shaderProgramID);
}
//======================================================================================================
void Shader::Destroy()
{
	glDeleteProgram(m_shaderProgramID);
}
//======================================================================================================
bool Shader::LinkProgram()
{
	glAttachShader(m_shaderProgramID, s_vertexShaderID);
	glAttachShader(m_shaderProgramID, s_fragmentShaderID);
	glLinkProgram(m_shaderProgramID);
	glDetachShader(m_shaderProgramID, s_vertexShaderID);
	glDetachShader(m_shaderProgramID, s_fragmentShaderID);

	GLint result = 0;
	glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &result);

	if (result == GL_FALSE)
	{
		GLchar error[1000];
		GLsizei bufferSize = 1000;
		glGetProgramInfoLog(m_shaderProgramID, bufferSize, &bufferSize, error);
		Utility::Log(Utility::Destination::WindowsMessageBox, error, Utility::Severity::Failure);
		return false;
	}

	return true;
}
//======================================================================================================
bool Shader::CompileShaders(const std::string& filename)
{
	std::string sourceCode;

	if (!Utility::LoadShaderFile(filename, sourceCode))
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error loading shader file \"" + (filename)+"\"."
			"Possible causes could be a corrupt or missing file. It could also be "
			"that the filename and/or path are incorrectly spelt.", Utility::Severity::Failure);
		return false;
	}

	std::vector<std::string> subStrings;
	Utility::ParseString(const_cast<std::string&>(filename), subStrings, '.');
	auto shaderID = (subStrings[1] == "vert") ? s_vertexShaderID : s_fragmentShaderID;

	const GLchar* finalCode = reinterpret_cast<const GLchar*>(sourceCode.c_str());
	glShaderSource(shaderID, 1, &finalCode, nullptr);
	glCompileShader(shaderID);

	GLint compileResult;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileResult);

	if (compileResult == GL_FALSE)
	{
		GLchar error[1000];
		GLsizei bufferSize = 1000;
		glGetShaderInfoLog(shaderID, bufferSize, &bufferSize, error);
		Utility::Log(Utility::Destination::WindowsMessageBox, error, Utility::Severity::Failure);
		return false;
	}

	return true;
}
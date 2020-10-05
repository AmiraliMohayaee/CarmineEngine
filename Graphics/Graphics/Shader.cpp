#include "Shader.h"
#include <fstream>
#include "Debug.h"


Shader* Shader::Instance()
{
	static Shader* shaderInstance = new Shader();

	return shaderInstance;
}


bool Shader::CreateProgram()
{
	m_shaderProgramID = glCreateProgram();

	if (!m_shaderProgramID)
	{
		// Shader Program Failed
		Debug::Log("Failed to create shader program.");
		// Add a system pause
		return false;
	}

	return true;
}

bool Shader::CreateShaders()
{
	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (!m_vertexShaderID)
	{
		// Vertex Shader Failed
		// Add a system pause
		return false;
	}

	if (!m_fragmentShaderID)
	{
		// Fragment Shader Failed
		// Add a system pause
		return false;
	}


	return true;
}

bool Shader::CompileShaders()
{
	std::string line;
	std::string source;
	std::fstream file("Assets/Shaders/main.vert");

	if (!file)
	{
		// something went wrong
		// add a system pause
		return false;
	}

	while (file.eof())
	{
		std::getline(file, line);
		source += line + '\n';
	}

	file.close();

	// Converting the file string read from file
	// to simple c-string
	const GLchar* glSource = static_cast<const GLchar*>(source.c_str());

	// bing the source to a vertex shader object
	glShaderSource(m_vertexShaderID, 1, &glSource, nullptr);

	// compile vertex shader code
	glCompileShader(m_vertexShaderID);


	///////////////////////////////////////////
	//	Error catching/trapping code
	///////////////////////////////////////////

	// For storing the error code
	GLint compileResult = 0;

	glGetShaderiv(m_vertexShaderID, GL_COMPILE_STATUS, &compileResult);

	if (compileResult == GL_TRUE)
	{
		// output a message that the shader compilation was successful
	}
	else
	{
		GLchar errorMessage[1000];
		GLsizei bufferSize = 1000;

		glGetShaderInfoLog(m_vertexShaderID, bufferSize, &bufferSize, errorMessage);

		// cout the error message
	}

	///////////////////////////////////////////



	return true;
}

bool Shader::CompileShader(std::string filename)
{
	std::string line;
	std::string source;
	std::fstream file(filename);

	if (!file)
	{
		Debug::Log("Failed to read file");
	}



	return true;
}

void Shader::AttachShaders()
{
	glAttachShader(m_shaderProgramID, m_vertexShaderID);
	glAttachShader(m_shaderProgramID, m_fragmentShaderID);
}

bool Shader::LinkProgram()
{
	// link shader program and enable it for use
	glLinkProgram(m_shaderProgramID);
	glUseProgram(m_shaderProgramID);

	// For storing the error code
	GLint linkResult = 0;

	// checking its compilation status
	glGetProgramiv(m_shaderProgramID, GL_COMPILE_STATUS, &linkResult);

	if (linkResult == GL_TRUE)
	{
		// output a message that the shader compilation was successful
	}
	else
	{
		GLchar errorMessage[1000];
		GLsizei bufferSize = 1000;

		glGetProgramInfoLog(m_shaderProgramID, bufferSize, &bufferSize, errorMessage);

		// cout the error message
	}

	///////////////////////////////////////////


	return true;
}

void Shader::DetachShaders()
{
	glDetachShader(m_shaderProgramID, m_vertexShaderID);
	glDetachShader(m_shaderProgramID, m_fragmentShaderID);
}

void Shader::DestroyShaders()
{
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
}

void Shader::DestroyProgram()
{
	glDeleteProgram(m_shaderProgramID);
}

Shader::Shader()
{
	m_shaderProgramID = 0;
	m_vertexShaderID = 0;
	m_fragmentShaderID = 0;
}

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
		Debug::Log("Failed to create the Vertex Shader.");
		// Add a system pause
		return false;
	}

	if (!m_fragmentShaderID)
	{
		Debug::Log("Failed to create the Fragment Shader.");
		// Add a system pause
		return false;
	}

	return true;
}

bool Shader::CompileShaders()
{
	//=====================================================
	//	Loading and Compiling Fragment Shader Details
	//=====================================================

	std::string line;
	std::string source;
	std::fstream file("Assets/Shaders/main.vert");

	if (!file)
	{
		Debug::Log("Failed to open the vertex shader file.");
		// add a system pause
		return false;
	}

	while (!file.eof())
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
		Debug::Log("Vertex Shader compilation successful.");
	}
	else
	{
		GLchar errorMessage[1000];
		GLsizei bufferSize = 1000;

		glGetShaderInfoLog(m_vertexShaderID, bufferSize, &bufferSize, errorMessage);

		Debug::Log(errorMessage);
	}

	//=====================================================
	//	Loading and Compiling Fragment Shader Details
	//=====================================================

	std::string line2;
	std::string source2;
	std::fstream file2("Assets/Shaders/main.frag");

	if (!file2)
	{
		Debug::Log("Failed to open the fragment shader file.");
		// add a system pause
		return false;
	}

	while (!file2.eof())
	{
		std::getline(file2, line2);
		source2 += line2 + '\n';
	}

	file2.close();

	// Converting the file string read from file
	// to simple c-string
	const GLchar* glSource2 = static_cast<const GLchar*>(source2.c_str());

	// bing the source to a vertex shader object
	glShaderSource(m_fragmentShaderID, 1, &glSource2, nullptr);

	// compile vertex shader code
	glCompileShader(m_fragmentShaderID);


	///////////////////////////////////////////
	//	Error catching/trapping code
	///////////////////////////////////////////

	// For storing the error code
	GLint compileResult2 = 0;

	glGetShaderiv(m_fragmentShaderID, GL_COMPILE_STATUS, &compileResult2);

	if (compileResult2 == GL_TRUE)
	{
		Debug::Log("Fragment shader compilation successful.");
	}
	else
	{
		GLchar errorMessage[1000];
		GLsizei bufferSize = 1000;

		glGetShaderInfoLog(m_fragmentShaderID, bufferSize, &bufferSize, errorMessage);

		Debug::Log(errorMessage);
	}


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

	// Check for file format
	if (filename.find("."))
	{
		std::string format;

		format = filename.substr(filename.find("."), 4);

		if (format == "vert")
		{
			// make vertex shader
		}
		else if (format == "frag")
		{
			// make fragment shader
		}
	}

	// Add the newly found shader type to the map container of shaders 


	while (!file.eof())
	{
		std::getline(file, line);
		source += line + '\n';
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
	//=====================================================================================
	// link shader program and enable it for use
	glLinkProgram(m_shaderProgramID);
	glUseProgram(m_shaderProgramID);

	// For storing the error code
	GLint linkResult = 0;

	// checking its compilation status
	glGetProgramiv(m_shaderProgramID, GL_COMPILE_STATUS, &linkResult);

	if (linkResult == GL_TRUE)
	{
		Debug::Log("Shader Program linked successfully");
	}
	else
	{
		GLchar errorMessage[1000];
		GLsizei bufferSize = 1000;

		glGetProgramInfoLog(m_shaderProgramID, bufferSize, &bufferSize, errorMessage);

		Debug::Log(errorMessage);
	}
	//=====================================================================================


	return true;
}

const GLuint Shader::GetShaderProgramID()
{
	return m_shaderProgramID;
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

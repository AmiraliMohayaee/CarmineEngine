#include "Shader.h"
#include <fstream>
#include "Debug.h"
#include <Windows.h>


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
		system("pause");
		return false;
	}

	if (!m_fragmentShaderID)
	{
		Debug::Log("Failed to create the Fragment Shader.");
		system("pause");
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
	glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &linkResult);

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

//===========================================
//	Looks up the attribute container and
//	returns the appropriate element
//===========================================
const GLuint Shader::GetAttributeID(std::string attribute)
{
	// Look up map for the appropriate element
	for (auto iterator = m_shaderAttributes.begin();
		iterator != m_shaderAttributes.end();
		iterator++)
	{
		if (iterator->first == attribute)
		{
			if (iterator->second == -1)
			{
				Debug::Log("Serach for shader attribute returned invalid: ", attribute);
				return -1;
			}

			Debug::Log("Following shader attribute ruturned a valid ID", attribute, iterator->second);

			return iterator->second;
		}
	}

	// Returning negative 1 to indicate that the element could
	// not have been found and 
	return -1;
}

const GLuint Shader::GetUniformID(std::string variable)
{
	for (auto iterator = m_shaderUniforms.begin();
		iterator != m_shaderUniforms.end();
		iterator++)
	{
		if (iterator->first == variable)
		{
			if (iterator->second == -1)
			{
				Debug::Log("Serach for shader uniform returned invalid: ", variable);

				return -1;
			}

			Debug::Log("Following shader uniform ruturned a valid ID", variable, iterator->second);

			return iterator->second;
		}
	}

	return -1;
}

void Shader::BindAttribute(std::string attribute)
{
	// Loop map and check if variable/uniform already exists
	// If it exists, return that existing ID
	// if not
	// Add variable to map container
	for (auto it = m_shaderAttributes.begin(); it != m_shaderAttributes.end();
		it++)
	{
		if (it->first == attribute)
		{
			// If the value already exists, then
			// we do nothing
			Debug::Log("Following Shader Attribute already exists: ", attribute);

			return;
		}
	}

	int ID = glGetAttribLocation(m_shaderProgramID, attribute.c_str());

	if (ID == -1)
	{
		Debug::Log("Attribute value inserted returning a negative value:", attribute);
	}
	
	m_shaderAttributes[attribute] = ID;
}

void Shader::BindUniform(std::string uniform)
{
	// Loop map and check if variable/uniform already exists
	// If it exists, return that existing ID
	// if not
	// Add variable to map container
	for (auto it = m_shaderUniforms.begin(); it != m_shaderUniforms.end();
		it++)
	{
		if (it->first == uniform)
		{
			// If the value already exists, we exit
			return;
		}
	}

	int ID = glGetUniformLocation(m_shaderProgramID, uniform.c_str());

	if (ID == -1)
	{
		Debug::Log("Uniform value inserted returning a negative value:", uniform);
	}


	//m_shaderUniforms.insert({ uniform, ID });

	m_shaderUniforms[uniform] = ID;
}

void Shader::SendUniformData(const std::string& uniform, GLint intData)
{
	GLint UniformLocation = Shader::Instance()->GetUniformID(uniform);

	glUniform1i(UniformLocation, intData);
}

void Shader::SendUniformData(const std::string& uniform, GLuint uintData)
{
	GLint UniformLocation = Shader::Instance()->GetUniformID(uniform);

	glUniform1ui(UniformLocation, uintData);
}

void Shader::SendUniformData(const std::string& uniform, GLfloat floatData)
{
	GLint UniformLocation = Shader::Instance()->GetUniformID(uniform);

	glUniform1f(UniformLocation, floatData);
}

void Shader::SendUniformData(const std::string& uniform, GLfloat x, GLfloat y)
{
	GLint UniformLocation = Shader::Instance()->GetUniformID(uniform);

	glUniform2f(UniformLocation, x, y);
}

void Shader::SendUniformData(const std::string& uniform, GLfloat x, GLfloat y, GLfloat z)
{
	GLint UniformLocation = Shader::Instance()->GetUniformID(uniform);

	glUniform3f(UniformLocation, x, y, z);
}

void Shader::SendUniformData(const std::string& uniform, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	GLint UniformLocation = Shader::Instance()->GetUniformID(uniform);

	glUniform4f(UniformLocation, x, y, z, w);
}

void Shader::SendUniformData(const std::string& uniform, glm::mat4& mat)
{
	GLint UniformLocation = Shader::Instance()->GetUniformID(uniform);

	glUniformMatrix4fv(UniformLocation, 1, GL_FALSE, &mat[0][0]);
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

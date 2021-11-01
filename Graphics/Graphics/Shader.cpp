#include "Shader.h"
#include <fstream>
#include <iostream>
#include <assert.h>
#include "Utility.h"


std::string Shader::s_shaderRootFolder = "Assets/Shaders/";

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
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Failed to create the Vertex Shader.",
			Utility::Severity::Failure);

		return false;
	}

	if (!m_fragmentShaderID)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Failed to create a fragment shader.",
			Utility::Severity::Failure);
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
	std::fstream file(s_shaderRootFolder + "main.vert");

	if (!file)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Failed to open the vertex shader file.",
			Utility::Severity::Failure);
		
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
		std::cout << "Vertex Shader created successfully." << std::endl;
	}
	else
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Vertex Shader compilation failed. Refer to console log for error.",
			Utility::Severity::Failure);
		
		GLchar errorMessage[1000];
		GLsizei bufferSize = 1000;

		glGetShaderInfoLog(m_vertexShaderID, bufferSize, &bufferSize, errorMessage);

		std::cout << errorMessage << std::endl;
	}

	//=====================================================
	//	Loading and Compiling Fragment Shader Details
	//=====================================================

	std::string line2;
	std::string source2;
	std::fstream file2(s_shaderRootFolder + "main.frag");

	if (!file2)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Failed to open the fragment shader file",
			Utility::Severity::Failure);
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
		std::cout << "Fragment shader compilation successful." << std::endl;
	}
	else
	{
		GLchar errorMessage[1000];
		GLsizei bufferSize = 1000;

		glGetShaderInfoLog(m_fragmentShaderID, bufferSize, &bufferSize, errorMessage);

		std::cout << errorMessage << std::endl;
	}


	return true;
}

bool Shader::CompileShader(std::string filename)
{
	//=====================================================
	//	Loading and Compiling shader according to type
	//=====================================================

	std::string line;
	std::string source;
	std::fstream file(s_shaderRootFolder + filename);


	if (!file)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Failed to read file",
			Utility::Severity::Failure);
	}

	// Check for file format
	if (filename.find("."))
	{
		std::string format;

		format = filename.substr(filename.find("."), 5);

		while (!file.eof())
		{
			std::getline(file, line);
			source += line + '\n';
		}

		// Closing file after fully copying its contents
		file.close();

		if (format == ".vert")
		{
			// make vertex shader
			const GLchar* glSource = static_cast<const GLchar*>(source.c_str());

			// bing the source to a vertex shader object
			glShaderSource(m_vertexShaderID, 1, &glSource, nullptr);

			// compile vertex shader code
			glCompileShader(m_vertexShaderID);

			GLint compileResult = 0;

			glGetShaderiv(m_vertexShaderID, GL_COMPILE_STATUS, &compileResult);

			if (compileResult == GL_TRUE)
			{
				std::cout << "Vertex Compilation successful." << std::endl;
			}
			else
			{
				Utility::Log(Utility::Destination::WindowsMessageBox,
					"Vertex Shader compilation failed. Refer to console log for error.",
					Utility::Severity::Failure);

				GLchar errorMessage[1000];
				GLsizei bufferSize = 1000;

				glGetShaderInfoLog(m_vertexShaderID, bufferSize, &bufferSize, errorMessage);

				std::cout << errorMessage << std::endl;
			}
		}

		else if (format == ".frag")
		{
			// make fragment shader

			const GLchar* glSource = static_cast<const GLchar*>(source.c_str());

			// bing the source to a vertex shader object
			glShaderSource(m_fragmentShaderID, 1, &glSource, nullptr);

			// compile vertex shader code
			glCompileShader(m_fragmentShaderID);

			GLint compileResult = 0;

			glGetShaderiv(m_fragmentShaderID, GL_COMPILE_STATUS, &compileResult);

			if (compileResult == GL_TRUE)
			{
				std::cout << "Fragment Shader compilation successful." << std::endl;
			}
			else
			{
				Utility::Log(Utility::Destination::WindowsMessageBox,
					"Fragment Shader compilation failed. Refer to console log for error.",
					Utility::Severity::Failure);

				GLchar errorMessage[1000];
				GLsizei bufferSize = 1000;

				glGetShaderInfoLog(m_fragmentShaderID, bufferSize, &bufferSize, errorMessage);

				std::cout << errorMessage << std::endl;
			}
		}
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
		std::cout << "Shader Program linked successfully" << std::endl;
	}
	else
	{
		GLchar errorMessage[1000];
		GLsizei bufferSize = 1000;

		glGetProgramInfoLog(m_shaderProgramID, bufferSize, &bufferSize, errorMessage);

		std::cout << errorMessage << std::endl;
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
				Utility::Log(Utility::Destination::WindowsMessageBox,
					"Serach for shader attribute returned invalid: " + attribute,
					Utility::Severity::Failure);
				return -1;
			}

			//Debug::Log("Following shader attribute ruturned a valid ID", attribute, iterator->second);

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
				Utility::Log(Utility::Destination::WindowsMessageBox,
					"Serach for shader uniform returned invalid: " + variable,
					Utility::Severity::Failure);

				return -1;
			}

			//Debug::Log("Following shader uniform ruturned a valid ID", variable, iterator->second);

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
			Utility::Log(Utility::Destination::WindowsMessageBox,
				"Following Shader Attribute already exists: " + attribute,
				Utility::Severity::Warning);

			return;
		}
	}

	int ID = glGetAttribLocation(m_shaderProgramID, attribute.c_str());

	if (ID == -1)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Attribute value inserted returning a negative value:" + attribute,
			Utility::Severity::Failure);
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
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Uniform value inserted returning a negative value:" + uniform,
			Utility::Severity::Failure);
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

void Shader::SendUniformData(const std::string& uniform, const glm::mat4& mat)
{
	GLint UniformLocation = Shader::Instance()->GetUniformID(uniform);

	glUniformMatrix4fv(UniformLocation, 1, GL_FALSE, &mat[0][0]);
}

void Shader::EnableVertexAttributeArray(GLuint attribute)
{
	glEnableVertexAttribArray(attribute);
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



// New implementation to be tested after getting the singletonised version 
// working
//GLint Shader::s_vertexShaderID = 0;
//GLint Shader::s_fragmentShaderID = 0;
//
//std::string Shader::s_shaderRootFolder = "Assets/Shaders/";
//
////======================================================================================================
//Shader::Shader()
//{
//	m_shaderProgramID = 0;
//}
////======================================================================================================
////TODO - Consider moving these as they could cause a crash!
//Shader::~Shader()
//{
//	glDeleteShader(s_vertexShaderID);
//	glDeleteShader(s_fragmentShaderID);
//}
////======================================================================================================
//GLuint Shader::GetUniformID(const std::string& uniform) const
//{
//	auto it = m_uniforms.find(uniform);
//	assert(it != m_uniforms.end());
//	return it->second;
//}
////======================================================================================================
//GLuint Shader::GetAttributeID(const std::string& attribute) const
//{
//	auto it = m_attributes.find(attribute);
//	assert(it != m_attributes.end());
//	return it->second;
//}
////======================================================================================================
//bool Shader::Create(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename)
//{
//	m_shaderProgramID = glCreateProgram();
//
//	//If the shader program ID is 0 it means an error occurred. Possible causes are 
//	//that GLAD has not been set up properly yet or your graphics card is very old
//	if (m_shaderProgramID == 0)
//	{
//		Utility::Log(Utility::Destination::WindowsMessageBox,
//			"Error creating shader program. Possible causes could be a "
//			"very old graphics card that does not support modern OpenGL.",
//			Utility::Severity::Failure);
//		return false;
//	}
//
//	if (s_vertexShaderID == 0)
//	{
//		s_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
//
//		if (s_vertexShaderID == 0)
//		{
//			Utility::Log(Utility::Destination::WindowsMessageBox,
//				"Error creating vertex shader object. Possible causes could be a "
//				"very old graphics card that does not support modern OpenGL.",
//				Utility::Severity::Failure);
//			return false;
//		}
//	}
//
//	if (s_fragmentShaderID == 0)
//	{
//		s_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
//
//		if (s_fragmentShaderID == 0)
//		{
//			Utility::Log(Utility::Destination::WindowsMessageBox,
//				"Error creating fragment shader object. Possible causes could be a "
//				"very old graphics card that does not support modern OpenGL.",
//				Utility::Severity::Failure);
//			return false;
//		}
//	}
//
//	if (!CompileShaders(vertexShaderFilename))
//	{
//		return false;
//	}
//
//	if (!CompileShaders(fragmentShaderFilename))
//	{
//		return false;
//	}
//
//	if (!LinkProgram())
//	{
//		return false;
//	}
//
//	return true;
//}
////======================================================================================================
//void Shader::BindUniform(const std::string& uniform)
//{
//	auto it = m_uniforms.find(uniform);
//
//	if (it == m_uniforms.end())
//	{
//		//Unbound shader uniforms are either 
//		//not present in the shader or unused
//		auto ID = glGetUniformLocation(m_shaderProgramID, uniform.c_str());
//		assert(ID != -1);
//		m_uniforms[uniform] = ID;
//	}
//}
////======================================================================================================
//void Shader::BindAttribute(const std::string& attribute)
//{
//	auto it = m_attributes.find(attribute);
//
//	if (it == m_attributes.end())
//	{
//		//Unbound shader attributes are either 
//		//not present in the shader or unused
//		auto ID = glGetAttribLocation(m_shaderProgramID, attribute.c_str());
//		assert(ID != -1);
//		m_attributes[attribute] = ID;
//	}
//}
////======================================================================================================
//void Shader::SendData(const std::string& uniform, GLint intData) const
//{
//	glUniform1i(GetUniformID(uniform), intData);
//}
////======================================================================================================
//void Shader::SendData(const std::string& uniform, GLuint uintData) const
//{
//	glUniform1ui(GetUniformID(uniform), uintData);
//}
////======================================================================================================
//void Shader::SendData(const std::string& uniform, GLfloat floatData) const
//{
//	glUniform1f(GetUniformID(uniform), floatData);
//}
////======================================================================================================
//void Shader::SendData(const std::string& uniform, const glm::vec2& vec2Data) const
//{
//	glUniform2fv(GetUniformID(uniform), 1, &vec2Data.x);
//}
////======================================================================================================
//void Shader::SendData(const std::string& uniform, const glm::vec3& vec3Data) const
//{
//	glUniform3fv(GetUniformID(uniform), 1, &vec3Data.x);
//}
////======================================================================================================
//void Shader::SendData(const std::string& uniform, const glm::vec4& vec4Data) const
//{
//	glUniform4fv(GetUniformID(uniform), 1, &vec4Data.x);
//}
////======================================================================================================
//void Shader::SendData(const std::string& uniform,
//	const glm::mat3& matrix3x3, bool transposed) const
//{
//	glUniformMatrix3fv(GetUniformID(uniform), 1, transposed, &matrix3x3[0][0]);
//}
////======================================================================================================
//void Shader::SendData(const std::string& uniform,
//	const glm::mat4& matrix4x4, bool transposed) const
//{
//	glUniformMatrix4fv(GetUniformID(uniform), 1, transposed, &matrix4x4[0][0]);
//}
////======================================================================================================
//void Shader::Use()
//{
//	glUseProgram(m_shaderProgramID);
//}
////======================================================================================================
//void Shader::Destroy()
//{
//	glDeleteProgram(m_shaderProgramID);
//}
////======================================================================================================
//bool Shader::LinkProgram()
//{
//	glAttachShader(m_shaderProgramID, s_vertexShaderID);
//	glAttachShader(m_shaderProgramID, s_fragmentShaderID);
//	glLinkProgram(m_shaderProgramID);
//	glDetachShader(m_shaderProgramID, s_vertexShaderID);
//	glDetachShader(m_shaderProgramID, s_fragmentShaderID);
//
//	GLint result = 0;
//	glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &result);
//
//	if (result == GL_FALSE)
//	{
//		GLchar error[1000];
//		GLsizei bufferSize = 1000;
//		glGetProgramInfoLog(m_shaderProgramID, bufferSize, &bufferSize, error);
//		Utility::Log(Utility::Destination::WindowsMessageBox, error, Utility::Severity::Failure);
//		return false;
//	}
//
//	return true;
//}
////======================================================================================================
//bool Shader::CompileShaders(const std::string& filename)
//{
//	std::string sourceCode;
//
//	if (!Utility::LoadShaderFile(filename, sourceCode))
//	{
//		Utility::Log(Utility::Destination::WindowsMessageBox,
//			"Error loading shader file \"" + (filename)+"\"."
//			"Possible causes could be a corrupt or missing file. It could also be "
//			"that the filename and/or path are incorrectly spelt.", Utility::Severity::Failure);
//		return false;
//	}
//
//	std::vector<std::string> subStrings;
//	Utility::ParseString(const_cast<std::string&>(filename), subStrings, '.');
//	auto shaderID = (subStrings[1] == "vert") ? s_vertexShaderID : s_fragmentShaderID;
//
//	const GLchar* finalCode = reinterpret_cast<const GLchar*>(sourceCode.c_str());
//	glShaderSource(shaderID, 1, &finalCode, nullptr);
//	glCompileShader(shaderID);
//
//	GLint compileResult;
//	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileResult);
//
//	if (compileResult == GL_FALSE)
//	{
//		GLchar error[1000];
//		GLsizei bufferSize = 1000;
//		glGetShaderInfoLog(shaderID, bufferSize, &bufferSize, error);
//		Utility::Log(Utility::Destination::WindowsMessageBox, error, Utility::Severity::Failure);
//		return false;
//	}
//
//	return true;
//}
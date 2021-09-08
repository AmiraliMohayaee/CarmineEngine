#include <fstream>
#include <string>
#include "Utility.h"

HWND Utility::s_windowHandle = nullptr;
//======================================================================================================
void Utility::CheckGLError()
{
	//This will return the first error that 
	//occured since this function was last called
	GLenum errorCode = glGetError();

	switch (errorCode)
	{

	case GL_NO_ERROR:
	{
		Log(Destination::LogFile, "There are no errors.", Severity::Default);
		Log(Destination::OutputWindow, "There are no errors.", Severity::Default);
		break;
	}

	case GL_INVALID_ENUM:
	{
		Log(Destination::LogFile, "Invalid enumeration type passed.", Severity::Failure);
		Log(Destination::OutputWindow, "Invalid enumeration type passed.", Severity::Failure);
		break;
	}

	case GL_INVALID_VALUE:
	{
		Log(Destination::LogFile, "Numeric value outside of accepted range.", Severity::Failure);
		Log(Destination::OutputWindow, "Numeric value outside of accepted range.", Severity::Failure);
		break;
	}

	case GL_INVALID_OPERATION:
	{
		Log(Destination::LogFile, "Invalid operation.", Severity::Failure);
		Log(Destination::OutputWindow, "Invalid operation.", Severity::Failure);
		break;
	}

	case GL_INVALID_FRAMEBUFFER_OPERATION:
	{
		Log(Destination::LogFile, "Framebuffer object incomplete.", Severity::Failure);
		Log(Destination::OutputWindow, "Framebuffer object incomplete.", Severity::Failure);
		break;
	}

	case GL_STACK_OVERFLOW:
	{
		Log(Destination::LogFile, "Stack overflow.", Severity::Failure);
		Log(Destination::OutputWindow, "Stack overflow.", Severity::Failure);
		break;
	}

	case GL_STACK_UNDERFLOW:
	{
		Log(Destination::LogFile, "Stack underflow.", Severity::Failure);
		Log(Destination::OutputWindow, "Stack underflow.", Severity::Failure);
		break;
	}

	case GL_OUT_OF_MEMORY:
	{
		Log(Destination::LogFile, "Out of memory.", Severity::Failure);
		Log(Destination::OutputWindow, "Out of memory.", Severity::Failure);
		break;
	}

	}
}
//======================================================================================================
void Utility::DisplayProfile()
{
	const GLubyte* profile = nullptr;

	profile = reinterpret_cast<const GLubyte*>(glGetString(GL_VENDOR));
	Utility::Log(Destination::LogFile, "Graphics card vendor: " + (*profile));

	profile = reinterpret_cast<const GLubyte*>(glGetString(GL_RENDERER));
	Utility::Log(Destination::LogFile, "Graphics card model: " + (*profile));

	profile = reinterpret_cast<const GLubyte*>(glGetString(GL_VERSION));
	Utility::Log(Destination::LogFile, "OpenGL version: " + (*profile));

	profile = reinterpret_cast<const GLubyte*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	Utility::Log(Destination::LogFile, "GLSL version: " + (*profile));
}
//======================================================================================================
void Utility::DisplayExtensions()
{
	GLint totalExtensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &totalExtensions);

	for (GLint i = 0; i < totalExtensions; i++)
	{
		const GLubyte* extension = reinterpret_cast<const GLubyte*>(glGetStringi(GL_EXTENSIONS, i));
		//Utility::Log(Destination::LogFile, std::to_string(i + 1) + (*extension));
	}
}
//======================================================================================================
void Utility::SetWindowHandle(HWND windowHandle)
{
	s_windowHandle = windowHandle;
}
//======================================================================================================
void Utility::RemoveCharacter(std::string& str, char character)
{
	auto it = std::find(str.begin(), str.end(), character);

	if (it != str.end())
	{
		do
		{
			str.erase(it);
			it = std::find(str.begin(), str.end(), character);
		} while (it != str.end());
	}
}
//======================================================================================================
void Utility::ParseString(std::string& str, std::vector<std::string>& subStrings, char token)
{
	size_t start = 0;
	size_t end = 0;

	assert(!str.empty());

	while (end != std::string::npos)
	{
		end = str.find(token, start);
		if ((end - start) > 0)
		{
			subStrings.push_back(str.substr(start, end - start));
		}
		start = end + 1;
	}
}
//======================================================================================================
bool Utility::LoadConfigFile(const std::string& filename,
	std::map<std::string, std::string>& dataMap)
{
	std::fstream file(filename, std::ios_base::in);

	if (!file.is_open())
	{
		return false;
	}

	std::string line;

	while (!file.eof())
	{
		std::getline(file, line);
		std::vector<std::string> subStrings;
		ParseString(line, subStrings, '=');

		if (!subStrings.empty())
		{
			dataMap[subStrings[0]] = subStrings[1];
		}
	}

	file.close();
	return true;
}
//======================================================================================================
bool Utility::LoadShaderFile(const std::string& filename, std::string& sourceCode)
{
	std::fstream file(filename, std::ios_base::in);

	if (!file.is_open())
	{
		return false;
	}

	std::string line;

	while (!file.eof())
	{
		getline(file, line);
		sourceCode += line + "\n";
	}

	file.close();
	return true;
}
//======================================================================================================
void Utility::Log(Destination destination, const glm::vec2& value, const std::string& label)
{
	Log(destination, value.x, value.y, 0.0f, label);
}
//======================================================================================================
void Utility::Log(Destination destination, const glm::vec3& value, const std::string& label)
{
	Log(destination, value.x, value.y, value.z, label);
}
//======================================================================================================
void Utility::Log(Destination destination, GLfloat value, const std::string& label)
{
	if (!label.empty())
	{
		if (destination == Destination::WindowsMessageBox)
		{
			MessageBox(s_windowHandle,
				reinterpret_cast<LPCWSTR>(std::to_wstring(value).c_str()),
				reinterpret_cast<LPCWSTR>(std::wstring(label.begin(), label.end()).c_str()),
				MB_ICONINFORMATION | MB_OK);
		}

		else if (destination == Destination::OutputWindow)
		{
			std::string message = "[" + label + "] " + std::to_string(value) + "\n";
			OutputDebugString(reinterpret_cast<LPCWSTR>
				(std::wstring(message.begin(), message.end()).c_str()));
		}

		else if (destination == Destination::LogFile)
		{
			std::fstream file("Data/Output.log", std::ios_base::out | std::ios_base::app);
			std::string message = "[" + label + "] " + std::to_string(value) + "\n";
			file << message;
			file.close();
		}
	}
}
//======================================================================================================
void Utility::Log(Destination destination, const std::string& message, Severity severity)
{
	if (!message.empty())
	{
		if (destination == Destination::WindowsMessageBox)
		{
			MessageBox(s_windowHandle,
				reinterpret_cast<LPCWSTR>(std::wstring(message.begin(), message.end()).c_str()),
				L"Log", static_cast<GLuint>(severity) | MB_OK);
		}

		else if (destination == Destination::OutputWindow)
		{
			std::string finalMessage;

			if (severity == Severity::Failure)
			{
				finalMessage = "[FAILURE] " + message + "\n";
			}

			else if (severity == Severity::Warning)
			{
				finalMessage = "[WARNING] " + message + "\n";
			}

			else
			{
				finalMessage = message + "\n";
			}

			OutputDebugString(reinterpret_cast<LPCWSTR>
				(std::wstring(finalMessage.begin(), finalMessage.end()).c_str()));
		}

		else if (destination == Destination::LogFile)
		{
			std::string finalMessage;
			std::fstream file("Data/Output.log", std::ios_base::out | std::ios_base::app);

			if (severity == Severity::Failure)
			{
				finalMessage = "[FAILURE] " + message + "\n";
			}

			else if (severity == Severity::Warning)
			{
				finalMessage = "[WARNING] " + message + "\n";
			}

			else
			{
				finalMessage = message + "\n";
			}

			file << finalMessage;
			file.close();
		}
	}
}
//======================================================================================================
void Utility::Log(Destination destination, GLfloat x, GLfloat y, GLfloat z, const std::string& label)
{
	if (!label.empty())
	{
		if (destination == Destination::WindowsMessageBox)
		{
			std::string message = "x = " + std::to_string(x) +
				", y = " + std::to_string(y) +
				", z = " + std::to_string(z);

			MessageBox(s_windowHandle,
				reinterpret_cast<LPCWSTR>(std::wstring(message.begin(), message.end()).c_str()),
				reinterpret_cast<LPCWSTR>(std::wstring(label.begin(), label.end()).c_str()),
				MB_ICONINFORMATION | MB_OK);
		}

		else if (destination == Destination::OutputWindow)
		{
			std::string message = "[" + label + "] " + "x = " + std::to_string(x) +
				", y = " + std::to_string(y) +
				", z = " + std::to_string(z) + "\n";
			OutputDebugString(reinterpret_cast<LPCWSTR>
				(std::wstring(message.begin(), message.end()).c_str()));
		}

		else if (destination == Destination::LogFile)
		{
			std::fstream file("Data/Output.log", std::ios_base::out | std::ios_base::app);
			std::string message = "[" + label + "] " + "x = " + std::to_string(x) +
				", y = " + std::to_string(y) +
				", z = " + std::to_string(z) + "\n";
			file << message;
			file.close();
		}
	}
}

void Utility::GraphicsErrorCatch()
{
	//////////////////////////////////////////
	// Open GL Debugger Message Catching
	//////////////////////////////////////////
	/*glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);

	glDebugMessageCallback(&GLError::GetGLErrorCallback, nullptr);*/
}

void APIENTRY Utility::GetGLErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message, const void* userParam)
{

#ifdef _DEBUG
	//
	//	Log(message);
	//
	//	switch (type)
	//	{
	//	case GL_DEBUG_TYPE_ERROR:
	//		Debug::Log("ERROR");
	//		break;
	//	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
	//		Debug::Log("DEPRECATED_BEHAVIOR");
	//		break;
	//	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
	//		Debug::Log("UNDEFINED_BEHAVIOR");
	//		break;
	//	case GL_DEBUG_TYPE_PORTABILITY:
	//		Debug::Log("PORTABILITY");
	//		break;
	//	case GL_DEBUG_TYPE_PERFORMANCE:
	//		Debug::Log("PERFORMANCE");
	//		break;
	//	case GL_DEBUG_TYPE_OTHER:
	//		Debug::Log("OTHER");
	//		break;
	//	}
	//
	//
	//	Debug::Log("id: ", id);
	//
	//	switch (severity)
	//	{
	//	case GL_DEBUG_SEVERITY_LOW:
	//		Debug::Log("LOW");
	//		break;
	//	case GL_DEBUG_SEVERITY_MEDIUM:
	//		Debug::Log("MEDIUM");
	//		break;
	//	case GL_DEBUG_SEVERITY_HIGH:
	//		Debug::Log("HIGH");
	//		break;
	//	}
	//
	//	Debug::Log("severity: ", severity);
	//
	//	Debug::Log("End of OpenGL Debug Log");

#endif

}
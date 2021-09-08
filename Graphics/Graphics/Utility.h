#pragma once

#include <Windows.h>
#include <map>
#include <string>
#include <vector>
#include <glm.hpp>
#include "glad.h"



class Utility
{
public:

	enum class Severity
	{
		Failure = MB_ICONERROR,
		Warning = MB_ICONWARNING,
		Default = MB_ICONINFORMATION
	};

	enum class Destination
	{
		LogFile,
		OutputWindow,
		WindowsMessageBox
	};

	static void SetWindowHandle(HWND windowHandle);

	static void CheckGLError();
	static void DisplayProfile();
	static void DisplayExtensions();

	static void RemoveCharacter(std::string& str, char character);

	static void ParseString(std::string& str,
		std::vector<std::string>& subStrings, char token);

	static bool LoadConfigFile(const std::string& filename,
		std::map<std::string, std::string>& dataMap);

	static bool LoadShaderFile(const std::string& filename,
		std::string& sourceCode);

	static void Log(Destination destination,
		GLfloat value, const std::string& label = "");
	static void Log(Destination destination,
		const glm::vec2& value, const std::string& label = "");
	static void Log(Destination destination,
		const glm::vec3& value, const std::string& label = "");
	static void Log(Destination destination,
		const std::string& message, Severity severity = Severity::Default);
	static void Log(Destination destination,
		GLfloat x, GLfloat y, GLfloat z = 0.0f, const std::string& label = "");

	void APIENTRY GetGLErrorCallback(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam);

	void GraphicsErrorCatch();

private:

	static HWND s_windowHandle;
};


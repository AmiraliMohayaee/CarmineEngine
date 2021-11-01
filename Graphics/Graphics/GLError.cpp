#include "GLError.h"
#include "Debug.h"




void APIENTRY GLError::GetGLErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, 
	GLsizei length, const GLchar* message, const void* userParam)
{

#ifdef _DEBUG

	Debug::Log(message);

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:
		Debug::Log("ERROR");
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		Debug::Log("DEPRECATED_BEHAVIOR");
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		Debug::Log("UNDEFINED_BEHAVIOR");
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		Debug::Log("PORTABILITY");
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		Debug::Log("PERFORMANCE");
		break;
	case GL_DEBUG_TYPE_OTHER:
		Debug::Log("OTHER");
		break;
	}


	Debug::Log("id: ", id);

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_LOW:
		Debug::Log("LOW");
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		Debug::Log("MEDIUM");
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		Debug::Log("HIGH");
		break;
	}

	Debug::Log("severity: ", severity);

	Debug::Log("End of OpenGL Debug Log");

#endif

}

void GLError::GraphicsErrorCatch()
{
	//////////////////////////////////////////
	// Open GL Debugger Message Catching
	//////////////////////////////////////////
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);

	glDebugMessageCallback(&GLError::GetGLErrorCallback, nullptr);
}

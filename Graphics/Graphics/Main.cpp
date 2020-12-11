#include "Screen.h"
#include "Shader.h"
#include "Input.h"
#include "Debug.h"
#include "Cube.h"
#include "Camera.h"
#include "GLError.h"
#include <iostream>



bool isProgramRunning = true;

int main(int argc, char* args[])
{
	if (!Screen::Instance()->InitScreen())
	{
		Debug::Log("Failed to Initialize a screen. Check your settings file.");
		return 0;
	}

	if (!Shader::Instance()->CreateProgram())
	{
		Debug::Log("Shader Program return a false result. Possile wrong linking.");
		return 0;
	}

	if (!Shader::Instance()->CreateShaders())
	{
		Debug::Log("Failed to create shaders.");
		return 0;
	}

	if (!Shader::Instance()->CompileShaders())
	{
		Debug::Log("Failed to compile shaders.");
		return 0;
	}

	Shader::Instance()->AttachShaders();

	if (!Shader::Instance()->LinkProgram())
	{
		Debug::Log("Failed to link the shader program.");
		return 0;
	}

	// Posting initial print of graphics driver details
	//display the manufacturer of the graphics hardware
	std::cout << (const char*)(glGetString(GL_VENDOR)) << std::endl;
	//display the make and model of the graphics card
	std::cout << (const char*)(glGetString(GL_RENDERER)) << std::endl;
	//display the current OpenGL version and mode set
	std::cout << (const char*)(glGetString(GL_VERSION)) << std::endl;


	//============================================================================
	//	Rendering
	//============================================================================
	Shader::Instance()->BindAttribute("vertexIn");
	Shader::Instance()->BindAttribute("colorIn");
	Shader::Instance()->BindUniform("model");
	Shader::Instance()->BindUniform("view");
	Shader::Instance()->BindUniform("projection");

	Camera camera;
	camera.InitCamera(0.0f, 0.0f, 4.0f, 60.0f, 0.1f, 1000.0f);

	Cube* cube = new Cube();
	cube->CreateBuffers();

	glEnable(GL_DEBUG_OUTPUT); 
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);

	glDebugMessageCallback(&GLError::GetGLErrorCallback, nullptr);

	// This loop is 
	while (isProgramRunning)
	{
		// Clearing the buffer
		Screen::Instance()->ClearBuffer();

		// Checking for input 
		Input::Instance()->Update();
		if (Input::Instance()->IsXClicked())
		{
			isProgramRunning = false;
		}

		cube->Draw();
		cube->Update();
		camera.UpdateCamera();


		// Swapping the buffers
		Screen::Instance()->SwapBuffer();
	}


	delete cube;


	Shader::Instance()->DetachShaders();
	Shader::Instance()->DestroyShaders();
	Shader::Instance()->DestroyProgram();
	Screen::Instance()->Shutdown();


	return 0;
}
#include "Screen.h"
#include "Shader.h"
#include "Input.h"
#include "Debug.h"
#include "Cube.h"
#include <iostream>


bool isProgramRunning = true;

int main(int argc, char* args[])
{
	//============================================================================
	//	Initializing shader program and accosiated shaders
	//============================================================================
	if (!Screen::Instance()->InitScreen())
	{
		return false;
		Debug::Log("Failed to Initialize a screen. Check your settings file.");
	}

	if (!Shader::Instance()->CreateProgram())
	{
		Debug::Log("Failed to create shader program.");
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
	// Attributes send into shader (once!)
	Shader::Instance()->BindAttribute("vertexIn");
	Shader::Instance()->BindAttribute("colorIn");
	Shader::Instance()->BindUniform("model");
	Shader::Instance()->BindUniform("view");


	Cube* cubeObj = new Cube();
	cubeObj->CreateBuffers();


	// This loop runs until the application is 
	// terminated via the window
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

		cubeObj->Draw();
		cubeObj->Update();

		// Swapping the buffers
		Screen::Instance()->SwapBuffer();
	}

	delete cubeObj;


	Shader::Instance()->DetachShaders();
	Shader::Instance()->DestroyShaders();
	Shader::Instance()->DestroyProgram();
	Screen::Instance()->Shutdown();

	return 0;
}
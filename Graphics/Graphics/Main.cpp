#include "Screen.h"
#include "Shader.h"
#include "Input.h"
#include "Debug.h"
#include <iostream>


bool isProgramRunning = true;

int main(int argc, char* args[])
{
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

	Color color;
	Position position;



	// This loop is 
	while (isProgramRunning)
	{
		color.r += 5.5f;
		color.g += 0.0f;
		color.b += 0.0f;

		// Clearing the buffer
		Screen::Instance()->ClearBuffer();

		// Checking for input 
		Input::Instance()->Update();
		if (Input::Instance()->IsXClicked())
		{
			isProgramRunning = false;
		}


		float pos[6] =
		{
			-0.5f, -0.5f,
			0.0f, 0.5f,
			0.5f, -0.5f
		};

		// Setting up a buffer for the vertex shader
		unsigned int buffer;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), pos, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);



		// Swapping the buffers
		Screen::Instance()->SwapBuffer();
	}


	Shader::Instance()->DetachShaders();
	Shader::Instance()->DestroyShaders();
	Shader::Instance()->DestroyProgram();
	Screen::Instance()->Shutdown();

	return 0;
}


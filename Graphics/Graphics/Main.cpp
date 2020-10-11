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

		glMatrixMode(GL_MODELVIEW);


		//Input::Instance()->PassKeyboardMsgDown();
		
		if (SDL_GetScancodeFromKey(SDL_SCANCODE_W))
		{
			std::cout << "W was pressed on the keyboard!" << std::endl;
		}

		glRotatef(1.0f, 0.0f, 1.0f, 0.0f);

		glBegin(GL_QUADS);
		//top left color and vertex of quad

			glColor3f(color.r, color.g, color.b);
			glVertex3f(-0.5f, 0.5f, 0.0f);

			//top right color and vertex of quad
			glColor3f(0, 1, 0);
			glVertex3f(0.5f, 0.5f, 0.0f);

			//bottom right color and vertex of quad
			glColor3f(0, 0, 1);
			glVertex3f(0.5f, -0.5f, 0.0f);

			//bottom left color and vertex of quad
			glColor3f(0, 0, 1);
			glVertex3f(-0.5f, -0.5f, 0.0f);


		glEnd();

		//glTranslatef(position.x + 0.01f, position.y, position.z);

		if (position.x == 0.5f)
		{
			glTranslatef(position.x + 0.01f, position.y + 0.0f, position.z + 0.0f);
		}

		if (position.x > 1.0f)
		{
			//position.x -= 0.1f;
			//glRotatef(1.0f, 0.0f, 1.0f, 0.0f);
			glTranslatef(position.x - 0.01f, position.y + 0.0f, position.z + 0.0f);
		}
		else if (position.x < -1.0f)
		{
			//position.x += 0.1f;
			//glRotatef(1.0f, 0.0f, 1.0f, 0.0f);
			glTranslatef(position.x + 0.01f, position.y + 0.0f, position.z + 0.0f);
		}


		//// Second Tri
		glBegin(GL_TRIANGLES);

		glColor3f(1, 0, 0);
		glVertex3f(0.0f, 0.5f, 0.0f);

		glColor3f(0, 1, 0);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glColor3f(0, 0, 1);
		glVertex3f(-0.5f, -0.5f, 0.0f);

		glEnd();

		// Swapping the buffers
		Screen::Instance()->SwapBuffer();
	}


	Shader::Instance()->DetachShaders();
	Shader::Instance()->DestroyShaders();
	Shader::Instance()->DestroyProgram();
	Screen::Instance()->Shutdown();

	return 0;
}
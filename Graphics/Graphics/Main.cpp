#include "Screen.h"
#include "Input.h"
#include <iostream>


bool isProgramRunning = true;

int main(int argc, char* args[])
{
	if (!Screen::Instance()->InitScreen())
	{
		return false;
		std::cout << "Failed to Initialize a screen. Check your settings file." << std::endl;
	}

	
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


		//char key = 

		//if (SDL_GetScancodeFromKey(SDL_SCANCODE_W))
		//{
		//	std::cout << "W was pressed on the keyboard!" << std::endl;
		//}

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

	Screen::Instance()->Shutdown();

	return 0;
}
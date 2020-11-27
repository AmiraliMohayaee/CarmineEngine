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


	//============================================================================
	//	Rendering
	//============================================================================
	// Seperate vertex data buffer object
	GLfloat vertices[] = { -0.5f,  0.5f, 0.0f,
							0.5f,  0.5f, 0.0f,
							0.5f, -0.5f, 0.0f,
							-0.5f, -0.5f, 0.0f
	};

	// Passing in color data
	GLfloat colors[] = { 1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f,
						0.0f, 1.0f, 0.0f,
						0.0f, 1.0f, 1.0f
	};

	// EBO indecies shared between the two triangles
	GLuint indicies[] = { 0, 1, 3,
		3, 1, 2
	};

	Shader::Instance()->BindAttribute("vertexIn");
	Shader::Instance()->BindAttribute("colorIn");

	// Attributes send into shader 
	GLuint vertexAttributeID = Shader::Instance()->GetAttributeID("vertexIn");
	GLuint colorAttributeID = Shader::Instance()->GetAttributeID("colorIn");

	glEnableVertexAttribArray(vertexAttributeID);
	glEnableVertexAttribArray(colorAttributeID);

	// Creating buffer and setting up the size
	GLuint VAO = 0;
	GLuint vertexVBO = 0;
	GLuint colorsVBO = 0;
	GLuint EBO = 0;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorsVBO);
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexAttributeID);

	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorAttributeID);

	// Setting up the EBO buffer elements, which is differentiated from the regular
	// array elements
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);


	glBindVertexArray(0);

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

		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		// Swapping the buffers
		Screen::Instance()->SwapBuffer();
	}

	// When we don't need the vert and color attributes
	// Ideal for use in a dtor
	glDisableVertexAttribArray(colorAttributeID);
	glDisableVertexAttribArray(vertexAttributeID);

	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &colorsVBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);

	Shader::Instance()->DetachShaders();
	Shader::Instance()->DestroyShaders();
	Shader::Instance()->DestroyProgram();
	Screen::Instance()->Shutdown();


	return 0;
}
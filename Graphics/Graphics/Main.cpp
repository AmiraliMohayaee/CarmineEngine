#include "Screen.h"
#include "Shader.h"
#include "Input.h"
#include "Debug.h"
//#include "Cube.h"
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


	// Seperate vertex data buffer object
	GLfloat vertices[] = { -0.5f,  0.5f, 0.0f, 0.5f,  0.5f, 0.0f,0.5f, -0.5f, 0.0f,-0.5f, -0.5f, 0.0f
	};

	// Passing in color data
	GLfloat colors[] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,0.0f, 1.0f, 0.0f,0.0f, 1.0f, 1.0f
	};

	// EBO indecies shared between the two triangles
	GLfloat indicies[] = { 0, 1, 3, 3, 1, 2
	};


	//Cube* cubeObj = new Cube();
	//cubeObj->CreateBuffers();
	GLuint m_vertexAttributeID = Shader::Instance()->GetAttributeID("vertexIn");
	GLuint m_colorAttributeID = Shader::Instance()->GetAttributeID("colorIn");
	GLuint m_modelUniformID = Shader::Instance()->GetUniformID("model");
	GLuint m_viewUniformID = Shader::Instance()->GetUniformID("view");

	GLuint m_VAO = 0;
	GLuint m_vertexVBO = 0;
	GLuint m_colorsVBO = 0;
	GLuint m_EBO = 0;

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_vertexVBO);
	glGenBuffers(1, &m_colorsVBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(m_vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(m_vertexAttributeID);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		glVertexAttribPointer(m_colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(m_colorAttributeID);

		// Setting up the EBO buffer elements, which is differentiated from the regular
		// array elements
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	//Shader::Instance()->SendUniformData("view", m_viewMatrix);

	glBindVertexArray(0);


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

		glBindVertexArray(m_VAO);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			//Shader::Instance()->SendUniformData("model", m_modelMatrix);
			//Shader::Instance()->SendUniformData("view", m_viewMatrix);

		glBindVertexArray(0);

		//cubeObj->Draw();
		//cubeObj->Update();

		// Swapping the buffers
		Screen::Instance()->SwapBuffer();
	}

	/*delete cubeObj;*/


	Shader::Instance()->DetachShaders();
	Shader::Instance()->DestroyShaders();
	Shader::Instance()->DestroyProgram();
	Screen::Instance()->Shutdown();

	return 0;
}
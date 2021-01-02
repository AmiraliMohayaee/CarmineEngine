#include "App.h"

App::App()
{
	m_isProgramRunning = true;

	m_camera = new Camera();
	m_cube = new Cube();
	m_grid = new Grid();
}

bool App::InitScreenAndShaders()
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
	Debug::Log((const char*)(glGetString(GL_VENDOR)));
	//display the make and model of the graphics card
	Debug::Log((const char*)(glGetString(GL_RENDERER)));
	//display the current OpenGL version and mode set
	Debug::Log((const char*)(glGetString(GL_VERSION)));

	return true;
}


void App::BindElements()
{
	Shader::Instance()->BindAttribute("vertexIn");
	Shader::Instance()->BindAttribute("colorIn");
	Shader::Instance()->BindUniform("model");
	Shader::Instance()->BindUniform("view");
	Shader::Instance()->BindUniform("projection");
}

void App::InitObjects()
{
	//////////////////////////////////////////
	// Initializing Viewing Grid and Camera
	//////////////////////////////////////////
	m_camera->InitCamera(0.0f, 0.0f, 5.0f, 75.0f, 0.1f, 1000.0f);
	m_cube->CreateBuffers();
	//m_grid->CreateBuffer();
	m_grid->SetupGridDimentions(4, 10, 1.0f, 1.0f, 1.0f);

	//////////////////////////////////////////
	// Open GL Debugger Message Catching
	//////////////////////////////////////////
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);

	glDebugMessageCallback(&GLError::GetGLErrorCallback, nullptr);
}

void App::Draw()
{
	m_cube->Draw();
	m_grid->Draw();
}

void App::Update()
{
	while (m_isProgramRunning)
	{
		// Clearing the buffer
		Screen::Instance()->ClearBuffer();

		// Checking for inputs 
		Input::Instance()->Update();
		if (Input::Instance()->IsXClicked())
		{
			m_isProgramRunning = false;
		}
		if (Input::Instance()->KeyPressed() == true)
		{
			if (Input::Instance()->GetKeyPressed() == Key_Esc)
			{
				m_isProgramRunning = false;
			}
		}
		
		// Encapsulates draw calls from other game objects
		Draw();
		m_camera->UpdateCamera();

		// Swapping the buffers
		Screen::Instance()->SwapBuffer();
	}
}

void App::Shutdown()
{
	delete m_camera;
	delete m_cube;
	delete m_grid;

	Shader::Instance()->DetachShaders();
	Shader::Instance()->DestroyShaders();
	Shader::Instance()->DestroyProgram();
	Screen::Instance()->Shutdown();
}

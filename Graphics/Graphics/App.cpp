#include "App.h"


App::App()
{
	m_isProgramRunning = true;

	m_camera = std::make_unique<Camera>();
	m_cube = std::make_unique<Cube>();
	m_grid = std::make_unique<Grid>();
	//m_quad = std::make_unique<Quad>();
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


	Debug::PrintGraphicsEngineVersion();

	return true;
}


void App::BindElements()
{
	Shader::Instance()->BindAttribute("vertexIn");
	Shader::Instance()->BindAttribute("colorIn");
	Shader::Instance()->BindAttribute("textureIn");
	Shader::Instance()->BindUniform("model");
	Shader::Instance()->BindUniform("view");
	Shader::Instance()->BindUniform("projection");
	Shader::Instance()->BindUniform("isTextured");
}

void App::InitObjects()
{
	//////////////////////////////////////////
	// Initializing Viewing Grid and Camera
	//////////////////////////////////////////

	Texture::Load("Assets/Textures/Crate_1_Diffuse.png", "CRATE");

	m_camera->InitCamera(0.0f, 0.0f, 5.0f, 45.0f, 0.1f, 1000.0f);
	m_cube->CreateBuffers();
	//m_quad->CreateBuffers();
	//m_grid->SetupGridDimentions(4, 11, 1.0f, 1.0f, 1.0f);
	m_grid->CreateBuffers();

	// Error Catching Code
	GLError::GraphicsErrorCatch();
}

void App::Draw()
{
	m_cube->Draw();
	//m_quad->Draw();
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
		
		
		m_camera->UpdateCamera();
		
		// Encapsulates draw calls from other game objects
		Draw();

		// Swapping the buffers
		Screen::Instance()->SwapBuffer();
	}
}

void App::Shutdown()
{
	//m_quad->DestroyBuffer();
	m_cube->DestroyBuffers();
	m_grid->DestroyBuffers();

	Shader::Instance()->DetachShaders();
	Shader::Instance()->DestroyShaders();
	Shader::Instance()->DestroyProgram();
	Screen::Instance()->Shutdown();
}

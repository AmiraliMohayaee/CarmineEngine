#include "App.h"


App::App()
{
	m_isProgramRunning = true;

	m_camera = std::make_unique<Camera>();
	m_cube = std::make_unique<Cube>();
	m_grid = std::make_unique<Grid>();
	m_model = std::make_unique<Model>();
	m_light = std::make_unique<Light>(0.0f, 3.0f, 0.0f);
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
	Shader::Instance()->BindAttribute("normalIn");
	Shader::Instance()->BindAttribute("textureIn");

	Shader::Instance()->BindUniform("model");
	Shader::Instance()->BindUniform("view");
	Shader::Instance()->BindUniform("projection");

	Shader::Instance()->BindUniform("isLit");
	Shader::Instance()->BindUniform("isTextured");
	Shader::Instance()->BindUniform("cameraPosition");

	Shader::Instance()->BindUniform("light.ambient");
	Shader::Instance()->BindUniform("light.diffuse");
	Shader::Instance()->BindUniform("light.specular");
	Shader::Instance()->BindUniform("light.position");

	Shader::Instance()->BindUniform("material.ambient");
	Shader::Instance()->BindUniform("material.diffuse");
	Shader::Instance()->BindUniform("material.specular");
	Shader::Instance()->BindUniform("material.shininess");
}

void App::InitObjects()
{
	//////////////////////////////////////////
	// Initializing Viewing Grid and Camera
	//////////////////////////////////////////

	Texture::Load("Assets/Textures/Crate_1_Diffuse.png", "CRATE");

	m_camera->InitCamera(0.0f, 0.0f, 5.0f, 45.0f, 0.1f, 1000.0f);
	m_cube->CreateBuffers();

	m_light->CreateBuffers();

	//m_quad->CreateBuffers();
	//m_grid->SetupGridDimentions(4, 11, 1.0f, 1.0f, 1.0f);
	m_grid->CreateBuffers();

	//m_model->Load("Assets/Models/Cube.obj");

	// Error Catching Code
	GLError::GraphicsErrorCatch();
}

void App::Draw()
{
	m_light->Render();
	m_light->SendToShader();

	m_cube->Draw();
	//m_quad->Draw();
	m_grid->Draw();

	//m_model->Render();
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
	m_light->DestroyBuffers();

	m_model->Unload();

	Shader::Instance()->DetachShaders();
	Shader::Instance()->DestroyShaders();
	Shader::Instance()->DestroyProgram();
	Screen::Instance()->Shutdown();
}

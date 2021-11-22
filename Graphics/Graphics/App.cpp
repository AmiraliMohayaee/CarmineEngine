#include "App.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"

App::App()
{
	m_isProgramRunning = true;

	// TODO: Add asserts inside the functions to make sure they're loaded before the materials are use
	Material::LoadMaterials("Materials.mat");
	//Material::LoadMaterials("cube.mtl");

	m_camera = std::make_unique<FPSCamera>();
	m_cube = std::make_unique<Cube>();
	m_grid = std::make_unique<Grid>();
	m_model = std::make_unique<Model>();
	m_light = std::make_unique<Light>(0.0f, 3.0f, 0.0f);
	m_quad = std::make_unique<Quad>();
}

bool App::InitScreenAndShaders()
{
	if (!Screen::Instance()->InitScreen())
	{
		std::cout << "Failed to Initialize a screen. Check your settings file." << std::endl;
		return 0;
	}

	if (!Shader::Instance()->CreateProgram())
	{
		std::cout << "Shader Program return a false result. Possile wrong linking." << std::endl;
		return 0;
	}

	if (!Shader::Instance()->CreateShaders())
	{
		std::cout << "Failed to create shaders." << std::endl;
		return 0;
	}

	if (!Shader::Instance()->CompileShader("main.vert"))
	{
		std::cout  <<"Failed to compile shaders." << std::endl;
		return 0;
	}

 	if (!Shader::Instance()->CompileShader("main.frag"))
	{
		std::cout << "Failed to compile shaders." << std::endl;
		return 0;
	}

	Shader::Instance()->AttachShaders();

	if (!Shader::Instance()->LinkProgram())
	{
		std::cout << "Failed to link the shader program." << std::endl;
		return 0;
	}

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

	Texture::Load("Crate_1_Diffuse.png", "CRATE");

	
	//m_camera->InitCamera(0.0f, 0.0f, 5.0f, 45.0f, 0.1f, 1000.0f);
	m_camera->SetSpeed(0.0f);
	m_camera->SetSensitivity(0.0f);
	m_camera->SetPosition(0.0f, 0.0f, 3.5f);
	m_camera->CreatePerspView();

	m_cube->Create();
	m_cube->IsLit(true);
	m_cube->IsTextured(true);

	m_light->Create();

	//m_quad->Create();
	//m_quad->IsLit(true);
	//m_quad->IsTextured(true);

	m_grid->SetupGridDimentions(4, 12, 1.0f, 1.0f, 1.0f, 1.0f);
	//m_grid->CreateBuffers();

	
	
	m_model->Load("Teapot.obj");
	m_model->IsLit(false);
	m_model->IsTextured(false);
	
	
	// Error Catching Code
	//GLError::GraphicsErrorCatch();
}

void App::Draw()
{
	m_light->Draw();
	m_light->SendToShader();

	m_cube->Draw();
	m_grid->Draw();
	//m_quad->Draw();

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
			if (Input::Instance()->GetKeyPressed() == KEY_ESC)
			{
				m_isProgramRunning = false;
			}
		}

		// Using mouse wheel to zoom in the camera
		float wheelMotion = static_cast<float>(Input::Instance()->GetMouseWheelMotion());
		wheelMotion *= 0.1;

		static glm::vec3 camPos = m_camera->GetTransform().GetPosition();
		
		camPos.z += wheelMotion;
		m_camera->GetTransform().SetPosition(camPos);

		std::cout << camPos.z << std::endl;
		std::cout << wheelMotion << std::endl;

		static GLfloat yaw = 0.0f;
		static GLfloat pitch = 0.0f;

		if (Input::Instance()->IsLeftButtonDown())
		{
			yaw += Input::Instance()->GetMouseMotion().x;
			pitch -= Input::Instance()->GetMouseMotion().y;
		}


		m_cube->GetTransform().SetRotation(pitch, yaw, 0.0f);
		m_grid->GetTransform().SetRotation(pitch, yaw, 0.0f);
		
		m_camera->Update();
		m_camera->SendToShader();

		if (Input::Instance()->IsRightButtonDown())
		{
			m_camera->Reset();
		}

		// Encapsulates draw calls from other game objects
		Draw();
		
		//UI==================================================================
		Screen::Instance()->StartUI();

		bool newScene = false;
		bool loadScene = false;
		bool saveScene = false;
		bool exitApp = false;
	
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::MenuItem("New scene", nullptr, &newScene);
				ImGui::MenuItem("Load scene...", nullptr, &loadScene);
				ImGui::MenuItem("Save scene", nullptr, &saveScene);
				ImGui::MenuItem("Exit", nullptr, &exitApp);
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Help"))
			{
				ImGui::MenuItem("Tutorial", nullptr, &newScene);
				ImGui::MenuItem("About...", nullptr, &newScene);
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		
		Screen::Instance()->RenderUI();

		//====================================================================
		// Swapping the buffers
		Screen::Instance()->SwapBuffer();

		m_isProgramRunning = !exitApp;
	}
}

void App::Shutdown()
{
	m_quad->Destroy();
	m_cube->Destroy();
	m_grid->Destroy();
	m_light->Destroy();

	m_model->Unload();

	Shader::Instance()->DetachShaders();
	Shader::Instance()->DestroyShaders();
	Shader::Instance()->DestroyProgram();
	Screen::Instance()->Shutdown();
}

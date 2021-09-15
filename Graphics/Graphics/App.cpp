#include "App.h"
#include "Utility.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"


App::App()
{
	m_isProgramRunning = true;

	// TODO: Add asserts inside the functions to make sure they're loaded before the materials are use
	Material::LoadMaterials("Materials.mat");
	//Material::LoadMaterials("cube.mtl");

	m_cube = std::make_unique<Cube>();
	m_grid = std::make_unique<Grid>();
	m_quad = std::make_unique<Quad>();
	m_model = std::make_unique<Model>();
	m_camera = std::make_unique<FPSCamera>();
	m_light = std::make_unique<Light>(0.0f, 3.0f, 0.0f);
}

bool App::InitScreenAndShaders()
{
	if (!Screen::Instance()->InitScreen())
	{
		Debug::Log("Failed to Initialize a screen. Check your settings file.");
		return 0;
	}

	m_mainShader = std::make_unique<Shader>();

	m_mainShader->Create("Assets/Shaders/main.vert", "Assets/Shaders/main.frag");
	
	m_mainShader->BindAttribute("vertexIn");
	m_mainShader->BindAttribute("colorIn");
	m_mainShader->BindAttribute("normalIn");
	m_mainShader->BindAttribute("textureIn");

	m_mainShader->BindUniform("model");
	m_mainShader->BindUniform("view");
	m_mainShader->BindUniform("projection");

	m_mainShader->BindUniform("isLit");
	m_mainShader->BindUniform("isTextured");
	m_mainShader->BindUniform("cameraPosition");

	m_mainShader->BindUniform("light.ambient");
	m_mainShader->BindUniform("light.diffuse");
	m_mainShader->BindUniform("light.specular");
	m_mainShader->BindUniform("light.position");

	m_mainShader->BindUniform("material.ambient");
	m_mainShader->BindUniform("material.diffuse");
	m_mainShader->BindUniform("material.specular");
	m_mainShader->BindUniform("material.shininess");
	
	//Debug::PrintGraphicsEngineVersion();

	return true;
}


void App::InitObjects()
{
	//////////////////////////////////////////
	// Initializing Viewing Grid and Camera
	//////////////////////////////////////////

	Texture::Load("Crate_1_Diffuse.png", "CRATE");

	m_camera->CreatePerspView();
	//m_camera->IsFlying(false);
	m_camera->SetSensitivity(0.0f);
	m_camera->SetSpeed(0.0f);
	m_camera->SetPosition(0.0f, 0.0f, 3.0f);
	
	m_cube->Create();
	m_cube->IsLit(true);
	m_cube->IsTextured(true);

	m_light->Create();

	//m_quad->Create();
	//m_quad->IsLit(false);
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
	auto& mainShader = *m_mainShader.get();

	m_grid->Draw(mainShader);
	
	m_light->Draw(mainShader);
	m_light->SendToShader(mainShader);

	m_cube->Draw(mainShader);
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
		int wheelMotion = Input::Instance()->GetMouseWheelMotion();

		static glm::vec3 camPos = m_camera->GetTransform().GetPosition();

		camPos.z += wheelMotion;
		m_camera->GetTransform().SetPosition(camPos);

		std::cout << wheelMotion << std::endl;

		static GLfloat yaw = 0.0f;
		static GLfloat pitch = 0.0f;
		
		if (Input::Instance()->IsLeftButtonDown())
		{
			yaw += Input::Instance()->GetMouseMotion().x;
			pitch -= Input::Instance()->GetMouseMotion().y;
		}


		auto& mainShader = *m_mainShader.get();

		m_cube->GetTransform().SetRotation(pitch, yaw, 0.0f);
		m_grid->GetTransform().SetRotation(pitch, yaw, 0.0f);
		
		m_camera->Update();
		m_camera->SendToShader(mainShader);
		
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
	}
}

void App::Shutdown()
{
	m_quad->Destroy();
	m_cube->Destroy();
	m_grid->Destroy();
	m_light->Destroy();

	m_model->Unload();

	m_mainShader->Destroy();
	Screen::Instance()->Shutdown();
}

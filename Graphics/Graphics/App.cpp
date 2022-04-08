#include "App.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"

App::App()
{
	m_isProgramRunning = true;

	// TODO: Add asserts inside the functions to make sure they're loaded before the materials are use
	Material::Load("Defaults", "Materials.mat");

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

	m_mainShader = std::make_unique<Shader>();

	m_mainShader->Create("Default.vert", "Default.frag");

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


	return true;
}


void App::InitObjects()
{
	//////////////////////////////////////////
	// Initializing Viewing Grid and Camera
	//////////////////////////////////////////

	//Texture::Load("Crate_1_Diffuse.png", "CRATE");

	// Loading in Font into Imgui directly from a file
	ImGui::GetIO().Fonts->AddFontFromFileTTF("Assets/Fonts/KindlyRewind-BOon.ttf", 12);
	
	//m_camera->InitCamera(0.0f, 0.0f, 5.0f, 45.0f, 0.1f, 1000.0f);
	m_camera->SetSpeed(0.5f);
	m_camera->SetSensitivity(1.0f);
	m_camera->SetPosition(0.0f, 0.0f, 3.5f);
	m_camera->CreatePerspView();

	//m_cube->Create();
	//m_cube->IsLit(true);
	//m_cube->IsTextured(true);

	//m_light->Create();

	//m_quad->Create();
	//m_quad->IsLit(true);
	//m_quad->IsTextured(true);

	m_grid->Create();
	//m_grid->SetupGridDimentions(4, 12, 1.0f, 1.0f, 1.0f, 1.0f);
	//m_grid->CreateBuffers();

	
	
	//m_model->Load("Teapot.obj");
	//m_model->IsLit(false);
	//m_model->IsTextured(false);
	
	
	// Error Catching Code
	//GLError::GraphicsErrorCatch();
}

void App::Draw()
{
	auto& mainShader = *m_mainShader.get();
	mainShader.Use();


	//m_light->Draw(mainShader);
	//m_light->SendToShader(mainShader);

	//m_cube->Draw(mainShader);
	m_grid->Draw(mainShader);
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
		auto wheelMotion = Input::Instance()->GetMouseWheelMotion();
		//wheelMotion *= 0.1f;

		static auto cameraPosition = m_camera->GetTransform().GetPosition();
		
		cameraPosition.z += wheelMotion;
		m_camera->GetTransform().SetPosition(cameraPosition);

		//std::cout << cameraPosition.z << std::endl;
		//std::cout << wheelMotion << std::endl;

		static GLfloat yaw = 0.0f;
		static GLfloat pitch = 0.0f;

		// Making an instance of InGui IO to disallow mouse click
		// and movement when using UI elements
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		if (!io.WantCaptureMouse)
		{

			if (Input::Instance()->IsLeftButtonDown())
			{
				yaw += Input::Instance()->GetMouseMotion().x;
				pitch -= Input::Instance()->GetMouseMotion().y;
			}

		}


		//m_cube->GetTransform().SetRotation(pitch, yaw, 0.0f);
		m_grid->GetTransform().SetRotation(pitch, yaw, 0.0f);
		
		auto& mainShader = *m_mainShader.get();

		m_camera->Update();
		m_camera->SendToShader(mainShader);

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

			if (ImGui::BeginMenu("Add"))
			{
				ImGui::MenuItem("Shapes", nullptr, nullptr);
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Help"))
			{
				ImGui::MenuItem("Tutorial", nullptr, &newScene);
				ImGui::MenuItem("About...", nullptr, &newScene);
				ImGui::EndMenu();
			}

			
			if (ImGui::Begin("Window"))
			{
				ImGui::Text("Hello World.");
				ImGui::Checkbox("Exit Appllication", &exitApp);
				//ImGui::SliderFloat("Size", &m_camera->GetTransform().GetPosition().z, 0.3f, 2.0f);
				ImGui::End();
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

	m_mainShader->Destroy();
	Screen::Instance()->Shutdown();
}

void App::MenuInput()
{

}

void App::ManageUI()
{

}

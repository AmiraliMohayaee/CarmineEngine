#include "App.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"


App::App()
{
	m_isProgramRunning = true;

	Material::LoadMaterials("Defaults", "Materials.mat");

	m_camera = std::make_unique<FPSCamera>();
	m_cube = std::make_unique<Cube>();
	m_grid = std::make_unique<Grid>();
	m_model = std::make_unique<Model>();
	m_light = std::make_unique<Light>(2.0f, 5.0f, 0.0f);
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

	m_mainShader->Create("main.vert", "main.frag");

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

	Texture::Load("Crate_1_Diffuse.png", "Crate");
	
	//m_camera->InitCamera(0.0f, 0.0f, 5.0f, 45.0f, 0.1f, 1000.0f);
	m_camera->SetSpeed(0.5f);
	m_camera->SetSensitivity(1.0f);
	//m_camera->SetPosition(0.0f, 3.0f, 10.0f);
	m_camera->GetTransform().SetPosition(0.0f, 3.0f, 10.0f);
	m_camera->CreatePerspView();

	m_cube->Create();
	m_cube->IsLit(true);
	m_cube->IsTextured(true);

	m_light->Create();

	//m_quad->Create();
	//m_quad->IsLit(true);
	//m_quad->IsTextured(true);

	m_grid->Create();
	//m_grid->SetupGridDimentions(4, 12, 1.0f, 1.0f, 1.0f, 1.0f);
	//m_grid->CreateBuffers();

	ImGui::GetIO().Fonts->AddFontFromFileTTF("Assets/Fonts/Arial.ttf", 18);
	ImGui::GetIO().Fonts->Build();
	
	//m_model->Load("Teapot.obj");
	//m_model->IsLit(false);
	//m_model->IsTextured(false);
	

	//////////////////////////////////////////
	// Initializing Audio and Sounds
	//////////////////////////////////////////
	Audio::Initialize();
	
	m_audio->Load(Audio::Type::Music, "test", "audiotest.mp3");
	m_audio = std::make_unique<Audio>(Audio::Type::Music, "test");

}

void App::Draw()
{
	auto& mainShader = *m_mainShader.get();

	mainShader.Use();

	m_light->Draw(mainShader);
	m_light->SendToShader(mainShader);

	//m_camera->Reset();
	//m_camera->SendToShader(mainShader);

	m_cube->Draw(mainShader);
	m_cube->SendToShader(mainShader);
	m_grid->Draw(mainShader);
	m_grid->SendToShader(mainShader);
}

void App::Update()
{



	while (m_isProgramRunning)
	{
		auto res = Screen::Instance()->GetResolution();

		//TODO - Put this away deep inside your engine (Screen/camera class?)
		glViewport(0, 0, res.x * 0.85, res.y);

		//====================================================================
		// Clearing the buffer
		Screen::Instance()->ClearBuffer();

		Draw();
		ManageUI();
		

		glViewport(res.x * 0.85f, 0, res.x * 0.15f, res.y);
		
		//TODO - Put this away deep inside your engine (Screen/camera class?)
		glViewport(0, 0, res.x * 0.85f, res.y);
		
		Screen::Instance()->ClearBuffer();

		ManageInput();
		Audio::Update();

		// Encapsulates draw calls from other game objects
		

		//====================================================================
		// Swapping the buffers
		Screen::Instance()->SwapBuffer();

		
	}
}

void App::Shutdown()
{
	Audio::Shutdown();
	m_quad->Destroy();
	m_cube->Destroy();
	m_grid->Destroy();
	m_light->Destroy();

	m_model->Unload();

	m_mainShader->Destroy();
	Screen::Instance()->Shutdown();
}

void App::ManageUI()
{
	//UI==================================================================
	Screen::Instance()->StartUI();

	bool newScene = false;
	bool loadScene = false;
	bool saveScene = false;
	bool exitApp = false;
	static bool playAudioTest = false;
	static bool stopAudioTest = false;
	
	static bool cameraSettingsOpen = false;

	m_sliderCamPos = m_camera->GetTransform().GetPosition();

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

		if (ImGui::BeginMenu("Settings"))
		{
			if (ImGui::MenuItem("Camera", nullptr, &newScene))
			{
				cameraSettingsOpen = true;
			}

			ImGui::EndMenu();
		}

		/*ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}*/

		ImGui::EndMainMenuBar();
	}

	

	if (ImGui::Begin("Audio"))
	{
		ImGui::Text("Audio Options");
		ImGui::Checkbox("Play Audio Test", &playAudioTest);

		if (playAudioTest)
		{
			m_audio->Play();
		}

		ImGui::Checkbox("Stop Audio Test", &stopAudioTest);

		if (stopAudioTest)
		{
			m_audio->Stop();
		}

		ImGui::End();
	}

	if (ImGui::Begin("Application"))
	{
		ImGui::Text("Hello World.");
		ImGui::Checkbox("Exit Appllication", &exitApp);
		ImGui::End();
	}

	if (cameraSettingsOpen)
	{
		if (ImGui::Begin("Camera settings", nullptr))
		{
			ImGui::Text("Use these sliders to control the camera");
			ImGui::SliderFloat("Camera: X", &m_sliderCamPos.x, 0, 8);
			ImGui::SliderFloat("Camera: Y", &m_sliderCamPos.y, 0, 8);
			ImGui::SliderFloat("Camera: Z", &m_sliderCamPos.z, 0, 8);
			//m_camera->SetPosition(m_sliderCamPos);
			ImGui::End();
		}
	}

	/*if (ImGui::Begin("Sliders"))
	{
		ImGui::Text("Use these sliders to move around the cemera");
		static float camPos = 0.0f;
		ImGui::SliderFloat("float", &camPos,
			0.0f, 10.0f);
		ImGui::End();
	}*/

	Screen::Instance()->RenderUI();
	
	
	m_isProgramRunning = !exitApp;
}

void App::ManageInput()
{
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
	cameraPosition.z -= wheelMotion;

	m_camera->GetTransform().SetPosition(cameraPosition);

	//std::cout << camPos.z << std::endl;
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

	m_camera->SendToShader(mainShader);

	if (Input::Instance()->IsRightButtonDown())
	{
		m_camera->Reset();
	}
}
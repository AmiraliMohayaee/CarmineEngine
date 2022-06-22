#pragma once


#include <memory>
#include "Screen.h"
#include "Input.h"
#include "Camera.h"
#include "Cube.h"
#include "Quad.h"
#include "Grid.h"
#include "Light.h"
#include "Model.h"
#include "FPSCamera.h"
#include "Shader.h"
#include "Audio.h"
#include "AboutBox.h"

class App
{

public:

	App();
	bool InitScreenAndShaders();


	void InitObjects();
	void Draw();
	void Update();
	void Shutdown();

	void ManageInput();
	void ManageUI(const Shader& shader);

private:

	bool m_isProgramRunning;

	std::unique_ptr<Cube> m_cube;
	std::unique_ptr<Grid> m_grid;
	std::unique_ptr<Quad> m_quad;
	std::unique_ptr<Audio> m_audio;
	std::unique_ptr<Light> m_light;
	std::unique_ptr<Model> m_model;
	std::unique_ptr<FPSCamera> m_camera;
	
	// TODO: Add the UI elements through container
	//std::unique_ptr<std::map<std::string, Dialog>> m_dialogs;
	std::unique_ptr<AboutBox> m_aboutBox;

	std::unique_ptr<Shader> m_mainShader;
	std::unique_ptr<Shader> m_lightShader;


};
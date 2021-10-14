#pragma once


#include <memory>
#include "Screen.h"
#include "Input.h"
#include "FPSCamera.h"
#include "Cube.h"
#include "Quad.h"
#include "Debug.h"
#include "Grid.h"
#include "Light.h"
#include "Model.h"
#include "Shader.h"
#include "Utility.h"


class App
{
public:

	App();
	bool InitScreenAndShaders();
	void BindElements();

	int GetTotalTime();
	int GetElapsedTime();

	void Draw();
	void Update();
	void Shutdown();
	void InitObjects();


private:
	bool m_isProgramRunning;

	std::unique_ptr<Cube> m_cube;
	std::unique_ptr<Grid> m_grid;
	std::unique_ptr<Quad> m_quad;
	std::unique_ptr<Light> m_light;
	std::unique_ptr<Model> m_model;
	std::unique_ptr<FPSCamera> m_camera;

	std::unique_ptr<Shader> m_mainShader;
	//std::unique_ptr<Shader> m_lightShader;

};
#pragma once


#include <memory>
#include "Screen.h"
#include "Shader.h"
#include "Input.h"
#include "Camera.h"
#include "Cube.h"
#include "Quad.h"
#include "Debug.h"
#include "GLError.h"
#include "Grid.h"


class App
{
public:
	App();
	bool InitScreenAndShaders();
	void BindElements();

	void InitObjects();
	void Draw();
	void Update();
	void Shutdown();


private:
	bool m_isProgramRunning;

	std::unique_ptr<Camera> m_camera;
	std::unique_ptr<Camera> m_cube;
	std::unique_ptr<Camera> m_grid;
	std::unique_ptr<Camera> m_quad;

	//Camera* m_camera;
	//Quad* m_quad;
	//Cube* m_cube;
	//Grid* m_grid;

};
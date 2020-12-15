#pragma once

#include "Screen.h"
#include "Shader.h"
#include "Input.h"
#include "Camera.h"
#include "Cube.h"
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

	Camera* m_camera;
	Cube* m_cube;
	Grid* m_grid;

};
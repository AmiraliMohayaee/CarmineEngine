#pragma once


#include <memory>
#include "State.h"



class Editor :	public State
{
public:

	Editor();
	virtual ~Editor() {}

	virtual void InputHandle();
	virtual State* Update();
	virtual void Draw();
	virtual void Shutdown();
	

private:

	void InitScreenAndShaders();
	void MenuInput();
	void ManageUI();

	bool m_isProgramRunning;

	//std::unique_ptr<Cube> m_cube;
	//std::unique_ptr<Grid> m_grid;
	//std::unique_ptr<Quad> m_quad;
	//std::unique_ptr<Light> m_light;
	//std::unique_ptr<Model> m_model;
	//std::unique_ptr<FPSCamera> m_camera;

	//std::unique_ptr<Shader> m_mainShader;
	//std::unique_ptr<Shader> m_lightShader;


};


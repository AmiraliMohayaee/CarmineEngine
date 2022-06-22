#pragma once
#include "Object.h"

#include "glad.h"
#include <glm.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"

//Also an ABC
class Dialog : public Object
{
public:

	// TODO Change the generic flags to equate to IMGUI types later
	enum WindowOpen
	{
		CLOSE = true,
		OPEN = false,
	};

	enum Style
	{
		NoCollapse = ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse,
		NoResize = ImGuiWindowFlags_::ImGuiWindowFlags_NoResize
	};

	enum Movable
	{
		MOVABLE,
		UNMOVABLE,
	};

	enum WindowState
	{
		DOCKABLE,
		STATIC,
		DRAGGABLE,
		NONINTERACTIVE,
		BUTTON,
	};

public:

	void Spacing(int amount);
	void Partition(const std::string& title);
	void SetDimension(const glm::uvec2& dimension);

protected:

	glm::uvec2 m_dimension;

};
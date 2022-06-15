#include "AboutBox.h"



void AboutBox::Create()
{
}

void AboutBox::Destroy()
{
}

void AboutBox::Draw(const Shader& shader)
{
	bool flag = false;;

	auto windowSize = ImVec2(300, 150);

	if (ImGui::Begin("About", &flag, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse 
		| ImGuiWindowFlags_::ImGuiWindowFlags_NoResize))
	{
		ImGui::SetWindowSize("About", windowSize);
		
		auto size = ImVec2(100, 25);
		ImGui::Text("This is an application.");
		
		Spacing(10);
		
		ImGui::Indent(90);
		
		if (ImGui::Button("OK", size))
		{
			m_isVisible = false;
		}

		ImGui::End();
	}

}

void AboutBox::Update()
{
}

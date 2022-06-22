#include "Dialog.h"

void Dialog::Spacing(int amount)
{

	for (int i = 0; i < amount; i++)
	{
		ImGui::Spacing();
	}

}

void Dialog::Partition(const std::string& title)
{
	ImGui::Text(title.c_str());
	ImGui::Separator();
	ImGui::Spacing();
}

void Dialog::SetDimension(const glm::uvec2& dimension)
{
	m_dimension = dimension;
}

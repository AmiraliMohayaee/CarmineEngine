#include "Dialog.h"

void Dialog::Spacing(int amount)
{

	for (int i = 0; i < amount; i++)
	{
		ImGui::Spacing();
	}

}

void Dialog::SetDimension(const glm::uvec2& dimension)
{
	m_dimension = dimension;
}

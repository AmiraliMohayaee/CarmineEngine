#include "Settings.h"

void Settings::Create()
{

}

void Settings::Destroy()
{

}

void Settings::Draw(const Shader& shader)
{
	if (ImGui::Begin("Settings", nullptr, Style::NoCollapse | Style::NoResize))
	{
		ImGui::SetWindowSize("Settings", ImVec2(m_dimension.x, m_dimension.y));

		Partition("Camera");
		ImGui::Checkbox("3D view", &m_cameraSettings.has3DView);
		ImGui::SliderFloat("FOV", &m_cameraSettings.cameraFOV, 20.0f, 90.0f);
		ImGui::SliderFloat("Far Clip", &m_cameraSettings.frustumFarClip, 10.0f, 1000.0f);
		ImGui::SliderFloat("Near clip", &m_cameraSettings.frustumNearClip, 0.001f, 10.0f);
		
		Spacing(3);
		
		Partition("Other");

		static char text[100] = "Hello";
		ImGui::InputText("Text", text, IM_ARRAYSIZE(text));

		Partition("More stuff");
		static int item = 0;
		const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIIIIII", "JJJJ", "KKKKKKK" };
		ImGui::Combo("Items", &item, items, 11);

		Partition("Even more stuff");
		const char* items2[] = { "Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon" };
		static int item_current = 1;
		ImGui::ListBox("listbox", &item_current, items2, IM_ARRAYSIZE(items2), 4);

		Spacing(3);
		ImGui::BulletText("Bullet point 1");

		ImGui::End();
	}
}

void Settings::Update()
{

}

const Settings::CameraSettings& Settings::GetCameraSettings()
{
	return m_cameraSettings;
}
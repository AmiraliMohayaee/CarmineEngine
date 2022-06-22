#include "Settings.h"

void Settings::Create()
{

}

void Settings::Destroy()
{

}

void Settings::Draw(const Shader& shader)
{
	if (ImGui::Begin("Settings",
		nullptr,
		ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_::ImGuiWindowFlags_NoResize))
	{
		ImGui::SetWindowSize("Settings", ImVec2(m_dimension.x, m_dimension.y));

		ImGui::Text("Camera");

		ImGui::SliderFloat("FOV", &m_cameraSettings.cameraFOV, 20.0f, 90.0f);
		ImGui::SliderFloat("Far Clip", &m_cameraSettings.frustumFarClip, 10.0f, 1000.0f);
		ImGui::SliderFloat("Near clip", &m_cameraSettings.frustumNearClip, 0.001f, 10.0f);

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
#include "Material.h"
#include "Shader.h"


Material::Material()
{
	m_shininess = 1.0f;
	m_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	m_specular = glm::vec3(1.0f, 1.0f, 1.0f);

}

Material::~Material()
{
}


void Material::SendToShader()
{
	Shader::Instance()->SendUniformData("material.shininess", m_shininess);
	Shader::Instance()->SendUniformData("material.ambient", m_ambient.r, m_ambient.g, m_ambient.b);
	Shader::Instance()->SendUniformData("material.diffuse", m_diffuse.r, m_diffuse.g, m_diffuse.b);
	Shader::Instance()->SendUniformData("material.specular", m_specular.r, m_specular.g, m_specular.b);
}

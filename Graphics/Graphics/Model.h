#pragma once

#include "Shader.h"
#include <gtc\matrix_transform.hpp>
#include <string>
#include <vector>


// Stored the seperate groups of the model
struct Mesh
{
	std::string name;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> UVs;
};


class Model
{
public:
	bool Load(std::string& filename);
	bool Create();
	
	void Render();
	void Destroy();
	
	


private:

	std::vector<Mesh> m_meshes;

};


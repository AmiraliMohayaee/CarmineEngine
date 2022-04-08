#pragma once

#include "Buffer.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <string>
#include <vector>
#include "Material.h"
#include "Texture.h"


// Stored the seperate groups of the model
struct Mesh
{
	std::string name;
	Material material;
	std::vector<GLuint> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec4> colors;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> UVs;
};

struct VertexGroup
{
	int v = -1;
	int t = -1;
	int n = -1;

	//This is required to be able to store this data type in a std::map
	bool operator< (const VertexGroup& other) const
	{
		if (this == &other)
		{
			return false;
		}

		if (v != other.v)
		{
			return v < other.v;
		}

		if (t != other.t)
		{
			return t < other.t;
		}

		return n < other.n;
	}
};


typedef std::vector<VertexGroup> Face;


class Model
{
public:
	bool Load(const std::string& filename);
	bool Load(const std::string& filename, const std::string& texture);
	void Render(const Shader& shader);
	void Unload();

	void IsTextured(bool flag);
	void IsLit(bool flag);
	

private:

	static std::string s_rootFolderModel;

	void FillBuffers();
	void SortVertexData(Mesh& newMesh, const Mesh& oldMesh, const std::vector<Face>& faces);
	
	glm::mat4 m_modelMatrix;

	bool m_isTextured;
	bool m_isLit;

	Texture m_ambientTexture;
	Texture m_diffuseTexture;
	Texture m_specularTexture;
	Texture m_normalTexture;
	Texture m_individualTexture;

	std::vector<Mesh> m_meshes;
	std::vector<Buffer> m_buffers;
	std::vector<Material> m_materials;
};


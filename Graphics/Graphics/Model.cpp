#include "Model.h"
#include "Utility.h"
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>

#include "Shader.h"


std::string Model::s_rootFolder = "Assets/Models/";
std::map<std::string, Model> Model::s_models;
//======================================================================================================
bool Model::Load(const std::string& tag,
	const std::string& filename,
	bool isNormalized,
	const std::string& defaultMaterial)
{
	assert(s_models.find(tag) == s_models.end());
	std::fstream file(s_rootFolder + filename, std::ios_base::in);

	if (!file)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error loading model file \"" + (s_rootFolder + filename) + "\"\n\n"
			"Possible causes could be a corrupt or missing file. Another reason could be "
			"that the filename and/or path are incorrectly spelt.", Utility::Severity::Failure);
		return false;
	}

	Mesh rawMesh;
	std::string lastMaterialName;

	std::string line;
	std::string lastName;
	std::vector<Face> faces;

	std::vector<std::string> subStrings;
	subStrings.reserve(10);

	Model model;
	model.m_tag = tag;

	while (!file.eof())
	{
		std::getline(file, line);
		subStrings.clear();

		//Only process data that is not blank or intended to be a comment
		if (!line.empty() && line[0] != '#')
		{
			Utility::ParseString(line, subStrings, ' ');

			//Vertex data
			if (subStrings[0] == "v")
			{
				rawMesh.vertices.push_back(glm::vec3(std::stof(subStrings[1]),
					std::stof(subStrings[2]),
					std::stof(subStrings[3])));
				continue;
			}

			//Normal data
			if (subStrings[0] == "vn")
			{
				rawMesh.normals.push_back(glm::vec3(std::stof(subStrings[1]),
					std::stof(subStrings[2]),
					std::stof(subStrings[3])));
				continue;
			}

			//Texture coordinate data
			if (subStrings[0] == "vt")
			{
				rawMesh.textureCoords.push_back(glm::vec2(std::stof(subStrings[1]),
					std::stof(subStrings[2])));
				continue;
			}

			//This is the line of face indices that contains data in 'v/t/n v/t/n v/t/n' format
			//This data together will make up a polygon face or triangle using the vtn indices
			//The data will be stored as v = subString[1], t = subString[2] and n = subString[3] 
			if (subStrings[0] == "f")
			{
				Face face;
				std::vector<std::string> numbers;
				numbers.reserve(10);

				//Parse face indices into individual index numbers so 1/2/3 becomes 1, 2 and 3
				//We subtract 1 because the index values in the .obj file are not zero-based
				for (int i = 1; i <= 3; i++)
				{
					numbers.clear();
					VertexGroup vertexGroup;
					Utility::ParseString(subStrings[i], numbers, '/');

					vertexGroup.v = std::stoi(numbers[0]) - 1;

					if (vertexGroup.v < 0)
					{
						vertexGroup.v = rawMesh.vertices.size() + (vertexGroup.v + 1);
					}

					//Some .obj files do not contain texture coordinate data 
					//so only add a texture index if there is one present
					if (numbers.size() > 2)
					{
						vertexGroup.t = std::stoi(numbers[1]) - 1;
						vertexGroup.n = std::stoi(numbers[2]) - 1;

						if (vertexGroup.t < 0)
						{
							vertexGroup.t = rawMesh.textureCoords.size() + (vertexGroup.t + 1);
						}

						if (vertexGroup.n < 0)
						{
							vertexGroup.n = rawMesh.normals.size() + (vertexGroup.n + 1);
						}
					}

					else
					{
						vertexGroup.n = std::stoi(numbers[2]) - 1;

						if (vertexGroup.n < 0)
						{
							vertexGroup.n = rawMesh.normals.size() + (vertexGroup.n + 1);
						}
					}

					face.push_back(vertexGroup);
				}

				faces.push_back(face);
				continue;
			}

			//This is the name of the material to use for the group 
			//All materials are found in the subsequent .mtl file
			if (subStrings[0] == "usemtl")
			{
				if (!model.m_material.GetGroup().empty())
				{
					for (const auto& material : model.m_material.GetGroup())
					{
						if (material.GetName() == subStrings[1])
						{
							lastMaterialName = subStrings[1];
							break;
						}
					}
				}

				continue;
			}

			//This indicates the name of the .mtl file to use for the mesh 
			//group. All materials are found in the subsequent material file
			//Note that sometimes the material file might not be found
			if (subStrings[0] == "mtllib")
			{
				model.m_material.Load(subStrings[1], subStrings[1]);
				model.m_material.SetGroup(subStrings[1]);
				continue;
			}

			//This indicates mesh groups or objects within 
			//the model which will make up the final model 
			if (subStrings[0] == "g" || subStrings[0] == "o")
			{
				//Go through all previously loaded faces 
				//and build a mesh from the previous group
				if (!faces.empty())
				{
					Mesh mesh;

					mesh.vertices.reserve(rawMesh.vertices.size());
					mesh.textureCoords.reserve(rawMesh.textureCoords.size());
					mesh.normals.reserve(rawMesh.normals.size());

					mesh.name = lastName;
					mesh.materialName = lastMaterialName;
					SortVertexData(mesh, rawMesh, faces);
					model.m_meshes.push_back(mesh);
				}

				//Make a note of the group name for the next mesh group
				lastName = subStrings[1];
				faces.clear();

				//TODO - Find a way to clear data that's 
				//no longer required from the raw mesh 
				//Not sure why this does not work?
				//rawMesh.vertices.clear();
				//rawMesh.textureCoords.clear();
				//rawMesh.normals.clear();

				continue;
			}

			//These are the smoothing groups
			if (subStrings[0] == "s")
			{
				//TODO
				continue;
			}
		}
	}

	file.close();

	//We do one more final clean-up of the raw data because v/t/n data is
	//usually read in AFTER a group name so the final data group needs sorting
	if (!faces.empty())
	{
		Mesh mesh;
		mesh.name = lastName;

		mesh.materialName = lastMaterialName;
		SortVertexData(mesh, rawMesh, faces);
		model.m_meshes.push_back(mesh);
	}

	//Check if any materials were loaded because there may be a 'mtllib' 
	//statement missing. This means that no materials, not even default 
	//ones are loaded so as a last resort, we add a default material
	if (model.m_material.GetGroup().empty())
	{
		model.m_material.SetGroup("Defaults");

		for (auto& mesh : model.m_meshes)
		{
			mesh.materialName = defaultMaterial;
		}
	}

	//Make sure the model has a normalized width, height and depth if required
	if (isNormalized)
	{
		Normalize(model);
	}

	//Get the new max lengths

	glm::vec3 minValues = glm::vec3(0.0f);
	glm::vec3 maxValues = glm::vec3(0.0f);

	for (const auto& mesh : model.m_meshes)
	{
		for (const auto& vertex : mesh.vertices)
		{
			maxValues = glm::max(maxValues, vertex);
			minValues = glm::min(minValues, vertex);
		}
	}

	model.m_dimension = maxValues - minValues;

	FillBuffers(model);
	s_models[tag] = model;
	return true;
}
//======================================================================================================
Model::Model(const std::string& tag,
	const std::string& filename,
	bool isNormalized,
	const std::string& defaultMaterial)
{
	m_dimension = glm::vec3(0.0f);

	if (!filename.empty())
	{
		Load(tag, filename, isNormalized, defaultMaterial);
		SetModel(tag);
	}

	else if (!tag.empty())
	{
		SetModel(tag);
	}
}
//======================================================================================================
const glm::vec3& Model::GetDimension() const
{
	return m_dimension;
}
//======================================================================================================
void Model::SetModel(const std::string& tag)
{
	auto it = s_models.find(tag);
	assert(it != s_models.end());
	*this = it->second;
}
//======================================================================================================
void Model::SetColor(const glm::vec4& color)
{
	SetColor(color.r, color.g, color.b, color.a);
}
//======================================================================================================
void Model::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	auto count = 0;
	for (auto& mesh : m_meshes)
	{
		for (auto& color : mesh.colors)
		{
			glm::vec4 newColor(r, g, b, a);
			color = newColor;
		}

		m_buffers[count++].FillVBO(Buffer::VBO::ColorBuffer, &mesh.colors[0].x,
			mesh.colors.size() * sizeof(glm::vec4));
	}
}
//======================================================================================================
void Model::FillBuffers(Model& model)
{
	//We have to create separate buffer objects if the .obj file data has separate groups
	//because of how the indices have been set up. Single group models will use one buffer
	//We can use one buffer for all data but then the indices have to be calculated differently
	for (auto& mesh : model.m_meshes)
	{
		//TODO - Need to label each buffer object properly
		static auto count = 0;

		Buffer buffer("Mesh_" + std::to_string(count++), mesh.indices.size(), true);

		buffer.FillEBO(&mesh.indices[0], mesh.indices.size() * sizeof(GLuint));
		buffer.FillVBO(Buffer::VBO::VertexBuffer,
			&mesh.vertices[0].x, mesh.vertices.size() * sizeof(glm::vec3));
		buffer.FillVBO(Buffer::VBO::NormalBuffer,
			&mesh.normals[0].x, mesh.normals.size() * sizeof(glm::vec3));

		//Fill the color buffer with a default white color 
		//For each vertex in the mesh there is a color value
		for (const auto& vertex : mesh.vertices)
		{
			glm::vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
			mesh.colors.push_back(color);
		}

		buffer.FillVBO(Buffer::VBO::ColorBuffer,
			&mesh.colors[0].x, mesh.colors.size() * sizeof(glm::vec4));

		if (!mesh.textureCoords.empty())
		{
			buffer.FillVBO(Buffer::VBO::TextureBuffer,
				&mesh.textureCoords[0].x, mesh.textureCoords.size() * sizeof(glm::vec2));
		}

		model.m_buffers.push_back(buffer);
	}
}
//======================================================================================================
void Model::SortVertexData(Mesh& newMesh, const Mesh& oldMesh, const std::vector<Face>& faces)
{
	GLuint count = 0;
	std::unordered_map<VertexGroup, GLuint, HashFunction> map;

	//Because the .obj file does not have any EBO data or any indices
	//this needs to be manually created. The raw .obj data will consist
	//of different amounts of vertex, UV and normal data. To use an EBO
	//we need to make sure the v/t/n VBO buffer sizes are all equal
	for (const auto& face : faces)
	{
		//We need to loop through all three v/t/n groupings for each face
		//because all three v/t/n groupings together make up a face triangle
		//We then see if the grouping is already in the map because groupings
		//can duplicate in the .obj. For example we could have 2/2/2 in the
		//.obj file multiple times, so we don't want to store duplicates
		for (auto i = 0; i < 3; i++)
		{
			auto it = map.find(face[i]);

			if (it == map.end())
			{
				glm::vec3 v = oldMesh.vertices[face[i].v];
				newMesh.vertices.push_back(v);

				//Some .obj files do not have texture coordinates 
				if (!oldMesh.textureCoords.empty())
				{
					newMesh.textureCoords.push_back(oldMesh.textureCoords[face[i].t]);
				}

				newMesh.normals.push_back(oldMesh.normals[face[i].n]);
				newMesh.indices.push_back(count);

				map[face[i]] = count;

				count++;

				if (count % 10 == 0)
				{
					map.clear();
				}
			}

			else
			{
				newMesh.indices.push_back(it->second);
			}
		}
	}
}
//======================================================================================================
void Model::Render(Shader& shader)
{
	assert(!m_tag.empty());

	m_normalMatrix = glm::inverse(glm::mat3(m_transform.GetMatrix()));
	shader.SendData("normal", m_normalMatrix, true);
	shader.SendData("model", m_transform.GetMatrix());

	auto count = 0;
	for (auto& mesh : m_meshes)
	{
		m_buffers[count].LinkEBO();
		m_buffers[count].LinkVBO(shader.GetAttributeID("vertexIn"),
			Buffer::VBO::VertexBuffer, Buffer::ComponentSize::XYZ, Buffer::DataType::FloatData);
		m_buffers[count].LinkVBO(shader.GetAttributeID("colorIn"),
			Buffer::VBO::ColorBuffer, Buffer::ComponentSize::RGBA, Buffer::DataType::FloatData);
		m_buffers[count].LinkVBO(shader.GetAttributeID("textureIn"),
			Buffer::VBO::TextureBuffer, Buffer::ComponentSize::UV, Buffer::DataType::FloatData);
		m_buffers[count].LinkVBO(shader.GetAttributeID("normalIn"),
			Buffer::VBO::NormalBuffer, Buffer::ComponentSize::XYZ, Buffer::DataType::FloatData);

		Material material;

		for (auto mat : m_material.GetGroup())
		{
			if (mat.GetName() == mesh.materialName)
			{
				material = mat;
				break;
			}
		}

		material.SendToShader(shader);

		if (material.IsTextured())
		{
			shader.SendData("isTextured", true);
			material.GetDiffuseMap().Bind();
		}

		else
		{
			shader.SendData("isTextured", false);
		}

		m_buffers[count++].Render(Buffer::RenderMode::Triangles);
	}
}
//======================================================================================================
void Model::Unload(const std::string& tag)
{
	if (!tag.empty())
	{
		auto it = s_models.find(tag);
		assert(it != s_models.end());

		for (auto& buffer : it->second.m_buffers)
		{
			Buffer::Destroy(buffer.GetTag());
		}

		Material::Unload(it->second.m_material.GetTag());
		s_models.erase(it);
	}

	else
	{
		for (auto& model : s_models)
		{
			for (auto& buffer : model.second.m_buffers)
			{
				Buffer::Destroy(buffer.GetTag());
			}

			Material::Unload(model.second.m_material.GetTag());
		}

		s_models.clear();
	}
}
//======================================================================================================
void Model::SetRootFolder(const std::string& rootFolder)
{
	s_rootFolder = rootFolder;
}
//======================================================================================================
void Model::Normalize(Model& model)
{
	glm::vec3 minValues = glm::vec3(0.0f);
	glm::vec3 maxValues = glm::vec3(0.0f);

	for (const auto& mesh : model.m_meshes)
	{
		for (const auto& vertex : mesh.vertices)
		{
			maxValues = glm::max(maxValues, vertex);
			minValues = glm::min(minValues, vertex);
		}
	}

	glm::vec3 length = maxValues - minValues;

	if (length == glm::vec3(0.0f))
	{
		return;
	}

	auto fraction = (1.0f / glm::max(glm::max(length.x, length.y), length.z));

	for (auto& mesh : model.m_meshes)
	{
		for (auto& vertex : mesh.vertices)
		{
			vertex *= fraction;
		}
	}
}
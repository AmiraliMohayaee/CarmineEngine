#include "Model.h"
#include "Debug.h"
#include "Tools.h"
#include <fstream>
#include <iostream>




bool Model::Load(const std::string& filename)
{

    std::fstream file(filename.c_str(), std::ios_base::in);

    if (!file)
    {
        Debug::Log("Error loading " + filename);
        return false;
    }

    std::string line;
    std::vector<std::string> lines;

    while (!file.eof())
    {
        std::getline(file, line);
        lines.push_back(line);
    }

    file.close();

    Mesh rawMesh;
    std::string lastName;
    std::vector<Face> faces;

    //Loop through all raw lines of data and break up the data into meaningful segments
    for (size_t i = 0; i < lines.size(); i++)
    {

        if (!lines[i].empty() && lines[i][0] != '#')
        {

            std::vector<std::string> subStrings;
            Tools::ParseString(lines[i], subStrings, ' ');

            //Vertices
            if (subStrings[0] == "v")
            {
                rawMesh.vertices.push_back(glm::vec3(std::stof(subStrings[1]),
                    std::stof(subStrings[2]),
                    std::stof(subStrings[3])));
                continue;
            }

            //UVs
            if (subStrings[0] == "vt")
            {
                rawMesh.UVs.push_back(glm::vec2(std::stof(subStrings[1]),
                    std::stof(subStrings[2])));
                continue;
            }

            //Normals
            if (subStrings[0] == "vn")
            {
                rawMesh.normals.push_back(glm::vec3(std::stof(subStrings[1]),
                    std::stof(subStrings[2]),
                    std::stof(subStrings[3])));
                continue;
            }

            //This is the line of face indices that contains data in 'v/t/n v/t/n v/t/n' format
            //This data together will make up a polygon face or triangle using the vtn indices
            //The data will be stored as v = subString[1], t = subString[2] and n = subString[3] 
            if (subStrings[0] == "f")
            {
                Face face;

                for (size_t i = 1; i <= 3; i++)
                {
                    VertexGroup vertexGroup;
                    std::vector<std::string> numbers;
                    Tools::ParseString(subStrings[i], numbers, '/');

                    vertexGroup.v = std::stoi(numbers[0]) - 1;
                    vertexGroup.t = std::stoi(numbers[1]) - 1;
                    vertexGroup.n = std::stoi(numbers[2]) - 1;

                    face.push_back(vertexGroup);
                }

                faces.push_back(face);
                continue;
            }

            if (subStrings[0] == "g" || subStrings[0] == "o")
            {
                if (!faces.empty())
                {
                    Mesh mesh;
                    mesh.name = lastName;
                    SortVertexData(mesh, rawMesh, faces);
                }

                lastName = subStrings[1];
                faces.clear();
                continue;
            }

            //These are the smoothing groups
            if (subStrings[0] == "s")
            {
                //TODO
            }

            //This is the name of the material to use for the group 
            //All materials are found in the subsequent .mtl file
            if (subStrings[0] == "usemtl")
            {
                //TODO
            }

            //This indicates the name of the .mtl file to use for the mesh 
            //group. All materials are found in the subsequent material file 
            if (subStrings[0] == "mtllib")
            {
                //TODO
            }

        }
    }

    //We do one more final clean-up of the raw data because v/t/n data is
    //usually read in AFTER a group name so the final data group needs sorting
    if (!faces.empty())
    {
        Mesh mesh;
        mesh.name = lastName;
        SortVertexData(mesh, rawMesh, faces);
    }

    FillBuffers();
    return true;
}


void Model::Render()
{
    Shader::Instance()->SendUniformData("isLit", false);
    Shader::Instance()->SendUniformData("isTextured", false);

    m_modelMatrix = glm::mat4(1.0f);

    Shader::Instance()->SendUniformData("model", m_modelMatrix);

    for (size_t i = 0; i < m_buffers.size(); i++)
    {
        m_buffers[i].Render(Buffer::TRIANGLES);
    }
}

void Model::Unload()
{
    for (size_t i = 0; i < m_buffers.size(); i++)
    {
        m_buffers[i].Destroy();
    }
}


void Model::FillBuffers()
{
    for (size_t i = 0; i < m_meshes.size(); i++)
    {
        Buffer buffer;

        buffer.Create(m_meshes[i].indices.size(), true);

        buffer.LinkEBO();
        buffer.LinkVBO("vertexIn", Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
        buffer.LinkVBO("colorIn", Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);
        buffer.LinkVBO("textureIn", Buffer::TEXTURE_BUFFER, Buffer::UV, Buffer::FLOAT);
        buffer.LinkVBO("normalIn", Buffer::NORMAL_BUFFER, Buffer::XYZ, Buffer::FLOAT);

        buffer.FillEBO(m_meshes[i].indices.data(), m_meshes[i].indices.size() * sizeof(GLuint), Buffer::SINGLE);
        buffer.FillVBO(Buffer::VERTEX_BUFFER, &m_meshes[i].vertices[0].x, m_meshes[i].vertices.size() * sizeof(glm::vec3), Buffer::SINGLE);

        for (size_t j = 0; j < m_meshes[i].vertices.size(); j++)
        {
            glm::vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
            m_meshes[i].colors.push_back(color);
        }

        buffer.FillVBO(Buffer::COLOR_BUFFER, &m_meshes[i].colors[0].x, m_meshes[i].colors.size() * sizeof(glm::vec4), Buffer::SINGLE);
        buffer.FillVBO(Buffer::TEXTURE_BUFFER, &m_meshes[i].UVs[0].x, m_meshes[i].UVs.size() * sizeof(glm::vec2), Buffer::SINGLE);
        buffer.FillVBO(Buffer::NORMAL_BUFFER, &m_meshes[i].normals[0].x, m_meshes[i].normals.size() * sizeof(glm::vec3), Buffer::SINGLE);

        m_buffers.push_back(buffer);
    }
}

void Model::SortVertexData(Mesh& newMesh, const Mesh& oldMesh, const std::vector<Face>& faces)
{
    GLuint count = 0;
    std::map<VertexGroup, GLuint> map;

    for (size_t i = 0; i < faces.size(); i++)
    {

        for (size_t j = 0; j < 3; j++)
        {

            auto it = map.find(faces[i][j]);

            if (it == map.end())
            {
                newMesh.vertices.push_back(oldMesh.vertices[faces[i][j].v]);
                newMesh.UVs.push_back(oldMesh.UVs[faces[i][j].t]);
                newMesh.normals.push_back(oldMesh.normals[faces[i][j].n]);
                newMesh.indices.push_back(count);

                map[faces[i][j]] = count++;
            }

            else
            {
                newMesh.indices.push_back(it->second);
            }

        }

    }

    m_meshes.push_back(newMesh);
}

#include "Mesh.hpp"
#include <Rendering/OpenGL.hpp>
#include <ResourceManagement/ObjLoader.hpp>
#include <ResourceManagement/MeshManager.hpp>
#include <vector>

namespace atom
{
	Mesh::Mesh(Vertex* vertices, unsigned int numVerts, unsigned int* indices, unsigned int numIndices)
	{
		IndexedModel model;

		for (unsigned int i = 0; i < numVerts; i++)
		{
			model.positions.push_back(vertices[i].position);
			model.texCoords.push_back(vertices[i].texCoord);
			model.normals.push_back(vertices[i].normal);
			model.tangents.push_back(vertices[i].tangent);
		}

		for (unsigned int i = 0; i < numIndices; i++)
			model.indices.push_back(indices[i]);

		model.CalcNormals();
		model.CalcTangentSpace();
		
		InitMesh(model);
	}

	Mesh::Mesh(const std::string& filename)
	{
		IndexedModel model = OBJModel(filename).ToIndexedModel();
		InitMesh(model);
	}

	Mesh::~Mesh()
	{
		GLCall(glDeleteVertexArrays(1, &vertexArrayObject));
		GLCall(glDeleteBuffers(NUM_BUFFERS, vertexArrayBuffers));
		
		MeshManager::DeleteInstance(name);
	}

	void Mesh::InitMesh(const IndexedModel& model)
	{
		GLCall(glGenVertexArrays(1, &vertexArrayObject));
		GLCall(glBindVertexArray(vertexArrayObject));

		drawCount = model.indices.size();
		GLCall(glGenBuffers(NUM_BUFFERS, vertexArrayBuffers));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]));
		GLCall(glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW));
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]));
		GLCall(glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW));
		GLCall(glEnableVertexAttribArray(1));
		GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW));
		GLCall(glEnableVertexAttribArray(2));
		GLCall(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TANGENT_VB]));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(model.tangents[0]) * model.tangents.size(), &model.tangents[0], GL_STATIC_DRAW));
		GLCall(glEnableVertexAttribArray(3));
		GLCall(glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0));

		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW));
		
		GLCall(glBindVertexArray(0));
	}

	void Mesh::Draw() const
	{
		GLCall(glBindVertexArray(vertexArrayObject));
		GLCall(glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0));
		GLCall(glBindVertexArray(0));
	}
}

#pragma once

#include <ResourceManagement/IndexedModel.hpp>
#include <Rendering/Vertex.hpp>
#include <string>
#include <unordered_map>

namespace atom
{
	class Mesh
	{
	private:

		enum
		{
			POSITION_VB,
			TEXCOORD_VB,
			NORMAL_VB,
			TANGENT_VB,
			INDEX_VB,
			NUM_BUFFERS
		};

		unsigned int vertexArrayObject;
		unsigned int vertexArrayBuffers[NUM_BUFFERS];
		unsigned int drawCount;
		std::string name;

		Mesh(const std::string& filename);
		Mesh(Vertex* vertices, unsigned int numVerts, unsigned int* indices, unsigned int numIndices);
		void InitMesh(const IndexedModel& model);

	public:
		virtual ~Mesh();
		void Draw() const;

		friend class MeshManager;
	};
}

#pragma once

namespace aquarium
{
	namespace render
	{
		namespace obj
		{
			struct Vertex
			{
				glm::vec3 m_pos;
				glm::vec3 m_nml;
				glm::vec2 m_tex;
			};

			using VertexArray = std::vector< Vertex >;
			using PositionArray = std::vector< glm::vec3 >;
			using NormalArray = std::vector< glm::vec3 >;
			using TexCoordArray = std::vector< glm::vec2 >;
			using FaceArray = std::vector< glm::ivec3 >;
			using UIntUInt64Map = std::map< uint64_t, uint32_t >;

			struct Submesh
			{
				VertexArray m_vertex;
				FaceArray m_faces;
				gl::Material * m_material{ nullptr };
				gl::Buffer m_vbo;
				gl::Buffer m_ibo;

				bool initialise();
				void cleanup();
			};

			using SubmeshArray = std::vector< Submesh >;

			struct Mesh
			{
				std::string m_name;
				SubmeshArray m_submeshes;
				gl::MaterialMap m_materials;

				bool initialise();
				void cleanup();
			};
		}
	}
}

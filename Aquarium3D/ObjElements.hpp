#pragma once

#include <map>

namespace aquarium
{
	namespace render
	{
		using ByteArray = std::vector< uint8_t >;

		namespace obj
		{
			struct Texture
			{
				std::string m_file;
				glm::ivec2 m_dimensions;
				ByteArray m_data;
				uint32_t m_glname{ GL_INVALID_INDEX };
				uint32_t m_format{ GL_RGBA };

				bool initialise();
				void cleanup();
			};

			struct Material
			{
				glm::vec4 m_ambientColour;
				glm::vec4 m_diffuseColour;
				glm::vec4 m_emissiveColour;
				glm::vec4 m_specularColour;
				float m_exponentValue{ 128.0f };
				float m_opacity{ 1.0f };
				Texture m_ambientTexture;
				Texture m_diffuseTexture;
				Texture m_emissiveTexture;
				Texture m_specularTexture;

				bool initialise();
				void cleanup();
			};

			struct Vertex
			{
				glm::vec3 m_pos;
				glm::vec3 m_nml;
				glm::vec2 m_tex;
			};

			struct VertexInfos
			{
				bool m_hasNml{ false };
				bool m_hasTex{ false };
			};

			using MaterialMap = std::map< std::string, Material >;
			using VertexArray = std::vector< Vertex >;
			using PositionArray = std::vector< glm::vec3 >;
			using NormalArray = std::vector< glm::vec3 >;
			using TexCoordArray = std::vector< glm::vec2 >;
			using FaceArray = std::vector< glm::ivec3 >;
			using UIntUInt64Map = std::map< uint64_t, uint32_t >;

			struct Submesh
			{
				uint32_t m_id{ 0 };
				bool m_hasNormals{ false };
				std::string m_name;
				VertexArray m_vertex;
				FaceArray m_faces;
				Material m_material;
				UIntUInt64Map m_vtxIndices;
				uint32_t m_vboName{ GL_INVALID_INDEX };
				uint32_t m_iboName{ GL_INVALID_INDEX };

				bool initialise();
				void cleanup();
			};

			using SubmeshArray = std::vector< Submesh >;

			struct Mesh
			{
				std::string m_name;
				SubmeshArray m_submeshes;

				bool initialise();
				void cleanup();
			};
		}
	}
}

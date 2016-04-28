#pragma once

namespace aquarium
{
	namespace render
	{
		using ByteArray = std::vector< uint8_t >;

		namespace gl
		{
			struct Texture
			{
				std::string m_file;
				glm::ivec2 m_dimensions;
				ByteArray m_data;
				uint32_t m_glName{ GL_INVALID_INDEX };
				uint32_t m_format{ GL_RGBA };
				uint32_t m_internal{ GL_RGBA };

				bool initialise();
				void cleanup();
				bool bind( uint32_t index );
				void unbind( uint32_t index );
			};

			struct Buffer
			{
				uint32_t m_target{ 0 };
				uint32_t m_glName{ GL_INVALID_INDEX };

				bool initialise( uint32_t target, void const * data, size_t size );
				void cleanup();
				bool bind();
				void unbind();
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
				bool bind();
				void unbind();
			};

			using MaterialMap = std::map< std::string, gl::Material >;
		}
	}
}

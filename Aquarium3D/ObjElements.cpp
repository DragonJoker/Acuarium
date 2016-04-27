#include "Prerequisites.hpp"

namespace aquarium
{
	namespace render
	{
		namespace obj
		{
			//************************************************************************************************

			bool Texture::initialise()
			{
				bool ret = true;

				if ( !m_data.empty() )
				{
					glGenTextures( 1, &m_glname );
					assert( m_glname != GL_INVALID_INDEX );
					glBindTexture( GL_TEXTURE_2D, m_glname );
					checkGlError( "glBindTexture" );
					glActiveTexture( GL_TEXTURE_2D );
					checkGlError( "glActiveTexture" );
					glTexImage2D( GL_TEXTURE_2D, 0, m_format, m_dimensions.x, m_dimensions.y, 0, m_format, GL_UNSIGNED_BYTE, m_data.data() );
					checkGlError( "glTexImage2D" );
					glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
					checkGlError( "glTexParameterf GL_TEXTURE_MIN_FILTER" );
					glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
					checkGlError( "glTexParameterf GL_TEXTURE_MAG_FILTER" );
					glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
					checkGlError( "glTexParameterf GL_TEXTURE_WRAP_S" );
					glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
					checkGlError( "glTexParameterf GL_TEXTURE_WRAP_T" );
					glBindTexture( GL_TEXTURE_2D, 0 );
					return checkGlError( "Texture initialisation" );
				}

				return ret;
			}

			void Texture::cleanup()
			{
				glDeleteTextures( 1, &m_glname );
			}

			//************************************************************************************************

			bool Material::initialise()
			{
				return m_ambientTexture.initialise()
					&& m_diffuseTexture.initialise()
					&& m_emissiveTexture.initialise()
					&& m_specularTexture.initialise();
			}

			void Material::cleanup()
			{
				m_ambientTexture.cleanup();
				m_diffuseTexture.cleanup();
				m_emissiveTexture.cleanup();
				m_specularTexture.cleanup();
			}

			//************************************************************************************************

			bool Submesh::initialise()
			{
				glGenBuffers( 1, &m_vboName );
				assert( m_vboName != GL_INVALID_INDEX );
				glBindBuffer( GL_ARRAY_BUFFER, m_vboName );
				glBufferData( GL_ARRAY_BUFFER, m_vertex.size() * sizeof( obj::Vertex ), m_vertex.data(),  GL_STATIC_DRAW );
				glBindBuffer( GL_ARRAY_BUFFER, 0 );
				bool ret = checkGlError( "VBO filling" );
				glGenBuffers( 1, &m_iboName );
				assert( m_iboName != GL_INVALID_INDEX );
				glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_iboName );
				glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_faces.size() * sizeof( glm::ivec3 ), m_faces.data(),  GL_STATIC_DRAW );
				glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
				ret &= checkGlError( "IBO filling" );
				return ret && m_material.initialise();
			}

			void Submesh::cleanup()
			{
				glDeleteBuffers( 1, &m_vboName );
				glDeleteBuffers( 1, &m_iboName );
			}

			//************************************************************************************************

			bool Mesh::initialise()
			{
				bool ret = true;

				for ( auto & submesh : m_submeshes )
				{
					if ( ret )
					{
						ret = submesh.initialise();
					}
				}

				return ret;
			}

			void Mesh::cleanup()
			{
				for ( auto & submesh : m_submeshes )
				{
					submesh.cleanup();
				}
			}

			//************************************************************************************************
		}
	}
}

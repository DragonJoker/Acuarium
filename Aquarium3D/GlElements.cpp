#include "Prerequisites.hpp"

namespace aquarium
{
	namespace render
	{
		namespace gl
		{
			//************************************************************************************************

			bool Texture::initialise()
			{
				bool ret = true;

				if ( !m_data.empty() )
				{
					ret = false;
					glGenTextures( 1, &m_glName );

					if ( bind( 0 ) )
					{
						glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
						glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
						glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
						glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
						glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
						glTexImage2D( GL_TEXTURE_2D, 0, m_internal, m_dimensions.x, m_dimensions.y, 0, m_format, GL_UNSIGNED_BYTE, m_data.data() );
						unbind( 0 );
						ret = checkGlError( "Texture initialisation" );
					}
				}

				return ret;
			}

			void Texture::cleanup()
			{
				assert( m_glName != GL_INVALID_INDEX );
				glDeleteTextures( 1, &m_glName );
			}

			bool Texture::bind( uint32_t index )
			{
				assert( m_glName != GL_INVALID_INDEX );
				glActiveTexture( GL_TEXTURE0 + index );
				glBindTexture( GL_TEXTURE_2D, m_glName );
				return checkGlError( "glBindTexture" );
			}

			void Texture::unbind( uint32_t index )
			{
				glActiveTexture( GL_TEXTURE0 + index );
				glBindTexture( GL_TEXTURE_2D, 0 );
			}

			//************************************************************************************************

			bool Buffer::initialise( uint32_t target, void const * data, size_t size )
			{
				bool ret = false;
				m_target = target;
				glGenBuffers( 1, &m_glName );
				assert( m_glName != GL_INVALID_INDEX );

				if ( bind() )
				{
					glBufferData( m_target, size, data,  GL_STATIC_DRAW );
					unbind();
					ret = checkGlError( "Buffer initialisation" );
				}

				return ret;
			}

			void Buffer::cleanup()
			{
				assert( m_glName != GL_INVALID_INDEX );
				glDeleteBuffers( 1, &m_glName );
			}

			bool Buffer::bind()
			{
				assert( m_glName != GL_INVALID_INDEX );
				glBindBuffer( m_target, m_glName );
				return checkGlError( "glBindBuffer" );
			}

			void Buffer::unbind()
			{
				glBindBuffer( m_target, 0 );
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
		}
	}
}

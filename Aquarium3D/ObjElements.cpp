#include "Prerequisites.hpp"

#include "TgaLoader.hpp"

namespace aquarium
{
	namespace render
	{
		namespace obj
		{
			//************************************************************************************************

			bool Submesh::initialise()
			{
				return m_vbo.initialise( GL_ARRAY_BUFFER, m_vertex.data(), m_vertex.size() * sizeof( Vertex ) )
					&& m_ibo.initialise( GL_ELEMENT_ARRAY_BUFFER, m_faces.data(), m_faces.size() * sizeof( glm::ivec3 ) );
			}

			void Submesh::cleanup()
			{
				m_vbo.cleanup();
				m_ibo.cleanup();
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

				for ( auto & it : m_materials )
				{
					if ( ret )
					{
						ret = it.second.initialise();
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

				for ( auto & it : m_materials )
				{
					it.second.cleanup();
				}
			}

			//************************************************************************************************
		}
	}
}

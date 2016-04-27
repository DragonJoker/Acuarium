#pragma once

#include "Prerequisites.hpp"

#include <memory>

namespace aquarium
{
	namespace render
	{
		namespace obj
		{
			struct Context
			{
				Context( std::string const & folder )
					: folder( folder )
				{
				}

				std::string const folder;
				Mesh mesh;
				MaterialMap loadedMaterials;
			};

			class Importer
			{
			public:
				Mesh importMesh( std::string const & filePath );
				bool importMeshAsync( std::string const & filePath );
				Mesh waitMesh();

			private:
				void doReadObjFile( std::string const & filePath, Context & context );
				uint32_t doProcessFace( std::string const & value, Submesh & submesh, PositionArray const & arrayPos, NormalArray const & arrayNml, TexCoordArray const & arrayTex );
				uint32_t doRetrieveIndex( std::string & str, uint32_t size );
				void doReadMaterials( std::string const & mtlFilePath, Context & context );
				void doAddTexture( std::string const & value, Texture & texture, Context & context );

			private:
				std::unique_ptr< Context > m_asyncContext;
				std::unique_ptr< std::thread > m_asyncLoader;
			};
		}
	}
}

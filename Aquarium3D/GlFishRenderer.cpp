#include "GlFishRenderer.hpp"

#include "ObjImporter.hpp"

#include <thread>

namespace aquarium
{
	namespace render
	{
		GlFishRenderer::GlFishRenderer()
		{
			std::array< std::string, RaceCount > const files
			{
				"../share/Aquarium3D/grouper/grouper.obj",
				"../share/Aquarium3D/tuna/tuna.obj",
				"../share/Aquarium3D/clown/clown.obj",
				"../share/Aquarium3D/ray/ray.obj",
				"../share/Aquarium3D/bass/bass.obj",
				"../share/Aquarium3D/carp/carp.obj"
			};

			std::array< obj::Importer, RaceCount > importers;
			auto index = 0u;

			for ( auto & importer : importers )
			{
				importer.importMeshAsync( files[index++] );
			}

			index = 0u;

			for ( auto & importer : importers )
			{
				m_meshes[index++] = importer.waitMesh();
			}
		}

		GlFishRenderer::~GlFishRenderer ()
		{
			for ( auto & mesh : m_meshes )
			{
				mesh.cleanup();
			}
		}

		void GlFishRenderer::doRender( Fish const & fish )
		{
		}

		void GlFishRenderer::doRenderBorn( Fish const & fish, Fish const & lhs, Fish const & rhs )
		{
		}

		void GlFishRenderer::doRenderDie( Fish const & fish )
		{
		}

		void GlFishRenderer::doRenderEat( Fish const & fish, Fish const & prey )
		{
		}

		void GlFishRenderer::doRenderEat( Fish const & fish, Seaweed const & prey )
		{
		}

		void GlFishRenderer::doRenderNoFood( Fish const & fish )
		{
		}

		void GlFishRenderer::doRenderNoMate( Fish const & fish )
		{
		}

		void GlFishRenderer::doRenderWrongMate( Fish const & fish, Fish const & mate )
		{
		}

		void GlFishRenderer::doRenderSwitchGender( Fish const & fish, Gender gender )
		{
		}
	}
}

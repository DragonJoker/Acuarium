#include "GlAquariumRenderer.hpp"

#include <Aquarium.hpp>

#include "GlFishRenderer.hpp"
#include "GlSeaweedRenderer.hpp"

#include "ObjImporter.hpp"

namespace aquarium
{
	namespace render
	{
		GlAquariumRenderer::GlAquariumRenderer( aquarium::Aquarium const & aqua )
			: AquariumRenderer{ aqua, std::make_unique< GlFishRenderer >(), std::make_unique< GlSeaweedRenderer >() }
			, m_glFishRenderer{ static_cast< GlFishRenderer & >( *m_fishRenderer ) }
			, m_glSeaweedRenderer{ static_cast< GlSeaweedRenderer & >( *m_seaweedRenderer ) }
			, m_mesh{ obj::Importer{}.importMesh( "../share/Aquarium3D/aquarium/aquarium.obj" ) }
		{
		}
		
		GlAquariumRenderer::~GlAquariumRenderer()
		{
		}

		void GlAquariumRenderer::doPreRender( uint32_t turn )
		{
		}

		void GlAquariumRenderer::doRender()
		{
		}
	}
}

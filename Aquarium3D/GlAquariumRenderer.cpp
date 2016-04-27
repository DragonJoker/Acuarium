#include "GlAquariumRenderer.hpp"

#include <Aquarium.hpp>

#include "GlFishRenderer.hpp"
#include "GlSeaweedRenderer.hpp"

#include "ObjImporter.hpp"

#if defined( _WIN32 )
#include "Windows.h"
#endif

#include <gl/GL.h>

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

		void GlAquariumRenderer::doRender( uint32_t turn )
		{
		}

		void GlAquariumRenderer::doOnFishBorn( Fish const & fish, Fish const & lhs, Fish const & rhs )
		{
			m_glFishRenderer.renderBorn( fish, lhs, rhs );
		}

		void GlAquariumRenderer::doOnFishDie( Fish const & fish )
		{
			m_glFishRenderer.renderDie( fish );
		}

		void GlAquariumRenderer::doOnFishEatFish( Fish const & fish, Fish const & prey )
		{
			m_glFishRenderer.renderEat( fish, prey );
		}

		void GlAquariumRenderer::doOnFishEatSeaweed( Fish const & fish, Seaweed const & prey )
		{
			m_glFishRenderer.renderEat( fish, prey );
		}

		void GlAquariumRenderer::doOnFishNoFood( Fish const & fish )
		{
			m_glFishRenderer.renderNoFood( fish );
		}

		void GlAquariumRenderer::doOnFishNoMate( Fish const & fish )
		{
			m_glFishRenderer.renderNoMate( fish );
		}

		void GlAquariumRenderer::doOnFishWrongMate( Fish const & fish, Fish const & mate )
		{
			m_glFishRenderer.renderWrongMate( fish, mate );
		}

		void GlAquariumRenderer::doOnFishSwitchGender( Fish const & fish, Gender gender )
		{
			m_glFishRenderer.renderSwitchGender( fish, gender );
		}

		void GlAquariumRenderer::doOnSeaweedBorn( Seaweed const & seaweed, Seaweed const & parent )
		{
			m_glSeaweedRenderer.renderBorn( seaweed, parent );
		}

		void GlAquariumRenderer::doOnSeaweedDie( Seaweed const & seaweed )
		{
			m_glSeaweedRenderer.renderDie( seaweed );
		}
	}
}

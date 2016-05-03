#include "SeaweedRenderer.hpp"

namespace aquarium
{
	namespace render
	{
		SeaweedRenderer::SeaweedRenderer()
		{
		}

		SeaweedRenderer::~SeaweedRenderer()
		{
		}

		void SeaweedRenderer::render( Seaweed const & seaweed )
		{
			doRender( seaweed );
		}

		void SeaweedRenderer::renderBorn( Seaweed const & seaweed, Seaweed const & parent )
		{
			doRenderBorn( seaweed, parent );
		}

		void SeaweedRenderer::renderDie( Seaweed const & seaweed )
		{
			doRenderDie( seaweed );
		}
	}
}

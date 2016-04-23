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
	}
}

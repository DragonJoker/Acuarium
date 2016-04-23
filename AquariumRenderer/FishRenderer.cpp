#include "FishRenderer.hpp"

namespace aquarium
{
	namespace render
	{
		FishRenderer::FishRenderer()
		{
		}

		FishRenderer::~FishRenderer()
		{
		}

		void FishRenderer::render( Fish const & fish )
		{
			doRender( fish );
		}
	}
}

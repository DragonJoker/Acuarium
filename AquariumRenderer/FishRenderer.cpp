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

		void FishRenderer::renderBorn( Fish const & fish, Fish const & lhs, Fish const & rhs )
		{
			doRenderBorn( fish, lhs, rhs );
		}

		void FishRenderer::renderDie( Fish const & fish )
		{
			doRenderDie( fish );
		}

		void FishRenderer::renderEat( Fish const & fish, Fish const & prey )
		{
			doRenderEat( fish, prey );
		}

		void FishRenderer::renderEat( Fish const & fish, Seaweed const & prey )
		{
			doRenderEat( fish, prey );
		}

		void FishRenderer::renderNoFood( Fish const & fish )
		{
			doRenderNoFood( fish );
		}

		void FishRenderer::renderNoMate( Fish const & fish )
		{
			doRenderNoMate( fish );
		}

		void FishRenderer::renderWrongMate( Fish const & fish, Fish const & mate )
		{
			doRenderWrongMate( fish, mate );
		}

		void FishRenderer::renderSwitchGender( Fish const & fish, Gender gender )
		{
			doRenderSwitchGender( fish, gender );
		}
	}
}

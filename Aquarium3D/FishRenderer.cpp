#include "FishRenderer.hpp"

namespace aquarium
{
	namespace render
	{
		GlFishRenderer::GlFishRenderer()
		{
		}

		GlFishRenderer::~GlFishRenderer ()
		{
		}

		void GlFishRenderer::doRender( Fish const & fish )
		{
		}

		void GlFishRenderer::renderBorn( Fish const & fish, Fish const & lhs, Fish const & rhs )
		{
		}

		void GlFishRenderer::renderDie( Fish const & fish )
		{
		}

		void GlFishRenderer::renderEat( Fish const & fish, Fish const & prey )
		{
		}

		void GlFishRenderer::renderEat( Fish const & fish, Seaweed const & prey )
		{
		}

		void GlFishRenderer::renderNoFood( Fish const & fish )
		{
		}

		void GlFishRenderer::renderNoMate( Fish const & fish )
		{
		}

		void GlFishRenderer::renderWrongMate( Fish const & fish, Fish const & mate )
		{
		}

		void GlFishRenderer::renderSwitchGender( Fish const & fish, Gender gender )
		{
		}
	}
}

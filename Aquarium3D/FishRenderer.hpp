#pragma once

#include "Prerequisites.hpp"
#include <FishRenderer.hpp>

namespace aquarium
{
	namespace render
	{
		class GlFishRenderer
			: public FishRenderer
		{
		public:
			GlFishRenderer();
			~GlFishRenderer();

			void renderBorn( Fish const & fish, Fish const & lhs, Fish const & rhs );
			void renderDie( Fish const & fish );
			void renderEat( Fish const & fish, Fish const & prey );
			void renderEat( Fish const & fish, Seaweed const & prey );
			void renderNoFood( Fish const & fish );
			void renderNoMate( Fish const & fish );
			void renderWrongMate( Fish const & fish, Fish const & mate );
			void renderSwitchGender( Fish const & fish, Gender gender );

		private:
			virtual void doRender( Fish const & fish );
		};
	}
}

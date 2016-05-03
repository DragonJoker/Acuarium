#pragma once

#include "AquariumRendererPrerequisites.hpp"

namespace aquarium
{
	namespace render
	{
		class FishRenderer
		{
		public:
			FishRenderer();
			~FishRenderer();

			void render( Fish const & fish );
			void renderBorn( Fish const & fish, Fish const & lhs, Fish const & rhs );
			void renderDie( Fish const & fish );
			void renderEat( Fish const & fish, Fish const & prey );
			void renderEat( Fish const & fish, Seaweed const & prey );
			void renderNoFood( Fish const & fish );
			void renderNoMate( Fish const & fish );
			void renderWrongMate( Fish const & fish, Fish const & mate );
			void renderSwitchGender( Fish const & fish, Gender gender );

		private:
			virtual void doRender( Fish const & fish ) = 0;
			virtual void doRenderBorn( Fish const & fish, Fish const & lhs, Fish const & rhs ) = 0;
			virtual void doRenderDie( Fish const & fish ) = 0;
			virtual void doRenderEat( Fish const & fish, Fish const & prey ) = 0;
			virtual void doRenderEat( Fish const & fish, Seaweed const & prey ) = 0;
			virtual void doRenderNoFood( Fish const & fish ) = 0;
			virtual void doRenderNoMate( Fish const & fish ) = 0;
			virtual void doRenderWrongMate( Fish const & fish, Fish const & mate ) = 0;
			virtual void doRenderSwitchGender( Fish const & fish, Gender gender ) = 0;
		};
	}
}

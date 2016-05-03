#pragma once

#include "AquariumRendererPrerequisites.hpp"

namespace aquarium
{
	namespace render
	{
		class SeaweedRenderer
		{
		public:
			SeaweedRenderer();
			~SeaweedRenderer();

			void render( Seaweed const & seaweed );
			void renderBorn( Seaweed const & seaweed, Seaweed const & parent );
			void renderDie( Seaweed const & seaweed );

		private:
			virtual void doRender( Seaweed const & seaweed ) = 0;
			virtual void doRenderBorn( Seaweed const & seaweed, Seaweed const & parent ) = 0;
			virtual void doRenderDie( Seaweed const & seaweed ) = 0;
		};
	}
}

#pragma once

#include "Prerequisites.hpp"

#include <SeaweedRenderer.hpp>

namespace aquarium
{
	namespace render
	{
		class GlSeaweedRenderer
			: public SeaweedRenderer
		{
		public:
			GlSeaweedRenderer();
			~GlSeaweedRenderer();

			void renderBorn( Seaweed const & seaweed, Seaweed const & parent );
			void renderDie( Seaweed const & fish );

		private:
			virtual void doRender( Seaweed const & seaweed );
		};
	}
}

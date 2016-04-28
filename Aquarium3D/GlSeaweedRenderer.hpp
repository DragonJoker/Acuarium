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

		private:
			virtual void doRender( Seaweed const & seaweed );
			virtual void doRenderBorn( Seaweed const & seaweed, Seaweed const & parent );
			virtual void doRenderDie( Seaweed const & seaweed );
		};
	}
}

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

		private:
			virtual void doRender( Seaweed const & seaweed ) = 0;
		};
	}
}

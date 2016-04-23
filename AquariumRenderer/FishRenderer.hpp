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

		private:
			virtual void doRender( Fish const & fish ) = 0;
		};
	}
}

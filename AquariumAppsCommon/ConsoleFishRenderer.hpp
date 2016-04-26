#include "AquariumAppsPrerequisites.hpp"

#include <FishRenderer.hpp>

namespace aquarium
{
	namespace render
	{
		class ConsoleFishRenderer
			: public FishRenderer
		{
		public:
			ConsoleFishRenderer() = default;
			~ConsoleFishRenderer() = default;

		private:
			virtual void doRender( Fish const & fish );
		};
	}
}

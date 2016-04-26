#include "AquariumAppsPrerequisites.hpp"

#include <SeaweedRenderer.hpp>

namespace aquarium
{
	namespace render
	{
		class ConsoleSeaweedRenderer
			: public SeaweedRenderer
		{
		public:
			ConsoleSeaweedRenderer() = default;
			~ConsoleSeaweedRenderer() = default;

		private:
			virtual void doRender( Seaweed const & seaweed );
		};
	}
}

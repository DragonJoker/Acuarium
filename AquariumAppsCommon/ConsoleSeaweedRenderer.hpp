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
			virtual void doRenderBorn( Seaweed const & seaweed, Seaweed const & parent );
			virtual void doRenderDie( Seaweed const & seaweed );
		};
	}
}

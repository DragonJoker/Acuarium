#include "AquariumAppsPrerequisites.hpp"

#include <AquariumRenderer.hpp>

namespace aquarium
{
	namespace render
	{
		class ConsoleAquariumRenderer
			: public AquariumRenderer
		{
		public:
			ConsoleAquariumRenderer( Aquarium const & aqua );
			~ConsoleAquariumRenderer() = default;

		private:
			virtual void doPreRender( uint32_t turn );
			virtual void doRender();
		};
	}
}

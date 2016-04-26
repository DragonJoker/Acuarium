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
			virtual void doRender( uint32_t turn );
			virtual void doOnFishBorn( Fish const & fish, Fish const & lhs, Fish const & rhs );
			virtual void doOnFishDie( Fish const & fish );
			virtual void doOnFishEatFish( Fish const & fish, Fish const & prey );
			virtual void doOnFishEatSeaweed( Fish const & fish, Seaweed const & prey );
			void doOnFishNoFood( Fish const & fish );
			void doOnFishNoMate( Fish const & fish );
			void doOnFishWrongMate( Fish const & fish, Fish const & mate );
			virtual void doOnFishSwitchGender( Fish const & fish, Gender gender );
			virtual void doOnSeaweedBorn( Seaweed const & seaweed, Seaweed const & parent );
			virtual void doOnSeaweedDie( Seaweed const & seaweed );
		};
	}
}

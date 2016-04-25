#pragma once

#include <AquariumRenderer.hpp>
#include "FishRenderer.hpp"
#include "SeaweedRenderer.hpp"

namespace aquarium
{
	namespace render
	{
		class GlAquariumRenderer
		  : public AquariumRenderer
		{
		public:
			GlAquariumRenderer( aquarium::Aquarium const & aqua );
			~GlAquariumRenderer();

		private:
			virtual void doPreRender( uint32_t turn );
			virtual void doRender( uint32_t turn );
			virtual void doOnFishBorn( Fish const & fish, Fish const & lhs, Fish const & rhs );
			virtual void doOnFishDie( Fish const & fish );
			virtual void doOnFishEatFish( Fish const & fish, Fish const & prey );
			virtual void doOnFishEatSeaweed( Fish const & fish, Seaweed const & prey );
			virtual void doOnFishNoFood( Fish const & fish );
			virtual void doOnFishNoMate( Fish const & fish );
			virtual void doOnFishWrongMate( Fish const & fish, Fish const & mate );
			virtual void doOnFishSwitchGender( Fish const & fish, Gender gender );
			virtual void doOnSeaweedBorn( Seaweed const & seaweed, Seaweed const & parent );
			virtual void doOnSeaweedDie( Seaweed const & seaweed );

		private:
			GlSeaweedRenderer & m_glSeaweedRenderer;
			GlFishRenderer & m_glFishRenderer;
		};
	}
}

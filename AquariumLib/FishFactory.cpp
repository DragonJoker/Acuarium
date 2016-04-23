#include "FishFactory.hpp"

#include "RacedFish.hpp"

namespace aquarium
{
	FishFactory::FishFactory()
		: m_creators{
			{
				{ Basse, RacedFish< Basse >::create },
				{ Tuna, RacedFish< Tuna >::create },
				{ Clown, RacedFish< Clown >::create },
				{ Sole, RacedFish< Sole >::create },
				{ Bass, RacedFish< Bass >::create },
				{ Carp, RacedFish< Carp >::create }
			}
		}
	{
	}

	FishPtr FishFactory::createFish( FishRace race, uint16_t age, std::string const & name, Gender gender )const
	{
		auto it = m_creators.find( race );

		if ( it == m_creators.end() )
		{
			throw std::runtime_error{ "No creator registered for this fish race." };
		}

		return it->second( age, name, gender );
	}
}

#include "RaceFactory.hpp"

#include "FishRace.hpp"

namespace aquarium
{
	RaceFactory::RaceFactory()
		: m_races{
			{
				{ Basse, std::make_shared< Race< Basse > >() },
				{ Tuna, std::make_shared< Race< Tuna > >() },
				{ Clown, std::make_shared< Race< Clown > >() },
				{ Sole, std::make_shared< Race< Sole > >() },
				{ Bass, std::make_shared< Race< Bass > >() },
				{ Carp, std::make_shared< Race< Carp > >() }
			}
		}
	{
	}

	RacePtr RaceFactory::getRace( FishRace race )const
	{
		auto it = m_races.find( race );

		if ( it == m_races.end() )
		{
			throw std::runtime_error{ "No creator registered for this fish race." };
		}

		return it->second;
	}
}

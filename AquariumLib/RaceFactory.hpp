#pragma once

#include "AquariumPrerequisites.hpp"

namespace aquarium
{
	class RaceFactory
	{
	public:
		RaceFactory();

		RacePtr getRace( FishRace race )const;

	private:
		std::map< FishRace, RacePtr > const m_races;
	};
}

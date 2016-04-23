#pragma once

#include "AquariumPrerequisites.hpp"

namespace aquarium
{
	class FishFactory
	{
	public:
		FishFactory();

		FishPtr createFish( FishRace race, uint16_t age, std::string const & name, Gender gender )const;

	private:
		std::map< FishRace, FishCreator > const m_creators;
	};
}

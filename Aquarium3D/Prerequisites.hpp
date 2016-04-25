#pragma once

#include <AquariumRendererPrerequisites.hpp>
#include <FishRace.hpp>

#include <fstream>
#include <glm/glm.hpp>

struct TurnAdds
{
	aquarium::FishArray m_fishes;
	aquarium::SeaweedArray m_seaweeds;
};

using TurnAddsMap = std::map< uint32_t, TurnAdds >;

void manualFillAquarium( TurnAddsMap & turns );
void autoFillAquarium( TurnAddsMap & turns );
void loadFromFile( std::string const & filename, TurnAddsMap & turns );
void updateAquarium( aquarium::Aquarium & aqua, TurnAddsMap & turnsAdds, uint32_t turn );
void saveAquarium( std::string const & filename, aquarium::Aquarium const & aqua );

namespace aquarium
{
	namespace render
	{
		class GlAquariumRenderer;
		class GlFishRenderer;
		class GlSeaweedRenderer;

		using GlFishRendererPtr = std::unique_ptr< GlFishRenderer >;
		using GlSeaweedRendererPtr = std::unique_ptr< GlSeaweedRenderer >;

		using PlacedSeaweed = std::pair< aquarium::SeaweedPtr, glm::vec3 >;
		using PlacedFish = std::pair< aquarium::FishPtr, glm::vec3 >;
		using SeaweedArray = std::vector< PlacedSeaweed >;
		using FishArray = std::vector< PlacedFish >;
	}
}

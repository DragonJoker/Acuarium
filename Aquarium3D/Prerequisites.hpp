#pragma once

#include <AquariumAppsPrerequisites.hpp>

#include <glm/glm.hpp>

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

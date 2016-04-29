#pragma once

#include <AquariumAppsPrerequisites.hpp>

#include "GL/glew.h"

#pragma warning( push )
#pragma warning( disable:4201 )
#include <glm/glm.hpp>
#pragma warning( pop )

#include "GlElements.hpp"
#include "ObjElements.hpp"

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

		bool checkGlError( std::string const & desc );
	}
}

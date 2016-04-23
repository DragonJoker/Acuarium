#pragma once

#include <AquariumPrerequisites.hpp>

#include <mutex>
#include <thread>

namespace aquarium
{
	namespace render
	{
		class AquariumRenderer;
		class FishRenderer;
		class SeaweedRenderer;

		using AquariumRendererPtr = std::unique_ptr< AquariumRenderer >;
		using FishRendererPtr = std::unique_ptr< FishRenderer >;
		using SeaweedRendererPtr = std::unique_ptr< SeaweedRenderer >;

		template< typename LockT >
		std::unique_lock< LockT > make_unique_lock( LockT & p_lock )
		{
			return std::unique_lock< LockT >{ p_lock };
		}
	}
}

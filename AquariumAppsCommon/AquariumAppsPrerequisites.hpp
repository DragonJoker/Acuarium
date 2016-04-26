#pragma once

#include <AquariumRendererPrerequisites.hpp>
#include <AquariumGame.hpp>

#include <fstream>

namespace aquarium
{
	namespace render
	{
		class ConsoleSeaweedRenderer;
		class ConsoleFishRenderer;
		class ConsoleAquariumRenderer;

		using ConsoleSeaweedRendererPtr = std::unique_ptr< ConsoleSeaweedRenderer >;
		using ConsoleFishRendererPtr = std::unique_ptr< ConsoleFishRenderer >;
		using ConsoleAquariumRendererPtr = std::unique_ptr< ConsoleAquariumRenderer >;

		struct NameManip;
		struct GenderManip;
		struct RaceManip;

		template< typename T >
		struct ManipCreator;

		std::ostream & operator<<( std::ostream & stream, NameManip const & manip );
		std::ostream & operator<<( std::ostream & stream, GenderManip const & manip );
		std::ostream & operator<<( std::ostream & stream, RaceManip const & manip );
	}
}

void manualFillAquarium( aquarium::TurnAddsMap & turns );
void autoFillAquarium( aquarium::TurnAddsMap & turns );
void loadFromFile( std::string const & filename, aquarium::TurnAddsMap & turns );
void saveAquarium( std::string const & filename, aquarium::Aquarium const & aqua );

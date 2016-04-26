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

		struct NameManip
		{
			NameManip( std::string const & str );
	
			std::string const & m_str;
		};

		struct GenderManip
		{
			GenderManip( Gender gender );
	
			std::string const m_str;
		};

		struct RaceManip
		{
			RaceManip( FishRace race );
	
			std::string const m_str;
		};

		template< typename T >
		struct ManipCreator;

		template<>
		struct ManipCreator< std::string >
		{
			using type = NameManip;
		};

		template<>
		struct ManipCreator< Gender >
		{
			using type = GenderManip;
		};

		template<>
		struct ManipCreator< FishRace >
		{
			using type = RaceManip;
		};

		template< typename T >
		typename ManipCreator< T >::type manip( T const & value )
		{
			return typename ManipCreator< T >::type{ value };
		}

		std::ostream & operator<<( std::ostream & stream, NameManip const & manip );
		std::ostream & operator<<( std::ostream & stream, GenderManip const & manip );
		std::ostream & operator<<( std::ostream & stream, RaceManip const & manip );
	}
}

void manualFillAquarium( aquarium::TurnAddsMap & turns );
void autoFillAquarium( aquarium::TurnAddsMap & turns );
void loadFromFile( std::string const & filename, aquarium::TurnAddsMap & turns );
void saveAquarium( std::string const & filename, aquarium::Aquarium const & aqua );

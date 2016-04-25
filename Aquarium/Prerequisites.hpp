#pragma once

#include <AquariumRendererPrerequisites.hpp>

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

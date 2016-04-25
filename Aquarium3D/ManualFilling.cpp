#include "Prerequisites.hpp"

#include <RaceFactory.hpp>
#include <Seaweed.hpp>
#include <Fish.hpp>

using namespace aquarium;

namespace
{
	template< typename T >
	void askIntValue( std::string const & text, T & value, T min = 0, T max = std::numeric_limits< T >::max() )
	{
		bool valid{ false };

		do
		{
			std::cout << text;
			valid = bool( std::cin >> value ) && value >= min && value <= max;

			if ( !valid )
			{
				std::cerr << "Invalid input... Try again.\n";
				std::cin.clear();
				std::cin.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
			}
		}
		while ( !valid );

		std::cin.clear();
		std::cin.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
	}
	
	void manualFillSeaweeds( TurnAdds & adds )
	{
		uint16_t seaweeds{ 0u };
		askIntValue( "Number of seaweeds? ", seaweeds );

		for ( uint16_t i{ 0u }; i < seaweeds; ++i )
		{
			uint16_t age{ 0u };
			askIntValue( "Age (0-19)? ", age, uint16_t{ 0u }, uint16_t{ 19u } );
			adds.m_seaweeds.emplace_back( age );
		}
	}

	void manualFillFishes( TurnAdds & adds )
	{
		RaceFactory factory;
		uint16_t fishes{ 0u };
		askIntValue( "Number of fishes? ", fishes );

		for ( uint16_t i{ 0u }; i < fishes; ++i )
		{
			std::string name = getRandomName();
			std::cout << "Fish " << ( i + 1 ) << " [" << name << "]\n";
			uint16_t age{ 0u };
			askIntValue( "Age (0-19)? ", age, uint16_t{ 0u }, uint16_t{ 19u } );
			uint16_t race{ 0u };
			askIntValue( "  Race\n    0: Basse\n    1: Tuna\n    2: Clown\n    3: Sole\n    4: Bass\n    5: Carp\n    Your choice? ", race, uint16_t( 0u ), uint16_t( RaceCount - 1 ) );
			uint16_t gender{ 0u };
			askIntValue( "  Gender\n    0: female\n    other: male\n    Your choice? ", gender );

			adds.m_fishes.emplace_back( factory.getRace( FishRace( race ) ), age, name, gender == 0u ? Female : Male );
		}
	}
}

void manualFillAquarium( TurnAddsMap & turns )
{
	auto & adds = turns.insert( { 0, TurnAdds{} } ).first->second;
	manualFillSeaweeds( adds );
	manualFillFishes( adds );
}

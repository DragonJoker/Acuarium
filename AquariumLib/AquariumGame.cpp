#include "AquariumGame.hpp"

#include "FishRace.hpp"
#include "RaceFactory.hpp"

namespace aquarium
{
	AquariumGame::AquariumGame( Aquarium & aquarium, TurnAddsMap && turnsAdds )
		: m_aquarium{ aquarium }
		, m_turnsAdds{ std::move( turnsAdds ) }
	{
		doAddTurnAdds();
	}

	void AquariumGame::update()
	{
		++m_turn;
		doAddTurnAdds();

		FishArray newFishes;
		SeaweedArray newSeaweeds;
		FishArray & fishes = m_aquarium.m_fishes;
		SeaweedArray & seaweeds = m_aquarium.m_seaweeds;
		doGrowLivings( fishes, seaweeds, newFishes, newSeaweeds );
		doUpdateLivings( fishes, seaweeds, newFishes, newSeaweeds );
	}

	void AquariumGame::doGrowLivings( FishArray & fishes, SeaweedArray & seaweeds, FishArray & newFishes, SeaweedArray & newSeaweeds )
	{
		try
		{
			// Grow seaweeds.
			for ( auto & seaweed : seaweeds )
			{
				auto child = seaweed.grow();

				if ( child )
				{
					m_aquarium.onSeaweedBorn( *child, seaweed );
					newSeaweeds.push_back( std::move( *child ) );
				}
			}

			// Grow fishes.
			for ( auto & current : fishes )
			{
				Fish * fish{ nullptr };
				Seaweed * seaweed{ nullptr };
				auto child = current.grow( fishes, seaweeds, fish, seaweed );

				if ( child )
				{
					m_aquarium.onFishBorn( *child, current, *fish );
					newFishes.push_back( std::move( *child ) );
				}
				else if ( fish )
				{
					m_aquarium.onFishEatFish( current, *fish );
				}
				else if ( seaweed )
				{
					m_aquarium.onFishEatSeaweed( current, *seaweed );
				}
			}
		}
		catch ( std::exception & exc )
		{
			std::cerr << "Error uncountered when moving to next turn: " << exc.what() << "\n";
		}
	}

	void AquariumGame::doUpdateLivings( FishArray & fishes, SeaweedArray & seaweeds, FishArray & newFishes, SeaweedArray & newSeaweeds )
	{
		// Remove dead seaweeds.
		auto deadsw = std::remove_if( seaweeds.begin(), seaweeds.end(), []( Seaweed const & seaweed )
		{
			return !seaweed.isAlive();
		} );
		seaweeds.erase( deadsw, seaweeds.end() );

		// Remove dead fishes.
		auto deadf = std::remove_if( fishes.begin(), fishes.end(), []( Fish const & fish )
		{
			return !fish.isAlive();
		} );
		fishes.erase( deadf, fishes.end() );

		// Add newborn seaweeds.
		for ( auto & seaweed : newSeaweeds )
		{
			m_aquarium.addSeaweed( std::move( seaweed ) );
		}

		// Add newborn fishes.
		for ( auto & fish : newFishes )
		{
			m_aquarium.addFish( std::move( fish ) );
		}
	}

	void AquariumGame::doAddTurnAdds()
	{
		for ( auto && seaweed : m_turnsAdds[m_turn].m_seaweeds )
		{
			m_aquarium.addSeaweed( std::move( seaweed ) );
		}

		for ( auto && fish : m_turnsAdds[m_turn].m_fishes )
		{
			m_aquarium.addFish( std::move( fish ) );
		}

		m_turnsAdds.erase( m_turn );
	}
}

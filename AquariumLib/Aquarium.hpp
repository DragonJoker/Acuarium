#pragma once

#include "Signal.hpp"
#include "FishRace.hpp"

namespace aquarium
{
	class Aquarium
	{
		friend class AquariumGame;

	public:
		void addFish( Fish && fish );
		void addSeaweed( Seaweed && seaweed );

		inline bool hasFishes() const
		{
			return !m_fishes.empty();
		}

		inline bool hasSeaweeds() const
		{
			return !m_seaweeds.empty();
		}

		inline FishArray const & getFishes() const
		{
			return m_fishes;
		}

		inline SeaweedArray const & getSeaweeds() const
		{
			return m_seaweeds;
		}

	public:
		mutable Signal< std::function< void( Fish const & fish, Fish const & lhs, Fish const & rhs ) > > onFishBorn;
		mutable Signal< std::function< void( Fish const & fish ) > > onFishDie;
		mutable Signal< std::function< void( Fish const & fish, Fish const & prey ) > > onFishEatFish;
		mutable Signal< std::function< void( Fish const & fish, Seaweed const & prey ) > > onFishEatSeaweed;
		mutable Signal< std::function< void( Fish const & fish ) > > onFishNoFood;
		mutable Signal< std::function< void( Fish const & fish ) > > onFishNoMate;
		mutable Signal< std::function< void( Fish const & fish, Fish const & mate ) > > onFishWrongMate;
		mutable Signal< std::function< void( Fish const & fish, Gender ) > > onFishSwitchGender;
		mutable Signal< std::function< void( Seaweed const & seaweed, Seaweed const & parent ) > > onSeaweedBorn;
		mutable Signal< std::function< void( Seaweed const & seaweed ) > > onSeaweedDie;

	private:
		FishArray m_fishes;
		SeaweedArray m_seaweeds;
	};

	std::ostream & operator<<( std::ostream & stream, Aquarium const & aqua );
	std::istream & operator>>( std::istream & stream, Aquarium & aqua );
}

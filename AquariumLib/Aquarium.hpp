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

		inline auto fishesCount() const
		{
			return m_fishes.size();
		}

		inline auto fishesBegin() const
		{
			return m_fishes.begin();
		}

		inline auto fishesBegin()
		{
			return m_fishes.begin();
		}

		inline auto fishesEnd() const
		{
			return m_fishes.end();
		}

		inline auto fishesEnd()
		{
			return m_fishes.end();
		}

		inline bool hasSeaweeds() const
		{
			return !m_seaweeds.empty();
		}

		inline auto seaweedsCount() const
		{
			return m_seaweeds.size();
		}

		inline auto seaweedsBegin() const
		{
			return m_seaweeds.begin();
		}

		inline auto seaweedsBegin()
		{
			return m_seaweeds.begin();
		}

		inline auto seaweedsEnd() const
		{
			return m_seaweeds.end();
		}

		inline auto seaweedsEnd()
		{
			return m_seaweeds.end();
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

		friend std::ostream & operator<<( std::ostream & stream, Aquarium const & aqua );
	};

	std::ostream & operator<<( std::ostream & stream, Aquarium const & aqua );
	std::istream & operator>>( std::istream & stream, Aquarium & aqua );
}

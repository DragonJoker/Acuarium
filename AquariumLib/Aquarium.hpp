#pragma once

#include "Signal.hpp"

namespace aquarium
{
	class Aquarium
	{
	public:
		void nextTurn();
		void update();
		void addFish( FishPtr && fish );
		void addSeaweed( SeaweedPtr && seaweed );

		inline bool hasFishes() const
		{
			return !m_fishes.empty() || !m_newFishes.empty();
		}

		inline bool hasSeaweeds() const
		{
			return !m_seaweeds.empty() || !m_newSeaweeds.empty();
		}

		inline FishArray const & getFishes() const
		{
			return m_fishes;
		}

		inline SeaweedArray const & getSeaweeds() const
		{
			return m_seaweeds;
		}

		inline std::default_random_engine & getRandomEngine()
		{
			return m_engine;
		}

	private:
		void doAddNewComers();
		void doRemoveDead();

	public:
		mutable Signal< std::function< void( FishPtr fish, FishPtr lhs, FishPtr rhs ) > > onFishBorn;
		mutable Signal< std::function< void( FishPtr fish ) > > onFishDie;
		mutable Signal< std::function< void( FishPtr fish, FishPtr prey ) > > onFishEatFish;
		mutable Signal< std::function< void( FishPtr fish, SeaweedPtr prey ) > > onFishEatSeaweed;
		mutable Signal< std::function< void( FishPtr fish ) > > onFishNoFood;
		mutable Signal< std::function< void( FishPtr fish ) > > onFishNoMate;
		mutable Signal< std::function< void( FishPtr fish, FishPtr mate ) > > onFishWrongMate;
		mutable Signal< std::function< void( FishPtr fish, Gender ) > > onFishSwitchGender;
		mutable Signal< std::function< void( SeaweedPtr seaweed, SeaweedPtr parent ) > > onSeaweedBorn;
		mutable Signal< std::function< void( SeaweedPtr seaweed ) > > onSeaweedDie;

	private:
		FishArray m_fishes;
		FishArray m_newFishes;
		SeaweedArray m_seaweeds;
		SeaweedArray m_newSeaweeds;
		std::random_device m_device;
		std::default_random_engine m_engine{ m_device() };

		friend std::istream & operator>>( std::istream & stream, Aquarium & aqua );
	};

	std::ostream & operator<<( std::ostream & stream, Aquarium const & aqua );
	std::istream & operator>>( std::istream & stream, Aquarium & aqua );
}

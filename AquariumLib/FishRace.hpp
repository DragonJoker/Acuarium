#pragma once

#include <cassert>

namespace aquarium
{
	class RaceBase
		: public std::enable_shared_from_this< RaceBase const >
	{
	protected:
		RaceBase( FishRace race, ConsumerType type )
			: m_race{ race }
			, m_type{ type }
		{
		}

	public:
		virtual ~RaceBase()
		{
		}

		inline FishRace getRace() const
		{
			return m_race;
		}

		inline bool isCarnivore() const
		{
			return m_type == Carnivore;
		}

		inline bool isHerbivore() const
		{
			return m_type == Herbivore;
		}

		virtual void grow( Fish & current ) const = 0;
		virtual void eat( Fish & current, FishArray & fishes, SeaweedArray & seaweeds, Fish *& fish, Seaweed *& seaweed ) const = 0;
		virtual FishPtr reproduce( Fish & current, FishArray & fishes, Fish *& mate ) const = 0;

	private:
		FishRace const m_race;
		ConsumerType const m_type;
	};

	namespace helper
	{
		template< FishRace RaceT, typename Enable = void > struct RaceGrowT;
		template< FishRace RaceT, typename Enable = void > struct RaceEatT;
		template< FishRace RaceT, typename Enable = void > struct RaceReproduceT;
	}

	template< FishRace RaceT >
	class Race
		: public RaceBase
	{
	public:
		Race()
			: RaceBase{ RaceT, ConsumerTypeGetter< RaceT >::value }
		{
		}

		virtual ~Race()
		{
		}

		virtual void grow( Fish & current ) const
		{
			helper::RaceGrowT< RaceT >::apply( current );
		}

		virtual void eat( Fish & current, FishArray & fishes, SeaweedArray & seaweeds, Fish *& fish, Seaweed *& seaweed ) const
		{
			helper::RaceEatT< RaceT >::apply( current, fishes, seaweeds, fish, seaweed );
		}

		virtual FishPtr reproduce( Fish & current, FishArray & fishes, Fish *& mate ) const
		{
			return helper::RaceReproduceT< RaceT >::apply( current, fishes, mate );
		}
	};
}

#include "FishRace.inl"

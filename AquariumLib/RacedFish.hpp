#pragma once

#include "Fish.hpp"
#include "Seaweed.hpp"

#include <cassert>

namespace aquarium
{
	namespace helper
	{
		template< FishRace Race, typename Enable = void > struct FishGrowT;
		template< FishRace Race, typename Enable = void > struct FishEatT;
		template< FishRace Race, typename Enable = void > struct FishReproduceT;
	}

	template< FishRace Race >
	class RacedFish
		: public Fish
		, public std::enable_shared_from_this< RacedFish< Race > >
	{
		using SharedFromThis = std::enable_shared_from_this< RacedFish< Race > >;

	public:
		RacedFish( uint16_t age, std::string const & name, Gender gender )
			: Fish{ Race, IsHerbivore< Race >::value, IsCarnivore< Race >::value, age, name, gender }
		{
		}

		virtual ~RacedFish()
		{
		}

		static FishPtr create( uint16_t age, std::string const & name, Gender gender )
		{
			return std::make_shared< RacedFish< Race > >( age, name, gender );
		}

	private:
		virtual void doGrow()
		{
			helper::FishGrowT< Race >::apply( SharedFromThis::shared_from_this() );
		}

		virtual void doEat( std::default_random_engine & engine, FishArray const & fishes, SeaweedArray const & seaweeds, FishPtr & fish, SeaweedPtr & seaweed )
		{
			helper::FishEatT< Race >::apply( SharedFromThis::shared_from_this(), engine, fishes, seaweeds, fish, seaweed );
		}

		virtual FishPtr doReproduce( std::default_random_engine & engine, FishArray const & fishes, FishPtr & mate )
		{
			return helper::FishReproduceT< Race >::apply( SharedFromThis::shared_from_this(), engine, fishes, mate );
		}

		virtual FishPtr sharedFromThis()
		{
			return shared_from_this();
		}
	};
}

#include "RacedFish.inl"

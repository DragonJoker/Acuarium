#pragma once

#include "Fish.hpp"
#include "Seaweed.hpp"

#include <cassert>

namespace aquarium
{
  namespace helper
  {
    template< FishRace Race, typename Enable=void > struct FishEatT;
    template< FishRace Race, typename Enable=void > struct FishNextTurnT;
    template< FishRace Race, typename Enable=void > struct FishReproduceT;
  }

  template< FishRace Race >
  class RacedFish
    : public Fish
  {
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
    virtual void doOnNextTurn()
    {
      helper::FishNextTurnT< Race >::apply( *this );
    }

    virtual void doEat( std::random_device & engine, FishArray const & fishes, SeaweedArray const & seaweeds )
    {
      helper::FishEatT< Race >::apply( *this, engine, fishes, seaweeds );
    }

    virtual FishPtr doReproduce( std::random_device & engine, FishArray const & fishes )
    {
      return helper::FishReproduceT< Race >::apply( *this, engine, fishes );
    }
  };
}

#include "RacedFish.inl"

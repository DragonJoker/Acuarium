#pragma once

#include "Aquarium.hpp"
#include "Fish.hpp"
#include "Seaweed.hpp"

#include <cassert>

namespace aquarium
{
  namespace helper
  {
    template< FishRace Race, typename Enable=void > struct FishEatT;
    template< FishRace Race, typename Enable=void > struct FishNewTurnT;
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
    virtual void doOnNewTurn( Aquarium & aqua )
    {
      helper::FishNewTurnT< Race >::newTurn( *this, aqua );
    }

    virtual void doEat( Aquarium & aqua )
    {
      helper::FishEatT< Race >::eat( *this, aqua );
    }

    virtual void doReproduce( Aquarium & aqua )
    {
      helper::FishReproduceT< Race >::reproduce( *this, aqua );
    }
  };
}

#include "RacedFish.inl"

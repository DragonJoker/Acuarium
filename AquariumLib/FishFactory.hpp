#pragma once

#include "Prerequisites.hpp"

namespace aquarium
{
  class FishFactory
  {
  public:
    FishFactory();

    void registerFishRace( FishRace race, FishCreator const & creator );
    FishPtr createFish( FishRace race, uint16_t age, std::string const & name, Gender gender )const;

  private:
    std::map< FishRace, FishCreator > m_creators;
  };
}

#pragma once

#include <Prerequisites.hpp>

#include <fstream>

struct TurnAdds
{
  aquarium::FishArray m_fishes;
  aquarium::SeaweedArray m_seaweeds;
};

using TurnAddsMap = std::map< uint32_t, TurnAdds >;

void manualFillAquarium( TurnAddsMap & turns );
void autoFillAquarium( TurnAddsMap & turns );
void loadFromFile( std::string const & filename, TurnAddsMap & turns );
void updateAquarium( aquarium::Aquarium & aqua, TurnAddsMap & turnsAdds, uint32_t turn );
void saveAquarium( std::string const & filename, aquarium::Aquarium const & aqua );

namespace render
{
  class AquariumRenderer;
  class FishRenderer;
  class SeaweedRenderer;

  struct Point
  {
    float x;
    float y;
    float z;
  };

  using PlacedSeaweed = std::pair< aquarium::SeaweedPtr, Point >;
  using PlacedFish = std::pair< aquarium::FishPtr, Point >;
  using SeaweedArray = std::vector< PlacedSeaweed >;
  using FishArray = std::vector< PlacedFish >;
}

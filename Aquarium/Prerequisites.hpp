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

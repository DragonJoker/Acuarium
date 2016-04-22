#include "Prerequisites.hpp"

#include <Aquarium.hpp>

void updateAquarium( aquarium::Aquarium & aqua, TurnAddsMap & turnsAdds, uint32_t turn )
{
  for ( auto && seaweed : turnsAdds[turn].m_seaweeds )
  {
    aqua.addSeaweed( std::move( seaweed ) );
  }

  for ( auto && fish : turnsAdds[turn].m_fishes )
  {
    aqua.addFish( std::move( fish ) );
  }

  turnsAdds.erase( turn );
  aqua.update();

  std::cout << "\n";
  std::cout << "****************************************\n";
  std::cout << "Aquarium's content:\n";
  std::cout << "****************************************\n\n";
  std::cout << aqua << std::endl;
}

void saveAquarium( std::string const & filename, aquarium::Aquarium const & aqua )
{
  std::ofstream out{ filename };

  if ( out )
  {
    out << aqua;
    out.close();
  }
}

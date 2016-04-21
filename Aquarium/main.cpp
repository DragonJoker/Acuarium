#include "Prerequisites.hpp"

#include <Aquarium.hpp>

int main( int argc, char * argv[] )
{
  aquarium::Aquarium aqua;
  uint32_t turn{ 0 };
  TurnAddsMap turns;

  if ( argc > 1 )
  {
    loadFromFile( argv[1], turns );
  }
  else
  {
    //manualFillAquarium( turns );
    autoFillAquarium( turns );
  }

  std::cout << "***********************************************************************************\n";
  std::cout << "TURN " << turn << ":\n";
  std::cout << "***********************************************************************************\n";
  updateAquarium( aqua, turns, turn );

  while ( aqua.hasFishes() || aqua.hasSeaweeds() )
  {
    std::cout << "***********************************************************************************\n";
    std::cout << "TURN " << ++turn << ":\n";
    std::cout << "***********************************************************************************\n";
    std::cout << "Actions:\n";
    std::cout << "****************************************\n\n";
    aqua.nextTurn();
    updateAquarium( aqua, turns, turn );
    //saveAquarium( "aqua.poisson", aqua );
    std::cin.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
  }
}

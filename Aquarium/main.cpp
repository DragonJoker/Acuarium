#include "Prerequisites.hpp"

#include "ConsoleRenderer.hpp"

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

	{
		aquarium::render::ConsoleAquariumRenderer renderer{ aqua };
		updateAquarium( aqua, turns, turn );
		renderer.render( turn );

		while ( aqua.hasFishes() || aqua.hasSeaweeds() )
		{
			{
				auto lock = make_unique_lock( renderer );
				aqua.nextTurn();
				updateAquarium( aqua, turns, ++turn );
			}
			renderer.render( turn );
			//saveAquarium( "aqua.poisson", aqua );
			std::cin.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
		}
	}
}

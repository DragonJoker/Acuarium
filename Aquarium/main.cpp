#include <AquariumAppsPrerequisites.hpp>

#include "ConsoleAquariumRenderer.hpp"

int main( int argc, char * argv[] )
{
	aquarium::Aquarium aqua;
	aquarium::TurnAddsMap turns;

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
		aquarium::AquariumGame game{ aqua, std::move( turns ) };
		aquarium::render::ConsoleAquariumRenderer renderer{ aqua };
		renderer.render( game.getTurn() );

		while ( aqua.hasFishes() || aqua.hasSeaweeds() )
		{
			{
				auto lock = make_unique_lock( renderer );
				game.update();
			}
			renderer.render( game.getTurn() );
			//saveAquarium( "aqua.poisson", aqua );
			std::cin.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
		}
	}
}

#include "Prerequisites.hpp"

#include <Aquarium.hpp>
#include <GLFW/glfw3.h>

#include "AquariumRenderer.hpp"
#include "ConsoleRenderer.hpp"

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

	int ret = -1;

	if ( glfwInit() )
	{
		GLFWwindow * window = glfwCreateWindow( 800, 600, "Acuarium++", nullptr, nullptr );

		if ( window )
		{
			glfwMakeContextCurrent( window );
			aquarium::render::GlAquariumRenderer renderer{ aqua };
			aquarium::render::ConsoleAquariumRenderer console{ aqua };
			aquarium::AquariumGame game{ aqua, turns };
			console.render( game.getTurn() );
			renderer.render( game.getTurn() );

			while ( !glfwWindowShouldClose( window ) && aqua.hasFishes() || aqua.hasSeaweeds() )
			{
				{
					auto lock = make_unique_lock( renderer );
					game.update();
				}
				console.render( game.getTurn() );
				renderer.render( game.getTurn() );
				glfwSwapBuffers( window );
				glfwPollEvents();
			}

			ret = 0;
		}
		
		glfwTerminate();
	}

	return ret;
}

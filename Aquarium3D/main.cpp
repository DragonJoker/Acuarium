#include "Prerequisites.hpp"

#include <Aquarium.hpp>
#include <GLFW/glfw3.h>

#include "AquariumRenderer.hpp"

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

	int ret = -1;

	if ( glfwInit() )
	{
		GLFWwindow * window = glfwCreateWindow( 800, 600, "Acuarium++", nullptr, nullptr );

		if ( window )
		{
			glfwMakeContextCurrent( window );
			aquarium::render::GlAquariumRenderer renderer{ aqua };
			updateAquarium( aqua, turns, turn );
			renderer.render( turn );

			while ( !glfwWindowShouldClose( window ) && aqua.hasFishes() || aqua.hasSeaweeds() )
			{
				{
					auto lock = make_unique_lock( renderer );
					aqua.nextTurn();
					updateAquarium( aqua, turns, ++turn );
				}
				renderer.render( turn );
				glfwSwapBuffers( window );
				glfwPollEvents();
			}

			ret = 0;
		}
		
		glfwTerminate();
	}

	return ret;
}

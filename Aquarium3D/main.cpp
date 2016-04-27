#include "Prerequisites.hpp"

#include <Aquarium.hpp>
#include <GLFW/glfw3.h>

#include "GlAquariumRenderer.hpp"
#include <ConsoleAquariumRenderer.hpp>

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

			if ( glewInit() == GLEW_OK )
			{
				glClearColor( 0.0f, 0.7f, 0.9f, 1.0f );
				aquarium::AquariumGame game{ aqua, turns };
				aquarium::render::GlAquariumRenderer renderer{ aqua };
				aquarium::render::ConsoleAquariumRenderer console{ aqua };
				console.render( game.getTurn() );
				renderer.render( game.getTurn() );

				while ( !glfwWindowShouldClose( window ) && aqua.hasFishes() || aqua.hasSeaweeds() )
				{
					glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
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
			else
			{
				std::cerr << "Couldn't initialise GLEW" << std::endl;
			}
		}
		
		glfwTerminate();
	}
	else
	{
		std::cerr << "Couldn't initialise GLFW" << std::endl;
	}

	return ret;
}

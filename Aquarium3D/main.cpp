#include "Prerequisites.hpp"

#include <Aquarium.hpp>
#include <GLFW/glfw3.h>

#include "GlAquariumRenderer.hpp"
#include <ConsoleAquariumRenderer.hpp>

void DebugLog( uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int, const char * message )
{
	if ( id != 131185 )
	{
		bool error = false;
		std::string toLog = "OpenGl Debug - ";

		switch ( source )
		{
		case GL_DEBUG_SOURCE_API:
			toLog += "Source:OpenGL\t";
			break;

		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			toLog += "Source:Windows\t";
			break;

		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			toLog += "Source:Shader compiler\t";
			break;

		case GL_DEBUG_SOURCE_THIRD_PARTY:
			toLog += "Source:Third party\t";
			break;

		case GL_DEBUG_SOURCE_APPLICATION:
			toLog += "Source:Application\t";
			break;

		case GL_DEBUG_SOURCE_OTHER:
			toLog += "Source:Other\t";
			break;
		}

		switch ( type )
		{
		case GL_DEBUG_TYPE_ERROR:
			toLog += "Type:Error\t";
			break;

		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			toLog += "Type:Deprecated behavior\t";
			break;

		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			toLog += "Type:Undefined behavior\t";
			break;

		case GL_DEBUG_TYPE_PORTABILITY:
			toLog += "Type:Portability\t";
			break;

		case GL_DEBUG_TYPE_PERFORMANCE:
			toLog += "Type:Performance\t";
			break;

		case GL_DEBUG_TYPE_OTHER:
			toLog += "Type:Other\t";
			break;
		}

		toLog += "ID:" + std::to_string( id ) + "\t";

		switch ( severity )
		{
		case GL_DEBUG_SEVERITY_HIGH:
			error = true;
			toLog += "Severity:High\t";
			break;

		case GL_DEBUG_SEVERITY_MEDIUM:
			toLog += "Severity:Medium\t";
			break;

		case GL_DEBUG_SEVERITY_LOW:
			toLog += "Severity:Low\t";
			break;
		}

		if ( error )
		{
			std::cerr << toLog << "Message:" << message <<std::endl;
		}
		else
		{
			std::cout << toLog << "Message:" << message <<std::endl;
		}
	}
}

void DebugLogAMD( uint32_t id, uint32_t category, uint32_t severity, int, const char * message )
{
	bool error = false;
	std::string toLog = "OpenGl Debug - ";

	switch ( category )
	{
	case GL_DEBUG_CATEGORY_API_ERROR_AMD:
		toLog += "Category:OpenGL\t";
		break;

	case GL_DEBUG_CATEGORY_WINDOW_SYSTEM_AMD:
		toLog += "Category:Windows\t";
		break;

	case GL_DEBUG_CATEGORY_DEPRECATION_AMD:
		toLog += "Category:Deprecated behavior\t";
		break;

	case GL_DEBUG_CATEGORY_UNDEFINED_BEHAVIOR_AMD:
		toLog += "Category:Undefined behavior\t";
		break;

	case GL_DEBUG_CATEGORY_PERFORMANCE_AMD:
		toLog += "Category:Performance\t";
		break;

	case GL_DEBUG_CATEGORY_SHADER_COMPILER_AMD:
		toLog += "Category:Shader compiler\t";
		break;

	case GL_DEBUG_CATEGORY_APPLICATION_AMD:
		toLog += "Category:Application\t";
		break;

	case GL_DEBUG_CATEGORY_OTHER_AMD:
		toLog += "Category:Other\t";
		break;
	}

	toLog += "ID:" + std::to_string( id ) + "\t";

	switch ( severity )
	{
	case GL_DEBUG_SEVERITY_HIGH:
		error = true;
		toLog += "Severity:High\t";
		break;

	case GL_DEBUG_SEVERITY_MEDIUM:
		toLog += "Severity:Medium\t";
		break;

	case GL_DEBUG_SEVERITY_LOW:
		toLog += "Severity:Low\t";
		break;
	}

	if ( error )
	{
		std::cerr << toLog << "Message:" << message << std::endl;
	}
	else
	{
		std::cout << toLog << "Message:" << message << std::endl;
	}
}

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
#if !defined( NDEBUG )

				if ( glDebugMessageCallback )
				{
					glDebugMessageCallback( GLDEBUGPROC( &DebugLog ), nullptr );
					glEnable( GL_DEBUG_OUTPUT );
					glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );
				}
				else if( glDebugMessageCallbackAMD )
				{
					glDebugMessageCallbackAMD( GLDEBUGPROCAMD( &DebugLogAMD ), nullptr );
					glEnable( GL_DEBUG_OUTPUT );
				}

#endif
				glClearColor( 0.0f, 0.7f, 0.9f, 1.0f );
				glEnable( GL_CULL_FACE );
				glEnable( GL_DEPTH_TEST );
				aquarium::AquariumGame game{ aqua, std::move( turns ) };
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

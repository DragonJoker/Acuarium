#include "ConsoleFishRenderer.hpp"

#include "StreamManip.hpp"

#include <Fish.hpp>

namespace aquarium
{
	namespace render
	{
		void ConsoleFishRenderer::doRender( Fish const & fish )
		{
			std::cout << manip( fish.getRace()->getRace() );
			std::cout << "\t" << manip( fish.getName() );
			std::cout << "\t" << manip( fish.getGender() );
			std::cout << " " << std::setw( 2 ) << std::left << fish.getAge();
			std::cout << " " << std::setw( 2 ) << std::left << fish.getHealth();
			std::cout << "\n";
		}

		void ConsoleFishRenderer::doRenderBorn( Fish const & fish, Fish const & lhs, Fish const & rhs )
		{
			std::cout << "[" << manip( fish.getName() ) << "] is born from the union of ";
			std::cout << "[" << manip( lhs.getName() ) << "] and ";
			std::cout << "[" << manip( rhs.getName() ) << "]" << std::endl;
		}

		void ConsoleFishRenderer::doRenderDie( Fish const & fish )
		{
			std::cout << "[" << manip( fish.getName() ) << "] is dead. :'(" << std::endl;
		}

		void ConsoleFishRenderer::doRenderEat( Fish const & fish, Fish const & prey )
		{
			std::cout << "[" << manip( fish.getName() ) << "] is feeding on [" << manip( prey.getName() ) << "]." << std::endl;
		}

		void ConsoleFishRenderer::doRenderEat( Fish const & fish, Seaweed const & )
		{
			std::cout << "[" << manip( fish.getName() ) << "] is feeding on a seaweed." << std::endl;
		}

		void ConsoleFishRenderer::doRenderNoFood( Fish const & fish )
		{
			std::cout << "[" << manip( fish.getName() ) << "] is hungry, but no food." << std::endl;
		}

		void ConsoleFishRenderer::doRenderNoMate( Fish const & fish )
		{
			std::cout << "[" << manip( fish.getName() ) << "] tried to reproduce, but no mate." << std::endl;
		}

		void ConsoleFishRenderer::doRenderWrongMate( Fish const & fish, Fish const & )
		{
			std::cout << "[" << manip( fish.getName() ) << "] tried to reproduce, but mate was not compatible" << std::endl;
		}

		void ConsoleFishRenderer::doRenderSwitchGender( Fish const & fish, Gender gender )
		{
			std::cout << "[" << manip( fish.getName() ) << "] switches gender from " << manip( gender );
			std::cout << " to " << manip( fish.getGender() ) << "" << std::endl;
		}
	}
}

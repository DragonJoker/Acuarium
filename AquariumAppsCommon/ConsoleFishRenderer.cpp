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
	}
}

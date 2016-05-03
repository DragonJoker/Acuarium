#include "ConsoleSeaweedRenderer.hpp"

#include <Seaweed.hpp>

namespace aquarium
{
	namespace render
	{
		void ConsoleSeaweedRenderer::doRender( Seaweed const & seaweed )
		{
			std::cout << " " << std::setw( 2 ) << std::left << seaweed.getAge();
			std::cout << " " << std::setw( 2 ) << std::left << seaweed.getHealth();
			std::cout << "\n";
		}

		void ConsoleSeaweedRenderer::doRenderBorn( Seaweed const &, Seaweed const & )
		{
		}

		void ConsoleSeaweedRenderer::doRenderDie( Seaweed const & )
		{
		}
	}
}

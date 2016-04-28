#include "ConsoleAquariumRenderer.hpp"

#include "ConsoleFishRenderer.hpp"
#include "ConsoleSeaweedRenderer.hpp"
#include "StreamManip.hpp"

#include <FishRace.hpp>

namespace aquarium
{
	namespace render
	{
		ConsoleAquariumRenderer::ConsoleAquariumRenderer( Aquarium const & aqua )
			: AquariumRenderer{ aqua, std::make_unique< ConsoleFishRenderer >(), std::make_unique< ConsoleSeaweedRenderer >() }
		{
			initialise( aqua );
		}

		void ConsoleAquariumRenderer::doPreRender( uint32_t turn )
		{
			std::cout << "***********************************************************************************\n";
			std::cout << "TURN " << turn << ":\n";
			std::cout << "***********************************************************************************\n";
			std::cout << "Actions:\n";
			std::cout << "****************************************\n\n";
		}

		void ConsoleAquariumRenderer::doRender()
		{
			std::cout << "\n";
			std::cout << "****************************************\n";
			std::cout << "Aquarium's content:\n";
			std::cout << "****************************************\n\n";
			std::cout << "Seaweeds: ";
			std::cout << m_aquarium.seaweedsCount() << "\n";
			uint16_t age{ 0 };
			uint16_t health{ 0 };
			uint32_t count{ 0 };

			std::vector< Seaweed const * > seaweeds;
			std::for_each( m_aquarium.seaweedsBegin(), m_aquarium.seaweedsEnd(), [this, &seaweeds]( Seaweed const & seaweed )
			{
				seaweeds.push_back( &seaweed );
			} );
			std::sort( std::begin( seaweeds ), std::end( seaweeds ), []( Seaweed const * lhs, Seaweed const * rhs )
			{
				return lhs->getHealth() < rhs->getHealth()
					|| ( lhs->getHealth() == rhs->getHealth()
						  && lhs->getAge() < rhs->getAge() );
			} );

			std::vector< Fish const * > fishes;
			std::for_each( m_aquarium.fishesBegin(), m_aquarium.fishesEnd(), [this, &fishes]( Fish const & fish )
			{
				fishes.push_back( &fish );
			} );
			std::sort( std::begin( fishes ), std::end( fishes ), []( Fish const * lhs, Fish const * rhs )
			{
				return lhs->getRace() < rhs->getRace()
					|| ( lhs->getRace() == rhs->getRace()
						  && ( lhs->getHealth() < rhs->getHealth()
							  || ( lhs->getHealth() == rhs->getHealth()
									&& lhs->getAge() < rhs->getAge() ) ) );
			} );

			for ( auto seaweed : seaweeds )
			{
				if ( seaweed->getAge() != age && seaweed->getHealth() != health && count > 0 )
				{
					std::cout << "(" << count << ") Seaweeds";
					m_seaweedRenderer->render( Seaweed{ age, health } );
					count = 0;
				}

				age = seaweed->getAge();
				health = seaweed->getHealth();
				++count;
			}

			if ( count > 0 )
			{
				std::cout << "(" << count << ") Seaweeds";
				m_seaweedRenderer->render( Seaweed{ age, health } );
			}

			std::cout << "\n";
			std::cout << "Fishes: ";
			std::cout << m_aquarium.fishesCount() << "\n";

			for ( auto fish : fishes )
			{
				m_fishRenderer->render( *fish );
			}

			std::cout << std::endl;
		}
	}
}

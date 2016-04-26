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

		void ConsoleAquariumRenderer::doRender( uint32_t turn )
		{
			std::cout << "\n";
			std::cout << "****************************************\n";
			std::cout << "Aquarium's content:\n";
			std::cout << "****************************************\n\n";
			std::cout << "Seaweeds: ";
			std::cout << m_aquarium.getSeaweeds().size() << "\n";
			uint16_t age{ 0 };
			uint16_t health{ 0 };
			uint32_t count{ 0 };
			auto seaweeds = m_aquarium.getSeaweeds();
			auto fishes = m_aquarium.getFishes();

			std::sort( std::begin( seaweeds ), std::end( seaweeds ), []( Seaweed const & lhs, Seaweed const & rhs )
			{
				return lhs.getHealth() < rhs.getHealth()
					|| ( lhs.getHealth() == rhs.getHealth()
						  && lhs.getAge() < rhs.getAge() );
			} );

			std::sort( std::begin( fishes ), std::end( fishes ), []( Fish const & lhs, Fish const & rhs )
			{
				return lhs.getRace() < rhs.getRace()
					|| ( lhs.getRace() == rhs.getRace()
						  && ( lhs.getHealth() < rhs.getHealth()
							  || ( lhs.getHealth() == rhs.getHealth()
									&& lhs.getAge() < rhs.getAge() ) ) );
			} );

			for ( auto const & seaweed : seaweeds )
			{
				if ( seaweed.getAge() != age && seaweed.getHealth() != health && count > 0 )
				{
					std::cout << "(" << count << ") Seaweeds";
					m_seaweedRenderer->render( Seaweed{ age, health } );
					count = 0;
				}

				age = seaweed.getAge();
				health = seaweed.getHealth();
				++count;
			}

			if ( count > 0 )
			{
				std::cout << "(" << count << ") Seaweeds";
				m_seaweedRenderer->render( Seaweed{ age, health } );
			}

			std::cout << "\n";
			std::cout << "Fishes: ";
			std::cout << m_aquarium.getFishes().size() << "\n";

			for ( auto const & fish : fishes )
			{
				m_fishRenderer->render( fish );
			}

			std::cout << std::endl;
		}

		void ConsoleAquariumRenderer::doOnFishBorn( Fish const & fish, Fish const & lhs, Fish const & rhs )
		{
			std::cout << "[" << manip( fish.getName() ) << "] is born from the union of ";
			std::cout << "[" << manip( lhs.getName() ) << "] and ";
			std::cout << "[" << manip( rhs.getName() ) << "]" << std::endl;
		}

		void ConsoleAquariumRenderer::doOnFishDie( Fish const & fish )
		{
			std::cout << "[" << manip( fish.getName() ) << "] is dead. :'(" << std::endl;
		}

		void ConsoleAquariumRenderer::doOnFishEatFish( Fish const & fish, Fish const & prey )
		{
			std::cout << "[" << manip( fish.getName() ) << "] is feeding on [" << manip( prey.getName() ) << "]." << std::endl;
		}

		void ConsoleAquariumRenderer::doOnFishEatSeaweed( Fish const & fish, Seaweed const & prey )
		{
			std::cout << "[" << manip( fish.getName() ) << "] is feeding on a seaweed." << std::endl;
		}

		void ConsoleAquariumRenderer::doOnFishNoFood( Fish const & fish )
		{
			std::cout << "[" << manip( fish.getName() ) << "] is hungry, but no food." << std::endl;
		}

		void ConsoleAquariumRenderer::doOnFishNoMate( Fish const & fish )
		{
			std::cout << "[" << manip( fish.getName() ) << "] tried to reproduce, but no mate." << std::endl;
		}

		void ConsoleAquariumRenderer::doOnFishWrongMate( Fish const & fish, Fish const & mate )
		{
			std::cout << "[" << manip( fish.getName() ) << "] tried to reproduce, but mate was not compatible" << std::endl;
		}

		void ConsoleAquariumRenderer::doOnFishSwitchGender( Fish const & fish, Gender gender )
		{
			std::cout << "[" << manip( fish.getName() ) << "] switches gender from " << manip( gender );
			std::cout << " to " << manip( fish.getGender() ) << "" << std::endl;
		}

		void ConsoleAquariumRenderer::doOnSeaweedBorn( Seaweed const & seaweed, Seaweed const & parent )
		{
		}

		void ConsoleAquariumRenderer::doOnSeaweedDie( Seaweed const & seaweed )
		{
		}
	}
}

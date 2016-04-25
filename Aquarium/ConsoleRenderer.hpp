#include "Prerequisites.hpp"

#include <AquariumRenderer.hpp>
#include <FishRace.hpp>

namespace aquarium
{
	namespace render
	{
		class ConsoleSeaweedRenderer
			: public SeaweedRenderer
		{
		public:
			ConsoleSeaweedRenderer() = default;
			~ConsoleSeaweedRenderer() = default;

		private:
			virtual void doRender( Seaweed const & seaweed )
			{
			}
		};

		class ConsoleFishRenderer
			: public FishRenderer
		{
		public:
			ConsoleFishRenderer() = default;
			~ConsoleFishRenderer() = default;

		private:
			virtual void doRender( Fish const & fish )
			{
			}
		};

		class ConsoleAquariumRenderer
			: public AquariumRenderer
		{
		public:
			ConsoleAquariumRenderer( Aquarium const & aqua )
				: AquariumRenderer{ aqua, std::make_unique< ConsoleFishRenderer >(), std::make_unique< ConsoleSeaweedRenderer >() }
			{
				initialise( aqua );
			}

			~ConsoleAquariumRenderer() = default;

		private:
			virtual void doPreRender( uint32_t turn )
			{
				std::cout << "***********************************************************************************\n";
				std::cout << "TURN " << turn << ":\n";
				std::cout << "***********************************************************************************\n";
				std::cout << "Actions:\n";
				std::cout << "****************************************\n\n";
			}

			virtual void doRender( uint32_t turn )
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

				for ( auto const & seaweed : m_aquarium.getSeaweeds() )
				{
					if ( seaweed.getAge() != age && seaweed.getHealth() != health && count > 0 )
					{
						std::cout << "(" << count << ") Seaweed";
						std::cout << " " << std::setw( 2 ) << std::left << age;
						std::cout << " " << std::setw( 2 ) << std::left << health;
						std::cout << "\n";
						count = 0;
					}

					age = seaweed.getAge();
					health = seaweed.getHealth();
					++count;
				}

				if ( count > 0 )
				{
					std::cout << "(" << count << ") Seaweed";
					std::cout << " " << std::setw( 2 ) << std::left << age;
					std::cout << " " << std::setw( 2 ) << std::left << health;
				}

				std::cout << "Fishes: ";
				std::cout << m_aquarium.getFishes().size() << "\n";

				for ( auto const & fish : m_aquarium.getFishes() )
				{
					std::cout << manip( fish.getRace()->getRace() );
					std::cout << "\t" << manip( fish.getName() );
					std::cout << "\t" << manip( fish.getGender() );
					std::cout << " " << std::setw( 2 ) << std::left << fish.getAge();
					std::cout << " " << std::setw( 2 ) << std::left << fish.getHealth();
					std::cout << "\n";
				}

				std::cout << std::endl;
			}

			virtual void doOnFishBorn( Fish const & fish, Fish const & lhs, Fish const & rhs )
			{
				std::cout << "[" << manip( fish.getName() ) << "] is born from the union of ";
				std::cout << "[" << manip( lhs.getName() ) << "] and ";
				std::cout << "[" << manip( rhs.getName() ) << "]" << std::endl;
			}

			virtual void doOnFishDie( Fish const & fish )
			{
				std::cout << "[" << manip( fish.getName() ) << "] is dead. :'(" << std::endl;
			}

			virtual void doOnFishEatFish( Fish const & fish, Fish const & prey )
			{
				std::cout << "[" << manip( fish.getName() ) << "] is feeding on [" << manip( prey.getName() ) << "]." << std::endl;
			}

			virtual void doOnFishEatSeaweed( Fish const & fish, Seaweed const & prey )
			{
				std::cout << "[" << manip( fish.getName() ) << "] is feeding on a seaweed." << std::endl;
			}

			void doOnFishNoFood( Fish const & fish )
			{
				std::cout << "[" << manip( fish.getName() ) << "] is hungry, but no food." << std::endl;
			}

			void doOnFishNoMate( Fish const & fish )
			{
				std::cout << "[" << manip( fish.getName() ) << "] tried to reproduce, but no mate." << std::endl;
			}

			void doOnFishWrongMate( Fish const & fish, Fish const & mate )
			{
				std::cout << "[" << manip( fish.getName() ) << "] tried to reproduce, but mate was not compatible" << std::endl;
			}

			virtual void doOnFishSwitchGender( Fish const & fish, Gender gender )
			{
				std::cout << "[" << manip( fish.getName() ) << "] switches gender from " << manip( gender );
				std::cout << " to " << manip( fish.getGender() ) << "" << std::endl;
			}

			virtual void doOnSeaweedBorn( Seaweed const & seaweed, Seaweed const & parent )
			{
			}

			virtual void doOnSeaweedDie( Seaweed const & seaweed )
			{
			}
		};
	}
}

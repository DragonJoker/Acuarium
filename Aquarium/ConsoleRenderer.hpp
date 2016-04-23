#include "Prerequisites.hpp"

#include <AquariumRenderer.hpp>
#include <Fish.hpp>
#include <Seaweed.hpp>

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
				std::cout << m_aquarium << std::endl;
			}

			virtual void doOnFishBorn( FishPtr fish, FishPtr lhs, FishPtr rhs )
			{
				std::cout << "[" << manip( fish->getName() ) << "] is born from the union of ";
				std::cout << "[" << manip( lhs->getName() ) << "] and ";
				std::cout << "[" << manip( rhs->getName() ) << "]" << std::endl;
			}

			virtual void doOnFishDie( FishPtr fish )
			{
				std::cout << "[" << aquarium::manip( fish->getName() ) << "] is dead. :'(" << std::endl;
			}

			virtual void doOnFishEatFish( FishPtr fish, FishPtr prey )
			{
				std::cout << "[" << manip( fish->getName() ) << "] is feeding on [" << manip( prey->getName() ) << "]." << std::endl;
			}

			virtual void doOnFishEatSeaweed( FishPtr fish, SeaweedPtr prey )
			{
				std::cout << "[" << manip( fish->getName() ) << "] is feeding on a seaweed." << std::endl;
			}

			void doOnFishNoFood( FishPtr fish )
			{
				std::cout << "[" << aquarium::manip( fish->getName() ) << "] is hungry, but no food." << std::endl;
			}

			void doOnFishNoMate( FishPtr fish )
			{
				std::cout << "[" << aquarium::manip( fish->getName() ) << "] tried to reproduce, but no mate." << std::endl;
			}

			void doOnFishWrongMate( FishPtr fish, FishPtr mate )
			{
				std::cout << "[" << aquarium::manip( fish->getName() ) << "] tried to reproduce, but mate was not compatible" << std::endl;
			}

			virtual void doOnFishSwitchGender( FishPtr fish, Gender gender )
			{
				std::cout << "[" << aquarium::manip( fish->getName() ) << "] switches gender from " << aquarium::manip( gender );
				std::cout << " to " << aquarium::manip( fish->getGender() ) << "" << std::endl;
			}

			virtual void doOnSeaweedBorn( SeaweedPtr seaweed, SeaweedPtr parent )
			{
			}

			virtual void doOnSeaweedDie( SeaweedPtr seaweed )
			{
			}
		};
	}
}

#include "Aquarium.hpp"

#include "Seaweed.hpp"
#include "Fish.hpp"
#include "RaceFactory.hpp"

namespace aquarium
{
	void Aquarium::nextTurn()
	{
		try
		{
			doAddNewComers();

			for ( auto & seaweed : m_seaweeds )
			{
				auto child = seaweed.grow();

				if ( child )
				{
					addSeaweed( std::move( *child ) );
				}
			}

			for ( auto & current : m_fishes )
			{
				Fish * fish{ nullptr };
				Seaweed * seaweed{ nullptr };
				auto child = current.grow( m_fishes, m_seaweeds, fish, seaweed );

				if ( child )
				{
					onFishBorn( *child, current, *fish );
					addFish( std::move( *child ) );
				}
				else if ( fish )
				{
					onFishEatFish( current, *fish );
				}
				else if ( seaweed )
				{
					onFishEatSeaweed( current, *seaweed );
				}

			}
		}
		catch ( std::exception & exc )
		{
			std::cerr << "Error uncountered when moving to next turn: " << exc.what() << "\n";
		}
	}

	void Aquarium::updateLists()
	{
		try
		{
			doRemoveDead();
			doAddNewComers();
		}
		catch ( std::exception & exc )
		{
			std::cerr << "Error uncountered when updating aquarium: " << exc.what() << "\n";
		}
	}

	void Aquarium::addFish( Fish && fish )
	{
		fish.onDie.connect( [this]( Fish const & fish ) { onFishDie( fish ); } );
		fish.onNoFood.connect( [this]( Fish const & fish ) { onFishNoFood( fish ); } );
		fish.onNoMate.connect( [this]( Fish const & fish ) { onFishNoMate( fish ); } );
		fish.onWrongMate.connect( [this]( Fish const & fish, Fish const & mate ) { onFishWrongMate( fish, mate ); } );
		fish.onSwitchGender.connect( [this]( Fish const & fish, Gender gender ) { onFishSwitchGender( fish, gender ); } );
		m_newFishes.emplace_back( std::move( fish ) );
	}

	void Aquarium::addSeaweed( Seaweed && seaweed )
	{
		m_newSeaweeds.emplace_back( std::move( seaweed ) );
	}

	void Aquarium::doAddNewComers()
	{
		for ( auto & seaweed : m_newSeaweeds )
		{
			m_seaweeds.emplace_back( std::move( seaweed ) );
		}

		m_newSeaweeds.clear();

		for ( auto & fish : m_newFishes )
		{
			m_fishes.emplace_back( std::move( fish ) );
		}

		m_newFishes.clear();

		for ( auto & fish : m_fishes )
		{
			fish.resetReproduced();
		}

		std::sort( std::begin( m_seaweeds ), std::end( m_seaweeds ), []( Seaweed const & lhs, Seaweed const & rhs )
		{
			return lhs.getAge() < rhs.getAge()
				|| ( lhs.getAge() == rhs.getAge()
					 && lhs.getHealth() < rhs.getHealth() );
		} );

		std::sort( std::begin( m_fishes ), std::end( m_fishes ), []( Fish const & lhs, Fish const & rhs )
		{
			return lhs.getRace() < rhs.getRace()
				|| ( lhs.getRace() == rhs.getRace()
					 && ( lhs.getAge() < rhs.getAge()
						  || ( lhs.getAge() == rhs.getAge()
							   && lhs.getHealth() < rhs.getHealth() ) ) );
		} );
	}

	void Aquarium::doRemoveDead()
	{
		auto deadsw = std::remove_if( m_seaweeds.begin(), m_seaweeds.end(), []( Seaweed const & seaweed )
		{
			return !seaweed.isAlive();
		} );
		m_seaweeds.erase( deadsw, m_seaweeds.end() );

		auto deadf = std::remove_if( m_fishes.begin(), m_fishes.end(), []( Fish const & fish )
		{
			return !fish.isAlive();
		} );
		m_fishes.erase( deadf, m_fishes.end() );
	}

	std::ostream & operator<<( std::ostream & stream, Aquarium const & aqua )
	{
		stream << "Seaweeds: ";
		stream << aqua.getSeaweeds().size() << "\n";
		uint16_t age{ 0 };
		uint16_t health{ 0 };
		uint32_t count{ 0 };

		for ( auto const & seaweed : aqua.getSeaweeds() )
		{
			if ( seaweed.getAge() != age && seaweed.getHealth() != health && count > 0 )
			{
				stream << "(" << count << ") " << Seaweed{ age, health } << "\n";
				count = 0;
			}

			age = seaweed.getAge();
			health = seaweed.getHealth();
			++count;
		}

		if ( count > 0 )
		{
			stream << "(" << count << ") " << Seaweed{ age, health } << "\n";
		}

		stream << "Fishes: ";
		stream << aqua.getFishes().size() << "\n";

		for ( auto const & fish : aqua.getFishes() )
		{
			stream << fish << "\n";
		}

		return stream;
	}

	std::istream & operator>>( std::istream & stream, Aquarium & aqua )
	{
		std::string sdump;
		stream >> sdump; //Seaweeds: 
		size_t count{ 0 };
		stream >> count;
		stream.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
		size_t i{ 0 };

		while ( i < count )
		{
			char cdump{ 0 };
			stream >> cdump;// (
			size_t swcount{ 0 };
			stream >> swcount;
			stream >> cdump;// )

			Seaweed seaweed{ 0, 0 };
			stream >> seaweed;
			stream.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );

			for ( auto j = 0u; j < swcount; ++j )
			{
				aqua.addSeaweed( { seaweed.getAge(), seaweed.getHealth() } );
			}

			i += swcount;
		}

		stream >> sdump; //Fishes: 
		stream >> count;
		stream.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
		RaceFactory factory;

		for ( size_t i{ 0 }; i < count; ++i )
		{
			std::string raceName;
			stream >> raceName;
			stream.ignore( std::numeric_limits< std::streamsize >::max(), '[' );
			Fish fish{ factory.getRace( getRace( raceName ) ), 0, std::string{}, Male };
			stream >> fish;
			stream.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
			aqua.addFish( std::move( fish ) );
		}

		return stream;
	}
}

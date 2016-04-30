#include "Aquarium.hpp"

#include "Seaweed.hpp"
#include "Fish.hpp"
#include "RaceFactory.hpp"

namespace aquarium
{
	void Aquarium::addFish( Fish && fish )
	{
		fish.onDie.connect( [this]( Fish const & fish ) { onFishDie( fish ); } );
		fish.onNoFood.connect( [this]( Fish const & fish ) { onFishNoFood( fish ); } );
		fish.onNoMate.connect( [this]( Fish const & fish ) { onFishNoMate( fish ); } );
		fish.onWrongMate.connect( [this]( Fish const & fish, Fish const & mate ) { onFishWrongMate( fish, mate ); } );
		fish.onSwitchGender.connect( [this]( Fish const & fish, Gender gender ) { onFishSwitchGender( fish, gender ); } );
		m_fishes.emplace_back( std::move( fish ) );
	}

	void Aquarium::addSeaweed( Seaweed && seaweed )
	{
		seaweed.onDie.connect( [this]( Seaweed const & seaweed ) { onSeaweedDie( seaweed ); } );
		m_seaweeds.emplace_back( std::move( seaweed ) );
	}

	std::ostream & operator<<( std::ostream & stream, Aquarium const & aqua )
	{
		stream << "Seaweeds: ";
		stream << aqua.m_seaweeds.size() << "\n";
		uint16_t age{ 0 };
		uint16_t health{ 0 };
		uint32_t count{ 0 };

		for ( auto const & seaweed : aqua.m_seaweeds )
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
		stream << aqua.m_fishes.size() << "\n";

		for ( auto const & fish : aqua.m_fishes )
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

		for ( size_t j{ 0 }; j < count; ++j )
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

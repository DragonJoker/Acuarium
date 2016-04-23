#include "Fish.hpp"

namespace aquarium
{
	Fish::Fish( FishRace race, bool herbivore, bool carnivore, uint16_t age, std::string const & name, Gender gender )
		: Living{ age, 10u }
		, m_race{ race }
		, m_name{ name }
		, m_gender{ gender }
		, m_herbivore{ herbivore }
		, m_carnivore{ carnivore }
	{
	}

	void Fish::beEaten()
	{
		damage( 4 );
	}

	FishPtr Fish::grow( std::default_random_engine & engine, FishArray const & fishes, SeaweedArray const & seaweeds, FishPtr & fishOrMate, SeaweedPtr & seaweed )
	{
		FishPtr ret;
		age();
		damage( 1 );

		if ( isAlive() )
		{
			doGrow();

			if ( getHealth() <= 5 )
			{
				eat( engine, fishes, seaweeds, fishOrMate, seaweed );
			}
			else if ( canReproduce() )
			{
				ret = reproduce( engine, fishes, fishOrMate );
			}
		}

		return ret;
	}

	void Fish::switchGender()
	{
		auto old = m_gender;
		m_gender = Gender( 1 - m_gender );
		onSwitchGender( sharedFromThis(), old );
	}

	void Fish::eat( std::default_random_engine & engine, FishArray const & fishes, SeaweedArray const & seaweeds, FishPtr & fish, SeaweedPtr & seaweed )
	{
		try
		{
			doEat( engine, fishes, seaweeds, fish, seaweed );
			heal( 5 );
		}
		catch ( NoFoodException & )
		{
			onNoFood( sharedFromThis() );
		}
	}

	FishPtr Fish::reproduce( std::default_random_engine & engine, FishArray const & fishes, FishPtr & mate )
	{
		FishPtr child;

		try
		{
			child = doReproduce( engine, fishes, mate );
			hasReproduced();
			mate->hasReproduced();
		}
		catch ( NoMateException & )
		{
			onNoMate( sharedFromThis() );
		}
		catch ( WrongMateException & exc )
		{
			onWrongMate( sharedFromThis(), exc.getMate() );
		}

		return child;
	}

	void Fish::doDie()
	{
		onDie( sharedFromThis() );
	}

	std::ostream & operator<<( std::ostream & stream, Fish const & fish )
	{
		stream << aquarium::manip( fish.getRace() );
		stream << "\t" << aquarium::manip( fish.getName() );
		stream << "\t" << aquarium::manip( fish.getGender() );
		stream << static_cast< Living const & >( fish );
		return stream;
	}

	std::istream & operator>>( std::istream & stream, Fish & fish )
	{
		std::string genderName;
		std::getline( stream, fish.m_name, '\t' );
		fish.m_name = fish.m_name.substr( fish.m_name.find_first_not_of( " \t" ) );
		fish.m_name = fish.m_name.substr( 0, fish.m_name.find_last_not_of( " \t" ) + 1 );
		stream >> genderName;
		fish.m_gender = getGender( genderName );
		stream >> static_cast< Living & >( fish );
		return stream;
	}
}

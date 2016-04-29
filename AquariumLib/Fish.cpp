#include "Fish.hpp"

#include "FishRace.hpp"

namespace aquarium
{
	Fish::Fish( RacePtr race, uint16_t age, std::string const & name, Gender gender, uint16_t health )
		: Living{ age, health }
		, m_race{ race }
		, m_name{ name }
		, m_gender{ gender }
	{
		assert( gender == Female || gender == Male );
	}

	void Fish::beEaten()
	{
		damage( 4 );
	}

	FishPtr Fish::grow( FishArray & fishes, SeaweedArray & seaweeds, Fish *& fishOrMate, Seaweed *& seaweed )
	{
		FishPtr ret;
		age();
		damage( 1 );

		if ( isAlive() )
		{
			m_race->grow( *this );

			if ( m_reproduced )
			{
				m_reproduced--;
			}

			if ( getHealth() <= 5 )
			{
				eat( fishes, seaweeds, fishOrMate, seaweed );
			}
			else if ( canReproduce() )
			{
				ret = reproduce( fishes, fishOrMate );
			}
		}

		return ret;
	}

	void Fish::switchGender()
	{
		auto old = m_gender;
		m_gender = Gender( 1 - m_gender );
		onSwitchGender( *this, old );
	}

	void Fish::eat( FishArray & fishes, SeaweedArray & seaweeds, Fish *& fish, Seaweed *& seaweed )
	{
		try
		{
			m_race->eat( *this, fishes, seaweeds, fish, seaweed );
			heal( 5 );
		}
		catch ( NoFoodException & )
		{
			onNoFood( *this );
		}
	}

	FishPtr Fish::reproduce( FishArray & fishes, Fish *& mate )
	{
		FishPtr child;

		try
		{
			child = m_race->reproduce( *this, fishes, mate );
			hasReproduced();
			mate->hasReproduced();
		}
		catch ( NoMateException & )
		{
			onNoMate( *this );
		}
		catch ( WrongMateException & exc )
		{
			onWrongMate( *this, exc.getMate() );
		}

		return child;
	}

	void Fish::doDie()
	{
		onDie( *this );
	}

	std::ostream & operator<<( std::ostream & stream, Fish const & fish )
	{
		stream << fish.getRace()->getRace();
		stream << " [" << fish.getName() << "]";
		stream << " " << fish.getGender();
		stream << static_cast< Living const & >( fish );
		return stream;
	}

	std::istream & operator>>( std::istream & stream, Fish & fish )
	{
		uint16_t gender{ 0 };
		std::getline( stream, fish.m_name, ']' );
		stream >> gender;
		fish.m_gender = Gender( gender );
		stream >> static_cast< Living & >( fish );
		return stream;
	}
}

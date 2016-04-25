#pragma once

#include "Living.hpp"

namespace aquarium
{
	class Fish
		: public Living
	{
	public:
		Fish( RacePtr race, uint16_t age, std::string const & name, Gender gender );
		~Fish() = default;

		FishPtr grow( FishArray & fishes, SeaweedArray & seaweeds, Fish *& fishOrMate, Seaweed *& seaweed );
		void beEaten();

		void switchGender();

		inline RacePtr getRace() const
		{
			return m_race;
		}

		inline std::string const & getName() const
		{
			return m_name;
		}

		inline Gender getGender() const
		{
			return m_gender;
		}

		inline bool canReproduce() const
		{
			return !m_reproduced;
		}

		inline void resetReproduced()
		{
			m_reproduced = false;
		}

	protected:
		void eat( FishArray & fishes, SeaweedArray & seaweeds, Fish *& fish, Seaweed *& seaweed );
		FishPtr reproduce( FishArray & fishes, Fish *& mate );

	private:
		virtual void doDie();

		inline void hasReproduced()
		{
			m_reproduced = true;
		}

	public:
		Signal< std::function< void( Fish const & fish ) > > onDie;
		Signal< std::function< void( Fish const & fish ) > > onNoFood;
		Signal< std::function< void( Fish const & fish ) > > onNoMate;
		Signal< std::function< void( Fish const & fish, Fish const & mate ) > > onWrongMate;
		Signal< std::function< void( Fish const & fish, Gender ) > > onSwitchGender;

	private:
		RacePtr m_race;
		std::string m_name;
		Gender m_gender;
		bool m_reproduced{ false };

		friend std::istream & operator>>( std::istream & stream, Fish & fish );
	};

	std::ostream & operator<<( std::ostream & stream, Fish const & fish );
	std::istream & operator>>( std::istream & stream, Fish & fish );
}

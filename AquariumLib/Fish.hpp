#pragma once

#include "Living.hpp"

namespace aquarium
{
	class Fish
		: public Living
	{
	public:
		Fish( FishRace race, bool herbivore, bool carnivore, uint16_t age, std::string const & name, Gender gender );
		virtual ~Fish() = default;

		FishPtr grow( std::default_random_engine & engine, FishArray const & fishes, SeaweedArray const & seaweeds, FishPtr & fishOrMate, SeaweedPtr & seaweed );
		void beEaten();

		void switchGender();

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

		inline FishRace getRace() const
		{
			return m_race;
		}

		inline bool isCarnivore() const
		{
			return m_carnivore;
		}

		inline bool isHerbivore() const
		{
			return m_herbivore;
		}

	protected:
		void eat( std::default_random_engine & engine, FishArray const & fishes, SeaweedArray const & seaweeds, FishPtr & fish, SeaweedPtr & seaweed );
		FishPtr reproduce( std::default_random_engine & engine, FishArray const & fishes, FishPtr & mate );

	private:
		virtual void doDie();
		virtual void doGrow() = 0;
		virtual void doEat( std::default_random_engine & engine, FishArray const & fishes, SeaweedArray const & seaweeds, FishPtr & fish, SeaweedPtr & seaweed ) = 0;
		virtual FishPtr doReproduce( std::default_random_engine & engine, FishArray const & fishes, FishPtr & mate ) = 0;
		virtual FishPtr sharedFromThis() = 0;

		inline void hasReproduced()
		{
			m_reproduced = true;
		}

	public:
		Signal< std::function< void( FishPtr fish ) > > onDie;
		Signal< std::function< void( FishPtr fish ) > > onNoFood;
		Signal< std::function< void( FishPtr fish ) > > onNoMate;
		Signal< std::function< void( FishPtr fish, FishPtr mate ) > > onWrongMate;
		Signal< std::function< void( FishPtr fish, Gender ) > > onSwitchGender;

	private:
		FishRace const m_race;
		bool const m_herbivore;
		bool const m_carnivore;
		std::string m_name;
		Gender m_gender;
		bool m_reproduced{ false };

		friend std::istream & operator>>( std::istream & stream, Fish & fish );
	};

	std::ostream & operator<<( std::ostream & stream, Fish const & fish );
	std::istream & operator>>( std::istream & stream, Fish & fish );
}

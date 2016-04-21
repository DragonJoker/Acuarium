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

    FishPtr onNextTurn( std::default_random_engine & engine, FishArray const & fishes, SeaweedArray const & seaweeds );
    FishPtr reproduce( std::default_random_engine & engine, FishArray const & fishes );
    void eat( std::default_random_engine & engine, FishArray const & fishes, SeaweedArray const & seaweeds );
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

    inline void hasReproduced()
    {
      m_reproduced = true;
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

  private:
    virtual void doOnNextTurn() = 0;
    virtual void doEat( std::default_random_engine & engine, FishArray const & fishes, SeaweedArray const & seaweeds ) = 0;
    virtual FishPtr doReproduce( std::default_random_engine & engine, FishArray const & fishes ) = 0;

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

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

    void onNewTurn( Aquarium & aqua );
    void switchGender();
    void reproduce( Aquarium & aqua );
    void eat( Aquarium & aqua );

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
    virtual void doOnNewTurn( Aquarium & aqua ) = 0;
    virtual void doReproduce( Aquarium & aqua ) = 0;
    virtual void doEat( Aquarium & aqua ) = 0;

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

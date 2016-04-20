#pragma once

#include "Prerequisites.hpp"

namespace aquarium
{
  class Living
  {
  public:
    Living( uint16_t age, uint16_t health );

    void grow();
    void damage( uint16_t value );
    void heal( uint16_t value );

    inline bool isAlive() const
    {
      return m_health > 0;
    }

    inline uint16_t getHealth() const
    {
      return m_health;
    }

    inline uint16_t getAge() const
    {
      return m_age;
    }

  private:
    uint16_t m_health;
    uint16_t m_age;

    friend std::istream & operator>>( std::istream & stream, Living & living );
  };

  std::ostream & operator<<( std::ostream & stream, Living const & living );
  std::istream & operator>>( std::istream & stream, Living & living );
}

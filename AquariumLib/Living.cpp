#include "Living.hpp"

namespace aquarium
{
  Living::Living( uint16_t age, uint16_t health )
    : m_age{ age }
    , m_health{ health }
  {
  }

  void Living::grow()
  {
    if ( isAlive() )
    {
      ++m_age;

      if ( m_age >= 20 )
      {
        m_health = 0;
      }
    }
  }

  void Living::damage( uint16_t value )
  {
    if ( isAlive() )
    {
      if ( value >= m_health )
      {
        m_health = 0;
      }
      else
      {
        m_health -= value;
      }
    }
  }

  void Living::heal( uint16_t value )
  {
    if ( isAlive() )
    {
      m_health += value;
    }
  }

  std::ostream & operator<<( std::ostream & stream, Living const & living )
  {
    stream << " " << std::setw( 2 ) << std::left << living.getAge();
    stream << " " << std::setw( 2 ) << std::left << living.getHealth();
    return stream;
  }

  std::istream & operator>>( std::istream & stream, Living & living )
  {
    stream >> living.m_age;
    stream >> living.m_health;
    return stream;
  }
}

#include "Seaweed.hpp"

namespace aquarium
{
  Seaweed::Seaweed( uint16_t age, uint16_t health )
    : Living{ age, health }
  {
  }

  SeaweedPtr Seaweed::onNextTurn()
  {
    SeaweedPtr child;
    grow();

    if ( isAlive() )
    {
      child = doGrow();
    }

    return child;
  }

  SeaweedPtr Seaweed::doGrow()
  {
    SeaweedPtr child;

    if ( getHealth () >= 10 )
    {
      uint16_t const half( getHealth() / 2 );
      child = std::make_shared< Seaweed >( 0u, half );
      damage( half );
    }
    else
    {
      heal( 1 );
    }

    return child;
  }

  bool operator==( Seaweed const & lhs, Seaweed const & rhs )
  {
    return lhs.getAge() == rhs.getAge() && lhs.getHealth() == rhs.getHealth();
  }

  bool operator!=( Seaweed const & lhs, Seaweed const & rhs )
  {
    return lhs.getAge() != rhs.getAge() || lhs.getHealth() != rhs.getHealth();
  }

  std::ostream & operator<<( std::ostream & stream, Seaweed const & seaweed )
  {
    stream << "Seaweed";
    stream << static_cast< Living const & >( seaweed );
    return stream;
  }

  std::istream & operator>>( std::istream & stream, Seaweed & seaweed )
  {
    std::string dump;
    stream >> dump;// Seaweed
    stream >> static_cast< Living & >( seaweed );
    return stream;
  }
}

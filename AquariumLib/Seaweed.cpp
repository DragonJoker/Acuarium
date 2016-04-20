#include "Seaweed.hpp"

#include "Aquarium.hpp"

namespace aquarium
{
  Seaweed::Seaweed( uint16_t age, uint16_t health )
    : Living{ age, health }
  {
  }

  void Seaweed::onNewTurn( Aquarium & aqua )
  {
    grow();

    if ( isAlive() )
    {
      doGrow( aqua );
    }
  }

  void Seaweed::doGrow( Aquarium & aqua )
  {
    if ( getHealth () >= 10 )
    {
      uint16_t const half( getHealth() / 2 );
      auto child = std::make_shared< Seaweed >( 0u, half );
      aqua.addSeaweed( std::move( child ) );
	  damage( half );
    }
    else
    {
      heal( 1 );
    }
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
    stream >> dump;
    stream >> static_cast< Living & >( seaweed );
    return stream;
  }
}

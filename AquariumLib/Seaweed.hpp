﻿#pragma once

#include "Living.hpp"

namespace aquarium
{
  class Seaweed
    : public Living
  {
  public:
    Seaweed( uint16_t age, uint16_t health = 10 );

    SeaweedPtr onNextTurn();

  private:
    SeaweedPtr doGrow();
  };

  bool operator==( Seaweed const & lhs, Seaweed const & rhs );
  bool operator!=( Seaweed const & lhs, Seaweed const & rhs );
  std::ostream & operator<<( std::ostream & stream, Seaweed const & seaweed );
  std::istream & operator>>( std::istream & stream, Seaweed & seaweed );
}

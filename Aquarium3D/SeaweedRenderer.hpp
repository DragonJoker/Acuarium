#pragma once

#include "Prerequisites.hpp"

namespace render
{
  class SeaweedRenderer
  {
  public:
    SeaweedRenderer();
    ~SeaweedRenderer();

    void render( aquarium::Seaweed const & seaweed, Point const & position );
  };
}

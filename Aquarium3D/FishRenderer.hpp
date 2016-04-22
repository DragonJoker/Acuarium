#pragma once

#include "Prerequisites.hpp"

namespace render
{
  class FishRenderer
  {
  public:
    FishRenderer();
    ~FishRenderer();

    void render( aquarium::Fish const & fish, Point const & position );
  };
}

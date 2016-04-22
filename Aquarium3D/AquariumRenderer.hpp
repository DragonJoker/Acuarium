#pragma once

#include "FishRenderer.hpp"
#include "SeaweedRenderer.hpp"

namespace render
{
  class AquariumRenderer
  {
  public:
    AquariumRenderer( aquarium::Aquarium const & aqua );
    ~AquariumRenderer();

    void render();

  private:
    void doUpdate();

  private:
    aquarium::Aquarium const & m_aquarium;
    SeaweedRenderer m_seaweedRenderer;
    FishRenderer m_fishRenderer;
    SeaweedArray m_seaweeds;
    FishArray m_fishes;
  };
}

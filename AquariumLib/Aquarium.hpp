﻿#pragma once

#include "Prerequisites.hpp"

namespace aquarium
{
  class Aquarium
  {
  public:
    void newTurn();
    void update();
    void addFish( FishPtr && fish );
    void addSeaweed( SeaweedPtr && seaweed );

    inline bool hasFishes() const
    {
      return !m_fishes.empty() || !m_newFishes.empty();
    }

    inline bool hasSeaweeds() const
    {
      return !m_seaweeds.empty() || !m_newSeaweeds.empty();
    }

    inline FishArray const & getFishes() const
    {
      return m_fishes;
    }

    inline SeaweedArray const & getSeaweeds() const
    {
      return m_seaweeds;
    }

    inline std::random_device & getRandomEngine()
    {
      return m_engine;
    }

  private:
    void doAddNewComers();
    void doRemoveDead();

  private:
    FishArray m_fishes;
    FishArray m_newFishes;
    SeaweedArray m_seaweeds;
    SeaweedArray m_newSeaweeds;
    std::random_device m_engine;

    friend std::istream & operator>>( std::istream & stream, Aquarium & aqua );
  };

  std::ostream & operator<<( std::ostream & stream, Aquarium const & aqua );
  std::istream & operator>>( std::istream & stream, Aquarium & aqua );
}
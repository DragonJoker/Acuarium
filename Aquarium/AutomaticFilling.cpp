#include "Prerequisites.hpp"

#include <RaceFactory.hpp>
#include <Seaweed.hpp>
#include <Fish.hpp>

namespace
{
  void fillAquarium2Basses1Tuna( TurnAddsMap & turns )
  {
    aquarium::RaceFactory factory;
    auto adds = turns.insert( { 0, TurnAdds{} } ).first;
    adds->second.m_seaweeds.emplace_back( 0 );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Basse ), 0, "Basse_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Basse ), 0, "Basse_02", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Tuna ), 0, "Tuna_01", aquarium::Female );
  }

  void fillAquarium2OfEach( TurnAddsMap & turns )
  {
    aquarium::RaceFactory factory;
    auto adds = turns.insert( { 0, TurnAdds{} } ).first;
    adds->second.m_seaweeds.emplace_back( 0 );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Basse ), 0, "Basse_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Basse ), 0, "Basse_02", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Tuna ), 0, "Tuna_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Tuna ), 0, "Tuna_02", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Clown ), 0, "Clown_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Clown ), 0, "Clown_02", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Sole ), 0, "Sole_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Sole ), 0, "Sole_02", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Bass ), 0, "Bass_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Bass ), 0, "Bass_02", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Carp ), 0, "Carp_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Carp ), 0, "Carp_02", aquarium::Female );
  }

  void fillAquarium3OfEach( TurnAddsMap & turns )
  {
    aquarium::RaceFactory factory;
    auto adds = turns.insert( { 0, TurnAdds{} } ).first;
    adds->second.m_seaweeds.emplace_back( 0 );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Basse ), 0, "Basse_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Basse ), 0, "Basse_02", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Basse ), 0, "Basse_03", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Tuna ), 0, "Tuna_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Tuna ), 0, "Tuna_02", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Tuna ), 0, "Tuna_03", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Clown ), 0, "Clown_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Clown ), 0, "Clown_02", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Clown ), 0, "Clown_03", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Sole ), 0, "Sole_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Sole ), 0, "Sole_02", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Sole ), 0, "Sole_03", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Bass ), 0, "Bass_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Bass ), 0, "Bass_02", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Bass ), 0, "Bass_03", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Carp ), 0, "Carp_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Carp ), 0, "Carp_02", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Carp ), 0, "Carp_03", aquarium::Female );
  }

  void fillAquarium2OfEachCarnivore( TurnAddsMap & turns )
  {
    aquarium::RaceFactory factory;
    auto adds = turns.insert( { 0, TurnAdds{} } ).first;
    adds->second.m_seaweeds.emplace_back( 0 );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Basse ), 0, "Basse_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Basse ), 0, "Basse_02", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Tuna ), 0, "Tuna_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Tuna ), 0, "Tuna_02", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Clown ), 0, "Clown_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Clown ), 0, "Clown_02", aquarium::Female );
  }

  void fillAquarium3OfEachCarnivore( TurnAddsMap & turns )
  {
    aquarium::RaceFactory factory;
    auto adds = turns.insert( { 0, TurnAdds{} } ).first;
    adds->second.m_seaweeds.emplace_back( 0 );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Basse ), 0, "Basse_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Basse ), 0, "Basse_02", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Basse ), 0, "Basse_03", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Tuna ), 0, "Tuna_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Tuna ), 0, "Tuna_02", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Tuna ), 0, "Tuna_03", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Clown ), 0, "Clown_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Clown ), 0, "Clown_02", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Clown ), 0, "Clown_03", aquarium::Female );
  }

  void fillAquarium2OfEachHerbivore( TurnAddsMap & turns )
  {
    aquarium::RaceFactory factory;
    auto adds = turns.insert( { 0, TurnAdds{} } ).first;
    //adds->second.m_seaweeds.emplace_back( 0 );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Sole ), 0, "Sole_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Sole ), 0, "Sole_02", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Bass ), 0, "Bass_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Bass ), 0, "Bass_02", aquarium::Female );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Carp ), 0, "Carp_01", aquarium::Male );
    adds->second.m_fishes.emplace_back( factory.getRace( aquarium::Carp ), 0, "Carp_02", aquarium::Female );
  }
}

void autoFillAquarium( TurnAddsMap & turns )
{
  fillAquarium3OfEachCarnivore( turns );
}

#include "Prerequisites.hpp"

#include <Aquarium.hpp>
#include <Fish.hpp>
#include <FishFactory.hpp>
#include <Seaweed.hpp>

void fillAquarium2Basses1Tuna( TurnAddsMap & turns )
{
  aquarium::FishFactory factory;
  auto adds = turns.insert( { 0, TurnAdds{} } ).first;
  adds->second.m_seaweeds.emplace_back( std::make_shared< aquarium::Seaweed >( 0 ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Basse, 0, "Basse_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Basse, 0, "Basse_02", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Tuna, 0, "Tuna_01", aquarium::Female ) );
}

void fillAquarium2OfEach( TurnAddsMap & turns )
{
  aquarium::FishFactory factory;
  auto adds = turns.insert( { 0, TurnAdds{} } ).first;
  adds->second.m_seaweeds.emplace_back( std::make_shared< aquarium::Seaweed >( 0 ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Basse, 0, "Basse_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Basse, 0, "Basse_02", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Tuna, 0, "Tuna_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Tuna, 0, "Tuna_02", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Clown, 0, "Clown_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Clown, 0, "Clown_02", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Sole, 0, "Sole_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Sole, 0, "Sole_02", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Bass, 0, "Bass_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Bass, 0, "Bass_02", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Carp, 0, "Carp_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Carp, 0, "Carp_02", aquarium::Female ) );
}

void fillAquarium3OfEach( TurnAddsMap & turns )
{
  aquarium::FishFactory factory;
  auto adds = turns.insert( { 0, TurnAdds{} } ).first;
  adds->second.m_seaweeds.emplace_back( std::make_shared< aquarium::Seaweed >( 0 ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Basse, 0, "Basse_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Basse, 0, "Basse_02", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Basse, 0, "Basse_03", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Tuna, 0, "Tuna_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Tuna, 0, "Tuna_02", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Tuna, 0, "Tuna_03", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Clown, 0, "Clown_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Clown, 0, "Clown_02", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Clown, 0, "Clown_03", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Sole, 0, "Sole_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Sole, 0, "Sole_02", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Sole, 0, "Sole_03", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Bass, 0, "Bass_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Bass, 0, "Bass_02", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Bass, 0, "Bass_03", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Carp, 0, "Carp_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Carp, 0, "Carp_02", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Carp, 0, "Carp_03", aquarium::Female ) );
}

void fillAquarium2OfEachCarnivore( TurnAddsMap & turns )
{
  aquarium::FishFactory factory;
  auto adds = turns.insert( { 0, TurnAdds{} } ).first;
  adds->second.m_seaweeds.emplace_back( std::make_shared< aquarium::Seaweed >( 0 ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Basse, 0, "Basse_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Basse, 0, "Basse_02", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Tuna, 0, "Tuna_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Tuna, 0, "Tuna_02", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Clown, 0, "Clown_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Clown, 0, "Clown_02", aquarium::Female ) );
}

void fillAquarium3OfEachCarnivore( TurnAddsMap & turns )
{
  aquarium::FishFactory factory;
  auto adds = turns.insert( { 0, TurnAdds{} } ).first;
  adds->second.m_seaweeds.emplace_back( std::make_shared< aquarium::Seaweed >( 0 ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Basse, 0, "Basse_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Basse, 0, "Basse_02", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Basse, 0, "Basse_03", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Tuna, 0, "Tuna_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Tuna, 0, "Tuna_02", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Tuna, 0, "Tuna_03", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Clown, 0, "Clown_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Clown, 0, "Clown_02", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Clown, 0, "Clown_03", aquarium::Female ) );
}

void fillAquarium2OfEachHerbivore( TurnAddsMap & turns )
{
  aquarium::FishFactory factory;
  auto adds = turns.insert( { 0, TurnAdds{} } ).first;
  adds->second.m_seaweeds.emplace_back( std::make_shared< aquarium::Seaweed >( 0 ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Sole, 0, "Sole_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Sole, 0, "Sole_02", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Bass, 0, "Bass_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Bass, 0, "Bass_02", aquarium::Female ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Carp, 0, "Carp_01", aquarium::Male ) );
  adds->second.m_fishes.emplace_back( factory.createFish( aquarium::Carp, 0, "Carp_02", aquarium::Female ) );
}

void autoFillAquarium( TurnAddsMap & turns )
{
  fillAquarium3OfEachCarnivore( turns );
}

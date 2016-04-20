#include "FishFactory.hpp"

#include "RacedFish.hpp"

namespace aquarium
{
  FishFactory::FishFactory()
  {
    registerFishRace( Basse, RacedFish< Basse >::create );
    registerFishRace( Tuna, RacedFish< Tuna >::create );
    registerFishRace( Clown, RacedFish< Clown >::create );
    registerFishRace( Sole, RacedFish< Sole >::create );
    registerFishRace( Bass, RacedFish< Bass >::create );
    registerFishRace( Carp, RacedFish< Carp >::create );
  }

  void FishFactory::registerFishRace( FishRace race, FishCreator const & creator )
  {
    m_creators[race] = creator;
  }

  FishPtr FishFactory::createFish( FishRace race, uint16_t age, std::string const & name, Gender gender )const
  {
    auto it = m_creators.find( race );

    if ( it == m_creators.end() )
    {
      throw std::runtime_error{ "No creator registered for this fish race." };
    }

    return it->second( age, name, gender );
  }
}

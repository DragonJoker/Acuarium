namespace aquarium
{
  namespace helper
  {
    //*********************************************************************************************

    template< typename ExceptionT, typename LivingT, typename FuncT >
    LivingT const & doGetRandom( std::random_device & engine, std::vector< LivingT > const & array, FuncT func )
    {
      using LivingTArray = std::vector< LivingT >;
      using LivingTArrayConstIt = typename LivingTArray::const_iterator;
      std::vector< LivingTArrayConstIt > targets;

      for ( LivingTArrayConstIt it{ array.begin() }; it != array.end(); ++it )
      {
        if ( func( *it ) )
        {
          targets.push_back( it );
        }
      }

      if ( targets.empty() )
      {
        throw ExceptionT{};
      }

      std::uniform_int_distribution< size_t > distribution{ 0u, targets.size() - 1u };
      auto found = targets[distribution( engine )];
      return *found;
    }

    //*********************************************************************************************

    template< FishRace Race, typename Enable >
    struct FishEatT
    {
      static inline void eat( RacedFish< Race > & fish, Aquarium & aqua )
      {
        auto const & food = doGetRandom< NoFoodException >( aqua.getRandomEngine(), aqua.getFishes(), [&fish]( FishPtr const & candidate )
        {
          return candidate->isAlive() && candidate.get() != &fish && candidate->getRace() != fish.getRace();
        } );

        std::cout << "[" << manip( fish.getName() ) << "] is feeding on [" << manip( food->getName() ) << "].\n";
        food->damage( 4 );
        fish.heal( 5 );
      }
    };

    template< FishRace Race >
    struct FishEatT< Race, typename std::enable_if< IsHerbivore< Race >::value >::type >
    {
      static inline void eat( RacedFish< Race > & fish, Aquarium & aqua )
      {
        auto const & food = doGetRandom< NoFoodException >( aqua.getRandomEngine(), aqua.getSeaweeds(), []( SeaweedPtr const & seaweed )
        {
          return seaweed->isAlive();
        } );

        std::cout << "[" << manip( fish.getName() ) << "] is feeding on a seaweed.\n";
        food->damage( 2 );
        fish.heal( 3 );
      }
    };

    //*********************************************************************************************

    template< FishRace Race, typename Enable >
    struct FishNewTurnT
    {
      static inline void newTurn( RacedFish< Race > & fish, Aquarium & aqua )
      {
      }
    };

    template< FishRace Race >
    struct FishNewTurnT< Race, typename std::enable_if< IsAgingHernaphrodite< Race >::value >::type >
    {
      static inline void newTurn( RacedFish< Race > & fish, Aquarium & aqua )
      {
        if ( fish.getAge() == 10 && fish.getGender() == Male )
        {
          fish.switchGender();
        }
      }
    };

    //*********************************************************************************************

    struct FishReproduce
    {
    protected:
      static inline void doReproduce( Fish & fish, Fish & mate, FishRace race, Aquarium & aqua )
      {
        std::uniform_int_distribution< int > distribution{ 0, 1 };
        auto child = FishFactory{}.createFish( race, 0, getRandomName( aqua.getRandomEngine() ), Gender( distribution( aqua.getRandomEngine() ) ) );
        std::cout << "[" << manip( child->getName() ) << "] is born from the union of ";
        std::cout << "[" << manip( fish.getName() ) << "] and ";
        std::cout << "[" << manip( mate.getName() ) << "]\n";
        fish.hasReproduced();
        mate.hasReproduced();
        aqua.addFish( std::move( child ) );
      }
    };

    template< FishRace Race, typename Enable >
    struct FishReproduceT
      : public FishReproduce
    {
      static inline void reproduce( RacedFish< Race > & fish, Aquarium & aqua )
      {
        auto const & mate = doGetRandom< NoMateException >( aqua.getRandomEngine(), aqua.getFishes(), [&fish]( FishPtr const & candidate )
        {
          return candidate->isAlive() && candidate.get() != &fish && candidate->canReproduce();
        } );

        if ( mate->getRace() != fish.getRace() || mate->getGender() == fish.getGender() )
        {
          throw WrongMateException{};
        }

        FishReproduce::doReproduce( fish, *mate, Race, aqua );
      }
    };

    template< FishRace Race >
    struct FishReproduceT< Race, typename std::enable_if< IsOpportunisiticHernaphrodite< Race >::value >::type >
      : public FishReproduce
    {
      static inline void reproduce( RacedFish< Race > & fish, Aquarium & aqua )
      {
        auto const & mate = doGetRandom< NoMateException >( aqua.getRandomEngine(), aqua.getFishes(), [&fish]( FishPtr const & candidate )
        {
          return candidate->isAlive() && candidate.get() != &fish && candidate->canReproduce();
        } );

        if ( mate->getRace() != fish.getRace() )
        {
          throw WrongMateException{};
        }

        if ( mate->getGender() == fish.getGender() )
        {
          fish.switchGender();
        }

        FishReproduce::doReproduce( fish, *mate, Race, aqua );
      }
    };

    //*********************************************************************************************
  }
}

namespace aquarium
{
	namespace helper
	{
		//*********************************************************************************************

		namespace detail
		{
			template< typename ExceptionT, typename LivingT, typename FuncT >
			LivingT const & doGetRandom( std::default_random_engine & engine, std::vector< LivingT > const & array, FuncT func )
			{
				using LivingTArray = std::vector< LivingT >;
				using LivingTArrayConstIt = typename LivingTArray::const_iterator;
				std::vector< LivingTArrayConstIt > targets;

				for ( LivingTArrayConstIt it{ array.begin() }; it != array.end(); ++it )
				{
					auto candidate = *it;

					if ( candidate->isAlive() && func( candidate ) )
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
		}

		//*********************************************************************************************

		template< FishRace Race, typename Enable >
		struct FishGrowT
		{
			using RacedFishPtr = std::shared_ptr< RacedFish< Race > >;

			static inline void apply( RacedFishPtr fish )
			{
			}
		};

		template< FishRace Race >
		struct FishGrowT< Race, typename std::enable_if< IsAgingHermaphrodite< Race >::value >::type >
		{
			using RacedFishPtr = std::shared_ptr< RacedFish< Race > >;

			static inline void apply( RacedFishPtr fish )
			{
				if ( fish->getAge() == 10 && fish->getGender() == Male )
				{
					fish->switchGender();
				}
			}
		};

		//*********************************************************************************************

		template< FishRace Race, typename Enable >
		struct FishEatT
		{
			using RacedFishPtr = std::shared_ptr< RacedFish< Race > >;

			static inline void apply( RacedFishPtr predator, std::default_random_engine & engine, FishArray const & fishes, SeaweedArray const & seaweeds, FishPtr & fish, SeaweedPtr & seaweed )
			{
				auto food = detail::doGetRandom< NoFoodException >( engine, fishes, [&predator]( FishPtr const & candidate )
				{
					return candidate != predator && candidate->getRace() != predator->getRace();
				} );

				food->beEaten();
				fish = food;
			}
		};

		template< FishRace Race >
		struct FishEatT< Race, typename std::enable_if< IsHerbivore< Race >::value >::type >
		{
			using RacedFishPtr = std::shared_ptr< RacedFish< Race > >;

			static inline void apply( RacedFishPtr predator, std::default_random_engine & engine, FishArray const & fishes, SeaweedArray const & seaweeds, FishPtr & fish, SeaweedPtr & seaweed )
			{
				auto food = detail::doGetRandom< NoFoodException >( engine, seaweeds, []( SeaweedPtr const & seaweed )
				{
					return true;
				} );

				food->beEaten();
				seaweed = food;
			}
		};

		//*********************************************************************************************

		template< FishRace Race, typename Enable >
		struct FishReproduceT
		{
			using RacedFishPtr = std::shared_ptr< RacedFish< Race > >;

			static inline FishPtr apply( RacedFishPtr fish, std::default_random_engine & engine, FishArray const & fishes, FishPtr & mate )
			{
				auto found = detail::doGetRandom< NoMateException >( engine, fishes, [&fish]( FishPtr const & candidate )
				{
					return candidate != fish && candidate->canReproduce();
				} );

				if ( found->getRace() != fish->getRace() || found->getGender() == fish->getGender() )
				{
					throw WrongMateException{ found };
				}

				mate = found;
				return FishFactory{}.createFish( Race, 0, getRandomName( engine ), Gender( std::uniform_int_distribution< int >{ 0, 1 }( engine ) ) );
			}
		};

		template< FishRace Race >
		struct FishReproduceT< Race, typename std::enable_if< IsOpportunisiticHermaphrodite< Race >::value >::type >
		{
			using RacedFishPtr = std::shared_ptr< RacedFish< Race > >;

			static inline FishPtr apply( RacedFishPtr fish, std::default_random_engine & engine, FishArray const & fishes, FishPtr & mate )
			{
				auto found = detail::doGetRandom< NoMateException >( engine, fishes, [&fish]( FishPtr const & candidate )
				{
					return candidate != fish && candidate->canReproduce();
				} );

				if ( found->getRace() != fish->getRace() )
				{
					throw WrongMateException{ found };
				}

				if ( found->getGender() == fish->getGender() )
				{
					fish->switchGender();
				}

				mate = found;
				return FishFactory{}.createFish( Race, 0, getRandomName( engine ), Gender( std::uniform_int_distribution< int >{ 0, 1 }( engine ) ) );
			}
		};

		//*********************************************************************************************
	}
}

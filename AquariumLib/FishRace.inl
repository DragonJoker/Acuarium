#include "Exception.hpp"

namespace aquarium
{
	namespace helper
	{
		//*********************************************************************************************

		namespace detail
		{
			template< typename ExceptionT, typename LivingT, typename FuncT >
			LivingT & doGetRandom( std::vector< LivingT > & array, FuncT func )
			{
				using LivingTArray = std::vector< LivingT >;
				using LivingTArrayIt = typename LivingTArray::iterator;
				std::vector< LivingTArrayIt > targets;

				for ( LivingTArrayIt it{ array.begin() }; it != array.end(); ++it )
				{
					auto & candidate = *it;

					if ( candidate.isAlive() && func( candidate ) )
					{
						targets.push_back( it );
					}
				}

				if ( targets.empty() )
				{
					throw ExceptionT{};
				}

				auto found = targets[getRandom< size_t >( 0u, targets.size() )];
				return *found;
			}
		}

		//*********************************************************************************************

		template< FishRace RaceT, typename Enable >
		struct RaceGrowT
		{
			static inline void apply( Fish & )
			{
			}
		};

		template< FishRace RaceT >
		struct RaceGrowT< RaceT, typename std::enable_if< IsAgingHermaphrodite< RaceT >::value >::type >
		{
			static inline void apply( Fish & current )
			{
				if ( current.getAge() == 10 && current.getGender() == Male )
				{
					current.switchGender();
				}
			}
		};

		//*********************************************************************************************

		template< FishRace RaceT, typename Enable >
		struct RaceEatT
		{
			static inline void apply( Fish & current, FishArray & fishes, SeaweedArray &, Fish *& fish, Seaweed *& )
			{
				auto & food = detail::doGetRandom< NoFoodException >( fishes, [&current]( Fish const & candidate )
				{
					return &candidate != &current && candidate.getRace()->getRace() != RaceT;
				} );

				food.beEaten();
				fish = &food;
			}
		};

		template< FishRace RaceT >
		struct RaceEatT< RaceT, typename std::enable_if< ConsumerTypeGetter< RaceT >::value == Herbivore >::type >
		{
			static inline void apply( Fish &, FishArray &, SeaweedArray & seaweeds, Fish *&, Seaweed *& seaweed )
			{
				auto & food = detail::doGetRandom< NoFoodException >( seaweeds, []( Seaweed const & )
				{
					return true;
				} );

				food.beEaten();
				seaweed = &food;
			}
		};

		//*********************************************************************************************

		template< FishRace RaceT, typename Enable >
		struct RaceReproduceT
		{
			static inline FishPtr apply( Fish & current, FishArray & fishes, Fish *& mate )
			{
				auto & found = detail::doGetRandom< NoMateException >( fishes, [&current]( Fish const & candidate )
				{
					return &candidate != &current && candidate.canReproduce();
				} );

				if ( found.getRace()->getRace() != RaceT || found.getGender() == current.getGender() )
				{
					throw WrongMateException{ found };
				}

				mate = &found;
				return std::make_unique< Fish >( current.getRace(), 0, getRandomName(), Gender( getRandom( 0u, 2u ) ) );
			}
		};

		template< FishRace RaceT >
		struct RaceReproduceT< RaceT, typename std::enable_if< IsOpportunisiticHermaphrodite< RaceT >::value >::type >
		{
			static inline FishPtr apply( Fish & current, FishArray & fishes, Fish *& mate )
			{
				auto & found = detail::doGetRandom< NoMateException >( fishes, [&current]( Fish const & candidate )
				{
					return &candidate != &current && candidate.canReproduce();
				} );

				if ( found.getRace()->getRace() != RaceT )
				{
					throw WrongMateException{ found };
				}

				if ( found.getGender() == current.getGender() )
				{
					current.switchGender();
				}

				mate = &found;
				return std::make_unique< Fish >( current.getRace(), 0, getRandomName(), Gender( getRandom( 0u, 2u ) ) );
			}
		};

		//*********************************************************************************************
	}
}

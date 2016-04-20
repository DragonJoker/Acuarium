#pragma once

#include <algorithm>
#include <clocale>
#include <cstdint>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <regex>
#include <string>
#include <sstream>
#include <thread>
#include <vector>

namespace aquarium
{
  typedef enum Gender : uint16_t
  {
    Female,
    Male,
    GenderCount,
  } Gender;

  typedef enum FishRace : uint16_t
  {
    Basse,
    Tuna,
    Clown,
    Sole,
    Bass,
    Carp,
    RaceCount,
  } FishRace;

  template< FishRace Race > struct IsCarnivore : public std::false_type {};
  template<> struct IsCarnivore< Basse > : public std::true_type {};
  template<> struct IsCarnivore< Tuna > : public std::true_type {};
  template<> struct IsCarnivore< Clown > : public std::true_type {};

  template< FishRace Race > struct IsHerbivore : public std::false_type {};
  template<> struct IsHerbivore< Sole > : public std::true_type {};
  template<> struct IsHerbivore< Bass > : public std::true_type {};
  template<> struct IsHerbivore< Carp > : public std::true_type {};

  template< FishRace Race > struct IsMonoGender : public std::false_type {};
  template<> struct IsMonoGender< Carp > : public std::true_type {};
  template<> struct IsMonoGender< Tuna > : public std::true_type {};

  template< FishRace Race > struct IsAgingHernaphrodite : public std::false_type {};
  template<> struct IsAgingHernaphrodite< Bass > : public std::true_type {};
  template<> struct IsAgingHernaphrodite< Basse > : public std::true_type {};

  template< FishRace Race > struct IsOpportunisiticHernaphrodite : public std::false_type {};
  template<> struct IsOpportunisiticHernaphrodite< Sole > : public std::true_type {};
  template<> struct IsOpportunisiticHernaphrodite< Clown > : public std::true_type {};

  class Aquarium;
  class Living;
  class Fish;
  class Seaweed;
  template< FishRace Race >
  class RacedFish;

  using FishPtr = std::shared_ptr< Fish >;
  using SeaweedPtr = std::shared_ptr< Seaweed >;
  using FishCreator = std::function< FishPtr( uint16_t, std::string const &, Gender ) >;
  using FishArray = std::vector< FishPtr >;
  using SeaweedArray = std::vector< SeaweedPtr >;

  class NoFoodException
    : public std::exception
  {
  public:
    virtual char const * what() const noexcept
    {
        return "No more food";
    }
  };

  class NoMateException
    : public std::exception
  {
  public:
    virtual char const * what() const noexcept
    {
        return "No mate";
    }
  };

  class WrongMateException
    : public std::exception
  {
  public:
    virtual char const * what() const noexcept
    {
        return "Mate was not compatible";
    }
  };

  Gender getGender( std::string const & name );
  FishRace getRace( std::string const & name );
  std::string getRandomName( std::random_device & engine );

  struct NameManip
  {
    NameManip( std::string const & str );

    std::string const & m_str;
  };

  struct GenderManip
  {
    GenderManip( Gender gender );

    std::string m_str;
  };

  struct RaceManip
  {
    RaceManip( FishRace race );

    std::string m_str;
  };

  template< typename T >
  struct ManipCreator;

  template<>
  struct ManipCreator< std::string >
  {
    using type = NameManip;
  };

  template<>
  struct ManipCreator< Gender >
  {
    using type = GenderManip;
  };

  template<>
  struct ManipCreator< FishRace >
  {
    using type = RaceManip;
  };

  template< typename T >
  typename ManipCreator< T >::type manip( T const & value )
  {
    return typename ManipCreator< T >::type{ value };
  }

  std::ostream & operator<<( std::ostream & stream, NameManip const & manip );
  std::ostream & operator<<( std::ostream & stream, GenderManip const & manip );
  std::ostream & operator<<( std::ostream & stream, RaceManip const & manip );
}

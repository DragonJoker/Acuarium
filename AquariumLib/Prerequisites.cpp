#include "Prerequisites.hpp"

namespace aquarium
{
  namespace
  {
    std::string const & getGenderName( Gender gender )
    {
      static std::string const Names[GenderCount]
      {
        "Female",
        "Male"
      };

      return Names[gender];
    }

    std::string const & getRaceName( FishRace race )
    {
      static std::string const Names[RaceCount]
      {
        "Basse",
        "Tuna",
        "Clown",
        "Sole",
        "Bass",
        "Carp",
      };

      return Names[race];
    }
  }

  Gender getGender( std::string const & name )
  {
    static std::map< std::string, Gender > const Genders
    {
      { "Female", Female },
      { "Male", Male },
      { "Femelle", Female },
      { "Mâle", Male },
    };
    auto it = Genders.find( name );

    if ( it == Genders.end() )
    {
      throw std::runtime_error{ "Not a valid gender name." };
    }

    return it->second;
  }

  FishRace getRace( std::string const & name )
  {
    static std::map< std::string, FishRace > const Races
    {
      { "Basse", Basse },
      { "Tuna", Tuna },
      { "Clown", Clown },
      { "Sole", Sole },
      { "Bass", Bass },
      { "Carp", Carp },
      { "Mérou", Basse },
      { "Thon", Tuna },
      { "Poisson-clown", Clown },
      { "Sole", Sole },
      { "Bar", Bass },
      { "Carpe", Carp },
    };

    auto it = Races.find( name );

    if ( it == Races.end() )
    {
      throw std::runtime_error{ "Not a valid fish race name." };
    }

    return it->second;
  }

  std::string getRandomName( std::default_random_engine & engine )
  {
    std::uniform_int_distribution< size_t > countDistribution{ 5, 10 };
    std::uniform_int_distribution< int32_t > charDistribution{ 32, 126 };
    std::stringstream ret;
    auto const count = countDistribution( engine );

    for ( size_t i{ 0u }; i < count; ++i )
    {
      ret << char( charDistribution( engine ) );
    }

    return ret.str();
  }

  NameManip::NameManip( std::string const & str )
    : m_str{ str }
  {
  }

  GenderManip::GenderManip( Gender gender )
    : m_str{ getGenderName( gender ) }
  {
  }

  RaceManip::RaceManip( FishRace race )
    : m_str{ getRaceName( race ) }
  {
  }

  std::ostream & operator<<( std::ostream & stream, NameManip const & manip )
  {
    stream << std::setw( 15 ) << std::left << manip.m_str;
    return stream;
  }

  std::ostream & operator<<( std::ostream & stream, GenderManip const & manip )
  {
    stream << std::setw( 6 ) << std::left << manip.m_str;
    return stream;
  }

  std::ostream & operator<<( std::ostream & stream, RaceManip const & manip )
  {
    stream << std::setw( 5 ) << std::left << manip.m_str;
    return stream;
  }
}

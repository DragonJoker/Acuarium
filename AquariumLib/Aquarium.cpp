#include "Aquarium.hpp"

#include "Seaweed.hpp"
#include "Fish.hpp"
#include "FishFactory.hpp"

namespace aquarium
{
  void Aquarium::newTurn()
  {
    doAddNewComers();

    for ( auto & seaweed : m_seaweeds )
    {
      seaweed->onNewTurn( *this );
    }

    for ( auto & fish : m_fishes )
    {
      fish->onNewTurn( *this );
    }
  }

  void Aquarium::update()
  {
    doRemoveDead();
    doAddNewComers();
  }

  void Aquarium::addFish( FishPtr && fish )
  {
    m_newFishes.emplace_back( std::move( fish ) );
  }

  void Aquarium::addSeaweed( SeaweedPtr && seaweed )
  {
    m_newSeaweeds.emplace_back( std::move( seaweed ) );
  }

  void Aquarium::doAddNewComers()
  {
    for ( auto & seaweed : m_newSeaweeds )
    {
      m_seaweeds.push_back( std::move( seaweed ) );
    }

    m_newSeaweeds.clear();

    for ( auto & fish : m_newFishes )
    {
      m_fishes.push_back( std::move( fish ) );
    }

    m_newFishes.clear();

    for ( auto & fish : m_fishes )
    {
      fish->resetReproduced();
    }

    std::sort( std::begin( m_seaweeds ), std::end( m_seaweeds ), []( SeaweedPtr const & lhs, SeaweedPtr const & rhs )
    {
      return lhs->getAge() < rhs->getAge()
          || ( lhs->getAge() == rhs->getAge() && lhs->getHealth() < rhs->getHealth() );
    } );

    std::sort( std::begin( m_fishes ), std::end( m_fishes ), []( FishPtr const & lhs, FishPtr const & rhs )
    {
      return lhs->getRace() < rhs->getRace()
          || ( lhs->getRace() == rhs->getRace()
            && ( lhs->getAge() < rhs->getAge()
              || ( lhs->getAge() == rhs->getAge() && lhs->getHealth() < rhs->getHealth() ) ) );
    } );
  }

  void Aquarium::doRemoveDead()
  {
    auto deadsw = std::remove_if( m_seaweeds.begin(), m_seaweeds.end(), []( SeaweedPtr const & seaweed )
    {
      return !seaweed->isAlive();
    } );
    m_seaweeds.erase( deadsw, m_seaweeds.end() );

    auto deadf = std::remove_if( m_fishes.begin(), m_fishes.end(), []( FishPtr const & fish )
    {
      if ( !fish->isAlive() )
      {
        std::cout << "[" << aquarium::manip( fish->getName() ) << "] is dead. :'(\n";
      }

      return !fish->isAlive();
    } );
    m_fishes.erase( deadf, m_fishes.end() );
  }

  std::ostream & operator<<( std::ostream & stream, Aquarium const & aqua )
  {
    stream << "Seaweeds: ";
    stream << aqua.getSeaweeds().size() << "\n";
    Seaweed previous{ 0, 0 };
    uint32_t count{ 0 };

    for ( auto const & seaweed : aqua.getSeaweeds() )
    {
      if ( *seaweed != previous && count > 0 )
      {
        stream << "(" << std::setw( 3 ) << std::left << count << ") " << previous << "\n";
        count = 0;
      }

      ++count;
      previous = *seaweed;
    }

    if ( count > 0 )
    {
      stream << "(" << std::setw( 3 ) << std::left << count << ") " << previous << "\n";
    }

    stream << "Fishes: ";
    stream << aqua.getFishes().size() << "\n";

    for ( auto const & fish : aqua.getFishes() )
    {
      stream << *fish << "\n";
    }

    return stream;
  }

  std::istream & operator>>( std::istream & stream, Aquarium & aqua )
  {
    std::string sdump;
    stream >> sdump; //Seaweeds: 
    size_t count{ 0 };
    stream >> count;
    stream.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
    size_t i{ 0 };

    while ( i < count )
    {
      char cdump{ 0 };
      stream >> cdump;// (
      size_t swcount{ 0 };
      stream >> swcount;
      stream >> cdump;// )

      Seaweed seaweed{ 0, 0 };
      stream >> seaweed;
      stream.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );

      for ( auto j = 0u; j < swcount; ++j )
      {
        aqua.m_seaweeds.emplace_back( std::make_shared< Seaweed >( seaweed ) );
      }

      i += swcount;
    }

    stream >> sdump; //Fishes: 
    stream >> count;
    stream.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
    FishFactory factory;

    for ( size_t i{ 0 }; i < count; ++i )
    {
      std::string raceName;
      stream >> raceName;
      stream.ignore( std::numeric_limits< std::streamsize >::max(), '\t' );
      FishPtr fish = factory.createFish( getRace( raceName ), 0, std::string{}, Male );
      stream >> *fish;
      stream.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
      aqua.m_fishes.emplace_back( std::move( fish ) );
    }

    return stream;
  }
}

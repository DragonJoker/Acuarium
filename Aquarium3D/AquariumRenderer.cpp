#include "AquariumRenderer.hpp"

#include <Aquarium.hpp>

#if defined( _WIN32 )
#include "Windows.h"
#endif

#include <gl/GL.h>

namespace render
{
  namespace
  {
    template< typename LivingT >
    using LivingTPtr = std::shared_ptr< LivingT >;
    template< typename LivingT >
    using  LivingTArray = std::vector< LivingTPtr< LivingT > >;
    template< typename LivingT >
    using  PlacedLivingT = std::pair< LivingTPtr< LivingT >, Point >;
    template< typename LivingT >
    using  PlacedLivingTArray = std::vector< PlacedLivingT< LivingT > >;

    template< typename LivingT >
    void doUpdatePlaced( LivingTArray< LivingT > const & livings, PlacedLivingTArray< LivingT > & placedLivings )
    {
      std::vector< typename PlacedLivingTArray< LivingT >::iterator > toRemove;
      std::vector< typename PlacedLivingTArray< LivingT > > toAdd;


    }
  }

  AquariumRenderer::AquariumRenderer( aquarium::Aquarium const & aqua )
    : m_aquarium{ aqua }
  {
  }

  AquariumRenderer::~AquariumRenderer()
  {
  }

  void AquariumRenderer::render()
  {
    doUpdate();

    for ( auto seaweed : m_seaweeds )
    {
      m_seaweedRenderer.render( *seaweed.first, seaweed.second );
    }

    for ( auto fish : m_fishes )
    {
      m_fishRenderer.render( *fish.first, fish.second );
    }
  }

  void AquariumRenderer::doUpdate()
  {
    doUpdatePlaced( m_aquarium.getFishes(), m_fishes );
    doUpdatePlaced( m_aquarium.getSeaweeds(), m_seaweeds );
  }
}

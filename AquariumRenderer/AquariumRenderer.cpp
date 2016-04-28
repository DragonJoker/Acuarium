#include "AquariumRenderer.hpp"

#include <Fish.hpp>
#include <Seaweed.hpp>

namespace aquarium
{
	namespace render
	{
		namespace
		{
			std::shared_ptr< Fish > copy( Fish const & fish )
			{
				return std::make_shared< Fish >( fish.getRace(), fish.getAge(), fish.getName(), fish.getGender(), fish.getHealth() );
			}

			std::shared_ptr< Seaweed > copy( Seaweed const & seaweed )
			{
				return std::make_shared<Seaweed >( seaweed.getAge(), seaweed.getHealth() );
			}
		}

		AquariumRenderer::AquariumRenderer( aquarium::Aquarium const & aqua, FishRendererPtr && p_fr, SeaweedRendererPtr && p_sr )
			: m_aquarium{ aqua }
			, m_fishRenderer{ std::move( p_fr ) }
			, m_seaweedRenderer{ std::move( p_sr ) }
		{
		}

		AquariumRenderer::~AquariumRenderer()
		{
			m_aquarium.onFishBorn.disconnect( m_connOnFishBorn );
			m_aquarium.onFishDie.disconnect( m_connOnFishDie );
			m_aquarium.onFishEatFish.disconnect( m_connOnFishEatFish );
			m_aquarium.onFishEatSeaweed.disconnect( m_connOnFishEatSeaweed );
			m_aquarium.onFishNoFood.disconnect( m_connOnFishNoFood );
			m_aquarium.onFishNoMate.disconnect( m_connOnFishNoMate );
			m_aquarium.onFishWrongMate.disconnect( m_connOnFishWrongMate );
			m_aquarium.onFishSwitchGender.disconnect( m_connOnFishSwithGender );
			m_aquarium.onSeaweedBorn.disconnect( m_connOnSeaweedBorn );
			m_aquarium.onSeaweedDie.disconnect( m_connOnSeaweedDie );
		}

		void AquariumRenderer::render( uint32_t turn )
		{
			doPreRender( turn );
			ActionArray actions = doSwapActions();

			for ( auto action : actions )
			{
				action();
			}

			doRender();
		}

		void AquariumRenderer::initialise( Aquarium const & aqua )
		{
			m_connOnFishBorn = aqua.onFishBorn.connect( [this]( Fish const & fish, Fish const & lhs, Fish const & rhs )
			{
				auto copyFish{ copy( fish ) };
				auto copyLhs{ copy( lhs ) };
				auto copyRhs{ copy( rhs ) };
				doPushAction( [this, copyFish, copyLhs, copyRhs]()
				{
					m_fishRenderer->renderBorn( *copyFish, *copyLhs, *copyRhs );
				} );
			} );
			m_connOnFishDie = aqua.onFishDie.connect( [this]( Fish const & fish )
			{
				auto copyFish{ copy( fish ) };
				doPushAction( [this, copyFish]
				{
					m_fishRenderer->renderDie( *copyFish );
				} );
			} );
			m_connOnFishEatFish = aqua.onFishEatFish.connect( [this]( Fish const & fish, Fish const & prey )
			{
				auto copyFish{ copy( fish ) };
				auto copyPrey{ copy( prey ) };
				doPushAction( [this, copyFish, copyPrey]()
				{
					m_fishRenderer->renderEat( *copyFish, *copyPrey );
				} );
			} );
			m_connOnFishEatSeaweed = aqua.onFishEatSeaweed.connect( [this]( Fish const & fish, Seaweed const & prey )
			{
				auto copyFish{ copy( fish ) };
				auto copyPrey{ copy( prey ) };
				doPushAction( [this, &copyFish, &copyPrey]()
				{
					m_fishRenderer->renderEat( *copyFish, *copyPrey );
				} );
			} );
			m_connOnFishNoFood = aqua.onFishNoFood.connect( [this]( Fish const & fish )
			{
				auto copyFish{ copy( fish ) };
				doPushAction( [this, copyFish]
				{
					m_fishRenderer->renderNoFood( *copyFish );
				} );
			} );
			m_connOnFishNoMate = aqua.onFishNoMate.connect( [this]( Fish const & fish )
			{
				auto copyFish{ copy( fish ) };
				doPushAction( [this, copyFish]
				{
					m_fishRenderer->renderNoMate( *copyFish );
				} );
			} );
			m_connOnFishWrongMate = aqua.onFishWrongMate.connect( [this]( Fish const & fish, Fish const & mate )
			{
				auto copyFish{ copy( fish ) };
				auto copyMate{ copy( mate ) };
				doPushAction( [this, copyFish, copyMate]
				{
					m_fishRenderer->renderWrongMate( *copyFish, *copyMate );
				} );
			} );
			m_connOnFishSwithGender = aqua.onFishSwitchGender.connect( [this]( Fish const & fish, Gender gender )
			{
				auto copyFish{ copy( fish ) };
				doPushAction( [this, copyFish, gender]
				{
					m_fishRenderer->renderSwitchGender( *copyFish, gender );
				} );
			} );
			m_connOnSeaweedBorn = aqua.onSeaweedBorn.connect( [this]( Seaweed const & seaweed, Seaweed const & parent )
			{
				auto copySeaweed{ copy( seaweed ) };
				auto copyParent{ copy( parent ) };
				doPushAction( [this, copySeaweed, copyParent]()
				{
					m_seaweedRenderer->renderBorn( *copySeaweed, *copyParent );
				} );
			} );
			m_connOnSeaweedDie = aqua.onSeaweedDie.connect( [this]( Seaweed const & seaweed )
			{
				auto copySeaweed{ copy( seaweed ) };
				doPushAction( [this, copySeaweed]()
				{
					m_seaweedRenderer->renderDie( *copySeaweed );
				} );
			} );
		}

		AquariumRenderer::ActionArray AquariumRenderer::doSwapActions()
		{
			ActionArray actions;
			auto l_lock = make_unique_lock( m_mutex );
			std::swap( m_actions, actions );
			return actions;
		}

		void AquariumRenderer::doPushAction( Action const & action )
		{
			m_actions.push_back( action );
		}
	}
}

#include "AquariumRenderer.hpp"

#include <Fish.hpp>
#include <Seaweed.hpp>

namespace aquarium
{
	namespace render
	{
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

			doRender( turn );
		}

		void AquariumRenderer::initialise( Aquarium const & aqua )
		{
			m_connOnFishBorn = aqua.onFishBorn.connect( [this]( FishPtr fish, FishPtr lhs, FishPtr rhs )
			{
				doPushAction( [this, fish, lhs, rhs]()
				{
					doOnFishBorn( fish, lhs, rhs );
				} );
			} );
			m_connOnFishDie = aqua.onFishDie.connect( [this]( FishPtr fish )
			{
				doPushAction( [this, fish]
				{
					doOnFishDie( fish );
				} );
			} );
			m_connOnFishEatFish = aqua.onFishEatFish.connect( [this]( FishPtr fish, FishPtr prey )
			{
				doPushAction( [this, fish, prey]()
				{
					doOnFishEatFish( fish, prey );
				} );
			} );
			m_connOnFishEatSeaweed = aqua.onFishEatSeaweed.connect( [this]( FishPtr fish, SeaweedPtr prey )
			{
				doPushAction( [this, fish, prey]()
				{
					doOnFishEatSeaweed( fish, prey );
				} );
			} );
			m_connOnFishNoFood = aqua.onFishNoFood.connect( [this]( FishPtr fish )
			{
				doPushAction( [this, fish]
				{
					doOnFishNoFood( fish );
				} );
			} );
			m_connOnFishNoMate = aqua.onFishNoMate.connect( [this]( FishPtr fish )
			{
				doPushAction( [this, fish]
				{
					doOnFishNoMate( fish );
				} );
			} );
			m_connOnFishWrongMate = aqua.onFishWrongMate.connect( [this]( FishPtr fish, FishPtr mate )
			{
				doPushAction( [this, fish, mate]
				{
					doOnFishWrongMate( fish, mate );
				} );
			} );
			m_connOnFishSwithGender = aqua.onFishSwitchGender.connect( [this]( FishPtr fish, Gender gender )
			{
				doPushAction( [this, fish, gender]
				{
					doOnFishSwitchGender( fish, gender );
				} );
			} );
			m_connOnSeaweedBorn = aqua.onSeaweedBorn.connect( [this]( SeaweedPtr seaweed, SeaweedPtr parent )
			{
				doPushAction( [this, seaweed, parent]()
				{
					doOnSeaweedBorn( seaweed, parent );
				} );
			} );
			m_connOnSeaweedDie = aqua.onSeaweedDie.connect( [this]( SeaweedPtr seaweed )
			{
				doPushAction( [this, seaweed]()
				{
					doOnSeaweedDie( seaweed );
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

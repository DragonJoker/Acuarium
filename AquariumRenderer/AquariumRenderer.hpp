#pragma once

#include "FishRenderer.hpp"
#include "SeaweedRenderer.hpp"

#include <Aquarium.hpp>

namespace aquarium
{
	namespace render
	{
		class AquariumRenderer
		{
			using Action = std::function< void() >;
			using ActionArray = std::vector< Action >;

		protected:
			AquariumRenderer( Aquarium const & aqua, FishRendererPtr && p_fr, SeaweedRendererPtr && p_sr );
			~AquariumRenderer();

		public:
			void render( uint32_t turn );

			inline void lock()
			{
				m_mutex.lock();
			}

			inline void unlock()
			{
				m_mutex.unlock();
			}

		protected:
			void initialise( Aquarium const & aqua );

		private:
			void doPushAction( Action const & p_action );
			ActionArray doSwapActions();

			virtual void doPreRender( uint32_t turn ) = 0;
			virtual void doRender( uint32_t turn ) = 0;
			virtual void doOnFishBorn( FishPtr fish, FishPtr lhs, FishPtr rhs ) = 0;
			virtual void doOnFishDie( FishPtr fish ) = 0;
			virtual void doOnFishEatFish( FishPtr fish, FishPtr prey ) = 0;
			virtual void doOnFishEatSeaweed( FishPtr fish, SeaweedPtr prey ) = 0;
			virtual void doOnFishNoFood( FishPtr fish ) = 0;
			virtual void doOnFishNoMate( FishPtr fish ) = 0;
			virtual void doOnFishWrongMate( FishPtr fish, FishPtr mate ) = 0;
			virtual void doOnFishSwitchGender( FishPtr fish, Gender gender ) = 0;
			virtual void doOnSeaweedBorn( SeaweedPtr seaweed, SeaweedPtr parent ) = 0;
			virtual void doOnSeaweedDie( SeaweedPtr seaweed ) = 0;

		protected:
			aquarium::Aquarium const & m_aquarium;

		private:
			std::mutex m_mutex;
			ActionArray m_actions;
			SeaweedRendererPtr m_seaweedRenderer;
			FishRendererPtr m_fishRenderer;
			uint32_t m_connOnFishBorn{ 0 };
			uint32_t m_connOnFishDie{ 0 };
			uint32_t m_connOnFishEatFish{ 0 };
			uint32_t m_connOnFishNoFood{ 0 };
			uint32_t m_connOnFishNoMate{ 0 };
			uint32_t m_connOnFishWrongMate{ 0 };
			uint32_t m_connOnFishSwithGender{ 0 };
			uint32_t m_connOnFishEatSeaweed{ 0 };
			uint32_t m_connOnSeaweedBorn{ 0 };
			uint32_t m_connOnSeaweedDie{ 0 };
		};
	}
}

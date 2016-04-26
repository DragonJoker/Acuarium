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
			// Derived classes must call this function from constructor
			void initialise( Aquarium const & aqua );

		private:
			void doPushAction( Action const & p_action );
			ActionArray doSwapActions();

			virtual void doPreRender( uint32_t turn ) = 0;
			virtual void doRender( uint32_t turn ) = 0;
			virtual void doOnFishBorn( Fish const & fish, Fish const & lhs, Fish const & rhs ) = 0;
			virtual void doOnFishDie( Fish const & fish ) = 0;
			virtual void doOnFishEatFish( Fish const & fish, Fish const & prey ) = 0;
			virtual void doOnFishEatSeaweed( Fish const & fish, Seaweed const & prey ) = 0;
			virtual void doOnFishNoFood( Fish const & fish ) = 0;
			virtual void doOnFishNoMate( Fish const & fish ) = 0;
			virtual void doOnFishWrongMate( Fish const & fish, Fish const & mate ) = 0;
			virtual void doOnFishSwitchGender( Fish const & fish, Gender gender ) = 0;
			virtual void doOnSeaweedBorn( Seaweed const & seaweed, Seaweed const & parent ) = 0;
			virtual void doOnSeaweedDie( Seaweed const & seaweed ) = 0;

		protected:
			aquarium::Aquarium const & m_aquarium;
			SeaweedRendererPtr m_seaweedRenderer;
			FishRendererPtr m_fishRenderer;

		private:
			std::mutex m_mutex;
			ActionArray m_actions;
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

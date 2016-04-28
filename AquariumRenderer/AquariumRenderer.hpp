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
			virtual void doRender() = 0;

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

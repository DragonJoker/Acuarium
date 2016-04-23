#pragma once

#include "AquariumPrerequisites.hpp"

#include <functional>

namespace aquarium
{
	template< typename Function >
	class Signal
	{
	public:
		uint32_t connect( Function p_function )
		{
			uint32_t l_return = uint32_t( m_slots.size() ) + 1;
			m_slots.insert( std::make_pair( l_return, p_function ) );
			return l_return;
		}

		void disconnect( uint32_t p_index )
		{
			auto it = m_slots.find( p_index );

			if ( it != m_slots.end() )
			{
				m_slots.erase( it );
			}
		}

		void operator()()const
		{
			for ( auto it = m_slots.begin(); it != m_slots.end(); ++it )
			{
				it->second();
			}
		}

		template< typename ... Params >
		void operator()( Params && ... p_params )const
		{
			for ( auto it = m_slots.begin(); it != m_slots.end(); ++it )
			{
				it->second( std::forward< Params >( p_params )... );
			}
		}

	private:
		std::map< uint32_t, Function > m_slots;
	};
}

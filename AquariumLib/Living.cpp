#include "Living.hpp"

namespace aquarium
{
	uint64_t Living::sm_count = 0;

	Living::Living( uint16_t age, uint16_t health )
		: m_id{ ++sm_count }
		, m_age{ age }
		, m_health{ health }
	{
	}

	void Living::age()
	{
		if ( isAlive() )
		{
			++m_age;

			if ( m_age >= 20 )
			{
				die();
			}
		}
	}

	void Living::damage( uint16_t value )
	{
		if ( isAlive() )
		{
			if ( value >= m_health )
			{
				die();
			}
			else
			{
				m_health -= value;
			}
		}
	}

	void Living::heal( uint16_t value )
	{
		if ( isAlive() )
		{
			if ( std::numeric_limits< uint16_t >::max() - value < m_health )
			{
				m_health = std::numeric_limits< uint16_t >::max();
			}
			else
			{
				m_health += value;
			}
		}
	}

	void Living::die()
	{
		if ( isAlive() )
		{
			doDie();
		}

		m_health = 0;
	}

	std::ostream & operator<<( std::ostream & stream, Living const & living )
	{
		stream << " " << living.getAge();
		stream << " " << living.getHealth();
		return stream;
	}

	std::istream & operator>>( std::istream & stream, Living & living )
	{
		stream >> living.m_age;
		stream >> living.m_health;
		return stream;
	}
}

#pragma once

#include "Signal.hpp"

namespace aquarium
{
	class Living
	{
	protected:
		Living( uint16_t age, uint16_t health );
		~Living() = default;
		Living( Living const & ) = delete;
		Living & operator=( Living const & ) = delete;
		Living( Living && ) = default;
		Living & operator=( Living && ) = default;

	public:
		inline bool isAlive() const
		{
			return m_health > 0;
		}

		inline uint16_t getHealth() const
		{
			return m_health;
		}

		inline uint16_t getAge() const
		{
			return m_age;
		}

	protected:
		void age();
		void damage( uint16_t value );
		void heal( uint16_t value );
		void die();

	private:
		virtual void doDie() = 0;

	private:
		uint16_t m_health;
		uint16_t m_age;

		friend std::istream & operator>>( std::istream & stream, Living & living );
	};

	std::ostream & operator<<( std::ostream & stream, Living const & living );
	std::istream & operator>>( std::istream & stream, Living & living );
}

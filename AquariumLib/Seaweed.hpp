#pragma once

#include "Living.hpp"

namespace aquarium
{
	class Seaweed
		: public Living
		, public std::enable_shared_from_this< Seaweed >
		, private NonCopyable
	{
	public:
		Seaweed( uint16_t age, uint16_t health = 10 );
		virtual ~Seaweed() = default;

		SeaweedPtr grow();
		void beEaten();

	public:
		Signal< std::function< void( SeaweedPtr seaweed ) > > onDie;
		Signal< std::function< void( SeaweedPtr seaweed, SeaweedPtr parent ) > > onBorn;

	private:
		virtual void doDie();
		SeaweedPtr doGrow();
	};

	bool operator==( Seaweed const & lhs, Seaweed const & rhs );
	bool operator!=( Seaweed const & lhs, Seaweed const & rhs );
	std::ostream & operator<<( std::ostream & stream, Seaweed const & seaweed );
	std::istream & operator>>( std::istream & stream, Seaweed & seaweed );
}

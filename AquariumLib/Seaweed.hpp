#pragma once

#include "Living.hpp"

namespace aquarium
{
	class Seaweed
		: public Living
	{
	public:
		Seaweed( uint16_t age, uint16_t health = 10u );
		~Seaweed() = default;
		Seaweed( Seaweed && ) = default;
		Seaweed & operator=( Seaweed && ) = default;
		Seaweed( Seaweed const & ) = delete;
		Seaweed & operator=( Seaweed const & ) = delete;

		SeaweedPtr grow();
		void beEaten();

	public:
		Signal< std::function< void( Seaweed const & seaweed ) > > onDie;
		Signal< std::function< void( Seaweed const & seaweed, Seaweed const & parent ) > > onBorn;

	private:
		virtual void doDie();
		SeaweedPtr doGrow();
	};

	bool operator==( Seaweed const & lhs, Seaweed const & rhs );
	bool operator!=( Seaweed const & lhs, Seaweed const & rhs );
	std::ostream & operator<<( std::ostream & stream, Seaweed const & seaweed );
	std::istream & operator>>( std::istream & stream, Seaweed & seaweed );
}

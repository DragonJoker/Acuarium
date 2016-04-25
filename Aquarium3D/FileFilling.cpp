#include "Prerequisites.hpp"

#include <RaceFactory.hpp>
#include <Seaweed.hpp>
#include <Fish.hpp>

namespace
{
	TurnAddsMap::iterator addTurn( std::sregex_iterator it, TurnAddsMap & turnsAdds )
	{
		std::smatch match{ *it };
		std::stringstream sturn{ match[1] };
		uint32_t turn{ 0 };
		sturn >> turn;
		return turnsAdds.insert( { turn, TurnAdds{} } ).first;
	}

	void addSeaweeds( std::sregex_iterator it, TurnAddsMap::iterator adds )
	{
		std::smatch match{ *it };
		std::stringstream scount{ match[1] };
		std::stringstream sage{ match[2] };
		uint16_t count{ 0u };
		uint16_t age{ 0u };
		scount >> count;
		sage >> age;

		for ( uint16_t i{ 0u }; i < count; ++i )
		{
			adds->second.m_seaweeds.emplace_back( age );
		}
	}

	void addFish( std::sregex_iterator it, TurnAddsMap::iterator adds )
	{
		aquarium::RaceFactory factory;
		std::smatch match{ *it };
		std::string name{ match[1] };
		std::string race{ match[2] };
		std::string gender{ match[3] };
		std::stringstream sage{ match[4] };
		uint16_t age{ 0u };
		sage >> age;
		adds->second.m_fishes.emplace_back( factory.getRace( aquarium::getRace( race ) ), age, name, aquarium::getGender( gender ) );
	}
}

void loadFromFile( std::string const & filename, TurnAddsMap & turnsAdds )
{
	std::ifstream file( filename );

	if ( file )
	{
		std::string line;
		std::regex const seawedExpr{ "([0-9]+) algues ([0-9]+) ans" };
		std::regex const fishExpr{ "([^,]+), (Basse|Tuna|Clown|Sole|Bass|Carp|Mérou|Thon|Poisson-clown|Bar|Carpe), (Male|Female|Mâle|Femelle), ([0-9]+) ans" };
		std::regex const turnExpr{ "===== tour ([^,]+) =====" };
		std::sregex_iterator endIt;
		auto adds = turnsAdds.insert( { 0u, TurnAdds{} } ).first;

		while ( std::getline( file, line ) && file )
		{
			std::sregex_iterator turnIt{ std::sregex_iterator( line.cbegin(), line.cend(), turnExpr ) };

			if ( turnIt != endIt )
			{
				adds = addTurn( turnIt, turnsAdds );
			}

			std::sregex_iterator seaweedIt{ std::sregex_iterator( line.cbegin(), line.cend(), seawedExpr ) };

			if ( seaweedIt != endIt )
			{
				addSeaweeds( seaweedIt, adds );
			}

			std::sregex_iterator fishIt{ std::sregex_iterator( line.cbegin(), line.cend(), fishExpr ) };

			if ( fishIt != endIt )
			{
				addFish( fishIt, adds );
			}
		}
	}
}

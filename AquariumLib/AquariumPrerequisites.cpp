#include "AquariumPrerequisites.hpp"

namespace aquarium
{
	Gender getGender( std::string const & name )
	{
		static std::map< std::string, Gender > const Genders
		{
			{ "Female", Female },
			{ "Male", Male },
			{ "Femelle", Female },
			{ "Mâle", Male },
		};
		auto it = Genders.find( name );

		if ( it == Genders.end() )
		{
			throw std::runtime_error{ "Not a valid gender name." };
		}

		return it->second;
	}

	FishRace getRace( std::string const & name )
	{
		static std::map< std::string, FishRace > const Races
		{
			{ "Basse", Basse },
			{ "Tuna", Tuna },
			{ "Clown", Clown },
			{ "Sole", Sole },
			{ "Bass", Bass },
			{ "Carp", Carp },
			{ "Mérou", Basse },
			{ "Thon", Tuna },
			{ "Poisson-clown", Clown },
			{ "Sole", Sole },
			{ "Bar", Bass },
			{ "Carpe", Carp },
		};

		auto it = Races.find( name );

		if ( it == Races.end() )
		{
			throw std::runtime_error{ "Not a valid fish race name." };
		}

		return it->second;
	}

	std::string getRandomName()
	{
		auto const count = getRandom< size_t >( 5u, 10u );
		std::stringstream ret;

		for ( size_t i{ 0u }; i < count; ++i )
		{
			ret << char( getRandom< uint16_t >( 32u, 126u ) );
		}

		return ret.str();
	}
}

#pragma once

#include "AquariumAppsPrerequisites.hpp"

namespace aquarium
{
	namespace render
	{
		struct NameManip
		{
			NameManip( std::string const & str );
	
			std::string const & m_str;
		};

		struct GenderManip
		{
			GenderManip( Gender gender );
	
			std::string const m_str;
		};

		struct RaceManip
		{
			RaceManip( FishRace race );
	
			std::string const m_str;
		};

		template<>
		struct ManipCreator< std::string >
		{
			using type = NameManip;
		};

		template<>
		struct ManipCreator< Gender >
		{
			using type = GenderManip;
		};

		template<>
		struct ManipCreator< FishRace >
		{
			using type = RaceManip;
		};

		template< typename T >
		typename ManipCreator< T >::type manip( T const & value )
		{
			return typename ManipCreator< T >::type{ value };
		}
	}
}

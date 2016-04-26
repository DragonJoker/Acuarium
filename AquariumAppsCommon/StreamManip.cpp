#include "StreamManip.hpp"

namespace aquarium
{
	namespace render
	{
		namespace
		{
			std::string const & getGenderName( Gender gender )
			{
				static std::string const Names[GenderCount]
				{
					"Female",
					"Male"
				};

				return Names[gender];
			}

			std::string const & getRaceName( FishRace race )
			{
				static std::string const Names[RaceCount]
				{
					"Basse",
					"Tuna",
					"Clown",
					"Sole",
					"Bass",
					"Carp",
				};

				return Names[race];
			}
		}

		NameManip::NameManip( std::string const & str )
			: m_str{ str }
		{
		}

		GenderManip::GenderManip( Gender gender )
			: m_str{ getGenderName( gender ) }
		{
		}

		RaceManip::RaceManip( FishRace race )
			: m_str{ getRaceName( race ) }
		{
		}

		std::ostream & operator<<( std::ostream & stream, NameManip const & manip )
		{
			stream << std::setw( 15 ) << std::left << manip.m_str;
			return stream;
		}

		std::ostream & operator<<( std::ostream & stream, GenderManip const & manip )
		{
			stream << std::setw( 6 ) << std::left << manip.m_str;
			return stream;
		}

		std::ostream & operator<<( std::ostream & stream, RaceManip const & manip )
		{
			stream << std::setw( 5 ) << std::left << manip.m_str;
			return stream;
		}
	}
}

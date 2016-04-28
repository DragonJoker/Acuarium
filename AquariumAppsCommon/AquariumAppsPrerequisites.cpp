#include "AquariumAppsPrerequisites.hpp"

#include <Aquarium.hpp>

void saveAquarium( std::string const & filename, aquarium::Aquarium const & aqua )
{
	std::ofstream out{ filename };

	if ( out )
	{
		out << aqua;
		out.close();
	}
}

#include "Prerequisites.hpp"

#include <Aquarium.hpp>

namespace aquarium
{
	namespace render
	{
		bool checkGlError( std::string const & desc )
		{
			auto err = glGetError();

			if ( err )
			{
				std::cerr << "OpenGL error " << std::hex << err << ", during operation: " << desc << std::endl;
			}

			return err == 0;
		}
	}
}

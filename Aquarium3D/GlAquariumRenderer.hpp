#pragma once

#include "Prerequisites.hpp"

#include <AquariumRenderer.hpp>

namespace aquarium
{
	namespace render
	{
		class GlAquariumRenderer
		  : public AquariumRenderer
		{
		public:
			GlAquariumRenderer( aquarium::Aquarium const & aqua );
			~GlAquariumRenderer();

		private:
			virtual void doPreRender( uint32_t turn );
			virtual void doRender();

		private:
			GlSeaweedRenderer & m_glSeaweedRenderer;
			GlFishRenderer & m_glFishRenderer;
			obj::Mesh m_mesh;
		};
	}
}

#pragma once

#include "Prerequisites.hpp"

namespace aquarium
{
	namespace render
	{
		class TgaLoader
		{
			typedef enum TypeCode : uint8_t
			{
				UncompressedRGB = 2,
				UncompressedL = 3,
			} TypeCode;

			struct TgaFile
			{
				TypeCode imageTypeCode;
				int16_t imageWidth;
				int16_t imageHeight;
				uint8_t bitCount;
				ByteArray imageData;
			};

		public:
			bool loadFile( obj::Texture & texture );

		private:
			bool doLoadFile( std::string const & filename, TgaFile & tgaFile );
		};
	}
}

#include "TgaLoader.hpp"

#include <cstdio>

#pragma warning( disable:4996 )

namespace aquarium
{
	namespace render
	{
		bool TgaLoader::loadFile( gl::Texture & texture )
		{
			TgaFile file;
			auto ret = doLoadFile( texture.m_file, file );

			if ( ret )
			{
				texture.m_dimensions.x = file.imageWidth;
				texture.m_dimensions.y = file.imageHeight;
				texture.m_data = std::move( file.imageData );

				if ( file.imageTypeCode == UncompressedRGB )
				{
					if ( file.bitCount == 32 )
					{
						texture.m_format = GL_RGBA;
						texture.m_internal = GL_RGBA8;
					}
					else
					{
						texture.m_format = GL_RGB;
						texture.m_internal = GL_RGB8;
					}
				}
				else
				{
					texture.m_format = GL_RED;
				}
			}

			return ret;
		}

		bool TgaLoader::doLoadFile( std::string const & filename, TgaLoader::TgaFile & tgaFile)
		{
			// Open the TGA file.
			auto filePtr = fopen( filename.c_str(), "rb" );

			if ( !filePtr )
			{
				return false;
			}

			// Read the two first bytes we don't need.
			uint8_t ucharDump;
			fread( &ucharDump, sizeof( uint8_t ), 1, filePtr );
			fread( &ucharDump, sizeof( uint8_t ), 1, filePtr );

			// Which type of image gets stored in imageTypeCode.
			fread( &tgaFile.imageTypeCode, sizeof( uint8_t ), 1, filePtr );

			// For our purposes, the type code should be 2 (uncompressed RGB image)
			// or 3 (uncompressed black-and-white images).
			if ( tgaFile.imageTypeCode != UncompressedRGB && tgaFile.imageTypeCode != UncompressedL )
			{
				fclose( filePtr );
				return false;
			}

			// Read 13 bytes of data we don't need.
			int16_t sintDump;
			fread( &sintDump, sizeof( int16_t ), 1, filePtr );
			fread( &sintDump, sizeof( int16_t ), 1, filePtr );
			fread( &ucharDump, sizeof( uint8_t ), 1, filePtr );
			fread( &sintDump, sizeof( int16_t ), 1, filePtr );
			fread( &sintDump, sizeof( int16_t ), 1, filePtr );

			// Read the image's width and height.
			fread( &tgaFile.imageWidth, sizeof( int16_t ), 1, filePtr );
			fread( &tgaFile.imageHeight, sizeof( int16_t ), 1, filePtr );

			// Read the bit depth.
			fread( &tgaFile.bitCount, sizeof( uint8_t ), 1, filePtr );

			// Read one byte of data we don't need.
			fread( &ucharDump, sizeof( uint8_t ), 1, filePtr );

			// Color mode -> 3 = BGR, 4 = BGRA.
			int colorMode = tgaFile.bitCount / 8;
			long imageSize = tgaFile.imageWidth * tgaFile.imageHeight * colorMode;

			// Allocate memory for the image data.
			tgaFile.imageData.resize( imageSize );

			// Read the image data.
			if ( imageSize != fread( tgaFile.imageData.data(), sizeof( uint8_t ), imageSize, filePtr ) )
			{
				fclose( filePtr );
				return false;
			}
			
			// Change from BGR to RGB so OpenGL can read the image data.
			for ( int imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode )
			{
				std::swap( tgaFile.imageData[imageIdx], tgaFile.imageData[imageIdx + 2] );
			}

			fclose( filePtr );
			return true;
		}
	}
}

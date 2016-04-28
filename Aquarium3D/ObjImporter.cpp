#include "ObjImporter.hpp"

#include "TgaLoader.hpp"

namespace aquarium
{
	namespace render
	{
		namespace obj
		{
			namespace
			{
				using StringArray = std::vector< std::string >;

				std::string & trim( std::string & txt )
				{
					auto index = txt.find_first_not_of( " \t" );

					if ( index != std::string::npos )
					{
						txt = txt.substr( txt.find_first_not_of( " \t" ) );
						txt = txt.substr( 0, txt.find_last_not_of( " \t" ) + 1 );
					}
					else
					{
						txt.clear();
					}

					return txt;
				}
		
				StringArray split( std::string const & txt, std::string const & delims, bool keepEmpty, uint32_t max )
				{
					StringArray	ret;

					if ( !txt.empty() && !delims.empty() && max > 0 )
					{
						ret.reserve( max + 1 );
						std::size_t pos = 0;
						std::size_t start = 0;

						do
						{
							pos = txt.find_first_of( delims, start );

							if ( pos == start )
							{
								start = pos + 1;

								if ( keepEmpty )
								{
									ret.push_back( std::string() );
								}
							}
							else if ( pos == std::string::npos || ret.size() == max )
							{
								std::string remnants = txt.substr( start );

								if ( !remnants.empty() || keepEmpty )
								{
									ret.push_back( remnants );
								}

								pos = std::string::npos;
							}
							else
							{
								ret.push_back( txt.substr( start, pos - start ) );
								start = pos + 1;
							}
						}
						while ( pos != std::string::npos );
					}

					return ret;
				}
			}
		
			Mesh Importer::importMesh( std::string const & filePath )
			{
				Mesh ret;

				try
				{
					auto index = std::max( int32_t( filePath.find_last_of( '/' ) ), int32_t( filePath.find_last_of( '\\' ) ) );
					auto folder = filePath.substr( 0, index + 1 );
					Context context{ folder };
					context.mesh.m_name = filePath.substr( index + 1 );
					context.mesh.m_name = context.mesh.m_name.substr( 0, context.mesh.m_name.find_last_of( '.' ) );
					std::cout << "Importing mesh: " << context.mesh.m_name << std::endl;
					doReadObjFile( filePath, context );
					ret = context.mesh;
					ret.initialise();
					std::cout << "Imported mesh: " << context.mesh.m_name << std::endl;
				}
				catch ( std::exception & exc )
				{
					std::cerr << "Encountered exception while importing mesh: " << exc.what() << std::endl;
				}

				return ret;
			}

			bool Importer::importMeshAsync( std::string const & filePath )
			{
				bool ret = false;

				try
				{
					auto index = std::max( int32_t( filePath.find_last_of( '/' ) ), int32_t( filePath.find_last_of( '\\' ) ) );
					auto folder = filePath.substr( 0, index + 1 );
					m_asyncContext = std::make_unique< Context >( folder );
					m_asyncContext->mesh.m_name = filePath.substr( index + 1 );
					m_asyncContext->mesh.m_name = m_asyncContext->mesh.m_name.substr( 0, m_asyncContext->mesh.m_name.find_last_of( '.' ) );
					std::cout << "Importing mesh: " << m_asyncContext->mesh.m_name << std::endl;
					m_asyncLoader = std::make_unique< std::thread >( [this, filePath]()
					{
						doReadObjFile( filePath, *m_asyncContext );
					} );
					ret = true;
				}
				catch ( std::exception & exc )
				{
					std::cerr << "Encountered exception while importing mesh: " << exc.what() << std::endl;
				}

				return ret;
			}

			Mesh Importer::waitMesh()
			{
				assert( m_asyncLoader && m_asyncContext );

				m_asyncLoader->join();
				auto ret = m_asyncContext->mesh;
				ret.initialise();
				std::cout << "Imported mesh: " << m_asyncContext->mesh.m_name << std::endl;
				return ret;
			}

			void Importer::doReadObjFile( std::string const & filePath, Context & context )
			{
				std::ifstream file{ filePath };

				if ( file.is_open() )
				{
					static std::string const MtlLib = "mtllib";
					static std::string const UseMtl = "usemtl";
					static std::string const Group = "group";
					static std::string const G = "g";
					static std::string const S = "s";
					static std::string const V = "v";
					static std::string const VN = "vn";
					static std::string const VT = "vt";
					static std::string const F = "f";

					std::string line;
					auto matIt = context.mesh.m_materials.end();
					PositionArray allPos;
					TexCoordArray allTex;
					NormalArray allNml;
					FaceArray allFaces;
					Submesh current;
					UIntUInt64Map vtxIndices;
					uint32_t lineNumber{ 0 };

					while ( std::getline( file, line ) )
					{
						trim( line );
						++lineNumber;

						if ( !line.empty() && line[0] != '#' )
						{
							auto splitted = split( line, " \t", false, 1 );

							if ( !splitted.empty() )
							{
								auto section = splitted[0];
								trim( section );
								std::transform( section.begin(), section.end(), section.begin(), tolower );
								std::string value;

								if ( splitted.size() > 1 )
								{
									value = splitted[1];
									trim( value );
								}

								if ( section == MtlLib )
								{
									// Material description file
									doReadMaterials( context.folder + value, context );
								}
								else if ( section == UseMtl )
								{
									// Material
									matIt = context.mesh.m_materials.find( value );

									if ( matIt != context.mesh.m_materials.end() )
									{
										current.m_material = &matIt->second;
									}
								}
								else if ( section == Group || section == G || section == S )
								{
									// Submesh
									if ( !current.m_vertex.empty() && !current.m_faces.empty() )
									{
										context.mesh.m_submeshes.push_back( std::move( current ) );
										UIntUInt64Map tmp;
										std::swap( tmp, vtxIndices );
									}

									if ( matIt != context.mesh.m_materials.end() )
									{
										current.m_material = &matIt->second;
									}
								}
								else if ( section == V )
								{
									// Vertex position
									std::stringstream stream( value );
									glm::vec3 vertex;
									stream >> vertex.x >> vertex.y >> vertex.z;
									allPos.push_back( vertex );
								}
								else if ( section == VT )
								{
									// Vertex UV
									std::stringstream stream( value );
									glm::vec2 uvw;
									stream >> uvw.x >> uvw.y;
									allTex.push_back( uvw );
								}
								else if ( section == VN )
								{
									// Vertex Normal
									std::stringstream stream( value );
									glm::vec3 normal;
									stream >> normal.x >> normal.y >> normal.z;
									allNml.push_back( normal );
								}
								else if ( section == F )
								{
									// Face indices
									auto faceValues = split( value, " \t", false, 0xFFFFFFFF );

									if ( faceValues.size() == 3 )
									{
										// Face represented by 3 vertices
										glm::ivec3 face;
										face.x = doProcessFace( faceValues[0], vtxIndices, current, allPos, allNml, allTex );
										face.y = doProcessFace( faceValues[2], vtxIndices, current, allPos, allNml, allTex );
										face.z = doProcessFace( faceValues[1], vtxIndices, current, allPos, allNml, allTex );
										current.m_faces.push_back( face );
										allFaces.push_back( face );
									}
									else if ( faceValues.size() == 4 )
									{
										// Face represented by 4 vertices
										glm::ivec3 face;
										face.x = doProcessFace( faceValues[0], vtxIndices, current, allPos, allNml, allTex );
										face.y = doProcessFace( faceValues[2], vtxIndices, current, allPos, allNml, allTex );
										face.z = doProcessFace( faceValues[1], vtxIndices, current, allPos, allNml, allTex );
										current.m_faces.push_back( face );
										allFaces.push_back( face );
										face.x = doProcessFace( faceValues[0], vtxIndices, current, allPos, allNml, allTex );
										face.y = doProcessFace( faceValues[3], vtxIndices, current, allPos, allNml, allTex );
										face.z = doProcessFace( faceValues[2], vtxIndices, current, allPos, allNml, allTex );
										current.m_faces.push_back( face );
										allFaces.push_back( face );
									}
								}
							}
						}
					}

					if ( !current.m_vertex.empty() && !current.m_faces.empty() )
					{
						context.mesh.m_submeshes.push_back( std::move( current ) );
					}
				}
				else
				{
					std::cerr << "Couldn't open mesh file: " << filePath << std::endl;
				}
			}

			uint32_t Importer::doProcessFace( std::string const & value, UIntUInt64Map & vtxIndices, Submesh & submesh, PositionArray const & arrayPos, NormalArray const & arrayNml, TexCoordArray const & arrayTex )
			{
				//	VertexSPtr l_return;
				std::string face( value );
				uint32_t ret = 0;
				//replace( face, "//", "/ /" );
				auto arrayIndex = split( face, "/", true, 3 );

				if ( !arrayIndex.empty() )
				{
					// Face description seems to contain at least positions
					trim( arrayIndex[0] );
					uint32_t posIdx = doRetrieveIndex( arrayIndex[0], uint32_t( arrayPos.size() ) );
					uint32_t texIdx = 0xFFFFFFFF;
					glm::vec3 nml;
					glm::vec2 tex;

					if ( arrayIndex.size() >= 2 )
					{
						// Face description seems to contain texture coordinates and normals too
						// Since texture coordinates can vary for the same position, we will store both indices has key to the map.
						trim( arrayIndex[1] );

						if (!arrayIndex[1].empty() )
						{
							// Texture coordinate is present
							texIdx = doRetrieveIndex( arrayIndex[1], uint32_t( arrayTex.size() ) );
							tex = arrayTex[texIdx];
						}

						if ( arrayIndex.size() >= 3 && !trim( arrayIndex[2] ).empty() )
						{
							// Normal is present
							nml = arrayNml[doRetrieveIndex( arrayIndex[2], uint32_t( arrayNml.size() ) )];
						}
					}
					else
					{
						// Face description seems to contain positions only
						if ( arrayTex.size() == arrayPos.size() )
						{
							tex = arrayTex[posIdx];
						}

						if ( arrayNml.size() == arrayPos.size() )
						{
							nml = arrayNml[posIdx];
						}
					}

					auto hash = ( uint64_t( posIdx ) << 32 ) + texIdx;
					auto it = vtxIndices.find( hash );

					if ( it == vtxIndices.end() )
					{
						// Vertex hasn't been inserted yet, so we insert it, to have good index, relative to the group's vertex
						it = vtxIndices.insert( { hash, uint32_t( submesh.m_vertex.size() ) } ).first;
						submesh.m_vertex.push_back( { arrayPos[posIdx], nml, tex } );
					}

					ret = it->second;
				}

				return ret;
			}

			uint32_t Importer::doRetrieveIndex( std::string & index, uint32_t size )
			{
				trim( index );
				std::stringstream stream{ index };
				int32_t ret{ 0 };
				stream >> ret;

				if ( ret < 0 )
				{
					ret = size + ret;
				}
				else
				{
					ret--;
				}

				return ret;
			}

			void Importer::doReadMaterials( std::string const & mtlFilePath, Context & context )
			{
				static std::string const NewMtl = "newmtl";
				static std::string const UseMtl = "usemtl";
				static std::string const KA = "ka";
				static std::string const KD = "kd";
				static std::string const KS = "ks";
				static std::string const TR = "tr";
				static std::string const D = "d";
				static std::string const NS = "ns";
				static std::string const MapKA = "map_ka";
				static std::string const MapKD = "map_kd";
				static std::string const MapKS = "map_ks";

				std::ifstream file{ mtlFilePath };
				std::string line;
				auto matIt = context.mesh.m_materials.end();

				while ( std::getline( file, line ) )
				{
					trim( line );

					if ( !line.empty() && line[0] != '#' )
					{
						auto splitted = split( line, " \t", false, 1 );

						if ( !splitted.empty() )
						{
							auto section = splitted[0];
							trim( section );
							std::transform( section.begin(), section.end(), section.begin(), tolower );
							std::string value;

							if ( splitted.size() > 1 )
							{
								value = splitted[1];
								trim( value );
							}

							if ( section == NewMtl )
							{
								// New material description
								matIt = context.mesh.m_materials.insert( { value, gl::Material{} } ).first;
							}
							else if ( section == KA )
							{
								// Ambient colour
								std::stringstream stream{ value };
								stream >> matIt->second.m_ambientColour.r >> matIt->second.m_ambientColour.g >> matIt->second.m_ambientColour.b >> matIt->second.m_ambientColour.a;
							}
							else if ( section == KD )
							{
								// Diffuse colour
								std::stringstream stream{ value };
								stream >> matIt->second.m_diffuseColour.r >> matIt->second.m_diffuseColour.g >> matIt->second.m_diffuseColour.b >> matIt->second.m_diffuseColour.a;
							}
							else if ( section == KS )
							{
								// Specular colour
								std::stringstream stream{ value };
								stream >> matIt->second.m_specularColour.r >> matIt->second.m_specularColour.g >> matIt->second.m_specularColour.b >> matIt->second.m_specularColour.a;
							}
							else if ( section == TR || section == D )
							{
								// Opacity
								std::stringstream stream{ value };
								stream >> matIt->second.m_opacity;
							}
							else if ( section == NS )
							{
								// Shininess
								std::stringstream stream{ value };
								stream >> matIt->second.m_exponentValue;
							}
							else if ( section == MapKD )
							{
								// Diffuse map
								doAddTexture( value, matIt->second.m_diffuseTexture, context );
							}
							else if ( section == MapKS )
							{
								// Specular map
								doAddTexture( value, matIt->second.m_specularTexture, context );
							}
							else if ( section == MapKA )
							{
								// Ambient map
								doAddTexture( value, matIt->second.m_ambientTexture, context );
							}
						}
					}
				}
			}

			void Importer::doAddTexture( std::string const & value, gl::Texture & texture, Context & context )
			{
				if ( !value.empty() )
				{
					texture.m_file = context.folder + value;
					TgaLoader{}.loadFile( texture );
				}
			}
		}
	}
}

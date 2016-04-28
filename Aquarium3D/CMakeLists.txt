project( Aquarium3D )

include( FileUtils )

find_package( OpenGL )
find_package( GLFW )
find_package( GLM )

if ( OPENGL_FOUND AND GLFW_FOUND AND GLM_FOUND )
	file( GLOB_RECURSE HEADER_FILES *.hpp *.h )
	file( GLOB_RECURSE SOURCE_FILES *.cpp *.c )

	add_definitions( -DGLEW_STATIC )

	include_directories(
		${CMAKE_SOURCE_DIR}/AquariumLib
		${CMAKE_SOURCE_DIR}/AquariumRenderer
		${CMAKE_SOURCE_DIR}/AquariumAppsCommon
		${CMAKE_SOURCE_DIR}/Aquarium3D
		${${OPENGL_gl_LIBRARY}}
		${GLFW_INCLUDE_DIRS}
		${GLM_INCLUDE_DIR}
	)

	add_executable( ${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} )
	target_link_libraries( ${PROJECT_NAME}
		AquariumLib
		AquariumRenderer
		AquariumAppsCommon
		${OPENGL_gl_LIBRARY}
		${GLFW_LIBRARIES}
	)

	copy_target_directory( ${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/data )
else ()
	if ( NOT OPENGL_FOUND )
		message( SEND_ERROR "Could not find OpenGL" )
	endif ()
	if ( NOT GLFW_FOUND )
		message( SEND_ERROR "Could not find GLFW" )
	endif ()
	if ( NOT GLM_FOUND )
		message( SEND_ERROR "Could not find GLM" )
	endif ()
endif ()

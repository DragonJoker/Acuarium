if ( WIN32 )
	find_path( GLFW_ROOT_DIR include/GLFW/glfw3.h )

	find_path( GLFW_INCLUDE_DIRS GLFW/glfw3.h
		HINTS
		PATH_SUFFIXES
			include
		PATHS
			${GLFW_ROOT_DIR}
	)

	if ( MSVC )
		set( SUBFOLDER lib-vc )
		if ( MSVC11 )
			set( SUBFOLDER ${SUBFOLDER}2012 )
		elseif ( MSVC12 )
			set( SUBFOLDER ${SUBFOLDER}2013 )
		elseif ( MSVC14 )
			set( SUBFOLDER ${SUBFOLDER}2015 )
		endif ()
	elseif ( MINGW )
		set( SUBFOLDER lib-mingw-w64 )
	endif ()

	find_path( GLFW_LIBRARY_DIR glfw3.lib libglfw3.a
		HINTS
			PATH_SUFFIXES
				${SUBFOLDER}
			PATHS
				${GLFW_ROOT_DIR}
	)

	find_library( GLFW_LIBRARY glfw3
		HINTS
			PATHS
				${GLFW_LIBRARY_DIR}
	)

	set( GLFW_LIBRARIES ${GLFW_LIBRARY} )
else ()
	find_package( PkgConfig REQUIRED )
	pkg_search_module( GLFW REQUIRED glfw3 )
endif ()

find_package_handle_standard_args( GLFW DEFAULT_MSG GLFW_LIBRARIES GLFW_INCLUDE_DIRS )
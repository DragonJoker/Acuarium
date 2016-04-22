project( Aquarium3D )

find_package( OpenGL )
find_package( GLFW )

if ( OPENGL_FOUND AND GLFW_FOUND )
  file( GLOB HEADER_FILES *.hpp )
  file( GLOB SOURCE_FILES *.cpp )

  include_directories(
    ${CMAKE_SOURCE_DIR}/AquariumLib
    ${${OPENGL_gl_LIBRARY}}
    ${GLFW_INCLUDE_DIRS}
  )

  add_executable( ${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} )
  target_link_libraries( ${PROJECT_NAME}
    AquariumLib
    ${OPENGL_gl_LIBRARY}
    ${GLFW_LIBRARIES}
  )
else ()
  if ( NOT OPENGL_FOUND )
    message( SEND_ERROR "Could not find OpenGL" )
  endif ()
  if ( NOT GLFW_FOUND )
    message( SEND_ERROR "Could not find GLFW" )
  endif ()
endif ()

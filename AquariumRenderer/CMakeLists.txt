project( AquariumRenderer )

file( GLOB HEADER_FILES *.hpp )
file( GLOB SOURCE_FILES *.cpp )

include_directories( ${CMAKE_SOURCE_DIR}/AquariumLib )

add_library( ${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES} )
target_link_libraries( ${PROJECT_NAME} AquariumLib )

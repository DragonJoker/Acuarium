project( AquariumLib )

file( GLOB HEADER_FILES *.hpp *.inl )
file( GLOB SOURCE_FILES *.cpp )

add_library( ${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES} )

#target_compile_features( ${PROJECT_NAME} PUBLIC cxx_range_for )

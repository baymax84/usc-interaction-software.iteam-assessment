# gather all sources in current dir using relative filenames
file( GLOB LIB_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.cc *.c )

add_library( ${PROJECT_NAME} SHARED ${LIB_SOURCES} )

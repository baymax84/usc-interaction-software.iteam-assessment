cmake_minimum_required( VERSION 2.6 )

# set project name
project( syntax_errors )

# set some common paths
set( PROJECT_EXECUTABLE_DIR bin )
set( PROJECT_LIBRARY_DIR lib )

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/${PROJECT_EXECUTABLE_DIR} )
set( LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/${PROJECT_LIBRARY_DIR} )

# set include paths
include_directories( include )

# add project components
add_subdirectory( include )
add_subdirectory( src )
add_subdirectory( exe )

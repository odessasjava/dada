project ( dada )
cmake_minimum_required ( VERSION 2.6 )

option ( WITH_DEBUG "With debug" OFF )
option ( WITH_GAME "With game" OFF )

if ( WITH_DEBUG )
  if ( WIN32 )
    add_definitions ( -D_DEBUG )
  else ( WIN32 )
    add_definitions ( -ggdb )
  endif ( WIN32 )
endif ( WITH_DEBUG )

include_directories ( /usr/include )
include_directories ( include )
include_directories ( src )

add_subdirectory ( src/dada/app )
add_subdirectory ( src/dada/core )
add_subdirectory ( src/dada/geometry )
add_subdirectory ( src/dada/gl )
add_subdirectory ( src/dada/scene )

if ( WITH_GAME )
  add_subdirectory ( game )
endif ( WITH_GAME )

project ( dada_app )

if ( UNIX )
  find_package ( X11 REQUIRED )
endif ( UNIX )

add_library ( dada_app
  Application.cpp
  Application.h
)

if ( UNIX )
  target_link_libraries ( dada_app ${X11_LIBRARIES} )
endif ( UNIX )

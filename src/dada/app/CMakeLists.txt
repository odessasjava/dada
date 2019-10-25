project ( dada_app )

find_library ( EGL_LIBRARY EGL )

if ( UNIX )
  find_package ( X11 REQUIRED )
endif ( UNIX )

add_library ( dada_app
  Application.cpp
  Application.h
)

if ( UNIX )
  target_link_libraries ( dada_app ${X11_LIBRARIES} )
else ( UNIX )  
  target_link_libraries ( dada_app ${EGL_LIBRARY} )
endif ( UNIX )

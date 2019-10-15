project ( dada_gl )

if ( WIN32 )
  find_library ( GL_LIBRARY opengl32 )
  #find_library ( GLEW_LIBRARY glew32 )
else ( WIN32 )
  find_package ( OpenGL REQUIRED )
  #find_package ( GLEW REQUIRED )
endif ( WIN32 )

add_library ( dada_gl
  EBO.cpp
  EBO.h
  GL.cpp
  GL.h
  Program.cpp
  Program.h
  Shader.cpp
  Shader.h
  VAO.cpp
  VAO.h
  VBO.cpp
  VBO.h
)

if ( WIN32 )
  #target_link_libraries ( dada_gl dada_core ${GL_LIBRARY} ${GLEW_LIBRARY} )
  target_link_libraries ( dada_gl dada_core ${GL_LIBRARY} )
else ( WIN32 )
  #target_link_libraries ( dada_gl dada_core ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} )
  target_link_libraries ( dada_gl dada_core ${OPENGL_LIBRARIES} )
endif ( WIN32 )

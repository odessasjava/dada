project ( dada_game )

include_directories ( . )

add_executable ( game
  game.cpp
)

target_link_libraries ( game dada_app dada_core dada_geometry dada_gl dada_scene )

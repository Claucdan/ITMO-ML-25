tetris_sources= [
  'grid.cpp',
  'tetris.cpp',
  'tetris-game.cpp',
  'figure-manager.cpp'
]


compiler = executable(
  'tetris',
  files(
    tetris_sources,
  ),
  include_directories: include_directories('.', '../'),
  dependencies: [ncurses_dep]
)

project(
  'slang',
  'cpp',
  version: '1.0.0',
  default_options: [
    'cpp_std=gnu++2a',
    'warning_level=3',
    'buildtype=release',
  ],
)

include_dirs = include_directories('.')

buildtype = get_option('buildtype')
if buildtype == 'release'
  add_global_arguments('-O3', '-DNDEBUG', language: 'cpp')
elif buildtype == 'debug'
  add_global_arguments('-O0', '-g', '-DDEBUG', language: 'cpp')
endif

gtest_dep = dependency('gtest', main: true, required: true)
spdlog_dep = dependency('spdlog', main: true, required: true)
ncurses_dep = dependency('ncurses')

subdir('src')

project('rk-buse', ['c', 'cpp'], version: '1.0.0', default_options : ['warning_level=3', 'werror=false', 'cpp_std=c++20'])

deps = [
  dependency('libusb-1.0')
]

executable('rk-buse', 
  files(
    'src/main.cpp',
    'src/buse/buse.cpp',
    'src/buse/block-operator.cpp',
    'src/xrock/rock.c',
    'src/xrock/progress.c',
    'src/xrock/rc4.c',
    'src/xrock/crc16.c',
    'src/xrock/misc.c',
  ), 
  include_directories : include_directories('src/xrock'),
  dependencies : deps,
  install : true)

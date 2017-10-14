cmake_minimum_required( VERSION 3.1 )
project( MusicSheet )
set (CMAKE_CXX_STANDARD 11)

set( CcMusicSheet_LIBS
  CcMusicSheet
  CcOpencvUltils
)

find_package( OpenCV REQUIRED )
add_executable( MusicSheet MusicSheet.cpp )
target_link_libraries( MusicSheet
  ${OpenCV_LIBS}
  ${CcMusicSheet_LIBS}
)

include_directories( "${PROJECT_SOURCE_DIR}/libs" )
add_subdirectory( libs )

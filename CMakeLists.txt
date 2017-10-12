cmake_minimum_required( VERSION 2.8 )
project( MusicSheet )

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

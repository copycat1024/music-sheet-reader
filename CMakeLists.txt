cmake_minimum_required( VERSION 3.1 )
project( MusicSheet )
set (CMAKE_CXX_STANDARD 11)

set( CcMusicSheet_LIBS
	CcMusicSheet
	CcOpencvUltils
)

find_package( OpenCV REQUIRED )
add_executable( msr_extract msr_extract.cpp )
target_link_libraries( msr_extract
	${OpenCV_LIBS}
	${CcMusicSheet_LIBS}
)

include_directories( "${PROJECT_SOURCE_DIR}/libs" )
add_subdirectory( libs )

include_directories( "${PROJECT_SOURCE_DIR}/utils" )
add_subdirectory( utils )

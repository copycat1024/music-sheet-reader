include_directories( "${PROJECT_SOURCE_DIR}/utils" )

add_library(CcMusicSheet
	# I/O functions
	music_io.hh
	music_io.cc

	# Error object
	music_error.hh

	# Locating functions
	music_locate.hh
	music_locate.cc
	locate/staves.hh   #locate staves
	locate/staves.cc
	locate/lines.hh    #locate lines
	locate/lines.cc
	locate/contour.hh  #locate symbols (contours)
	locate/contour.cc
	locate/classify.hh #classify symbols
	locate/classify.cc

	# Present and debug
	music_present.hh
	music_present.cc
	music_debug.hh
	music_debug.cc

)

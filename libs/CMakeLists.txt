add_library(CcOpencvUltils
	opencv_utils.hh
	opencv_utils.cc
)

add_library(CcMusicSheet
	# Main functions
	music_main.hh
	music_main.cc

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
	locate/symbols.hh  #locate symbols (base)
	locate/symbols.cc
	locate/clefs.hh    #locate clefs
	locate/clefs.cc

	# Editting functions
	music_transform.hh
	music_transform.cc

	# Present and debug
	music_present.hh
	music_present.cc
	music_debug.hh
	music_debug.cc

)

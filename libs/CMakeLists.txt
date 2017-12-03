add_library(CcOpencvUltils
	cc_opencv_ultils.hh
	cc_opencv_ultils.cc
)

add_library(CcMusicSheet
	# Main functions
	cc_music_main.hh
	cc_music_main.cc

	# I/O functions
	cc_music_io.hh
	cc_music_io.cc

	# Locating functions
	cc_music_locate.hh
	cc_music_locate.cc
	locate/cc_music_staves.hh   #locate staves
	locate/cc_music_staves.cc
	locate/cc_music_lines.hh    #locate lines
	locate/cc_music_lines.cc
	locate/cc_music_symbols.hh  #locate symbols (base)
	locate/cc_music_symbols.cc
	locate/cc_music_clefs.hh    #locate clefs
	locate/cc_music_clefs.cc

	# Editting functions
	cc_music_transform.hh
	cc_music_transform.cc

	# Present and debug
	cc_music_present.hh
	cc_music_present.cc
	cc_music_debug.hh
	cc_music_debug.cc

)

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
	cc_music_frames.hh #locate frames
	cc_music_frames.cc
	cc_music_lines.hh  #locate lines
	cc_music_lines.cc

	# Editting functions
	cc_music_transform.hh
	cc_music_transform.cc
	cc_music_present.hh
	cc_music_present.cc

)

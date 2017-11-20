/* CC Music Reader main header
 *
 * Contain the main functions of the program
 *
 * Status: Locked
 *
 */

#ifndef CC_MUSIC_MAIN
#define CC_MUSIC_MAIN

namespace cc {

// express the task that should be done
enum TaskNumber {
	NO_ARGUMENT,
	INPUT_FILE_ERROR,
	PROCESS_INPUT_FILE
};

// program object
class MusicSheetReaderProgram {
public:
	// handle the arguments
	TaskNumber handleArguments(int, char**);

	// process the image, and show the results
	void processImage(char*);
};

}
#endif

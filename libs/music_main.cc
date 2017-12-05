/* CC Music Reader main code
 *
 * Contain the main functions of the program
 *
 * Status: Locked
 *
 */

#include <iostream>
#include "music_main.hh"
#include "music_io.hh"
#include "music_locate.hh"
#include "music_present.hh"
#include "music_debug.hh"
#include "music_error.hh"

using namespace std;
using namespace cv;

namespace cc {

// Status: Locked
TaskNumber Program::handleArguments(int argc, char** argv){
	if (argc < 2) return NO_ARGUMENT;
	if (!fileExist(argv[1])) return INPUT_FILE_ERROR;
	return PROCESS_INPUT_FILE;
}

// Status: Locked
void Program::processImage(char* image_name){

	Locator   loc; // locate and store elements of the sheet music
	Presenter pre; // present the results
	Debugger  dbg; // debug the results

	Mat image; // input image

	// Load image
	if(!loadGreyImage(image_name, image)){
		cout << "No image data!" << endl;
		return;
	}
	cout << "Image successfully loaded." << endl;
	cout << "Name: " << image_name << endl;
	cout << "Size: " << image.cols << "x" << image.rows << endl;
	cout << endl;
	pre.presentInput(image); // present input

	// Clock start
	double t = (double) getTickCount();

	// Locate sheet music from image
	try {
		loc.locateFrom(image);
	} catch (Error e) {
		dbg.debug(loc, e);
		return;
	}

	// Clock ends
	t = ((double) getTickCount() - t)/getTickFrequency();

	// Present results
	pre.presentResults(loc);

	cout << "Times passed in seconds: " << t << endl;

	return;
}

}

/* CC Music Reader main code
 *
 * Contain the main functions of the program
 *
 * Status: Locked
 *
 */

#include <iostream>
#include "cc_music_main.hh"
#include "cc_music_io.hh"
#include "cc_music_locate.hh"
#include "cc_music_present.hh"
#include "cc_music_debug.hh"

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
	pre.presentInput(image); // present input

	// Clock start
	double t = (double) getTickCount();

	// Locate sheet music from image
	bool suc = loc.locateMusicSheetFrom(image);

	// Clock ends
	t = ((double) getTickCount() - t)/getTickFrequency();

	// Present results
	if (suc)
		pre.presentResults(loc);
	else
		dbg.debug();

	cout << "Times passed in seconds: " << t << endl;

	return;
}

}

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

	Locator loc;   // locate and store elements of the sheet music
	Presenter pre; // present the results

	Mat image; // input image

	// Clock start
	double t = (double)getTickCount();

	// Load image
	if(!loadGreyImage(image_name, image)){
		cout << "No image data!" << endl;
		return;
	}
	pre.presentInput(image); // present input

	// Locate sheet music from image
	loc.locateMusicSheetFrom(image);
	cout << "Loc done" << endl;
	pre.presentResults(loc); // present results
	cout << "Pre done" << endl;

	// Clock ends
	t = ((double)getTickCount() - t)/getTickFrequency();

	// Show the image until a key is pressed
	pre.presentHold(); // present hold

	cout << "Times passed in seconds: " << t << endl;

	return;
}

}

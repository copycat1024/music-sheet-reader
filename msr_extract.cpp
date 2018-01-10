#include <iostream>
#include "music_io.hh"
#include "music_locate.hh"
#include "music_present.hh"
#include "music_debug.hh"
#include "music_error.hh"

using namespace std;
using namespace cv;
using namespace cc;

enum TaskNumber {
	NO_ARGUMENT,
	INPUT_FILE_ERROR,
	PROCESS_INPUT_FILE
};

TaskNumber handleArguments(int argc, char** argv){
	if (argc < 2) return NO_ARGUMENT;
	if (!fileExist(argv[1])) return INPUT_FILE_ERROR;
	return PROCESS_INPUT_FILE;
}

void processImage(char* image_name){

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
	pre.presentResults(loc, image);

	cout << "Times passed in seconds: " << t << endl;

	return;
}

int main(int argc, char** argv){
	switch (handleArguments(argc, argv)){
		case NO_ARGUMENT:
			cerr << "The program " << argv[0] << " require argument." << endl;
			cerr << "Usage: " << argv[0] << " <image_file_name>." << endl;
			break;
		case INPUT_FILE_ERROR:
			cerr << "File " << argv[1] << " doesn't exist." << endl;
			break;
		case PROCESS_INPUT_FILE:
			processImage(argv[1]);
			break;
		default:
			cerr << "Internal error: handleArguments return unknown result." << endl;
	}
	return 0;
}

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "cc_music_main.hh"
#include "cc_music_io.hh"
#include "cc_music_locate.hh"
#include "cc_music_present.hh"
#include "cc_opencv_ultils.hh"

using namespace std;
using namespace cv;

namespace cc {

TaskNumber MusicSheetReaderProgram::handleArguments(int argc, char** argv){
	MusicSheetReaderIO io;
	if (argc < 2) return NO_ARGUMENT;
	if (!io.fileExist(argv[1])) return INPUT_FILE_ERROR;
	return PROCESS_INPUT_FILE;
}

void MusicSheetReaderProgram::processImage(char* image_name){
	// Clock start
	double t = (double)getTickCount();

	MusicSheetReaderIO io;
	MusicSheetReaderLocator loc;

	Mat input_image;
	Mat binary_image;
	Mat show_image;
	Mat sheet_lines_image;
	Mat symbols_image;

	if(!io.loadGreyImage(image_name, input_image)){
		cout << "No image data!" << endl;
		return;
	}
	io.showImage("Input", input_image);

	loc.locateMusicSheetFrom(input_image);

	auto lines = loc.Lines();
	cout << "Found " << lines.size() << " lines." << endl;

	auto frames = loc.Frames();
	cout << "Found " << frames.size() << " frames." << endl;
	if (!loc.Success()){
		io.showHold();
		return;
	}

//	loc.locateSymbols(frames[0]);
//	auto symbols = loc.Symbols();

	cvtColor(input_image, show_image, CV_GRAY2BGR);
	drawRects(show_image, frames, Scalar(0,255,0));
	drawLines(show_image, lines, Scalar(255,0,255));

	auto fl = splitFrames(input_image, frames);
	io.showImage("Result", show_image);
	io.showImage("Frame 0", fl[0]);

//	loc.locateSymbols2(input_image);

	// Clock ends
	t = ((double)getTickCount() - t)/getTickFrequency();

	io.showHold();

	cout << "Times passed in seconds: " << t << endl;

	return;
}

}

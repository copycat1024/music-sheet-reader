/* CC Music Reader Presenter code
 *
 * Contain the object used to present the result.
 *
 * Status:
 *  Open:   1
 *  Legacy: 1
 *  Locked: 5
 *
 */

#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "cc_opencv_ultils.hh"
#include "cc_music_present.hh"
#include "cc_music_io.hh"

using namespace cv;
using namespace std;

namespace cc {

// Status: Legacy
vector<Mat> splitStaves(Mat src, vector<Vec4i> staves){
	vector<Mat> res;
	for (auto v: staves){
		auto f = src(Rect(v[0], v[1], v[2] - v[0], v[3] - v[1]));
		res.push_back(f);
	}
	return res;
}

// Status: Locked
void Presenter::presentInput(Mat input_image){
	_input_image = input_image;
	showImage("Input", input_image);
}

// Status: Locked
void Presenter::presentResults(Locator loc){
	_loc = loc;

	// make show image
	_makeROI();

	// staves and lines
	_presentStavesAndLines();

	// hold
	showHold();
}

// Status: Open
void Presenter::_presentStavesAndLines(){
	Mat show_image;

	cvtColor(_input_image, show_image, CV_GRAY2BGR);
	drawRects(show_image, _loc.Staves(), Scalar(0,255,0));
	drawLines(show_image, _loc.Lines(), Scalar(255,0,255));
	drawRects(show_image, _loc.Symbols(), Scalar(255,0,0));

	imwrite("show.jpg", show_image);

	show_image = show_image(_ROI);
	showImage("Staves and lines", show_image);

	auto staves = _loc.Staves();
	cout << "Found " << staves.size() << " staves." << endl;
	auto lines = _loc.Lines();
	cout << "Found " << lines.size() << " lines." << endl;
}


void Presenter::_makeROI(){
	auto& s = _loc.Staves();

	int x1 = 0;
	int y1 = 0;
	int x2 = _input_image.cols;
	int y2 = _input_image.rows;

	_ROI = Rect(x1, y1, x2 - x1, y2 - y1);
}

}

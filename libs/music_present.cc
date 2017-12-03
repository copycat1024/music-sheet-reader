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

#include "opencv_utils.hh"
#include "music_present.hh"
#include "music_io.hh"

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

	imwrite("present/staves+lines.jpg", show_image);

	auto staves = _loc.Staves();
	cout << "Found " << staves.size() << " staves." << endl;
	auto lines = _loc.Lines();
	cout << "Found " << lines.size() << " lines." << endl;
}

}

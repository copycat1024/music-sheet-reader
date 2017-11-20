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
#include <opencv2/imgproc/imgproc.hpp>
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
void MusicSheetReaderPresenter::presentInput(Mat input_image){
	_input_image = input_image;
	showImage("Input", input_image);
}

// Status: Locked
void MusicSheetReaderPresenter::presentResults(MusicSheetReaderLocator loc){
//	if (loc.Status() == Error::Normal){
	if (false){
		// present staves and lines
		_presentStavesAndLines(loc);
	} else {
		// debug
		_debug(loc, loc.Status());
	}
}

// Status: Locked
void MusicSheetReaderPresenter::presentHold(){
	showHold();
}

// Status: Locked
void MusicSheetReaderPresenter::_drawLines(Mat image, vector<Vec4i> lines, Scalar color){
	for( std::size_t i = 0; i < lines.size(); i++ ){
		Vec4i l = lines[i];
		line(image, Point(l[0], l[1]), Point(l[2], l[3]), color);
	}
}

// Status: Locked
void MusicSheetReaderPresenter::_drawRects(Mat image, vector<Vec4i> lines, Scalar color){
	for( std::size_t i = 0; i < lines.size(); i++ ){
		Vec4i l = lines[i];
		rectangle(image, Point(l[0] - 1, l[1] - 1), Point(l[2] + 1, l[3] + 1), color);
	}
}

// Status: Open
void MusicSheetReaderPresenter::_presentStavesAndLines(MusicSheetReaderLocator loc){
	Mat show_image;

	cvtColor(_input_image, show_image, CV_GRAY2BGR);
	_drawRects(show_image, loc.Staves(), Scalar(0,255,0));
	_drawLines(show_image, loc.Lines(), Scalar(255,0,255));
	_drawRects(show_image, loc.Symbols(), Scalar(255,0,0));
	showImage("Result", show_image);

	auto staves = loc.Staves();
	cout << "Found " << staves.size() << " staves." << endl;
	auto lines = loc.Lines();
	cout << "Found " << lines.size() << " lines." << endl;
}

void MusicSheetReaderPresenter::_debug(MusicSheetReaderLocator loc, Error err){
	if (err == Error::StavesFail){
		cout << "Staves locator fail" << endl;
	} else if (err == Error::LinesFail){
		cout << "Lines locator fail" << endl;
		cout << loc._lines.Lines().size() << endl;
		Mat show_image = loc._binary_image.clone();
		cvtColor(show_image, show_image, CV_GRAY2BGR);
		_drawLines(show_image, loc._staves._lines, Scalar(0,255,0));
		showImage("lines", show_image);
		showImage("bin", loc._staves._sheet_lines_image);
	}
}

}

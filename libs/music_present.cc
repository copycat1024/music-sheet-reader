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
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "opencv_utils.hh"
#include "music_present.hh"
#include "music_locate.hh"
#include "music_io.hh"

using namespace cv;
using namespace std;

namespace cc {

// Status: Locked
void Presenter::presentResults(const Locator& loc, const Mat& input_image){
	cout << endl;
	cout << "Present: " << endl;

	// staves and lines
	_presentStavesAndLines(loc, input_image);
}

// Status: Open
void Presenter::_presentStavesAndLines(const Locator& _loc, const Mat& input_image){
	Mat show_image;
	cvtColor(input_image, show_image, CV_GRAY2BGR);

	drawRects(show_image, _loc.Staves(), Scalar(0,255,0));
	drawLines(show_image, _loc.Lines(), Scalar(255,0,255));

	imwrite("present/staves+lines.jpg", show_image);

	auto staves = _loc.Staves();
	cout << "Found " << staves.size() << " staves." << endl;
	auto lines = _loc.Lines();
	cout << "Found " << lines.size() << " lines." << endl;
}

}

/* CC Music Reader Match Locator code
 *
 * Contain the base object for symbols locating.
 *
 *

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "opencv_utils.hh"
#include "symbols.hh"

using namespace std;
using namespace cv;

// Private functions

Mat matchPattern(const Mat& image, const Mat& pattern){
	Mat result_f, result;

	// run matchTemplate with normalization
	matchTemplate(image, pattern, result_f, CV_TM_CCOEFF_NORMED);

	// convert the normalized result in float to unsigned char
	((Mat) (result_f*255)).convertTo(result, CV_8UC1);

	return result;
}

double getPatternQuality(const Mat& result){
	double minVal, maxVal;
	Point minLoc, maxLoc;
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	return (maxVal*100)/255;
}

Point locateMax(Mat image, Vec4i frame){
	Mat src = image(Rect(frame[0], frame[1], frame[2] - frame[0], frame[3] - frame[1]));

	double minVal, maxVal;
	Point minLoc, maxLoc;
	minMaxLoc(src, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	int x = frame[0];
	int y = frame[1];
	if (maxLoc.x > 0) x += maxLoc.x;
	if (maxLoc.y > 0) y += maxLoc.y;

	return Point(x, y);
}

vector<Vec4i> SymbolsLocator::_locatePatterns(const Mat& image, const Mat& pattern, const int percentage){
	vector<Vec4i> res;
	Mat bin, result = matchPattern(image, pattern);
//	quality = getPatternQuality(result);

	threshold(result, bin, percentage * 255 / 100, 255, 0);

	auto blocks = locateContours(bin);
	for (auto b : blocks){
		Point p = locateMax(result, b);
		res.push_back(Vec4i(p.x, p.y, p.x + pattern.cols, p.y + pattern.rows));
	}
	return res;
}

}
*/

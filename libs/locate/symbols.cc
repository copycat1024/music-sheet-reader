/* CC Music Reader Symbol code
 *
 * Contain the base object for symbols locating.
 *
 * Status:
 *  Locked: 1
 *  Final:  5
 *
 */

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "symbols.hh"

using namespace std;
using namespace cv;

// Private functions -----------------------------------------------
// Status: Final
Mat matchPattern(const Mat& image, const Mat& pattern){
	Mat result_f, result;

	// run matchTemplate with normalization
	matchTemplate(image, pattern, result_f, CV_TM_CCOEFF_NORMED);

	// convert the normalized result in float to unsigned char
	((Mat) (result_f*255)).convertTo(result, CV_8UC1);

	return result;
}

// Status: Locked
double getPatternQuality(const Mat& result){
	double minVal, maxVal;
	Point minLoc, maxLoc;
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	return (maxVal*100)/255;
}

// Status: Final
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

// Status: Final
vector<Vec4i> locateContours(const Mat& image){
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy, res;

	findContours(image, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	for(vector<Point> c : contours){
		int x1,x2,y1,y2;
		x1 = c[0].x;
 		x2 = c[0].x;
		y1 = c[0].y;
		y2 = c[0].y;
		for (int j=1; j<c.size(); j++){
			if (x1>c[j].x) x1 = c[j].x;
			if (x2<c[j].x) x2 = c[j].x;
			if (y1>c[j].y) y1 = c[j].y;
			if (y2<c[j].y) y2 = c[j].y;
		}
		res.push_back(Vec4i(x1, y1, x2, y2));
	}
	return res;
}

bool intersect(const int a, const int b1, const int b2){
	return (a > b1) && (a < b2);
}

bool intersect(const Vec4i& a, const Vec4i& b){
//	bool res = (a[2]>b[0]) || (b[2]>a[0]) || (a[3]>b[1]) || (b[3]>a[1]);
	bool res = (a[2]<b[0]) || (b[2]<a[0]) || (a[3]<b[1]) || (b[3]<a[1]);
	return !res;
}

// Object methods --------------------------------------------------
namespace cc{

// Status: Open
void SymbolsLocator::locateFrom(const cv::Mat& image, const vector<Vec4i>& staves){
	vector<Vec4i> raw = locateContours(image);
	vector<Vec4i> raw1;

	cout << raw.size() << endl;
	cout << staves.size() << endl;

	for (auto c : raw){
		for (auto s : staves){
			if (intersect(c, s)){
				raw1.push_back(c);
				break;
			}
		}
	}

	throw Error::SymbolsFail;
}

// Status: Final
vector<Vec4i> SymbolsLocator::_locateContours(const Mat& image){
	return locateContours(image);
}

// Status: Final
vector<Vec4i> SymbolsLocator::_locatePatterns(const Mat& image, const Mat& pattern, const int percentage){
	vector<Vec4i> res;
	Mat bin, result = matchPattern(image, pattern);
	quality = getPatternQuality(result);

	threshold(result, bin, percentage * 255 / 100, 255, 0);

	auto blocks = locateContours(bin);
	for (auto b : blocks){
		Point p = locateMax(result, b);
		res.push_back(Vec4i(p.x, p.y, p.x + pattern.cols, p.y + pattern.rows));
	}
	return res;
}

}

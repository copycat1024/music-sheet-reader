/* CC Music Reader Match contuors header
 *
 * Contain the base object for symbols locating by contours locating.
 *
 */

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "opencv_utils.hh"
#include "contour.hh"

using namespace std;
using namespace cv;

// Private functions

vector<Vec4i> locateContours(const Mat& image){
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy, res;

	findContours(image, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	for(vector<Point> c : contours){
		int x1 = c[0].x, x2 = c[0].x;
		int y1 = c[0].y, y2 = c[0].y;
		for (auto p : c){
			if (x1>p.x) x1 = p.x;
			if (x2<p.x) x2 = p.x;
			if (y1>p.y) y1 = p.y;
			if (y2<p.y) y2 = p.y;
		}
		if (x2>x1 && y2>y1) res.push_back(Vec4i(x1, y1, x2, y2));
	}
	return res;
}

bool intersect(const Vec4i& a, const Vec4i& b){
	bool res = (a[2]<b[0]) || (b[2]<a[0]) || (a[3]<b[1]) || (b[3]<a[1]);
	return !res;
}

Mat isolate(const Mat& binary_image){
	Mat line_image = applyMorphFilter(binary_image, binary_image.cols/2, 1);
	Mat res	= binary_image - line_image;

	Mat morphStructure = getStructuringElement(MORPH_RECT, Size(1,3));
	dilate(res, res, morphStructure, Point(-1, -1));
	erode(res, res, morphStructure, Point(-1, -1));

	return res;
}

// Object methods

namespace cc{

void ContoursLocator::locateFrom(const Mat& image, const vector<Vec4i>& staves){
	Mat symbol_image = isolate(image);
	vector<Vec4i> raw = locateContours(symbol_image);

	for (auto c : raw){
		for (auto s : staves){
			if (intersect(c, s)){
				result.push_back(c);
				break;
			}
		}
	}

	cout << result.size() << endl;

	throw Error::SymbolsFail;
}

}

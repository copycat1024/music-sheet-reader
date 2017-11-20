/* CC Music Reader Symbol code
 *
 * Contain the base object for symbols locating.
 *
 * Status:
 *  Open:   1
 *  Locked: 3
 *
 */

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "cc_music_symbols.hh"

using namespace std;
using namespace cv;

namespace cc{

// Status: Open
void MusicSheetReaderSymbolsLocator::Test(Mat image){
	int percentage = 75;

	Mat pattern = imread("N4.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat result  = _matchPattern(pattern, image);

	threshold(result, result, percentage * 255 / 100, 255, 0);
	auto contour = _locateContours(result);
	imshow("p", result);
	return;

}

// Status: Final
Mat MusicSheetReaderSymbolsLocator::_matchPattern(Mat pattern, Mat image){
	Mat result_f, result;
	matchTemplate(image, pattern, result_f, CV_TM_CCOEFF);
	normalize(result_f, result_f, 0, 255, NORM_MINMAX, -1, Mat() );
	result_f.convertTo(result, CV_8UC1);
	return result;
}

// Status: Locked
vector<Vec4i> MusicSheetReaderSymbolsLocator::_locateContours(Mat image){
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

// Status: Final
Point MusicSheetReaderSymbolsLocator::_locateMax(Mat image, Vec4i frame){
	Mat src = image(Rect(frame[0], frame[1], frame[2] - frame[0], frame[3] - frame[1]));
	double minVal, maxVal;
	Point minLoc, maxLoc;
	minMaxLoc(src, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
	return Point(maxLoc.x + frame[0], maxLoc.y + frame[1]);
}

vector<Vec4i> MusicSheetReaderSymbolsLocator::_locatePatterns(Mat image, Mat pattern, int percentage){
	vector<Vec4i> res;
	Mat result = _matchPattern(pattern, image);
	Mat bin;

	threshold(result, bin, percentage * 255 / 100, 255, 0);
	auto blocks = _locateContours(bin);
	for (auto b : blocks){
		Point p = _locateMax(result, b);
		cout << p.x << ' ' << p.y << endl;
		res.push_back(Vec4i(p.x, p.y, p.x + pattern.cols, p.y + pattern.rows));
	}
	return res;
}

}

/* CC Music Reader Stave Locator code
 *
 * Contain the object used to locate music staves from images.
 *
 */

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "opencv_utils.hh"
#include "music_error.hh"
#include "staves.hh"

using namespace std;
using namespace cv;

// Private functions

void useHough(const Mat& image, vector<Vec4i>& res){
	// HoughLinesP setting
	int threshold = image.cols / 4;
	int minLen = image.cols / 2;
	int maxGap = 10;
	HoughLinesP(image, res, 1, CV_PI/2, threshold, minLen, maxGap);
}

bool locateStaves(vector<Vec4i>& lines, const int width, vector<Vec4i>& staves){
	// sort the result base on y1
	auto cmp = [](const Vec4i& l, const Vec4i& r){
		return l[1]<r[1];
	};
	sort(lines.begin(), lines.end(), cmp);

	bool fl = false;
	int a = 0;
	int x1 = width;
	int x2 = 0;
	int y1;
	int y2 = -2;

	// group lines into staves
	for (auto l : lines){

		if (l[1] != y2+1){
			if (a == 0){
				if (fl) staves.push_back(Vec4i(x1, y1, x2, y2));
				fl = true;
				y1 = l[1];
				x1 = width;
				x2 = 0;
			}
			if (a == 4){
				a = 0;
			} else
				a++;
		}

		if (x1 > l[0]) x1 = l[0];
		if (x2 < l[2]) x2 = l[2];
		y2 = l[1];
	}
	staves.push_back(Vec4i(x1, y1, x2, y2));

	return a != 0;
}

// Objects members

namespace cc {

void StavesLocator::locateFrom(Mat binary_image){

	// Apply Morph transform to eliminate noise
	lines_image = applyMorphFilter(binary_image,9,1);

	// use Hough transform to find the sheet lines
	useHough(lines_image, hough_lines);

	// locate staves from list of sheet lines
	if (locateStaves(hough_lines, lines_image.cols, staves)) throw Error::StavesFail; // throw
}

}

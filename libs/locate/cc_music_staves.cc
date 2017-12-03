/* CC Music Reader Stave Locator code
 *
 * Contain the object used to locate music staves from images.
 *
 * Status:
 *  Locked: 3
 *
 */

#include "cc_music_staves.hh"
#include "cc_music_transform.hh"
#include "cc_opencv_ultils.hh"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace cc {

// Status: Locked
bool StavesLocator::locateFrom(Mat binary_image){

	// Apply Morph transform to eliminate noise
	lines_image = applyMorphFilter(binary_image,9,1);

	// use Hough transform to find the sheet lines
	_useHough(lines_image, hough_lines);

	// locate staves from list of sheet lines
	if (!_locateStaves(hough_lines, lines_image.cols))
		return false;

	// if locateStaves succeeded
	return true;
}

// Status: Locked
void StavesLocator::_useHough(Mat& image, vector<Vec4i>& res){
	// set up HoughLinesP
	int threshold = image.cols / 4;
	int minLen = image.cols / 2;
	int maxGap = 10;
	HoughLinesP(image, res, 1, CV_PI/2, threshold, minLen, maxGap);
}

// Status: Locked
bool StavesLocator::_locateStaves(vector<Vec4i> &lines, int width){
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

		if (x1 > l[0]) x1 = l[0];
		if (x2 < l[2]) x2 = l[2];

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
		y2 = l[1];
	}
	staves.push_back(Vec4i(x1, y1, x2, y2));

	return a == 0;
}

}

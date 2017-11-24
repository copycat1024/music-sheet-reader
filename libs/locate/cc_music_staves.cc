/* CC Music Reader Stave Locator code
 *
 * Contain the object used to locate music staves from images.
 *
 * Status:
 * 	Open:   2
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
std::vector<cv::Vec4i> StavesLocator::Staves() const{
	return _staves;
}

// Status: Locked
bool StavesLocator::locateStavesFrom(Mat binary_image){

	// Apply Morph transform to eliminate noise
	
	_sheet_lines_image = applyMorphFilter(binary_image,9,1);

	// use Hough transform to find the sheet lines
	auto hough_line = _locateSheetLines(_sheet_lines_image);
	cout << "    Locating done." << endl;
	hough_line = _sanitizeSheetLines(hough_line);
	cout << "    Sanitizing done." << endl;
	cout << "  Hough transform done." << endl;

	// locate staves from list of sheet lines
	if (!_locateStaves(hough_line)) return false;

	// if locateStaves succeeded
	_lines = hough_line;
	return true;
}

// Status: Locked
vector<Vec4i> StavesLocator::_locateSheetLines(Mat image){
	vector<Vec4i> lines; // direct result from HoughLinesP

	// set up HoughLinesP
	int line_min_size = 10;
	int threshold = image.cols / 10;
	int minLen = image.cols / 2;
	int maxGap = 10;
	HoughLinesP(image, lines, 1, CV_PI/2, threshold, minLen, maxGap);

	// results
	return lines;
}

// Status: Open
vector<Vec4i> StavesLocator::_sanitizeSheetLines(vector<Vec4i> lines){
	vector<Vec4i> res;

	// sort the result base on y1
	auto cmp = [](const Vec4i& l, const Vec4i& r){
		return l[1]<r[1];
	};
	sort(lines.begin(), lines.end(), cmp);
	cout << "     Sorting done" << endl;

	// pick the fist line in a block of adjacent lines
	int i,c=0,s=0;
	if (lines.size()==0) return res;
	res.push_back(lines[0]);
	for(i = 1; i<lines.size(); i++){
		if (lines[i][1]!=lines[i-1][1]+1){
			c++;
			if (c%5 != 0){
				s+=lines[i][1]-lines[i-1][1];
			}
			res.push_back(lines[i]);
		}
	}
	cout << "      Picking done" << endl;

	return res;
}

// Status: Open
bool StavesLocator::_locateStaves(vector<Vec4i> lines){
	vector<Vec4i> res; // list of staves
	int i;
	int left_x, right_x, top_y, bottom_y;

	// check if the number of lines devides to 5 (since there are 5 lines in a stave)
	if (lines.size()%5!=0){
		cout << "Number does not match." << endl;
		cout << "Found: " << lines.size() << endl;
		return false;
	}

	// get the left-est x1 and x2, these will be the coordinates for all staves
	// also check if any line is sloped
	left_x = lines[i][0];
	right_x = lines[i][2];
	for (i=0; i<lines.size(); i++){
		if (left_x < lines[i][0]) left_x = lines[i][0];
		if (right_x < lines[i][2]) right_x = lines[i][2];
		if (lines[i][1] != lines[i][3]) {
			cout << "Line " << i << " is sloped." << endl;
			cout << lines[i][1] << ' ' << lines[i][3] << endl;
			return false;
		}
	}

	// get the y1 of the 1st and 5th line as the coordinates of each stave
	for (i=0; i<lines.size()/5; i++){
		top_y = lines[i*5][1];
		bottom_y = lines[i*5 + 4][1];
		res.push_back(Vec4i(left_x, top_y, right_x, bottom_y));
	}

	// Results
	_staves = res;
	return true;
}

}

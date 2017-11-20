/* CC Music Reader Lines Locator code
 *
 * Contain the object used to precisely locate stave lines from images.
 *
 * Status:
 *  Locked: 4
 *
 */

#include "cc_music_lines.hh"
#include "cc_music_transform.hh"
#include "cc_opencv_ultils.hh"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace cc {

// Status: Locked
vector<Vec4i> MusicSheetReaderLinesLocator::Lines() const{
	vector<Vec4i> res;
	for (auto c: _lines){
		res.push_back(Vec4i(_left_x, c, _right_x, c));
	}
	return res;
}

// Status: Locked
bool MusicSheetReaderLinesLocator::locateLinesFrom(Mat image, vector<Vec4i> frames){
	//
	_left_x  = frames[0][0];
	_right_x = frames[0][2];

	for (auto f: frames)
		_locateLinesFromFrame(image, f);

	return _lines.size() == frames.size()*5;
}

// Status: Locked
void MusicSheetReaderLinesLocator::_locateLinesFromFrame(Mat image, Vec4i frame){
	// set up area of interest and add padding
	int x1 = frame[0];
	int x2 = frame[2];
	int y1 = frame[1] - 2;
	int y2 = frame[3] + 4;

	// list
	vector<int> v;
	int i,j;
	unsigned char* p;

	v.resize(y2-y1+1);
	for(i=y1; i<=y2; ++i){
				p = image.ptr<uchar>(i);
				for (j=x1; j<x2; ++j){
						v[i-y1] += (p[j]/16)*(p[j]/16);
				}
		}

	for (i=1; i<v.size()-1; ++i)
		if (v[i] < v[i-1] && v[i] < v[i+1] && v[i] / (_right_x - _left_x) < 64)
			_lines.push_back(i+y1);
}

}

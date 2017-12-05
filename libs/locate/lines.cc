/* CC Music Reader Lines Locator code
 *
 * Contain the object used to precisely locate stave lines from images.
 *
 * Status:
 *  Locked: 1
 *  Open:   1
 *
 */

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "opencv_utils.hh"
#include "music_error.hh"
#include "music_transform.hh"
#include "lines.hh"

using namespace std;
using namespace cv;

namespace cc {

// Status: Open
void LinesLocator::locateFrom(Mat image, vector<Vec4i> frames){
	for (auto f: frames)
		_locateFromFrame(image, f);

	if (lines.size() != frames.size()*5) throw Error::LinesFail; // throw
}

// Status: Locked
void LinesLocator::_locateFromFrame(Mat image, Vec4i frame){
	// set up area of interest and add padding
	int x1 = frame[0];
	int x2 = frame[2];
	int y1 = frame[1] - 2;
	int y2 = frame[3] + 2;

	// calculate the squared sum of all point in each line into v
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

	// find local peaks that has the average value per point lower than 64
	for (i=1; i<v.size()-1; ++i)
		if (v[i] < v[i-1] && v[i] < v[i+1] && v[i] / (x2 - x1) < 64)
			lines.push_back(Vec4i(x1, i+y1, x2, i+y1));
}

}

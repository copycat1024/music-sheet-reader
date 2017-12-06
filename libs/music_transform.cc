/* CC Music Reader Transform code
 *
 * Contain the functions that transform Mat images.
 *
 * Status:
 *  Locked: 3
 *
 */

#include "music_transform.hh"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

namespace cc {

// Status: Locked
Mat applyMorphFilter(Mat binary_image, int x, int y){
	Mat morphStructure = getStructuringElement(MORPH_RECT, Size(x,y));
	Mat r = binary_image.clone();
	erode(r, r, morphStructure, Point(-1, -1));
	dilate(r, r, morphStructure, Point(-1, -1));
	return r;
}

// Status: Locked
Mat applyMorphFilter(Mat binary_image, int x){
	return applyMorphFilter(binary_image, x, x);
}

// Status: Locked
Mat polarize(Mat image){
	Mat res;
	int mask_size = (image.cols/100)*2 + 1;
	adaptiveThreshold(~image, res, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, mask_size, -2);
	return res;
}

}

/* CC Music Reader Clef code
 *
 * Contain the base object for clefs locating.
 *
 * Status:
 *  Open: 1
 *
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include "clefs.hh"

using namespace std;
using namespace cv;

namespace cc{

//Status: Open
void ClefsLocator::locateClefsFrom(Mat image){
	int percentage = 75;

	Mat pattern = imread("pattern/g-clef.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	GClefs = _locatePatterns(image, pattern, percentage);
	return;
}

}

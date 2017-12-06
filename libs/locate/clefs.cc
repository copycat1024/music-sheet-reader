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
void ClefsLocator::locateFrom(Mat image, double gap_size){
	const int percentage = 75;
	const double model_size = 7.75;

	Mat model = imread("pattern/g-clef.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat pattern;

	double f = gap_size / model_size;
	Size p_size(model.cols * f, model.rows * f);

	resize(model, pattern, p_size, 0, 0, INTER_LINEAR);
	GClefs = _locatePatterns(image, pattern, percentage);

	cout << "Gap size " << gap_size << endl;

/*
	Vec4i v = GClefs[0];
	Mat c = image(Rect(v[0], v[1], v[2] - v[0], v[3] - v[1]));
	imwrite("present/clef.jpg", c);
*/
	return;
}

}

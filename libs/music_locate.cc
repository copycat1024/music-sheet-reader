/* CC Music Reader Locator code
 *
 * Contain the object used to locate the elements of the music sheet.
 *
 */

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "opencv_utils.hh"
#include "music_locate.hh"
#include "music_io.hh"
#include "music_error.hh"

using namespace std;
using namespace cv;

// Local functions
Mat polarize(Mat image){
	Mat res;
	int mask_size = (image.cols/100)*2 + 1;
	adaptiveThreshold(~image, res, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, mask_size, -2);
	return res;
}

namespace cc {

// Interfaces

const std::vector<cv::Vec4i>& Locator::Lines() const{
	return _lines.lines;
}

const std::vector<cv::Vec4i>& Locator::Staves() const{
	return _staves.staves;
}

std::vector<cv::Vec4i> Locator::Symbols(){
	return _con.result;
}

void Locator::locateFrom(Mat image){

	// Convert greyscale image to binary image by adaptive threshold
	_binary_image = polarize(image);

	imwrite("debug/binary.bmp", _binary_image);

	// Locate staves from binary image
	_staves.locateFrom(_binary_image);

	// Locate lines from greyscale image
	_lines.locateFrom(image, _staves.staves);

	// Open ---------------------------------------------------
//	_clefs.locateFrom(image, _lines.gap_size);
	_con.locateFrom(_binary_image, _staves.staves);
	// --------------------------------------------------------
}

}

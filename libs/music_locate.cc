/* CC Music Reader Locator code
 *
 * Contain the object used to locate the elements of the music sheet.
 *
 * Status:
 *  Open:   1
 *  Legacy: 4
 *  Locked: 3
 *
 */

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "opencv_utils.hh"
#include "music_locate.hh"
#include "music_io.hh"
#include "music_transform.hh"
#include "music_error.hh"
#include "locate/symbols.hh"

using namespace std;
using namespace cv;

namespace cc {

// Interfaces

// Status: Locked
const std::vector<cv::Vec4i>& Locator::Lines() const{
	return _lines.lines;
}

// Status: Locked
const std::vector<cv::Vec4i>& Locator::Staves() const{
	return _staves.staves;
}

// Status: Legacy
std::vector<cv::Vec4i> Locator::Symbols(){
	return _sym.result;
}

// Status: Open
void Locator::locateFrom(Mat image){

	// Convert greyscale image to binary image by adaptive threshold
	_binary_image = polarize(image);
	Mat _symbol_image = applyMorphFilter(_binary_image, 1, 3);

	imwrite("debug/sym.jpg", _symbol_image);
	imwrite("debug/binary.jpg", _binary_image);

	// Locate staves from binary image
	_staves.locateFrom(_binary_image);

	// Locate lines from greyscale image
	_lines.locateFrom(image, _staves.staves);

	// Open ---------------------------------------------------
//	SymbolsLocator s;
//	s.Test(image);
	_clefs.locateFrom(image, _lines.gap_size);
	_sym.locateFrom(_symbol_image);
	// --------------------------------------------------------
}

// Status: Legacy
void Locator::locateSymbols(Vec4i stave){
	Mat image = _binary_image(Rect(stave[0], stave[1], stave[2] - stave[0], stave[3] - stave[1]));
	image = applyMorphFilter(image, 3);
//	_locateContours(stave, image);
}

}

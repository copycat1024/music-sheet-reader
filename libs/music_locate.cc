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

#include "music_locate.hh"
#include "music_io.hh"
#include "music_transform.hh"
#include "opencv_utils.hh"
#include "locate/symbols.hh"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

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
	return _clefs.GClefs;
}

// Status: Open
void Locator::locateFrom(Mat image){

	// Convert greyscale image to binary image by adaptive threshold
	_binary_image = polarize(image);

	// Locate staves from binary image
	cout << "Locating staves ... " << endl;
	if (!_staves.locateFrom(_binary_image)){
		throw Error::StavesFail;
	}
	cout << " Done." << endl;

	// Locate lines from greyscale image
	cout << "Locating lines ..." << endl;
	if (!_lines.locateFrom(image, _staves.staves)){
		throw Error::LinesFail;
	}
	cout << " Done." << endl;

	// Open ---------------------------------------------------
//	SymbolsLocator s;
//	s.Test(image);
	_clefs.locateClefsFrom(image);
	// --------------------------------------------------------
}

// Status: Legacy
void Locator::locateSymbols(Vec4i stave){
	Mat image = _binary_image(Rect(stave[0], stave[1], stave[2] - stave[0], stave[3] - stave[1]));
	image = applyMorphFilter(image, 3);
//	_locateContours(stave, image);
}

}
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

#include "cc_music_locate.hh"
#include "cc_music_io.hh"
#include "cc_music_transform.hh"
#include "cc_opencv_ultils.hh"
#include "locate/cc_music_symbols.hh"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace cc {

// Interfaces

// Status: Locked
cv::Mat MusicSheetReaderLocator::imageBinary(){
	return _binary_image;
}

// Status: Locked
std::vector<cv::Vec4i> MusicSheetReaderLocator::Lines(){
	return _lines.Lines();
}

// Status: Locked
std::vector<cv::Vec4i> MusicSheetReaderLocator::Staves(){
	return _staves.Staves();
}

// Status: Legacy
std::vector<cv::Vec4i> MusicSheetReaderLocator::Symbols(){
	return _symbols;
}

// Heavy-lifting code

// Status: Open
bool MusicSheetReaderLocator::locateMusicSheetFrom(Mat image){

	// Convert greyscale image to binary image by adaptive threshold
	_binary_image = polarize(image);

	// Locate staves from binary image
	if (!_staves.locateStavesFrom(_binary_image)){
		cout << "Locate staves failed." << endl;
		return false;
	}

	// Locate lines from greyscale image
	if (!_lines.locateLinesFrom(image, _staves.Staves())){
		cout << "Locate lines failed." << endl;
		return false;
	}

	// Open ---------------------------------------------------
	MusicSheetReaderSymbolsLocator s;
	s.Test(image);
	// --------------------------------------------------------
	return true;
}

// Status: Legacy
void MusicSheetReaderLocator::locateSymbols(Vec4i stave){
	Mat image = _binary_image(Rect(stave[0], stave[1], stave[2] - stave[0], stave[3] - stave[1]));
	image = applyMorphFilter(image, 3);
//	_locateContours(stave, image);
}

}

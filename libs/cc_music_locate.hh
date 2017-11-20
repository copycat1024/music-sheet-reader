/* CC Music Reader Locator header
 *
 * Contain the object used to locate the elements of the music sheet.
 *
 * Status: Legacy
 *
 */

#ifndef CC_MUSIC_LOCATE
#define CC_MUSIC_LOCATE

#include <opencv2/core/core.hpp>
#include <vector>
#include "locate/cc_music_staves.hh"
#include "locate/cc_music_lines.hh"

namespace cc {

class MusicSheetReaderLocator {
public:
	// take greyscale image of music sheet
	bool locateMusicSheetFrom(cv::Mat);

	// get binary image
	cv::Mat imageBinary();

	// get list of sheet lines in Vec4i
	std::vector<cv::Vec4i> Lines();

	// get list of located staves
	std::vector<cv::Vec4i> Staves();

	// get list of located symbols
	std::vector<cv::Vec4i> Symbols();

	// use to locate symbols
	void locateSymbols(cv::Vec4i);

	// developing function
	void locateSymbols2(cv::Mat);
private:
	MusicSheetReaderStavesLocator _staves;
	MusicSheetReaderLinesLocator _lines;

	std::vector<cv::Vec4i> _symbols;
	cv::Mat _binary_image;
	bool _success;
};

}

#endif

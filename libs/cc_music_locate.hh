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
#include "locate/cc_music_clefs.hh"

namespace cc {

class Debugger;

// error codes
enum class Error{
	StavesFail,
	LinesFail
};

class Locator {
public:
	// take greyscale image of music sheet
	void locateFrom(cv::Mat);

	// get binary image
	cv::Mat& imageBinary();

	// get list of sheet lines in Vec4i
	std::vector<cv::Vec4i> Lines();

	// get list of located staves
	std::vector<cv::Vec4i>& Staves();

	// get list of located symbols
	std::vector<cv::Vec4i> Symbols();

	// use to locate symbols
	void locateSymbols(cv::Vec4i);

	// developing function
	void locateSymbols2(cv::Mat);
private:
	StavesLocator _staves;
	LinesLocator  _lines;
	ClefsLocator  _clefs;

	cv::Mat _binary_image;

	friend Debugger;
};

}

#endif

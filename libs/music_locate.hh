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
#include "locate/staves.hh"
#include "locate/lines.hh"
#include "locate/clefs.hh"

namespace cc {

class Debugger;

class Locator {
public:
	// take greyscale image of music sheet
	void locateFrom(cv::Mat);

	// get list of sheet lines in Vec4i
	const std::vector<cv::Vec4i>& Lines() const;

	// get list of located staves
	const std::vector<cv::Vec4i>& Staves() const;

	// get list of located symbols
	std::vector<cv::Vec4i> Symbols();

	// use to locate symbols
	void locateSymbols(cv::Vec4i);

	// developing function
	void locateSymbols2(cv::Mat);
private:
	StavesLocator  _staves;
	LinesLocator   _lines;
	ClefsLocator   _clefs;
	SymbolsLocator _sym;

	cv::Mat _binary_image;

	friend Debugger;
};

}

#endif

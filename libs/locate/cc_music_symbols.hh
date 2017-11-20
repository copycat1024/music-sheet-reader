/* CC Music Reader Lines Symbol code
 *
 * Contain the base object for symbols locating.
 *
 * Status: Open
 *
 */

#ifndef CC_MUSIC_SYMBOLS
#define CC_MUSIC_SYMBOLS

#include <opencv2/core/core.hpp>
#include <vector>

namespace cc {

class MusicSheetReaderSymbolsLocator {
public:
	void Test(cv::Mat);
protected:
	cv::Mat _matchPattern(cv::Mat, cv::Mat, int);
	std::vector<cv::Vec4i> _locateContours(cv::Mat);
};

}
#endif

/* CC Music Reader Symbol header
 *
 * Contain the base object for symbols locating.
 *
 * Status: Locked
 *
 */

#ifndef CC_MUSIC_SYMBOLS
#define CC_MUSIC_SYMBOLS

#include <opencv2/core/core.hpp>
#include <vector>
#include "music_error.hh"

namespace cc {

class SymbolsLocator {
public:
	void locateFrom(const cv::Mat&);

	std::vector<cv::Vec4i> result;
protected:
	double quality;
protected:
	std::vector<cv::Vec4i> _locateContours(const cv::Mat&);
	std::vector<cv::Vec4i> _locatePatterns(const cv::Mat&, const cv::Mat&, const int);
};

}
#endif

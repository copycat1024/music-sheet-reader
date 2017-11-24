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

namespace cc {

class SymbolsLocator {
public:
	void Test(cv::Mat);
protected:
	std::vector<cv::Vec4i> _locateContours(cv::Mat);
	std::vector<cv::Vec4i> _locatePatterns(cv::Mat, cv::Mat, int);
private:
	cv::Mat _matchPattern(cv::Mat, cv::Mat);
	cv::Point _locateMax(cv::Mat, cv::Vec4i);
};

}
#endif

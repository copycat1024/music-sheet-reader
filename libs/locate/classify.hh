/* CC Music Reader symbols classifier header
 *
 * Contain the object for classifying symbols from contours locating.
 *
 */

#ifndef CC_MUSIC_CLASSIFY
#define CC_MUSIC_CLASSIFY

#include <opencv2/core/core.hpp>
#include <vector>

namespace cc {

class SymbolsClassifier {
public:
	void locateFrom(const std::vector<cv::Mat>&);
	std::vector<std::vector<int>> result;
private:
	std::vector<cv::Mat> _h;
	std::vector<cv::Mat> _v;
	int _compare(int, int);
};

}

#endif

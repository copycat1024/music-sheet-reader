/* CC Music Reader Lines Locator header
 *
 * Contain the object used to precisely locate stave lines from images.
 *
 * Status: Locked
 *
 */

#ifndef CC_MUSIC_LINES
#define CC_MUSIC_LINES

#include <opencv2/core/core.hpp>
#include <vector>

namespace cc {

class LinesLocator {
public:
	bool locateLinesFrom(cv::Mat, std::vector<cv::Vec4i>);
	std::vector<cv::Vec4i> lines;
private:
	void _locateLinesFromFrame(cv::Mat, cv::Vec4i);
};

}
#endif

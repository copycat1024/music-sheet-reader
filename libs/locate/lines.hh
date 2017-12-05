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
	// list of located lines
	std::vector<cv::Vec4i> lines;

	// take greyscale image and list of staves
	void locateFrom(cv::Mat, std::vector<cv::Vec4i>);
private:
	void _locateFromFrame(cv::Mat, cv::Vec4i);
};

}
#endif

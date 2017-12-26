/* CC Music Reader Lines Locator header
 *
 * Contain the object used to precisely locate stave lines from images.
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

	// size of the gap between lines
	double gap_size;
};

}
#endif

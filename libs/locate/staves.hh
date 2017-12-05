/* CC Music Reader Stave Locator header
 *
 * Contain the object used to locate music staves from images.
 *
 * Status: Legacy
 *
 */

#ifndef CC_MUSIC_FRAMES
#define CC_MUSIC_FRAMES

#include <opencv2/core/core.hpp>
#include <vector>

namespace cc {

class StavesLocator {
public:
	// list of located staves
	std::vector<cv::Vec4i> staves;

	// take binary image of music sheet
	void locateFrom(cv::Mat);

	// image used by HoughLinesP
	cv::Mat lines_image;

	// direct result from HoughLinesP
	std::vector<cv::Vec4i> hough_lines;
};

}

#endif

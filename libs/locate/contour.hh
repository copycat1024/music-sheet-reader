/* CC Music Reader Contour locator header
 *
 * Contain the base object for symbols locating by contours locating.
 *
 */

#ifndef CC_MUSIC_CONTOUR
#define CC_MUSIC_CONTOUR

#include <opencv2/core/core.hpp>
#include <vector>
#include "music_error.hh"

namespace cc {

class ContoursLocator {
public:
	void locateFrom(const cv::Mat&, const std::vector<cv::Vec4i>&);
	std::vector<cv::Vec4i> result;
	cv::Mat symbol_image;
};

}

#endif

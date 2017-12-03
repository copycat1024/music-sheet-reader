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

class Presenter;

class StavesLocator {
public:
	// get list of located staves
	std::vector<cv::Vec4i> staves;

	// take binary image of music sheet
	bool locateStavesFrom(cv::Mat);
private:
	std::vector<cv::Vec4i> _hough_line;
	cv::Mat _sheet_lines_image;

	std::vector<cv::Vec4i> _useHough(cv::Mat);
	bool _locateStaves(std::vector<cv::Vec4i>&, int);

	friend Presenter;
};

}

#endif

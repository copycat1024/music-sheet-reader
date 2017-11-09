#ifndef CC_MUSIC_LINES
#define CC_MUSIC_LINES

#include <opencv2/core/core.hpp>
#include <vector>

namespace cc {

class MusicSheetReaderLinesLocator {
public:
	void locateLinesFrom(cv::Mat, std::vector<cv::Vec4i>);
};

}
#endif

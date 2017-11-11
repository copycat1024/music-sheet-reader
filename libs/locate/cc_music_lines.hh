#ifndef CC_MUSIC_LINES
#define CC_MUSIC_LINES

#include <opencv2/core/core.hpp>
#include <vector>

namespace cc {

class MusicSheetReaderLinesLocator {
public:
	bool locateLinesFrom(cv::Mat, std::vector<cv::Vec4i>);
	std::vector<cv::Vec4i> Lines() const;
private:
	int _left_x, _right_x;
	void _locateLinesFromFrame(cv::Mat, cv::Vec4i);
	std::vector<int> _lines;
};

}
#endif

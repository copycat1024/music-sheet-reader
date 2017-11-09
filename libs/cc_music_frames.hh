#ifndef CC_MUSIC_FRAMES
#define CC_MUSIC_FRAMES

#include <opencv2/core/core.hpp>
#include <vector>

namespace cc {

class MusicSheetReaderFramesLocator {
public:
	// get list of sheet lines in Vec4i
	std::vector<cv::Vec4i> Lines();

	// get list of located frames
	std::vector<cv::Vec4i> Frames();

	// check if locateFramesFrom can locate
	bool Success();

	// take binary image of music sheet
	void locateFramesFrom(cv::Mat);
private:
	std::vector<cv::Vec4i> _lines, _frames;
	cv::Mat _sheet_lines_image;
	float _gap_size;
	bool _success;
	void _locateSheetLines(cv::Mat);
	void _locateFrames(std::vector<cv::Vec4i>);
};

}

#endif

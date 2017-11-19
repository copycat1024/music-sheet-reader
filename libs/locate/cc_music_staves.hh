#ifndef CC_MUSIC_FRAMES
#define CC_MUSIC_FRAMES

#include <opencv2/core/core.hpp>
#include <vector>

namespace cc {

class MusicSheetReaderFramesLocator {
public:
	// get list of sheet lines
	std::vector<cv::Vec4i> Lines() const;

	// get list of located frames
	std::vector<cv::Vec4i> Frames() const;

	// take binary image of music sheet
	bool locateFramesFrom(cv::Mat);
private:
	std::vector<cv::Vec4i> _lines, _frames;
	cv::Mat _sheet_lines_image;
	float _gap_size;
	std::vector<cv::Vec4i> _locateSheetLines(cv::Mat);
	bool _locateFrames(std::vector<cv::Vec4i>);
};

}

#endif

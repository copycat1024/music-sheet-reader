#ifndef CC_MUSIC_FRAMES
#define CC_MUSIC_FRAMES

#include <opencv2/core/core.hpp>
#include <vector>

namespace cc {

class MusicSheetReaderStavesLocator {
public:
	// get list of sheet lines
	std::vector<cv::Vec4i> Lines() const;

	// get list of located staves
	std::vector<cv::Vec4i> Staves() const;

	// take binary image of music sheet
	bool locateStavesFrom(cv::Mat);
private:
	std::vector<cv::Vec4i> _lines, _staves;
	cv::Mat _sheet_lines_image;
	float _gap_size;
	std::vector<cv::Vec4i> _locateSheetLines(cv::Mat);
	bool _locateStaves(std::vector<cv::Vec4i>);
};

}

#endif

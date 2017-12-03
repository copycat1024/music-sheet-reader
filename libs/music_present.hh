/* CC Music Reader Presenter header
 *
 * Contain the object used to present the result.
 *
 * Status: Locked
 *
 */

#ifndef CC_MUSIC_PRESENT
#define CC_MUSIC_PRESENT

#include <opencv2/core/core.hpp>
#include <string>
#include <vector>
#include "music_locate.hh"

namespace cc{

std::vector<cv::Mat> splitStaves(cv::Mat, std::vector<cv::Vec4i>);

class Presenter{
public:
	// present input image
	void presentInput(cv::Mat);

	// present results
	void presentResults(Locator);

	// hold the images being shown until a key is pressed
	void presentHold();
private:
	cv::Mat _input_image;

	Locator _loc;

	void _drawLines(cv::Mat, std::vector<cv::Vec4i>, cv::Scalar);
	void _drawRects(cv::Mat, std::vector<cv::Vec4i>, cv::Scalar);

	void _presentStavesAndLines();

};

}

#endif

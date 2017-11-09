#ifndef CC_MUSIC_PRESENT
#define CC_MUSIC_PRESENT

#include <opencv2/core/core.hpp>
#include <string>
#include <vector>

namespace cc{

void drawLines(cv::Mat, std::vector<cv::Vec4i>, cv::Scalar);
void drawRects(cv::Mat, std::vector<cv::Vec4i>, cv::Scalar);
std::vector<cv::Mat> splitFrames(cv::Mat, std::vector<cv::Vec4i>);

}

#endif

#ifndef CC_MUSIC_LOCATE
#define CC_MUSIC_LOCATE

#include <opencv2/core/core.hpp>
#include <vector>

std::vector<cv::Vec4i> locateFrames(std::vector<cv::Vec4i>);
std::vector<cv::Vec4i> locateSheetLines(cv::Mat);
std::vector<cv::Vec4i> locateSymbols(cv::Mat image, cv::Vec4i frame);

#endif

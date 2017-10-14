#ifndef CC_MUSIC_EDIT
#define CC_MUSIC_EDIT

#include <opencv2/core/core.hpp>
#include <string>
#include <vector>

void drawLines(cv::Mat, std::vector<cv::Vec4i>, cv::Scalar);
void drawRects(cv::Mat, std::vector<cv::Vec4i>, cv::Scalar);
void removeLine(cv::Mat, cv::Vec4i);
void polarize(cv::Mat, int);
void inverse(cv::Mat);

#endif
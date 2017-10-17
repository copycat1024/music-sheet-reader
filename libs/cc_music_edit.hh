#ifndef CC_MUSIC_EDIT
#define CC_MUSIC_EDIT

#include <opencv2/core/core.hpp>
#include <string>
#include <vector>

void drawLines(cv::Mat, std::vector<cv::Vec4i>, cv::Scalar);
void drawRects(cv::Mat, std::vector<cv::Vec4i>, cv::Scalar);
void applyMorphFilter(cv::Mat, int, int);
void applyMorphFilter2(cv::Mat, int);
void removeAllLines(cv::Mat, std::vector<cv::Vec4i>);
cv::Mat polarize(cv::Mat);
void inverse(cv::Mat);

#endif

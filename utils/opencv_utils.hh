#ifndef CC_OPENCV_ULTILS
#define CC_OPENCV_ULTILS

#include <opencv2/core/core.hpp>
#include <string>
#include <vector>

std::string typeToStr(const cv::Mat&);
std::string depthToStr(const cv::Mat&);

void drawLines(cv::Mat image, std::vector<cv::Vec4i> vec, cv::Scalar color);
void drawRects(cv::Mat image, std::vector<cv::Vec4i> vec, cv::Scalar color);

cv::Mat applyMorphFilter(cv::Mat, int, int);
cv::Mat crop(cv::Mat, cv::Vec4i);
#endif

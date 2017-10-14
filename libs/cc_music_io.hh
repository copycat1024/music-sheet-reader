#ifndef CC_MUSIC_IO
#define CC_MUSIC_IO

#include <opencv2/core/core.hpp>
#include <string>
#include <vector>

bool fileExist(char*);
cv::Mat loadGreyImage(char*);
void showImage(std::string, cv::Mat);
void showHold();
void drawLines(cv::Mat, std::vector<cv::Vec4i>, cv::Scalar);

#endif

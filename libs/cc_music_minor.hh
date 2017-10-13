#ifndef CC_MUSIC_MINOR
#define CC_MUSIC_MINOR

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <vector>

#define DEBUG1

bool fileExist(char*);
cv::Mat polarize(cv::Mat, int);

cv::Mat loadGreyImage(char*);
void showImage(std::string, cv::Mat);
void showHold();
std::vector<cv::Vec4i> getSheetLines(cv::Mat);
cv::Mat makeShowImage(cv::Mat, std::vector<cv::Vec4i>, cv::Scalar);
std::vector<cv::Vec4i> locateFrames(std::vector<cv::Vec4i>);

#endif

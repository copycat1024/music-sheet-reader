#ifndef CC_MUSIC_TRANSFORM
#define CC_MUSIC_TRANSFORM

#include <opencv2/core/core.hpp>
#include <string>
#include <vector>

namespace cc{

cv::Mat applyMorphFilter(cv::Mat, int, int);
cv::Mat applyMorphFilter(cv::Mat, int);
void removeAllLines(cv::Mat, std::vector<cv::Vec4i>);
cv::Mat polarize(cv::Mat);
void inverse(cv::Mat);

}

#endif

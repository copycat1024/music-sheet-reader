/* CC Music Reader Transform header
 *
 * Contain the functions that transform Mat images.
 *
 * Status: Legacy
 *
 */

#ifndef CC_MUSIC_TRANSFORM
#define CC_MUSIC_TRANSFORM

#include <opencv2/core/core.hpp>
#include <string>
#include <vector>

namespace cc{

cv::Mat applyMorphFilter(cv::Mat, int, int);
cv::Mat applyMorphFilter(cv::Mat, int);
cv::Mat polarize(cv::Mat);
void removeLine(cv::Mat, cv::Vec4i, int);
void removeAllLines(cv::Mat, std::vector<cv::Vec4i>);
void inverse(cv::Mat);

}

#endif

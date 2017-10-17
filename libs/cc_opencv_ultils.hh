#ifndef CC_OPENCV_ULTILS
#define CC_OPENCV_ULTILS

#include <opencv2/core/core.hpp>
#include <string>
#include <vector>

std::string typeToStr(const cv::Mat&);
std::string depthToStr(const cv::Mat&);

class IntSegment {
public:
  int x1,x2,y1,y2;
  IntSegment(cv::Vec4i);
  IntSegment operator=(cv::Vec4i);
};

typedef std::vector<IntSegment> IntSegmentArray;

#endif

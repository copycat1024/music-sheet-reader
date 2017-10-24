#ifndef CC_MUSIC_LOCATE
#define CC_MUSIC_LOCATE

#include <opencv2/core/core.hpp>
#include <vector>

namespace cc {

std::vector<cv::Vec4i> locateFrameLines(cv::Mat, cv::Vec4i);
std::vector<cv::Vec4i> locateSymbols(cv::Mat image, cv::Vec4i frame);

class MusicSheetReaderLocator {
public:
  void locateMusicSheetFrom(cv::Mat);
  cv::Mat imageSheetLines();
  cv::Mat imageBinary();
  std::vector<cv::Vec4i> Lines();
  std::vector<cv::Vec4i> Frames();
  std::vector<cv::Vec4i> Symbols();
  bool Success();
  void locateSymbols(cv::Vec4i);
  void locateSymbols2(cv::Mat);
private:
  std::vector<cv::Vec4i> _lines, _frames, _symbols;
  cv::Mat _sheet_lines_image, _binary_image;
  bool _success;
  float _gap_size;
  void _locateSheetLines(cv::Mat);
  void _locateFrames(std::vector<cv::Vec4i>);
  
};

}
#endif

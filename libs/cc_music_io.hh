#ifndef CC_MUSIC_IO
#define CC_MUSIC_IO

#include <opencv2/core/core.hpp>
#include <string>

namespace cc {

class MusicSheetReaderIO {
public:
  bool fileExist(const char*);
  bool loadGreyImage(const char*, cv::Mat&);
  void showImage(std::string, cv::Mat);
  void showHold();
};

}
#endif

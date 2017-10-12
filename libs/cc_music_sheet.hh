#ifndef CC_MUSIC_SHEET
#define CC_MUSIC_SHEET

#include <opencv2/core/core.hpp>

enum TaskNumber {
  NO_ARGUMENT,
  INPUT_FILE_ERROR,
  PROCESS_INPUT_FILE
};

TaskNumber handleArguments(int, char**);
bool fileExist(char*);
void processImage(char*);

#endif

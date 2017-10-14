#ifndef CC_MUSIC_MAIN
#define CC_MUSIC_MAIN

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

enum TaskNumber {
  NO_ARGUMENT,
  INPUT_FILE_ERROR,
  PROCESS_INPUT_FILE
};

TaskNumber handleArguments(int, char**);
void processImage(char*);

#endif

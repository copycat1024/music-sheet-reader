#include "cc_music_io.hh"
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

namespace cc{

bool MusicSheetReaderIO::fileExist(const char* file_name){
  ifstream f(file_name);
  return f.good();
}

bool MusicSheetReaderIO::loadGreyImage(const char* image_name, Mat& image){
  image = imread(image_name, CV_LOAD_IMAGE_GRAYSCALE);
  return image.data;
}

void MusicSheetReaderIO::showImage(string title, Mat pic){
  int dev_null = open("/dev/null", O_RDWR);
  int err_old = dup(STDERR_FILENO);
  dup2(dev_null, STDERR_FILENO);
  namedWindow(title, CV_WINDOW_AUTOSIZE );
  imshow(title, pic);
  dup2(err_old, STDERR_FILENO);
}

void MusicSheetReaderIO::showHold(){
  waitKey();
}

}

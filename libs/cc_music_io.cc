#include <fstream>
#include "cc_music_io.hh"
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

bool fileExist(char* file_name){
  ifstream f(file_name);
  return f.good();
}

Mat loadGreyImage(char* image_name){
  return imread(image_name, CV_LOAD_IMAGE_GRAYSCALE);
}

void showImage(string title, Mat pic){
  int dev_null = open("/dev/null", O_RDWR);
  int err_old = dup(STDERR_FILENO);
  dup2(dev_null, STDERR_FILENO);
  namedWindow(title, CV_WINDOW_AUTOSIZE );
  imshow(title, pic);
  dup2(err_old, STDERR_FILENO);
}

void showHold(){
  waitKey();
}

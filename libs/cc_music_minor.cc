#include <fstream>
#include "cc_music_minor.hh"
#include <unistd.h>
#include <fcntl.h>
#include <string>

using namespace std;
using namespace cv;

bool fileExist(char* file_name){
  ifstream f(file_name);
  return f.good();
}

Mat polarize(Mat image, int threshold){
  Mat res;
  Mat table(1, 256, CV_8U);
  uchar* p = table.data;
  for(int i = 0; i < 256; ++i)
    p[i] = i<threshold ? 255 : 0;
  LUT(image, table, res);
  return res;
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

vector<Vec4i> getSheetLines(Mat image){
  vector<Vec4i> lines;
  Mat temp;

  Mat kernel = (Mat_<float>(3,3) <<  0, -1, 0, 0, 3, 0, 0, -1, 0);
  filter2D(image, temp, image.depth(), kernel);
  image = temp;

  image = polarize(image, 128);
  showImage("Debug", image);

  int threshold = image.cols / 10;
  int minLen = image.cols / 2;
  int maxGap = 10;
  HoughLinesP(image, lines, 1, CV_PI/180, threshold, minLen, maxGap);

  return lines;
}

Mat makeShowImage(Mat image, vector<Vec4i> lines){
  Mat res;
  cvtColor(image, res, CV_GRAY2BGR);
  for( size_t i = 0; i < lines.size(); i++ ){
    Vec4i l = lines[i];
    line(res, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, CV_AA);
//    cout << l[0] << ' ' << l[1] << ' ' << l[2] << ' ' << l[3] << endl;
  }
  return res;
}

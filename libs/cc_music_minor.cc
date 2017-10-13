#include <fstream>
#include "cc_music_minor.hh"
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <iostream>

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

Mat makeShowImage(Mat image, vector<Vec4i> lines, Scalar color){
  Mat res;
  if (image.channels() == 1){
    cvtColor(image, res, CV_GRAY2BGR);
  } else {
    res = image;
  }
  for( size_t i = 0; i < lines.size(); i++ ){
    Vec4i l = lines[i];
    line(res, Point(l[0], l[1]), Point(l[2], l[3]), color, 1, CV_AA);
  }
  return res;
}

#ifdef DEBUG1
void printVec4i(Vec4i l){
  for (int j = 0; j<4; j++){
    cout.width(5);
    cout << l[j];
  }
  cout << endl;
}
#endif

vector<Vec4i> locateFrames(vector<Vec4i> lines){
  vector<Vec4i> mid, res;
  size_t i,j;
  int min_x, max_x, min_y, max_y;

  auto cmp = [](const Vec4i& l, const Vec4i& r){
    return l[1]<r[1];
  };
  sort(lines.begin(), lines.end(), cmp);

  for(i = 0; i<lines.size(); i++){
    if (i==0){
      mid.push_back(lines[i]);
#ifdef DEBUG1
      cout << "IN  "; printVec4i(lines[i]);
#endif
    } else {
      if (lines[i][1]!=lines[i-1][1]+1)
        mid.push_back(lines[i]);
#ifdef DEBUG1
      if (lines[i][1]!=lines[i-1][1]+1){
        cout << "IN  "; printVec4i(lines[i]);
      } else {
        cout << "OUT "; printVec4i(lines[i]);
      }
#endif
    }
  }

  if (mid.size()%5!=0){
    cout << "Number does not match." << endl;
    cout << "Found: " << mid.size() << endl;
    return vector<Vec4i>();
  }

  for (i=0; i<mid.size(); i++)
    if (i%5 == 0){
        min_x = mid[i][0];
        min_y = mid[i][1];
        max_x = mid[i][2];
        max_y = mid[i][3];
    } else {
      if (min_x > mid[i][0]) min_x = mid[i][0];
      if (min_y > mid[i][1]) min_y = mid[i][1];
      if (max_x < mid[i][2]) max_x = mid[i][2];
      if (max_y < mid[i][3]) max_y = mid[i][3];
      if (i%5 == 4){
        res.push_back(Vec4i(min_x, min_y, max_x, max_y));
      }
    }

  return res;
}

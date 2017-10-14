#include "cc_music_edit.hh"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;

void polarize(Mat image, int threshold){
  Mat table(1, 256, CV_8U);
  uchar* p = table.data;
  for(int i = 0; i < 256; ++i)
    p[i] = i<threshold ? 255 : 0;
  LUT(image, table, image);
}

void removeLine(Mat image, Vec4i line){
  int x1 = line[0];
  int y = line[1];
  int x2 = line[2];
  cout << x1 << endl;
  cout << x2 << endl;
  cout << y << endl;
  uchar* top = image.ptr<uchar>(y-1);
  uchar* mid = image.ptr<uchar>(y  );
  uchar* bot = image.ptr<uchar>(y+1);
  for (int i=x1; i<=x2; i++){
    mid[i]= top[i] > bot[i] ? top[i] : bot[i];
  }
}

void drawLines(Mat image, vector<Vec4i> lines, Scalar color){
  for( size_t i = 0; i < lines.size(); i++ ){
    Vec4i l = lines[i];
    line(image, Point(l[0], l[1]), Point(l[2], l[3]), color);
  }
  return;
}

void drawRects(Mat image, vector<Vec4i> lines, Scalar color){
  for( size_t i = 0; i < lines.size(); i++ ){
    Vec4i l = lines[i];
    rectangle(image, Point(l[0], l[1]), Point(l[2], l[3]), color);
  }
  return;
}

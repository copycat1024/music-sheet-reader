#include "cc_music_edit.hh"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

void removeLine(Mat, Vec4i, int);

void polarize(Mat image, int threshold){
  Mat table(1, 256, CV_8U);
  uchar* p = table.data;
  for(int i = 0; i < 256; ++i)
    p[i] = i<threshold ? 255 : 0;
  LUT(image, table, image);
}

void inverse(Mat image){
  Mat table(1, 256, CV_8U);
  uchar* p = table.data;
  for(int i = 0; i < 256; ++i)
    p[i] = 255 - i;
  LUT(image, table, image);
}

void removeLine(Mat image, Vec4i line, int notice){
  int x1 = line[0];
  int y = line[1];
  int x2 = line[2];
  uchar* top = image.ptr<uchar>(y-1);
  uchar* mid = image.ptr<uchar>(y  );
  uchar* bot = image.ptr<uchar>(y+1);
  for (int i=x1; i<=x2; i++){
    if (notice == 0)
      mid[i] = top[i] > bot[i] ? top[i] : bot[i];
    else if (notice == 1)
      mid[i] = top[i];
    else if (notice == 2)
      mid[i] = bot[i];
    else
      mid[i] = 255;
  }
}

void removeAllLines(Mat image, vector<Vec4i> lines){
  int i,n;
  for (i=0; i<lines.size(); i++){
    auto l = lines[i];
    n=0;
    if (i>0)
      if (lines[i][1] == lines[i-1][1]+1) n+=2;
    if (i+1<lines.size())
      if (lines[i][1] == lines[i+1][1]-1) n+=1;
    removeLine(image, l, n);
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
    rectangle(image, Point(l[0] - 1, l[1] - 1), Point(l[2] + 1, l[3] + 1), color);
  }
  return;
}

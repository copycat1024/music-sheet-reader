#include "cc_music_locate.hh"
#include "cc_music_io.hh"
#include "cc_music_edit.hh"
#include "cc_opencv_ultils.hh"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace cc {

void MusicSheetReaderLocator::_locateSheetLines(Mat image){
  vector<Vec4i> lines, mid;
  Mat temp = image;

  cout << "locateSheetLines" << endl;
  int line_min_size = 10;

  int threshold = temp.cols / 10;
  int minLen = temp.cols / 2;
  int maxGap = 10;
  HoughLinesP(temp, lines, 1, CV_PI/2, threshold, minLen, maxGap);

  auto cmp = [](const Vec4i& l, const Vec4i& r){
    return l[1]<r[1];
  };
  sort(lines.begin(), lines.end(), cmp);

  int i,c=0,s=0;
  mid.push_back(lines[0]);
  for(i = 1; i<lines.size(); i++){
    if (lines[i][1]!=lines[i-1][1]+1){
      c++;
      if (c%5 != 0){
        s+=lines[i][1]-lines[i-1][1];
      }
      mid.push_back(lines[i]);
    }
  }
  _gap_size = s/((c+1.)*5./4.);
  _lines = mid;
}

void MusicSheetReaderLocator::_locateFrames(vector<Vec4i> lines){
  vector<Vec4i> mid, res;
  int i;
  int min_x, max_x, min_y, max_y;
  mid = lines;

  if (mid.size()%5!=0){
    cout << "Number does not match." << endl;
    cout << "Found: " << mid.size() << endl;
    _success = false;
    return;
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
        int space = (max_y - min_y)*3/8 + 1;
        res.push_back(Vec4i(min_x, min_y - space, max_x + 1, max_y + space));
      }
    }

  _frames = res;
}

void MusicSheetReaderLocator::locateMusicSheetFrom(Mat image){
  _success = true;
  _binary_image = polarize(image);
  _sheet_lines_image = _binary_image.clone();
  _locateSheetLines(_sheet_lines_image);
  _locateFrames(_lines);
}

cv::Mat MusicSheetReaderLocator::imageSheetLines(){
  return _sheet_lines_image;
}

cv::Mat MusicSheetReaderLocator::imageBinary(){
  return _binary_image;
}

std::vector<cv::Vec4i> MusicSheetReaderLocator::Lines(){
  return _lines;
}

std::vector<cv::Vec4i> MusicSheetReaderLocator::Frames(){
  return _frames;
}

std::vector<cv::Vec4i> MusicSheetReaderLocator::Symbols(){
  return _symbols;
}

bool MusicSheetReaderLocator::Success(){
  return _success;
}

void MusicSheetReaderLocator::locateContours(Mat image){
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  RNG rng(12345);

  findContours(image, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Draw contours
  Mat drawing = Mat::zeros(image.size(), CV_8UC3);
  Mat drawing2 = Mat::zeros(image.size(), CV_8UC3);
  for( int i = 0; i< contours.size(); i++ ){
    Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
    drawContours( drawing2, contours, i, color, 1, 8, hierarchy, 0, Point() );
    int x1,x2,y1,y2;
    x1 = contours[i][0].x;
    x2 = contours[i][0].x;
    y1 = contours[i][0].y;
    y2 = contours[i][0].y;
    for (int j=1; j<contours[i].size(); j++){
      if (x1>contours[i][j].x) x1 = contours[i][j].x;
      if (x2<contours[i][j].x) x2 = contours[i][j].x;
      if (y1>contours[i][j].y) y1 = contours[i][j].y;
      if (y2<contours[i][j].y) y2 = contours[i][j].y;
    }
    rectangle(drawing, Point(x1,y1), Point(x2,y2), color);
//    if (x2-x1<10 && x2-x1>7 && y2-y1>4){
    if (true){
     _symbols.push_back(Vec4i(frame[0]+x1, frame[1]+y1, frame[0]+x2, frame[1]+y2));
      cout << x2-x1 << 'x' << y2-y1 << endl;
    }
  }

  /// Show in a window
  namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
  namedWindow( "Contours2", CV_WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );
  imshow( "Contours2", drawing2 );
  imshow("Ori", image);
  waitKey();

}

float urg(Mat);
float urg2(Mat);

void MusicSheetReaderLocator::locateSymbols2(Mat image){
  cout << "Lots" << endl;
  Mat templ, res, p;
  templ = imread("N2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
  matchTemplate(image, templ, p, TM_CCOEFF_NORMED);
  normalize(p, p, 0, 100, NORM_MINMAX, -1, Mat() );
  Mat k;
  p.convertTo(k, CV_8UC1);
  threshold(k, res, 80, 255, 0);

  cout << depthToStr(p) << endl;
  cout << depthToStr(res) << endl;
  imshow("Res", res);
  imshow("p", k);
  return;
}

}

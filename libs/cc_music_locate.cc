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

/*
vector<Vec4i> locateFrameLines(Mat input_image, Vec4i frame){
  vector<Vec4i> lines, res;
  int x1 = frame[0];
  int y1 = frame[1];
  int x2 = frame[2];
  int y2 = frame[3];
  Mat image = input_image.clone();
  image = image(Rect(x1, y1, x2-x1, y2-y1));

  image = polarize(image);

  int threshold = image.rows / 4;
  int minLen = image.rows / 4;
  int maxGap = 10;
  HoughLinesP(image, lines, 1, CV_PI/180, threshold, minLen, maxGap);

  auto cmp = [](const Vec4i& l, const Vec4i& r){
    return l[1]<r[1];
  };
  sort(lines.begin(), lines.end(), cmp);

  for (auto ll : lines){
    ll[0] += x1;
    ll[1] += y1;
    ll[2] += x1;
    ll[3] += y1;
    res.push_back(ll);
  }
  return res;
}

vector<Vec4i> locateSymbols(Mat input_image, Vec4i frame){
  vector<Vec4i> res, resx;
  vector<int> weight;
  Mat image = input_image;
  int i,j;
  int x1 = frame[0];
  int y1 = frame[1];
  int x2 = frame[2];
  int y2 = frame[3];

  weight.resize(x2 - x1 + 1, 0);
  for (i=y1; i<=y2; i++){
    uchar* row = image.ptr<uchar>(i);
    for (j=x1; j<=x2; j++){
      if (row[j] == 255) weight[j-x1]++;
    }
  }

  bool streak = false;
  int xa = 0;
  for (j=x1; j<=x2; j++){
    int a = weight[j-x1];
    if (a != 0 && !streak){
      xa = j;
      streak = true;
    }
    if (a == 0 && streak){
      streak = false;
      resx.push_back(Vec4i(xa, y1, j, y2));
    }
  }
  for (Vec4i v : resx){
    vector<Vec4i> r = locateSymbolsX(image, v);
    res.insert(res.end(), r.begin(), r.end());
  }
  return res;
}

vector<Vec4i> locateSymbolsX(Mat image, Vec4i frame){
  vector<Vec4i> res;
  vector<int> weight;
  int i,j;
  int x1 = frame[0];
  int y1 = frame[1];
  int x2 = frame[2];
  int y2 = frame[3];

  weight.resize(y2 - y1 + 1, 0);
  for (i=y1; i<=y2; i++){
    uchar* row = image.ptr<uchar>(i);
    for (j=x1; j<=x2; j++){
      if (row[j] == 255) weight[i-y1]++;
    }
  }

  bool streak = false;
  int ya = 0;
  for (j=y1; j<=y2; j++){
    int a = weight[j-y1];
    if (a != 0 && !streak){
      ya = j;
      streak = true;
    }
    if (a == 0 && streak){
      streak = false;
      res.push_back(Vec4i(x1, ya, x2, j));
    }
  }
  return res;
}
*/

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

void MusicSheetReaderLocator::locateSymbols(Vec4i frame){
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  RNG rng(12345);
  Mat image = _binary_image(Rect(frame[0], frame[1], frame[2]-frame[0], frame[3]-frame[1]));

  applyMorphFilter2(image,3);

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
  templ = imread("N1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
  matchTemplate(image, templ, p, TM_CCOEFF_NORMED);
  normalize(p, p, 0, 1, NORM_MINMAX, -1, Mat() );
  p = p*256;
  Mat k;
  p.convertTo(k, CV_8UC1);
  threshold(k, res, 32*7, 255, 0);

  cout << urg(res) << endl;
  cout << urg2(res) << endl;
  cout << depthToStr(p) << endl;
  cout << depthToStr(res) << endl;
  imshow("Res", res);
  imshow("p", k);
  return;
}

}
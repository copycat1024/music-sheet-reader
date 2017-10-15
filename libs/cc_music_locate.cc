#include "cc_music_locate.hh"
#include "cc_music_io.hh"
#include "cc_music_edit.hh"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

vector<Vec4i> locateSymbolsX(Mat, Vec4i);

vector<Vec4i> locateSheetLines(Mat image){
  vector<Vec4i> lines;
  Mat temp;

  int line_min_size = temp.cols / 10;
  applyMorphFilter(temp, line_min_size, 1);
  showImage(temp);

  int threshold = temp.cols / 10;
  int minLen = temp.cols / 2;
  int maxGap = 10;
  HoughLinesP(temp, lines, 1, CV_PI/180, threshold, minLen, maxGap);

  auto cmp = [](const Vec4i& l, const Vec4i& r){
    return l[1]<r[1];
  };
  sort(lines.begin(), lines.end(), cmp);

  return lines;
}

vector<Vec4i> locateFrames(vector<Vec4i> lines){
  vector<Vec4i> mid, res;
  size_t i,j;
  int min_x, max_x, min_y, max_y;

  for(i = 0; i<lines.size(); i++){
    if (i==0){
      mid.push_back(lines[i]);
    } else {
      if (lines[i][1]!=lines[i-1][1]+1)
        mid.push_back(lines[i]);
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
        int space = (max_y - min_y)*3/8 + 1;
        res.push_back(Vec4i(min_x, min_y - space, max_x + 1, max_y + space));
      }
    }

  return res;
}

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
  Mat image = input_image.clone(), temp;
  int i,j;
  int x1 = frame[0];
  int y1 = frame[1];
  int x2 = frame[2];
  int y2 = frame[3];

  Mat kernel = (Mat_<float>(3,3) <<  0, 0, 0, -1, 3, -1, 0, 0, 0);
  filter2D(image, temp, image.depth(), kernel);
  image = temp;

  image = polarize(image);
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
    cout << a << endl;
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

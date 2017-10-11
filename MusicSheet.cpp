#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace cv;
using namespace std;

string depthToStr(const Mat&);
string typeToStr(const Mat&);


int main( int argc, char** argv ){
  cout << "Music Sheet Reader alpha" << endl;
  char* imageName = argv[1];

  freopen("/dev/null", "w", stderr);

  Mat A;
  Mat B;
  Mat C;
  Mat D;
  Mat E;
  Mat F;

  A = imread( imageName, 1);

  if( argc != 2 || !A.data ){
    cout << "No image data!" << endl;
    return 0;
  }

  cvtColor(A,C,CV_BGR2GRAY);
  cout << imageName << endl;
  cout << "C.depth() = " << depthToStr(C) << endl;


  Mat kern = (Mat_<float>(3,3) <<  0, -1, 0, 0, 3, 0, 0, -1, 0);
  filter2D(C, E, C.depth(), kern);

  Mat T(1, 256, CV_8U);
  uchar* p = T.data;
  for(int i = 0; i < 256; ++i)
    p[i] = i<128 ? 255 : 0;
  LUT(E, T, F);

  cvtColor(F, B, CV_GRAY2BGR);

  vector<Vec4i> lines;
  int threshold = F.cols / 10;
  int minLen = F.cols / 2;
  int maxGap = 10;
  HoughLinesP(F, lines, 1, CV_PI/180, threshold, minLen, maxGap);
  cout << "Found " << lines.size() << " lines."<< endl;

  auto cmp = [](const Vec4i& l, const Vec4i& r){
    return l[1]>r[1];
  };
  sort(lines.begin(), lines.end(), cmp);

  for( size_t i = 0; i < lines.size(); i++ ){
    Vec4i l = lines[i];
    line(B, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, CV_AA);
//    cout << l[0] << ' ' << l[1] << ' ' << l[2] << ' ' << l[3] << endl;
  }

//  imwrite( "new_image.jpg", B );

  namedWindow( imageName, CV_WINDOW_AUTOSIZE );
  namedWindow( "Reduced color image", CV_WINDOW_AUTOSIZE );
  imshow( imageName, E);
  imshow( "Reduced color image", B);
  waitKey(0);

  return 0;
}

string depthToStr(const Mat& mat)
{
    const int depth = mat.depth();

    switch (depth)
    {
    case CV_8U:  return "CV_8U";
    case CV_8S:  return "CV_8S";
    case CV_16U: return "CV_16U";
    case CV_16S: return "CV_16S";
    case CV_32S: return "CV_32S";
    case CV_32F: return "CV_32F";
    case CV_64F: return "CV_64F";
    default:
        return "Invalid depth type of matrix!";
    }
}

string typeToStr(const Mat& mat)
{
    const int mtype = mat.type();

    switch (mtype)
    {
    case CV_8UC1:  return "CV_8UC1";
    case CV_8UC2:  return "CV_8UC2";
    case CV_8UC3:  return "CV_8UC3";
    case CV_8UC4:  return "CV_8UC4";

    case CV_8SC1:  return "CV_8SC1";
    case CV_8SC2:  return "CV_8SC2";
    case CV_8SC3:  return "CV_8SC3";
    case CV_8SC4:  return "CV_8SC4";

    case CV_16UC1: return "CV_16UC1";
    case CV_16UC2: return "CV_16UC2";
    case CV_16UC3: return "CV_16UC3";
    case CV_16UC4: return "CV_16UC4";

    case CV_16SC1: return "CV_16SC1";
    case CV_16SC2: return "CV_16SC2";
    case CV_16SC3: return "CV_16SC3";
    case CV_16SC4: return "CV_16SC4";

    case CV_32SC1: return "CV_32SC1";
    case CV_32SC2: return "CV_32SC2";
    case CV_32SC3: return "CV_32SC3";
    case CV_32SC4: return "CV_32SC4";

    case CV_32FC1: return "CV_32FC1";
    case CV_32FC2: return "CV_32FC2";
    case CV_32FC3: return "CV_32FC3";
    case CV_32FC4: return "CV_32FC4";

    case CV_64FC1: return "CV_64FC1";
    case CV_64FC2: return "CV_64FC2";
    case CV_64FC3: return "CV_64FC3";
    case CV_64FC4: return "CV_64FC4";

    default:
        return "Invalid type of matrix!";
    }
}

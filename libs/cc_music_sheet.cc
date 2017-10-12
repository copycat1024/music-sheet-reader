#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
#include "cc_music_sheet.hh"
#include "cc_opencv_ultils.hh"

using namespace std;
using namespace cv;

TaskNumber handleArguments(int argc, char** argv){
  if (argc < 2) return NO_ARGUMENT;
  if (!fileExist(argv[1])) return INPUT_FILE_ERROR;
  return PROCESS_INPUT_FILE;
}

bool fileExist(char* file_name){
  ifstream f(file_name);
  return f.good();
}

void processImage(char* image_name){
  char* imageName = image_name;
  cout << "Music Sheet Reader alpha" << endl;

//  freopen("/dev/null", "w", stderr);

  Mat A;
  Mat B;
  Mat C;
  Mat D;
  Mat E;
  Mat F;

  A = imread(imageName, CV_LOAD_IMAGE_GRAYSCALE);

  if( !A.data ){
    cout << "No image data!" << endl;
    return;
  }
  C = A;

//  cvtColor(A,C,CV_BGR2GRAY);
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
}

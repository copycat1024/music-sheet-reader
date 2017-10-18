#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "cc_music_main.hh"
#include "cc_music_io.hh"
#include "cc_music_locate.hh"
#include "cc_music_edit.hh"
#include "cc_opencv_ultils.hh"

using namespace std;
using namespace cv;

namespace cc {

TaskNumber MusicSheetReaderProgram::handleArguments(int argc, char** argv){
  MusicSheetReaderIO io;
  if (argc < 2) return NO_ARGUMENT;
  if (!io.fileExist(argv[1])) return INPUT_FILE_ERROR;
  return PROCESS_INPUT_FILE;
}

void MusicSheetReaderProgram::processImage(char* image_name){
  MusicSheetReaderIO io;
  MusicSheetReaderLocator loc;

  Mat input_image;
  Mat binary_image;
  Mat show_image;
  Mat sheet_lines_image;
  Mat symbols_image;

  if(!io.loadGreyImage(image_name, input_image)){
    cout << "No image data!" << endl;
    return;
  }
  io.showImage("Input", input_image);

  binary_image = polarize(input_image);
  io.showImage("Binary threshold", binary_image);

  loc.locateMusicSheetFrom(binary_image);
  sheet_lines_image = loc.imageSheetLines();
  auto lines = loc.Lines();
  cout << "Found " << lines.size() << " lines." << endl;
  io.showImage("Sheet lines", sheet_lines_image);

  auto frames = loc.Frames();
  cout << "Found " << frames.size() << " frames." << endl;
  if (!loc.Success()){
    io.showHold();
    return;
  }

  loc.locateSymbols(binary_image, frames[0]);
  auto symbols = loc.Symbols();
//  symbols_image = binary_image.clone();
//  auto symbols = locateSymbols(symbols_image, frames[0]);
//  io.showImage("A", A);

  cvtColor(input_image, show_image, CV_GRAY2BGR);
  drawRects(show_image, frames, Scalar(0,255,0));
  drawRects(show_image, symbols, Scalar(255,0,255));
  io.showImage("Result", show_image);

  io.showHold();


  return;
}

}
// --------------------- end of namespace
/*
void processImage1(char* image_name){
  Mat image = loadGreyImage(image_name);

  if( !image.data ){
    cout << "No image data!" << endl;
    return;
  }

  imshow("gray", image);
  // Apply adaptiveThreshold at the bitwise_not of gray, notice the ~ symbol
  Mat bw = polarize(image);
  // Show binary image
  imshow("binary", bw);
  waitKey(0);

  // Create the images that will use to extract the horizontal and vertical lines
  Mat horizontal = bw.clone();
  Mat vertical = bw.clone();
  // Specify size on horizontal axis
  int horizontalsize = horizontal.cols / 10;
  // Create structure element for extracting horizontal lines through morphology operations
  Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontalsize,1));
  // Apply morphology operations
  erode(horizontal, horizontal, horizontalStructure, Point(-1, -1));
  imshow("horizontal1", horizontal);

  dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1));
  // Show extracted horizontal lines
  imshow("horizontal", horizontal);
  waitKey(0);

  // Specify size on vertical axis
  int verticalsize = vertical.rows / 3;
  // Create structure element for extracting vertical lines through morphology operations
  Mat verticalStructure = getStructuringElement(MORPH_RECT, Size( 1,verticalsize));
  // Apply morphology operations
  erode(vertical, vertical, verticalStructure, Point(-1, -1));
  dilate(vertical, vertical, verticalStructure, Point(-1, -1));
  // Show extracted vertical lines
  imshow("vertical", vertical);
  // Inverse vertical image
  bitwise_not(vertical, vertical);
  imshow("vertical_bit", vertical);
  // Extract edges and smooth image according to the logic
  // 1. extract edges
  // 2. dilate(edges)
  // 3. src.copyTo(smooth)
  // 4. blur smooth img
  // 5. smooth.copyTo(src, edges)
  // Step 1
  Mat edges;
  adaptiveThreshold(vertical, edges, 255, CV_ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, -2);
  imshow("edges", edges);
  // Step 2
  Mat kernel = Mat::ones(2, 2, CV_8UC1);
  dilate(edges, edges, kernel);
  imshow("dilate", edges);
  // Step 3
  Mat smooth;
  vertical.copyTo(smooth);
  // Step 4
  blur(smooth, smooth, Size(2, 2));
  // Step 5
  smooth.copyTo(vertical, edges);
  // Show final result
  imshow("smooth", vertical);
  waitKey(0);
  return;
}
*/

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

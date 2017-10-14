#include <iostream>
#include "cc_music_main.hh"
#include "cc_music_io.hh"
#include "cc_music_locate.hh"
#include "cc_music_edit.hh"
#include "cc_opencv_ultils.hh"

using namespace std;
using namespace cv;

TaskNumber handleArguments(int argc, char** argv){
  if (argc < 2) return NO_ARGUMENT;
  if (!fileExist(argv[1])) return INPUT_FILE_ERROR;
  return PROCESS_INPUT_FILE;
}

void processImage(char* image_name){
  cout << "Music Sheet Reader alpha" << endl;

  Mat image;
  Mat show_image;

  image = loadGreyImage(image_name);

  if( !image.data ){
    cout << "No image data!" << endl;
    return;
  }

  auto lines = locateSheetLines(image);
  cout << "Found " << lines.size() << " lines." << endl;
  auto frames = locateFrames(lines);
  cout << "Found " << frames.size() << " frames." << endl;

  showImage("Original", image);

  auto temp = image.clone();

  for (auto l : lines)
    removeLine(temp, l);

  polarize(temp, 128);
  cvtColor(temp, show_image, CV_GRAY2BGR);

  drawRects(show_image, frames, Scalar(0,255,0));
  showImage("Frames", show_image);

  auto n = locateSymbols(temp, frames[0]);
  cout << "Found " << n.size() << " symbols." << endl;
  drawRects(show_image, n, Scalar(0,0,255));
  showImage("Symbol", show_image);

  showHold();

}

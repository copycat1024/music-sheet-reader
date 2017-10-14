#include <iostream>
#include "cc_music_main.hh"
#include "cc_music_minor.hh"
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

  cvtColor(image, show_image, CV_GRAY2BGR);

  drawLines(show_image, lines, Scalar(0,0,255));
  showImage("Process1", show_image);

  drawLines(show_image, frames, Scalar(0,255,0));
  showImage("Process2", show_image);

  auto f = frames[0];
  auto crop = image(Rect(f[0], f[1], f[2]-f[0], f[3]-f[1]));
  showImage("Crop", crop);

  showHold();
}

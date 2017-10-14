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

  for (auto l : lines)
    removeLine(image, l);


  cvtColor(image, show_image, CV_GRAY2BGR);

  drawRects(show_image, frames, Scalar(0,255,0));
  showImage("Frames", show_image);

  auto f = frames[0];
  auto crop = image(Rect(f[0], f[1], f[2]-f[0], f[3]-f[1]));
  showImage("Crop", crop);

  showHold();
}

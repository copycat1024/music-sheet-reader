#include "cc_music_lines.hh"
#include "cc_music_transform.hh"
#include "cc_opencv_ultils.hh"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace cc {

void MusicSheetReaderLinesLocator::locateLinesFrom(Mat image, vector<Vec4i> frames){
	//
	cout << frames.size() << endl;
}

}

#include <iostream>
#include <iomanip>
#include <opencv/cv.hpp>
#include "cc_music_debug.hh"
#include "cc_music_locate.hh"
#include "cc_opencv_ultils.hh"

using namespace std;
using namespace cv;

namespace cc{

void Debugger::debug(Locator& loc, Error e){
	cout << "Debug started." << endl;
	if (e == Error::StavesFail){
		cout << "Staves locator failed." << endl;
		auto stv = loc._staves;

		cout << "Hough lines: " << endl;
		for (auto l : stv.hough_lines){
			cout << " " << setw(6) << l[0];
			cout << " " << setw(6) << l[1];
			cout << " " << setw(6) << l[2];
			cout << " " << setw(6) << l[3];
			cout << endl;
		}

		Mat show_image;
		cvtColor(loc._binary_image, show_image, CV_GRAY2BGR);
		drawLines(show_image, stv.hough_lines, Scalar(255, 0, 0));
		imwrite("debug/hough.jpg", show_image);

//		Mat show_image;
//		cvtColor(loc._binary_image, show_image, CV_GRAY2BGR);
//		drawLines(show_image, stv.hough_lines, Scalar(255, 0, 0));
		imwrite("debug/line.jpg", stv.lines_image);

	}
}

}

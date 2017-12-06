#include <iostream>
#include <iomanip>
#include <opencv/cv.hpp>
#include "opencv_utils.hh"
#include "music_debug.hh"
#include "music_locate.hh"
#include "music_error.hh"

using namespace std;
using namespace cv;

namespace cc{

void Debugger::debug(Locator& loc, Error e){
	cout << "Locator loc failed. Debug started." << endl;
	if (e == Error::StavesFail){
		cout << "Failure: Staves locator" << endl;
		auto stv = loc._staves;

		cout << "Hough lines: " << endl;
		for (auto l : stv.hough_lines){
			cout << " " << setw(6) << l[0];
			cout << " " << setw(6) << l[1];
			cout << " " << setw(6) << l[2];
			cout << " " << setw(6) << l[3];
			cout << endl;
		}

		cout << "Staves: " << endl;
		for (auto l : stv.staves){
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

		imwrite("debug/line.jpg", stv.lines_image);

	} else if (e == Error::SymbolsFail){
		auto sym = loc._sym;
		cout << "s " << sym.result.size() << endl;

		Mat show_image;
		cvtColor(loc._binary_image, show_image, CV_GRAY2BGR);

		drawRects(show_image, sym.result, Scalar(255,0,255));

		imwrite("debug/sym.jpg", show_image);
	}
}

}

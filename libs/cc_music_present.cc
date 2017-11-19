#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include "cc_music_present.hh"
#include "cc_music_io.hh"

using namespace cv;
using namespace std;

namespace cc {

vector<Mat> splitFrames(Mat src, vector<Vec4i> frames){
	vector<Mat> res;
	for (auto v: frames){
		auto f = src(Rect(v[0], v[1], v[2] - v[0], v[3] - v[1]));
		res.push_back(f);
	}
	return res;
}

void MusicSheetReaderPresenter::presentResults(MusicSheetReaderLocator loc){
	Mat show_image;

	cvtColor(_input_image, show_image, CV_GRAY2BGR);
	_drawRects(show_image, loc.Frames(), Scalar(0,255,0));
	_drawLines(show_image, loc.Lines(), Scalar(255,0,255));
	showImage("Result", show_image);

	auto frames = loc.Frames();
	cout << "Found " << frames.size() << " frames." << endl;
	auto lines = loc.Lines();
	cout << "Found " << lines.size() << " lines." << endl;
}

void MusicSheetReaderPresenter::presentInput(Mat input_image){
	_input_image = input_image;
	showImage("Input", input_image);
}

void MusicSheetReaderPresenter::presentHold(){
	showHold();
}

void MusicSheetReaderPresenter::_drawLines(Mat image, vector<Vec4i> lines, Scalar color){
	for( std::size_t i = 0; i < lines.size(); i++ ){
		Vec4i l = lines[i];
		line(image, Point(l[0], l[1]), Point(l[2], l[3]), color);
	}
}

void MusicSheetReaderPresenter::_drawRects(Mat image, vector<Vec4i> lines, Scalar color){
	for( std::size_t i = 0; i < lines.size(); i++ ){
		Vec4i l = lines[i];
		rectangle(image, Point(l[0] - 1, l[1] - 1), Point(l[2] + 1, l[3] + 1), color);
	}
}

}

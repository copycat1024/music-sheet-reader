#include "cc_music_present.hh"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

namespace cc {

void drawLines(Mat image, vector<Vec4i> lines, Scalar color){
	for( std::size_t i = 0; i < lines.size(); i++ ){
		Vec4i l = lines[i];
		line(image, Point(l[0], l[1]), Point(l[2], l[3]), color);
	}
}

void drawRects(Mat image, vector<Vec4i> lines, Scalar color){
	for( std::size_t i = 0; i < lines.size(); i++ ){
		Vec4i l = lines[i];
		rectangle(image, Point(l[0] - 1, l[1] - 1), Point(l[2] + 1, l[3] + 1), color);
	}
}

vector<Mat> splitFrames(Mat src, vector<Vec4i> frames){
	vector<Mat> res;
	for (auto v: frames){
		auto f = src(Rect(v[0], v[1], v[2] - v[0], v[3] - v[1]));
		res.push_back(f);
	}
	return res;
}

}

#include "cc_music_locate.hh"
#include "cc_music_io.hh"
#include "cc_music_edit.hh"
#include "cc_opencv_ultils.hh"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace cc {

bool MusicSheetReaderFramesLocator::Success(){
	return _success;
}

std::vector<cv::Vec4i> MusicSheetReaderFramesLocator::Lines(){
	return _lines;
}

std::vector<cv::Vec4i> MusicSheetReaderFramesLocator::Frames(){
	return _frames;
}

void MusicSheetReaderFramesLocator::locateFramesFrom(Mat binary_image){

	// Initialize success status
	// This flag will be set to false by the following co-routine
	_success = true;

	// _locateSheetLines apply Morph to make sheet lines image
	_sheet_lines_image = binary_image.clone();
	_locateSheetLines(_sheet_lines_image);

	// locate frames from list of sheet lines
	_locateFrames(_lines);

}

void MusicSheetReaderFramesLocator::_locateSheetLines(Mat image){
	vector<Vec4i> lines, mid;
	Mat temp = image;

	cout << "locateSheetLines" << endl;
	int line_min_size = 10;

	int threshold = temp.cols / 10;
	int minLen = temp.cols / 2;
	int maxGap = 10;
	HoughLinesP(temp, lines, 1, CV_PI/2, threshold, minLen, maxGap);

	auto cmp = [](const Vec4i& l, const Vec4i& r){
		return l[1]<r[1];
	};
	sort(lines.begin(), lines.end(), cmp);

	int i,c=0,s=0;
	mid.push_back(lines[0]);
	for(i = 1; i<lines.size(); i++){
		if (lines[i][1]!=lines[i-1][1]+1){
			c++;
			if (c%5 != 0){
				s+=lines[i][1]-lines[i-1][1];
			}
			mid.push_back(lines[i]);
		}
	}

	// Results
	_gap_size = s/((c+1.)*5./4.);
	_lines = mid;
}

void MusicSheetReaderFramesLocator::_locateFrames(vector<Vec4i> lines){
	vector<Vec4i> mid, res;
	int i;
	int min_x, max_x, min_y, max_y;
	mid = lines;

	if (mid.size()%5!=0){
		cout << "Number does not match." << endl;
		cout << "Found: " << mid.size() << endl;
		_success = false;
		return;
	}

	for (i=0; i<mid.size(); i++)
		if (i%5 == 0){
				min_x = mid[i][0];
				min_y = mid[i][1];
				max_x = mid[i][2];
				max_y = mid[i][3];
		} else {
			if (min_x > mid[i][0]) min_x = mid[i][0];
			if (min_y > mid[i][1]) min_y = mid[i][1];
			if (max_x < mid[i][2]) max_x = mid[i][2];
			if (max_y < mid[i][3]) max_y = mid[i][3];
			if (i%5 == 4){
				int space = (max_y - min_y)*3/8 + 1;
				res.push_back(Vec4i(min_x, min_y - space, max_x + 1, max_y + space));
			}
		}

	// Results
	_frames = res;
}

}

#include "cc_music_locate.hh"
#include "cc_music_io.hh"
#include "cc_music_transform.hh"
#include "cc_opencv_ultils.hh"
#include "cc_music_frames.hh"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace cc {

// Interfaces
cv::Mat MusicSheetReaderLocator::imageBinary(){
	return _binary_image;
}

std::vector<cv::Vec4i> MusicSheetReaderLocator::Lines(){
	return _frames.Lines();
}

std::vector<cv::Vec4i> MusicSheetReaderLocator::Frames(){
	return _frames.Frames();
}

std::vector<cv::Vec4i> MusicSheetReaderLocator::Symbols(){
	return _symbols;
}

bool MusicSheetReaderLocator::Success(){
	return _success;
}

// Heavy-lifting code

void MusicSheetReaderLocator::locateMusicSheetFrom(Mat image){

	// Convert greyscale image to binary image by adaptive threshold
	_binary_image = polarize(image);

	// Locate frames from binary image
	_success = 	_frames.locateFramesFrom(_binary_image);

	if (_success)
		_lines.locateLinesFrom(image, _frames.Frames());
}

void MusicSheetReaderLocator::locateSymbols(Vec4i frame){
	Mat image = _binary_image(Rect(frame[0], frame[1], frame[2] - frame[0], frame[3] - frame[1]));
	image = applyMorphFilter(image, 3);
	_locateContours(frame, image);
}

void MusicSheetReaderLocator::_locateContours(Vec4i frame, Mat image){
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	RNG rng(12345);

	
	findContours(image, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Draw contours
	Mat drawing = Mat::zeros(image.size(), CV_8UC3);
	Mat drawing2 = Mat::zeros(image.size(), CV_8UC3);
	for( int i = 0; i< contours.size(); i++ ){
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours( drawing2, contours, i, color, 1, 8, hierarchy, 0, Point() );
		int x1,x2,y1,y2;
		x1 = contours[i][0].x;
		x2 = contours[i][0].x;
		y1 = contours[i][0].y;
		y2 = contours[i][0].y;
		for (int j=1; j<contours[i].size(); j++){
			if (x1>contours[i][j].x) x1 = contours[i][j].x;
			if (x2<contours[i][j].x) x2 = contours[i][j].x;
			if (y1>contours[i][j].y) y1 = contours[i][j].y;
			if (y2<contours[i][j].y) y2 = contours[i][j].y;
		}
		rectangle(drawing, Point(x1,y1), Point(x2,y2), color);
		if (x2-x1<10 && x2-x1>7 && y2-y1>4){
			_symbols.push_back(Vec4i(frame[0]+x1, frame[1]+y1, frame[0]+x2, frame[1]+y2));
			cout << x2-x1 << 'x' << y2-y1 << endl;
		}
	}

	/// Show in a window
	namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
	namedWindow( "Contours2", CV_WINDOW_AUTOSIZE );
	imshow( "Contours", drawing );
	imshow( "Contours2", drawing2 );
	imshow("Ori", image);
	waitKey();


}

void MusicSheetReaderLocator::locateSymbols2(Mat image){
	cout << "Lots" << endl;
	Mat pattern, result, result_f;
	pattern = imread("N4.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	matchTemplate(image, pattern, result_f, CV_TM_CCOEFF);
	normalize(result_f, result_f, 0, 255, NORM_MINMAX, -1, Mat() );
	result_f.convertTo(result, CV_8UC1);
	threshold(result, result, 64*2, 255, 0);

/*
	int i,j;
	for (i=0; i<result.rows; i++)
		for (j=0; j<result.cols; j++)
			if (result.at<uchar>(i,j)>0)
				cout << result_f.at<float>(i,j) << endl;
*/
	imshow("p", result);
	return;
}

}

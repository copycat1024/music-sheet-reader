/* CC Music Reader Locator code
 *
 * Contain the object used to locate the elements of the music sheet.
 *
 * Status:
 *  Open:   0
 *  Legacy:
 *  Locked: 
 *
 */

#include "cc_music_locate.hh"
#include "cc_music_io.hh"
#include "cc_music_transform.hh"
#include "cc_opencv_ultils.hh"
#include "locate/cc_music_staves.hh"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace cc {

// Interfaces

// Status: Locked
cv::Mat MusicSheetReaderLocator::imageBinary(){
	return _binary_image;
}

// Status: Locked
std::vector<cv::Vec4i> MusicSheetReaderLocator::Lines(){
	return _lines.Lines();
}

// Status: Locked
std::vector<cv::Vec4i> MusicSheetReaderLocator::Staves(){
	return _staves.Staves();
}

// Status: Legacy
std::vector<cv::Vec4i> MusicSheetReaderLocator::Symbols(){
	return _symbols;
}

// Heavy-lifting code

// Status: Locked
bool MusicSheetReaderLocator::locateMusicSheetFrom(Mat image){

	// Convert greyscale image to binary image by adaptive threshold
	_binary_image = polarize(image);

	// Locate staves from binary image
	if (!_staves.locateStavesFrom(_binary_image)){
		cout << "Locate staves failed." << endl;
		return false;
	}

	// Locate lines from greyscale image
	if (!_lines.locateLinesFrom(image, _staves.Staves())){
		cout << "Locate lines failed." << endl;
		return false;
	}

	return true;
}

// Status: Legacy
void MusicSheetReaderLocator::locateSymbols(Vec4i stave){
	Mat image = _binary_image(Rect(stave[0], stave[1], stave[2] - stave[0], stave[3] - stave[1]));
	image = applyMorphFilter(image, 3);
	_locateContours(stave, image);
}

// Status: Legacy
void MusicSheetReaderLocator::_locateContours(Vec4i stave, Mat image){
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
			_symbols.push_back(Vec4i(stave[0]+x1, stave[1]+y1, stave[0]+x2, stave[1]+y2));
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

// Status: Legacy
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

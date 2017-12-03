/* CC Music Reader Transform code
 *
 * Contain the functions that transform Mat images.
 *
 * Status:
 *  Locked: 3
 *  Legacy: 3
 *
 */

#include "music_transform.hh"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

namespace cc {

// Status: Locked
Mat applyMorphFilter(Mat binary_image, int x, int y){
	Mat morphStructure = getStructuringElement(MORPH_RECT, Size(x,y));
	Mat r = binary_image.clone();
	erode(r, r, morphStructure, Point(-1, -1));
	dilate(r, r, morphStructure, Point(-1, -1));
	return r;
}

// Status: Locked
Mat applyMorphFilter(Mat binary_image, int x){
	return applyMorphFilter(binary_image, x, x);
}

// Status: Locked
Mat polarize(Mat image){
	Mat res;
	int mask_size = (image.cols/100)*2 + 1;
	adaptiveThreshold(~image, res, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, mask_size, -2);
	return res;
}

// Status: Legacy
void inverse(Mat image){
	Mat table(1, 256, CV_8U);
	uchar* p = table.data;
	for(int i = 0; i < 256; ++i)
		p[i] = 255 - i;
	LUT(image, table, image);
}

// Status: Legacy
void removeLine(Mat image, Vec4i line, int notice){
	int x1 = line[0];
	int y = line[1];
	int x2 = line[2];
	uchar* top = image.ptr<uchar>(y-1);
	uchar* mid = image.ptr<uchar>(y  );
	uchar* bot = image.ptr<uchar>(y+1);
	for (int i=x1; i<=x2; i++){
		if (notice == 0)
			mid[i] = top[i] > bot[i] ? top[i] : bot[i];
		else if (notice == 1)
			mid[i] = top[i];
		else if (notice == 2)
			mid[i] = bot[i];
		else
			mid[i] = 255;
	}
}

// Status: Legacy
void removeAllLines(Mat image, vector<Vec4i> lines){
	int i,n;
	for (i=0; i<lines.size(); i++){
		auto l = lines[i];
		n=0;
		if (i>0)
			if (lines[i][1] == lines[i-1][1]+1) n+=2;
		if (i+1<lines.size())
			if (lines[i][1] == lines[i+1][1]-1) n+=1;
		removeLine(image, l, n);
	}
}

}
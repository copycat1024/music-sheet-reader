#include "cc_music_transform.hh"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

namespace cc {

void removeLine(Mat, Vec4i, int);

Mat polarize(Mat image){
	Mat res;
	adaptiveThreshold(~image, res, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, -2);
	return res;
}

Mat applyMorphFilter(Mat binary_image, int x, int y){
	Mat morphStructure = getStructuringElement(MORPH_RECT, Size(x,y));
	Mat a, r;
	dilate(binary_image, a, morphStructure, Point(-1, -1));
	erode(a, r, morphStructure, Point(-1, -1));
	return r;
}

Mat applyMorphFilter(Mat binary_image, int x){
	return applyMorphFilter(binary_image, x, x);
}

void inverse(Mat image){
	Mat table(1, 256, CV_8U);
	uchar* p = table.data;
	for(int i = 0; i < 256; ++i)
		p[i] = 255 - i;
	LUT(image, table, image);
}

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

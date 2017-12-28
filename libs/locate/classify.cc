/* CC Music Reader symbols classifier header
 *
 * Contain the object for classifying symbols from contours locating.
 *
 */

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "opencv_utils.hh"
#include "classify.hh"
#include "music_error.hh"

#define HORIZONTAL 0
#define VERTICAL 1

using namespace std;
using namespace cv;

// Private function

// reduce and scale
Mat rns(Mat crop, int dim, int size){
	Mat res, rdc, rsz;
	if (dim == HORIZONTAL){
		reduce(crop, rdc, dim, CV_REDUCE_AVG);
		resize(rdc, rsz, Size(size, 1));
	} else if (dim == VERTICAL){
		reduce(crop, rdc, dim, CV_REDUCE_AVG);
		resize(rdc, rsz, Size(1, size));
	}
	rsz.convertTo(res, CV_16S);
	return res;
}

int compare(Mat a, Mat b){
	Mat d = a - b;
	int s=0, m, i, j;
	for(i=0; i<d.rows; ++i)
		for(j=0; j<d.cols; ++j){
			m = d.at<short>(i,j);
			s += m*m/(d.rows*d.cols);
		}
	return s;
}

// Objects method

namespace cc{

void SymbolsClassifier::locateFrom(const std::vector<cv::Mat>& crops){
	for (Mat c : crops){
		_h.push_back(rns(c, HORIZONTAL, 4));
		_v.push_back(rns(c, VERTICAL, 10));
	}

	int i, j;
	int c = _compare(0, 1);
	int min = c, max = c;
	int max_diff = 401;

	for (i=0; i<crops.size(); ++i){
		bool fl = true;
		for (auto& v : result){
			if (_compare(i, v[0]) < max_diff){
				v.push_back(i);
				fl = false;
			}
		}
		if (fl){
			vector<int> v;
			v.push_back(i);
			result.push_back(v);
		}
	}

	int sp = 13;

	cout << "size " << result.size() << endl;
	for (i=0; i<result.size(); ++i){
		cout << "[" << i << "]";
		for (int n : result[i]){
			cout << " " << n;
		}
		cout << endl;
		if (i == sp){
			for (int n : result[i]){
				cout << _h[n] << endl;
				cout << _v[n] << endl;
			}
		}
	}

	throw Error::debug;
}

int SymbolsClassifier::_compare(int a, int b){
	int h = compare(_h[a], _h[b]);
	int v = compare(_v[a], _v[b]);
	return h/2+v;
}

}

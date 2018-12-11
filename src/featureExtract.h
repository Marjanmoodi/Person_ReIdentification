#pragma once
#include <opencv\cv.h>
#include <opencv2\highgui\highgui.hpp>
using namespace cv;
class featureExtract
{
private:
	
public:
	 MatND uhist;
	 MatND dhist;
	Mat upBody;
	Mat upHSV;
	Mat downHSV;
	Mat downBody;
	Mat uhistImg;
	Mat dhistImg;
	featureExtract(Mat up,Mat down);
	featureExtract();
	void Hist(Mat d,Mat u);
	MatND  getUphist();
	MatND  getDownhist();
	~featureExtract(void);
};


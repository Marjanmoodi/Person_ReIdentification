#pragma once
#include <opencv2\imgproc\imgproc.hpp>
using namespace cv;
class background
{

public:
	Mat khar;
	background(void);
	Mat finalres;
	~background(void);
	void subtract(string s);
	Mat img_bw;
	cv::Mat foreGround;
};


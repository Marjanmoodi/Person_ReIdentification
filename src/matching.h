#pragma once
#include "opencv\cv.h"
#include "opencv2\highgui\highgui.hpp"
using namespace cv;
class matching
{
public:
	int indexOfperson;
	int indexarray[200];
	MatND torso;
	MatND legs;
	string hDataset;
	double claculateSim();
	matching(void);
	matching(MatND t,string s);
	matching(MatND t,MatND s);
	MatND gallery;
	void test();
	~matching(void);
};


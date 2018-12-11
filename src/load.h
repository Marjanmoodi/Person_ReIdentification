#pragma once
#include <opencv\cv.h>
#include <opencv2\highgui\highgui.hpp>
#include "god.h"
#include "featureExtract.h"
#include "part.h"
#include "background.h"
using namespace cv;
using namespace std;
class load
{
private:
	Mat SourceImage;
	int numberOfPerson;
	int numberOfShot;
	god* prog;
	part p;
	featureExtract feature;
	background back;
	
public:
	//void test();
	background getbackground();
	load(god* g);
	load(void);
	~load(void);
	bool loadDataSet(String s);

};


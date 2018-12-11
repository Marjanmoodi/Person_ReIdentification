//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//#include "opencv\cv.h"
//#include "opencv2\legacy\legacy.hpp"
//
//using namespace cv;
//using namespace std;
//
//Mat src; Mat src_gray;
//int thresh = 100;
//int max_thresh = 255;
//RNG rng(12345);
//
///// Function header
//void thresh_callback(int, void* );
//using namespace cv;
///** @function main */
//int main( int argc, char** argv )
//{
//	Mat bin = imread("",1);
//	
//	IplConvKernel* pb= cvCreateStructuringElementEx(3,3,1,1,CV_SHAPE_RECT,NULL);
//	
//
//	cvErode(&bin,erode,pb,2);
//
//	cvReleaseStructuringElement(&pb);
//
//
//	Mat Binmat(erode, 0);
//
//	findContours(Binmat, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
//
//	cvSnakeImage( bin, contours, length_of_contours, &alpha, &beta, &gamma,
//
//		CV_VALUE, cvSize(3,3), criteria, 2 );
//
//}
// TrainingTools.cpp
//
 
#include "snakeWirhContours.h"
#include <iostream>
#include <string.h>
#include <opencv2\highgui\highgui_c.h>
#include <opencv\cv.h>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\legacy\legacy.hpp>
#include <fstream>
 
 
IplImage *image = 0 ; 
IplImage *image2 = 0 ; 
 
using namespace std;
int Thresholdness = 141;
int ialpha = 20;
int ibeta=20; 
int igamma=20; 
 
void onChange(int pos)
{
 
	if(image2) cvReleaseImage(&image2);
	if(image) cvReleaseImage(&image);
 
	image2 = cvLoadImage("C:\\Users\\Marjan\\Desktop/1.jpg",1); 
	image= cvLoadImage("C:\\Users\\Marjan\\Desktop/1.jpg",0);
 
	cvThreshold(image,image,90,255,CV_THRESH_BINARY); 
 cvSaveImage("C:\\Users\\Marjan\\Desktop/binarythresh.png",image);
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contours = 0;
 
	cvFindContours( image, storage, &contours, sizeof(CvContour), 
		CV_RETR_EXTERNAL , CV_CHAIN_APPROX_SIMPLE );
 
	if(!contours) return ; 
	int length =10;
		//contours->total;	
	if(length<10)
	{return ; }
	CvPoint* point = new CvPoint[length]; 
 
	CvSeqReader reader;
	CvPoint pt= cvPoint(0,0);;	
	CvSeq *contour2=contours;	
 
	cvStartReadSeq(contour2, &reader);
	for (int i = 0; i < length; i++)
	{
		CV_READ_SEQ_ELEM(pt, reader);
		point[i]=pt;
	}
	cvReleaseMemStorage(&storage);
 
	
	for(int i=0;i<length;i++)
	{
		int j = (i+1)%length;
		cvLine( image2, point[i],point[j],CV_RGB( 0, 0, 255 ),1,8,0 ); 
	}
 
	float alpha=ialpha/100.0f; 
	float beta=ibeta/100.0f; 
	float gamma=igamma/100.0f; 
 
	CvSize size; 
	size.width=3; 
	size.height=3; 
	CvTermCriteria criteria; 
	criteria.type=CV_TERMCRIT_ITER; 
	criteria.max_iter=1000; 
	criteria.epsilon=0.1; 
	cvSnakeImage( image, point,length,&alpha,&beta,&gamma,CV_VALUE,size,criteria,0 ); 
 
	
	for(int i=0;i<length;i++)
	{
		int j = (i+1)%length;
		cvLine( image2, point[i],point[j],CV_RGB( 0, 255, 0 ),1,8,0 ); 
	}
	delete []point;
 
}
 
//int main(int argc, char* argv[])
//{
// 
 
	/*cvNamedWindow("win1",0); 
	cvCreateTrackbar("Thd", "win1", &Thresholdness, 255, onChange);
	cvCreateTrackbar("alpha", "win1", &ialpha, 100, onChange);
	cvCreateTrackbar("beta", "win1", &ibeta, 100, onChange);
	cvCreateTrackbar("gamma", "win1", &igamma, 100, onChange);
	cvResizeWindow("win1",300,500);*/
//	onChange(0);
//	cvSaveImage("C:\\Users\\Marjan\\Desktop/testcontour.jpeg",image2);
// 
//	/*for(;;)
//	{
//		if(cvWaitKey(40)==27) break;
//		cvShowImage("win1",image2);
//	}*/
// 
//	return 0;
//}

#include "background.h"
#include <opencv2\legacy\legacy.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "typeOfImage.h"
using namespace cv;
background::background(void)
{
}
void background::subtract(string t)
{
	//Mat	image=i;
	//imread
	char * targ= strdup(t.c_str());
	int count=0;
	Mat img = imread(targ);
	Mat pure(img);

	// define bounding rectangle
	cv::Rect rectangle(1,1,62,126);
	cv::Mat result; // segmentation result (4 possible values)
	cv::Mat bgModel,fgModel; // the models (internally used)

	// GrabCut segmentation
	cv::grabCut(img,    // input image
		result,   // segmentation result
		rectangle,// rectangle containing foreground
		bgModel,fgModel, // models
		2,        // number of iterations
		cv::GC_INIT_WITH_RECT); // use rectangle

	// Get the pixels marked as likely foreground
	cv::compare(result,cv::GC_PR_FGD,result,cv::CMP_EQ);
	img_bw=result>128;
	// Generate output image
	 finalres=(img.size(),CV_8UC3,cv::Scalar(255,255,255));
	//cv::Mat background(image.size(),CV_8UC3,cv::Scalar(255,255,255));
	 imwrite("C:\\Users\\Marjan\\Desktop/finalresbefore.jpg",finalres);
	img.copyTo(finalres,result); // bg pixels not copied

	// draw rectangle on original image
	cv::rectangle(img, rectangle, cv::Scalar(0,0,0),1);

	imwrite("C:\\Users\\Marjan\\Desktop/result.jpg",result);

	imwrite("C:\\Users\\Marjan\\Desktop/Foregroundafter.jpg",finalres);

	//imshow("win1",dst);
	khar=imread(t);
//	khar.copyTo(finalres,img_bw);
//	imwrite("C:\\Users\\Marjan\\Desktop/img_bw.jpeg",img_bw);
//	imwrite("C:\\Users\\Marjan\\Desktop/finalres.jpeg",finalres);
	//	imwrite("C:\\Users\\Marjan\\Desktop/kharfinal.jpeg",khar);
	//	waitKey(0);
}
//Mat background::getBinaryForeground()
//{
//	return img_bw;
//}
background::~background(void)
{
}

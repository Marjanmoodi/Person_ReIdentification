#include "featureextract.h"

featureExtract::featureExtract()
{
}
featureExtract::featureExtract(Mat u,Mat d)
{
	upBody=u;
	downBody=d;
}

void featureExtract::Hist(Mat dmask,Mat umask)
{
	Mat test;
	cvtColor(upBody, upHSV, CV_BGR2HSV);
	
	cvtColor(downBody,downHSV, CV_BGR2HSV);
	imwrite("C:\\Users\\Marjan\\Desktop/uhsv.png",upHSV);
	imwrite("C:\\Users\\Marjan\\Desktop/uhsv.png",test);
	int hbins = 30, sbins = 30;
	int histSize[] = {hbins, sbins}; //30ta hbins 30ta sbins
	float hranges[] = { 0, 180 };
	float sranges[] = { 0, 256 };
	const float* ranges[] = { hranges, sranges };
	imwrite("C:\\Users\\Marjan\\Desktop/umask.png",umask);
	int channels[] = {0, 1};
	calcHist( &upHSV, 1, channels, umask,
		uhist, 2, histSize, ranges,
		true, // the histogram is uniform
		false );
	normalize(uhist, uhist, 0, 1, NORM_MINMAX, -1, Mat() );
	//normalize( hist_test1, hist_test1, 0, 1,NORM_MINMAX, -1, Mat() );
	calcHist( &downHSV, 1, channels, dmask,dhist, 2, histSize, ranges,true, // the histogram is uniform
		false );
	normalize(uhist, uhist, 0, 1, NORM_MINMAX, -1, Mat() );
//	double maxVal=0;

//	minMaxLoc(uhist, 0, &maxVal, 0, 0);

//	int scale = 10;
//	uhistImg = Mat::zeros(sbins*scale, hbins*10, CV_8UC3);
//	dhistImg = Mat::zeros(sbins*scale, hbins*10, CV_8UC3);

	/*for( int h = 0; h < hbins; h++ )
		for( int s = 0; s < sbins; s++ )
		{
			float binVal = uhist.at<float>(h, s);
			int intensity = cvRound(binVal*255/maxVal);
			rectangle( uhistImg, Point(h*scale, s*scale),
				Point( (h+1)*scale - 1, (s+1)*scale - 1),
				Scalar::all(intensity),
				CV_FILLED );
		}

		for( int h = 0; h < hbins; h++ )
			for( int s = 0; s < sbins; s++ )
			{
				float binVal = dhist.at<float>(h, s);
				int intensity = cvRound(binVal*255/maxVal);
				rectangle( dhistImg, Point(h*scale, s*scale),
					Point( (h+1)*scale - 1, (s+1)*scale - 1),
					Scalar::all(intensity),
					CV_FILLED );
			}


			imwrite( "C:/users/Marjan/Desktop/up.jpg", upBody );
			imwrite( "C:/users/Marjan/Desktop/uphist.jpg", uhistImg );
			imwrite( "C:/users/Marjan/Desktop/downhist.jpg", dhistImg );
			imwrite( "C:/users/Marjan/Desktop/down.jpg", downBody );*/

			//	imwrite("C:/users/Marjan/Desktop/2.jpg",histImg);

}

MatND featureExtract:: getUphist()
{
	return uhist;
}
MatND featureExtract:: getDownhist()
{
	return dhist;
}
featureExtract::~featureExtract(void)
{
}

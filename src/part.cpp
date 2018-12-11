#include "part.h"
#include <opencv\cv.h>
#include <opencv2\highgui\highgui.hpp>
#include "typeOfImage.h"
#include "background.h"
#include "load.h"
using namespace std;
part::part()
{
	//body=imread("C:\\Users\\Marjan\\Desktop/17.png",1);
	temp=0;
}

//part::part()
//
//{
//	
//	//	methode=a;// a=0 simple methode a=1 adaptive methode
//}
void part::fixedpart(Mat f,Mat p)
{
	body=p;
	cv::Size s=body.size();
	rows = s.height;
	cols = s.width;
	up.x = 0;
	up.y = rows / 6.25;
	up.height = rows / 3.44;
	up.width = cols;
	simpleTorso = body(up);
	imwrite("C:\\Users\\Marjan\\Desktop/marjan.jpeg",simpleTorso);
	down.x=0;
	down.y=rows/2.2222;
	down.height=rows/1.81;
	down.width=cols;
	simpleLegs = body(down);
	imwrite("C:\\Users\\Marjan\\Desktop/moodi.jpeg",simpleLegs);
	FG=f;
	upMask=FG(up);
	downMask=FG(down);
	

}

Mat part::getSimpleUp()
{
	return simpleTorso;
	
}
Mat part::getSimpledown()
{
	return simpleLegs;
}


double part::Cvalue(int i)
{
	
	Mat HSVbody;
	typeOfImage tp;
//	cvtColor(body, HSVbody, CV_BGR2HSV);
	//imwrite("C:\\Users\\Marjan\\Desktop/hsv.jpg",HSVbody);
	//cvNamedWindow("win");
	//imshow("win",HSVbody);
	//waitKey(0);
	cv::Size s=body.size();
	rows = s.height;
	int sigma=rows/5;
	int J = s.width;
	Rect up_rect;
	Rect down_rect;
	up_rect.y=i-sigma;
	up_rect.x=0;
	up_rect.height=sigma;
	up_rect.width=J;
	down_rect.y=i;
	down_rect.x=0;
	down_rect.height=sigma;
	down_rect.width=J;
	Mat u=body(up_rect);
	Mat d=body(down_rect);
	imwrite("C:\\Users\\Marjan\\Desktop/up/"+std::to_string( i )+".jpeg",u);
	imwrite("C:\\Users\\Marjan\\Desktop/down/"+std::to_string( i )+".jpeg",d);
	//string dType = tp.typ(d.type());
	//float kh=d.at<uchar>(32,64);
	//Vec3b rgbv = d.at<Vec3b>(16,10);
	 C=norm(u,d,NORM_L2);
	return C;
	
}
double part::newCvalue(int i)
{
	typeOfImage tp;
	cv::Size s=body.size();
	rows = s.height;
	int sigma=rows/5;
	int J = s.width;
	double newC=0;
	for(int x=0;x<J;x++) //j

	{
		for(int y=0;y<sigma;y++) //sigma
		{
			Vec3b upPoints=body.at<Vec3b>(i-y,x);
			Vec3b downPoints=body.at<Vec3b>(i+y,x);
			bool test=FG.at<uchar>(72,25);
		//imwrite("C:\\Users\\Marjan\\Desktop/FG.png",FG);
			if(FG.at<uchar>(i-y,x)!=0 && FG.at<uchar>(i+y,x)!=0 ) // noghate sefid 255 foreground
			{
				
				
				double distance=sqrt(((upPoints[0]-downPoints[0])*(upPoints[0]-downPoints[0]))+((upPoints[1]-downPoints[1])*(upPoints[1]-downPoints[1]))+((upPoints[2]-downPoints[2])*(upPoints[2]-downPoints[2])));
				newC=newC+distance;
				
			}

		}



	}
	return newC;
}
double part:: symmetryC(int k)
{
	typeOfImage tp;
	cv::Size s=body.size();
	rows = s.height;
	int sigma=rows/5;
	int J = s.width;
	double symC=0;
	for(int x=0;x<cols/4;x++) //j

	{
		for(int y=indexOfHead;y<indexOfleg;y++) //sigma
		{
			Vec3b leftPoints=body.at<Vec3b>(y,k-x);
			Vec3b rightPoints=body.at<Vec3b>(y,k+x);
			bool test=FG.at<uchar>(72,25);
		//imwrite("C:\\Users\\Marjan\\Desktop/FG.png",FG);
			if(FG.at<uchar>(y,k-x)!=0 && FG.at<uchar>(y,k+x)!=0 ) // noghate sefid 255 foreground
			{
				
				
				double distance=sqrt(((leftPoints[0]-rightPoints[0])*(leftPoints[0]-rightPoints[0]))+((leftPoints[1]-rightPoints[1])*(leftPoints[1]-rightPoints[1]))+((leftPoints[2]-rightPoints[2])*(leftPoints[2]-rightPoints[2])));
				symC=symC+distance;
				
			}

		}
		return symC;


}
}
double part:: symmetryCd(int k)
{
	typeOfImage tp;
	cv::Size s=body.size();
	rows = s.height;
	int sigma=rows/5;
	int J = s.width;
	double symC=0;
	for(int x=0;x<cols/4;x++) //j

	{
		for(int y=indexOfleg;y<s.height;y++) //sigma
		{
			Vec3b leftPoints=body.at<Vec3b>(y,k-x);
			Vec3b rightPoints=body.at<Vec3b>(y,k+x);
			bool test=FG.at<uchar>(72,25);
		//imwrite("C:\\Users\\Marjan\\Desktop/FG.png",FG);
			if(FG.at<uchar>(y,k-x)!=0 && FG.at<uchar>(y,k+x)!=0 ) // noghate sefid 255 foreground
			{
				
				
				double distance=sqrt(((leftPoints[0]-rightPoints[0])*(leftPoints[0]-rightPoints[0]))+((leftPoints[1]-rightPoints[1])*(leftPoints[1]-rightPoints[1]))+((leftPoints[2]-rightPoints[2])*(leftPoints[2]-rightPoints[2])));
				symC=symC+distance;
				
			}

		}
		return symC;


}
}
double part::optimumC2(int i)
{
	cv::Size s=body.size();
	rows = s.height;
	int sigma=rows/5;
	int J = s.width;
	Rect up_rect;
	Rect down_rect;
	up_rect.y=i-sigma;
	up_rect.x=0;
	up_rect.height=sigma;
	up_rect.width=J;
	down_rect.y=i;
	down_rect.x=0;
	down_rect.height=sigma;
	down_rect.width=J;
	Mat u=body(up_rect);
	Mat d=body(down_rect);
	Mat upFG=FG(up_rect);
	Mat downFG=FG(down_rect);
	Mat Both;
	bitwise_and(upFG,downFG,Both);
	Mat upChannel[3];
	Mat downChannel[3];
    split(u,upChannel);
	split(d,downChannel);
	Mat sub[3];
	Mat powered[3];
	int a=upChannel[0].at<uchar>(20,20);
	int b=downChannel[0].at<uchar>(20,20);
	//sub[0]=upChannel[0]-downChannel[0];
	
	subtract(upChannel[0],downChannel[0],sub[0]);
	cv::Mat m = cv::Mat::eye(5,5,CV_32FC1);

	//cv::FileStorage file("C:\\Users\\Marjan\\Desktop/mat.xml", cv::FileStorage::WRITE);
	//file << m;

	FileStorage fs("C:\\Users\\Marjan\\Desktop/mat.yml", FileStorage::WRITE);
Mat cameraMatrix = (Mat_<double>(3,3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
fs << "cameraMatrix" << sub[0];
fs.release();
divide(255,sub[0],sub[0]);
 sqrt(sub[0],sub[1]);
	
	FileStorage fs2("C:\\Users\\Marjan\\Desktop/matsqtr.yml", FileStorage::WRITE);
fs2 << "cameraMatrix" << sub[1];
fs2.release();
	sub[1]=upChannel[1]-downChannel[1];
	sub[2]=upChannel[2]-downChannel[2];
	pow(sub[0],2,powered[0]);
	pow(sub[1],2,powered[1]);
	pow(sub[2],2,powered[2]);
	
	a=powered[0].at<uchar>(0,0);
	Mat sum;
	sum=powered[0]+powered[1]+powered[2];
	Mat distance;
	double C=0;
	//sqrt(sum,sum);
	pow(sum,0.5,distance);
	for(int x=0;x<J;x++) //j

	{
		for(int y=0;y<sigma;y++)
		{
			if(Both.at<uchar>(x,i-y)!=0 && Both.at<uchar>(x,i+y)!=0 )
			{
			C+=sum.at<uchar>(x,y);
			}
		}
//	imwrite("C:\\Users\\Marjan\\Desktop/blue.jpeg",channel[2]);
	return C;
}
}
	
double part::optimumC(int i)
{
cv::Size s=body.size();
	rows = s.height;
	int sigma=rows/5;
	int J = s.width;
	Rect up_rect;
	Rect down_rect;
	up_rect.y=i-sigma;
	up_rect.x=0;
	up_rect.height=sigma;
	up_rect.width=J;
	down_rect.y=i;
	down_rect.x=0;
	down_rect.height=sigma;
	down_rect.width=J;
	Mat u=body(up_rect);
	Mat d=body(down_rect);
	Mat upFG=FG(up_rect);
	Mat downFG=FG(down_rect);
	Mat Both;
	bitwise_and(upFG,downFG,Both);
	imwrite("C:\\Users\\Marjan\\Desktop/down/downFG"+std::to_string( i )+".jpeg",downFG);
	imwrite("C:\\Users\\Marjan\\Desktop/up/upFG"+std::to_string( i )+".jpeg",upFG);
	imwrite("C:\\Users\\Marjan\\Desktop/both/bothFG"+std::to_string( i )+".jpeg",Both);
	C=norm(u,d,NORM_L2,Both);
	return C;
}

double part::Svalue(int i)
{
	
	int A1=0;
	int A2=0;
	cv::Size s=body.size();
	rows = s.height;
	int sigma=rows/5;
	int J = s.width;
	for(int p=0;p<sigma;p++)
	{
		
		for(int k=0;k<J;k++)
		{
			if((int)FG.at<uchar>(i-p,k)!=0) // white pixels foreground
				A1++;
		}
		
	}
	for(int p=0;p<sigma;p++)
	{
		for(int k=0;k<J;k++)
		{
			if(FG.at<char>(i+p,k)!=0)
				A2++;
		}
		
	}
	 int Smid=abs(A1-A2);
	int temp=J*sigma;
	S=(double)Smid/temp;
	 return S;
}
int part::torsoLegs(Mat f,Mat pure)
{
	body=pure;
	
	imwrite("C:\\Users\\Marjan\\Desktop/marjanhastam.jpeg",body);
	double temp=20;
	FG=f;
	indexOfHead=0;
	 indexOfleg=0;
	cv::Size s=body.size();
	cols=s.width;
	rows = s.height; //128
	int sigma=rows/5; //25
	int length=rows-3*sigma;
	double Cvlues[53];
	double Svlues[53];
	double testres[53];
	double maxCValue=0;
	
	for(int y=2*sigma;y<(rows-sigma);y++) // 50 t0 103
	{
		//Cvlues[y-sigma]=1;
		Cvlues[y-2*sigma]=newCvalue(y);
	    Svlues[y-2*sigma]=Svalue(y);
	//	double argmin=(1-(Cvalue(y))+Svalue(y));
		
		
	
		
	}
	
	for(int y=2*sigma;y<(rows-sigma);y++) // 32 ta 96
	{
	if(maxCValue< Cvlues[y-2*sigma])
		{
			maxCValue=Cvlues[y-2*sigma];
			// indexOfleg=y;
		}
	}
	for(int y=2*sigma;y<(rows-sigma);y++) // 32 ta 96
	{
		Cvlues[y-2*sigma]=Cvlues[y-2*sigma]/maxCValue;
	}

	for(int y=2*sigma;y<(rows-sigma);y++)
	{
		double argmin=1-Cvlues[y-2*sigma]+Svlues[y-2*sigma];
		testres[y-2*sigma]=argmin;
		if(temp>argmin)
		{
		temp=argmin;
		indexOfleg= y;
		}
	
	}
	return indexOfleg;
//	return 0;
}
int part::bodyHead(Mat f,Mat p)
{
	FG=f;
	int khar;
	cv::Size s=body.size();
	cols=s.width;
	rows = s.height;
	int sigma=rows/5;
	int hd=torsoLegs(f,p);
	for(int x=sigma;x<rows/3;x++)
	{
		double argmin=-Svalue(x);
		if(temp>argmin)
		{
			temp=argmin;
			indexOfHead=x;
		}
	
		
	}
	return indexOfHead;
}
Mat part:: torso(Mat fg,Mat pure)
{
		
		Rect up;
		up.x=0;
		up.y=indexOfHead;
		Size s=body.size();
		up.width=s.width;
		up.height=indexOfleg-indexOfHead;
		Mat upBody=pure(up);
		 upMask=fg(up);
		 imwrite("C:\\Users\\Marjan\\Desktop/upasli.jpeg",upBody);
		 imwrite("C:\\Users\\Marjan\\Desktop/upmask.jpeg",upMask);
		return upBody;
		
}

Mat part::Legs(Mat fg,Mat pure)
{
	load l;
	Rect down;
		down.x=0;
		down.y=indexOfleg;
		Size s=body.size();
		down.width=s.width;
		down.height=s.height-indexOfleg;
		 downMask=fg(down);
		Mat downBody=pure(down);
		imwrite("C:\\Users\\Marjan\\Desktop/downasli.jpeg",downBody);
		imwrite("C:\\Users\\Marjan\\Desktop/downamask.jpeg",downMask);
		return downBody;
}
double part::Ssymmetry(int i)
{
	int A1=0;
	int A2=0;
Size s=body.size();
int rows=s.width;
int sigma=rows/4;
	for(int k=0;k<sigma;k++)
	{
		for(int p=indexOfHead;p<indexOfleg;p++)
		{
		if((int)FG.at<uchar>(p,i-k)!=0)
		A1++;
		if((int)FG.at<uchar>(p,i+k)!=0)
		A2++;
		}
	}
	 int Smid=abs(A1-A2);
	 int temp=(indexOfleg-indexOfHead)*sigma;
	S=(double)Smid/temp;
	 return S;

}
double part::Susymmetry(int i)
{
	int A1=0;
	int A2=0;
Size s=body.size();
int rows=s.width;
int f=s.height;
int sigma=rows/4;
	for(int k=0;k<sigma;k++)
	{
		for(int p=indexOfleg;p<f;p++)
		{
		if((int)FG.at<uchar>(p,i-k)!=0)
		A1++;
		if((int)FG.at<uchar>(p,i+k)!=0)
		A2++;
		}
	}
	 int Smid=abs(A1-A2);
	 int temp=(indexOfleg-indexOfHead)*sigma;
	S=(double)Smid/temp;
	 return S;

}
int part::upsymmetry()
{
	double temp=20;
	int indexOfupSymm=0;
	cv::Size s=body.size();
	cols=s.width;
	int rows = s.height;
	int head=indexOfHead;
	int torso=indexOfleg;
	int sigma=cols/4;
	for(int x=cols/4;x<cols*3/4;x++)
	{
		{
			double argmin=symmetryC(x)+Ssymmetry(x);
		if(temp>argmin)
		{
			temp=argmin;
			indexOfupSymm=x;
		}
		}
		
	}
	return indexOfupSymm;
}
int part::downsymmetry()
{
	double temp=20;
	int indexOfupSymm=0;
	cv::Size s=body.size();
	cols=s.width;
	int rows = s.height;
	int head=indexOfHead;
	int torso=indexOfleg;
	int sigma=cols/4;
	for(int x=cols/4;x<cols*3/4;x++)
	{
		{
			double argmin=symmetryCd(x)+Susymmetry(x);
		if(temp>argmin)
		{
			temp=argmin;
			indexOfupSymm=x;
		}
		}
		
	}
	return indexOfupSymm;
}


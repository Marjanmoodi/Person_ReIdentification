#include "load.h"
#include "god.h"
#include "part.h"
#include "featureExtract.h"
#include "qprogressbar.h"
#include <opencv\cv.h>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "typeOfImage.h"
#include "background.h"
using namespace cv;
using namespace std;
load::load(god* g)
{
	prog=g;
	

}
load::load(void)
{

}

bool load::loadDataSet(String s)
{
	typeOfImage pt;
	
	//background b;
	numberOfPerson=200;
	numberOfShot=5;
	float percent=numberOfPerson*numberOfShot;
	String baseAddress=s+"\/";
	int Pvalue=0;
	String post=std::string(".png");
	int count=0;
	String addr;
	for(int j=1;j<=numberOfPerson;j++){
		FileStorage fs("C:\\Users\\Marjan\\Desktop/mats/mat"+std::to_string(j)+".yml", FileStorage::WRITE);
				for(int i=1;i<=numberOfShot;i++)
		{
			count++;
			if(j<10)
			 addr="person_000"+std::to_string( j )+"/000"+std::to_string( i );
			else if(j<100)
				addr="person_00"+std::to_string( j )+"/000"+std::to_string( i );
			else if(j<1000)
				addr="person_0"+std::to_string( j )+"/000"+std::to_string( i );
			String address=baseAddress+addr+post;
			back.subtract(address);
			if(prog->p1==0){
				p.fixedpart(back.img_bw,back.finalres);
				feature=featureExtract(p.getSimpleUp(),p.getSimpledown());
			}
			else
			{
				p.torsoLegs(back.img_bw,back.finalres);
				p.bodyHead(back.img_bw,back.finalres);
				Mat t=p.torso(back.img_bw,back.finalres);
				Mat l=p.Legs(back.img_bw,back.finalres);
				feature=featureExtract(t,l);
			}
		
			feature.Hist(p.downMask,p.upMask);
			float value=count/percent;
			Pvalue=value*100;
			prog->setProgValue(Pvalue);
			MatND uphist=feature.getUphist();
			MatND downhist=feature.getDownhist();
			fs << "upHistogram"+std::to_string(i) << uphist;
			fs << "downHistogram"+std::to_string(i) << downhist;

		}
		
	}

	
		return true;
	
}
//void load::test()
//{
//cv::Mat my_histogram;
//cv::FileStorage fs("my_histogram_file.yml", cv::FileStorage::READ);
//if (!fs.isOpened()) 
//{std::cout << "unable to open file storage!" << std::endl; return;}
//fs >> "my_histogram" >>feature.histImg;
//fs.release();
//}
background load::getbackground()
{
 return back;
}
load::~load(void)
{
}

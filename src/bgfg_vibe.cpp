#include "bgfg_vibe.h"
#include "opencv2\highgui\highgui.hpp"
#include "opencv\cv.h"
using namespace cv;
bgfg_vibe::bgfg_vibe():R(20),N(20),noMin(2),phi(0)
{
    initDone=false;
    rnd=cv::theRNG();
    ri=0;
}
void bgfg_vibe::init()
{
    for(int i=0;i<rndSize;i++)
    {
        rndp[i]=rnd(phi);
        rndn[i]=rnd(N);
        rnd8[i]=rnd(8);
    }
}
void bgfg_vibe::setphi(int phi)
{
    this->phi=phi;
    for(int i=0;i<rndSize;i++)
    {
        rndp[i]=rnd(phi);
    }
}
void bgfg_vibe::init_model(cv::Mat& firstSample)
{
    std::vector<cv::Mat> channels;
    split(firstSample,channels);
    if(!initDone)
    {
        init();
        initDone=true;
    }
    model=new Model;
    model->fgch= new cv::Mat*[channels.size()];
    model->samples=new cv::Mat**[N];
    model->fg=new cv::Mat(cv::Size(firstSample.cols,firstSample.rows), CV_8UC1);
    for(size_t s=0;s<channels.size();s++)
    {       
        model->fgch[s]=new cv::Mat(cv::Size(firstSample.cols,firstSample.rows), CV_8UC1);
        cv::Mat** samples= new cv::Mat*[N];
        for(int i=0;i<N;i++)
        {
            samples[i]= new cv::Mat(cv::Size(firstSample.cols,firstSample.rows), CV_8UC1);
        }
        for(int i=0;i<channels[s].rows;i++)
        {
            int ioff=channels[s].step.p[0]*i;
            for(int j=0;j<channels[0].cols;j++)
            {
                for(int k=0;k<1;k++)
                {
                    (samples[k]->data + ioff)[j]=channels[s].at<uchar>(i,j);
                }
                (model->fgch[s]->data + ioff)[j]=0;

                if(s==0)(model->fg->data + ioff)[j]=0;
            }
        }
        model->samples[s]=samples;
    }
}
void bgfg_vibe::fg1ch(cv::Mat& frame,cv::Mat** samples,cv::Mat* fg)
{
    int step=frame.step.p[0];
    for(int i=1;i<frame.rows-1;i++)
    {
        int ioff= step*i;
        for(int j=1;j<frame.cols-1;j++)
        {
            int count =0,index=0;
            while((count<noMin) && (index<N))
            {
                int dist= (samples[index]->data + ioff)[j]-(frame.data + ioff)[j];
                if(dist<=R && dist>=-R)
                {
                    count++; 
                }
                index++;
            }
            if(count>=noMin)
            {
                ((fg->data + ioff))[j]=0;
                int rand= rndp[rdx];
                if(rand==0)
                {
                    rand= rndn[rdx];
                    (samples[rand]->data + ioff)[j]=(frame.data + ioff)[j];
                }
                rand= rndp[rdx];
                int nxoff=ioff;
                if(rand==0)
                {
                    int nx=i,ny=j;
                    int cases= rnd8[rdx];
                    switch(cases)
                    {
                    case 0:
                        //nx--;
                        nxoff=ioff-step;
                        ny--;
                        break;
                    case 1:
                        //nx--;
                        nxoff=ioff-step;
                        ny;
                        break;
                    case 2:
                        //nx--;
                        nxoff=ioff-step;
                        ny++;
                        break; 
                    case 3:
                        //nx++;
                        nxoff=ioff+step;
                        ny--;
                        break; 
                    case 4:
                        //nx++;
                        nxoff=ioff+step;
                        ny;
                        break; 
                    case 5:
                        //nx++;
                        nxoff=ioff+step;
                        ny++;
                        break; 
                    case 6:
                        //nx;
                        ny--;
                        break; 
                    case 7:
                        //nx;
                        ny++;
                        break; 
                    }
                    rand= rndn[rdx];
                    (samples[rand]->data + nxoff)[ny]=(frame.data + ioff)[j];
                }
            }else
            {
                ((fg->data + ioff))[j]=255;
            }
        }
    }
}
void bgfg_vibe::mean()
{

	cv::Mat avgImg;
	Mat first[5];
	
	first[0]=imread("C:\\Users\\Marjan\\Desktop\\project resources\\1/0001.png");
	first[1]=imread("C:\\Users\\Marjan\\Desktop\\project resources\\1/0002.png");
	first[2]=imread("C:\\Users\\Marjan\\Desktop\\project resources\\1/0003.png");
	first[3]=imread("C:\\Users\\Marjan\\Desktop\\project resources\\1/0004.png");
	first[4]=imread("C:\\Users\\Marjan\\Desktop\\project resources\\1/0005.png");
	Size s=first[0].size();
avgImg.create(s.width, s.height,CV_32FC3);

for(int i = 1; i <= 5; i++){
  Mat image =first[i-1];
  cv::accumulate(image, avgImg);
}

avgImg = avgImg / N;
Mat Mean   = Mat::zeros(s.width, s.height,CV_32F); 
 for(int i = 1; i <= 5 ; i++){
     Mat image =first[i-1];
      accumulate(image, Mean);
    }
 Mean = Mean /5;
 Mean.convertTo(Mean,CV_8U);
 imshow("mean",Mean);
 waitKey(0);
}
void bgfg_vibe:: test()
{
// Open another image
Mat image;
image= cv::imread("C:\\Users\\Marjan\\Desktop/m.png");
//Mat img=imread("C:\\Users\\Marjan\\Desktop/m1.png");
Mat prbg;
//bitwise_xor(image,img,prbg);
//Mat bw=prbg>128;
//cvtColor(bw,prbg,CV_BGR2GRAY);
//imwrite("C:\\Users\\Marjan\\Desktop/subtract.png",prbg);
//imwrite("C:\\Users\\Marjan\\Desktop/subtract2.png",bw);
Mat image2 = image.clone();
Size s=image.size();
int x=s.width-3;
int y=s.height-3;
// define bounding rectangle
cv::Rect rectangle(1,1,x,y);
Mat bebinam=image(rectangle);
cv::Mat result; // segmentation result (4 possible values)
cv::Mat bgModel,fgModel; // the models (internally used)

// GrabCut segmentation
cv::grabCut(image,    // input image
            result,   // segmentation result
            rectangle,// rectangle containing foreground
            bgModel,fgModel, // models
              1,    // number of iterations
			  cv::GC_INIT_WITH_RECT); // use rectangle

// Get the pixels marked as likely foreground
//imwrite("C:\\Users\\Marjan\\Desktop/aftergrab.jpg",result);
//imwrite("C:\\Users\\Marjan\\Desktop/afergrab.jpg",fgModel);
cv::compare(result,cv::GC_PR_FGD,result,cv::CMP_EQ);
//imwrite("C:\\Users\\Marjan\\Desktop/afercompare.jpg",result);
// Generate output image
cv::Mat foreground(image.size(),CV_8UC3,cv::Scalar(255,255,255));
//cv::Mat background(image.size(),CV_8UC3,cv::Scalar(255,255,255));
image.copyTo(foreground,result); // bg pixels not copied

// draw rectangle on original image
cv::rectangle(image, rectangle, cv::Scalar(255,255,255),1);

imwrite("C:\\Users\\Marjan\\Desktop/img_1.jpg",image);

imwrite("C:\\Users\\Marjan\\Desktop/Foreground.jpg",foreground);
//imwrite("C:\\Users\\Marjan\\Desktop/bebinam.jpg",bebinam);
Mat background = image2 - foreground;
//imwrite("C:\\Users\\Marjan\\Desktop/Background.jpg",background);
}
cv::Mat* bgfg_vibe::fg(cv::Mat& frame)
{
    std::vector<cv::Mat> channels;
    split(frame,channels);
    for(size_t i=0;i<channels.size();i++)
    {
        fg1ch(channels[i],model->samples[i],model->fgch[i]);        
        if(i>0 && i<2)
        {
            bitwise_or(*model->fgch[i-1],*model->fgch[i],*model->fg);
        }
        if(i>=2)
        {
            bitwise_or(*model->fg,*model->fgch[i],*model->fg);
        }
    }
    if(channels.size()==1) return model->fgch[0];
    return model->fg;
}

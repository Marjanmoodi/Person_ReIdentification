////#include "stdafx.h"   
//   
//// STL includes:   
//#include <iostream>   
//using namespace std;   
//   
//// OpenCV includes   
//#include <opencv2\highgui\highgui.hpp>
//   
//// local includes   
//#include "snake.h"   
////#include <opencv2\
//   
//   
//////////////////////////////////////////////////////////////////////////////   
//Snake::Snake(QtCvWrapper* parent, IplImage* inImg) :   
//    m_parent(parent),   
//    m_inImg(0),   
//    m_snakeImg(0),   
//    m_alpha((float)1.0),   
//    m_beta((float)1.0),   
//    m_gamma((float)1.2),   
//    m_numSegments(200),   
//    m_numIteration(20)   
//{   
//    m_inImg = cvCloneImage(inImg);   
//   
//    m_winSize.width = 5;   
//    m_winSize.height = 5;   
//   
//    m_snakeImg = cvCreateImage( cvSize(m_inImg->width, m_inImg->height),    
//        IPL_DEPTH_8U, 3);   
//    m_crit = cvTermCriteria(CV_TERMCRIT_ITER, m_numIteration, 0.0);   
//    m_snakeCurve = new CvPoint[m_numSegments];   
//}   
//   
//////////////////////////////////////////////////////////////////////////////   
//Snake::~Snake(void)   
//{   
//    delete[] m_snakeCurve;   
//}   
//   
//////////////////////////////////////////////////////////////////////////////   
//void Snake::initSnakeCurve()   
//{   
//    m_snakeCurve = new CvPoint[m_numSegments];   
//    for(int i = 0; i < m_numSegments; i++)   
//    {   
//        m_snakeCurve[i].x = cvRound( 0.8 * m_inImg->width * cos(i * 6.28 / m_numSegments) / 2.0   
//            + m_inImg->width / 2 );   
//   
//        m_snakeCurve[i].y = cvRound( 0.8 * m_inImg->height * sin(i * 6.28 / m_numSegments) / 2.0   
//            + m_inImg->height / 2 );   
//    }   
//}   
//   
//////////////////////////////////////////////////////////////////////////////   
//void Snake::initSnakeCurve(CvPoint* pt)   
//{   
//    m_snakeCurve = pt;   
//    if(m_inImg->nChannels == 1)   
//        cvCvtColor(m_inImg, m_snakeImg, CV_GRAY2RGB);   
//    else if (m_inImg->nChannels == 3)   
//        cvCopy( m_inImg, m_snakeImg, NULL);   
//   
//    for (int actSegment = 0; actSegment < m_numSegments; actSegment++)   
//    {   
//        if(actSegment < m_numSegments-1)   
//            cvLine(m_snakeImg, pt[actSegment], pt[actSegment+1],   
//            CV_RGB(255, 0, 0), 2, 1);   
//        else   
//            cvLine(m_snakeImg, pt[actSegment], pt[0],   
//            CV_RGB(0, 255, 0), 2, 1);   
//    }   
//}   
//   
//////////////////////////////////////////////////////////////////////////////   
//IplImage* Snake::iterateSnakeCurve(int numIterations, bool showIterations)   
//{   
//    m_snakeImg = cvCreateImage( cvSize(m_inImg->width, m_inImg->height),    
//        IPL_DEPTH_8U, 3);   
//   
//    char wndName[] = "SNAKE";   
//   
//    for (int i = 0; i < numIterations; i++)   
//    {   
//        cvSnakeImage(m_inImg, m_snakeCurve, m_numSegments,    
//            &m_alpha, &m_beta, &m_gamma, 1, m_winSize, m_crit, 1);   
//   
//        if (showIterations)   
//        {   
//            // clear the line with loading the inital image   
//            if(m_inImg->nChannels == 1)   
//                cvCvtColor(m_inImg, m_snakeImg, CV_GRAY2RGB);   
//            else if (m_inImg->nChannels == 3)   
//                cvCopy( m_inImg, m_snakeImg, NULL);   
//            else   
//                qDebug("SNAKE - iterate: Undefined number of channels in the input image!");   
//   
//            for (int actSegment = 0; actSegment < m_numSegments; actSegment++)   
//            {   
//                if(actSegment < m_numSegments-1)   
//                    cvLine(m_snakeImg, m_snakeCurve[actSegment], m_snakeCurve[actSegment+1],   
//                    CV_RGB(255, 0, 0), 2, 1);   
//                else   
//                    cvLine(m_snakeImg, m_snakeCurve[actSegment], m_snakeCurve[0],   
//                    CV_RGB(0, 255, 0), 2, 1);   
//            }   
//            if (m_parent->iterate() == true)   
//            {   
//                cvNamedWindow( wndName, 1 );   
//                cvResizeWindow( wndName, m_inImg->width,m_inImg->height );   
//                cvShowImage( wndName, m_snakeImg );   
//   
//                if (m_parent->step() == true)   
//                    cvWaitKey(0);   
//                else   
//                    cvWaitKey(200);   
//            }   
//        }   
//    }   
//    cvDestroyWindow(wndName);   
//    return m_snakeImg;   
//}
#include "opencv2/opencv.hpp"
#include <string>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

class WatershedSegmenter{
private:
    cv::Mat markers;
public:
    void setMarkers(cv::Mat& markerImage)
    {
        markerImage.convertTo(markers, CV_32S);
    }

    cv::Mat process(cv::Mat &image)
    {
        cv::watershed(image, markers);
        markers.convertTo(markers,CV_8U);
        return markers;
    }
};


//int main(int argc, char* argv[])
//{
//    cv::Mat image = cv::imread("C:\\Users\\Marjan\\Desktop/1.jpg");
//    cv::Mat blank(image.size(),CV_8U,cv::Scalar(0xFF));
//    cv::Mat dest(image.size(),CV_8U,cv::Scalar(0xFF));
//    imshow("originalimage", image);
//
//    // Create markers image
//    cv::Mat markers(image.size(),CV_8U,cv::Scalar(-1));
//    //Rect(topleftcornerX, topleftcornerY, width, height);
//    //top rectangle
//    markers(Rect(0,0,image.cols, 5)) = Scalar::all(1);
//    //bottom rectangle
//    markers(Rect(0,image.cols-5,image.cols, 5)) = Scalar::all(1);
//    //left rectangle
//    markers(Rect(0,0,5,image.rows)) = Scalar::all(1);
//    //right rectangle
//    markers(Rect(image.cols-5,0,5,image.rows)) = Scalar::all(1);
//    //centre rectangle
//    markers(Rect(image.cols/2,image.rows/2,50, 50)) = Scalar::all(2);
//
//
//    //Create watershed segmentation object
//    WatershedSegmenter segmenter;
//    segmenter.setMarkers(markers);
//    cv::Mat result = segmenter.process(image);
//    result.convertTo(result,CV_8U);
//
//   bitwise_and(image, blank, dest, result);
//	imshow("final_result", blank);
//
//    cv::waitKey(0);
//
//    return 0;
//}
//int main(  )
//{
//    Mat drawing1 = Mat::zeros( Size(400,200), CV_8UC1 );
//    Mat drawing2 = Mat::zeros( Size(400,200), CV_8UC1 );
// 
//    drawing1(Range(0,drawing1.rows),Range(0,drawing1.cols/2))=255; imshow("drawing1",drawing1);
//    drawing2(Range(100,150),Range(150,350))=255; imshow("drawing2",drawing2);
// 
//    Mat res;
//    bitwise_and(drawing1,drawing2,res);     imshow("AND",res);
//    bitwise_or(drawing1,drawing2,res);      imshow("OR",res);
//    bitwise_xor(drawing1,drawing2,res);     imshow("XOR",res);
//    bitwise_not(drawing1,res);              imshow("NOT",res);
// 
// 
//    waitKey(0);
//    return(0);
//}
#pragma once
#include<opencv2\highgui\highgui.hpp>
using namespace cv;
class part
{
private:
	//Mat body;
	int methode;
	int indexOfHead;
	int indexOfleg;
	int rows;
	int cols;
	Rect up;
	Rect down;
	Mat simpleTorso;
	Mat simpleLegs;
	double C;
	double S;
	Mat FG;
	double max;
	double temp;
	
//	double findMax[];
public:
	Mat downMask;
	Mat upMask;
	Mat body;
	Mat Legs(Mat a,Mat b);
	Mat torso(Mat a,Mat b);
	double optimumC(int i);
	double optimumC2(int i);
	part();
	int downsymmetry();
	double  symmetryC(int p);
	double  symmetryCd(int p);
	double newCvalue(int i);
	void fixedpart(Mat f,Mat p);
	Mat getSimpleUp();
	Mat getSimpledown();
	double Cvalue(int i);
	double Svalue(int i);
	void weightedHist();
	int torsoLegs(Mat a,Mat b);
	int upsymmetry();
	int bodyHead(Mat t,Mat j);
	double Ssymmetry(int i);
	double Susymmetry(int i);


};

//	~part();



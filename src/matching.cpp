#include "matching.h"
#include "featureExtract.h"
#include <iostream>
#include <string>
using namespace std;
matching::matching(void)
{
}
matching::matching(MatND t,string s)
{
	hDataset=s;
	//testHist=t;
}
matching::matching(MatND t,MatND s)
{
	legs=s;
	torso=t;
}
double matching::claculateSim()
{
	const int numberOfPerson=200;
	const int numberOfProb=5;
	MatND gallery;
	double upsimilarity[numberOfPerson][numberOfProb];
	double downsimilarity[numberOfPerson][numberOfProb];
	for(int i=1;i<=numberOfPerson;i++)
	{
		FileStorage fs2("C:\\Users\\Marjan\\Desktop/mats/mat"+std::to_string(i)+".yml",FileStorage::READ);	
		for(int j=1;j<=numberOfProb;j++)
		{
			fs2["upHistogram"+std::to_string(j)] >> gallery; //0-> [-1,1] , 1->[0,binahayat] ], 2->[0,1] 1 behtarin ,3 [0,1] behtarin 0
			double marjan=compareHist(torso,gallery,3);
			upsimilarity[i-1][j-1]=marjan;
			fs2["downHistogram"+std::to_string(j)] >> gallery;
			double marjan2=compareHist(legs,gallery,3);
			downsimilarity[i-1][j-1]=marjan2;
		
		}
	}

	
	double TorsoAverage[numberOfPerson];
	float sum;
	for(int i=1;i<=numberOfPerson;i++)
	{
		sum=0;
		for(int j=1;j<=numberOfProb;j++)
		{
			sum+=upsimilarity[i-1][j-1];
		}
		TorsoAverage[i-1]=sum/numberOfProb;
	
	}
	double legAverage[numberOfPerson];
	
	for(int i=1;i<=numberOfPerson;i++)
	{
		sum=0;
		for(int j=1;j<=numberOfProb;j++)
		{
			sum+=downsimilarity[i-1][j-1];
		}
		legAverage[i-1]=sum/numberOfProb;
	
	}
	double totalAverage[numberOfPerson];
	//int indexarray[numberOfPerson];
	for(int i=1;i<=numberOfPerson;i++)
	{
		totalAverage[i-1]=TorsoAverage[i-1]*0.55+legAverage[i-1]*0.45;
		indexarray[i-1]=i;
	}
	
	int i, j, flag = 1;    // set flag to 1 to start first pass
     double temp;
	 int temp2;             // holding variable
	  int Length =numberOfPerson; 
	  for(i = 1; (i <= Length) && flag; i++)
     {
          flag = 0;
		  for (j=0; j < (Length -1); j++)
         {
			 if (totalAverage[j+1] < totalAverage[j])      // ascending order simply changes to <
              { 
				  temp = totalAverage[j]; 

				  temp2=indexarray[j]; // swap elements
				  indexarray[j]=indexarray[j+1];
				  indexarray[j+1]=temp2;
				  totalAverage[j] = totalAverage[j+1];
				  totalAverage[j+1] = temp;
                    flag = 1;               // indicates that a swap occurred.
               }
          }
     } 
	double min=totalAverage[0];
	indexOfperson=indexarray[0];
	
	return min;

//double similarity[20];
//  for(int i=0;i<1;i++)
//  {
//	 // Mat gallery=imread(hDataset+"/"+std::to_string(i));
//	   
//	  
//	  
//  
//  }
//  double small = similarity[0];
// for(int i=1;i<20;i++)
//{
//	if(similarity[i]<small)
//	{
//	small = similarity[i];
//	int index=i;
//	}
//}
// return small;
}
void matching:: test()
{
	Mat m1=imread("C:\\Users\\Marjan\\Desktop/downhist.jpg");
	Mat m2=imread("C:\\Users\\Marjan\\Desktop/downhist.jpg");
	double resu=compareHist(m1,m1,2);


}
matching::~matching(void)
{
}

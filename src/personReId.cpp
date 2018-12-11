#include "personReId.h"
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <qfiledialog.h>
#include "load.h"
#include "background.h"
#include "matching.h"
#include <qmessagebox.h>
#include "qscrollarea.h"
using namespace std;
using namespace cv;
personReId::personReId(QWidget *parent) //main windows
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.progressBar->hide();
	ui.test->setStyleSheet("border: 1px solid Blue");
	ui.a->hide();
	ui.b->hide();
	ui.c->hide();
	ui.d->hide();
	ui.a->setStyleSheet("border: 1px solid Blue");
	ui.b->setStyleSheet("border: 1px solid Blue");
	ui.c->setStyleSheet("border: 1px solid Blue");
	ui.d->setStyleSheet("border: 1px solid Blue");
	ui.label_3->hide();
	ui.label_5->hide();
	ui.label_6->hide();
	ui.label_7->hide();


}
QString personReId::ShowTarg(QString Source) //show target
{


	QPixmap pix(Source);
	ui.test->setPixmap(pix);
	return Source;


}
void personReId::myslot() //select dataset
{
	dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"C:/Users/Marjan/Desktop",   QFileDialog::ShowDirsOnly  | QFileDialog::DontResolveSymlinks);
	ui.lineEdit->setText(dir);
}

void personReId::myslot2() // Train dataset
{
	QString cb = ui.comboBox ->currentText();
	QString pmethod="Adaptive";
	if(!cb.compare(pmethod))
		p1=1;
	else
		p1=0;
	//QString cb2 = ui.comboBox_2 ->currentText();
	QString hnethod="weighted";
	QPalette p = ui.progressBar->palette();
	p.setColor(QPalette::Highlight, Qt::darkBlue);
	ui.progressBar->show();
	std::string path=dir.toLocal8Bit().constData();
	load l(this);
	bool load=l.loadDataSet(path);
	if(load)
	{
		QMessageBox::information(this,tr("new"),tr("Dataset Loaded"));
	}
	else
	{
		QMessageBox::information(this,tr("new"),tr("Failed to Load"));
	}
}
void personReId::myslot3() // target slot
{
	fileName = QFileDialog::getOpenFileName(this, tr("Open Target folder"), "C:/Users/Marjan/Desktop",  tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));
	ShowTarg(fileName);
}
void personReId::setProgValue(int i)
{
	ui.progressBar->setValue(i);
}
void personReId:: myslot4()
{
	if(fileName !=NULL)
	{
		ui.a->show();
	ui.b->show();
	ui.c->show();
	ui.d->show();
	ui.label_3->show();
	ui.label_5->show();
	ui.label_6->show();
	ui.label_7->show();
		QPixmap pix();
		std::string target = fileName.toLocal8Bit().constData();
		background b;
		b.subtract(target);
		imwrite("C:\\Users\\Marjan\\Desktop\\silouhette.jpg",b.img_bw);
		QString qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\silouhette.jpg");
		ui.a->setPixmap(qstr);
		imwrite("C:\\Users\\Marjan\\Desktop\\foreground.jpg",b.finalres);
		 qstr="C:\\Users\\Marjan\\Desktop\\foreground.jpg";
		ui.b->setPixmap(qstr);
	//	imwrite("c:\\users\\marjan\\desktop/lined.png",b.khar);
		part p;
		char * targ= strdup(target.c_str());
		IplImage* img = cvLoadImage ("C:\\Users\\Marjan\\Desktop\\foreground.jpg",1);
		//iplimage* img2 = cvloadimage ("c:\\users\\marjan\\desktop\\4.png");

		// double c=norm(khar,khar2,norm_l2);
		//	p.body=imread("c:\\users\\marjan\\desktop\\3.png");
		int BL=p.torsoLegs(b.img_bw,b.khar); // body legs partition
		int BH=p.bodyHead(b.img_bw,b.khar); //body head partition
		int upsym=p.upsymmetry();
		int downsym=p.downsymmetry();
	CvPoint p1;
		p1.x=0;
		p1.y=BL;
		CvPoint p2;
		p2.x=63;
		p2.y=BL;
		CvPoint p3;
		p3.x=0;
		p3.y=BH;
		CvPoint p4;
		p4.x=63;
		p4.y=BH;
		CvPoint p5;
		p5.x=upsym;
		p5.y=BH;
		CvPoint p6;
		p6.x=upsym;
		p6.y=BL;
		CvPoint p7;
		p7.x=downsym;
		p7.y=BL;
		CvPoint p8;
		p8.x=downsym;
		p8.y=127;

	cvLine(img,p1,p2,CV_RGB( 0, 0, 255 ),1,8,0 );
	cvLine(img,p3,p4,CV_RGB( 0, 0, 255 ),1,8,0 );
	cvLine(img,p5,p6,CV_RGB( 255, 0, 0 ),1,8,0 );
	cvLine(img,p7,p8,CV_RGB( 0, 255, 0 ),1,8,0 );
	cvSaveImage("C:\\Users\\Marjan\\Desktop/line.jpg",img);
		 qstr="C:\\Users\\Marjan\\Desktop/line.jpg";
		ui.c->setPixmap(qstr);
		Rect up;
		up.x=0;
		up.y=BH;
		Size s=p.body.size();
		up.width=s.width;
		up.height=BL-BH;
		Rect down;
		down.x=0;
		down.y=BL;
		down.width=s.width;
		////	p.optimumC2(3);
		down.height=s.height-BL;
		Mat upBody=b.khar(up);
		Mat upMask=b.img_bw(up);
		Mat downMask=b.img_bw(down);
		Mat downBody=b.khar(down);
		imwrite("c:\\users\\marjan\\desktop/finaltest.png",downBody);
		featureExtract f;
		f.upBody=upBody;
		f.downBody=downBody;

		f.Hist(downMask,upMask);
		matching m(f.uhist,f.dhist);
		double sim=m.claculateSim();


			if(m.indexarray[0]<10)
			{
		 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_000"+std::to_string(m.indexarray[0])+"/0001.png");
			}
		else if(m.indexarray[0]<100)
		{
			 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_00"+std::to_string(m.indexarray[0])+"/0001.png");
			}
		else if(m.indexarray[0]<1000)
		{
			qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_0"+std::to_string(m.indexarray[0])+"/0001.png");
		}
		ui.r_1->setPixmap(qstr);
		ui.d->setPixmap(qstr);
		if(m.indexarray[1]<10)
			{
		 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_000"+std::to_string(m.indexarray[1])+"/0001.png");
			}
		else if(m.indexarray[1]<100)
		{
			 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_00"+std::to_string(m.indexarray[1])+"/0001.png");
			}
		else if(m.indexarray[1]<1000)
		{
			qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_0"+std::to_string(m.indexarray[1])+"/0001.png");
		}
		ui.r_2->setPixmap(qstr);
		if(m.indexarray[2]<10)
			{
		 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_000"+std::to_string(m.indexarray[2])+"/0001.png");
			}
		else if(m.indexarray[2]<100)
		{
			 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_00"+std::to_string(m.indexarray[2])+"/0001.png");
			}
		else if(m.indexarray[2]<1000)
		{
			qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_0"+std::to_string(m.indexarray[2])+"/0001.png");
		}
		ui.r_3->setPixmap(qstr);
		if(m.indexarray[3]<10)
			{
		 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_000"+std::to_string(m.indexarray[3])+"/0001.png");
			}
		else if(m.indexarray[3]<100)
		{
			 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_00"+std::to_string(m.indexarray[3])+"/0001.png");
			}
		else if(m.indexarray[3]<1000)
		{
			qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_0"+std::to_string(m.indexarray[3])+"/0001.png");
		}
		ui.r_4->setPixmap(qstr);
		if(m.indexarray[4]<10)
			{
		 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_000"+std::to_string(m.indexarray[4])+"/0001.png");
			}
		else if(m.indexarray[4]<100)
		{
			 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_00"+std::to_string(m.indexarray[4])+"/0001.png");
			}
		else if(m.indexarray[4]<1000)
		{
			qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_0"+std::to_string(m.indexarray[4])+"/0001.png");
		}
		ui.r_5->setPixmap(qstr);
		if(m.indexarray[5]<10)
			{
		 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_000"+std::to_string(m.indexarray[5])+"/0001.png");
			}
		else if(m.indexarray[5]<100)
		{
			 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_00"+std::to_string(m.indexarray[5])+"/0001.png");
			}
		else if(m.indexarray[5]<1000)
		{
			qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_0"+std::to_string(m.indexarray[5])+"/0001.png");
		}
		ui.r_6->setPixmap(qstr);
		if(m.indexarray[6]<10)
			{
		 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_000"+std::to_string(m.indexarray[6])+"/0001.png");
			}
		else if(m.indexarray[6]<100)
		{
			 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_00"+std::to_string(m.indexarray[6])+"/0001.png");
			}
		else if(m.indexarray[6]<1000)
		{
			qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_0"+std::to_string(m.indexarray[6])+"/0001.png");
		}
		ui.r_7->setPixmap(qstr);
		if(m.indexarray[7]<10)
			{
		 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_000"+std::to_string(m.indexarray[7])+"/0001.png");
			}
		else if(m.indexarray[7]<100)
		{
			 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_00"+std::to_string(m.indexarray[7])+"/0001.png");
			}
		else if(m.indexarray[7]<1000)
		{
			qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_0"+std::to_string(m.indexarray[7])+"/0001.png");
		}
		ui.r_8->setPixmap(qstr);
		if(m.indexarray[8]<10)
			{
		 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_000"+std::to_string(m.indexarray[8])+"/0001.png");
			}
		else if(m.indexarray[8]<100)
		{
			 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_00"+std::to_string(m.indexarray[8])+"/0001.png");
			}
		else if(m.indexarray[8]<1000)
		{
			qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_0"+std::to_string(m.indexarray[8])+"/0001.png");
		}

		ui.r_9->setPixmap(qstr);
		if(m.indexarray[9]<10)
			{
		 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_000"+std::to_string(m.indexarray[9])+"/0001.png");
			}
		else if(m.indexarray[9]<100)
		{
			 qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_00"+std::to_string(m.indexarray[9])+"/0001.png");
			}
		else if(m.indexarray[9]<1000)
		{
			qstr = QString::fromStdString("C:\\Users\\Marjan\\Desktop\\multi_shot\\cam_b/person_0"+std::to_string(m.indexarray[9])+"/0001.png");
		}

		ui.r_10->setPixmap(qstr);




		//	double d= m.claculateSim();
		//	part p;
		//	p.fixedpart();
		//	featureextract f;
		//	f.hist();
		//matching

	}

}


personReId::~personReId()
{

}

#ifndef GOD_H
#define GOD_H

#include <QtWidgets/QMainWindow>
#include "ui_god.h"
using namespace std;
class god : public QMainWindow
{
	Q_OBJECT

public:
	std::string target;
	QString dir;
	god(QWidget *parent = 0);
	QString fileName;
	~god();
	QString ShowTarg(QString s);
	void connectLoad(QString s);
	void numberOfTarget();
	void setProgValue(int p);
	int p1;
	int p2;
public slots:
	void myslot();
	void myslot2();
	void myslot3();
	void myslot4();
	
public:
	Ui::godClass ui;
};

#endif // GOD_H

#ifndef WIND2_H
#define WIND2_H

#include <QWidget>
#include "ui_wind2.h"

class wind2 : public QWidget
{
	Q_OBJECT

public:
	wind2(QWidget *parent = 0);
	~wind2();

private:
	Ui::wind2 ui;
};

#endif // WIND2_H

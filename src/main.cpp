#include "bgfg_vibe.h"
#include "god.h"
#include "load.h"
#include "part.h"
#include <qtwidgets/qapplication>
#include <qlabel.h>
#include <opencv2\highgui\highgui.hpp>
#include "background.h"
#include "part.h"
#include "bgfg_vibe.h"
#include "matching.h"
using namespace cv;
using namespace std;
int main(int argc, char *argv[])
{
	
	QApplication a(argc ,argv);
	god w;
//	background b;
//	b.subtract();
	w.show();
	return a.exec();
	/*bgfg_vibe b;
	b.test();*/
	/*matching m;
	m.test();*/
	
}





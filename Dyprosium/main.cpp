#include <QtGui/QApplication>

#include "frmmain.h"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	FrmMain frmMain;
	frmMain.show();

	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

	return a.exec();
}

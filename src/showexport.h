#ifndef SHOWEXPORT_H
#define SHOWEXPORT_H

#include <QDialog>
#include "ui_showexport.h"

class ShowExport : public QDialog {
	Q_OBJECT

public:
	ShowExport(QWidget *parent = 0);
	~ShowExport();

public:
	static int showMessage(QWidget * parent, QString message);

private:
	Ui::ShowExport ui;
};

#endif // SHOWEXPORT_H

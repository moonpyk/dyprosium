#include "showexport.h"

ShowExport::ShowExport(QWidget *parent) : QDialog(parent) {
	ui.setupUi(this);
}

ShowExport::~ShowExport() {}

int ShowExport::showMessage(QWidget * parent, QString message) {
	ShowExport * dialog = new ShowExport(parent);

	dialog->ui.textBrowser->setText(message);

	return dialog->exec();
}
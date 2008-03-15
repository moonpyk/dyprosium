#ifndef SUBNETBEGIN_H
#define SUBNETBEGIN_H

#include <QWizardPage>
#include "ui_subnetbegin.h"

#define SN_WIZ_FIELD_NAME "name"
#define SN_WIZ_FIELD_DESCRIPTION "description"

class SubnetBegin : public QWizardPage {
	Q_OBJECT

public:
	SubnetBegin(QWidget *parent = 0);
	~SubnetBegin();

private:
	Ui::SubnetBegin ui;
};

#endif // SUBNETBEGIN_H

#ifndef SUBNETBEGIN_H
#define SUBNETBEGIN_H

#include <QWizardPage>
#include "ui_wizardsubnetbegin.h"

#define SN_WIZ_FIELD_NAME "name"
#define SN_WIZ_FIELD_DESCRIPTION "description"

class WizardSubnetBegin : public QWizardPage {
	Q_OBJECT

public:
	WizardSubnetBegin(QWidget *parent = 0);
	~WizardSubnetBegin();

private:
	Ui::WizardSubnetBegin ui;
};

#endif // SUBNETBEGIN_H

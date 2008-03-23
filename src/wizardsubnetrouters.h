#ifndef SUBNETROUTERS_H
#define SUBNETROUTERS_H

#include <QWizardPage>
#include "ui_wizardsubnetrouters.h"

#define SN_WIZ_FIELD_ROUTERS "routersList"

class WizardSubnetRouters : public QWizardPage {
	Q_OBJECT

public:
	WizardSubnetRouters(QWidget *parent = 0);
	~WizardSubnetRouters();

private:
	Ui::WizardSubnetRouters ui;
};

#endif // SUBNETROUTERS_H

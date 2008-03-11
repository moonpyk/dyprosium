#ifndef SUBNETROUTERS_H
#define SUBNETROUTERS_H

#include <QWizardPage>
#include "ui_subnetrouters.h"

#define SN_WIZ_FIELD_ROUTERS "routersList"

class SubnetRouters : public QWizardPage {
	Q_OBJECT

public:
	SubnetRouters(QWidget *parent = 0);
	~SubnetRouters();

private:
	Ui::SubnetRouters ui;
};

#endif // SUBNETROUTERS_H

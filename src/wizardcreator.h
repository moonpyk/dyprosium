#ifndef WIZARDS_H
#define WIZARDS_H

#include "subnetbegin.h"
#include "subnetrange.h"
#include "subnetleasetime.h"
#include "subnetrouters.h"
#include "subnetdns.h"

class WizardCreator : public QObject {
	Q_OBJECT

public:
	WizardCreator(QObject * parent = NULL);

public:
	static QWizard * createAddSubnetWizard(QWidget * parent = NULL);

private:
	static QWizardPage * _createAddSubnetBegin(QWidget * parent = NULL);
	static QWizardPage * _createAddSubnetCreateIntro(QWidget * parent = NULL);
	static QWizardPage * _createAddSubnetAddressRange(QWidget * parent = NULL);
	static QWizardPage * _createAddSubnetLeaseTime(QWidget * parent = NULL);
	static QWizardPage * _createAddSubnetRouters(QWidget * parent = NULL);
	static QWizardPage * _createAddSubnetDNS(QWidget * parent = NULL);
};

#endif //WIZARDS_H

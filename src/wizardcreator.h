#ifndef WIZARDS_H
#define WIZARDS_H

#include <QObject>

#include <QLabel>
#include <QVBoxLayout>

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

	static QWizardPage * createAddSubNetBegin(QWidget * parent = NULL);
	static QWizardPage * createAddSubNetCreateIntro(QWidget * parent = NULL);
	static QWizardPage * createAddSubnetAddressRange(QWidget * parent = NULL);
	static QWizardPage * createAddSubnetLeaseTime(QWidget * parent = NULL);
	static QWizardPage * createAddSubnetRouters(QWidget * parent = NULL);
	static QWizardPage * createAddSubnetDNS(QWidget * parent = NULL);
};

#endif //WIZARDS_H

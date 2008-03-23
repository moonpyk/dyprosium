#ifndef SUBNETRANGE_H
#define SUBNETRANGE_H

#define SN_WIZ_FIELD_FIRST_IP_ADDRESS "firstIpAddress"
#define SN_WIZ_FIELD_LAST_IP_ADDRESS "lastIpAddress"
#define SN_WIZ_FIELD_MASK_IP_ADDRESS "maskIpAddress"
#define SN_WIZ_FILED_NETWORK_IP_ADDRESS "networkIpAddress"

#include <QWizardPage>

#include "ui_wizardsubnetrange.h"

class WizardSubnetRange : public QWizardPage {
	Q_OBJECT

public:
	WizardSubnetRange(QWidget *parent = 0);

public:
	Q_PROPERTY(bool isComplete READ isComplete);

	bool isComplete() const;

private:
	bool _checkComplete();
	void _setIsComplete(bool val);

	void _calculateNetworkAddress();
	void _calculateNetworkAddress(int value);
	
private:
	Ui::WizardSubnetRange ui;

	bool _isComplete;

private slots:
	void addresses_textChanged(const QString value);
	void on_spinLength_valueChanged(int value);
};

#endif // SUBNETRANGE_H

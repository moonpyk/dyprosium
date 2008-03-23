#ifndef SUBNETLEASETIME_H
#define SUBNETLEASETIME_H

#include <QWizardPage>
#include "ui_wizardsubnetleasetime.h"

#define SN_WIZ_FIELD_LEASE_TIME "leaseTime"

class WizardSubnetLeaseTime : public QWizardPage {
	Q_OBJECT

public:
	WizardSubnetLeaseTime(QWidget *parent = 0);
	~WizardSubnetLeaseTime();

public:
	virtual bool isComplete() const;

private:
	void _setCompleted(bool val);

	void _checkCompleted();

private slots:
	void on_leaseTimeEdit_valueChanged();

private:
	bool _isComplete;

	Ui::WizardSubnetLeaseTime ui;
};

#endif // SUBNETLEASETIME_H

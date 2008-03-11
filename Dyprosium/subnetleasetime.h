#ifndef SUBNETLEASETIME_H
#define SUBNETLEASETIME_H

#include <QWizardPage>
#include "ui_subnetleasetime.h"

#define SN_WIZ_FIELD_LEASE_TIME "leaseTime"

class SubnetLeaseTime : public QWizardPage {
	Q_OBJECT

public:
	SubnetLeaseTime(QWidget *parent = 0);
	~SubnetLeaseTime();

public:
	virtual bool isComplete() const;

private:
	void _setCompleted(bool val);

	void _checkCompleted();

private slots:
	void on_leaseTimeEdit_valueChanged();

private:
	bool _isComplete;

	Ui::SubnetLeaseTime ui;
};

#endif // SUBNETLEASETIME_H

#ifndef SUBNETDNS_H
#define SUBNETDNS_H

#include <QWizardPage>

#include <QHostInfo>

#include "ui_subnetdns.h"

#define SN_WIZ_FIELD_PARENT_DOMAIN "parentDomain"
#define SN_WIZ_FIELD_DNSLIST "dnsList"

class WizardSubnetDNS : public QWizardPage {
	Q_OBJECT

public:
	WizardSubnetDNS(QWidget *parent = 0);
	~WizardSubnetDNS();

private:
	Ui::WizardSubnetDNS ui;

private slots:
	void on_lineDNSSolve_textChanged(const QString value);
	void on_btnResolve_clicked();

	void appendDNSLookupResult(QHostInfo info);
};

#endif // SUBNETDNS_H

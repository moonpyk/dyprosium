#include "wizardsubnetdns.h"

WizardSubnetDNS::WizardSubnetDNS(QWidget *parent) : QWizardPage(parent)
{
	ui.setupUi(this);

	setTitle(tr("Noms de domaine et serveurs DNS"));
	setSubTitle(
		tr("DNS (Domain Name System) mappe et traduit les noms "
		"de domaines utilisés par les clients sur le réseau."
		));

	registerField(SN_WIZ_FIELD_DNSLIST, ui.dnsList, "stringList", "stringListChanged");
	registerField(SN_WIZ_FIELD_PARENT_DOMAIN, ui.lineParentDomain);

	ui.spinnerWidget->setLinesWidth(1);
	ui.spinnerWidget->setInsetFactor(0.5);
	ui.spinnerWidget->setVisible(false);
}

WizardSubnetDNS::~WizardSubnetDNS() { }

void WizardSubnetDNS::on_btnResolve_clicked() {
	QHostInfo::lookupHost(ui.lineDNSSolve->text(), this, SLOT(appendDNSLookupResult(QHostInfo)));

	ui.spinnerWidget->setVisible(true);
	ui.btnResolve->setEnabled(false);
}

void WizardSubnetDNS::on_lineDNSSolve_textChanged(const QString value) {
	ui.btnResolve->setEnabled(value.length() > 0);
}

void WizardSubnetDNS::appendDNSLookupResult(QHostInfo info) {
	if(info.error() == QHostInfo::NoError) {
		ui.dnsList->setCurrentString(info.addresses()[0].toString());
	}

	ui.spinnerWidget->setVisible(false);
	ui.btnResolve->setEnabled(true);
}

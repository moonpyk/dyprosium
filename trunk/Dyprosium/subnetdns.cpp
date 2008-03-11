#include "subnetdns.h"

SubnetDNS::SubnetDNS(QWidget *parent) : QWizardPage(parent)
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

SubnetDNS::~SubnetDNS() { }

void SubnetDNS::on_btnResolve_clicked() {
	QHostInfo::lookupHost(ui.lineDNSSolve->text(), this, SLOT(appendDNSLookupResult(QHostInfo)));

	ui.spinnerWidget->setVisible(true);
	ui.btnResolve->setEnabled(false);
}

void SubnetDNS::on_lineDNSSolve_textChanged(const QString value) {
	ui.btnResolve->setEnabled(value.length() > 0);
}

void SubnetDNS::appendDNSLookupResult(QHostInfo info) {
	if(info.error() == QHostInfo::NoError) {
		ui.dnsList->setCurrentString(info.addresses()[0].toString());
	}

	ui.spinnerWidget->setVisible(false);
	ui.btnResolve->setEnabled(true);
}

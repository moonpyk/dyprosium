#include "wizardcreator.h"

WizardCreator::WizardCreator (QObject * parent /*= NULL*/) : QObject(parent) {} 

QWizardPage * WizardCreator::createAddSubNetCreateIntro (QWidget * parent /*= NULL*/) {
	QWizardPage * retPage = new QWizardPage(parent);

	retPage->setTitle(tr("Introduction"));

	QLabel *introLabel = new QLabel(
		tr("This wizard will help you create a new subnetwork on your DHCP server."
		"This subnetwork will permit to distribute IP addresses to the network"
		));

	introLabel->setWordWrap(true);

	QLabel * nextLabel = new QLabel(
		tr("Click Next to continue."));

	nextLabel->setWordWrap(true);

	QVBoxLayout * layout = new QVBoxLayout;
	layout->addWidget(introLabel);
	layout->addWidget(nextLabel);

	retPage->setLayout(layout);

	return retPage;
}

QWizardPage * WizardCreator::createAddSubNetBegin(QWidget * parent /*= NULL*/) {
	return new SubnetBegin(parent);
}

QWizardPage * WizardCreator::createAddSubnetAddressRange (QWidget * parent /*= NULL*/) {
	return new SubnetRange(parent);
}

QWizardPage * WizardCreator::createAddSubnetLeaseTime(QWidget * parent /*= NULL*/) {
	return new SubnetLeaseTime(parent);
}

QWizardPage * WizardCreator::createAddSubnetRouters(QWidget * parent /*= NULL*/) {
	return new SubnetRouters(parent);
}

QWizardPage * WizardCreator::createAddSubnetDNS(QWidget * parent /*= NULL*/) {
	return new SubnetDNS(parent);
}

QWizard * WizardCreator::subnetWizard(QWidget * parent) {
	QWizard * wizard = new QWizard(parent);

	wizard->addPage(createAddSubNetCreateIntro(wizard));
	wizard->addPage(createAddSubNetBegin(wizard));
	wizard->addPage(createAddSubnetAddressRange(wizard));
	wizard->addPage(createAddSubnetLeaseTime(wizard));
	wizard->addPage(createAddSubnetRouters(wizard));
	wizard->addPage(createAddSubnetDNS(wizard));

	wizard->setWindowTitle(tr("Assistant de création de nouvelle étendue"));

	return wizard;
}
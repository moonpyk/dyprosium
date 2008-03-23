#include "wizardcreator.h"

WizardCreator::WizardCreator (QObject * parent /*= NULL*/) : QObject(parent) {} 

QWizardPage * WizardCreator::createAddSubNetCreateIntro (QWidget * parent /*= NULL*/) {
	QWizardPage * retPage = new QWizardPage(parent);

	retPage->setTitle(tr("Introduction"));

	QLabel *introLabel = new QLabel(
		tr("Cet assistant va vous aider a cr�er un sous-r�seau dans la configuration de votre serveur DHCP."
		"Ce sous-r�seau va permettre la distribution d'adresses IP sur le r�seau"
		));

	introLabel->setWordWrap(true);

	QLabel * nextLabel = new QLabel(
		tr("Cliquez sur suivant pour continuer"));

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

QWizard * WizardCreator::createAddSubnetWizard(QWidget * parent) {
	QWizard * wizard = new QWizard(parent);

	wizard->addPage(createAddSubNetCreateIntro(wizard));
	wizard->addPage(createAddSubNetBegin(wizard));
	wizard->addPage(createAddSubnetAddressRange(wizard));
	wizard->addPage(createAddSubnetLeaseTime(wizard));
	wizard->addPage(createAddSubnetRouters(wizard));
	wizard->addPage(createAddSubnetDNS(wizard));

	wizard->setWindowTitle(tr("Assistant de cr�ation de nouvelle �tendue"));

	return wizard;
}
#include "wizardcreator.h"

#include <QLabel>
#include <QVBoxLayout>

WizardCreator::WizardCreator (QObject * parent /*= NULL*/) : QObject(parent) {} 

QWizardPage * WizardCreator::_createAddSubnetCreateIntro (QWidget * parent /*= NULL*/) {
	QWizardPage * retPage = new QWizardPage(parent);

	retPage->setTitle(tr("Introduction"));

	QLabel *introLabel = new QLabel(
		tr("Cet assistant va vous aider a créer un sous-réseau dans la configuration de votre serveur DHCP."
		"Ce sous-réseau va permettre la distribution d'adresses IP sur le réseau"
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

QWizardPage * WizardCreator::_createAddSubnetBegin(QWidget * parent /*= NULL*/) {
	return new WizardSubnetBegin(parent);
}

QWizardPage * WizardCreator::_createAddSubnetAddressRange (QWidget * parent /*= NULL*/) {
	return new WizardSubnetRange(parent);
}

QWizardPage * WizardCreator::_createAddSubnetLeaseTime(QWidget * parent /*= NULL*/) {
	return new WizardSubnetLeaseTime(parent);
}

QWizardPage * WizardCreator::_createAddSubnetRouters(QWidget * parent /*= NULL*/) {
	return new WizardSubnetRouters(parent);
}

QWizardPage * WizardCreator::_createAddSubnetDNS(QWidget * parent /*= NULL*/) {
	return new WizardSubnetDNS(parent);
}

QWizard * WizardCreator::createAddSubnetWizard(QWidget * parent) {
	QWizard * wizard = new QWizard(parent);

	wizard->addPage(_createAddSubnetCreateIntro(wizard));
	wizard->addPage(_createAddSubnetBegin(wizard));
	wizard->addPage(_createAddSubnetAddressRange(wizard));
	wizard->addPage(_createAddSubnetLeaseTime(wizard));
	wizard->addPage(_createAddSubnetRouters(wizard));
	wizard->addPage(_createAddSubnetDNS(wizard));

	wizard->setWindowTitle(tr("Assistant de création de nouvelle étendue"));

	return wizard;
}
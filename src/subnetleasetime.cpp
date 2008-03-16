#include "subnetleasetime.h"

SubnetLeaseTime::SubnetLeaseTime(QWidget *parent) : QWizardPage(parent) {
	ui.setupUi(this);

	setTitle(tr("Durée du bail"));

	setSubTitle(tr(
		"La durée du bail doit théoriquement être égale au temps moyen durant "
		"lequel l'ordinateur est connecté au même réseau physique. "
		));

	_isComplete = false;
	
	registerField(SN_WIZ_FIELD_LEASE_TIME, ui.leaseTimeEdit, "valueString", "valueChanged");
	
	ui.leaseTimeEdit->valueString();

	_checkCompleted();
}

SubnetLeaseTime::~SubnetLeaseTime() {}

// Properties

bool SubnetLeaseTime::isComplete() const {
	return _isComplete;
}

// Private methods

void SubnetLeaseTime::_setCompleted(bool val) {
	if(_isComplete != val) {
		_isComplete = val;

		emit completeChanged();
	}
}

void SubnetLeaseTime::_checkCompleted() {
	_setCompleted(ui.leaseTimeEdit->valueString() != "0");
}

// Private slots

void SubnetLeaseTime::on_leaseTimeEdit_valueChanged() {
	_checkCompleted();
}
#include "subnetrange.h"
#include "iptools.h"

SubnetRange::SubnetRange(QWidget *parent) : QWizardPage(parent), _isComplete(false) {
	ui.setupUi(this);

	this->setTitle(tr("Plage d'adresses IP"));
	this->setSubTitle(tr("Vous définissez la plage d'adresses en identifiant un jeu d'adresses IP consecutives."));

	registerField(SN_WIZ_FIELD_FIRST_IP_ADDRESS, ui.lineFirstAddress);
	registerField(SN_WIZ_FIELD_LAST_IP_ADDRESS, ui.lineLastAddress);
	registerField(SN_WIZ_FIELD_MASK_IP_ADDRESS, ui.lineMask);
	registerField(SN_WIZ_FILED_NETWORK_IP_ADDRESS, ui.lineNetworkAddress);
	
	QObject::connect(ui.lineFirstAddress, SIGNAL(textChanged(QString)), this, SLOT(addresses_textChanged(QString)));
	QObject::connect(ui.lineLastAddress, SIGNAL(textChanged(QString)), this, SLOT(addresses_textChanged(QString)));
}

bool SubnetRange::isComplete() const {
	return _isComplete;
}

void SubnetRange::_setIsComplete(bool val) {
	if(val != _isComplete) {
		_isComplete = val;

		emit completeChanged();
	}
}

void SubnetRange::on_spinLength_valueChanged(int value) {
	_calculateNetworkAddress(value);
}

void SubnetRange::addresses_textChanged(const QString value) {
	_calculateNetworkAddress();
	_setIsComplete(_checkComplete());
}

void SubnetRange::_calculateNetworkAddress() {
	_calculateNetworkAddress(ui.spinLength->value());
}

void SubnetRange::_calculateNetworkAddress(int value) {
	ui.lineMask->setText(maskNumberToIPv4Netmask(value));

	ui.lineNetworkAddress->setText(
		calcutateNetworkAdress(ui.lineFirstAddress->text(), ui.lineMask->text())
	);
}

bool SubnetRange::_checkComplete() {
	QString firstAddress	= ui.lineFirstAddress->text();
	QString lastAddress		= ui.lineLastAddress->text();

	QHostAddress addressChecker;

	bool complete = true;

	complete &= addressChecker.setAddress(firstAddress);
	complete &= addressChecker.setAddress(lastAddress);
	complete &= isOnSameSubnet(firstAddress, lastAddress);

	return complete;
}

#include "dhsubnetwork.h"

#pragma region DHSubNetworkExclusion Class

// -- DHSubNetworkExclusion 

QHostAddress DHSubNetworkExclusion::startAddress() const {
	return _startAddress;
}

void DHSubNetworkExclusion::setStartAddress(QHostAddress val) {
	_startAddress = val;
}

QHostAddress DHSubNetworkExclusion::endAddress() const {
	return _endAddress;
}

void DHSubNetworkExclusion::setEndAddress(QHostAddress val) {
	_endAddress = val;
}

DHExclusionType DHSubNetworkExclusion::type() const {
	return _type;
}

void DHSubNetworkExclusion::setType(DHExclusionType val) {
	_type = val;
}

void DHSubNetworkExclusion::flushConfiguration (QXmlStreamWriter * stream) {
	stream->writeEmptyElement("Exclusion");
	flushBaseConfInformations(stream);

	stream->writeAttribute("Type", QString::number(_type));

	switch(_type) {
	case SimpleAdress:
		stream->writeAttribute("Address", _startAddress.toString());
		break;

	case Range:
		stream->writeAttribute("StartAddress", _startAddress.toString());
		stream->writeAttribute("EndAddress", _endAddress.toString());
	    break;
	}
}

#pragma endregion

#pragma region DHSubNetworkReservation Class

// -- DHSubNetworkReservation

DHSubNetworkReservation::DHSubNetworkReservation() {
	_treeWidgetItem = NULL;

	setName("");

	this->_address		= "";
	this->_macAddress	= "";
	this->_activated	= "";

	_initializeTreeWidgetItem();
}

DHSubNetworkReservation::DHSubNetworkReservation(QString name, QString address, QString macAddress, bool activated /*= true*/) {
	_treeWidgetItem = NULL;

	setName(name);

	this->_address		= address;
	this->_macAddress	= macAddress;
	this->_activated	= activated;

	_initializeTreeWidgetItem();
}

DHSubNetworkReservation::~DHSubNetworkReservation() {
	delete _treeWidgetItem;
}

void DHSubNetworkReservation::flushConfiguration (QXmlStreamWriter * stream) {
	stream->writeStartElement("Reservation");
	flushBaseConfInformations(stream);

	stream->writeAttribute("Address", _address);
	stream->writeAttribute("MacType", _macAddressType);
	stream->writeAttribute("MacAddress", _macAddress);
	stream->writeAttribute("Activated", QString::number(_activated));

	// Options
	if(_options.count() > 0) {
		stream->writeStartElement("Options");

		foreach(DHOptionDuet option, _options) {
			option.flushConfiguration(stream);
		}

		stream->writeEndElement();
	}

	stream->writeEndElement();
}

void DHSubNetworkReservation::setName(QString val) {
	DHConfigurationBase::setName(val);

	_bindTreeWidgetItemName();
}

QString DHSubNetworkReservation::address() const {
	return _address;
}

void DHSubNetworkReservation::setAddress(QString val) {
	_address = val;

	_bindTreeWidgetItemName();
}

QString DHSubNetworkReservation::macAddress() const {
	return _macAddress;
}

void DHSubNetworkReservation::setMacAddress(QString val) {
	_macAddress = val;
}

QString DHSubNetworkReservation::macAddressType() const {
	return _macAddressType;
}

void DHSubNetworkReservation::setMacAddressType(QString type) {
	_macAddressType = type;
}

bool DHSubNetworkReservation::activated() const {
	return _activated;
}

void DHSubNetworkReservation::setActivated(bool val) {
	_activated = val;
}

QList<DHOptionDuet> * DHSubNetworkReservation::options() {
	return &_options;
}

QTreeWidgetItem * DHSubNetworkReservation::treeWidgetItem() const {
	return _treeWidgetItem;
}

// Private methods

void DHSubNetworkReservation::_initializeTreeWidgetItem() {
	_treeWidgetItem = new QTreeWidgetItem(QStringList());
	_treeWidgetItem->setIcon(0, QIcon(":/images/Resources/computer.png"));
	_treeWidgetItem->setItemRole(TREE_ROLE_SUBNET_RESERVATION_OPTION);
	_treeWidgetItem->setDataPtr(this);

	_bindTreeWidgetItemName();
}

void DHSubNetworkReservation::_bindTreeWidgetItemName() {
	if(_treeWidgetItem) {
		_treeWidgetItem->setText(0, tr("%1 [%2]").arg(this->name()).arg(this->address()));
	}
}

#pragma endregion

// -- DHSubNetwork

// CTor

DHSubNetwork::DHSubNetwork(QString name, QString networkAddressString, QString netMaskString, QString startAddressString, QString endAddressString) {
	setName(name);

	this->_networkAddress	= QHostAddress(networkAddressString);
	this->_netMask			= QHostAddress(netMaskString);
	this->_startAddress		= QHostAddress(startAddressString);
	this->_endAddress		= QHostAddress(endAddressString);

	_initializeTreeWidgetItems(networkAddressString, name);
}

// DTor

DHSubNetwork::~DHSubNetwork() {
	foreach (DHSubNetworkExclusion * exclusion, _exclusions) {
		delete exclusion;
	}

	foreach (DHSubNetworkReservation * reservation, _reservations) {
		delete reservation;
	}

	delete _subnetExclusionsItemWidget;
	delete _subnetReservationsItemWidget;
	delete _subnetOptionsItemWidget;

	delete _subnetItemWidget;
}

// Properties

QHostAddress DHSubNetwork::networkAddress() const {
	return _networkAddress;
}

void DHSubNetwork::setNetworkAddress(QHostAddress val) {
	_networkAddress = val;
}

QHostAddress DHSubNetwork::netMask() const {
	return _netMask;
}

void DHSubNetwork::setNetMask(QHostAddress val) {
	_netMask = val;
}

QHostAddress DHSubNetwork::startAddress() const {
	return _startAddress;
}

void DHSubNetwork::setStartAddress(QHostAddress val) {
	_startAddress = val;
}

QHostAddress DHSubNetwork::endAddress() const {
	return _endAddress;
}

void DHSubNetwork::setEndAddress(QHostAddress val) {
	_endAddress = val;
}

QString DHSubNetwork::leaseTime() const {
	return _leaseTime;
}

void DHSubNetwork::setLeaseTime(QString val) {
	_leaseTime = val;
}

QList<DHSubNetworkReservation *> DHSubNetwork::reservations() const {
	return _reservations;
}

QList<DHOptionDuet> * DHSubNetwork::options() {
	return &_options;
}

// Public methods

void DHSubNetwork::addSubNetworkExclusion (DHSubNetworkExclusion * exclusion) {
	if(exclusion->parent() != this) {
		exclusion->setParent(this);
	}

	_exclusions.append(exclusion);
}

bool DHSubNetwork::removeSubNetworkSubNetworkExclusion (DHSubNetworkExclusion * exclusion) {
	return _exclusions.removeAll(exclusion);
}

void DHSubNetwork::addSubNetworkReservation (DHSubNetworkReservation * reservation) {
	if(reservation->parent() != this) {
		reservation->setParent(this);
	}

	_subnetReservationsItemWidget->addChild(reservation->treeWidgetItem());

	_reservations.append(reservation);
}

bool DHSubNetwork::removeSubNetworkReservation (DHSubNetworkReservation * reservation) {
	if(_reservations.contains(reservation)) {
		QTreeWidgetItem * widget = reservation->treeWidgetItem();

		if(widget->parent() == _subnetReservationsItemWidget) {
			_subnetReservationsItemWidget->removeChild(widget);
		}

		return _reservations.removeAll(reservation);
	}

	return false;
}

void DHSubNetwork::flushConfiguration (QXmlStreamWriter * stream) {
	stream->writeStartElement("SubNetwork");

	flushBaseConfInformations(stream);

	stream->writeAttribute("NetworkAddress", _networkAddress.toString());
	stream->writeAttribute("Mask", _netMask.toString());
	stream->writeAttribute("StartAddress", _startAddress.toString());
	stream->writeAttribute("EndAddress", _endAddress.toString());
	stream->writeAttribute("LeaseTime", _leaseTime);

	// Exclusions
	if (_exclusions.count() > 0) {
		stream->writeStartElement("Exclusions");

		foreach(DHSubNetworkExclusion * reservation, _exclusions) {
			reservation->flushConfiguration(stream);
		}

		stream->writeEndElement();
	}

	// Reservations
	if(_reservations.count() > 0) {
		stream->writeStartElement("Reservations");

		foreach(DHSubNetworkReservation * reservation, _reservations) {
			reservation->flushConfiguration(stream);
		}

		stream->writeEndElement();
	}

	// Options
	if(_options.count() > 0) {
		stream->writeStartElement("Options");

		foreach (DHOptionDuet option, _options) {
			option.flushConfiguration(stream);
		}

		stream->writeEndElement();
	}

	stream->writeEndElement();
}

QTreeWidgetItem * DHSubNetwork::subnetItemWidget() {
	return _subnetItemWidget;
}

QTreeWidgetItem * DHSubNetwork::subnetOptionsItemWidget() {
	return _subnetOptionsItemWidget;
}

QTreeWidgetItem * DHSubNetwork::subnetReservationsItemWidget() {
	return _subnetReservationsItemWidget;
}

void DHSubNetwork::_initializeTreeWidgetItems(QString networkAddressString, QString name) {
	_subnetItemWidget = new QTreeWidgetItem(QStringList());
	_subnetItemWidget->setText(0, tr("Range [%1] %2").arg(networkAddressString).arg(name));
	_subnetItemWidget->setIcon(0, QIcon(":/images/Resources/world.png"));
	_subnetItemWidget->setItemRole(TREE_ROLE_SUBNET);
	_subnetItemWidget->setDataPtr(this);

#ifdef SUBNET_EXCLUSIONS_SUPPORT
	_subnetExclusionsItemWidget = new QTreeWidgetItem(_subnetItemWidget);
	_subnetExclusionsItemWidget->setText(0, tr("Address exclusions"));
	_subnetExclusionsItemWidget->setIcon(0, QIcon(":/images/Resources/folder_delete.png"));
	_subnetExclusionsItemWidget->setItemRole(TREE_ROLE_SUBNET_EXCLUSIONS);
#else
	_subnetExclusionsItemWidget = NULL;
#endif

	_subnetReservationsItemWidget = new QTreeWidgetItem(_subnetItemWidget);
	_subnetReservationsItemWidget->setText(0, tr("Address reservations"));
	_subnetReservationsItemWidget->setIcon(0, QIcon(":/images/Resources/folder_heart.png"));
	_subnetReservationsItemWidget->setItemRole(TREE_ROLE_SUBNET_RESERVATIONS);

	_subnetOptionsItemWidget = new QTreeWidgetItem(_subnetItemWidget);
	_subnetOptionsItemWidget->setText(0, tr("Subnet options"));
	_subnetOptionsItemWidget->setIcon(0, QIcon(":/images/Resources/folder_wrench.png"));
	_subnetOptionsItemWidget->setItemRole(TREE_ROLE_SUBNET_OPTIONS);
}


#ifndef DHSUBNETWORK_H
#define DHSUBNETWORK_H

#include "dhconfbase.h"
#include "dhconfiguration.h"

#include <QTreeWidgetItem>

#include <QHostAddress>
#include <QTime>

class DHSubNetwork;
class DHConfiguration;

#pragma region DHSubNetworkExclusion Class

class DHSubNetworkExclusion : public DHConfigurationBase {
	Q_OBJECT

public:
	Q_PROPERTY(QHostAddress startAddress READ startAddress WRITE setStartAddress)
	Q_PROPERTY(QHostAddress endAddress READ endAddress WRITE setEndAddress)
	Q_PROPERTY(DHExclusionType type READ type WRITE setType)
	
	QHostAddress startAddress() const;
	void setStartAddress(QHostAddress val);
	
	QHostAddress endAddress() const;
	void setEndAddress(QHostAddress val);

	DHExclusionType type() const;
	void setType(DHExclusionType val);

	inline DHSubNetwork * parentSubnetwork() { return qobject_cast<DHSubNetwork *>(parent()); }

public:
	void flushConfiguration(QXmlStreamWriter * stream);

private:
	QHostAddress _startAddress;
	QHostAddress _endAddress;

	DHExclusionType _type;
};

#pragma endregion

#pragma region DHSubNetworkReservation Class

class DHSubNetworkReservation : public DHConfigurationBase {
	Q_OBJECT

public:
	DHSubNetworkReservation();
	DHSubNetworkReservation(QString name, QString address, QString macAddress, QString macType, bool activated = true);
	~DHSubNetworkReservation();

public:
	Q_PROPERTY(QString address READ address WRITE setAddress);
	Q_PROPERTY(QString macAddress READ macAddress WRITE setMacAddress);
	Q_PROPERTY(QString macAddressType READ macAddressType WRITE setMacAddressType);
	Q_PROPERTY(bool activated READ activated WRITE setActivated);

	Q_PROPERTY(QList<DHOptionDuet> * options READ options);

	virtual void setName(QString val);

	QString address() const;
	void setAddress(QString val);

	QString macAddress() const;
	void setMacAddress(QString val);

	QString macAddressType() const;
	void setMacAddressType(QString type);

	bool activated() const;
	void setActivated(bool val);

	QList<DHOptionDuet> * options();

	QTreeWidgetItem * treeWidgetItem() const;

	inline DHSubNetwork * parentSubnetwork() { return qobject_cast<DHSubNetwork *>(parent()); }

public:
	void flushConfiguration(QXmlStreamWriter * stream);

private:
	void _initializeTreeWidgetItem();
	void _bindTreeWidgetItemName();
private:
	QString _address;
	QString _macAddress;
	QString _macAddressType;

	QList<DHOptionDuet> _options;

	bool _activated;

	QTreeWidgetItem * _treeWidgetItem;
};

#pragma endregion

#pragma region DHSubNetwork Class

class DHSubNetwork : public DHConfigurationBase {
	Q_OBJECT

public:
	DHSubNetwork(QString name, QString networkAddressString, QString netMaskString, QString startAddressString, QString endAddressString);
	~DHSubNetwork();
	
public:
	// Properties
	Q_PROPERTY(QHostAddress networkAddress READ networkAddress WRITE setNetworkAddress);
	Q_PROPERTY(QHostAddress netMask READ netMask WRITE setNetMask);
	Q_PROPERTY(QHostAddress startAddress READ startAddress WRITE setStartAddress);
	Q_PROPERTY(QHostAddress endAddress READ endAddress WRITE setEndAddress);
	Q_PROPERTY(QString leaseTime READ leaseTime WRITE setLeaseTime);

	Q_PROPERTY(QList<DHSubNetworkReservation *> reservations READ reservations);
	Q_PROPERTY(QList<DHOptionDuet> * options READ options);

	QHostAddress networkAddress() const;
	void setNetworkAddress(QHostAddress val);

	QHostAddress netMask() const;
	void setNetMask(QHostAddress val);

	QHostAddress startAddress() const;
	void setStartAddress(QHostAddress val);

	QHostAddress endAddress() const;
	void setEndAddress(QHostAddress val);

	QString leaseTime() const;
	void setLeaseTime(QString val);

	QList<DHOptionDuet> * options();

	QList<DHSubNetworkReservation *> reservations() const;

	QTreeWidgetItem * subnetItemWidget();
	QTreeWidgetItem * subnetOptionsItemWidget();
	QTreeWidgetItem * subnetReservationsItemWidget();

	inline DHConfiguration * parentConfiguration() { return qobject_cast<DHConfiguration *>(parent()); }

public:
	//Network Exclusion / Reservation
	void addSubNetworkExclusion(DHSubNetworkExclusion * exclusion); 
	bool removeSubNetworkSubNetworkExclusion(DHSubNetworkExclusion * exclusion);

	void addSubNetworkReservation(DHSubNetworkReservation * reservation);
	bool removeSubNetworkReservation(DHSubNetworkReservation * reservation);

public:
	void flushConfiguration(QXmlStreamWriter * stream);

private:
	void _initializeTreeWidgetItems(QString networkAddressString, QString name);

private:
	QHostAddress _networkAddress;
	QHostAddress _netMask;

	QHostAddress _startAddress;
	QHostAddress _endAddress;

	QList<DHSubNetworkExclusion *> _exclusions;
	QList<DHSubNetworkReservation *> _reservations;

	QList<DHOptionDuet> _options;

	QTreeWidgetItem * _subnetItemWidget;

	QTreeWidgetItem * _subnetExclusionsItemWidget;
	QTreeWidgetItem * _subnetReservationsItemWidget;
	QTreeWidgetItem * _subnetOptionsItemWidget;

	QString _leaseTime;
};

#pragma endregion

Q_DECLARE_METATYPE(DHSubNetwork *);
Q_DECLARE_METATYPE(DHSubNetworkExclusion *);
Q_DECLARE_METATYPE(DHSubNetworkReservation *);

#endif //DHSUBNETWORK_H
#ifndef DHCPCONF_H
#define DHCPCONF_H

#include <QTreeWidgetItem>

#include "dhconfbase.h"
#include "dhsubnetwork.h"

class DHSubNetwork;
class DHSubNetworkExclusion;
class DHSubNetworkReservation;

class DHConfiguration : public DHConfigurationBase {
	Q_OBJECT

public: 
	DHConfiguration(QString fileName, QString name);
	~DHConfiguration();

public:
	Q_PROPERTY(QString fileName READ name WRITE setFileName);
	Q_PROPERTY(QTreeWidgetItem* rootItemWidget READ rootItemWidget);
	Q_PROPERTY(QList<DHSubNetwork *>  subNetworks READ subNetworks);
	Q_PROPERTY(QList<DHOptionDuet> * options READ options);

	QString fileName() const;
	void setFileName(QString val);

	QTreeWidgetItem * rootItemWidget();
	QTreeWidgetItem * globalOptionsItemWidget();

	QList<DHSubNetwork *> subNetworks();

	QList<DHOptionDuet> * options();

public:
	// Subnets
	bool addSubNetwork(DHSubNetwork * subnet);
	bool removeSubNetwork(DHSubNetwork * subnet);

	QString xmlConfiguration();
	void flushConfiguration(QXmlStreamWriter * stream);

private:
	void _initializeTreeWidgetItems();

private:
	QString _fileName;

	QTreeWidgetItem * _rootItemWidget;

	QTreeWidgetItem * _globalOptionsItemWidget;

	QList<DHSubNetwork *> _subNetworks;
	QList<DHOptionDuet> _options;
};

Q_DECLARE_METATYPE(DHConfiguration *);

#endif DHCPCONF_H
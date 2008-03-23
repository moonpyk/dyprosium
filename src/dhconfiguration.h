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
	DHConfiguration(const QString& name = "");
	~DHConfiguration();

public:
	Q_PROPERTY(QTreeWidgetItem* rootItemWidget READ rootItemWidget);
	Q_PROPERTY(QList<DHSubNetwork *>  subNetworks READ subNetworks);
	Q_PROPERTY(QList<DHOptionDuet> * options READ options);
	Q_PROPERTY(QString fileName READ fileName WRITE setFileName);

	virtual void setName(QString val);

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
	void writeXmlConfiguration(QIODevice * device);

	void flushConfiguration(QXmlStreamWriter * stream);

private:
	void _initializeTreeWidgetItems();
	void _bindTreeWidgetItemName();	

private:
	QTreeWidgetItem * _rootItemWidget;

	QTreeWidgetItem * _globalOptionsItemWidget;

	QList<DHSubNetwork *> _subNetworks;
	QList<DHOptionDuet> _options;

	QString _fileName;
};

Q_DECLARE_METATYPE(DHConfiguration *);

#endif DHCPCONF_H
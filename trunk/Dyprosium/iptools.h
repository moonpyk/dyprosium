#ifndef IPTOOLS_H
#define IPTOOLS_H

#include <QHostAddress>

#define arraySizeEquals(array1, array2, size) \
	((array1.count() == array2.count()) && array1.count() == size)

QString maskNumberToIPv4Netmask(uint netmask);

QString calcutateNetworkAdress(QHostAddress ip, QHostAddress mask);
QString calcutateNetworkAdress(QString firstIp, QString mask);

QStringList parseIpAddress(QString address);

bool isAddressValid(QString address);

bool isOnSameSubnet(QString first, QString second);

#endif // IPTOOLS_H

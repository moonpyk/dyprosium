#include "iptools.h"

#include <QStringList>

#define RETVAL_ERROR_STRING "UNKNOWN"

QStringList parseIpAddress(QString address) {
	return address.split('.');
}

int * parseIpAddressToIntArray(QString address) {
	int * retval = new int[4];
	
	return retval;
}

QString maskNumberToIPv4Netmask (uint netmask) {
	int retVal[] = { 0, 0, 0, 0 };
	int pos = 0;

	if (netmask <= 32) {
		while (netmask > 0) {
			if (netmask >= 8) {
				retVal[pos]		= 255;
				netmask			= netmask - 8;
				++pos;

			} else {
				retVal[pos] = 255 - ( 255 >> netmask );
				netmask = 0;
			}
		}

		return QString("%1.%2.%3.%4")
			.arg(retVal[0])
			.arg(retVal[1])
			.arg(retVal[2])
			.arg(retVal[3]);
	}

	return RETVAL_ERROR_STRING;
}

QString calcutateNetworkAdress(QHostAddress ip, QHostAddress mask) {
	return calcutateNetworkAdress(ip.toString(), mask.toString());
}

QString calcutateNetworkAdress(QString ip, QString mask) {
	QStringList ipStringArray	= parseIpAddress(ip);
	QStringList maskStringArray = parseIpAddress(mask);

	if(arraySizeEquals(ipStringArray, maskStringArray, 4)) {
		int ipArray[]		=  { 0, 0, 0, 0 };
		int maskArray[]		=  { 0, 0, 0, 0 };
		
		for (int i = 0 ; i < 4 ; i++) {
			bool success;

			ipArray[i] = ipStringArray[i].toInt(&success);

			if(!success) {
				return RETVAL_ERROR_STRING;
			}

			maskArray[i] = maskStringArray[i].toInt(&success);

			if(!success) {
				return RETVAL_ERROR_STRING;
			}
		}

		int retVal[] = { 0, 0, 0, 0 };

		for (int i = 0; i < 4 ; i++) {
			retVal[i] = ipArray[i] & maskArray[i];
		}

		return QString("%1.%2.%3.%4")
			.arg(retVal[0])
			.arg(retVal[1])
			.arg(retVal[2])
			.arg(retVal[3]);
	}

	return RETVAL_ERROR_STRING;
}

bool isOnSameSubnet(QString first, QString second) {
	QStringList firstStringArray	= parseIpAddress(first);
	QStringList secondStringArray	= parseIpAddress(second);

	firstStringArray.removeLast();
	secondStringArray.removeLast();

	if(arraySizeEquals(firstStringArray, secondStringArray, 3)) {
		return (firstStringArray == secondStringArray);
	}

	return false;
}

bool isAddressValid(QString address) {
	QHostAddress hostAddress;

	return hostAddress.setAddress(address);
}
#ifndef CONFIGURATIONREADER_H
#define CONFIGURATIONREADER_H

#include <QXmlStreamReader>

#include "dhconfiguration.h"

class ConfigurationReader : private QXmlStreamReader {
public:
	void test();
	void read(QIODevice * device);

private:
	void _readDyprosium();

	void _readSubNetworkList();
	void _readSubNetwork();

	void _readSubNetworkReservationList();
	void _readSubNetworkReservation();

	void _readGlobalOptionList();
	void _readSubnetOptionList();
	void _readSubnetReservationOptionList();

	void _readGlobalOption();
	void _readSubnetOption();
	void _readSubnetReservationOption();

	DHOptionDuet _readOption();

	// ERRORS

	void _raiseUnexpectedElementError(const QString &type);
	void _raiseUnexpectedElementError(QStringRef type);

	void _raiseInvalidElementError(const QString &type);

	// UTILS

	bool _hasAttribute(const QString &value);

	QString _getAttribute(const QString &value);
	bool _getBooleanAttribute(const QString &value);
	QString _getDescriptionAttribute();

	void _resetConfig();
	
private:
	DHConfiguration * _currentConfiguration;
	DHSubNetwork * _currentSubNetwork;
	DHSubNetworkReservation * _currentSubNetworkReservation;
};

#endif // CONFIGURATIONREADER_H

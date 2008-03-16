#ifndef CONFIGURATIONREADER_H
#define CONFIGURATIONREADER_H

#include <QXmlStreamReader>

class DHConfiguration;
class DHSubNetwork;
class DHSubNetworkReservation;
class DHOptionDuet;

class ConfigurationReader : private QXmlStreamReader {

public:
	DHConfiguration * read(QIODevice * device);

	QXmlStreamReader::Error error() const;
	QString errorString() const;

	qint64 columnNumber () const;
	qint64 lineNumber () const;

private:
	void _readDyprosium();

	void _readInformationsElement();
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
	void _raiseUnexpectedElementError();
	void _raiseInvalidElementError(const QString &type);
	void _raiseInvalidFileTypeError();

	// UTILS

	bool _hasAttribute(const QString &value);

	QString _getAttribute(const QString &value);
	bool _getBooleanAttribute(const QString &value);
	QString _getDescriptionAttribute();

	void _parsePrepare();
	void _parseEnd();

private:
	DHConfiguration * _configuration;
	DHSubNetwork * _currentSubNetwork;
	DHSubNetworkReservation * _currentSubNetworkReservation;

	bool _gotConfigurationInformations;
};

#endif // CONFIGURATIONREADER_H

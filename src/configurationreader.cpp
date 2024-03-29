#include "configurationreader.h"

#include "dhconfiguration.h"

#include <QFile>

#define CONF_ASSERT_PLUS(NAME, PLUS) Q_ASSERT(_configuration && isStartElement() && (name() == NAME) && PLUS)
#define CONF_ASSERT(NAME) CONF_ASSERT_PLUS(NAME, true)

#define TOKEN_DYPROSIUM "Dyprosium"

#define TOKEN_INFORMATIONS "Informations"

#define TOKEN_OPTION "Option"
#define TOKEN_OPTION_LIST "Options"

#define TOKEN_SUBNETWORK "SubNetwork"
#define TOKEN_SUBNETWORK_LIST "SubNetworks"

#define TOKEN_RESERVATION "Reservation"
#define TOKEN_RESERVATIONS_LIST "Reservations"

DHConfiguration * ConfigurationReader::read(QIODevice * device) {
	_parsePrepare();
	 
	setDevice(device);

	while(!atEnd()) {
		readNext();

		if(isStartElement()) {
			if(
				name() == TOKEN_DYPROSIUM &&
				attributes().value("Version") == DYPROSIUM_FILE_VERSION
			) {
				_readDyprosium();

			} else {
				_raiseInvalidFileTypeError();

			}
		}
	}

	if(hasError()) {
		delete _configuration;
		
		return NULL;
	}

	return _configuration;
}

QXmlStreamReader::Error ConfigurationReader::error() const {
	return QXmlStreamReader::error();
}

QString ConfigurationReader::errorString() const {
	return QXmlStreamReader::errorString();
}

qint64 ConfigurationReader::columnNumber() const {
	return QXmlStreamReader::columnNumber();
}

qint64 ConfigurationReader::lineNumber() const {
	return QXmlStreamReader::lineNumber();
}

// Private

void ConfigurationReader::_readDyprosium() {
	CONF_ASSERT(TOKEN_DYPROSIUM);

	while(!atEnd()) {
		readNext();

		if(isEndElement()) break;

		if(isStartElement()) {
			if(name() == TOKEN_SUBNETWORK_LIST) {
				_readSubNetworkList();

			} else if(name() == TOKEN_OPTION_LIST) {
				_readGlobalOptionList();

			} else if (name() == TOKEN_INFORMATIONS) {
				_readInformationsElement();
		
			} else {
				_raiseUnexpectedElementError();
			}
		}
	}

	if(!_gotConfigurationInformations) {
		raiseError(QObject::tr("No 'Informations' element was found in the _configuration."));
	}

	_parseEnd();
}

void ConfigurationReader::_readInformationsElement() {
	CONF_ASSERT(TOKEN_INFORMATIONS);

	QString name = _getAttribute("Name");

	_configuration->setName(name);
	_configuration->setDescription(_getDescriptionAttribute());

	if(!name.isEmpty()) {
		_gotConfigurationInformations = true;
	}

	readElementText();
}

void ConfigurationReader::_readSubNetworkList() {
	CONF_ASSERT(TOKEN_SUBNETWORK_LIST);

	while(!atEnd()) {
		readNext();

		if(isEndElement()) break;

		if(isStartElement()) {
			if(name() == TOKEN_SUBNETWORK) {
				_readSubNetwork();

			} else {
				_raiseUnexpectedElementError();
			}
		} 
	}
}

void ConfigurationReader::_readSubNetwork() {
	CONF_ASSERT(TOKEN_SUBNETWORK);

	if(
		_hasAttribute("Name") &&
		_hasAttribute("NetworkAddress") &&
		_hasAttribute("Mask") &&
		_hasAttribute("StartAddress") && 
		_hasAttribute("EndAddress") && 
		_hasAttribute("LeaseTime")
	) {
		_currentSubNetwork = new DHSubNetwork(
			_getAttribute("Name"),
			_getAttribute("NetworkAddress"),
			_getAttribute("Mask"),
			_getAttribute("StartAddress"),
			_getAttribute("EndAddress")
		);

		_currentSubNetwork->setLeaseTime(_getAttribute("LeaseTime"));
		_currentSubNetwork->setDescription(_getDescriptionAttribute());

		_configuration->addSubNetwork(_currentSubNetwork);

	} else {
		_raiseInvalidElementError(TOKEN_SUBNETWORK);
	}

	while(!atEnd()) {
		readNext();

		if(isEndElement()) break;

		if(isStartElement()) {
			if(name() == TOKEN_RESERVATIONS_LIST) {
				_readSubNetworkReservationList();

			} else if (name() == TOKEN_OPTION_LIST) {
				_readSubnetOptionList();

			} else {
				_raiseUnexpectedElementError();
			}
		} 
	}
}

void ConfigurationReader::_readSubNetworkReservationList() {
	CONF_ASSERT_PLUS(TOKEN_RESERVATIONS_LIST, _currentSubNetwork);

	while(!atEnd()) {
		readNext();

		if(isEndElement()) break;

		if(isStartElement()) {
			if(name() == TOKEN_RESERVATION) {
				_readSubNetworkReservation();

			} else {
				_raiseUnexpectedElementError();
			}
		} 
	}
}

void ConfigurationReader::_readSubNetworkReservation() {
	CONF_ASSERT_PLUS(TOKEN_RESERVATION, _currentSubNetwork);

	if(
		_hasAttribute("Name") &&
		_hasAttribute("Address") &&
		_hasAttribute("MacType") &&
		_hasAttribute("MacAddress") && 
		_hasAttribute("Activated")
	) {
			bool activated = _getBooleanAttribute("Activated");

			_currentSubNetworkReservation = new DHSubNetworkReservation(
				_getAttribute("Name"),
				_getAttribute("Address"),
				_getAttribute("MacAddress"),
				_getAttribute("MacType"),
				activated
			);

			_currentSubNetworkReservation->setDescription(_getDescriptionAttribute());

			_currentSubNetwork->addSubNetworkReservation(_currentSubNetworkReservation);

	} else {
		_raiseInvalidElementError(TOKEN_RESERVATION);
	}

	while(!atEnd()) {
		readNext();

		if(isEndElement()) break;

		if(isStartElement()) {
			if(name() == TOKEN_OPTION_LIST) {
				_readSubnetReservationOptionList();

			} else {
				_raiseUnexpectedElementError();
			}
		} 
	}
}

// READ OPTIONS

void ConfigurationReader::_readGlobalOptionList() {
	CONF_ASSERT(TOKEN_OPTION_LIST);

	while(!atEnd()) {
		readNext();

		if(isEndElement()) break;

		if(isStartElement()) {
			if(name() == TOKEN_OPTION) {
				_readGlobalOption();

			} else {
				_raiseUnexpectedElementError();
			}
		}
	}
}

void ConfigurationReader::_readSubnetOptionList() {
	CONF_ASSERT_PLUS(TOKEN_OPTION_LIST, _currentSubNetwork);

	while(!atEnd()) {
		readNext();

		if(isEndElement()) break;

		if(isStartElement()) {
			if(name() == TOKEN_OPTION) {
				_readSubnetOption();

			} else {
				_raiseUnexpectedElementError();
			}
		}
	}
}

void ConfigurationReader::_readSubnetReservationOptionList() {
	CONF_ASSERT_PLUS(TOKEN_OPTION_LIST, _currentSubNetwork && _currentSubNetworkReservation);

	while(!atEnd()) {
		readNext();

		if(isEndElement()) break;

		if(isStartElement()) {
			if(name() == TOKEN_OPTION) {
				_readSubnetReservationOption();

			} else {
				_raiseUnexpectedElementError();
			}
		}
	}
}

// READ PARTICULAR OPTION

void ConfigurationReader::_readGlobalOption() {
	CONF_ASSERT(TOKEN_OPTION);

	DHOptionDuet ret = _readOption();

	_configuration->options()->append(ret);
}

void ConfigurationReader::_readSubnetOption() {
	CONF_ASSERT_PLUS(TOKEN_OPTION, _currentSubNetwork);

	DHOptionDuet ret = _readOption();

	_currentSubNetwork->options()->append(ret);
}

void ConfigurationReader::_readSubnetReservationOption() {
	CONF_ASSERT_PLUS(TOKEN_OPTION, _currentSubNetwork && _currentSubNetworkReservation);

	DHOptionDuet ret = _readOption();

	_currentSubNetworkReservation->options()->append(ret);
}

DHOptionDuet ConfigurationReader::_readOption() {
	CONF_ASSERT(TOKEN_OPTION);

	DHOptionDuet duet;

	if(_hasAttribute("Type") && _hasAttribute("Value")) {
		duet.type	= (DHOptionType)_getAttribute("Type").toInt();
		duet.value	= _getAttribute("Value");

	} else {
		_raiseInvalidElementError(TOKEN_OPTION);
	}

	readElementText(); // To next element

	return duet;
}

// ERRORS
void ConfigurationReader::_raiseUnexpectedElementError() {
	raiseError(QObject::tr("Unexpected element type : %1").arg(name().toString()));
}

void ConfigurationReader::_raiseInvalidElementError(const QString &type) {
	raiseError(QObject::tr("Invalid %1 element").arg(type));
}

void ConfigurationReader::_raiseInvalidFileTypeError() {
	raiseError(QObject::tr("The file is not a Dyprosium version %1 file").arg(DYPROSIUM_FILE_VERSION));
}

// UTILS
QString ConfigurationReader::_getAttribute(const QString &value) {
	return attributes().value(value).toString();
}

bool ConfigurationReader::_getBooleanAttribute(const QString &value)  {
	if(_hasAttribute(value)) {
		QString attrString = _getAttribute(value).toLower();

		if(attrString == "true" || attrString == "yes" || attrString == "1") {
			return true;
		}

		return false;
	}

	return false;
}

QString ConfigurationReader::_getDescriptionAttribute() {
	if(_hasAttribute("Description")) {
		return _getAttribute("Description");
	}

	return "";
}

bool ConfigurationReader::_hasAttribute(const QString &value) {
	return !attributes().value(value).isNull();
}

void ConfigurationReader::_parsePrepare() {
	_configuration					= new DHConfiguration("");;
	_currentSubNetwork				= NULL;
	_currentSubNetworkReservation	= NULL;
	_gotConfigurationInformations	= false;
}

void ConfigurationReader::_parseEnd() {
	_currentSubNetwork				= NULL;
	_currentSubNetworkReservation	= NULL;
}

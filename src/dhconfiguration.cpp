#include <QXmlStreamWriter>
#include <QFile>

#include "dhconfiguration.h"

// -- DHConfiguration

// CTor

DHConfiguration::DHConfiguration(const QString& name) {
	_rootItemWidget				= NULL;
	_globalOptionsItemWidget	= NULL;

	setName(name);

	_initializeTreeWidgetItems();
}

DHConfiguration::~DHConfiguration() {
	foreach(DHSubNetwork * subNetwork, _subNetworks) {
		delete subNetwork;
	}

	delete _globalOptionsItemWidget;
	delete _rootItemWidget;
}

// Properties

void DHConfiguration::setName(QString val) {
	DHConfigurationBase::setName(val);

	_bindTreeWidgetItemName();
}

QTreeWidgetItem * DHConfiguration::rootItemWidget() {
	return _rootItemWidget;
}

QTreeWidgetItem * DHConfiguration::globalOptionsItemWidget() {
	return _globalOptionsItemWidget;
}

QList<DHSubNetwork *> DHConfiguration::subNetworks() {
	return _subNetworks;
}

QList<DHOptionDuet> * DHConfiguration::options() {
	return &_options;
}

QString DHConfiguration::fileName() const {
	return _fileName;
}

void DHConfiguration::setFileName(QString val) {
	_fileName = val;
}
// Public Methods

bool DHConfiguration::addSubNetwork(DHSubNetwork * subnet) {
	if(!_subNetworks.contains(subnet)) {
		if (subnet->parent() != this) {
			subnet->setParent(this);
		}

		_rootItemWidget->insertChild(0, subnet->subnetItemWidget());

		_subNetworks.append(subnet);

		return true;
	} 

	return false;
}

bool DHConfiguration::removeSubNetwork(DHSubNetwork * subnet) {
	if(_subNetworks.contains(subnet)) {
		QTreeWidgetItem * widget = subnet->subnetItemWidget();

		if(widget->parent() == _rootItemWidget) {
			_rootItemWidget->removeChild(widget);
		}

		return _subNetworks.removeAll(subnet);
	}

	return false;
}

void DHConfiguration::flushConfiguration (QXmlStreamWriter * stream) {
	stream->writeStartDocument("1.0");

	stream->writeStartElement("Dyprosium");
	stream->writeAttribute("Version", DYPROSIUM_FILE_VERSION);

	// Informations
	stream->writeEmptyElement("Informations");
	stream->writeAttribute("Name", name());
	stream->writeAttribute("Description", description());

	// Global Options
	if(_options.count() > 0) {
		stream->writeStartElement("Options");

		foreach(DHOptionDuet option, _options) {
			option.flushConfiguration(stream);
		}

		stream->writeEndElement();
	}

	// SubNetworks
	if (_subNetworks.count() > 0) {
		stream->writeStartElement("SubNetworks");

		foreach (DHSubNetwork * subnet, _subNetworks) {
			subnet->flushConfiguration(stream);
		}

		stream->writeEndElement();
	}

	stream->writeEndDocument();
}

void DHConfiguration::writeXmlConfiguration(QIODevice * device) {
	QXmlStreamWriter * xmlWriter = new QXmlStreamWriter(device);
	xmlWriter->setAutoFormatting(true);

	flushConfiguration(xmlWriter);
}

QString DHConfiguration::xmlConfiguration() {
	QString outputBuffer;

	QXmlStreamWriter * xmlWriter = new QXmlStreamWriter(&outputBuffer);
	xmlWriter->setAutoFormatting(true);

	flushConfiguration(xmlWriter);

	return outputBuffer;
}

void DHConfiguration::_initializeTreeWidgetItems() {
	_rootItemWidget = new QTreeWidgetItem(QStringList());
	_rootItemWidget->setIcon(0, QIcon(":/images/Resources/folder_page.png"));
	_rootItemWidget->setItemRole(TREE_ROLE_ROOT);
	_rootItemWidget->setDataPtr(this);

	_globalOptionsItemWidget = new QTreeWidgetItem(_rootItemWidget);
	_globalOptionsItemWidget->setText(0, tr("Options globales"));
	_globalOptionsItemWidget->setIcon(0, QIcon(":/images/Resources/wrench_orange.png"));
	_globalOptionsItemWidget->setItemRole(TREE_ROLE_GLOBAL_OPTIONS);

	_bindTreeWidgetItemName();
}

void DHConfiguration::_bindTreeWidgetItemName() {
	if(_rootItemWidget) {
		_rootItemWidget->setText(0, tr("Configuration [%1]").arg(this->name()));
	}
}

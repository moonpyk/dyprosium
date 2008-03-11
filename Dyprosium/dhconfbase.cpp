#include "dhconfbase.h"

// -- DHConfigurationBase

void DHConfigurationBase::flushBaseConfInformations (QXmlStreamWriter * stream) {
	stream->writeAttribute("Name", _name);
	stream->writeAttribute("Description", _description);
}

QString DHConfigurationBase::name() const {
	return _name;
}

void DHConfigurationBase::setName(QString val) {
	_name = val;
}

QString DHConfigurationBase::description() const {
	return _description;
}

void DHConfigurationBase::setDescription(QString val) {
	_description = val;
}

// -- DHOptionDuet

DHOptionDuet::DHOptionDuet() {
	this->type		= option_null;
	this->value		= "";
}

DHOptionDuet::DHOptionDuet(DHOptionType type, QString value) {
	this->type			= type;
	this->value			= value;
}

DHOptionDuet::DHOptionDuet(const DHOptionDuet& duet) {
	this->type			= duet.type;
	this->value			= duet.value;
}

void DHOptionDuet::flushConfiguration(QXmlStreamWriter * stream) const {
	stream->writeEmptyElement("Option");
	stream->writeAttribute("Type", QString::number(type));
	stream->writeAttribute("Value", value);
}

bool DHOptionDuet::equals(DHOptionDuet duet) const {
	return (this->type == duet.type) && (this->value == duet.value);
}

bool DHOptionDuet::equals(DHOptionDuet * duet) const {
	if(duet) {
		return equals(*duet);
	}
	
	return false;
}

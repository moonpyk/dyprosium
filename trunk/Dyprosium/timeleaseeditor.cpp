#include "timeleaseeditor.h"

//CTor

TimeLeaseEditor::TimeLeaseEditor(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);

	ui.spinDays->setValue(LEASE_DAYS_DEFAULT_VALUE);
	ui.spinHours->setValue(LEASE_HOURS_DEFAULT_VALUE);
	ui.spinMinutes->setValue(LEASE_MINUTES_DEFAULT_VALUE);

	QObject::connect(ui.spinDays, SIGNAL(valueChanged(int)), this, SLOT(_itemValueChanged()));
	QObject::connect(ui.spinHours, SIGNAL(valueChanged(int)), this, SLOT(_itemValueChanged()));
	QObject::connect(ui.spinMinutes, SIGNAL(valueChanged(int)), this, SLOT(_itemValueChanged()));
	
	QObject::connect(ui.radioFixed, SIGNAL(toggled(bool)), this, SLOT(_itemValueChanged()));
	QObject::connect(ui.radioInfinite, SIGNAL(toggled(bool)), this, SLOT(_itemValueChanged()));
}

TimeLeaseEditor::~TimeLeaseEditor() { }

// Properties

int TimeLeaseEditor::days() const {
	return ui.spinDays->value();
}

void TimeLeaseEditor::setDays(int val) {
	ui.spinDays->setValue(val);
}

int TimeLeaseEditor::hours() const {
	return ui.spinHours->value();
}

void TimeLeaseEditor::setHours(int val) {
	ui.spinHours->setValue(val);
}

int TimeLeaseEditor::minutes() const {
	return ui.spinMinutes->value();
}

void TimeLeaseEditor::setMinutes(int val) {
	ui.spinMinutes->setValue(val);
}

bool TimeLeaseEditor::isInfinite() const {
	return ui.radioInfinite->isChecked();
}

void TimeLeaseEditor::setInfinite(bool val) {
	ui.radioInfinite->setChecked(val);
}

int TimeLeaseEditor::value() const {
	if(isInfinite()) {
		return -1;

	} else {
		int value = 
			_days(days()) + 
			_hours(hours()) +
			_minutes(minutes());

		return value;
	}
}

QString TimeLeaseEditor::valueString() const {
	if(!isInfinite()) {
		return QString::number(value());
	}

	return "infinite";
}

// Private functions

int TimeLeaseEditor::_seconds(int val) const {
	return val;
}

int TimeLeaseEditor::_minutes(int val) const {
	return 60 * _seconds(val);
}

int TimeLeaseEditor::_hours(int val) const {
	return 60 * _minutes(val);
}

int TimeLeaseEditor::_days(int val) const {
	return 24 * _hours(val);
}

// Private slots

void TimeLeaseEditor::_itemValueChanged() {
	emit valueChanged();
}

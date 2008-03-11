#ifndef TIMELEASE_H
#define TIMELEASE_H

#include <QWidget>
#include "ui_timeleaseeditor.h"

#define LEASE_DAYS_DEFAULT_VALUE 8
#define LEASE_HOURS_DEFAULT_VALUE  0
#define LEASE_MINUTES_DEFAULT_VALUE 0

class TimeLeaseEditor : public QWidget {
	Q_OBJECT

public:
	TimeLeaseEditor(QWidget *parent = 0);
	~TimeLeaseEditor();

signals:
	void valueChanged();

public:
	Q_PROPERTY(int days READ days WRITE setDays);
	Q_PROPERTY(int hours READ hours WRITE setHours);
	Q_PROPERTY(int minutes READ minutes WRITE setMinutes);
	Q_PROPERTY(bool isInfinite READ isInfinite WRITE setInfinite);

	Q_PROPERTY(int value READ value);
	Q_PROPERTY(QString valueString READ valueString);

	int days() const;
	void setDays(int val);

	int hours() const;
	void setHours(int val);

	int minutes() const;
	void setMinutes(int val);

	bool isInfinite() const;
	void setInfinite(bool val);

	int value() const;
	QString valueString() const;

private:
	int _seconds(int val) const;
	int _minutes(int val) const;
	int _hours(int val) const;
	int _days(int val) const;

private slots:
	void _itemValueChanged();

private:
	Ui::TimeLeaseEditor ui;
};

#endif // TIMELEASE_H

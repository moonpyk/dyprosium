#ifndef ADDRESSLISTEDITOR_H
#define ADDRESSLISTEDITOR_H

#include "stringlisteditor.h"

#include <QHostAddress>

class AddressListEditor : public StringListEditor {
	Q_OBJECT

public:
	// CTor
	AddressListEditor(QWidget *parent = 0) : StringListEditor(parent) {
		setTitle(tr("Liste d'adresses :"));
		setInputMask("000.000.000.000;_");
	}

protected:
	virtual bool validateStringEntry(QString text) {
		QHostAddress addressTester;

		return addressTester.setAddress(text);
	}
};

#endif // ADDRESSLISTEDITOR_H
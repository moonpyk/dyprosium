#include "reservationeditor.h"

#include <QDialogButtonBox>
#include <QPushButton>

#include "iptools.h"

// CTor

ReservationEditor::ReservationEditor(DHSubNetworkReservation * reservation, QWidget *parent /*= 0*/)
	: QWidget(parent) {
	ui.setupUi(this);

	_reservation = reservation;

	loadFields();

	QObject::connect(ui.lineName, SIGNAL(textChanged(QString)), this, SLOT(_fields_textChanged(QString)));
	QObject::connect(ui.lineMacAddress, SIGNAL(textChanged(QString)), this, SLOT(_fields_textChanged(QString)));
	QObject::connect(ui.lineIPAddress, SIGNAL(textChanged(QString)), this, SLOT(_fields_textChanged(QString)));
}

ReservationEditor::~ReservationEditor() { }

// Properties

DHSubNetworkReservation * ReservationEditor::reservation() {
	return _reservation;
}

void ReservationEditor::setReservation(DHSubNetworkReservation * val) {
	_reservation = val;
}

bool ReservationEditor::fieldsValid() const {
	return _fieldsValid;
}

// Public methods

QDialog * ReservationEditor::createDialog(QWidget *parent /*= 0*/, Qt::WindowFlags f /*= 0*/) {
	QDialog * dialog = new QDialog(parent, f);
	//dialog->resize(335, 326);
	dialog->setWindowTitle(tr("Editeur de réservations"));

	QVBoxLayout			* vboxLayout;
	QDialogButtonBox	* buttonBox;

	this->setParent(dialog);	

	vboxLayout	= new QVBoxLayout(dialog);
	vboxLayout->addWidget(this);

	buttonBox = new QDialogButtonBox(dialog);
	buttonBox->setOrientation(Qt::Horizontal);
	buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::NoButton | QDialogButtonBox::Ok);

	QPushButton * okButton = buttonBox->button(QDialogButtonBox::Ok);
	okButton->setEnabled(_areFieldsValid());

	QObject::connect(this, SIGNAL(fieldsValidChanged(bool)), okButton, SLOT(setEnabled(bool)));

	vboxLayout->addWidget(buttonBox);

	QObject::connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
	QObject::connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

	return dialog;
}

// Public slots

void ReservationEditor::loadFields() {
	if(_reservation) {
		ui.lineName->setText(_reservation->name());
		ui.lineMacAddress->setText(_reservation->macAddress());

		QString macTypeL = _reservation->macAddressType().toLower();

		if(macTypeL == "token-ring") {
			ui.comboMacType->setCurrentIndex(RESA_COMBO_TOKEN_RING);

		} else if (macTypeL == "fddi") {
			ui.comboMacType->setCurrentIndex(RESA_COMBO_FDDI);

		} else {
			ui.comboMacType->setCurrentIndex(RESA_COMBO_ETHERNET);
		}

		ui.lineIPAddress->setText(_reservation->address());
		ui.textDescription->setText(_reservation->description());
	}
}

bool ReservationEditor::saveFields() {
	if(_areFieldsValid()) {
		_reservation->setName(ui.lineName->text());
		_reservation->setDescription(ui.textDescription->toPlainText());

		_reservation->setAddress(ui.lineIPAddress->text());
		_reservation->setMacAddress(ui.lineMacAddress->text());
		_reservation->setMacAddressType(ui.comboMacType->currentText().toLower());
	
		return true;
	}

	return false;
}

// Private methods

bool ReservationEditor::_areFieldsValid() {
	return
		!ui.lineName->text().isEmpty()&& 
		(ui.lineIPAddress->hasAcceptableInput() && isAddressValid(ui.lineIPAddress->text())) &&
		ui.lineMacAddress->hasAcceptableInput();
}
void ReservationEditor::_setFieldsValid(bool val) {
	if (_fieldsValid != val) { 
		_fieldsValid = val; 
		
		emit fieldsValidChanged(val);
	}
}

void ReservationEditor::_verifyFields() {
	_setFieldsValid( _areFieldsValid() );
}

// Private slots

void ReservationEditor::_fields_textChanged(const QString &) {
	_verifyFields();
}

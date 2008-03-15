#ifndef RESERVATIONEDITOR_H
#define RESERVATIONEDITOR_H

#include <QDialog>

#include "ui_reservationeditor.h"

#include "dhsubnetwork.h"

#define RESA_COMBO_ETHERNET		0
#define RESA_COMBO_FDDI			1
#define RESA_COMBO_TOKEN_RING	2

class ReservationEditor : public QWidget {
	Q_OBJECT

public:
	ReservationEditor(DHSubNetworkReservation * reservation, QWidget *parent = 0);
	~ReservationEditor();

signals:
	void fieldsValidChanged(bool value);

public:
	Q_PROPERTY(DHSubNetworkReservation * reservation READ reservation WRITE setReservation);

	Q_PROPERTY(bool fieldsValid READ fieldsValid);

	DHSubNetworkReservation * reservation();
	void setReservation(DHSubNetworkReservation * val);

	bool fieldsValid() const;

public slots:
	void loadFields();
	bool saveFields();

public:
	QDialog * createDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);

private:
	bool _areFieldsValid();
	void _setFieldsValid(bool val);
	void _verifyFields();

private:
	Ui::ReservationEditor ui;

	DHSubNetworkReservation * _reservation;

	bool _fieldsValid;

private slots:
	void _fields_textChanged(const QString &);
};

#endif // RESERVATIONEDITOR_H

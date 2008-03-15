#ifndef RESERVATIONSVIEW_H
#define RESERVATIONSVIEW_H

#include <QWidget>

#include "ui_reservationsview.h"

#include "control_interfaces.h"
#include "dhsubnetwork.h"

#pragma region ReservationViewLine Struct

struct ReservationViewLine {
	ReservationViewLine(DHSubNetworkReservation * reservation);
	~ReservationViewLine();

	// Properties
	int row();

	// Methods
	void reflectChanges();

	void addLineTo(QTableWidget * widget);
	bool belongsTo(QTableWidget * widget);
	void removeLine();

	// Variables
	QTableWidgetItem * nameItem;
	QTableWidgetItem * ipAddressItem;
	QTableWidgetItem * macAddressItem;

	DHSubNetworkReservation * reservation;
};

#pragma endregion

class ReservationsView : public QWidget, public ISimpleActionsClient {
	Q_OBJECT

public:
	ReservationsView(QWidget *parent = 0);
	~ReservationsView();

public:
	Q_PROPERTY(bool isIntroMode READ isIntroMode WRITE setIntroMode);

	Q_PROPERTY(bool addEnabled READ addEnabled WRITE setAddEnabled);
	Q_PROPERTY(bool removeEnabled READ removeEnabled WRITE setRemoveEnabled);
	Q_PROPERTY(bool editEnabled READ editEnabled WRITE setEditEnabled);

	Q_PROPERTY(DHSubNetwork * currentDHSubNetwork READ currentDHSubNetwork WRITE setCurrentDHSubNetwork);

	bool isIntroMode() const;
	void setIntroMode(bool value);

	bool addEnabled () const;
	void setAddEnabled(bool value);

	bool removeEnabled () const ;
	void setRemoveEnabled(bool value);

	bool editEnabled() const;
	void setEditEnabled(bool value);

	DHSubNetwork * currentDHSubNetwork() const;
	void setCurrentDHSubNetwork(DHSubNetwork * val);

	// TODO : Q_PROPERTY here
	int currentRowNumber();
	ReservationViewLine * currentLine();
	DHSubNetworkReservation * currentReservation();

signals:
	void valuesChanged();
	void simpleActionButtonsEnabledChanged();

public slots:
	void add();
	void remove();
	void edit();
	
	void clear();

	void toggleIntro();
	void setToIntroModeIfEmpty(); 

private:
	void _populateItems();
	void _appendReservationToTable(DHSubNetworkReservation * reservation);
	
	void _connectSignals();

	void _removeAll();
	void _removeLine(ReservationViewLine * line);

	void _checkSimpleActionButtonsEnabled (QTableWidgetItem* current);

private slots:
	void on_tableReservations_currentItemChanged(QTableWidgetItem* current, QTableWidgetItem*);
	
private:
	Ui::ReservationsView ui;

	QList<ReservationViewLine *> _reservationLines;

	DHSubNetwork * _currentDHSubNetwork;
	
};

#endif // RESERVATIONSVIEW_H

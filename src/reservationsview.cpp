#include "reservationsview.h"

#include "reservationeditor.h"

#pragma region ReservationViewLine Struct

ReservationViewLine::ReservationViewLine(DHSubNetworkReservation * reservation) {
	this->reservation = reservation;

	this->nameItem			= new QTableWidgetItem(QString());
	this->ipAddressItem		= new QTableWidgetItem(QString());
	this->macAddressItem	= new QTableWidgetItem(QString());

	reflectChanges();
}

ReservationViewLine::~ReservationViewLine() {
	delete nameItem;
	delete ipAddressItem;
	delete macAddressItem;
}

int ReservationViewLine::row() {
	if(nameItem) {
		return nameItem->row();
	}

	return -1;
}

bool ReservationViewLine::belongsTo(QTableWidget * widget) {
	if(widget) {
		return (widget->item(row(), 0) == nameItem);
	}

	return false;
}

void ReservationViewLine::removeLine() {
	QTableWidget * widget = nameItem->tableWidget();

	if(widget) {
		int itemRowId = row();

		widget->removeRow(itemRowId);

		nameItem		= NULL;
		ipAddressItem	= NULL;
		macAddressItem	= NULL;
	}
}

void ReservationViewLine::reflectChanges() {
	nameItem->setText(reservation->name());
	ipAddressItem->setText(reservation->address());
	macAddressItem->setText(reservation->macAddress());
}

void ReservationViewLine::addLineTo(QTableWidget * widget) {
	if(widget) {
		int newrowNumber = widget->rowCount();

		widget->setRowCount(newrowNumber + 1);

		widget->setItem(newrowNumber, 0, nameItem);
		widget->setItem(newrowNumber, 1, ipAddressItem);
		widget->setItem(newrowNumber, 2, macAddressItem);
	}
}

#pragma endregion 

ReservationsView::ReservationsView(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);

	ui.titleWidget->setText("Address Reservations");
	ui.titleWidget->setPixmap(QPixmap(":/images/Resources/folder_heart.png"));

	_connectSignals();

	setIntroMode(true);
	setSimpleActionsEnabled(false);

	_currentDHSubNetwork = NULL;
}

ReservationsView::~ReservationsView() { }

// Proterties

bool ReservationsView::addEnabled() const {
	return (ui.btnAdd->isEnabled() && ui.btnAddReservation->isEnabled());
}

void ReservationsView::setAddEnabled(bool value) {
	if(value != addEnabled()) {
		ui.btnAdd->setEnabled(value);
		ui.btnAddReservation->setEnabled(value);

		emit simpleActionButtonsEnabledChanged();
	}
}

bool ReservationsView::removeEnabled() const {
	return ui.btnRemove->isEnabled();
}

void ReservationsView::setRemoveEnabled(bool value) {
	if(value != removeEnabled()) {
		ui.btnRemove->setEnabled(value);

		emit simpleActionButtonsEnabledChanged();
	}
}

bool ReservationsView::editEnabled() const {
	return ui.btnEdit->isEnabled();
}

void ReservationsView::setEditEnabled(bool value) {
	if(value != editEnabled()) {
		ui.btnEdit->setEnabled(value);

		emit simpleActionButtonsEnabledChanged();
	}
}

bool ReservationsView::isIntroMode() const {
	return (ui.controlsStack->currentIndex() == 0);
}

void ReservationsView::setIntroMode(bool value) {
	if (value) {
		ui.controlsStack->setCurrentIndex(0);

	} else {
		ui.controlsStack->setCurrentIndex(1);
	}
}

DHSubNetwork * ReservationsView::currentDHSubNetwork() const {
	return _currentDHSubNetwork;
}

void ReservationsView::setCurrentDHSubNetwork(DHSubNetwork * val) {
	_currentDHSubNetwork = val;

	if(val) {
		setAddEnabled(true);
		_populateItems();

	} else {
		setSimpleActionsEnabled(false);
		_removeAll();
	}

	emit valuesChanged();
}

// Public slots

void ReservationsView::add() {
	DHSubNetworkReservation * newReservation = new DHSubNetworkReservation();
	
	ReservationEditor * editor		= new ReservationEditor(newReservation);
	QDialog * editionDialog			= editor->createDialog(this);

	if(editionDialog->exec() == QDialog::Accepted) {
		editor->saveFields();

		_currentDHSubNetwork->addSubNetworkReservation(newReservation);

		_appendReservationToTable(newReservation);

		emit valuesChanged();

	} else {
		delete newReservation;
	}
}

void ReservationsView::remove() {
	ReservationViewLine * line = this->currentLine();

	if(line) {
		DHSubNetworkReservation * currentReservation = line->reservation;

		//TODO : Confirmation

		_currentDHSubNetwork->removeSubNetworkReservation(currentReservation);
		line->removeLine();
		_reservationLines.removeAll(line);

		emit valuesChanged();
	}
}

void ReservationsView::edit() {
	ReservationViewLine * line = this->currentLine();

	if(line) {
		DHSubNetworkReservation * currentReservation = line->reservation;

		ReservationEditor * editor		= new ReservationEditor(currentReservation);
		QDialog * editionDialog			= editor->createDialog(this);

		if (editionDialog->exec() == QDialog::Accepted) {
			editor->saveFields();

			line->reflectChanges();

			emit valuesChanged();
		}

		editionDialog->deleteLater();
	}
}

// Public methods

int ReservationsView::currentRowNumber() {
	return ui.tableReservations->currentRow();
}

DHSubNetworkReservation * ReservationsView::currentReservation() {
	ReservationViewLine * line  = currentLine();

	if(line) {
		return line->reservation;
	}

	return NULL;
}

ReservationViewLine * ReservationsView::currentLine() {
	foreach(ReservationViewLine * line, _reservationLines) {
		if(line->row() == currentRowNumber()) {
			return line;
		}
	}

	return NULL;
}

void ReservationsView::clear() {
	_removeAll();
}

void ReservationsView::toggleIntro() {
	setIntroMode(!isIntroMode());
}

void ReservationsView::setToIntroModeIfEmpty() {
	setIntroMode(ui.tableReservations->rowCount() == 0);
}

// Private methods

void ReservationsView::_connectSignals() {
	QObject::connect(ui.btnAdd, SIGNAL(clicked()), this, SLOT(add()));
	QObject::connect(ui.btnRemove, SIGNAL(clicked()), this, SLOT(remove()));
	QObject::connect(ui.btnEdit, SIGNAL(clicked()), this, SLOT(edit()));

	QObject::connect(this, SIGNAL(valuesChanged()), this, SLOT(setToIntroModeIfEmpty()));
}

void ReservationsView::_populateItems() {
	foreach(DHSubNetworkReservation * reservation, _currentDHSubNetwork->reservations()) {
		_appendReservationToTable(reservation);
	}
}

void ReservationsView::_appendReservationToTable(DHSubNetworkReservation * reservation) {
	ReservationViewLine * line = new ReservationViewLine(reservation);

	line->addLineTo(ui.tableReservations);

	_reservationLines.append(line);
}

void ReservationsView::_removeAll() {
	foreach(ReservationViewLine * line, _reservationLines) {
		line->removeLine();

		_reservationLines.removeAll(line);
	}
}

void ReservationsView::_removeLine(ReservationViewLine * line) {
	line->removeLine();

	_reservationLines.clear();
}

void ReservationsView::_checkSimpleActionButtonsEnabled (QTableWidgetItem* current) {
	bool editControlsEnabled = (current != NULL);

	setRemoveEnabled(editControlsEnabled);
	setEditEnabled(editControlsEnabled);
}

// Private slots

void ReservationsView::on_tableReservations_currentItemChanged(QTableWidgetItem* current, QTableWidgetItem*) {
	_checkSimpleActionButtonsEnabled(current);
}

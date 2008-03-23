#include "optionsview.h"

#include "optioneditor.h"

#include <QHeaderView>
#include <QDialogButtonBox>

#pragma region OptionViewLine Struct

OptionViewLine::OptionViewLine (DHOptionDuet duet) {
	this->duet					= new DHOptionDuet(duet);
	
	this->idItem				= new QTableWidgetItem(QString());
	this->typeStringItem		= new QTableWidgetItem(QString());
	this->valueStringItem		= new QTableWidgetItem(QString());

	reflectChanges();
}

OptionViewLine::~OptionViewLine () {
	delete idItem;
	delete typeStringItem;
	delete valueStringItem;

	delete duet;
}

int OptionViewLine::row () {
	return idItem->row();
}

void OptionViewLine::removeLine () {
	QTableWidget * widget = idItem->tableWidget();

	if(widget) {
		int itemRow = row();

		widget->removeRow(itemRow);

		idItem			= NULL;
		typeStringItem	= NULL;
		valueStringItem = NULL;
	}
}

bool OptionViewLine::belongsTo (QTableWidget * widget) {
	if(widget) {
		return (widget->item(row(), 0) == idItem);
	}

	return false;
}

void OptionViewLine::reflectChanges() {
	idItem			->setText(QString::number(duet->type));
	typeStringItem	->setText(dhOptionTypeToQString(duet->type));
	valueStringItem	->setText(duet->value);
}

void OptionViewLine::addLineTo(QTableWidget * widget) {
	if(widget) {
		int newrowNumber = widget->rowCount();

		widget->setRowCount(newrowNumber + 1);
		widget->setItem(newrowNumber, 0, idItem);
		widget->setItem(newrowNumber, 1, typeStringItem);
		widget->setItem(newrowNumber, 2, valueStringItem);
	}
}

#pragma endregion

// CTor

OptionsView::OptionsView(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);

	ui.titleWidget->setPixmap(QPixmap(":/images/wrench_orange.png"));

	ui.tableOptions->verticalHeader()->hide();

	_connectSignals();
}

// DTor

OptionsView::~OptionsView() {
	// #TODO : Implement OptionsView DToR
}

// Properties

QList<DHOptionDuet> OptionsView::optionsList () const {
	QList<DHOptionDuet> retval;

	foreach(DHOptionDuet* duet, _options.uniqueKeys()) {
		retval.append(*duet);
	}

	return retval;
}

void OptionsView::setOptionsList (QList<DHOptionDuet> value) {
	_clearTableOptions();

	foreach(DHOptionDuet duet, value) {
		addOption(duet);
	}

	emit valuesChanged();
}

QString OptionsView::title() const {
	return ui.titleWidget->text();
}

void OptionsView::setTitle (QString value) {
	ui.titleWidget->setText(value);
}

bool OptionsView::addEnabled () const {
	return ui.btnAdd->isEnabled() && ui.btnAddOption->isEnabled();
}

void OptionsView::setAddEnabled(bool value) {
	if(value != addEnabled()) {
		ui.btnAdd->setEnabled(value);
		ui.btnAddOption->setEnabled(value);

		emit simpleActionButtonsEnabledChanged();
	}
}

bool OptionsView::removeEnabled () const {
	return ui.btnRemove->isEnabled();
}

void OptionsView::setRemoveEnabled(bool value) {
	if(value != removeEnabled()) {
		ui.btnRemove->setEnabled(value);

		emit simpleActionButtonsEnabledChanged();
	}
}

bool OptionsView::editEnabled() const {
	return ui.btnEdit->isEnabled();
}

void OptionsView::setEditEnabled(bool value) {
	if(value != editEnabled()) {
		ui.btnEdit->setEnabled(value);

		emit simpleActionButtonsEnabledChanged();
	}
}

DHOptionDuet * OptionsView::currentDuet() {
	OptionViewLine * line = currentLine(); 

	if(line) {
		return line->duet;
	}

	return NULL;
}

OptionViewLine * OptionsView::currentLine() {
	foreach(OptionViewLine * line, _options) {
		if(line->row() == currentRowNumber()) {
			return line;
		}
	}

	return NULL;
}

int OptionsView::currentRowNumber() {
	return ui.tableOptions->currentRow();
}

// Public slots

void OptionsView::add () {
	OptionEditor * editor	= new OptionEditor();
	QDialog * editionDialog = editor->createDialog(this);

	if (editionDialog->exec() == QDialog::Accepted) {
		addOption(DHOptionDuet(editor->type(), editor->value()));

		ui.tableOptions->resizeColumnsToContents();

		emit valuesChanged();
	}

	editionDialog->deleteLater();
}

void OptionsView::remove () {
	DHOptionDuet * duet = currentDuet();

	removeOption(duet);

	ui.tableOptions->resizeColumnsToContents();

	emit valuesChanged();
}

void OptionsView::edit() {
	OptionEditor * editor	= new OptionEditor();
	QDialog * editionDialog = editor->createDialog(this);

	OptionViewLine * line	= currentLine();
	DHOptionDuet * duet		= line->duet;

	editor->setType(duet->type);
	editor->setValue(duet->value);

	if (editionDialog->exec() == QDialog::Accepted) {

		// Duet value changed ?
		DHOptionDuet newDuet = editor->toDuet();

		if(!duet->equals(newDuet)) {
			*duet = newDuet;

			line->reflectChanges();

			ui.tableOptions->resizeColumnsToContents();

			emit valuesChanged();
		}
	}

	editionDialog->deleteLater();
}

void OptionsView::clear() {
	_clearTableOptions();
}
// Public methods

bool OptionsView::addOption(DHOptionDuet duet) {
	if(findOption(duet.type) == NULL) {
		OptionViewLine * newLine = new OptionViewLine(duet);

		newLine->addLineTo(ui.tableOptions);

		_options.insert(newLine->duet, newLine);

		return true;
	}

	return false;
}

bool OptionsView::removeOption (DHOptionDuet * duet) {
	if(_options.contains(duet)) {
		OptionViewLine * line = _options.value(duet, NULL);

		if (line) {
			if(line->belongsTo(ui.tableOptions)) {
				_options.remove(duet);

				_deleteLine(line);

				return true;
			}
		}
	}

	return false;
}

DHOptionDuet * OptionsView::findOption (DHOptionType type) {
	foreach(OptionViewLine * line, _options) {
		if(line->duet->type == type) {
			return line->duet;
		}
	}

	return NULL;
}

DHOptionDuet * OptionsView::optionAt (int row) {
	foreach(OptionViewLine * line, _options) {
		if(line->row() == row) {
			return line->duet;
		}
	}

	return NULL;
}

void OptionsView::reflectChangeOn (DHOptionDuet * duet) {
	OptionViewLine * line = _options.value(duet, NULL);

	if(line != NULL) {
		line->reflectChanges();
	}
}

void OptionsView::reflectAllChanges() {
	foreach(DHOptionDuet * duet, _options.uniqueKeys()) {
		reflectChangeOn(duet);
	}
}
// Private methods

void OptionsView::_clearTableOptions () {
	foreach(OptionViewLine * line, _options) {
		_deleteLine(line);
	}

	_options.clear();
}

void OptionsView::_connectSignals () {
	QObject::connect(ui.btnAdd, SIGNAL(clicked()), this, SLOT(add()));
	QObject::connect(ui.btnRemove, SIGNAL(clicked()), this, SLOT(remove()));
	QObject::connect(ui.btnEdit, SIGNAL(clicked()), this, SLOT(edit()));

	QObject::connect(this, SIGNAL(valuesChanged()), this, SLOT(setToIntroModeIfEmpty()));
}

void OptionsView::_deleteLine(OptionViewLine * line) {
	line->removeLine();

	delete line;
}

void OptionsView::_checkSimpleActionButtonsEnabled (QTableWidgetItem* current) {
	bool editControlsEnabled = (current != NULL);

	setRemoveEnabled(editControlsEnabled);
	setEditEnabled(editControlsEnabled);
}

// Private slots

void OptionsView::on_tableOptions_currentItemChanged(QTableWidgetItem* current, QTableWidgetItem*) {
	_checkSimpleActionButtonsEnabled(current);
}

bool OptionsView::isIntroMode() const {
	return (ui.controlsStack->currentIndex() == 0);
}

void OptionsView::setIntroMode(bool value) {
	if (value) {
		ui.controlsStack->setCurrentIndex(0);

	} else {
		ui.controlsStack->setCurrentIndex(1);
	}
}

void OptionsView::toggleIntro() {
	setIntroMode(!isIntroMode());
}

void OptionsView::setToIntroModeIfEmpty() {
	setIntroMode(ui.tableOptions->rowCount() == 0);
}

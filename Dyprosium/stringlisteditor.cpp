#include "stringlisteditor.h"
#include "iptools.h"

StringListEditor::StringListEditor(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);
}

// Properties

QStringList StringListEditor::stringList () const {
	return _stringList;
}

void StringListEditor::setStringList(QStringList addressList) {
	foreach(QString address, addressList) {
		addString(address);
	}
}

QString StringListEditor::currentString() const {
	return ui.editString->text();
}

void StringListEditor::setCurrentString(QString address) {
	ui.editString->setText(address);
}

QString StringListEditor::inputMask() const {
	return ui.editString->inputMask();
}

void StringListEditor::setInputMask(QString mask) {
	ui.editString->setInputMask(mask);
}

QString StringListEditor::title() const {
	return ui.lblTitle->text();
}

void StringListEditor::setTitle(QString title) {
	ui.lblTitle->setText(title);
}

// Public slots

bool StringListEditor::addString(QString value) {
	if(validateStringEntry(value)) {
		if(!_stringList.contains(value)) {
			_stringList.append(value);

			QListWidgetItem * item = 
				new QListWidgetItem(value, ui.listString);

			Q_UNUSED(item);

			emit stringAdded(value);
			emit stringListChanged();

			return true;
		}
	}

	return false;
}

// Protected

void StringListEditor::keyReleaseEvent (QKeyEvent * event) {
	if(ui.listString->hasFocus() && (ui.listString->selectedItems().count() == 1)) {
		switch(event->key())
		{
		case Qt::Key_Delete:
			if(ui.btnRemove->isEnabled()) {
				event->accept();

				removeSelectedItem();

				return;
			}
			break;

		case Qt::Key_Plus:
			if(ui.btnDown->isEnabled()) {
				event->accept();

				moveSelectedItem(1);
				return;
			}

			break;

		case Qt::Key_Minus:
			if(ui.btnUp->isEnabled()) {
				event->accept();

				moveSelectedItem(-1);
				return;
			}
			break;
		}
	}

	QWidget::keyReleaseEvent(event);
}

bool StringListEditor::validateStringEntry(QString text) {
	return true;
}

// Private functions

void StringListEditor::stringEntered () {
	if(addString(ui.editString->text())) {
		ui.editString->clear();
		ui.editString->setFocus(Qt::ShortcutFocusReason);
	}
}

void StringListEditor::checkButtonsEnabled (QListWidgetItem* current) {
	bool baseEnabled = (current != NULL);

	ui.btnRemove->setEnabled(baseEnabled);

	if(baseEnabled) {
		int index			= ui.listString->currentRow();
		int maxItemIndex	= ui.listString->count() - 1;

		ui.btnUp->setEnabled(index > 0);
		ui.btnDown->setEnabled(index != maxItemIndex);

	} else {
		ui.btnUp->setEnabled(false);
		ui.btnDown->setEnabled(false);
	}
}

bool StringListEditor::removeSelectedItem () {
	if(ui.listString->selectedItems().count() == 1) {
		QListWidgetItem * selectedItem = ui.listString->selectedItems()[0];

		QString ip = selectedItem->text();

		ui.listString->removeItemWidget(selectedItem);

		delete selectedItem;

		ui.listString->setFocus(Qt::ShortcutFocusReason);

		if(_stringList.removeAll(ip)) {
			emit stringRemoved(ip);
			emit stringListChanged();

			return true;
		}
	}

	return false;
}

void StringListEditor::moveSelectedItem (int offset) {
	if(ui.listString->selectedItems().count() == 1) {
		QListWidgetItem * selectedItem	= ui.listString->selectedItems()[0];
		QListWidgetItem * newItem		= new QListWidgetItem(*selectedItem);

		int selectedItemIndex			= ui.listString->currentRow();

		ui.listString->removeItemWidget(selectedItem);
		delete selectedItem;

		int newItemIndex = selectedItemIndex + offset;

		ui.listString->insertItem(newItemIndex, newItem);
		ui.listString->setCurrentRow(newItemIndex);
		ui.listString->setFocus(Qt::ShortcutFocusReason);

		_stringList.move(selectedItemIndex, newItemIndex);

		emit stringMoved(newItem->text());
		emit stringListChanged();
	}
}

// Private slots

void StringListEditor::on_editString_textChanged(const QString text) {
	ui.btnAdd->setEnabled(validateStringEntry(text));
}

void StringListEditor::on_listString_currentItemChanged(QListWidgetItem* current, QListWidgetItem*) {
	checkButtonsEnabled(current);
}

void StringListEditor::on_editString_returnPressed() {
	stringEntered();
}

void StringListEditor::on_btnAdd_clicked() {
	stringEntered();
}

bool StringListEditor::on_btnRemove_clicked () {
	return removeSelectedItem();
}

void StringListEditor::on_btnUp_clicked() {
	moveSelectedItem(-1);
}

void StringListEditor::on_btnDown_clicked() {
	moveSelectedItem(1);
}

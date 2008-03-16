#include "optioneditor.h"

#include <QHeaderView>
#include <QDialogButtonBox>

// OptionEditorLine Struct

OptionEditorLine::OptionEditorLine(DHOptionType type) {
	this->type			= type;
	this->idItem		= new QTableWidgetItem(QString::number(type));
	this->stringItem	= new QTableWidgetItem(dhOptionTypeToQString(type));
}

OptionEditorLine::~OptionEditorLine() {
	delete idItem;
	delete stringItem;
}

int OptionEditorLine::row() {
	return idItem->row();
}

void OptionEditorLine::setSelected(bool value) {
	if(idItem->isSelected() != value) {
		idItem->setSelected(value);
	}

	if(stringItem->isSelected() != value) {
		stringItem->setSelected(value);
	}

	if(value) {
		idItem->tableWidget()->scrollToItem(idItem);
	}
}

void OptionEditorLine::insertInTableWidget(QTableWidget * widget, int row) {
	widget->insertRow(row);

	widget->setItem(row, 0, idItem);
	widget->setItem(row, 1, stringItem);
}

// OptionEditor Class

OptionEditor::OptionEditor(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);

	ui.pageStringList->setTitle("Values list :");

	ui.typesTable->verticalHeader()->hide();

	_populateTypes();
	
	ui.typesTable->resizeColumnsToContents();

	_editorType					= StringEdit;
	_ignoreNextItemChangedEvt	= false;
}

OptionEditor::~OptionEditor() { }

// Properties

QString OptionEditor::value() const {
	return _valueForEditorType();
}

void OptionEditor::setValue(QString value) {
	if(value != _value) {
		_value = value;

		_showValueForEditorType(_value);
	}
}

DHOptionType OptionEditor::type() const {
	return _type;
}

void OptionEditor::setType(DHOptionType type) {
	_setType(type, true);
	_ignoreNextItemChangedEvt = true;
}

// Public methods

void OptionEditor::setOptionFromDuet(DHOptionDuet duet) {
	setType(duet.type);
	setValue(duet.value);
}

DHOptionDuet OptionEditor::toDuet() {
	return DHOptionDuet(type(), value());
}

QDialog * OptionEditor::createDialog(QWidget *parent /*= 0*/, Qt::WindowFlags f /*= 0*/) {
	QDialog * dialog = new QDialog(parent, f);
	dialog->resize(563, 446);
	dialog->setWindowTitle(tr("Editeur d'options"));

	QVBoxLayout			* vboxLayout;
	QDialogButtonBox	* buttonBox;

	this->setParent(dialog);	

	vboxLayout	= new QVBoxLayout(dialog);
	vboxLayout->addWidget(this);

	buttonBox = new QDialogButtonBox(dialog);
	buttonBox->setOrientation(Qt::Horizontal);
	buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::NoButton | QDialogButtonBox::Ok);

	vboxLayout->addWidget(buttonBox);

	QObject::connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
	QObject::connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

	return dialog;
}

// Private methods

void OptionEditor::_populateTypes () {
	for (int i = 0 ; i < 77 ; i++) {
		int newRow = ui.typesTable->rowCount();

		OptionEditorLine * line = new OptionEditorLine(dhOptionTypesArray[i]);

		line->insertInTableWidget(ui.typesTable, newRow);

		_typeLines.append(line);
	}
}

void OptionEditor::_setType(DHOptionType type, bool selectBack) {
	if(_type != type) {
		_type = type;

		_setEditorType(type, selectBack);
		_showValueForEditorType(_value);
	}
}

void OptionEditor::_setEditorType(DHOptionType type, bool selectBack) {
	_editorType = dhOptionTypeEditorType(type);

	if(selectBack) {
		foreach(OptionEditorLine * line, _typeLines) {
			line->setSelected(line->type == type);
		}
	}

	ui.stackedWidget->setCurrentIndex((int)_editorType);
}

void OptionEditor::_showValueForEditorType(QString value) {
	value = value.trimmed();

	switch(_editorType) {
		case FlagEdit:
			if(value.toLower() == "false") {
				ui.radioFalse->setChecked(true);

			} else if (value.toLower() == "true") {
				ui.radioTrue->setChecked(true);

			} else {
				ui.radioFalse->setChecked(false);
				ui.radioTrue->setChecked(false);
			}
			break;

		case AddressListEdit: {
				QStringList valuesList = value.split(',');

				foreach(QString subValue, valuesList) {
					ui.pageAddressList->addString(subValue.simplified());
				}
			}
			break;

		case AddressEdit:
			ui.lineAddress->setText(value);
			break;

		case StringListEdit: {
				QStringList valuesList = value.split(',');

				foreach(QString subValue, valuesList) {
					ui.pageStringList->addString(subValue.simplified());
				}
			}
			break;

		case StringEdit:
			ui.lineValue->setText(value);
			break;
	}
}

QString OptionEditor::_valueForEditorType() const {
	switch(_editorType) {
		case FlagEdit:
			return ui.radioTrue->isChecked() ? "true" : "false";
			break;

		case AddressListEdit:
			return ui.pageAddressList->stringList().join(", ");
			break;

		case AddressEdit:
			return ui.lineAddress->text();
			break;

		case StringListEdit:
			return ui.pageStringList->stringList().join(", ");
			break;

		case StringEdit:
			return ui.lineValue->text();
			break;
	}

	return "";
}

// Private slots

void OptionEditor::on_typesTable_currentItemChanged(QTableWidgetItem*, QTableWidgetItem*) {
	if(!_ignoreNextItemChangedEvt) {
		int currentRow				= ui.typesTable->currentRow();
		QTableWidgetItem * item		= ui.typesTable->item(currentRow, 0);

		if (item) {
			bool ok;
			int typeNumber = item->text().toInt(&ok);

			if(ok) {
				_setType((DHOptionType)typeNumber, false);
			}
		}

	} else {
		_ignoreNextItemChangedEvt = false;
	}
}


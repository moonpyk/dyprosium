#ifndef OPTIONEDITOR_H
#define OPTIONEDITOR_H

#include <QDialog>

#include "dhconfiguration.h"
#include "ui_optioneditor.h"

struct OptionEditorLine {
	OptionEditorLine(DHOptionType type);
	~OptionEditorLine();

	int row();
	
	void setSelected(bool value);
	void insertInTableWidget(QTableWidget * widget, int row);

	QTableWidgetItem * idItem;
	QTableWidgetItem * stringItem;
	DHOptionType type;
};

class OptionEditor : public QWidget {
	Q_OBJECT

public:
	OptionEditor(QWidget *parent = 0);
	~OptionEditor();

public:
	void setOptionFromDuet(DHOptionDuet duet);
	DHOptionDuet toDuet();

	QDialog * createDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);

public:
	Q_PROPERTY(QString value READ value WRITE setValue);
	Q_PROPERTY(DHOptionType type READ type WRITE setType);

	QString value() const;
	void setValue(QString val);

	DHOptionType type() const;
	void setType(DHOptionType type);

private:
	void _populateTypes();

	void _setType(DHOptionType type, bool selectBack);
	void _setEditorType(DHOptionType type, bool selectBack);

	void _showValueForEditorType(QString value);
	QString _valueForEditorType() const;

private:
	Ui::OptionEditor ui;

	DHOptionEditorType _editorType;

	DHOptionType _type;
	QString _value;

	QList<OptionEditorLine *> _typeLines;

	bool _ignoreNextItemChangedEvt;

private slots:
	void on_typesTable_currentItemChanged(QTableWidgetItem*, QTableWidgetItem*);
};

#endif // OPTIONEDITOR_H

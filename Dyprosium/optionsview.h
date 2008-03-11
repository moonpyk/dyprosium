#ifndef OPTIONSVIEW_H
#define OPTIONSVIEW_H

#include "dhconfiguration.h"

#include <QMap>
#include <QWidget>
#include <QTableWidgetItem>

#include "ui_optionsview.h"

#include "control_interfaces.h"

#pragma region OptionViewLine Struct

struct OptionViewLine {
	OptionViewLine(DHOptionDuet duet);
	~OptionViewLine();

	// Properties
	int typeID() const;
	void setTypeId (int value);

	QString value() const;
	void setValue(QString value);

	int row();

	// Methods
	void reflectChanges();

	void addLineTo(QTableWidget * widget);
	bool belongsTo(QTableWidget * widget);
	void removeLine();

	// Variables
	QTableWidgetItem * idItem;
	QTableWidgetItem * typeStringItem;
	QTableWidgetItem * valueStringItem;

	DHOptionDuet * duet;
};

#pragma endregion

class OptionsView : public QWidget, public ISimpleActionsClient {
	Q_OBJECT

public:
	OptionsView(QWidget *parent = 0);
	~OptionsView();

public:
	Q_PROPERTY(QString title READ title WRITE setTitle);

	Q_PROPERTY(bool isIntroMode READ isIntroMode WRITE setIntroMode);

	Q_PROPERTY(bool addEnabled READ addEnabled WRITE setAddEnabled);
	Q_PROPERTY(bool removeEnabled READ removeEnabled WRITE setRemoveEnabled);
	Q_PROPERTY(bool editEnabled READ editEnabled WRITE setEditEnabled);

	Q_PROPERTY(QList<DHOptionDuet> optionsList READ optionsList WRITE setOptionsList);
	
	Q_PROPERTY(DHOptionDuet * currentDuet READ currentDuet);
	Q_PROPERTY(OptionViewLine * currentLine READ currentLine);
	Q_PROPERTY(int currentRowNumber READ currentRowNumber);

	QList<DHOptionDuet> optionsList() const;
	void setOptionsList(QList<DHOptionDuet> value);

	QString title() const;
	void setTitle(QString value);

	bool isIntroMode() const;
	void setIntroMode(bool value);

	bool addEnabled () const;
	void setAddEnabled(bool value);

	bool removeEnabled () const;
	void setRemoveEnabled(bool value);

	bool editEnabled() const;
	void setEditEnabled(bool value);

	DHOptionDuet * currentDuet();
	OptionViewLine * currentLine();
	int currentRowNumber();

signals:
	void valuesChanged();
	void simpleActionButtonsEnabledChanged();

public slots:
	void toggleIntro();
	void setToIntroModeIfEmpty();

	void add();
	void remove();
	void edit();

	void clear();

public:
	bool addOption(DHOptionDuet duet);
	bool removeOption(DHOptionDuet * duet);

	DHOptionDuet * optionAt(int row);
	DHOptionDuet * findOption(DHOptionType type);

	void reflectChangeOn(DHOptionDuet * duet);
	void reflectAllChanges();

private:
	void _connectSignals ();
	void _clearTableOptions();

	void _deleteLine(OptionViewLine * line);

	void _checkSimpleActionButtonsEnabled (QTableWidgetItem* current);

private:
	Ui::OptionsView ui;

	QMap<DHOptionDuet *, OptionViewLine *> _options;

private slots:
	void on_tableOptions_currentItemChanged(QTableWidgetItem*, QTableWidgetItem*);
};

#endif // OPTIONSVIEW_H


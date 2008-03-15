#ifndef STRINGLISTEDITOR_H
#define STRINGLISTEDITOR_H

#include <QWidget>
#include <QKeyEvent>

#include "ui_stringlisteditor.h"

class StringListEditor : public QWidget {
	Q_OBJECT

public:
	// CTor
	StringListEditor(QWidget *parent = 0);

signals:
	// Signals
	void stringAdded(QString address);
	void stringRemoved(QString address);
	void stringMoved(QString address);

	void stringListChanged();

public:
	Q_PROPERTY(QStringList stringList READ stringList WRITE setStringList);
	Q_PROPERTY(QString currentString READ currentString WRITE setCurrentString);
	Q_PROPERTY(QString inputMask READ inputMask WRITE setInputMask);
	Q_PROPERTY(QString title READ title WRITE setTitle);

	// Properties
	QStringList stringList() const;
	void setStringList(QStringList address);

	QString currentString() const;
	void setCurrentString(QString address);

	QString inputMask() const;
	void setInputMask(QString mask);

	QString title() const;
	void setTitle(QString title);

public:
	// Public methods
	bool removeSelectedItem ();

public slots:
	// Public slots
	bool addString(QString value);

protected:
	virtual void keyReleaseEvent (QKeyEvent * event);
	virtual bool validateStringEntry(QString text);

private:
	void stringEntered ();
	void moveSelectedItem (int offset);
	void checkButtonsEnabled (QListWidgetItem* current);

private slots:
	void on_listString_currentItemChanged(QListWidgetItem* current, QListWidgetItem*);

	void on_editString_textChanged(const QString test);
	void on_editString_returnPressed();
	
	void on_btnAdd_clicked();
	bool on_btnRemove_clicked();
	void on_btnDown_clicked();
	void on_btnUp_clicked();

private:
	QStringList _stringList;
	Ui::StringListEditor ui;
};

#endif // STRINGLISTEDITOR_H

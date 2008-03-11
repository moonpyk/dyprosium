#ifndef CONTROL_INTERFACES_H
#define CONTROL_INTERFACES_H

class ISimpleActionsClient {
public:
	virtual bool addEnabled() const				= 0;
	virtual void setAddEnabled(bool value)		= 0;

	virtual bool removeEnabled() const			= 0;
	virtual void setRemoveEnabled(bool value)	= 0;

	virtual bool editEnabled() const			= 0;
	virtual void setEditEnabled(bool value)		= 0;

	bool areSimpleActionsEnabled(bool value) const {
		return addEnabled() && removeEnabled() && editEnabled();
	}

	void setSimpleActionsEnabled(bool value) {
		setAddEnabled(value);
		setEditEnabled(value);
		setRemoveEnabled(value);
	}

public slots:
	virtual void add()		= 0;
	virtual void remove()	= 0;
	virtual void edit()		= 0; 

signals:
	virtual void simpleActionButtonsEnabledChanged() = 0;
};

#endif // CONTROL_INTERFACES_H
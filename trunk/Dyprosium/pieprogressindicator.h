#ifndef PIEPROGRESSINDICATOR_H
#define PIEPROGRESSINDICATOR_H

#include <QWidget>
#include <QPaintEvent>
#include <QTimer>

class PieProgressIndicator : public QWidget {
	Q_OBJECT

public:
	PieProgressIndicator(QWidget *parent = 0);
	~PieProgressIndicator();

	Q_PROPERTY(int value READ value WRITE setValue);
	Q_PROPERTY(int minValue READ minValue WRITE setMinValue);
	Q_PROPERTY(int maxValue READ maxValue WRITE setMaxValue);


public slots:
	int value() const { return _value; }
	void setValue(int val) { _value = val % (_maxValue +1); update(); }

	int minValue() const { return _minValue; }
	void setMinValue(int val) { _minValue = val; update(); }
	
	int maxValue() const { return _maxValue; }
	void setMaxValue(int val) { _maxValue = val; _value = _value % _maxValue;  update(); }

private:
	int _angle();

protected:
	virtual void paintEvent (QPaintEvent * event);

	int _minValue;
	int _maxValue;
	int _value;
};

#endif // PIEPROGRESSINDICATOR_H

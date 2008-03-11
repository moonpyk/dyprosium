#ifndef SPINNERWIDGET_H
#define SPINNERWIDGET_H

#include <QColor>
#include <QWidget>
#include <QPaintEvent>

#include <QTimer>

class SpinnerWidget : public QWidget {
	Q_OBJECT

public:
	SpinnerWidget(QWidget * parent = NULL, int interval = 50, bool start = true);

public:
	Q_PROPERTY(int linesCount READ linesCount WRITE setLinesCount);
	Q_PROPERTY(int linesWidth READ linesWidth WRITE setLinesWidth);
	Q_PROPERTY(QColor linesColor READ linesColor WRITE setLinesColor);
	Q_PROPERTY(qreal insetFactor READ insetFactor WRITE setInsetFactor);
	Q_PROPERTY(bool useFixedSize READ useFixedSize WRITE setUseFixedSize);
	Q_PROPERTY(QSize fixedSize READ fixedSize WRITE setFixedSize);
	Q_PROPERTY(bool roundedCap READ roundedCap WRITE setRoundedCap);
	Q_PROPERTY(int rotationInterval READ rotationInterval WRITE setRotationInterval);

	Q_PROPERTY(QSize spinnerSize READ spinnerSize);
	Q_PROPERTY(bool rotationStarted READ isRotationStarted);

	int linesCount() const;
	void setLinesCount(int val);

	int linesWidth() const;
	void setLinesWidth(int val);

	QColor linesColor() const;
	void setLinesColor(QColor val);

	qreal insetFactor() const;
	void setInsetFactor(qreal val);

	bool useFixedSize() const;
	void setUseFixedSize(bool val);

	QSize fixedSize() const;
	void setFixedSize(QSize val);

	bool roundedCap() const;
	void setRoundedCap(bool val);

	int rotationInterval() const;
	void setRotationInterval(int val);

	QSize spinnerSize() const;

	Qt::PenCapStyle capStyle() const;

	bool isRotationStarted() const;

public slots:
	void startRotation();
	void stopRotation();
	void toggleRotation();

protected:
	virtual void paintEvent (QPaintEvent * event);
	virtual void renderSpinner();
	
private slots:
	void _rotation_update();

private:
	int _currentStep;

	int _linesCount;
	int _linesWidth;
	QColor _linesColor;
	
	qreal _insetFactor;

	bool _useFixedSize;
	bool _roundedCap;

	QTimer _timerRotation;

	QSize _fixedSize;
};

#endif // SPINNERWIDGET_H
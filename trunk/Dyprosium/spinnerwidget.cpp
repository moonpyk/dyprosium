#include "spinnerwidget.h"

#include <QPen>
#include <QPointF>
#include <QPainter>

#include <cmath>

#define MATH_PI 3.14159265358979323846

// CTor

SpinnerWidget::SpinnerWidget(QWidget * parent /*= NULL*/, int interval /*= 50*/, bool start /*= true*/)
: QWidget(parent) {
	_currentStep	= 0;

	_linesCount		= 12;
	_linesWidth		= 4;
	_linesColor		= Qt::black;

	_insetFactor	= 0.7;

	_roundedCap		= true;

	_useFixedSize	= false;
	_fixedSize		= QSize(32, 32);

	_timerRotation.setInterval(interval);
	
	QObject::connect(&_timerRotation, SIGNAL(timeout()), this, SLOT(_rotation_update()));

	if(start) {
		startRotation();
	}
}

// Properties

int SpinnerWidget::linesCount() const {
	return _linesCount;
}

void SpinnerWidget::setLinesCount(int val) {
	_linesCount = val;

	update();
}

int SpinnerWidget::linesWidth() const {
	return _linesWidth;
}

void SpinnerWidget::setLinesWidth(int val) {
	_linesWidth = val;

	update();
}

QColor SpinnerWidget::linesColor() const {
	return _linesColor;
}

void SpinnerWidget::setLinesColor(QColor val) {
	_linesColor = val;

	update();
}

qreal SpinnerWidget::insetFactor() const {
	return _insetFactor;
}

void SpinnerWidget::setInsetFactor(qreal val) {
	_insetFactor = val;

	update();
}

bool SpinnerWidget::useFixedSize() const {
	return _useFixedSize;
}

void SpinnerWidget::setUseFixedSize(bool val) {
	_useFixedSize = val;

	update();
}

QSize SpinnerWidget::fixedSize() const {
	return _fixedSize;
}

void SpinnerWidget::setFixedSize(QSize val) {
	_fixedSize = val;

	update();
}

bool SpinnerWidget::roundedCap() const {
	return _roundedCap;
}

void SpinnerWidget::setRoundedCap(bool val) {
	_roundedCap = val;

	update();
}

int SpinnerWidget::rotationInterval() const {
	return _timerRotation.interval();
}

void SpinnerWidget::setRotationInterval(int val) {
	_timerRotation.setInterval(val);
}

QSize SpinnerWidget::spinnerSize() const {
	if(_useFixedSize) {
		return fixedSize();

	} else {
		return size() - QSize(_linesWidth, _linesWidth);
	}
}

Qt::PenCapStyle SpinnerWidget::capStyle() const {
	return _roundedCap ? Qt::RoundCap : Qt::SquareCap;
}

bool SpinnerWidget::isRotationStarted() const {
	return _timerRotation.isActive();
}

// Public slots

void SpinnerWidget::startRotation() {
	_timerRotation.start();
}

void SpinnerWidget::stopRotation() {
	_timerRotation.stop();
}

void SpinnerWidget::toggleRotation() {
	isRotationStarted() ? stopRotation() : startRotation();
}

// Protected event handlers

void SpinnerWidget::paintEvent(QPaintEvent * event) {
	renderSpinner();

	QWidget::paintEvent(event);
}

void SpinnerWidget::renderSpinner() {
	qreal x = (width() / 2);
	qreal y = (height() / 2);

	qreal radius	= qMin( spinnerSize().width() / 2 , spinnerSize().height() / 2 );
	qreal half		= _linesCount / 2;	

	QPainter painter(this);        
	painter.setRenderHint(QPainter::Antialiasing);

	QPen pen;
	pen.setWidth(_linesWidth);
	pen.setCapStyle(capStyle());

	for (int i = 0 ; i < _linesCount ; i++) {
		qreal inset		= _insetFactor * radius;
		qreal alpha		= ((qreal)(((i + _linesCount) - _currentStep) % _linesCount)) / ((qreal) _linesCount);

		QColor color(_linesColor);
		color.setAlpha(alpha * 255);

		pen.setColor(color);

		qreal angle = ((i * MATH_PI) / half); 

		QPointF start(
			x + ((radius - inset) * cos(angle)),
			y + ((radius - inset) * sin(angle))
			);

		QPointF end(
			x + (radius * cos(angle)),
			y + (radius * sin(angle))
			);	

		painter.setPen(pen);
		painter.drawLine(start, end);
	}
}

// Private slots

void SpinnerWidget::_rotation_update() {
	_currentStep = (_currentStep + 1) % _linesCount;
	update();
}

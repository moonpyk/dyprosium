#include "pieprogressindicator.h"

#include <QPainter>
#include <QPen>
#include <QRectF>

PieProgressIndicator::PieProgressIndicator(QWidget *parent) : QWidget(parent) {
	_value		= 0;

	_minValue	= 0;
	_maxValue	= 100;
}

PieProgressIndicator::~PieProgressIndicator() {

}

void PieProgressIndicator::paintEvent(QPaintEvent * event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.translate(width() / 2, height() / 2);

	qreal mainRadius = qMin( width() , height() );
	qreal innerRadus = mainRadius * 0.9;

	painter.setBrush(Qt::black);
	painter.setPen(Qt::black);

	painter.drawEllipse(QRectF(-mainRadius / 2.0, -mainRadius / 2.0, mainRadius, mainRadius));

	int angle = _angle();

	if(angle) {
		painter.setBrush(Qt::gray);
		painter.setPen(Qt::gray);

		painter.drawPie(QRectF(-innerRadus / 2.0, -innerRadus / 2.0, innerRadus, innerRadus), 90 * 16, angle);
	}
}

int PieProgressIndicator::_angle() {
	return (((qreal)_value / (qreal)_maxValue) * -5760);
}

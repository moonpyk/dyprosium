#include "titlewidget.h"

#include <QTextDocument> // Qt::mightBeRichText : bool

// CTOr

TitleWidget::TitleWidget(QWidget *parent) : QWidget(parent) {
	_initWidgets();
}

TitleWidget::~TitleWidget() {}

// Properties

QString TitleWidget::text() const {
	return _textLabel->text();
}

void TitleWidget::setText(const QString &text, Qt::Alignment alignment /*= Qt::AlignLeft | Qt::AlignVCenter*/) {
	_textLabel->setVisible(!text.isNull());
	
	if (!Qt::mightBeRichText(text)) {
		_textLabel->setStyleSheet("QLabel { font-weight: bold; }");
	}
	
	_textLabel->setText(text);
	_textLabel->setAlignment(alignment);
	
	this->show();
}

QString TitleWidget::comment() const {
	return _commentLabel->text();
}

void TitleWidget::setComment(const QString &comment, MessageType type /*= PlainMessage*/) {
	_commentVisible = !comment.isNull();
	_commentLabel->setVisible(_commentVisible);
	
	QString styleSheet;
	switch (type) {
			//FIXME: we need the usability color styles to implement different
			//       yet palette appropriate colours for the different use cases!
			//       also .. should we include an icon here,
			//       perhaps using the imageLabel?
		case InfoMessage:
		case WarningMessage:
		case ErrorMessage:
			styleSheet = QString("QLabel { color: palette(highlighted-text); background: palette(highlight); }");
			break;
		case PlainMessage:
		default:
			break;
	}
	
	//TODO: should we override the current icon with the corresponding MessageType icon?
	_commentLabel->setStyleSheet(styleSheet);
	_commentLabel->setText(comment);
	
	this->show();
	
}

const QPixmap * TitleWidget::pixmap() const {
	return _imageLabel->pixmap();
}

void TitleWidget::setPixmap(const QPixmap &pixmap, ImageAlignment alignment /*= ImageRight*/) {
	_imageLabel->setVisible(!pixmap.isNull());

	int rowSpan = _commentVisible ? 2 : 1;
	
	_headerLayout->removeWidget(_textLabel);
	_headerLayout->removeWidget(_commentLabel);
	_headerLayout->removeWidget(_imageLabel);

	if (alignment == ImageLeft) {
		// swap the text and image labels around
		_headerLayout->addWidget(_imageLabel, 0, 0, rowSpan, 1);
		_headerLayout->addWidget(_textLabel, 0, 1);
		
		_headerLayout->addWidget(_commentLabel, 1, 1);

		_headerLayout->setColumnStretch(0, 0);
		_headerLayout->setColumnStretch(1, 1);
		
	} else {
		_headerLayout->addWidget(_textLabel, 0, 0);
		_headerLayout->addWidget(_commentLabel, 1, 0);
		_headerLayout->addWidget(_imageLabel, 0, 1, rowSpan, 1);

		_headerLayout->setColumnStretch(1, 0);
		_headerLayout->setColumnStretch(0, 1);
	}
	
	_imageLabel->setPixmap(pixmap);
}

void TitleWidget::setWidget(QWidget *widget) {
	_headerLayout->addWidget(widget, 2, 0, 1, 2);
}

QWidget * TitleWidget::buddy() {
	return _textLabel->buddy();
}

void TitleWidget::setBuddy(QWidget *buddy) {
	_textLabel->setBuddy(buddy);
}

void TitleWidget::setMargin(int val) {
	_headerLayout->setMargin(val);
}

int TitleWidget::margin() const {
	return _headerLayout->margin();
}

int TitleWidget::spacing() const {
	return _headerLayout->spacing();
}

void TitleWidget::setSpacing(int spacing) {
	_headerLayout->setSpacing(spacing);
}

// Private methods

void TitleWidget::_initWidgets() {
	QFrame *titleFrame = new QFrame(this);

	titleFrame->setAutoFillBackground(true);
	titleFrame->setFrameShape(QFrame::StyledPanel);
	titleFrame->setFrameShadow(QFrame::Plain);
	titleFrame->setBackgroundRole(QPalette::Base);

	// default image / text part start
	_headerLayout = new QGridLayout(titleFrame);
	_headerLayout->setColumnStretch(0, 1);
	_headerLayout->setMargin(6);

	_textLabel = new QLabel(titleFrame);
	_textLabel->setVisible(false);

	_imageLabel = new QLabel(titleFrame);
	_imageLabel->setVisible(false);

	_headerLayout->addWidget(_textLabel, 0, 0);
	_headerLayout->addWidget(_imageLabel, 0, 1, 1, 2);

	_commentLabel = new QLabel(titleFrame);
	_commentVisible = false;
	_commentLabel->setVisible(false);

	_headerLayout->addWidget(_commentLabel, 1, 0);

	// default image / text part end

	QVBoxLayout * mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(titleFrame);
	mainLayout->setMargin(0);

	setLayout(mainLayout);
}

#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QGridLayout>

class TitleWidget : public QWidget {
	Q_OBJECT
	
public:
	TitleWidget(QWidget *parent = 0);
	virtual ~TitleWidget();

public:
	Q_ENUMS(ImageAlignment)
	enum ImageAlignment {
			ImageLeft, 
			ImageRight 
	};

	Q_ENUMS(MessageType)
	enum MessageType {
		PlainMessage, 
		InfoMessage, 
		WarningMessage, 
		ErrorMessage 
	};

public:
	// Properties
	Q_PROPERTY(QString text READ text WRITE setText);
	Q_PROPERTY(QString comment READ comment WRITE setComment);
	Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap);
	Q_PROPERTY(int margin READ margin WRITE setMargin);
	Q_PROPERTY(int spacing READ spacing WRITE setSpacing);

	QString text() const;
	QString comment() const;

	const QPixmap *pixmap() const;

	int margin() const;
	int spacing() const;
	 
	void setWidget(QWidget *widget);

	QWidget * buddy();
	void setBuddy(QWidget *buddy);

public slots:
	// Property Slot Setters
	void setText(const QString &text, Qt::Alignment alignment = Qt::AlignLeft | Qt::AlignVCenter);
	void setComment(const QString &comment, MessageType type = PlainMessage);
	void setPixmap(const QPixmap &pixmap, ImageAlignment alignment = ImageRight);
	void setMargin(int val);
	void setSpacing(int spacing);

private:
	void _initWidgets();

private:
	 QGridLayout * _headerLayout;
	 QLabel * _imageLabel;
	 QLabel * _textLabel;
	 QLabel * _commentLabel;

	 bool _commentVisible;
};

#endif // TITLEWIDGET_H

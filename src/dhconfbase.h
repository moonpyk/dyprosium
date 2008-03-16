#ifndef DHCONFBASE_H
#define DHCONFBASE_H

#include <QObject>
#include <QXmlStreamWriter>

#include "dhenums.h"

#define DYPROSIUM_FILE_VERSION "Beta"

struct DHOptionDuet {
	DHOptionDuet();
	DHOptionDuet(DHOptionType type, QString value);
	DHOptionDuet(const DHOptionDuet& duet); 

	#pragma region Operators

	inline bool operator == (DHOptionDuet duet) const { return equals(duet); }
	inline bool operator != (DHOptionDuet duet) const { return !equals(duet); }

	inline bool operator < (DHOptionDuet duet) const { return !equals(duet); }
	inline bool operator > (DHOptionDuet duet) const { return !equals(duet); }

	#pragma endregion
	
	// Methods
	void flushConfiguration(QXmlStreamWriter * stream) const;

	bool equals(DHOptionDuet duet) const;
	bool equals(DHOptionDuet * p_duet) const;
	
	// Variables
	DHOptionType type;
	QString value;
};

class DHConfigurationBase : public QObject {
	Q_OBJECT

public:
	Q_PROPERTY(QString name READ name WRITE setName);
	Q_PROPERTY(QString name READ description WRITE setDescription);

	virtual QString name() const;
	virtual void setName(QString val);

	virtual QString description() const;
	virtual void setDescription(QString val);

public:
	void flushBaseConfInformations(QXmlStreamWriter * stream);

private:
	QString _name;
	QString _description;
};

#endif //DHCONFBASE_H

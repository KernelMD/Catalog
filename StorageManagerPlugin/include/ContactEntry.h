#ifndef CONTACTENTRY_H
#define CONTACTENTRY_H

#include <QObject>
#include <QString>
#include <QStringList>

class ContactEntry : public QObject
{
	Q_OBJECT

	Q_PROPERTY(int ident READ Ident)
	Q_PROPERTY(QString name READ Name WRITE setName NOTIFY NameChanged)
	Q_PROPERTY(QString iconName READ IconName WRITE setIconName
			   NOTIFY IconNameChanged)
public:
	explicit ContactEntry(int ident, QObject *parent = 0);
	~ContactEntry();

	int Ident() const;
	const QString& Name() const;
	const QString& IconName() const;

	ContactEntry* Clone() const;
public slots:
	void setName(const QString& name);
	void setIconName(const QString& iconName);
signals:
	void NameChanged(const QString&);
	void IconNameChanged(const QString&);
private:
	const int m_ident;
	QString m_name;
	QString m_iconName;
};

#endif // CONTACTENTRY_H

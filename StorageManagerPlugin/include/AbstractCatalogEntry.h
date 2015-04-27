#ifndef ABSTRACTCATALOGENTRY_H
#define ABSTRACTCATALOGENTRY_H

#include <QObject>
#include <QString>

class AbstractCatalogEntry : public QObject {
	Q_OBJECT
public:
	/**
	 * @brief The EntryType enum signifies type of entry.
	 */
	enum EntryType { Category, Item, Invalid };

	Q_PROPERTY(EntryType type READ Type)
	Q_PROPERTY(int ident READ Ident)
	Q_PROPERTY(int parentIdent READ ParentIdent WRITE setParentIdent
			   NOTIFY ParentIdentChanged)
	Q_PROPERTY(QString name READ Name WRITE setName NOTIFY NameChanged)
	Q_PROPERTY(QString iconName READ IconName WRITE setIconName
			   NOTIFY IconNameChanged)

	EntryType Type() const;
	int Ident() const;
	int ParentIdent() const;
	const QString& Name() const;
	const QString& IconName() const;

	virtual AbstractCatalogEntry* Clone() const = 0;
public slots:
	void setParentIdent(int parentIdent);
	void setName(const QString& name);
	void setIconName(const QString& iconPath);
signals:
	void ParentIdentChanged(int);
	void NameChanged(const QString&);
	void IconNameChanged(const QString&);
protected:
	// Prevent instantiation by user.
	AbstractCatalogEntry(EntryType type, int ident, QObject* parent = 0);

	const EntryType m_type;
	const int m_ident;
	int m_parentIdent;
	QString m_name;
	QString m_iconName;
};

#endif // ABSTRACTCATALOGENTRY_H

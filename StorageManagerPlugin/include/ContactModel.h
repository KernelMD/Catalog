#ifndef CONTACTMODEL_H
#define CONTACTMODEL_H

#include <QAbstractListModel>
#include <QByteArray>
#include <QHash>
#include <QList>
#include "../include/ContactEntry.h"

class ContactModel : public QAbstractListModel {
	Q_OBJECT
public:
	enum Roles {
		identRole = Qt::UserRole + 1,
		nameRole,
		iconNameRole,
	};

	ContactModel(QObject* parent = 0);
	~ContactModel();

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role) const;
	/// Appends copy of entry to the model.
	Q_INVOKABLE void Append(const ContactEntry* entry);
	Q_INVOKABLE void Clear();

	QHash<int, QByteArray> roleNames() const;
private:
	QList<ContactEntry*> m_data;
};

#endif // CONTACTMODEL_H

#ifndef CATALOGMODEL_H
#define CATALOGMODEL_H

#include <QAbstractListModel>
#include <QByteArray>
#include <QHash>
#include <QList>
#include "../include/AbstractCatalogEntry.h"

class CatalogModel : public QAbstractListModel {
	Q_OBJECT
public:
	enum Roles {
		typeRole = Qt::UserRole + 1,
		identRole,
		parentIdentRole,
		nameRole,
		iconNameRole,
		// This is only for ItemCatalogEntry'es.
		costRole
	};

	CatalogModel(QObject* parent = 0);
	~CatalogModel();

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role) const;
	/// Appends copy of entry to the model.
	Q_INVOKABLE void Append(const AbstractCatalogEntry* entry);
	Q_INVOKABLE void Clear();

	QHash<int, QByteArray> roleNames() const;
private:
	QList<AbstractCatalogEntry*> m_data;
};

#endif // CATALOGMODEL_H

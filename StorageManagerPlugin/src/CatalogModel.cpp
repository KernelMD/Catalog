#include "../include/CatalogModel.h"
#include "../include/CategoryCatalogEntry.h"
#include "../include/CommodityCatalogEntry.h"

CatalogModel::CatalogModel(QObject* parent) : QAbstractListModel(parent){
}

CatalogModel::~CatalogModel() {
	for (QList<AbstractCatalogEntry*>::iterator i = m_data.begin();
			i != m_data.end(); ++i)
		delete *i;
	m_data.clear();
}

int CatalogModel::rowCount(const QModelIndex& parent) const {
	Q_UNUSED(parent);
	return m_data.size();
}


QVariant CatalogModel::data(const QModelIndex& index, int role) const {
	if (index.row() < 0 || index.row() > m_data.size())
		return QVariant();
	switch (role) {
	case typeRole:
		return m_data[index.row()]->Type();
		break;
	case identRole:
		return m_data[index.row()]->Ident();
		break;
	case parentIdentRole:
		return m_data[index.row()]->ParentIdent();
		break;
	case nameRole:
		return m_data[index.row()]->Name();
		break;
	case iconNameRole:
		return m_data[index.row()]->IconName();
		break;
	case costRole:
		if (m_data[index.row()]->Type() == AbstractCatalogEntry::Item)
			return ((CommodityCatalogEntry*)m_data[index.row()])
					->Cost();
		else
			return QVariant();
		break;
	default:
		return QVariant();
		break;
	}
}

void CatalogModel::Append(const AbstractCatalogEntry *entry) {
	beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
	m_data.append(entry->Clone());
	endInsertRows();
}

void CatalogModel::Clear() {
	beginRemoveRows(QModelIndex(), 0, m_data.size());
	for (QList<AbstractCatalogEntry*>::size_type i = 0; i < m_data.size(); i++)
		delete m_data[i];
	m_data.clear();
	endRemoveRows();
}

QHash<int, QByteArray> CatalogModel::roleNames() const {
	static QHash<int, QByteArray> roles;
	if (roles.empty()) { // Init map only once.
		roles[typeRole] = "type";
		roles[identRole] = "ident";
		roles[parentIdentRole] = "parentIdent";
		roles[nameRole] = "name";
		roles[iconNameRole] = "iconName";
		roles[costRole] = "cost";
	}
	return roles;
}

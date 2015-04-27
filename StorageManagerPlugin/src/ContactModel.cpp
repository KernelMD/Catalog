#include "../include/ContactModel.h"

ContactModel::ContactModel(QObject* parent) : QAbstractListModel(parent) {
}

ContactModel::~ContactModel() {
	for (QList<ContactEntry*>::iterator i = m_data.begin(); i != m_data.end(); ++i)
		delete *i;
	m_data.clear();
}

int ContactModel::rowCount(const QModelIndex& parent) const {
	Q_UNUSED(parent);
	return m_data.size();
}

QVariant ContactModel::data(const QModelIndex& index, int role) const {
	if (index.row() < 0 || index.row() > m_data.size())
		return QVariant();
	switch (role) {
	case identRole:
		return m_data[index.row()]->Ident();
		break;
	case nameRole:
		return m_data[index.row()]->Name();
		break;
	case iconNameRole:
		return m_data[index.row()]->IconName();
		break;
	default:
		return QVariant();
		break;
	}
}

void ContactModel::Append(const ContactEntry *entry) {
	m_data.append(entry->Clone());
}

void ContactModel::Clear() {
	beginRemoveRows(QModelIndex(), 0, m_data.size());
	for (QList<ContactEntry*>::size_type i = 0; i < m_data.size(); i++)
		delete m_data[i];
	m_data.clear();
	endRemoveRows();
}

QHash<int, QByteArray> ContactModel::roleNames() const {
	static QHash<int, QByteArray> roles;
	if (roles.empty()) { // Initialize only once.
		roles[identRole] = "ident";
		roles[nameRole] = "name";
		roles[iconNameRole] = "iconName";
	}
	return roles;
}

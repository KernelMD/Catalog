#include "include/AbstractCatalogEntry.h"

AbstractCatalogEntry::EntryType AbstractCatalogEntry::Type() const {
	return m_type;
}

int AbstractCatalogEntry::Ident() const {
	return m_ident;
}

int AbstractCatalogEntry::ParentIdent() const {
	return m_parentIdent;
}

const QString&AbstractCatalogEntry::Name() const {
	return m_name;
}

const QString&AbstractCatalogEntry::IconName() const {
	return m_iconName;
}

void AbstractCatalogEntry::setParentIdent(int parentIdent) {
	if (parentIdent != m_parentIdent) {
		m_parentIdent = parentIdent;
		emit ParentIdentChanged(parentIdent);
	}
}

void AbstractCatalogEntry::setName(const QString& name) {
	if (name != m_name) {
		m_name = name;
		emit NameChanged(name);
	}
}

void AbstractCatalogEntry::setIconName(const QString& iconName) {
	if (iconName != m_iconName) {
		m_iconName = iconName;
		emit IconNameChanged(iconName);
	}
}

AbstractCatalogEntry::AbstractCatalogEntry(AbstractCatalogEntry::EntryType type,
		int ident, QObject* parent) : QObject(parent), m_type(type),
		m_ident(ident) { }

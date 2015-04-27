#include "include/ContactEntry.h"

ContactEntry::ContactEntry(int ident, QObject* parent) : QObject(parent), m_ident(ident) {
}

ContactEntry::~ContactEntry() { }

int ContactEntry::Ident() const{
	return m_ident;
}

const QString&ContactEntry::Name() const {
	return m_name;
}

const QString&ContactEntry::IconName() const {
	return m_iconName;
}

ContactEntry* ContactEntry::Clone() const {
	ContactEntry* copy = new ContactEntry(this->m_ident);
	copy->setName(this->m_name);
	copy->setIconName(this->m_iconName);
	return copy;
}

void ContactEntry::setName(const QString& name) {
	if (name != m_name) {
		m_name = name;
		emit NameChanged(name);
	}
}

void ContactEntry::setIconName(const QString& iconName) {
	if (iconName != m_iconName) {
		m_iconName = iconName;
		emit IconNameChanged(iconName);
	}
}

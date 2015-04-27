#include "include/CategoryCatalogEntry.h"

CategoryCatalogEntry::CategoryCatalogEntry(int ident, QObject* parent) :
		AbstractCatalogEntry(AbstractCatalogEntry::Category, ident, parent){ }

CategoryCatalogEntry::~CategoryCatalogEntry() { }

AbstractCatalogEntry* CategoryCatalogEntry::Clone() const {
	CategoryCatalogEntry* copy = new CategoryCatalogEntry(m_ident);
	copy->setParentIdent(this->m_parentIdent);
	copy->setName(this->m_name);
	copy->setIconName(this->m_iconName);
	return copy;
}

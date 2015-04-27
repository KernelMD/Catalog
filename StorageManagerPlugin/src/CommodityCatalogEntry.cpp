#include "include/CommodityCatalogEntry.h"

CommodityCatalogEntry::CommodityCatalogEntry(int ident, QObject* parent) :
		AbstractCatalogEntry(AbstractCatalogEntry::Item, ident, parent) { }

CommodityCatalogEntry::~CommodityCatalogEntry() { }

const QString& CommodityCatalogEntry::Cost() const {
	return m_cost;
}

AbstractCatalogEntry* CommodityCatalogEntry::Clone() const {
	CommodityCatalogEntry* copy = new CommodityCatalogEntry(this->m_ident);
	copy->setParentIdent(this->m_parentIdent);
	copy->setName(this->m_name);
	copy->setIconName(this->m_iconName);
	copy->setCost(this->m_cost);
	return copy;
}

void CommodityCatalogEntry::setCost(const QString& cost) {
	if (cost != m_cost) {
		m_cost = cost;
		emit CostChanged(cost);
	}
}

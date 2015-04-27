#ifndef CATEGORYCATALOGENTRY_H
#define CATEGORYCATALOGENTRY_H

#include <QObject>
#include "../include/AbstractCatalogEntry.h"

class CategoryCatalogEntry : public AbstractCatalogEntry {
	Q_OBJECT
public:
	explicit CategoryCatalogEntry(int ident, QObject *parent = 0);
	~CategoryCatalogEntry();
	AbstractCatalogEntry* Clone() const;
};

#endif // CATEGORYCATALOGENTRY_H

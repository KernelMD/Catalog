#ifndef COMMODITYCATALOGENTRY_H
#define COMMODITYCATALOGENTRY_H

#include <QObject>
#include <QString>
#include "../include/AbstractCatalogEntry.h"

class CommodityCatalogEntry : public AbstractCatalogEntry {
	Q_OBJECT

	Q_PROPERTY(QString cost READ Cost WRITE setCost NOTIFY CostChanged)
public:
	explicit CommodityCatalogEntry(int ident, QObject *parent = 0);
	~CommodityCatalogEntry();

	const QString& Cost() const;

	AbstractCatalogEntry* Clone() const;
public slots:
	void setCost(const QString& cost);
signals:
	void CostChanged(const QString&);
private:
	QString m_cost;
};

#endif // COMMODITYCATALOGENTRY_H

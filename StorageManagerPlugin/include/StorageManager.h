#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QThread>
#include "../include/CatalogModel.h"
#include "../include/ContactModel.h"
#include "../include/Commodity.h"
#include "../include/Contact.h"
#include "../include/SyncManager.h"

class StorageManager : public QObject
{
	Q_OBJECT
	Q_PROPERTY(const QString cachePath READ CachePath)
public:
	explicit StorageManager(QObject *parent = 0);
	~StorageManager();

	const QString& CachePath() const;

	// Creates and returns content of some category (root is represented via
	// implicit parent, with ident = 0).
	// WARNING! Result should be deleted later.
	Q_INVOKABLE CatalogModel* GetCategoryContent(int parentIdent = 0) const;
	// Creates and returns list of contacts.
	// WARNING! Result should be deleted later.
	Q_INVOKABLE ContactModel* GetContactList() const;
	// WARNING! Result should be deleted later.
	Q_INVOKABLE Commodity* GetCommodity(int itemIdent) const;
	// WARNING! Result should be deleted later.
	Q_INVOKABLE Contact* GetContact(int contactIdent) const;
	Q_INVOKABLE void UpdateStorage();
private:
	const QString m_defaultCachePath;
	QSqlDatabase m_localDB;
	QThread m_syncThread;
private slots:
	void HandleSyncResults(int exitCode);
signals:
	void StartSync();
	void AbortSync();
};

#endif // STORAGEMANAGER_H

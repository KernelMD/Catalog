#include "include/StorageManager.h"
#include "../include/CategoryCatalogEntry.h"
#include "../include/CommodityCatalogEntry.h"
#include "../include/ContactEntry.h"
#include "../include/SyncManager.h"
#include <QDir>
#include <QFile>
#include <QSqlQuery>

#include <QDebug>

StorageManager::StorageManager(QObject *parent) : QObject(parent),
		m_defaultCachePath(
			// Some black magic to set path, depending on the target platform.
			#ifdef __ANDROID__
				"/sdcard/Android/data/com.KernelMD.Catalog/"
			#elif _WIN32
				".\\Data\\"
			#elif __linux__
				"./Data/"
			#endif
		) {
	m_localDB = QSqlDatabase::addDatabase("QSQLITE");
	m_localDB.setDatabaseName(m_defaultCachePath + "db.sqlite");
	m_localDB.open();
}

StorageManager::~StorageManager() {
	m_localDB.close();
	emit AbortSync();
	m_syncThread.quit();
	m_syncThread.wait();
}

const QString&StorageManager::CachePath() const {
	return m_defaultCachePath;
}

CatalogModel* StorageManager::GetCategoryContent(int parentIdent) const {
	CatalogModel* model = new CatalogModel();

	QString query_start_str = "SELECT id, parent_id, name, icon_name ";
	QString query_end_str = "WHERE parent_id = " +
		QString::number(parentIdent) + ';';

	// Firstly, process categories.
	QSqlQuery query;
	query.exec(query_start_str + "FROM categories " + query_end_str);
	while (query.next()) {
		CategoryCatalogEntry entry(query.value(0).toInt());
		entry.setParentIdent(query.value(1).toInt());
		entry.setName(query.value(2).toString());
		entry.setIconName(query.value(3).toString());

		model->Append(&entry);
	}

	// Now, repeat for the items.
	query.clear();
	query.exec(query_start_str + ", cost FROM items " + query_end_str);
	while (query.next()) {
		CommodityCatalogEntry entry(query.value(0).toInt());
		entry.setParentIdent(query.value(1).toInt());
		entry.setName(query.value(2).toString());
		entry.setIconName(query.value(3).toString());
		entry.setCost(query.value(4).toString());

		model->Append(&entry);
	}

	return model;
}

ContactModel* StorageManager::GetContactList() const {
	ContactModel* model = new ContactModel();
	QString query_str = "SELECT id, name, icon_name FROM contacts";

	QSqlQuery query;
	query.exec(query_str);
	while (query.next()) {
		ContactEntry contact(query.value(0).toInt());
		contact.setName(query.value(1).toString());
		contact.setIconName(query.value(2).toString());

		model->Append(&contact);
	}

	return model;
}

Commodity* StorageManager::GetCommodity(int itemIdent) const {
	Commodity* res = new Commodity();
	QString query_str =
		"SELECT name,description,image_name,cost FROM items WHERE id=" +
		QString::number(itemIdent) + ';';

	QSqlQuery query;
	query.exec(query_str);
	query.next();
	res->setName(query.value(0).toString());
	res->setDescription(query.value(1).toString());
	res->setImageName(query.value(2).toString());
	res->setCost(query.value(3).toString());

	return res;
}

Contact* StorageManager::GetContact(int contactIdent) const {
	Contact* res = new Contact();

	QSqlQuery query;
	query.exec("SELECT name,image_name FROM contacts WHERE id=" +
			   QString::number(contactIdent) + ';');

	query.next();
	res->setName(query.value(0).toString());
	res->setImageName(query.value(1).toString());

	QString query_start_str = "SELECT text FROM ";
	QString query_end_str = " WHERE contact_id=" +
			QString::number(contactIdent) + ';';

	query.clear();
	query.exec(query_start_str + "contact_addresses" + query_end_str);
	QList<QString> tmpList;
	while (query.next())
		tmpList.append(query.value(0).toString());
	res->setAddresses(tmpList);

	query.clear();
	query.exec(query_start_str + "contact_emails" + query_end_str);
	tmpList.clear();
	while (query.next())
		tmpList.append(query.value(0).toString());
	res->setEmails(tmpList);

	query.clear();
	query.exec(query_start_str + "contact_phones" + query_end_str);
	tmpList.clear();
	while (query.next())
		tmpList.append(query.value(0).toString());
	res->setPhones(tmpList);

	query.clear();
	query.exec(query_start_str + "contact_websites" + query_end_str);
	tmpList.clear();
	while (query.next())
		tmpList.append(query.value(0).toString());
	res->setWebsites(tmpList);

	return res;
}

// For now, implementing sync via direct connection to remote db.
void StorageManager::UpdateStorage() {
	// Prepare cache directory.
	QDir tmp_path(m_defaultCachePath);
	tmp_path.mkdir("tmp");
	tmp_path.cd("tmp");
	// Copy database.
	m_localDB.close();
	QFile tmp_file(m_defaultCachePath + "db.sqlite");
	tmp_file.open(QIODevice::ReadOnly);
	tmp_file.copy(tmp_path.absolutePath() + QDir::separator() + "db.sqlite");
	tmp_file.close();
	m_localDB.open();

	// Prepare sync manager.
	SyncManager* mgr = new SyncManager;

	NetworkParams remote_db_params {
		"mysql.cybersoul.ru", // address
		3306, // port
		"mobile", // login
		"zcSBVwKWbA8DGZNV" // password
	};
	mgr->SetDBServerParams(remote_db_params,"mobile_base1");
	NetworkParams remote_cache_params {
		"", // address
		0, // port
		"", // login
		"" // password
	};
	mgr->SetCacheServerParams(remote_cache_params);
	mgr->SetTempDir(m_defaultCachePath + QDir::separator() + "tmp");

	mgr->moveToThread(&m_syncThread);
	connect(&m_syncThread, &QThread::finished, mgr, &QObject::deleteLater);
	connect(this, &StorageManager::StartSync, mgr, &SyncManager::Start);
	connect(this, &StorageManager::AbortSync, mgr, &SyncManager::Stop);
	connect(mgr, &SyncManager::SyncStopped, this,
			&StorageManager::HandleSyncResults);

	m_syncThread.start();
	emit StartSync();
}

void StorageManager::HandleSyncResults(int exitCode) {
	switch (exitCode) {
	case SyncManager::Aborted:
		qDebug() << "Sync aborted";
		break;
	case SyncManager::Error:
		qDebug() << "Sync error";
		break;
	case SyncManager::Finished:
		qDebug() << "Sync finished";
		break;
	default:
		qDebug() << "Error: unknown sync status " << exitCode;
		break;
	}
}

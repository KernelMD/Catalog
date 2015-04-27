#include "../include/SyncManager.h"
#include <QSqlQuery>

SyncManager::SyncManager(QObject* parent) :
		QObject(parent), m_currentState(Finished) { }

SyncManager::~SyncManager() {
	Stop();
	m_dbCopy.close();
}

const NetworkParams&SyncManager::DBServerParams() const {
	return m_dbServerParams;
}

const NetworkParams&SyncManager::CacheServerParams() const {
	return m_cacheServerParams;
}

const QString&SyncManager::TempDir() const {
	return m_tmpDir;
}

SyncManager::SyncStatus SyncManager::Status() const {
	return m_currentState;
}

void SyncManager::SetDBServerParams(const NetworkParams& parm, const QString& dbName) {
	if (m_remoteDB.isOpen())
		m_remoteDB.close();
	m_dbServerParams = parm;
	m_remoteDB = QSqlDatabase::addDatabase("QMYSQL", "remoteConnection");
	m_remoteDB.setHostName(m_dbServerParams.address);
	m_remoteDB.setPort(m_dbServerParams.port);
	m_remoteDB.setUserName(m_dbServerParams.login);
	m_remoteDB.setPassword(m_dbServerParams.password);
	m_remoteDB.setDatabaseName(dbName);
	m_remoteDB.open();
}

void SyncManager::SetCacheServerParams(const NetworkParams& parm) {
	m_cacheServerParams = parm;
}

void SyncManager::SetTempDir(const QString& dir) {
	if (m_dbCopy.isOpen())
		m_dbCopy.close();
	m_tmpDir = dir;
	m_dbCopy = QSqlDatabase::addDatabase("QSQLITE", "tmpConnection");
	m_dbCopy.setDatabaseName(m_tmpDir + QDir::separator() + "db.sqlite");
	m_dbCopy.open();
}

void SyncManager::Start() {
	// Indicate changes sync state.
	m_currentState = Working;

	QSqlQuery tmpQuery("tmpConnection");
	QSqlQuery remoteQuery("remoteConnection");
}

void SyncManager::Stop() {
	// Indicate changes in sync state.
	if (m_currentState == Working) {
		m_currentState = Aborted;
		emit SyncStopped(m_currentState);
	}
}

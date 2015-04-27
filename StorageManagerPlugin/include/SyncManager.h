#ifndef SYNCMANAGER_H
#define SYNCMANAGER_H

#include <QDir>
#include <QList>
#include <QNetworkAccessManager>
#include <QObject>
#include <QSqlDatabase>
#include <QString>

struct NetworkParams {
	QString address;
	int port;
	QString login;
	QString password;
};

class SyncManager : public QObject
{
	Q_OBJECT
public:
	enum SyncStatus {
		Working,
		Aborted,
		Finished,
		Error
	};

	SyncManager(QObject* parent = 0);
	~SyncManager();

	const NetworkParams& DBServerParams() const;
	const NetworkParams& CacheServerParams() const;
	const QString& TempDir() const;
	enum SyncStatus Status() const;

	void SetDBServerParams(const NetworkParams& parm, const QString& dbName);
	void SetCacheServerParams(const NetworkParams& parm);
	void SetTempDir(const QString&);
public slots:
	void Start();
	void Stop();
signals:
	void SyncStopped(int);
private:
	enum SyncStatus m_currentState;

	NetworkParams m_dbServerParams;
	NetworkParams m_cacheServerParams;
	QString m_tmpDir;

	QNetworkAccessManager m_networkMgr;
	QSqlDatabase m_dbCopy;
	QSqlDatabase m_remoteDB;

	QList<QString> m_filesToDownload;
signals:
	void cacheDownloadFinished(bool success);
};

#endif // SYNCMANAGER_H

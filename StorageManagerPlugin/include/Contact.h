#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>
#include <QString>
#include <QStringList>

class Contact : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString name READ Name WRITE setName NOTIFY NameChanged)
	Q_PROPERTY(QString imageName READ ImageName
			   WRITE setImageName NOTIFY ImageNameChanged)
	Q_PROPERTY(QStringList addresses READ Addresses
			   WRITE setAddresses NOTIFY AddressesChanged)
	Q_PROPERTY(QStringList emails READ Emails
			   WRITE setEmails NOTIFY EmailsChanged)
	Q_PROPERTY(QStringList phones READ Phones
			   WRITE setPhones NOTIFY PhonesChanged)
	Q_PROPERTY(QStringList websites READ Websites
			   WRITE setWebsites NOTIFY WebsitesChanged)
public:
	explicit Contact(QObject *parent = 0);
	~Contact();

	const QString& Name() const;
	const QString& ImageName() const;
	const QStringList& Addresses() const;
	const QStringList& Emails() const;
	const QStringList& Phones() const;
	const QStringList& Websites() const;
public slots:
	void setName(const QString&name);
	void setImageName(const QString&imageName);
	void setAddresses(const QStringList&addresses);
	void setEmails(const QStringList&emails);
	void setPhones(const QStringList&phones);
	void setWebsites(const QStringList&);
signals:
	void NameChanged(const QString&);
	void ImageNameChanged(const QString&);
	void AddressesChanged();
	void EmailsChanged();
	void PhonesChanged();
	void WebsitesChanged();
private:
	QString m_name;
	QString m_imageName;
	QStringList m_addresses;
	QStringList m_emails;
	QStringList m_phones;
	QStringList m_websites;
};

#endif // CONTACT_H

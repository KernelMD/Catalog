#include "../include/Contact.h"

Contact::Contact(QObject *parent) : QObject(parent) { }

Contact::~Contact() { }


const QString&Contact::Name() const {
	return m_name;
}

const QString&Contact::ImageName() const {
	return m_imageName;
}

const QStringList&Contact::Addresses() const {
	return m_addresses;
}

const QStringList&Contact::Emails() const {
	return m_emails;
}

const QStringList&Contact::Phones() const {
	return m_phones;
}

const QStringList&Contact::Websites() const {
	return m_websites;
}

void Contact::setName(const QString& name) {
	if (name != m_name) {
		m_name = name;
		emit NameChanged(name);
	}
}

void Contact::setImageName(const QString& imageName) {
	if (imageName != m_imageName) {
		m_imageName = imageName;
		emit ImageNameChanged(imageName);
	}
}

void Contact::setAddresses(const QStringList& addresses) {
	m_addresses = addresses;
	emit AddressesChanged();
}

void Contact::setEmails(const QStringList& emails) {
	m_emails = emails;
	emit EmailsChanged();
}

void Contact::setPhones(const QStringList& phones) {
	m_phones = phones;
	emit PhonesChanged();
}

void Contact::setWebsites(const QStringList& websites) {
	m_websites = websites;
	emit WebsitesChanged();
}

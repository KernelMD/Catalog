#include "../include/Commodity.h"

Commodity::Commodity(QObject *parent) : QObject(parent) { }

Commodity::~Commodity() { }

const QString&Commodity::Description() const {
	return m_description;
}

const QString&Commodity::Name() const {
	return m_name;
}

const QString&Commodity::ImageName() const {
	return m_imageName;
}

const QString&Commodity::Cost() const {
	return m_cost;
}

void Commodity::setDescription(const QString& description) {
	if (description != m_description) {
		m_description = description;
		emit DescriptionChanged(description);
	}
}

void Commodity::setName(const QString& name) {
	if (name != m_name) {
		m_name = name;
		emit NameChanged(name);
	}
}

void Commodity::setImageName(const QString& imageName) {
	if (imageName != m_imageName) {
		m_imageName = imageName;
		emit ImageNameChanged(imageName);
	}
}

void Commodity::setCost(const QString& cost) {
	if (cost != m_cost) {
		m_cost = cost;
		emit CostChanged(cost);
	}
}

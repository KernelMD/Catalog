#ifndef COMMODITY_H
#define COMMODITY_H

#include <QObject>
#include <QString>

class Commodity : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString description READ Description
			   WRITE setDescription NOTIFY DescriptionChanged)
	Q_PROPERTY(QString name READ Name WRITE setName NOTIFY NameChanged)
	Q_PROPERTY(QString imageName READ ImageName WRITE setImageName
			   NOTIFY ImageNameChanged)
	Q_PROPERTY(QString cost READ Cost WRITE setCost NOTIFY CostChanged)
public:
	explicit Commodity(QObject *parent = 0);
	~Commodity();

	const QString& Description() const;
	const QString& Name() const;
	const QString& ImageName() const;
	const QString& Cost() const;
public slots:
	void setDescription(const QString& description);
	void setName(const QString& name);
	void setImageName(const QString& imageName);
	void setCost(const QString& cost);
signals:
	void DescriptionChanged(const QString&);
	void NameChanged(const QString&);
	void ImageNameChanged(const QString&);
	void CostChanged(const QString&);
private:
	QString m_description;
	QString m_name;
	QString m_imageName;
	QString m_cost;
};

#endif // COMMODITY_H

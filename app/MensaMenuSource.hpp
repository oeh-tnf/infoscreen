#pragma once

#include <QObject>
#include <QJsonObject>
#include <QNetworkAccessManager>
 
class MensaMenuSource : public QObject
{
	Q_OBJECT
	
	Q_PROPERTY(QJsonObject jkuJson READ jkuJson NOTIFY jkuJsonChanged)
	Q_PROPERTY(QJsonObject khgJson READ khgJson NOTIFY khgJsonChanged)

signals:
	void jkuJsonChanged(QJsonObject json);
	void khgJsonChanged(QJsonObject json);

public slots:
    void load();

public:
	explicit MensaMenuSource(QObject *parent = nullptr);
	~MensaMenuSource() override = default;

	QJsonObject jkuJson() const;
	QJsonObject khgJson() const;

private:
	QJsonObject m_jkuJson;
	QJsonObject m_khgJson;
	QNetworkAccessManager *m_qnam;
};

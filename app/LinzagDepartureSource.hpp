#pragma once

#include <QObject>
#include <QJsonObject>
#include <QNetworkAccessManager>
 
class LinzagDepartureSource : public QObject
{
	Q_OBJECT
	
	Q_PROPERTY(QString stopId READ stopId WRITE setStopId)
	Q_PROPERTY(QJsonObject json READ json NOTIFY jsonChanged)

signals:
	void jsonChanged(QJsonObject json);

public slots:
    void load();

public:
	explicit LinzagDepartureSource(QObject *parent = nullptr);
	~LinzagDepartureSource() override = default;

	QString stopId() const;
	QJsonObject json() const;

	void setStopId(QString stopId);

private:
	QString m_stopId;
	QJsonObject m_json;
	QNetworkAccessManager *m_qnam;
};

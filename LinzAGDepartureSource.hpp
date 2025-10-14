#pragma once

#include <QQmlEngine>
#include <Qt>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>
#include <QObject>
#include <QJsonObject>
#include <QNetworkAccessManager>
 
class LinzAGDepartureSource : public QObject
{
	Q_OBJECT
	QML_ELEMENT
	
	Q_PROPERTY(QString stopId MEMBER m_stopId)
	Q_PROPERTY(QJsonObject json READ json NOTIFY jsonChanged)

signals:
	void jsonChanged();

public slots:
    void load();

public:
	explicit LinzAGDepartureSource(QObject *parent = nullptr);
	~LinzAGDepartureSource() override = default;

	QJsonObject json() const;

private:
	QString m_stopId;
	QJsonObject m_json;
	QNetworkAccessManager qnam;
};

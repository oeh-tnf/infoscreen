#pragma once

#include <QQmlEngine>
#include <Qt>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>
#include <QObject>
#include <QJsonObject>
 
class LinzAGDepartureModel : public QAbstractTableModel
{
	Q_OBJECT
	QML_ELEMENT
	
	Q_PROPERTY(QJsonObject json MEMBER m_json WRITE setJson NOTIFY jsonChanged)
	Q_PROPERTY(QDateTime now MEMBER m_now WRITE setNow NOTIFY nowChanged)

signals:
	void jsonChanged();
	void nowChanged();

public:
	explicit LinzAGDepartureModel(QObject *parent = nullptr);
	~LinzAGDepartureModel() override = default;
	
	void setJson(QJsonObject &json);
	void setNow(QDateTime &now);
	
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
	QJsonObject m_json;
	QDateTime m_now;
};

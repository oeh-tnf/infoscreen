#pragma once

#include <Qt>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>
#include <QObject>
#include <QJsonObject>

class OoevvDepartureModel : public QAbstractTableModel
{
	Q_OBJECT

	Q_PROPERTY(QJsonObject json MEMBER m_json WRITE setJson)
	Q_PROPERTY(QDateTime time MEMBER m_time WRITE setTime)

public slots:
	void setJson(QJsonObject json);
	void setTime(QDateTime time);

public:
	explicit OoevvDepartureModel(QObject *parent = nullptr);
	~OoevvDepartureModel() override = default;

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
	QJsonObject m_json;
	QDateTime m_time;
};

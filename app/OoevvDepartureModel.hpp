#pragma once

#include <Qt>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>
#include <QObject>
#include <QJsonObject>

#include "DepartureModel.hpp"

class OoevvDepartureModel : public DepartureModel
{
	Q_OBJECT

	Q_PROPERTY(QJsonObject json MEMBER m_json WRITE setJson)

public slots:
	void setJson(QJsonObject json);

public:
	explicit OoevvDepartureModel(QObject *parent = nullptr);
	~OoevvDepartureModel() override = default;

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
	QJsonObject m_json;
};

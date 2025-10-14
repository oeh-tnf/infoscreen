#include <QJsonArray>

#include "LinzAGDepartureModel.hpp"

LinzAGDepartureModel::LinzAGDepartureModel(QObject *parent) :
	QAbstractTableModel(parent)
{}

void LinzAGDepartureModel::setJson(QJsonObject &json) {
	beginResetModel();
	m_json = json;
	emit jsonChanged();
	endResetModel();
}

void LinzAGDepartureModel::setNow(QDateTime &now) {
	m_now = now;
	emit nowChanged();
	emit dataChanged(index(0,2), index(m_json["stopEvents"].toArray().size()-1,2));
}

int LinzAGDepartureModel::rowCount([[maybe_unused]] const QModelIndex &parent) const
{
	return m_json["stopEvents"].toArray().size();
}

int LinzAGDepartureModel::columnCount([[maybe_unused]] const QModelIndex &parent) const
{
	return 3;
}

QVariant LinzAGDepartureModel::data(const QModelIndex &index, int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();
	if (index.column() == 0) // line number
		return m_json["stopEvents"][index.row()]["transportation"]["number"].toString();
	if (index.column() == 1) // destination
		return m_json["stopEvents"][index.row()]["transportation"]["destination"]["name"].toString().remove("Linz/Donau ");
	if (index.column() == 2) // departure time
		return m_now.secsTo(QDateTime::fromString(m_json["stopEvents"][index.row()]["departureTimePlanned"].toString(), Qt::ISODate))/60;
	return QVariant();
}

#include "moc_LinzAGDepartureModel.cpp"

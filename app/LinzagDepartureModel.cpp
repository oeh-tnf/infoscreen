#include <QJsonArray>

#include "LinzagDepartureModel.hpp"

LinzagDepartureModel::LinzagDepartureModel(QObject *parent) :
	QAbstractTableModel(parent)
{}

void LinzagDepartureModel::setJson(QJsonObject json) {
	beginResetModel();
	m_json = json;
	endResetModel();
}

void LinzagDepartureModel::setTime(QDateTime time) {
	m_time = time;
	emit dataChanged(index(0,2), index(m_json["stopEvents"].toArray().size()-1,2));
}

int LinzagDepartureModel::rowCount([[maybe_unused]] const QModelIndex &parent) const
{
	return m_json["stopEvents"].toArray().size();
}

int LinzagDepartureModel::columnCount([[maybe_unused]] const QModelIndex &parent) const
{
	return 3;
}

QVariant LinzagDepartureModel::data(const QModelIndex &index, int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();
	if (index.column() == 0) // line number
		return m_json["stopEvents"][index.row()]["transportation"]["number"].toString();
	if (index.column() == 1) // destination
		return m_json["stopEvents"][index.row()]["transportation"]["destination"]["name"].toString().remove("Linz/Donau ");
	if (index.column() == 2) // departure time
	{
		QString rawTime = m_json["stopEvents"][index.row()]["departureTimeEstimated"].toString(m_json["stopEvents"][index.row()]["departureTimePlanned"].toString());
		return m_time.secsTo(QDateTime::fromString(rawTime, Qt::ISODate))/60;
	}
	return QVariant();
}

#include "moc_LinzagDepartureModel.cpp"

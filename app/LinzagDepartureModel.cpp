#include <QJsonArray>

#include "LinzagDepartureModel.hpp"

LinzagDepartureModel::LinzagDepartureModel(QObject *parent) :
	DepartureModel(parent)
{}

void LinzagDepartureModel::setJson(QJsonObject json) {
	beginResetModel();
	m_json = json;
	endResetModel();
}

int LinzagDepartureModel::rowCount([[maybe_unused]] const QModelIndex &parent) const
{
	return m_json["stopEvents"].toArray().size();
}

static QHash<QString,QString> lineColors = {
	{"1", "#ed3f80"},
	{"2", "#c57eb5"},
	{"77", "#945437"}
};

QVariant LinzagDepartureModel::data(const QModelIndex &index, int role) const
{
	if (role == LineRole)
		return m_json["stopEvents"][index.row()]["transportation"]["number"].toString();
	if (role == LineColorRole)
		return lineColors.value(data(index, LineRole).toString(), "#f37d21");
	if (role == DirectionRole)
		return m_json["stopEvents"][index.row()]["transportation"]["destination"]["name"].toString().remove("Linz/Donau ");
	if (role == TimeRole)
	{
		QString rawTime = m_json["stopEvents"][index.row()]["departureTimeEstimated"].toString(m_json["stopEvents"][index.row()]["departureTimePlanned"].toString());
		return QDateTime::fromString(rawTime, Qt::ISODate);
	}
	return QVariant();
}

#include "moc_LinzagDepartureModel.cpp"

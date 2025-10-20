#include "OoevvDepartureModel.hpp"

#include <QJsonArray>

OoevvDepartureModel::OoevvDepartureModel(QObject *parent):
	DepartureModel(parent)
{}

void OoevvDepartureModel::setJson(QJsonObject json)
{
	beginResetModel();
	m_json = json;
	endResetModel();
}

int OoevvDepartureModel::rowCount(const QModelIndex &parent) const
{
	return m_json["jnyL"].toArray().size();
}

QVariant OoevvDepartureModel::data(const QModelIndex &index, int role) const
{
	if (role == LineRole)
		return m_json["common"]["prodL"][m_json["jnyL"][index.row()]["prodX"].toInt(-1)]["number"].toString();
	if (role == LineColorRole)
		return "#e94c4b";
	if (role == DirectionRole)
		return m_json["jnyL"][index.row()]["dirTxt"].toString()
			.remove("Linz ")
			.remove(" via JKU")
			.replace("Hbf", "Hauptbahnhof");
	if (role == TimeRole)
	{
		QDate date = QDate::fromString(m_json["jnyL"][index.row()]["date"].toString(), "yyyyMMdd");
		QString rawTime = m_json["jnyL"][index.row()]["stbStop"]["dTimeR"].toString(m_json["jnyL"][index.row()]["stbStop"]["dTimeS"].toString());
		return QDateTime(date, QTime::fromString(rawTime, "hhmmss"));
	}
	return QVariant();
}


#include "moc_OoevvDepartureModel.cpp"

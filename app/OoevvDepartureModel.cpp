#include "OoevvDepartureModel.hpp"

#include <QJsonArray>

OoevvDepartureModel::OoevvDepartureModel(QObject *parent):
	QAbstractTableModel(parent)
{}

void OoevvDepartureModel::setJson(QJsonObject json)
{
	beginResetModel();
	m_json = json;
	endResetModel();
}

void OoevvDepartureModel::setTime(QDateTime time)
{
	m_time = time;
	emit dataChanged(index(0,2), index(rowCount()-1,2));
}

int OoevvDepartureModel::rowCount(const QModelIndex &parent) const
{
	return m_json["jnyL"].toArray().size();
}

int OoevvDepartureModel::columnCount(const QModelIndex &parent) const
{
	return 3;
}

QVariant OoevvDepartureModel::data(const QModelIndex &index, int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();
	if (index.column() == 0) // line number
		return m_json["common"]["prodL"][m_json["jnyL"][index.row()]["prodX"].toInt(-1)]["number"].toString();
	if (index.column() == 1) // destination
		return m_json["jnyL"][index.row()]["dirTxt"].toString()
			.remove("Linz ")
			.remove(" via JKU")
			.replace("Hbf", "Hauptbahnhof");
	if (index.column() == 2) // departure time
	{
		QDate date = QDate::fromString(m_json["jnyL"][index.row()]["date"].toString(), "yyyyMMdd");
		QString rawTime = m_json["jnyL"][index.row()]["stbStop"]["dTimeR"].toString(m_json["jnyL"][index.row()]["stbStop"]["dTimeS"].toString());
		QTime time = QTime::fromString(rawTime, "hhmmss");
		return m_time.secsTo(QDateTime(date, time))/60;
	}
	return QVariant();
}


#include "moc_OoevvDepartureModel.cpp"

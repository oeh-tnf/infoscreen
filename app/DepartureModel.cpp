#include "DepartureModel.hpp"

DepartureModel::DepartureModel(QObject *parent):
	QAbstractListModel(parent)
{}

QHash<int, QByteArray> DepartureModel::roleNames() const
{
	return {
		{LineRole, "line"},
		{LineColorRole, "lineColor"},
		{DirectionRole, "direction"},
		{RealtimeRole, "realtime"},
		{TimeRole, "time"}
	};
}

#include "moc_DepartureModel.cpp"

#include "DepartureModel.hpp"

DepartureModel::DepartureModel(QObject *parent):
	QAbstractListModel(parent)
{}

QHash<int, QByteArray> DepartureModel::roleNames() const
{
	return {
		{LineRole, "line"},
		{DirectionRole, "direction"},
		{TimeRole, "time"}
	};
}

#include "moc_DepartureModel.cpp"

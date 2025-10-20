#include "DeparturesSortFilterProxyModel.hpp"

#include "DepartureModel.hpp"

DeparturesSortFilterProxyModel::DeparturesSortFilterProxyModel(QObject *parent):
	QSortFilterProxyModel(parent)
{}

void DeparturesSortFilterProxyModel::setTime(QDateTime time) {
	beginResetModel();
	m_time = time;
	endResetModel();
}

bool DeparturesSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
	return true;
	return sourceModel()->data(sourceModel()->index(source_row, 0, source_parent), DepartureModel::TimeRole).toDateTime() >= m_time;
}

#include "moc_DeparturesSortFilterProxyModel.cpp"

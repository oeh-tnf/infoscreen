#include "DeparturesSortFilterProxyModel.hpp"

DeparturesSortFilterProxyModel::DeparturesSortFilterProxyModel(QObject *parent):
	QSortFilterProxyModel(parent)
{}

bool DeparturesSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
	return sourceModel()->data(sourceModel()->index(source_row, 2, source_parent)).toInt() >= 0;
}

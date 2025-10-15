#pragma once

#include <QSortFilterProxyModel>

class DeparturesSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
	explicit DeparturesSortFilterProxyModel(QObject *parent = nullptr);
	~DeparturesSortFilterProxyModel() override = default;

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

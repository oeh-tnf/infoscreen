#pragma once

#include <QSortFilterProxyModel>
#include <QDateTime>

class DeparturesSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

	Q_PROPERTY(QDateTime time MEMBER m_time WRITE setTime)

public slots:
	void setTime(QDateTime time);

public:
	explicit DeparturesSortFilterProxyModel(QObject *parent = nullptr);
	~DeparturesSortFilterProxyModel() override = default;

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    QDateTime m_time;
};

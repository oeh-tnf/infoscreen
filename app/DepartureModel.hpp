#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QByteArray>
#include <QHash>

class DepartureModel : public QAbstractListModel
{
	Q_OBJECT

public:
	enum {
		LineRole = Qt::UserRole,
		LineColorRole,
		DirectionRole,
		CancelledRole,
		RealtimeRole,
		TimeRole
	};

public:
	explicit DepartureModel(QObject *parent = nullptr);
	~DepartureModel() override = default;

	QHash<int, QByteArray> roleNames() const override;
};

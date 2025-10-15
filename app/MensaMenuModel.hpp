#pragma once

#include <Qt>
#include <QAbstractListModel>
#include <QModelIndex>
#include <QVariant>
#include <QObject>
#include <QJsonObject>

class MensaMenuModel : public QAbstractListModel
{
	Q_OBJECT

	Q_PROPERTY(QJsonObject json MEMBER m_json WRITE setJson)

public slots:
	void setJson(QJsonObject json);

public:
	explicit MensaMenuModel(QObject *parent = nullptr);
	~MensaMenuModel() override = default;

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
	QJsonObject m_json;
};

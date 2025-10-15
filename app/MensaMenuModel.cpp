#include "MensaMenuModel.hpp"

#include <QJsonArray>

MensaMenuModel::MensaMenuModel(QObject *parent):
	QAbstractListModel(parent)
{}

void MensaMenuModel::setJson(QJsonObject json)
{
	beginResetModel();
	m_json = json;
	endResetModel();
}

int MensaMenuModel::rowCount(const QModelIndex &parent ) const
{
	return m_json["menuTypes"].toArray().size();
}

QVariant MensaMenuModel::data(const QModelIndex &index, int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();
	QString menu;
	bool first = true;
	for (QJsonValue starter : m_json["menuTypes"][index.row()]["menu"]["groupedDishes"]["STARTER"].toArray())
	{
		if (!first)
			menu.append("\n");
		first = false;
		menu.append(starter["name"].toString());
	}
	for (QJsonValue mainCourse : m_json["menuTypes"][index.row()]["menu"]["groupedDishes"]["MAIN_COURSE"].toArray())
	{
		if (!first)
			menu.append("\n");
		first = false;
		menu.append(mainCourse["name"].toString());
	}
	for (QJsonValue dessert : m_json["menuTypes"][index.row()]["menu"]["groupedDishes"]["DESSERT"].toArray())
	{
		if (!first)
			menu.append("\n");
		first = false;
		menu.append(dessert["name"].toString());
	}
	return menu;
}

#include "moc_MensaMenuModel.cpp"

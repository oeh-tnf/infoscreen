#include <QJsonDocument>
#include <QNetworkReply>
#include <iostream>

#include "LinzAGDepartureSource.hpp"

LinzAGDepartureSource::LinzAGDepartureSource(QObject *parent):
	QObject(parent)
{}

QJsonObject LinzAGDepartureSource::json() const
{
	return m_json;
}

void LinzAGDepartureSource::load()
{
	QNetworkReply *reply = (qnam.get(QNetworkRequest(QUrl("https://www.linzag.at/linz-efa/XML_DM_REQUEST?mode=direct&name_dm=at:44:41101&type_dm=any&outputFormat=rapidJSON&type_db=any&useRealtime=1"))));
	auto onFinished = [this, reply]() {
		m_json = QJsonDocument::fromJson(reply->readAll()).object();
		emit jsonChanged();
	};
	QObject::connect(reply, &QNetworkReply::finished, onFinished);
}

#include "moc_LinzAGDepartureSource.cpp"

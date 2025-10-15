#include "LinzagDepartureSource.hpp"

#include <QJsonDocument>
#include <QNetworkReply>
#include <QUrlQuery>

LinzagDepartureSource::LinzagDepartureSource(QObject *parent):
	QObject(parent),
	m_qnam(new QNetworkAccessManager(this))
{}

QJsonObject LinzagDepartureSource::json() const
{
	return m_json;
}

void LinzagDepartureSource::load()
{
	QUrl url("https://www.linzag.at/linz-efa/XML_DM_REQUEST");
	url.setQuery({
		{"mode", "direct"},
		{"name_dm", m_stopId},
		{"type_dm", "any"},
		{"outputFormat", "rapidJson"},
		{"type_db", "any"},
		{"useRealtime", "1"}
	});
	QNetworkReply *reply = m_qnam->get(QNetworkRequest(url));
	QObject::connect(reply, &QNetworkReply::finished, this, [this, reply]() {
		m_json = QJsonDocument::fromJson(reply->readAll()).object();
		emit jsonChanged(m_json);
		reply->deleteLater();
	});
}

QString LinzagDepartureSource::stopId() const
{
	return m_stopId;
}

void LinzagDepartureSource::setStopId(QString stopId)
{
	m_stopId = stopId;
}

#include "moc_LinzagDepartureSource.cpp"

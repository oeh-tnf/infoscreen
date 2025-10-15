#include "OoevvDepartureSource.hpp"

#include <QJsonArray>
#include <QNetworkReply>

OoevvDepartureSource::OoevvDepartureSource(QObject *parent):
	QObject(parent),
	m_qnam(new QNetworkAccessManager(this))
{}

void OoevvDepartureSource::load()
{
	QUrl url("https://verkehrsauskunft.ooevv.at/bin/mgate.exe");
	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	QJsonDocument data(QJsonObject{
		{"ver", "1.59"},
		{"lang", "deu"},
		{"auth", QJsonObject{
			{"type", "AID"},
			{"aid", "wf7mcf9bv3nv8g5f"}
		}},
		{"client", QJsonObject{
			{"type", "WEB"}
		}},
		{"svcReqL", QJsonArray{
			QJsonObject{
				{"req", QJsonObject{
					{"stbLoc", QJsonObject{
						{"lid", "L=" + m_stopId}
					}},
					{"jnyFltrL", QJsonArray{
						QJsonObject{
							{"type", "PROD"},
							{"mode", "INC"},
							{"value", 1088}
						}
					}},
					//"date":now.strftime("%Y%m%d"),
					//"time":now.strftime("%H%M%S"),
					{"type", "DEP"},
					{"sort", "PT"},
					{"maxJny", 40},
				}},
				{"meth", "StationBoard"}
			}
		}}
	});
	QNetworkReply *reply = m_qnam->post(
		request,
		data.toJson(QJsonDocument::JsonFormat::Compact)
	);
	QObject::connect(reply, &QNetworkReply::finished, this, [this, reply]() {
		m_json = QJsonDocument::fromJson(reply->readAll())["svcResL"][0]["res"].toObject();
		emit jsonChanged(m_json);
		reply->deleteLater();
	});
}

QString OoevvDepartureSource::stopId() const
{
	return m_stopId;
}

QJsonObject OoevvDepartureSource::json() const
{
	return m_json;
}

void OoevvDepartureSource::setStopId(QString stopId)
{
	m_stopId = stopId;
}

#include "moc_OoevvDepartureSource.cpp"

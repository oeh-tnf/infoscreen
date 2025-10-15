#include "MensaMenuSource.hpp"

#include <QJsonDocument>
#include <QNetworkReply>
#include <QJsonArray>

MensaMenuSource::MensaMenuSource(QObject *parent):
	QObject(parent),
	m_qnam(new QNetworkAccessManager(this))
{}

void MensaMenuSource::load()
{
	QUrl url("https://menu.jku.at/api/menus");
	QNetworkReply *reply = m_qnam->get(QNetworkRequest(url));
	QObject::connect(reply, &QNetworkReply::finished, this, [this, reply]() {
		QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
		for (QJsonValue menu : doc.array())
		{
			if (menu["restaurant"]["name"] == "JKU Mensa")
			{
				m_jkuJson = menu.toObject();
				emit jkuJsonChanged(m_jkuJson);
			}
			else if (menu["restaurant"]["name"] == "KHG Mensa")
			{
				m_khgJson = menu.toObject();
				emit khgJsonChanged(m_khgJson);
			}
		}
		reply->deleteLater();
	});
}

QJsonObject MensaMenuSource::jkuJson() const
{
	return m_jkuJson;
}

QJsonObject MensaMenuSource::khgJson() const
{
	return m_khgJson;
}

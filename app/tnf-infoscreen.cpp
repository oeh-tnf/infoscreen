#include <chrono>

#include <QGuiApplication>
#include <QUrl>
#include <QQuickView>
#include <QQuickItem>
#include <QConcatenateTablesProxyModel>
#include <QTimer>
#include <QFont>

#include "DeparturesSortFilterProxyModel.hpp"
#include "LinzagDepartureModel.hpp"
#include "LinzagDepartureSource.hpp"
#include "MensaMenuModel.hpp"
#include "MensaMenuSource.hpp"
#include "OoevvDepartureModel.hpp"
#include "OoevvDepartureSource.hpp"
#include "CurrentTime.hpp"

int main(int argc, char **argv) {
	using namespace std::literals;

	QGuiApplication app(argc, argv);

	QFont font("Red Hat Display");
	font.setFeature("tnum", 1);
	app.setFont(font);

	CurrentTime *time = new CurrentTime();

	LinzagDepartureSource *linzagSource = new LinzagDepartureSource();
	linzagSource->setStopId("at:44:41101");

	OoevvDepartureSource *ooevvSource = new OoevvDepartureSource();
	ooevvSource->setStopId("444110100");

	LinzagDepartureModel *linzagModel = new LinzagDepartureModel();
	QObject::connect(linzagSource, SIGNAL(jsonChanged(QJsonObject)), linzagModel, SLOT(setJson(QJsonObject)));

	OoevvDepartureModel *ooevvModel = new OoevvDepartureModel();
	QObject::connect(ooevvSource, SIGNAL(jsonChanged(QJsonObject)), ooevvModel, SLOT(setJson(QJsonObject)));

	QConcatenateTablesProxyModel *allDeparturesModel = new QConcatenateTablesProxyModel();
	allDeparturesModel->addSourceModel(linzagModel);
	allDeparturesModel->addSourceModel(ooevvModel);

	DeparturesSortFilterProxyModel *departuresModel = new DeparturesSortFilterProxyModel();
	QObject::connect(time, SIGNAL(timeChanged(QDateTime)), departuresModel, SLOT(setTime(QDateTime)));
	departuresModel->setSourceModel(allDeparturesModel);
	departuresModel->sort(2);
	
	MensaMenuSource *mensaSource = new MensaMenuSource();

	MensaMenuModel *jkuMensaModel = new MensaMenuModel();
	QObject::connect(mensaSource, SIGNAL(jkuJsonChanged(QJsonObject)), jkuMensaModel, SLOT(setJson(QJsonObject)));

	MensaMenuModel *khgMensaModel = new MensaMenuModel();
	QObject::connect(mensaSource, SIGNAL(khgJsonChanged(QJsonObject)), khgMensaModel, SLOT(setJson(QJsonObject)));

	QTimer *reloadTimer = new QTimer();
	QObject::connect(reloadTimer, SIGNAL(timeout()), linzagSource, SLOT(load()));
	QObject::connect(reloadTimer, SIGNAL(timeout()), ooevvSource, SLOT(load()));
	QObject::connect(reloadTimer, SIGNAL(timeout()), mensaSource, SLOT(load()));
	reloadTimer->setInterval(1min);
	reloadTimer->start();

	linzagSource->load();
	ooevvSource->load();
	mensaSource->load();

	QQuickView *view = new QQuickView;
	view->setInitialProperties({
		{"time", QVariant::fromValue(time)},
		{"departures", QVariant::fromValue(departuresModel)},
		{"jku_mensa", QVariant::fromValue(jkuMensaModel)},
		{"khg_mensa", QVariant::fromValue(khgMensaModel)}
	});
	view->loadFromModule("TnfInfoscreen", "TnfInfoscreen");
	view->setResizeMode(QQuickView::SizeRootObjectToView);
	view->showFullScreen();


	return app.exec();
}

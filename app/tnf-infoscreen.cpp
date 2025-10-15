#include <chrono>

#include <QGuiApplication>
#include <QUrl>
#include <QQuickView>
#include <QQuickItem>
#include <QConcatenateTablesProxyModel>
#include <QTimer>

#include "DeparturesSortFilterProxyModel.hpp"
#include "LinzagDepartureModel.hpp"
#include "LinzagDepartureSource.hpp"
#include "OoevvDepartureModel.hpp"
#include "OoevvDepartureSource.hpp"
#include "CurrentTime.hpp"

int main(int argc, char **argv) {
	using namespace std::literals;

	QGuiApplication app(argc, argv);

	CurrentTime *time = new CurrentTime();

	LinzagDepartureSource *linzagSource = new LinzagDepartureSource();
	linzagSource->setStopId("at:44:41101");

	OoevvDepartureSource *ooevvSource = new OoevvDepartureSource();
	ooevvSource->setStopId("444110100");

	LinzagDepartureModel *linzagModel = new LinzagDepartureModel();
	QObject::connect(linzagSource, SIGNAL(jsonChanged(QJsonObject)), linzagModel, SLOT(setJson(QJsonObject)));
	QObject::connect(time, SIGNAL(timeChanged(QDateTime)), linzagModel, SLOT(setTime(QDateTime)));
	linzagModel->setTime(time->getTime());

	OoevvDepartureModel *ooevvModel = new OoevvDepartureModel();
	QObject::connect(ooevvSource, SIGNAL(jsonChanged(QJsonObject)), ooevvModel, SLOT(setJson(QJsonObject)));
	QObject::connect(time, SIGNAL(timeChanged(QDateTime)), ooevvModel, SLOT(setTime(QDateTime)));
	ooevvModel->setTime(time->getTime());

	QConcatenateTablesProxyModel *allDeparturesModel = new QConcatenateTablesProxyModel();
	allDeparturesModel->addSourceModel(linzagModel);
	allDeparturesModel->addSourceModel(ooevvModel);

	DeparturesSortFilterProxyModel *departuresModel = new DeparturesSortFilterProxyModel();
	departuresModel->setSourceModel(allDeparturesModel);
	departuresModel->sort(2);

	QTimer *reloadTimer = new QTimer();
	QObject::connect(reloadTimer, SIGNAL(timeout()), linzagSource, SLOT(load()));
	QObject::connect(reloadTimer, SIGNAL(timeout()), ooevvSource, SLOT(load()));
	reloadTimer->setInterval(1min);
	reloadTimer->start();

	linzagSource->load();
	ooevvSource->load();

	QQuickView *view = new QQuickView;
	view->setInitialProperties({
		{"time", time->getTime()},
		{"departures", QVariant::fromValue(departuresModel)},
	});
	view->loadFromModule("TnfInfoscreen", "TnfInfoscreen");
	view->setResizeMode(QQuickView::SizeRootObjectToView);
	QQuickItem *root = view->rootObject();
	QObject::connect(time, &CurrentTime::timeChanged, root, [root, time](){ root->setProperty("time", time->getTime()); });
	view->showFullScreen();


	return app.exec();
}

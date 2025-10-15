#include <QGuiApplication>
#include <QUrl>
#include <QQuickView>
#include <QQuickItem>

#include "CurrentTime.hpp"

int main(int argc, char **argv) {
	QGuiApplication app(argc, argv);

	CurrentTime *time = new CurrentTime();

	QQuickView *view = new QQuickView;
	view->setInitialProperties({
		{"time", time->getTime()}
	});
	view->loadFromModule("TnfInfoscreen", "TnfInfoscreen");
	view->setResizeMode(QQuickView::SizeRootObjectToView);
	QQuickItem *root = view->rootObject();
	QObject::connect(time, &CurrentTime::timeChanged, root, [root, time](){ root->setProperty("time", time->getTime()); });
	view->showFullScreen();

	return app.exec();
}

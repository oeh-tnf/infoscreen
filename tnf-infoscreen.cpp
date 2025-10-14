#include <QGuiApplication>
#include <QUrl>
#include <QQuickView>

int main(int argc, char **argv) {
	QGuiApplication app(argc, argv);

	QQuickView *view = new QQuickView;
	view->setSource(QUrl("qrc:/tnf-infoscreen.qml"));
	view->setResizeMode(QQuickView::SizeRootObjectToView);
	view->showFullScreen();

	return app.exec();
}

#pragma once

#include <QDateTime>
#include <QObject>

class CurrentTime : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QDateTime time READ getTime NOTIFY timeChanged)

signals:
	void timeChanged(QDateTime time);

public slots:
    void updateTime();

public:
	explicit CurrentTime(QObject *parent = nullptr);
	~CurrentTime() override = default;

	QDateTime getTime();

private:
	QDateTime m_time;
};

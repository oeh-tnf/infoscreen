#include "CurrentTime.hpp"

#include <chrono>

#include <QTimer>

CurrentTime::CurrentTime(QObject *parent):
    QObject(parent),
    m_time(QDateTime::currentDateTime())
{
    using namespace std::literals;

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CurrentTime::updateTime);
    timer->setInterval(1s);
    timer->start();
}

void CurrentTime::updateTime()
{
    QDateTime now = QDateTime::currentDateTime();
    if (m_time.time().minute() != now.time().minute())
    {
        m_time = QDateTime::currentDateTime();
        emit timeChanged(m_time);
    }
}

QDateTime CurrentTime::getTime()
{
    return m_time;
}

#include "moc_CurrentTime.cpp"

#include "WindowManager.h"

#include <QCoreApplication>
#include <QDebug>

#include <xcb/xcb.h>

namespace madobe {

WindowManager::WindowManager(QObject *parent)
    : QObject(parent)
{
    QCoreApplication::instance()->installNativeEventFilter(this);
}

WindowManager::~WindowManager()
{
}

bool WindowManager::nativeEventFilter(const QByteArray &eventType,
        void *message, long *result)
{
    qDebug() << "Native event: " << eventType;
    if (eventType == "xcb_generic_event_t") {
        xcb_generic_event_t *ev = static_cast<xcb_generic_event_t*>(message);
        qDebug() << ev;
        qDebug() << result;
    }

    return false;
}

} // namespace madobe

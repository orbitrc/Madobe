#ifndef _MADOBE_WINDOW_MANAGER_H
#define _MADOBE_WINDOW_MANAGER_H

#include <QObject>
#include <QAbstractNativeEventFilter>

#include <xcb/xcb.h>

namespace madobe {

class WindowManager : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    explicit WindowManager(xcb_connection_t *conn, QObject *parent = nullptr);
    ~WindowManager();

    virtual bool nativeEventFilter(const QByteArray &eventType, void *message,
            long *result) override;

signals:

private:
    xcb_connection_t *_conn;
    xcb_window_t _rootWindow;
};

} // namespace madobe

#endif // _MADOBE_WINDOW_MANAGER_H

#ifndef _MADOBE_WINDOW_MANAGER_H
#define _MADOBE_WINDOW_MANAGER_H

#include <QObject>
#include <QAbstractNativeEventFilter>

namespace madobe {

class WindowManager : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    explicit WindowManager(QObject *parent = nullptr);
    ~WindowManager();

    virtual bool nativeEventFilter(const QByteArray &eventType, void *message,
            long *result) override;

signals:

};

} // namespace madobe

#endif // _MADOBE_WINDOW_MANAGER_H

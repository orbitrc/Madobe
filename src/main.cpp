#include <QApplication>
#include <QX11Info>

#include <xcb/xcb.h>

#include "WindowManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    xcb_connection_t *conn = QX11Info::connection();

    madobe::WindowManager windowManager(conn);

    return a.exec();
}

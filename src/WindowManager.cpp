#include "WindowManager.h"

#include <QCoreApplication>
#include <QX11Info>
#include <QDebug>

#include <stdlib.h>

#include <xcb/xcb.h>

namespace madobe {

WindowManager::WindowManager(xcb_connection_t *conn, QObject *parent)
    : QObject(parent)
{
    this->_conn = conn;

    xcb_screen_t *screen;
    screen = xcb_setup_roots_iterator(xcb_get_setup(this->_conn)).data;
    this->_rootWindow = screen->root;
    qDebug() << "Root window: " << this->_rootWindow;
    qDebug() << "QX11Info::appScreen(): " << QX11Info::appScreen();

//    xcb_grab_key(this->_conn, 1, screen->root, XCB_MOD_MASK_ANY, XCB_GRAB_ANY,
//        XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC);
    QCoreApplication::instance()->installNativeEventFilter(this);

    xcb_get_window_attributes_cookie_t window_attributes_cookie =
        xcb_get_window_attributes_unchecked(this->_conn, this->_rootWindow);
    xcb_get_window_attributes_reply_t *window_attributes_reply =
        xcb_get_window_attributes_reply(
            this->_conn,
            window_attributes_cookie,
            NULL
        );
    unsigned int new_event_mask = window_attributes_reply->your_event_mask
        | XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY
        | XCB_EVENT_MASK_STRUCTURE_NOTIFY
        | XCB_EVENT_MASK_PROPERTY_CHANGE
        | XCB_EVENT_MASK_KEY_PRESS;
    xcb_change_window_attributes(this->_conn, this->_rootWindow,
        XCB_CW_EVENT_MASK, (const void*)(&new_event_mask));
    free(window_attributes_reply);
}

WindowManager::~WindowManager()
{
    xcb_disconnect(this->_conn);
}

bool WindowManager::nativeEventFilter(const QByteArray &eventType,
        void *message, long *result)
{
    if (eventType == "xcb_generic_event_t") {
        xcb_generic_event_t *ev = static_cast<xcb_generic_event_t*>(message);
        auto responseType = ev->response_type & ~0x80;
        switch (responseType) {
        case XCB_KEY_PRESS:
            qDebug() << "XCB_KEY_PRESS";
            break;
        case XCB_EXPOSE:
            qDebug() << "XCB_EXPOSE";
            break;
        case XCB_CREATE_NOTIFY:
        {
            xcb_create_notify_event_t *create_notify = (xcb_create_notify_event_t*)ev;
            qDebug() << "XCB_CREATE_NOTIFY" << create_notify->window;
            break;
        }
        case XCB_DESTROY_NOTIFY:
        {
            xcb_destroy_notify_event_t *destroy_notify = (xcb_destroy_notify_event_t*)ev;
            qDebug() << "XCB_DESTROY_NOTIFY" << destroy_notify->window;
            break;
        }
        case XCB_DELETE_PROPERTY:
        {
            qDebug() << "XCB_DELETE_PROPERTY";
            break;
        }
        case XCB_PROPERTY_NOTIFY:
        {
            xcb_property_notify_event_t *property_notify = (xcb_property_notify_event_t*)ev;
            qDebug() << "XCB_PROPERTY_NOTIFY" << property_notify->atom << property_notify->window;
            break;
        }
        case XCB_CLIENT_MESSAGE:
        {
            xcb_client_message_event_t *client_message = (xcb_client_message_event_t*)ev;
            qDebug() << "XCB_CLIENT_MESSAGE" << client_message->window;
            break;
        }
        default:
            qDebug() << responseType;
            break;
        }
    } else {
        qDebug() << "Not a xcb_generic_event_t";
    }

    return false;
}

} // namespace madobe

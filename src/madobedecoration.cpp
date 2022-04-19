#include "madobedecoration.h"

#include <QPainter>

#include <KPluginFactory>
#include <KDecoration2/Decoration>

K_PLUGIN_FACTORY_WITH_JSON(
    MadobeDecorationFactory,
    "madobe.json",
    registerPlugin<madobe::Decoration>();
)

namespace madobe {
    Decoration::Decoration(QObject *parent, const QVariantList& args)
        : KDecoration2::Decoration(parent, args)
    {
        // TODO: Implement.
    }

    Decoration::~Decoration()
    {
    }

    void Decoration::paint(QPainter *painter, const QRect& repaintRegion)
    {
        // TODO: Implement.
        QRect titleBarRect = QRect(QPoint(0, 0), QSize(100, 30));
        painter->setBrush(Qt::green);
        painter->drawRect(titleBarRect);
    }

    void Decoration::init()
    {
        QRect titleBarRect = QRect(QPoint(0, 0), QSize(100, 30));
        this->setTitleBar(titleBarRect);

        this->setBorders(QMargins(0, 30, 0, 0));

        this->update();
    }
}

#include "madobedecoration.moc"

#include "madobedecoration.h"

#include <QPainter>

#include <KPluginFactory>
#include <KDecoration2/Decoration>
#include <KDecoration2/DecoratedClient>

#include "logger.h"

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
        auto c = this->client().toStrongRef();

        Logger logger;
        QString info = "Begin paint: from - " + c->caption() + "\n";
        logger.info(info.toUtf8());

        QRect titleBarRect = QRect(QPoint(0, 0), QSize(100, 30));
        painter->setBrush(Qt::green);
        painter->drawRect(titleBarRect);
    }

    void Decoration::init()
    {
        auto c = this->client().toStrongRef();
        (void)c;

        QRect titleBarRect = QRect(QPoint(0, 0), QSize(100, 30));
        this->setTitleBar(titleBarRect);

        this->setBorders(QMargins(0, 30, 0, 0));

        this->update();
    }
}

#include "madobedecoration.moc"

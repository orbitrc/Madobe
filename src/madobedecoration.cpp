#include "madobedecoration.h"

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
    }
}

#include "madobedecoration.moc"

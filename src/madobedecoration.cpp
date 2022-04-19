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

    // Draw border.
    QRect borderRect = QRect(
        QPoint(0, 0),
        QSize(
            c->width() + (this->borderWidth() * 2),
            c->height() + (this->borderWidth() * 2) + (this->titleBarHeight())
        )
    );
    painter->setBrush(Qt::black);
    painter->drawRect(borderRect);

    // Draw title bar.
    QRect titleBarRect = QRect(
        QPoint(this->borderWidth(), this->borderWidth()),
        QSize(c->width(), this->titleBarHeight())
    );
    painter->setBrush(QColor::fromRgb(0x00, 0x00, 0x82));
    painter->setPen(Qt::NoPen);
    painter->drawRect(titleBarRect);

    // Draw title.
    painter->setPen(Qt::white);
    QFont font("sans-serif", 12, QFont::Bold);
    painter->setFont(font);
    painter->drawText(titleBarRect, Qt::AlignCenter, c->caption());
}

void Decoration::init()
{
    auto c = this->client().toStrongRef();
    (void)c;

    QRect titleBarRect = QRect(QPoint(0, 0), QSize(100, 30));
    this->setTitleBar(titleBarRect);

    this->setBorders(QMargins(
        this->borderWidth(),
        this->borderWidth() + 30,
        this->borderWidth(),
        this->borderWidth()
    ));

    this->update();
}

int Decoration::shadowWidth() const
{
    return 40;
}

int Decoration::resizeWidth() const
{
    return 5;
}

int Decoration::borderWidth() const
{
    return 2;
}

int Decoration::titleBarHeight() const
{
    return 30;
}

int Decoration::titleFontSize() const
{
    return 14;
}

//=================
// Private Slots
//=================

void Decoration::updateBorder()
{
    auto c = this->client().toStrongRef();

    c->width();
}


} // namespace madobe

#include "madobedecoration.moc"

#include "button.h"

#include <QPainter>

#include "madobedecoration.h"

namespace madobe {

Button::Button(QObject *parent, const QVariantList& args)
    : KDecoration2::DecorationButton(KDecoration2::DecorationButtonType::Close, nullptr, parent)
{
}

Button::Button(KDecoration2::DecorationButtonType type,
        Decoration *decoration, QObject *parent)
    : KDecoration2::DecorationButton(type, decoration, parent)
{
}

Button::~Button()
{
}

void Button::paint(QPainter *painter, const QRect &repaintRegion)
{
    painter->setBrush(Qt::red);
    painter->setPen(Qt::NoPen);
    painter->drawRect(this->geometry());
}

} // namespace madobe

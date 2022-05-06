#include "button.h"

#include <QPainter>

#include "madobedecoration.h"
#include "theme.h"

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
    auto decoration = static_cast<Decoration*>(this->decoration().data());
    painter->setBrush(Qt::red);
    painter->setPen(Qt::NoPen);
    painter->drawRect(this->geometry());
    if (decoration->theme() != nullptr &&
            decoration->theme()->close_image() != nullptr) {
        QImage close(decoration->theme()->close_image(),
            this->size().width(), this->size().height(),
            this->size().width() * 4,
            QImage::Format_RGBA8888);
        painter->drawImage(this->geometry(), close, close.rect());
    }
}

} // namespace madobe

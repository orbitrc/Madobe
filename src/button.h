#ifndef _MADOBE_BUTTON_H
#define _MADOBE_BUTTON_H

#include <KDecoration2/DecorationButton>

namespace madobe {

class Decoration;

class Button : public KDecoration2::DecorationButton
{
    Q_OBJECT
public:
    explicit Button(QObject *parent = nullptr,
            const QVariantList& args = QVariantList());

    explicit Button(KDecoration2::DecorationButtonType type,
            Decoration *decoration, QObject *parent);

    virtual ~Button();

    void paint(QPainter *painter, const QRect& repaintRegion) override;
};

} // namespace madobe

#endif // _MADOBE_BUTTON_H

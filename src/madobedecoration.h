#ifndef _MADOBEDECORATION_H
#define _MADOBEDECORATION_H

#include <QVariant>

#include <KDecoration2/Decoration>

namespace madobe {

class Decoration : public KDecoration2::Decoration
{
    Q_OBJECT
public:
    explicit Decoration(QObject *parent = nullptr,
            const QVariantList& args = QVariantList());

    virtual ~Decoration();

    void paint(QPainter *painter, const QRect& repaintRegion) override;

    int shadowWidth() const;

    int resizeWidth() const;

    int borderWidth() const;

    int titleBarHeight() const;

    int titleFontSize() const;

public slots:
    void init() override;

private slots:
    void updateBorder();

    void updateTitleBar();

private:
};

} // namespace madobe

#endif // _MADOBEDECORATION_H

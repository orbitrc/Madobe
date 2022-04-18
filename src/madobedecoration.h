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
    private:
    };
}

#endif // _MADOBEDECORATION_H

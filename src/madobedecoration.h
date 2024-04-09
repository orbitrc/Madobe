#ifndef _MADOBEDECORATION_H
#define _MADOBEDECORATION_H

#include <memory>

#include <QVariant>

#include <KDecoration2/Decoration>
#include <KDecoration2/DecorationShadow>

namespace madobe {

class Button;
class Theme;

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

    //===============
    // Properties
    //===============
   QString themeId() const;
   void setThemeId(const QString& themeId);

   Theme* theme() const;

signals:
   void themeIdChanged(const QString& themeId);

public slots:
    bool init() override;

private slots:
    void updateBorder();

    void updateTitleBar();

    void readConfFileThemeId();

    void loadTheme();

    /// Called once from init() slot.
    void initShadow();

private:
    Button *m_closeButton;
    QString m_themeId;
    Theme *m_theme;
    std::shared_ptr<KDecoration2::DecorationShadow> m_shadow;
};

} // namespace madobe

#endif // _MADOBEDECORATION_H

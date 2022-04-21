#include "madobedecoration.h"

#include <stdlib.h>

#include <QPainter>
#include <QFile>
#include <QSettings>

#include <KPluginFactory>
#include <KDecoration2/Decoration>
#include <KDecoration2/DecoratedClient>
#include <KDecoration2/DecorationSettings>

#include "logger.h"
#include "conf.h"
#include "theme.h"
#include "button.h"

#define CONF_FILE_PATH      "/etc/madobe.conf"
#define USER_CONF_FILE_PATH ".config/madobe.conf"

K_PLUGIN_FACTORY_WITH_JSON(
    MadobeDecorationFactory,
    "madobe.json",
    registerPlugin<madobe::Decoration>();
    registerPlugin<madobe::Button>();
)

namespace madobe {

Decoration::Decoration(QObject *parent, const QVariantList& args)
    : KDecoration2::Decoration(parent, args)
{
    // TODO: Implement.
    this->m_closeButton = nullptr;
    this->m_themeId = "standalone";
    this->m_theme = nullptr;
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
    painter->drawText(titleBarRect, Qt::AlignCenter,
        c->caption() + " (" + this->m_themeId + ")");

    if (this->m_closeButton != nullptr) {
        this->m_closeButton->setVisible(true);
        this->m_closeButton->paint(painter, repaintRegion);
    }
}

void Decoration::init()
{
    auto c = this->client().toStrongRef();
    auto s = this->settings();
    (void)c;

    this->readConfFileThemeId();
    this->loadTheme();

    QRect titleBarRect = QRect(
        QPoint(this->borderWidth(), this->borderWidth()),
        QSize(100, 30)
    );
    this->setTitleBar(titleBarRect);

    this->setBorders(QMargins(
        this->borderWidth(),
        this->borderWidth() + 30,
        this->borderWidth(),
        this->borderWidth()
    ));

    this->setResizeOnlyBorders(QMargins(
        this->resizeWidth() - this->borderWidth(),
        this->resizeWidth() - this->borderWidth(),
        this->resizeWidth() - this->borderWidth(),
        this->resizeWidth() - this->borderWidth()
    ));

    // Init buttons.
    if (this->m_closeButton == nullptr) {
        this->m_closeButton = new Button(KDecoration2::DecorationButtonType::Close, this, this);
        this->m_closeButton->setGeometry(QRectF(0, 0, 20, 20));
    }

    // Connections with settings.
    QObject::connect(s.data(), &KDecoration2::DecorationSettings::reconfigured,
                     this, [this]() {
        this->readConfFileThemeId();
    });

    // Connections with properties.
    QObject::connect(this, &Decoration::themeIdChanged,
                     this, &Decoration::loadTheme);

    this->update();
}

int Decoration::shadowWidth() const
{
    return this->m_theme->shadow_width();
}

int Decoration::resizeWidth() const
{
    return this->m_theme->resize_width();
}

int Decoration::borderWidth() const
{
    return this->m_theme->border_width();
}

int Decoration::titleBarHeight() const
{
    return this->m_theme->title_bar_height();
}

int Decoration::titleFontSize() const
{
    return 14;
}

//=================
// Properties
//=================
QString Decoration::themeId() const
{
    return this->m_themeId;
}

void Decoration::setThemeId(const QString &themeId)
{
    if (this->m_themeId != themeId) {
        this->m_themeId = themeId;

        emit this->themeIdChanged(themeId);
    }
}

//=================
// Private Slots
//=================

void Decoration::updateBorder()
{
    auto c = this->client().toStrongRef();

    c->width();
}

void Decoration::readConfFileThemeId()
{
    auto userConfFilePath = QString(getenv("HOME")) + "/" + USER_CONF_FILE_PATH;

    QFile userF(userConfFilePath);
    if (userF.exists()) {
        Conf conf(userConfFilePath.toUtf8());
        auto themeId = conf.value("General/Theme", "");
        if (themeId != "") {
            this->setThemeId(QString::fromStdString(themeId));
        }
    } else {
        QFile f(CONF_FILE_PATH);
        if (f.exists()) {
            Conf conf(CONF_FILE_PATH);
            auto themeId = conf.value("General/Theme", "");
            if (themeId != "") {
                this->setThemeId(QString::fromStdString(themeId));
            }
        }
    }

    if (this->m_themeId == "") {
        this->m_themeId = "standalone";
    }
}

void Decoration::loadTheme()
{
    auto themeId = this->themeId();

    if (this->m_theme != nullptr) {
        delete this->m_theme;
    }
    this->m_theme = new Theme(themeId.toUtf8());
}

} // namespace madobe

#include "madobedecoration.moc"

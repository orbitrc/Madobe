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

    painter->setPen(Qt::NoPen);
    // Draw border.
    QRect borderRect = QRect(
        QPoint(0, 0),
        QSize(
            c->width() + (this->borderWidth() * 2),
            c->height() + (this->borderWidth() * 2) + (this->titleBarHeight())
        )
    );
    painter->setBrush(Qt::green);
    painter->drawRect(borderRect);
    // Border top left.
    QRect borderTopLeftRect = QRect(
        QPoint(0, 0),
        QSize(this->borderWidth(), this->borderWidth())
    );
    if (this->m_theme != nullptr &&
            this->m_theme->border_top_left_image() != nullptr) {
        logger.info("Found top-left border image.\n");
        QImage borderTopLeft(this->m_theme->border_top_left_image(),
            this->borderWidth(), this->borderWidth(),
            this->borderWidth() * 4,
            QImage::Format_RGBA8888);
        painter->drawImage(borderTopLeftRect, borderTopLeft, borderTopLeft.rect());
    }
    // Border top.
    QRect borderTopRect = QRect(
        QPoint(this->borderWidth(), 0),
        QSize(c->width(), this->borderWidth())
    );
    if (this->m_theme != nullptr &&
            this->m_theme->border_top_image() != nullptr) {
        QImage borderTop(this->m_theme->border_top_image(),
            1, this->borderWidth(),
            1 * 4,
            QImage::Format_RGBA8888);
        painter->drawImage(borderTopRect, borderTop, borderTop.rect());
    }
    // Border top right.
    QRect borderTopRightRect = QRect(
        QPoint(c->width() + this->borderWidth(), 0),
        QSize(this->borderWidth(), this->borderWidth())
    );
    if (this->m_theme != nullptr &&
            this->m_theme->border_top_right_image() != nullptr) {
        QImage borderTopRight(this->m_theme->border_top_right_image(),
            this->borderWidth(), this->borderWidth(),
            this->borderWidth() * 4,
            QImage::Format_RGBA8888);
        painter->drawImage(borderTopRightRect, borderTopRight, borderTopRight.rect());
    }
    // Border left.
    QRect borderLeftRect = QRect(
        QPoint(0, this->borderWidth()),
        QSize(
            this->borderWidth(),
            c->height() + (this->titleBarHeight())
        )
    );
    if (this->m_theme != nullptr &&
            this->m_theme->border_left_image() != nullptr) {
        QImage borderLeft(this->m_theme->border_left_image(),
            this->borderWidth(), 1,
            this->borderWidth() * 4,
            QImage::Format_RGBA8888);
        painter->drawImage(borderLeftRect, borderLeft, borderLeft.rect());
    }
    // Border right.
    QRect borderRightRect = QRect(
        QPoint(this->borderWidth() + c->width(), this->borderWidth()),
        QSize(this->borderWidth(), c->height() + (this->titleBarHeight()))
    );
    if (this->m_theme != nullptr &&
            this->m_theme->border_right_image() != nullptr) {
        QImage borderRight(this->m_theme->border_right_image(),
            this->borderWidth(), 1,
            this->borderWidth() * 4,
            QImage::Format_RGBA8888);
        painter->drawImage(borderRightRect, borderRight, borderRight.rect());
    }
    // Border bottom left.
    QRect borderBottomLeftRect = QRect(
        QPoint(0, this->borderWidth() + c->height() + this->titleBarHeight()),
        QSize(this->borderWidth(), this->borderWidth())
    );
    if (this->m_theme != nullptr &&
            this->m_theme->border_bottom_left_image() != nullptr) {
        QImage borderBottomLeft(this->m_theme->border_bottom_left_image(),
            this->borderWidth(), this->borderWidth(),
            this->borderWidth() * 4,
            QImage::Format_RGBA8888);
        painter->drawImage(borderBottomLeftRect, borderBottomLeft, borderBottomLeft.rect());
    }
    // Border bottom.
    QRect borderBottomRect = QRect(
        QPoint(
            this->borderWidth(),
            this->borderWidth() + c->height() + this->titleBarHeight()
        ),
        QSize(c->width(), this->borderWidth())
    );
    if (this->m_theme != nullptr &&
            this->m_theme->border_bottom_image() != nullptr) {
        QImage borderBottom(this->m_theme->border_bottom_image(),
            1, this->borderWidth(),
            1 * 4,
            QImage::Format_RGBA8888);
        painter->drawImage(borderBottomRect, borderBottom, borderBottom.rect());
    }
    // Border bottom right.
    QRect borderBottomRightRect = QRect(
        QPoint(
            this->borderWidth() + c->width(),
            c->height() + this->borderWidth() + this->titleBarHeight()
        ),
        QSize(this->borderWidth(), this->borderWidth())
    );
    if (this->m_theme != nullptr &&
            this->m_theme->border_bottom_right_image() != nullptr) {
        QImage borderBottomRight(this->m_theme->border_bottom_right_image(),
            this->borderWidth(), this->borderWidth(),
            this->borderWidth() * 4,
            QImage::Format_RGBA8888);
        painter->drawImage(borderBottomRightRect, borderBottomRight, borderBottomRight.rect());
    }

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
    QFont font("sans-serif", this->titleFontSize(), QFont::Bold);
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
        QSize(100, this->titleBarHeight())
    );
    this->setTitleBar(titleBarRect);

    this->setBorders(QMargins(
        this->borderWidth(),
        this->borderWidth() + this->titleBarHeight(),
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
        this->m_closeButton->setGeometry(QRectF(4, 4, 20, 20));
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
    return 12;
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

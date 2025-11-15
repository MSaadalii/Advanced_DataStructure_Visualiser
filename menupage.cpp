#include "menupage.h"
#include <QPainter>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>
#include <QTimer>

MenuPage::MenuPage(QWidget *parent)
    : QWidget(parent)
    , animationsStarted(false)
{
    setupUI();
    setupAnimations();

    setMinimumSize(900, 750);
}

MenuPage::~MenuPage()
{
}

void MenuPage::setupUI()
{
    // Main layout with margins
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(50, 40, 50, 40);
    mainLayout->setSpacing(0);

    // Create menu container
    menuContainer = new QWidget(this);
    QVBoxLayout *containerLayout = new QVBoxLayout(menuContainer);
    containerLayout->setSpacing(0);
    containerLayout->setContentsMargins(0, 0, 0, 0);

    // Title section
    titleLabel = new QLabel("Data Structure Visualizer", menuContainer);
    QFont titleFont;

    QStringList preferredFonts = {"Segoe UI", "Poppins", "SF Pro Display", "Arial"};
    for (const QString &fontName : preferredFonts) {
        if (QFontDatabase::families().contains(fontName)) {
            titleFont.setFamily(fontName);
            break;
        }
    }

    titleFont.setPointSize(38);
    titleFont.setBold(true);
    titleFont.setLetterSpacing(QFont::AbsoluteSpacing, -1);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: #2d1b69;");
    titleLabel->setAlignment(Qt::AlignCenter);

    containerLayout->addWidget(titleLabel);
    containerLayout->addSpacing(12);

    // Subtitle
    subtitleLabel = new QLabel("Choose your structure to explore", menuContainer);
    QFont subtitleFont;
    subtitleFont.setFamily(titleFont.family());
    subtitleFont.setPointSize(15);
    subtitleLabel->setFont(subtitleFont);
    subtitleLabel->setStyleSheet("color: #6b5b95;");
    subtitleLabel->setAlignment(Qt::AlignCenter);

    containerLayout->addWidget(subtitleLabel);
    containerLayout->addSpacing(50);

    // Create grid layout for cards (2x2)
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setSpacing(34);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    // Create cards for each data structure
    QWidget *treeCard = createMenuCard(
        "Binary Search Tree",
        "Hierarchical structure with nodes and edges",
        "🌳",
        treeButton
        );

    QWidget *rbTreeCard = createMenuCard(
        "Red-Black Tree",
        "Self-balancing binary search tree",
        "🔴",
        rbTreeButton
        );

    QWidget *graphCard = createMenuCard(
        "Graph",
        "Network of vertices and connections",
        "🕸️",
        graphButton
        );

    QWidget *hashCard = createMenuCard(
        "Hash Table",
        "Key-value pairs with fast lookup",
        "🗝️",
        hashTableButton
        );

    // Add cards to grid (2 columns)
    gridLayout->addWidget(treeCard, 0, 0);
    gridLayout->addWidget(rbTreeCard, 0, 1);
    gridLayout->addWidget(graphCard, 1, 0);
    gridLayout->addWidget(hashCard, 1, 1);

    // Store cards for animation
    cards.append(treeCard);
    cards.append(rbTreeCard);
    cards.append(graphCard);
    cards.append(hashCard);

    containerLayout->addLayout(gridLayout);
    containerLayout->addStretch();

    menuContainer->setLayout(containerLayout);
    mainLayout->addWidget(menuContainer);

    // Connect button signals
    connect(treeButton, &QPushButton::clicked, this, &MenuPage::onTreeClicked);
    connect(rbTreeButton, &QPushButton::clicked, this, &MenuPage::onRedBlackTreeClicked);
    connect(graphButton, &QPushButton::clicked, this, &MenuPage::onGraphClicked);
    connect(hashTableButton, &QPushButton::clicked, this, &MenuPage::onHashTableClicked);

    setLayout(mainLayout);
}

QWidget* MenuPage::createMenuCard(const QString &title, const QString &description,
                                  const QString &icon, QPushButton* &button)
{
    QWidget *card = new QWidget(this);
    card->setFixedSize(380, 245);

    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(24, 20, 24, 20);
    cardLayout->setSpacing(5);

    // Icon label
    QLabel *iconLabel = new QLabel(icon, card);
    QFont iconFont;
    iconFont.setPointSize(42);
    iconLabel->setFont(iconFont);
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setFixedHeight(54);
    iconLabel->setStyleSheet("background: transparent; border: none;");
    cardLayout->addWidget(iconLabel);

    cardLayout->addSpacing(0);

    // Title label
    QLabel *titleLabel = new QLabel(title, card);
    QFont titleFont;
    QStringList preferredFonts = {"Segoe UI", "Poppins", "Arial"};
    for (const QString &fontName : preferredFonts) {
        if (QFontDatabase::families().contains(fontName)) {
            titleFont.setFamily(fontName);
            break;
        }
    }
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: #2d1b69; margin-top: 2px; background: transparent; border: none;");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFixedHeight(32);
    cardLayout->addWidget(titleLabel);

    // Description label
    QLabel *descLabel = new QLabel(description, card);
    QFont descFont;
    descFont.setFamily(titleFont.family());
    descFont.setPointSize(11);
    descLabel->setFont(descFont);
    descLabel->setStyleSheet("color: #7a6b95; background: transparent; border: none;");
    descLabel->setAlignment(Qt::AlignCenter);
    descLabel->setWordWrap(true);
    descLabel->setFixedHeight(36);
    cardLayout->addWidget(descLabel);

    cardLayout->addSpacing(3);

    // Button
    button = new QPushButton("Explore", card);
    button->setFixedHeight(45);
    button->setCursor(Qt::PointingHandCursor);
    styleButton(button);
    cardLayout->addWidget(button);

    card->setLayout(cardLayout);
    styleCard(card);

    return card;
}

void MenuPage::styleCard(QWidget *card)
{
    card->setStyleSheet(R"(
        QWidget {
            background-color: rgba(255, 255, 255, 0.95);
            border-radius: 24px;
            border: 2px solid rgba(123, 79, 255, 0.1);
        }
    )");

    // Add drop shadow effect
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(card);
    shadow->setBlurRadius(30);
    shadow->setXOffset(0);
    shadow->setYOffset(8);
    shadow->setColor(QColor(123, 79, 255, 40));
    card->setGraphicsEffect(shadow);
}

void MenuPage::styleButton(QPushButton *button)
{
    QFont buttonFont;
    QStringList preferredFonts = {"Segoe UI", "Poppins", "Arial"};
    for (const QString &fontName : preferredFonts) {
        if (QFontDatabase::families().contains(fontName)) {
            buttonFont.setFamily(fontName);
            break;
        }
    }

    buttonFont.setPointSize(13);
    buttonFont.setBold(true);
    button->setFont(buttonFont);

    QString buttonStyle = R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #7b4fff, stop:1 #9b6fff);
            color: white;
            border: none;
            border-radius: 22px;
            padding: 12px;
            text-align: center;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #6c3cff, stop:1 #8b5fff);
        }
        QPushButton:pressed {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #5a32cc, stop:1 #7a4ccc);
        }
    )";

    button->setStyleSheet(buttonStyle);
}

void MenuPage::setupAnimations()
{
    animationGroup = new QParallelAnimationGroup(this);

    // Create fade-in animations for each card with stagger effect
    for (int i = 0; i < cards.size(); ++i) {
        QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect(this);
        opacity->setOpacity(0.0);
        cardOpacities.append(opacity);

        // Create a sequential group for this card (pause + fade)
        QSequentialAnimationGroup *cardSequence = new QSequentialAnimationGroup();

        // Add pause before animation starts (for stagger effect)
        QPauseAnimation *pause = new QPauseAnimation(i * 100);
        cardSequence->addAnimation(pause);

        // Add fade-in animation
        QPropertyAnimation *fadeIn = new QPropertyAnimation(opacity, "opacity");
        fadeIn->setDuration(800);
        fadeIn->setStartValue(0.0);
        fadeIn->setEndValue(1.0);
        fadeIn->setEasingCurve(QEasingCurve::OutCubic);
        cardSequence->addAnimation(fadeIn);

        animationGroup->addAnimation(cardSequence);
    }
}

void MenuPage::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Create gradient background
    QLinearGradient gradient(0, 0, width(), height());
    gradient.setColorAt(0.0, QColor(250, 247, 255));  // Very light purple
    gradient.setColorAt(0.5, QColor(242, 235, 255));  // Soft lavender
    gradient.setColorAt(1.0, QColor(237, 228, 255));  // Lavender

    painter.fillRect(rect(), gradient);

    // Add subtle circular gradients for depth
    QRadialGradient topCircle(width() * 0.2, height() * 0.15, width() * 0.4);
    topCircle.setColorAt(0.0, QColor(200, 180, 255, 30));
    topCircle.setColorAt(1.0, QColor(200, 180, 255, 0));
    painter.fillRect(rect(), topCircle);

    QRadialGradient bottomCircle(width() * 0.8, height() * 0.85, width() * 0.5);
    bottomCircle.setColorAt(0.0, QColor(180, 150, 255, 25));
    bottomCircle.setColorAt(1.0, QColor(180, 150, 255, 0));
    painter.fillRect(rect(), bottomCircle);
}

void MenuPage::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    if (!animationsStarted) {
        // Apply opacity effects to cards
        for (int i = 0; i < cards.size() && i < cardOpacities.size(); ++i) {
            cards[i]->setGraphicsEffect(cardOpacities[i]);
        }

        // Start staggered animations
        animationGroup->start();
        animationsStarted = true;
    }
}

void MenuPage::onTreeClicked()
{
    qDebug() << "Tree visualization opened";
    emit dataStructureSelected("Binary Search Tree");
}

void MenuPage::onRedBlackTreeClicked()
{
    qDebug() << "Red-Black Tree visualization opened";
    emit dataStructureSelected("Red-Black Tree");
}

void MenuPage::onGraphClicked()
{
    qDebug() << "Graph visualization opened";
    emit dataStructureSelected("Graph");
}

void MenuPage::onHashTableClicked()
{
    qDebug() << "Hash Table visualization opened";
    emit dataStructureSelected("Hash Table");
}

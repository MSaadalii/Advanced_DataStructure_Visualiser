#include "homepage.h"

HomePage::HomePage(QWidget *parent)
    : QWidget(parent)
    , animationsStarted(false)
{
    setupUI();
    setupAnimations();

    // Set minimum window size
    setMinimumSize(1000, 650);
}

HomePage::~HomePage()
{
}

void HomePage::setupUI()
{
    // Create main horizontal layout
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Create left and right panels
    leftPanel = new QWidget(this);
    rightPanel = new QWidget(this);

    setupLeftPanel();
    setupRightPanel();

    // Add panels to main layout (50-50 split)
    mainLayout->addWidget(leftPanel, 1);
    mainLayout->addWidget(rightPanel, 1);

    setLayout(mainLayout);
}

void HomePage::setupLeftPanel()
{
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setContentsMargins(60, 60, 60, 60);

    // Add top spacer
    leftLayout->addStretch(1);

    // Create title label with better visibility
    titleLabel = new QLabel("Advanced Data\nStructure Visualizer", leftPanel);
    QFont titleFont;

    // Try to use modern fonts
    QStringList preferredFonts = {"Segoe UI", "Poppins", "Arial", "Helvetica"};
    for (const QString &fontName : preferredFonts) {
        if (QFontDatabase::families().contains(fontName)) {
            titleFont.setFamily(fontName);
            break;
        }
    }

    titleFont.setPointSize(42);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: #2d1b69; line-height: 1.2;");
    titleLabel->setWordWrap(true);

    leftLayout->addWidget(titleLabel);
    leftLayout->addSpacing(25);

    // Create subtitle with better contrast
    subtitleLabel = new QLabel("Visualize, Understand, and Master\nData Structures", leftPanel);
    QFont subtitleFont;
    subtitleFont.setFamily(titleFont.family());
    subtitleFont.setPointSize(16);
    subtitleLabel->setFont(subtitleFont);
    subtitleLabel->setStyleSheet("color: #5a4088; line-height: 1.6;");
    subtitleLabel->setWordWrap(true);

    leftLayout->addWidget(subtitleLabel);
    leftLayout->addSpacing(30);

    // Create description text
    descriptionLabel = new QLabel(
        "An interactive educational tool designed to help students "
        "and developers understand complex data structures through "
        "beautiful visualizations and step-by-step animations.",
        leftPanel
        );
    QFont descFont;
    descFont.setFamily(titleFont.family());
    descFont.setPointSize(12);
    descriptionLabel->setFont(descFont);
    descriptionLabel->setStyleSheet("color: #6b5b8c; line-height: 1.8;");
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setMaximumWidth(450);

    leftLayout->addWidget(descriptionLabel);
    leftLayout->addSpacing(40);

    // Create "Get Started" button
    getStartedButton = new QPushButton("Get Started →", leftPanel);
    getStartedButton->setFixedSize(220, 55);
    getStartedButton->setCursor(Qt::PointingHandCursor);

    styleButton();

    leftLayout->addWidget(getStartedButton, 0, Qt::AlignLeft);

    // Add bottom spacer
    leftLayout->addStretch(2);

    // Connect button signal
    connect(getStartedButton, &QPushButton::clicked, this, &HomePage::onGetStartedClicked);

    leftPanel->setLayout(leftLayout);
}

void HomePage::setupRightPanel()
{
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setContentsMargins(40, 40, 40, 40);
    rightLayout->setAlignment(Qt::AlignCenter);

    // Create illustration/visualization placeholder
    illustrationLabel = new QLabel(rightPanel);
    illustrationLabel->setAlignment(Qt::AlignCenter);
    illustrationLabel->setMinimumSize(400, 400);

    // Create a visual representation using styled text
    QString illustration =
        "<div style='text-align: center;'>"
        "<div style='font-size: 120px; color: #7b4fff; margin-bottom: 20px;'>📊</div>"
        "<div style='font-size: 80px; color: #9d7fff; margin: 10px;'>🌳</div>"
        "<div style='font-size: 80px; color: #b99fff; margin: 10px;'>📈</div>"
        "<div style='font-size: 80px; color: #d4b8ff; margin: 10px;'>🔗</div>"
        "</div>";

    illustrationLabel->setText(illustration);
    illustrationLabel->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
        "stop:0 rgba(123, 79, 255, 0.08), "
        "stop:1 rgba(212, 184, 255, 0.12)); "
        "border-radius: 20px; "
        "padding: 40px;"
        );

    rightLayout->addWidget(illustrationLabel);

    rightPanel->setLayout(rightLayout);
}

void HomePage::styleButton()
{
    QFont buttonFont;
    buttonFont.setFamily(titleLabel->font().family());
    buttonFont.setPointSize(13);
    buttonFont.setBold(true);
    getStartedButton->setFont(buttonFont);

    QString buttonStyle = R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #7b4fff, stop:1 #9d7fff);
            color: white;
            border: none;
            border-radius: 27px;
            padding: 12px 30px;
            text-align: center;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #6c3cff, stop:1 #8866ff);
        }
        QPushButton:pressed {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #5a32cc, stop:1 #7355dd);
        }
    )";

    getStartedButton->setStyleSheet(buttonStyle);
}

void HomePage::setupAnimations()
{
    // Setup left panel opacity effect
    leftPanelOpacity = new QGraphicsOpacityEffect(this);
    leftPanelOpacity->setOpacity(0.0);

    // Setup left panel animation
    leftPanelAnimation = new QPropertyAnimation(leftPanelOpacity, "opacity", this);
    leftPanelAnimation->setDuration(1200);
    leftPanelAnimation->setStartValue(0.0);
    leftPanelAnimation->setEndValue(1.0);
    leftPanelAnimation->setEasingCurve(QEasingCurve::OutCubic);

    // Setup right panel opacity effect
    rightPanelOpacity = new QGraphicsOpacityEffect(this);
    rightPanelOpacity->setOpacity(0.0);

    // Setup right panel animation
    rightPanelAnimation = new QPropertyAnimation(rightPanelOpacity, "opacity", this);
    rightPanelAnimation->setDuration(1200);
    rightPanelAnimation->setStartValue(0.0);
    rightPanelAnimation->setEndValue(1.0);
    rightPanelAnimation->setEasingCurve(QEasingCurve::OutCubic);
}

void HomePage::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Create a more subtle gradient
    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0.0, QColor(250, 248, 255));    // Very light lavender
    gradient.setColorAt(1.0, QColor(245, 240, 255));    // Slightly darker lavender

    painter.fillRect(rect(), gradient);
}

void HomePage::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    // Start animations only once
    if (!animationsStarted) {
        // Apply opacity effects to panels
        leftPanel->setGraphicsEffect(leftPanelOpacity);
        rightPanel->setGraphicsEffect(rightPanelOpacity);

        leftPanelAnimation->start();

        // Delay right panel animation by 200ms
        QTimer::singleShot(200, [this]() {
            if (rightPanelAnimation) {
                rightPanelAnimation->start();
            }
        });

        animationsStarted = true;
    }
}

void HomePage::onGetStartedClicked()
{
    qDebug() << "Navigating to Main Menu...";
    emit navigateToMenu();
}

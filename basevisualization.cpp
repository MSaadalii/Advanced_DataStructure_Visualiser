#include "basevisualization.h"
#include <QLinearGradient>
#include <QFont>

BaseVisualization::BaseVisualization(const QString &title, QWidget *parent)
    : QWidget(parent)
    , visualizationTitle(title)
    , mainSplitter(nullptr)
    , leftPanel(nullptr)
    , rightPanel(nullptr)
    , leftLayout(nullptr)
    , backButton(nullptr)
    , titleLabel(nullptr)
    , rightTabWidget(nullptr)
    , stepsList(nullptr)
    , algorithmList(nullptr)
    , statusLabel(nullptr)
{
    setMinimumSize(1200, 800);
    setupUI();
}

BaseVisualization::~BaseVisualization()
{
    // Base destructor - subclasses should handle their specific cleanup
}

void BaseVisualization::setupUI()
{
    // Main splitter for left (visualization) and right (controls + trace) panels
    mainSplitter = new QSplitter(Qt::Horizontal, this);
    mainSplitter->setStyleSheet(getSplitterStyle());

    setupVisualizationArea();
    setupRightPanel(); // Pure virtual - implemented by subclasses
    
    // Set splitter proportions (65% visualization, 35% controls+trace)
    mainSplitter->addWidget(leftPanel);
    mainSplitter->addWidget(rightPanel);
    mainSplitter->setSizes({780, 420});
    
    // Main layout
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(mainSplitter);
    setLayout(mainLayout);
}

void BaseVisualization::setupVisualizationArea()
{
    leftPanel = new QWidget();
    leftPanel->setStyleSheet("background: transparent;");
    leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setContentsMargins(40, 30, 20, 30);
    leftLayout->setSpacing(25);

    setupHeader();
}

void BaseVisualization::setupHeader()
{
    // Header with back button and title
    QHBoxLayout *headerLayout = new QHBoxLayout();

    // Back button
    backButton = new QPushButton("← Back to Operations");
    backButton->setFixedSize(180, 45);
    backButton->setCursor(Qt::PointingHandCursor);
    backButton->setStyleSheet(getBackButtonStyle());
    connect(backButton, &QPushButton::clicked, this, &BaseVisualization::onBackClicked);

    // Title
    titleLabel = new QLabel(visualizationTitle);
    QFont titleFont;
    QStringList preferredFonts = {"Segoe UI", "Poppins", "SF Pro Display", "Arial"};
    for (const QString &fontName : preferredFonts) {
        if (QFontDatabase::families().contains(fontName)) {
            titleFont.setFamily(fontName);
            break;
        }
    }
    titleFont.setPointSize(28);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: #2c3e50; background: transparent;");
    titleLabel->setAlignment(Qt::AlignCenter);

    headerLayout->addWidget(backButton, 0, Qt::AlignLeft);
    headerLayout->addStretch();
    headerLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    headerLayout->addStretch();

    leftLayout->addLayout(headerLayout);
}

void BaseVisualization::setupStepTrace()
{
    // Step trace area with tabs
    rightTabWidget = new QTabWidget();
    rightTabWidget->setStyleSheet(R"(
        QTabWidget::pane {
            border: 2px solid #e0e0e0;
            border-radius: 8px;
            background: white;
        }
        QTabBar::tab {
            background: #f8f9fa;
            color: #495057;
            padding: 8px 16px;
            margin-right: 2px;
            border-top-left-radius: 6px;
            border-top-right-radius: 6px;
            font-weight: 500;
        }
        QTabBar::tab:selected {
            background: white;
            color: #7b4fff;
            border-bottom: 2px solid #7b4fff;
        }
        QTabBar::tab:hover:!selected {
            background: #e9ecef;
        }
    )");

    // Steps tab
    QWidget *stepsTab = new QWidget();
    QVBoxLayout *stepsLayout = new QVBoxLayout(stepsTab);
    stepsLayout->setContentsMargins(15, 15, 15, 15);

    QLabel *stepsLabel = createStyledLabel("Operation Steps:", 14);
    stepsLabel->setStyleSheet("font-weight: bold; color: #495057; margin-bottom: 8px;");
    stepsLayout->addWidget(stepsLabel);

    stepsList = new QListWidget();
    stepsList->setStyleSheet(getScrollBarStyle());
    stepsLayout->addWidget(stepsList);

    // Status label
    statusLabel = createStyledLabel("Ready", 12);
    statusLabel->setStyleSheet("color: #28a745; font-weight: bold; padding: 8px; background: #f8f9fa; border-radius: 4px;");
    stepsLayout->addWidget(statusLabel);

    rightTabWidget->addTab(stepsTab, "Steps");

    // Algorithm tab
    QWidget *algorithmTab = new QWidget();
    QVBoxLayout *algorithmLayout = new QVBoxLayout(algorithmTab);
    algorithmLayout->setContentsMargins(15, 15, 15, 15);

    QLabel *algorithmLabel = createStyledLabel("Algorithm Details:", 14);
    algorithmLabel->setStyleSheet("font-weight: bold; color: #495057; margin-bottom: 8px;");
    algorithmLayout->addWidget(algorithmLabel);

    algorithmList = new QListWidget();
    algorithmList->setStyleSheet(getScrollBarStyle());
    algorithmLayout->addWidget(algorithmList);

    rightTabWidget->addTab(algorithmTab, "Algorithm");
}

QPushButton* BaseVisualization::createStyledButton(const QString &text, const QString &color)
{
    QPushButton *button = new QPushButton(text);
    button->setFixedSize(120, 40);
    button->setCursor(Qt::PointingHandCursor);
    button->setStyleSheet(getButtonStyle(color));
    return button;
}

QLabel* BaseVisualization::createStyledLabel(const QString &text, int fontSize)
{
    QLabel *label = new QLabel(text);
    QFont font("Segoe UI", fontSize);
    label->setFont(font);
    return label;
}

void BaseVisualization::addStepToHistory(const QString &step)
{
    if (stepsList) {
        stepsList->addItem(step);
        stepsList->scrollToBottom();
    }
}

void BaseVisualization::addOperationSeparator()
{
    if (stepsList) {
        stepsList->addItem("────────────────────────");
    }
}

void BaseVisualization::setControlsEnabled(bool enabled)
{
    // Base implementation - subclasses can override for specific controls
    // IMPORTANT: Back button should NEVER be disabled - user must always be able to go back!
    if (backButton) {
        backButton->setEnabled(true);  // Always enabled
    }
}

QString BaseVisualization::getButtonStyle(const QString &color)
{
    return QString(R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 %1, stop:1 %2);
            color: white;
            border: none;
            border-radius: 20px;
            font-weight: bold;
            font-size: 12px;
            padding: 8px 16px;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 %3, stop:1 %4);
        }
        QPushButton:pressed {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 %5, stop:1 %6);
        }
        QPushButton:disabled {
            background: #cccccc;
            color: #666666;
        }
    )").arg(color)
       .arg(color == "#7b4fff" ? "#9b6fff" : color)
       .arg(color == "#7b4fff" ? "#6b3fff" : color)
       .arg(color == "#7b4fff" ? "#8b5fff" : color)
       .arg(color == "#7b4fff" ? "#5b2fff" : color)
       .arg(color == "#7b4fff" ? "#7b4fff" : color);
}

QString BaseVisualization::getBackButtonStyle()
{
    return R"(
        QPushButton {
            background-color: rgba(74, 144, 226, 0.1);
            color: #4a90e2;
            border: 2px solid rgba(74, 144, 226, 0.3);
            border-radius: 22px;
            padding: 10px 20px;
            font-family: 'Segoe UI';
            font-size: 13px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: rgba(74, 144, 226, 0.2);
            border-color: #4a90e2;
        }
        QPushButton:pressed {
            background-color: rgba(74, 144, 226, 0.3);
        }
    )";
}

QString BaseVisualization::getSplitterStyle()
{
    return R"(
        QSplitter::handle {
            background-color: #e0e0e0;
            width: 2px;
        }
        QSplitter::handle:hover {
            background-color: #7b4fff;
        }
    )";
}

QString BaseVisualization::getScrollBarStyle()
{
    return R"(
        QListWidget {
            background: white;
            border: 1px solid #e0e0e0;
            border-radius: 6px;
            padding: 8px;
            font-family: 'Segoe UI';
            font-size: 12px;
            selection-background-color: rgba(123, 79, 255, 0.2);
        }
        QListWidget::item {
            padding: 6px;
            border-bottom: 1px solid #f0f0f0;
            color: #495057;
        }
        QListWidget::item:selected {
            background: rgba(123, 79, 255, 0.1);
            color: #7b4fff;
        }
        QScrollBar:vertical {
            background: rgba(0, 0, 0, 0.05);
            width: 8px;
            border-radius: 4px;
            margin: 0;
        }
        QScrollBar::handle:vertical {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 rgba(123, 79, 255, 0.6),
                stop:1 rgba(155, 111, 255, 0.6));
            border-radius: 4px;
            min-height: 20px;
        }
        QScrollBar::handle:vertical:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 rgba(123, 79, 255, 0.8),
                stop:1 rgba(155, 111, 255, 0.8));
        }
        QScrollBar::handle:vertical:pressed {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 rgba(123, 79, 255, 1.0),
                stop:1 rgba(155, 111, 255, 1.0));
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px;
        }
    )";
}

void BaseVisualization::onBackClicked()
{
    emit backToOperations();
}

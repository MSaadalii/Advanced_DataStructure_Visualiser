#include "backbutton.h"

BackButton::BackButton(QWidget *parent)
    : QPushButton("← Back to Operations", parent)
    , m_connectionEstablished(false)
{
    setupButton();
}

BackButton::BackButton(ButtonType type, QWidget *parent)
    : QPushButton(parent)
    , m_connectionEstablished(false)
{
    switch (type) {
        case BackToOperations:
            setText("← Back to Operations");
            break;
        case BackToMenu:
            setText("← Back to Menu");
            break;
    }
    setupButton();
}

BackButton::BackButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
    , m_connectionEstablished(false)
{
    setupButton();
}

BackButton::~BackButton()
{
    // Ensure proper cleanup
    disconnect();
}

void BackButton::setEnabled(bool enabled)
{
    // Back button should ALWAYS be enabled - user must always be able to navigate back
    // Ignore any attempts to disable it
    QPushButton::setEnabled(true);
    
    // Re-apply style to ensure it looks correct
    applyRoundedStyle();
    
    // Re-establish connection to ensure it works
    ensureConnection();
}

void BackButton::setupButton()
{
    // Always ensure button is enabled and visible
    setEnabled(true);
    setVisible(true);
    setFixedSize(180, 45);
    setCursor(Qt::PointingHandCursor);
    setFocusPolicy(Qt::StrongFocus);
    
    // Apply rounded style
    applyRoundedStyle();
    
    // Ensure connection is established
    ensureConnection();
}

void BackButton::applyRoundedStyle()
{
    // Highly rounded style with prominent border-radius (30px for pill shape)
    setStyleSheet(R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 rgba(123, 79, 255, 0.15),
                stop:1 rgba(74, 144, 226, 0.15));
            color: #2d3748;
            border: 2px solid rgba(123, 79, 255, 0.3);
            border-radius: 30px;
            padding: 12px 24px;
            font-family: 'Segoe UI', 'Arial', sans-serif;
            font-size: 13px;
            font-weight: 600;
            min-width: 150px;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 rgba(123, 79, 255, 0.25),
                stop:1 rgba(74, 144, 226, 0.25));
            border: 2px solid rgba(123, 79, 255, 0.5);
            color: #1a202c;
            border-radius: 30px;
        }
        QPushButton:pressed {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 rgba(123, 79, 255, 0.35),
                stop:1 rgba(74, 144, 226, 0.35));
            border: 2px solid rgba(123, 79, 255, 0.6);
            color: #0a0f14;
            border-radius: 30px;
        }
        QPushButton:disabled {
            background: rgba(123, 79, 255, 0.05);
            color: rgba(123, 79, 255, 0.4);
            border: 2px solid rgba(123, 79, 255, 0.15);
            border-radius: 30px;
        }
        QPushButton:focus {
            border: 2px solid rgba(123, 79, 255, 0.7);
            border-radius: 30px;
            outline: none;
        }
    )");
}

void BackButton::ensureConnection()
{
    // Disconnect any existing connections first
    disconnect(this, &QPushButton::clicked, this, &BackButton::onClicked);
    disconnect(this, &QPushButton::clicked, this, &BackButton::onButtonClicked);
    
    // Establish robust connection using both methods
    bool connected1 = connect(this, &QPushButton::clicked, this, &BackButton::onClicked, Qt::UniqueConnection);
    bool connected2 = connect(this, &QPushButton::clicked, this, &BackButton::onButtonClicked, Qt::UniqueConnection);
    
    m_connectionEstablished = connected1 || connected2;
    
    if (!m_connectionEstablished) {
        // Fallback: use old-style connection
        connect(this, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
        m_connectionEstablished = true;
    }
}

void BackButton::showEvent(QShowEvent *event)
{
    QPushButton::showEvent(event);
    // Always ensure button is enabled and styled correctly when shown
    QPushButton::setEnabled(true);
    applyRoundedStyle();
    ensureConnection();
    setCursor(Qt::PointingHandCursor);
}

void BackButton::enterEvent(QEnterEvent *event)
{
    QPushButton::enterEvent(event);
    setCursor(Qt::PointingHandCursor);
}

void BackButton::leaveEvent(QEvent *event)
{
    QPushButton::leaveEvent(event);
    setCursor(Qt::ArrowCursor);
}

void BackButton::onClicked()
{
    // Primary handler
    if (isEnabled() && isVisible()) {
        emit backRequested();
    }
}

void BackButton::onButtonClicked()
{
    // Backup handler - ensures it always works
    if (isEnabled() && isVisible()) {
        emit backRequested();
    }
}
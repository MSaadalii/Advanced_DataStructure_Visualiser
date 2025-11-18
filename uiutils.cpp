#include "uiutils.h"

QString UIUtils::getButtonStyle(const QString &color)
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

QString UIUtils::getBackButtonStyle()
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

QString UIUtils::getScrollBarStyle()
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

QPushButton* UIUtils::createStyledButton(const QString &text, const QString &color)
{
    QPushButton *button = new QPushButton(text);
    button->setFixedSize(120, 40);
    button->setCursor(Qt::PointingHandCursor);
    button->setStyleSheet(getButtonStyle(color));
    return button;
}

BackButton* UIUtils::createBackButton(BackButton::ButtonType type)
{
    return new BackButton(type);
}

BackButton* UIUtils::createBackButton(const QString &text)
{
    return new BackButton(text);
}

QLabel* UIUtils::createTitleLabel(const QString &title)
{
    QLabel *label = new QLabel(title);
    QFont titleFont = getPreferredFont(28, true);
    label->setFont(titleFont);
    label->setStyleSheet("color: #2c3e50; background: transparent;");
    label->setAlignment(Qt::AlignCenter);
    return label;
}

QLabel* UIUtils::createStyledLabel(const QString &text, int fontSize)
{
    QLabel *label = new QLabel(text);
    QFont font = getPreferredFont(fontSize);
    label->setFont(font);
    return label;
}

QFont UIUtils::getPreferredFont(int size, bool bold)
{
    QFont font;
    QStringList preferredFonts = {"Segoe UI", "Poppins", "SF Pro Display", "Arial"};
    for (const QString &fontName : preferredFonts) {
        if (QFontDatabase::families().contains(fontName)) {
            font.setFamily(fontName);
            break;
        }
    }
    font.setPointSize(size);
    font.setBold(bold);
    return font;
}
